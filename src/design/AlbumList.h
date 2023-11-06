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
 */

#ifndef AlbumVolumeArray_H
#define AlbumVolumeArray_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <vector>


#include "Defs.h"

#include "utils/VolumeList.h"
#include "design/DesignDefs.h"
#include "design/AlbumVolume.h"

namespace Design {

    class AlbumVolume;

    int WayToSort( Design::AlbumVolume* sect1, Design::AlbumVolume* sect2 );

    class AlbumList : public Utils::VolumeList
    {

    public:

        AlbumList( ) : Utils::VolumeList( ) { };

        ~AlbumList( ) { };

        Design::AlbumVolume* AddNewVolume( wxString filename );

        Design::AlbumVolume* NewVolumeInstance( wxString filename );

    private:
    };
}
#endif