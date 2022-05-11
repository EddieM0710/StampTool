/**
 * @file Specimen.h
 * @author Eddie Monroe ()
 * @brief This is a wrapper of an wxXmlNode for
 * safe/convenient getting/putting.
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef Instance_h
#define Instance_h

#include <vector>
#include <wx/dataview.h>
#include <wx/string.h>

#include "Defs.h"
#include "CatalogNode.h"

#include "wx/xml/xml.h"


namespace Catalog {


    /**
     * @brief This is a wrapper of an wxXmlNode for
     * safe/convenient getting/putting.
     * @see CatalogNode, Stamp, Specimen
     *
     **************************************************/
    class Specimen : public CatalogNode
    {
    public:
        Specimen( ) : CatalogNode( )
        {
            SetNodeType( NT_Specimen );
            IsOK( );
        };

        Specimen( wxXmlNode* ele ) : CatalogNode( ele )
        {
            SetNodeType( NT_Specimen );
            IsOK( );
        };

        ~Specimen( ) { };

        bool IsOK( );

        wxString GetAttr( ItemDataTypes type );
        void SetAttr( ItemDataTypes type, wxString val );

        wxString GetVal( ItemDataTypes type ) { GetAttr( type ); };
        void SetVal( ItemDataTypes type, wxString val ) { SetAttr( type, val ); };

        wxString GetType( ) { return GetAttr( IDT_Type ); };
        void SetType( wxString val ) { SetAttr( IDT_Type, val ); };

        wxString GetCondition( ) { return GetAttr( IDT_Condition ); };
        void SetCondition( wxString val ) { SetAttr( IDT_Condition, val ); };

        wxString GetValue( ) { return GetAttr( IDT_Value ); };
        void SetValue( wxString val ) { SetAttr( IDT_Value, val ); };

        wxString GetLocation( ) { return GetAttr( IDT_Location ); };
        void SetLocation( wxString val ) { SetAttr( IDT_Location, val ); };

        wxString GetRemarks( ) { return GetAttr( IDT_Remarks ); };
        void SetRemarks( wxString val ) { SetAttr( IDT_Remarks, val ); };

        /**
         * @brief Fills the input vector with the specimen values and returns the element pointer for convenience
         *
         * @param data
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* GetData( wxVector<wxVariant>* data );

    private:
        bool m_OK;
        bool m_dataDirty[ IDT_NbrTypes ];
    };
}

#endif