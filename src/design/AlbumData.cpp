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
 **************************************************/

#include "gui/DesignTreeCtrl.h"
 //#include "gui/FileCreateDialog.h"

#include "utils/Settings.h"
#include "utils/Project.h"

#include "design/AlbumVolume.h"

#include "design/AlbumData.h"
namespace Design {

    AlbumData::AlbumData( ToolData* toolData )
    {
        //       m_toolData = toolData;
    };


    Design::AlbumVolume* AlbumData::GetAlbumVolume( )
    {
        return m_albumList.GetAlbumVolume( );
    }

    Design::AlbumVolume* AlbumData::NewAlbumVolume( void )
    {

        m_designTreeCtrl->DeleteAllItems( );
        GetToolData( )->GetStampAlbumCatalogLink( )->Clear( );

        return m_albumList.NewAlbumVolume( );
    }

    void AlbumData::FileOpen( wxString filename )
    {
        GetProject( )->SetDesignFilename( filename );
        LoadDesignVolumeFiles( );
        LoadDesignTree( );
    }
    void AlbumData::LoadDesignVolumeFiles( )
    {
        m_albumList.LoadAlbums( );

        //    NewAlbumVolume( );
        //    //wxString albumFilename = m_project->GetDesignFilename( );
        //    m_albumVolume->LoadXML( );
    }


    void AlbumData::LoadDesignTree( )
    {
        GetDesignTreeCtrl( )->LoadTree( );
    }

    void AlbumData::LoadDefaultAlbumVolume( )
    {
        //m_albumList.LoadAlbums( );
        GetAlbumVolume( )->LoadDefaultDocument( );
    }

    void AlbumData::LoadNew( wxString designFileName )
    {
        GetProject( )->SetDesignFilename( designFileName );

        LoadDefaultAlbumVolume( );
        LoadDesignTree( );
        SetDirty( false );
    }

    void AlbumData::FileSave( )
    {
        Design::AlbumVolume* volume = m_albumList.GetAlbumVolume( );
        if ( volume )
        {
            //m_albumVolume->SaveXML( GetProject( )->GetDesignFilename( ) );
            volume->SaveXML( );
        }
    };

    void AlbumData::FileSaveAs( wxString filename )
    {
        GetProject( )->SetDesignFilename( filename );
        FileSave( );
    };


    // Load the Catalog and Design data then populate trees
    void AlbumData::LoadData( )
    {
        LoadDesignVolumeFiles( );
        LoadDesignTree( );
    }

}