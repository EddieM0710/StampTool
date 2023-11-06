/**
 * @file AppData.cpp
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
#include <wx/log.h>

#include "Defs.h"
#include "catalog/CatalogDefs.h"
#include "catalog/CatalogVolume.h"
#include "catalog/CatalogData.h"
#include "collection/CollectionList.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/StampToolFrame.h"
#include "gui/AppData.h" 
#include "utils/Settings.h"
#include "utils/Project.h"

#include "design/AlbumVolume.h"
#include "design/AlbumData.h"
#include "catalog/StampMount.h"


 //--------

AppData::AppData( ) {

    m_catalogData = new Catalog::CatalogData( );
    m_albumData = new Design::AlbumData( );
    m_mountData = new Catalog::StampMountData( );
    m_collectionList = new Inventory::CollectionList( );

    // two entries in an array
    defaultDash.Add( .6 );
    defaultDash.Add( .6 );

};

//--------

void AppData::Clear( )
{

    m_collectionList->Clear( );
    m_mountData->Clear( );

    m_catalogData->Clear( );
    m_albumData->Clear( );
    m_StampAlbumCatalogLink->Clear( );
    m_project->CloseProject( );

}

//--------

void AppData::SetCaption( )
{
    GetProject( )->SetCaption( );
}

//--------


Design::AlbumData* AppData::GetAlbumData( ) {
    return m_albumData;
};

//--------

Catalog::CatalogData* AppData::GetCatalogData( ) {
    return m_catalogData;
};

//--------

Inventory::CollectionList* AppData::GetCollectionList( ) {
    return m_collectionList;
};

//--------

Catalog::StampMountData* AppData::GetStampMountData( ) {
    return m_mountData;
};

//--------

Utils::Project* AppData::GetProject( ) {
    return  m_project;
};

//--------

Utils::Settings* AppData::GetSettings( ) {
    return m_settings;
};

//--------

Utils::StampList* AppData::GetStampAlbumCatalogLink( ) {
    return m_StampAlbumCatalogLink;
};

//--------

void AppData::InitAppData( )
{
    m_settings = new Utils::Settings( );
    m_project = new Utils::Project( );
    m_StampAlbumCatalogLink = new Utils::StampList( );

    m_project->InitProject( );
    m_settings->InitSettings( );

    if ( m_settings->GetLoadLastFileAtStartUp( ) )
    {
        m_project->SetProjectFilename( m_settings->GetLastFile( ) );
    }
    else
    {
        m_project->SetProjectFilename( "" );
    }
}

