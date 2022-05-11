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

void GeneratorData::LoadCatalogData( wxString catalogFilename )
{
    m_catalogData = Catalog::NewCatalogData( );
    m_catalogData->LoadXML( catalogFilename );
}
void GeneratorData::LoadAlbumData( wxString albumFilename )
{    
    m_albumData = Layout::NewAlbumData( );
    m_albumData->LoadXML( albumFilename );
}

