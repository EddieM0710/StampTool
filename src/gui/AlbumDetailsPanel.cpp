/*
 * @file  AlbumDetailsPanel.cpp
 *@brief
* @author Eddie Monroe
* Modified by:
* @author Wed 23 Nov 2022 12:01:34 CST
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

// includes
#include "wx/imaglist.h"
// includes

#include "gui/AlbumDetailsPanel.h"
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
#include "AlbumDetailsPanel.h"

IMPLEMENT_DYNAMIC_CLASS( AlbumDetailsPanel, HelperPanel )


BEGIN_EVENT_TABLE( AlbumDetailsPanel, HelperPanel )

END_EVENT_TABLE( )

//--------------

AlbumDetailsPanel::AlbumDetailsPanel( )
{
    Init( );
}

//--------------

AlbumDetailsPanel::AlbumDetailsPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

AlbumDetailsPanel::~AlbumDetailsPanel( )
{
}

//--------------

bool AlbumDetailsPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    // wxDialog::Create( parent, id, caption, pos, size, style );
    wxPanel::Create( parent, id, pos, size, style );

    //( notebook, ID_PAGEDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );


    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

wxPanel* AlbumDetailsPanel::SetupAlbumDetailsPanel( wxWindow* parent, int& lastID )
{
    wxPanel* albumDetailsPanel = new wxPanel( parent, ++lastID, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    albumDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* albumVerticalSizer = new wxBoxSizer( wxVERTICAL );
    albumDetailsPanel->SetSizer( albumVerticalSizer );

    //first row

    m_name = SetupLabelText( albumDetailsPanel, albumVerticalSizer, ++lastID, _( "Name" ), true, wxCommandEventHandler( AlbumDetailsPanel::OnNameClick ) );

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer( wxHORIZONTAL );
    albumVerticalSizer->Add( itemBoxSizer17, 1, wxGROW | wxALL, 5 );

    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( albumDetailsPanel, ++lastID, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );

    itemBoxSizer17->Add( m_statusList, 1, wxGROW | wxALL, 5 );
    return albumDetailsPanel;
}


wxPanel* AlbumDetailsPanel::SetupPageDetailsPanel( wxWindow* parent, int& lastID )
{

    //>>> pageDetails vvvvv
    wxPanel* pageDetailsPanel = new wxPanel( parent, ++lastID, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    pageDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    pageDetailsPanel->SetSizer( detailsHorizontalSizer );

    wxBoxSizer* leftColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( leftColumnVerticalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* rightColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( rightColumnVerticalSizer, 1, wxGROW | wxALL, 0 );


    SetupFontPicker( pageDetailsPanel, leftColumnVerticalSizer, lastID,
        _( "Title Font" ), _( "Default" ),
        m_titleFontPicker, m_titleColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnTitleFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnTitleColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnTitleDefaultClick ) );


    SetupFontPicker( pageDetailsPanel, leftColumnVerticalSizer, lastID,
        _( "SubTitle Font" ), _( "Default" ),
        m_subTitleFontPicker, m_titleColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnSubTitleFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnSubTitleColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnSubTitleDefaultClick ) );

    SetupFontPicker( pageDetailsPanel, leftColumnVerticalSizer, lastID,
        _( "Text Font" ), _( "Default" ),
        m_textFontPicker, m_textColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnTextFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnTextColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnTextDefaultClick ) );



    wxStaticBox* oversizePaperBox = new wxStaticBox( pageDetailsPanel, wxID_ANY, _( "OverSize Paper" ) );

    wxStaticBoxSizer* paperVSizer = new wxStaticBoxSizer( oversizePaperBox, wxVERTICAL );

    leftColumnVerticalSizer->Add( paperVSizer, 0, wxGROW | wxALL, 0 );

    m_overSizeCheckbox = SetupCheckBox( oversizePaperBox, paperVSizer, ++lastID,
        _( "Oversize Paper" ), wxCommandEventHandler( AlbumDetailsPanel::OnOverSizeCheckBoxClick ) );

    wxBoxSizer* paperSizeBoxSizer = new wxBoxSizer( wxHORIZONTAL );

    paperVSizer->Add( paperSizeBoxSizer, 0, wxGROW | wxALL, 0 );

    //paperSizeBoxSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    HorizontalSpacer( paperSizeBoxSizer );

    m_paperHeight = SetupLabelText( oversizePaperBox, paperSizeBoxSizer, lastID,
        _( "Height" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPaperHeight ) );

    paperSizeBoxSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_paperWidth = SetupLabelText( oversizePaperBox, paperSizeBoxSizer, lastID,
        _( "Width" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPaperWidth ) );



    wxStaticBox* pageBox = new wxStaticBox( pageDetailsPanel, wxID_ANY, _( "Page" ) );

    wxStaticBoxSizer* pageBoxVSizer = new wxStaticBoxSizer( pageBox, wxVERTICAL );

    rightColumnVerticalSizer->Add( pageBoxVSizer, 1, wxGROW | wxALL, 0 );




    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    pageBoxVSizer->Add( itemBoxSizer4, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer4 );

    m_pageHeight = SetupLabelText( pageBox, itemBoxSizer4, lastID,
        _( "Height" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPageHeight ) );

    HorizontalSpacer( itemBoxSizer4 );

    m_pageWidth = SetupLabelText( pageBox, itemBoxSizer4, lastID,
        _( "Width" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPageWidth ) );

    wxStaticBox* marginBox = new wxStaticBox( pageBox, wxID_ANY, _( "Margin" ) );

    wxStaticBoxSizer* marginBoxVSizer = new wxStaticBoxSizer( marginBox, wxVERTICAL );

    pageBoxVSizer->Add( marginBoxVSizer, 0, wxGROW | wxALL, 5 );



    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer7, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer7 );

    m_topPageMargin = SetupLabelText( pageBox, itemBoxSizer7, lastID,
        _( "Top" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnTopPageMargin ) );
    HorizontalSpacer( itemBoxSizer7 );

    m_bottomPageMargin = SetupLabelText( pageBox, itemBoxSizer7, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnBottomPageMargin ) );

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer10, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer10 );

    m_leftPageMargin = SetupLabelText( pageBox, itemBoxSizer10, lastID,
        _( "Left" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnLeftPageMargin ) );

    HorizontalSpacer( itemBoxSizer10 );

    m_rightPageMargin = SetupLabelText( pageBox, itemBoxSizer10, lastID,
        _( "Right" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnRightPageMargin ) );

    wxBoxSizer* borderBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    pageBoxVSizer->Add( borderBoxSizer, 0, wxGROW | wxALL, 0 );

    m_borderFilename = SetupLabelText( pageBox, borderBoxSizer, lastID,
        _( "Border Filename" ), true, wxCommandEventHandler( AlbumDetailsPanel::OnBorderFilename ) );
    m_borderSize = SetupLabelText( pageBox, borderBoxSizer, lastID,
        _( "Border Size" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnBorderSize ) );

    wxArrayString m_orientationChoiceStrings( 2, Design::OrientationStrings );
    m_orientationChoice = SetupChoice( pageBox, pageBoxVSizer, ++lastID,
        _( "Orientation:" ), m_orientationChoiceStrings, wxCommandEventHandler( AlbumDetailsPanel::OnOrientationChoice ) );
    m_orientationChoice->SetSelection( Design::AT_Portrait );
    return pageDetailsPanel;
}


wxPanel* AlbumDetailsPanel::SetupRowColDetailsPanel( wxWindow* parent, int& lastID )
{

    wxPanel* rowColDetailsPanel = new wxPanel( parent, ++lastID, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    rowColDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* rowColVerticalSizer = new wxBoxSizer( wxVERTICAL );
    rowColDetailsPanel->SetSizer( rowColVerticalSizer );
    return rowColDetailsPanel;

}


wxPanel* AlbumDetailsPanel::SetupStampDetailsPanel( wxWindow* parent, int& lastID )
{

    wxPanel* stampDetailsPanel = new wxPanel( parent, ++lastID, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    stampDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* stampHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    stampDetailsPanel->SetSizer( stampHorizontalSizer );

    wxBoxSizer* stampLeftVerticalSizer = new wxBoxSizer( wxVERTICAL );
    stampHorizontalSizer->Add( stampLeftVerticalSizer, 0, wxGROW | wxALL, 0 );

    wxBoxSizer* stampRightVerticalSizer = new wxBoxSizer( wxVERTICAL );
    stampHorizontalSizer->Add( stampRightVerticalSizer, 0, wxGROW | wxALL, 0 );




    SetupFontPicker( stampDetailsPanel, stampLeftVerticalSizer, lastID,
        _( "Default Catalog Nbr Font" ), _( "Default" ),
        m_nbrFontPicker, m_nbrColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnNbrFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnNbrColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnNbrDefaultClick ) );


    SetupFontPicker( stampDetailsPanel, stampLeftVerticalSizer, lastID,
        _( "Default Name Font" ), _( "Default" ),
        m_nameFontPicker, m_nameColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnNameFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnNameColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnNameDefaultClick ) );

    wxBoxSizer* sizer = new wxBoxSizer( wxHORIZONTAL );
    stampRightVerticalSizer->Add( sizer, 0, wxGROW | wxALL, 0 );

    m_nbrCheckbox = SetupCheckBox( stampDetailsPanel, sizer, ++lastID,
        _( "Show Catalog Nbr" ), wxCommandEventHandler( AlbumDetailsPanel::OnBorderSize ) );
    m_grayScaleImagesCheckbox = SetupCheckBox( stampDetailsPanel, sizer, ++lastID,
        _( "Show Grayscale Images" ), wxCommandEventHandler( AlbumDetailsPanel::OnBorderSize ) );

    m_catalog = SetupLabelText( stampDetailsPanel, stampRightVerticalSizer, lastID,
        _( "Catalog Code" ), true, wxCommandEventHandler( AlbumDetailsPanel::OnCatalogCode ) );



    m_stampNameLocationBox = new wxStaticBox( stampDetailsPanel, wxID_ANY, _( "Name Location" ) );
    m_stampNameLocationVSizer = new wxStaticBoxSizer( m_stampNameLocationBox, wxVERTICAL );
    stampRightVerticalSizer->Add( m_stampNameLocationVSizer, 0, wxGROW | wxALL, 5 );

    m_stampNameLocationHSizer = new wxBoxSizer( wxHORIZONTAL );
    m_stampNameLocationVSizer->Add( m_stampNameLocationHSizer, 0, wxGROW | wxALL, 0 );

    m_topButton = new wxRadioButton( m_stampNameLocationVSizer->GetStaticBox( ), ++lastID,
        _( "Top" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_topButton->SetValue( true );
    m_stampNameLocationHSizer->Add( m_topButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( m_topButton->GetId( ), wxEVT_RADIOBUTTON, wxCommandEventHandler( AlbumDetailsPanel::OnNameLocationButtonSelected ) );

    m_bottomButton = new wxRadioButton( m_stampNameLocationVSizer->GetStaticBox( ), ++lastID,
        _( "Bottom" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_bottomButton->SetValue( false );
    m_stampNameLocationHSizer->Add( m_bottomButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( m_bottomButton->GetId( ), wxEVT_RADIOBUTTON, wxCommandEventHandler( AlbumDetailsPanel::OnNameLocationButtonSelected ) );

    return stampDetailsPanel;
}

void AlbumDetailsPanel::CreateControls( )
{
    theDialog = this;

    int lastID = ID_ALBUMDETAILSDIALOG + 1;


    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 1, wxGROW | wxALL, 5 );

    wxNotebook* notebook = new wxNotebook( theDialog, ++lastID, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
    notebookHorizontalSizer->Add( notebook, 1, wxGROW | wxALL, 5 );

    wxPanel* albumDetailsPanel = SetupAlbumDetailsPanel( notebook, lastID );
    notebook->AddPage( albumDetailsPanel, _( "Album" ) );

    wxPanel* pageDetailsPanel = AlbumDetailsPanel::SetupPageDetailsPanel( notebook, lastID );
    notebook->AddPage( pageDetailsPanel, _( "Page" ) );

    wxPanel* rowColDetailsPanel = SetupRowColDetailsPanel( notebook, lastID );
    notebook->AddPage( rowColDetailsPanel, _( "Row/Col" ) );

    wxPanel* stampDetailsPanel = SetupStampDetailsPanel( notebook, lastID );
    notebook->AddPage( stampDetailsPanel, _( "Stamp" ) );

    m_name->SetToolTip( "Name of Album" );
    m_paperHeight->SetToolTip( "Height of paper in printer (in mm)" );
}


//--------------

wxString AlbumDetailsPanel::GetBorderSize( ) {
    return m_borderSize->GetValue( );
}

// --------------

wxString AlbumDetailsPanel::GetBorderFilename( ) {
    return m_borderFilename->GetValue( );
}

wxString AlbumDetailsPanel::GetCatalog( ) {
    return m_catalog->GetValue( );
};

//--------------

wxFont AlbumDetailsPanel::GetNameFont( ) {
    return m_nameFontPicker->GetSelectedFont( );
}

//--------------

wxString AlbumDetailsPanel::GetBottomPageMargin( ) {
    return m_bottomPageMargin->GetValue( );
}

//--------------

wxString AlbumDetailsPanel::GetLeftPageMargin( ) {
    return m_leftPageMargin->GetValue( );
}

//--------------

wxString AlbumDetailsPanel::GetName( ) {
    return m_name->GetValue( );
}

//--------------

wxFont AlbumDetailsPanel::GetNbrFont( ) {
    return m_nbrFontPicker->GetSelectedFont( );
}

//--------------

wxColour AlbumDetailsPanel::GetNbrColor( ) {
    return m_nbrColorPicker->GetColour( );
}

//--------------

wxColour AlbumDetailsPanel::GetNameColor( ) {
    return m_nbrColorPicker->GetColour( );
}

bool AlbumDetailsPanel::GetOverSizePaper( ) {
    return m_overSizeCheckbox->IsChecked( );
}

//--------------

wxString AlbumDetailsPanel::GetPageHeight( ) {
    return m_pageHeight->GetValue( );
}

//--------------

wxString AlbumDetailsPanel::GetPageWidth( ) {
    return m_pageWidth->GetValue( );
}

//--------------

wxString AlbumDetailsPanel::GetPaperHeight( ) {
    return m_paperHeight->GetValue( );
}

//--------------

wxString AlbumDetailsPanel::GetPaperWidth( ) {
    return m_paperWidth->GetValue( );
}

//--------------

wxString AlbumDetailsPanel::GetRightPageMargin( ) {
    return m_rightPageMargin->GetValue( );
}

//--------------

bool AlbumDetailsPanel::GetShowNbr( ) {
    return m_nbrCheckbox->IsChecked( );
}

wxFont AlbumDetailsPanel::GetSubTitleFont( ) {
    return m_subTitleFontPicker->GetSelectedFont( );
}

wxColour AlbumDetailsPanel::GetSubTitleColor( ) {
    return m_subTitleColorPicker->GetColour( );
}

//--------------

bool AlbumDetailsPanel::GetShowStampTitle( ) {
    return m_stampTitleCheckbox->GetValue( );
}

bool AlbumDetailsPanel::GetShowStampSubTitle( ) {
    return m_stampSubTitleCheckbox->GetValue( );
}

//--------------

wxColour AlbumDetailsPanel::GetTextColor( ) {
    return m_textColorPicker->GetColour( );
}

//--------------

wxFont AlbumDetailsPanel::GetTextFont( ) {
    return m_textFontPicker->GetSelectedFont( );
}

//--------------

wxFont AlbumDetailsPanel::GetTitleFont( ) {
    return m_titleFontPicker->GetSelectedFont( );
}


//--------------

wxColour AlbumDetailsPanel::GetTitleColor( ) {
    return m_titleColorPicker->GetColour( );
}

//--------------

wxString AlbumDetailsPanel::GetTopPageMargin( ) {
    return m_topPageMargin->GetValue( );
}
//--------------

void AlbumDetailsPanel::Init( )
{
    m_name = NULL;
    m_pageHeight = NULL;
    m_pageWidth = NULL;
    m_topPageMargin = NULL;
    m_bottomPageMargin = NULL;
    m_rightPageMargin = NULL;
    m_leftPageMargin = NULL;
    m_borderSize = NULL;
    m_validate = NULL;
    m_statusList = NULL;
}


//--------------

//--------------

void AlbumDetailsPanel::SetName( wxString name )
{
    m_name->ChangeValue( name );
}

//--------------

void AlbumDetailsPanel::SetPageHeight( wxString height )
{
    m_pageHeight->ChangeValue( height );
}

//--------------

void AlbumDetailsPanel::SetPageWidth( wxString width )
{
    m_pageWidth->ChangeValue( width );
}
//--------------

void AlbumDetailsPanel::SetPaperHeight( wxString height )
{
    m_paperHeight->ChangeValue( height );
}

//--------------

void AlbumDetailsPanel::SetPaperWidth( wxString width )
{
    m_paperWidth->ChangeValue( width );
}

//--------------

void AlbumDetailsPanel::SetTopPageMargin( wxString topPageMargin )
{
    m_topPageMargin->ChangeValue( topPageMargin );
}

//--------------

void AlbumDetailsPanel::SetBottomPageMargin( wxString bottomPageMargin )
{
    m_bottomPageMargin->ChangeValue( bottomPageMargin );
}

//--------------

void AlbumDetailsPanel::SetLeftPageMargin( wxString leftPageMargin )
{
    m_leftPageMargin->ChangeValue( leftPageMargin );
}

//--------------

void AlbumDetailsPanel::SetRightPageMargin( wxString rightPageMargin )
{
    m_rightPageMargin->ChangeValue( rightPageMargin );
}

//--------------

void AlbumDetailsPanel::SetBorderSize( wxString borderSize )
{
    m_borderSize->ChangeValue( borderSize );
}

void AlbumDetailsPanel::SetBorderFilename( wxString filename )
{
    m_borderFilename->ChangeValue( filename );
}
void AlbumDetailsPanel::SetCatalog( wxString catCode )
{
    m_catalog->ChangeValue( catCode );
}

//--------------

void AlbumDetailsPanel::SetupDialog( Design::Album* album )
{
    m_album = album;
    UpdateControls( );

    wxArrayString* errors = m_album->GetErrorArray( );
    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }
};


//--------------

void AlbumDetailsPanel::SetShowNbr( bool state ) {
    m_nbrCheckbox->SetValue( state );
}

void AlbumDetailsPanel::SetOverSizePaper( bool state ) {
    m_overSizeCheckbox->SetValue( state );
}

//--------------

void AlbumDetailsPanel::SetShowStampTitle( bool state ) {
    m_stampTitleCheckbox->SetValue( state );
}

//--------------

void AlbumDetailsPanel::SetNbrFont( wxFont font ) {
    m_nbrFontPicker->SetSelectedFont( font );
}

//--------------

void AlbumDetailsPanel::SetNameFont( wxFont font ) {
    m_nameFontPicker->SetSelectedFont( font );
}

//--------------

void AlbumDetailsPanel::SetTextFont( wxFont font ) {
    m_textFontPicker->SetSelectedFont( font );
}

//--------------

void AlbumDetailsPanel::SetTitleFont( wxFont font ) {
    m_titleFontPicker->SetSelectedFont( font );
}

void AlbumDetailsPanel::SetSubTitleFont( wxFont font ) {
    m_subTitleFontPicker->SetSelectedFont( font );
}

//--------------

void AlbumDetailsPanel::SetNbrColor( wxColour color ) {
    m_nbrColorPicker->SetColour( color );
}

//--------------

void AlbumDetailsPanel::SetNameColor( wxColour color ) {
    m_nbrColorPicker->SetColour( color );
}

//--------------

void AlbumDetailsPanel::SetTextColor( wxColour color ) {
    m_textColorPicker->SetColour( color );
}

//--------------

void AlbumDetailsPanel::SetTitleColor( wxColour color ) {
    m_titleColorPicker->SetColour( color );
}

void AlbumDetailsPanel::SetSubTitleColor( wxColour color ) {
    m_subTitleColorPicker->SetColour( color );
}

//--------------

void AlbumDetailsPanel::SetGrayScaleImages( bool val ) {
    m_grayScaleImagesCheckbox->SetValue( val );
};

//--------------

bool AlbumDetailsPanel::GetGrayScaleImages( ) {
    return m_grayScaleImagesCheckbox->GetValue( );
}

//--------------

bool AlbumDetailsPanel::ShowToolTips( )
{
    return true;
}

//--------------

void AlbumDetailsPanel::OnNbrDefaultClick( wxCommandEvent& event )
{

    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NbrFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nbrFontPicker->SetSelectedFont( font );
    m_nbrColorPicker->SetColour( color );
    m_album->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );

    event.Skip( );
}

//--------------

void AlbumDetailsPanel::OnNameDefaultClick( wxCommandEvent& event )
{

    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_NameFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_nameFontPicker->SetSelectedFont( font );
    m_nameColorPicker->SetColour( color );
    m_album->SetFont( Design::AT_NameFontType, GetNameFont( ), GetNameColor( ) );

    event.Skip( );
}

//--------------

//--------------

void AlbumDetailsPanel::OnSubTitleFontPicker( wxFontPickerEvent& event )
{
    m_album->SetFont( Design::AT_SubTitleFontType, GetSubTitleFont( ), GetSubTitleColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnSubTitleColorPicker( wxColourPickerEvent& event )
{
    m_album->SetFont( Design::AT_SubTitleFontType, GetSubTitleFont( ), GetSubTitleColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    m_album->SetFont( Design::AT_SubTitleFontType, GetSubTitleFont( ), GetSubTitleColor( ) );

    event.Skip( );

}
void AlbumDetailsPanel::OnTitleFontPicker( wxFontPickerEvent& event )
{
    m_album->SetFont( Design::AT_TitleFontType, GetTitleFont( ), GetTitleColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnTitleColorPicker( wxColourPickerEvent& event )
{
    m_album->SetFont( Design::AT_TitleFontType, GetTitleFont( ), GetTitleColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    m_album->SetFont( Design::AT_TitleFontType, GetTitleFont( ), GetTitleColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnTextFontPicker( wxFontPickerEvent& event )
{
    m_album->SetFont( Design::AT_TextFontType, GetTextFont( ), GetTextColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnTextColorPicker( wxColourPickerEvent& event )
{
    m_album->SetFont( Design::AT_TextFontType, GetTextFont( ), GetTextColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnTextDefaultClick( wxCommandEvent& event )
{
    int ndx = GetSettings( )->GetFontNdxPreference( Design::AT_TextFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_textFontPicker->SetSelectedFont( font );
    m_textColorPicker->SetColour( color );
    m_album->SetFont( Design::AT_TextFontType, GetTextFont( ), GetTextColor( ) );
    event.Skip( );
}


//--------------
void AlbumDetailsPanel::OnNameClick( wxCommandEvent& event )
{
    wxString docName = m_album->GetDocName( );
    wxString name = m_name->GetValue( );
    if ( docName.Cmp( name ) )
    {
        m_album->SetDocName( name );
    }
    event.Skip( );

}

void AlbumDetailsPanel::OnOverSizeCheckBoxClick( wxCommandEvent& event )
{
    if ( m_overSizeCheckbox->IsChecked( ) != m_album->GetOverSizePaper( ) )
    {
        m_album->SetOverSizePaper( m_overSizeCheckbox->IsChecked( ) );
    }
    event.Skip( );

}

//--------------
void AlbumDetailsPanel::OnPaperHeight( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
    event.Skip( );

}

void AlbumDetailsPanel::OnNbrFontPicker( wxFontPickerEvent& event )
{
    m_album->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnNbrColorPicker( wxColourPickerEvent& event )
{
    m_album->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );
    event.Skip( );
}

void AlbumDetailsPanel::OnNameFontPicker( wxFontPickerEvent& event )
{
    m_album->SetFont( Design::AT_NameFontType, GetNameFont( ), GetNameColor( ) );
    event.Skip( );

}

void AlbumDetailsPanel::OnNameColorPicker( wxColourPickerEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnPaperWidth( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnPageHeight( wxCommandEvent& event )
{

    double valAlbum = m_album->GetPageHeight( );
    double valLocal = 0;
    wxString valLocalStr = m_pageWidth->GetValue( );
    valLocalStr.ToDouble( &valLocal );
    if ( valAlbum != valLocal )
    {
        m_album->SetPageHeight( valLocalStr );
    }
}

void AlbumDetailsPanel::OnPageWidth( wxCommandEvent& event )
{
    double valAlbum = m_album->GetWidth( );
    double valLocal = 0;
    wxString valLocalStr = m_pageWidth->GetValue( );
    valLocalStr.ToDouble( &valLocal );

    if ( valAlbum != valLocal )
    {
        m_album->SetPageWidth( valLocalStr );
    }
}

void AlbumDetailsPanel::OnTopPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnBottomPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnLeftPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnRightPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnBorderFilename( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnBorderSize( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPaperHeightStr( );
    wxString valLocal = m_paperHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperHeight( valLocal );
    }
}
void AlbumDetailsPanel::OnCatalogCode( wxCommandEvent& event )
{
    wxString cat = m_catalog->GetValue( );
    m_album->SetCatalog( cat );
}
void AlbumDetailsPanel::OnOrientationChoice( wxCommandEvent& event )
{
    m_album->SetDefaultOrientation( Design::OrientationStrings[ m_orientationChoice->GetSelection( ) ] );
}

void AlbumDetailsPanel::OnNameLocationButtonSelected( wxCommandEvent& event )
{
    bool top;
    Design::TitleLocation currLoc = m_album->GetTitleLocationType( );
    Design::TitleLocation localLoc = Design::AT_TitleLocationBottom;
    if ( m_topButton->GetValue( ) )
    {
        localLoc = Design::AT_TitleLocationTop;
    }
    if ( currLoc != localLoc )
    {
        m_album->SetTitleLocationType( localLoc );
    }
}

// void AlbumDetailsPanel::OnOkClick( wxCommandEvent& event )
// {
//     m_album->SetAttrStr( Design::AT_Name, GetName( ) );
//     m_album->SetPaperHeight( GetPaperHeight( ) );
//     m_album->SetPaperWidth( GetPaperWidth( ) );
//     m_album->SetPageHeight( GetPageHeight( ) );
//     m_album->SetPageWidth( GetPageWidth( ) );
//     m_album->SetTopPageMargin( GetTopPageMargin( ) );
//     m_album->SetBottomPageMargin( GetBottomPageMargin( ) );
//     m_album->SetLeftPageMargin( GetLeftPageMargin( ) );
//     m_album->SetRightPageMargin( GetRightPageMargin( ) );
//     m_album->SetBorderSize( GetBorderSize( ) );

//     m_album->SetOverSizePaper( GetOverSizePaper( ) );
//     m_album->SetShowNbr( GetShowNbr( ) );
//     //m_album->SetShowTitle( GetShowStampTitle( ) );
//     //m_album->SetShowSubTitle( GetShowStampSubTitle( ) );
//     m_album->SetGrayScaleImages( GetGrayScaleImages( ) );
//     m_album->SetDefaultOrientation( GetOrientation( ) );
//     m_album->SetTitleLocationType( m_stampNameLocation );
//     m_album->SetCatalog( GetCatalog( ) );

//     m_album->SetBorderFilename( GetBorderFilename( ) );
//     wxFont newFont = GetNbrFont( );

//     m_album->SetFont( Design::AT_TextFontType, GetTextFont( ), GetTextColor( ) );
//     m_album->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );
//     m_album->SetFont( Design::AT_TitleFontType, GetTitleFont( ), GetTitleColor( ) );
//     m_album->SetFont( Design::AT_SubTitleFontType, GetSubTitleFont( ), GetSubTitleColor( ) );
//     m_album->SetFont( Design::AT_NameFontType, GetNameFont( ), GetNameColor( ) );


//     event.Skip( );
// }

void AlbumDetailsPanel::SetStampNameLocation( )
{
    Design::TitleLocation loc = m_album->GetTitleLocationType( );
    if ( loc == Design::AT_TitleLocationBottom )
    {
        m_stampNameLocation = Design::AT_TitleLocationBottom;
        m_bottomButton->SetValue( true );
    }
    else
    {
        m_stampNameLocation = Design::AT_TitleLocationTop;
        m_topButton->SetValue( true );
    }
}
//--------------

void AlbumDetailsPanel::UpdateControls( )
{
    SetOverSizePaper( m_album->GetOverSizePaper( ) );
    SetPaperHeight( m_album->GetPaperHeightStr( ) );
    SetPaperWidth( m_album->GetPaperWidthStr( ) );
    SetPageHeight( m_album->GetPageHeightStr( ) );
    SetPageWidth( m_album->GetPageWidthStr( ) );
    SetTopPageMargin( m_album->GetTopPageMarginStr( ) );
    SetBottomPageMargin( m_album->GetTopPageMarginStr( ) );
    SetLeftPageMargin( m_album->GetLeftPageMarginStr( ) );
    SetRightPageMargin( m_album->GetRightPageMarginStr( ) );
    SetBorderSize( m_album->GetBorderSizeStr( ) );
    SetShowNbr( m_album->GetShowNbr( ) );
    // SetShowStampTitle( m_album->GetShowTitle( ) );
    SetGrayScaleImages( m_album->GetGrayScaleImages( ) );
    SetBorderFilename( m_album->GetBorderFileName( ) );

    SetNbrFont( m_album->GetFont( Design::AT_NbrFontType ) );
    SetTextFont( m_album->GetFont( Design::AT_TextFontType ) );
    SetTitleFont( m_album->GetFont( Design::AT_TitleFontType ) );
    SetNameFont( m_album->GetFont( Design::AT_NameFontType ) );
    SetNbrColor( m_album->GetColor( Design::AT_NbrFontType ) );
    SetTextColor( m_album->GetColor( Design::AT_TextFontType ) );
    SetTitleColor( m_album->GetColor( Design::AT_TitleFontType ) );
    SetNameColor( m_album->GetColor( Design::AT_NameFontType ) );
    SetName( m_album->GetAttrStr( Design::AT_Name ) );
    SetStampNameLocation( );
    SetCatalog( m_album->GetCatalog( ) );


}

void AlbumDetailsPanel::OnOrientationchoiceSelected( wxCommandEvent& event )
{
    event.Skip( );
}



void AlbumDetailsPanel::OnTopRadioButtonSelected( wxCommandEvent& event )
{
    m_stampNameLocation = Design::AT_TitleLocationBottom;
    event.Skip( );
}


void AlbumDetailsPanel::OnBottomRadioButtonSelected( wxCommandEvent& event )
{
    m_stampNameLocation = Design::AT_TitleLocationBottom;
    event.Skip( );
}

