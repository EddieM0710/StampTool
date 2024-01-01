/**
 * @file StampDetailsPanel.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2022-03-27
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

#include "wx/notebook.h"
#include "wx/treectrl.h"
#include <wx/fontpicker.h>
#include <wx/checkbox.h>
#include <wx/tokenzr.h>

#include "gui/StampDetailsPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/FontPickerHelper.h"
#include "design/Album.h"
#include "utils/StampList.h"
#include "utils/Settings.h"
#include "Defs.h"
#include "utils/FontList.h"
#include "catalog/CatalogCode.h"
 //#include "gui/TitleHelper.h"
  /*
   * StampDetailsPanel type definition
   */

IMPLEMENT_DYNAMIC_CLASS( StampDetailsPanel, HelperPanel )


/*
 * StampDetailsPanel event table definition
 */
 //  /**
 //   * BEGIN_EVENT_TABLE
 //   *
 //   * @param  {StampDetailsPanel} undefined :
 //   * @param  {wxDialog} undefined           :
 //   */
 //     BEGIN_EVENT_TABLE( StampDetailsPanel, HelperPanel )
 //     // EVT_BUTTON( ID_REFRESHBUTTON, StampDetailsPanel::OnRefreshButtonClick )
 //     // EVT_BUTTON( wxID_CANCEL, StampDetailsPanel::OnCancelClick )
 //     // EVT_BUTTON( wxID_OK, StampDetailsPanel::OnOkClick )
 //     EVT_CHECKBOX( ID_CATNBRCHECKBOX, StampDetailsPanel::OnCatNbrCheckboxClick )
 //     // EVT_RADIOBUTTON( ID_DEFAULTRADIOBUTTON, StampDetailsPanel::OnDefaultRadioButtonSelected )
 //     EVT_RADIOBUTTON( ID_TOPRADIOBUTTON, StampDetailsPanel::OnNamePositionButtonSelected )
 //     EVT_RADIOBUTTON( ID_BOTTOMRADIOBUTTON, StampDetailsPanel::OnNamePositionButtonSelected )
 //     END_EVENT_TABLE( )

 //     //-------

    StampDetailsPanel::StampDetailsPanel( )
{
    Init( );
}

//-------

StampDetailsPanel::StampDetailsPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    m_designTreeID = ( ( AlbumTreeCtrl* ) parent )->GetCurrentTreeID( );
    Create( parent, id, caption, pos, size, style );
}

//-------

StampDetailsPanel::~StampDetailsPanel( )
{

}

//-------

bool StampDetailsPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // StampDetailsPanel creation
    return true;
}

//-------

void StampDetailsPanel::CreateControls( )
{

    StampDetailsPanel* theDialog = this;

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialog->SetSizer( detailsHorizontalSizer );

    /////////


    int lastID = ID_LastID;

    wxNotebook* focusNotebook = new wxNotebook( theDialog, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxBK_LEFT );
    focusNotebook->SetPadding( wxSize( 1, 1 ) );
    detailsHorizontalSizer->Add( focusNotebook, 1, wxGROW | wxALL, 5 );

    wxPanel* commonPanel = new wxPanel( focusNotebook, ++lastID, wxDefaultPosition,
        wxDefaultSize, wxTAB_TRAVERSAL );
    commonPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* commonHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    commonPanel->SetSizer( commonHorizontalSizer );


    wxBoxSizer* leftCommonVerticalSizer = new wxBoxSizer( wxVERTICAL );
    commonHorizontalSizer->Add( leftCommonVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* middleCommonVerticalSizer = new wxBoxSizer( wxVERTICAL );
    commonHorizontalSizer->Add( middleCommonVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* rightCommonVerticalSizer = new wxBoxSizer( wxVERTICAL );
    commonHorizontalSizer->Add( rightCommonVerticalSizer, 1, wxGROW | wxALL, 0 );


    focusNotebook->AddPage( commonPanel, _( "Basic" ) );

    wxPanel* advancedPanel = new wxPanel( focusNotebook, ++lastID, wxDefaultPosition,
        wxDefaultSize, wxTAB_TRAVERSAL );
    advancedPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* advancedHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    advancedPanel->SetSizer( advancedHorizontalSizer );


    wxBoxSizer* leftAdvancedVerticalSizer = new wxBoxSizer( wxVERTICAL );
    advancedHorizontalSizer->Add( leftAdvancedVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* middleAdvancedVerticalSizer = new wxBoxSizer( wxVERTICAL );
    advancedHorizontalSizer->Add( middleAdvancedVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* rightAdvancedVerticalSizer = new wxBoxSizer( wxVERTICAL );
    advancedHorizontalSizer->Add( rightAdvancedVerticalSizer, 1, wxGROW | wxALL, 0 );

    focusNotebook->AddPage( advancedPanel, _( "Special" ) );


    wxBoxSizer* checkBoxHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    leftCommonVerticalSizer->Add( checkBoxHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_nbrCheckbox = SetupCheckBox( commonPanel, checkBoxHorizontalSizer, ++lastID,
        _( "Show ID" ), wxCommandEventHandler( StampDetailsPanel::OnCatNbrCheckboxClick ) );


    m_nbrCheckbox->SetValue( false );
    //   checkBoxHorizontalSizer->Add( m_nbrCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );



    m_catCode = SetupMultilineLabeledText( advancedPanel, middleAdvancedVerticalSizer, lastID,
        "Catalog Codes", true,
        wxCommandEventHandler( StampDetailsPanel::OnCatalogCodesChanged ) );

    m_catNbr = new wxComboBox( commonPanel, ID_IDLABELTEXTBOX, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, m_catCodesStringArray, wxCB_DROPDOWN );
    leftCommonVerticalSizer->Add( m_catNbr, 0, wxGROW | wxALL, 5 );

    Connect( ID_IDLABELTEXTBOX, wxEVT_COMBOBOX, wxCommandEventHandler( StampDetailsPanel::OnCatNbrComboBoxSel ) );


    m_titleHelper = SetupTitleHelper( commonPanel, middleCommonVerticalSizer, lastID, HasTextCtrl,
        wxCommandEventHandler( StampDetailsPanel::OnNameCheckboxClick ),
        wxCommandEventHandler( StampDetailsPanel::OnNameTextChanged ) );

    SetupFontPicker( advancedPanel, leftAdvancedVerticalSizer, lastID,
        _( "Name Font" ), _( "Default" ),
        m_nameFontPicker, m_nameColorPicker,
        wxFontPickerEventHandler( StampDetailsPanel::OnNameFontPicker ),
        wxColourPickerEventHandler( StampDetailsPanel::OnNameColorPicker ),
        wxCommandEventHandler( StampDetailsPanel::OnNameDefaultClick ) );


    SetupFontPicker( advancedPanel, leftAdvancedVerticalSizer, lastID,
        _( "Nbr Font" ), _( "Default" ),
        m_nbrFontPicker, m_nbrColorPicker,
        wxFontPickerEventHandler( StampDetailsPanel::OnNbrFontPicker ),
        wxColourPickerEventHandler( StampDetailsPanel::OnNbrColorPicker ),
        wxCommandEventHandler( StampDetailsPanel::OnNbrDefaultClick ) );


    // wxBoxSizer* nameLocationboxSizer;
    // wxStaticBox* nameLocationbox = SetupBoxSizer( commonPanel, leftCommonVerticalSizer, "Name Location", lastID, nameLocationboxSizer, wxHORIZONTAL );


    // m_topButton = new wxRadioButton( nameLocationbox, lastID, _( "Top" ), wxDefaultPosition, wxDefaultSize, 0 );
    // m_topButton->SetValue( true );
    // nameLocationboxSizer->Add( m_topButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // m_bottomButton = new wxRadioButton( nameLocationbox, lastID, _( "Bottom" ), wxDefaultPosition, wxDefaultSize, 0 );
    // m_bottomButton->SetValue( false );
    // nameLocationboxSizer->Add( m_bottomButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );



    wxBoxSizer* locationSizer;
    wxStaticBox* locationBox = SetupBoxSizer( commonPanel, middleCommonVerticalSizer,
        "Stamp Name Location", lastID, locationSizer, wxHORIZONTAL );

    m_topButton = SetupRadioButton( locationBox, locationSizer, lastID,
        _( "Top" ), true, wxCommandEventHandler( StampDetailsPanel::OnNamePositionButtonSelected ) );
    m_topButton->SetToolTip( _( "Name above Stamp." ) );

    m_bottomButton = SetupRadioButton( locationBox, locationSizer, lastID,
        _( "Bottom" ), false,
        wxCommandEventHandler( StampDetailsPanel::OnNamePositionButtonSelected ) );
    m_bottomButton->SetToolTip( _( "Name below Stamp." ) );






    m_imagePath = SetupLabelText( advancedPanel, middleAdvancedVerticalSizer, lastID,
        _( "Image Name" ), true, wxCommandEventHandler( StampDetailsPanel::OnMountAllowanceWidth ) );

    wxBoxSizer* stampboxSizer;
    wxStaticBox* stampboxBox = SetupBoxSizer( commonPanel, leftCommonVerticalSizer,
        "Stamp", lastID, stampboxSizer, wxHORIZONTAL );

    m_height = SetupLabelText( stampboxBox, stampboxSizer, lastID,
        _( "Height" ), false, wxCommandEventHandler( StampDetailsPanel::OnHeight ) );

    m_width = SetupLabelText( stampboxBox, stampboxSizer, lastID,
        _( "Width" ), false, wxCommandEventHandler( StampDetailsPanel::OnWidth ) );


    wxBoxSizer* selvageBoxSizer;
    wxStaticBox* selvageBox = SetupBoxSizer( advancedPanel, rightAdvancedVerticalSizer,
        "Selvage", lastID, selvageBoxSizer, wxHORIZONTAL );

    m_selvageHeight = SetupLabelText( selvageBox, selvageBoxSizer, lastID,
        _( "Height" ), false, wxCommandEventHandler( StampDetailsPanel::OnSelvageHeight ) );

    m_selvageWidth = SetupLabelText( selvageBox, selvageBoxSizer, lastID,
        _( "Width" ), false, wxCommandEventHandler( StampDetailsPanel::OnSelvageWidth ) );


    wxBoxSizer* mountBoxSizer;
    wxStaticBox* mountSize = SetupBoxSizer( advancedPanel, rightAdvancedVerticalSizer,
        "Mount Allowance", lastID, mountBoxSizer, wxHORIZONTAL );

    m_mountAllowanceHeight = SetupLabelText( mountSize, mountBoxSizer, lastID,
        _( "Height" ), false, wxCommandEventHandler( StampDetailsPanel::OnMountAllowanceHeight ) );

    m_mountAllowanceWidth = SetupLabelText( mountSize, mountBoxSizer, lastID,
        _( "Width" ), false, wxCommandEventHandler( StampDetailsPanel::OnMountAllowanceWidth ) );


    wxBoxSizer* statusSizer = new wxBoxSizer( wxHORIZONTAL );
    rightCommonVerticalSizer->Add( statusSizer, 1, wxGROW | wxALL, 5 );

    m_statusList = new wxListBox( commonPanel, ++lastID, wxDefaultPosition,
        wxDefaultSize, m_statusListStrings, wxLB_SINGLE );

    statusSizer->Add( m_statusList, 1, wxGROW | wxALL, 5 );


    m_imagePath->SetLabel( "ImageName" );
    Layout( );
}

//-------

void StampDetailsPanel::Init( )
{
    m_catNbr = NULL;
    //   m_name = NULL;
    m_height = NULL;
    m_width = NULL;
    m_validate = NULL;
    m_statusList = NULL;
    m_designTreeID = NULL;
    m_nbrCheckbox = NULL;
    m_titleCheckbox = NULL;

}

//-------

wxString StampDetailsPanel::GetImageFilename( )
{
    return m_imagePath->GetValue( );
}

//-------

wxString StampDetailsPanel::GetHeight( )
{
    return m_height->GetValue( );
}

//-------

wxString StampDetailsPanel::GetWidth( )
{
    return m_width->GetValue( );
}

//-------

wxString StampDetailsPanel::GetSelvageHeight( )
{
    return m_selvageHeight->GetValue( );
}

//-------

wxString StampDetailsPanel::GetSelvageWidth( )
{
    return m_selvageWidth->GetValue( );
}

//-------

wxString StampDetailsPanel::GetMountAllowanceHeight( )
{
    return m_mountAllowanceHeight->GetValue( );
}

//-------

wxString StampDetailsPanel::GetMountAllowanceWidth( )
{
    return m_mountAllowanceWidth->GetValue( );
}

//-------

wxString StampDetailsPanel::GetCatNbr( )
{
    return m_catNbr->GetValue( );
}

//-------

wxString StampDetailsPanel::GetName( )
{
    return m_titleHelper->titleLabel->GetValue( );
}

//-------

bool StampDetailsPanel::GetShowNbr( )
{
    return m_nbrCheckbox->IsChecked( );
}

//-------

bool StampDetailsPanel::GetShowTitle( )
{
    return m_titleHelper->titleCheckbox->IsChecked( );
}

//-------

bool StampDetailsPanel::GetShowSubTitle( )
{
    return m_titleHelper->subTitleCheckbox->IsChecked( );
}

//-------

wxFont StampDetailsPanel::GetNbrFont( )
{
    return m_nbrFontPicker->GetSelectedFont( );
}

//-------

wxFont StampDetailsPanel::GetNameFont( )
{
    return m_nameFontPicker->GetSelectedFont( );
}

//-------

wxColour StampDetailsPanel::GetNbrColor( )
{
    return m_nbrColorPicker->GetColour( );
}


wxColour StampDetailsPanel::GetNameColor( )
{
    return m_nameColorPicker->GetColour( );
}

//-------

void StampDetailsPanel::OnNamePositionButtonSelected( wxCommandEvent& event )
{
    if ( m_topButton->GetValue( ) )
    {
        m_stamp->SetStampNamePosition( Design::AT_StampNamePositionTop );
    }
    else
    {
        m_stamp->SetStampNamePosition( Design::AT_StampNamePositionBottom );

    }

    Update( );

    event.Skip( );
}


void StampDetailsPanel::OnCatalogCodesChanged( wxCommandEvent& event )
{

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnCatNbrComboBoxSel( wxCommandEvent& event )
{
    wxString catNbr = m_catNbr->GetValue( );
    m_stamp->SetNbrString( catNbr );
    int pos = catNbr.Find( ":" );
    wxString cat = catNbr.Mid( 0, pos );
    m_stamp->SetCatalog( cat );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnNameFontPicker( wxFontPickerEvent& event )
{
    // wxEventType = event.GetEventType( );
    m_stamp->GetNameFrame( )->SetFont( m_nameFontPicker->GetSelectedFont( ), m_nameColorPicker->GetColour( ) );

    Update( );

    event.Skip( );
}

//-------

void  StampDetailsPanel::OnNameColorPicker( wxColourPickerEvent& event )
{
    m_stamp->GetNameFrame( )->SetFont( m_nameFontPicker->GetSelectedFont( ), m_nameColorPicker->GetColour( ) );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnNbrFontPicker( wxFontPickerEvent& event )
{
    m_stamp->GetNbrFrame( )->SetFont( m_nbrFontPicker->GetSelectedFont( ), m_nbrColorPicker->GetColour( ) );

    Update( );

    event.Skip( );
}

//-------

void  StampDetailsPanel::OnNbrColorPicker( wxColourPickerEvent& event )
{
    m_stamp->GetNbrFrame( )->SetFont( m_nbrFontPicker->GetSelectedFont( ), m_nbrColorPicker->GetColour( ) );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnNbrDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_NbrFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nbrFontPicker->SetSelectedFont( font );
    m_nbrColorPicker->SetColour( color );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnNameDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NameFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nameFontPicker->SetSelectedFont( font );
    m_nameColorPicker->SetColour( color );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::SetTitle( wxString name )
{
    m_titleHelper->titleLabel->ChangeValue( name );
}

//-------

void  StampDetailsPanel::OnNameTextChanged( wxCommandEvent& event )
{
    wxString title = m_titleHelper->titleLabel->GetValue( );
    m_stamp->SetNameString( title );

    Update( );

    event.Skip( );
};

void StampDetailsPanel::OnSubTitleTextChanged( wxCommandEvent& event )
{
}

//-------

void StampDetailsPanel::OnNameCheckboxClick( wxCommandEvent& event )
{
    UpdateTitleState( m_titleHelper );
    m_stamp->SetShowTitle( m_titleHelper->titleCheckbox->GetValue( ) );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnCatNbrCheckboxClick( wxCommandEvent& event )
{
    bool state = m_nbrCheckbox->GetValue( );
    m_stamp->SetShowNbr( state );

    Update( );

    event.Skip( );
}

//-------

void StampDetailsPanel::OnHeight( wxCommandEvent& event )
{
    wxString str = m_height->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetActualStampHeight( val );

    Update( );

    event.Skip( );
};

//-------

void StampDetailsPanel::OnWidth( wxCommandEvent& event )
{
    wxString str = m_width->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetActualStampWidth( val );

    Update( );

    event.Skip( );
};

//-------

void StampDetailsPanel::OnSelvageHeight( wxCommandEvent& event )
{
    wxString str = m_selvageHeight->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetSelvageHeight( val );

    Update( );

};

//-------

void StampDetailsPanel::OnSelvageWidth( wxCommandEvent& event )
{
    wxString str = m_selvageWidth->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetSelvageWidth( val );

    Update( );

    event.Skip( );
};

//-------

void StampDetailsPanel::OnMountAllowanceHeight( wxCommandEvent& event )
{
    wxString str = m_mountAllowanceHeight->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetSelvageHeight( val );

    Update( );

    event.Skip( );
};

//-------

void StampDetailsPanel::OnMountAllowanceWidth( wxCommandEvent& event )
{
    wxString str = m_mountAllowanceWidth->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetMountAllowanceWidth( val );

    Update( );

    event.Skip( );
};

//-------

void StampDetailsPanel::SetupDialog( Design::Stamp* stamp )
{
    m_stamp = stamp;
    UpdateControls( );
    SetStatusList( );
};


//-------

void StampDetailsPanel::SetCatCodes( )
{
    m_catCodesString = m_stamp->GetCatalogCodes( );
    if ( m_catCodesString.IsEmpty( ) )
    {
        wxTreeItemId m_designTreeID = GetAlbumTreeCtrl( )->GetSelection( );
        if ( m_designTreeID.IsOk( ) )
        {
            DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( m_designTreeID );

            Utils::StampLink* link = data->GetStampLink( );
            if ( link )
            {
                wxTreeItemId catTreeID = link->GetCatTreeID( );
                wxXmlNode* node = GetCatalogTreeCtrl( )->GetItemNode( catTreeID );

                if ( node )
                {
                    // Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
                    Catalog::Entry  stamp( node );
                    m_catCodesString = stamp.GetCatalogCodes( );
                    m_stamp->SetCatalogCodes( m_catCodesString );
                }
            }
        }
    }
    if ( !m_catCodesString.IsEmpty( ) )
    {
        Catalog::CatalogCode catCodeArray( m_catCodesString );
        m_catCodesStringArray = catCodeArray.GetCodes( );
        wxString cat = m_stamp->GetCatalog( );
        wxString preferredID = catCodeArray.GetPreferredCatalogCode( cat );
        m_catCode->ChangeValue( m_catCodesString );
        m_catNbr->Clear( );
        m_catNbr->Append( m_catCodesStringArray );
        int ndx = m_catNbr->FindString( preferredID );
        m_stamp->SetNbrString( preferredID );
        m_catNbr->SetSelection( ndx );
        return;
    }
    else
    {
        wxString str = m_stamp->GetNbrString( );
        m_catNbr->Clear( );
        m_catNbr->Append( str );
        m_catNbr->SetSelection( 0 );
        return;
    }
    m_catCode->ChangeValue( "" );
}

//-------

bool StampDetailsPanel::ShowToolTips( )
{
    return true;
}

//-------

void StampDetailsPanel::SetImageFilename( wxString path )
{
    m_imagePath->ChangeValue( path );
}

//-------

void StampDetailsPanel::SetHeight( wxString height )
{
    m_height->ChangeValue( height );
}

//-------

void StampDetailsPanel::SetWidth( wxString width )
{
    m_width->ChangeValue( width );
}

//-------

void StampDetailsPanel::SetSelvageHeight( wxString height )
{
    m_selvageHeight->ChangeValue( height );
}

void StampDetailsPanel::SetSelvageWidth( wxString width )
{
    m_selvageWidth->ChangeValue( width );
}

//-------

void StampDetailsPanel::SetMountAllowanceHeight( wxString height )
{
    m_mountAllowanceHeight->ChangeValue( height );
}

//-------

void StampDetailsPanel::SetMountAllowanceWidth( wxString width )
{
    m_mountAllowanceWidth->ChangeValue( width );
}

//-------

void StampDetailsPanel::SetCatNbr( wxString catNbr )
{
    m_catNbr->SetStringSelection( catNbr );
}

//-------

void StampDetailsPanel::SetName( wxString name )
{
    m_titleHelper->titleLabel->ChangeValue( name );
}

//-------

void StampDetailsPanel::SetShowNbr( bool state )
{
    m_nbrCheckbox->SetValue( state );
}

//-------

void StampDetailsPanel::SetShowTitle( bool state )
{
    m_titleHelper->titleCheckbox->SetValue( state );
}

//-------

void StampDetailsPanel::SetNbrFont( wxFont font )
{
    m_nbrFontPicker->SetSelectedFont( font );
}

//-------

void StampDetailsPanel::SetNameFont( wxFont font )
{
    m_nameFontPicker->SetSelectedFont( font );
}

//-------

void StampDetailsPanel::SetNbrColor( wxColour color )
{
    m_nbrColorPicker->SetColour( color );
}

//-------

void StampDetailsPanel::SetNameColor( wxColour color )
{
    m_nameColorPicker->SetColour( color );
}

//-------

void StampDetailsPanel::SetTitleLocation( )
{
    Design::StampNamePosType titleLocation = m_stamp->GetStampNamePositionType( );
    if ( titleLocation == Design::AT_StampNamePositionTop )
    {
        m_topButton->SetValue( true );
        m_bottomButton->SetValue( false );
    }
    else //if ( m_titleLocation == Design::AT_StampNameLocationBottom )
    {
        m_topButton->SetValue( false );
        m_bottomButton->SetValue( true );
    }
}

//-------

void StampDetailsPanel::UpdateControls( )
{
    SetCatCodes( );

    SetHeight( m_stamp->GetActualStampHeightStr( ) );
    SetWidth( m_stamp->GetActualStampWidthStr( ) );

    SetSelvageHeight( m_stamp->GetSelvageHeightStr( ) );
    SetSelvageWidth( m_stamp->GetSelvageWidthStr( ) );

    SetMountAllowanceHeight( m_stamp->GetMountAllowanceHeightStr( ) );
    SetMountAllowanceWidth( m_stamp->GetMountAllowanceWidthStr( ) );

    //SetCatNbr( m_stamp->GetNbrString( ) );
    SetName( m_stamp->GetNameString( ) );
    SetShowNbr( m_stamp->GetShowNbr( ) );
    SetShowTitle( m_stamp->GetShowTitle( ) );
    SetTitle( m_stamp->GetNameString( ) );
    //  SetShowSubTitle( m_stamp->GetShowSubTitle( ) );
    SetNbrFont( m_stamp->GetNbrFrame( )->GetFont( ) );
    SetNameFont( m_stamp->GetNameFrame( )->GetFont( ) );
    SetNbrColor( m_stamp->GetNbrFrame( )->GetColor( ) );
    SetNameColor( m_stamp->GetNameFrame( )->GetColor( ) );
    SetImageFilename( m_stamp->GetStampImageFilename( ) );
    SetTitleLocation( );
}

//-------

void StampDetailsPanel::SetStatusList( )
{
    m_statusList->Clear( );
    wxArrayString* errors = m_stamp->GetErrorArray( );
    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }
}
//-------

void StampDetailsPanel::Update( )
{
    GetAlbumTreeCtrl( )->Update( );
    SetStatusList( );
}
