#include "cbDiffMenu.h"

#include <wx/filedlg.h>

#include "cbDiffUtils.h"
#include "cbDiffEditor.h"

#include <projectmanager.h>
#include <editormanager.h>
#include <cbproject.h>
#include <cbeditor.h>

#define IDSTART (wxID_HIGHEST + 20000)

using namespace cbDiffUtils;

namespace
{
    const long ID_SELECT_FIRST = wxNewId();
    const long ID_SELECT_SECOND = wxNewId();
    const long ID_SELECT_LOCAL = wxNewId();
}


BEGIN_EVENT_TABLE(cbDiffMenu, wxMenu)
END_EVENT_TABLE()

cbDiffMenu::cbDiffMenu(wxEvtHandler* parent, wxString basefile, bool &prevSelectionValid, wxString &prevFileName, std::vector<long> &ids):
    wxMenu(),
    m_basefile(basefile),
    m_ids(ids),
    m_prevValid(prevSelectionValid),
    m_prevFileName(prevFileName)
{
    if(m_prevValid == false)
    {
        Append(ID_SELECT_FIRST, _("Compare to"));

        parent->Connect(ID_SELECT_FIRST, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cbDiffMenu::OnSelectFirst, NULL, this);
    }
    else
    {
        Append(ID_SELECT_SECOND, _("Compare"));
        Append(ID_SELECT_FIRST, _("Reselect first"));

        parent->Connect(ID_SELECT_SECOND, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cbDiffMenu::OnSelectSecond, NULL, this);
        parent->Connect(ID_SELECT_FIRST, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cbDiffMenu::OnSelectFirst, NULL, this);
    }

    // the project or NULL
    ProjectFile* file = IsFileInActiveProject(basefile);
    m_projectfilenames = GetActiveProjectFilesAbsolute(file);
    m_openfilenames = cbDiffUtils::GetOpenFilesLong(basefile);

    unsigned int projectFiles = m_projectfilenames.GetCount();
    unsigned int openFiles = m_openfilenames.GetCount();

    wxArrayString shortnames = GetActiveProjectFilesRelative(file);



    while (m_ids.size() < projectFiles + openFiles)
            m_ids.push_back(wxNewId());

    // project open?
    if(projectFiles)
    {
        wxMenu* projmenu = new wxMenu();
        for(unsigned int i = 0; i < shortnames.GetCount(); ++i)
        {
            projmenu->Append(m_ids[i], shortnames[i]);
            parent->Connect(m_ids[i],wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&cbDiffMenu::OnSelectProject, NULL, this);
        }
        AppendSubMenu(projmenu, _("Project files"));
    }


    shortnames = cbDiffUtils::GetOpenFilesShort(basefile);
    // files open?
    if(openFiles)
    {
        wxMenu* openmenu = new wxMenu();
        for(unsigned int i = 0; i < openFiles; i++)
        {
            openmenu->Append(m_ids[i+projectFiles], shortnames[i]);
            parent->Connect(m_ids[i+projectFiles],wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&cbDiffMenu::OnSelectOpen, NULL, this);
        }
        AppendSubMenu(openmenu, _("Open files"));
    }




    Append(ID_SELECT_LOCAL, _("Local file..."));
    parent->Connect(ID_SELECT_LOCAL, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction)&cbDiffMenu::OnSelectLocal, NULL, this);

}

cbDiffMenu::~cbDiffMenu()
{
    Destroy(FindItem(_("Project files")));
    Destroy(FindItem(_("Open files")));
}

void cbDiffMenu::OnSelectOpen(wxCommandEvent& event)
{

}

void cbDiffMenu::OnSelectProject(wxCommandEvent& event)
{
    if(!wxFileExists(m_basefile))
        return;

    unsigned int idx = 0;
    std::vector<long>::iterator it;
    for( it = m_ids.begin() ; it < m_ids.end(); ++it )
    {
        if (*it == event.GetId())
            break;
    }
    if ( it == m_ids.end() ) return;

    if(idx < m_projectfilenames.GetCount() && wxFileExists(m_projectfilenames[idx]))
        new cbDiffEditor(m_basefile, m_projectfilenames[idx]);
}

void cbDiffMenu::OnSelectLocal(wxCommandEvent& event)
{
    if(!wxFileExists(m_basefile))
        return;

    wxFileDialog selfile(Manager::Get()->GetAppWindow(), _("Select file"),
                         wxEmptyString, wxEmptyString,
                         wxFileSelectorDefaultWildcardStr,
                         wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_PREVIEW);

    if(selfile.ShowModal() == wxID_OK)
        new cbDiffEditor(m_basefile, selfile.GetPath());
}

void cbDiffMenu::OnSelectFirst(wxCommandEvent& event)
{
    m_prevFileName = m_basefile;
    m_prevValid = true;

}

void cbDiffMenu::OnSelectSecond(wxCommandEvent& event)
{
    if ( m_prevValid )
    {
        new cbDiffEditor(m_prevFileName, m_basefile);
    }
    m_prevValid = false;
}
