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
 **************************************************/

#ifndef CatalogData_h
#define CatalogData_h

#include "utils/StampList.h"
#include "catalog/CatalogList.h"

namespace Catalog { class CatalogVolume; };
namespace Catalog { class CatalogList; };
namespace Catalog { class Entry; };


class CatalogTreeCtrl;
class StampDescriptionPanel;

namespace Catalog
{
    // Links to all the data and controls needed for Album design
    class CatalogData
    {
    public:

        ///  @brief Get the Catalog Volume object
        ///  
        ///  @return Catalog::CatalogVolume* 
        inline Catalog::CatalogVolume* GetCatalogVolume( )
        {
            return m_catalogList.GetCatalogVolume( );
        };

        ///  @brief Get the Volume Name Strings object
        ///  
        ///  @return wxArrayString& 
        wxArrayString& GetVolumeNameStrings( )
        {
            return m_catalogList.GetVolumeNameStrings( );
        }


        ///  @brief Open the Catalog xml file
        ///  
        ///  @param filename 
        void FileOpen( wxString filename );

        ///  @brief Get the Catalog List object
        ///  
        ///  @return Catalog::CatalogList* 
        Catalog::CatalogList* GetCatalogList( ) { return &m_catalogList; };

        ///  @brief  Load the catalog data from xml file
        void LoadCatalogVolumeFiles( );

        ///  @brief Read a csv file containing the Catalog entry data
        ///  
        ///  @param csvFilename 
        ///  @return true 
        ///  @return false 
        bool ReadCatalogCSV( wxString csvFilename );

        ///  @brief Load the xml data into the tree
        ///  
        void LoadCatalogTree( );

        ///  @brief Load a new unnamed empty catalog 
        ///  
        ///  @param catFile 
        void LoadNew( wxString catFile );

        ///  @brief Specify the name to save as 
        ///  
        ///  @param filename 
        void FileSaveAs( wxString filename );

        ///  @brief Save the fils
        ///  
        void FileSave( );



        ///  @brief Creates a new CatalogVolume. Deletes current one to prevent memory leaks.
        ///  
        ///  @return Catalog::CatalogVolume* 
        Catalog::CatalogVolume* NewCatalogVolume( );



        /// @brief Get the Catalog Notebook page TreeCtrl object
        ///
        /// @return CatalogTreeCtrl*
        ///
        inline CatalogTreeCtrl* GetCatalogPageTreeCtrl( ) { return m_catalogPageTreeCtrl; };

        ///  @brief Get the Album Notebook Page TreeCtrl object
        ///  
        ///  @return CatalogTreeCtrl* 
        inline CatalogTreeCtrl* GetAlbumPageTreeCtrl( ) { return m_albumPageTreeCtrl; };


        ///  @brief Get the Description Panel object
        ///  @return StampDescriptionPanel*
        inline StampDescriptionPanel* GetDescriptionPanel( ) { return m_stampDescriptionPanel; };

        ///  @brief Set the Catalog Notebook Page TreeCtrl object
        ///  
        ///  @param treeCtrl 
        void SetCatalogPageTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_catalogPageTreeCtrl = treeCtrl; };

        ///  @brief Set the Album Notebook Page TreeCtrl object
        ///  
        ///  @param treeCtrl 
        void SetAlbumPageTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_albumPageTreeCtrl = treeCtrl; };

        ///  @brief Set the Description Panel object
        ///  
        ///  @param descriptionPanel 
        void SetDescriptionPanel( StampDescriptionPanel* descriptionPanel ) { m_stampDescriptionPanel = descriptionPanel; };

        ///  @brief Get the Image Filename object
        ///  
        ///  @param stampId 
        ///  @return wxString 
        wxString GetImageFilename( wxString stampId );

        ///  @brief Get the Image Path object
        ///  
        ///  @return wxString 
        wxString GetImagePath( );

        ///  @brief Load the catalog data from file
        ///  
        void LoadData( );


        ///  @brief Set the Current Stamp object for sisplay in 
        /// all gui panels;
        ///  
        ///  @param stamp 
        void SetCurrentStamp( wxXmlNode* stamp );


        ///  @brief Get the Current Stamp object to display
        ///  
        ///  @return Entry* 
        inline Entry* GetCurrentStamp( ) { return m_stamp; };

    private:

        Catalog::Entry* m_stamp;
        Catalog::CatalogList m_catalogList;
        CatalogTreeCtrl* m_catalogPageTreeCtrl;
        CatalogTreeCtrl* m_albumPageTreeCtrl;
        StampDescriptionPanel* m_stampDescriptionPanel;
    };
}
#endif
