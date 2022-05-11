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


namespace Layout {

    class Album;

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
        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );
        wxXmlDocument* GetDoc( ) { return m_albumDoc; };
        void SaveXML( wxString filename );
        void LoadXML( wxString filename );

        Album* GetAlbum( ) { return m_album; };
        void SetAlbum( Album* album ) { m_album = album; };
        wxString GetTitle( ) { return m_title; };
        void  SetTitle( wxString val ) { m_title = val; };

    private:
        /* data */
        wxXmlDocument* m_albumDoc;
        Album* m_album;
        wxString m_title;
    };
}
#endif