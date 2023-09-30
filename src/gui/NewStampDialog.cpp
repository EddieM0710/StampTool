/*
 * @file NewStampDialog.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-06-03
 *
 * @copyright Copyright ( c ) 2022
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
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "LabeledTextBox.h"
#include "NewStampDialog.h"

 /*
  * NewStampDialog type definition
  */

IMPLEMENT_DYNAMIC_CLASS( NewStampDialog, wxDialog )


/*
 * NewStampDialog event table definition
 */

    BEGIN_EVENT_TABLE( NewStampDialog, wxDialog )

    // NewStampDialog event table entries
    EVT_CHOICE( ID_EMISSIONCHOICE, NewStampDialog::OnEmissionchoiceSelected )
    EVT_CHOICE( ID_FORMATCHOICE, NewStampDialog::OnFormatchoiceSelected )
    EVT_BUTTON( wxID_CANCEL, NewStampDialog::OnCancelClick )
    EVT_BUTTON( wxID_OK, NewStampDialog::OnOkClick )
    // NewStampDialog event table entries

    END_EVENT_TABLE( )
    ; // silly business; The above macro screws up the formatter


    /*
     * NewStampDialog constructors
     */

NewStampDialog::NewStampDialog( )
{
    Init( );
}

NewStampDialog::NewStampDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * NewStampDialog creator
 */

bool NewStampDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // NewStampDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // NewStampDialog creation
    return true;
}


/*
 * NewStampDialog destructor
 */

NewStampDialog::~NewStampDialog( )
{
    // NewStampDialog destruction
    // NewStampDialog destruction
}


/*
 * Member initialisation
 */

void NewStampDialog::Init( )
{
    // NewStampDialog member initialisation
    m_ID = NULL;
    m_name = NULL;
    m_emission = NULL;
    m_format = NULL;
    m_issueDate = NULL;
    m_country = NULL;
    m_catalog = NULL;
    m_catNbr = NULL;
    m_width = NULL;
    m_height = NULL;
    // NewStampDialog member initialisation
}


/*
 * Control creation for NewStampDialog
 */

void NewStampDialog::CreateControls( )
{
    // NewStampDialog content construction
    NewStampDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer1 );

    m_ID = new LabeledTextBox( itemDialog1, ID_IDLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    if ( NewStampDialog::ShowToolTips( ) )
        m_ID->SetToolTip( _( "Enter unique ID" ) );
    itemBoxSizer1->Add( m_ID, 0, wxGROW | wxALL, 2 );

    m_name = new LabeledTextBox( itemDialog1, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_name, 0, wxGROW | wxALL, 2 );

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer8, 0, wxALIGN_LEFT | wxALL, 2 );

    wxStaticText* itemStaticText9 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Emission" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add( itemStaticText9, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    wxArrayString m_emissionStrings;
    for ( int i = 0; i < Catalog::ET_NbrTypes; i++ )
    {
        m_emissionStrings.Add( _( Catalog::EmissionStrings[ i ] ) );
    }
    // m_emissionStrings.Add( _( "Unknown" ) );
    // m_emissionStrings.Add( _( "Commemorative" ) );
    // m_emissionStrings.Add( _( "Definitive" ) );
    // m_emissionStrings.Add( _( "Hunting Permit" ) );
    // m_emissionStrings.Add( _( "Revenue" ) );
    // m_emissionStrings.Add( _( "Air Post" ) );
    // m_emissionStrings.Add( _( "Air Post Official" ) );
    // m_emissionStrings.Add( _( "Air Post Semi-Postal" ) );
    // m_emissionStrings.Add( _( "ATM labels" ) );
    // m_emissionStrings.Add( _( "Cinderella" ) );
    // m_emissionStrings.Add( _( "Illegal" ) );
    // m_emissionStrings.Add( _( "Insured Letter" ) );
    // m_emissionStrings.Add( _( "Military" ) );
    // m_emissionStrings.Add( _( "Newspaper" ) );
    // m_emissionStrings.Add( _( "Official" ) );
    // m_emissionStrings.Add( _( "Parcel Post" ) );
    // m_emissionStrings.Add( _( "Personal Delivery" ) );
    // m_emissionStrings.Add( _( "Personalized" ) );
    // m_emissionStrings.Add( _( "Postage Due" ) );
    // m_emissionStrings.Add( _( "Postal Tax" ) );
    // m_emissionStrings.Add( _( "Precancelled" ) );
    // m_emissionStrings.Add( _( "Private" ) );
    // m_emissionStrings.Add( _( "Regional" ) );
    // m_emissionStrings.Add( _( "Registration" ) );
    // m_emissionStrings.Add( _( "Semi-Postal" ) );
    // m_emissionStrings.Add( _( "War Tax" ) );
    m_emission = new wxChoice( itemDialog1, ID_EMISSIONCHOICE, wxDefaultPosition, wxDefaultSize, m_emissionStrings, 0 );
    m_emission->SetStringSelection( _( "Unknown" ) );
    itemBoxSizer8->Add( m_emission, 1, wxGROW | wxALL, 1 );

    wxBoxSizer* itemBoxSizer11 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer11, 0, wxALIGN_LEFT | wxALL, 2 );

    wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Format" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add( itemStaticText12, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

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
    m_format = new wxChoice( itemDialog1, ID_FORMATCHOICE, wxDefaultPosition, wxDefaultSize, m_formatStrings, 0 );
    m_format->SetStringSelection( _( "Unknown" ) );
    itemBoxSizer11->Add( m_format, 1, wxGROW | wxALL, 1 );

    m_issueDate = new LabeledTextBox( itemDialog1, ID_ISSUEDTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    m_issueDate->SetHelpText( _( "Format: YYYY-MM-DD" ) );
    if ( NewStampDialog::ShowToolTips( ) )
        m_issueDate->SetToolTip( _( "Issue Date" ) );
    itemBoxSizer1->Add( m_issueDate, 0, wxGROW | wxALL, 2 );

    m_country = new LabeledTextBox( itemDialog1, ID_COUNTRYTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_country, 0, wxGROW | wxALL, 2 );

    m_catalog = new LabeledTextBox( itemDialog1, ID_CATALOGTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_catalog, 0, wxGROW | wxALL, 2 );

    m_catNbr = new LabeledTextBox( itemDialog1, ID_CATNBRTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_catNbr, 0, wxGROW | wxALL, 2 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer2, 0, wxGROW | wxALL, 2 );

    m_width = new LabeledTextBox( itemDialog1, ID_WIDTHTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    m_width->SetHelpText( _( "Width in centimeters" ) );
    if ( NewStampDialog::ShowToolTips( ) )
        m_width->SetToolTip( _( "Width in centimeters" ) );
    itemBoxSizer2->Add( m_width, 1, wxGROW | wxALL, 2 );

    itemBoxSizer2->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_height = new LabeledTextBox( itemDialog1, ID_HEIGHTTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    m_height->SetHelpText( _( "Height in centmeters" ) );
    if ( NewStampDialog::ShowToolTips( ) )
        m_height->SetToolTip( _( "Height in centmeters" ) );
    itemBoxSizer2->Add( m_height, 1, wxGROW | wxALL, 2 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton4 = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( itemButton4, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer3->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton6 = new wxButton( itemDialog1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( itemButton6, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // NewStampDialog content construction

        // m_status->SetLabel( "Status" );
    m_issueDate->SetLabel( "Issue Date" );
    m_emission->SetLabel( "Emission" );
    m_format->SetLabel( "Format" );
    m_width->SetLabel( "Width" );
    m_height->SetLabel( "Height" );
    m_ID->SetLabel( "ID" );
    m_name->SetLabel( "Name" );
    m_catalog->SetLabel( "Catalog" );
    m_catNbr->SetLabel( "Nbr" );
    m_country->SetLabel( "Country" );
}




bool NewStampDialog::ShowToolTips( )
{
    return true;
}



/*
 *   ID_EMISSIONCHOICE
 */

void NewStampDialog::OnEmissionchoiceSelected( wxCommandEvent& event )
{
    wxString strSel = m_emission->GetStringSelection( );
    //   if ( m_stamp ) m_stamp->SetEmission( strSel );

    event.Skip( );

}


/*
 *   ID_FORMATCHOICE
 */

void NewStampDialog::OnFormatchoiceSelected( wxCommandEvent& event )
{
    int sel = m_format->GetSelection( );
    wxString strSel = m_format->GetStringSelection( );
    //   if ( m_stamp ) m_stamp->SetFormat( strSel );

    event.Skip( );

}


/*
 *   wxID_CANCEL
 */

void NewStampDialog::OnCancelClick( wxCommandEvent& event )
{

    event.Skip( );

}

void NewStampDialog::UpdateStamp( )
{

    if ( m_country->IsModified( ) )
    {
        //        m_stamp->SetDirty( );
        //        m_stamp->SetCountryID( m_country->GetValue( ) );
    }

}
/*
 *   wxID_OK
 */

void NewStampDialog::OnOkClick( wxCommandEvent& event )
{
    UpdateStamp( );

    event.Skip( );

}

/*
 *
 *
 */

void NewStampDialog::SetChoice( wxChoice* ctrl, wxString str )
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
 */

 // void NewStampDialog::SetChoice( wxChoice* ctrl, int ndx )
 // { 
 //     ctrl->SetSelection( ndx );
 // }

 /*
  *
  *
  */

void NewStampDialog::SetStamp( Catalog::Entry* stamp )
{
    m_stamp = stamp;
    if ( m_stamp->IsOK( ) )
    {
        m_ID->SetValue( m_stamp->GetID( ) );
        m_name->SetValue( m_stamp->GetName( ) );
        m_issueDate->SetValue( m_stamp->GetAttr( Catalog::DT_Issued_on ) );
        SetChoice( m_emission, m_stamp->GetEmission( ) );
        SetChoice( m_format, m_stamp->GetFormat( ) );
        //        m_series->SetValue( m_stamp->GetAttr(  Catalog::DT_Series ) );
        //        m_themes->SetValue( m_stamp->GetAttr(  Catalog::DT_Themes ) );
        m_country->SetValue( m_stamp->GetAttr( Catalog::DT_Country ) );
        //        SetChoice( m_status, m_stamp->GetInventoryStatus( ) );
    }
}

/*
 *
 *
 */



