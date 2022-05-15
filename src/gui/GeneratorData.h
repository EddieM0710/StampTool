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



// Links to all the data and controls needed for Album design
class GeneratorData
{
public:
    GeneratorData( ) {
        m_catalogData = 0;
        m_designData = 0;
        m_catalogTreeCtrl = 0;
        m_designTreeCtrl = 0;
        m_descriptionPanel = 0;
    };
    ~GeneratorData( ) {};

    inline Utils::StampList* GetStampAlbumCatalogLink( ) { return &m_StampAlbumCatalogLink; };

    inline Catalog::CatalogData* GetCatalogData( ) { return m_catalogData; };
    void LoadCatalogData( wxString catalogFilename );

    inline Design::DesignData* GetDesignData( ) { return m_designData; };

   
        // creates a new DesignData instance and loads default data
        void LoadDefaultDesignData(  );

        //creates a new DesignData instance and loads a file
        void LoadDesignData();

        //Load the Design tree with current xml document
        void LoadDesignTree();
        
        // Load the catalog data from xml file
        void LoadCatalogData();
        
        //Load the xml datainto the tree
        void LoadCatalogTree();

        //Load the Catalog and Design data and trees
        void LoadData();

        void InitODTDocument();

        // Load last Project file at startup if enabled
        void InitLoad();

    void SetCatalogData( Catalog::CatalogData* catalogData );

    // void SetDesignData( Design::DesignData* designData )
    // {
    //     if ( designData != m_designData )
    //     {
    //         delete m_designData;
    //         m_designData = ( Design::DesignData* )0;
    //     }
    //     m_designData = designData;
    // };

    ODT::Document* GetODTDocument( );
    void SetODTDocument( ODT::Document* doc );

    Utils::Settings* GetSettings( );
    void SetSettings( Utils::Settings* settings );
    Utils::Project* GetProject( );
    void SetProject( Utils::Project* settings );

    inline CatalogTreeCtrl* GetCatalogTreeCtrl( ) { return m_catalogTreeCtrl; };
    inline DesignTreeCtrl* GetDesignTreeCtrl( ) { return m_designTreeCtrl; };
    inline DescriptionPanel* GetDescriptionPanel( ) { return m_descriptionPanel; };
    inline AlbumImagePanel* GetAlbumImagePanel( ) { return m_albumImagePanel; };
    void SetCatalogTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_catalogTreeCtrl = treeCtrl; };
    void SetDesignTreeCtrl( DesignTreeCtrl* treeCtrl ) { m_designTreeCtrl = treeCtrl; };
    void SetDescriptionPanel( DescriptionPanel* descriptionPanel ) { m_descriptionPanel = descriptionPanel; };
    void SetAlbumImagePanel( AlbumImagePanel* albumImagePanel ) { m_albumImagePanel = albumImagePanel; };
    Design::DesignData* NewDesignData( void );

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
};
#endif