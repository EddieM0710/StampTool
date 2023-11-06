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

 //#include "CatalogCodePanel.h"
#include "catalog/CatalogData.h"
#include "CharacteristicsPanel.h"
#include "Defs.h"
#include "StampDescriptionPanel.h"
#include "IdentificationPanel.h"
#include "ImagePanel.h"
#include "InventoryPanel.h"
 //#include "MiscellaneousDataPanel.h"
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

EVT_SPLITTER_SASH_POS_CHANGED( ID_HORIZONTALLITTERWINDOW, StampDescriptionPanel::OnNotebooksplitterwindowSashPosChanged )

EVT_SLIDER( ID_ZOOMSLIDER, StampDescriptionPanel::OnZoomsliderUpdated )
EVT_TEXT( ID_DESCRIPTIONTEXTCTRL, StampDescriptionPanel::OnDescriptionTextctrlTextUpdated )
EVT_TEXT( ID_BKGNDTEXTCTRL, StampDescriptionPanel::OnBkGndTextUpdated )
EVT_TEXT_MAXLEN( ID_BKGNDTEXTCTRL, StampDescriptionPanel::OnBkgndtextctrlMaxLen )
//EVT_SPLITTER_SASH_POS_CHANGED( ID_HORIZONTALLITTERWINDOW, StampDescriptionPanel::OnSplitterwindowSashPosChanged )

END_EVENT_TABLE( )

//-------

StampDescriptionPanel::StampDescriptionPanel( void ) {
    Init( );
}

//-------



StampDescriptionPanel::StampDescriptionPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//-------


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

//-------


StampDescriptionPanel::~StampDescriptionPanel( void )
{
    // StampDescriptionPanel destruction
    // StampDescriptionPanel destruction
}

//-------

void StampDescriptionPanel::Clear( )
{

    m_identificationPanel->Clear( );
    m_zoomSlider->SetValue( 100 );
    m_stampImage->Clear( );
    m_inventoryPanel->Clear( );
}

//-------

void StampDescriptionPanel::Init( void )
{
    // StampDescriptionPanel member initialisation
    m_identificationPanel = NULL;
    m_zoomSlider = NULL;
    m_stampImage = NULL;
    m_inventoryPanel = NULL;
}

//-------

void StampDescriptionPanel::CreateControls( void )
{
    StampDescriptionPanel* thisPanel = this;

    wxBoxSizer* topVerticalSizer = new wxBoxSizer( wxVERTICAL );
    thisPanel->SetSizer( topVerticalSizer );

    wxBoxSizer* topHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    topVerticalSizer->Add( topHorizontalSizer, 1, wxGROW | wxALL, 5 );

    wxSplitterWindow* horizontalSplitterWindow = new wxSplitterWindow(
        thisPanel, ID_HORIZONTALLITTERWINDOW, wxDefaultPosition,
        wxDefaultSize, wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    horizontalSplitterWindow->SetSashPosition( 100 );
    horizontalSplitterWindow->SetMinimumPaneSize( 50 );
    horizontalSplitterWindow->SetSashGravity( 0.2 );


    wxPanel* stampAndImagePanel = new wxPanel( horizontalSplitterWindow, ID_HORIZONTALPLITTERWINDOW, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    stampAndImagePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* stampAndImageVerticalSizer = new wxBoxSizer( wxVERTICAL );
    stampAndImagePanel->SetSizer( stampAndImageVerticalSizer );

    wxBoxSizer* stampAndImageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );

    stampAndImageVerticalSizer->Add( stampAndImageHorizontalSizer, 1, wxGROW | wxALL, 5 );

    wxSplitterWindow* stampAndImageVerticalSplitterWindow = new wxSplitterWindow(
        stampAndImagePanel, ID_DESCRIPTIONSPLITTERWINDOW, wxDefaultPosition,
        wxDefaultSize, wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    stampAndImageVerticalSplitterWindow->SetSashPosition( 100 );
    stampAndImageVerticalSplitterWindow->SetMinimumPaneSize( 100 );
    stampAndImageVerticalSplitterWindow->SetSashGravity( 0.2 );

    wxBoxSizer* vSizer = new wxBoxSizer( wxVERTICAL );
    stampAndImageVerticalSplitterWindow->SetSizer( vSizer );

    wxBoxSizer* hSizer = new wxBoxSizer( wxHORIZONTAL );
    vSizer->Add( hSizer, 1, wxGROW | wxALL, 5 );


    m_identificationPanel = new IdentificationPanel(
        stampAndImageVerticalSplitterWindow,
        ID_IDENTIFICATIONPANELFORIEGN, wxDefaultPosition,
        wxDefaultSize, 0 );
    hSizer->Add( m_identificationPanel, 1, wxGROW | wxALL, 5 );

    //   wxBoxSizer* identificationPanelVerticalSizer = new wxBoxSizer( wxVERTICAL );
    //   m_identificationPanel->SetSizer( identificationPanelVerticalSizer );

    //   wxBoxSizer* identificationPanelHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );

    //   identificationPanelVerticalSizer->Add( identificationPanelHorizontalSizer, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

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
    stampImageHorizontalSizer->Add( m_zoomSlider, 1, wxGROW | wxALL, 0 );

    m_stampImage = new ImagePanel( StampImagePanel, ID_STAMPIMAGEPANEL, wxDefaultPosition,
        wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_stampImage->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    stampImageVerticalSizer->Add( m_stampImage, 1, wxGROW | wxALL, 0 );

    stampAndImageVerticalSplitterWindow->SplitVertically( m_identificationPanel, StampImagePanel, 200 );
    stampAndImageVerticalSizer->Add( stampAndImageVerticalSplitterWindow, 1, wxGROW | wxALL, 5 );

    m_inventoryPanel = new InventoryPanel( horizontalSplitterWindow, ID_INVENTORYPANEL, wxDefaultPosition,
        wxDefaultSize, wxSIMPLE_BORDER );

    horizontalSplitterWindow->SplitHorizontally( stampAndImagePanel, m_inventoryPanel, 500 );
    topHorizontalSizer->Add( horizontalSplitterWindow, 1, wxGROW | wxALL, 5 );


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

//-------

void StampDescriptionPanel::OnSplitterwindowSashPosChanged( wxSplitterEvent& event )
{
    Fit( );
    Layout( );
    event.Skip( );
}

//-------

void StampDescriptionPanel::OnBkgndtextctrlMaxLen( wxCommandEvent& event )
{
    event.Skip( );
}

//-------

void StampDescriptionPanel::OnLeaveWindow( wxMouseEvent& event )
{
    event.Skip( );
}

//-------

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

//-------

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

//-------

void StampDescriptionPanel::OnNotebooksplitterwindowSashPosChanged( wxSplitterEvent& event )
{
    int pos = event.GetSashPosition( );
    event.Skip( );
}

//-------

void StampDescriptionPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double ) val / 100.0;
    m_stampImage->SetZoom( zoom );

    event.Skip( );
}

//-------

void StampDescriptionPanel::SetDataEditable( bool val )
{
    m_inventoryPanel->SetDataEditable( val );
    m_identificationPanel->SetDataEditable( val );
}

//-------

bool StampDescriptionPanel::ShowToolTips( void ) {
    return true;
}

//-------

void StampDescriptionPanel::UpdateStatus( void )
{
    m_inventoryPanel->UpdateInventoryGrid( );
}

//-------

void StampDescriptionPanel::UpdatePanel( )
{
    Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );

    m_inventoryPanel->UpdateInventoryGrid( );
    m_identificationPanel->UpdatePanel( );
    wxString imageFile = stamp.FindImageName( );
    m_stampImage->SetBitmap( imageFile );
}

//-------

