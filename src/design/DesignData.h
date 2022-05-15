/**
 * @file DesignData.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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

        void MakePage( LayoutBase* node );

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
}
#endif