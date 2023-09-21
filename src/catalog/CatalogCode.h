/**
 * @file CatalogCode.h
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

#ifndef CatalogCode_h
#define CatalogCode_h

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogBase.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogVolume.h"
 //#include "utils/ImageRepository.h"
#include <wx/string.h>
#include <wx/arrstr.h>

namespace Catalog {


    wxString MakeImageName( wxString catCode );
    void GetCodes( wxString catCodeStr, wxString& catalog, wxString& country, wxString& code );

    /**
     * @brief This is a wrapper of an wxXmlNode for
     * safe/convenient getting/putting.
     *
     *
     */
    class CatalogCode
    {
        /**
           * @brief Construct a new CatalogCode object
           *
           */
        CatalogCode( )
        {

        };

    public:

        /**
         * @brief Construct a new CatalogCode object
         *
         * @param entry
         */
        CatalogCode( wxString codeList );

        /**
         * @brief Destroy the CatalogCode object
         *
         */
        ~CatalogCode( ) { };

        wxString FindImageName( );

        wxString GetPreferredCatalogCode( wxString cat );

        bool IsCatalogCode( wxString catCode );
        wxArrayString& GetCodes( ){
            return m_codes;
        };

    private:
        wxArrayString m_codes;
        wxString m_codeList;
    };
}
#endif