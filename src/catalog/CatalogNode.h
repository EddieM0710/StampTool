/**
 * @file CatalogNode.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef Node_h
#define Node_h

#include "CatalogDefs.h"
#include "wx/xml/xml.h"


namespace Catalog {


    class CatalogNode
    {
    public:
        CatalogNode( ) { SetElement( ( wxXmlNode* )0 ); };

        CatalogNode( wxXmlNode* ele ) { SetElement( ele ); };

        ~CatalogNode( ) { };

        void SetCatalogNodeType( CatalogNodeType type ) { m_nodeType = type; };
        CatalogNodeType GetCatalogNodeType( ) { return m_nodeType; };

        wxXmlNode* GetElement( ) { return m_Element; };
        void SetElement( wxXmlNode* node ) { m_Element = node; };

        virtual bool IsOK( ) = 0;


    private:
        wxXmlNode* m_Element;
        CatalogNodeType m_nodeType;
    };
}
#endif