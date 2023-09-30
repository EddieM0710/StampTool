/**
 * @file AlbumVolume.h
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

#ifndef AlbumVolume_H
#define AlbumVolume_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/treebase.h>
#include <wx/zipstrm.h>
#include <wx/arrstr.h>
#include <unordered_map>

#include "Defs.h"
#include "design/DesignDefs.h"

#include "utils/XMLUtilities.h"
#include "utils/Volume.h"

class AlbumTreeCtrl;
//namespace Utils { class ImageRepository; };

namespace Design {

    class Album;
    class LayoutBase;
    class AlbumBase;

    /// @brief class that contains all the data for the Album design
    class AlbumVolume : public Utils::Volume
    {

    public:

        AlbumVolume( );

        ~AlbumVolume( );

        Album* GetAlbum( ) {
            return m_album;
        };

        AlbumBase* GetPage( AlbumBase* node );

        AlbumVolume* InitAlbumVolume( );

        void LoadDefaultDocument( );

        void MakePage( Design::LayoutBase* node );

        void SaveXML( );

        void Save( );

        void SaveDesignTree( );

        void SetAlbum( Album* album ) {
            m_album = album;
        };

        void SetAlbumName( wxString str )
        {
            wxXmlNode* root = GetDoc( )->GetRoot( );
            if ( root )
            {
                Utils::SetAttrStr( root, "Name", str );
            }
        };

        void UpdateAlbum( );

        void UpdatePage( AlbumBase* node );

        NodeStatus ValidatePage( AlbumBase* node );

    private:
        Album* m_album;

    };


    AlbumVolume* NewAlbumVolume( );
    typedef std::unordered_map< std::string, AlbumVolume*> AlbumVolumeArray;
    typedef std::unordered_map< int, wxTreeItemId > AlbumMenuIDArray;

}
#endif