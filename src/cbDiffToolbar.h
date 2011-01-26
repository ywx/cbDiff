#ifndef CBDIFFTOOLBAR_H
#define CBDIFFTOOLBAR_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class cbDiffEditor;

class cbDiffToolbar : public wxPanel
{
public:
    cbDiffToolbar(cbDiffEditor* parent, int viewmode, wxString hlang);
    virtual ~cbDiffToolbar();
protected:
private:
    /// IDs
    enum
    {
        ID_BBRELOAD = 1545,
        ID_BBSWAP,
        ID_CHLANG
    };
    cbDiffEditor* m_parent;
    wxBitmapButton* BBTable;
    wxBitmapButton* BBUnified;
    wxBitmapButton* BBSideBySide;
    wxChoice* CHLang;

    wxString m_lasthlang;

    void OnButton(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif // CBDIFFTOOLBAR_H
