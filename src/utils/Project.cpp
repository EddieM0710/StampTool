#include "utils/Project.h"
#include "utils/Settings.h"
#include "Defs.h"
#include <iostream>
#include "catalog/CatalogData.h"
#include "album/AlbumDefs.h"
#include "album/AlbumData.h"
#include <wx/filename.h>

namespace Utils {

    Project::Project( )
    {
        InitDefs( );
        m_settings = new Settings( );
        if ( m_settings->GetLoadLastFileAtStartUp())
        {
            wxString filename = m_settings->GetLastFile();

            if ( wxFileExists( filename ))
            {

                if( LoadProject( filename ))
                {
                    wxString catalogFilename = GetCatalogFilename();
                    m_catalogData = Catalog::NewCatalogData( );
                    m_catalogData->LoadXML( catalogFilename );
                
                    wxString albumFilename = GetAlbumFilename();
                    m_albumData = Layout::NewAlbumData( );
                    m_albumData->LoadXML( albumFilename );
                }
            }
        }
    };


    ODT::Document* Project::GetODTDocument( )
    {
        return m_ODTDoc;
    };
    void Project::SetODTDocument( ODT::Document* doc )
    {
        m_ODTDoc = doc; m_dirty = true;
    };

    wxString Project::GetOutputFilename( )
    {
        return m_outputFilename;
    };
    void Project::SetOutputFilename( wxString outputFilename )
    {
        m_outputFilename = outputFilename; m_dirty = true;
    };

    wxString Project::GetAlbumFilename( )
    {
        return m_albumFilename;
    };
    void Project::SetAlbumFilename( wxString albumFilename )
    {
        m_albumFilename = albumFilename;
        m_dirty = true;
    };
    wxString Project::GetImagePath( )
    {
        return m_imagePath;
    };
    void Project::SetImagePath( wxString imagePath )
    {
        m_imagePath = imagePath; m_dirty = true;
    };
    wxString Project::GetCatalogFilename( )
    {
        return m_catalogFilename;
    };

    Settings* Project::GetSettings( )
    {
        return  m_settings;
    };
    void Project::SetSettings( Settings* settings )
    {
        m_settings = settings;
    };

    Catalog::CatalogData* Project::GetCatalogData( )
    {
        return m_catalogData;
    };
    Layout::AlbumData* Project::GetAlbumData( )
    {
        return m_albumData;
    };


    void Project::SetCatalogFilename( wxString catalogFilename )
    {
        if ( m_catalogFilename.Cmp( catalogFilename ) )
        {
            m_catalogFilename = catalogFilename;
            m_dirty = true;
        }
    };

    void Project::SetCatalogData( Catalog::CatalogData* catalogData )
    {
        if ( catalogData != m_catalogData )
        {
            delete m_catalogData;
            m_catalogData = ( Catalog::CatalogData* )0;
        }
        m_catalogData = catalogData;
    };

    void Project::SetAlbumData( Layout::AlbumData* albumData )
    {
        if ( albumData != m_albumData )
        {
            delete m_albumData;
            m_albumData = ( Layout::AlbumData* )0;
        }
        m_albumData = albumData;
    };

wxString Project::MakeFile( wxString filename)
{
    wxFileName newFile(filename);
    if ( !newFile.IsAbsolute() )
    {
        newFile.MakeAbsolute();
    }
    return newFile.GetFullPath();
}

    bool Project::LoadProject( wxString filename )
    {
        wxFileName projFile(filename);
        if ( projFile.FileExists() )
        {
            if ( !projFile.IsAbsolute() )
            {
                projFile.MakeAbsolute();
            }
        }
        else
        {
            //setup new files
            return false;
        }

        wxString cwd = projFile.GetPath();
        m_settings->SetWorkingDirectory( cwd );
        wxFileName::SetCwd( cwd ) ;	
        m_projectFilename = projFile.GetFullPath();


        m_ProjectDoc = new wxXmlDocument();
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
        return true;
    }

    bool Project::LoadAttributes( wxXmlNode* thisObject )
    {
        const wxXmlAttribute* attr = thisObject->GetAttributes( );
        wxFileName filename;
        while ( attr )
        {
            wxString name = attr->GetName( );
            wxString val = attr->GetValue( );

            if ( !name.Cmp( "OutputName" ) )
            {
                m_outputFilename = MakeFile( val );
            }
            else if ( !name.Cmp( "Album" ) )
            {
                m_albumFilename = MakeFile( val );
            }
            else if ( !name.Cmp( "ImagePath" ) )
            {
                GetSettings()->SetImageDirectory(  MakeFile( val ) );
            }
            else if ( !name.Cmp( "Catalog" ) )
            {
                m_catalogFilename = MakeFile( val );
            }
            attr = attr->GetNext( );
        }
    }
}