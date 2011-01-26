#include "cbDiffSelectFiles.h"

#include <editorcolourset.h>
#include <configmanager.h>

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(cbDiffSelectFiles)
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/filedlg.h>
	#include <wx/string.h>
	#include <wx/intl.h>
	#include <wx/textctrl.h>
	#include <wx/choice.h>
	#include <wx/radiobox.h>
	//*)
#endif
//(*InternalHeaders(cbDiffSelectFiles)
#include <wx/button.h>
//*)


#include "cbDiffUtils.h"
#include "cbDiffEditor.h"

//(*IdInit(cbDiffSelectFiles)
const long cbDiffSelectFiles::ID_TCFROM = wxNewId();
const long cbDiffSelectFiles::ID_BSFROM = wxNewId();
const long cbDiffSelectFiles::ID_TCTO = wxNewId();
const long cbDiffSelectFiles::ID_BSTO = wxNewId();
const long cbDiffSelectFiles::ID_RADIOBOX1 = wxNewId();
const long cbDiffSelectFiles::ID_CHOICE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(cbDiffSelectFiles,wxDialog)
	//(*EventTable(cbDiffSelectFiles)
	//*)
	EVT_RADIOBOX(ID_RADIOBOX1, cbDiffSelectFiles::OnRadioBox)
END_EVENT_TABLE()

cbDiffSelectFiles::cbDiffSelectFiles(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(cbDiffSelectFiles)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Select Files:"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("From:"));
	TCFromFile = new wxTextCtrl(this, ID_TCFROM, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TCFROM"));
	StaticBoxSizer2->Add(TCFromFile, 10, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BSelectFrom = new wxButton(this, ID_BSFROM, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT, wxDefaultValidator, _T("ID_BSFROM"));
	StaticBoxSizer2->Add(BSelectFrom, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("To:"));
	TCToFile = new wxTextCtrl(this, ID_TCTO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TCTO"));
	StaticBoxSizer3->Add(TCToFile, 10, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BSelectTo = new wxButton(this, ID_BSTO, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT, wxDefaultValidator, _T("ID_BSTO"));
	StaticBoxSizer3->Add(BSelectTo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	wxString __wxRadioBoxChoices_1[3] =
	{
		_("Tabular"),
		_("Unified Diff"),
		_("Side by side")
	};
	RBViewing = new wxRadioBox(this, ID_RADIOBOX1, _("Displaytype:"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 1, wxRA_VERTICAL, wxDefaultValidator, _T("ID_RADIOBOX1"));
	RBViewing->SetSelection(0);
	BoxSizer2->Add(RBViewing, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Language:"));
	CHHLang = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	StaticBoxSizer4->Add(CHHLang, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	SelectFile = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_PREVIEW, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BSFROM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cbDiffSelectFiles::OnSelectFrom);
	Connect(ID_BSTO,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cbDiffSelectFiles::OnSelectTo);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&cbDiffSelectFiles::OnHLangChange);
	//*)

    CHHLang->Append(cbDiffUtils::GetAllHighlightLanguages());

    ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("cbdiffsettings"));
    if (cfg)
    {
        RBViewing->SetSelection(cfg->ReadInt(_T("viewmode"), 0));
        CHHLang->SetStringSelection(cfg->Read(_T("hlang"), _("Plain Text")));
        if(RBViewing->GetSelection() == 1)
        {
            CHHLang->Enable(false);
            CHHLang->SetStringSelection(_("Diff/Patch"));
        }
    }
}

cbDiffSelectFiles::~cbDiffSelectFiles()
{
	//(*Destroy(cbDiffSelectFiles)
	//*)
}

void cbDiffSelectFiles::OnSelectFrom(wxCommandEvent& event)
{
    if(SelectFile->ShowModal() == wxID_OK)
    {
        TCFromFile->SetValue(SelectFile->GetPath());
    }
}

void cbDiffSelectFiles::OnSelectTo(wxCommandEvent& event)
{
    if(SelectFile->ShowModal() == wxID_OK)
    {
        TCToFile->SetValue(SelectFile->GetPath());
    }
}

void cbDiffSelectFiles::OnRadioBox(wxCommandEvent& event)
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

void cbDiffSelectFiles::OnHLangChange(wxCommandEvent& event)
{
    m_lasthlang = event.GetString();
}

wxString cbDiffSelectFiles::GetFromFile()
{
    return TCFromFile->GetValue();
}

wxString cbDiffSelectFiles::GetToFile()
{
    return TCToFile->GetValue();
}

int cbDiffSelectFiles::GetViewingMode()
{
    return RBViewing->GetSelection() + cbDiffEditor::TABLE;
}

wxString cbDiffSelectFiles::GetHighlightLanguage()
{
    return CHHLang->GetStringSelection();
}
