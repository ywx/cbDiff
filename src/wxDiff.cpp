#include "wxDiff.h"

#include "../dtl-1.12/dtl/dtl.hpp"

#include <sstream>
#include <fstream>
#include <wx/textfile.h>
#include <wx/filename.h>
#include <wx/sstream.h>
#include <wx/tokenzr.h>

using dtl::Diff;
using dtl::elemInfo;
using dtl::uniHunk;
using std::pair;
using std::string;
using std::ifstream;
using std::vector;

wxDiff::wxDiff(wxString filename1, wxString filename2)
              : m_filename1(filename1), m_filename2(filename2)
{
    typedef std::string elem;
    typedef pair<elem, elemInfo> sesElem;
    ifstream Aifs(filename1.mbc_str());
    ifstream Bifs(filename2.mbc_str());
    elem buf;
    vector<elem> ALines, BLines;

    while(getline(Aifs, buf))
    {
        ALines.push_back(buf);
    }
    while(getline(Bifs, buf))
    {
        BLines.push_back(buf);
    }

    Diff<elem, vector<elem> > diff(ALines, BLines);
    diff.onHuge();
    diff.compose();

    uniHunk< sesElem > hunk;

    diff.composeUnifiedHunks();
    std::ostringstream help;
    diff.printUnifiedFormat();
    diff.printUnifiedFormat(help);

    m_diff = wxString(help.str().c_str(), wxConvUTF8);

    vector<wxArrayString> diffs;
    wxStringTokenizer tkz(m_diff, wxT("\n"));
    wxArrayString currdiff;
    while(tkz.HasMoreTokens())
    {
        wxString token = tkz.GetNextToken();
        if(token.StartsWith(_T("@@")) &&
           token.EndsWith(_T("@@")) &&
           !currdiff.IsEmpty())
        {
            diffs.push_back(currdiff);
            currdiff.clear();
        }
        currdiff.Add(token);
    }
    if(!currdiff.IsEmpty())
        diffs.push_back(currdiff);

    ParseDiff(diffs);
}

wxDiff::~wxDiff()
{
}

wxString wxDiff::IsDifferent()
{
    wxFileName filename(m_filename1);
    wxDateTime modifyTime;
    wxDateTime modifyTime2;
    filename.GetTimes(0, &modifyTime, 0);
    filename.Assign(m_filename2);
    filename.GetTimes(0, &modifyTime2, 0);
    if(modifyTime == modifyTime2 && m_filename1 == m_filename2)
        return _("Same file => Same content!");
    if(m_added_lines.GetCount() == 0 && m_removed_lines.GetCount() == 0)
        return _("Different files, but same content!");
    return wxEmptyString;
}

wxString wxDiff::CreateHeader()
{
    wxString header;
    wxFileName filename(m_filename1);
    wxDateTime modifyTime;
    filename.GetTimes(0, &modifyTime, 0);
    header << _T("--- ") << m_filename1
           << _T("\t") << modifyTime.Format(_T("%Y-%m-%d %H:%M:%S %z"))
           << _T("\n");
    filename.Assign(m_filename2);
    filename.GetTimes(0, &modifyTime, 0);
    header << _T("+++ ") << m_filename2
           << _T("\t") << modifyTime.Format(_T("%Y-%m-%d %H:%M:%S %z"))
           << _T("\n");
    return header;
}

void wxDiff::ParseDiff(vector<wxArrayString> diffs)
{
    int file_start_left = 0;
    int file_start_right = 0;
    for(unsigned int i = 0; i < diffs.size(); i++)
    {
        wxArrayString currdiff = diffs[i];
        wxString headline = currdiff[0];
        headline.Replace(_T("@@"),_T(""));
        headline.Trim();
        long start_left = -1;
        long start_right = -1;
        headline.Mid(headline.Find(_T("-")) + 1,
                     headline.Find(_T(","))).ToLong(&start_left);
        headline.Mid(headline.Find(_T("+")) + 1,
                     headline.Find(_T(","))).ToLong(&start_right);
        start_left +=file_start_left;
        start_right +=file_start_right;
        for(unsigned int i = 1; i < currdiff.size(); i++)
        {
            wxString line = currdiff[i];
            if(line.StartsWith(_T("+")))
            {
                m_added_lines.Add(start_right);
                m_left_empty_lines.Add(start_left);
            }
            if(line.StartsWith(_T("-")))
            {
                m_removed_lines.Add(start_left);
                m_right_empty_lines.Add(start_right);
            }
            start_right++;
            start_left++;
        }
        file_start_left = m_left_empty_lines.GetCount();
        file_start_right = m_right_empty_lines.GetCount();
    }
}

wxString wxDiff::GetDiff()
{
    return CreateHeader() + m_diff;
}

wxArrayInt wxDiff::GetAddedLines()
{
    return m_added_lines;
}

wxArrayInt wxDiff::GetLeftEmptyLines()
{
    return m_left_empty_lines;
}

wxArrayInt wxDiff::GetRightEmptyLines()
{
    return m_right_empty_lines;
}

wxArrayInt wxDiff::GetRemovedLines()
{
    return m_removed_lines;
}

wxString wxDiff::GetFromFilename()
{
    return m_filename1;
}

wxString wxDiff::GetToFilename()
{
    return m_filename2;
}
