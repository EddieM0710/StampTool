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
 */

#include "catalog/CatalogData.h"
#include "catalog/CatalogVolume.h"
#include "catalog/Entry.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/CatalogPanel.h"
#include "gui/AlbumPanel.h"
#include "gui/StampDescriptionPanel.h"
 ////#include "gui/AppData.h" 
#include "utils/Project.h"
#include "Defs.h" 

namespace Catalog
{

    ///  @brief Create anew empty Catalog
    ///  
    ///  @return Catalog::CatalogVolume* 
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

    ///  @brief Open a catalog file
    ///  
    ///  @param filename 
    void CatalogData::FileOpen( wxString filename )
    {
        Catalog::CatalogVolume* volume = GetCatalogList( )->NewCatalogVolume( );
        volume->SetVolumeFilename( filename );
        volume->Load( );
        GetCatalogList( )->BuildVolumeNameStrings( );
        UpdateCatalogVolumeStrings( );
        LoadCatalogTree( );
    }

    ///  @brief Save a catalog file
    ///  
    void CatalogData::FileSave( )
    {
        m_catalogList.SaveCatalogVolumes( );
    }

    // void CatalogData::FileSaveAs( wxString filename )
    // {
    //     GetProject( )->SetCatalogFilename( filename );
    //     FileSave( );
    // }

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

    void CatalogData::LoadCatalogTree( )
    {
        GetCatalogPageTreeCtrl( )->LoadTree( );
        GetAlbumPageTreeCtrl( )->LoadTree( );
    }

    bool CatalogData::ImportCSV( wxString csvFilename )
    {
        wxFileName csvFile( csvFilename );
        wxString ext = csvFile.GetExt( );
        if ( !ext.CmpNoCase( "csv" ) )
        {
            wxFileName catalogFile = csvFile;
            catalogFile.SetExt( "cat" );

            Catalog::CatalogVolume* catalogVolume = GetCatalogList( )->NewCatalogVolume( );

            catalogVolume->SetVolumeFilename( catalogFile.GetFullPath( ) );
            bool readStatus = catalogVolume->LoadCSV( csvFile.GetFullPath( ) );
            if ( readStatus )
            {
                GetCatalogList( )->BuildVolumeNameStrings( );
                UpdateCatalogVolumeStrings( );
                GetCatalogVolume( )->EditDetailsDialog( m_catalogNotebookPagePanel );
                GetCatalogData( )->LoadCatalogTree( );
            }
            return readStatus;
        }
        return false;
    }

    ///  @brief  Load the Catalog data then populate trees
    ///  
    void CatalogData::LoadData( )
    {
        m_catalogList.Load( );
        GetCatalogList( )->BuildVolumeNameStrings( );
        UpdateCatalogVolumeStrings( );
        LoadCatalogTree( );
    }

    void CatalogData::LoadNew( wxString catFile )
    {
        Catalog::CatalogVolume* volume = GetCatalogList( )->NewCatalogVolume( );
        volume->SetVolumeFilename( catFile );
        //        GetProject( )->SetCatalogFilename( catFile );
        LoadCatalogTree( );
        SetDirty( );
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

    void CatalogData::UpdateCatalogVolumeStrings( )
    {
        m_catalogNotebookPagePanel->SetVolumeListStrings( m_catalogList.GetVolumeNameStrings( ) );
        m_albumNotebookPagePanel->SetVolumeListStrings( m_catalogList.GetVolumeNameStrings( ) );
        m_catalogNotebookPagePanel->SetVolumeListSelection( m_catalogList.GetCatalogVolumeNdx( ) );
        m_albumNotebookPagePanel->SetVolumeListSelection( m_catalogList.GetCatalogVolumeNdx( ) );
    }
}