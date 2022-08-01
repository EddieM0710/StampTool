/**
 * @file IconDefs.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-04-01
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/log.h"
#include "wx/wx.h"
#endif

#include <iostream>

#include "wx/artprov.h"
#include "wx/image.h"
#include "wx/imaglist.h"

#include "gui/IconDefs.h"

namespace Design 
{
Design::IconID AlbumImageSelection[ Design::AT_NbrAlbumTypes ][ Catalog::ST_NbrCheckedStatusTypes ] = {
    { Design::Icon_Stamp, Design::Icon_StampSelected }, //   FT_FormatUnknown = 0,
    { Design::Icon_Stamp, Design::Icon_StampSelected }, //   FT_Stamp,
    { Design::Icon_StampBlock, Design::Icon_StampBlockSelected }, //   FT_Se_tenant,
    { Design::Icon_StampMiniSheet, Design::Icon_StampMiniSheetSelected }, //   FT_Mini_Sheet,
    { Design::Icon_StampSouvenirSheet, Design::Icon_StampSouvenirSheetSelected }, //   FT_Souvenir_Sheet,
    { Design::Icon_StampMiniSheet, Design::Icon_StampMiniSheetSelected }, //   FT_Booklet,
    { Design::Icon_StampMiniSheet, Design::Icon_StampMiniSheetSelected } }; //   FT_Tete_Beche,
}
// IconID CatalogImageSelection[ Catalog::FT_NbrTypes ][ 2 ] = {
//     { Icon_Stamp, Icon_StampSelected }, //   FT_FormatUnknown = 0,
//     { Icon_Stamp, Icon_StampSelected }, //   FT_Stamp,
//     { Icon_StampBlock, Icon_StampBlockSelected }, //   FT_Se_tenant,
//     { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Mini_Sheet,
//     { Icon_StampSouvenirSheet, Icon_StampSouvenirSheetSelected }, //   FT_Souvenir_Sheet,
//     { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Booklet,
//     { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Booklet_Pane,
//     { Icon_StampBlock, Icon_StampBlockSelected }, //   FT_Gutter_Pair,
//     { Icon_StampSouvenirSheet, Icon_StampSouvenirSheetSelected }, //    FT_Stamp_with_Attached_Label,
//     { Icon_StampBlock, Icon_StampBlockSelected } }; //   FT_Tete_Beche,

namespace Catalog
{
Catalog::IconID CatalogImageSelection[ Catalog::FT_NbrTypes ][ Catalog::ST_NbrInventoryStatusTypes   ] = {
    { Catalog::Icon_StampUnknown, Catalog::Icon_StampMissing, Catalog::Icon_StampOrdered, Catalog::Icon_StampOwn,
      Catalog::Icon_StampOwnVariant, Catalog::Icon_StampExclude }, //   FT_FormatUnknown = 0,
    { Catalog::Icon_StampUnknown, Catalog::Icon_StampMissing, Catalog::Icon_StampOrdered, Catalog::Icon_StampOwn,
      Catalog::Icon_StampOwnVariant, Catalog::Icon_StampExclude }, //   FT_Stamp,
    { Catalog::Icon_StampUnknownBlock, Catalog::Icon_StampMissingBlock, Catalog::Icon_StampOrderedBlock,
      Catalog::Icon_StampOwnBlock, Catalog::Icon_StampOwnVariantBlock,
      Catalog::Icon_StampExcludeBlock }, //   FT_Se_tenant,
    { Catalog::Icon_StampUnknownMiniSheet, Catalog::Icon_StampMissingMiniSheet,
      Catalog::Icon_StampOrderedMiniSheet, Catalog::Icon_StampOwnMiniSheet,
      Catalog::Icon_StampOwnVariantMiniSheet,
      Catalog::Icon_StampExcludeMiniSheet }, //   FT_Mini_Sheet,
    { Catalog::Icon_StampUnknownSouvenirSheet, Catalog::Icon_StampMissingSouvenirSheet,
      Catalog::Icon_StampOrderedSouvenirSheet, Catalog::Icon_StampOwnSouvenirSheet,
      Catalog::Icon_StampOwnVariantSouvenirSheet,
      Catalog::Icon_StampExcludeSouvenirSheet }, //   FT_Souvenir_Sheet,
    { Catalog::Icon_StampUnknownMiniSheet, Catalog::Icon_StampMissingMiniSheet,
      Catalog::Icon_StampOrderedMiniSheet, Catalog::Icon_StampOwnMiniSheet,
      Catalog::Icon_StampOwnVariantMiniSheet,
      Catalog::Icon_StampExcludeMiniSheet }, //   FT_Booklet,
    { Catalog::Icon_StampUnknownMiniSheet, Catalog::Icon_StampMissingMiniSheet,
      Catalog::Icon_StampOrderedMiniSheet, Catalog::Icon_StampOwnMiniSheet,
      Catalog::Icon_StampOwnVariantMiniSheet,
      Catalog::Icon_StampExcludeMiniSheet }, //   FT_Booklet_Pane,
    { Catalog::Icon_StampUnknownBlock, Catalog::Icon_StampMissingBlock, Catalog::Icon_StampOrderedBlock,
      Catalog::Icon_StampOwnBlock, Catalog::Icon_StampOwnVariantBlock,
      Catalog::Icon_StampExcludeBlock }, //   FT_Gutter_Pair,
    { Catalog::Icon_StampUnknownSouvenirSheet, Catalog::Icon_StampMissingSouvenirSheet,
      Catalog::Icon_StampOrderedSouvenirSheet, Catalog::Icon_StampOwnSouvenirSheet,
      Catalog::Icon_StampOwnVariantSouvenirSheet,
      Catalog::Icon_StampExcludeSouvenirSheet }, //    FT_Stamp_with_Attached_Label,
    { Catalog::Icon_StampUnknownBlock, Catalog::Icon_StampMissingBlock, Catalog::Icon_StampOrderedBlock,
      Catalog::Icon_StampOwnBlock, Catalog::Icon_StampOwnVariantBlock,
      Catalog::Icon_StampExcludeBlock } }; //   FT_Tete_Beche,
};

wxImageList* CreateAlbumImageList( )
{
    wxImageList* images;
    wxBusyCursor wait;

    wxIcon icons[ 9 ];

    icons[ Design::Icon_StampSelected ] = wxIcon( StampRed );
    icons[ Design::Icon_Stamp ] = wxIcon( StampBlue );
    icons[ Design::Icon_StampBlockSelected ] = wxIcon( StampRedBlock );
    icons[ Design::Icon_StampBlock ] = wxIcon( StampBlueBlock );
    icons[ Design::Icon_StampMiniSheetSelected ] = wxIcon( MiniSheetRed );
    icons[ Design::Icon_StampMiniSheet ] = wxIcon( MiniSheetBlue );
    icons[ Design::Icon_StampSouvenirSheetSelected ] = wxIcon( SouvenirSheetRed );
    icons[ Design::Icon_StampSouvenirSheet ] = wxIcon( SouvenirSheetBlue );
    icons[ Design::Icon_Folder ] = wxIcon( folder_xpm );

    int width = icons[ 0 ].GetWidth( ), height = icons[ 0 ].GetHeight( );

    // Make an state image list containing small icons
    images = new wxImageList( width, height, true );

    for ( size_t i = 0; i < WXSIZEOF( icons ); i++ )
    {
        images->Add( icons[ i ] );
    }
return images;
}

wxImageList* CreateAlbumStateImageList( bool del )
{
    wxImageList* states;
    wxBusyCursor wait;

    wxIcon icons[ 2 ];
    icons[ 0 ] = wxIcon( unchecked_xpm );
    icons[ 1 ] = wxIcon( checked_xpm );

    int width = icons[ 0 ].GetWidth( );
    int height = icons[ 0 ].GetHeight( );

    // Make an state image list containing small icons
    states = new wxImageList( width, height, true );

    for ( size_t i = 0; i < WXSIZEOF( icons ); i++ )
        states->Add( icons[ i ] );

    return states;
}

wxImageList* CreateCatalogImageList( )
{
    wxImageList* images;
    wxBusyCursor wait;
    const int nbrIcons = 25;
    wxIcon icons[ nbrIcons ];

    icons[ Catalog::Icon_StampUnknown ] = wxIcon( StampBrown );
    icons[ Catalog::Icon_StampMissing ] = wxIcon( StampRed );
    icons[ Catalog::Icon_StampOrdered ] = wxIcon( StampBlue );
    icons[ Catalog::Icon_StampOwn ] = wxIcon( StampGreen );
    icons[ Catalog::Icon_StampOwnVariant ] = wxIcon( StampYellow );
    icons[ Catalog::Icon_StampExclude ] = wxIcon( StampBlack );
    icons[ Catalog::Icon_StampUnknownBlock ] = wxIcon( StampBrownBlock );
    icons[ Catalog::Icon_StampMissingBlock ] = wxIcon( StampRedBlock );
    icons[ Catalog::Icon_StampOrderedBlock ] = wxIcon( StampBlueBlock );
    icons[ Catalog::Icon_StampOwnBlock ] = wxIcon( StampGreenBlock );
    icons[ Catalog::Icon_StampOwnVariantBlock ] = wxIcon( StampYellowBlock );
    icons[ Catalog::Icon_StampExcludeBlock ] = wxIcon( StampBlackBlock );
    icons[ Catalog::Icon_StampUnknownMiniSheet ] = wxIcon( MiniSheetBrown );
    icons[ Catalog::Icon_StampMissingMiniSheet ] = wxIcon( MiniSheetRed );
    icons[ Catalog::Icon_StampOrderedMiniSheet ] = wxIcon( MiniSheetBlue );
    icons[ Catalog::Icon_StampOwnMiniSheet ] = wxIcon( MiniSheetGreen );
    icons[ Catalog::Icon_StampOwnVariantMiniSheet ] = wxIcon( MiniSheetYellow );
    icons[ Catalog::Icon_StampExcludeMiniSheet ] = wxIcon( MiniSheetBlack );
    icons[ Catalog::Icon_StampUnknownSouvenirSheet ] = wxIcon( SouvenirSheetBrown );
    icons[ Catalog::Icon_StampMissingSouvenirSheet ] = wxIcon( SouvenirSheetRed );
    icons[ Catalog::Icon_StampOrderedSouvenirSheet ] = wxIcon( SouvenirSheetBlue );
    icons[ Catalog::Icon_StampOwnSouvenirSheet ] = wxIcon( SouvenirSheetGreen );
    icons[ Catalog::Icon_StampOwnVariantSouvenirSheet ] = wxIcon( SouvenirSheetYellow );
    icons[ Catalog::Icon_StampExcludeSouvenirSheet ] = wxIcon( SouvenirSheetBlack );
    icons[ Catalog::Icon_Folder ] = wxIcon( folder_xpm );

    int width = icons[ 0 ].GetWidth( ), height = icons[ 0 ].GetHeight( );

    // Make an state image list containing small icons
    images = new wxImageList( width, height, true );

    for ( size_t i = 0; i < nbrIcons; i++ )
    {
        images->Add( icons[ i ] );
    }

    return images ;
}

wxImageList* CreateCatalogStateImageList(bool del)
{
    wxImageList *states;
    wxBusyCursor wait;

        wxIcon icons[2];
        icons[0] = wxIcon(unchecked_xpm);
        icons[1] = wxIcon(checked_xpm);

        int width  = icons[0].GetWidth();
        int height = icons[0].GetHeight();

        // Make an state image list containing small icons
        states = new wxImageList(width, height, true);

        for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
            states->Add(icons[i]);
    

    return states;
}
