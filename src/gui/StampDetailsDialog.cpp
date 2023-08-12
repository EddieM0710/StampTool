/**
 * @file StampDetailsDialog.cpp
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

#include "gui/StampDetailsDialog.h"
#include "gui/LabeledTextBox.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/FontPickerHelper.h"
#include "design/Album.h"
#include "utils/StampList.h"
#include "utils/Settings.h"
#include "Defs.h"
#include "utils/FontList.h"
#include "gui/TitleHelper.h"
 /*
  * StampDetailsDialog type definition
  */

IMPLEMENT_DYNAMIC_CLASS( StampDetailsDialog, wxDialog )


/*
 * StampDetailsDialog event table definition
 */
 /**
  * BEGIN_EVENT_TABLE
  *
  * @param  {StampDetailsDialog} undefined :
  * @param  {wxDialog} undefined           :
  */
    BEGIN_EVENT_TABLE( StampDetailsDialog, wxDialog )
    EVT_BUTTON( ID_REFRESHBUTTON, StampDetailsDialog::OnRefreshButtonClick )
    EVT_BUTTON( wxID_CANCEL, StampDetailsDialog::OnCancelClick )
    EVT_BUTTON( wxID_OK, StampDetailsDialog::OnOkClick )
    EVT_CHECKBOX( ID_CATNBRCHECKBOX, StampDetailsDialog::OnCatNbrCheckboxClick )
    EVT_RADIOBUTTON( ID_DEFAULTRADIOBUTTON, StampDetailsDialog::OnDefaultRadioButtonSelected )
    EVT_RADIOBUTTON( ID_TOPRADIOBUTTON, StampDetailsDialog::OnTopRadioButtonSelected )
    EVT_RADIOBUTTON( ID_BOTTOMRADIOBUTTON, StampDetailsDialog::OnBottomRadioButtonSelected )
    END_EVENT_TABLE( )


    /*
     * StampDetailsDialog constructors
     */

    StampDetailsDialog::StampDetailsDialog( )
{
    Init( );
}


StampDetailsDialog::StampDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * StampDetailsDialog creator
 */

bool StampDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // StampDetailsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // StampDetailsDialog creation
    return true;
}


/*
 * StampDetailsDialog destructor
 */

StampDetailsDialog::~StampDetailsDialog( )
{
    // StampDetailsDialog destruction
    // StampDetailsDialog destruction
}


/*
 * Member initialisation
 */

void StampDetailsDialog::Init( )
{
    // StampDetailsDialog member initialisation
    m_catNbr = NULL;
    m_name = NULL;
    m_height = NULL;
    m_width = NULL;
    m_validate = NULL;
    m_statusList = NULL;
    m_designTreeID = NULL;
    m_nbrCheckbox = NULL;
    m_titleCheckbox = NULL;

    // StampDetailsDialog member initialisation
}


/*
 * Control creation for StampDetailsDialog
 */

void StampDetailsDialog::CreateControls( )
{

    StampDetailsDialog* theDialog = this;

    m_dialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( m_dialogVerticalSizer );
    {
        wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( theDialogHorizontalSizer, 0, wxGROW | wxALL, 0 );

        wxBoxSizer* checkBoxHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( checkBoxHorizontalSizer, 0, wxGROW | wxALL, 0 );

        m_nbrCheckbox = new wxCheckBox( theDialog, ID_CATNBRCHECKBOX, _( "Show ID" ), wxDefaultPosition, wxDefaultSize, 0 );
        m_nbrCheckbox->SetValue( false );
        checkBoxHorizontalSizer->Add( m_nbrCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );

        m_catNbr = new LabeledTextBox( theDialog, ID_IDLABELTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_catNbr->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        m_dialogVerticalSizer->Add( m_catNbr, 0, wxGROW | wxALL, 5 );

        int lastID = ID_LastID;

        m_catNbrFontPickerHelper = new FontPicker(
            theDialog, m_dialogVerticalSizer,
            _( "Catalog Nbr Font" ), _( "Default" ), lastID,
            *wxNORMAL_FONT, *wxBLACK );
        m_nbrFontPicker = m_catNbrFontPickerHelper->GetFontPickerCtrl( );
        m_nbrColorPicker = m_catNbrFontPickerHelper->GetColourPickerCtrl( );

        Connect( m_catNbrFontPickerHelper->GetDefaultButton( )->GetId( ),
            wxEVT_BUTTON,
            wxCommandEventHandler( StampDetailsDialog::OnNbrDefaultClick ) );

        m_titleHelper = new TitleHelper( theDialog, m_dialogVerticalSizer, lastID, HasLabels | NoHideTitle );
        m_name = m_titleHelper->GetTitleLabel( );
        m_subTitleLabel = m_titleHelper->GetSubTitleLabel( );
        m_titleCheckbox = m_titleHelper->GetTitleCheckbox( );
        m_titleCheckbox->SetLabelText( "Name" );
        m_titleCheckbox->SetValue( true );
        m_subTitleCheckbox = m_titleHelper->GetSubTitleCheckbox( );
        m_subTitleCheckbox->SetLabelText( "SubTitle" );
        m_subTitleCheckbox->SetValue( false );

        m_nameFontPicker = m_titleHelper->GetTitleFontPickerCtrl( );
        m_nameColorPicker = m_titleHelper->GetTitleColourPickerCtrl( );

        m_subTitleFontPicker = m_titleHelper->GetSubTitleFontPickerCtrl( );
        m_subTitleColorPicker = m_titleHelper->GetSubTitleColourPickerCtrl( );

        Connect( m_titleHelper->GetSubTitleDefaultButton( )->GetId( ),
            wxEVT_BUTTON,
            wxCommandEventHandler( StampDetailsDialog::OnNameDefaultClick ) );

        Connect( m_titleHelper->GetSubTitleDefaultButton( )->GetId( ),
            wxEVT_BUTTON,
            wxCommandEventHandler( StampDetailsDialog::OnSubTitleDefaultClick ) );

        Connect( m_titleHelper->GetTitleCheckbox( )->GetId( ),
            wxEVT_CHECKBOX,
            wxCommandEventHandler( StampDetailsDialog::OnNameCheckboxClick ) );

        Connect( m_titleHelper->GetSubTitleCheckbox( )->GetId( ),
            wxEVT_CHECKBOX,
            wxCommandEventHandler( StampDetailsDialog::OnSubTitleCheckboxClick ) );

        m_TitleLocationBox = new wxStaticBox( theDialog, wxID_ANY, _( "Name Location" ) );
        m_titleLocationVSizer = new wxStaticBoxSizer( m_TitleLocationBox, wxVERTICAL );
        m_dialogVerticalSizer->Add( m_titleLocationVSizer, 0, wxGROW | wxALL, 5 );

        m_titleLocationHSizer = new wxBoxSizer( wxHORIZONTAL );
        m_titleLocationVSizer->Add( m_titleLocationHSizer, 0, wxGROW | wxALL, 0 );

        m_defaultButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_DEFAULTRADIOBUTTON, _( "Default" ), wxDefaultPosition, wxDefaultSize, 0 );
        m_defaultButton->SetValue( false );
        m_titleLocationHSizer->Add( m_defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_topButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_TOPRADIOBUTTON, _( "Top" ), wxDefaultPosition, wxDefaultSize, 0 );
        m_topButton->SetValue( true );
        m_titleLocationHSizer->Add( m_topButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_bottomButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_BOTTOMRADIOBUTTON, _( "Bottom" ), wxDefaultPosition, wxDefaultSize, 0 );
        m_bottomButton->SetValue( false );
        m_titleLocationHSizer->Add( m_bottomButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_imagePath = new LabeledTextBox( theDialog, ID_IMAGEPATHLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_imagePath->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        m_dialogVerticalSizer->Add( m_imagePath, 0, wxGROW | wxALL, 5 );

        wxBoxSizer* sizeSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( sizeSizer, 0, wxGROW | wxALL, 0 );

        wxStaticText* stampStaticText = new wxStaticText( theDialog, wxID_STATIC, _( "Stamp" ), wxDefaultPosition, wxDefaultSize, 0 );
        sizeSizer->Add( stampStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_height = new LabeledTextBox( theDialog, ID_HEIGHTLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_height->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        sizeSizer->Add( m_height, 1, wxGROW | wxALL, 5 );

        m_width = new LabeledTextBox( theDialog, ID_WIDTHLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_width->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        sizeSizer->Add( m_width, 1, wxGROW | wxALL, 5 );

        wxBoxSizer* selvageSizeSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( selvageSizeSizer, 0, wxGROW | wxALL, 0 );

        wxStaticText* selvageStaticText = new wxStaticText( theDialog, wxID_STATIC, _( "Selvage" ), wxDefaultPosition, wxDefaultSize, 0 );
        selvageSizeSizer->Add( selvageStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_selvageHeight = new LabeledTextBox( theDialog, ID_SELVAGEHEIGHTLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_selvageHeight->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        selvageSizeSizer->Add( m_selvageHeight, 1, wxGROW | wxALL, 5 );

        m_selvageWidth = new LabeledTextBox( theDialog, ID_SELVAGEWIDTHLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_selvageWidth->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        selvageSizeSizer->Add( m_selvageWidth, 1, wxGROW | wxALL, 5 );

        wxBoxSizer* mountSizeSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( mountSizeSizer, 0, wxGROW | wxALL, 0 );

        wxStaticText* mountStaticText = new wxStaticText( theDialog, wxID_STATIC, _( "Mount Allowance" ), wxDefaultPosition, wxDefaultSize, 0 );
        mountSizeSizer->Add( mountStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_mountAllowanceHeight = new LabeledTextBox( theDialog, ID_MOUNTHEIGHTLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_mountAllowanceHeight->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        mountSizeSizer->Add( m_mountAllowanceHeight, 1, wxGROW | wxALL, 5 );

        m_mountAllowanceWidth = new LabeledTextBox( theDialog, ID_MOUNTWIDTHLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
        m_mountAllowanceWidth->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
        mountSizeSizer->Add( m_mountAllowanceWidth, 1, wxGROW | wxALL, 5 );

        wxBoxSizer* refreshSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( refreshSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

        wxButton* itemButton7 = new wxButton( theDialog, ID_REFRESHBUTTON, _( "Refresh from Catalog" ), wxDefaultPosition, wxDefaultSize, 0 );
        refreshSizer->Add( itemButton7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        refreshSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        m_validate = new wxButton( theDialog, ID_VALIDATEBUTTON, _( "Validate" ), wxDefaultPosition, wxDefaultSize, 0 );
        refreshSizer->Add( m_validate, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

        wxBoxSizer* statusSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( statusSizer, 2, wxGROW | wxALL, 5 );

        m_statusList = new wxListBox( theDialog, ID_LISTCTRL, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );

        statusSizer->Add( m_statusList, 2, wxGROW | wxALL, 5 );

        wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
        m_dialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );
        {
            wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
            dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

            wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
            dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
        }
    }

    m_catNbr->SetLabel( "Catalog Nbr" );
    m_name->SetLabel( "Name" );
    m_height->SetLabel( "Height" );
    m_width->SetLabel( "Width" );
    m_selvageHeight->SetLabel( "Height" );
    m_selvageWidth->SetLabel( "Width" );
    m_mountAllowanceHeight->SetLabel( "Height" );
    m_mountAllowanceWidth->SetLabel( "Width" );
    m_imagePath->SetLabel( "ImageName" );
    m_subTitleLabel->SetLabel( "Subtitle" );
}


void StampDetailsDialog::SetTitleLocation( )
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


void StampDetailsDialog::UpdateControls( )
{
    SetHeight( m_stamp->GetStampHeightStr( ) );
    SetWidth( m_stamp->GetStampWidthStr( ) );

    SetSelvageHeight( m_stamp->GetSelvageHeightStr( ) );
    SetSelvageWidth( m_stamp->GetSelvageWidthStr( ) );

    SetMountAllowanceHeight( m_stamp->GetMountAllowanceHeightStr( ) );
    SetMountAllowanceWidth( m_stamp->GetMountAllowanceWidthStr( ) );

    SetCatNbr( m_stamp->GetAttrStr( Design::AT_CatNbr ) );
    SetName( m_stamp->GetAttrStr( Design::AT_Name ) );
    SetShowNbr( m_stamp->GetShowNbr( ) );
    SetShowTitle( m_stamp->GetShowTitle( ) );
    SetShowSubTitle( m_stamp->GetShowSubTitle( ) );
    SetNbrFont( m_stamp->GetNbrFrame( )->GetFont( ) );
    SetNameFont( m_stamp->GetNameFrame( )->GetFont( ) );
    SetNbrColor( m_stamp->GetNbrFrame( )->GetColor( ) );
    SetNameColor( m_stamp->GetNameFrame( )->GetColor( ) );
    SetTitleLocation( );
}


void StampDetailsDialog::SetupDialog( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        m_designTreeID = id;
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( m_designTreeID );
        m_stamp = ( Design::Stamp* ) data->GetNodeElement( );
        UpdateControls( );

        wxArrayString* errors = m_stamp->GetErrorArray( );
        if ( !errors->IsEmpty( ) )
        {
            m_statusList->InsertItems( *errors, 0 );
        }
    }
};


void StampDetailsDialog::RefreshFromCatalog( )
{
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
                Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
                Catalog::Entry  stamp( node );
                SetHeight( stamp.GetHeight( ) );
                SetWidth( stamp.GetWidth( ) );
                SetName( stamp.GetName( ) );
                SetCatNbr( stamp.GetID( ) );
                wxString label;
                label = GetCatNbr( ) + " - " + GetName( );
                GetAlbumTreeCtrl( )->SetItemText( m_designTreeID, label );
            }
        }
    }
}


bool StampDetailsDialog::ShowToolTips( )
{
    return true;
}


void StampDetailsDialog::SetImageFilename( wxString path )
{
    m_imagePath->SetValue( path );
    m_height->SetModified( false );
}


void StampDetailsDialog::SetHeight( wxString height )
{
    m_height->SetValue( height );
    m_height->SetModified( false );
}


void StampDetailsDialog::SetWidth( wxString width )
{
    m_width->SetValue( width );
    m_width->SetModified( false );
}


void StampDetailsDialog::SetSelvageHeight( wxString height )
{
    m_selvageHeight->SetValue( height );
    m_selvageHeight->SetModified( false );
}


void StampDetailsDialog::SetSelvageWidth( wxString width )
{
    m_selvageWidth->SetValue( width );
    m_selvageWidth->SetModified( false );
}


void StampDetailsDialog::SetMountAllowanceHeight( wxString height )
{
    m_mountAllowanceHeight->SetValue( height );
    m_mountAllowanceHeight->SetModified( false );
}


void StampDetailsDialog::SetMountAllowanceWidth( wxString width )
{
    m_mountAllowanceWidth->SetValue( width );
    m_mountAllowanceWidth->SetModified( false );
}


void StampDetailsDialog::SetCatNbr( wxString catNbr )
{

    m_catNbr->SetValue( catNbr );
    m_catNbr->SetModified( false );
}


void StampDetailsDialog::SetName( wxString name )
{
    m_name->SetValue( name );
    m_name->SetModified( false );
}


void StampDetailsDialog::SetShowNbr( bool state )
{
    m_nbrCheckbox->SetValue( state );
}


void StampDetailsDialog::SetShowTitle( bool state )
{
    m_titleCheckbox->SetValue( state );

    m_titleHelper->ShowTitleFontPicker( state );
    m_dialogVerticalSizer->Layout( );
}


void StampDetailsDialog::SetShowSubTitle( bool state )
{
    m_subTitleCheckbox->SetValue( state );

    m_titleHelper->ShowSubTitleFontPicker( state );
    m_subTitleLabel->Show( state );
    m_dialogVerticalSizer->Layout( );
}


void StampDetailsDialog::SetNbrFont( wxFont font )
{
    m_nbrFontPicker->SetSelectedFont( font );
}


void StampDetailsDialog::SetNameFont( wxFont font )
{
    m_nameFontPicker->SetSelectedFont( font );
}


void StampDetailsDialog::SetNbrColor( wxColour color )
{
    m_nbrColorPicker->SetColour( color );
}


void StampDetailsDialog::SetNameColor( wxColour color )
{
    m_nameColorPicker->SetColour( color );
}


wxString StampDetailsDialog::GetImageFilename( )
{
    return m_imagePath->GetValue( );
}


wxString StampDetailsDialog::GetHeight( )
{
    return m_height->GetValue( );
}


wxString StampDetailsDialog::GetWidth( )
{
    return m_width->GetValue( );
}


wxString StampDetailsDialog::GetSelvageHeight( )
{
    return m_selvageHeight->GetValue( );
}


wxString StampDetailsDialog::GetSelvageWidth( )
{
    return m_selvageWidth->GetValue( );
}


wxString StampDetailsDialog::GetMountAllowanceHeight( )
{
    return m_mountAllowanceHeight->GetValue( );
}


wxString StampDetailsDialog::GetMountAllowanceWidth( )
{
    return m_mountAllowanceWidth->GetValue( );
}


wxString StampDetailsDialog::GetCatNbr( )
{
    return m_catNbr->GetValue( );
}


wxString StampDetailsDialog::GetName( )
{
    return m_name->GetValue( );
}


bool StampDetailsDialog::GetShowNbr( )
{
    return m_nbrCheckbox->IsChecked( );
}


bool StampDetailsDialog::GetShowTitle( )
{
    return m_titleCheckbox->IsChecked( );
}


bool StampDetailsDialog::GetShowSubTitle( )
{
    return m_subTitleCheckbox->IsChecked( );
}


wxFont StampDetailsDialog::GetNbrFont( )
{
    return m_nbrFontPicker->GetSelectedFont( );
}


wxFont StampDetailsDialog::GetNameFont( )
{
    return m_nameFontPicker->GetSelectedFont( );
}


wxColour StampDetailsDialog::GetNbrColor( )
{
    return m_nbrColorPicker->GetColour( );
}


wxColour StampDetailsDialog::GetNameColor( )
{
    return m_nameColorPicker->GetColour( );
}


bool StampDetailsDialog::IsNameModified( )
{
    return m_name->IsModified( );
}


bool StampDetailsDialog::IsIDModified( )
{
    return m_catNbr->IsModified( );
}


bool StampDetailsDialog::IsHeightModified( )
{
    return m_height->IsModified( );
}


bool StampDetailsDialog::IsWidthModified( )
{
    return m_width->IsModified( );
}


bool StampDetailsDialog::IsSelvageHeightModified( )
{
    return m_selvageHeight->IsModified( );
}


bool StampDetailsDialog::IsSelvageWidthModified( )
{
    return m_selvageWidth->IsModified( );
}


bool StampDetailsDialog::IsMountAllowanceHeightModified( )
{
    return m_mountAllowanceHeight->IsModified( );
}


bool StampDetailsDialog::IsMountAllowanceWidthModified( )
{
    return m_mountAllowanceWidth->IsModified( );
}


void StampDetailsDialog::SetHeightModified( bool state )
{
    m_height->SetModified( state );
}


void StampDetailsDialog::SetWidthModified( bool state )
{
    m_width->SetModified( state );
}


void StampDetailsDialog::SetSelvageHeightModified( bool state )
{
    m_selvageHeight->SetModified( state );
}


void StampDetailsDialog::SetSelvageWidthModified( bool state )
{
    m_selvageWidth->SetModified( state );
}


void StampDetailsDialog::SetMountAllowanceHeightModified( bool state )
{
    m_mountAllowanceHeight->SetModified( state );
}


void StampDetailsDialog::SetMountAllowanceWidthModified( bool state )
{
    m_mountAllowanceWidth->SetModified( state );
}


void StampDetailsDialog::SetCatNbrModified( bool state )
{
    m_catNbr->SetModified( state );
}


void StampDetailsDialog::SetNameModified( bool state )
{
    m_name->SetModified( state );
}


/*
 *   ID_BUTTON
 */

void StampDetailsDialog::OnRefreshButtonClick( wxCommandEvent& event )
{
    RefreshFromCatalog( );

    event.Skip( );
}


/*
 *   wxID_CANCEL
 */

void StampDetailsDialog::OnCancelClick( wxCommandEvent& event )
{

    event.Skip( );
}


/*
 *   wxID_OK
 */

void StampDetailsDialog::OnOkClick( wxCommandEvent& event )
{

    m_stamp->SetAttrStr( Design::AT_CatNbr, GetCatNbr( ) );
    m_stamp->SetAttrStr( Design::AT_Name, GetName( ) );
    m_stamp->SetStampHeight( GetHeight( ) );
    m_stamp->SetStampWidth( GetWidth( ) );
    m_stamp->SetSelvageHeight( GetSelvageHeight( ) );

    m_stamp->SetSelvageWidth( GetSelvageWidth( ) );

    m_stamp->SetMountAllowanceHeight( GetMountAllowanceHeight( ) );
    m_stamp->SetMountAllowanceWidth( GetMountAllowanceWidth( ) );

    m_stamp->SetShowNbr( GetShowNbr( ) );
    m_stamp->SetShowTitle( GetShowTitle( ) );
    m_stamp->SetShowSubTitle( GetShowSubTitle( ) );

    m_stamp->GetNameFrame( )->SetFont( GetNameFont( ), GetNameColor( ) );
    m_stamp->GetNbrFrame( )->SetFont( GetNbrFont( ), GetNbrColor( ) );
    m_stamp->SetTitleLocation( m_titleLocation );
    event.Skip( );
}


void StampDetailsDialog::OnTopRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationTop;
    event.Skip( );
}


void StampDetailsDialog::OnBottomRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationBottom;
    event.Skip( );
}


void StampDetailsDialog::OnDefaultRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationDefault;
    event.Skip( );
}


void StampDetailsDialog::OnNbrDefaultClick( wxCommandEvent& event )
{
    //m_stamp->GetNbrFrame( )->GetFontNdx()
    //MakeDefaultFont( );
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_NbrFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nbrFontPicker->SetSelectedFont( font );
    m_nbrColorPicker->SetColour( color );

    event.Skip( );
}


void StampDetailsDialog::OnNameDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NameFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nameFontPicker->SetSelectedFont( font );
    m_nameColorPicker->SetColour( color );
    event.Skip( );
}


void StampDetailsDialog::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );
    event.Skip( );
}


void StampDetailsDialog::OnNameCheckboxClick( wxCommandEvent& event )
{
    m_titleHelper->UpdateTitleState( );

    m_dialogVerticalSizer->Layout( );
}


void StampDetailsDialog::OnCatNbrCheckboxClick( wxCommandEvent& event )
{
    bool state = m_nbrCheckbox->GetValue( );

    m_catNbrFontPickerHelper->ShowFontPicker( state );
    m_dialogVerticalSizer->Layout( );
}


void StampDetailsDialog::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    m_titleHelper->UpdateSubTitleState( );
    m_dialogVerticalSizer->Layout( );
};
