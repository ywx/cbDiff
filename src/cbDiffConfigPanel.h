#ifndef CBDIFFCONFIGPANEL_H
#define CBDIFFCONFIGPANEL_H

//(*Headers(cbDiffConfigPanel)
#include <wx/panel.h>
class wxStaticBoxSizer;
class wxChoice;
class wxButton;
class wxSlider;
class wxBoxSizer;
class wxStaticText;
class wxRadioBox;
//*)

#include <configurationpanel.h>

class cbDiffConfigPanel: public cbConfigurationPanel
{
	public:

		cbDiffConfigPanel(wxWindow* parent);
		virtual ~cbDiffConfigPanel();

        virtual wxString GetTitle() const;
        /// @return the panel's bitmap base name. You must
        /// supply two bitmaps: \<basename\>.png and \<basename\>-off.png...
        virtual wxString GetBitmapBaseName() const;
        /// Called when the user chooses to apply the configuration.
        virtual void OnApply();
        /// Called when the user chooses to cancel the configuration.
        virtual void OnCancel();
	private:

		//(*Declarations(cbDiffConfigPanel)
		wxSlider* SLCarAlpha;
		wxChoice* CHCaret;
		wxRadioBox* RBViewing;
		wxStaticText* StaticText3;
		wxButton* BColRem;
		wxSlider* SLAddAlpha;
		wxSlider* SLRemAlpha;
		wxButton* BColAdd;
		wxButton* BColCar;
		//*)

		//(*Identifiers(cbDiffConfigPanel)
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT1;
		static const long ID_SLIDER1;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_SLIDER2;
		static const long ID_CHOICE1;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT3;
		static const long ID_SLIDER3;
		static const long ID_RADIOBOX1;
		static const long ID_CHOICE2;
		//*)

		//(*Handlers(cbDiffConfigPanel)
		void OnColAddClick(wxCommandEvent& event);
		void OnColRemClick(wxCommandEvent& event);
		void OnColCarClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
