/**
 * @file MiscellaneousDataPanel.cpp
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

#include <curl/curl.h>
#include <wx/clipbrd.h>
#include <wx/file.h>
#include <wx/url.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h> 
 //#include <wx/webrequest.h>

#include "LabeledTextBox.h"
#include "MiscellaneousDataPanel.h"
#include "Defs.h"
#include "utils/Settings.h"
#include "catalog/CatalogData.h"
//#include "gui/WebViewPanel.h"
//#include "StampToolApp.h"

//wxDECLARE_APP( StampToolApp );



IMPLEMENT_DYNAMIC_CLASS( MiscellaneousDataPanel, wxPanel )
; // silly business; The above macro screws up the formatter


BEGIN_EVENT_TABLE( MiscellaneousDataPanel, wxPanel )

EVT_BUTTON( ID_MYSTICBUTTON, MiscellaneousDataPanel::OnMysticButtonClick )
EVT_BUTTON( ID_COLNECTBUTTON, MiscellaneousDataPanel::OnColnectButtonClick )
EVT_BUTTON( ID_EBAYBUTTON, MiscellaneousDataPanel::OneBayButtonClick )
EVT_BUTTON( ID_NPMBUTTON, MiscellaneousDataPanel::OnNPMButtonClick )
EVT_BUTTON( ID_SITETBUTTON, MiscellaneousDataPanel::OnSiteButtonClick )


END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

MiscellaneousDataPanel::MiscellaneousDataPanel( )
{
    Init( );
}

MiscellaneousDataPanel::MiscellaneousDataPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}


bool MiscellaneousDataPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
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


MiscellaneousDataPanel::~MiscellaneousDataPanel( )
{
}

void MiscellaneousDataPanel::Init( )
{
    m_link = NULL;
    m_catCodes = NULL;
    m_imageName = NULL;

}

void MiscellaneousDataPanel::CreateControls( )
{

    MiscellaneousDataPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer3, 0, wxGROW | wxALL, 0 );

    m_link = new LabeledTextBox( itemPanel1, ID_LINKTEXTBOX, wxDefaultPosition,
        wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_link, 0, wxGROW | wxALL, 0 );

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer8, 0, wxGROW | wxALL, 5 );

    wxButton* itemButton9
        = new wxButton( itemPanel1, ID_MYSTICBUTTON, _( "Mystic" ),
            wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton9, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton10
        = new wxButton( itemPanel1, ID_COLNECTBUTTON, _( "Colnect" ),
            wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton10, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton11
        = new wxButton( itemPanel1, ID_EBAYBUTTON, _( "eBay" ),
            wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton11, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton12
        = new wxButton( itemPanel1, ID_NPMBUTTON, _( "NPM" ), wxDefaultPosition,
            wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton12, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton112
        = new wxButton( itemPanel1, ID_SITETBUTTON, _( "Read Website" ), wxDefaultPosition,
            wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer8->Add( itemButton112, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_catCodes = new LabeledTextBox( itemPanel1, ID_CATCODETEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_catCodes, 0, wxGROW | wxALL, 0 );

    m_imageName = new LabeledTextBox( itemPanel1, ID_IMAGENAMETEXTBOX,
        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_imageName, 0, wxGROW | wxALL, 0 );

    m_link->SetLabel( Catalog::DataTypeNames[ Catalog::DT_Link ] );
    m_catCodes->SetLabel( Catalog::DataTypeNames[ Catalog::DT_Catalog_Codes ] );
    m_imageName->SetLabel( "Image Name" );

    SetDataEditable( GetSettings( )->IsCatalogVolumeEditable( ) );

}

bool MiscellaneousDataPanel::ShowToolTips( )
{
    return true;
}

void MiscellaneousDataPanel::UpdatePanel( )
{
    Catalog::Entry* stamp = GetCatalogData( )->GetCurrentStamp( );

    if ( stamp->IsOK( ) )
    {

        m_link->SetValue( stamp->GetAttr( Catalog::DT_Link ) );
        m_catCodes->SetValue( stamp->GetAttr( Catalog::DT_Catalog_Codes ) );
        wxString id = stamp->GetAttr( Catalog::DT_ID_Nbr );
        id = id.Trim( true );
        id = id.Trim( false );
        id.Replace( ":", "_" );
        id.Replace( " ", "_" );
        id.Append( ".jpg" );
        m_imageName->SetValue( id );
    }
}

void MiscellaneousDataPanel::OnColnectButtonClick( wxCommandEvent& event )
{
    if ( wxTheClipboard->Open( ) )
    {
        // This data objects are held by the clipboard, 
        // so do not delete them in the app.
        wxString imageName = m_imageName->GetValue( );
        int pos = imageName.Find( ".jpg" );
        imageName = imageName.Mid( 0, pos );
        wxTheClipboard->SetData( new wxTextDataObject( imageName ) );
        wxTheClipboard->Close( );
    }
    wxString link = m_link->GetValue( );
    //    wxGetApp( ).GetFrame( )->GetWebViewPage( )->DoLoad( link );
    wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s &", link );
    system( cmd.fn_str( ) );
    event.Skip( );

}

void MiscellaneousDataPanel::OnSiteButtonClick( wxCommandEvent& event )
{

    RetrieveImage( );
    // if ( wxTheClipboard->Open( ) )
    // {
    //     // This data objects are held by the clipboard, 
    //     // so do not delete them in the app.
    //     wxString imageName = m_imageName->GetValue( );
    //     int pos = imageName.Find( ".jpg" );
    //     imageName = imageName.Mid( 0, pos );
    //     wxTheClipboard->SetData( new wxTextDataObject( imageName ) );
    //     wxTheClipboard->Close( );
    // }
    // wxString link = m_link->GetValue( );
    // wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s &", link );
    // system( cmd.fn_str( ) );
    event.Skip( );

}
/*
 *   ID_BUTTON
 */

void MiscellaneousDataPanel::OnMysticButtonClick( wxCommandEvent& event )
{

    event.Skip( );

}

/*
 *   ID_NPMBUTTON
 */

void MiscellaneousDataPanel::OnNPMButtonClick( wxCommandEvent& event )
{

    event.Skip( );
}

/*
 *   ID_EBAYBUTTON
 */

void MiscellaneousDataPanel::OneBayButtonClick( wxCommandEvent& event )
{
    //     wxString link = m_link->GetValue( );
    //     wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s", 
    //     link ); system ( cmd.fn_str( ) );
    // "https://www.ebay.com/sch/i.html?_from = R40&_nkw = us+stamps+%s&_sacat = 261&LH_TitleDesc = 0&_osacat = 261&_odkw = us+stamps"

    event.Skip( );

}

void MiscellaneousDataPanel::SetDataEditable( bool val )
{
    //$    m_score->SetEditable( val );;
     //$   m_accuracy->SetEditable( val );;
    m_link->SetEditable( val );;
    m_catCodes->SetEditable( val );;
    m_imageName->SetEditable( val );;

}

size_t MiscellaneousDataPanel::write_data( void* ptr, size_t size, size_t nmemb, void* stream )
{
    size_t written = fwrite( ptr, size, nmemb, ( FILE* ) stream );
    return written;
}


void MiscellaneousDataPanel::RetrieveImage( )
{
    bool status = FALSE;

    // m_stamp->GetLink( );
    wxString url = m_link->GetValue( );
    //   wxGetApp( ).GetFrame( )->StartWebRequest( Page_Text, url );
    //wxString text = wxGetApp( ).GetFrame( )->GetWebText( );

}
