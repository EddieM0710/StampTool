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

        wxString GetProjectFilename() { return m_projectFilename; };
        void SetProjectFilename(wxString name );

        ODT::Document* GetODTDocument( );
        void SetODTDocument( ODT::Document* doc );

        wxString GetOutputFilename( );
        void SetOutputFilename( wxString outputFilename );

        wxString GetDesignFilename( );
        void SetDesignFilename( wxString albumFilename );;
        void LoadDesignData();
        void LoadDesignTree();

        wxString GetImagePath( );
        void SetImagePath( wxString imagePath );

        wxString GetCatalogFilename( );
        void SetCatalogFilename( wxString catalogFilename );
        void LoadCatalogData();
        void LoadCatalogTree();

        Settings* GetLSettings( );
        void SetSettings( Settings* settings );

        bool LoadProject(  );
        void LoadData();
        void InitODTDocument();

        void LoadAttributes( wxXmlNode* thisObject );
        void Save(  );

        wxString MakeFileAbsolute( wxString filename);

        inline GeneratorData* GetGeneratorData(){ return &m_generatorData; };

        void SetDirty( bool state = true ) { m_dirty = state; };
        bool isDirty( ) { return m_dirty; };

    private:
        wxXmlDocument* m_ProjectDoc;
        ODT::Document* m_ODTDoc;
        wxString m_projectFilename;
        wxString m_outputFilename;
        wxString m_designFilename;
        wxString m_imagePath;
        wxString m_catalogFilename;
        Settings* m_settings;
        GeneratorData m_generatorData;
        bool m_dirty;

    };
}
#endif