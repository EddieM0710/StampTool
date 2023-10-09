/**
 * @file Defs.cpp
 * @author Eddie Monroe ( you@domain.com )
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright ( c ) 2021
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Defs.h"
#include "CatalogDefs.h"
#include "DesignDefs.h"
#include "CatalogVolume.h"
#include "catalog/CatalogData.h"
#include "catalog/StampMount.h"
#include "collection/CollectionData.h"
#include "design/AlbumData.h"
#include "Settings.h"
#include "utils/Project.h"
#include "gui/AppData.h"
#include "gui/CatalogTOCTreeCtrl.h"
#include "StampToolApp.h"
wxDECLARE_APP( StampToolApp );

bool Dirty = false;

//namespace Inventory { class CollectionData; };

void SetDirty( bool state ) {
    Dirty = state;
};
bool IsDirty( ) {
    return Dirty;
};


Design::AlbumData* GetAlbumData( ) {
    return GetAppData( )->GetAlbumData( );
}

AlbumImagePanel* GetAlbumImagePanel( ) {
    return GetAlbumData( )->GetAlbumImagePanel( );
};

//CatalogTreeCtrl* GetAlbumPageTreeCtrl( ) { return GetCatalogData( )->GetAlbumPageTreeCtrl( ); };

AlbumTreeCtrl* GetAlbumTreeCtrl( ) {
    return GetAlbumData( )->GetAlbumTreeCtrl( );
};

Design::AlbumVolume* GetAlbumVolume( ) {
    return GetAlbumData( )->GetAlbumVolume( );
};

Catalog::CatalogData* GetCatalogData( ) {
    return GetAppData( )->GetCatalogData( );
}

Inventory::CollectionList* GetCollectionList( ) {
    return GetAppData( )->GetCollectionList( );
}

Catalog::StampMountData* GetStampMountData( ) {
    return GetAppData( )->GetStampMountData( );
}

CatalogTreeCtrl* GetCatalogTreeCtrl( ) {
    return GetCatalogData( )->GetCatalogTreeCtrl( );
};
CatalogTOCTreeCtrl* GetCatalogTOCTreeCtrl( ) {
    return GetCatalogData( )->GetCatalogTOCTreeCtrl( );
};

AlbumTOCTreeCtrl* GetAlbumTOCTreeCtrl( ) {
    return GetAlbumData( )->GetAlbumTOCTreeCtrl( );
};

Utils::FontList* GetFontList( ) {
    return GetAlbumData( )->GetFontList( );
};

Catalog::CatalogVolume* GetCatalogVolume( )
{
    Catalog::CatalogData* genData = GetCatalogData( );
    if ( genData )
    {
        return genData->GetCatalogVolume( );
    }
    return ( Catalog::CatalogVolume* ) 0;
};

StampToolFrame* GetFrame( )
{
    return wxGetApp( ).GetFrame( );
}

AppData* GetAppData( )
{
    return wxGetApp( ).GetAppData( );
}


Utils::Project* GetProject( ) {
    return GetAppData( )->GetProject( );
}

Utils::Settings* GetSettings( )
{
    return GetAppData( )->GetSettings( );
};

Utils::StampList* GetStampAlbumCatalogLink( ) {
    return GetAppData( )->GetStampAlbumCatalogLink( );
};

void InitDefs( )
{
    Catalog::InitCatalogDefs( );
    Design::InitDesignDefs( Design::DD_Display );
}

void ReportError( wxString funct, wxString msg, bool fatal )
{
    wxString status = "";
    if ( fatal )
    {
        status = "fatal";
    }
    wxLogDebug( " Warning: %s %s %s\n", funct, msg, status );
}
