/*
 * @file  PageDefaultsPanel.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright ( c ) 2022
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

#include "wx/imaglist.h"
#include <wx/arrstr.h>

#include "wx/notebook.h"

#include "gui/PageDefaultsPanel.h"
#include "gui/PageDefaultsPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "design/TitleFrame.h"
#include "design/Page.h"
#include "design/Album.h"
#include "design/DesignDefs.h"
#include "utils/FontList.h"
#include "utils/Settings.h"
#include "Defs.h"

IMPLEMENT_DYNAMIC_CLASS( PageDefaultsPanel, HelperPanel )

//--------------

PageDefaultsPanel::PageDefaultsPanel( )
{
    Init( );
}

//--------------

PageDefaultsPanel::PageDefaultsPanel( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
    // SetMinClientSize( wxSize( 100, 100 ) );
}

//--------------

bool PageDefaultsPanel::Create( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

//--------------

PageDefaultsPanel::~PageDefaultsPanel( )
{

}

//--------------

void PageDefaultsPanel::Init( )
{
}

//--------------

void PageDefaultsPanel::CreateControls( )
{
    PageDefaultsPanel* thePanel = this;
    int lastID = ID_LastID;

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    thePanel->SetSizer( detailsHorizontalSizer );

    wxNotebook* focusNotebook = new wxNotebook( thePanel, ++lastID,
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




    wxBoxSizer* oversizePaperSizer;
    wxStaticBox* oversizePaperBox = SetupBoxSizer( advancedPanel, leftAdvancedVerticalSizer,
        "OverSize Paper", lastID, oversizePaperSizer, wxVERTICAL );

    m_overSizeCheckbox = SetupCheckBox( oversizePaperBox, oversizePaperSizer, ++lastID,
        _( "Oversize Paper" ), wxCommandEventHandler( PageDefaultsPanel::OnOverSizeCheckBoxClick ) );


    wxBoxSizer* paperSizeBoxSizer = new wxBoxSizer( wxHORIZONTAL );

    oversizePaperSizer->Add( paperSizeBoxSizer, 0, wxGROW | wxALL, 0 );

    //paperSizeBoxSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    VerticalSpacer( oversizePaperSizer );

    m_paperHeight = SetupLabelText( oversizePaperBox, paperSizeBoxSizer, lastID,
        _( "Height" ), false, wxCommandEventHandler( PageDefaultsPanel::OnPaperHeight ) );

    paperSizeBoxSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_paperWidth = SetupLabelText( oversizePaperBox, paperSizeBoxSizer, lastID,
        _( "Width" ), false, wxCommandEventHandler( PageDefaultsPanel::OnPaperWidth ) );


    wxBoxSizer* pageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    middleCommonVerticalSizer->Add( pageHorizontalSizer, 0, wxGROW | wxALL, 0 );


    wxBoxSizer* pageBoxVSizer;
    wxStaticBox* pageBox = SetupBoxSizer( commonPanel, pageHorizontalSizer,
        "Page Size", lastID, pageBoxVSizer, wxVERTICAL );


    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    pageBoxVSizer->Add( itemBoxSizer4, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer4 );

    m_pageHeight = SetupLabelText( pageBox, itemBoxSizer4, lastID,
        _( "Height" ), false, wxCommandEventHandler( PageDefaultsPanel::OnPageHeight ) );
    m_pageHeight->SetToolTip( _( "Page layout height in mm." ) );

    HorizontalSpacer( itemBoxSizer4 );

    m_pageWidth = SetupLabelText( pageBox, itemBoxSizer4, lastID,
        _( "Width" ), false, wxCommandEventHandler( PageDefaultsPanel::OnPageWidth ) );
    m_pageWidth->SetToolTip( _( "Page layout width in mm." ) );

    wxBoxSizer* marginBoxVSizer;
    wxStaticBox* marginBox = SetupBoxSizer( commonPanel, pageHorizontalSizer,
        "Page Margin", lastID, marginBoxVSizer, wxVERTICAL );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer7, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer7 );

    m_topPageMargin = SetupLabelText( marginBox, itemBoxSizer7, lastID,
        _( "Top" ), false, wxCommandEventHandler( PageDefaultsPanel::OnTopPageMargin ) );
    m_topPageMargin->SetToolTip( _( "Page top margin in mm." ) );
    HorizontalSpacer( itemBoxSizer7 );

    m_bottomPageMargin = SetupLabelText( marginBox, itemBoxSizer7, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( PageDefaultsPanel::OnBottomPageMargin ) );
    m_bottomPageMargin->SetToolTip( _( "Page bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    marginBoxVSizer->Add( itemBoxSizer10, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer10 );

    m_leftPageMargin = SetupLabelText( marginBox, itemBoxSizer10, lastID,
        _( "Left" ), false, wxCommandEventHandler( PageDefaultsPanel::OnLeftPageMargin ) );
    m_leftPageMargin->SetToolTip( _( "Page left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer10 );

    m_rightPageMargin = SetupLabelText( marginBox, itemBoxSizer10, lastID,
        _( "Right" ), false, wxCommandEventHandler( PageDefaultsPanel::OnRightPageMargin ) );
    m_rightPageMargin->SetToolTip( _( "Page right margin in mm." ) );

    wxArrayString m_orientationChoiceStrings( 2, Design::OrientationStrings );
    m_orientationChoice = SetupChoice( commonPanel, leftCommonVerticalSizer, ++lastID,
        _( "Orientation:" ), m_orientationChoiceStrings,
        wxCommandEventHandler( PageDefaultsPanel::OnOrientationChoice ) );
    m_orientationChoice->SetSelection( Design::AT_Portrait );


    wxBoxSizer* borderBoxSizer;
    wxStaticBox* borderBox = SetupBoxSizer( commonPanel, rightCommonVerticalSizer,
        "Border", lastID, borderBoxSizer, wxVERTICAL );

    m_borderFilename = SetupLabelText( borderBox, borderBoxSizer, lastID,
        _( "Filename" ), true, wxCommandEventHandler( PageDefaultsPanel::OnBorderFilename ) );
    m_borderFilename->SetToolTip( _( "Filename of border image" ) );

    wxBoxSizer* itemBorderBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    borderBoxSizer->Add( itemBorderBoxSizer, 0, wxGROW | wxALL, 0 );

    m_borderSize = SetupLabelText( borderBox, itemBorderBoxSizer, lastID,
        _( "Size" ), false, wxCommandEventHandler( PageDefaultsPanel::OnBorderSize ) );
    m_borderSize->SetToolTip( _( "width of the border to be added to the margin for layout in mm." ) );

    m_showBorder = SetupCheckBox( borderBox, itemBorderBoxSizer, ++lastID,
        _( "Show Border" ), wxCommandEventHandler( PageDefaultsPanel::OnShowBorderCheckBoxClick ) );
    m_showBorder->SetToolTip( _( "Show the page border." ) );

    m_titleHelper = SetupTitleHelper( commonPanel, leftCommonVerticalSizer, lastID, HasSubTitle,
        wxCommandEventHandler( PageDefaultsPanel::OnTitleCheckboxClick ),
        wxCommandEventHandler( PageDefaultsPanel::OnSubTitleCheckboxClick ),
        wxCommandEventHandler( PageDefaultsPanel::OnSubTitleCheckboxClick ) );

    wxBoxSizer* contenrMarginBoxVSizer;
    wxStaticBox* contenrMarginBox = SetupBoxSizer( advancedPanel, rightAdvancedVerticalSizer,
        "Content Margin", lastID, contenrMarginBoxVSizer, wxVERTICAL );

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer( wxHORIZONTAL );
    contenrMarginBoxVSizer->Add( itemBoxSizer17, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer17 );

    m_topContentMargin = SetupLabelText( contenrMarginBox, itemBoxSizer17, lastID,
        _( "Top" ), false, wxCommandEventHandler( PageDefaultsPanel::OnTopContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content top margin in mm." ) );
    HorizontalSpacer( itemBoxSizer17 );

    m_bottomContentMargin = SetupLabelText( contenrMarginBox, itemBoxSizer17, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( PageDefaultsPanel::OnBottomContentMargin ) );
    m_bottomContentMargin->SetToolTip( _( "Content bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer110 = new wxBoxSizer( wxHORIZONTAL );
    contenrMarginBoxVSizer->Add( itemBoxSizer110, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer110 );

    m_leftContentMargin = SetupLabelText( contenrMarginBox, itemBoxSizer110, lastID,
        _( "Left" ), false, wxCommandEventHandler( PageDefaultsPanel::OnLeftContentMargin ) );
    m_leftContentMargin->SetToolTip( _( "Content left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer110 );

    m_rightContentMargin = SetupLabelText( contenrMarginBox, itemBoxSizer110, lastID,
        _( "Right" ), false, wxCommandEventHandler( PageDefaultsPanel::OnRightContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content right margin in mm." ) );
}

//--------------

wxString PageDefaultsPanel::GetBorderSize( ) {
    return m_borderSize->GetValue( );
}

// --------------

wxString PageDefaultsPanel::GetBorderFilename( ) {
    return m_borderFilename->GetValue( );
}

//--------------

wxString PageDefaultsPanel::GetBottomPageMargin( ) {
    return m_bottomPageMargin->GetValue( );
}

//--------------

wxString PageDefaultsPanel::GetLeftPageMargin( ) {
    return m_leftPageMargin->GetValue( );
}

//--------------

bool PageDefaultsPanel::GetOverSizePaper( ) {
    return m_overSizeCheckbox->IsChecked( );
}

//--------------

wxString PageDefaultsPanel::GetPageHeight( ) {
    return m_pageHeight->GetValue( );
}

//--------------

wxString PageDefaultsPanel::GetPageWidth( ) {
    return m_pageWidth->GetValue( );
}

//--------------

wxString PageDefaultsPanel::GetPaperHeight( ) {
    return m_paperHeight->GetValue( );
}

//--------------

wxString PageDefaultsPanel::GetPaperWidth( ) {
    return m_paperWidth->GetValue( );
}

//--------------

wxString PageDefaultsPanel::GetRightPageMargin( ) {
    return m_rightPageMargin->GetValue( );
}

//--------------

wxString PageDefaultsPanel::GetTopPageMargin( ) {
    return m_topPageMargin->GetValue( );
}
//--------------

void PageDefaultsPanel::UpdateControls( )
{

    SetOrientation( Design::AlbumPageDefaults( )->Orientation( ) );
    m_titleHelper->subTitleCheckbox->SetValue( Design::AlbumPageDefaults( )->ShowSubTitle( ) );
    m_titleHelper->titleCheckbox->SetValue( Design::AlbumPageDefaults( )->ShowTitle( ) );

    SetTopPageMargin( Design::AlbumPageDefaults( )->TopMarginStr( ) );
    SetBottomPageMargin( Design::AlbumPageDefaults( )->BottomMarginStr( ) );
    SetLeftPageMargin( Design::AlbumPageDefaults( )->LeftMarginStr( ) );
    SetRightPageMargin( Design::AlbumPageDefaults( )->RightMarginStr( ) );

    SetPaperHeight( Design::AlbumPageDefaults( )->PaperHeightStr( ) );
    SetPaperWidth( Design::AlbumPageDefaults( )->PaperWidthStr( ) );
    SetPageHeight( Design::AlbumPageDefaults( )->PageHeightStr( ) );
    SetPageWidth( Design::AlbumPageDefaults( )->PageWidthStr( ) );

    SetTopContentMargin( Design::AlbumPageDefaults( )->TopContentMarginStr( ) );
    SetBottomContentMargin( Design::AlbumPageDefaults( )->BottomContentMarginStr( ) );
    SetLeftContentMargin( Design::AlbumPageDefaults( )->LeftContentMarginStr( ) );
    SetRightContentMargin( Design::AlbumPageDefaults( )->RightContentMarginStr( ) );

    SetOverSizePaper( Design::AlbumPageDefaults( )->OverSizePaper( ) );
    SetBorderSize( Design::AlbumPageDefaults( )->BorderSizeStr( ) );
    SetBorderFilename( Design::AlbumPageDefaults( )->BorderFilename( ) );
}

//--------------

void PageDefaultsPanel::SetupDialog( Design::Page* page )
{
    UpdateControls( );
};

//--------------

bool PageDefaultsPanel::ShowToolTips( )
{
    return true;
}

//--------------


void PageDefaultsPanel::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->ShowSubTitle( m_titleHelper->subTitleCheckbox->GetValue( ) );
    UpdateSubTitleState( m_titleHelper );
};

//--------------

void PageDefaultsPanel::OnTitleCheckboxClick( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->ShowTitle( m_titleHelper->titleCheckbox->GetValue( ) );
    UpdateTitleState( m_titleHelper );
}

//--------------

void PageDefaultsPanel::SetPageHeight( wxString height )
{
    m_pageHeight->ChangeValue( height );
}

//--------------

void PageDefaultsPanel::SetPageWidth( wxString width )
{
    m_pageWidth->ChangeValue( width );
}

//--------------

void PageDefaultsPanel::SetPaperHeight( wxString height )
{
    m_paperHeight->ChangeValue( height );
}

//--------------

void PageDefaultsPanel::SetPaperWidth( wxString width )
{
    m_paperWidth->ChangeValue( width );
}

//--------------

void PageDefaultsPanel::SetTopPageMargin( wxString topPageMargin )
{
    m_topPageMargin->ChangeValue( topPageMargin );
}

//--------------

void PageDefaultsPanel::SetBottomPageMargin( wxString bottomPageMargin )
{
    m_bottomPageMargin->ChangeValue( bottomPageMargin );
}

//--------------

void PageDefaultsPanel::SetLeftPageMargin( wxString leftPageMargin )
{
    m_leftPageMargin->ChangeValue( leftPageMargin );
}

//--------------

void PageDefaultsPanel::SetRightPageMargin( wxString rightPageMargin )
{
    m_rightPageMargin->ChangeValue( rightPageMargin );
}




//--------------

void PageDefaultsPanel::SetTopContentMargin( wxString topContentMargin )
{
    m_topContentMargin->ChangeValue( topContentMargin );
}

//--------------

void PageDefaultsPanel::SetBottomContentMargin( wxString bottomContentMargin )
{
    m_bottomContentMargin->ChangeValue( bottomContentMargin );
}

//--------------

void PageDefaultsPanel::SetLeftContentMargin( wxString leftContentMargin )
{
    m_leftContentMargin->ChangeValue( leftContentMargin );
}

//--------------

void PageDefaultsPanel::SetRightContentMargin( wxString rightPageMargin )
{
    m_rightContentMargin->ChangeValue( rightPageMargin );
}

//--------------

void PageDefaultsPanel::SetBorderSize( wxString borderSize )
{
    m_borderSize->ChangeValue( borderSize );
}

//--------------

void PageDefaultsPanel::SetBorderFilename( wxString filename )
{
    m_borderFilename->ChangeValue( filename );
}

//--------------

void PageDefaultsPanel::SetOverSizePaper( bool state ) {
    m_overSizeCheckbox->SetValue( state );
}

//--------------

void PageDefaultsPanel::OnTopContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->TopContentMargin( Design::AlbumPageDefaults( )->TopContentMarginStr( ) );
    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnBottomContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->BottomContentMargin( Design::AlbumPageDefaults( )->BottomContentMarginStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnLeftContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->LeftContentMargin( Design::AlbumPageDefaults( )->LeftContentMarginStr( ) );
    Update( );
    event.Skip( );

}

//--------------

void PageDefaultsPanel::OnRightContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->RightContentMargin( Design::AlbumPageDefaults( )->RightContentMarginStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnOverSizeCheckBoxClick( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->OverSizePaper( m_overSizeCheckbox->IsChecked( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnPaperHeight( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->PaperHeight( Design::AlbumPageDefaults( )->PaperHeightStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnPaperWidth( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->PaperWidth( Design::AlbumPageDefaults( )->PaperWidthStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnPageHeight( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->PageHeight( Design::AlbumPageDefaults( )->PageHeightStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnPageWidth( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->PageWidth( Design::AlbumPageDefaults( )->PageWidthStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnTopPageMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->TopMargin( Design::AlbumPageDefaults( )->TopMarginStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnBottomPageMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->BottomMargin( Design::AlbumPageDefaults( )->BottomMarginStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnLeftPageMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->LeftMargin( Design::AlbumPageDefaults( )->LeftMarginStr( ) );

    Update( );
    event.Skip( );

}

//--------------

void PageDefaultsPanel::OnRightPageMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->RightMargin( Design::AlbumPageDefaults( )->RightMarginStr( ) );


    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnBorderFilename( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->BorderFilename( Design::AlbumPageDefaults( )->BorderFilename( ) );

    Update( );
    event.Skip( );
}

//--------------

void PageDefaultsPanel::OnBorderSize( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->BorderSize( Design::AlbumPageDefaults( )->BorderSizeStr( ) );

    Update( );
    event.Skip( );
}

void PageDefaultsPanel::OnShowBorderCheckBoxClick( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->ShowBorder( Design::AlbumPageDefaults( )->BorderSizeStr( ) );

    Update( );
    event.Skip( );
}
//--------------

void PageDefaultsPanel::OnOrientationChoice( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->Orientation( Design::OrientationStrings[ m_orientationChoice->GetSelection( ) ] );

    Update( );
    event.Skip( );
}
//-------

void PageDefaultsPanel::Update( )
{
    GetAlbumTreeCtrl( )->Update( );
}