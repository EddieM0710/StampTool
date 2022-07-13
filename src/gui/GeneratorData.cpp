/**
 * @file GeneratorData.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "gui/GeneratorData.h" 
#include "catalog/CatalogDefs.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include "design/DesignData.h"
#include "catalog/CatalogData.h"

GeneratorData* NewGeneratorDataInstance()
{
   return new GeneratorData();
}

GeneratorData::GeneratorData( ) {
    m_catalogData = 0;
    m_designData = 0;
    m_catalogTreeCtrl = 0;
    m_designTreeCtrl = 0;
    m_descriptionPanel = 0;
    m_project = 0;
    m_settings = 0;
};

void GeneratorData::InitGeneratorData()
{
        m_catalogData = 0;
        m_designData = 0;
        m_catalogTreeCtrl = 0;
        m_designTreeCtrl = 0;
        m_descriptionPanel = 0;
        SetProject( Utils::NewProjectInstance());

        m_settings = Utils::NewSettingsInstance( );

        if ( m_settings->GetLoadLastFileAtStartUp( ) )
        {
            m_project->SetProjectFilename( m_settings->GetLastFile( ) );

            // if ( wxFileExists( filename ) )
            // {
            //     if ( LoadProjectXML( filename ) )
            //     {
            //     }
            // }
        }
}

void GeneratorData::SetProject( Utils::Project* project ) 
{ 
    if ( m_project ) 
    {
        m_project->~Project();
    }
    m_project = project; 
};



void GeneratorData::FileNewProject()
{
    LoadNewDesign();
    LoadNewCatalog();
}

// Load the Catalog and Design data then populate trees
void GeneratorData::LoadData( )
{
    ReadCatalogFile( );
    LoadCatalogTree( );
    ReadDesignFile( );
    LoadDesignTree( );
    InitODTDocument( );
}

void GeneratorData::FileOpenProject(wxString filename)
{
    m_project->SetProjectFilename( filename );
    m_project->LoadProjectXML( );
    LoadData( );
}

void GeneratorData::FileSaveProject( )
{
    m_project->Save( );   
}

void GeneratorData::FileSaveAsProject( wxString filename )
{
    m_project->SetProjectFilename( filename );
    FileSaveProject( );
}

Catalog::CatalogData* GeneratorData::NewCatalogData( )
{
    if ( m_catalogData )
    {
        m_catalogData->~CatalogData();
        m_catalogTreeCtrl->ClearCatalogTree();
    }
    m_catalogData = Catalog::NewCatalogDataInstance();
    return m_catalogData;
};

// void GeneratorData::LoadCatalogXML( wxString catalogFilename )
// {
// }

////*****

void GeneratorData::ReadCatalogFile( )
{
    NewCatalogData( );
    m_catalogData->LoadXML( m_project->GetCatalogFilename() );
}


void GeneratorData::ReadCatalogCSV( wxString csvFilename )
{
    wxFileName csvFile( csvFilename );
    wxString ext = csvFile.GetExt( );
    if ( !ext.CmpNoCase( "csv" ) )
    {
        wxFileName catalogFile = csvFile;
        catalogFile.SetExt( "cat.xml" );

        m_project->SetCatalogFilename( catalogFile.GetFullPath( ) );

        NewCatalogData( );
        m_catalogData->LoadCSV( csvFile.GetFullPath() );

    }
}

void GeneratorData::LoadCatalogTree( )
{
    GetCatalogTreeCtrl( )->LoadTree( );
}

void GeneratorData::LoadNewCatalog( )
{
    Catalog::NewCatalogDataInstance();
    m_project->SetCatalogFilename("unnamed.cat.xml");
    LoadCatalogTree( );
    SetDirty();
}
Design::DesignData* GeneratorData::FileOpenDesign( wxString filename )
{
    m_project->SetDesignFilename( filename );
    ReadDesignFile( );
    LoadDesignTree( );
}
Design::DesignData* GeneratorData::FileOpenCatalog( wxString filename )
{
    m_project->SetCatalogFilename( filename );
    ReadCatalogFile( );
    LoadCatalogTree( );
}

Design::DesignData* GeneratorData::NewDesignData( void )
{
    if ( m_designData )
    {
        delete m_designData;

        m_designTreeCtrl->DeleteAllItems( );
        m_StampAlbumCatalogLink.Clear( );
    }
    m_designData = Design::NewDesignDataInstance( );
    return m_designData;
}


void GeneratorData::ReadDesignFile( )
{
    NewDesignData( );
    wxString albumFilename = m_project->GetDesignFilename( );
    m_designData->LoadXML( albumFilename );
}


void GeneratorData::LoadDesignTree( )
{
    GetDesignTreeCtrl( )->LoadTree( );
}

void GeneratorData::LoadDefaultDesignData( )
{
    NewDesignData( );
    m_designData->LoadDefaultDocument( );
}

void GeneratorData::LoadNewDesign( )
{
    m_project->SetDesignFilename("unnamed.alb.xml");
    m_project->SetODTOutputFilename( "unnamed.odt" );
    LoadDefaultDesignData();
    LoadDesignTree( );
    SetDirty(false);
}

void GeneratorData::FileSaveDesign( )
{    
    m_designData->SaveXML( GetProject( )->GetDesignFilename( ) );
};

void GeneratorData::FileSaveAsDesign( wxString filename )
{    
    m_project->SetDesignFilename( filename );
    FileSaveDesign( );
};

    void GeneratorData::FileSaveAsCatalog( wxString filename )
    {
        m_project->SetCatalogFilename( filename );
        FileSaveCatalog( );
    }
    
    void GeneratorData::FileSaveCatalog( )
    {
        m_catalogData->Save( );
    }

void GeneratorData::InitODTDocument( )
{
    ODT::Document* odtDoc = new ODT::Document( );
    SetODTDocument( odtDoc );
}

ODT::Document* GeneratorData::GetODTDocument( )
{
    return m_ODTDoc;
};

//*****

void GeneratorData::SetODTDocument( ODT::Document* doc )
{
    m_ODTDoc = doc; SetDirty( );
};

void GeneratorData::InitLoad( )
{
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    {
        m_project->LoadProjectXML( );
        LoadData( );
    }
}


wxString GeneratorData::GetImageFilename( wxString stampId )
{

    wxString dirName = GetSettings( )->GetImageDirectory( );
    wxString fileName = stampId ;
    wxString imageFile;
    if ( dirName.IsEmpty() || fileName.IsEmpty() )
    {
        imageFile = "";
    }
    else
    {
        fileName = fileName.Trim(true);
        fileName = fileName.Trim(false);
        fileName.Replace(":","_");
        fileName.Replace(" ","_");
        imageFile =  wxString::Format( "%s/%s.jpg", dirName, fileName );
    }    
    return imageFile;
}
