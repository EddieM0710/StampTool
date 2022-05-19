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

        CatalogData( );
        ~CatalogData( );
        bool IsOK( );

        // Create a Catalog xml doc
        wxXmlDocument* NewDocument( );

        // Delete the current Catalog xml doc and replace with new doc
        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );

        // Get the Catalog XML doc
        wxXmlDocument* GetDoc( ) { return m_stampDoc; };

        //Create and load a new Catalog xml Doc
        void NewCatalog();

        void Save( );
        // Load Catalog xml file
        void LoadXML( wxString filename );

        // Load Catalog csv file
        void LoadCSV( wxString filename );

       // wxString GetTitle( ) { return m_title; }
       // void SetTitle( wxString val ) { m_title = val; };

        wxXmlNode* FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value );
        wxXmlNode* FindNodeWithPropertyAndValue( wxString property, wxString value );

        void SetDirty( bool state = true );
        bool isDirty( ) { return m_dirty; };

    private:
        wxXmlDocument* m_stampDoc;
      //  wxString m_title;
        bool m_dirty;
    };
    
    CatalogData* NewCatalogDataInstance();

}
#endif