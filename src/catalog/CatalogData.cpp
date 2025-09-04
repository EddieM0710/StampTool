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
#include "collection/CollectionList.h"
#include "collection/Collection.h"
#include "catalog/Entry.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/CatalogPanel.h"
#include "gui/AlbumPanel.h"
#include "gui/StampDescriptionPanel.h"
#include "gui/InventoryPanel.h"
#include "utils/Project.h"
#include "Defs.h" 
#include "catalog/StampMount.h"
#include "gui/CatalogTOCTreeCtrl.h"
#include "GenerateList.h"

namespace Catalog
{
    void CatalogData::Clear( )
    {
        m_stamp = 0;
        m_catalogList.Clear( );
        m_catalogTreeCtrl->Clear( );
        m_catalogTocTreeCtrl->Clear( );
        m_stampDescriptionPanel->Clear( );
        //m_generateListPanel->Clear;

        m_catalogPanel->Clear( );

    }

    void CatalogData::FileOpen( wxString filename )
    {
        GetCatalogList( )->NewCatalogVolume( filename );
        // GetCatalogList( )->BuildVolumeNameStrings( );
        // UpdateCatalogVolumeStrings( );
        // LoadCatalogTree( );
    }
    // void CatalogData::FindStamp( )
    // {
    //     m_catalogList.GetArray( );

    //     Utils::VolumeArray* array = m_catalogList.GetArray( );

    //     Utils::VolumeArray::iterator it = array->begin( );

    //     // Iterate through the map and print the elements
    //     while ( it != array->end( ) )
    //     {
    //         Utils::Volume* volume = ( Utils::Volume* ) ( it->second );
    //         volume->Find( );
    //         ++it;
    //     }
    // };


    void CatalogData::FileSave( )
    {
        m_catalogList.SaveVolumes( );
    }

    InventoryPanel* CatalogData::GetInventoryPanel( ) {
        return GetDescriptionPanel( )->GetInventoryPanel( );
    };

    wxXmlDocument* CatalogData::LoadMountCSV( )
    {
        wxString mountFile = "StampMounts.csv";
        wxXmlDocument* res = GetStampMountData( )->LoadXML( );
        return res;
    }

    // void CatalogData::LoadNew( wxString catFile )
    // {

    //     Catalog::CatalogVolume* volume = GetCatalogList( )->AddNewVolume( catFile );

    //     LoadCatalogTree( );
    //     volume->SetDirty( false );

    // }

    // Catalog::CatalogVolume* CatalogData::NewCatalogVolume( wxString filename )
    // {
    //     CatalogVolume* vol = new CatalogVolume( );
    //     vol->SetFilename( filename );
    //     vol->Load( );

    //     wxString volName = vol->GetName( );
    //     Catalog::CatalogList* list = GetCatalogData( )->GetCatalogList( );
    //     list->SetCurrentVolume( vol );
    //     return vol;
    // }

    // Update the Inventory Panel and reload the catalog tree 
    // to reflect new collection
    void CatalogData::SetCollection( wxString newCollection )
    {
        Inventory::Collection* currCol = GetCollectionList( )->GetCurrentCollection( );

        if ( newCollection.Cmp( currCol->GetName( ) ) )
        {
            //the Catalog tree will need to be rebuilt (i.e., the ID's will change) so save the selected node
            wxXmlNode* ele = GetCatalogTreeCtrl( )->GetSelectionNode( );

            //set the new selection
            GetCollectionList( )->SetCurrentCollection( newCollection );

            //update the panels
            UpdateCatalogPanels( );

            // find the node in the new tree
            GetCatalogTreeCtrl( )->SetSelection( ele );

        }

    }

    void CatalogData::SetCurrentStamp( wxXmlNode* xmlNode )
    {
        m_stamp = xmlNode;
        GetDescriptionPanel( )->UpdatePanel( );
        GetDescriptionPanel( )->Show( );
    };

    void CatalogData::UpdateCatalogPanels( )
    {
        //update the inventory
        GetInventoryPanel( )->UpdateInventory( );

        // reload the tree
        GetCatalogTreeCtrl( )->LoadCatalogTree( );

        GetCatalogPanel( )->SetVolumeListCtrl( );
    }
}