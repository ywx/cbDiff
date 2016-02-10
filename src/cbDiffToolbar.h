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
    cbDiffToolbar(cbDiffEditor* parent, int viewmode);
    virtual ~cbDiffToolbar();
protected:
private:
    cbDiffEditor* m_parent;
    wxBitmapButton* BBTable;
    wxBitmapButton* BBUnified;
    wxBitmapButton* BBSideBySide;

    void OnButton(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif // CBDIFFTOOLBAR_H
