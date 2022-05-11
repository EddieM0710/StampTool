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

#include "AlbumDefs.h"
#include "AlbumData.h"
#include "Defs.h"
#include "utils/Project.h"
#include "album/Album.h"
#include "album/TitlePage.h"
#include "album/Title.h"
#include "album/Page.h"
#include "album/Row.h"
#include "album/Column.h"
#include "album/Stamp.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/GeneratorData.h"

namespace Layout {

    AlbumData* NewAlbumData( void )
    {
        return new AlbumData();
    }

    Album* GetAlbum( void )
    {
        AlbumData* albumData = GetAlbumData(  )  ;
        if ( albumData )
        {
            return albumData->GetAlbum();
        }
        return (Album*)0;
    }


    AlbumData* GetAlbumData( void )
    {
        GeneratorData* project = GetGeneratorData( );
        if ( project )
        {
            return project->GetAlbumData( );
        }
        return ( AlbumData* )0;
    };

    AlbumData* SetAlbumData( AlbumData* albumData )
    {
        GeneratorData* project = GetGeneratorData( );
        if ( project )
        {
            project->SetAlbumData( albumData );
        }
    };


        wxString AlbumNodeNames[AT_NbrAlbumTypes] = {
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

    void InitAlbumDefs( )
    {

    }

    AlbumNodeType FindAlbumNodeType( wxString name )
    {
        wxString baseName;
        for ( int i = 0; i < AT_NbrAlbumTypes; i++ )
        {
            baseName = AlbumNodeNames[i];
            if ( !name.Cmp( baseName ) )
            {
                return ( AlbumNodeType )i;
            }
        }
        return ( AlbumNodeType )-1;
    };


    // wxString GetAttribute( AlbumNodeType type )
    // {
    //     return Utils::GetAttrStr( GetNodeElement( ), AttrNameStrings[type]);
    // }

    // double GetAttributeDbl( AlbumNodeType type )
    // {
    //     return Utils::GetAttrDbl( GetNodeElement( ), AttrNameStrings[type] );
    // }
    //   void SetAttrStr( AlbumNodeType type, wxString val )
    //     {
    //         Utils::SetAttrStr( GetNodeElement( ), AttrNameStrings[type], val );
    //     };
    //   void SetAttrDbl( AlbumNodeType type, double val )
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
    LayoutNode* GetSelectedNodePage( )
    {
        AlbumData* albumData = Layout::GetAlbumData( );
        if ( albumData )
        {
            AlbumTreeCtrl* treeCtrl = GetAlbumTreeCtrl( );
            if ( treeCtrl )
            {
                Layout::LayoutNode* node = treeCtrl->GetSelectedNode( );
                if ( node )
                {
                    for ( AlbumNodeList::iterator it = node->BeginAlbumNodeList(); it != node->EndAlbumNodeList(); ++it )
                    {
                        LayoutNode* child = ( LayoutNode* )( *it );
                        if ( child->GetNodeType() == AT_Page )
                        {
                            return child;
                        }
                    }
                }
            }
        }
        return (LayoutNode*)0;
    }


    // LayoutNode* MakeNode( AlbumNodeType type, wxXmlNode* node )
    // {
    //     LayoutNode* object = (LayoutNode*)0;
    //     if ( type == AT_TitlePage )
    //     {
    //         object = (LayoutNode*)new TitlePage( node);
    //     }
    //     else if ( type == AT_Page )
    //     {
    //         object = (LayoutNode*)new Page( node );
    //     }
    //     else if ( type == AT_Title )
    //     {
    //         object = (LayoutNode*)new Title( node );
    //     }
    //     else if ( type == AT_Col )
    //     {
    //         object = (LayoutNode*)new Column( node );
    //     }
    //     else if ( type == AT_Row )
    //     {
    //         object = (LayoutNode*)new Row( node );
    //     }
    //     else if ( type == AT_Stamp )
    //     {
    //         object = (LayoutNode*)new Stamp( node );
    //     }
    //     return object;
    // }
}