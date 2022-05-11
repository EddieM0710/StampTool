/**
 * @file CatalogCode.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2021-03-01
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef CatalogCode_h
#define CatalogCode_h

#include <vector>
#include <wx/dataview.h>
#include <wx/string.h>

#include "Defs.h"
#include "Node.h"

#include "wx/xml/xml.h"

 



/**
 * @todo fix catalog code usage
 *
 **************************************************/

 /**
  * @brief This is a wrapper of an wxXmlNode for
  * safe/convenient getting/putting.
  * @see Node, Stamp, CatalogCode, Specimen, Classification
  *
  **************************************************/
class CatalogCode : public Node
{
public:
    CatalogCode( ) : Node( )
    {
        SetNodeType( NT_CatalogCode );
        IsOK( );
    };

    CatalogCode( wxXmlNode* ele ) : Node( ele )
    {
        SetNodeType( NT_CatalogCode );
        IsOK( );
    };

    ~CatalogCode( ) { };

    bool IsOK( );

    wxString GetAttr( CatalogCodeTypes type );
    void SetAttr( CatalogCodeTypes type, wxString val );

    wxString GetVal( CatalogCodeTypes type ) { GetAttr( type ); };
    void SetVal( CatalogCodeTypes type, wxString val ) { SetAttr( type, val ); };

        void SetCatalog( wxString val );
        void SetCountry( wxString val );
        void SetID( wxString val );

    /**
     * @brief Fills the input vector with the code values and returns the element pointer for convenience
     * 
     * @param data   pointer to vector to fill
     * @return wxXmlNode*   pointer to the element of this CatalogCode
     **************************************************/
    wxXmlNode* GetData( wxVector<wxVariant>* data );


    wxString GetCatalog( );
    wxString GetCountry( );
    wxString GetID( );


private:
    bool m_OK;
    bool m_dataDirty[ CC_NbrTypes ];
};

#endif