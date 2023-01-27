/**
 * @file DesignData.h
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

#ifndef DesignData_H
#define DesignData_H

#include "Defs.h"
#include "design/DesignDefs.h"
#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/treebase.h>

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
    class DesignData
    { 
    public:

        /**
         * @brief Construct a new Catalog Data object
         *
         */
        DesignData( );
        ~DesignData( );
        DesignData* InitDesignData( );
        bool IsOK( );

        // create new DesignData xml wxXmlDocument
        wxXmlDocument* NewDesignDocument( );

        // Get the DesignData xml Doc
        wxXmlDocument* GetDoc( ) { return m_albumDoc; };

        // create a new design document with default data
        void LoadDefaultDocument( );

        void SaveXML( wxString filename );
        void SaveDesignTree( );
        bool LoadXML( wxString filename );

        Album* GetAlbum( ) { return m_album; };
        void SetAlbum( Album* album ) { m_album = album; };

        void MakePage( Design::LayoutBase* node );

        void SetDirty( bool state = true );
        bool isDirty( ) { return m_dirty; };

        AlbumBase* GetPage( AlbumBase* node );
        wxTreeItemId GetPage( wxTreeItemId id );
        NodeStatus ValidatePage( AlbumBase* node );
        AlbumBase* ValidateChildren( AlbumBase* node );

        void SaveNodeData( wxTreeItemId treeItemId );
        void UpdateAlbum( );

    private:
        wxXmlDocument* m_albumDoc;
        Album* m_album;

        bool m_dirty;
    };


    DesignData* NewDesignDataInstance( );

}
#endif