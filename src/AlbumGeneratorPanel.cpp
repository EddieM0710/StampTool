/**
 * @file AlbumGeneratorPanel.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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


#include "CatalogDataTreeCtrl.h"
#include "wx/imaglist.h"
//#include "AlbumGeneratorDialog.h"

#include "AlbumGeneratorPanel.h"

#include "ManageCatalogData.h"



/*
 * IdentificationPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AlbumGeneratorPanel, wxPanel )
; // silly business; The above macro screws up the formatter

/*
 * AlbumGeneratorPanel event table definition
 */

    BEGIN_EVENT_TABLE( AlbumGeneratorPanel, wxPanel )

    // AlbumGeneratorPanel event table entries
    EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, AlbumGeneratorPanel::OnNotebookPageChanged )
    EVT_TEXT( ID_TITLETEXTCTRL, AlbumGeneratorPanel::OnTitleTextUpdated )
    // AlbumGeneratorPanel event table entries

    END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

    /*
     * AlbumGeneratorPanel constructors
     */

    AlbumGeneratorPanel::AlbumGeneratorPanel( )
{
    Init( );
}

AlbumGeneratorPanel::AlbumGeneratorPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * AlbumGeneratorPanel creator
 */

bool AlbumGeneratorPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    // AlbumGeneratorPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    // AlbumGeneratorPanel creation
    return true;
}

/*
 * AlbumGeneratorPanel destructor
 */

AlbumGeneratorPanel::~AlbumGeneratorPanel( )
{
    // AlbumGeneratorPanel destruction
    // AlbumGeneratorPanel destruction
}

/*
 * Member initialisation
 */

void AlbumGeneratorPanel::Init( )
{
    // AlbumGeneratorPanel member initialisation

    m_notebook = NULL;
    m_sizer = NULL;
    // AlbumGeneratorPanel member initialisation
}

/*
 * Control creation for AlbumGeneratorPanel
 */

void AlbumGeneratorPanel::CreateControls( )
{
    // AlbumGeneratorPanel content construction

    AlbumGeneratorPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer2, 1, wxGROW | wxALL, 0 );

    wxSplitterWindow* itemSplitterWindow3 = new wxSplitterWindow(
        itemPanel1, ID_SPLITTERWINDOW, wxDefaultPosition, wxDefaultSize,
        wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    itemSplitterWindow3->SetMinimumPaneSize( 20 );
    itemSplitterWindow3->SetSashGravity( 0.2 );

    m_mngCatalogData = new  ManageCatalogData(  itemSplitterWindow3, ID_PANEL1, 
        wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL);
    
    m_notebook
        = new wxNotebook( itemSplitterWindow3, ID_NOTEBOOK, wxDefaultPosition,
            wxDefaultSize, wxBK_DEFAULT );

    m_albumSplitterWindow = new AlbumSplitterWindow(
        m_notebook, ID_ALBUMSPLITTERWINDOWFOREIGN, wxDefaultPosition,
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_albumSplitterWindow->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    m_notebook->AddPage( m_albumSplitterWindow, _( "Album" ) );
  
    itemSplitterWindow3->SplitVertically( m_mngCatalogData, m_notebook, 100 );
    itemBoxSizer2->Add( itemSplitterWindow3, 1, wxGROW | wxALL, 0 );

    // AlbumGeneratorPanel content construction
 }

/*
 * Should we show tooltips?
 */

bool AlbumGeneratorPanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AlbumGeneratorPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
     // AlbumGeneratorPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // AlbumGeneratorPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumGeneratorPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
     // AlbumGeneratorPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // AlbumGeneratorPanel icon retrieval
}
void AlbumGeneratorPanel::SetStamp( Stamp* stamp )
{
    m_stamp = stamp;
//    SetGallery( );
}

void AlbumGeneratorPanel::UpdateStatus( )
{
}

void AlbumGeneratorPanel::LoadAECmdTree( )
{
    m_albumSplitterWindow->LoadCmdTree( );
}

// void AlbumGeneratorPanel::ClearAECmdTree( )
// {
//     m_albumSplitterWindow->ClearCmdTree( );
// }
/*
 * wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
 */

void AlbumGeneratorPanel::OnNotebookPageChanged( wxNotebookEvent& event )
{
    // wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
   //in AlbumGeneratorPanel.
   // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
   //in AlbumGeneratorPanel.
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TITLETEXTCTRL
 */

void AlbumGeneratorPanel::OnTitleTextUpdated( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TITLETEXTCTRL in AlbumGeneratorPanel.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TITLETEXTCTRL in AlbumGeneratorPanel. 
}
