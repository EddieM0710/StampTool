#ifndef Project_h
#define Project_h

#include "wx/string.h"
#include <wx/xml/xml.h>
//using namespace tinyxml2;
#include "Defs.h"
//#include "utils/Settings.h"
//#include "odt/Document.h"
//#include "album/AlbumData.h"
#include "catalog/CatalogData.h"

namespace ODT { class Document; };
namespace Layout { class AlbumData;};
namespace Catalog { class CatalogData;};

namespace Utils {
 class Settings;

    class Project
    {
    public:
        Project( );
        ~Project( ) {};

        ODT::Document* GetODTDocument( );
        void SetODTDocument( ODT::Document* doc );

        wxString GetOutputFilename( );
        void SetOutputFilename( wxString outputFilename );

        wxString GetAlbumFilename( );
        void SetAlbumFilename( wxString albumFilename );;
        wxString GetImagePath( );
        void SetImagePath( wxString imagePath );
        wxString GetCatalogFilename( );
        void SetCatalogFilename( wxString catalogFilename );

        Settings* GetSettings( );
        void SetSettings( Settings* settings );

        Catalog::CatalogData* GetCatalogData( );
        void SetCatalogData(  Catalog::CatalogData* catalogData );
        Layout::AlbumData* GetAlbumData( );
        void SetAlbumData( Layout::AlbumData* albumData );

        bool LoadProject( wxString filename );
        bool LoadAttributes( wxXmlNode* thisObject );
        wxString MakeFile( wxString filename);


    private:
        wxXmlDocument* m_ProjectDoc;
        ODT::Document* m_ODTDoc;
        wxString m_projectFilename;
        wxString m_outputFilename;
        wxString m_albumFilename;
        wxString m_imagePath;
        wxString m_catalogFilename;
        Catalog::CatalogData* m_catalogData;
        Layout::AlbumData* m_albumData;
        Settings* m_settings;
        bool m_dirty;
    };
}
#endif