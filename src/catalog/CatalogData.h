/**
 * @file CatalogData.h
 * @author Eddie Monroe ( )
 * @brief
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

#ifndef CatalogData_H
#define CatalogData_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <vector>

#include "Defs.h"

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogSectionData.h"

namespace Catalog { 

class CatalogSectionData;

    class CatalogData
    { 
    public:

        CatalogData( ){ m_catalogSectionDataNdx = -1; };
        ~CatalogData( );
        bool IsOK( );
        Catalog::CatalogSectionData* NewCatalogSectionData( );
        Catalog::CatalogSectionData* GetCatalogSectionData( );
        void SaveCatalogSections( );
        void LoadCatalogSections( );
        bool ClearCatalogArray( );
        wxArrayString& GetSectionNameStrings( ) { return m_sectionNameStrings; };
        void SetCatalogSectionDataNdx( int i );
        Catalog::CatalogSectionDataArray* GetCatalogArray( ){ return &m_catalogArray; };

    private:
        Catalog::CatalogSectionDataArray m_catalogArray;
        int m_catalogSectionDataNdx;
        wxArrayString m_sectionNameStrings;


    };
}
#endif