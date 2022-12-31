/**
 * @file CatalogData.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
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

#ifndef CatalogData_H
#define CatalogData_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <vector>

#include "Defs.h"

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogVolumeData.h"

namespace Catalog {

class CatalogVolumeData;

    class CatalogData
    {
    public:

        CatalogData( ){ m_catalogVolumeDataNdx = -1; };
        ~CatalogData( );
        bool IsOK( );
        Catalog::CatalogVolumeData* NewCatalogVolumeData( );
        Catalog::CatalogVolumeData* GetCatalogVolumeData( );
        void SaveCatalogVolumes();
        void LoadCatalogVolumes();
        wxArrayString& GetVolumeNameStrings() {return m_volumeNameStrings;};
        void SetCatalogVolumeDataNdx( int i);
        Catalog::CatalogVolumeDataArray* GetCatalogArray(){ return &m_catalogArray; };

    private:
        Catalog::CatalogVolumeDataArray m_catalogArray;
        int m_catalogVolumeDataNdx;
        wxArrayString m_volumeNameStrings;


    };
}
#endif