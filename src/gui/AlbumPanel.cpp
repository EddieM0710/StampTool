/* 
 * @file AlbumPanel.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2021  
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 */


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// includes
#include "gui/DesignTreeCtrl.h"
#include "wx/imaglist.h"
#include "gui/StaticItem.h"
// includes

#include "gui/AlbumPanel.h"
#include "gui/GuiDefs.h"
#include "gui/GeneratorData.h"
//#include "DesignData.h"
// XPM images
// XPM images


/*
 * AlbumPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AlbumPanel, wxPanel )


/*
 * AlbumPanel event table definition
 */

    BEGIN_EVENT_TABLE( AlbumPanel, wxPanel )

    // AlbumPanel event table entries
    // AlbumPanel event table entries

    END_EVENT_TABLE( )


    /*
     * AlbumPanel constructors
     */

    AlbumPanel::AlbumPanel( )
{
    Init( );
}

AlbumPanel::AlbumPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}


/*
 * AlbumPanel creator
 */

bool AlbumPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    // AlbumPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // AlbumPanel creation
    return true;
}


/*
 * AlbumPanel destructor
 */

AlbumPanel::~AlbumPanel( )
{
    // AlbumPanel destruction
    // AlbumPanel destruction
}


/*
 * Member initialisation
 */

void AlbumPanel::Init( )
{
    // AlbumPanel member initialisation
    m_designTreeCtrl = NULL;
    // AlbumPanel member initialisation
}


/*
 * Control creation for AlbumPanel
 */

void AlbumPanel::CreateControls( )
{
    AlbumPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    m_designTreeCtrl = new DesignTreeCtrl( itemPanel1, ID_DESIGNTREECTRL, wxDefaultPosition, wxSize( 100, 100 ), wxTR_HAS_BUTTONS |wxTR_FULL_ROW_HIGHLIGHT|wxTR_SINGLE|wxSUNKEN_BORDER|wxTR_DEFAULT_STYLE );
    itemBoxSizer1->Add( m_designTreeCtrl, 1, wxGROW | wxALL, 5 );

 //   itemScrolledWindow1->FitInside( );

    GetGeneratorData( )->SetDesignTreeCtrl(m_designTreeCtrl);
}


/*
 * Should we show tooltips?
 */

bool AlbumPanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AlbumPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
// AlbumPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // AlbumPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
// AlbumPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // AlbumPanel icon retrieval
}

void AlbumPanel::LoadAlbumLayout( )
{
   m_designTreeCtrl->LoadTree();
}

void AlbumPanel::LoadAEData( wxString filename )
{

}