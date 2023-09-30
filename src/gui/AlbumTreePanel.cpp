/*
 * @file AlbumTreePanel.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-22
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
#include "wx/wx.h"
#endif


#include "gui/AlbumTreeCtrl.h"
#include "wx/imaglist.h"
#include "wx/notebook.h"


#include "gui/AlbumTreePanel.h"
#include "gui/GuiDefs.h"
 //#include "gui/AppData.h"
#include "design/AlbumData.h"
#include "gui/AlbumTOCTreeCtrl.h"
 /*
  * AlbumTreePanel type definition
  */

IMPLEMENT_DYNAMIC_CLASS( AlbumTreePanel, wxPanel )

BEGIN_EVENT_TABLE( AlbumTreePanel, wxPanel )
END_EVENT_TABLE( )

//--------------

AlbumTreePanel::AlbumTreePanel( )
{
    Init( );
}

//--------------

AlbumTreePanel::AlbumTreePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//--------------

AlbumTreePanel::~AlbumTreePanel( ) { }

//--------------

bool AlbumTreePanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

//--------------

void AlbumTreePanel::CreateControls( )
{
    //    std::cout << "AlbumTreePanel" << "\n";
    AlbumTreePanel* itemPanel1 = this;

    // wxBoxSizer* topHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );

    wxBoxSizer* topVerticalSizer = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( topVerticalSizer );

    //topHorizontalSizer->Add( topVerticalSizer, 0, wxGROW | wxALL, 5 );

    wxBoxSizer* nameHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    topVerticalSizer->Add( nameHorizontalSizer, 0, wxGROW | wxALL, 5 );


    wxStaticText* albumListStatic = new wxStaticText(
        itemPanel1, wxID_STATIC, _( "Album List" ), wxDefaultPosition, wxDefaultSize, 0 );
    nameHorizontalSizer->Add( albumListStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    int ID_LISTCHOICE = 1234;
    m_albumListCtrl = new wxTextCtrl( itemPanel1, ID_LISTCHOICE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    Connect( ID_LISTCHOICE, wxEVT_CONTEXT_MENU, wxContextMenuEventHandler( AlbumTreePanel::OnContextMenu ) );//, NULL, this );

    // nameHorizontalSizer->Add( m_albumListCtrl, 1, wxGROW | wxALL, 5 );
    nameHorizontalSizer->Add( m_albumListCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    int lastID = 10;
    m_albumTreePanelNotebook = new wxNotebook( itemPanel1, ++lastID, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
    topVerticalSizer->Add( m_albumTreePanelNotebook, 1, wxGROW | wxALL, 5 );

    m_tocTreeCtrl = new AlbumTOCTreeCtrl( m_albumTreePanelNotebook, ID_AlbumTOCTreeCtrl, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxSUNKEN_BORDER | wxTR_DEFAULT_STYLE );
    m_albumTreePanelNotebook->AddPage( m_tocTreeCtrl, _( "  TOC  " ) );

    GetAlbumData( )->SetAlbumTOCTreeCtrl( m_tocTreeCtrl );

    m_albumTreeCtrl = new AlbumTreeCtrl( m_albumTreePanelNotebook, ID_ALBUMTREECTRL, wxDefaultPosition, wxSize( 100, 100 ), wxTR_HAS_BUTTONS | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxSUNKEN_BORDER | wxTR_DEFAULT_STYLE );
    m_albumTreePanelNotebook->AddPage( m_albumTreeCtrl, _( "  Layout  " ) );
    // itemBoxSizer1->Add( m_albumTreeCtrl, 1, wxGROW | wxALL, 5 );

    Layout( );
    GetAlbumData( )->SetAlbumTreeCtrl( m_albumTreeCtrl );
}

//--------------

void AlbumTreePanel::Init( )
{
    m_albumTreeCtrl = NULL;
}

//--------------

void AlbumTreePanel::LoadAlbumLayout( )
{
    m_albumTreeCtrl->LoadTree( );
}

//--------------

bool AlbumTreePanel::ShowToolTips( )
{
    return true;
}



void AlbumTreePanel::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint point = event.GetPosition( );

    point = ScreenToClient( point );
    wxMenu* menu = m_tocTreeCtrl->GetMenu( );

    //PopupMenu( menu, point.x, point.y );


    int id = GetPopupMenuSelectionFromUser( *menu, point.x, point.y );

    wxTreeItemId treeId = GetAlbumData( )->GetAlbumList( ).FindMenuID( id );
    m_tocTreeCtrl->SelectItem( treeId );

    TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( treeId );
    wxString name = m_tocTreeCtrl->GetItemText( treeId );
    m_albumListCtrl->SetValue( name );
}
