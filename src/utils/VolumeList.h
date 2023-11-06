/**
 * @file VolumeList.h
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

#ifndef VolumeList_H
#define VolumeList_H

#include "wx/xml/xml.h"
#include <wx/string.h>

#include "Defs.h"


#include "utils/Volume.h"


namespace Utils {

    class Volume;

    int WayToSort( Utils::Volume* sect1, Utils::Volume* sect2 );

    class VolumeList
    {
    public:

        VolumeList( ) {
            m_currVolume = ( Volume* ) 0;
        };

        ~VolumeList( ) { };

        wxXmlNode* AddChild( wxXmlNode* child );

        bool Clear( );

        void dumpArray( wxArrayString& array );

        wxTreeItemId FindMenuID( int id );

        MenuIDArray::iterator FindMenuIDIterator( int id );

        Utils::Volume* FindVolume( wxString str );

        VolumeArray::iterator FindVolumeIterator( wxString str );

        Utils::VolumeArray* GetArray( ) {
            return &m_volumeArray;
        };

        Utils::Volume* GetVolume( );

        void Insert( int id, wxTreeItemId treeId );

        void Insert( wxString str, Utils::Volume* vol );

        virtual Volume* NewVolumeInstance( wxString filename ) = 0;

        void RemoveVolume( wxString name );

        void RemoveVolume( Volume* vol );

        void SaveDirtyVolumes( );

        void SaveVolumes( );

        //        void Load( );

        void SetCurrentVolume( Volume* vol );


    private:
        MenuIDArray m_menuIDArray;
        Utils::VolumeArray m_volumeArray;
        Utils::Volume* m_currVolume;
    };
}
#endif