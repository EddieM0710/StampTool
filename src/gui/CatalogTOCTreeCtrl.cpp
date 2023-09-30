/**
 * @file CatalogTOCTreeCtrl.cpp
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


#include "catalog/CatalogData.h"
#include "collection/CollectionList.h"
#include "gui/GuiDefs.h"
#include "gui/StampToolFrame.h"
#include "gui/StampToolPanel.h"
#include "gui/CatalogTOCTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/CatalogPanel.h"
#include "gui/GenerateList.h"


 //wxDECLARE_APP( StampToolApp );

wxIMPLEMENT_CLASS( CatalogTOCTreeCtrl, TOCTreeCtrl );

wxBEGIN_EVENT_TABLE( CatalogTOCTreeCtrl, TOCTreeCtrl )

//EVT_TREE_BEGIN_DRAG( ID_CatalogTOCTreeCtrl, CatalogTOCTreeCtrl::OnBeginDrag )
//EVT_TREE_END_DRAG( ID_CatalogTOCTreeCtrl, CatalogTOCTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_CatalogTOCTreeCtrl, CatalogTOCTreeCtrl::OnSelChanged )
//EVT_TREE_ITEM_MENU( ID_CatalogTOCTreeCtrl, CatalogTOCTreeCtrl::OnItemMenu )
//EVT_TREE_ITEM_COLLAPSED( ID_CatalogTOCTreeCtrl, CatalogTOCTreeCtrl::OnTreectrlItemCollapsed )
//EVT_TREE_ITEM_EXPANDED( ID_CatalogTOCTreeCtrl, CatalogTOCTreeCtrl::OnTreectrlItemExpanded )
wxEND_EVENT_TABLE( )

//--------------

CatalogTOCTreeCtrl::CatalogTOCTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : TOCTreeCtrl( parent, id, pos, size, style )
{
    //   m_reverseSort = false;

   //    CreateImageList( );
}

wxXmlNode* CatalogTOCTreeCtrl::GetCurrVolumeRoot( )
{
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( GetCurrentTreeID( ) );
    Utils::TOCBaseType type = data->GetType( );
    if ( type == Utils::TOC_Volume )
    {
        Catalog::CatalogVolume* vol = ( Catalog::CatalogVolume* ) data->GetVolume( );
        if ( vol )
        {
            return vol->GetDoc( )->GetRoot( );
        }
    }
    return ( wxXmlNode* ) 0;
}

void CatalogTOCTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( itemId );
    Utils::TOCBaseType type = data->GetType( );
    if ( type == Utils::TOC_Volume )
    {
        SetCurrentTreeID( itemId );
        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( itemId );
        wxString name = GetItemText( itemId );
        GetCatalogData( )->GetCatalogTreePanel( )->GetVolumeListCtrl( )->SetValue( name );

        GetCatalogData( )->GetCatalogList( )->SetCatalogVolume( ( Catalog::CatalogVolume* ) data->GetVolume( ) );

        wxXmlNode* xmlNode = data->GetNodeElement( );

        GenerateList* generateListPanel = GetCatalogData( )->GetGenerateListPanel( );

        if ( generateListPanel == ( GenerateList* ) GetFrame( )->GetStampToolPanel( )->GetPage( ) )
        {
            generateListPanel->UpdateGrid( );
        }
        else
        {
            GetFrame( )->GetStampToolPanel( )->GetCatalogPagePanel( )->SetNotebookPage( 1 );
        }
        GetCatalogData( )->GetCatalogTreeCtrl( )->LoadTree( );
        //       GetCatalogData( )->GetCatalogTreePanel( )->SetNotebookPage( 1 );
               //   GetCatalogData( )->SetCurrentStamp( xmlNode );
    }

    event.Skip( );
}


void  CatalogTOCTreeCtrl::LinkMenuItemToTreeItem( int id, wxTreeItemId treeId )
{
    GetCatalogData( )->GetCatalogList( )->Insert( id, treeId );
}

void CatalogTOCTreeCtrl::ReSortTree( )
{

    ClearTree( );

    Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
    catalogVolume->ReSortTree( );

    LoadTree( );
}

void CatalogTOCTreeCtrl::EditDetailsDialog( TOCTreeCtrl* parent )
{
    GetCatalogVolume( )->EditDetailsDialog( parent );
}


void CatalogTOCTreeCtrl::LoadTree( )
{
    wxXmlNode* TOCNode = GetProject( )->GetCatalogListNode( );

    // first make sure all the links to the items are gone
    Utils::StampList* stampList = GetStampAlbumCatalogLink( );
    stampList->ClearCatalogLinks( );

    TOCTreeCtrl::LoadTree( TOCNode, "CatalogList" );
}
