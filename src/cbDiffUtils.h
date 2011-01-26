#ifndef CBDIFFUTILS_H
#define CBDIFFUTILS_H

#include <wx/arrstr.h>
#include <wx/bitmap.h>

class cbProject;
class ProjectFile;

#define wxGetBitmapFromMemory(name) \
        cbDiffUtils::_wxGetBitmapFromMemory(name ## _png, sizeof(name ## _png))

namespace cbDiffUtils
{
    wxArrayString GetActiveProjectFilesRelative(ProjectFile* exclude);
    wxArrayString GetActiveProjectFilesAbsolute(ProjectFile* exclude);
    ProjectFile* IsFileInActiveProject(wxString filename);
    wxArrayString GetOpenFilesShort(wxString excludefile);
    wxArrayString GetOpenFilesLong(wxString excludefile);
    wxArrayString GetAllHighlightLanguages();
    wxBitmap _wxGetBitmapFromMemory(const unsigned char *data, int length);
}
#endif // CBDIFFUTILS_H
