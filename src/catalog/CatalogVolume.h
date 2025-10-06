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
#include "utils/Volume.h"
#include "utils/XMLUtilities.h"

 //namespace Utils { class ImageRepository; };

namespace Catalog {

    class CatalogVolume;


    typedef std::unordered_map< std::string, CatalogVolume*  > CatalogVolumeArray;
    typedef std::unordered_map< int, wxTreeItemId > CatalogMenuIDArray;

    /**
     * @brief Contains the filename and xml data location of the Catalog Volume
     *
     */
    class CatalogVolume : public Utils::Volume
    {
    public:


        CatalogVolume( );

        ~CatalogVolume( );

        void EditDetailsDialog( wxWindow* parent );

        bool FixupInventoryStatus( wxXmlNode* parent, InventoryStatusType status );

        bool FixupInventoryStatus( );

        bool LoadCSV( wxString filename, wxString newFilename );

        /**
         * @brief  this makes a list of the children entry elements that can have childrem
         */
        Utils::wxXmlNodeArray* MakeParentList( Catalog::FormatType parentType );

        void MakeParentList( Catalog::FormatType parentType, Utils::wxXmlNodeArray* parentList, wxXmlNode* node );

        void NewCatalog( );

        /**
         * @brief  This is an attempt to group the entrys;  
         * i.e., an item of type entry can be a child of an item SeTenent type.
         * 
         */
        void ReGroupMultiples( );

        /**
         * @brief resort the tree with the new sort order data. Probably doing this because the sort order was changed.
         * 
         */
        void ReSortTree( );

        void Save( );

        void SaveXML( );

        /**
         * @brief this looks through the xml tree and makes related entries of childType a child of the parent type
         * 
         * @param parentType 
         * @param childType 
         * @param secondChildType 
         */
        void StructureCatalogVolume( Catalog::FormatType parentType, 
            Catalog::FormatType childType, 
            Catalog::FormatType secondChildType = Catalog::FT_FormatUnknown );

        /**
         * @brief 
         * 
         * @param parent 
         * @return true 
         * @return false 
         */
        bool UpdateMount( wxXmlNode* parent );

        bool UpdateMount( );

        void LoadDefaultDocument( wxString volName );


    private:

    };

}
#endif