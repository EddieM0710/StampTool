/*
 * @file  StampDefaultsPanel.cpp
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

#include "gui/StampDefaultsPanel.h"
#include "gui/StampDefaultsPanel.h"
#include "gui/LabeledTextBox.h"

#include "design/TitleFrame.h"
#include "design/Page.h"
#include "design/Album.h"
#include "design/DesignDefs.h"

#include "utils/Settings.h"
#include "Defs.h"


IMPLEMENT_DYNAMIC_CLASS( StampDefaultsPanel, HelperPanel )


BEGIN_EVENT_TABLE( StampDefaultsPanel, HelperPanel )

END_EVENT_TABLE( )


//---------

StampDefaultsPanel::StampDefaultsPanel( )
{
    Init( );
}

//---------

StampDefaultsPanel::StampDefaultsPanel( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//---------

bool StampDefaultsPanel::Create( wxWindow* parent, wxWindowID id,
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

//---------

StampDefaultsPanel::~StampDefaultsPanel( )
{

}

//---------

void StampDefaultsPanel::Init( )
{

}

//---------

void StampDefaultsPanel::CreateControls( )
{
    StampDefaultsPanel* stampDefaultsPanel = this;


    wxBoxSizer* stampHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    stampDefaultsPanel->SetSizer( stampHorizontalSizer );


    int lastID = ID_LastID;

    wxNotebook* focusNotebook = new wxNotebook( stampDefaultsPanel, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxBK_LEFT );
    focusNotebook->SetPadding( wxSize( 1, 1 ) );
    stampHorizontalSizer->Add( focusNotebook, 1, wxGROW | wxALL, 5 );

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



    m_stampTitleCheckbox = SetupCheckBox( commonPanel, leftCommonVerticalSizer, ++lastID,
        _( "Show Stamp Name" ), wxCommandEventHandler( StampDefaultsPanel::OnShowName ) );

    m_nbrCheckbox = SetupCheckBox( commonPanel, leftCommonVerticalSizer, ++lastID,
        _( "Show Catalog Nbr" ), wxCommandEventHandler( StampDefaultsPanel::OnShowNbr ) );

    m_ImagesCheckbox = SetupCheckBox( commonPanel, leftCommonVerticalSizer, ++lastID,
        _( "Show Images" ), wxCommandEventHandler( StampDefaultsPanel::OnShowImages ) );

    m_grayScaleImagesCheckbox = SetupCheckBox( commonPanel, leftCommonVerticalSizer, ++lastID,
        _( "Show Grayscale Images" ), wxCommandEventHandler( StampDefaultsPanel::OnGrayscale ) );

    m_catalog = SetupLabelText( commonPanel, rightCommonVerticalSizer, lastID,
        _( "Catalog Code" ), true, wxCommandEventHandler( StampDefaultsPanel::OnCatalogCode ) );



    wxBoxSizer* locationSizer;
    wxStaticBox* locationBox = SetupBoxSizer( commonPanel, middleCommonVerticalSizer,
        "Stamp Name Location", lastID, locationSizer, wxHORIZONTAL );

    m_topButton = SetupRadioButton( locationBox, locationSizer, lastID, _( "Top" ), true,
        wxCommandEventHandler( StampDefaultsPanel::OnNameLocationButtonSelected ) );
    m_topButton->SetToolTip( _( "Name above Stamp." ) );

    m_bottomButton = SetupRadioButton( locationBox, locationSizer, lastID, _( "Bottom" ), false,
        wxCommandEventHandler( StampDefaultsPanel::OnNameLocationButtonSelected ) );
    m_bottomButton->SetToolTip( _( "Name below Stamp." ) );

    m_StampMargin =
        SetupLabelText( advancedPanel, middleAdvancedVerticalSizer, lastID, "Stamp Internal Margin", false,
            wxCommandEventHandler( StampDefaultsPanel::OnStampMargin ) );


    wxBoxSizer* selvageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    leftAdvancedVerticalSizer->Add( selvageHorizontalSizer, 1, wxGROW | wxALL, 0 );


    wxBoxSizer* selvageBoxSizer;
    wxStaticBox* selvageBox = SetupBoxSizer( advancedPanel, selvageHorizontalSizer, "Selvage", lastID, selvageBoxSizer, wxHORIZONTAL );

    m_selvageHeight = SetupLabelText( selvageBox, selvageBoxSizer, lastID, _( "Height" ), false, wxCommandEventHandler( StampDefaultsPanel::OnSelvageHeight ) );

    m_selvageWidth = SetupLabelText( selvageBox, selvageBoxSizer, lastID, _( "Width" ), false, wxCommandEventHandler( StampDefaultsPanel::OnSelvageWidth ) );


    wxBoxSizer* mountBoxSizer;
    wxStaticBox* mountSize = SetupBoxSizer( advancedPanel, selvageHorizontalSizer, "Mount Allowance", lastID, mountBoxSizer, wxHORIZONTAL );

    m_mountAllowanceHeight = SetupLabelText( mountSize, mountBoxSizer, lastID, _( "Height" ), false, wxCommandEventHandler( StampDefaultsPanel::OnMountAllowanceHeight ) );

    m_mountAllowanceWidth = SetupLabelText( mountSize, mountBoxSizer, lastID, _( "Width" ), false, wxCommandEventHandler( StampDefaultsPanel::OnMountAllowanceWidth ) );


    wxBoxSizer* contentMarginBoxVSizer;
    wxStaticBox* contentMarginBox = SetupBoxSizer( advancedPanel, rightAdvancedVerticalSizer,
        "Content Margin", lastID, contentMarginBoxVSizer, wxVERTICAL );

    wxBoxSizer* contentMarginBoxHSizer = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( contentMarginBoxHSizer, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( contentMarginBoxHSizer );

    m_topContentMargin = SetupLabelText( contentMarginBox, contentMarginBoxHSizer, lastID,
        _( "Top" ), false, wxCommandEventHandler( StampDefaultsPanel::OnTopContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content top margin in mm." ) );
    HorizontalSpacer( contentMarginBoxHSizer );

    m_bottomContentMargin = SetupLabelText( contentMarginBox, contentMarginBoxHSizer, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( StampDefaultsPanel::OnBottomContentMargin ) );
    m_bottomContentMargin->SetToolTip( _( "Content bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer110 = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( itemBoxSizer110, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer110 );

    m_leftContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer110, lastID,
        _( "Left" ), false, wxCommandEventHandler( StampDefaultsPanel::OnLeftContentMargin ) );
    m_leftContentMargin->SetToolTip( _( "Content left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer110 );

    m_rightContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer110, lastID,
        _( "Right" ), false, wxCommandEventHandler( StampDefaultsPanel::OnRightContentMargin ) );
    m_rightContentMargin->SetToolTip( _( "Content right margin in mm." ) );
}

//--------------

void StampDefaultsPanel::UpdateControls( )
{
    SetShowNbr( Design::AlbumStampDefaults( )->ShowNbr( ) );
    SetShowStampTitle( Design::AlbumStampDefaults( )->ShowName( ) );
    SetGrayScaleImages( Design::AlbumStampDefaults( )->GrayScaleImages( ) );

    SetCatalog( Design::AlbumStampDefaults( )->Catalog( ) );

    SetStampNamePosition( Design::AlbumStampDefaults( )->StampNamePositionType( ) );
    SetTopContentMargin( Design::AlbumStampDefaults( )->TopContentMarginStr( ) );
    SetBottomContentMargin( Design::AlbumStampDefaults( )->BottomContentMarginStr( ) );
    SetLeftContentMargin( Design::AlbumStampDefaults( )->LeftContentMarginStr( ) );
    SetRightContentMargin( Design::AlbumStampDefaults( )->RightContentMarginStr( ) );
    SetStampMargin( Design::AlbumStampDefaults( )->StampMarginStr( ) );
    SetSelvageHeight( Design::AlbumStampDefaults( )->SelvageHeightStr( ) );
    SetSelvageWidth( Design::AlbumStampDefaults( )->SelvageWidthStr( ) );
    SetMountAllowanceHeight( Design::AlbumStampDefaults( )->MountAllowanceHeightStr( ) );
    SetMountAllowanceWidth( Design::AlbumStampDefaults( )->MountAllowanceWidthStr( ) );
    // wxCheckBox* m_ImagesCheckbox;

}

//--------------

void StampDefaultsPanel::SetSelvageHeight( wxString selvageHeight )
{
    m_selvageHeight->ChangeValue( selvageHeight );
}

//----------------

void StampDefaultsPanel::SetSelvageWidth( wxString selvageWidth )
{
    m_selvageWidth->ChangeValue( selvageWidth );
}

//----------------

void StampDefaultsPanel::SetMountAllowanceHeight( wxString mountAllowanceHeight )
{
    m_mountAllowanceHeight->ChangeValue( mountAllowanceHeight );
}

//----------------

void StampDefaultsPanel::SetMountAllowanceWidth( wxString mountAllowanceWidth )
{
    m_mountAllowanceWidth->ChangeValue( mountAllowanceWidth );
}

//----------------

void StampDefaultsPanel::SetStampMargin( wxString stampMargin )
{
    m_StampMargin->ChangeValue( stampMargin );
}

//----------------

void StampDefaultsPanel::SetupDialog( Design::Page* page )
{
    UpdateControls( );
};

//---------

bool StampDefaultsPanel::ShowToolTips( )
{
    return true;
}

//---------

wxString StampDefaultsPanel::GetCatalog( ) {
    return m_catalog->GetValue( );
};

//----------------

void StampDefaultsPanel::SetCatalog( wxString catCode )
{
    m_catalog->ChangeValue( catCode );
}

//--------------

bool StampDefaultsPanel::GetShowNbr( ) {
    return m_nbrCheckbox->IsChecked( );
}

//--------------

bool StampDefaultsPanel::GetShowStampTitle( ) {
    return m_stampTitleCheckbox->GetValue( );
}

//--------------

bool StampDefaultsPanel::GetShowStampSubTitle( ) {
    return m_stampSubTitleCheckbox->GetValue( );
}

//--------------

void StampDefaultsPanel::SetShowNbr( bool state ) {
    m_nbrCheckbox->SetValue( state );
}

//--------------

void StampDefaultsPanel::SetShowStampTitle( bool state ) {
    m_stampTitleCheckbox->SetValue( state );
}

//--------------

void StampDefaultsPanel::SetGrayScaleImages( bool val ) {
    m_grayScaleImagesCheckbox->SetValue( val );
};

//--------------

void StampDefaultsPanel::OnCatalogCode( wxCommandEvent& event )
{
    wxString cat = m_catalog->GetValue( );
    Design::AlbumStampDefaults( )->Catalog( cat );
    Update( );
    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnGrayscale( wxCommandEvent& event )
{
    Design::AlbumStampDefaults( )->GrayScaleImages( m_grayScaleImagesCheckbox->GetValue( ) );
    Update( );
    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnShowImages( wxCommandEvent& event )
{
    Design::AlbumStampDefaults( )->ShowImage( m_ImagesCheckbox->GetValue( ) );
    Update( );
    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnShowNbr( wxCommandEvent& event )
{
    Design::AlbumStampDefaults( )->ShowNbr( m_nbrCheckbox->GetValue( ) );
    Update( );
    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnShowName( wxCommandEvent& event )
{
    Design::AlbumStampDefaults( )->ShowNbr( m_stampTitleCheckbox->GetValue( ) );
    Update( );
    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnNameLocationButtonSelected( wxCommandEvent& event )
{

    if ( m_topButton->GetValue( ) )
    {
        Design::AlbumStampDefaults( )->StampNamePosition( Design::AT_StampNamePositionTop );
    }
    else
    {
        Design::AlbumStampDefaults( )->StampNamePosition( Design::AT_StampNamePositionBottom );
    }
    Update( );

    event.Skip( );
}

//----------------

void StampDefaultsPanel::OnStampMargin( wxCommandEvent& event )
{
    Design::AlbumStampDefaults( )->StampMargin( m_StampMargin->GetValue( ) );
    Update( );

    event.Skip( );
}

//--------------

void StampDefaultsPanel::SetStampNamePosition( Design::StampNamePosType type )
{
    if ( type == Design::AT_StampNamePositionBottom )
    {
        m_bottomButton->SetValue( true );
    }
    else
    {
        m_topButton->SetValue( true );
    }
}

//--------------

void StampDefaultsPanel::OnTopContentMargin( wxCommandEvent& event )
{
    Design::AlbumFrameDefaults( )->TopContentMargin( m_topContentMargin->GetValue( ) );
    Update( );

    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnBottomContentMargin( wxCommandEvent& event )
{
    Design::AlbumFrameDefaults( )->BottomContentMargin( m_bottomContentMargin->GetValue( ) );
    Update( );

    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnLeftContentMargin( wxCommandEvent& event )
{
    Design::AlbumFrameDefaults( )->LeftContentMargin( m_leftContentMargin->GetValue( ) );
    Update( );

    event.Skip( );
}

//--------------

void StampDefaultsPanel::OnRightContentMargin( wxCommandEvent& event )
{
    Design::AlbumFrameDefaults( )->RightContentMargin( m_rightContentMargin->GetValue( ) );
    Update( );

    event.Skip( );
}

//-------

void StampDefaultsPanel::OnSelvageHeight( wxCommandEvent& event )
{
    wxString str = m_selvageWidth->GetValue( );
    double val;
    str.ToDouble( &val );
    Design::AlbumStampDefaults( )->SelvageHeight( val );
    Update( );

    event.Skip( );
};

//-------

void StampDefaultsPanel::OnSelvageWidth( wxCommandEvent& event )
{
    wxString str = m_selvageWidth->GetValue( );
    double val;
    str.ToDouble( &val );
    Design::AlbumStampDefaults( )->SelvageWidth( val );
    Update( );

    event.Skip( );
};

//-------

void StampDefaultsPanel::OnMountAllowanceHeight( wxCommandEvent& event )
{
    wxString str = m_mountAllowanceHeight->GetValue( );
    double val;
    str.ToDouble( &val );
    Design::AlbumStampDefaults( )->MountAllowanceHeight( val );
    Update( );

    event.Skip( );
};

//-------

void StampDefaultsPanel::OnMountAllowanceWidth( wxCommandEvent& event )
{
    wxString str = m_mountAllowanceWidth->GetValue( );
    double val;
    str.ToDouble( &val );
    Design::AlbumStampDefaults( )->MountAllowanceWidth( val );
    Update( );

    event.Skip( );
};

//--------------

void StampDefaultsPanel::SetTopContentMargin( wxString topContentMargin )
{
    m_topContentMargin->ChangeValue( topContentMargin );
}

//--------------

void StampDefaultsPanel::SetBottomContentMargin( wxString bottomContentMargin )
{
    m_bottomContentMargin->ChangeValue( bottomContentMargin );
}

//--------------

void StampDefaultsPanel::SetLeftContentMargin( wxString leftContentMargin )
{
    m_leftContentMargin->ChangeValue( leftContentMargin );
}

//--------------

void StampDefaultsPanel::SetRightContentMargin( wxString rightPageMargin )
{
    m_rightContentMargin->ChangeValue( rightPageMargin );
}
//-------

void StampDefaultsPanel::Update( )
{
    GetAlbumTreeCtrl( )->Update( );
}