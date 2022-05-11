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


#include "catalog/CatalogDefs.h"
#include "wx/xml/xml.h"


namespace Catalog {

    class CatalogNode
    {
    public:
        CatalogNode( ){};

        CatalogNode( wxXmlNode* ele ) { SetNodeElement( ele );};

        ~CatalogNode( ) { SetNodeElement( ( wxXmlNode* )0 );  };

        void SetNodeType( CatalogNodeType type ) { m_nodeType = type; };
        CatalogNodeType GetNodeType( ) { return m_nodeType; };

        wxXmlNode* GetNodeElement( ) { return m_Element; };
        void SetNodeElement( wxXmlNode* node ) { m_Element = node; };
        wxXmlNode* GetFirstChild( ) { return m_Element->GetChildren(); };
        
         wxString GetNodeAttrStr( wxString name );
         double GetNodeAttrDbl( wxString name );
         void SetNodeAttrStr( wxString name, wxString val );
         void SetNodeAttrDbl( wxString name, double val );


      //  wxXmlNode* GetNodeElement( ) { return m_Element; };
       // void SetNodeElement( wxXmlNode* node ) { m_Element = node; };

        virtual bool IsOK( ) = 0;

    private:
        wxXmlNode* m_Element;
        CatalogNodeType m_nodeType;            
    };
}
#endif