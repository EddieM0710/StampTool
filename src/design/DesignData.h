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

        wxXmlDocument* NewDocument( );
        wxXmlDocument* GetDoc( ) { return m_albumDoc; };

        void SaveXML( wxString filename );
        bool LoadXML( wxString filename );

        Album* GetAlbum( ) { return m_album; };
        void SetAlbum( Album* album ) { m_album = album; };

        Page* AddPage( LayoutBase* node );
        Column* AddCol( LayoutBase* node );
        Row* AddRow( LayoutBase* node );
        Stamp* AddStamp( LayoutBase* node );
        Title* AddTitle( LayoutBase* node );

        void SetDirty( bool state = true ) { m_dirty = state; };
        bool isDirty( ) { return m_dirty; };

        AlbumBase* GetPage( AlbumBase* node);
        NodeStatus ValidatePage( AlbumBase* node );
        AlbumBase* ValidateChildren( AlbumBase* node );

    private:
        wxXmlDocument* m_albumDoc;
        Album* m_album;

        bool m_dirty;
    };
}
#endif