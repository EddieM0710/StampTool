/**
 * @file ToolData.h
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

#ifndef ToolData_h
#define ToolData_h

#include "utils/StampList.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogSectionData.h"

namespace Design { class DesignData; };
namespace Catalog { class CatalogSectionData; };
namespace Utils { class Project; };
namespace Utils { class Settings; };

class CatalogTreeCtrl;
class DesignTreeCtrl;
class StampDescriptionPanel;
class AlbumImagePanel;

ToolData* NewToolDataInstance( );

// Links to all the data and controls needed for Album design
class ToolData
{ 
public:
    ToolData( );
    ~ToolData( ) { };
    void InitToolData( );

/** **************************************************
 * @brief Get the Stamp Album Catalog Link object
 * 
 * @return Utils::StampList* 
 **************************************************/
    inline Utils::StampList* GetStampAlbumCatalogLink( ) { return &m_StampAlbumCatalogLink; };

/** **************************************************
 * @brief 
 * 
 **************************************************/
   // void LoadCatalogXML( wxString catalogFilename );

    inline Design::DesignData* GetDesignData( ) { return m_designData; };

    Design::DesignData* FileOpenDesign( wxString filename );
    Design::DesignData* FileOpenCatalog( wxString filename );

    /**
     * @brief Create a new empty DesignData instance and clear tree
     *
     * @return Design::DesignData*
     */
    Design::DesignData* NewDesignData( void );


    /**
     * @brief creates a new DesignData instance and loads default data
     *
     */
    void LoadDefaultDesignData( );

    /**
     * @brief creates a new DesignData instance and loads xml file specified in Project
     *
     */
    void ReadDesignFile( );


    /** ***************************************************
     * @brief Load the Design tree with current xml document
     *
     */
    void LoadDesignTree( );

    /** ************************************************
     * @brief Load a new unnamed Design with default data
     * 
     */
    void LoadNewDesign( wxString designFileName  );

    inline Catalog::CatalogSectionData* GetCatalogSectionData( ) 
    { return m_catalogData.GetCatalogSectionData( ); };

    wxArrayString& GetSectionNameStrings( )
    { 
        return m_catalogData.GetSectionNameStrings( );
    }

    Catalog::CatalogData* GetCatalogData( ){ return &m_catalogData; };

    /** ****************************************
     * @brief Load the catalog data from xml file
     * 
     */
    void LoadCatalogSectionFiles( );

    //Load a csv catalog.
    bool ReadCatalogCSV( wxString csvFilename );

    //Load the xml data into the tree
     void LoadCatalogTree( );

    //Load a new unnamed empty catalog 
    void LoadNewCatalog( wxString catFile );

    //Load the Catalog and Design data and trees
    void LoadData( );

    // Load a new Project
    void FileNewProject( wxString prjName );

    /** ****************************************
     * @brief Read the project file and load the Catalog and Design
     * 
     * @param filename 
     */
    void FileOpenProject( wxString filename );

    // @brief Perform File-Save for Project
    void FileSaveProject( );

    // @brief Perform File-SaveAs for Project
    void FileSaveAsProject( wxString filename );
  
    void FileSaveAsDesign( wxString filename );
    void FileSaveDesign( );
 
    void FileSaveAsCatalog( wxString filename );
    void FileSaveCatalog( );

    // Load last Project file at startup if enabled
    void InitLoad( );

    // Creates a new CatalogSectionData. Deletes current one to prevent memory leaks.
    Catalog::CatalogSectionData* NewCatalogSectionData( );


    Utils::Settings* GetSettings( ) { return m_settings; };
    void SetSettings( Utils::Settings* settings ) { m_settings = settings; };
    Utils::Project* GetProject( ) { return  m_project; };
    void SetProject( Utils::Project* project );

    /** ****************************************
     * @brief Get the Catalog Tree Ctrl object
     * 
     * @return CatalogTreeCtrl* 
     */
    inline CatalogTreeCtrl* GetCatalogPageTreeCtrl( ) { return m_catalogPageTreeCtrl; };
    inline CatalogTreeCtrl* GetAlbumPageTreeCtrl( ) { return m_albumPageTreeCtrl; };
    
    /** ****************************************
     * @brief Get the Design Tree Ctrl object
     * 
     * @return DesignTreeCtrl* 
     */
    inline DesignTreeCtrl* GetDesignTreeCtrl( ) { return m_designTreeCtrl; };

    /* -----------------------------------------------------------------
     * @brief Get the Description Panel object
     * 
     * @return StampDescriptionPanel* 
     */
    inline StampDescriptionPanel* GetDescriptionPanel( ) { return m_stampDescriptionPanel; };
    inline AlbumImagePanel* GetAlbumImagePanel( ) { return m_albumImagePanel; };
    void SetCatalogPageTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_catalogPageTreeCtrl = treeCtrl; };
    void SetAlbumPageTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_albumPageTreeCtrl = treeCtrl; };
    void SetDesignTreeCtrl( DesignTreeCtrl* treeCtrl ) { m_designTreeCtrl = treeCtrl; };
    void SetDescriptionPanel( StampDescriptionPanel* descriptionPanel ) { m_stampDescriptionPanel = descriptionPanel; };
    void SetAlbumImagePanel( AlbumImagePanel* albumImagePanel ) { m_albumImagePanel = albumImagePanel; };
    wxString GetImageFilename( wxString stampId );
    wxString GetImagePath( );

    void SetDirty( bool state = true ) { m_dirty = state; };
    // Is project dirty?
    bool isDirty( ) { return m_dirty; };

private:

    Utils::Settings* m_settings;
    Utils::Project* m_project;
    Utils::StampList m_StampAlbumCatalogLink;
    Catalog::CatalogData m_catalogData;
   // int m_catalogSectionDataNdx;
    Design::DesignData* m_designData;

    CatalogTreeCtrl* m_catalogPageTreeCtrl;
    CatalogTreeCtrl* m_albumPageTreeCtrl;
    DesignTreeCtrl* m_designTreeCtrl;
    AlbumImagePanel* m_albumImagePanel;
    StampDescriptionPanel* m_stampDescriptionPanel;
    bool m_dirty;
};
#endif