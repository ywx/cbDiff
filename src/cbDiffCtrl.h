#ifndef CBDIFFCTRL_H
#define CBDIFFCTRL_H

#include <wx/panel.h>

#include <configmanager.h>
#include <editorcolourset.h>

#include "cbDiffEditor.h"
#include "wxDiff.h"

class cbDiffCtrl: public wxPanel
{
public:
    cbDiffCtrl(wxWindow* parent)
    : wxPanel(parent, -1, wxPoint(1000, 1000)), m_theme(0)
    {
        m_theme = new EditorColourSet(
                      Manager::Get()->GetConfigManager(_T("editor"))->
                      Read(_T("/colour_sets/active_colour_set"),
                      COLORSET_DEFAULT));
    }
    virtual ~cbDiffCtrl() { wxDELETE(m_theme); }
    virtual void Init(cbDiffColors colset) = 0;
    virtual void SetHlang(wxString lang) = 0;
    virtual void ShowDiff(wxDiff diff) = 0;
protected:
    EditorColourSet* m_theme;
private:
    DECLARE_EVENT_TABLE()
};

#endif // CBDIFFCTRL_H
