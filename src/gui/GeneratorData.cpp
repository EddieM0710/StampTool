/**
 * @file GeneratorData.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
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
#include "catalog/CatalogVolumeData.h"

#include <wx/log.h>

GeneratorData* NewGeneratorDataInstance()
{
   return new GeneratorData();
}

GeneratorData::GeneratorData( ) {

    m_designData = 0;
    m_catalogTreeCtrl = 0;
    m_designTreeCtrl = 0;
    m_stampDescriptionPanel = 0;
    m_project = 0;
    m_settings = 0;
};

void GeneratorData::InitGeneratorData()
{
        m_designData = 0;
        m_catalogTreeCtrl = 0;
        m_designTreeCtrl = 0;
        m_stampDescriptionPanel = 0;
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



void GeneratorData::FileNewProject( wxString prjName )
{
    m_project->SetProjectFilename( prjName );
    wxString lastFile = wxGetCwd();
    lastFile += "/" + prjName;
    GetSettings()->SetLastFile(lastFile);
    //LoadNewDesign();
   // LoadNewCatalog();
}

// Load the Catalog and Design data then populate trees
void GeneratorData::LoadData( )
{
    bool state = wxLog::IsEnabled( ) 	;
    LoadCatalogVolumeFiles( );
    LoadCatalogTree( );
    ReadDesignFile( );
    LoadDesignTree( );
    CreateODTDocument( );
}

void GeneratorData::FileOpenProject(wxString filename)
{
    m_project->SetProjectFilename( filename );
    wxString lastFile = wxGetCwd();
    lastFile += "/" + filename;
    GetSettings()->SetLastFile(lastFile);
    m_project->LoadProjectXML( );
    LoadData( );
}

void GeneratorData::FileSaveProject( )
{
    m_settings->Save();
    m_project->Save( );   
}

void GeneratorData::FileSaveAsProject( wxString filename )
{
    m_project->SetProjectFilename( filename );
    wxString lastFile = wxGetCwd();
    lastFile += "/" + filename;
    GetSettings()->SetLastFile(lastFile);
    FileSaveProject( );
}

Catalog::CatalogVolumeData* GeneratorData::NewCatalogVolumeData( )
{
    if ( m_catalogTreeCtrl )
    {
        m_catalogTreeCtrl->ClearCatalogTree();
    }

    return m_catalogData.NewCatalogVolumeData();
};

// void GeneratorData::LoadCatalogXML( wxString catalogFilename )
// {
// }

////*****

void GeneratorData::LoadCatalogVolumeFiles( )
{
    m_catalogData.LoadCatalogVolumes();
}


bool GeneratorData::ReadCatalogCSV( wxString csvFilename )
{
    wxFileName csvFile( csvFilename );
    wxString ext = csvFile.GetExt( );
    if ( !ext.CmpNoCase( "csv" ) )
    {
        wxFileName catalogFile = csvFile;
        catalogFile.SetExt( "cat.xml" );

        m_project->SetCatalogFilename( catalogFile.GetFullPath( ) );

        Catalog::CatalogVolumeData* catalogVolumeData = NewCatalogVolumeData( );

        catalogVolumeData->SetVolumeFilename( catalogFile.GetFullPath( ) );
        return catalogVolumeData->LoadCSV( csvFile.GetFullPath() );
    }
}

void GeneratorData::LoadCatalogTree( )
{
    GetCatalogTreeCtrl( )->LoadTree( );
}

void GeneratorData::LoadNewCatalog( wxString catFile )
{
    Catalog::NewCatalogVolumeDataInstance();
    m_project->SetCatalogFilename( catFile );
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
    LoadCatalogVolumeFiles( );
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

void GeneratorData::LoadNewDesign( wxString designFileName  )
{
    m_project->SetDesignFilename(designFileName);
   // wxFileName file( designFileName );
   // wxString name = file.GetName();
    int pos = designFileName.find_first_of(".");
    wxString odtName = designFileName.Mid( 0, pos );
    odtName += ".odt";
    m_project->SetODTOutputFilename( odtName );

    LoadDefaultDesignData();
    LoadDesignTree( );
    SetDirty(false);
}

void GeneratorData::FileSaveDesign( )
{    
    if ( m_designData )
    {
        m_designData->SaveXML( GetProject( )->GetDesignFilename( ) );
    }
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
        m_catalogData.SaveCatalogVolumes( );
    }

void GeneratorData::CreateODTDocument( )
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

wxString GeneratorData::GetImagePath()
{
    wxString volFilename = GetCatalogVolumeData()->GetVolumeFilename();
    wxFileName fn(volFilename);
    fn.ClearExt();
    fn.SetName("");
    wxString dirName = GetCatalogVolumeData()->GetCatalogVolumeImagePath( );
    if ( !dirName.IsEmpty() )
    {
        fn.AppendDir(dirName);
    }    
    return fn.GetPath();
}

wxString GeneratorData::GetImageFilename( wxString stampId )
{

    wxString artPath = GetImagePath();
    wxString fileName = stampId ;
    wxString imageFile;
    if ( artPath.IsEmpty() || fileName.IsEmpty() )
    {
        imageFile = "";
    }
    else
    {
        fileName = fileName.Trim(true);
        fileName = fileName.Trim(false);
        fileName.Replace(":","_");
        fileName.Replace(" ","_");
        wxFileName fn;
        fn.SetPath( artPath );
        fn.SetName(fileName);
        fn.SetExt("jpg");
        imageFile = fn.GetFullPath();// wxString::Format( "%s/%s.jpg", dirName, fileName );
    }    
    return imageFile;
}
