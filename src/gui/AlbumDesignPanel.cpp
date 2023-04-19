
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
#include <wx/filedlg.h> 

#include "gui/AlbumDesignPanel.h"

#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumDesignTreePanel.h"
#include "gui/AlbumImagePanel.h"
#include "gui/ToolData.h" 
#include "gui/LabeledTextBox.h"
#include "gui/FileCreateDialog.h"
#include "Defs.h"


IMPLEMENT_DYNAMIC_CLASS( AlbumDesignPanel, wxPanel )

/*
 * AlbumDesignPanel event table definition
 */

    BEGIN_EVENT_TABLE( AlbumDesignPanel, wxPanel )
    EVT_SLIDER( ID_ALBUMZOOMSLIDER, AlbumDesignPanel::OnZoomsliderUpdated )
    EVT_BUTTON( ID_MANAGEBUTTON, AlbumDesignPanel::OnManageClick )
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

    wxBoxSizer* nameHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    thePanelVerticalSizer->Add( nameHorizontalSizer, 0, wxGROW | wxALL, 0 );

    // LabeledTextBox* m_name = new LabeledTextBox( thePanel, 12345, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    // m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    // nameHorizontalSizer->Add( m_name, 1, wxALIGN_CENTER_VERTICAL | wxALL, 0 );
    // m_name->SetLabel( "Album Name" );

    wxButton* m_manageButton = new wxButton( thePanel, ID_MANAGEBUTTON, _( "Manage" ), wxDefaultPosition, wxDefaultSize, 0 );
    nameHorizontalSizer->Add( m_manageButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    nameHorizontalSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* albumListStatic = new wxStaticText(
        thePanel, wxID_STATIC, _( "Album List" ), wxDefaultPosition, wxDefaultSize, 0 );
    nameHorizontalSizer->Add( albumListStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_albumListCtrl = new wxChoice( thePanel, ID_LISTCHOICE, wxDefaultPosition, wxSize( -1, -1 ), GetAlbumData( )->GetVolumeNameStrings( ), wxLB_HSCROLL );
    // nameHorizontalSizer->Add( m_albumListCtrl, 1, wxGROW | wxALL, 5 );
    nameHorizontalSizer->Add( m_albumListCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

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

    GetAlbumData( )->SetAlbumImagePanel( m_albumImagePanel );
}

bool AlbumDesignPanel::ShowToolTips( )
{
    return true;
}

void AlbumDesignPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double ) val / 100.0;
    m_albumImagePanel->SetZoom( zoom );

    event.Skip( );
}
void AlbumDesignPanel::OnManageClick( wxCommandEvent& event )
{

    wxMenu m_designMenu;
    m_designMenu.Append( ID_NEWDESIGN, _( "New Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_OPENDESIGN, _( "Open Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_REMOVEDESIGN, _( "Remove Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_GENERATEPDF, _( "Generate PDF Album" ), wxEmptyString, wxITEM_NORMAL );


    switch ( GetPopupMenuSelectionFromUser( m_designMenu ) )
    {
    case ID_NEWDESIGN:
    {
        break;
    }
    case ID_OPENDESIGN:
    {
        break;
    }
    case ID_REMOVEDESIGN:
    {
        break;
    }
    case ID_GENERATEPDF:
    {
        break;
    }
    }
}

