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


#include "gui/AlbumTreePanel.h"
#include "gui/GuiDefs.h"
//#include "gui/AppData.h"
#include "design/AlbumData.h"

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
    AlbumTreePanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    m_albumTreeCtrl = new AlbumTreeCtrl( itemPanel1, ID_ALBUMTREECTRL, wxDefaultPosition, wxSize( 100, 100 ), wxTR_HAS_BUTTONS | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxSUNKEN_BORDER | wxTR_DEFAULT_STYLE );
    itemBoxSizer1->Add( m_albumTreeCtrl, 1, wxGROW | wxALL, 5 );

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

