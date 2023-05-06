/**
 * @file StampDescriptionPanel.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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
 *
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/imaglist.h"

#include "CatalogCodePanel.h"
#include "catalog/CatalogData.h"
#include "CharacteristicsPanel.h"
#include "Defs.h"
#include "StampDescriptionPanel.h"
#include "IdentificationPanel.h"
#include "ImagePanel.h"
#include "InventoryPanel.h"
#include "MiscellaneousDataPanel.h"
#include "Settings.h"
#include "Stamp.h"
#include "AppData.h"
#include "CatalogVolume.h"

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



StampDescriptionPanel::StampDescriptionPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * StampDescriptionPanel creator
 */

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

    return true;
}

/*
 * StampDescriptionPanel destructor
 */

StampDescriptionPanel::~StampDescriptionPanel( void )
{
    // StampDescriptionPanel destruction
    // StampDescriptionPanel destruction
}

/*
 * Member initialisation
 */

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
    //m_stamp = NULL;
}

/*
 * Control creation for StampDescriptionPanel
 */

void StampDescriptionPanel::CreateControls( void )
{
    // StampDescriptionPanel content construction

    StampDescriptionPanel* thisPanel = this;

    wxBoxSizer* topVerticalSizer = new wxBoxSizer( wxVERTICAL );
    thisPanel->SetSizer( topVerticalSizer );

    wxBoxSizer* topHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    topVerticalSizer->Add( topHorizontalSizer, 1, wxGROW | wxALL, 5 );

    wxSplitterWindow* horizontalSplitterWindow = new wxSplitterWindow(
        thisPanel, ID_HORIZONTALLITTERWINDOW, wxDefaultPosition,
        wxSize( 100, 400 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    horizontalSplitterWindow->SetSashPosition( 400 );
    horizontalSplitterWindow->SetMinimumPaneSize( 300 );
    horizontalSplitterWindow->SetSashGravity( 0.2 );


    wxPanel* stampAndImagePanel = new wxPanel( horizontalSplitterWindow, ID_HORIZONTALPLITTERWINDOW, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    stampAndImagePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* stampAndImageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    stampAndImagePanel->SetSizer( stampAndImageHorizontalSizer );

    wxBoxSizer* stampAndImageVerticalSizer = new wxBoxSizer( wxVERTICAL );
    stampAndImageHorizontalSizer->Add( stampAndImageVerticalSizer, 1, wxGROW | wxALL, 5 );

    wxSplitterWindow* stampAndImageVerticalSplitterWindow = new wxSplitterWindow(
        stampAndImagePanel, ID_DESCRIPTIONSPLITTERWINDOW, wxDefaultPosition,
        wxSize( 200, 200 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    stampAndImageVerticalSplitterWindow->SetSashPosition( 500 );
    stampAndImageVerticalSplitterWindow->SetMinimumPaneSize( 100 );
    stampAndImageVerticalSplitterWindow->SetSashGravity( 0.2 );


    m_identificationPanel = new IdentificationPanel(
        stampAndImageVerticalSplitterWindow,
        ID_IDENTIFICATIONPANELFORIEGN, wxDefaultPosition,
        wxDefaultSize, 0 );


    wxBoxSizer* identificationPanelHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    m_identificationPanel->SetSizer( identificationPanelHorizontalSizer );

    wxBoxSizer* identificationPanelVerticalSizer = new wxBoxSizer( wxVERTICAL );

    identificationPanelHorizontalSizer->Add( identificationPanelVerticalSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );





    wxPanel* StampImagePanel = new wxPanel( stampAndImageVerticalSplitterWindow,
        ID_STAMPDESCRIPTIONPANEL, wxDefaultPosition,
        wxDefaultSize, wxTAB_TRAVERSAL );
    StampImagePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );


    wxBoxSizer* stampImageVerticalSizer = new wxBoxSizer( wxVERTICAL );
    StampImagePanel->SetSizer( stampImageVerticalSizer );

    wxBoxSizer* stampImageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    stampImageVerticalSizer->Add( stampImageHorizontalSizer, 0, wxGROW | wxALL, 5 );


    wxStaticText* zoomStaticText = new wxStaticText(
        StampImagePanel, wxID_STATIC, _( "Zoom" ), wxDefaultPosition, wxDefaultSize, 0 );
    stampImageHorizontalSizer->Add( zoomStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_zoomSlider =
        new wxSlider( StampImagePanel, ID_ZOOMSLIDER, 100, 25, 300, wxDefaultPosition,
            wxDefaultSize, wxSL_HORIZONTAL );
    stampImageHorizontalSizer->Add( m_zoomSlider, 0, wxGROW | wxALL, 0 );

    m_stampImage =
        new ImagePanel( StampImagePanel, ID_STAMPIMAGEPANEL, wxDefaultPosition,
            wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_stampImage->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    stampImageVerticalSizer->Add( m_stampImage, 1, wxGROW | wxALL, 0 );



    stampAndImageVerticalSplitterWindow->SplitVertically( m_identificationPanel, StampImagePanel, 300 );
    stampAndImageVerticalSizer->Add( stampAndImageVerticalSplitterWindow, 1, wxGROW | wxALL, 5 );



    wxPanel* notebookPanel = new wxPanel( horizontalSplitterWindow, ID_NOTEBOOKPANEL,
        wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    notebookPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* notebookPanelVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookPanel->SetSizer( notebookPanelVerticalSizer );

    wxBoxSizer* notebookPanelHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    notebookPanelVerticalSizer->Add( notebookPanelHorizontalSizer, 1, wxGROW | wxALL, 5 );



    wxNotebook* descriptionNotebook =
        new wxNotebook( notebookPanel, ID_DESCRIPTIONLNOTEBOOK,
            wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    m_inventoryPanel =
        new InventoryPanel( descriptionNotebook, ID_INVENTORYPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );

    descriptionNotebook->AddPage( m_inventoryPanel, _( "Inventory" ) );



    m_catalogCodePanel =
        new CatalogCodePanel( descriptionNotebook, ID_CATALOGCODEPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );

    descriptionNotebook->AddPage( m_catalogCodePanel, _( "Catalog Codes" ) );



    m_characteristicsPanel = new CharacteristicsPanel(
        descriptionNotebook, ID_CHARACTERISTICSWINDOW, wxDefaultPosition,
        wxSize( 100, 100 ), wxSIMPLE_BORDER );

    descriptionNotebook->AddPage( m_characteristicsPanel, _( "Characteristics" ) );

    m_miscellaneousDataPanel = new MiscellaneousDataPanel(
        descriptionNotebook, ID_MISCELLANEOUSDATAFORIEGN, wxDefaultPosition,
        wxDefaultSize, wxSIMPLE_BORDER | wxTAB_TRAVERSAL );
    m_miscellaneousDataPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    descriptionNotebook->AddPage( m_miscellaneousDataPanel, _( "Miscellaneous" ) );



    notebookPanelHorizontalSizer->Add( descriptionNotebook, 1, wxGROW | wxALL, 5 );

    //$     wxScrolledWindow* itemScrolledWindow1 = new wxScrolledWindow( 
    //$         descriptionNotebook, ID_DESCRIPTIONSCROLLEDWINDOW, wxDefaultPosition, 
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
    //$      descriptionNotebook->AddPage( itemScrolledWindow1, _( "Description" ) );

        //$ wxPanel* itemPanel16 = 
        //$     new wxPanel( descriptionNotebook, ID_BACKGROUNDPANEL1, wxDefaultPosition, 
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

        //$ descriptionNotebook->AddPage( itemPanel16, _( "Background" ) );


    horizontalSplitterWindow->SplitHorizontally( stampAndImagePanel, notebookPanel, 500 );
    topHorizontalSizer->Add( horizontalSplitterWindow, 1, wxGROW | wxALL, 5 );


    //stampAndImageVerticalSplitterWindow->SplitVertically( m_identificationPanel, StampImagePanel, 400 );

    // wxNotebook* descriptionNotebook = 
    //     new wxNotebook( horizontalSplitterWindow, ID_DESCRIPTIONLNOTEBOOK, 
    //         wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    // horizontalSplitterWindow->SplitHorizontally( stampAndImageVerticalSplitterWindow, descriptionNotebook, 800 );
    // horizontalSplitterWindow->SetSashPosition( 600 );
    // topVerticalSizer->Add( horizontalSplitterWindow, 3, wxGROW | wxALL, 5 );

    // Connect events and objects
//$    m_bkgndText->Connect( ID_BKGNDTEXTCTRL,  LEAVE_WINDOW, 
//$        wxMouseEventHandler( StampDescriptionPanel::OnLeaveWindow ), 
//$        NULL, this );
    // StampDescriptionPanel content construction
 //$     m_bkgndText->SetEditable( GetSettings( )->IsCatalogVolumeEditable( )  );
  //$    m_description->SetEditable( GetSettings( )->IsCatalogVolumeEditable( )  );


    // // display a random image until one is selected
    wxString filename;
    // if (  GetCatalogVolume( ) )
    // { 
    //     filename = GetSettings( )->GetImageDirectory( );
    //     filename.Append( "/4503.jpg" );
    // }
    // else 
    // { 
    filename = "";
    //     }
    m_stampImage->SetBitmap( filename );
}


/*
 *
 *
 *  COMMAND_TEXT_MAXLEN event handler for ID_BKGNDTEXTCTRL
 */

void StampDescriptionPanel::OnBkgndtextctrlMaxLen( wxCommandEvent& event )
{
    event.Skip( );
}

/*
 *
 *
 *  LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL
 */

void StampDescriptionPanel::OnLeaveWindow( wxMouseEvent& event )
{
    event.Skip( );
}

/*
 *
 *
 *
 */

bool StampDescriptionPanel::ShowToolTips( void ) { return true; }




/*
 * UpdateStatus
 *
 */

void StampDescriptionPanel::UpdateStatus( void )
{
    m_identificationPanel->UpdateStatus( );
}

/*
 *
 *  COMMAND_SLIDER_UPDATED event handler for ID_SLIDER
 *
 */

void StampDescriptionPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double ) val / 100.0;
    m_stampImage->SetZoom( zoom );

    event.Skip( );
}

/*
 *
 *
 *   ID_BKGNDTEXTCTRL
 */

void StampDescriptionPanel::OnBkGndTextUpdated( wxCommandEvent& event )
{
    //$ if ( m_bkgndText->IsModified( ) )
    //$ { 
    //$     wxSize i = m_bkgndText->GetMaxClientSize( );
    //$     wxString strSel = m_bkgndText->GetValue( );
    //$     m_stamp->SetBackground( strSel );
    //$     m_bkgndText->SetModified( false );
    //$ }

    event.Skip( );
}

/*
 *   ID_DESCRIPTIONTEXTCTRL
 */

void StampDescriptionPanel::OnDescriptionTextctrlTextUpdated( wxCommandEvent& event )
{
    //$ if ( m_description->IsModified( ) )
    //$ { 
    //$     wxSize i = m_description->GetMaxClientSize( );
    //$     wxString strSel = m_description->GetValue( );
    //$     m_stamp->SetDescription( strSel );
    //$     m_description->SetModified( false );
    //$ }
    //  
    event.Skip( );
}

/*
 *
 * initializes the StampDescriptionPanel with new stamp values
 */

void StampDescriptionPanel::UpdatePanel( )//wxXmlNode* stamp )
{
    Catalog::Entry* stamp = GetCatalogData( )->GetCurrentStamp( );

    m_inventoryPanel->UpdatePanel( );
    m_catalogCodePanel->UpdatePanel( );
    m_characteristicsPanel->UpdatePanel( );
    m_identificationPanel->UpdatePanel( );
    m_miscellaneousDataPanel->UpdatePanel( );
    wxString imageFile = GetCatalogData( )->GetImageFilename( stamp->GetID( ) );
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