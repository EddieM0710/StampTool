/*
 * @file  RowDetailsPanel.cpp
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
#include "wx/notebook.h"

#include "gui/RowDetailsPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "design/Row.h"
#include "design/TitleFrame.h"
#include "design/Album.h"
#include "utils/FontList.h"


 /*
  * RowDetailsPanel type definition
  */
IMPLEMENT_DYNAMIC_CLASS( RowDetailsPanel, HelperPanel )


/*
 * RowDetailsPanel event table definition
 */
    BEGIN_EVENT_TABLE( RowDetailsPanel, HelperPanel )
    // EVT_RADIOBUTTON( ID_DEFAULTRADIOBUTTON, RowDetailsPanel::OnDefaultRadioButtonSelected )
    // EVT_RADIOBUTTON( ID_TOPRADIOBUTTON, RowDetailsPanel::OnTopRadioButtonSelected )
    // EVT_RADIOBUTTON( ID_BOTTOMRADIOBUTTON, RowDetailsPanel::OnBottomRadioButtonSelected )
    // EVT_RADIOBUTTON( ID_CALCULATEDRADIOBUTTON, RowDetailsPanel::OnCalculatedClick )
    // EVT_RADIOBUTTON( ID_FIXEDRADIOBUTTON, RowDetailsPanel::OnFixedClick )
    END_EVENT_TABLE( )
    ;

/*
 * RowDetailsPanel constructors
 */

RowDetailsPanel::RowDetailsPanel( )
{
    Init( );
}

RowDetailsPanel::RowDetailsPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * RowDetailsPanel creator
 */

bool RowDetailsPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // RowDetailsPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // RowDetailsPanel creation
    return true;
}



RowDetailsPanel::~RowDetailsPanel( )
{

}


void RowDetailsPanel::Init( )
{

    m_frameCheckbox = NULL;
    m_statusList = NULL;
}




void RowDetailsPanel::CreateControls( )
{
    RowDetailsPanel* theDialog = this;

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialog->SetSizer( detailsHorizontalSizer );


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


    m_frameCheckbox = SetupCheckBox( commonPanel, leftCommonVerticalSizer, lastID,
        ( "Show Frame" ), wxCommandEventHandler( RowDetailsPanel::OnFrameCheckboxClick ) );
    m_frameCheckbox->SetValue( false );


    m_titleHelper = SetupTitleHelper( commonPanel, leftCommonVerticalSizer, lastID, DefaultTitleHelperStyle,
        wxCommandEventHandler( RowDetailsPanel::OnTitleCheckboxClick ),
        wxCommandEventHandler( RowDetailsPanel::OnTitleTextChanged ),
        wxCommandEventHandler( RowDetailsPanel::OnSubTitleCheckboxClick ),
        wxCommandEventHandler( RowDetailsPanel::OnSubTitleTextChanged ) );


    //wxBoxSizer* fontboxSizer;
    //wxStaticBox* fontBox = SetupBoxSizer( theDialog, m_leftColumnVerticalSizer, "Font", lastID, fontboxSizer, wxVERTICAL );


    SetupFontPicker( advancedPanel, leftAdvancedVerticalSizer, lastID,
        _( "Title Font" ), _( "Default" ),
        m_titleFontPicker, m_titleColorPicker,
        wxFontPickerEventHandler( RowDetailsPanel::OnTitleFontPicker ),
        wxColourPickerEventHandler( RowDetailsPanel::OnTitleColorPicker ),
        wxCommandEventHandler( RowDetailsPanel::OnTitleDefaultClick ) );


    SetupFontPicker( advancedPanel, leftAdvancedVerticalSizer, lastID,
        _( "SubTitle Font" ), _( "Default" ),
        m_subTitleFontPicker, m_subTitleColorPicker,
        wxFontPickerEventHandler( RowDetailsPanel::OnSubTitleFontPicker ),
        wxColourPickerEventHandler( RowDetailsPanel::OnSubTitleColorPicker ),
        wxCommandEventHandler( RowDetailsPanel::OnSubTitleDefaultClick ) );





    wxBoxSizer* alignmentModeVSizer;
    wxStaticBox* alignmentModeBox = SetupBoxSizer( commonPanel, middleCommonVerticalSizer, "Member Stamp Alignment Mode", lastID, alignmentModeVSizer, wxHORIZONTAL );

    m_alignTopButton = SetupRadioButton( alignmentModeBox, alignmentModeVSizer, lastID, _( "Top" ), false,
        wxCommandEventHandler( RowDetailsPanel::OnAlignmentModeButtonSelected ) );

    m_alignMiddleButton = SetupRadioButton( alignmentModeBox, alignmentModeVSizer, lastID, _( "Middle" ), false,
        wxCommandEventHandler( RowDetailsPanel::OnAlignmentModeButtonSelected ) );

    m_alignBottomButton = SetupRadioButton( alignmentModeBox, alignmentModeVSizer, lastID, _( "Bottom" ), false,
        wxCommandEventHandler( RowDetailsPanel::OnAlignmentModeButtonSelected ) );



    wxBoxSizer* memberPositionVSizer;
    wxStaticBox* memberPositionStaticBox = SetupBoxSizer( commonPanel, middleCommonVerticalSizer, "Member Position", lastID, memberPositionVSizer, wxHORIZONTAL );

    m_positionCalculated = SetupRadioButton( memberPositionStaticBox, memberPositionVSizer, lastID, _( "Calculated" ), true,
        wxCommandEventHandler( RowDetailsPanel::OnCalculatedClick ) );
    m_positionCalculated->SetToolTip( _( "Calculate based on available space." ) );

    HorizontalSpacer( memberPositionVSizer );

    m_positionFixed = SetupRadioButton( memberPositionStaticBox, memberPositionVSizer, lastID, _( "Fixed" ), false,
        wxCommandEventHandler( RowDetailsPanel::OnFixedClick ) );
    m_positionCalculated->SetToolTip( _( "Evenly Distributed" ) );

    m_positionFixedSize = new wxTextCtrl( memberPositionStaticBox, ++lastID, _( "4" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_positionFixedSize->SetToolTip( _( "mm" ) );
    m_positionFixedSize->Enable( false );
    memberPositionVSizer->Add( m_positionFixedSize, 0, wxALIGN_LEFT | wxALL, 5 );



    //>>error list ctrls
    wxBoxSizer* errorListSizer = new wxBoxSizer( wxHORIZONTAL );
    rightCommonVerticalSizer->Add( errorListSizer, 2, wxGROW | wxALL, 5 );

    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( commonPanel, ID_LISTCTRL, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );
    errorListSizer->Add( m_statusList, 2, wxGROW | wxALL, 0 );
    //<< error list ctrls

}
// Design::StampNamePositionType  RowDetailsPanel::GetTitleLocationType( )
// {
//     return m_titleLocation;
// }



void RowDetailsPanel::SetAlignmentMode( )
{
    Design::AlignmentModeType mode = m_row->GetAlignmentModeType( );
    if ( mode == Design::AlignTop )
    {
        m_alignTopButton->SetValue( true );
    }
    else if ( mode == Design::AlignMiddle )
    {
        m_alignMiddleButton->SetValue( true );
    }
    else if ( mode == Design::AlignBottom )
    {
        m_alignBottomButton->SetValue( true );
    }
    else
    {
        m_alignDefaultButton->SetValue( true );;
    }
}

void RowDetailsPanel::UpdateControls( )
{

    SetTitle( m_row->GetTitleString( ) );
    SetShowTitle( m_row->GetShowTitle( ) );
    SetShowSubTitle( m_row->GetShowSubTitle( ) );
    SetShow( m_row->GetShow( ) );
    SetColor( m_row->GetTitleFrame( )->GetHeadingColor( ) );
    // SetTitleLocation( );
    SetAlignmentMode( );
    SetFixedSpacingSize( m_row->GetFixedSpacing( ) );
    SetCalculateSpacing( m_row->CalculateSpacing( ) );

    wxListBox* m_statusList;
}


void RowDetailsPanel::SetupDialog( Design::Row* row )
{
    m_row = row;
    UpdateControls( );
    wxArrayString* errors = m_row->GetErrorArray( );


    if ( !errors->IsEmpty( ) )
    {
        m_statusList->InsertItems( *errors, 0 );
    }
};
bool RowDetailsPanel::GetShowTitle( ) {
    return m_titleHelper->titleCheckbox->IsChecked( );
};;
bool RowDetailsPanel::GetShowSubTitle( ) {
    return m_titleHelper->subTitleCheckbox->IsChecked( );

};;
bool RowDetailsPanel::GetShow( ) {
    return m_frameCheckbox->IsChecked( );

};


void RowDetailsPanel::SetShowTitle( bool state ) {
    m_titleHelper->titleCheckbox->SetValue( state );
};
void RowDetailsPanel::SetShowSubTitle( bool state ) {
    //   m_titleHelper->subTitleCheckbox->SetValue( state );
};
void RowDetailsPanel::SetShow( bool state ) {
    m_frameCheckbox->SetValue( state );
};

wxString RowDetailsPanel::GetTitle( ) {
    return m_titleHelper->titleLabel->GetValue( );
};


void RowDetailsPanel::SetTitle( wxString str ) {
    m_titleHelper->titleLabel->SetValue( str );
};


void RowDetailsPanel::SetFont( wxFont font )
{
    m_titleFontPicker->SetSelectedFont( font );
}

void RowDetailsPanel::SetColor( wxColour color )
{
    m_titleColorPicker->SetColour( color );
}

void RowDetailsPanel::SetCalculateSpacing( bool val )
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


void RowDetailsPanel::OnAlignmentModeButtonSelected( wxCommandEvent& event )
{
    if ( m_alignTopButton->GetValue( ) )
    {
        m_row->SetAlignmentMode( Design::AlignTop );
    }
    else if ( m_alignMiddleButton->GetValue( ) )
    {
        m_row->SetAlignmentMode( Design::AlignMiddle );
    }
    else if ( m_alignBottomButton->GetValue( ) )
    {
        m_row->SetAlignmentMode( Design::AlignBottom );
    }

    event.Skip( );
}


void RowDetailsPanel::OnCalculatedClick( wxCommandEvent& event )
{
    m_positionFixedSize->Enable( false );
    m_row->SetCalculateSpacing( true );
    event.Skip( );
}
void RowDetailsPanel::OnFixedClick( wxCommandEvent& event )
{
    m_positionFixedSize->Enable( true );
    m_row->SetCalculateSpacing( false );
    event.Skip( );
}



void RowDetailsPanel::OnTitleTextChanged( wxCommandEvent& event )
{
    wxString title = m_titleHelper->titleLabel->GetValue( );
    m_row->SetTitleString( title );
}
void RowDetailsPanel::OnSubTitleTextChanged( wxCommandEvent& event )
{
    //     wxString title = m_titleHelper->subTitleLabel->GetValue( );
    //     m_row->SetSubTitleString( title );
}


void RowDetailsPanel::OnTitleFontPicker( wxFontPickerEvent& event )
{
}
void RowDetailsPanel::OnTitleColorPicker( wxColourPickerEvent& event )
{
}

void RowDetailsPanel::OnSubTitleFontPicker( wxFontPickerEvent& event )
{
}
void RowDetailsPanel::OnSubTitleColorPicker( wxColourPickerEvent& event )
{
}
void RowDetailsPanel::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    event.Skip( );
}



void RowDetailsPanel::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );
    event.Skip( );
}

void RowDetailsPanel::OnFrameCheckboxClick( wxCommandEvent& event )
{
    m_row->SetShow( m_frameCheckbox->GetValue( ) );
}

void RowDetailsPanel::OnTitleCheckboxClick( wxCommandEvent& event )
{
    m_row->SetShowTitle( m_titleHelper->titleCheckbox->GetValue( ) );
    UpdateTitleState( m_titleHelper );
    Layout( );
}

void RowDetailsPanel::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    UpdateSubTitleState( m_titleHelper );
    Layout( );
};
