/**
 * @file CatalogVolume.h
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

#ifndef CatalogVolume_H
#define CatalogVolume_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/treectrl.h>
#include <unordered_map>
#include <functional>

#include "CatalogDefs.h"
#include "utils/XMLUtilities.h"
#include "utils/Volume.h"

 //namespace Utils { class ImageRepository; };

namespace Catalog {

    class CatalogVolume;


    typedef std::unordered_map< std::string, CatalogVolume*  > CatalogVolumeArray;
    typedef std::unordered_map< int, wxTreeItemId > CatalogMenuIDArray;

    //CatalogVolume* NewCatalogVolumeInstance( );

    class CatalogVolume : public Utils::Volume
    {
    public:


        CatalogVolume( );

        ~CatalogVolume( );

        // bool operator>( CatalogVolume* rhs )
        // {
        //     if ( GetName( ).Cmp( rhs->GetName( ) ) > 0 )
        //     {
        //         return true;
        //     }
        //     return false;
        // }

        // bool operator<( CatalogVolume* rhs )
        // {
        //     if ( GetName( ).Cmp( rhs->GetName( ) ) > 0 )
        //     {
        //         return false;
        //     }
        //     return true;
        // }



        void EditDetailsDialog( wxWindow* parent );

        bool FixupInventoryStatus( wxXmlNode* parent, InventoryStatusType status );

        bool FixupInventoryStatus( );

        //void Load( );

        bool LoadCSV( wxString filename );

        Utils::wxXmlNodeArray* MakeParentList( Catalog::FormatType parentType );

        void MakeParentList( Catalog::FormatType parentType, Utils::wxXmlNodeArray* parentList, wxXmlNode* node );

        void NewCatalog( );

        void ReGroupMultiples( );

        void ReSortTree( );

        void Save( );

        void SaveXML( );



        /// this looks through the xml tree and makes related entries of childType a child of the parent type
        void StructureCatalogVolume( Catalog::FormatType parentType,
            Catalog::FormatType childType,
            Catalog::FormatType secondChildType = Catalog::FT_FormatUnknown );

        bool UpdateMount( wxXmlNode* parent );

        bool UpdateMount( );

        void LoadDefaultDocument( wxString volName );


    private:

    };

    //CatalogVolume* NewCatalogVolume( );

}
#endif