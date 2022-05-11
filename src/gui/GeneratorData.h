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
#include "album/AlbumData.h"
#include "utils/StampList.h"

namespace Layout { class AlbumData; };
namespace Catalog { class CatalogData; };
class CatalogTreeCtrl;
class AlbumTreeCtrl;
class DescriptionPanel;

class GeneratorData
{
public:
 GeneratorData(){};
 ~GeneratorData(){};

    inline Utils::StampList& GetStampAlbumCatalogLink( ) { return m_StampAlbumCatalogLink; };

    inline Catalog::CatalogData* GetCatalogData( ) { return m_catalogData; };
    void LoadCatalogData( wxString catalogFilename );

    inline Layout::AlbumData* GetAlbumData( ) { return m_albumData; };
    void LoadAlbumData( wxString albumFilename );

    void SetCatalogData( Catalog::CatalogData* catalogData )
    {
        if ( catalogData != m_catalogData )
        {
            delete m_catalogData;
            m_catalogData = ( Catalog::CatalogData* )0;
        }
        m_catalogData = catalogData;
    };

    void SetAlbumData( Layout::AlbumData* albumData )
    {
        if ( albumData != m_albumData )
        {
            delete m_albumData;
            m_albumData = ( Layout::AlbumData* )0;
        }
        m_albumData = albumData;
    };

    inline CatalogTreeCtrl* GetCatalogTreeCtrl( ) { return m_catalogTreeCtrl; };
    inline AlbumTreeCtrl* GetAlbumTreeCtrl( ) { return m_AlbumTreeCtrl; };
    inline DescriptionPanel* GetDescriptionPanel(  ) { return m_descriptionPanel; };
    void SetCatalogTreeCtrl( CatalogTreeCtrl* treeCtrl ) { m_catalogTreeCtrl = treeCtrl; };
    void SetAlbumTreeCtrl( AlbumTreeCtrl* treeCtrl ) { m_AlbumTreeCtrl = treeCtrl; };
    void SetDescriptionPanel( DescriptionPanel* descriptionPanel ) { m_descriptionPanel = descriptionPanel; };

private:
    Utils::StampList m_StampAlbumCatalogLink;
    Catalog::CatalogData* m_catalogData;
    Layout::AlbumData* m_albumData;
    CatalogTreeCtrl* m_catalogTreeCtrl;
    AlbumTreeCtrl* m_AlbumTreeCtrl;
    DescriptionPanel* m_descriptionPanel;
};
#endif