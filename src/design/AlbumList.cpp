/**
 * @file AlbumList.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/filename.h>


#include "design/AlbumList.h"
#include "design/AlbumData.h"
#include "gui/AlbumPanel.h"
#include "utils/Project.h"
#include "gui/StampToolFrame.h"
#include "gui/AlbumTOCTreeCtrl.h"

#include "Defs.h"

 //#include "StampToolApp.h"

 ///wxDECLARE_APP( StampToolApp );

namespace Design {



    Design::AlbumVolume* AlbumList::NewVolumeInstance( wxString filename )
    {
        Design::AlbumVolume* albumVolume = new Design::AlbumVolume( );
        SetCurrentVolume( albumVolume );
        albumVolume->SetFilename( filename );
        return albumVolume;
    }


    Design::AlbumVolume* AlbumList::AddNewVolume( wxString filename )
    {

        // make the volume
        Design::AlbumVolume* vol = NewVolumeInstance( filename );

        wxFileName albumFile( filename );
        wxString volName = albumFile.GetName( );
        vol->LoadDefaultDocument( volName );

        // Add it to the ProjectList
        wxXmlNode* newNode = GetProject( )->AddNewAlbumVolume( filename, volName );

        // Add it to the catalog List
        Insert( volName, vol );

        // Add it to the tree
        wxTreeItemId treeRootID = GetAlbumTOCTreeCtrl( )->GetRootItem( );
        GetAlbumTOCTreeCtrl( )->AddChild( treeRootID, newNode, GetAlbumTOCTreeCtrl( )->GetMenu( ) );

        return vol;
    }


}