#include "cbDiffConfigPanel.h"

//(*InternalHeaders(cbDiffConfigPanel)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/slider.h>
#include <wx/intl.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/radiobox.h>
//*)
#include <wx/colordlg.h>

#include <configmanager.h>

#include "cbDiffUtils.h"

//(*IdInit(cbDiffConfigPanel)
const long cbDiffConfigPanel::ID_BUTTON2 = wxNewId();
const long cbDiffConfigPanel::ID_STATICTEXT1 = wxNewId();
const long cbDiffConfigPanel::ID_SLIDER1 = wxNewId();
const long cbDiffConfigPanel::ID_BUTTON1 = wxNewId();
const long cbDiffConfigPanel::ID_STATICTEXT2 = wxNewId();
const long cbDiffConfigPanel::ID_SLIDER2 = wxNewId();
const long cbDiffConfigPanel::ID_CHOICE1 = wxNewId();
const long cbDiffConfigPanel::ID_BUTTON3 = wxNewId();
const long cbDiffConfigPanel::ID_STATICTEXT3 = wxNewId();
const long cbDiffConfigPanel::ID_SLIDER3 = wxNewId();
const long cbDiffConfigPanel::ID_RADIOBOX1 = wxNewId();
const long cbDiffConfigPanel::ID_CHOICE2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(cbDiffConfigPanel, cbConfigurationPanel)
	//(*EventTable(cbDiffConfigPanel)
	//*)
END_EVENT_TABLE()

cbDiffConfigPanel::cbDiffConfigPanel(wxWindow* parent)
{
	//(*Initialize(cbDiffConfigPanel)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer5;
	wxBoxSizer* BoxSizer2;
	wxStaticText* StaticText1;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxBoxSizer* BoxSizer1;
	wxStaticText* StaticText2;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Added Lines:"));
	BColAdd = new wxButton(this, ID_BUTTON2, _("Colour"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticBoxSizer2->Add(BColAdd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Alpha:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticBoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SLAddAlpha = new wxSlider(this, ID_SLIDER1, 50, 0, 255, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
	StaticBoxSizer2->Add(SLAddAlpha, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Removed Lines:"));
	BColRem = new wxButton(this, ID_BUTTON1, _("Colour"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBoxSizer1->Add(BColRem, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Alpha:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBoxSizer1->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SLRemAlpha = new wxSlider(this, ID_SLIDER2, 50, 0, 255, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER2"));
	StaticBoxSizer1->Add(SLRemAlpha, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Caret Line:"));
	CHCaret = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	CHCaret->SetSelection( CHCaret->Append(_("Underline")) );
	CHCaret->Append(_("Background"));
	StaticBoxSizer3->Add(CHCaret, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BColCar = new wxButton(this, ID_BUTTON3, _("Colour"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer2->Add(BColCar, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Alpha:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer2->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SLCarAlpha = new wxSlider(this, ID_SLIDER3, 50, 0, 255, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER3"));
	BoxSizer2->Add(SLCarAlpha, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer1->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("Default values:"));
	wxString __wxRadioBoxChoices_1[3] =
	{
		_("Tabular"),
		_("Unified Diff"),
		_("Side by side")
	};
	RBViewing = new wxRadioBox(this, ID_RADIOBOX1, _("Displaytype:"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 1, wxRA_VERTICAL, wxDefaultValidator, _T("ID_RADIOBOX1"));
	RBViewing->SetSelection(0);
	StaticBoxSizer4->Add(RBViewing, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Language:"));
	CHHLang = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	StaticBoxSizer5->Add(CHHLang, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(StaticBoxSizer5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cbDiffConfigPanel::OnColAddClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cbDiffConfigPanel::OnColRemClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cbDiffConfigPanel::OnColCarClick);
	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&cbDiffConfigPanel::OnViewModeChange);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&cbDiffConfigPanel::OnHLangChange);
	//*)
    BColAdd->SetBackgroundColour(wxColour(0,255,0,50));
    BColRem->SetBackgroundColour(wxColour(255,0,0,50));
    CHCaret->SetSelection(0);
	BColCar->SetBackgroundColour(wxColour(122,122,0));

    CHHLang->Append(cbDiffUtils::GetAllHighlightLanguages());

    ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("cbdiffsettings"));
    if (cfg)
    {
        BColAdd->SetBackgroundColour(cfg->ReadColour(_T("addedlines"), wxColour(0,255,0,50)));
        SLAddAlpha->SetValue(cfg->ReadInt(_T("addedlinesalpha"), 50));
        BColRem->SetBackgroundColour(cfg->ReadColour(_T("removedlines"), wxColour(255,0,0,50)));
        SLRemAlpha->SetValue(cfg->ReadInt(_T("removedlinesalpha"),50));
        CHCaret->SetSelection(cfg->ReadInt(_T("caretlinetype")));
        BColCar->SetBackgroundColour(cfg->ReadColour(_T("caretline"), wxColor(122,122,0)));
        SLCarAlpha->SetValue(cfg->ReadInt(_T("caretlinealpha"), 50));
        RBViewing->SetSelection(cfg->ReadInt(_T("viewmode"), 0));
        if(RBViewing->GetSelection() == 1)
            CHHLang->Enable(false);
        CHHLang->SetStringSelection(cfg->Read(_T("hlang"), _("Plain Text")));
    }

    BColAdd->SetLabel(BColAdd->GetBackgroundColour().GetAsString());
    BColRem->SetLabel(BColRem->GetBackgroundColour().GetAsString());
    BColCar->SetLabel(BColCar->GetBackgroundColour().GetAsString());
}

cbDiffConfigPanel::~cbDiffConfigPanel()
{
	//(*Destroy(cbDiffConfigPanel)
	//*)
}

wxString cbDiffConfigPanel::GetTitle() const
{
    return _("cbDiff Settings");
}

/// @return the panel's bitmap base name.
/// You must supply two bitmaps: \<basename\>.png and \<basename\>-off.png...
wxString cbDiffConfigPanel::GetBitmapBaseName() const
{
    return _T("cbdiffconf");
}

/// Called when the user chooses to apply the configuration.
void cbDiffConfigPanel::OnApply()
{
    ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("cbdiffsettings"));
    if (cfg)
    {
        cfg->Write(_T("addedlines"), BColAdd->GetBackgroundColour());
        cfg->Write(_T("addedlinesalpha"), SLAddAlpha->GetValue());
        cfg->Write(_T("removedlines"), BColRem->GetBackgroundColour());
        cfg->Write(_T("removedlinesalpha"), SLRemAlpha->GetValue());
        cfg->Write(_T("caretlinetype"), CHCaret->GetSelection());
        cfg->Write(_T("caretline"), BColCar->GetBackgroundColour());
        cfg->Write(_T("caretlinealpha"), SLCarAlpha->GetValue());
        cfg->Write(_T("viewmode"), RBViewing->GetSelection());
        cfg->Write(_T("hlang"), CHHLang->GetStringSelection());
    }
}

/// Called when the user chooses to cancel the configuration.
void cbDiffConfigPanel::OnCancel()
{

}

void cbDiffConfigPanel::OnColAddClick(wxCommandEvent& event)
{
    wxColourData data;
    data.SetColour(BColAdd->GetBackgroundColour());
    wxColourDialog dialog(this, &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        BColAdd->SetBackgroundColour(dialog.GetColourData().GetColour());
        BColAdd->SetLabel(dialog.GetColourData().GetColour().GetAsString());
    }
}

void cbDiffConfigPanel::OnColRemClick(wxCommandEvent& event)
{
    wxColourData data;
    data.SetColour(BColRem->GetBackgroundColour());
    wxColourDialog dialog(this, &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        BColRem->SetBackgroundColour(dialog.GetColourData().GetColour());
        BColRem->SetLabel(dialog.GetColourData().GetColour().GetAsString());
    }
}

void cbDiffConfigPanel::OnColCarClick(wxCommandEvent& event)
{
    wxColourData data;
    data.SetColour(BColCar->GetBackgroundColour());
    wxColourDialog dialog(this, &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        BColCar->SetBackgroundColour(dialog.GetColourData().GetColour());
        BColCar->SetLabel(dialog.GetColourData().GetColour().GetAsString());
    }
}

void cbDiffConfigPanel::OnViewModeChange(wxCommandEvent& event)
{
    if(RBViewing->GetSelection() == 1)
    {
        m_lasthlang = CHHLang->GetStringSelection();
        CHHLang->SetStringSelection(_("Diff/Patch"));
        CHHLang->Disable();
    }
    else
    {
        CHHLang->Enable();
        CHHLang->SetStringSelection(m_lasthlang);
    }
}

void cbDiffConfigPanel::OnHLangChange(wxCommandEvent& event)
{
    m_lasthlang = event.GetString();
}
