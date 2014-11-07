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

namespace {

    /// IDs
    const long int ID_BBRELOAD = wxNewId();
    const long int ID_BBSWAP = wxNewId();
    const long int ID_BUTTON_TABLE = wxNewId();
    const long int ID_BUTTON_UNIFIED = wxNewId();
    const long int ID_BUTTON_SIDEBYSIDE = wxNewId();

};

BEGIN_EVENT_TABLE(cbDiffToolbar, wxEvtHandler)
END_EVENT_TABLE()

cbDiffToolbar::cbDiffToolbar(cbDiffEditor* parent,
                             int viewmode)
                             : wxPanel(parent), m_parent(parent)
{
    BBTable = new wxBitmapButton(this, ID_BUTTON_TABLE,
                                 wxGetBitmapFromMemory(table),
                                 wxDefaultPosition,
                                 wxDefaultSize,
                                 wxBU_AUTODRAW);
    BBTable->SetToolTip(_("Display as a table"));
    BBUnified = new wxBitmapButton(this, ID_BUTTON_UNIFIED,
                                  wxGetBitmapFromMemory(unified),
                                  wxDefaultPosition,
                                  wxDefaultSize, wxBU_AUTODRAW);
    BBUnified->SetToolTip(_("Display as unified diff"));
    BBSideBySide = new wxBitmapButton(this, ID_BUTTON_SIDEBYSIDE,
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

    wxBoxSizer* boxsizer = new wxBoxSizer(wxHORIZONTAL);
    boxsizer->Add(BBTable, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBUnified, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBSideBySide, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(-1,-1,0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBReload, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(BBSwap, 0, wxALL|wxALIGN_CENTER, 5);
    boxsizer->Add(-1,-1,0, wxALL|wxALIGN_CENTER, 5);
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
    else
    {
        if (event.GetId() == ID_BUTTON_TABLE)
        {
            if ( m_parent->GetMode() != cbDiffEditor::TABLE)
            {
                m_parent->SetMode(cbDiffEditor::TABLE);
                BBTable->Enable(false);
		        BBUnified->Enable();
		        BBSideBySide->Enable();
            }
        }
        else if (event.GetId() == ID_BUTTON_UNIFIED)
        {
            if ( m_parent->GetMode() != cbDiffEditor::UNIFIED)
            {
                m_parent->SetMode(cbDiffEditor::UNIFIED);
		        BBTable->Enable();
                BBUnified->Enable(false);
		        BBSideBySide->Enable();
            }
        }
        else if (event.GetId() == ID_BUTTON_SIDEBYSIDE)
        {
            if ( m_parent->GetMode() != cbDiffEditor::SIDEBYSIDE)
            {
                m_parent->SetMode(cbDiffEditor::SIDEBYSIDE);
		        BBTable->Enable();
		        BBUnified->Enable();
                BBSideBySide->Enable(false);
            }
        }
    }

    m_parent->Reload();
}

