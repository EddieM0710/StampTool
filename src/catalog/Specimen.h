/**
 * @file Specimen.h
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
 */

#ifndef Instance_h
#define Instance_h

#include <vector>
#include <wx/dataview.h>
#include <wx/string.h>

#include "Defs.h"
#include "CatalogBase.h"

#include "wx/xml/xml.h"

namespace Catalog {

    /**
     * @brief This is a wrapper of an wxXmlNode for
     * safe/convenient getting/putting.
     * @see CatalogBase, Stamp, Specimen
     *
     */
    class Specimen : public CatalogBase
    {

    public:

        ///  @brief Construct a new Specimen object
        ///  
        Specimen( ) : CatalogBase( )
        {
            SetNodeType( NT_Specimen );
            IsOK( );
        };

        ///  @brief Construct a new Specimen object
        ///  
        ///  @param ele 
        Specimen( wxXmlNode* ele ) : CatalogBase( ele )
        {
            SetNodeType( NT_Specimen );
            IsOK( );
        };

        ///  @brief Destroy the Specimen object
        ///  
        ~Specimen( ) { };

        ///  @brief Get the attribute value of type
        ///  
        ///  @param type 
        ///  @return wxString 
        wxString GetAttr( ItemDataTypes type );

        ///  @brief Get the IDT_Condition Attribute
        ///  
        ///  @return wxString 
        wxString GetCondition( ) { return GetAttr( IDT_Condition ); };

        /**
         * @brief Fills the input vector with the specimen values and returns the element pointer for convenience
         *
         * @param data
         * @return wxXmlNode*
         */
        wxXmlNode* GetData( wxVector<wxVariant>* data );

        ///  @brief Get the IDT_Location Attribute
        ///  
        ///  @return wxString 
        wxString GetLocation( ) { return GetAttr( IDT_Location ); };

        ///  @brief Get the IDT_Remarks  Attribute
        ///  
        ///  @return wxString 
        wxString GetRemarks( ) { return GetAttr( IDT_Remarks ); };

        ///  @brief Get the IDT_Type Attribute
        ///  
        ///  @return wxString 
        wxString GetType( ) { return GetAttr( IDT_Type ); };

        ///  @brief Convenience function. Same as GetAttr( type )
        ///  
        ///  @param type 
        ///  @return wxString 
        wxString GetVal( ItemDataTypes type ) { return GetAttr( type ); };

        ///  @brief Get the IDT_Value Attribute
        ///  
        ///  @return wxString 
        wxString GetValue( ) { return GetAttr( IDT_Value ); };

        ///  @brief Sanity check instance
        ///  
        ///  @return true 
        ///  @return false 
        bool IsOK( );

        ///  @brief Set the attribute value of type
        ///  
        ///  @param type 
        ///  @param val 
        void SetAttr( ItemDataTypes type, wxString val );

        ///  @brief Set the IDT_Condition Attribute
        ///  
        ///  @param val 
        void SetCondition( wxString val ) { SetAttr( IDT_Condition, val ); };

        ///  @brief Set the IDT_Location Attribute
        ///  
        ///  @param val 
        void SetLocation( wxString val ) { SetAttr( IDT_Location, val ); };

        ///  @brief Set the IDT_RemarksV Attribute
        ///  
        ///  @param val 
        void SetRemarks( wxString val ) { SetAttr( IDT_Remarks, val ); };

        ///  @brief Set the IDT_Type Attribute
        ///  
        ///  @param val 
        void SetType( wxString val ) { SetAttr( IDT_Type, val ); };

        ///  @brief Convenience function. Same as SGetAttr( type )
        ///  
        ///  @param type 
        ///  @param val 
        void SetVal( ItemDataTypes type, wxString val ) { SetAttr( type, val ); };

        ///  @brief Set the IDT_Value Attribute
        ///  
        ///  @param val 
        void SetValue( wxString val ) { SetAttr( IDT_Value, val ); };

    private:
        bool m_OK;
        bool m_dataDirty[ IDT_NbrTypes ];
    };
}

#endif