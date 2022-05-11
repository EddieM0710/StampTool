/**
 * @file IdentificationPanel.cpp
 * @author Eddie Monroe ()
 * @brief IdentificationPanel displays Stamp data relative to the stamp identification
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

#include "LabeledTextBox.h"

#include "Classification.h"
#include "IdentificationPanel.h"
#include "catalog/Stamp.h"
#include "catalog/CatalogDefs.h"
#include "gui/CatalogTreeCtrl.h"
/*
 * IdentificationPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( IdentificationPanel, wxPanel )
; // Formatting silly business; The above macro screws up the formatter but the semicolon fixes it

/*
 * IdentificationPanel event table definition
 */

BEGIN_EVENT_TABLE( IdentificationPanel, wxPanel )

// IdentificationPanel event table entries
EVT_CHOICE( ID_STATUSCHOICE, IdentificationPanel::OnStatuschoiceSelected )
EVT_CHOICE( ID_EMISSIONCHOICE, IdentificationPanel::OnEmissionchoiceSelected )
EVT_CHOICE( ID_FORMATCHOICE, IdentificationPanel::OnFormatchoiceSelected )
// IdentificationPanel event table entries

END_EVENT_TABLE( )
; // silly business; The above macro screws up the formatter

/*
 * IdentificationPanel constructors
 *
 */
IdentificationPanel::IdentificationPanel( )
{
    Init( );
}

/*
 *
 *
 **************************************************/

IdentificationPanel::IdentificationPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * IdentificationPanel creator
 *
 **************************************************/

bool IdentificationPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    // IdentificationPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // IdentificationPanel creation

    return true;
}

/*
 * IdentificationPanel destructor
 *
 **************************************************/

IdentificationPanel::~IdentificationPanel( )
{
    // IdentificationPanel destruction
    // IdentificationPanel destruction
}

/*
 * Member initialisation
 *
 **************************************************/

void IdentificationPanel::Init( )
{
    // IdentificationPanel member initialisation
    m_ID = NULL;
    m_status = NULL;
    m_name = NULL;
    m_emission = NULL;
    m_format = NULL;
    m_issueDate = NULL;
    m_series = NULL;
    m_themes = NULL;
    m_country = NULL;
    // IdentificationPanel member initialisation
}

/*
 * Control creation for IdentificationPanel
 *
 **************************************************/

void IdentificationPanel::CreateControls( )
{
    // IdentificationPanel content construction

    IdentificationPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
        2 );

    m_ID = new LabeledTextBox( itemPanel1, ID_IDLABELEDTEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_ID, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    wxStaticText* itemStaticText6 = new wxStaticText( itemPanel1, wxID_STATIC, _( "Status" ),
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add( itemStaticText6, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        5 );

    wxArrayString m_statusStrings;
    m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_None ] );
    m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Missing ] );
    m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Ordered] );
    m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Own] );
    m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_OwnVariant] );
    m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Exclude] );
    m_status = new wxChoice( itemPanel1, ID_STATUSCHOICE, wxDefaultPosition,
        wxDefaultSize, m_statusStrings, 0 );
    m_status->SetStringSelection( _( "None" ) );
    itemBoxSizer5->Add( m_status, 1, wxGROW | wxALL, 1 );

    m_name = new LabeledTextBox( itemPanel1, ID_NAMELABELEDTEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_name, 0, wxGROW | wxALL, 2 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer3, 0, wxALIGN_LEFT | wxALL, 2 );

    wxStaticText* itemStaticText1 = new wxStaticText( itemPanel1, wxID_STATIC, _( "Emission" ),
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( itemStaticText1, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        0 );

    wxArrayString m_emissionStrings;
    m_emissionStrings.Add( _( "Unknown" ) );
    m_emissionStrings.Add( _( "Commemorative" ) );
    m_emissionStrings.Add( _( "Definitive" ) );
    m_emissionStrings.Add( _( "Hunting Permit" ) );
    m_emissionStrings.Add( _( "Revenue" ) );
    m_emissionStrings.Add( _( "Air Post" ) );
    m_emissionStrings.Add( _( "Air Post Official" ) );
    m_emissionStrings.Add( _( "Air Post Semi-Postal" ) );
    m_emissionStrings.Add( _( "ATM labels" ) );
    m_emissionStrings.Add( _( "Cinderella" ) );
    m_emissionStrings.Add( _( "Illegal" ) );
    m_emissionStrings.Add( _( "Insured Letter" ) );
    m_emissionStrings.Add( _( "Military" ) );
    m_emissionStrings.Add( _( "Newspaper" ) );
    m_emissionStrings.Add( _( "Official" ) );
    m_emissionStrings.Add( _( "Parcel Post" ) );
    m_emissionStrings.Add( _( "Personal Delivery" ) );
    m_emissionStrings.Add( _( "Personalized" ) );
    m_emissionStrings.Add( _( "Postage Due" ) );
    m_emissionStrings.Add( _( "Postal Tax" ) );
    m_emissionStrings.Add( _( "Precancelled" ) );
    m_emissionStrings.Add( _( "Private" ) );
    m_emissionStrings.Add( _( "Regional" ) );
    m_emissionStrings.Add( _( "Registration" ) );
    m_emissionStrings.Add( _( "Semi-Postal" ) );
    m_emissionStrings.Add( _( "War Tax" ) );
    m_emission = new wxChoice( itemPanel1, ID_EMISSIONCHOICE, wxDefaultPosition,
        wxDefaultSize, m_emissionStrings, 0 );
    m_emission->SetStringSelection( _( "Unknown" ) );
    itemBoxSizer3->Add( m_emission, 1, wxGROW | wxALL, 1 );

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer4, 0, wxALIGN_LEFT | wxALL, 2 );

    wxStaticText* itemStaticText5 = new wxStaticText( itemPanel1, wxID_STATIC, _( "Format" ),
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add( itemStaticText5, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        0 );

    wxArrayString m_formatStrings;
    m_formatStrings.Add( _( "Unknown" ) );
    m_formatStrings.Add( _( "Stamp" ) );
    m_formatStrings.Add( _( "Se-tenant" ) );
    m_formatStrings.Add( _( "Mini Sheet" ) );
    m_formatStrings.Add( _( "Souvenir Sheet" ) );
    m_formatStrings.Add( _( "Booklet" ) );
    m_formatStrings.Add( _( "Booklet Pane" ) );
    m_formatStrings.Add( _( "Gutter Pair" ) );
    m_formatStrings.Add( _( "Stamp with Attached Label" ) );
    m_formatStrings.Add( _( "Tete-Beche" ) );
    m_format = new wxChoice( itemPanel1, ID_FORMATCHOICE, wxDefaultPosition,
        wxDefaultSize, m_formatStrings, 0 );
    m_format->SetStringSelection( _( "Unknown" ) );
    itemBoxSizer4->Add( m_format, 1, wxGROW | wxALL, 1 );

    m_issueDate = new LabeledTextBox( itemPanel1, ID_ISSUEDTEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_issueDate, 0, wxGROW | wxALL, 2 );

    m_series = new LabeledTextBox( itemPanel1, ID_SERIESTEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_series, 0, wxGROW | wxALL, 2 );

    m_themes = new LabeledTextBox( itemPanel1, ID_THEMETEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_themes, 0, wxGROW | wxALL, 2 );

    m_country = new LabeledTextBox( itemPanel1, ID_COUNTRYTEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_country, 0, wxGROW | wxALL, 2 );

    // IdentificationPanel content construction

    // m_status->SetLabel("Status");
    m_issueDate->SetLabel( "Issue Date" );
    m_emission->SetLabel( "Emission" );
    m_format->SetLabel( "Format" );
    m_themes->SetLabel( "Themes" );
    m_ID->SetLabel( "ID" );
    m_name->SetLabel( "Name" );
    // m_ID->SetID(m_stamp.GetID());
    // m_ID->SetName(m_stamp.GetName());
    m_series->SetLabel( "Series" );
    m_status->SetLabel( "Status" );
    m_country->SetLabel( "Country" );
}

/*
 * Should we show tooltips?
 *
 **************************************************/

bool IdentificationPanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 *
 **************************************************/

wxBitmap IdentificationPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    // IdentificationPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // IdentificationPanel bitmap retrieval
}

/*
 * Get icon resources
 *
 **************************************************/

wxIcon IdentificationPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
    // IdentificationPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // IdentificationPanel icon retrieval
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_EMISSIONCHOICE
 *
 **************************************************/

void IdentificationPanel::OnEmissionchoiceSelected( wxCommandEvent& event )
{
    wxString strSel = m_emission->GetStringSelection( );
    if ( m_stamp ) m_stamp->SetEmission( strSel );

    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_EMISSIONCHOICE
    // in IdentificationPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_EMISSIONCHOICE
    // in IdentificationPanel.
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_FORMATCHOICE
 *
 **************************************************/

void IdentificationPanel::OnFormatchoiceSelected( wxCommandEvent& event )
{
    int sel = m_format->GetSelection( );
    wxString strSel = m_format->GetStringSelection( );
    if ( m_stamp ) m_stamp->SetFormat( strSel );

    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_FORMATCHOICE
    // in IdentificationPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_FORMATCHOICE in
    // IdentificationPanel.
}

/*
 *
 *
 **************************************************/

void IdentificationPanel::SetChoice( wxChoice* ctrl, wxString str )
{
    int ndx = ctrl->FindString( str );
    if ( ndx == wxNOT_FOUND )
    {
        ndx = 0;
    }
    ctrl->SetSelection( ndx );
}

/*
 *
 *
 **************************************************/

void IdentificationPanel::SetChoice( wxChoice* ctrl, int ndx )
{
    ctrl->SetSelection( ndx );
}

/*
 *
 *
 **************************************************/

void IdentificationPanel::SetStamp( Catalog::Stamp* stamp )
{
    m_stamp = stamp;
    if ( m_stamp->IsOK( ) )
    {
        m_ID->SetValue( m_stamp->GetAttr(  Catalog::DT_ID_Nbr)  );
        m_name->SetValue( m_stamp->GetAttr(  Catalog::DT_Name) );
        m_issueDate->SetValue( m_stamp->GetAttr(  Catalog::DT_Issued_on) );
        SetChoice( m_emission, m_stamp->GetEmission( ) );
        SetChoice( m_format, m_stamp->GetFormat( ) );
        m_series->SetValue( m_stamp->GetAttr(  Catalog::DT_Series) );
        m_themes->SetValue( m_stamp->GetAttr(  Catalog::DT_Themes ));
        m_country->SetValue( m_stamp->GetAttr(  Catalog::DT_Country ) );
        SetChoice( m_status, m_stamp->GetInventoryStatus( ) );
    }
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_STATUSCHOICE
 *
 **************************************************/

void IdentificationPanel::OnStatuschoiceSelected( wxCommandEvent& event )
{
    wxString strSel = m_status->GetStringSelection( );
    m_stamp->SetInventoryStatus( strSel );
    GetCatalogTreeCtrl()->SetInventoryStatusImage( );
    
    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_STATUSCHOICE
    // in IdentificationPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_STATUSCHOICE in
    // IdentificationPanel.
}

/*
 *
 *
 **************************************************/

void IdentificationPanel::UpdateStatus( )
{
    if ( m_stamp->IsOK( ) )
    {
        SetChoice( m_status, m_stamp->GetInventoryStatus( ) );
    }
}
