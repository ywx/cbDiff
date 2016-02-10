#ifndef CBDIFFSELECTFILES_H
#define CBDIFFSELECTFILES_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(cbDiffSelectFiles)
	#include <wx/dialog.h>
	class wxTextCtrl;
	class wxStaticBoxSizer;
	class wxChoice;
	class wxButton;
	class wxStdDialogButtonSizer;
	class wxFileDialog;
	class wxBoxSizer;
	class wxRadioBox;
	//*)
#endif
//(*Headers(cbDiffSelectFiles)
//*)

class cbDiffSelectFiles: public wxDialog
{
	public:

		cbDiffSelectFiles(wxWindow* parent, wxWindowID id = wxID_ANY);
		virtual ~cbDiffSelectFiles();

        wxString GetFromFile();
        wxString GetToFile();

        int GetViewingMode();
	protected:
	private:
        //(*Declarations(cbDiffSelectFiles)
        wxRadioBox* RBViewing;
        wxButton* BSelectTo;
        wxTextCtrl* TCFromFile;
        wxTextCtrl* TCToFile;
        wxButton* BSelectFrom;
        wxFileDialog* SelectFile;
        //*)

        //(*Identifiers(cbDiffSelectFiles)
        static const long ID_TCFROM;
        static const long ID_BSFROM;
        static const long ID_TCTO;
        static const long ID_BSTO;
        static const long ID_RADIOBOX1;
        //*)

		//(*Handlers(cbDiffSelectFiles)
		void OnSelectTo(wxCommandEvent& event);
		void OnSelectFrom(wxCommandEvent& event);
		//*)

        DECLARE_EVENT_TABLE()
};

#endif // CBDIFFSELECTFILES_H
