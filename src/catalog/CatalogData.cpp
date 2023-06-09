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
#include "catalog/StampMount.h"

namespace Catalog
{

    ///  @brief Create anew empty Catalog
    ///  
    ///  @return Catalog::CatalogVolume* 
    Catalog::CatalogVolume* CatalogData::NewCatalogVolume( )
    {
        if ( m_catalogTreeCtrl )
        {
            m_catalogTreeCtrl->ClearCatalogTree( );
        }
        // if ( m_albumPageTreeCtrl )
        // {
        //     m_albumPageTreeCtrl->ClearCatalogTree( );
        // }

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
        //       wxString artPath = GetImagePath( );
        wxString fileName = stampId;
        wxString imageFile;
        if ( fileName.IsEmpty( ) )
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
            //            fn.SetPath( artPath );
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

    InventoryPanel* CatalogData::GetInventoryPanel( ) { return GetDescriptionPanel( )->GetInventoryPanel( ); };

    void CatalogData::LoadCatalogTree( )
    {
        //        SetCollectionListStrings( );
        //        SetCollectionListSelection( );

        GetCatalogTreeCtrl( )->LoadTree( );
        //  GetAlbumPageTreeCtrl( )->LoadTree( );
    }

    bool CatalogData::ImportCSV( wxString csvFilename )
    {
        wxFileName csvFile( csvFilename );
        wxString ext = csvFile.GetExt( );
        if ( !ext.CmpNoCase( "csv" ) )
        {

            wxString cwd = wxGetCwd( );
            wxFileName catalogFile;// = csvFile;
            catalogFile.SetPath( cwd );

            wxString name = csvFile.GetName( );
            catalogFile.SetName( name );
            catalogFile.SetExt( "cat" );

            Catalog::CatalogVolume* catalogVolume = GetCatalogList( )->NewCatalogVolume( );
            wxString fullPath = catalogFile.GetFullPath( );
            wxString fullName = catalogFile.GetFullName( );
            wxString path = catalogFile.GetPath( );
            catalogVolume->SetVolumeFilename( catalogFile.GetFullPath( ) );

            bool readStatus = catalogVolume->LoadCSV( csvFile.GetFullPath( ) );
            if ( readStatus )
            {
                GetCatalogList( )->BuildVolumeNameStrings( );
                UpdateCatalogVolumeStrings( );
                GetCatalogVolume( )->EditDetailsDialog( m_catalogTreePanel );

                GetCatalogVolume( )->MakeCatalogImageRepository( );
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

    wxXmlDocument* CatalogData::LoadMountCSV( )
    {
        // StampMountData* stampMount = new StampMountData( );
        wxString mountFile = "StampMounts.csv";
        wxXmlDocument* res = GetStampMountData( )->LoadXML( );
        //LoadMountCSV( mountFile );
        return res;
    }

    void CatalogData::LoadNew( wxString catFile )
    {
        Catalog::CatalogVolume* volume = GetCatalogList( )->NewCatalogVolume( );
        volume->SetVolumeFilename( catFile );
        //        GetProject( )->SetCatalogFilename( catFile );
        LoadCatalogTree( );
        SetDirty( );
    }

    void CatalogData::SetCurrentStamp( wxXmlNode* xmlNode )
    {
        m_stamp = xmlNode;
        GetDescriptionPanel( )->UpdatePanel( );
        GetDescriptionPanel( )->Show( );
    };

    void CatalogData::SetCollectionListStrings( )
    {
        m_catalogTreePanel->SetCollectionListStrings( );
    }
    void CatalogData::SetCollectionListSelection( )
    {
        m_catalogTreePanel->SetCollectionListSelection( );
    }

    void CatalogData::UpdateCatalogVolumeStrings( )
    {
        m_catalogTreePanel->SetVolumeListStrings( m_catalogList.GetVolumeNameStrings( ) );
        m_catalogTreePanel->SetVolumeListSelection( m_catalogList.GetCatalogVolumeNdx( ) );
    }
}