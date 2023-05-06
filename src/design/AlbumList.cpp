/**
 * @file AlbumList.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/filename.h>


#include "design/AlbumList.h"
#include "design/AlbumData.h"
#include "gui/AlbumPanel.h"
 //#include "gui/AppData.h"
#include "gui/StampToolFrame.h"

#include "Defs.h"

//#include "StampToolApp.h"

///wxDECLARE_APP( StampToolApp );

namespace Design {

    bool AlbumList::ClearAlbumVolumeArray( )
    {
        while ( !m_albumVolumeArray.empty( ) )
        {
            AlbumVolume* albumVolume = m_albumVolumeArray.back( );
            if ( albumVolume->IsOK( ) ) delete albumVolume;
            m_albumVolumeArray.pop_back( );
        }
        return true;
    }

    Design::AlbumVolume* AlbumList::GetAlbumVolume( )
    {
        if ( m_albumVolumeNdx >= 0 )
        {
            if ( !m_albumVolumeArray.empty( ) )
            {
                return m_albumVolumeArray.at( m_albumVolumeNdx );
            }
        }
        return ( Design::AlbumVolume* ) 0;
    };

    void AlbumList::LoadAlbums( )
    {
        for ( Design::AlbumVolumeArray::iterator it = std::begin( m_albumVolumeArray );
            it != std::end( m_albumVolumeArray );
            ++it )
        {
            Design::AlbumVolume* albumVolume = ( Design::AlbumVolume* ) ( *it );
            albumVolume->LoadXML( );
            wxString name = albumVolume->GetAlbumName( );
            if ( !name.IsEmpty( ) )
            {
                name = albumVolume->GetAlbumFilename( );
                wxFileName fn( name );
                albumVolume->SetAlbumName( fn.GetName( ) );
            }
        }

        if ( m_albumVolumeArray.size( ) > 1 )
        {
            sort( m_albumVolumeArray.begin( ), m_albumVolumeArray.end( ), WayToSort );
        }
        m_albumNameStrings.Clear( );
        for ( Design::AlbumVolumeArray::iterator it = std::begin( m_albumVolumeArray );
            it != std::end( m_albumVolumeArray );
            ++it )
        {
            Design::AlbumVolume* album = ( Design::AlbumVolume* ) ( *it );
            m_albumNameStrings.Add( album->GetAlbumName( ) );
        }
        AlbumPanel* albPanel = GetFrame( )->GetAlbumAlbumPanel( );
        albPanel->SetAlbumListStrings( m_albumNameStrings );
        m_albumVolumeNdx = 0;
        albPanel->SetAlbumListSelection( m_albumVolumeNdx );

    };

    Design::AlbumVolume* AlbumList::NewAlbumVolume( )
    {
        Design::AlbumVolume* albumVolume = Design::NewAlbumVolumeInstance( );
        m_albumVolumeArray.push_back( albumVolume );
        m_albumVolumeNdx = m_albumVolumeArray.size( ) - 1;
        return albumVolume;
    }

    void AlbumList::SaveAlbums( )
    {
        for ( Design::AlbumVolumeArray::iterator it = std::begin( m_albumVolumeArray );
            it != std::end( m_albumVolumeArray );
            ++it )
        {
            Design::AlbumVolume* album = ( Design::AlbumVolume* ) ( *it );
            album->SaveXML( );
        }
    };

    void AlbumList::SetAlbumVolumeNdx( int i )
    {
        m_albumVolumeNdx = i;
        GetAlbumData( )->LoadDesignTree( );
    };

    int WayToSort( Design::AlbumVolume* sect1, Design::AlbumVolume* sect2 )
    {
        wxString name1 = sect1->GetAlbumName( );
        wxString name2 = sect2->GetAlbumName( );
        return name1.compare( name2 );
    }
}