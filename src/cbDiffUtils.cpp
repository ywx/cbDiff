#include "cbDiffUtils.h"

#include <projectfile.h>
#include <cbproject.h>
#include <editormanager.h>
#include <projectmanager.h>
#include <cbeditor.h>
#include <configmanager.h>
#include <editorcolourset.h>

#include <wx/mstream.h>

namespace cbDiffUtils
{
    wxArrayString GetActiveProjectFilesRelative(ProjectFile* exclude)
    {
        wxArrayString ar;
        cbProject* project = Manager::Get()->GetProjectManager()
                                           ->GetActiveProject();
        if(project)
        {
            for(int i = 0; i < project->GetFilesCount(); i++)
                if(project->GetFile(i) && project->GetFile(i) != exclude)
                    ar.Add(project->GetFile(i)->relativeFilename);
        }
        return ar;
    }

    wxArrayString GetActiveProjectFilesAbsolute(ProjectFile* exclude)
    {
        wxArrayString ar;
        cbProject* project = Manager::Get()->GetProjectManager()
                                           ->GetActiveProject();
        if(project)
        {
            for(int i = 0; i < project->GetFilesCount(); i++)
                if(project->GetFile(i) && project->GetFile(i) != exclude)
                    ar.Add(project->GetFile(i)->file.GetFullPath());
        }
        return ar;
    }

    wxArrayString GetOpenFilesShort(wxString excludefile)
    {
        wxArrayString ar;
        EditorManager* em = Manager::Get()->GetEditorManager();
        if(em->GetBuiltinEditor(excludefile))
            excludefile = em->GetBuiltinEditor(excludefile)->GetShortName();
        for(int i = 0; i < em->GetEditorsCount(); i++)
            if(em->GetBuiltinEditor(i) &&
                    excludefile != em->GetBuiltinEditor(i)->GetShortName())
                ar.Add(em->GetBuiltinEditor(i)->GetShortName());
        return ar;
    }

    wxArrayString GetOpenFilesLong(wxString excludefile)
    {
        wxArrayString ar;
        EditorManager* em = Manager::Get()->GetEditorManager();
        for(int i = 0; i < em->GetEditorsCount(); i++)
            if(em->GetBuiltinEditor(i) &&
                    excludefile != em->GetBuiltinEditor(i)->GetFilename())
                ar.Add(em->GetBuiltinEditor(i)->GetFilename());
        return ar;
    }

    ProjectFile* IsFileInActiveProject(wxString filename)
    {
        cbProject* pr = Manager::Get()->GetProjectManager()->GetActiveProject();
        if(pr)
            return pr->GetFileByFilename(filename, false);
        return NULL;
    }

    wxArrayString GetAllHighlightLanguages()
    {
        static wxArrayString langs;
        // Get them once, as they shouldn't change during App run
        if(langs.GetCount() == 0)
        {
            EditorColourSet *theme =
            new EditorColourSet(Manager::Get()->GetConfigManager(_T("editor"))->
                                Read(_T("/colour_sets/active_colour_set"),
                                COLORSET_DEFAULT));
            if (theme)
                langs = theme->GetAllHighlightLanguages();
            langs.Insert(_("Plain Text"), 0);
            wxDELETE(theme);
        }
        return langs;
    }

    wxBitmap _wxGetBitmapFromMemory(const unsigned char *data, int length)
    {
       wxMemoryInputStream is(data, length);
       return wxBitmap(wxImage(is, wxBITMAP_TYPE_ANY, -1), -1);
    }
}
