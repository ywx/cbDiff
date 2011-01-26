#include "cbSideBySideCtrl.h"

#include <manager.h>
#include <editormanager.h>
#include <configmanager.h>
#include <logmanager.h>
#include <cbstyledtextctrl.h>
#include <cbeditor.h>

#include <wx/textfile.h>

#include "cbDiffEditor.h"

/**
    We need to create this timer,
    because if we use the Scintilla events
    the graphic get messed up.
    And its easier to handle all the
    synchronisation stuff in one function.
    Trust me or try it self. ;-)
**/
class LineChangedTimer : public wxTimer
{
    cbSideBySideCtrl* m_pane;
public:
    LineChangedTimer(cbSideBySideCtrl* pane) : wxTimer()
    {
        m_pane = pane;
    }
    void Notify()
    {
        m_pane->Synchronize();
    }
    void start()
    {
        wxTimer::Start(20);
    }
};

BEGIN_EVENT_TABLE(cbSideBySideCtrl, cbDiffCtrl)
END_EVENT_TABLE()

cbSideBySideCtrl::cbSideBySideCtrl(wxWindow* parent) : cbDiffCtrl(parent)
{
    wxBoxSizer* VBoxSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* HBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    TCLeft = new cbStyledTextCtrl(this, wxID_ANY);
    TCRight = new cbStyledTextCtrl(this, wxID_ANY);
    VScrollBar = new wxScrollBar(this, wxID_ANY, wxDefaultPosition,
                                 wxDefaultSize, wxSB_VERTICAL);
    HScrollBar = new wxScrollBar(this, wxID_ANY);
    HBoxSizer->Add(TCLeft, 1, wxALL|wxEXPAND|wxALIGN_CENTER, 0);
    HBoxSizer->Add(TCRight, 1, wxALL|wxEXPAND|wxALIGN_CENTER, 0);
    HBoxSizer->Add(VScrollBar, 0, wxALL|wxEXPAND|wxALIGN_CENTER, 0);
    VBoxSizer->Add(HBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER, 5);
    VBoxSizer->Add(HScrollBar, 0, wxALL|wxEXPAND|wxALIGN_CENTER, 0);
    SetSizer(VBoxSizer);
    VBoxSizer->Fit(this);
    VBoxSizer->SetSizeHints(this);

    TCLeft->SetVScrollBar(VScrollBar);
    TCLeft->SetHScrollBar(HScrollBar);
    TCRight->SetVScrollBar(VScrollBar);
    TCRight->SetHScrollBar(HScrollBar);

    m_timer = new LineChangedTimer(this);
    m_timer->start();

    m_vscrollpos = VScrollBar->GetThumbPosition();
    m_hscrollpos = HScrollBar->GetThumbPosition();
}

cbSideBySideCtrl::~cbSideBySideCtrl()
{
    wxDELETE(m_timer);
}

void cbSideBySideCtrl::Init(cbDiffColors colset)
{
    int width = 7 * TCLeft->TextWidth(wxSCI_STYLE_LINENUMBER, _T("9"));
    wxColor marbkg = TCLeft->StyleGetBackground(wxSCI_STYLE_LINENUMBER);

    cbEditor::ApplyStyles(TCLeft);
    TCLeft->SetMargins(0,0);
    TCLeft->SetMarginWidth(0,width);
    TCLeft->SetMarginType(0, wxSCI_MARGIN_RTEXT);
    TCLeft->SetMarginWidth(1, 16);
    TCLeft->SetMarginType(1, wxSCI_MARGIN_SYMBOL);
    TCLeft->SetMarginWidth(2,0);    // to hide the change and the fold margin
    TCLeft->SetMarginWidth(3,0);    // made by cbEditor::ApplyStyles
    TCLeft->MarkerDefine(MINUS_MARKER, wxSCI_MARK_MINUS,
                         colset.m_removedlines, colset.m_removedlines);
    TCLeft->MarkerDefine(EQUAL_MARKER, wxSCI_MARK_CHARACTER + 61,
                         *wxWHITE, marbkg);
    TCLeft->MarkerDefine(RED_BKG_MARKER, wxSCI_MARK_BACKGROUND,
                         colset.m_removedlines, colset.m_removedlines);
    TCLeft->MarkerSetAlpha(RED_BKG_MARKER, colset.m_removedlines.Alpha());
    TCLeft->MarkerDefine(GREY_BKG_MARKER, wxSCI_MARK_BACKGROUND,
                         *wxLIGHT_GREY, *wxLIGHT_GREY);
    if(colset.m_caretlinetype == 0)
        TCLeft->MarkerDefine(CARET_LINE_MARKER, wxSCI_MARK_UNDERLINE,
                             colset.m_caretline, colset.m_caretline);
    else
    {
        TCLeft->MarkerDefine(CARET_LINE_MARKER, wxSCI_MARK_BACKGROUND,
                             colset.m_caretline, colset.m_caretline);
        TCLeft->MarkerSetAlpha(CARET_LINE_MARKER, colset.m_caretline.Alpha());
    }
    m_theme->Apply(m_theme->GetHighlightLanguage(colset.m_hlang), TCLeft);

    cbEditor::ApplyStyles(TCRight);
    TCRight->SetMargins(0,0);
    TCRight->SetMarginWidth(0,width);
    TCRight->SetMarginType(0, wxSCI_MARGIN_RTEXT);
    TCRight->SetMarginWidth(1, 16);
    TCRight->SetMarginType(1, wxSCI_MARGIN_SYMBOL);
    TCRight->SetMarginWidth(2,0);    // to hide the change and fold margin
    TCRight->SetMarginWidth(3,0);    // made by cbEditor::ApplyStyles
    TCRight->MarkerDefine(PLUS_MARKER, wxSCI_MARK_PLUS,
                          colset.m_addedlines, colset.m_addedlines);
    TCRight->MarkerDefine(EQUAL_MARKER, wxSCI_MARK_CHARACTER + 61,
                          *wxWHITE, marbkg);
    TCRight->MarkerDefine(GREEN_BKG_MARKER, wxSCI_MARK_BACKGROUND,
                          colset.m_addedlines, colset.m_addedlines);
    TCRight->MarkerSetAlpha(GREEN_BKG_MARKER, colset.m_addedlines.Alpha());
    TCRight->MarkerDefine(GREY_BKG_MARKER, wxSCI_MARK_BACKGROUND,
                          *wxLIGHT_GREY, *wxLIGHT_GREY);
    if(colset.m_caretlinetype == 0)
        TCRight->MarkerDefine(CARET_LINE_MARKER, wxSCI_MARK_UNDERLINE,
                              colset.m_caretline, colset.m_caretline);
    else
    {
        TCRight->MarkerDefine(CARET_LINE_MARKER, wxSCI_MARK_BACKGROUND,
                              colset.m_caretline, colset.m_caretline);
        TCRight->MarkerSetAlpha(CARET_LINE_MARKER, colset.m_caretline.Alpha());
    }
    m_theme->Apply(m_theme->GetHighlightLanguage(colset.m_hlang), TCRight);
}

void cbSideBySideCtrl::SetHlang(wxString lang)
{
    m_theme->Apply(m_theme->GetHighlightLanguage(lang), TCLeft);
    m_theme->Apply(m_theme->GetHighlightLanguage(lang), TCRight);
}

void cbSideBySideCtrl::ShowDiff(wxDiff diff)
{
    wxArrayInt right_added = diff.GetAddedLines();
    wxArrayInt right_empty = diff.GetRightEmptyLines();
    wxArrayInt left_empty = diff.GetLeftEmptyLines();
    wxArrayInt left_removed = diff.GetRemovedLines();

    /* Left Textctrl (m_fromfile) */
    TCLeft->SetReadOnly(false);
    TCLeft->ClearAll();
    wxTextFile tff(diff.GetFromFilename());
    tff.Open();
    bool refill = false;
    wxString str = tff.GetFirstLine();
    int linecount = tff.GetLineCount() + left_empty.GetCount();
    int linenumber = 1;
    for (int i = 0; i < linecount; i++)
    {
        if(refill && !tff.Eof())
            str = tff.GetNextLine();
        if(left_removed.Index(i+1) != wxNOT_FOUND)
        {
            TCLeft->AppendText(str + _T("\n"));
            refill = true;
            TCLeft->MarginSetStyle(i, wxSCI_STYLE_LINENUMBER);
            TCLeft->MarginSetText(i,wxString::Format(_T("%d"),linenumber));
            TCLeft->MarkerAdd(i, MINUS_MARKER);
            TCLeft->MarkerAdd(i, RED_BKG_MARKER);
            linenumber++;
            continue;
        }
        if(left_empty.Index(i+1) != wxNOT_FOUND)
        {
            TCLeft->AppendText(_T("\n"));
            TCLeft->MarkerAdd(i, GREY_BKG_MARKER);
            refill = false;
            continue;
        }
        TCLeft->AppendText(str + _T("\n"));
        refill = true;
        TCLeft->MarginSetStyle(i, wxSCI_STYLE_LINENUMBER);
        TCLeft->MarginSetText(i,wxString::Format(_T("%d"),linenumber));
        TCLeft->MarkerAdd(i, EQUAL_MARKER);
        linenumber++;
    }
    TCLeft->SetReadOnly(true);

    /* Right Textctrl (m_tofile) */
    TCRight->SetReadOnly(false);
    TCRight->ClearAll();
    wxTextFile tft(diff.GetToFilename());
    tft.Open();
    refill = false;
    str = tft.GetFirstLine();
    linecount = tft.GetLineCount() + right_empty.GetCount();
    linenumber = 1;
    for (int i = 0; i < linecount; i++)
    {
        if(refill && !tft.Eof())
            str = tft.GetNextLine();
        if(right_added.Index(i+1) != wxNOT_FOUND)
        {
            TCRight->AppendText(str + _T("\n"));
            refill = true;
            TCRight->MarginSetStyle(i, wxSCI_STYLE_LINENUMBER);
            TCRight->MarginSetText(i, wxString::Format(_T("%d"),linenumber));
            linenumber++;
            TCRight->MarkerAdd(i, PLUS_MARKER);
            TCRight->MarkerAdd(i, GREEN_BKG_MARKER);
            continue;
        }
        if(right_empty.Index(i+1) != wxNOT_FOUND)
        {
            TCRight->AppendText(_T("\n"));
            TCRight->MarkerAdd(i, GREY_BKG_MARKER);
            refill = false;
            continue;
        }
        TCRight->AppendText(str + _T("\n"));
        refill = true;
        TCRight->MarginSetStyle(i, wxSCI_STYLE_LINENUMBER);
        TCRight->MarginSetText(i, wxString::Format(_T("%d"),linenumber));
        TCRight->MarkerAdd(i, EQUAL_MARKER);
        linenumber++;
    }
    TCRight->SetReadOnly(true);
}

void cbSideBySideCtrl::Synchronize()
{
    static int last_lhandle = -1;
    static int last_rhandle = -1;
    static int last_line = -1;

    int curr_line = 0;
    if(TCLeft->GetSCIFocus())   // which scintilla control has the focus?
        curr_line = TCLeft->GetCurrentLine();

    if(TCRight->GetSCIFocus())
        curr_line = TCRight->GetCurrentLine();

    /* Caretline background synchronisation */
    if(curr_line != last_line)
    {
        TCLeft->MarkerDeleteHandle(last_lhandle);
        TCRight->MarkerDeleteHandle(last_rhandle);

        last_lhandle = TCLeft->MarkerAdd(curr_line, CARET_LINE_MARKER);
        last_rhandle = TCRight->MarkerAdd(curr_line, CARET_LINE_MARKER);

        last_line = curr_line;
        return;
    }
    int curr_scroll_focus = 0;
    // which wxcontrol has the scrollfocus?
    if(TCLeft->GetRect().Contains(ScreenToClient(wxGetMousePosition())))
        curr_scroll_focus = 1;
    if(TCRight->GetRect().Contains(ScreenToClient(wxGetMousePosition())))
        curr_scroll_focus = 2;

    /* Zoom synchronisation */
    if(TCRight->GetZoom() != TCLeft->GetZoom())
    {
        if(curr_scroll_focus == 1)
            TCRight->SetZoom(TCLeft->GetZoom());
        if(curr_scroll_focus == 2)
            TCLeft->SetZoom(TCRight->GetZoom());
    }

    /* Scroll synchronisation */
    if(m_vscrollpos != VScrollBar->GetThumbPosition())
    {
        TCLeft->SetFirstVisibleLine(VScrollBar->GetThumbPosition());
        TCRight->SetFirstVisibleLine(VScrollBar->GetThumbPosition());
        m_vscrollpos = VScrollBar->GetThumbPosition();
    }
    if(m_hscrollpos != HScrollBar->GetThumbPosition())
    {
        TCLeft->SetXOffset(HScrollBar->GetThumbPosition());
        TCRight->SetXOffset(HScrollBar->GetThumbPosition());
        m_hscrollpos = HScrollBar->GetThumbPosition();
    }
}
