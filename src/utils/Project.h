#ifndef Project_h
#define Project_h

#include "wx/string.h"
#include <wx/xml/xml.h>
#include "gui/GeneratorData.h"

namespace ODT { class Document; };

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

        Settings* GetLSettings( );
        void SetSettings( Settings* settings );

        bool LoadProject( wxString filename );
        bool LoadAttributes( wxXmlNode* thisObject );
        wxString MakeFile( wxString filename);
        inline GeneratorData* GetGeneratorData(){ return &m_generatorData; };

    private:
        wxXmlDocument* m_ProjectDoc;
        ODT::Document* m_ODTDoc;
        wxString m_projectFilename;
        wxString m_outputFilename;
        wxString m_albumFilename;
        wxString m_imagePath;
        wxString m_catalogFilename;
        Settings* m_settings;
        GeneratorData m_generatorData;
        bool m_dirty;

    };
}
#endif