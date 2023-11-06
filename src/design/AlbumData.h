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


        AlbumData( ) { };

        ~AlbumData( ) { };

        void Clear( );

        void FileOpen( wxString filename );

        void FileSave( );

        void FileSaveAs( wxString filename );

        inline AlbumImagePanel* GetAlbumImagePanel( ) {
            return m_albumImagePanel;
        };

        inline Design::AlbumList& GetAlbumList( ) {
            return m_albumList;
        };

        AlbumPanel* GetAlbumPanel( ) {
            return m_albumPanel;
        };

        inline AlbumTOCTreeCtrl* GetAlbumTOCTreeCtrl( ) {
            return m_albumTocTreeCtrl;
        };

        inline AlbumTreeCtrl* GetAlbumTreeCtrl( ) {
            return m_albumTreeCtrl;
        };

        AlbumVolume* GetAlbumVolume( );


        Utils::FontList* GetFontList( ) {
            return &m_fontList;
        };

        void InitAlbumData( );

        void LoadData( );

        void LoadDesignTree( );

        void LoadDesignVolumeFiles( );

        void LoadNew( wxString designFileName );

        void NewDesign( );

        void OpenDesign( );

        void SetAlbumImagePanel( AlbumImagePanel* albumImagePanel ) {
            m_albumImagePanel = albumImagePanel;
        };

        void SetAlbumPanel( AlbumPanel* albumPanel ) {
            m_albumPanel = albumPanel;
        };

        void SetAlbumTreeCtrl( AlbumTreeCtrl* treeCtrl ) {
            m_albumTreeCtrl = treeCtrl;
        };

        void SetAlbumTOCTreeCtrl( AlbumTOCTreeCtrl* treeCtrl ) {
            m_albumTocTreeCtrl = treeCtrl;
        };


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