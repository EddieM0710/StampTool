/*
 * @file         AlbumDetailsDialog.cpp
 *@brief
* @author      Eddie Monroe
* Modified by:
* @author     Wed 23 Nov 2022 12:01:34 CST
 *
* @copyright Copyright ( c ) 2024
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
 ///////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "wx/notebook.h"

//  includes
#include "wx/imaglist.h"
//  includes

#include "gui/AlbumDetailsDialog.h"
#include "gui/LabeledTextBox.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/FontPickerHelper.h"
#include "design/DesignDefs.h"
#include "design/Album.h"
#include "utils/StampList.h"
#include "utils/Settings.h"
#include "utils/FontList.h"
#include "Defs.h"
#include "wx/treectrl.h"
#include <wx/fontdlg.h>
#include <wx/fontdata.h>

IMPLEMENT_DYNAMIC_CLASS( AlbumDetailsDialog, wxDialog )

BEGIN_EVENT_TABLE( AlbumDetailsDialog, wxDialog )
EVT_BUTTON( wxID_CANCEL, AlbumDetailsDialog::OnCancelClick )
EVT_BUTTON( wxID_OK, AlbumDetailsDialog::OnOkClick )
EVT_BUTTON( ID_NBRDEFAULTFONTBUTTON, AlbumDetailsDialog::OnNbrDefaultClick )
EVT_BUTTON( ID_NAMEDEFAULTFONTBUTTON, AlbumDetailsDialog::OnNameDefaultClick )
EVT_BUTTON( ID_TITLEDEFAULTFONTBUTTON, AlbumDetailsDialog::OnTitleDefaultClick )
EVT_BUTTON( ID_TEXTDEFAULTFONTBUTTON, AlbumDetailsDialog::OnTextDefaultClick )
EVT_CHOICE( ID_ORIENTATIONCHOICE, AlbumDetailsDialog::OnOrientationchoiceSelected )
END_EVENT_TABLE( )

//--------------

AlbumDetailsDialog::AlbumDetailsDialog( )
{
    Init( );
}

//--------------

AlbumDetailsDialog::AlbumDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

AlbumDetailsDialog::~AlbumDetailsDialog( )
{
}

//--------------

bool AlbumDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

//--------------

void AlbumDetailsDialog::CreateControls( )
{
    //   std::cout << "AlbumDetailsDialog" << "\n";
    theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 0, wxGROW | wxALL, 0 );

    //first row
    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer6, 0, wxGROW | wxALL, 0 );

    m_name = new LabeledTextBox( theDialog, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer6->Add( m_name, 1, wxGROW | wxALL, 5 );

    FontPicker* nbrFontPickerHelper = new FontPicker(
        theDialog, theDialogVerticalSizer,
        _( "Default Catalog Nbr  Font" ), wxID_STATIC,
        ID_NBRFONTPICKER, ID_NBRCOLORPICKER,
        _( "Default" ), ID_NBRDEFAULTFONTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_nbrFontPicker = nbrFontPickerHelper->GetFontPickerCtrl( );
    m_nbrColorPicker = nbrFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* nameFontPickerHelper = new FontPicker(
        theDialog, theDialogVerticalSizer,
        _( "Default Name Font" ), wxID_STATIC,
        ID_NAMEFONTPICKER, ID_NAMECOLORPICKER,
        _( "Default" ), ID_NAMEDEFAULTFONTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_nameFontPicker = nameFontPickerHelper->GetFontPickerCtrl( );
    m_nameColorPicker = nameFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* titleFontPickerHelper = new FontPicker(
        theDialog, theDialogVerticalSizer,
        _( "Default Title Font" ), wxID_STATIC,
        ID_TITLEFONTPICKER, ID_TITLECOLORPICKER,
        _( "Default" ), ID_TITLEDEFAULTFONTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_titleFontPicker = titleFontPickerHelper->GetFontPickerCtrl( );
    m_titleColorPicker = titleFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* textFontPickerHelper = new FontPicker(
        theDialog, theDialogVerticalSizer,
        _( "Default Text Font" ), wxID_STATIC,
        ID_TEXTFONTPICKER, ID_TEXTCOLORPICKER,
        _( "Default" ), ID_TEXTDEFAULTFONTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_textFontPicker = textFontPickerHelper->GetFontPickerCtrl( );
    m_textColorPicker = textFontPickerHelper->GetColourPickerCtrl( );

    wxBoxSizer* paperSizeBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( paperSizeBoxSizer, 0, wxGROW | wxALL, 0 );

    m_overSizeCheckbox = new wxCheckBox( theDialog, ID_OVERSIZECHECKBOX, _( "Oversize Paper" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_overSizeCheckbox->SetValue( true );
    paperSizeBoxSizer->Add( m_overSizeCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );

    m_paperHeight = new LabeledTextBox( theDialog, ID_PAPERHEIGHTLABELEDTEXTBOX123, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_paperHeight->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    paperSizeBoxSizer->Add( m_paperHeight, 1, wxGROW | wxALL, 5 );

    m_paperWidth = new LabeledTextBox( theDialog, ID_PAPERWIDTHLABELEDTEXTBOX123, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_paperWidth->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    paperSizeBoxSizer->Add( m_paperWidth, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer4, 0, wxGROW | wxALL, 0 );

    m_height = new LabeledTextBox( theDialog, ID_HEIGHTLABELEDTEXTBOX123, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_height->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer4->Add( m_height, 1, wxGROW | wxALL, 5 );

    m_width = new LabeledTextBox( theDialog, ID_WIDTHLABELEDTEXTBOX123, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_width->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer4->Add( m_width, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer7, 0, wxGROW | wxALL, 0 );

    m_topMargin = new LabeledTextBox( theDialog, ID_TOPMARGINLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_topMargin->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer7->Add( m_topMargin, 1, wxGROW | wxALL, 5 );

    m_bottomMargin = new LabeledTextBox( theDialog, ID_BOTTOMMARGINLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_bottomMargin->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer7->Add( m_bottomMargin, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer10, 0, wxGROW | wxALL, 0 );

    m_rightMargin = new LabeledTextBox( theDialog, ID_RIGHTMARGINLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_rightMargin->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer10->Add( m_rightMargin, 1, wxGROW | wxALL, 5 );

    m_leftMargin = new LabeledTextBox( theDialog, ID_LEFTMARGINLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_leftMargin->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer10->Add( m_leftMargin, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* borderBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( borderBoxSizer, 0, wxGROW | wxALL, 0 );

    m_borderFilename = new LabeledTextBox( theDialog, ID_BORDERFILENAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_borderFilename->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    borderBoxSizer->Add( m_borderFilename, 1, wxGROW | wxALL, 5 );


    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer3, 0, wxGROW | wxALL, 0 );

    m_borderSize = new LabeledTextBox( theDialog, ID_BORDERSIZELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_borderSize->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer3->Add( m_borderSize, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer20 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer20, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    m_nbrCheckbox = new wxCheckBox( theDialog, ID_NBRDEFAULTCHECKBOX, _( "Show Catalog Nbr" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_nbrCheckbox->SetValue( true );
    itemBoxSizer20->Add( m_nbrCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_stampTitleCheckbox = new wxCheckBox( theDialog, ID_STAMPTITLEDEFAULTCHECKBOX, _( "Show Stamp Title" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_stampTitleCheckbox->SetValue( true );
    itemBoxSizer20->Add( m_stampTitleCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_grayScaleImagesCheckbox = new wxCheckBox( theDialog, ID_GRAYSCALECHECKBOX, _( "Show Grayscale Images" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_grayScaleImagesCheckbox->SetValue( true );
    itemBoxSizer20->Add( m_grayScaleImagesCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    wxStaticText* orientationStatic = new wxStaticText(
        theDialog, wxID_STATIC, _( " Default Orientation:" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer20->Add( orientationStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxArrayString m_orientationChoiceStrings( 2, Design::OrientationStrings );
    m_orientationChoice = new wxChoice( theDialog, wxALIGN_CENTER_VERTICAL, wxDefaultPosition, wxDefaultSize, m_orientationChoiceStrings, 0 );
    m_orientationChoice->SetSelection( Design::AT_Portrait );

    itemBoxSizer20->Add( m_orientationChoice, 0, wxALIGN_LEFT | wxALL, 0 );

    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer13, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* itemButton14 = new wxButton( theDialog, ID_REFRESHBUTTON123, _( "Refresh from Catalog" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add( itemButton14, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer13->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_validate = new wxButton( theDialog, ID_VALIDATEBUTTON123, _( "Validate" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add( m_validate, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( itemBoxSizer17, 2, wxGROW | wxALL, 5 );

    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( theDialog, ID_LISTCTRL123, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );

    itemBoxSizer17->Add( m_statusList, 2, wxGROW | wxALL, 5 );

    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  

    m_name->SetToolTip( "Name of Album" );
    m_paperHeight->SetToolTip( "Height of paper in printer (in mm)" );
    m_name->SetLabel( "Name" );
    m_paperHeight->SetLabel( "Paper Height" );
    m_paperWidth->SetLabel( "Paper Width" );
    m_borderFilename->SetLabel( "Border Filename" );
    m_height->SetLabel( "Page Height" );
    m_width->SetLabel( "Page Width" );
    m_topMargin->SetLabel( "Top Margin" );
    m_bottomMargin->SetLabel( "Bottom Margin" );
    m_rightMargin->SetLabel( "Right Margin" );
    m_leftMargin->SetLabel( "Left Margin" );
    m_borderSize->SetLabel( "Border Size" );
}

//--------------


//--------------

wxString AlbumDetailsDialog::GetName( ) { return m_name->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetPaperHeight( ) { return m_paperHeight->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetPaperWidth( ) { return m_paperWidth->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetPageHeight( ) { return m_height->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetPageWidth( ) { return m_width->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetTopMargin( ) { return m_topMargin->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetBottomMargin( ) { return m_bottomMargin->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetLeftMargin( ) { return m_leftMargin->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetRightMargin( ) { return m_rightMargin->GetValue( ); }

//--------------

wxString AlbumDetailsDialog::GetBorderSize( ) { return m_borderSize->GetValue( ); }

// --------------

wxString AlbumDetailsDialog::GetBorderFilename( ) { return m_borderFilename->GetValue( ); }

//--------------

wxFont AlbumDetailsDialog::GetNbrFont( ) { return m_nbrFontPicker->GetSelectedFont( ); }

//--------------

wxFont AlbumDetailsDialog::GetNameFont( ) { return m_nameFontPicker->GetSelectedFont( ); }

//--------------

wxFont AlbumDetailsDialog::GetTextFont( ) { return m_textFontPicker->GetSelectedFont( ); }

//--------------

wxFont AlbumDetailsDialog::GetTitleFont( ) { return m_titleFontPicker->GetSelectedFont( ); }

//--------------

wxColour AlbumDetailsDialog::GetNbrColor( ) { return m_nbrColorPicker->GetColour( ); }

//--------------

wxColour AlbumDetailsDialog::GetNameColor( ) { return m_nbrColorPicker->GetColour( ); }

//--------------

wxColour AlbumDetailsDialog::GetTextColor( ) { return m_textColorPicker->GetColour( ); }

//--------------

wxColour AlbumDetailsDialog::GetTitleColor( ) { return m_titleColorPicker->GetColour( ); }

//--------------

bool AlbumDetailsDialog::GetShowNbr( ) { return m_nbrCheckbox->IsChecked( ); }
bool AlbumDetailsDialog::GetOverSizePaper( ) { return m_overSizeCheckbox->IsChecked( ); }

//--------------

bool AlbumDetailsDialog::GetShowStampTitle( ) { return m_stampTitleCheckbox->GetValue( ); }

//--------------

void AlbumDetailsDialog::Init( )
{
    m_name = NULL;
    m_height = NULL;
    m_width = NULL;
    m_topMargin = NULL;
    m_bottomMargin = NULL;
    m_rightMargin = NULL;
    m_leftMargin = NULL;
    m_borderSize = NULL;
    m_validate = NULL;
    m_statusList = NULL;
}


//--------------

bool AlbumDetailsDialog::IsNameModified( ) { return m_name->IsModified( ); }

//--------------

bool AlbumDetailsDialog::IsPaperHeightModified( ) { return m_paperHeight->IsModified( ); }

//--------------

bool AlbumDetailsDialog::IsPaperWidthModified( ) { return m_paperWidth->IsModified( ); }
//--------------

bool AlbumDetailsDialog::IsPageHeightModified( ) { return m_height->IsModified( ); }

//--------------

bool AlbumDetailsDialog::IsPageWidthModified( ) { return m_width->IsModified( ); }

//--------------

bool AlbumDetailsDialog::IsTopMarginModified( ) { return m_topMargin->IsModified( ); }

//--------------

bool AlbumDetailsDialog::IsBottomMarginModified( ) { return m_bottomMargin->IsModified( ); }

//--------------

bool AlbumDetailsDialog::IsLeftMarginModified( ) { return m_leftMargin->IsModified( ); }

//--------------

bool AlbumDetailsDialog::IsRightMarginModified( ) { return m_rightMargin->IsModified( ); };

//--------------

bool AlbumDetailsDialog::IsBorderSizeModified( ) { return m_borderSize->IsModified( ); }


//--------------

void AlbumDetailsDialog::SetName( wxString name )
{
    m_name->SetValue( name );
    m_name->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetPageHeight( wxString height )
{
    m_height->SetValue( height );
    m_height->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetPageWidth( wxString width )
{
    m_width->SetValue( width );
    m_width->SetModified( false );
}
//--------------

void AlbumDetailsDialog::SetPaperHeight( wxString height )
{
    m_paperHeight->SetValue( height );
    m_paperHeight->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetPaperWidth( wxString width )
{
    m_paperWidth->SetValue( width );
    m_paperWidth->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetTopMargin( wxString topMargin )
{
    m_topMargin->SetValue( topMargin );
    m_topMargin->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetBottomMargin( wxString bottomMargin )
{
    m_bottomMargin->SetValue( bottomMargin );
    m_bottomMargin->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetLeftMargin( wxString leftMargin )
{
    m_leftMargin->SetValue( leftMargin );
    m_leftMargin->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetRightMargin( wxString rightMargin )
{
    m_rightMargin->SetValue( rightMargin );
    m_rightMargin->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetBorderSize( wxString borderSize )
{
    m_borderSize->SetValue( borderSize );
    m_borderSize->SetModified( false );
}

void AlbumDetailsDialog::SetBorderFilename( wxString filename )
{
    m_borderFilename->SetValue( filename );
    m_borderFilename->SetModified( false );
}

//--------------

void AlbumDetailsDialog::SetupDialog( wxTreeItemId treeID )
{
    if ( treeID.IsOk( ) )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( treeID );
        m_album = ( Design::Album* ) data->GetNodeElement( );
        UpdateControls( );

        wxArrayString* errors = m_album->GetErrorArray( );
        if ( !errors->IsEmpty( ) )
        {
            m_statusList->InsertItems( *errors, 0 );
        }
    }
};

//--------------

void AlbumDetailsDialog::SetNameModified( bool state ) { m_name->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetPaperHeightModified( bool state ) { m_paperHeight->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetPaperWidthModified( bool state ) { m_paperWidth->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetPageHeightModified( bool state ) { m_height->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetPageWidthModified( bool state ) { m_width->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetTopMarginModified( bool state ) { m_topMargin->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetBottomMarginModified( bool state ) { m_bottomMargin->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetLeftMarginModified( bool state ) { m_leftMargin->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetRightMarginModified( bool state ) { m_rightMargin->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetBorderSizeModified( bool state ) { m_borderSize->SetModified( state ); }

//--------------

void AlbumDetailsDialog::SetShowNbr( bool state ) { m_nbrCheckbox->SetValue( state ); }

void AlbumDetailsDialog::SetOverSizePaper( bool state ) { m_overSizeCheckbox->SetValue( state ); }

//--------------

void AlbumDetailsDialog::SetShowStampTitle( bool state ) { m_stampTitleCheckbox->SetValue( state ); }

//--------------

void AlbumDetailsDialog::SetNbrFont( wxFont font ) { m_nbrFontPicker->SetSelectedFont( font ); }

//--------------

void AlbumDetailsDialog::SetNameFont( wxFont font ) { m_nameFontPicker->SetSelectedFont( font ); }

//--------------

void AlbumDetailsDialog::SetTextFont( wxFont font ) { m_textFontPicker->SetSelectedFont( font ); }

//--------------

void AlbumDetailsDialog::SetTitleFont( wxFont font ) { m_titleFontPicker->SetSelectedFont( font ); }

//--------------

void AlbumDetailsDialog::SetNbrColor( wxColour color ) { m_nbrColorPicker->SetColour( color ); }

//--------------

void AlbumDetailsDialog::SetNameColor( wxColour color ) { m_nbrColorPicker->SetColour( color ); }

//--------------

void AlbumDetailsDialog::SetTextColor( wxColour color ) { m_textColorPicker->SetColour( color ); }

//--------------

void AlbumDetailsDialog::SetTitleColor( wxColour color ) { m_titleColorPicker->SetColour( color ); }

//--------------

void AlbumDetailsDialog::SetGrayScaleImages( bool val ) { m_grayScaleImagesCheckbox->SetValue( val ); };

//--------------

bool AlbumDetailsDialog::GetGrayScaleImages( ) { return m_grayScaleImagesCheckbox->GetValue( ); }

//--------------

bool AlbumDetailsDialog::ShowToolTips( )
{
    return true;
}


//--------------

void AlbumDetailsDialog::OnCancelClick( wxCommandEvent& event )
{
    event.Skip( );
}

//--------------

void AlbumDetailsDialog::OnNbrDefaultClick( wxCommandEvent& event )
{

    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NbrFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nbrFontPicker->SetSelectedFont( font );
    m_nbrColorPicker->SetColour( color );

    event.Skip( );
}

//--------------

void AlbumDetailsDialog::OnNameDefaultClick( wxCommandEvent& event )
{

    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NameFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nameFontPicker->SetSelectedFont( font );
    m_nameColorPicker->SetColour( color );

    event.Skip( );
}

//--------------

void AlbumDetailsDialog::OnTextDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_TextFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_textFontPicker->SetSelectedFont( font );
    m_textColorPicker->SetColour( color );

    event.Skip( );
}

//--------------

void AlbumDetailsDialog::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );

    event.Skip( );
}

//--------------

void AlbumDetailsDialog::OnOkClick( wxCommandEvent& event )
{

    if ( IsNameModified( ) )
    {
        wxString newName = GetName( );
        m_album->SetAttrStr( Design::AT_Name, newName );
    }

    if ( IsPaperHeightModified( ) )
    {
        m_album->SetPaperHeight( GetPaperHeight( ) );
    }
    if ( IsPaperWidthModified( ) )
    {
        m_album->SetPaperWidth( GetPaperWidth( ) );
    }
    if ( IsPageHeightModified( ) )
    {
        m_album->SetPageHeight( GetPageHeight( ) );
    }
    if ( IsPageWidthModified( ) )
    {
        m_album->SetPageWidth( GetPageWidth( ) );
    }
    if ( IsTopMarginModified( ) )
    {
        m_album->SetTopMargin( GetTopMargin( ) );
    }
    if ( IsBottomMarginModified( ) )
    {
        m_album->SetBottomMargin( GetBottomMargin( ) );
    }
    if ( IsLeftMarginModified( ) )
    {
        m_album->SetLeftMargin( GetLeftMargin( ) );
    }
    if ( IsRightMarginModified( ) )
    {
        m_album->SetRightMargin( GetRightMargin( ) );
    }
    if ( IsBorderSizeModified( ) )
    {
        m_album->SetBorderSize( GetBorderSize( ) );
    }
    m_album->SetOverSizePaper( GetOverSizePaper( ) );
    m_album->SetShowNbr( GetShowNbr( ) );
    m_album->SetShowTitle( GetShowStampTitle( ) );
    m_album->SetGrayScaleImages( GetGrayScaleImages( ) );
    m_album->SetDefaultOrientation( GetOrientation( ) );


    m_album->SetBorderFilename( GetBorderFilename( ) );
    wxFont newFont = GetNbrFont( );

    m_album->SetFont( Design::AT_TextFontType, GetTextFont( ), GetTextColor( ) );
    m_album->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );
    m_album->SetFont( Design::AT_TitleFontType, GetTitleFont( ), GetTitleColor( ) );


    event.Skip( );
}

//--------------

void AlbumDetailsDialog::UpdateControls( )
{
    SetOverSizePaper( m_album->GetOverSizePaper( ) );
    SetPaperHeight( m_album->GetPaperHeightStr( ) );
    SetPaperWidth( m_album->GetPaperWidthStr( ) );
    SetPageHeight( m_album->GetPageHeightStr( ) );
    SetPageWidth( m_album->GetPageWidthStr( ) );
    SetTopMargin( m_album->GetTopMarginStr( ) );
    SetBottomMargin( m_album->GetTopMarginStr( ) );
    SetLeftMargin( m_album->GetLeftMarginStr( ) );
    SetRightMargin( m_album->GetRightMarginStr( ) );
    SetBorderSize( m_album->GetBorderSizeStr( ) );
    SetShowNbr( m_album->GetShowNbr( ) );
    SetShowStampTitle( m_album->GetShowTitle( ) );
    SetGrayScaleImages( m_album->GetGrayScaleImages( ) );
    SetBorderFilename( m_album->GetBorderFileName( ) );

    SetNbrFont( m_album->GetFont( Design::AT_NbrFontType ) );
    SetTextFont( m_album->GetFont( Design::AT_TextFontType ) );
    SetTitleFont( m_album->GetFont( Design::AT_TitleFontType ) );
    SetNbrColor( m_album->GetColor( Design::AT_NbrFontType ) );
    SetTextColor( m_album->GetColor( Design::AT_TextFontType ) );
    SetTitleColor( m_album->GetColor( Design::AT_TitleFontType ) );
    SetName( m_album->GetAttrStr( Design::AT_Name ) );

}

void AlbumDetailsDialog::OnOrientationchoiceSelected( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_ORIENTATIONCHOICE in PageDetailsDialog.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_ORIENTATIONCHOICE in PageDetailsDialog. 
}

