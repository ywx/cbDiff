#ifndef CBDIFFTOOLBAR_H
#define CBDIFFTOOLBAR_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#ifdef UseWxToolbar
    #define isUseWxToolbar 1
#else
    #define isUseWxToolbar 0
#endif

#ifdef UseWxAuiToolbar
    #define isUseWxAuiToolbar 1
#else
    #define isUseWxAuiToolbar 0
#endif

#if ( wxCHECK_VERSION(3, 0, 0) || isUseWxAuiToolbar )
#include "wx/aui/aui.h"
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
#if isUseWxAuiToolbar
    wxAuiToolBar* toolbar;
#else
    #if ( wxCHECK_VERSION(3, 0, 0) || isUseWxToolbar )
    wxToolBar* toolbar;
    #else
    wxBitmapButton* BBTable;
    wxBitmapButton* BBUnified;
    wxBitmapButton* BBSideBySide;
    #endif
#endif
    wxChoice* CHLang;

    wxString m_lasthlang;

    void OnButton(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif // CBDIFFTOOLBAR_H
