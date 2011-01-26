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

BEGIN_EVENT_TABLE(cbDiffMenu, wxMenu)
END_EVENT_TABLE()

cbDiffMenu::cbDiffMenu(wxEvtHandler* parent, wxString basefile) : wxMenu()
{
    m_basefile = basefile;
    m_localid = IDSTART;

    // the project or NULL
    ProjectFile* file = IsFileInActiveProject(basefile);
    wxArrayString shortnames = GetActiveProjectFilesRelative(file);
    m_projectfilenames = GetActiveProjectFilesAbsolute(file);

    // project open?
    if(shortnames.GetCount())
    {
        wxMenu* projmenu = new wxMenu();
        for(unsigned int i = 0; i < shortnames.GetCount(); i++, m_localid++)
            projmenu->Append(m_localid, shortnames[i]);
        AppendSubMenu(projmenu, _("Project files"));
    }

    shortnames = cbDiffUtils::GetOpenFilesShort(basefile);
    m_openfilenames = cbDiffUtils::GetOpenFilesLong(basefile);

    // files open?
    if(shortnames.GetCount())
    {
        wxMenu* openmenu = new wxMenu();
        for(unsigned int i = 0; i < shortnames.GetCount(); i++, m_localid++)
            openmenu->Append(m_localid, shortnames[i]);
        AppendSubMenu(openmenu, _("Open files"));
    }

    Append(m_localid, _("Local file..."));

    // On MSW the only way to get our events is to catch all events
    // so we use this "global" connect and then we look if the event is for us
    parent->Connect(wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction)&cbDiffMenu::OnSelect, NULL, this);
}

cbDiffMenu::~cbDiffMenu()
{
    Destroy(FindItem(_("Project files")));
    Destroy(FindItem(_("Open files")));
}

void cbDiffMenu::OnSelect(wxCommandEvent& event)
{
	if(event.GetId() < IDSTART || event.GetId() > m_localid)
        return event.Skip();

    if(!wxFileExists(m_basefile))
        return;

    // want to select a local file
    if(event.GetId() == m_localid)
    {
        wxFileDialog selfile(Manager::Get()->GetAppWindow(), _("Select file"),
                             wxEmptyString, wxEmptyString,
                             wxFileSelectorDefaultWildcardStr,
                             wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_PREVIEW);
        if(selfile.ShowModal() == wxID_OK)
            new cbDiffEditor(m_basefile, selfile.GetPath());
        return;
    }

    // helpers to differentiate between project and openfiles menuids
    int realid = event.GetId() - IDSTART;
    int idbreak = m_projectfilenames.GetCount();
    int realopenid = realid - idbreak;

    // projectfile selected
    if(realid < idbreak &&
       wxFileExists(m_projectfilenames[realid]))
    {
        new cbDiffEditor(m_basefile,
                         m_projectfilenames[realid]);
    }
    // openfile selected
    else if(realid >= idbreak &&
            wxFileExists(m_openfilenames[realopenid]))
    {
        new cbDiffEditor(m_basefile,
                         m_openfilenames[realopenid]);
    }
}
