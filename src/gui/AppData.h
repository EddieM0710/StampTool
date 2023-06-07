/**
 * @file AppData.h
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

#ifndef AppData_h
#define AppData_h

#include "utils/StampList.h"

namespace Design { class AlbumData; };
namespace Catalog { class CatalogData; };
namespace Inventory { class CollectionList; };
namespace Catalog { class StampMountData; };
namespace Utils { class Project; };
namespace Utils { class Settings; };

// Links to all the data and controls needed for Album design
class AppData
{
public:

    ///@brief Construct a new Tool Data object
    ///
    AppData( );

    ///@brief Destroy the Tool Data object
    ///
    ~AppData( ) { };

    void SetCaption( );

    ///  @brief Get the Album Data object
    ///  
    ///  @return * Design::AlbumData* 
    Design::AlbumData* GetAlbumData( );

    ///@brief Get the Catalog Data object
    ///
    ///@return Catalog::CatalogData* 
    Catalog::CatalogData* GetCatalogData( );

    Inventory::CollectionList* GetCollectionList( );

    Catalog::StampMountData* GetStampMountData( );

    ///@brief Get the Project object
    ///@return Utils::Project* 
    Utils::Project* GetProject( );

    ///@brief Get the Settings object
    ///@return Utils::Settings* 
    Utils::Settings* GetSettings( );

    ///  @brief Get the Stamp Album Catalog Link object
    ///  
    ///  @return Utils::StampList* 
    Utils::StampList* GetStampAlbumCatalogLink( );

    ///@brief 
    ///
    void InitAppData( );


    ///  @brief Is project dirty?
    ///  
    ///  @return true 
    ///  @return false 
    bool isDirty( ) { return m_dirty; };

    void SetDirty( bool val = true ) { m_dirty = val; };


private:

    Utils::Settings* m_settings;
    Utils::Project* m_project;
    Catalog::CatalogData* m_catalogData;
    Inventory::CollectionList* m_collectionList;
    Catalog::StampMountData* m_mountData;
    Design::AlbumData* m_albumData;
    Utils::StampList* m_StampAlbumCatalogLink;
    bool m_dirty;
};
#endif