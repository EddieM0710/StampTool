/**
 * @file Defs.cpp
 * @author Eddie Monroe (you@domain.com)
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
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
 */

 // For compilers that support precompilation, includes "wx/wx.h".
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

#include "DesignDefs.h"
#include "DesignData.h"
#include "Defs.h"
#include "utils/Project.h"
#include "design/Album.h"
#include "design/TitlePage.h"
#include "design/Title.h"
#include "design/Page.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/GeneratorData.h"

// namespace for all Album design 
namespace Design {

    wxRealPoint  PpMM;    
    
    bool IsAlbumBaseTypeValid( AlbumBaseType type ) 
    { 
        return (type>=AT_Album && type < AT_NbrAlbumTypes );
    };

    Album* GetAlbum( void )
    {
        DesignData* designData = GetDesignData( );
        if ( designData )
        {
            return designData->GetAlbum( );
        }
        return ( Album* )0;
    }


    DesignData* GetDesignData( void )
    {
        GeneratorData* project = GetGeneratorData( );
        if ( project )
        {
            return project->GetDesignData( );
        }
        return ( DesignData* )0;
    };

    // DesignData* SetDesignData( DesignData* designData )
    // {
    //     GeneratorData* project = GetGeneratorData( );
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
            "Title",
            "TitlePage",
            "Stamp" };

    const char* AttrFontStrings [ FT_NbrAttrTypes ] = {
        "Name",
        "Family",
        "Size",
        "Weight",
        "Color",
        "Style"};
   

    const char* AttrNameStrings[ AT_NbrAttrTypes ] = {
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
            "TopContentPadding",
            "BottomContentPadding",
            "LeftContentPadding",
            "RightContentPadding"};

    void InitDesignDefs( )
    {
        wxSize ppi = wxGetDisplayPPI( );
        PpMM.x = ppi.x / 25.4;
        PpMM.y = ppi.y / 25.4;
    }

    AlbumBaseType FindAlbumBaseType( wxString name )
    {
        wxString baseName;
        for ( int i = 0; i < AT_NbrAlbumTypes; i++ )
        {
            baseName = AlbumBaseNames[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( AlbumBaseType )i;
            }
        }
        return ( AlbumBaseType )-1;
    };


    // wxString GetAttribute( AlbumBaseType type )
    // {
    //     return Utils::GetAttrStr( GetNodeElement( ), AttrNameStrings[type]);
    // }

    // double GetAttributeDbl( AlbumBaseType type )
    // {
    //     return Utils::GetAttrDbl( GetNodeElement( ), AttrNameStrings[type] );
    // }
    //   void SetAttrStr( AlbumBaseType type, wxString val )
    //     {
    //         Utils::SetAttrStr( GetNodeElement( ), AttrNameStrings[type], val );
    //     };
    //   void SetAttrDbl( AlbumBaseType type, double val )
    //     {
    //         Utils::SetAttrDbl( GetNodeElement( ), AttrNameStrings[type], val );
    //     };


    // void UpdateSizes( wxXmlNode* child )
    // {
    //     wxString name = child->GetName( );
    //     if ( name.Cmp( "Page" ) )
    //     {
    //         Page node( child );
    //         node.UpdateSizes( );
    //     }
    //     else if ( name.Cmp( "Column" ) )
    //     {
    //         Column node( child );
    //         node.UpdateSizes( );
    //     }
    //     else if ( name.Cmp( "Row" ) )
    //     {
    //         Row node( child );
    //         node.UpdateSizes( );
    //     }
    //     else if ( name.Cmp( "Title" ) )
    //     {
    //         Title node( child );
    //         node.UpdateSizes( );
    //     }
    //     else if ( name.Cmp( "TitlePage" ) )
    //     {
    //         TitlePage node( child );
    //         node.UpdateSizes( );
    //     }

    // }
    LayoutBase* GetSelectedNodePage( )
    {
        DesignData* designData = Design::GetDesignData( );
        if ( designData )
        {
            DesignTreeCtrl* treeCtrl = GetDesignTreeCtrl( );
            if ( treeCtrl )
            {
                wxTreeItemId id = treeCtrl->GetSelection();
                if ( id.IsOk() )
                {
                    DesignTreeItemData* data = (DesignTreeItemData*)treeCtrl->GetItemData(id);
                    while ( id.IsOk() && data )
                    {
                        Design::AlbumBaseType type = data->GetType();
                        if ( type == Design::AT_Album )
                        {
                            wxTreeItemIdValue cookie;
                            wxTreeItemId childID = treeCtrl->GetFirstChild( id, cookie);
                            if ( childID.IsOk() )
                            {
                                Design::AlbumBaseType childType = treeCtrl->GetItemType( childID );
                                data = (DesignTreeItemData*)treeCtrl->GetItemData(childID);
                                return (LayoutBase*) data->GetNodeElement();
                            }
                        }
                        else if ( type == AT_Page)
                        {
                            return (LayoutBase*) data->GetNodeElement();
                        }
                        id = treeCtrl->GetItemParent(id);
                        if ( id.IsOk() )
                        {
                            data = (DesignTreeItemData*)treeCtrl->GetItemData(id);
                        }
                    }
                }
            }
        }
        return ( LayoutBase* )0;
    }


    AlbumBase* MakeNode( wxXmlNode* node )
    {
        wxString nodeName = node->GetName();
        AlbumBaseType type = FindAlbumBaseType( nodeName );

        AlbumBase* object = (AlbumBase*)0;

        if ( type == AT_Album )
        {
            object = (AlbumBase*)new Album( node);
        }
        if ( type == AT_Page )
        {
            object = (AlbumBase*)new Page( node );
        }
        // else if ( type == AT_Title )
        // {
        //     object = (AlbumBase*)new Title( node );
        // }
        else if ( type == AT_Col )
        {
            object = (AlbumBase*)new Column( node );
        }
        else if ( type == AT_Row )
        {
            object = (AlbumBase*)new Row( node );
        }
        else if ( type == AT_Stamp )
        {
            object = (AlbumBase*)new Stamp( node );
        }
        return object;
    }
}