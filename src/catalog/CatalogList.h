/**
 * @file CatalogList.h
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
 */

#ifndef CatalogList_H
#define CatalogList_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/treectrl.h>
#include <vector>

#include "Defs.h"

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogVolume.h"
#include "utils/VolumeList.h"


namespace Catalog {

    class CatalogVolume;

    int WayToSort( Catalog::CatalogVolume* sect1, Catalog::CatalogVolume* sect2 );

    ///  @brief The array that contains all the catalogs
    ///  
    class CatalogList : public Utils::VolumeList
    {


    public:


        CatalogList( ) : Utils::VolumeList( ) { };

        ~CatalogList( ) { };

        Catalog::CatalogVolume* NewVolumeInstance( wxString filename );

        Catalog::CatalogVolume* AddNewVolume( wxString filename );

        bool ImportCSV( wxString csvFilename );

        Catalog::CatalogVolume* NewCatalogVolume( wxString filename );

    private:

    };
}
#endif