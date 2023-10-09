/**
 * @file IdentificationPanel.cpp
 * @author Eddie Monroe ( )
 * @brief IdentificationPanel displays Stamp data relative to the stamp identification
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

#include <wx/clipbrd.h>

#include "Defs.h"
 //#include "gui/LabeledTextBox.h"
#include "gui/IdentificationPanel.h"
#include "gui/CatalogTreeCtrl.h"
 //#include "gui/AppData.h"
#include "gui/StampDescriptionPanel.h"
#include "utils/Settings.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogDefs.h"
#include "catalog/StampMount.h"


IMPLEMENT_DYNAMIC_CLASS( IdentificationPanel, HelperPanel )


BEGIN_EVENT_TABLE( IdentificationPanel, HelperPanel )

//EVT_CHOICE( ID_STATUSCHOICE, IdentificationPanel::OnStatuschoiceSelected )
EVT_CHOICE( ID_EMISSIONCHOICE, IdentificationPanel::OnEmissionchoiceSelected )
EVT_CHOICE( ID_FORMATCHOICE, IdentificationPanel::OnFormatchoiceSelected )
// EVT_TEXT( ID_ISSUEDTEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )
// EVT_TEXT( ID_SERIESTEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )
// EVT_TEXT( ID_THEMETEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )
// EVT_TEXT( ID_COUNTRYTEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )
// EVT_TEXT( ID_NAMELABELEDTEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )
// EVT_TEXT( ID_IDLABELEDTEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )
// EVT_TEXT( ID_WIDTHLABELEDTEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )
// EVT_TEXT( ID_HEIGHTLABELEDTEXTBOX, IdentificationPanel::OnTextctrlTextUpdated )


EVT_BUTTON( ID_COLNECTBUTTON, IdentificationPanel::OnColnectButtonClick )
EVT_BUTTON( ID_EBAYBUTTON, IdentificationPanel::OneBayButtonClick )
EVT_BUTTON( ID_NPMBUTTON, IdentificationPanel::OnNPMButtonClick )

EVT_CHECKBOX( ID_EDITCHECKBOX, IdentificationPanel::OnEditCheckBox )

EVT_COMBOBOX( ID_STAMPMOUNTTEXTBOX, IdentificationPanel::OnComboboxSelected )
EVT_TEXT( ID_STAMPMOUNTTEXTBOX, IdentificationPanel::OnComboboxUpdated )

END_EVENT_TABLE( )

IdentificationPanel::IdentificationPanel( )
{
    Init( );
}

IdentificationPanel::IdentificationPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}


bool IdentificationPanel::Create( wxWindow* parent, wxWindowID id,
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


IdentificationPanel::~IdentificationPanel( )
{

}


void IdentificationPanel::Init( )
{
    // m_ID = NULL;
     //m_status = NULL;
    m_name = NULL;
    m_width = NULL;
    m_height = NULL;
    m_emission = NULL;
    m_format = NULL;
    m_issueDate = NULL;
    m_series = NULL;
    m_themes = NULL;
    m_country = NULL;
    m_perforation = NULL;
    m_printing = NULL;
    m_link = NULL;
    m_catCode = NULL;
    m_imageName = NULL;
    mountComboBox = NULL;
}

void IdentificationPanel::CreateControls( )
{

    IdentificationPanel* thePanel = this;
    int lastID = ID_IDLABELEDTEXTBOX;
    wxBoxSizer* panelVerticalSizer = new wxBoxSizer( wxVERTICAL );
    thePanel->SetSizer( panelVerticalSizer );

    wxBoxSizer* idHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    panelVerticalSizer->Add( idHorizontalSizer, 1, wxGROW | wxALL, 2 );

    // m_editCheckbox = new wxCheckBox( thePanel, ++lastID, _( "Edit" ), wxDefaultPosition, wxDefaultSize, 0 );
    // m_editCheckbox->SetValue( false );
    // idHorizontalSizer->Add( m_editCheckbox, 0, wxALIGN_CENTRE_VERTICAL | wxALL, 0 );


    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    panelVerticalSizer->Add( itemBoxSizer1, 0, wxGROW | wxALL, 2 );

    wxBoxSizer* catCodeVerticalSizer = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( catCodeVerticalSizer, 1, wxGROW | wxALL, 2 );



    wxStaticText* m_catcodeStatic = new wxStaticText( thePanel, wxID_STATIC, _( "CatalogCodes" ), wxDefaultPosition, wxDefaultSize, 0 );

    catCodeVerticalSizer->Add( m_catcodeStatic, 0, wxALIGN_LEFT | wxALL, 0 );

    m_catCode = new wxTextCtrl( thePanel, ++lastID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    catCodeVerticalSizer->Add( m_catCode, 1, wxGROW | wxALL, 0 );


    m_name = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Name", true, wxCommandEventHandler( IdentificationPanel::OnNameUpdated ) );

    //wxBoxSizer* emissionHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
   // panelVerticalSizer->Add( emissionHorizontalSizer, 0, wxALIGN_LEFT | wxALL, 2 );

    // wxStaticText* emissionStaticText = new wxStaticText( thePanel, wxID_STATIC, _( "Emission" ), wxDefaultPosition, wxDefaultSize, 0 );
    // emissionHorizontalSizer->Add( emissionStaticText, 0, wxALIGN_LEFT | wxALL, 0 );

    wxArrayString m_emissionStrings;
    for ( int i = 0; i < Catalog::ET_NbrTypes; i++ )
    {
        m_emissionStrings.Add( _( Catalog::EmissionStrings[ i ] ) );
    }

    //  m_emission = new wxChoice( thePanel, ++lastID, wxDefaultPosition, wxDefaultSize, m_emissionStrings, 0 );


    m_emission = SetupChoice( thePanel, panelVerticalSizer, lastID, _( "Emission" ),
        m_emissionStrings, wxCommandEventHandler( IdentificationPanel::OnEmissionchoiceSelected ) );

    m_emission->SetStringSelection( _( "Unknown" ) );
    //   emissionHorizontalSizer->Add( m_emission, 1, wxGROW | wxALL, 1 );

   // wxBoxSizer* formatHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
   // panelVerticalSizer->Add( formatHorizontalSizer, 0, wxALIGN_LEFT | wxALL, 2 );

    // wxStaticText* formatStaticText = new wxStaticText( thePanel, wxID_STATIC, _( "Format" ), wxDefaultPosition, wxDefaultSize, 0 );
     //formatHorizontalSizer->Add( formatStaticText, 0, wxALIGN_LEFT | wxALL, 0 );

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

    //m_format = new wxChoice( thePanel, ++lastID, wxDefaultPosition, wxDefaultSize, m_formatStrings, 0 );
   // formatHorizontalSizer->Add( m_format, 1, wxGROW | wxALL, 1 );

    m_format = SetupChoice( thePanel, panelVerticalSizer, lastID, _( "Format" ),
        m_formatStrings, wxCommandEventHandler( IdentificationPanel::OnEmissionchoiceSelected ) );
    m_format->SetStringSelection( _( "Unknown" ) );

    m_issueDate = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Issued On", true, wxCommandEventHandler( IdentificationPanel::OnIssuedUpdated ) );

    m_series = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Series", true, wxCommandEventHandler( IdentificationPanel::OnSeriesUpdated ) );

    m_themes = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Theme", true, wxCommandEventHandler( IdentificationPanel::OnThemeUpdated ) );

    m_country = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Country", true, wxCommandEventHandler( IdentificationPanel::OnCountryUpdated ) );

    m_perforation = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Perforation", true, wxCommandEventHandler( IdentificationPanel::OnPerforationUpdated ) );

    m_printing = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Printing", true, wxCommandEventHandler( IdentificationPanel::OnPrintingUpdated ) );

    wxBoxSizer* sizeHorizontalSizer;
    wxStaticBox* sizeBox = SetupBoxSizer( thePanel, panelVerticalSizer, "Size", lastID, sizeHorizontalSizer, wxHORIZONTAL );
    m_width = SetupLabelText( sizeBox, sizeHorizontalSizer, ++lastID, "Width", false, wxCommandEventHandler( IdentificationPanel::OnWidthUpdated ) );

    m_height = SetupLabelText( sizeBox, sizeHorizontalSizer, ++lastID, "Height", false, wxCommandEventHandler( IdentificationPanel::OnHeightUpdated ) );

    m_link = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Link", true, wxCommandEventHandler( IdentificationPanel::OnLinkUpdated ) );

    // wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
   //  panelVerticalSizer->Add( itemBoxSizer8, 1, wxGROW | wxALL, 5 );

    m_imageName = SetupLabelText( thePanel, panelVerticalSizer, ++lastID, "Image Name", true, wxCommandEventHandler( IdentificationPanel::OnImageUpdated ) );

    //   m_link->SetLabel( Catalog::DataTypeNames[ Catalog::DT_Link ] );
    //   m_imageName->SetLabel( "Image Name" );

     //  wxBoxSizer* MountHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
     //  panelVerticalSizer->Add( MountHorizontalSizer, 0, wxGROW | wxALL, 0 );
    wxBoxSizer* MountHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    panelVerticalSizer->Add( MountHorizontalSizer, 0, wxGROW | wxALL, 0 );

    wxStaticText* mountStaticText = new wxStaticText( thePanel, wxID_STATIC, Catalog::DataTypeNames[ Catalog::DT_StampMount ],
        wxDefaultPosition, wxDefaultSize, 0 );
    MountHorizontalSizer->Add( mountStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0 );

    wxArrayString itemComboBox3Strings;
    for ( int i = 0; i < Catalog::NbrStampMounts; i++ )
    {
        itemComboBox3Strings.Add( Catalog::mounts[ i ].name );
    }
    mountComboBox = new wxComboBox( thePanel, ID_STAMPMOUNTTEXTBOX, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, itemComboBox3Strings, wxCB_DROPDOWN );
    MountHorizontalSizer->Add( mountComboBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );



    wxButton* itemButton10 = new wxButton( thePanel, ID_COLNECTBUTTON, _( "Colnect" ),
        wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    panelVerticalSizer->Add( itemButton10, 0, wxALIGN_LEFT | wxALL, 5 );



    // m_issueDate->SetLabel( "Issue Date" );
    // m_emission->SetLabel( "Emission" );
    // m_format->SetLabel( "Format" );
    // m_themes->SetLabel( "Themes" );
    // // m_ID->SetLabel( "ID" );
    // m_name->SetLabel( "Name" );
    // m_width->SetLabel( "Width" );
    // m_height->SetLabel( "Height" );

    // m_series->SetLabel( "Series" );
    // //m_status->SetLabel( "Status" );
    // m_country->SetLabel( "Country" );
    // m_perforation->SetLabel( "Perforation" );
    // m_printing->SetLabel( "Printing" );
    SetDataEditable( GetSettings( )->IsCatalogVolumeEditable( ) );
    Layout( );
    Refresh( );
    FitInside( );
}



bool IdentificationPanel::ShowToolTips( )
{
    return true;
}



void IdentificationPanel::UpdateStampValue( Catalog::DataTypes dt, wxTextCtrl* textBox )
{
    if ( textBox->IsModified( ) )
    {
        Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );

        wxString val = textBox->GetValue( );
        stamp.SetAttr( dt, val );
        textBox->SetModified( false );
    }
}

void IdentificationPanel::OnIssuedUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Issued_on, m_issueDate );
    event.Skip( );

}
void IdentificationPanel::OnSeriesUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Series, m_series );
    event.Skip( );

}
void IdentificationPanel::OnThemeUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Themes, m_themes );
    event.Skip( );

}
void IdentificationPanel::OnCountryUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Country, m_country );
    event.Skip( );

}
void IdentificationPanel::OnPerforationUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Perforation, m_perforation );
    event.Skip( );

}
void IdentificationPanel::OnPrintingUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Printing, m_printing );
    event.Skip( );

}
void IdentificationPanel::OnNameUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Name, m_name );
    event.Skip( );

}
void IdentificationPanel::OnWidthUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Width, m_width );
    event.Skip( );

}
void IdentificationPanel::OnHeightUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Height, m_height );
    event.Skip( );

}

void IdentificationPanel::OnLinkUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_Link, m_link );
    event.Skip( );

}

void IdentificationPanel::OnImageUpdated( wxCommandEvent& event )
{
    UpdateStampValue( Catalog::DT_ImageName, m_imageName );
    event.Skip( );

}

void IdentificationPanel::OnEmissionchoiceSelected( wxCommandEvent& event )
{
    wxString strSel = m_emission->GetStringSelection( );
    Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );
    if ( stamp.IsOK( ) ) stamp.SetEmission( strSel );

    event.Skip( );

}


void IdentificationPanel::OnFormatchoiceSelected( wxCommandEvent& event )
{
    int sel = m_format->GetSelection( );
    wxString strSel = m_format->GetStringSelection( );
    Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );
    if ( stamp.IsOK( ) ) stamp.SetFormat( strSel );


    event.Skip( );

}


void IdentificationPanel::SetChoice( wxChoice* ctrl, wxString str )
{
    int ndx = ctrl->FindString( str );
    if ( ndx == wxNOT_FOUND )
    {
        ndx = 0;
    }
    ctrl->SetSelection( ndx );
}

void IdentificationPanel::SetChoice( wxChoice* ctrl, int ndx )
{
    ctrl->SetSelection( ndx );
}

void IdentificationPanel::UpdatePanel( )
{
    Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );
    if ( stamp.IsOK( ) )
    {

        m_name->ChangeValue( stamp.GetName( ) );
        m_width->ChangeValue( stamp.GetAttr( Catalog::DT_Width ) );
        m_height->ChangeValue( stamp.GetAttr( Catalog::DT_Height ) );
        m_issueDate->SetValue( stamp.GetAttr( Catalog::DT_Issued_on ) );
        SetChoice( m_emission, stamp.GetEmission( ) );
        SetChoice( m_format, stamp.GetFormat( ) );
        m_series->ChangeValue( stamp.GetAttr( Catalog::DT_Series ) );
        m_themes->ChangeValue( stamp.GetAttr( Catalog::DT_Themes ) );
        m_country->ChangeValue( stamp.GetAttr( Catalog::DT_Country ) );
        m_perforation->ChangeValue( stamp.GetAttr( Catalog::DT_Perforation ) );
        m_printing->ChangeValue( stamp.GetAttr( Catalog::DT_Printing ) );
        //SetChoice( m_status, stamp.GetInventoryStatus( ) );

        m_link->SetValue( stamp.GetAttr( Catalog::DT_Link ) );
        m_catCode->SetValue( stamp.GetAttr( Catalog::DT_Catalog_Codes ) );
        wxString id = stamp.FindImageName( );
        m_imageName->SetValue( id );
        mountComboBox->SetValue( stamp.GetAttr( Catalog::DT_StampMount ) );
    }
}

void IdentificationPanel::SetDataEditable( bool val )
{
    m_issueDate->SetEditable( val );
    m_emission->Enable( val );
    m_format->Enable( val );
    m_themes->SetEditable( val );
    //   m_ID->SetEditable( val );
    m_name->SetEditable( val );
    m_width->SetEditable( val );
    m_height->SetEditable( val );
    m_series->SetEditable( val );
    // m_status->Enable( val );
    m_country->SetEditable( val );
    m_perforation->SetEditable( val );
    m_printing->SetEditable( val );
    m_link->SetEditable( val );;
    //   m_catCodes->SetEditable( val );;
    m_imageName->SetEditable( val );;
    mountComboBox->SetEditable( val );;
}


void IdentificationPanel::OnComboboxSelected( wxCommandEvent& event )
{
    event.Skip( );
}

void IdentificationPanel::OnComboboxUpdated( wxCommandEvent& event )
{
    Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );
    stamp.SetAttr( Catalog::DT_StampMount, mountComboBox->GetStringSelection( ) );
    event.Skip( );
}
void IdentificationPanel::OnEditCheckBox( wxCommandEvent& event )
{
    bool val = m_editCheckbox->GetValue( );
    GetSettings( )->SetCatalogVolumeEditable( val );
    GetCatalogData( )->GetDescriptionPanel( )->SetDataEditable( val );
    event.Skip( );
}


// void IdentificationPanel::OnStatuschoiceSelected( wxCommandEvent& event )
// {
//     wxString strSel = m_status->GetStringSelection( );
//     Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );
//     if ( stamp.IsOK( ) )
//     {
//         stamp.SetInventoryStatus( strSel );
//         GetCatalogTreeCtrl( )->SetInventoryStatusImage( );
//     }
//     event.Skip( );

// }

// void IdentificationPanel::UpdateStatus( )
// {
//     Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );

//     if ( stamp.IsOK( ) )
//     {
//         SetChoice( m_status, stamp.GetInventoryStatus( ) );
//     }
// }

void IdentificationPanel::OnColnectButtonClick( wxCommandEvent& event )
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
    int a = system( cmd.fn_str( ) );
    event.Skip( );

}


void IdentificationPanel::OnNPMButtonClick( wxCommandEvent& event )
{

    event.Skip( );
}


void IdentificationPanel::OneBayButtonClick( wxCommandEvent& event )
{

    // Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );
    // if ( stamp.IsOK( ) )
    // {

    //     wxString str = "Postage Stamp " +
    //         stamp.GetAttr( Catalog::DT_ID_Nbr ) + " + " + stamp.GetAttr( Catalog::DT_Name );
    //     wxString space = " ";
    //     wxString plus = "+";
    //     str.Replace( space, plus );
    //     wxString link = "https://www.ebay.com/sch/i.html?_nkw=" + str + "&_sop=15";
    //     //https://www.ebay.com/sch/i.html?_from=R40&_nkw=garden&_sacat=260";
    //     wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s", link );
    //     system( cmd.fn_str( ) );
    //     // "https://www.ebay.com/sch/i.html?_from = R40&_nkw = us+stamps+%s&_sacat = 261&LH_TitleDesc = 0&_osacat = 261&_odkw = us+stamps"
    // https://www.ebay.com/sch/i.html?_from=R40&_trksid=p2499334.m570.l1313&_nkw=Garden+Corsage&_sacat=260

    //     event.Skip( );

    // }
}
