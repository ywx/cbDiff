#ifndef WXDIFF_H
#define WXDIFF_H

#include <wx/wx.h>

#include <vector>

class wxDiff
{
public:
    wxDiff(wxString filename1, wxString filename2);
    virtual ~wxDiff();

    wxString IsDifferent();

    wxString GetDiff();
    wxArrayInt GetAddedLines();
    wxArrayInt GetLeftEmptyLines();
    wxArrayInt GetRightEmptyLines();
    wxArrayInt GetRemovedLines();
    wxString GetFromFilename();
    wxString GetToFilename();
private:
    wxString CreateHeader();
    void ParseDiff(std::vector<wxArrayString> diffs);

    wxString m_filename1;
    wxString m_filename2;
    wxString m_diff;
    wxArrayString m_diff_lines;
    wxArrayInt m_added_lines;
    wxArrayInt m_left_empty_lines;
    wxArrayInt m_right_empty_lines;
    wxArrayInt m_removed_lines;
};

#endif // WXDIFF_H
