/**
 * @file AlbumData.h
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

#ifndef AlbumData_h
#define AlbumData_h

#include "utils/StampList.h"
#include "utils/FontList.h"
#include "design/AlbumList.h"

namespace Design {
    class AlbumVolume;
};
namespace Design {
    class AlbumList;
};

class AlbumPanel;
class AlbumTreeCtrl;
class AlbumImagePanel;


namespace Design {
    // Links to all the data and controls needed for Album design
    class AlbumData
    {
    public:

        // AlbumData( ) { };

         ///  @brief Construct a new Album Data object
         ///  
         ///  @param AppData 
        AlbumData( ) { };

        ///  @brief Destroy the Album Data object
        ///  
        ~AlbumData( ) { };

        ///  @brief Get the Album Image Panel object
        ///  
        ///  @return AlbumImagePanel* 
        inline AlbumImagePanel* GetAlbumImagePanel( ) {
            return m_albumImagePanel;
        };

        ///  @brief Open an Album file named filename
        ///  
        ///  @param filename 
        void FileOpen( wxString filename );

        ///  @brief Save the Album File
        ///  
        void FileSave( );

        ///  @brief 
        ///  
        ///  @param filename 
        void FileSaveAs( wxString filename );

        ///  @brief Get the Album List object
        ///  
        ///  @return Design::AlbumList& 
        inline Design::AlbumList& GetAlbumList( ) {
            return m_albumList;
        };

        inline AlbumTOCTreeCtrl* GetAlbumTOCTreeCtrl( ) {
            return m_albumTocTreeCtrl;
        };

        ///  @brief Get the Album Volume object
        ///  
        ///  @return Album::AlbumVolume* 
        AlbumVolume* GetAlbumVolume( );

        ///  @brief Get the Design Tree Ctrl object
        ///  
        ///  @return AlbumTreeCtrl* 
        inline AlbumTreeCtrl* GetAlbumTreeCtrl( ) {
            return m_albumTreeCtrl;
        };

        ///  @brief Get the Font List object
        ///  
        ///  @return Utils::FontList* 
        Utils::FontList* GetFontList( ) {
            return &m_fontList;
        };

        ///  @brief Get the Volume Name Strings object
        ///  
        ///  @return wxArrayString& 
        // wxArrayString& GetVolumeNameStrings( )
        // {
        //     return m_albumList.GetVolumeNameStrings( );
        // }

        ///  @brief 
        ///  
        void InitAlbumData( );

        ///  @brief 
        ///  
        void LoadData( );

        ///  @brief 
        ///  
        void LoadDefaultAlbumVolume( );

        ///  @brief 
        ///  
        void LoadDesignVolumeFiles( );

        ///  @brief 
        ///  
        void LoadDesignTree( );

        /**
         * @brief Load a new unnamed Design with default data
         *
         */
        void LoadNew( wxString designFileName );

        /**
         * @brief Create a new empty AlbumVolume instance and clear tree
         *
         */
        Design::AlbumVolume* NewAlbumVolume( void );

        ///  @brief 
        ///  
        void NewDesign( );

        ///  @brief 
        ///  
        void OpenDesign( );

        void SetAlbumPanel( AlbumPanel* albumPanel ) {
            m_albumPanel = albumPanel;
        };

        AlbumPanel* GetAlbumPanel( ) {
            return m_albumPanel;
        };

        ///  @brief Set the Album Image Panel object
        ///  
        ///  @param albumImagePanel 
        void SetAlbumImagePanel( AlbumImagePanel* albumImagePanel ) {
            m_albumImagePanel = albumImagePanel;
        };

        ///  @brief Set the Design Tree Ctrl object
        ///  
        ///  @param treeCtrl 
        void SetAlbumTreeCtrl( AlbumTreeCtrl* treeCtrl ) {
            m_albumTreeCtrl = treeCtrl;
        };

        void SetAlbumTOCTreeCtrl( AlbumTOCTreeCtrl* treeCtrl ) {
            m_albumTocTreeCtrl = treeCtrl;
        };

        //void UpdateAlbumVolumeStrings( );

    private:
        AlbumPanel* m_albumPanel;

        AlbumImagePanel* m_albumImagePanel;

        Utils::FontList m_fontList;

        Design::AlbumList m_albumList;

        AlbumTreeCtrl* m_albumTreeCtrl;

        AlbumTOCTreeCtrl* m_albumTocTreeCtrl;
    };
}
#endif