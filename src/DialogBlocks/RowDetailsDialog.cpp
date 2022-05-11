/////////////////////////////////////////////////////////////////////////////
// Name:        RowDetailsDialog.cpp
// Purpose:     
// Author:      Eddie Monroe
// Modified by: 
// Created:     Fri 29 Apr 2022 17:39:37 CDT
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Fri 29 Apr 2022 17:39:37 CDT

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

#include "RowDetailsDialog.h"

////@begin XPM images
////@end XPM images


/*
 * RowDetailsDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( RowDetailsDialog, wxDialog )


/*
 * RowDetailsDialog event table definition
 */

BEGIN_EVENT_TABLE( RowDetailsDialog, wxDialog )

////@begin RowDetailsDialog event table entries
    EVT_BUTTON( wxID_OK, RowDetailsDialog::OnOkClick )
////@end RowDetailsDialog event table entries

END_EVENT_TABLE()


/*
 * RowDetailsDialog constructors
 */

RowDetailsDialog::RowDetailsDialog()
{
    Init();
}

RowDetailsDialog::RowDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * RowDetailsDialog creator
 */

bool RowDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin RowDetailsDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end RowDetailsDialog creation
    return true;
}


/*
 * RowDetailsDialog destructor
 */

RowDetailsDialog::~RowDetailsDialog()
{
////@begin RowDetailsDialog destruction
////@end RowDetailsDialog destruction
}


/*
 * Member initialisation
 */

void RowDetailsDialog::Init()
{
////@begin RowDetailsDialog member initialisation
    m_name = NULL;
    m_titleCheckbox = NULL;
    m_frameCheckbox = NULL;
    m_statusList = NULL;
////@end RowDetailsDialog member initialisation
}


/*
 * Control creation for RowDetailsDialog
 */

void RowDetailsDialog::CreateControls()
{    
////@begin RowDetailsDialog content construction
    // Generated by DialogBlocks, Fri 29 Apr 2022 17:45:15 CDT (unregistered)

    RowDetailsDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 0, wxGROW|wxALL, 0);

    m_name = new LabeledTextBox( itemDialog1, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    m_name->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    itemBoxSizer1->Add(m_name, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_titleCheckbox = new wxCheckBox( itemDialog1, ID_TITLECHECKBOX, _("Show Title"), wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckbox->SetValue(false);
    itemBoxSizer3->Add(m_titleCheckbox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_frameCheckbox = new wxCheckBox( itemDialog1, ID_FRAMECHECKBOX, _("Show Frame"), wxDefaultPosition, wxDefaultSize, 0 );
    m_frameCheckbox->SetValue(false);
    itemBoxSizer3->Add(m_frameCheckbox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer4, 2, wxGROW|wxALL, 5);

    m_statusList = new wxListCtrl( itemDialog1, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxLC_NO_HEADER );
    itemBoxSizer4->Add(m_statusList, 2, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxButton* itemButton6 = new wxButton( itemDialog1, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton7 = new wxButton( itemDialog1, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end RowDetailsDialog content construction
}


/*
 * Should we show tooltips?
 */

bool RowDetailsDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap RowDetailsDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin RowDetailsDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end RowDetailsDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon RowDetailsDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin RowDetailsDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end RowDetailsDialog icon retrieval
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void RowDetailsDialog::OnOkClick( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in RowDetailsDialog.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in RowDetailsDialog. 
}
