/////////////////////////////////////////////////////////////////////////////
// Name:        CatalogUpdater.cpp
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Sat 17 Jun 2023 20:33:14 CDT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/imaglist.h"

#include "CatalogUpdater.h"


/*
 * CatalogUpdater type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CatalogUpdater, wxDialog )



BEGIN_EVENT_TABLE( CatalogUpdater, wxDialog )

EVT_LISTBOX( ID_LISTBOX, CatalogUpdater::OnListboxSelected )
EVT_LIST_ITEM_SELECTED( ID_LISTCTRL, CatalogUpdater::OnListctrlSelected )

END_EVENT_TABLE( )



CatalogUpdater::CatalogUpdater( )
{
    Init( );
}

CatalogUpdater::CatalogUpdater( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


bool CatalogUpdater::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}


/*
 * CatalogUpdater destructor
 */

CatalogUpdater::~CatalogUpdater( )
{

}


/*
 * Member initialisation
 */

void CatalogUpdater::Init( )
{

}


/*
 * Control creation for CatalogUpdater
 */

void CatalogUpdater::CreateControls( )
{

    CatalogUpdater* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 0, wxGROW | wxALL, 5 );

    wxPanel* itemPanel2 = new wxPanel( itemDialog1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    itemPanel2->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer1->Add( itemPanel2, 0, wxGROW | wxALL, 5 );

    wxSplitterWindow* itemSplitterWindow3 = new wxSplitterWindow( itemPanel2, ID_SPLITTERWINDOW, wxDefaultPosition, wxSize( 800, 600 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    itemSplitterWindow3->SetMinimumPaneSize( 0 );

    wxArrayString itemListBox4Strings;
    wxListBox* itemListBox4 = new wxListBox( itemSplitterWindow3, ID_LISTBOX, wxDefaultPosition, wxDefaultSize, itemListBox4Strings, wxLB_SINGLE );

    wxListCtrl* itemListCtrl5 = new wxListCtrl( itemSplitterWindow3, ID_LISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT );

    itemSplitterWindow3->SplitVertically( itemListBox4, itemListCtrl5, 300 );

}


/*
 * Should we show tooltips?
 */

bool CatalogUpdater::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap CatalogUpdater::GetBitmapResource( const wxString& name )
{
    wxUnusedVar( name );
    return wxNullBitmap;
}

/*
 * Get icon resources
 */

wxIcon CatalogUpdater::GetIconResource( const wxString& name )
{
    // Icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
}



void CatalogUpdater::OnListboxSelected( wxCommandEvent& event )
{
    event.Skip( );
}


void CatalogUpdater::OnListctrlSelected( wxListEvent& event )
{

    event.Skip( );
}

