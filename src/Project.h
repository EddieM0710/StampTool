#ifndef Project_h
#define Project_h

#include "wx/string.h"
#include <wx/xml/xml.h>
//using namespace tinyxml2;

class Project
{
public:
    Project() 
    {
        InitDefs( );
        m_settings = new Settings( );
        Load();

    };
    ~Project() {};

    wxString GetOutputName() { return m_outputName; };
    wxString GetAlbum() { return m_album; };
    wxString GetImagePath() { return m_imagePath; };
    wxString GetCatalogs() { return m_catalog; };

    bool Load( wxString filename );
    bool LoadAttributes( wxXmlNode* thisObject );


private:
    wxXmlDocument m_ProjectDoc;
    wxString m_filename;
    wxString m_outputName;
    wxString m_album;
    wxString m_imagePath;
    wxString m_catalog;
    CatalogData* m_catalogData;
    AlbumData* m_albumData;
    Settings* m_settings;
};
#endif