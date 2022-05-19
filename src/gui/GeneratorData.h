/**
 * @file GeneratorData.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef GeneratorData_h
#define GeneratorData_h

#include "utils/StampList.h"

namespace ODT { class Document; };
namespace Design { class DesignData; };
namespace Catalog { class CatalogData; };
namespace Utils { class Project; };
namespace Utils { class Settings; };

class CatalogTreeCtrl;
class DesignTreeCtrl;
class DescriptionPanel;
class AlbumImagePanel;

GeneratorData* NewGeneratorDataInstance( );

// Links to all the data and controls needed for Album design
class GeneratorData
{
public:
    GeneratorData( );
    ~GeneratorData( ) {};
    void InitGeneratorData( );

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
    void LoadCatalogXML( wxString catalogFilename );

    inline Design::DesignData* GetDesignData( ) { return m_designData; };

    Design::DesignData* FileOpenDesign( wxString filename );

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
    void LoadNewDesign( );

    inline Catalog::CatalogData* GetCatalogData( ) { return m_catalogData; };

    /** ****************************************
     * @brief Load the catalog data from xml file
     * 
     */
    void ReadCatalogFile( );

    //Load a csv catalog.
    void ReadCatalogCSV( wxString csvFilename );

    //Load the xml data into the tree
     void LoadCatalogTree( );

    //Load a new unnamed empty catalog 
    void LoadNewCatalog( );

    //Load the Catalog and Design data and trees
    void LoadData( );

    // Load a new Project
    void FileNewProject();

    /** ****************************************
     * @brief Read the project file and load the Catalog and Design
     * 
     * @param filename 
     */
    void FileOpenProject(wxString filename);

    // @brief Perform File-Save for Project
    void FileSaveProject( );

    // @brief Perform File-SaveAs for Project
    void FileSaveAsProject( wxString filename );

    void InitODTDocument( );

    // Load last Project file at startup if enabled
    void InitLoad( );

    // Creates a new CatalogData. Deletes current one to prevent memory leaks.
    Catalog::CatalogData* NewCatalogData( );

    /**
     *
     * @brief
     *
     * @return ODT::Document*
     */
    ODT::Document* GetODTDocument( );


    void SetODTDocument( ODT::Document* doc );


    Utils::Settings* GetSettings( ) { return m_settings; };
    void SetSettings( Utils::Settings* settings ) { m_settings = settings; };
    Utils::Project* GetProject( ) { return  m_project; };
    void SetProject( Utils::Project* project );

    /** ****************************************
     * @brief Get the Catalog Tree Ctrl object
     * 
     * @return CatalogTreeCtrl* 
     */
    inline CatalogTreeCtrl* GetCatalogTreeCtrl( ) { return m_catalogTreeCtrl; };
    
    /** ****************************************
     * @brief Get the Design Tree Ctrl object
     * 
     * @return DesignTreeCtrl* 
     */
    inline DesignTreeCtrl* GetDesignTreeCtrl( ) { return m_designTreeCtrl; };

    /* -----------------------------------------------------------------
     * @brief Get the Description Panel object
     * 
     * @return DescriptionPanel* 
     */
    inline DescriptionPanel* GetDescriptionPanel( ) { return m_descriptionPanel; };
    inline AlbumImagePanel* GetAlbumImagePanel( ) { return m_albumImagePanel; };
    void SetCatalogTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_catalogTreeCtrl = treeCtrl; };
    void SetDesignTreeCtrl( DesignTreeCtrl* treeCtrl ) { m_designTreeCtrl = treeCtrl; };
    void SetDescriptionPanel( DescriptionPanel* descriptionPanel ) { m_descriptionPanel = descriptionPanel; };
    void SetAlbumImagePanel( AlbumImagePanel* albumImagePanel ) { m_albumImagePanel = albumImagePanel; };

    void SetDirty( bool state = true ) { m_dirty = state; };
    // Is project dirty?
    bool isDirty( ) { return m_dirty; };

private:

    Utils::Settings* m_settings;
    Utils::Project* m_project;
    Utils::StampList m_StampAlbumCatalogLink;
    Catalog::CatalogData* m_catalogData;
    Design::DesignData* m_designData;
    ODT::Document* m_ODTDoc;

    CatalogTreeCtrl* m_catalogTreeCtrl;
    DesignTreeCtrl* m_designTreeCtrl;
    AlbumImagePanel* m_albumImagePanel;
    DescriptionPanel* m_descriptionPanel;
    bool m_dirty;
};
#endif