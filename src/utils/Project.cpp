#include <iostream>
#include <wx/filename.h>
#include "Defs.h"
#include "utils/Project.h"


#include "utils/Settings.h"

#include "catalog/CatalogData.h"
#include "design/DesignDefs.h"
#include "design/DesignData.h"
#include "design/AlbumBase.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/DesignTreeCtrl.h"


namespace Utils {

    Project::Project( )
    {
        InitDefs( );
        m_settings = new Settings( );
        if ( m_settings->GetLoadLastFileAtStartUp( ) )
        {
            m_projectFilename = m_settings->GetLastFile( );

            // if ( wxFileExists( filename ) )
            // {
            //     if ( LoadProject( filename ) )
            //     {
            //     }
            // }
        }

        SetDirty( false );
    };


    ODT::Document* Project::GetODTDocument( )
    {
        return m_ODTDoc;
    };
    void Project::SetODTDocument( ODT::Document* doc )
    {
        m_ODTDoc = doc; SetDirty( );
        ;
    };

    wxString Project::GetOutputFilename( )
    {
        return m_outputFilename;
    };
    void Project::SetOutputFilename( wxString outputFilename )
    {
        m_outputFilename = outputFilename; m_dirty = true;
    };

    wxString Project::GetDesignFilename( )
    {
        return m_designFilename;
    };
    void Project::SetDesignFilename( wxString albumFilename )
    {
        m_designFilename = albumFilename;
        m_dirty = true;
    };
    wxString Project::GetImagePath( )
    {
        return m_imagePath;
    };
    void Project::SetImagePath( wxString imagePath )
    {
        m_imagePath = imagePath; SetDirty( );
    };
    wxString Project::GetCatalogFilename( )
    {
        return m_catalogFilename;
    };

    Settings* Project::GetLSettings( )
    {
        return  m_settings;
    };
    void Project::SetSettings( Settings* settings )
    {
        m_settings = settings;
    };


    void Project::SetCatalogFilename( wxString catalogFilename )
    {
        if ( m_catalogFilename.Cmp( catalogFilename ) )
        {
            m_catalogFilename = catalogFilename;
            SetDirty( );
        }
    };
    void Project::SetProjectFilename(wxString name ) 
    {  
        m_projectFilename = name; 
        GetSettings( )->SetLastFile( m_projectFilename );
    };

    wxString Project::MakeFileAbsolute( wxString filename )
    {
        wxFileName newFile( filename );
        if ( !newFile.IsAbsolute( ) )
        {
            newFile.MakeAbsolute( );
        }
        return newFile.GetFullPath( );
    }

    bool Project::LoadProject(  )
    {
        wxFileName projFile( m_projectFilename );
        if ( projFile.FileExists( ) )
        {
            if ( !projFile.IsAbsolute( ) )
            {
                projFile.MakeAbsolute( );
            }
        }
        else
        {
            //setup new files
            return false;
        }

        wxString cwd = projFile.GetPath( );
        m_settings->SetWorkingDirectory( cwd );
        wxFileName::SetCwd( cwd );
//        m_projectFilename = projFile.GetFullPath( );


        m_ProjectDoc = new wxXmlDocument( );
        if ( !m_ProjectDoc->Load( m_projectFilename ) )
        {
            ReportError( "Project::Load", "error loading Prokect xml file.", true );
            return false;
        }

        wxXmlNode* projectRoot = m_ProjectDoc->GetRoot( );
        wxString name = projectRoot->GetName( );
        if ( name.Cmp( "Project" ) )
        {
            std::cout << "Initial node must be <Project>"
                << "\n";
            std::cout << "Found \"" << name << "\" instead.\n";
            return false;
        }
        LoadAttributes( projectRoot );

        GetSettings( )->SetLastFile( m_projectFilename );

//        LoadData();

        SetDirty( false );
        return true;
    }

    void Project::LoadData()
    {
        LoadCatalogData( );
        LoadDesignData( );

        LoadDesignTree( );
        LoadCatalogTree( );

    }

    void Project::LoadCatalogData( )
    {
        wxString catalogFilename = GetCatalogFilename( );
        m_generatorData.LoadCatalogData( catalogFilename );
    }

    void Project::LoadCatalogTree( )
    {
        GetCatalogTreeCtrl( )->LoadTree( );
    }

    void Project::LoadDesignData( )
    {
        wxString albumFilename = GetDesignFilename( );
        m_generatorData.LoadDesignData( albumFilename );
    }

    void Project::LoadDesignTree( )
    {
        GetDesignTreeCtrl( )->LoadTree( );
    }

    void Project::LoadAttributes( wxXmlNode* thisObject )
    {
        const wxXmlAttribute* attr = thisObject->GetAttributes( );
        wxFileName filename;
        while ( attr )
        {
            wxString name = attr->GetName( );
            wxString val = attr->GetValue( );

            if ( !name.Cmp( "OutputName" ) )
            {
                m_outputFilename = MakeFileAbsolute( val );
            }
            else if ( !name.Cmp( "Album" ) )
            {
                m_designFilename = MakeFileAbsolute( val );
            }
            else if ( !name.Cmp( "ImagePath" ) )
            {
                GetLSettings( )->SetImageDirectory( MakeFileAbsolute( val ) );
            }
            else if ( !name.Cmp( "Catalog" ) )
            {
                m_catalogFilename = MakeFileAbsolute( val );
            }
            attr = attr->GetNext( );
        }
    }

    void Project::Save( )
    {

        if ( wxFileExists( m_projectFilename ) )
        {
            wxFileName bakFile( m_projectFilename );
            bakFile.SetExt( "bak" );
            wxRenameFile( m_projectFilename, bakFile.GetFullName( ), true );
        }
        if ( m_ProjectDoc )
        {
            delete m_ProjectDoc;
        }
        m_ProjectDoc = new wxXmlDocument(  );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Project" );

        root->AddAttribute( "OutputName", m_outputFilename );
        root->AddAttribute( "Album", m_designFilename );
        root->AddAttribute( "ImagePath", m_imagePath );
        root->AddAttribute( "Catalog", m_catalogFilename );

        m_ProjectDoc->SetRoot( root );

        m_ProjectDoc->Save( m_projectFilename );

        SetDirty( false );
    }

}