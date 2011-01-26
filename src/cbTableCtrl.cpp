#include "cbTableCtrl.h"

#include <manager.h>
#include <editormanager.h>
#include <configmanager.h>
#include <logmanager.h>
#include <cbstyledtextctrl.h>
#include <cbeditor.h>

#include <wx/textfile.h>

cbTableCtrl::cbTableCtrl(wxWindow* parent) : cbDiffCtrl(parent)
{
    wxBoxSizer* BoxSizer = new wxBoxSizer(wxHORIZONTAL);
    m_txtctrl = new cbStyledTextCtrl(this, wxID_ANY);
    BoxSizer->Add(m_txtctrl, 1,wxEXPAND|wxALIGN_CENTER, 0);
    SetSizer(BoxSizer);
}

cbTableCtrl::~cbTableCtrl()
{
    //dtor
}

void cbTableCtrl::Init(cbDiffColors colset)
{
    int width = 20 * m_txtctrl->TextWidth(wxSCI_STYLE_LINENUMBER, _T("9"));
    wxColor marbkg = m_txtctrl->StyleGetBackground(wxSCI_STYLE_LINENUMBER);

    cbEditor::ApplyStyles(m_txtctrl);
    m_txtctrl->SetMargins(0, 0);
    m_txtctrl->SetMarginWidth(0, width);
    m_txtctrl->SetMarginType(0, wxSCI_MARGIN_RTEXT); // from and to file lines
    m_txtctrl->SetMarginWidth(1, 0);
    m_txtctrl->SetMarginWidth(2, 0);
    // to hide the fold margin made by cbEditor::ApplyStyles
    m_txtctrl->SetMarginWidth(3, 0);
    m_txtctrl->MarkerDefine(RED_BKG_MARKER, wxSCI_MARK_BACKGROUND,
                            colset.m_removedlines, colset.m_removedlines);
    m_txtctrl->MarkerSetAlpha(RED_BKG_MARKER, colset.m_removedlines.Alpha());
    m_txtctrl->MarkerDefine(GREEN_BKG_MARKER, wxSCI_MARK_BACKGROUND,
                            colset.m_addedlines, colset.m_addedlines);
    m_txtctrl->MarkerSetAlpha(GREEN_BKG_MARKER, colset.m_addedlines.Alpha());
    m_theme->Apply(m_theme->GetHighlightLanguage(colset.m_hlang), m_txtctrl);
}

void cbTableCtrl::SetHlang(wxString lang)
{
    m_theme->Apply(m_theme->GetHighlightLanguage(lang), m_txtctrl);
}

void cbTableCtrl::ShowDiff(wxDiff diff)
{
    wxArrayInt right_added = diff.GetAddedLines();
    wxArrayInt right_empty = diff.GetRightEmptyLines();
    wxArrayInt left_empty = diff.GetLeftEmptyLines();
    wxArrayInt left_removed = diff.GetRemovedLines();

    /* Table Textctrl */
    m_txtctrl->SetReadOnly(false);
    m_txtctrl->ClearAll();
    wxTextFile tff(diff.GetFromFilename());
    wxTextFile tft(diff.GetToFilename());
    tff.Open();
    tft.Open();
    bool refillfrom = false;
    bool refillto = false;
    wxString strfrom = tff.GetFirstLine();
    wxString strto = tft.GetFirstLine();
    int linecount = tff.GetLineCount() + left_empty.GetCount();
    int linenumberfrom = 1;
    int linenumberto = 1;
    for (int i = 0; i < linecount; i++)
    {
        if(refillfrom && !tff.Eof())
            strfrom = tff.GetNextLine();
        if(refillto && !tft.Eof())
            strto = tft.GetNextLine();
        if(left_removed.Index(i+1) != wxNOT_FOUND)
        {
            m_txtctrl->AppendText(strfrom + _T("\n"));
            refillfrom = true;
            refillto = false;
            m_txtctrl->MarginSetStyle(i, wxSCI_STYLE_LINENUMBER);
            m_txtctrl->MarginSetText(i, wxString::Format(_T("%9d%9c"),
                                                         linenumberfrom,
                                                         ' '));
            m_txtctrl->MarkerAdd(i, RED_BKG_MARKER);
            linenumberfrom++;
            continue;
        }
        if(right_added.Index(i+1) != wxNOT_FOUND)
        {
            m_txtctrl->AppendText(strto + _T("\n"));
            m_txtctrl->MarginSetStyle(i, wxSCI_STYLE_LINENUMBER);
            m_txtctrl->MarginSetText(i, wxString::Format(_T("%9d"),
                                                         linenumberto));
            m_txtctrl->MarkerAdd(i, GREEN_BKG_MARKER);
            refillfrom = false;
            refillto = true;
            linenumberto++;
            continue;
        }
        m_txtctrl->AppendText(strfrom + _T("\n"));
        refillfrom = true;
        refillto = true;
        m_txtctrl->MarginSetStyle(i, wxSCI_STYLE_LINENUMBER);
        m_txtctrl->MarginSetText(i, wxString::Format(_T("%9d%9d"),
                                                     linenumberfrom,
                                                     linenumberto));
        linenumberfrom++;
        linenumberto++;
    }
    m_txtctrl->SetReadOnly(true);
}
