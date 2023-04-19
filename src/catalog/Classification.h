/**
 * @file Classification.h
 * @author Eddie Monroe ( )
 * @brief This is a wrapper of an wxXmlNode for
 * safe/convenient getting/putting.
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
 *
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/
#ifndef Classification_H
#define Classification_H

#include "CatalogDefs.h"
#include "CatalogBase.h"
#include "wx/xml/xml.h"
#include <wx/string.h>



namespace Catalog {

    /**
     * @brief This is a wrapper of an wxXmlNode for
     * safe/convenient getting/putting.
     * @see CatalogBase, Stamp, Specimen
     *
     **************************************************/
    class Classification : public CatalogBase
    {
    public:
        /**
         * @brief Construct a new Classification object
         *
         * @note This node is invalid until the node type is defined.
         * @see CatalogBase::SetCatNode
         *
         **************************************************/
        Classification( void ) : CatalogBase( )
        {
            SetXMLCatNode( 0 );
            SetNodeType( ( CatalogBaseType ) -1 );
        }

        /**
         * @brief Construct a new Classification object
         *
         * @param  node ; must be set to a valid Classification
         * node type or this instance will be invalid.
         **************************************************/
        Classification( wxXmlNode* node ) : CatalogBase( node )
        {
            if ( IsOK( ) )
            {
                SetNodeType( GetNodeType( ) );
            }
            else
            {
                SetNodeType( ( CatalogBaseType ) -1 );
            }
        };

        /**
         * @brief Destroy the Classification object
         *
         **************************************************/
        ~Classification( void ) { };

        /**
         * @brief Returns true if this is a valid Classification node.
         *
         * @return true  : if this node is defined and the node name is one of
         * NT_Catalog, NT_Period, NT_Year, or NT_Emission
         * @return false : otherwise
         */
        bool IsOK( void );

        /**
         * @brief Gets the XML attribute value of this node type.
         *
         * @param  type   a valid data type ( DataTypes )
         * @return wxString   the value of this type or "" if none.
         **************************************************/
        wxString GetAttr( ClassificationTypes type );

        /**
         * @brief Sets the node type to val.
         *
         * This is actually setting an XML attribute of this node to type = val.
         *
         * @param type   a valid data type
         * @param val   the string to be associated with this type
         **************************************************/
        void SetAttr( ClassificationTypes type, wxString val );

        /**
         * @brief Get the Val object
         *
         * @param  type   a valid data type
         * @return wxString  the value of this type or "" if none.
         **************************************************/
        wxString GetVal( ClassificationTypes type ) { return GetAttr( type ); };

        /**
         * @brief Set the Val object
         *
         * @param  type  a valid data type
         * @param  val the string to be associated with this type
         **************************************************/
        void SetVal( ClassificationTypes type, wxString val ) { SetAttr( type, val ); };

        /**
         * @brief Get the Name object
         *
         * @return wxString
         **************************************************/
        wxString GetTitle( void ) { return GetAttr( CT_Title ); };

        //        wxString GetPreferredCatalog( ) { return GetAttr( CT_PreferredCatalog ); };
        //        wxString GetImageDirectory( ) { return GetAttr( CT_ImageDirectory ); };

                /**
                 * @brief Set the Title object
                 *
                 * @param  val the value to set title
                 **************************************************/
        void SetTitle( wxString val ) { SetAttr( CT_Title, val ); };

        //        void SetPreferredCatalog( wxString val ) { SetAttr( CT_PreferredCatalog, val ); };
        //        void SetImageDirectory( wxString val ) { SetAttr( CT_ImageDirectory, val ); };

                /**
                 * @brief loop thru the CT_Names and find one that is
                 *  eqal to name and returns the corresponding DataType
                 *
                 * @param  name  string to search for
                 * @return ClassificationTypes the datatype corresponding to name
                 **************************************************/
        ClassificationTypes FindDataType( wxString name );

        /**
         * @brief stub for Classification to keep interface common.
         * This function is meaningful for Stamps
         *
         * @return true  Alswys returns true

         **************************************************/
        bool IsMultiple( void );

        /**
         * @brief Returns the Name of this element.
         *
         * @return wxString
         **************************************************/
        wxString GetLabel( void ) { return GetTitle( ); }
    };

}
#endif