/**
 * @file StampToolPanel.cpp
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
 *
 **************************************************/


 
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "wx/imaglist.h"
//#include "StampToolDialog.h"

#include "gui/StampToolPanel.h"

#include "gui/CatalogPanel.h"

#include "gui/StampDescriptionPanel.h"
#include "gui/GenerateList.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/GuiUtils.h"
/*
 * IdentificationPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( StampToolPanel, wxPanel )
; // silly business; The above macro screws up the formatter

/*
 * StampToolPanel event table definition
 */

BEGIN_EVENT_TABLE( StampToolPanel, wxPanel )

// StampToolPanel event table entries
EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, StampToolPanel::OnNotebookPageChanged )
EVT_TEXT( ID_TITLETEXTCTRL, StampToolPanel::OnTitleTextUpdated )
// StampToolPanel event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

    /*
     * StampToolPanel constructors
     */

StampToolPanel::StampToolPanel( )
{ 
    Init( );
}

StampToolPanel::StampToolPanel( wxWindow* parent, wxWindowID id, 
    const wxPoint& pos, const wxSize& size, 
    long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * StampToolPanel creator
 */

bool StampToolPanel::Create( wxWindow* parent, wxWindowID id, 
    const wxPoint& pos, const wxSize& size, 
    long style )
{ 
    // StampToolPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    // StampToolPanel creation
    return true;
}

/*
 * StampToolPanel destructor
 */

StampToolPanel::~StampToolPanel( )
{ 
    // StampToolPanel destruction
    // StampToolPanel destruction
}

/*
 * Member initialisation
 */

void StampToolPanel::Init( )
{ 
    // StampToolPanel member initialisation

    m_notebook = NULL;
    m_sizer = NULL;
    // StampToolPanel member initialisation
}

/*
 * Control creation for StampToolPanel
 */

void StampToolPanel::CreateControls( )
{ 
    // StampToolPanel content construction

    StampToolPanel* itemPanel1 = this;

    wxBoxSizer* panelVerticalBoxSizer = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( panelVerticalBoxSizer );

    wxBoxSizer* panelHorizontalBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    panelVerticalBoxSizer->Add( panelHorizontalBoxSizer, 1, wxGROW | wxALL, 0 );

    m_notebook
        = new wxNotebook( itemPanel1, ID_NOTEBOOK, wxDefaultPosition, 
            wxDefaultSize, wxBK_DEFAULT );

    panelHorizontalBoxSizer->Add( m_notebook, 1, wxGROW | wxALL, 0 );

    m_catalogNotebookPage = new wxSplitterWindow( 
        m_notebook, ID_CATALOGSPLITTERWINDOW, wxDefaultPosition, wxDefaultSize, 
        wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    m_catalogNotebookPage->SetMinimumPaneSize( 20 );

    m_catalogTreePanel = new CatalogPanel( m_catalogNotebookPage, ID_CATALOGPAGE, 
        wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    
        GetToolData( )->SetCatalogPageTreeCtrl( m_catalogTreePanel->GetCatalogTree() );
        m_catalogTreePanel->GetCatalogTree()->SetStates( false );

    m_stampDescriptionPanel = new StampDescriptionPanel( 
        m_catalogNotebookPage, ID_DESCRIPTIONPANELFOREIGN, wxDefaultPosition, 
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_stampDescriptionPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    m_catalogNotebookPage->SplitVertically( m_catalogTreePanel, m_stampDescriptionPanel, 600 );
 //   panelHorizontalBoxSizer->Add( catalogSplitterWindow, 1, wxGROW | wxALL, 0 );

    m_notebook->AddPage( m_catalogNotebookPage, _( "Catalog" ) );


    m_albumNotebookPage = new wxSplitterWindow( 
        m_notebook, ID_DESIGNSPLITTERWINDOW, wxDefaultPosition, wxDefaultSize, 
        wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    m_albumNotebookPage->SetMinimumPaneSize( 20 );

    m_albumTreePanel = new  CatalogPanel( m_albumNotebookPage, ID_DESIGNPAGE, 
        wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
        GetToolData( )->SetAlbumPageTreeCtrl( m_albumTreePanel->GetCatalogTree() );
        m_albumTreePanel->GetCatalogTree()->SetStates( true );

    m_albumDesignPanel = new AlbumDesignPanel( 
        m_albumNotebookPage, ID_ALBUMSPLITTERWINDOWFOREIGN, wxDefaultPosition, 
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_albumDesignPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    m_albumNotebookPage->SplitVertically( m_albumTreePanel, m_albumDesignPanel, 600 );

    m_notebook->AddPage( m_albumNotebookPage, _( "Album" ) );

    m_generateListPanel = new GenerateList( m_notebook, ID_GENERTELISTFOREIGN, wxDefaultPosition, 
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL  );

    m_notebook->AddPage( m_generateListPanel, _( "List" ) );

    // StampToolPanel content construction

    GetToolData( )->SetDescriptionPanel( m_stampDescriptionPanel );

}



bool StampToolPanel::ShowToolTips( )
{ 
    return true;
}


void StampToolPanel::UpdateStatus( )
{ 
    m_stampDescriptionPanel->UpdateStatus( );
}

bool StampToolPanel::ShouldShowStates( )
{ 

    if ( m_notebook->GetPage( m_notebook->GetSelection( ) ) == m_albumNotebookPage )
    {    
        return true;
    }
    return false;
}
/*
 *  COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
 */

void StampToolPanel::OnNotebookPageChanged( wxNotebookEvent& event )
{ 
 int sel = m_notebook->GetSelection( ) ;

wxWindow* page = m_notebook->GetPage( sel );

    if ( ShouldShowStates( ) )
    { 
        m_albumTreePanel->GetCatalogTree()->SetStates( true );
        m_albumTreePanel->GetCatalogTree()->LoadTree();
    }
    else
    { 
        m_catalogTreePanel->GetCatalogTree()->SetStates( false );
        m_catalogTreePanel->GetCatalogTree()->LoadTree();
    }
    event.Skip( );
}


/*
 *   ID_TITLETEXTCTRL
 */

void StampToolPanel::OnTitleTextUpdated( wxCommandEvent& event )
{ 
    event.Skip( );
}
