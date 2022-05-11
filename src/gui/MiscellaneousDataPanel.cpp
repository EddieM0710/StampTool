/**
 * @file MiscellaneousDataPanel.cpp
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

 
#include "LabeledTextBox.h"
 

#include "MiscellaneousDataPanel.h"

 
 

/*
 * MiscellaneousDataPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( MiscellaneousDataPanel, wxPanel )
; // silly business; The above macro screws up the formatter

/*
 * MiscellaneousDataPanel event table definition
 */

BEGIN_EVENT_TABLE( MiscellaneousDataPanel, wxPanel )

 // MiscellaneousDataPanel event table entries
EVT_BUTTON( ID_MYSTICBUTTON, MiscellaneousDataPanel::OnMysticButtonClick )
EVT_BUTTON( ID_COLNECTBUTTON, MiscellaneousDataPanel::OnColnectButtonClick )
EVT_BUTTON( ID_EBAYBUTTON, MiscellaneousDataPanel::OneBayButtonClick )
EVT_BUTTON( ID_NPMBUTTON, MiscellaneousDataPanel::OnNPMButtonClick )
 // MiscellaneousDataPanel event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * MiscellaneousDataPanel constructors
 */

MiscellaneousDataPanel::MiscellaneousDataPanel( )
{
    Init( );
}

MiscellaneousDataPanel::MiscellaneousDataPanel( wxWindow *parent, wxWindowID id,
                                                const wxPoint &pos,
                                                const wxSize &size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * MiscellaneousData creator
 */

bool MiscellaneousDataPanel::Create( wxWindow *parent, wxWindowID id,
                                     const wxPoint &pos, const wxSize &size,
                                     long style )
{
     // MiscellaneousDataPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
     // MiscellaneousDataPanel creation
    return true;
}

/*
 * MiscellaneousDataPanel destructor
 */

MiscellaneousDataPanel::~MiscellaneousDataPanel( )
{
     // MiscellaneousDataPanel destruction
     // MiscellaneousDataPanel destruction
}

/*
 * Member initialisation
 */

void MiscellaneousDataPanel::Init( )
{
    m_stamp = new Catalog::Stamp( );
     // MiscellaneousDataPanel member initialisation
    m_score = NULL;
    m_accuracy = NULL;
    m_link = NULL;
    m_catCodes = NULL;
    m_imageName = NULL;

     // MiscellaneousDataPanel member initialisation
}

/*
 * Control creation for MiscellaneousData
 */

void MiscellaneousDataPanel::CreateControls( )
{
     // MiscellaneousDataPanel content construction

    MiscellaneousDataPanel *itemPanel1 = this;

    wxBoxSizer *itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer *itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer3, 0, wxGROW | wxALL, 0 );

    m_score = new LabeledTextBox( itemPanel1, ID_SCORETEXTBOX,
                                  wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( m_score, 0, wxGROW | wxALL, 0 );

    itemBoxSizer3->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_accuracy = new LabeledTextBox( itemPanel1, ID_ACCURACYTEXTBOX,
                                     wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( m_accuracy, 0, wxGROW | wxALL, 0 );

    m_link = new LabeledTextBox( itemPanel1, ID_LINKTEXTBOX, wxDefaultPosition,
                                 wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_link, 0, wxGROW | wxALL, 0 );

    wxBoxSizer *itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer8, 0, wxGROW | wxALL, 5 );

    wxButton *itemButton9
        = new wxButton( itemPanel1, ID_MYSTICBUTTON, _( "Mystic" ),
                        wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton9, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton *itemButton10
        = new wxButton( itemPanel1, ID_COLNECTBUTTON, _( "Colnect" ),
                        wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton10, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton *itemButton11
        = new wxButton( itemPanel1, ID_EBAYBUTTON, _( "eBay" ),
                        wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton11, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton *itemButton12
        = new wxButton( itemPanel1, ID_NPMBUTTON, _( "NPM" ), wxDefaultPosition,
                        wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton12, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_catCodes = new LabeledTextBox( itemPanel1, ID_CATCODETEXTBOX,
                                     wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_catCodes, 0, wxGROW | wxALL, 0 );

    m_imageName = new LabeledTextBox( itemPanel1, ID_IMAGENAMETEXTBOX,
                                  wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_imageName, 0, wxGROW | wxALL, 0 );

     // MiscellaneousDataPanel content construction

        m_score->SetLabel( Catalog::DT_DataNames[Catalog::DT_Score] );
        m_accuracy->SetLabel( Catalog::DT_DataNames[Catalog::DT_Accuracy] );
        m_link->SetLabel( Catalog::DT_DataNames[Catalog::DT_Link] );
        m_catCodes->SetLabel( Catalog::DT_DataNames[Catalog::DT_Catalog_Codes] );
        m_imageName->SetLabel( "Image Name" );

}

/*
 * Should we show tooltips?
 */

bool MiscellaneousDataPanel::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MiscellaneousDataPanel::GetBitmapResource( const wxString &name )
{
    // Bitmap retrieval
     // MiscellaneousDataPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
     // MiscellaneousDataPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MiscellaneousDataPanel::GetIconResource( const wxString &name )
{
    // Icon retrieval
     // MiscellaneousDataPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
     // MiscellaneousDataPanel icon retrieval
}

void MiscellaneousDataPanel::SetStamp( Catalog::Stamp *stamp )
{
    m_stamp = stamp;
    if ( m_stamp->IsOK( ) )
    {
        m_score->SetValue( m_stamp->GetAttr(Catalog::DT_Score) );
        m_accuracy->SetValue( m_stamp->GetAttr(Catalog::DT_Accuracy) );
        m_link->SetValue( m_stamp->GetAttr(Catalog::DT_Link) );
        m_catCodes->SetValue( m_stamp->GetAttr(Catalog::DT_Catalog_Codes) );
        wxString id = m_stamp->GetAttr(Catalog::DT_ID_Nbr);
        id = id.Trim(true);
        id = id.Trim(false);
        id.Replace(":","_");
        id.Replace(" ","_");
        id.Append(".jpg");        
        m_imageName->SetValue( id );

        //       m_description->SetValue( m_stamp->GetDescription() );
    }
}

void MiscellaneousDataPanel::ShowStamp( )
{
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_GOBUTTON
 */

void MiscellaneousDataPanel::OnColnectButtonClick( wxCommandEvent &event )
{
    wxString link = m_link->GetValue( );
    wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s", link );
    system( cmd.fn_str( ) );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_GOBUTTON in
    //MiscellaneousData.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_GOBUTTON in
    //MiscellaneousData.
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void MiscellaneousDataPanel::OnMysticButtonClick( wxCommandEvent &event )
{
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in
    //MiscellaneousData.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in
    //MiscellaneousData.
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NPMBUTTON
 */

void MiscellaneousDataPanel::OnNPMButtonClick( wxCommandEvent &event )
{
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NPMBUTTON in
    //MiscellaneousData.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NPMBUTTON in
    //MiscellaneousData.
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_EBAYBUTTON
 */

void MiscellaneousDataPanel::OneBayButtonClick( wxCommandEvent &event )
{
    //     wxString link = m_link->GetValue();
    //     wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s",
    //     link); system ( cmd.fn_str() );
    // "https://www.ebay.com/sch/i.html?_from=R40&_nkw=us+stamps+%s&_sacat=261&LH_TitleDesc=0&_osacat=261&_odkw=us+stamps"
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_EBAYBUTTON in
    //MiscellaneousData.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_EBAYBUTTON in
    //MiscellaneousData.
}