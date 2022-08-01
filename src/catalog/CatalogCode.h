/**
 * @file CatalogCode.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2021-03-01
 *
 * @copyright Copyright (c) 2021
 * 
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
    public:
        CatalogCode( ) : CatalogBase( )
        {
            SetNodeType( NT_CatalogCode );
            IsOK( );
        };

        CatalogCode( wxXmlNode* ele ) : CatalogBase( ele )
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

}

#endif