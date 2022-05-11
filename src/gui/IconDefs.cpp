/**
 * @file IconDefs.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
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



IconID AlbumImageSelection[ Layout::AT_NbrAlbumTypes ][ 2 ] = {
    { Icon_Stamp, Icon_StampSelected }, //   FT_FormatUnknown = 0,
    { Icon_Stamp, Icon_StampSelected }, //   FT_Stamp,
    { Icon_StampBlock, Icon_StampBlockSelected }, //   FT_Se_tenant,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Mini_Sheet,
    { Icon_StampSouvenirSheet, Icon_StampSouvenirSheetSelected }, //   FT_Souvenir_Sheet,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Booklet,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected } }; //   FT_Tete_Beche,

IconID CatalogImageSelection[ Catalog::FT_NbrTypes ][ 2 ] = {
    { Icon_Stamp, Icon_StampSelected }, //   FT_FormatUnknown = 0,
    { Icon_Stamp, Icon_StampSelected }, //   FT_Stamp,
    { Icon_StampBlock, Icon_StampBlockSelected }, //   FT_Se_tenant,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Mini_Sheet,
    { Icon_StampSouvenirSheet, Icon_StampSouvenirSheetSelected }, //   FT_Souvenir_Sheet,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Booklet,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Booklet_Pane,
    { Icon_StampBlock, Icon_StampBlockSelected }, //   FT_Gutter_Pair,
    { Icon_StampSouvenirSheet, Icon_StampSouvenirSheetSelected }, //    FT_Stamp_with_Attached_Label,
    { Icon_StampBlock, Icon_StampBlockSelected } }; //   FT_Tete_Beche,


wxImageList* CreateAlbumImageList( )
{
    wxImageList* images;
    wxBusyCursor wait;

    wxIcon icons[ 9 ];

    icons[ Icon_StampSelected ] = wxIcon( StampRed );
    icons[ Icon_Stamp ] = wxIcon( StampBlue );
    icons[ Icon_StampBlockSelected ] = wxIcon( StampRedBlock );
    icons[ Icon_StampBlock ] = wxIcon( StampBlueBlock );
    icons[ Icon_StampMiniSheetSelected ] = wxIcon( MiniSheetRed );
    icons[ Icon_StampMiniSheet ] = wxIcon( MiniSheetBlue );
    icons[ Icon_StampSouvenirSheetSelected ] = wxIcon( SouvenirSheetRed );
    icons[ Icon_StampSouvenirSheet ] = wxIcon( SouvenirSheetBlue );
    icons[ Icon_Folder ] = wxIcon( folder_xpm );

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
    const int nbrIcons = 9;
    wxIcon icons[ nbrIcons ];

    icons[ Icon_StampSelected ] = wxIcon( StampRed );
    icons[ Icon_Stamp ] = wxIcon( StampBlue );
    icons[ Icon_StampBlockSelected ] = wxIcon( StampRedBlock );
    icons[ Icon_StampBlock ] = wxIcon( StampBlueBlock );
    icons[ Icon_StampMiniSheetSelected ] = wxIcon( MiniSheetRed );
    icons[ Icon_StampMiniSheet ] = wxIcon( MiniSheetBlue );
    icons[ Icon_StampSouvenirSheetSelected ] = wxIcon( SouvenirSheetRed );
    icons[ Icon_StampSouvenirSheet ] = wxIcon( SouvenirSheetBlue );
    icons[ Icon_Folder ] = wxIcon( folder_xpm );

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
