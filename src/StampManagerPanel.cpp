/////////////////////////////////////////////////////////////////////////////
// Name:        StampManagerPanel.cpp
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Fri 25 Mar 2022 16:21:43 CDT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Fri 25 Mar 2022 16:21:43 CDT

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "StampTreeCtrl.h"
#include "wx/imaglist.h"
#include "DescriptionPanel.h"
////@end includes

#include "StampManagerPanel.h"

////@begin XPM images

////@end XPM images


/*
 * StampManagerPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( StampManagerPanel, wxPanel )


/*
 * StampManagerPanel event table definition
 */

BEGIN_EVENT_TABLE( StampManagerPanel, wxPanel )

////@begin StampManagerPanel event table entries
    EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, StampManagerPanel::OnNotebookPageChanged )
////@end StampManagerPanel event table entries

END_EVENT_TABLE()


/*
 * StampManagerPanel constructors
 */

StampManagerPanel::StampManagerPanel()
{
    Init();
}

StampManagerPanel::StampManagerPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * StampManagerPanel creator
 */

bool StampManagerPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin StampManagerPanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    Centre();
////@end StampManagerPanel creation
    return true;
}


/*
 * StampManagerPanel destructor
 */

StampManagerPanel::~StampManagerPanel()
{
////@begin StampManagerPanel destruction
////@end StampManagerPanel destruction
}


/*
 * Member initialisation
 */

void StampManagerPanel::Init()
{
////@begin StampManagerPanel member initialisation
    m_listTree = NULL;
    m_notebook = NULL;
    m_descriptionPanel = NULL;
    m_galleryPage = NULL;
    m_sizer = NULL;
////@end StampManagerPanel member initialisation
}


/*
 * Control creation for StampManagerPanel
 */

void StampManagerPanel::CreateControls()
{    
////@begin StampManagerPanel content construction
    // Generated by DialogBlocks, Fri 25 Mar 2022 16:21:43 CDT (unregistered)

    StampManagerPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer2, 1, wxGROW|wxALL, 0);

    wxSplitterWindow* itemSplitterWindow3 = new wxSplitterWindow( itemPanel1, ID_SPLITTERWINDOW, wxDefaultPosition, wxDefaultSize, wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow3->SetMinimumPaneSize(20);
    itemSplitterWindow3->SetSashGravity(0.2);

    wxPanel* itemPanel4 = new wxPanel( itemSplitterWindow3, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel4->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
    itemPanel4->SetSizer(itemBoxSizer5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer5->Add(itemBoxSizer6, 2, wxGROW|wxALL, 0);
    m_listTree = new StampTreeCtrl( itemPanel4, ID_TREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS |wxTR_FULL_ROW_HIGHLIGHT|wxTR_SINGLE|wxSUNKEN_BORDER|wxTR_DEFAULT_STYLE );
    itemBoxSizer6->Add(m_listTree, 2, wxGROW|wxALL, 0);

    m_notebook = new wxNotebook( itemSplitterWindow3, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    m_descriptionPanel = new DescriptionPanel( m_notebook, ID_DESCRIPTIONPANELFOREIGN, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    m_descriptionPanel->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);

    m_notebook->AddPage(m_descriptionPanel, _("Stamp"));

    m_galleryPage = new wxScrolledWindow( m_notebook, ID_GALLERYSCROLLEDWINDOW, wxDefaultPosition, wxSize(100, 100), wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL );
    m_galleryPage->SetScrollbars(1, 1, 0, 0);
    m_sizer = new wxFlexGridSizer(0, 6, 0, 0);
    m_galleryPage->SetSizer(m_sizer);

    m_galleryPage->FitInside();
    m_notebook->AddPage(m_galleryPage, _("Gallery"));

    wxPanel* itemPanel3 = new wxPanel( m_notebook, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel3->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);

    m_notebook->AddPage(itemPanel3, _("Tab"));

    itemSplitterWindow3->SplitVertically(itemPanel4, m_notebook, 100);
    itemBoxSizer2->Add(itemSplitterWindow3, 1, wxGROW|wxALL, 0);

////@end StampManagerPanel content construction
}


/*
 * wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
 */

void StampManagerPanel::OnNotebookPageChanged( wxNotebookEvent& event )
{
////@begin wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK in StampManagerPanel.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK in StampManagerPanel. 
}


/*
 * Should we show tooltips?
 */

bool StampManagerPanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap StampManagerPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin StampManagerPanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end StampManagerPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon StampManagerPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin StampManagerPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end StampManagerPanel icon retrieval
}
