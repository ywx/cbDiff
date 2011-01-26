#include "cbDiffToolbar.h"

#include "cbDiffEditor.h"

#include <manager.h>
#include <editormanager.h>
#include <logmanager.h>
#include "cbDiffUtils.h"

/// bitmaps
#include "../images/swap.h"
#include "../images/reload.h"
#include "../images/table.h"
#include "../images/unified.h"
#include "../images/sidebyside.h"



BEGIN_EVENT_TABLE(cbDiffToolbar, wxEvtHandler)
END_EVENT_TABLE()

cbDiffToolbar::cbDiffToolbar(cbDiffEditor* parent,
                             int viewmode,
                             wxString hlang)
                             : wxPanel(parent), m_parent(parent)
{
    BBTable = new wxBitmapButton(this, cbDiffEditor::TABLE,
                                 wxGetBitmapFromMemory(table),
                                 wxDefaultPosition,
                                 wxDefaultSize,
                                 wxBU_AUTODRAW);
    BBTable->SetToolTip(_("Display as a table"));
    BBUnified = new wxBitmapButton(this, cbDiffEditor::UNIFIED,
                                  wxGetBitmapFromMemory(unified),
                                  wxDefaultPosition,
                                  wxDefaultSize, wxBU_AUTODRAW);
    BBUnified->SetToolTip(_("Display as unified diff"));
    BBSideBySide = new wxBitmapButton(this, cbDiffEditor::SIDEBYSIDE,
                               wxGetBitmapFromMemory(sidebyside),
                               wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    BBSideBySide->SetToolTip(_("Display side by side"));

    wxBitmapButton* BBReload = new wxBitmapButton(this, ID_BBRELOAD,
                                wxGetBitmapFromMemory(reload),
                                wxDefaultPosition, wxDefaultSize,
                                wxBU_AUTODRAW);
    BBReload->SetToolTip(_("Reload files"));
    wxBitmapButton* BBSwap = new wxBitmapButton(this, ID_BBSWAP,
                                    wxGetBitmapFromMemory(swap),
                                    wxDefaultPosition, wxDefaultSize,
                                    wxBU_AUTODRAW);
    BBSwap->SetToolTip(_("Swap files"));

    CHLang = new wxChoice(this, ID_CHLANG);
    CHLang->Append(cbDiffUtils::GetAllHighlightLanguages());
    if(hlang == wxEmptyString)
        CHLang->SetStringSelection(_("Plain text"));
    else
        CHLang->SetStringSelection(hlang);

    wxBoxSizer* boxsizer = new wxBoxSizer(wxHORIZONTAL);
    boxsizer->Add(BBTable, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBUnified, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBSideBySide, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(-1,-1,0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBReload, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBSwap, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(-1,-1,0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(CHLang, 0, wxALL|wxALIGN_CENTER, 5);
    SetSizer(boxsizer);
    boxsizer->Layout();

    switch (viewmode)
    {
    case cbDiffEditor::TABLE:
        BBTable->Enable(false);
        break;
    case cbDiffEditor::UNIFIED:
        BBUnified->Enable(false);
        break;
    case cbDiffEditor::SIDEBYSIDE:
        BBSideBySide->Enable(false);
        break;
    default:
        break;
    }

    Connect(wxEVT_COMMAND_BUTTON_CLICKED,
            (wxObjectEventFunction)&cbDiffToolbar::OnButton);
    Connect(wxEVT_COMMAND_CHOICE_SELECTED,
            (wxObjectEventFunction)&cbDiffToolbar::OnChoice);
}

cbDiffToolbar::~cbDiffToolbar()
{
    //dtor
}

void cbDiffToolbar::OnButton(wxCommandEvent& event)
{
    if(event.GetId() == ID_BBSWAP)
    {
        m_parent->Swap();
        return;
    }
    else if(event.GetId() != m_parent->GetMode() &&
           (event.GetId() == cbDiffEditor::TABLE ||
            event.GetId() == cbDiffEditor::UNIFIED ||
            event.GetId() == cbDiffEditor::SIDEBYSIDE))
    {
        BBTable->Enable();
        BBUnified->Enable();
        BBSideBySide->Enable();
        CHLang->Enable();
        CHLang->SetStringSelection(m_lasthlang);
        m_parent->SetMode(event.GetId());
        m_parent->SetHlang(m_lasthlang);
        switch (event.GetId())
        {
        case cbDiffEditor::TABLE:
            BBTable->Enable(false);
            break;
        case cbDiffEditor::UNIFIED:
            BBUnified->Enable(false);
            m_lasthlang = CHLang->GetStringSelection();
            CHLang->SetStringSelection(_T("Diff/Patch"));
            CHLang->Disable();
            break;
        case cbDiffEditor::SIDEBYSIDE:
            BBSideBySide->Enable(false);
            break;
        default:
            break;
        }
    }
    m_parent->Reload();
}

void cbDiffToolbar::OnChoice(wxCommandEvent& event)
{
    m_lasthlang = event.GetString();
    m_parent->SetHlang(event.GetString());
}
