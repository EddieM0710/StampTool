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

#include "Defs.h"
#include "tinyxml2.h"
#include <wx/string.h>

using namespace tinyxml2;

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
    XMLDocument* NewDocument( );
    XMLDocument* ReplaceDocument( XMLDocument* doc );
    XMLDocument* GetDoc( ) { return m_stampDoc; };
    void SaveXML( wxString filename );
    void LoadXML( wxString filename );
    void LoadCSV( wxString filename );

    wxString GetTitle( ) { return m_title; }
    void  SetTitle( wxString val ) { m_title = val; };

private:
    /* data */
    XMLDocument* m_stampDoc;
    wxString m_title;
};

#endif