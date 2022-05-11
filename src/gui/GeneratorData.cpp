/**
 * @file GeneratorData.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "gui/GeneratorData.h" 
#include "catalog/CatalogDefs.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/Settings.h"

void GeneratorData::LoadCatalogData( wxString catalogFilename )
{
    m_catalogData = Catalog::NewCatalogData( );
    m_catalogData->LoadXML( catalogFilename );
}

Design::DesignData*  GeneratorData::NewDesignData( void )
{
    GeneratorData* genData = GetGeneratorData( );
    if ( m_designData )
    {
        delete m_designData;

        Utils::StampList* stampList = genData->GetStampAlbumCatalogLink();
        DesignTreeCtrl* designTree = genData->GetDesignTreeCtrl( );
        designTree->DeleteAllItems();
        stampList->Clear();
    }
    m_designData = new Design::DesignData();
    return m_designData;
}
void GeneratorData::LoadDesignData( wxString albumFilename )
{
    NewDesignData( ); 

    m_designData->LoadXML( albumFilename );

}

