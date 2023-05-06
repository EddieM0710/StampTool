/**
 * @file AlbumData.cpp
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
#include "Defs.h"
#include "gui/AlbumTreeCtrl.h"
 //#include "gui/FileCreateDialog.h"

#include "utils/Settings.h"
#include "utils/Project.h"
#include "gui/StampToolFrame.h"

#include "design/AlbumVolume.h"

#include "design/AlbumData.h"

namespace Design {


    void AlbumData::FileOpen( wxString filename )
    {
        GetProject( )->SetDesignFilename( filename );
        LoadDesignVolumeFiles( );
        LoadDesignTree( );
    }

    void AlbumData::FileSave( )
    {
        Design::AlbumVolume* volume = m_albumList.GetAlbumVolume( );
        if ( volume )
        {
            volume->SaveXML( );
        }
    };

    void AlbumData::FileSaveAs( wxString filename )
    {
        GetProject( )->SetDesignFilename( filename );
        FileSave( );
    };

    Design::AlbumVolume* AlbumData::GetAlbumVolume( )
    {
        return m_albumList.GetAlbumVolume( );
    }

    /// Load the Catalog and Design data then populate trees
    void AlbumData::LoadData( )
    {
        LoadDesignVolumeFiles( );
        LoadDesignTree( );
    }

    void AlbumData::LoadDefaultAlbumVolume( )
    {
        GetAlbumVolume( )->LoadDefaultDocument( );
    }

    void AlbumData::LoadDesignTree( )
    {
        GetAlbumTreeCtrl( )->LoadTree( );
    }

    void AlbumData::LoadDesignVolumeFiles( )
    {
        m_albumList.LoadAlbums( );

    }

    void AlbumData::LoadNew( wxString designFileName )
    {
        GetProject( )->SetDesignFilename( designFileName );

        LoadDefaultAlbumVolume( );
        LoadDesignTree( );
        SetDirty( false );
    }

    Design::AlbumVolume* AlbumData::NewAlbumVolume( void )
    {

        m_albumTreeCtrl->DeleteAllItems( );
        GetStampAlbumCatalogLink( )->Clear( );

        return m_albumList.NewAlbumVolume( );
    }

}