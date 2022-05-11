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

#include "Defs.h"
#include "catalog/CatalogData.h"
#include "design/DesignData.h"
#include "utils/StampList.h"

namespace Design { class DesignData; };
namespace Catalog { class CatalogData; };
class CatalogTreeCtrl;
class DesignTreeCtrl;
class DescriptionPanel;

class GeneratorData
{
public:
 GeneratorData(){
    m_catalogData = 0;
    m_designData = 0;
    m_catalogTreeCtrl = 0;
    m_DesignTreeCtrl = 0;
    m_descriptionPanel = 0;
 };
 ~GeneratorData(){};

    inline Utils::StampList* GetStampAlbumCatalogLink( ) { return &m_StampAlbumCatalogLink; };

    inline Catalog::CatalogData* GetCatalogData( ) { return m_catalogData; };
    void LoadCatalogData( wxString catalogFilename );

    inline Design::DesignData* GetDesignData( ) { return m_designData; };
    void LoadDesignData( wxString albumFilename );

    void SetCatalogData( Catalog::CatalogData* catalogData )
    {
        if ( catalogData != m_catalogData )
        {
            delete m_catalogData;
            m_catalogData = ( Catalog::CatalogData* )0;
        }
        m_catalogData = catalogData;
    };

    // void SetDesignData( Design::DesignData* designData )
    // {
    //     if ( designData != m_designData )
    //     {
    //         delete m_designData;
    //         m_designData = ( Design::DesignData* )0;
    //     }
    //     m_designData = designData;
    // };

    inline CatalogTreeCtrl* GetCatalogTreeCtrl( ) { return m_catalogTreeCtrl; };
    inline DesignTreeCtrl* GetDesignTreeCtrl( ) { return m_DesignTreeCtrl; };
    inline DescriptionPanel* GetDescriptionPanel(  ) { return m_descriptionPanel; };
    void SetCatalogTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_catalogTreeCtrl = treeCtrl; };
    void SetDesignTreeCtrl( DesignTreeCtrl* treeCtrl ) { m_DesignTreeCtrl = treeCtrl; };
    void SetDescriptionPanel( DescriptionPanel* descriptionPanel ) { m_descriptionPanel = descriptionPanel; };
    Design::DesignData*  NewDesignData( void );

private:
    Utils::StampList m_StampAlbumCatalogLink;
    Catalog::CatalogData* m_catalogData;
    Design::DesignData* m_designData;
    CatalogTreeCtrl* m_catalogTreeCtrl;
    DesignTreeCtrl* m_DesignTreeCtrl;
    DescriptionPanel* m_descriptionPanel;
};
#endif