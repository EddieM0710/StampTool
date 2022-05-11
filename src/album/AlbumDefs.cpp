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


namespace Layout {

    AlbumData* GetAlbumData( void )
    {
        Utils::Project* project = GetProject( );
        if ( project )
        {
            return project->GetAlbumData( );
        }
        return ( AlbumData* )0;
    };

    AlbumData* SetAlbumData( AlbumData* albumData )
    {
        Utils::Project* project = GetProject( );
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


    void UpdateSizes( wxXmlNode* child )
    {
        wxString name = child->GetName( );
        if ( name.Cmp( "Page" ) )
        {
            Page node( child );
            node.UpdateSizes( );
        }
        else if ( name.Cmp( "Column" ) )
        {
            Column node( child );
            node.UpdateSizes( );
        }
        else if ( name.Cmp( "Row" ) )
        {
            Row node( child );
            node.UpdateSizes( );
        }
        else if ( name.Cmp( "Title" ) )
        {
            Title node( child );
            node.UpdateSizes( );
        }
        else if ( name.Cmp( "TitlePage" ) )
        {
            TitlePage node( child );
            node.UpdateSizes( );
        }

    }
}