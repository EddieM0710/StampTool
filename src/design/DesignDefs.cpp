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

#include <iostream>

#include "DesignDefs.h"
#include "AlbumVolume.h"
#include "Defs.h"
#include "utils/Project.h"
#include "design/Album.h"
#include "utils/FontList.h"
#include "design/Page.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "design/AlbumData.h"
#include "gui/AlbumTreeCtrl.h"
 //#include "gui/AppData.h"

  // namespace for all Album design 
namespace Design {



    wxString AttrNameStrings[ AT_NbrAttrTypes ] = {
            "Name",
            "PageWidth",
            "PageHeight",
            "TopMargin",
            "BottomMargin",
            "RightMargin",
            "LeftMargin",
            "BorderFileName",
            "BorderSize",
            "Height",
            "Width",
            "XPos",
            "YPos",
            "MinHeight",
            "MinWidth",
            "CatNbr",
            "Link",
            "ShowTitle",
            "ShowCatNbr",
            "ShowFrame",
            "ShowImage",
            "Orientation",
            "GrayScaleImages",
            "TopContentPadding",
            "BottomContentPadding",
            "LeftContentPadding",
            "RightContentPadding",
            "FontType",
            "NativeFontString",
            "Color",
            "ImageName",
            "CalculateSpacing",
            "FixedSpacingSize",
            "OversizePaper",
            "PaperHeight",
            "PaperWidth",
            "SelvageHeight",
        "SelvageWidth",
        "MountAllowanceHeight",
        "MountAllowanceWidth"
    };
    wxString OrientationStrings[ 2 ] = { "Portrait", "Landscape" };

    bool IsPortrait( wxString orientation )
    {
        return !orientation.Cmp( OrientationStrings[ AT_Portrait ] );
    };

    wxString AlbumBaseNames[ AT_NbrAlbumTypes ] = {
            "Album",
            "Page",
            "Row",
            "Col",
            "TextBox",
            "Title",
            "TitlePage",
            "Stamp",
            "Font" };


    int DefaultPointSize[ AT_NbrFontUsageTypes ] = { 6, 10, 14, 8, 10 };

    wxString FontUsageTypeStrings[ AT_NbrFontUsageTypes ] = {
        "Unspecified",
        "Text",
        "Title",
        "CatNbr",
        "Name"
    };


    AlbumAttrType FindAlbumAttrType( wxString name )
    {
        wxString attrName;
        for ( int i = 0; i < AT_NbrAttrTypes; i++ )
        {
            attrName = AlbumBaseNames[ i ];
            if ( !name.Cmp( attrName ) )
            {
                return ( AlbumAttrType ) i;
            }
        }
        return ( AlbumAttrType ) -1;
    };

    AlbumBaseType FindAlbumBaseType( wxString name )
    {
        wxString baseName;
        for ( int i = 0; i < AT_NbrAlbumTypes; i++ )
        {
            baseName = AlbumBaseNames[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( AlbumBaseType ) i;
            }
        }
        return ( AlbumBaseType ) -1;
    };

    FontUsageType FindFontUsageType( wxString name )
    {
        wxString usageStr;
        for ( int i = 0; i < AT_NbrFontUsageTypes; i++ )
        {
            usageStr = FontUsageTypeStrings[ i ];
            if ( !name.Cmp( usageStr ) )
            {
                return ( FontUsageType ) i;
            }
        }
        return ( FontUsageType ) -1;
    };
    Album* GetAlbum( void )
    {
        AlbumVolume* albumVolume = GetAlbumVolume( );
        if ( albumVolume )
        {
            return albumVolume->GetAlbum( );
        }
        return ( Album* ) 0;
    }


    AlbumVolume* GetAlbumVolume( void )
    {
        AlbumData* albumData = GetAlbumData( );
        if ( albumData )
        {
            return albumData->GetAlbumVolume( );
        }
        return ( AlbumVolume* ) 0;
    };



    LayoutBase* GetSelectedNodePage( )
    {
        AlbumVolume* albumVolume = Design::GetAlbumVolume( );
        if ( albumVolume )
        {
            AlbumTreeCtrl* treeCtrl = GetAlbumTreeCtrl( );
            if ( treeCtrl )
            {
                wxTreeItemId id = treeCtrl->GetSelection( );
                if ( id.IsOk( ) )
                {
                    DesignTreeItemData* data = ( DesignTreeItemData* ) treeCtrl->GetItemData( id );
                    while ( id.IsOk( ) && data )
                    {
                        Design::AlbumBaseType type = data->GetType( );
                        if ( type == Design::AT_Album )
                        {
                            wxTreeItemIdValue cookie;
                            wxTreeItemId childID = treeCtrl->GetFirstChild( id, cookie );
                            if ( childID.IsOk( ) )
                            {
                                Design::AlbumBaseType childType = treeCtrl->GetItemType( childID );
                                data = ( DesignTreeItemData* ) treeCtrl->GetItemData( childID );
                                return ( LayoutBase* ) data->GetNodeElement( );
                            }
                        }
                        else if ( type == AT_Page )
                        {
                            return ( LayoutBase* ) data->GetNodeElement( );
                        }
                        id = treeCtrl->GetItemParent( id );
                        if ( id.IsOk( ) )
                        {
                            data = ( DesignTreeItemData* ) treeCtrl->GetItemData( id );
                        }
                    }
                }
            }
        }
        return ( LayoutBase* ) 0;
    }

    void InitDesignDefs( ScaleClient client )
    {

    }

    bool IsAlbumBaseTypeValid( AlbumBaseType type )
    {
        return ( type >= AT_Album && type < AT_NbrAlbumTypes );
    };

    AlbumBase* MakeNode( wxXmlNode* node )
    {


        wxString nodeName = node->GetName( );
        AlbumBaseType type = FindAlbumBaseType( nodeName );

        AlbumBase* object = ( AlbumBase* ) 0;

        if ( type == AT_Album )
        {
            object = ( AlbumBase* )new Album( node );
        }
        if ( type == AT_Page )
        {
            object = ( AlbumBase* )new Page( node );
        }
        // else if ( type == AT_Title )
        // { 
        //     object = ( AlbumBase* )new Title( node );
        // }
        else if ( type == AT_Col )
        {
            object = ( AlbumBase* )new Column( node );
        }
        else if ( type == AT_Row )
        {
            object = ( AlbumBase* )new Row( node );
        }
        else if ( type == AT_Stamp )
        {
            object = ( AlbumBase* )new Stamp( node );
        }
        return object;
    }
}