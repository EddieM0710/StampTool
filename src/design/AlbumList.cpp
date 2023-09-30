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
#include "gui/TOCTreeCtrl.h"

#include "Defs.h"

//#include "StampToolApp.h"

///wxDECLARE_APP( StampToolApp );

namespace Design {

    // void AlbumList::LoadAlbums( )
    // {
    //     for ( Design::AlbumVolumeArray::iterator it = std::begin( m_albumVolumeArray );
    //         it != std::end( m_albumVolumeArray );
    //         ++it )
    //     {
    //         Design::AlbumVolume* albumVolume = ( Design::AlbumVolume* ) ( *it );
    //         albumVolume->LoadXML( );
    //         wxString name = albumVolume->GetAlbumName( );
    //         if ( !name.IsEmpty( ) )
    //         {
    //             name = albumVolume->GetAlbumFilename( );
    //             wxFileName fn( name );
    //             albumVolume->SetAlbumName( fn.GetName( ) );
    //         }
    //     }

    //     if ( m_albumVolumeArray.size( ) > 1 )
    //     {
    //         sort( m_albumVolumeArray.begin( ), m_albumVolumeArray.end( ), WayToSort );
    //     }
    //     m_albumNameStrings.Clear( );
    //     for ( Design::AlbumVolumeArray::iterator it = std::begin( m_albumVolumeArray );
    //         it != std::end( m_albumVolumeArray );
    //         ++it )
    //     {
    //         Design::AlbumVolume* album = ( Design::AlbumVolume* ) ( *it );
    //         m_albumNameStrings.Add( album->GetAlbumName( ) );
    //     }
    //     AlbumPanel* albPanel = GetFrame( )->GetAlbumPanel( );
    //     //  albPanel->SetAlbumListStrings( m_albumNameStrings );
    //     m_currVolume = album;
    //     // albPanel->SetAlbumListSelection( m_albumVolumeNdx );

    // };

    Design::AlbumVolume* AlbumList::NewVolumeInstance( )
    {
        Design::AlbumVolume* albumVolume = Design::NewAlbumVolume( );
        return albumVolume;
    }


}