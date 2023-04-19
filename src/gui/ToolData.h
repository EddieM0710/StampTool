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
#include "design/AlbumData.h"

namespace Design { class AlbumData; };
namespace Catalog { class CatalogData; };
namespace Utils { class Project; };
namespace Utils { class Settings; };

// Links to all the data and controls needed for Album design
class ToolData
{
public:
    ///@brief Construct a new Tool Data object
    ///
    ToolData( );

    ///@brief Destroy the Tool Data object
    ///
    ~ToolData( ) { };

    ///@brief 
    ///
    void InitToolData( );

    /// 
    ///@brief Get the Settings object
    ///
    ///@return Utils::Settings* 
    inline Utils::Settings* GetSettings( ) { return m_settings; };

    ///@brief Get the Project object
    ///
    ///@return Utils::Project* 
    inline Utils::Project* GetProject( ) { return  m_project; };

    ///@brief Get the Catalog Data object
    ///
    ///@return Catalog::CatalogData* 
    inline Catalog::CatalogData* GetCatalogData( ) { return m_catalogData; };

    ///  @brief Get the Album Data object
    ///  
    ///  @return * Design::AlbumData* 
    inline Design::AlbumData* GetAlbumData( ) { return m_albumData; };

    ///  @brief Get the Stamp Album Catalog Link object
    ///  
    ///  @return Utils::StampList* 
    inline Utils::StampList* GetStampAlbumCatalogLink( ) { return m_StampAlbumCatalogLink; };


    ///Load the Catalog and Design data and trees
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

    ///---
    ///  @brief  Perform File-SaveAs for Project
    ///  
    ///  @param filename 
    void FileSaveAsProject( wxString filename );

    void SetDirty( bool state = true ) { m_dirty = state; };
    ///---
    ///  @brief Is project dirty?
    ///  
    ///  @return true 
    ///  @return false 
    bool isDirty( ) { return m_dirty; };

private:

    Utils::Settings* m_settings;
    Utils::Project* m_project;
    Catalog::CatalogData* m_catalogData;
    Design::AlbumData* m_albumData;
    Utils::StampList* m_StampAlbumCatalogLink;
    bool m_dirty;
};
#endif