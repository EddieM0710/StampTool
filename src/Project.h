#ifndef Project_h
#define Project_h

#include "wx/string.h"
#include <wx/xml/xml.h>
//using namespace tinyxml2;

class Project
{
public:
    Project() {};
    ~Project() {};

    wxString GetOutputName() { return m_outputName; };
    wxString GetLayout() { return m_layout; };
    wxString GetImagePath() { return m_imagePath; };
    wxString GetStampProperties() { return m_stampProperties; };

    bool Load( wxString filename );
    bool LoadAttributes( wxXmlNode* thisObject );


private:
    wxXmlDocument m_ProjectDoc;
    wxString m_filename;
    wxString m_outputName;
    wxString m_layout;
    wxString m_imagePath;
    wxString m_stampProperties;
};
#endif