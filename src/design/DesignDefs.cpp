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
#include "DesignData.h"
#include "Defs.h"
#include "utils/Project.h"
#include "design/Album.h"
#include "utils/FontList.h"
#include "design/TitlePage.h"
 //#include "design/Title.h"
#include "design/Page.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/ToolData.h"

 // namespace for all Album design 
namespace Design {

    wxRealPoint  ScaleFactor;

    bool IsAlbumBaseTypeValid( AlbumBaseType type )
    {
        return ( type >= AT_Album && type < AT_NbrAlbumTypes );
    };

    Album* GetAlbum( void )
    {
        DesignData* designData = GetDesignData( );
        if ( designData )
        {
            return designData->GetAlbum( );
        }
        return ( Album* ) 0;
    }

    // FontList* GetFontList( void )
             // { 
    //     DesignData* designData = GetDesignData( );
        //     if ( designData )
    //     { 
    //         return designData->GetFontList( );
    //     }
    //     return ( FontList* )0;
    // }


    DesignData* GetDesignData( void )
    {
        ToolData* project = GetToolData( );
        if ( project )
        {
            return project->GetDesignData( );
        }
        return ( DesignData* ) 0;
    };

    // DesignData* SetDesignData( DesignData* designData )
    // { 
    //     ToolData* project = GetToolData( );
    //     if ( project )
    //     { 
    //         project->SetDesignData( designData );
    //     }
    // };


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
            "FixedSpacingSize"
    };

    void InitDesignDefs( ScaleClient client )
    {

        if ( client == DD_PDF )
        {
            ScaleFactor.x = 1.0;
            ScaleFactor.y = 1.0;
        }
        else //if ( client == DD_Display)
        {
            wxSize ppi = wxGetDisplayPPI( );
            ScaleFactor.x = ppi.x / 25.4;
            ScaleFactor.y = ppi.y / 25.4;
        }
    }

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

    AT_FontUsageType FindFontUsageType( wxString name )
    {
        wxString usageStr;
        for ( int i = 0; i < AT_NbrFontUsageTypes; i++ )
        {
            usageStr = AT_FontUsageTypeStrings[ i ];
            if ( !name.Cmp( usageStr ) )
            {
                return ( AT_FontUsageType ) i;
            }
        }
        return ( AT_FontUsageType ) -1;
    };

    LayoutBase* GetSelectedNodePage( )
    {
        DesignData* designData = Design::GetDesignData( );
        if ( designData )
        {
            DesignTreeCtrl* treeCtrl = GetDesignTreeCtrl( );
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
    wxString AT_FontUsageTypeStrings[ AT_NbrFontUsageTypes ] = {
        "Unspecified",
        "Text",
        "Title",
        "CatNbr",
        "Name"
    };

    int AT_DefaultPointSize[ AT_NbrFontUsageTypes ] = { 6, 10, 14, 8, 10 };

    wxFontFamily AT_FontFamilyMap[ AT_NbrFontFamilies ] =
    {
        wxFONTFAMILY_DEFAULT,
        wxFONTFAMILY_DECORATIVE,
        wxFONTFAMILY_ROMAN,
        wxFONTFAMILY_SCRIPT,
        wxFONTFAMILY_SWISS,
        wxFONTFAMILY_MODERN,
        wxFONTFAMILY_TELETYPE
    };


    wxString AT_FontFamilyStrings[ AT_NbrFontFamilies ] =
    {
        "Decorative",
        "Roman",
        "Script",
        "Swiss",
        "Modern",
        "Teletype"
    };
    bool IsOK( AT_FontFamilyType type )
    {
        return ( ( type >= AT_Default ) && ( type < AT_NbrFontFamilies ) );
    }

    AT_FontFamilyType GetATFamily( wxFontFamily wxVal )
    {
        for ( int i = 0; i < AT_NbrFontFamilies; i++ )
        {
            if ( AT_FontFamilyMap[ i ] == wxVal )
            {
                return ( AT_FontFamilyType ) i;
            }
        }
        return ( AT_FontFamilyType ) UnknownFontVal;
    };

    AT_FontFamilyType GetFamilyFromStr( wxString family )
    {
        for ( int i = 0; i < AT_NbrFontFamilies; i++ )
        {
            if ( !AT_FontFamilyStrings[ i ].compare( family ) )
            {
                return ( AT_FontFamilyType ) i;
            }
        }
        return ( AT_FontFamilyType ) UnknownFontVal;
    }

    wxFontStyle AT_FontStyleMap[ AT_NbrFontStyles ] =
    {
        wxFONTSTYLE_NORMAL,
        wxFONTSTYLE_ITALIC,
        wxFONTSTYLE_SLANT,
        wxFONTSTYLE_MAX
    };

    wxString AT_FontStyleStrings[ AT_NbrFontStyles ] =
    {
        "Normal",
        "Italic",
        "Slant",
        "Max",
    };

    AT_FontStyleType GetATStyle( wxFontStyle wxVal )
    {
        for ( int i = 0; i < AT_NbrFontStyles; i++ )
        {
            if ( AT_FontStyleMap[ i ] == wxVal )
            {
                return ( AT_FontStyleType ) i;
            }
        }
        return ( AT_FontStyleType ) UnknownFontVal;
    };

    bool IsOK( AT_FontStyleType type )
    {
        return ( ( type >= AT_Normal ) && ( type < AT_NbrFontStyles ) );
    }

    wxFontWeight AT_FontWeightMap[ AT_NbrFontWeights ] =
    {
        wxFONTWEIGHT_INVALID,
        wxFONTWEIGHT_THIN,
        wxFONTWEIGHT_EXTRALIGHT,
        wxFONTWEIGHT_LIGHT,
        wxFONTWEIGHT_NORMAL,
        wxFONTWEIGHT_MEDIUM,
        wxFONTWEIGHT_SEMIBOLD,
        wxFONTWEIGHT_BOLD,
        wxFONTWEIGHT_EXTRABOLD,
        wxFONTWEIGHT_HEAVY,
        wxFONTWEIGHT_EXTRAHEAVY
    };


    wxString AT_FontWeightStrings[ AT_NbrFontWeights ] =
    {
        "Invalid",
        "Thin",
        "ExtraLight",
        "Light",
        "Normal",
        "Medium",
        "SemiBold",
        "Bold",
        "ExtraBold",
        "Heavy",
        "ExtraHeavy"
    };

    AT_FontWeightType GetATWeight( wxFontWeight wxVal )
    {
        for ( int i = 0; i < AT_NbrFontWeights; i++ )
        {
            if ( AT_FontWeightMap[ i ] == wxVal )
            {
                return ( AT_FontWeightType ) i;
            }
        }
        return ( AT_FontWeightType ) UnknownFontVal;
    };

    bool IsOK( AT_FontWeightType type )
    {
        return ( ( type >= AT_ThinWeight ) && ( type < AT_NbrFontWeights ) );
    }
}