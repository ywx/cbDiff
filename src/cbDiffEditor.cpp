#include "cbDiffEditor.h"

#include <manager.h>
#include <editormanager.h>
#include <configmanager.h>
#include <logmanager.h>
#include <cbeditor.h>

#include "wxDiff.h"

#include "cbDiffToolbar.h"

/// diffctrls
#include "cbTableCtrl.h"
#include "cbUnifiedCtrl.h"
#include "cbSideBySideCtrl.h"

//! static Editor set
cbDiffEditor::EditorsSet cbDiffEditor::m_AllEditors;

BEGIN_EVENT_TABLE(cbDiffEditor,EditorBase)
    EVT_CONTEXT_MENU(cbDiffEditor::OnContextMenu)
END_EVENT_TABLE()

cbDiffEditor::cbDiffEditor(const wxString& firstfile,
                           const wxString& secondfile,
                           int viewmode,
                           wxString hlang)
    : EditorBase((wxWindow*)Manager::Get()->GetEditorManager()->GetNotebook(),
                 firstfile + secondfile),
      m_diffctrl(0)
{
    m_fromfile = firstfile;
    m_tofile = secondfile;

    m_colorset.m_addedlines = wxColour(0,255,0,50);
    m_colorset.m_removedlines = wxColour(255,0,0,50);
    m_colorset.m_caretlinetype = 0;
    m_colorset.m_caretline = wxColor(122,122,0);

    ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("cbdiffsettings"));
    if (cfg)
    {
        wxColour add = cfg->ReadColour(_T("addedlines"), wxColour(0,255,0,50));
        int addalpha = cfg->ReadInt(_T("addedlinesalpha"), 50);
        wxColour rem = cfg->ReadColour(_T("removedlines"), wxColour(255,0,0,50));
        int remalpha = cfg->ReadInt(_T("removedlinesalpha"), 50);
        m_colorset.m_caretlinetype = cfg->ReadInt(_T("caretlinetype"));
        wxColour car = cfg->ReadColour(_T("caretline"), wxColor(122,122,0));
        int caralpha = cfg->ReadInt(_T("caretlinealpha"), 50);
        m_colorset.m_addedlines = wxColour(add.Red(), add.Green(),
                                           add.Blue(), addalpha);
        m_colorset.m_removedlines = wxColour(rem.Red(), rem.Green(),
                                             rem.Blue(), remalpha);
        m_colorset.m_caretline = wxColour(car.Red(), car.Green(),
                                          car.Blue(), caralpha);

        if(viewmode == DEFAULT)
        {
            viewmode = cfg->ReadInt(_T("viewmode"), 0) + TABLE;
            hlang = cfg->Read(_T("hlang"), _("Plain Text"));
        }
    }
    m_colorset.m_hlang = hlang;

    cbDiffToolbar* difftoolbar = new cbDiffToolbar(this, viewmode, hlang);

    wxBoxSizer* BoxSizer = new wxBoxSizer(wxVERTICAL);
    BoxSizer->Add(difftoolbar, 0, wxALL|wxEXPAND|wxALIGN_CENTER, 0);
    SetSizer(BoxSizer);
    SetMode(viewmode);

    m_AllEditors.insert(this);

    ShowDiff();

    difftoolbar->Layout();
    m_diffctrl->Layout();
    BoxSizer->Layout();
    Layout();
}

cbDiffEditor::~cbDiffEditor()
{
    m_AllEditors.erase(this);
}

void cbDiffEditor::ShowDiff()
{
    /* Diff creation */
    wxDiff diff(m_fromfile, m_tofile);
    SetTitle(_T("Diff: ") +
             wxFileNameFromPath(m_fromfile) +
             _T(" ") +
             wxFileNameFromPath(m_tofile));

    wxString different = diff.IsDifferent();
    if(different != wxEmptyString)
        cbMessageBox(different, _("cbDiff"));

    m_diffctrl->ShowDiff(diff);
}

bool cbDiffEditor::Save()
{
    ConfigManager* mgr = Manager::Get()->GetConfigManager(_T("app"));
    wxString Path = wxGetCwd();
    wxString Filter;
    if(mgr && Path.IsEmpty())
    {
        Path = mgr->Read(_T("/file_dialogs/save_file_as/directory"), Path);
    }
    wxFileDialog dlg(Manager::Get()->GetAppWindow(),
                     _("Save file"),
                     Path,
                     wxEmptyString,
                     _("Diff files (*.diff)|*.diff"),
                     wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    PlaceWindow(&dlg);
    if (dlg.ShowModal() != wxID_OK)
    {
        // cancelled out
        return false;
    }
    wxString Filename = dlg.GetPath();

    // store the last used directory
    if(mgr)
    {
        wxString Test = dlg.GetDirectory();
        mgr->Write(_T("/file_dialogs/save_file_as/directory"),
                   dlg.GetDirectory());
    }

    if(!cbSaveToFile(Filename, m_diff))
    {
        wxString msg;
        msg.Printf(_("File %s could not be saved..."), GetFilename().c_str());
        cbMessageBox(msg, _("Error saving file"), wxICON_ERROR);
        return false; // failed; file is read-only?
    }
    return true;;
}

bool cbDiffEditor::SaveAs()
{
    return Save();
}

void cbDiffEditor::Swap()
{
    wxString temp = m_fromfile;
    m_fromfile = m_tofile;
    m_tofile = temp;
    Reload();
}

void cbDiffEditor::Reload()
{
    if(!m_fromfile.IsEmpty() && !m_tofile.IsEmpty())
        ShowDiff();
}

int cbDiffEditor::GetMode()
{
    return m_viewingmode;
}

void cbDiffEditor::SetMode(int mode)
{
    if(m_diffctrl)
    {
        GetSizer()->Detach(m_diffctrl);
        wxDELETE(m_diffctrl);
    }
    if(mode == TABLE)
        m_diffctrl = new cbTableCtrl(this);
    else if(mode == UNIFIED)
        m_diffctrl = new cbUnifiedCtrl(this);
    else if(mode == SIDEBYSIDE)
        m_diffctrl = new cbSideBySideCtrl(this);

    GetSizer()->Add(m_diffctrl, 2, wxALL|wxEXPAND|wxALIGN_CENTER, 0);
    GetSizer()->Layout();
    m_diffctrl->Init(m_colorset);
    m_viewingmode = mode;
}

void cbDiffEditor::SetHlang(wxString lang)
{
    m_colorset.m_hlang = lang;
    m_diffctrl->SetHlang(lang);
}


void cbDiffEditor::CloseAllEditors()
{
    EditorsSet s = m_AllEditors;
    for (EditorsSet::iterator i = s.begin(); i != s.end(); ++i )
    {
        EditorManager::Get()->QueryClose(*i);
        (*i)->Close();
    }
    assert(m_AllEditors.empty());
}
