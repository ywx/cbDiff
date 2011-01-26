#ifndef CBDIFFMENU_H
#define CBDIFFMENU_H

#include <wx/menu.h>

class cbDiffMenu : public wxMenu
{
public:
    cbDiffMenu(wxEvtHandler* parent, wxString basefile);
    virtual ~cbDiffMenu();
private:
    wxString m_basefile;
    wxArrayString m_projectfilenames;
    wxArrayString m_openfilenames;

    int m_localid;

    void OnSelect(wxCommandEvent& event);
    DECLARE_EVENT_TABLE();
};

#endif // CBDIFFMENU_H
