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
#include "wx/treectrl.h"
#include <wx/fontdlg.h>
#include <wx/fontdata.h>

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
    wxPanel* albumDetailsPanel = new wxPanel( parent, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    albumDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* albumVerticalSizer = new wxBoxSizer( wxVERTICAL );
    albumDetailsPanel->SetSizer( albumVerticalSizer );

    m_name = SetupLabelText( albumDetailsPanel, albumVerticalSizer, ++lastID,
        _( "Name" ), true, wxCommandEventHandler( AlbumDetailsPanel::OnNameClick ) );

    wxBoxSizer* itemBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    albumVerticalSizer->Add( itemBoxSizer, 1, wxGROW | wxALL, 5 );

    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( albumDetailsPanel, ++lastID,
        wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );

    itemBoxSizer->Add( m_statusList, 1, wxGROW | wxALL, 5 );
    return albumDetailsPanel;
}


wxPanel* AlbumDetailsPanel::SetupPageDetailsPanel( wxWindow* parent, int& lastID )
{

    //>>> pageDetails vvvvv
    wxPanel* pageDetailsPanel = new wxPanel( parent, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    pageDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    pageDetailsPanel->SetSizer( detailsHorizontalSizer );

    wxBoxSizer* leftColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsHorizontalSizer->Add( leftColumnVerticalSizer, 1, wxGROW | wxALL, 0 );

    //  wxBoxSizer* rightColumnVerticalSizer = new wxBoxSizer( wxVERTICAL );
    //  detailsHorizontalSizer->Add( rightColumnVerticalSizer, 1, wxGROW | wxALL, 0 );


    SetupFontPicker( pageDetailsPanel, leftColumnVerticalSizer, lastID,
        _( "Title Font" ), _( "Default" ),
        m_titleFontPicker, m_titleColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnTitleFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnTitleColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnTitleDefaultClick ) );

    SetupFontPicker( pageDetailsPanel, leftColumnVerticalSizer, lastID,
        _( "SubTitle Font" ), _( "Default" ),
        m_subTitleFontPicker, m_subTitleColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnSubTitleFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnSubTitleColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnSubTitleDefaultClick ) );

    SetupFontPicker( pageDetailsPanel, leftColumnVerticalSizer, lastID,
        _( "Text Font" ), _( "Default" ),
        m_textFontPicker, m_textColorPicker,
        wxFontPickerEventHandler( AlbumDetailsPanel::OnTextFontPicker ),
        wxColourPickerEventHandler( AlbumDetailsPanel::OnTextColorPicker ),
        wxCommandEventHandler( AlbumDetailsPanel::OnTextDefaultClick ) );



    wxBoxSizer* oversizePaperSizer;
    wxStaticBox* oversizePaperBox = SetupBoxSizer( pageDetailsPanel, leftColumnVerticalSizer,
        "OverSize Paper", lastID, oversizePaperSizer, wxVERTICAL );

    m_overSizeCheckbox = SetupCheckBox( oversizePaperBox, oversizePaperSizer, ++lastID,
        _( "Oversize Paper" ), wxCommandEventHandler( AlbumDetailsPanel::OnOverSizeCheckBoxClick ) );

    wxBoxSizer* paperSizeBoxSizer = new wxBoxSizer( wxHORIZONTAL );

    oversizePaperSizer->Add( paperSizeBoxSizer, 0, wxGROW | wxALL, 0 );

    //paperSizeBoxSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    HorizontalSpacer( paperSizeBoxSizer );

    m_paperHeight = SetupLabelText( oversizePaperBox, paperSizeBoxSizer, lastID,
        _( "Height" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPaperHeight ) );

    paperSizeBoxSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_paperWidth = SetupLabelText( oversizePaperBox, paperSizeBoxSizer, lastID,
        _( "Width" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPaperWidth ) );


    wxBoxSizer* pageBoxVSizer;
    wxStaticBox* pageBox = SetupBoxSizer( pageDetailsPanel, leftColumnVerticalSizer,
        "Page Size", lastID, pageBoxVSizer, wxVERTICAL );


    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    pageBoxVSizer->Add( itemBoxSizer4, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer4 );

    m_pageHeight = SetupLabelText( pageBox, itemBoxSizer4, lastID,
        _( "Height" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPageHeight ) );
    m_pageHeight->SetToolTip( _( "Page layout height in mm." ) );

    HorizontalSpacer( itemBoxSizer4 );

    m_pageWidth = SetupLabelText( pageBox, itemBoxSizer4, lastID,
        _( "Width" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnPageWidth ) );
    m_pageWidth->SetToolTip( _( "Page layout width in mm." ) );




    wxBoxSizer* marginBoxVSizer;
    wxStaticBox* marginBox = SetupBoxSizer( pageDetailsPanel, leftColumnVerticalSizer,
        "Margin", lastID, marginBoxVSizer, wxVERTICAL );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer7, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer7 );

    m_topPageMargin = SetupLabelText( marginBox, itemBoxSizer7, lastID,
        _( "Top" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnTopPageMargin ) );
    m_topPageMargin->SetToolTip( _( "Page top margin in mm." ) );
    HorizontalSpacer( itemBoxSizer7 );

    m_bottomPageMargin = SetupLabelText( marginBox, itemBoxSizer7, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnBottomPageMargin ) );
    m_bottomPageMargin->SetToolTip( _( "Page bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer10, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer10 );

    m_leftPageMargin = SetupLabelText( marginBox, itemBoxSizer10, lastID,
        _( "Left" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnLeftPageMargin ) );
    m_leftPageMargin->SetToolTip( _( "Page left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer10 );

    m_rightPageMargin = SetupLabelText( marginBox, itemBoxSizer10, lastID,
        _( "Right" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnRightPageMargin ) );
    m_topPageMargin->SetToolTip( _( "Page right margin in mm." ) );


    wxBoxSizer* borderBoxSizer;
    wxStaticBox* borderBox = SetupBoxSizer( pageDetailsPanel, leftColumnVerticalSizer,
        "Border", lastID, borderBoxSizer, wxVERTICAL );

    m_borderFilename = SetupLabelText( borderBox, borderBoxSizer, lastID,
        _( "Filename" ), true, wxCommandEventHandler( AlbumDetailsPanel::OnBorderFilename ) );
    m_borderFilename->SetToolTip( _( "Filename of border image" ) );
    m_borderSize = SetupLabelText( borderBox, borderBoxSizer, lastID,
        _( "Size" ), false, wxCommandEventHandler( AlbumDetailsPanel::OnBorderSize ) );
    m_borderSize->SetToolTip( _( "width of the border to be added to the margin for layout in mm." ) );


    wxArrayString m_orientationChoiceStrings( 2, Design::OrientationStrings );
    m_orientationChoice = SetupChoice( pageDetailsPanel, leftColumnVerticalSizer, ++lastID,
        _( "Orientation:" ), m_orientationChoiceStrings,
        wxCommandEventHandler( AlbumDetailsPanel::OnOrientationChoice ) );
    m_orientationChoice->SetSelection( Design::AT_Portrait );
    return pageDetailsPanel;
}


wxPanel* AlbumDetailsPanel::SetupRowColDetailsPanel( wxWindow* parent, int& lastID )
{

    wxPanel* rowColDetailsPanel = new wxPanel( parent, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    rowColDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* rowColVerticalSizer = new wxBoxSizer( wxVERTICAL );
    rowColDetailsPanel->SetSizer( rowColVerticalSizer );


    wxBoxSizer* locationSizer;
    wxStaticBox* locationBox = SetupBoxSizer( rowColDetailsPanel, rowColVerticalSizer,
        "Name Location", lastID, locationSizer, wxHORIZONTAL );

    m_topButton = SetupRadioButton( locationBox, locationSizer, lastID, _( "Top" ), true,
        wxCommandEventHandler( AlbumDetailsPanel::OnNameLocationButtonSelected ) );
    m_topButton->SetToolTip( _( "Name above Stamp." ) );

    m_bottomButton = SetupRadioButton( locationBox, locationSizer, lastID, _( "Bottom" ), false,
        wxCommandEventHandler( AlbumDetailsPanel::OnNameLocationButtonSelected ) );
    m_bottomButton->SetToolTip( _( "Name below Stamp." ) );


    return rowColDetailsPanel;

}


wxPanel* AlbumDetailsPanel::SetupStampDetailsPanel( wxWindow* parent, int& lastID )
{

    wxPanel* stampDetailsPanel = new wxPanel( parent, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    stampDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* stampHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    stampDetailsPanel->SetSizer( stampHorizontalSizer );

    wxBoxSizer* stampLeftVerticalSizer = new wxBoxSizer( wxVERTICAL );
    stampHorizontalSizer->Add( stampLeftVerticalSizer, 1, wxGROW | wxALL, 0 );

    //  wxBoxSizer* stampRightVerticalSizer = new wxBoxSizer( wxVERTICAL );
    //  stampHorizontalSizer->Add( stampRightVerticalSizer, 0, wxGROW | wxALL, 0 );

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


    m_nbrCheckbox = SetupCheckBox( stampDetailsPanel, stampLeftVerticalSizer, ++lastID,
        _( "Show Catalog Nbr" ), wxCommandEventHandler( AlbumDetailsPanel::OnBorderSize ) );

    m_grayScaleImagesCheckbox = SetupCheckBox( stampDetailsPanel, stampLeftVerticalSizer, ++lastID,
        _( "Show Grayscale Images" ), wxCommandEventHandler( AlbumDetailsPanel::OnGrayscale ) );

    m_catalog = SetupLabelText( stampDetailsPanel, stampLeftVerticalSizer, lastID,
        _( "Catalog Code" ), true, wxCommandEventHandler( AlbumDetailsPanel::OnCatalogCode ) );



    wxBoxSizer* alignmentizer;
    wxStaticBox* alignmentBox = SetupBoxSizer( stampDetailsPanel, stampLeftVerticalSizer,
        "Default Member Alignment", lastID, alignmentizer, wxHORIZONTAL );

    m_alignTop = SetupRadioButton( alignmentBox, alignmentizer, lastID, _( "Top" ), true,
        wxCommandEventHandler( AlbumDetailsPanel::OnAlignmentButtonSelected ) );
    m_alignTop->SetToolTip( _( "Align Top of Stamps." ) );

    m_alignMiddle = SetupRadioButton( alignmentBox, alignmentizer, lastID, _( "Middle" ), false,
        wxCommandEventHandler( AlbumDetailsPanel::OnAlignmentButtonSelected ) );
    m_alignMiddle->SetToolTip( _( "Align middle of Stamps." ) );

    m_alignBottom = SetupRadioButton( alignmentBox, alignmentizer, lastID, _( "Bottom" ), false,
        wxCommandEventHandler( AlbumDetailsPanel::OnAlignmentButtonSelected ) );
    m_alignBottom->SetToolTip( _( "Align bottom of Stamps." ) );

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

    wxNotebook* notebook = new wxNotebook( theDialog, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
    notebookHorizontalSizer->Add( notebook, 1, wxGROW | wxALL, 5 );

    wxPanel* albumDetailsPanel = SetupAlbumDetailsPanel( notebook, lastID );
    notebook->AddPage( albumDetailsPanel, _( "Album" ) );

    wxPanel* pageDetailsPanel = SetupPageDetailsPanel( notebook, lastID );
    notebook->AddPage( pageDetailsPanel, _( "Page" ) );

    wxPanel* rowColDetailsPanel = SetupRowColDetailsPanel( notebook, lastID );
    notebook->AddPage( rowColDetailsPanel, _( "Row/Col" ) );

    wxPanel* stampDetailsPanel = SetupStampDetailsPanel( notebook, lastID );
    notebook->AddPage( stampDetailsPanel, _( "Stamp" ) );

    Layout( );

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

// //--------------
// void AlbumDetailsPanel::OnPaperHeight( wxCommandEvent& event )
// {
//     wxString valAlbum = m_album->GetPaperHeightStr( );
//     wxString valLocal = m_paperHeight->GetValue( );
//     if ( valAlbum.Cmp( valLocal ) )
//     {
//         m_album->SetPaperHeight( valLocal );
//     }
//     event.Skip( );

// }

void AlbumDetailsPanel::OnNbrFontPicker( wxFontPickerEvent& event )
{
    m_album->SetFont( Design::AT_NbrFontType, GetNbrFont( ), GetNbrColor( ) );
    event.Skip( );
}


void AlbumDetailsPanel::OnNameColorPicker( wxColourPickerEvent& event )

{
    m_album->SetFont( Design::AT_NameFontType, GetNameFont( ), GetNameColor( ) );
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

void AlbumDetailsPanel::OnPaperHeight( wxCommandEvent& event )
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
    wxString valAlbum = m_album->GetPaperWidthStr( );
    wxString valLocal = m_paperWidth->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPaperWidth( valLocal );
    }
}

void AlbumDetailsPanel::OnPageHeight( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPageHeightStr( );
    wxString valLocal = m_pageHeight->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPageHeight( valLocal );
    }
}

void AlbumDetailsPanel::OnPageWidth( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetPageWidthStr( );
    wxString valLocal = m_pageWidth->GetValue( );

    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetPageWidth( valLocal );
    }
}

void AlbumDetailsPanel::OnTopPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetTopPageMarginStr( );
    wxString valLocal = m_topPageMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetTopPageMargin( valLocal );
    }
}

void AlbumDetailsPanel::OnBottomPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetBottomPageMarginStr( );
    wxString valLocal = m_bottomPageMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetBottomPageMargin( valLocal );
    }
}

void AlbumDetailsPanel::OnLeftPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetLeftPageMarginStr( );
    wxString valLocal = m_leftPageMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetLeftPageMargin( valLocal );
    }
}

void AlbumDetailsPanel::OnRightPageMargin( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetRightPageMarginStr( );
    wxString valLocal = m_rightPageMargin->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetRightPageMargin( valLocal );
    }
}

void AlbumDetailsPanel::OnBorderFilename( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetBorderFileName( );
    wxString valLocal = m_borderFilename->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetBorderFilename( valLocal );
    }
}

void AlbumDetailsPanel::OnBorderSize( wxCommandEvent& event )
{
    wxString valAlbum = m_album->GetBorderSizeStr( );
    wxString valLocal = m_borderSize->GetValue( );
    if ( valAlbum.Cmp( valLocal ) )
    {
        m_album->SetBorderSize( valLocal );
    }
}
void AlbumDetailsPanel::OnCatalogCode( wxCommandEvent& event )
{
    wxString cat = m_catalog->GetValue( );
    m_album->SetCatalog( cat );
}
void AlbumDetailsPanel::OnGrayscale( wxCommandEvent& event )
{
    m_album->SetGrayScaleImages( m_grayScaleImagesCheckbox->GetValue( ) );
}

void AlbumDetailsPanel::OnShowNbr( wxCommandEvent& event )
{
    m_album->SetShowNbr( m_nbrCheckbox->GetValue( ) );
}

void AlbumDetailsPanel::OnOrientationChoice( wxCommandEvent& event )
{
    m_album->SetDefaultOrientation( Design::OrientationStrings[ m_orientationChoice->GetSelection( ) ] );
}

void AlbumDetailsPanel::OnAlignmentButtonSelected( wxCommandEvent& event )
{
    Design::AlignmentMode currLoc = m_album->GetAlignmentModeType( );
    Design::AlignmentMode localLoc = Design::AlignTop;
    if ( m_alignTop->GetValue( ) )
    {
        localLoc = Design::AlignTop;
    }
    else if ( m_alignBottom->GetValue( ) )
    {
        localLoc = Design::AlignBottom;
    }
    else if ( m_alignMiddle->GetValue( ) )
    {
        localLoc = Design::AlignMiddle;
    }
    else
    {
        localLoc = Design::AlignTop;
    }
    if ( currLoc != localLoc )
    {
        m_album->SetAlignmentModeType( localLoc );
    }
}


void AlbumDetailsPanel::OnNameLocationButtonSelected( wxCommandEvent& event )
{
    bool top;
    Design::StampNameLocation currLoc = m_album->GetDefaultStampNameLocationType( );
    Design::StampNameLocation localLoc = Design::AT_StampNameLocationBottom;
    if ( m_topButton->GetValue( ) )
    {
        localLoc = Design::AT_StampNameLocationTop;
    }
    if ( currLoc != localLoc )
    {
        m_album->SetDefaultStampNameLocationType( localLoc );
    }
}



void AlbumDetailsPanel::SetStampNameLocation( )
{
    Design::StampNameLocation loc = m_album->GetDefaultStampNameLocationType( );
    if ( loc == Design::AT_StampNameLocationBottom )
    {
        m_stampNameLocation = Design::AT_StampNameLocationBottom;
        m_bottomButton->SetValue( true );
    }
    else
    {
        m_stampNameLocation = Design::AT_StampNameLocationTop;
        m_topButton->SetValue( true );
    }
}

void AlbumDetailsPanel::SetAlignmentMode( )
{
    Design::AlignmentMode loc = m_album->GetAlignmentModeType( );
    if ( loc == Design::AlignBottom )
    {
        m_alignmentMode = loc;
        m_alignBottom->SetValue( true );
    }
    else   if ( loc == Design::AlignMiddle )
    {
        m_alignmentMode = loc;
        m_alignBottom->SetValue( true );
    }
    else
    {
        m_alignmentMode = Design::AlignTop;
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
    SetAlignmentMode( );
    SetCatalog( m_album->GetCatalog( ) );


}

void AlbumDetailsPanel::OnOrientationchoiceSelected( wxCommandEvent& event )
{
    event.Skip( );
}



// void AlbumDetailsPanel::OnTopRadioButtonSelected( wxCommandEvent& event )
// {
//     m_stampNameLocation = Design::AT_StampNameLocationBottom;
//     event.Skip( );
// }


// void AlbumDetailsPanel::OnBottomRadioButtonSelected( wxCommandEvent& event )
// {
//     m_stampNameLocation = Design::AT_StampNameLocationBottom;
//     event.Skip( );
// }

