#ifndef CBUNIFIEDCTRL_H
#define CBUNIFIEDCTRL_H

#include "cbDiffCtrl.h"

class cbStyledTextCtrl;

class cbUnifiedCtrl : public cbDiffCtrl
{
public:
    cbUnifiedCtrl(wxWindow* parent);
    virtual ~cbUnifiedCtrl();
    virtual void Init(cbDiffColors colset);
    virtual void SetHlang(wxString lang);
    virtual void ShowDiff(wxDiff diff);
private:
    cbStyledTextCtrl* m_txtctrl;
};

#endif // CBUNIFIEDCTRL_H
