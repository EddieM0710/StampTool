/*
 * @file SettingsDialog.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-12
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
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif



#include <wx/notebook.h>

#include "Defs.h"
#include "Settings.h"
#include "gui/SettingsDialog.h"
#include "gui/SortOrderPanel.h"
#include "gui/DefinePeriodsPanel.h"
#include "gui/FontPickerHelper.h"
#include <wx/font.h>
#include <wx/colour.h>
#include "utils/FontList.h"

 // XPM images
 // XPM images


 /*
  * SettingsDialog type definition
  */

IMPLEMENT_DYNAMIC_CLASS( SettingsDialog, wxDialog )


/*
 * SettingsDialog event table definition
 */

    BEGIN_EVENT_TABLE( SettingsDialog, wxDialog )

    // SettingsDialog event table entries
    EVT_TEXT( ID_IMAGEDIRECTORTEXTBOX, SettingsDialog::OnImagedirectortextboxTextUpdated )
    EVT_TEXT( ID_COUNTRYTEXTBOX, SettingsDialog::OnCountrytextboxTextUpdated )
    EVT_TEXT( ID_CATALOGTEXTBOX, SettingsDialog::OnCatalogtextboxTextUpdated )
    EVT_CHECKBOX( ID_OPENLASTCHECKBOX, SettingsDialog::OnOpenlastcheckboxClick )
    EVT_TEXT( ID_RECENTSIZETEXTCTRL, SettingsDialog::OnRecentsizetextctrlTextUpdated )
    EVT_BUTTON( wxID_OK, SettingsDialog::OnOkClick )
    // SettingsDialog event table entries

    END_EVENT_TABLE( )


    /*
     * SettingsDialog constructors
     */

    SettingsDialog::SettingsDialog( )
{
    Init( );
}

SettingsDialog::SettingsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
    //m_imageDirectory->SetValue( GetSettings( )->GetImageDirectory( ) );
    m_country->SetValue( GetSettings( )->GetCountryID( ) );
    m_catalog->SetValue( GetSettings( )->GetCatalogID( ) );
    m_loadLastFileAtStartUp->SetValue( GetSettings( )->GetLoadLastFileAtStartUp( ) );
    wxString str = wxString::Format( "%i", GetSettings( )->GetNbrRecentPreference( ) );
    m_recentListSize->SetValue( str );
}


/*
 * SettingsDialog creator
 */

bool SettingsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // SettingsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // SettingsDialog creation
    return true;
}


/*
 * SettingsDialog destructor
 */

SettingsDialog::~SettingsDialog( )
{
    // SettingsDialog destruction
    // SettingsDialog destruction
}


/*
 * Member initialisation
 */

void SettingsDialog::Init( )
{
    // SettingsDialog member initialisation
    m_imageDirectory = NULL;
    m_country = NULL;
    m_catalog = NULL;
    m_loadLastFileAtStartUp = NULL;
    m_recentListSize = NULL;
    // SettingsDialog member initialisation
}


/*
 * Control creation for SettingsDialog
 */

void SettingsDialog::CreateControls( )
{
    // SettingsDialog content construction

    SettingsDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    // wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    // theDialogVerticalSizer->Add( itemBoxSizer3, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 2, wxGROW | wxALL, 5 );

    wxNotebook* notebook = new wxNotebook( theDialog, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* notebookDetailsPanel = new wxPanel( notebook, ID_NOTEBOOKDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    notebookDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookDetailsPanel->SetSizer( detailsVerticalSizer );

    wxBoxSizer* imageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( imageHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText1 = new wxStaticText( notebookDetailsPanel, wxID_STATIC, _( "Image Directory" ), wxDefaultPosition, wxDefaultSize, 0 );
    imageHorizontalSizer->Add( itemStaticText1, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_imageDirectory = new wxTextCtrl( notebookDetailsPanel, ID_IMAGEDIRECTORTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    imageHorizontalSizer->Add( m_imageDirectory, 3, wxGROW | wxALL, 5 );

    // wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxHORIZONTAL );
    // theDialogVerticalSizer->Add( itemBoxSizer5, 1, wxGROW | wxALL, 5 );

    // wxStaticText* itemStaticText3 = new wxStaticText( notebookDetailsPanel, wxID_STATIC, _( "Working Directory" ), wxDefaultPosition, wxDefaultSize, 0 );
    // itemBoxSizer5->Add( itemStaticText3, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    wxBoxSizer* codePrefHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( codePrefHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText5 = new wxStaticText( notebookDetailsPanel, wxID_STATIC, _( "Country Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( itemStaticText5, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_country = new wxTextCtrl( notebookDetailsPanel, ID_COUNTRYTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( m_country, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    codePrefHorizontalSizer->Add( 10, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText8 = new wxStaticText( notebookDetailsPanel, wxID_STATIC, _( "Catalog Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( itemStaticText8, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_catalog = new wxTextCtrl( notebookDetailsPanel, ID_CATALOGTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( m_catalog, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* recentHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( recentHorizontalSizer, 0, wxGROW | wxALL, 5 );

    m_loadLastFileAtStartUp = new wxCheckBox( notebookDetailsPanel, ID_OPENLASTCHECKBOX, _( "Load Last File at Startup" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_loadLastFileAtStartUp->SetValue( false );
    recentHorizontalSizer->Add( m_loadLastFileAtStartUp, 2, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    recentHorizontalSizer->Add( 20, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText2 = new wxStaticText( notebookDetailsPanel, wxID_STATIC, _( "Size of RecentList" ), wxDefaultPosition, wxDefaultSize, 0 );
    recentHorizontalSizer->Add( itemStaticText2, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_recentListSize = new wxTextCtrl( notebookDetailsPanel, ID_RECENTSIZETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    recentHorizontalSizer->Add( m_recentListSize, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    notebook->AddPage( notebookDetailsPanel, _( "Details" ) );

    m_sortOrderPanel =
        new SortOrderPanel( notebook, ID_SORTORDERPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );

    notebook->AddPage( m_sortOrderPanel, _( "Sort Order" ) );

    m_definePeriodsPanel =
        new DefinePeriodsPanel( notebook, ID_DEFINEPERIODSPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );

    notebook->AddPage( m_definePeriodsPanel, _( "Define Periods" ) );



    wxPanel* notebookFontsPanel = new wxPanel( notebook, ID_NOTEBOOKFONTSPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    notebookFontsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* fontsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookFontsPanel->SetSizer( fontsVerticalSizer );

    wxBoxSizer* fontsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    fontsVerticalSizer->Add( fontsHorizontalSizer, 0, wxGROW | wxALL, 5 );



    wxFont catNbrFont = GetSettings( )->GetNbrFont( );
    wxColour catNbrColor = GetSettings( )->GetNbrColor( );
    wxFont titleFont = GetSettings( )->GetTitleFont( );
    wxColour titleColor = GetSettings( )->GetTitleColor( );
    wxFont textFont = GetSettings( )->GetTextFont( );
    wxColour textColor = GetSettings( )->GetTextColor( );

    int lastID = ID_LastID;


    FontPicker* catNbrFontPickerHelper = new FontPicker(
        notebookFontsPanel, fontsVerticalSizer,
        _( "Default Stamp Nbr Font" ), _( "Default" ), lastID,
        catNbrFont, catNbrColor );
    m_nbrFontPicker = catNbrFontPickerHelper->GetFontPickerCtrl( );
    m_nbrColorPicker = catNbrFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* titleFontPickerHelper = new FontPicker(
        notebookFontsPanel, fontsVerticalSizer,
        _( "Default Title Font" ), _( "Default" ), lastID,
        titleFont, titleColor );
    m_titleFontPicker = titleFontPickerHelper->GetFontPickerCtrl( );
    m_titleColorPicker = titleFontPickerHelper->GetColourPickerCtrl( );


    FontPicker* textFontPickerHelper = new FontPicker(
        notebookFontsPanel, fontsVerticalSizer,
        _( "Default Text Font" ), _( "Default" ), lastID,
        textFont, textColor );
    m_textFontPicker = textFontPickerHelper->GetFontPickerCtrl( );
    m_textColorPicker = textFontPickerHelper->GetColourPickerCtrl( );


    FontPicker* nameFontPickerHelper = new FontPicker(
        notebookFontsPanel, fontsVerticalSizer,
        _( "Default Stamp Name Font" ), _( "Default" ), lastID,
        textFont, textColor );
    m_nameFontPicker = nameFontPickerHelper->GetFontPickerCtrl( );
    m_nameColorPicker = nameFontPickerHelper->GetColourPickerCtrl( );

    notebook->AddPage( notebookFontsPanel, _( "Fonts" ) );


    theDialogHorizontalSizer->Add( notebook, 2, wxGROW | wxALL, 5 );

    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton13 = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton13, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton14 = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton14, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // SettingsDialog content construction
}




bool SettingsDialog::ShowToolTips( )
{
    return true;
}


/*
 *   ID_IMAGEDIRECTORTEXTBOX
 */

void SettingsDialog::OnImagedirectortextboxTextUpdated( wxCommandEvent& event )
{

    m_dirty = true;
    event.Skip( );

}


/*
 *   ID_COUNTRYTEXTBOX
 */

void SettingsDialog::OnCountrytextboxTextUpdated( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}


/*
 *   ID_CATALOGTEXTBOX
 */

void SettingsDialog::OnCatalogtextboxTextUpdated( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}


/*
 *   ID_OPENLASTCHECKBOX
 */

void SettingsDialog::OnOpenlastcheckboxClick( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}


/*
 *   ID_RECENTSIZETEXTCTRL
 */

void SettingsDialog::OnRecentsizetextctrlTextUpdated( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}

void SettingsDialog::OnOkClick( wxCommandEvent& event )
{
    UpdateSettings( );
    m_definePeriodsPanel->OnOkClick( );
    m_sortOrderPanel->OnOkClick( );

    if ( GetSettings( )->isDirty( ) )
        GetSettings( )->Save( );

    event.Skip( );


}

void SettingsDialog::UpdateSettings( )
{

    if ( m_imageDirectory->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        //GetSettings( )->SetImageDirectory( m_imageDirectory->GetValue( ) );
        m_imageDirectory->SetModified( false );
    }

    if ( m_country->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetCountryID( m_country->GetValue( ) );
        m_country->SetModified( false );
    }


    if ( m_catalog->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetCatalogID( m_catalog->GetValue( ) );
        m_catalog->SetModified( false );
    }

    if ( m_loadLastFileAtStartUp->GetValue( ) != GetSettings( )->GetLoadLastFileAtStartUp( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetLoadLastFileAtStartUp( m_loadLastFileAtStartUp->GetValue( ) );
    }


    if ( m_recentListSize->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        long val;
        if ( m_recentListSize->GetValue( ).ToLong( &val ) )
        {
            GetSettings( )->SetNbrRecentPreference( val );
        }
        else
        {
            GetSettings( )->SetNbrRecentPreference( 1 );
        }
        m_recentListSize->SetModified( false );
    }

    wxFont titleFont = m_titleFontPicker->GetSelectedFont( );
    wxColour titleColor = m_titleColorPicker->GetColour( );
    int ndx = GetFontList( )->AddNewFont( titleFont, titleColor );
    GetSettings( )->SetFontNdxPreference( Design::AT_TitleFontType, ndx );

    wxFont catNbrFont = m_nbrFontPicker->GetSelectedFont( );
    wxColour catNbrColor = m_nbrColorPicker->GetColour( );
    ndx = GetFontList( )->AddNewFont( catNbrFont, catNbrColor );
    GetSettings( )->SetFontNdxPreference( Design::AT_NbrFontType, ndx );

    wxFont textFont = m_textFontPicker->GetSelectedFont( );
    wxColour textColor = m_textColorPicker->GetColour( );
    ndx = GetFontList( )->AddNewFont( textFont, textColor );
    GetSettings( )->SetFontNdxPreference( Design::AT_TextFontType, ndx );

    wxFont nameFont = m_nameFontPicker->GetSelectedFont( );
    wxColour nameColor = m_nameColorPicker->GetColour( );
    ndx = GetFontList( )->AddNewFont( nameFont, nameColor );
    GetSettings( )->SetFontNdxPreference( Design::AT_NameFontType, ndx );

    GetFontList( )->InitFonts( );

    if ( GetSettings( )->isDirty( ) )
        GetSettings( )->Save( );
}