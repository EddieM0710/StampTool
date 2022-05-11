/////////////////////////////////////////////////////////////////////////////
// Name:        AlbumSplitterWiindow.cpp
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Wed 19 Jan 2022 14:01:07 CST
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Wed 19 Jan 2022 14:01:07 CST

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "gui/AlbumSplitterWindow.h"
////@begin XPM images
////@end XPM images

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

////@begin AlbumSplitterWindow event table entries
////@end AlbumSplitterWindow event table entries

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
////@begin AlbumSplitterWindow creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    Centre();
////@end AlbumSplitterWindow creation
    return true;
}


/*
 * AlbumSplitterWindow destructor
 */

AlbumSplitterWindow::~AlbumSplitterWindow()
{
////@begin AlbumSplitterWindow destruction
////@end AlbumSplitterWindow destruction
}


/*
 * Member initialisation
 */

void AlbumSplitterWindow::Init()
{
////@begin AlbumSplitterWindow member initialisation
    m_secondarySplitterWindow = NULL;
////@end AlbumSplitterWindow member initialisation
}


/*
 * Control creation for AlbumSplitterWiindow
 */

void AlbumSplitterWindow::CreateControls()
{    
////@begin AlbumSplitterWindow content construction
    // Generated by DialogBlocks, Fri 21 Jan 2022 19:49:21 CST (unregistered)

    AlbumSplitterWindow* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 1, wxGROW|wxALL, 5);

    m_secondarySplitterWindow = new wxSplitterWindow( itemPanel1, ID_SECONDARYSPLITTERWINDOW, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    m_secondarySplitterWindow->SetMinimumPaneSize(0);
    m_albumPanel = new AlbumPanel( m_secondarySplitterWindow, ID_SCROLLEDWINDOW, wxDefaultPosition, wxSize(100, 100), wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL );

    //itemScrolledWindow2->FitInside();
    m_albumImagePanel = 
        new AlbumImagePanel( m_secondarySplitterWindow, ID_ALBUMALBUMIMAGEPANEL, wxDefaultPosition,
            wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_albumImagePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
   // itemBoxSizer7->Add( m_albumImagePanel, 1, wxGROW | wxALL, 0 );

    m_secondarySplitterWindow->SplitVertically(m_albumPanel, m_albumImagePanel, 200);
    itemBoxSizer1->Add(m_secondarySplitterWindow, 1, wxGROW|wxALL, 5);

////@end AlbumSplitterWindow content construction
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
////@begin AlbumSplitterWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AlbumSplitterWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumSplitterWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AlbumSplitterWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AlbumSplitterWindow icon retrieval
}

