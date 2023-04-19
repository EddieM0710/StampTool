/**
 * @file CatalogCode.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2021-03-01
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

#ifndef CatalogCode_h
#define CatalogCode_h

#include <vector>
#include <wx/dataview.h>
#include <wx/string.h>

#include "CatalogDefs.h"
#include "CatalogBase.h"

#include "wx/xml/xml.h"



namespace Catalog {



    /**
     * @todo fix catalog code usage
     *
     **************************************************/

     /**
      * @brief This is a wrapper of an wxXmlNode for
      * safe/convenient getting/putting.
      * @see CatalogBase, Stamp, CatalogCode, Specimen, Classification
      *
      **************************************************/
    class CatalogCode : public CatalogBase
    {
    private:
        CatalogCode( ) : CatalogBase( )
        {
            SetNodeType( NT_CatalogCode );
            IsOK( );
        };

    public:

        ///  @brief Construct a new Catalog Code object
        ///  
        ///  @param ele 
        CatalogCode( wxXmlNode* ele ) : CatalogBase( ele )
        {
            SetNodeType( NT_CatalogCode );
            IsOK( );
        };


        ///  @brief Destroy the Catalog Code object
        ///  
        ~CatalogCode( ) { };


        ///  @brief Sanity check on CataloCode instantion
        ///  
        ///  @return true 
        ///  @return false 
        bool IsOK( );


        ///  @brief Get the attr value for the given type
        ///  
        ///  @param type 
        ///  @return wxString 
        wxString GetAttr( CatalogCodeTypes type );


        ///  @brief Set the attr value fo th given type
        ///  
        ///  @param type 
        ///  @param val 
        void SetAttr( CatalogCodeTypes type, wxString val );


        ///  @brief Convenience function for setting Catalog attribute
        ///  
        ///  @param val 
        void SetCatalog( wxString val );

        ///  @brief Convenience function for setting Country attribute
        ///  
        ///  @param val 
        void SetCountry( wxString val );

        ///  @brief Convenience function for setting ID attribute
        ///  
        ///  @param val 
        void SetID( wxString val );

        /**
         * @brief Fills the input vector with the code values and returns the element pointer for convenience
         *
         * @param data   pointer to vector to fill
         * @return wxXmlNode*   pointer to the element of this CatalogCode
         **************************************************/
        wxXmlNode* GetData( wxVector<wxVariant>* data );



        ///  @brief Convenience function for getting Catalog attribute
        ///  
        ///  @param val 
        wxString GetCatalog( );

        ///  @brief Convenience function for getting Country attribute
        ///  
        ///  @param val 
        wxString GetCountry( );

        ///  @brief Convenience function for getting id attribute
        ///  
        ///  @param val 
        wxString GetID( );


    private:
        bool m_OK;
        bool m_dataDirty[ CC_NbrTypes ];
    };

}

#endif