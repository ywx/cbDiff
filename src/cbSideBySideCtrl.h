#ifndef CBSIDEBYSIDECTRL_H
#define CBSIDEBYSIDECTRL_H

#include "cbDiffCtrl.h"

class LineChangedTimer;
class cbStyledTextCtrl;

class cbSideBySideCtrl : public cbDiffCtrl
{
public:
    cbSideBySideCtrl(wxWindow* parent);
    virtual ~cbSideBySideCtrl();
    virtual void Init(cbDiffColors colset);
    virtual void SetHlang(wxString lang);
    virtual void ShowDiff(wxDiff diff);
    void Synchronize();
private:
    cbStyledTextCtrl* TCLeft;
    cbStyledTextCtrl* TCRight;

    wxScrollBar* VScrollBar;
    wxScrollBar* HScrollBar;

    int m_vscrollpos;
    int m_hscrollpos;

    LineChangedTimer* m_timer;
    DECLARE_EVENT_TABLE()
};

#endif // CBSIDEBYSIDECTRL_H
