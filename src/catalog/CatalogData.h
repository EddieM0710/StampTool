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

namespace Catalog { class CatalogVolume; };
namespace Catalog { class CatalogList; };
namespace Catalog { class Entry; };


class CatalogTreeCtrl;
class StampDescriptionPanel;
class CatalogPanel;
class InventoryPanel;
class GenerateList;

namespace Catalog
{

    ///  @brief Links the Catalog data and Catalog gui.
    ///  
    class CatalogData
    {
    public:

        ///  @brief Construct a new Catalog Data object
        ///  
        CatalogData( ) { };

        ///  @brief Destroy the Catalog Data object
        ///  
        ~CatalogData( ) { };

        ///  @brief Open the Catalog xml file
        ///  
        ///  @param filename 
        void FileOpen( wxString filename );

        ///  @brief Save the fils
        ///  
        void FileSave( );

        ///  @brief Specify the name to save as 
        ///  
        ///  @param filename 
        void FileSaveAs( wxString filename );

        ///  @brief Get the Album Notebook Page TreeCtrl object
        ///  
        ///  @return CatalogTreeCtrl* 
        //inline CatalogTreeCtrl* GetAlbumPageTreeCtrl( ) { return m_albumPageTreeCtrl; };

        ///  @brief Get the Catalog List object
        ///  
        ///  @return Catalog::CatalogList* 
        Catalog::CatalogList* GetCatalogList( ) { return &m_catalogList; };

        /// @brief Get the Catalog Notebook page TreeCtrl object
        ///
        /// @return CatalogTreeCtrl*
        ///
        inline CatalogTreeCtrl* GetCatalogTreeCtrl( ) { return m_catalogTreeCtrl; };

        ///  @brief Get the Image Filename object
        ///  
        ///  @param stampId 
        ///  @return wxString 
        wxString GetImageFilename( wxString stampId );

        ///  @brief Get the Image Path object
        ///  
        ///  @return wxString 
        wxString GetImagePath( );

        // CatalogPanel*  GetCatalogPanel( ){ return m_catalogPanel; };

         ///  @brief Get the Catalog Volume object
         ///  
         ///  @return Catalog::CatalogVolume* 
        inline Catalog::CatalogVolume* GetCatalogVolume( )
        {
            return m_catalogList.GetCatalogVolume( );
        };

        ///  @brief Get the Current Stamp object to display
        ///  
        ///  @return Entry* 
        inline wxXmlNode* GetCurrentStamp( ) { return m_stamp; };

        ///  @brief Get the Description Panel object
        ///  @return StampDescriptionPanel*
        inline StampDescriptionPanel* GetDescriptionPanel( ) { return m_stampDescriptionPanel; };

        InventoryPanel* GetInventoryPanel( );

        GenerateList* GetGenerateListPanel( ) { return m_generateListPanel; };

        ///  @brief Get the Volume Name Strings object
        ///  
        ///  @return wxArrayString& 
        wxArrayString& GetVolumeNameStrings( )
        {
            return m_catalogList.GetVolumeNameStrings( );
        }

        ///  @brief Load the xml data into the tree
        ///  
        void LoadCatalogTree( );

        ///  @brief Load the catalog data from file
        ///  
        void LoadData( );

        wxXmlDocument* LoadMountCSV( );

        ///  @brief Load a new unnamed empty catalog 
        ///  
        ///  @param catFile 
        void LoadNew( wxString catFile );

        ///  @brief Creates a new CatalogVolume. Deletes current one to prevent memory leaks.
        ///  
        ///  @return Catalog::CatalogVolume* 
        Catalog::CatalogVolume* NewCatalogVolume( );

        ///  @brief Read a csv file containing the Catalog entry data
        ///  
        ///  @param csvFilename 
        ///  @return true 
        ///  @return false 
        bool ImportCSV( wxString csvFilename );

        ///  @brief Set the Album Notebook Page TreeCtrl object
        ///  
        ///  @param treeCtrl 
      //  void SetAlbumPageTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_albumPageTreeCtrl = treeCtrl; };

        ///  @brief Set the Description Panel object
        ///  
        ///  @param descriptionPanel 
        void SetDescriptionPanel( StampDescriptionPanel* descriptionPanel ) { m_stampDescriptionPanel = descriptionPanel; };

        void SetGenerateListPanel( GenerateList* generateListPanel ) { m_generateListPanel = generateListPanel; };


        ///  @brief Set the Catalog Notebook Page TreeCtrl object
        ///  
        ///  @param treeCtrl 
        void SetCatalogTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_catalogTreeCtrl = treeCtrl; };

        void SetCatalogTreePanel( CatalogPanel* catalogPanel ) { m_catalogTreePanel = catalogPanel; };


        CatalogPanel* GetCatalogTreePanel( ) { return m_catalogTreePanel; };

        ///  @brief Set the Volume List Strings object
        ///  
        ///  @param choices 
        void SetCollectionListStrings( );

        ///  @brief Set the Volume List Selection object
        ///  
        ///  @param i 
        void SetCollectionListSelection( );

        //void SetAlbumNotebookPagePanel( CatalogPanel* catalogPanel ) { m_albumNotebookPagePanel = catalogPanel; };

        ///  @brief Set the Current Stamp object for sisplay in 
        /// all gui panels;
        ///  
        ///  @param stamp 
        void SetCurrentStamp( wxXmlNode* xmlNode );

        void UpdateCatalogVolumeStrings( );

    private:

        wxXmlNode* m_stamp;
        Catalog::CatalogList m_catalogList;
        CatalogTreeCtrl* m_catalogTreeCtrl;
        //CatalogTreeCtrl* m_albumPageTreeCtrl;
        StampDescriptionPanel* m_stampDescriptionPanel;
        GenerateList* m_generateListPanel;

        CatalogPanel* m_catalogTreePanel;
        //CatalogPanel* m_albumNotebookPagePanel;
    };
}
#endif
