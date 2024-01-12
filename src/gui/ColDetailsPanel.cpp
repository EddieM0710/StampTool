/*
 * @file src/gui/ColDetailsPanel.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
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
#include "wx/notebook.h"
#include "wx/imaglist.h"

#include "gui/ColDetailsPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
 //#include "gui/TitleHelper.h"
#include "design/Column.h"
#include "design/Album.h"
#include "design/TitleFrame.h"
#include "utils/FontList.h"

IMPLEMENT_DYNAMIC_CLASS( ColDetailsPanel, HelperPanel )

BEGIN_EVENT_TABLE( ColDetailsPanel, HelperPanel )
EVT_BUTTON( wxID_OK, ColDetailsPanel::OnOkClick )
//EVT_BUTTON( ID_COLDEFAULTFONTBUTTON, ColDetailsPanel::OnTitleDefaultClick )

END_EVENT_TABLE( )

//--------------

ColDetailsPanel::ColDetailsPanel( )
{
    Init( );
}

//--------------

ColDetailsPanel::ColDetailsPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

ColDetailsPanel::~ColDetailsPanel( )
{
}

//--------------

bool ColDetailsPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // ColDetailsPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // ColDetailsPanel creation
    return true;
}

//--------------

void ColDetailsPanel::CreateControls( )
{

    ColDetailsPanel* theDialog = this;

    m_dialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( m_dialogVerticalSizer );


    // //>> first row ctrls
    wxBoxSizer* firstRowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    m_dialogVerticalSizer->Add( firstRowHorizontalSizer, 0, wxGROW | wxALL, 0 );


    int lastID = ID_LastID;

    m_frameCheckbox = SetupCheckBox( theDialog, firstRowHorizontalSizer, lastID,
        ( "Show Frame" ), wxCommandEventHandler( ColDetailsPanel::OnFrameCheckboxClick ) );
    m_frameCheckbox->SetValue( false );

    // m_frameCheckbox = new wxCheckBox( theDialog, ID_FRAMECHECKBOX, _( "Show Frame" ), wxDefaultPosition, wxDefaultSize, 0 );
    // m_frameCheckbox->SetValue( false );
    // m_dialogVerticalSizer->Add( m_frameCheckbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );
    // //>> first row ctrls


    m_titleHelper = SetupTitleHelper( theDialog, m_dialogVerticalSizer, lastID, DefaultTitleHelperStyle,
        wxCommandEventHandler( ColDetailsPanel::OnTitleCheckboxClick ),
        wxCommandEventHandler( ColDetailsPanel::OnTitleTextChanged ),
        wxCommandEventHandler( ColDetailsPanel::OnSubTitleCheckboxClick ),
        wxCommandEventHandler( ColDetailsPanel::OnSubTitleTextChanged ) );

    SetupFontPicker( theDialog, m_dialogVerticalSizer, lastID,
        _( "Title" ), _( "Default" ),
        m_titleFontPicker, m_titleColorPicker,
        wxFontPickerEventHandler( ColDetailsPanel::OnTitleFontPicker ),
        wxColourPickerEventHandler( ColDetailsPanel::OnTitleColorPicker ),
        wxCommandEventHandler( ColDetailsPanel::OnTitleDefaultClick ) );


    FontPicker* titleFontPicker = SetupFontPicker( theDialog, m_dialogVerticalSizer, lastID,
        _( "SubTitle" ), _( "Default" ),
        m_subTitleFontPicker, m_subTitleColorPicker,
        wxFontPickerEventHandler( ColDetailsPanel::OnSubTitleFontPicker ),
        wxColourPickerEventHandler( ColDetailsPanel::OnSubTitleColorPicker ),
        wxCommandEventHandler( ColDetailsPanel::OnSubTitleDefaultClick ) );


    // m_titleHelper = new TitleHelper( theDialog, m_dialogVerticalSizer, lastID, HasLabels );
    // m_titleLabel = m_titleHelper->GetTitleLabel( );
    // m_subTitleLabel = m_titleHelper->GetSubTitleLabel( );
    // m_titleCheckbox = m_titleHelper->GetTitleCheckbox( );
    // m_titleCheckbox->SetLabelText( "Title" );
    // m_titleCheckbox->SetValue( true );
    // m_subTitleCheckbox = m_titleHelper->GetSubTitleCheckbox( );
    // m_subTitleCheckbox->SetLabelText( "SubTitle" );
    // m_subTitleCheckbox->SetValue( false );

    // m_titleFontPicker = m_titleHelper->GetTitleFontPickerCtrl( );
    // m_titleColorPicker = m_titleHelper->GetTitleColourPickerCtrl( );

    // m_subTitleFontPicker = m_titleHelper->GetSubTitleFontPickerCtrl( );
    // m_subTitleColorPicker = m_titleHelper->GetSubTitleColourPickerCtrl( );

    // Connect( m_titleHelper->GetSubTitleDefaultButton( )->GetId( ),
    //     wxEVT_BUTTON,
    //     wxCommandEventHandler( ColDetailsPanel::OnNameDefaultClick ) );

    // Connect( m_titleHelper->GetSubTitleDefaultButton( )->GetId( ),
    //     wxEVT_BUTTON,
    //     wxCommandEventHandler( ColDetailsPanel::OnSubTitleDefaultClick ) );

    // Connect( m_titleHelper->GetTitleCheckbox( )->GetId( ),
    //     wxEVT_CHECKBOX,
    //     wxCommandEventHandler( ColDetailsPanel::OnNameCheckboxClick ) );

    // Connect( m_titleHelper->GetSubTitleCheckbox( )->GetId( ),
    //     wxEVT_CHECKBOX,
    //     wxCommandEventHandler( ColDetailsPanel::OnSubTitleCheckboxClick ) );
    //@@@


    wxStaticBox* memberPositionStaticBox = new wxStaticBox( theDialog, wxID_ANY, _( "Member Position" ) );
    wxStaticBoxSizer* memberPositionStaticBoxSizer = new wxStaticBoxSizer( memberPositionStaticBox, wxHORIZONTAL );
    m_dialogVerticalSizer->Add( memberPositionStaticBoxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    m_positionCalculated = new wxRadioButton( memberPositionStaticBoxSizer->GetStaticBox( ), ID_CALCULATEDRADIOBUTTON, _( "Calculated" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_positionCalculated->SetValue( true );
    m_positionCalculated->SetToolTip( _( "Evenly Distributed" ) );
    memberPositionStaticBoxSizer->Add( m_positionCalculated, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    memberPositionStaticBoxSizer->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    m_positionFixed = new wxRadioButton( memberPositionStaticBoxSizer->GetStaticBox( ), ID_FIXEDRADIOBUTTON, _( "Fixed" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_positionFixed->SetValue( false );
    memberPositionStaticBoxSizer->Add( m_positionFixed, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_positionFixedSize = new wxTextCtrl( memberPositionStaticBoxSizer->GetStaticBox( ), ID_FIXEDSIZETEXTCTRL, _( "4" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_positionFixedSize->SetToolTip( _( "mm" ) );
    m_positionFixedSize->Enable( false );
    memberPositionStaticBoxSizer->Add( m_positionFixedSize, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    //>>error list ctrls
    wxBoxSizer* errorListSizer = new wxBoxSizer( wxHORIZONTAL );
    m_dialogVerticalSizer->Add( errorListSizer, 2, wxGROW | wxALL, 5 );

    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( theDialog, ID_LISTCTRL, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );
    errorListSizer->Add( m_statusList, 2, wxGROW | wxALL, 5 );
    //<<error list ctrls



    wxBoxSizer* contentMarginBoxVSizer;
    wxStaticBox* contentMarginBox = SetupBoxSizer( theDialog, m_dialogVerticalSizer,
        "Content Margin", lastID, contentMarginBoxVSizer, wxVERTICAL );

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( itemBoxSizer17, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer17 );

    m_topContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer17, lastID,
        _( "Top" ), false, wxCommandEventHandler( ColDetailsPanel::OnTopContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content top margin in mm." ) );
    HorizontalSpacer( itemBoxSizer17 );

    m_bottomContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer17, lastID,
        _( "Bottom" ), false, wxCommandEventHandler( ColDetailsPanel::OnBottomContentMargin ) );
    m_bottomContentMargin->SetToolTip( _( "Content bottom margin in mm." ) );


    wxBoxSizer* itemBoxSizer110 = new wxBoxSizer( wxHORIZONTAL );
    contentMarginBoxVSizer->Add( itemBoxSizer110, 0, wxGROW | wxALL, 0 );

    HorizontalSpacer( itemBoxSizer110 );

    m_leftContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer110, lastID,
        _( "Left" ), false, wxCommandEventHandler( ColDetailsPanel::OnLeftContentMargin ) );
    m_leftContentMargin->SetToolTip( _( "Content left margin in mm." ) );

    HorizontalSpacer( itemBoxSizer110 );

    m_rightContentMargin = SetupLabelText( contentMarginBox, itemBoxSizer110, lastID,
        _( "Right" ), false, wxCommandEventHandler( ColDetailsPanel::OnRightContentMargin ) );
    m_topContentMargin->SetToolTip( _( "Content right margin in mm." ) );

}




//--------------


void ColDetailsPanel::UpdateControls( )
{
    //SetTitle ( m_col->GetTitleString ( ) );
    SetShowTitle( m_col->GetShowTitle( ) );
    SetShowSubTitle( m_col->GetShowSubTitle( ) );
    SetShow( m_col->GetShowFrame( ) );
    SetTitleFont( m_col->GetTitleFrame( )->GetHeadingFont( ) );
    SetTitleColor( m_col->GetTitleFrame( )->GetHeadingColor( ) );


    SetTopContentMargin( Design::AlbumPageDefaults( )->TopContentMarginStr( ) );
    SetBottomContentMargin( Design::AlbumPageDefaults( )->BottomContentMarginStr( ) );
    SetLeftContentMargin( Design::AlbumPageDefaults( )->LeftContentMarginStr( ) );
    SetRightContentMargin( Design::AlbumPageDefaults( )->RightContentMarginStr( ) );

    //   m_col->GetDefaultStampNamePositionType( );
}


//--------------

void ColDetailsPanel::SetupDialog( Design::Column* col )
{

    m_col = col;
    UpdateControls( );

    wxArrayString* errors = m_col->GetErrorArray( );

    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }
};

//--------------

bool ColDetailsPanel::GetShowTitle( ) {
    return m_titleHelper->titleCheckbox->IsChecked( );
};;

bool ColDetailsPanel::GetShowSubTitle( ) {
    return m_titleHelper->subTitleCheckbox->IsChecked( );
};;

//--------------

bool ColDetailsPanel::GetShowFrame( ) {
    return m_frameCheckbox->IsChecked( );
};

wxString ColDetailsPanel::GetTitle( ) {
    return m_titleHelper->titleLabel->GetValue( );
};

//--------------

void ColDetailsPanel::SetShowTitle( bool state ) {
    m_titleHelper->titleCheckbox->SetValue( state );
};
void ColDetailsPanel::SetShowSubTitle( bool state ) {
    m_titleHelper->subTitleCheckbox->SetValue( state );
};

//--------------

void ColDetailsPanel::SetShow( bool state ) {
    m_frameCheckbox->SetValue( state );
};

//--------------

//--------------

wxFont ColDetailsPanel::GetTitleFont( ) {
    return m_titleFontPicker->GetSelectedFont( );
}

//--------------

wxColour ColDetailsPanel::GetTitleColor( ) {
    return m_titleColorPicker->GetColour( );
}

//--------------

void ColDetailsPanel::Init( )
{
    m_frameCheckbox = NULL;
    m_statusList = NULL;
}

//--------------

bool ColDetailsPanel::IsNameModified( ) {
    return m_titleHelper->titleLabel->IsModified( );
};

//--------------

void ColDetailsPanel::OnOkClick( wxCommandEvent& event )
{

    // m_col->SetTitleString ( GetTitle ( ) );

    m_col->SetShowFrame( GetShowFrame( ) );
    m_col->SetShowTitle( GetShowTitle( ) );
    m_col->SetShowSubTitle( GetShowSubTitle( ) );

    m_col->GetTitleFrame( )->SetHeadingFont( GetTitleFont( ), GetTitleColor( ) );
    m_col->SetCalculateSpacing( CalculateSpacing( ) );
    m_col->SetFixedSpacingSize( GetFixedSpacing( ) );

    event.Skip( );

}


//--------------

void ColDetailsPanel::OnFrameCheckboxClick( wxCommandEvent& event )
{
    m_col->SetShowFrame( m_frameCheckbox->GetValue( ) );
}

//--------------

void ColDetailsPanel::SetCalculateSpacing( bool val )
{
    if ( val )
    {
        m_positionCalculated->SetValue( true );
        m_positionFixed->SetValue( false );
        m_positionFixedSize->Enable( false );
    }
    else
    {
        m_positionFixed->SetValue( true );
        m_positionCalculated->SetValue( false );
        m_positionFixedSize->Enable( true );

    }
};

void ColDetailsPanel::SetTitleFont( wxFont font ) {
    m_titleFontPicker->SetSelectedFont( font );
}

//--------------

void ColDetailsPanel::SetTitleColor( wxColour color ) {
    m_titleColorPicker->SetColour( color );
}


void ColDetailsPanel::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    event.Skip( );
}


void ColDetailsPanel::OnTitleTextChanged( wxCommandEvent& event )
{
}
void ColDetailsPanel::OnSubTitleTextChanged( wxCommandEvent& event )
{
}

void ColDetailsPanel::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );
    event.Skip( );
}

void ColDetailsPanel::OnTitleFontPicker( wxFontPickerEvent& event )
{
    m_col->GetTitleFrame( )->SetHeadingFont( m_titleFontPicker->GetSelectedFont( ), m_titleColorPicker->GetColour( ) );

    m_col->GetTitleFrame( )->SetHeadingFont(
        m_titleFontPicker->GetSelectedFont( ),
        m_titleColorPicker->GetColour( ) );

}
void ColDetailsPanel::OnTitleColorPicker( wxColourPickerEvent& event )
{
    m_col->GetTitleFrame( )->SetHeadingFont(
        m_titleFontPicker->GetSelectedFont( ),
        m_titleColorPicker->GetColour( ) );
}

void ColDetailsPanel::OnSubTitleFontPicker( wxFontPickerEvent& event )
{
    m_col->GetTitleFrame( )->SetSubHeadingFont(
        m_subTitleFontPicker->GetSelectedFont( ),
        m_subTitleColorPicker->GetColour( ) );
}
void ColDetailsPanel::OnSubTitleColorPicker( wxColourPickerEvent& event )
{
    m_col->GetTitleFrame( )->SetSubHeadingFont(
        m_subTitleFontPicker->GetSelectedFont( ),
        m_subTitleColorPicker->GetColour( ) );

}



void ColDetailsPanel::OnTitleCheckboxClick( wxCommandEvent& event )
{
    m_col->SetShowTitle( m_titleHelper->titleCheckbox->GetValue( ) );
    UpdateTitleState( m_titleHelper );
    Layout( );
}



void ColDetailsPanel::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    m_col->SetShowSubTitle( m_titleHelper->subTitleCheckbox->GetValue( ) );
    UpdateSubTitleState( m_titleHelper );
    Layout( );
};

//-------

void ColDetailsPanel::SetStatusList( )
{
    m_statusList->Clear( );
    wxArrayString* errors = m_col->GetErrorArray( );
    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }
}
//-------

void ColDetailsPanel::Update( )
{
    GetAlbumTreeCtrl( )->Update( );
    SetStatusList( );
}

//--------------

void ColDetailsPanel::SetTopContentMargin( wxString topContentMargin )
{
    m_topContentMargin->ChangeValue( topContentMargin );
}

//--------------

void ColDetailsPanel::SetBottomContentMargin( wxString bottomContentMargin )
{
    m_bottomContentMargin->ChangeValue( bottomContentMargin );
}

//--------------

void ColDetailsPanel::SetLeftContentMargin( wxString leftContentMargin )
{
    m_leftContentMargin->ChangeValue( leftContentMargin );
}

//--------------

void ColDetailsPanel::SetRightContentMargin( wxString rightPageMargin )
{
    m_rightContentMargin->ChangeValue( rightPageMargin );
}

//--------------

void ColDetailsPanel::OnTopContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->TopContentMargin( Design::AlbumPageDefaults( )->TopContentMarginStr( ) );
    Update( );
    event.Skip( );
}

//--------------

void ColDetailsPanel::OnBottomContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->BottomContentMargin( Design::AlbumPageDefaults( )->BottomContentMarginStr( ) );

    Update( );
    event.Skip( );
}

//--------------

void ColDetailsPanel::OnLeftContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->LeftContentMargin( Design::AlbumPageDefaults( )->LeftContentMarginStr( ) );
    Update( );
    event.Skip( );

}

//--------------

void ColDetailsPanel::OnRightContentMargin( wxCommandEvent& event )
{
    Design::AlbumPageDefaults( )->RightContentMargin( Design::AlbumPageDefaults( )->RightContentMarginStr( ) );

    Update( );
    event.Skip( );
}
