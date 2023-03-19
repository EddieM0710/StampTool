
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/imaglist.h"

#include "gui/AlbumDesignPanel.h"

#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumDesignTreePanel.h"
#include "gui/AlbumImagePanel.h"
#include "gui/ToolData.h" 



IMPLEMENT_DYNAMIC_CLASS( AlbumDesignPanel, wxPanel )


/*
 * AlbumDesignPanel event table definition
 */

BEGIN_EVENT_TABLE( AlbumDesignPanel, wxPanel )
EVT_SLIDER( ID_ALBUMZOOMSLIDER, AlbumDesignPanel::OnZoomsliderUpdated )
END_EVENT_TABLE( )


AlbumDesignPanel::AlbumDesignPanel( )
{ 
    Init( );
}

AlbumDesignPanel::AlbumDesignPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}

bool AlbumDesignPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    return true;
}

AlbumDesignPanel::~AlbumDesignPanel( )
{ 
}

void AlbumDesignPanel::Init( )
{ 
    m_secondarySplitterWindow = NULL;
}

void AlbumDesignPanel::CreateControls( )
{    
    AlbumDesignPanel* thePanel = this;

    wxBoxSizer* thePanelVerticalSizer = new wxBoxSizer( wxVERTICAL );
    thePanel->SetSizer( thePanelVerticalSizer );

    wxBoxSizer* splitterWindowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    thePanelVerticalSizer->Add( splitterWindowHorizontalSizer, 1, wxGROW | wxALL, 5 );

    m_secondarySplitterWindow = new wxSplitterWindow( thePanel, ID_SECONDARYSPLITTERWINDOW, wxDefaultPosition, wxSize( 100, 100 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    m_secondarySplitterWindow->SetMinimumPaneSize( 0 );
    m_albumDesignTreePanel = new AlbumDesignTreePanel( m_secondarySplitterWindow, ID_SCROLLEDWINDOW, wxDefaultPosition, wxSize( 100, 100 ), wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );

    wxPanel* descriptionPanel = 
        new wxPanel( m_secondarySplitterWindow, ID_STAMPDESCRIPTIONPANEL, wxDefaultPosition, 
            wxDefaultSize, wxTAB_TRAVERSAL );
    descriptionPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxVERTICAL );
    descriptionPanel->SetSizer( itemBoxSizer5 );

    wxBoxSizer* imagePanelHorizontalalSizer = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer5->Add( imagePanelHorizontalalSizer, 1, wxGROW | wxALL, 5 );
    
    wxBoxSizer* imagePanelVerticalSizer = new wxBoxSizer( wxVERTICAL );
    imagePanelHorizontalalSizer->Add( imagePanelVerticalSizer, 1, wxGROW | wxALL, 5 );
    wxBoxSizer* zoomHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    imagePanelVerticalSizer->Add( zoomHorizontalSizer, 0, wxGROW | wxALL, 0 );

    wxStaticText* zoomStatic = new wxStaticText( 
        descriptionPanel, wxID_STATIC, _( "Zoom" ), wxDefaultPosition, wxDefaultSize, 0 );
    zoomHorizontalSizer->Add( zoomStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_zoomSlider = 
        new wxSlider( descriptionPanel, ID_ALBUMZOOMSLIDER, 50, 10, 100, wxDefaultPosition, 
            wxDefaultSize, wxSL_HORIZONTAL );
    zoomHorizontalSizer->Add( m_zoomSlider, 1, wxGROW | wxALL, 0 );

    m_albumImagePanel = 
        new AlbumImagePanel( descriptionPanel, ID_ALBUMALBUMIMAGEPANEL, wxDefaultPosition, 
            wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE );
    m_albumImagePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    imagePanelVerticalSizer->Add( m_albumImagePanel, 1, wxGROW | wxALL, 0 );

    m_secondarySplitterWindow->SplitVertically( m_albumDesignTreePanel, descriptionPanel, 200 );

    splitterWindowHorizontalSizer->Add( m_secondarySplitterWindow, 1, wxGROW | wxALL, 5 );

    GetToolData( )->SetAlbumImagePanel( m_albumImagePanel );
}

bool AlbumDesignPanel::ShowToolTips( )
{ 
    return true;
}

void AlbumDesignPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{ 
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double )val / 100.0;
    m_albumImagePanel->SetZoom( zoom );

    event.Skip( );
}
