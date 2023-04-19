/**
 * @file AlbumList.h
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

#ifndef AlbumVolumeArray_H
#define AlbumVolumeArray_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <vector>

#include "Defs.h"

#include "design/DesignDefs.h"
#include "design/AlbumVolume.h"

namespace Design {

    class AlbumVolume;

    class AlbumList
    {
    public:

        AlbumList( ) {
            m_albumVolumeArray.clear( );
            m_albumVolumeNdx = -1;
        };
        ~AlbumList( ) { };
        bool IsOK( );
        Design::AlbumVolume* NewAlbumVolume( );
        Design::AlbumVolume* GetAlbumVolume( );
        void SaveAlbums( );
        void LoadAlbums( );
        bool ClearAlbumVolumeArray( );
        wxArrayString& GetVolumeNameStrings( ) { return m_albumNameStrings; };
        void SetAlbumVolumeNdx( int i );
        Design::AlbumVolumeArray* GetAlbumVolumeArray( ) { return &m_albumVolumeArray; };

    private:
        Design::AlbumVolumeArray m_albumVolumeArray;
        int m_albumVolumeNdx;
        wxArrayString m_albumNameStrings;


    };
}
#endif