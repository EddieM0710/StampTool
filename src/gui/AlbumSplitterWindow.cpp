
/* 
 * @file AlbumSplitterWiindow.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-19
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
#include "wx/imaglist.h"
// includes

#include "gui/AlbumSplitterWindow.h"
// XPM images
// XPM images

#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumPanel.h"
#include "gui/AlbumImagePanel.h"
#include "gui/GeneratorData.h" 
/*
 * AlbumSplitterWindow type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AlbumSplitterWindow, wxPanel )


/*
 * AlbumSplitterWindow event table definition
 */

BEGIN_EVENT_TABLE( AlbumSplitterWindow, wxPanel )

// AlbumSplitterWindow event table entries
EVT_SLIDER( ID_ALBUMZOOMSLIDER, AlbumSplitterWindow::OnZoomsliderUpdated )
// AlbumSplitterWindow event table entries

END_EVENT_TABLE()


/*
 * AlbumSplitterWindow constructors
 */

AlbumSplitterWindow::AlbumSplitterWindow()
{
    Init();
}

AlbumSplitterWindow::AlbumSplitterWindow( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * AlbumSplitterWiindow creator
 */

bool AlbumSplitterWindow::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
// AlbumSplitterWindow creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    Centre();
// AlbumSplitterWindow creation
    return true;
}


/*
 * AlbumSplitterWindow destructor
 */

AlbumSplitterWindow::~AlbumSplitterWindow()
{
// AlbumSplitterWindow destruction
// AlbumSplitterWindow destruction
}




void AlbumSplitterWindow::Init()
{
// AlbumSplitterWindow member initialisation
    m_secondarySplitterWindow = NULL;
// AlbumSplitterWindow member initialisation
}


/*
 * Control creation for AlbumSplitterWiindow
 */

void AlbumSplitterWindow::CreateControls()
{    
// AlbumSplitterWindow content construction

    AlbumSplitterWindow* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 1, wxGROW|wxALL, 5);

    m_secondarySplitterWindow = new wxSplitterWindow( itemPanel1, ID_SECONDARYSPLITTERWINDOW, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    m_secondarySplitterWindow->SetMinimumPaneSize(0);
    m_albumPanel = new AlbumPanel( m_secondarySplitterWindow, ID_SCROLLEDWINDOW, wxDefaultPosition, wxSize(100, 100), wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL );

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

    m_secondarySplitterWindow->SplitVertically(m_albumPanel, itemPanel4, 200);

    itemBoxSizer1->Add(m_secondarySplitterWindow, 1, wxGROW|wxALL, 5);

// AlbumSplitterWindow content construction
    GetGeneratorData( )->SetAlbumImagePanel( m_albumImagePanel );
}


/*
 * Should we show tooltips?
 */

bool AlbumSplitterWindow::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AlbumSplitterWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
// AlbumSplitterWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
// AlbumSplitterWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumSplitterWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
// AlbumSplitterWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
// AlbumSplitterWindow icon retrieval
}

/*************************************************************/

void AlbumSplitterWindow::OnZoomsliderUpdated( wxCommandEvent& event )
{
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double )val / 100.0;
    m_albumImagePanel->SetZoom( zoom );

    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // DescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // DescriptionPanel.
}
