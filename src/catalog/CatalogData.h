/**
 * @file CatalogData.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright ( c ) 2022
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

#ifndef CatalogData_h
#define CatalogData_h

#include "utils/StampList.h"
#include "catalog/CatalogList.h"

namespace Catalog {
    class CatalogVolume;
};
namespace Catalog {
    class CatalogList;
};
namespace Catalog {
    class Entry;
};


class CatalogTreeCtrl;
class CatalogTOCTreeCtrl;
class StampDescriptionPanel;
class CatalogPanel;
class InventoryPanel;
class GenerateList;
class ImageGalleryPanel;


namespace Catalog
{

    ///  @brief Links the Catalog data and Catalog gui.
    ///  
    class CatalogData
    {
    public:

        CatalogData( ) { };

        ~CatalogData( ) { };

        void Clear( );

        void FileOpen( wxString filename );

        void FileSave( );

        void FileSaveAs( wxString filename );

        Catalog::CatalogList* GetCatalogList( ) {
            return &m_catalogList;
        };

        inline CatalogTreeCtrl* GetCatalogTreeCtrl( ) {
            return m_catalogTreeCtrl;
        };
        inline CatalogTOCTreeCtrl* GetCatalogTOCTreeCtrl( ) {
            return m_catalogTocTreeCtrl;
        };

        CatalogPanel* GetCatalogPanel( ) {
            return m_catalogPanel;
        };

        inline Catalog::CatalogVolume* GetCatalogVolume( )
        {
            return ( Catalog::CatalogVolume* ) m_catalogList.GetVolume( );
        };

        inline wxXmlNode* GetCurrentStamp( ) {
            return m_stamp;
        };

        inline StampDescriptionPanel* GetDescriptionPanel( ) {
            return m_stampDescriptionPanel;
        };

        GenerateList* GetGenerateListPanel( ) {
            return m_generateListPanel;
        };

        InventoryPanel* GetInventoryPanel( );

        wxXmlDocument* LoadMountCSV( );

        // void LoadNew( wxString catFile );

        //CatalogVolume* NewCatalogVolume( wxString filename );

        void SetCollection( wxString newCollection );

        void SetCatalogTreeCtrl( CatalogTreeCtrl* treeCtrl ) {
            m_catalogTreeCtrl = treeCtrl;
        };

        void SetCatalogTOCTreeCtrl( CatalogTOCTreeCtrl* treeCtrl ) {
            m_catalogTocTreeCtrl = treeCtrl;
        };

        void SetDescriptionPanel( StampDescriptionPanel* descriptionPanel ) {
            m_stampDescriptionPanel = descriptionPanel;
        };

        void SetGenerateListPanel( GenerateList* generateListPanel ) {
            m_generateListPanel = generateListPanel;
        };

        void SetImageGalleryPanel( ImageGalleryPanel* imageGalleryPanel ) {
            m_imageGalleryPanel = imageGalleryPanel;
        };

        ImageGalleryPanel* GetImageGalleryPanel( ) {
            return m_imageGalleryPanel;
        };


        void SetCatalogPanel( CatalogPanel* catalogPanel ) {
            m_catalogPanel = catalogPanel;
        };

        // void SetCollectionListSelection( );

        void SetCurrentStamp( wxXmlNode* xmlNode );

        void UpdateCatalogPanels( );

    private:

        wxXmlNode* m_stamp;
        Catalog::CatalogList m_catalogList;
        CatalogTreeCtrl* m_catalogTreeCtrl;
        CatalogTOCTreeCtrl* m_catalogTocTreeCtrl;
        StampDescriptionPanel* m_stampDescriptionPanel;
        GenerateList* m_generateListPanel;
        ImageGalleryPanel* m_imageGalleryPanel;
        CatalogPanel* m_catalogPanel;
    };
}
#endif
