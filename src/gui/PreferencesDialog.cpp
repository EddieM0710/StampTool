/*
 * @file PreferencesDialog.cpp
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
#include "utils/Settings.h"
#include "utils/Project.h"
#include "gui/PreferencesDialog.h"
#include "gui/SortOrderPanel.h"
#include "gui/DefinePeriodsPanel.h"
#include "gui/FontPickerHelper.h"
#include "collection/CollectionList.h"
#include "collection/Collection.h"
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/filepicker.h>
#include "utils/FontList.h"

 // XPM images
 // XPM images


 /*
  * PreferencesDialog type definition
  */

IMPLEMENT_DYNAMIC_CLASS( PreferencesDialog, wxDialog )


/*
 * PreferencesDialog event table definition
 */

    BEGIN_EVENT_TABLE( PreferencesDialog, wxDialog )

    // PreferencesDialog event table entries
    EVT_TEXT( ID_IMAGEDIRECTORTEXTBOX, PreferencesDialog::OnImagedirectortextboxTextUpdated )
    EVT_TEXT( ID_COUNTRYTEXTBOX, PreferencesDialog::OnCountrytextboxTextUpdated )
    EVT_TEXT( ID_CATALOGTEXTBOX, PreferencesDialog::OnCatalogtextboxTextUpdated )
    EVT_CHECKBOX( ID_OPENLASTCHECKBOX, PreferencesDialog::OnOpenlastcheckboxClick )
    EVT_TEXT( ID_RECENTSIZETEXTCTRL, PreferencesDialog::OnRecentsizetextctrlTextUpdated )
    EVT_BUTTON( wxID_OK, PreferencesDialog::OnOkClick )
    EVT_BUTTON( ID_DIRPICKERBTN, PreferencesDialog::BrowseForDir )
EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, PreferencesDialog::OnNotebookPageChanged )
    
   // PreferencesDialog event table entries

    END_EVENT_TABLE( )


    /*
     * PreferencesDialog constructors
     */

    PreferencesDialog::PreferencesDialog( )
{
    Init( );
}

PreferencesDialog::PreferencesDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
    InitDetailsPanel( );
}

void PreferencesDialog::InitDetailsPanel( )
{
    m_imageDirectory->SetValue( GetProject( )->GetImageDirectory( ) );
    m_catalog->SetValue( GetProject( )->GetProjectCatalogCode( ) );
    m_country->SetValue( GetProject( )->GetProjectCountryCode( ) );
    m_loadLastFileAtStartUp->SetValue( GetSettings( )->GetLoadLastFileAtStartUp( ) );
    wxString str = wxString::Format( "%i", GetSettings( )->GetNbrRecentPreference( ) );
    m_recentListSize->SetValue( str );

}


/*
 * PreferencesDialog creator
 */

bool PreferencesDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // PreferencesDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // PreferencesDialog creation
    return true;
}


/*
 * PreferencesDialog destructor
 */

PreferencesDialog::~PreferencesDialog( )
{
    // PreferencesDialog destruction
    // PreferencesDialog destruction
}


/*
 * Member initialisation
 */

void PreferencesDialog::Init( )
{
    // PreferencesDialog member initialisation
    m_imageDirectory = NULL;
    m_country = NULL;
    m_catalog = NULL;
    m_loadLastFileAtStartUp = NULL;
    m_recentListSize = NULL;
    // PreferencesDialog member initialisation
}

wxPanel* PreferencesDialog::CreateNotebookDetailsPanel( wxWindow* parent )
{

    wxPanel* preferencesDetailsPanel = new wxPanel( parent, ID_NOTEBOOKDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    preferencesDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    preferencesDetailsPanel->SetSizer( detailsVerticalSizer );

    wxBoxSizer* imageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( imageHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText1 = new wxStaticText( preferencesDetailsPanel, wxID_STATIC, _( "Image Directory" ), wxDefaultPosition, wxDefaultSize, 0 );
    imageHorizontalSizer->Add( itemStaticText1, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_imageDirectory = new wxTextCtrl( preferencesDetailsPanel, ID_IMAGEDIRECTORTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    imageHorizontalSizer->Add( m_imageDirectory, 3, wxGROW | wxALL, 5 );

    wxButton* browseButton = new wxButton( preferencesDetailsPanel, ID_DIRPICKERBTN, _( "Browse" ), wxDefaultPosition, wxDefaultSize, 0 );
    imageHorizontalSizer->Add( browseButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxHORIZONTAL );
    // theDialogVerticalSizer->Add( itemBoxSizer5, 1, wxGROW | wxALL, 5 );

    // wxStaticText* itemStaticText3 = new wxStaticText( preferencesDetailsPanel, wxID_STATIC, _( "Working Directory" ), wxDefaultPosition, wxDefaultSize, 0 );
    // itemBoxSizer5->Add( itemStaticText3, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    wxBoxSizer* codePrefHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( codePrefHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText5 = new wxStaticText( preferencesDetailsPanel, wxID_STATIC, _( "Country Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( itemStaticText5, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_country = new wxTextCtrl( preferencesDetailsPanel, ID_COUNTRYTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( m_country, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    codePrefHorizontalSizer->Add( 10, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText8 = new wxStaticText( preferencesDetailsPanel, wxID_STATIC, _( "Catalog Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( itemStaticText8, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_catalog = new wxTextCtrl( preferencesDetailsPanel, ID_CATALOGTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( m_catalog, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* recentHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( recentHorizontalSizer, 0, wxGROW | wxALL, 5 );

    m_loadLastFileAtStartUp = new wxCheckBox( preferencesDetailsPanel, ID_OPENLASTCHECKBOX, _( "Load Last File at Startup" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_loadLastFileAtStartUp->SetValue( false );
    recentHorizontalSizer->Add( m_loadLastFileAtStartUp, 2, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    recentHorizontalSizer->Add( 20, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText2 = new wxStaticText( preferencesDetailsPanel, wxID_STATIC, _( "Size of RecentList" ), wxDefaultPosition, wxDefaultSize, 0 );
    recentHorizontalSizer->Add( itemStaticText2, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_recentListSize = new wxTextCtrl( preferencesDetailsPanel, ID_RECENTSIZETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    recentHorizontalSizer->Add( m_recentListSize, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    return preferencesDetailsPanel;
}

wxPanel* PreferencesDialog::CreateNotebookFontsPanel( wxWindow* parent )
{

    wxPanel* fontsPanel = new wxPanel( parent, ID_NOTEBOOKFONTSPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    fontsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* fontsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    fontsPanel->SetSizer( fontsVerticalSizer );

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
        fontsPanel, fontsVerticalSizer,
        _( "Default Stamp Nbr Font" ), _( "Default" ), lastID,
        catNbrFont, catNbrColor );
    m_nbrFontPicker = catNbrFontPickerHelper->GetFontPickerCtrl( );
    m_nbrColorPicker = catNbrFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* titleFontPickerHelper = new FontPicker(
        fontsPanel, fontsVerticalSizer,
        _( "Default Title Font" ), _( "Default" ), lastID,
        titleFont, titleColor );
    m_titleFontPicker = titleFontPickerHelper->GetFontPickerCtrl( );
    m_titleColorPicker = titleFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* textFontPickerHelper = new FontPicker(
        fontsPanel, fontsVerticalSizer,
        _( "Default Text Font" ), _( "Default" ), lastID,
        textFont, textColor );
    m_textFontPicker = textFontPickerHelper->GetFontPickerCtrl( );
    m_textColorPicker = textFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* nameFontPickerHelper = new FontPicker(
        fontsPanel, fontsVerticalSizer,
        _( "Default Stamp Name Font" ), _( "Default" ), lastID,
        textFont, textColor );
    m_nameFontPicker = nameFontPickerHelper->GetFontPickerCtrl( );
    m_nameColorPicker = nameFontPickerHelper->GetColourPickerCtrl( );
    return fontsPanel;
}
wxPanel* PreferencesDialog::CreateCollectionPanel( wxWindow* parent )
{
    
    wxPanel* preferencesCollectionPanel = new wxPanel( m_notebook, ID_NOTEBOOKCOLLECTIONPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    preferencesCollectionPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* collectionVerticalSizer = new wxBoxSizer( wxVERTICAL );
    preferencesCollectionPanel->SetSizer( collectionVerticalSizer );

    m_grid = new wxGrid( preferencesCollectionPanel, ID_COLLECTIONGRID, wxDefaultPosition, wxSize( 100, 100 ),
        wxHSCROLL | wxVSCROLL );
    m_grid->SetDefaultColSize( 100 );
    m_grid->SetDefaultRowSize( 25 );
    m_grid->SetColLabelSize( 25 );
    m_grid->SetRowLabelSize( 50 );
    m_grid->CreateGrid( 0, 3, wxGrid::wxGridSelectCells );
    collectionVerticalSizer->Add( m_grid, 1, wxGROW | wxALL, 5 );
    m_grid->SetColLabelValue( 0, "Name" );
    m_grid->SetColLabelValue( 1, "Description" );
    m_grid->SetColLabelValue( 2, "Location" );

    int cnt = m_grid->GetNumberRows( );
    for ( int i = 0; i < GetCollectionList( )->GetNameArray( ).Count( ); i++ )
    {
        m_grid->InsertRows( cnt, 1 );
        cnt++;
        Inventory::Collection* collection = GetCollectionList( )->GetCollection( i );
        m_grid->SetCellValue( i, 0, collection->GetName( ) );
        m_grid->SetCellValue( i, 1, collection->GetDescription( ) );
        m_grid->SetCellValue( i, 2, collection->GetLocation( ) );
    }
    return preferencesCollectionPanel;
}
/*
 * Control creation for PreferencesDialog
 */

void PreferencesDialog::CreateControls( )
{
    // PreferencesDialog content construction

    PreferencesDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    // wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    // theDialogVerticalSizer->Add( itemBoxSizer3, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 2, wxGROW | wxALL, 5 );

    m_notebook = new wxNotebook( theDialog, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    m_DetailsPanel = CreateNotebookDetailsPanel( m_notebook );
    m_notebook->AddPage( m_DetailsPanel, _( "Details" ) );

    m_SortOrderPanel =
        new SortOrderPanel( m_notebook, ID_SORTORDERPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );
    m_notebook->AddPage( m_SortOrderPanel, _( "Sort Order" ) );


    m_DefinePeriodsPanel =
        new DefinePeriodsPanel( m_notebook, ID_DEFINEPERIODSPANEL, wxDefaultPosition,
            wxSize( 100, 100 ), wxSIMPLE_BORDER );
    m_notebook->AddPage( m_DefinePeriodsPanel, _( "Define Periods" ) );


    m_FontsPanel = CreateNotebookFontsPanel( m_notebook );
    m_notebook->AddPage( m_FontsPanel, _( "Fonts" ) );


    m_CollectionPanel = CreateCollectionPanel( m_notebook );
    m_notebook->AddPage( m_CollectionPanel, _( "Collection" ) );


    theDialogHorizontalSizer->Add( m_notebook, 2, wxGROW | wxALL, 5 );

    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton13 = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton13, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton14 = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton14, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // PreferencesDialog content construction

    m_SortOrderPanel->InitSortControls();
}




bool PreferencesDialog::ShowToolTips( )
{
    return true;
}

void PreferencesDialog::OnNotebookPageChanged( wxNotebookEvent& event )
{
    int newPageNdx = m_notebook->GetSelection( );
    int oldPageNdx = event.GetOldSelection();
    wxWindow* newPage = m_notebook->GetPage( newPageNdx );
     wxWindow* oldPage = m_notebook->GetPage( oldPageNdx );
     if (oldPage == m_DetailsPanel)
     {
         UpdateDetails();
     }
     else if (oldPage == m_SortOrderPanel)
     {
         m_SortOrderPanel->Update();
     }
     else if (oldPage == m_DefinePeriodsPanel)
     {
         m_DefinePeriodsPanel->Update();
     }
     else if (oldPage == m_FontsPanel)
     {
   
         UpdateFonts();
     }
     else if (oldPage == m_CollectionPanel)
     {
         UpdateCollectionList();
     }

    //  if (newPage == m_DetailsPanel)
    //  {
    //     InitDetailsPanel();
    //  }
    //  else if (newPage == m_SortOrderPanel)
    //  {
    //      m_SortOrderPanel->InitSortControls( );
    //  }
    //  else if (newPage == m_DefinePeriodsPanel)
    //  {
    //      m_DefinePeriodsPanel->InitControls( );
    //  }
    //  else if (newPage == m_FontsPanel)
    //  {
    //      InitFonts();
    //  }
    //  else if (newPage == m_CollectionPanel)
    //  {
    //     InitCollectionGrid();
    //  }
}
/*
 *   ID_IMAGEDIRECTORTEXTBOX
 */

void PreferencesDialog::OnImagedirectortextboxTextUpdated( wxCommandEvent& event )
{
    m_imageDirectory->SetModified( true );
    m_dirty = true;
    event.Skip( );

}


/*
 *   ID_COUNTRYTEXTBOX
 */

void PreferencesDialog::OnCountrytextboxTextUpdated( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}

void PreferencesDialog::BrowseForDir( wxCommandEvent& event )
{
    wxString value = m_imageDirectory->GetValue();
    wxDirDialog dlg( this,
                    "Select the Art directory:",
                    value,
                    0);

    if ( dlg.ShowModal() == wxID_OK )
    {
        m_imageDirectory->SetValue( dlg.GetPath( ) );
        m_imageDirectory->SetModified( true );
    }

    event.Skip( );
}

/*
 *   ID_CATALOGTEXTBOX
 */

void PreferencesDialog::OnCatalogtextboxTextUpdated( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}


/*
 *   ID_OPENLASTCHECKBOX
 */

void PreferencesDialog::OnOpenlastcheckboxClick( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}


/*
 *   ID_RECENTSIZETEXTCTRL
 */

void PreferencesDialog::OnRecentsizetextctrlTextUpdated( wxCommandEvent& event )
{

    m_dirty = true;

    event.Skip( );

}

void PreferencesDialog::OnOkClick( wxCommandEvent& event )
{
    UpdateDetails();
    UpdateFonts( );
    m_DefinePeriodsPanel->OnOkClick( );
    m_SortOrderPanel->OnOkClick( );

    if ( GetSettings( )->isDirty( ) )
        GetSettings( )->Save( );

    event.Skip( );


}

void PreferencesDialog::UpdateDetails()
{


        GetSettings( )->SetDirty( );
        GetProject( )->SetImageDirectory( m_imageDirectory->GetValue( ) );
        m_imageDirectory->SetModified( false );

        GetSettings( )->SetDirty( );
        GetProject( )->SetProjectCountryCode( m_country->GetValue( ) );
        m_country->SetModified( false );

        GetSettings( )->SetDirty( );
        GetProject( )->SetProjectCatalogCode( m_catalog->GetValue( ) );
        m_catalog->SetModified( false );

        GetSettings( )->SetDirty( );
        GetSettings( )->SetLoadLastFileAtStartUp( m_loadLastFileAtStartUp->GetValue( ) );

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

// void PreferencesDialog::UpdateFonts()
// {

//     wxFont titleFont = m_titleFontPicker->GetSelectedFont( );
//     wxColour titleColor = m_titleColorPicker->GetColour( );
//     int ndx = GetFontList( )->AddNewFont( titleFont, titleColor );
//     GetSettings( )->SetFontNdxPreference( Design::AT_TitleFontType, ndx );

//     wxFont catNbrFont = m_nbrFontPicker->GetSelectedFont( );
//     wxColour catNbrColor = m_nbrColorPicker->GetColour( );
//     ndx = GetFontList( )->AddNewFont( catNbrFont, catNbrColor );
//     GetSettings( )->SetFontNdxPreference( Design::AT_NbrFontType, ndx );

//     wxFont textFont = m_textFontPicker->GetSelectedFont( );
//     wxColour textColor = m_textColorPicker->GetColour( );
//     ndx = GetFontList( )->AddNewFont( textFont, textColor );
//     GetSettings( )->SetFontNdxPreference( Design::AT_TextFontType, ndx );

//     wxFont nameFont = m_nameFontPicker->GetSelectedFont( );
//     wxColour nameColor = m_nameColorPicker->GetColour( );
//     ndx = GetFontList( )->AddNewFont( nameFont, nameColor );
//     GetSettings( )->SetFontNdxPreference( Design::AT_NameFontType, ndx );

//     GetFontList( )->InitFonts( );

// }



void PreferencesDialog::UpdateFonts( )
{

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

   // GetFontList( )->InitFonts( );

    if ( GetSettings( )->isDirty( ) )
        GetSettings( )->Save( );
}

void PreferencesDialog::UpdateCollectionList()
{
    int cnt = m_grid->GetNumberRows( );
    Inventory::CollectionList *collectionList = GetCollectionList( );
    collectionList->Clear();
     for ( int i = 0; i < cnt; i++ )
    {
     collectionList->AddCollection(  m_grid->GetCellValue( i, 0 ), m_grid->GetCellValue( i, 1),  m_grid->GetCellValue( i, 2) );
    }
}

void PreferencesDialog::InitCollectionGrid()
{
    int cnt = m_grid->GetNumberRows( );
    int nbrcollections = GetCollectionList( )->GetNameArray( ).Count( );
    m_grid->DeleteRows(0, nbrcollections);
    for ( int i = 0; i < nbrcollections; i++ )
    {
        m_grid->InsertRows( cnt, 1 );
        cnt++;
        Inventory::Collection* collection = GetCollectionList( )->GetCollection( i );
        m_grid->SetCellValue( i, 0, collection->GetName( ) );
        m_grid->SetCellValue( i, 1, collection->GetDescription( ) );
        m_grid->SetCellValue( i, 2, collection->GetLocation( ) );
    }
}