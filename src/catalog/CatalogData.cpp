/**
 * @file CatalogData.cpp
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

#include "catalog/CatalogData.h"
#include "catalog/CatalogVolume.h"
#include "catalog/Entry.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/StampDescriptionPanel.h"
#include "gui/ToolData.h" 
#include "utils/Project.h"
#include "Defs.h" 

namespace Catalog
{

    Catalog::CatalogVolume* CatalogData::NewCatalogVolume( )
    {
        if ( m_catalogPageTreeCtrl )
        {
            m_catalogPageTreeCtrl->ClearCatalogTree( );
        }
        if ( m_albumPageTreeCtrl )
        {
            m_albumPageTreeCtrl->ClearCatalogTree( );
        }

        return m_catalogList.NewCatalogVolume( );
    };

    // void CatalogData::LoadCatalogXML( wxString catalogFilename )
    // { 
    // }

    //*****

    void CatalogData::LoadCatalogVolumeFiles( )
    {
        m_catalogList.LoadCatalogVolumes( );
    }


    bool CatalogData::ReadCatalogCSV( wxString csvFilename )
    {
        wxFileName csvFile( csvFilename );
        wxString ext = csvFile.GetExt( );
        if ( !ext.CmpNoCase( "csv" ) )
        {
            wxFileName catalogFile = csvFile;
            catalogFile.SetExt( "cat.xml" );

            GetProject( )->SetCatalogFilename( catalogFile.GetFullPath( ) );

            Catalog::CatalogVolume* catalogVolume = NewCatalogVolume( );

            catalogVolume->SetVolumeFilename( catalogFile.GetFullPath( ) );
            return catalogVolume->LoadCSV( csvFile.GetFullPath( ) );
        }
        return false;
    }

    void CatalogData::LoadCatalogTree( )
    {
        GetCatalogPageTreeCtrl( )->LoadTree( );
        GetAlbumPageTreeCtrl( )->LoadTree( );
    }

    void CatalogData::LoadNew( wxString catFile )
    {
        Catalog::NewCatalogVolumeInstance( );
        GetProject( )->SetCatalogFilename( catFile );
        LoadCatalogTree( );
        SetDirty( );
    }

    void CatalogData::FileOpen( wxString filename )
    {
        GetProject( )->SetCatalogFilename( filename );
        LoadCatalogVolumeFiles( );
        LoadCatalogTree( );
    }

    void CatalogData::FileSaveAs( wxString filename )
    {
        GetProject( )->SetCatalogFilename( filename );
        FileSave( );
    }

    void CatalogData::FileSave( )
    {
        m_catalogList.SaveCatalogVolumes( );
    }


    wxString CatalogData::GetImagePath( )
    {
        wxString sectFilename = GetCatalogVolume( )->GetVolumeFilename( );
        wxFileName fn( sectFilename );
        fn.ClearExt( );
        fn.SetName( "" );
        wxString dirName = GetCatalogVolume( )->GetCatalogVolumeImagePath( );
        if ( !dirName.IsEmpty( ) )
        {
            fn.AppendDir( dirName );
        }
        return fn.GetPath( );
    }

    wxString CatalogData::GetImageFilename( wxString stampId )
    {

        wxString artPath = GetImagePath( );
        wxString fileName = stampId;
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
            imageFile = fn.GetFullPath( );
            // wxString::Format( "%s/%s.jpg", dirName, fileName );
        }
        return imageFile;
    }
    // void CatalogData::InitLoad( )
    // { 
    //     if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    //     { 
    //         m_project->LoadProjectXML( );
    //         LoadData( );
    //     }
    // }


    // Load the Catalog and Design data then populate trees
    void CatalogData::LoadData( )
    {
        LoadCatalogVolumeFiles( );
        LoadCatalogTree( );
    }

    void CatalogData::SetCurrentStamp( wxXmlNode* stamp )
    {
        if ( m_stamp )
        {
            delete m_stamp;
        }
        m_stamp = new Catalog::Entry( stamp );
        GetDescriptionPanel( )->Show( );
    };
}