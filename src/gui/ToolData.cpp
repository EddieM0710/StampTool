/**
 * @file ToolData.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright ( c ) 2022
 * 
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/
#include <wx/log.h>

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogSectionData.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/ToolData.h" 
#include "utils/Settings.h"
#include "utils/Project.h"

#include "design/DesignData.h"


ToolData* NewToolDataInstance( )
{ 
   return new ToolData( );
}

ToolData::ToolData( ) { 

    m_designData = 0;
    m_catalogPageTreeCtrl = 0;
    m_albumPageTreeCtrl = 0;
    m_designTreeCtrl = 0;
    m_stampDescriptionPanel = 0;
    m_project = 0;
    m_settings = 0;
};

void ToolData::InitToolData( )
{ 
        m_designData = 0;
        m_catalogPageTreeCtrl = 0;
        m_albumPageTreeCtrl = 0;
        m_designTreeCtrl = 0;
        m_stampDescriptionPanel = 0;
        SetProject( Utils::NewProjectInstance( ) );

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

void ToolData::SetProject( Utils::Project* project ) 
{ 
    if ( m_project ) 
    { 
        m_project->~Project( );
    }
    m_project = project; 
};



void ToolData::FileNewProject( wxString prjName )
{ 
    m_project->SetProjectFilename( prjName );
    wxString lastFile = wxGetCwd( );
    lastFile += "/" + prjName;
    GetSettings( )->SetLastFile( lastFile );
    //LoadNewDesign( );
   // LoadNewCatalog( );
}

// Load the Catalog and Design data then populate trees
void ToolData::LoadData( )
{ 
    bool state = wxLog::IsEnabled( ) 	;
    LoadCatalogSectionFiles( );
    LoadCatalogTree( );
    ReadDesignFile( );
    LoadDesignTree( );
}

void ToolData::FileOpenProject( wxString filename )
{ 
    m_project->SetProjectFilename( filename );
    wxString lastFile = wxGetCwd( );
    lastFile += "/" + filename;
    GetSettings( )->SetLastFile( lastFile );
    m_project->LoadProjectXML( );
    LoadData( );
}

void ToolData::FileSaveProject( )
{ 
    m_settings->Save( );
    m_project->Save( );   
}

void ToolData::FileSaveAsProject( wxString filename )
{ 
    m_project->SetProjectFilename( filename );
    wxString lastFile = wxGetCwd( );
    lastFile += "/" + filename;
    GetSettings( )->SetLastFile( lastFile );
    FileSaveProject( );
}

Catalog::CatalogSectionData* ToolData::NewCatalogSectionData( )
{ 
    if ( m_catalogPageTreeCtrl )
    { 
        m_catalogPageTreeCtrl->ClearCatalogTree( );
    }
    if ( m_albumPageTreeCtrl )
    { 
        m_albumPageTreeCtrl->ClearCatalogTree( );
    }

    return m_catalogData.NewCatalogSectionData( );
};

// void ToolData::LoadCatalogXML( wxString catalogFilename )
// { 
// }

////*****

void ToolData::LoadCatalogSectionFiles( )
{ 
    m_catalogData.LoadCatalogSections( );
}


bool ToolData::ReadCatalogCSV( wxString csvFilename )
{ 
    wxFileName csvFile( csvFilename );
    wxString ext = csvFile.GetExt( );
    if ( !ext.CmpNoCase( "csv" ) )
    { 
        wxFileName catalogFile = csvFile;
        catalogFile.SetExt( "cat.xml" );

        m_project->SetCatalogFilename( catalogFile.GetFullPath( ) );

        Catalog::CatalogSectionData* catalogSectionData = NewCatalogSectionData( );

        catalogSectionData->SetSectionFilename( catalogFile.GetFullPath( ) );
        return catalogSectionData->LoadCSV( csvFile.GetFullPath( ) );
    }
    return false;
}

void ToolData::LoadCatalogTree( )
{ 
    GetCatalogPageTreeCtrl( )->LoadTree( );
    GetAlbumPageTreeCtrl( )->LoadTree( );
}

void ToolData::LoadNewCatalog( wxString catFile )
{ 
    Catalog::NewCatalogSectionDataInstance( );
    m_project->SetCatalogFilename( catFile );
    LoadCatalogTree( );
    SetDirty( );
}
Design::DesignData* ToolData::FileOpenDesign( wxString filename )
{ 
    m_project->SetDesignFilename( filename );
    ReadDesignFile( );
    LoadDesignTree( );
    return (Design::DesignData*)0;
}
Design::DesignData* ToolData::FileOpenCatalog( wxString filename )
{ 
    m_project->SetCatalogFilename( filename );
    LoadCatalogSectionFiles( );
    LoadCatalogTree( );
    return (Design::DesignData*)0;
}

Design::DesignData* ToolData::NewDesignData( void )
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


void ToolData::ReadDesignFile( )
{ 
    NewDesignData( );
    wxString albumFilename = m_project->GetDesignFilename( );
    m_designData->LoadXML( albumFilename );
}


void ToolData::LoadDesignTree( )
{ 
    GetDesignTreeCtrl( )->LoadTree( );
}

void ToolData::LoadDefaultDesignData( )
{ 
    NewDesignData( );
    m_designData->LoadDefaultDocument( );
}

void ToolData::LoadNewDesign( wxString designFileName  )
{ 
    m_project->SetDesignFilename( designFileName );

    LoadDefaultDesignData( );
    LoadDesignTree( );
    SetDirty( false );
}

void ToolData::FileSaveDesign( )
{    
    if ( m_designData )
    { 
        m_designData->SaveXML( GetProject( )->GetDesignFilename( ) );
    }
};

void ToolData::FileSaveAsDesign( wxString filename )
{    
    m_project->SetDesignFilename( filename );
    FileSaveDesign( );
};

    void ToolData::FileSaveAsCatalog( wxString filename )
    { 
        m_project->SetCatalogFilename( filename );
        FileSaveCatalog( );
    }
    
    void ToolData::FileSaveCatalog( )
    { 
        m_catalogData.SaveCatalogSections( );
    }


void ToolData::InitLoad( )
{ 
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    { 
        m_project->LoadProjectXML( );
        LoadData( );
    }
}

wxString ToolData::GetImagePath( )
{ 
    wxString sectFilename = GetCatalogSectionData( )->GetSectionFilename( );
    wxFileName fn( sectFilename );
    fn.ClearExt( );
    fn.SetName( "" );
    wxString dirName = GetCatalogSectionData( )->GetCatalogSectionImagePath( );
    if ( !dirName.IsEmpty( ) )
    { 
        fn.AppendDir( dirName );
    }  
    return fn.GetPath( );
}

wxString ToolData::GetImageFilename( wxString stampId )
{ 

    wxString artPath = GetImagePath( );
    wxString fileName = stampId ;
    wxString imageFile;
    if ( artPath.IsEmpty( ) || fileName.IsEmpty( ) )
    { 
        imageFile = "";
    }
    else
    { 
        fileName = fileName.Trim( true );
        fileName = fileName.Trim( false );
        fileName.Replace( ":", "_" );
        fileName.Replace( " ", "_" );
        wxFileName fn;
        fn.SetPath( artPath );
        fn.SetName( fileName );
        fn.SetExt( "jpg" );
        imageFile = fn.GetFullPath( );// wxString::Format( "%s/%s.jpg", dirName, fileName );
    }  
    return imageFile;
}
