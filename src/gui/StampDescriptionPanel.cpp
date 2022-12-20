/**
 * @file StampDescriptionPanel.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
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

#include "wx/imaglist.h"

#include "CatalogCodePanel.h"
#include "CharacteristicsPanel.h"
#include "Defs.h"
#include "StampDescriptionPanel.h"
#include "IdentificationPanel.h"
#include "ImagePanel.h"
#include "InventoryPanel.h"
#include "MiscellaneousDataPanel.h"
#include "Settings.h"
#include "Stamp.h"
#include "GeneratorData.h"
#include "CatalogData.h"

/*
 * StampDescriptionPanel type definition
 */
IMPLEMENT_DYNAMIC_CLASS( StampDescriptionPanel, wxPanel )
; // silly business; The above macro screws up the formatter but the semicolon fixes it

/*
 * StampDescriptionPanel event table definition
 */

BEGIN_EVENT_TABLE( StampDescriptionPanel, wxPanel )

// StampDescriptionPanel event table entries
EVT_SLIDER( ID_ZOOMSLIDER, StampDescriptionPanel::OnZoomsliderUpdated )
EVT_TEXT( ID_DESCRIPTIONTEXTCTRL, StampDescriptionPanel::OnDescriptionTextctrlTextUpdated )
EVT_TEXT( ID_BKGNDTEXTCTRL, StampDescriptionPanel::OnBkGndTextUpdated )
EVT_TEXT_MAXLEN( ID_BKGNDTEXTCTRL, StampDescriptionPanel::OnBkgndtextctrlMaxLen )
// StampDescriptionPanel event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
* StampDescriptionPanel constructors
*/

StampDescriptionPanel::StampDescriptionPanel( void ) { Init( ); }

/****************************************************/

StampDescriptionPanel::StampDescriptionPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * StampDescriptionPanel creator
 ***************************************************************/

bool StampDescriptionPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    // StampDescriptionPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );

    if ( FindWindow( ID_NOTEBOOKSPLITTERWINDOW ) )
        ( ( wxSplitterWindow* )FindWindow( ID_NOTEBOOKSPLITTERWINDOW ) )
        ->SetSashPosition( 200 );
    if ( FindWindow( ID_DESCRIPTIONSPLITTERWINDOW ) )
        ( ( wxSplitterWindow* )FindWindow( ID_DESCRIPTIONSPLITTERWINDOW ) )
        ->SetSashPosition( 250 );
    // StampDescriptionPanel creation
    return true;
}

/*
 * StampDescriptionPanel destructor
 ***************************************************************/

StampDescriptionPanel::~StampDescriptionPanel( void )
{
    // StampDescriptionPanel destruction
    // StampDescriptionPanel destruction
}

/*
 * Member initialisation
 ***************************************************************/

void StampDescriptionPanel::Init( void )
{
    // StampDescriptionPanel member initialisation
    m_identificationPanel = NULL;
    m_zoomSlider = NULL;
    m_stampImage = NULL;
    m_inventoryPanel = NULL;
    m_characteristicsPanel = NULL;
    m_miscellaneousDataPanel = NULL;
//$    m_description = NULL;
//$    m_bkgndText = NULL;
    // StampDescriptionPanel member initialisation
    m_stamp = NULL;
}

/*
 * Control creation for StampDescriptionPanel
 ***************************************************************/

void StampDescriptionPanel::CreateControls( void )
{
    // StampDescriptionPanel content construction

    StampDescriptionPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxHORIZONTAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer2->Add( itemBoxSizer3, 3, wxGROW | wxALL, 0 );

    wxSplitterWindow* itemSplitterWindow1 = new wxSplitterWindow(
        itemPanel1, ID_NOTEBOOKSPLITTERWINDOW, wxDefaultPosition,
        wxSize( 100, 100 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    itemSplitterWindow1->SetMinimumPaneSize( 100 );
    itemSplitterWindow1->SetSashGravity( 0.2 );

    wxSplitterWindow* itemSplitterWindow2 = new wxSplitterWindow(
        itemSplitterWindow1, ID_DESCRIPTIONSPLITTERWINDOW, wxDefaultPosition,
        wxSize( 100, 100 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    itemSplitterWindow2->SetMinimumPaneSize( 100 );
    itemSplitterWindow2->SetSashGravity( 0.2 );

    m_identificationPanel = new IdentificationPanel(
        itemSplitterWindow2, ID_IDENTIFICATIONPANELFORIEGN, wxDefaultPosition,
        wxDefaultSize, 0 );

    wxPanel* itemPanel4 =
        new wxPanel( itemSplitterWindow2, ID_DESCRIPTIONPANEL, wxDefaultPosition,
            wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel4->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxVERTICAL );
    itemPanel4->SetSizer( itemBoxSizer5 );

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer5->Add( itemBoxSizer6, 1, wxGROW | wxALL, 5 );
    
    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer6->Add( itemBoxSizer7, 1, wxGROW | wxALL, 5 );
    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer7->Add( itemBoxSizer8, 0, wxGROW | wxALL, 0 );

    wxStaticText* itemStaticText9 = new wxStaticText(
        itemPanel4, wxID_STATIC, _( "Zoom" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add( itemStaticText9, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_zoomSlider =
        new wxSlider( itemPanel4, ID_ZOOMSLIDER, 100, 25, 300, wxDefaultPosition,
            wxDefaultSize, wxSL_HORIZONTAL );
    itemBoxSizer8->Add( m_zoomSlider, 1, wxGROW | wxALL, 0 );

    m_stampImage =
        new ImagePanel( itemPanel4, ID_STAMPIMAGEPANEL, wxDefaultPosition,
            wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_stampImage->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer7->Add( m_stampImage, 1, wxGROW | wxALL, 0 );

    itemSplitterWindow2->SplitVertically( m_identificationPanel, itemPanel4, 250 );
    wxNotebook* itemNotebook12 =
        new wxNotebook( itemSplitterWindow1, ID_DESCRIPTIONLNOTEBOOK,
            wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    m_inventoryPanel =
        new InventoryPanel( itemNotebook12, ID_INVENTORYPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );

    itemNotebook12->AddPage( m_inventoryPanel, _( "Inventory" ) );

    m_catalogCodePanel =
        new CatalogCodePanel( itemNotebook12, ID_CATALOGCODEPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );

    itemNotebook12->AddPage( m_catalogCodePanel, _( "Catalog Codes" ) );

    m_characteristicsPanel = new CharacteristicsPanel(
        itemNotebook12, ID_CHARACTERISTICSWINDOW, wxDefaultPosition,
        wxSize( 100, 100 ), wxSIMPLE_BORDER );

    itemNotebook12->AddPage( m_characteristicsPanel, _( "Characteristics" ) );

     m_miscellaneousDataPanel = new MiscellaneousDataPanel(
        itemNotebook12, ID_MISCELLANEOUSDATAFORIEGN, wxDefaultPosition,
        wxDefaultSize, wxSIMPLE_BORDER | wxTAB_TRAVERSAL );
     m_miscellaneousDataPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

     itemNotebook12->AddPage( m_miscellaneousDataPanel, _( "Miscellaneous" ) );

//$     wxScrolledWindow* itemScrolledWindow1 = new wxScrolledWindow(
//$         itemNotebook12, ID_DESCRIPTIONSCROLLEDWINDOW, wxDefaultPosition,
//$         wxDefaultSize, wxSIMPLE_BORDER | wxHSCROLL | wxVSCROLL );
//$     itemScrolledWindow1->SetScrollbars( 1, 1, 0, 0 );
//$     wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
//$     itemScrolledWindow1->SetSizer( itemBoxSizer4 );

//$     wxBoxSizer* itemBoxSizer9 = new wxBoxSizer( wxVERTICAL );
//$     itemBoxSizer4->Add( itemBoxSizer9, 1, wxGROW | wxALL, 0 );
//$     m_description =
//$        new wxTextCtrl( itemScrolledWindow1, ID_DESCRIPTIONTEXTCTRL, wxEmptyString,
//$            wxDefaultPosition, wxSize( -1, 100 ), wxTE_MULTILINE );
//$      itemBoxSizer9->Add( m_description, 1, wxGROW | wxALL, 0 );

//$      itemScrolledWindow1->FitInside( );
//$      itemNotebook12->AddPage( itemScrolledWindow1, _( "Description" ) );

    //$ wxPanel* itemPanel16 =
    //$     new wxPanel( itemNotebook12, ID_BACKGROUNDPANEL1, wxDefaultPosition,
    //$         wxDefaultSize, wxSIMPLE_BORDER | wxTAB_TRAVERSAL );
    //$ itemPanel16->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    //$ wxBoxSizer* itemBoxSizer17 = new wxBoxSizer( wxVERTICAL );
    //$ itemPanel16->SetSizer( itemBoxSizer17 );

    //$ wxScrolledWindow* itemScrolledWindow19 = new wxScrolledWindow(
    //$     itemPanel16, ID_BKGNDSCROLLEDWINDOW, wxDefaultPosition, wxSize( 100, -1 ),
    //$     wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );
    //$ itemBoxSizer17->Add( itemScrolledWindow19, 1, wxGROW | wxALL, 0 );
    //$ itemScrolledWindow19->SetScrollbars( 1, 1, 0, 0 );
    //$ wxBoxSizer* itemBoxSizer20 = new wxBoxSizer( wxHORIZONTAL );
    //$ itemScrolledWindow19->SetSizer( itemBoxSizer20 );

    //$ wxBoxSizer* itemBoxSizer21 = new wxBoxSizer( wxVERTICAL );
    //$ itemBoxSizer20->Add( itemBoxSizer21, 1, wxGROW | wxALL, 0 );
    //$ m_bkgndText =
    //$     new wxTextCtrl( itemScrolledWindow19, ID_BKGNDTEXTCTRL, wxEmptyString,
    //$         wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    //$ itemBoxSizer21->Add( m_bkgndText, 1, wxGROW | wxALL, 5 );

    //$ itemScrolledWindow19->FitInside( );

    //$ itemNotebook12->AddPage( itemPanel16, _( "Background" ) );

    itemSplitterWindow1->SplitHorizontally( itemSplitterWindow2, itemNotebook12,
        200 );
    itemBoxSizer3->Add( itemSplitterWindow1, 1, wxGROW | wxALL, 5 );

    // Connect events and objects
//$    m_bkgndText->Connect( ID_BKGNDTEXTCTRL, wxEVT_LEAVE_WINDOW,
//$        wxMouseEventHandler( StampDescriptionPanel::OnLeaveWindow ),
//$        NULL, this );
    // StampDescriptionPanel content construction
 //$     m_bkgndText->SetEditable( GetSettings()->IsCatalogDataEditable()  );
  //$    m_description->SetEditable( GetSettings()->IsCatalogDataEditable()  );


    // display a random image until one is selected
    wxString filename;
    if (  GetCatalogData( ) )
    {
        filename = GetSettings( )->GetImageDirectory( );
        filename.Append( "/4503.jpg" );
    }
    else 
    {
        filename = "";
        }
    m_stampImage->SetBitmap( filename );
}


/*
 *
 *
 * wxEVT_COMMAND_TEXT_MAXLEN event handler for ID_BKGNDTEXTCTRL
 ***************************************************************/

void StampDescriptionPanel::OnBkgndtextctrlMaxLen( wxCommandEvent& event )
{
    // wxEVT_COMMAND_TEXT_MAXLEN event handler for ID_BKGNDTEXTCTRL in
    // StampDescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_TEXT_MAXLEN event handler for ID_BKGNDTEXTCTRL in
    // StampDescriptionPanel.
}

/*
 *
 *
 * wxEVT_LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL
 ***************************************************************/

void StampDescriptionPanel::OnLeaveWindow( wxMouseEvent& event )
{
    // wxEVT_LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL in
    // StampDescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL in
    // StampDescriptionPanel.
}

/*
 *
 *
 * Should we show tooltips?
 ***************************************************************/

bool StampDescriptionPanel::ShowToolTips( void ) { return true; }

/*
 *
 *
 * Get bitmap resources
 ***************************************************************/

wxBitmap StampDescriptionPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    // StampDescriptionPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // StampDescriptionPanel bitmap retrieval
}

/*
 *
 *
 * Get icon resources
 ***************************************************************/

wxIcon StampDescriptionPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
    // StampDescriptionPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // StampDescriptionPanel icon retrieval
}

/*
 * UpdateStatus
 *
 ***************************************************************/

void StampDescriptionPanel::UpdateStatus( void )
{
    m_identificationPanel->UpdateStatus( );
}

/*
 *
 * wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER
 *
 ***************************************************************/

void StampDescriptionPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double )val / 100.0;
    m_stampImage->SetZoom( zoom );

    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // StampDescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // StampDescriptionPanel.
}

/*
 *
 *
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_BKGNDTEXTCTRL
 ***************************************************************/

void StampDescriptionPanel::OnBkGndTextUpdated( wxCommandEvent& event )
{
    //$ if ( m_bkgndText->IsModified( ) )
    //$ {
    //$     wxSize i = m_bkgndText->GetMaxClientSize( );
    //$     wxString strSel = m_bkgndText->GetValue( );
    //$     m_stamp->SetBackground( strSel );
    //$     m_bkgndText->SetModified( false );
    //$ }

    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_BKGNDTEXTCTRL in
    // StampDescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_BKGNDTEXTCTRL in
    // StampDescriptionPanel.
}

/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_DESCRIPTIONTEXTCTRL
 ***************************************************************/

void StampDescriptionPanel::OnDescriptionTextctrlTextUpdated( wxCommandEvent& event )
{
    //$ if ( m_description->IsModified( ) )
    //$ {
    //$     wxSize i = m_description->GetMaxClientSize( );
    //$     wxString strSel = m_description->GetValue( );
    //$     m_stamp->SetDescription( strSel );
    //$     m_description->SetModified( false );
    //$ }
    // wxEVT_COMMAND_TEXT_UPDATED event handler for
    // ID_DESCRIPTIONTEXTCTRL in StampDescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_DESCRIPTIONTEXTCTRL
    // in StampDescriptionPanel.
}

/*
 *
 * initializes the StampDescriptionPanel with new stamp values
 ***************************************************************/

void StampDescriptionPanel::SetStamp( wxXmlNode* stamp )
{
    if (m_stamp)
    {
        delete m_stamp;
    }
    m_stamp = new Catalog::Entry(stamp);
//$    m_bkgndText->ChangeValue( m_stamp->GetBackground( ) );
//$    m_description->ChangeValue( m_stamp->GetDescription( ) );

    m_inventoryPanel->SetStamp( m_stamp );
    m_catalogCodePanel->SetStamp( m_stamp );
    m_characteristicsPanel->SetStamp( m_stamp );
    m_identificationPanel->SetStamp( m_stamp );
    m_miscellaneousDataPanel->SetStamp( m_stamp );

    wxString imageFile = GetGeneratorData( )->GetImageFilename( m_stamp->GetID( ) );
    m_stampImage->SetBitmap( imageFile );
}

void StampDescriptionPanel::SetDataEditable( bool val )
{
    m_inventoryPanel->SetDataEditable( val );
    m_catalogCodePanel->SetDataEditable( val );
    m_characteristicsPanel->SetDataEditable( val );
    m_identificationPanel->SetDataEditable( val );
    m_miscellaneousDataPanel->SetDataEditable( val );
//$    m_bkgndText->SetEditable( val );
//$    m_description->SetEditable( val );
}