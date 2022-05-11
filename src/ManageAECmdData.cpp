/////////////////////////////////////////////////////////////////////////////
// Name:        manageaecmddata.cpp
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Sat 22 Jan 2022 13:28:32 CST
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Sat 22 Jan 2022 13:28:32 CST

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "AlbumTreeCtrl.h"
#include "wx/imaglist.h"
#include "StaticItem.h"
////@end includes

#include "ManageAECmdData.h"
#include "ReadAlbumEasyFile.h"
#include "AECmdData.h"
////@begin XPM images
////@end XPM images


/*
 * ManageAECmdData type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ManageAECmdData, wxPanel )


/*
 * ManageAECmdData event table definition
 */

    BEGIN_EVENT_TABLE( ManageAECmdData, wxPanel )

    ////@begin ManageAECmdData event table entries
    ////@end ManageAECmdData event table entries

    END_EVENT_TABLE( )


    /*
     * ManageAECmdData constructors
     */

    ManageAECmdData::ManageAECmdData( )
{
    Init( );
}

ManageAECmdData::ManageAECmdData( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}


/*
 * ManageAECmdData creator
 */

bool ManageAECmdData::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    ////@begin ManageAECmdData creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    ////@end ManageAECmdData creation
    return true;
}


/*
 * ManageAECmdData destructor
 */

ManageAECmdData::~ManageAECmdData( )
{
    ////@begin ManageAECmdData destruction
    ////@end ManageAECmdData destruction
}


/*
 * Member initialisation
 */

void ManageAECmdData::Init( )
{
    ////@begin ManageAECmdData member initialisation
    m_aeCmdTreeCtrl = NULL;
    m_CmdDataTextCtrl = NULL;
    ////@end ManageAECmdData member initialisation
}


/*
 * Control creation for ManageAECmdData
 */

void ManageAECmdData::CreateControls( )
{
    ////@begin ManageAECmdData content construction
        // Generated by DialogBlocks, Sat 22 Jan 2022 13:42:11 CST (unregistered)

    ManageAECmdData* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    m_aeCmdTreeCtrl = new AlbumTreeCtrl( itemPanel1, ID_AECMDTREECTRL, wxDefaultPosition, wxSize( 100, 100 ), wxTR_SINGLE );
    itemBoxSizer1->Add( m_aeCmdTreeCtrl, 1, wxGROW | wxALL, 5 );

    wxScrolledWindow* itemScrolledWindow1 = new wxScrolledWindow( itemPanel1, ID_SCROLLEDWINDOW, wxDefaultPosition, wxSize( 100, 100 ), wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );
    itemBoxSizer1->Add( itemScrolledWindow1, 1, wxGROW | wxALL, 5 );
    itemScrolledWindow1->SetScrollbars( 1, 1, 0, 0 );
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemScrolledWindow1->SetSizer( itemBoxSizer2 );

    m_CmdDataTextCtrl = new StaticItem( itemScrolledWindow1, ID_CMDDATATEXTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxSIMPLE_BORDER );
    itemBoxSizer2->Add( m_CmdDataTextCtrl, 1, wxGROW | wxALL, 5 );

    itemScrolledWindow1->FitInside( );

    ////@end ManageAECmdData content construction
}


/*
 * Should we show tooltips?
 */

bool ManageAECmdData::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap ManageAECmdData::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin ManageAECmdData bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    ////@end ManageAECmdData bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon ManageAECmdData::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin ManageAECmdData icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    ////@end ManageAECmdData icon retrieval
}


void ManageAECmdData::LoadAEFile( wxString filename )
{
    ReadAlbumEasyFile* readFile = new ReadAlbumEasyFile( filename, m_AEItemArray );
    readFile->ProcessFile();
    m_aeCmdTreeCtrl->DeleteAllItems( );
    m_aeCmdTreeCtrl->LoadTree( );
}

void ManageAECmdData::LoadAEData( wxString filename )
{
    GetAECmdData( )->LoadXML( filename );
    m_aeCmdTreeCtrl->DeleteAllItems( );
    m_aeCmdTreeCtrl->LoadTree( );
}