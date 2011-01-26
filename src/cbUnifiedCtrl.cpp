#include "cbUnifiedCtrl.h"

#include <manager.h>
#include <editormanager.h>
#include <configmanager.h>
#include <logmanager.h>
#include <cbstyledtextctrl.h>
#include <cbeditor.h>

cbUnifiedCtrl::cbUnifiedCtrl(wxWindow* parent) : cbDiffCtrl(parent)
{
    wxBoxSizer* BoxSizer = new wxBoxSizer(wxHORIZONTAL);
    m_txtctrl = new cbStyledTextCtrl(this, wxID_ANY);
    BoxSizer->Add(m_txtctrl, 1, wxEXPAND|wxALIGN_CENTER, 0);
    SetSizer(BoxSizer);
}

cbUnifiedCtrl::~cbUnifiedCtrl()
{
}


void cbUnifiedCtrl::Init(cbDiffColors colset)
{
    cbEditor::ApplyStyles(m_txtctrl);
    m_txtctrl->SetMargins(0,0);
    m_txtctrl->SetMarginWidth(0,0);    // don't show linenumber
    m_txtctrl->SetMarginWidth(1,0);    // don't show +-= symbol margin
    m_txtctrl->SetMarginWidth(2,0);    // to hide the change and fold
    m_txtctrl->SetMarginWidth(3,0);    // margin made by cbEditor::ApplyStyles
    m_theme->Apply(_T("DiffPatch"), m_txtctrl);
}

void cbUnifiedCtrl::SetHlang(wxString lang)
{
    // Nothing todo, because the highlight language is always DiffPatch
}

void cbUnifiedCtrl::ShowDiff(wxDiff diff)
{
    m_txtctrl->SetReadOnly(false);
    m_txtctrl->ClearAll();
    m_txtctrl->AppendText(diff.GetDiff());
    m_txtctrl->SetReadOnly(true);
}
