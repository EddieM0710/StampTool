/**
 * @file AlbumTOCTreeCtrl.cpp
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
 */

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/log.h"
#include "wx/wx.h"
#endif

#include <iostream>

#include "wx/artprov.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/math.h"
#include "wx/menu.h"
#include "wx/renderer.h"
#include "wx/wupdlock.h"
#include <wx/clipbrd.h>
#include <wx/filename.h>

#include "Defs.h"

#include "utils/Project.h"
#include "utils/XMLUtilities.h"


#include "design/AlbumData.h"
#include "collection/CollectionList.h"
#include "gui/GuiDefs.h"
#include "gui/StampToolFrame.h"
#include "gui/StampToolPanel.h"
#include "gui/AlbumTOCTreeCtrl.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumTreePanel.h"
#include "gui/AlbumPanel.h"


 //wxDECLARE_APP( StampToolApp );

wxIMPLEMENT_CLASS( AlbumTOCTreeCtrl, TOCTreeCtrl );

wxBEGIN_EVENT_TABLE( AlbumTOCTreeCtrl, TOCTreeCtrl )

//EVT_TREE_BEGIN_DRAG( ID_AlbumTOCTreeCtrl, AlbumTOCTreeCtrl::OnBeginDrag )
//EVT_TREE_END_DRAG( ID_AlbumTOCTreeCtrl, AlbumTOCTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_AlbumTOCTreeCtrl, AlbumTOCTreeCtrl::OnSelChanged )
//EVT_TREE_ITEM_MENU( ID_AlbumTOCTreeCtrl, AlbumTOCTreeCtrl::OnItemMenu )
//EVT_TREE_ITEM_COLLAPSED( ID_AlbumTOCTreeCtrl, AlbumTOCTreeCtrl::OnTreectrlItemCollapsed )
//EVT_TREE_ITEM_EXPANDED( ID_AlbumTOCTreeCtrl, AlbumTOCTreeCtrl::OnTreectrlItemExpanded )
wxEND_EVENT_TABLE( )

//--------------

AlbumTOCTreeCtrl::AlbumTOCTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : TOCTreeCtrl( parent, id, pos, size, style )
{
    //   m_reverseSort = false;

   //    CreateImageList( );
}

wxXmlNode* AlbumTOCTreeCtrl::GetCurrVolumeRoot( )
{
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( GetCurrentTreeID( ) );
    Utils::TOCBaseType type = data->GetType( );
    if ( type == Utils::TOC_Volume )
    {
        Design::AlbumVolume* vol = ( Design::AlbumVolume* ) data->GetVolume( );
        wxXmlNode* xmlNode = vol->GetDoc( )->GetRoot( );
        return xmlNode;
    }
    return ( wxXmlNode* ) 0;
}

void AlbumTOCTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( itemId );
    Utils::TOCBaseType type = data->GetType( );
    if ( type == Utils::TOC_Volume )
    {
        SetCurrentTreeID( itemId );
        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( itemId );
        wxString name = GetItemText( itemId );
        GetAlbumData( )->GetAlbumPanel( )->GetAlbumTreePanel( )->GetAlbumListCtrl( )->SetValue( name );

        GetAlbumData( )->GetAlbumList( ).SetCurrentVolume( ( Design::AlbumVolume* ) data->GetVolume( ) );

        GetAlbumData( )->GetAlbumTreeCtrl( )->LoadTree( );
        GetAlbumData( )->GetAlbumPanel( )->GetAlbumTreePanel( )->SetNotebookPage( 1 );
        //   GetAlbumData( )->SetCurrentStamp( xmlNode );
    }

    event.Skip( );
}


void  AlbumTOCTreeCtrl::LinkMenuItemToTreeItem( int id, wxTreeItemId treeId )
{
    GetAlbumData( )->GetAlbumList( ).Insert( id, treeId );
}



void AlbumTOCTreeCtrl::EditDetailsDialog( TOCTreeCtrl* parent ){
    // GetAlbumVolume( )->EditDetailsDialog( parent );
}


VolumePtr AlbumTOCTreeCtrl::FindVolume( wxString str ){
    return ( VolumePtr ) GetAlbumData( )->GetAlbumList( ).FindVolume( str );
};

wxString AlbumTOCTreeCtrl::GetVolumeName( VolumePtr volume ) {
    return ( ( Design::AlbumVolume* ) volume )->GetName( );
};

void AlbumTOCTreeCtrl::LoadTree( )
{
    // TOCNode is the project xml node where the Album list starts.
    wxXmlNode* TOCNode = GetProject( )->GetAlbumListNode( );
    TOCTreeCtrl::LoadTree( TOCNode, "AlbumList" );
}
