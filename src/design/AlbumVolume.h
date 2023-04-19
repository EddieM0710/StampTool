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
 **************************************************/

#ifndef AlbumVolume_H
#define AlbumVolume_H

#include "Defs.h"
#include "design/DesignDefs.h"
#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/treebase.h>
#include "utils/XMLUtilities.h"

class DesignTreeCtrl;

namespace Design {

    class Album;
    class Page;
    class Row;
    class Column;
    class Stamp;
    class Title;
    class LayoutBase;
    class AlbumBase;

    // class that contains all the data for the Album design
    class AlbumVolume
    {
    public:

        /**
         * @brief Construct a new Catalog Data object
         *
         */
        AlbumVolume( );
        ~AlbumVolume( );
        AlbumVolume* InitAlbumVolume( );
        bool IsOK( );

        // create new AlbumVolume xml wxXmlDocument
        wxXmlDocument* NewDesignDocument( );

        // Get the AlbumVolume xml Doc
        wxXmlDocument* GetDoc( ) { return m_albumDoc; };

        // create a new design document with default data
        void LoadDefaultDocument( );

        /// @brief Save the AlbumVolume to an xml file  
        /// @param filename 
        void SaveXML( );

        // transfers the AlbumVolume tree to an xml file
        void SaveDesignTree( );

        // loads an xml file into memory 
        bool LoadXML( );

        Album* GetAlbum( ) { return m_album; };
        void SetAlbum( Album* album ) { m_album = album; };

        void MakePage( Design::LayoutBase* node );

        /// @brief Set the design to dirty
        /// @param state 
        void SetDirty( bool state = true );

        bool isDirty( ) { return m_dirty; };

        // Gets the page of the selected design given node
        AlbumBase* GetPage( AlbumBase* node );

        //        wxTreeItemId GetPage( wxTreeItemId id );

        NodeStatus ValidatePage( AlbumBase* node );

        //        AlbumBase* ValidateChildren( AlbumBase* node );

        //        void SaveNodeData( wxTreeItemId treeItemId );
        void UpdateAlbum( );
        void UpdatePage( AlbumBase* node );

        void SetAlbumFilename( wxString name ) { m_albumFilename = name; };
        wxString GetAlbumFilename( ) { return m_albumFilename; };
        wxString GetAlbumName( )
        {
            wxXmlNode* root = m_albumDoc->GetRoot( );
            if ( root )
            {
                return Utils::GetAttrStr( root, "Name" );
            }
            return "";
        };
        void SetAlbumName( wxString str )
        {
            wxXmlNode* root = m_albumDoc->GetRoot( );
            if ( root )
            {
                Utils::SetAttrStr( root, "Name", str );
            }
        };
    private:
        int isOKPtr;
        wxString m_albumFilename;
        wxXmlDocument* m_albumDoc;
        Album* m_album;
        bool m_dirty;
    };


    AlbumVolume* NewAlbumVolumeInstance( );
    typedef std::vector<AlbumVolume*> AlbumVolumeArray;
}
#endif