/**
 * @file FindStamp.cpp
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

 
 

#include "FindStamp.h"

 
 

/*
 * FindStamp type definition
 */

IMPLEMENT_DYNAMIC_CLASS( FindStamp, wxDialog )
; // silly business; The above macro screws up the formatter

/*
 * FindStamp event table definition
 */

BEGIN_EVENT_TABLE( FindStamp, wxDialog )

 // FindStamp event table entries
EVT_BUTTON( wxID_FIND, FindStamp::OnFindClick )
EVT_BUTTON( wxID_CANCEL, FindStamp::OnCancelClick )
 // FindStamp event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * FindStamp constructors
 */

FindStamp::FindStamp( )
{
    Init( );
}

FindStamp::FindStamp( wxWindow *parent, wxWindowID id, const wxString &caption,
                      const wxPoint &pos, const wxSize &size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

/*
 * FindStamp creator
 */

bool FindStamp::Create( wxWindow *parent, wxWindowID id,
                        const wxString &caption, const wxPoint &pos,
                        const wxSize &size, long style )
{
     // FindStamp creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
     // FindStamp creation
    return true;
}

/*
 * FindStamp destructor
 */

FindStamp::~FindStamp( )
{
     // FindStamp destruction
     // FindStamp destruction
}

/*
 * Member initialisation
 */

void FindStamp::Init( )
{
     // FindStamp member initialisation
    m_searchText = NULL;
    m_idCheckBox = NULL;
    m_titleCheckBox = NULL;
    m_seriesCheckBox = NULL;
    m_themeCheckBox = NULL;
    m_cancel = NULL;
     // FindStamp member initialisation
}

/*
 * Control creation for FindStamp
 */

void FindStamp::CreateControls( )
{
     // FindStamp content construction

    FindStamp *itemDialog1 = this;

    wxBoxSizer *itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxBoxSizer *itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 1, wxGROW | wxALL, 5 );

    m_searchText = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, wxEmptyString,
                                   wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_searchText, 1, wxGROW | wxALL, 5 );

    wxButton *itemButton3
        = new wxButton( itemDialog1, wxID_FIND, _( "&Find" ), wxDefaultPosition,
                        wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer1->Add( itemButton3, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer *itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                        5 );

    wxBoxSizer *itemBoxSizer5 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer4->Add( itemBoxSizer5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_idCheckBox = new wxCheckBox( itemDialog1, ID_IDCHECKBOX, _( "ID" ),
                                   wxDefaultPosition, wxDefaultSize, 0 );
    m_idCheckBox->SetValue( false );
    itemBoxSizer5->Add( m_idCheckBox, 0, wxALIGN_LEFT | wxALL, 5 );

    m_titleCheckBox
        = new wxCheckBox( itemDialog1, ID_TITLECHECKBOX, _( "Name" ),
                          wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckBox->SetValue( false );
    itemBoxSizer5->Add( m_titleCheckBox, 0, wxALIGN_LEFT | wxALL, 5 );

    wxBoxSizer *itemBoxSizer8 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer4->Add( itemBoxSizer8, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_seriesCheckBox
        = new wxCheckBox( itemDialog1, ID_SERIESCHECKBOX, _( "Series" ),
                          wxDefaultPosition, wxDefaultSize, 0 );
    m_seriesCheckBox->SetValue( false );
    itemBoxSizer8->Add( m_seriesCheckBox, 0, wxALIGN_LEFT | wxALL, 5 );

    m_themeCheckBox
        = new wxCheckBox( itemDialog1, ID_CTHEMEHECKBOX, _( "Theme" ),
                          wxDefaultPosition, wxDefaultSize, 0 );
    m_themeCheckBox->SetValue( false );
    itemBoxSizer8->Add( m_themeCheckBox, 0, wxALIGN_LEFT | wxALL, 5 );

    wxBoxSizer *itemBoxSizer11 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer11, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                        5 );

    m_cancel = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ),
                             wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add( m_cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

     // FindStamp content construction
}

/*
 * Should we show tooltips?
 */

bool FindStamp::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap FindStamp::GetBitmapResource( const wxString &name )
{
    // Bitmap retrieval
     // FindStamp bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
     // FindStamp bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon FindStamp::GetIconResource( const wxString &name )
{
    // Icon retrieval
     // FindStamp icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
     // FindStamp icon retrieval
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NEXTBUTTON
 */

void FindStamp::OnFindClick( wxCommandEvent &event )
{
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NEXTBUTTON in
    //FindStamp.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NEXTBUTTON in
    //FindStamp.
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void FindStamp::OnCancelClick( wxCommandEvent &event )
{
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in
    //FindStamp.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in
    //FindStamp.
}
