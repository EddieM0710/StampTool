/* 
 * @file GalleryPanel.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-02-21
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
// includes

#include "gui/GalleryPanel.h"

// XPM images

// XPM images


/*
 * GalleryPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( GalleryPanel, wxPanel )


/*
 * GalleryPanel event table definition
 */

BEGIN_EVENT_TABLE( GalleryPanel, wxPanel )

// GalleryPanel event table entries
// GalleryPanel event table entries

END_EVENT_TABLE( )


/*
 * GalleryPanel constructors
 */

GalleryPanel::GalleryPanel( )
{ 
    Init( );
}

GalleryPanel::GalleryPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}


/*
 * GalleryPanel creator
 */

bool GalleryPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
// GalleryPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
// GalleryPanel creation
    return true;
}


/*
 * GalleryPanel destructor
 */

GalleryPanel::~GalleryPanel( )
{ 
// GalleryPanel destruction
// GalleryPanel destruction
}


/*
 * Member initialisation
 */

void GalleryPanel::Init( )
{ 
// GalleryPanel member initialisation
    m_scrolledWindow = NULL;
    m_sizer = NULL;
// GalleryPanel member initialisation
}


/*
 * Control creation for GalleryPanel
 */

void GalleryPanel::CreateControls( )
{    
// GalleryPanel content construction

    GalleryPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer3, 1, wxGROW | wxALL, 0 );

    m_scrolledWindow = new wxScrolledWindow( itemPanel1, ID_IMAGEGALLERYSCROLLEDWINDOW, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );
    itemBoxSizer3->Add( m_scrolledWindow, 1, wxGROW | wxALL, 0 );
    m_scrolledWindow->SetScrollbars( 1, 1, 0, 0 );
    m_sizer = new wxGridSizer( 0, 5, 0, 0 );
    m_scrolledWindow->SetSizer( m_sizer );

    m_scrolledWindow->FitInside( );

// GalleryPanel content construction
}


/*
 * Should we show tooltips?
 */

bool GalleryPanel::ShowToolTips( )
{ 
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap GalleryPanel::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
// GalleryPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
// GalleryPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon GalleryPanel::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
// GalleryPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
// GalleryPanel icon retrieval
}
