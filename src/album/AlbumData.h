/**
 * @file AlbumData.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef AlbumData_H
#define AlbumData_H

#include "Defs.h"
#include "wx/xml/xml.h"
#include <wx/string.h>

class AlbumTreeCtrl;

namespace Layout {

    class Album;
    class Page;
    class Row;
    class Column;
    class Stamp;
    class Title;
    class LayoutNode;

    
    class AlbumData
    {
    public:

        /**
         * @brief Construct a new Catalog Data object
         *
         */
        AlbumData( );
        ~AlbumData( );
        bool IsOK( );
        wxXmlDocument* NewDocument( );
//        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );
        wxXmlDocument* GetDoc( ) { return m_albumDoc; };
        void SaveXML( wxString filename );
        void LoadXML( wxString filename );

        Album* GetAlbum( ) { return m_album; };
        void SetAlbum( Album* album ) { m_album = album; };
//        wxString GetTitle( ) { return m_title; };
//        void  SetTitle( wxString val ) { m_title = val; };

        Page* AddPage( LayoutNode* node );

        Column* AddCol( LayoutNode* node );
        Row* AddRow( LayoutNode* node );
        Stamp* AddStamp( LayoutNode* node );
        Title* AddTitle( LayoutNode* node );
//        AlbumTreeCtrl* GetAlbumTreeCtrl() { return m_albumTreeCtrl;};
//        void SetAlbumTreeCtrl( AlbumTreeCtrl* ctrl) {  m_albumTreeCtrl = ctrl;};
    private:
        /* data */
        wxXmlDocument* m_albumDoc;
        Album* m_album;
//        AlbumTreeCtrl* m_albumTreeCtrl;
    };
}
#endif