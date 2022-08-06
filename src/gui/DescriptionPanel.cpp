/**
 * @file DescriptionPanel.cpp
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
#include "DescriptionPanel.h"
#include "IdentificationPanel.h"
#include "ImagePanel.h"
#include "InventoryPanel.h"
#include "MiscellaneousDataPanel.h"
#include "Settings.h"
#include "Stamp.h"
#include "GeneratorData.h"
#include "CatalogData.h"

/*
 * DescriptionPanel type definition
 */
IMPLEMENT_DYNAMIC_CLASS( DescriptionPanel, wxPanel )
; // silly business; The above macro screws up the formatter but the semicolon fixes it

/*
 * DescriptionPanel event table definition
 */

BEGIN_EVENT_TABLE( DescriptionPanel, wxPanel )

// DescriptionPanel event table entries
EVT_SLIDER( ID_ZOOMSLIDER, DescriptionPanel::OnZoomsliderUpdated )
EVT_TEXT( ID_DESCRIPTIONTEXTCTRL, DescriptionPanel::OnDescriptionTextctrlTextUpdated )
EVT_TEXT( ID_BKGNDTEXTCTRL, DescriptionPanel::OnBkGndTextUpdated )
EVT_TEXT_MAXLEN( ID_BKGNDTEXTCTRL, DescriptionPanel::OnBkgndtextctrlMaxLen )
// DescriptionPanel event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
* DescriptionPanel constructors
*/

DescriptionPanel::DescriptionPanel( void ) { Init( ); }

/****************************************************/

DescriptionPanel::DescriptionPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * DescriptionPanel creator
 ***************************************************************/

bool DescriptionPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    // DescriptionPanel creation
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
    // DescriptionPanel creation
    return true;
}

/*
 * DescriptionPanel destructor
 ***************************************************************/

DescriptionPanel::~DescriptionPanel( void )
{
    // DescriptionPanel destruction
    // DescriptionPanel destruction
}

/*
 * Member initialisation
 ***************************************************************/

void DescriptionPanel::Init( void )
{
    // DescriptionPanel member initialisation
    m_identificationPanel = NULL;
    m_zoomSlider = NULL;
    m_stampImage = NULL;
    m_inventoryPanel = NULL;
    m_characteristicsPanel = NULL;
    m_miscellaneousDataPanel = NULL;
//$    m_description = NULL;
//$    m_bkgndText = NULL;
    // DescriptionPanel member initialisation
    m_stamp = NULL;
}

/*
 * Control creation for DescriptionPanel
 ***************************************************************/

void DescriptionPanel::CreateControls( void )
{
    // DescriptionPanel content construction

    DescriptionPanel* itemPanel1 = this;

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
//$        wxMouseEventHandler( DescriptionPanel::OnLeaveWindow ),
//$        NULL, this );
    // DescriptionPanel content construction
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

void DescriptionPanel::OnBkgndtextctrlMaxLen( wxCommandEvent& event )
{
    // wxEVT_COMMAND_TEXT_MAXLEN event handler for ID_BKGNDTEXTCTRL in
    // DescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_TEXT_MAXLEN event handler for ID_BKGNDTEXTCTRL in
    // DescriptionPanel.
}

/*
 *
 *
 * wxEVT_LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL
 ***************************************************************/

void DescriptionPanel::OnLeaveWindow( wxMouseEvent& event )
{
    // wxEVT_LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL in
    // DescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL in
    // DescriptionPanel.
}

/*
 *
 *
 * Should we show tooltips?
 ***************************************************************/

bool DescriptionPanel::ShowToolTips( void ) { return true; }

/*
 *
 *
 * Get bitmap resources
 ***************************************************************/

wxBitmap DescriptionPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    // DescriptionPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // DescriptionPanel bitmap retrieval
}

/*
 *
 *
 * Get icon resources
 ***************************************************************/

wxIcon DescriptionPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
    // DescriptionPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // DescriptionPanel icon retrieval
}

/*
 * UpdateStatus
 *
 ***************************************************************/

void DescriptionPanel::UpdateStatus( void )
{
    m_identificationPanel->UpdateStatus( );
}

/*
 *
 * wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER
 *
 ***************************************************************/

void DescriptionPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double )val / 100.0;
    m_stampImage->SetZoom( zoom );

    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // DescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER in
    // DescriptionPanel.
}

/*
 *
 *
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_BKGNDTEXTCTRL
 ***************************************************************/

void DescriptionPanel::OnBkGndTextUpdated( wxCommandEvent& event )
{
    //$ if ( m_bkgndText->IsModified( ) )
    //$ {
    //$     wxSize i = m_bkgndText->GetMaxClientSize( );
    //$     wxString strSel = m_bkgndText->GetValue( );
    //$     m_stamp->SetBackground( strSel );
    //$     m_bkgndText->SetModified( false );
    //$ }

    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_BKGNDTEXTCTRL in
    // DescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_BKGNDTEXTCTRL in
    // DescriptionPanel.
}

/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_DESCRIPTIONTEXTCTRL
 ***************************************************************/

void DescriptionPanel::OnDescriptionTextctrlTextUpdated( wxCommandEvent& event )
{
    //$ if ( m_description->IsModified( ) )
    //$ {
    //$     wxSize i = m_description->GetMaxClientSize( );
    //$     wxString strSel = m_description->GetValue( );
    //$     m_stamp->SetDescription( strSel );
    //$     m_description->SetModified( false );
    //$ }
    // wxEVT_COMMAND_TEXT_UPDATED event handler for
    // ID_DESCRIPTIONTEXTCTRL in DescriptionPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_TEXT_UPDATED event handler for ID_DESCRIPTIONTEXTCTRL
    // in DescriptionPanel.
}

/*
 *
 * initializes the DescriptionPanel with new stamp values
 ***************************************************************/

void DescriptionPanel::SetStamp( wxXmlNode* stamp )
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

void DescriptionPanel::SetDataEditable( bool val )
{
    m_inventoryPanel->SetDataEditable( val );
    m_catalogCodePanel->SetDataEditable( val );
    m_characteristicsPanel->SetDataEditable( val );
    m_identificationPanel->SetDataEditable( val );
    m_miscellaneousDataPanel->SetDataEditable( val );
//$    m_bkgndText->SetEditable( val );
//$    m_description->SetEditable( val );
}