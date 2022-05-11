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
#include "gui/DesignTreeCtrl.h"
#include "wx/imaglist.h"
#include "gui/StaticItem.h"
////@end includes

#include "gui/AlbumPanel.h"
#include "gui/GuiDefs.h"
#include "gui/GeneratorData.h"
//#include "DesignData.h"
////@begin XPM images
////@end XPM images


/*
 * AlbumPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AlbumPanel, wxPanel )


/*
 * AlbumPanel event table definition
 */

    BEGIN_EVENT_TABLE( AlbumPanel, wxPanel )

    ////@begin AlbumPanel event table entries
    ////@end AlbumPanel event table entries

    END_EVENT_TABLE( )


    /*
     * AlbumPanel constructors
     */

    AlbumPanel::AlbumPanel( )
{
    Init( );
}

AlbumPanel::AlbumPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}


/*
 * AlbumPanel creator
 */

bool AlbumPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    ////@begin AlbumPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    ////@end AlbumPanel creation
    return true;
}


/*
 * AlbumPanel destructor
 */

AlbumPanel::~AlbumPanel( )
{
    ////@begin AlbumPanel destruction
    ////@end AlbumPanel destruction
}


/*
 * Member initialisation
 */

void AlbumPanel::Init( )
{
    ////@begin AlbumPanel member initialisation
    m_designTreeCtrl = NULL;
    ////@end AlbumPanel member initialisation
}


/*
 * Control creation for AlbumPanel
 */

void AlbumPanel::CreateControls( )
{
    AlbumPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    m_designTreeCtrl = new DesignTreeCtrl( itemPanel1, ID_DESIGNTREECTRL, wxDefaultPosition, wxSize( 100, 100 ), wxTR_HAS_BUTTONS |wxTR_FULL_ROW_HIGHLIGHT|wxTR_SINGLE|wxSUNKEN_BORDER|wxTR_DEFAULT_STYLE );
    itemBoxSizer1->Add( m_designTreeCtrl, 1, wxGROW | wxALL, 5 );

 //   itemScrolledWindow1->FitInside( );

    GetGeneratorData( )->SetDesignTreeCtrl(m_designTreeCtrl);
}


/*
 * Should we show tooltips?
 */

bool AlbumPanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AlbumPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AlbumPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    ////@end AlbumPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AlbumPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    ////@end AlbumPanel icon retrieval
}

void AlbumPanel::LoadAlbumLayout( )
{
   m_designTreeCtrl->LoadTree();
}

void AlbumPanel::LoadAEData( wxString filename )
{

}