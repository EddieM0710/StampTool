/**
 * @file Defs.cpp
 * @author Eddie Monroe (you@domain.com)
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
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

namespace Design {


    Album* GetAlbum( void )
    {
        DesignData* designData = GetDesignData(  )  ;
        if ( designData )
        {
            return designData->GetAlbum();
        }
        return (Album*)0;
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


        wxString AlbumBaseNames[AT_NbrAlbumTypes] = {
                "Album",
                "Page",
                "Row",
                "Col",
                "Title",
                "TitlePage",
                "Stamp"  };
    
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
                "ID",
                "Link" };

    void InitDesignDefs( )
    {

    }

    AlbumBaseType FindAlbumBaseType( wxString name )
    {
        wxString baseName;
        for ( int i = 0; i < AT_NbrAlbumTypes; i++ )
        {
            baseName = AlbumBaseNames[i];
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
                Design::LayoutBase* node = treeCtrl->GetSelectedNode( );
                if ( node )
                {
                    for ( AlbumBaseList::iterator it = node->BeginAlbumBaseList(); it != node->EndAlbumBaseList(); ++it )
                    {
                        LayoutBase* child = ( LayoutBase* )( *it );
                        if ( child->GetNodeType() == AT_Page )
                        {
                            return child;
                        }
                    }
                }
            }
        }
        return (LayoutBase*)0;
    }


    // LayoutBase* MakeNode( AlbumBaseType type, wxXmlNode* node )
    // {
    //     LayoutBase* object = (LayoutBase*)0;
    //     if ( type == AT_TitlePage )
    //     {
    //         object = (LayoutBase*)new TitlePage( node);
    //     }
    //     else if ( type == AT_Page )
    //     {
    //         object = (LayoutBase*)new Page( node );
    //     }
    //     else if ( type == AT_Title )
    //     {
    //         object = (LayoutBase*)new Title( node );
    //     }
    //     else if ( type == AT_Col )
    //     {
    //         object = (LayoutBase*)new Column( node );
    //     }
    //     else if ( type == AT_Row )
    //     {
    //         object = (LayoutBase*)new Row( node );
    //     }
    //     else if ( type == AT_Stamp )
    //     {
    //         object = (LayoutBase*)new Stamp( node );
    //     }
    //     return object;
    // }
}