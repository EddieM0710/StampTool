/**
 * @file AlbumGenPanel.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
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
 *
 **************************************************/


 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "wx/imaglist.h"
//#include "AlbumGenDialog.h"

#include "gui/AlbumGenPanel.h"

#include "gui/CatalogPanel.h"

#include "gui/StampDescriptionPanel.h"
#include "gui/GenerateList.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/GuiUtils.h"
/*
 * IdentificationPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AlbumGenPanel, wxPanel )
; // silly business; The above macro screws up the formatter

/*
 * AlbumGenPanel event table definition
 */

BEGIN_EVENT_TABLE( AlbumGenPanel, wxPanel )

// AlbumGenPanel event table entries
EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, AlbumGenPanel::OnNotebookPageChanged )
EVT_TEXT( ID_TITLETEXTCTRL, AlbumGenPanel::OnTitleTextUpdated )
// AlbumGenPanel event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

    /*
     * AlbumGenPanel constructors
     */

AlbumGenPanel::AlbumGenPanel( )
{
    Init( );
}

AlbumGenPanel::AlbumGenPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * AlbumGenPanel creator
 */

bool AlbumGenPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    // AlbumGenPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    // AlbumGenPanel creation
    return true;
}

/*
 * AlbumGenPanel destructor
 */

AlbumGenPanel::~AlbumGenPanel( )
{
    // AlbumGenPanel destruction
    // AlbumGenPanel destruction
}

/*
 * Member initialisation
 */

void AlbumGenPanel::Init( )
{
    // AlbumGenPanel member initialisation

    m_notebook = NULL;
    m_sizer = NULL;
    // AlbumGenPanel member initialisation
}

/*
 * Control creation for AlbumGenPanel
 */

void AlbumGenPanel::CreateControls( )
{
    // AlbumGenPanel content construction

    AlbumGenPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer2, 1, wxGROW | wxALL, 0 );

    wxSplitterWindow* itemSplitterWindow3 = new wxSplitterWindow(
        itemPanel1, ID_SPLITTERWINDOW, wxDefaultPosition, wxDefaultSize,
        wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    itemSplitterWindow3->SetMinimumPaneSize( 20 );


    m_mngCatalogVolumeData = new  CatalogPanel( itemSplitterWindow3, ID_PANEL1,
        wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_notebook
        = new wxNotebook( itemSplitterWindow3, ID_NOTEBOOK, wxDefaultPosition,
            wxDefaultSize, wxBK_DEFAULT );

    m_stampDescriptionPanel = new StampDescriptionPanel(
        m_notebook, ID_DESCRIPTIONPANELFOREIGN, wxDefaultPosition,
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_stampDescriptionPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    m_notebook->AddPage( m_stampDescriptionPanel, _( "Stamp" ) );
    itemSplitterWindow3->SplitVertically( m_mngCatalogVolumeData, m_notebook, 600 );
    itemBoxSizer2->Add( itemSplitterWindow3, 1, wxGROW | wxALL, 0 );

    m_albumDesignPanel = new AlbumDesignPanel(
        m_notebook, ID_ALBUMSPLITTERWINDOWFOREIGN, wxDefaultPosition,
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_albumDesignPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    m_notebook->AddPage( m_albumDesignPanel, _( "Album" ) );

    m_generateListPanel = new GenerateList( m_notebook, ID_GENERTELISTFOREIGN, wxDefaultPosition,
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL  );

    m_notebook->AddPage( m_generateListPanel, _( "List" ) );

    // AlbumGenPanel content construction

    GetGeneratorData( )->SetDescriptionPanel( m_stampDescriptionPanel );

}

/*
 * Should we show tooltips?
 */

bool AlbumGenPanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AlbumGenPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
     // AlbumGenPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // AlbumGenPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumGenPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
     // AlbumGenPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // AlbumGenPanel icon retrieval
}


void AlbumGenPanel::UpdateStatus( )
{
    m_stampDescriptionPanel->UpdateStatus();
}

bool AlbumGenPanel::ShouldShowStates()
{

    if ( m_notebook->GetPage( m_notebook->GetSelection() ) == m_albumDesignPanel )
    {
        return true;
    }
    return false;
}
/*
 * wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
 */

void AlbumGenPanel::OnNotebookPageChanged( wxNotebookEvent& event )
{
    // int sel = event.GetOldSelection( );
    // event.GetSelection();
    
    // wxWindow* oldPage = m_notebook->GetPage( sel );
    if ( ShouldShowStates() )
    {
        GetCatalogTreeCtrl( )->SetStates( true );
    }
    else
    {
        GetCatalogTreeCtrl( )->SetStates( false );
    }

    // wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
   //in AlbumGenPanel.
   // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
   //in AlbumGenPanel.
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TITLETEXTCTRL
 */

void AlbumGenPanel::OnTitleTextUpdated( wxCommandEvent& event )
{
    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TITLETEXTCTRL in AlbumGenPanel.
        // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TITLETEXTCTRL in AlbumGenPanel. 
}
