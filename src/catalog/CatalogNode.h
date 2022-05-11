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

#ifndef CatalogNode_h
#define CatalogNode_h

#include "Node.h"

#include "catalog/CatalogDefs.h"
#include "wx/xml/xml.h"


namespace Catalog {

    class CatalogNode : public Node
    {
    public:
        CatalogNode( ) : Node(  ){};

        CatalogNode( wxXmlNode* ele ): Node(ele) { };

        ~CatalogNode( ) { };

        void SetCatalogNodeType( CatalogNodeType type ) { SetNodeType( (int)type); };
        CatalogNodeType GetCatalogNodeType( ) { return (CatalogNodeType)GetNodeType(); };

      //  wxXmlNode* GetNodeElement( ) { return m_Element; };
       // void SetNodeElement( wxXmlNode* node ) { m_Element = node; };

        virtual bool IsOK( ) = 0;

    private:
     
        
    };
}
#endif