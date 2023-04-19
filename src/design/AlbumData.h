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
 **************************************************/

#ifndef AlbumData_h
#define AlbumData_h

#include "utils/StampList.h"
#include "utils/FontList.h"
#include "design/AlbumList.h"

namespace Design { class AlbumVolume; };
namespace Design { class AlbumList; };

class DesignTreeCtrl;
class AlbumImagePanel;

namespace Design {
    // Links to all the data and controls needed for Album design
    class AlbumData
    {
        AlbumData( ) { };

    public:
        AlbumData( ToolData* toolData );
        ~AlbumData( ) { };
        void InitAlbumData( );

        //        inline Design::AlbumVolume* GetAlbumVolume( ) { return m_albumVolume; };
        inline Design::AlbumList& GetAlbumList( ) { return m_albumList; };

        void FileOpen( wxString filename );
        void SetDesignTreeCtrl( DesignTreeCtrl* treeCtrl ) { m_designTreeCtrl = treeCtrl; };

        inline DesignTreeCtrl* GetDesignTreeCtrl( ) { return m_designTreeCtrl; };

        void LoadDefaultAlbumVolume( );

        void LoadDesignVolumeFiles( );

        void LoadDesignTree( );

        /** ************************************************
         * @brief Load a new unnamed Design with default data
         *
         */
        void LoadNew( wxString designFileName );


        void FileSaveAs( wxString filename );
        void FileSave( );

        void NewDesign( );

        void OpenDesign( );

        void LoadData( );

        wxArrayString& GetVolumeNameStrings( )
        {
            return m_albumList.GetVolumeNameStrings( );
        }

        /**
         * @brief Create a new empty AlbumVolume instance and clear tree
         *
         */
        Design::AlbumVolume* NewAlbumVolume( void );

        inline AlbumImagePanel* GetAlbumImagePanel( ) { return m_albumImagePanel; };
        void SetAlbumImagePanel( AlbumImagePanel* albumImagePanel ) { m_albumImagePanel = albumImagePanel; };

        Utils::FontList* GetFontList( ) { return &m_fontList; };

        ///  @brief Get the Album Volume object
        ///  
        ///  @return Album::AlbumVolume* 
        AlbumVolume* GetAlbumVolume( );

    private:
        //        ToolData* m_toolData;
        AlbumImagePanel* m_albumImagePanel;
        Utils::FontList m_fontList;

        //        Design::AlbumVolume* m_albumVolume;
        Design::AlbumList m_albumList;

        DesignTreeCtrl* m_designTreeCtrl;
    };
}
#endif