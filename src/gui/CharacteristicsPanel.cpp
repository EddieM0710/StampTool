/**
 * @file CharacteristicsPanel.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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

#include "Defs.h"
#include "gui/CharacteristicsPanel.h"
#include "gui/LabeledTextBox.h"
#include "utils/Settings.h"
/*
 * CharacteristicsPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CharacteristicsPanel, wxPanel )
; // silly business; The above macro screws up the formatter

/*
 * CharacteristicsPanel event table definition
 */

BEGIN_EVENT_TABLE( CharacteristicsPanel, wxPanel )

// CharacteristicsPanel event table entries
EVT_TEXT( ID_HEIGHTEXTBOX, CharacteristicsPanel::OnTextctrlTextUpdated )
EVT_TEXT( ID_WIDTHTEXTBOX, CharacteristicsPanel::OnTextctrlTextUpdated )

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * CharacteristicsPanel constructors
 */
CharacteristicsPanel::CharacteristicsPanel( ) { Init( ); }

CharacteristicsPanel::CharacteristicsPanel( wxWindow* parent, wxWindowID id, 
    const wxPoint& pos, 
    const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * CharacteristicsPanel creator
 */

bool CharacteristicsPanel::Create( wxWindow* parent, wxWindowID id, 
    const wxPoint& pos, const wxSize& size, 
    long style )
{ 
    // CharacteristicsPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    { 
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // CharacteristicsPanel creation
    return true;
}

/*
 * CharacteristicsPanel destructor
 */
CharacteristicsPanel::~CharacteristicsPanel( void )
{ 
    // CharacteristicsPanel destruction
    // CharacteristicsPanel destruction
}

/*
 * Member initialisation
 */
void CharacteristicsPanel::Init( void )
{ 
    // CharacteristicsPanel member initialisation
//$    m_faceValue = NULL;
//$    m_currency = NULL;
    m_height = NULL;
    m_width = NULL;
//$    m_perforation = NULL;
//$    m_watermark = NULL;
//$    m_gum = NULL;
//$    m_variant = NULL;
//$    m_colors = NULL;
//$    m_paper = NULL;
//$    m_printing = NULL;
//$    m_printRun = NULL;
//$    m_expiryDate = NULL;
    // CharacteristicsPanel member initialisation
}

/*
 * Control creation for CharacteristicsPanel
 */
void CharacteristicsPanel::CreateControls( void )
{ 
    // CharacteristicsPanel content construction

    CharacteristicsPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer2, 1, wxGROW | wxALL, 5 );

//$    m_faceValue = 
//$        new LabeledTextBox( itemPanel1, ID_FACETEXTBOX, wxDefaultPosition, 
//$            wxDefaultSize, wxDOUBLE_BORDER );
//$    itemBoxSizer2->Add( m_faceValue, 0, wxGROW | wxALL, 2 );

//$    m_currency = new LabeledTextBox( itemPanel1, ID_CURRENCYTEXTBOX, 
//$        wxDefaultPosition, wxDefaultSize, 0 );
//$    itemBoxSizer2->Add( m_currency, 0, wxGROW | wxALL, 2 );

    m_height = new LabeledTextBox( itemPanel1, ID_HEIGHTEXTBOX, wxDefaultPosition, 
        wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_height, 0, wxGROW | wxALL, 2 );

    m_width = new LabeledTextBox( itemPanel1, ID_WIDTHTEXTBOX, wxDefaultPosition, 
        wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_width, 0, wxGROW | wxALL, 2 );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer7, 1, wxGROW | wxALL, 5 );

//$    m_perforation = new LabeledTextBox( itemPanel1, ID_PERFORATIONTEXTBOX, 
//$        wxDefaultPosition, wxDefaultSize, 0 );
//$    itemBoxSizer7->Add( m_perforation, 0, wxGROW | wxALL, 2 );

//$    m_watermark = new LabeledTextBox( itemPanel1, ID_WATERMARKEXTBOX, 
//$        wxDefaultPosition, wxDefaultSize, 0 );
//$    itemBoxSizer7->Add( m_watermark, 0, wxGROW | wxALL, 2 );

//$    m_gum = new LabeledTextBox( itemPanel1, ID_GUMTEXTBOX, wxDefaultPosition, 
//$        wxDefaultSize, 0 );
//$    itemBoxSizer7->Add( m_gum, 0, wxGROW | wxALL, 2 );

//$    wxBoxSizer* itemBoxSizer11 = new wxBoxSizer( wxVERTICAL );
//$    itemBoxSizer1->Add( itemBoxSizer11, 1, wxGROW | wxALL, 5 );

//$    m_variant = new LabeledTextBox( itemPanel1, ID_VARIANTTEXTBOX, 
//$        wxDefaultPosition, wxDefaultSize, 0 );
//$    itemBoxSizer11->Add( m_variant, 0, wxGROW | wxALL, 2 );

//$    m_colors = new LabeledTextBox( itemPanel1, ID_COLORSTEXTBOX, wxDefaultPosition, 
//$        wxDefaultSize, 0 );
//$    itemBoxSizer11->Add( m_colors, 0, wxGROW | wxALL, 2 );

//$    m_paper = new LabeledTextBox( itemPanel1, ID_PAPERTEXTBOX, wxDefaultPosition, 
//$        wxDefaultSize, 0 );
//$    itemBoxSizer11->Add( m_paper, 0, wxGROW | wxALL, 2 );

//$    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer( wxVERTICAL );
//$    itemBoxSizer1->Add( itemBoxSizer15, 1, wxGROW | wxALL, 5 );

//$    m_printing = new LabeledTextBox( itemPanel1, ID_PRINTINGTEXTBOX, 
    //$     wxDefaultPosition, wxDefaultSize, 0 );
    //$ itemBoxSizer15->Add( m_printing, 0, wxGROW | wxALL, 2 );

    //$ m_printRun = new LabeledTextBox( itemPanel1, ID_PRINTRUNTEXTBOX, 
    //$     wxDefaultPosition, wxDefaultSize, 0 );
    //$ itemBoxSizer15->Add( m_printRun, 0, wxGROW | wxALL, 2 );

    //$ m_expiryDate = new LabeledTextBox( itemPanel1, ID_EXPIRYDATEEXTBOX, 
    //$     wxDefaultPosition, wxDefaultSize, 0 );
    //$ itemBoxSizer15->Add( m_expiryDate, 0, wxGROW | wxALL, 2 );

    // CharacteristicsPanel content construction
    m_width->SetValue( "40" );
    m_height->SetValue( "40" );
//$    m_faceValue->SetLabel( "Face Value" );
//$    m_currency->SetLabel( "Currency" );
//$    m_expiryDate->SetLabel( "Expiry Date" );

    m_height->SetLabel( "Height" );
    m_width->SetLabel( "Width" );
//$    m_paper->SetLabel( "Paper" );
//$    m_watermark->SetLabel( "Watermark" );
//$    m_perforation->SetLabel( "Perforation" );
//$    m_gum->SetLabel( "Gum" );
    //  m_printing->SetLabel( "Printing" );
    //  m_printRun->SetLabel( "PrintRun" );
//$   m_variant->SetLabel( "Variant" );
//$    m_colors->SetLabel( "Colors" );
//$    m_printing->SetLabel( "Printing" );
//$    m_printRun->SetLabel( "Print Run" );

    SetDataEditable( GetSettings( )->IsCatalogSectionDataEditable( ) );

}

/*
 * Should we show tooltips?
 */
bool CharacteristicsPanel::ShowToolTips( void ) { return true; }

/*
 * Get bitmap resources
 */
wxBitmap CharacteristicsPanel::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
    // CharacteristicsPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // CharacteristicsPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CharacteristicsPanel::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
    // CharacteristicsPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // CharacteristicsPanel icon retrieval
    /*!
     * CharacteristicsPanel class declaration
     */
}

// initializes the CharacteristicsPanel with new stamp values
void CharacteristicsPanel::SetStamp( Catalog::Entry* stamp )
{ 
    m_stamp = stamp;
    if ( m_stamp->IsOK( ) )
    { 
//$        m_printing->SetValue( m_stamp->GetAttr( Catalog::DT_Printing ) );
//$        m_printRun->SetValue( m_stamp->GetAttr( Catalog::DT_Print_run ) );
//$        m_variant->SetValue( m_stamp->GetAttr( Catalog::DT_Variant ) );
        m_height->SetValue( m_stamp->GetAttr( Catalog::DT_Height ) );
        m_width->SetValue( m_stamp->GetAttr( Catalog::DT_Width ) );
//$        m_paper->SetValue( m_stamp->GetAttr( Catalog::DT_Paper ) );
//$        m_watermark->SetValue( m_stamp->GetAttr( Catalog::DT_Watermark ) );
//$        m_perforation->SetValue( m_stamp->GetAttr( Catalog:: DT_Perforation ) );
 //$       m_gum->SetValue( m_stamp->GetAttr( Catalog::DT_Gum ) );
//$        m_colors->SetValue( m_stamp->GetAttr( Catalog::DT_Colors ) );
//$        m_faceValue->SetValue( m_stamp->GetAttr( Catalog::DT_FaceValue ) );
//$        m_currency->SetValue( m_stamp->GetAttr( Catalog::DT_Currency ) );
//$        m_expiryDate->SetValue( m_stamp->GetAttr( Catalog::DT_Expiry_date ) );
    }
}


void CharacteristicsPanel::UpdateStampValue( Catalog::DataTypes dt, LabeledTextBox* textBox  )
{ 
    if ( textBox->IsModified( ) )
    { 
        wxString val = textBox->GetValue( );
        m_stamp->SetAttr( dt, val );
        textBox->SetModified( false );
    }
}

void CharacteristicsPanel::OnTextctrlTextUpdated( wxCommandEvent& event )
{ 
  void* eventObject = event.GetClientData( );
    //$ if ( eventObject == m_printing )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Printing, m_printing );
    //$ }
    //$ else if ( eventObject == m_printRun )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Print_run, m_printRun );
    //$ }
    //$ else if ( eventObject == m_variant )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Variant, m_variant );
    //$ }
    //$ else 
    if ( eventObject == m_height )
    { 
        UpdateStampValue( Catalog::DT_Height, m_height );
    }
    else if ( eventObject == m_width )
    { 
        UpdateStampValue( Catalog::DT_Width, m_width );
    }
    //$ else if ( eventObject == m_paper )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Paper, m_paper );
    //$ }
    //$ else if ( eventObject == m_watermark )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Watermark, m_watermark );
    //$ }
    //$ else if ( eventObject == m_perforation )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Perforation, m_perforation );
    //$ }
    //$ else if ( eventObject == m_gum )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Gum, m_gum );
    //$ }
    //$ else if ( eventObject == m_colors )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Colors, m_colors );
    //$ }
    //$ else if ( eventObject == m_faceValue )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_FaceValue, m_faceValue );
    //$ }
    //$ else if ( eventObject == m_currency )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Currency, m_currency );
    //$ }
    //$ else if ( eventObject == m_expiryDate )
    //$ { 
    //$     UpdateStampValue( Catalog::DT_Expiry_date, m_expiryDate );
    //$ }
    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_EMISSIONCHOICE
    // in IdentificationPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_EMISSIONCHOICE
    // in IdentificationPanel.
}

void CharacteristicsPanel::SetDataEditable( bool val )
{ 
    //$  m_faceValue->SetEditable( val );
    //$  m_currency->SetEditable( val );
      m_height->SetEditable( val );
      m_width->SetEditable( val );
    //$  m_perforation->SetEditable( val );
    //$  m_watermark->SetEditable( val );
    //$  m_gum->SetEditable( val );
    //$  m_variant->SetEditable( val );
    //$  m_colors->SetEditable( val );
    //$  m_paper->SetEditable( val );
    //$  m_printing->SetEditable( val );
    //$  m_printRun->SetEditable( val );
    //$  m_expiryDate->SetEditable( val );
}