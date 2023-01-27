
/* 
 * @file AlbumSplitterWiindow.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-19
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

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// includes
#include "wx/imaglist.h"
// includes

#include "gui/AlbumDesignPanel.h"
// XPM images
// XPM images

#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumDesignTreePanel.h"
#include "gui/AlbumImagePanel.h"
#include "gui/ToolData.h" 
/*
 * AlbumDesignPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AlbumDesignPanel, wxPanel )


/*
 * AlbumDesignPanel event table definition
 */

BEGIN_EVENT_TABLE( AlbumDesignPanel, wxPanel )

// AlbumDesignPanel event table entries
EVT_SLIDER( ID_ALBUMZOOMSLIDER, AlbumDesignPanel::OnZoomsliderUpdated )
// AlbumDesignPanel event table entries

END_EVENT_TABLE( )


/*
 * AlbumDesignPanel constructors
 */

AlbumDesignPanel::AlbumDesignPanel( )
{ 
    Init( );
}

AlbumDesignPanel::AlbumDesignPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}


/*
 * AlbumSplitterWiindow creator
 */

bool AlbumDesignPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
// AlbumDesignPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
// AlbumDesignPanel creation
    return true;
}


/*
 * AlbumDesignPanel destructor
 */

AlbumDesignPanel::~AlbumDesignPanel( )
{ 
// AlbumDesignPanel destruction
// AlbumDesignPanel destruction
}




void AlbumDesignPanel::Init( )
{ 
// AlbumDesignPanel member initialisation
    m_secondarySplitterWindow = NULL;
// AlbumDesignPanel member initialisation
}


/*
 * Control creation for AlbumSplitterWiindow
 */

void AlbumDesignPanel::CreateControls( )
{    
// AlbumDesignPanel content construction

    AlbumDesignPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 1, wxGROW | wxALL, 5 );

    m_secondarySplitterWindow = new wxSplitterWindow( itemPanel1, ID_SECONDARYSPLITTERWINDOW, wxDefaultPosition, wxSize( 100, 100 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    m_secondarySplitterWindow->SetMinimumPaneSize( 0 );
    m_albumDesignTreePanel = new AlbumDesignTreePanel( m_secondarySplitterWindow, ID_SCROLLEDWINDOW, wxDefaultPosition, wxSize( 100, 100 ), wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );

    wxPanel* itemPanel4 = 
        new wxPanel( m_secondarySplitterWindow, ID_DESCRIPTIONPANEL, wxDefaultPosition, 
            wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel4->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxVERTICAL );
    itemPanel4->SetSizer( itemBoxSizer5 );

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer5->Add( itemBoxSizer6, 1, wxGROW | wxALL, 5 );
    
    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer6->Add( itemBoxSizer7, 1, wxGROW | wxALL, 5 );
    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer7->Add( itemBoxSizer8, 0, wxGROW | wxALL, 0 );

    wxStaticText* itemStaticText9 = new wxStaticText( 
        itemPanel4, wxID_STATIC, _( "Zoom" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add( itemStaticText9, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_zoomSlider = 
        new wxSlider( itemPanel4, ID_ALBUMZOOMSLIDER, 50, 10, 100, wxDefaultPosition, 
            wxDefaultSize, wxSL_HORIZONTAL );
    itemBoxSizer8->Add( m_zoomSlider, 1, wxGROW | wxALL, 0 );

    m_albumImagePanel = 
        new AlbumImagePanel( itemPanel4, ID_ALBUMALBUMIMAGEPANEL, wxDefaultPosition, 
            wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE );
    m_albumImagePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer7->Add( m_albumImagePanel, 1, wxGROW | wxALL, 0 );

    m_secondarySplitterWindow->SplitVertically( m_albumDesignTreePanel, itemPanel4, 200 );

    itemBoxSizer1->Add( m_secondarySplitterWindow, 1, wxGROW | wxALL, 5 );

// AlbumDesignPanel content construction
    GetToolData( )->SetAlbumImagePanel( m_albumImagePanel );
}


/*
 * Should we show tooltips?
 */

bool AlbumDesignPanel::ShowToolTips( )
{ 
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AlbumDesignPanel::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
// AlbumDesignPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
// AlbumDesignPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumDesignPanel::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
// AlbumDesignPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
// AlbumDesignPanel icon retrieval
}

/*************************************************************/

void AlbumDesignPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{ 
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double )val / 100.0;
    m_albumImagePanel->SetZoom( zoom );

    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // StampDescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // StampDescriptionPanel.
}
