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

#include "AlbumData.h"
#include "AlbumDefs.h"
#include "Defs.h"
#include "utils/Project.h"

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


    wxArrayString AlbumNodeNames;


    void InitAlbumDefs( )
    {
        AlbumNodeNames.Add( "Album" );
        AlbumNodeNames.Add( "Page" );
        AlbumNodeNames.Add( "Row" );
        AlbumNodeNames.Add( "Col" );
        AlbumNodeNames.Add( "Title" );
        AlbumNodeNames.Add( "Stamp" );
        AlbumNodeNames.Add( "NbrAlbumTypes" );
    }

    AlbumNodeType FindAlbumNodeType( wxString name )
    {
        wxString baseName;

        int cnt = AlbumNodeNames.GetCount( );
        for ( int i = 0; i < cnt; i++ )
        {
            baseName = AlbumNodeNames.Item( i );
            if ( !name.Cmp( baseName ) )
            {
                return ( AlbumNodeType )i;
            }
        }
        return ( AlbumNodeType )-1;
    };
}