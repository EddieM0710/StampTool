/**
 * @file CatalogData.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef CatalogData_H
#define CatalogData_H

#include "wx/xml/xml.h"
#include <wx/string.h>

#include "CatalogDefs.h"


namespace Catalog {


    class CatalogData
    {
    public:

        /**
         * @brief Construct a new Catalog Data object
         *
         */
        CatalogData( );
        ~CatalogData( );
        bool IsOK( );
        wxXmlDocument* NewDocument( );
        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );
        wxXmlDocument* GetDoc( ) { return m_stampDoc; };
        void Save( );
        void LoadXML(  wxString filename );
        void LoadCSV( wxString filename );

        wxString GetTitle( ) { return m_title; }
        void  SetTitle( wxString val ) { m_title = val; };
         wxXmlNode* FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value );
        wxXmlNode* FindNodeWithPropertyAndValue( wxString property, wxString value );

        void SetDirty( bool state = true ) { m_dirty = state; };
        bool isDirty( ) { return m_dirty; };

    private:
        /* data */
        wxXmlDocument* m_stampDoc;
        wxString m_title;

        bool m_dirty;
    };
}
#endif