#ifndef CBDIFFMENU_H
#define CBDIFFMENU_H

#include <wx/menu.h>
#include <vector>

class cbDiffMenu : public wxMenu
{
public:
    cbDiffMenu(wxEvtHandler* parent, wxString basefile, bool &prevSelected, wxString &prevFileName, std::vector<long> &ids);
    virtual ~cbDiffMenu();
private:
    wxString m_basefile;
    wxArrayString m_projectfilenames;
    wxArrayString m_openfilenames;

    std::vector<long> &m_ids;

    bool &m_prevValid;
    wxString &m_prevFileName;

    void OnSelectProject(wxCommandEvent& event);
    void OnSelectOpen(wxCommandEvent& event);
    void OnSelectLocal(wxCommandEvent& event);
    void OnSelectFirst(wxCommandEvent& event);
    void OnSelectSecond(wxCommandEvent& event);
    DECLARE_EVENT_TABLE();
};

#endif // CBDIFFMENU_H
