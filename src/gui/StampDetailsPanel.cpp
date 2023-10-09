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
 /**
  * BEGIN_EVENT_TABLE
  *
  * @param  {StampDetailsPanel} undefined :
  * @param  {wxDialog} undefined           :
  */
    BEGIN_EVENT_TABLE( StampDetailsPanel, HelperPanel )
    // EVT_BUTTON( ID_REFRESHBUTTON, StampDetailsPanel::OnRefreshButtonClick )
    // EVT_BUTTON( wxID_CANCEL, StampDetailsPanel::OnCancelClick )
    // EVT_BUTTON( wxID_OK, StampDetailsPanel::OnOkClick )
    EVT_CHECKBOX( ID_CATNBRCHECKBOX, StampDetailsPanel::OnCatNbrCheckboxClick )
    // EVT_RADIOBUTTON( ID_DEFAULTRADIOBUTTON, StampDetailsPanel::OnDefaultRadioButtonSelected )
    // EVT_RADIOBUTTON( ID_TOPRADIOBUTTON, StampDetailsPanel::OnTopRadioButtonSelected )
    // EVT_RADIOBUTTON( ID_BOTTOMRADIOBUTTON, StampDetailsPanel::OnBottomRadioButtonSelected )
    END_EVENT_TABLE( )


    StampDetailsPanel::StampDetailsPanel( )
{
    Init( );
}


StampDetailsPanel::StampDetailsPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    m_designTreeID = ( ( AlbumTreeCtrl* ) parent )->GetCurrentTreeID( );
    Create( parent, id, caption, pos, size, style );
}



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


StampDetailsPanel::~StampDetailsPanel( )
{

}


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


/*
 * Control creation for StampDetailsPanel
 */

void StampDetailsPanel::CreateControls( )
{

    StampDetailsPanel* theDialog = this;

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialog->SetSizer( detailsHorizontalSizer );

    wxBoxSizer* m_leftColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( m_leftColumnVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* m_rightColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( m_rightColumnVerticalSizer, 1, wxGROW | wxALL, 0 );


    wxBoxSizer* checkBoxHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    m_leftColumnVerticalSizer->Add( checkBoxHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_nbrCheckbox = new wxCheckBox( theDialog, ID_CATNBRCHECKBOX, _( "Show ID" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_nbrCheckbox->SetValue( false );
    checkBoxHorizontalSizer->Add( m_nbrCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );


    // wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    // m_leftColumnVerticalSizer->Add( itemBoxSizer1, 1, wxGROW | wxALL, 2 );

    // wxBoxSizer* catCodeVerticalSizer = new wxBoxSizer( wxVERTICAL );
    // itemBoxSizer1->Add( catCodeVerticalSizer, 0, wxGROW | wxALL, 2 );

    wxStaticText* m_catcodeStatic = new wxStaticText( theDialog, wxID_STATIC, _( "CatalogCodes" ),
        wxDefaultPosition, wxDefaultSize, 0 );

    m_leftColumnVerticalSizer->Add( m_catcodeStatic, 0, wxALIGN_LEFT | wxALL, 0 );

    m_catCode = new wxTextCtrl( theDialog, ID_CATCODETEXTBOX, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );


    m_leftColumnVerticalSizer->Add( m_catCode, 0, wxGROW | wxALL, 0 );

    //    m_nbrCheckbox = SetupCheckBox( theDialog, ID_CATNBRCHECKBOX, lastID, _( "Show ID" ),
    //        wxCommandEventHandler( StampDetailsPanel::OnCatNbrCheckboxClick ) );

    // wxBoxSizer* itemBoxSizer6 = new wxBoxSizer( wxHORIZONTAL );
    // m_leftColumnVerticalSizer->Add( itemBoxSizer6, 1, wxGROW | wxALL, 5 );

    m_catNbr = new wxComboBox( theDialog, ID_IDLABELTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_catCodesStringArray, wxCB_DROPDOWN );
    m_leftColumnVerticalSizer->Add( m_catNbr, 0, wxGROW | wxALL, 5 );

    Connect( ID_IDLABELTEXTBOX, wxEVT_COMBOBOX, wxCommandEventHandler( StampDetailsPanel::OnCatNbrComboBoxSel ) );



    int lastID = ID_LastID;


    m_titleHelper = SetupTitleHelper( theDialog, m_leftColumnVerticalSizer, lastID, HasTextCtrl,
        wxCommandEventHandler( StampDetailsPanel::OnNameCheckboxClick ),
        wxCommandEventHandler( StampDetailsPanel::OnNameTextChanged ),
        wxCommandEventHandler( StampDetailsPanel::OnSubTitleCheckboxClick ),
        wxCommandEventHandler( StampDetailsPanel::OnSubTitleTextChanged ) );


    // m_fontBox = new wxStaticBox( theDialog, wxID_ANY, _( "Stamp Fonts" ) );
    // m_fontVSizer = new wxStaticBoxSizer( m_fontBox, wxVERTICAL );
    // m_leftColumnVerticalSizer->Add( m_fontVSizer, 0, wxGROW | wxALL, 5 );

   // m_fontBox = SetupStaticBox( theDialog, m_leftColumnVerticalSizer, m_fontVSizer );

    wxBoxSizer* fontboxSizer;
    m_fontBox = SetupBoxSizer( theDialog, m_leftColumnVerticalSizer, "Font", lastID, fontboxSizer, wxVERTICAL );


    SetupFontPicker( m_fontBox, fontboxSizer, lastID,
        _( "Name" ), _( "Default" ),
        m_nameFontPicker, m_nameColorPicker,
        wxFontPickerEventHandler( StampDetailsPanel::OnNameFontPicker ),
        wxColourPickerEventHandler( StampDetailsPanel::OnNameColorPicker ),
        wxCommandEventHandler( StampDetailsPanel::OnNameDefaultClick ) );


    SetupFontPicker( m_fontBox, fontboxSizer, lastID,
        _( "Nbr" ), _( "Default" ),
        m_nbrFontPicker, m_nbrColorPicker,
        wxFontPickerEventHandler( StampDetailsPanel::OnNbrFontPicker ),
        wxColourPickerEventHandler( StampDetailsPanel::OnNbrColorPicker ),
        wxCommandEventHandler( StampDetailsPanel::OnNbrDefaultClick ) );


    wxBoxSizer* nameLocationboxSizer;
    wxStaticBox* nameLocationbox = SetupBoxSizer( theDialog, m_rightColumnVerticalSizer, "Name Location", lastID, nameLocationboxSizer, wxHORIZONTAL );

    m_defaultButton = new wxRadioButton( nameLocationbox, lastID, _( "Default" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_defaultButton->SetValue( false );
    nameLocationboxSizer->Add( m_defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_topButton = new wxRadioButton( nameLocationbox, lastID, _( "Top" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_topButton->SetValue( true );
    nameLocationboxSizer->Add( m_topButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_bottomButton = new wxRadioButton( nameLocationbox, lastID, _( "Bottom" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_bottomButton->SetValue( false );
    nameLocationboxSizer->Add( m_bottomButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    m_imagePath = SetupLabelText( theDialog, m_leftColumnVerticalSizer, lastID, _( "Image Name" ), true, wxCommandEventHandler( StampDetailsPanel::OnMountAllowanceWidth ) );

    wxBoxSizer* stampboxSizer;
    wxStaticBox* stampboxBox = SetupBoxSizer( theDialog, m_rightColumnVerticalSizer, "Stamp", lastID, stampboxSizer, wxHORIZONTAL );

    m_height = SetupLabelText( stampboxBox, stampboxSizer, lastID, _( "Height" ), false, wxCommandEventHandler( StampDetailsPanel::OnHeight ) );

    m_width = SetupLabelText( stampboxBox, stampboxSizer, lastID, _( "Width" ), false, wxCommandEventHandler( StampDetailsPanel::OnWidth ) );


    wxBoxSizer* selvageBoxSizer;
    wxStaticBox* selvageBox = SetupBoxSizer( theDialog, m_rightColumnVerticalSizer, "Selvage", lastID, selvageBoxSizer, wxHORIZONTAL );

    m_selvageHeight = SetupLabelText( selvageBox, selvageBoxSizer, lastID, _( "Height" ), false, wxCommandEventHandler( StampDetailsPanel::OnSelvageHeight ) );

    m_selvageWidth = SetupLabelText( selvageBox, selvageBoxSizer, lastID, _( "Width" ), false, wxCommandEventHandler( StampDetailsPanel::OnSelvageWidth ) );


    wxBoxSizer* mountBoxSizer;
    wxStaticBox* mountSize = SetupBoxSizer( theDialog, m_rightColumnVerticalSizer, "Mount Allowance", lastID, mountBoxSizer, wxHORIZONTAL );

    m_mountAllowanceHeight = SetupLabelText( mountSize, mountBoxSizer, lastID, _( "Height" ), false, wxCommandEventHandler( StampDetailsPanel::OnMountAllowanceHeight ) );

    m_mountAllowanceWidth = SetupLabelText( mountSize, mountBoxSizer, lastID, _( "Width" ), false, wxCommandEventHandler( StampDetailsPanel::OnMountAllowanceWidth ) );


    wxBoxSizer* statusSizer = new wxBoxSizer( wxHORIZONTAL );
    m_rightColumnVerticalSizer->Add( statusSizer, 1, wxGROW | wxALL, 5 );

    m_statusList = new wxListBox( theDialog, ID_LISTCTRL, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );

    statusSizer->Add( m_statusList, 1, wxGROW | wxALL, 5 );


    m_imagePath->SetLabel( "ImageName" );
    Layout( );
}


void StampDetailsPanel::SetTitleLocation( )
{
    m_titleLocation = m_stamp->GetTitleLocation( );
    if ( m_titleLocation == Design::AT_TitleLocationTop )
    {
        m_topButton->SetValue( true );
        m_bottomButton->SetValue( false );
        m_defaultButton->SetValue( false );;
    }
    else if ( m_titleLocation == Design::AT_TitleLocationBottom )
    {
        m_topButton->SetValue( false );
        m_bottomButton->SetValue( true );
        m_defaultButton->SetValue( false );;
    }
    else if ( m_titleLocation == Design::AT_TitleLocationDefault )
    {
        m_topButton->SetValue( false );
        m_bottomButton->SetValue( false );
        m_defaultButton->SetValue( true );;
    }
}


void StampDetailsPanel::UpdateControls( )
{
    SetCatCodes( );

    SetHeight( m_stamp->GetStampHeightStr( ) );
    SetWidth( m_stamp->GetStampWidthStr( ) );

    SetSelvageHeight( m_stamp->GetSelvageHeightStr( ) );
    SetSelvageWidth( m_stamp->GetSelvageWidthStr( ) );

    SetMountAllowanceHeight( m_stamp->GetMountAllowanceHeightStr( ) );
    SetMountAllowanceWidth( m_stamp->GetMountAllowanceWidthStr( ) );

    //SetCatNbr( m_stamp->GetNbrString( ) );
    SetName( m_stamp->GetNameString( ) );
    SetShowNbr( m_stamp->GetShowNbr( ) );
    SetShowTitle( m_stamp->GetShowTitle( ) );
    //  SetShowSubTitle( m_stamp->GetShowSubTitle( ) );
    SetNbrFont( m_stamp->GetNbrFrame( )->GetFont( ) );
    SetNameFont( m_stamp->GetNameFrame( )->GetFont( ) );
    SetNbrColor( m_stamp->GetNbrFrame( )->GetColor( ) );
    SetNameColor( m_stamp->GetNameFrame( )->GetColor( ) );
    SetImageFilename( m_stamp->GetStampImageFilename( ) );
    SetTitleLocation( );
}


void StampDetailsPanel::SetupDialog( Design::Stamp* stamp )
{

    m_stamp = stamp;
    UpdateControls( );

    wxArrayString* errors = m_stamp->GetErrorArray( );
    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }

};


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
        m_catCode->SetValue( m_catCodesString );
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
    m_catCode->SetValue( "" );
}


// void StampDetailsPanel::RefreshFromCatalog( )
// {
//     wxTreeItemId m_designTreeID = GetAlbumTreeCtrl( )->GetSelection( );
//     if ( m_designTreeID.IsOk( ) )
//     {
//         DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( m_designTreeID );

//         Utils::StampLink* link = data->GetStampLink( );
//         if ( link )
//         {
//             wxTreeItemId catTreeID = link->GetCatTreeID( );
//             wxXmlNode* node = GetCatalogTreeCtrl( )->GetItemNode( catTreeID );

//             if ( node )
//             {
//                 Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
//                 Catalog::Entry  stamp( node );
//                 SetHeight( stamp.GetHeight( ) );
//                 SetWidth( stamp.GetWidth( ) );
//                 SetName( stamp.GetName( ) );
//                 SetCatNbr( stamp.GetID( ) );
//                 wxString label;
//                 label = GetCatNbr( ) + " - " + GetName( );
//                 GetAlbumTreeCtrl( )->SetItemText( m_designTreeID, label );
//             }
//         }
//     }
// }


bool StampDetailsPanel::ShowToolTips( )
{
    return true;
}


void StampDetailsPanel::SetImageFilename( wxString path )
{
    m_imagePath->SetValue( path );
    m_height->SetModified( false );
}


void StampDetailsPanel::SetHeight( wxString height )
{
    m_height->SetValue( height );
    m_height->SetModified( false );
}


void StampDetailsPanel::SetWidth( wxString width )
{
    m_width->SetValue( width );
    m_width->SetModified( false );
}


void StampDetailsPanel::SetSelvageHeight( wxString height )
{
    m_selvageHeight->SetValue( height );
    m_selvageHeight->SetModified( false );
}


void StampDetailsPanel::SetSelvageWidth( wxString width )
{
    m_selvageWidth->SetValue( width );
    m_selvageWidth->SetModified( false );
}


void StampDetailsPanel::SetMountAllowanceHeight( wxString height )
{
    m_mountAllowanceHeight->SetValue( height );
    m_mountAllowanceHeight->SetModified( false );
}


void StampDetailsPanel::SetMountAllowanceWidth( wxString width )
{
    m_mountAllowanceWidth->SetValue( width );
    m_mountAllowanceWidth->SetModified( false );
}


void StampDetailsPanel::SetCatNbr( wxString catNbr )
{
    m_catNbr->SetStringSelection( catNbr );
}


void StampDetailsPanel::SetName( wxString name )
{
    m_titleHelper->titleLabel->SetValue( name );
}


void StampDetailsPanel::SetShowNbr( bool state )
{
    m_nbrCheckbox->SetValue( state );
}


void StampDetailsPanel::SetShowTitle( bool state )
{
    m_titleHelper->titleCheckbox->SetValue( state );

    //  m_titleHelper->ShowTitleFontPicker( state );
    Layout( );
}


// void StampDetailsPanel::SetShowSubTitle( bool state )
// {
//     m_titleHelper->subTitleCheckbox->SetValue( state );

//     //   m_titleHelper->ShowSubTitleFontPicker( state );
//     m_titleHelper->subTitleLabel->Show( state );
//     m_dialogVerticalSizer->Layout( );
// }


void StampDetailsPanel::SetNbrFont( wxFont font )
{
    m_nbrFontPicker->SetSelectedFont( font );
}


void StampDetailsPanel::SetNameFont( wxFont font )
{
    m_nameFontPicker->SetSelectedFont( font );
}


void StampDetailsPanel::SetNbrColor( wxColour color )
{
    m_nbrColorPicker->SetColour( color );
}


void StampDetailsPanel::SetNameColor( wxColour color )
{
    m_nameColorPicker->SetColour( color );
}


wxString StampDetailsPanel::GetImageFilename( )
{
    return m_imagePath->GetValue( );
}


wxString StampDetailsPanel::GetHeight( )
{
    return m_height->GetValue( );
}


wxString StampDetailsPanel::GetWidth( )
{
    return m_width->GetValue( );
}


wxString StampDetailsPanel::GetSelvageHeight( )
{
    return m_selvageHeight->GetValue( );
}


wxString StampDetailsPanel::GetSelvageWidth( )
{
    return m_selvageWidth->GetValue( );
}


wxString StampDetailsPanel::GetMountAllowanceHeight( )
{
    return m_mountAllowanceHeight->GetValue( );
}


wxString StampDetailsPanel::GetMountAllowanceWidth( )
{
    return m_mountAllowanceWidth->GetValue( );
}


wxString StampDetailsPanel::GetCatNbr( )
{
    return m_catNbr->GetValue( );
}


wxString StampDetailsPanel::GetName( )
{
    return m_titleHelper->titleLabel->GetValue( );
}


bool StampDetailsPanel::GetShowNbr( )
{
    return m_nbrCheckbox->IsChecked( );
}


bool StampDetailsPanel::GetShowTitle( )
{
    return m_titleHelper->titleCheckbox->IsChecked( );
}


bool StampDetailsPanel::GetShowSubTitle( )
{
    return m_titleHelper->subTitleCheckbox->IsChecked( );
}


wxFont StampDetailsPanel::GetNbrFont( )
{
    return m_nbrFontPicker->GetSelectedFont( );
}


wxFont StampDetailsPanel::GetNameFont( )
{
    return m_nameFontPicker->GetSelectedFont( );
}


wxColour StampDetailsPanel::GetNbrColor( )
{
    return m_nbrColorPicker->GetColour( );
}


wxColour StampDetailsPanel::GetNameColor( )
{
    return m_nameColorPicker->GetColour( );
}


// bool StampDetailsPanel::IsNameModified( )
// {
//     return m_name->IsModified( );
// }


bool StampDetailsPanel::IsIDModified( )
{
    //  return m_catNbr->IsModified( );
    return true;
}


bool StampDetailsPanel::IsHeightModified( )
{
    return m_height->IsModified( );
}


bool StampDetailsPanel::IsWidthModified( )
{
    return m_width->IsModified( );
}


bool StampDetailsPanel::IsSelvageHeightModified( )
{
    return m_selvageHeight->IsModified( );
}


bool StampDetailsPanel::IsSelvageWidthModified( )
{
    return m_selvageWidth->IsModified( );
}


bool StampDetailsPanel::IsMountAllowanceHeightModified( )
{
    return m_mountAllowanceHeight->IsModified( );
}


bool StampDetailsPanel::IsMountAllowanceWidthModified( )
{
    return m_mountAllowanceWidth->IsModified( );
}


void StampDetailsPanel::SetHeightModified( bool state )
{
    m_height->SetModified( state );
}


void StampDetailsPanel::SetWidthModified( bool state )
{
    m_width->SetModified( state );
}


void StampDetailsPanel::SetSelvageHeightModified( bool state )
{
    m_selvageHeight->SetModified( state );
}


void StampDetailsPanel::SetSelvageWidthModified( bool state )
{
    m_selvageWidth->SetModified( state );
}


void StampDetailsPanel::SetMountAllowanceHeightModified( bool state )
{
    m_mountAllowanceHeight->SetModified( state );
}


void StampDetailsPanel::SetMountAllowanceWidthModified( bool state )
{
    m_mountAllowanceWidth->SetModified( state );
}


void StampDetailsPanel::SetCatNbrModified( bool state )
{
}


// void StampDetailsPanel::SetNameModified( bool state )
// {
//     m_name->SetModified( state );
// }



void StampDetailsPanel::OnTopRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationTop;
    event.Skip( );
}


void StampDetailsPanel::OnBottomRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationBottom;
    event.Skip( );
}

void StampDetailsPanel::OnCatNbrComboBoxSel( wxCommandEvent& event )
{
    wxString catNbr = m_catNbr->GetValue( );
    m_stamp->SetNbrString( catNbr );
    int pos = catNbr.Find( ":" );
    wxString cat = catNbr.Mid( 0, pos );
    m_stamp->SetCatalog( cat );

}

void StampDetailsPanel::OnDefaultRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationDefault;
    event.Skip( );
}

void StampDetailsPanel::OnNameFontPicker( wxFontPickerEvent& event )
{
}
void  StampDetailsPanel::OnNameColorPicker( wxColourPickerEvent& event )
{
}

void StampDetailsPanel::OnNbrFontPicker( wxFontPickerEvent& event )
{
}
void  StampDetailsPanel::OnNbrColorPicker( wxColourPickerEvent& event )
{
}

void StampDetailsPanel::OnNbrDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_NbrFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nbrFontPicker->SetSelectedFont( font );
    m_nbrColorPicker->SetColour( color );

    event.Skip( );
}


void StampDetailsPanel::OnNameDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NameFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nameFontPicker->SetSelectedFont( font );
    m_nameColorPicker->SetColour( color );
    event.Skip( );
}


void StampDetailsPanel::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );
    event.Skip( );
}
void  StampDetailsPanel::OnNameTextChanged( wxCommandEvent& event )
{
};

void StampDetailsPanel::OnSubTitleTextChanged( wxCommandEvent& event )
{
};

void StampDetailsPanel::OnNameCheckboxClick( wxCommandEvent& event )
{
    UpdateTitleState( m_titleHelper );
    Layout( );
}


void StampDetailsPanel::OnCatNbrCheckboxClick( wxCommandEvent& event )
{
    bool state = m_nbrCheckbox->GetValue( );
    m_stamp->SetShowNbr( state );
    m_catNbrFontPickerHelper->ShowFontPicker( state );
    Layout( );
}


void StampDetailsPanel::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    UpdateSubTitleState( m_titleHelper );
    Layout( );
};

void StampDetailsPanel::OnHeight( wxCommandEvent& event )
{
    wxString str = m_height->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetHeight( val );
    Layout( );
};

void StampDetailsPanel::OnWidth( wxCommandEvent& event )
{
    wxString str = m_width->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetWidth( val );
    Layout( );
};


void StampDetailsPanel::OnSelvageHeight( wxCommandEvent& event )
{
    wxString str = m_selvageHeight->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetSelvageHeight( val );
    Layout( );
};

void StampDetailsPanel::OnSelvageWidth( wxCommandEvent& event )
{
    wxString str = m_selvageWidth->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetSelvageWidth( val );
    Layout( );
};

void StampDetailsPanel::OnMountAllowanceHeight( wxCommandEvent& event )
{
    wxString str = m_mountAllowanceHeight->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetSelvageHeight( val );
    Layout( );
};

void StampDetailsPanel::OnMountAllowanceWidth( wxCommandEvent& event )
{
    wxString str = m_mountAllowanceWidth->GetValue( );
    double val;
    str.ToDouble( &val );
    m_stamp->SetMountAllowanceWidth( val );
    Layout( );
};