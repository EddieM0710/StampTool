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
 **************************************************/


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

 // #include <iostream>
#include <wx/filename.h>
// #include <wx/string.h>
// #include "wx/xml/xml.h"
// #include <wx/msgdlg.h>

#include "design/AlbumList.h"
#include "gui/AlbumDesignPanel.h"


#include "Defs.h"

// #include "catalog/CatalogDefs.h"
// #include "catalog/Entry.h"

// #include "utils/CSV.h"
// #include "utils/Settings.h"
// #include "utils/Project.h"
// #include "utils/XMLUtilities.h"
#include "StampToolApp.h"
#include "gui/ToolData.h"

wxDECLARE_APP( StampToolApp );

namespace Design {

    Design::AlbumVolume* AlbumList::NewAlbumVolume( )
    {
        Design::AlbumVolume* albumVolume = Design::NewAlbumVolumeInstance( );
        m_albumVolumeArray.push_back( albumVolume );
        m_albumVolumeNdx = m_albumVolumeArray.size( ) - 1;
        return albumVolume;
    }
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

    int wayToSort( Design::AlbumVolume* sect1, Design::AlbumVolume* sect2 )
    {
        wxString name1 = sect1->GetAlbumName( );
        wxString name2 = sect2->GetAlbumName( );
        return name1.compare( name2 );
    }

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
            sort( m_albumVolumeArray.begin( ), m_albumVolumeArray.end( ), wayToSort );
        }
        m_albumNameStrings.Clear( );
        for ( Design::AlbumVolumeArray::iterator it = std::begin( m_albumVolumeArray );
            it != std::end( m_albumVolumeArray );
            ++it )
        {
            Design::AlbumVolume* album = ( Design::AlbumVolume* ) ( *it );
            m_albumNameStrings.Add( album->GetAlbumName( ) );
        }
        AlbumDesignPanel* albPanel = wxGetApp( ).GetFrame( )->GetAlbumDesignPanel( );
        albPanel->SetAlbumListStrings( m_albumNameStrings );
        m_albumVolumeNdx = 0;
        albPanel->SetAlbumListSelection( m_albumVolumeNdx );

    };

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

    void AlbumList::SetAlbumVolumeNdx( int i ) {
        m_albumVolumeNdx = i;
        GetAlbumData( )->LoadDesignTree( );
    };
}