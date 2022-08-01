/**
 * @file CatalogBase.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>. 
 * *
 **************************************************/

#ifndef CatalogBase_h
#define CatalogBase_h


#include "catalog/CatalogDefs.h"
#include "wx/xml/xml.h"


namespace Catalog {

    class CatalogBase
    {
    public:
        CatalogBase( ) {};

        CatalogBase( wxXmlNode* ele ) { SetXMLCatNode( ele ); };

        ~CatalogBase( ) { SetXMLCatNode( ( wxXmlNode* )0 ); };

        void SetNodeType( CatalogBaseType type ) { m_nodeType = type; };
        CatalogBaseType GetNodeType( ) { return m_nodeType; };

        wxXmlNode* GetCatXMLNode( ) { return m_catXMLNode; };
        void SetXMLCatNode( wxXmlNode* node ) { m_catXMLNode = node; };
        wxXmlNode* GetFirstChild( ) { return m_catXMLNode->GetChildren( ); };

        wxString GetNodeAttrStr( wxString name );
        double GetNodeAttrDbl( wxString name );
        void SetNodeAttrStr( wxString name, wxString val );
        void SetNodeAttrDbl( wxString name, double val );

        virtual bool IsOK( ) = 0;

    private:
        wxXmlNode* m_catXMLNode;
        CatalogBaseType m_nodeType;
    };
}
#endif