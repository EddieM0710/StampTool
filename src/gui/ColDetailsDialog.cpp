/*
 * @file src/gui/ColDetailsDialog.cpp
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

#include "gui/ColDetailsDialog.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "gui/TitleHelper.h"
#include "design/Column.h"
#include "design/Album.h"
#include "utils/FontList.h"

IMPLEMENT_DYNAMIC_CLASS( ColDetailsDialog, wxDialog )

BEGIN_EVENT_TABLE( ColDetailsDialog, wxDialog )
EVT_BUTTON( wxID_OK, ColDetailsDialog::OnOkClick )
EVT_RADIOBUTTON( ID_DEFAULTRADIOBUTTON, ColDetailsDialog::OnDefaultRadioButtonSelected )
EVT_RADIOBUTTON( ID_TOPRADIOBUTTON, ColDetailsDialog::OnTopRadioButtonSelected )
EVT_RADIOBUTTON( ID_BOTTOMRADIOBUTTON, ColDetailsDialog::OnBottomRadioButtonSelected )
//EVT_BUTTON( ID_COLDEFAULTFONTBUTTON, ColDetailsDialog::OnTitleDefaultClick )

END_EVENT_TABLE( )

//--------------

ColDetailsDialog::ColDetailsDialog( )
{
    Init( );
}

//--------------

ColDetailsDialog::ColDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

ColDetailsDialog::~ColDetailsDialog( )
{
}

//--------------

bool ColDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // ColDetailsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // ColDetailsDialog creation
    return true;
}

//--------------

void ColDetailsDialog::CreateControls( )
{
    //   std::cout << "ColDetailsDialog" << "\n";

    ColDetailsDialog* theDialog = this;

    m_dialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( m_dialogVerticalSizer );


    // //>> first row ctrls
    wxBoxSizer* firstRowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    m_dialogVerticalSizer->Add( firstRowHorizontalSizer, 0, wxGROW | wxALL, 0 );


    m_frameCheckbox = new wxCheckBox( theDialog, ID_FRAMECHECKBOX, _( "Show Frame" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_frameCheckbox->SetValue( false );
    m_dialogVerticalSizer->Add( m_frameCheckbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );
    //>> first row ctrls


    int lastID = ID_LastID;

    m_titleHelper = new TitleHelper( theDialog, m_dialogVerticalSizer, lastID, HasLabels );
    m_titleLabel = m_titleHelper->GetTitleLabel( );
    m_subTitleLabel = m_titleHelper->GetSubTitleLabel( );
    m_titleCheckbox = m_titleHelper->GetTitleCheckbox( );
    m_titleCheckbox->SetLabelText( "Title" );
    m_titleCheckbox->SetValue( true );
    m_subTitleCheckbox = m_titleHelper->GetSubTitleCheckbox( );
    m_subTitleCheckbox->SetLabelText( "SubTitle" );
    m_subTitleCheckbox->SetValue( false );

    m_titleFontPicker = m_titleHelper->GetTitleFontPickerCtrl( );
    m_titleColorPicker = m_titleHelper->GetTitleColourPickerCtrl( );

    m_subTitleFontPicker = m_titleHelper->GetSubTitleFontPickerCtrl( );
    m_subTitleColorPicker = m_titleHelper->GetSubTitleColourPickerCtrl( );

    Connect( m_titleHelper->GetSubTitleDefaultButton( )->GetId( ),
        wxEVT_BUTTON,
        wxCommandEventHandler( ColDetailsDialog::OnNameDefaultClick ) );

    Connect( m_titleHelper->GetSubTitleDefaultButton( )->GetId( ),
        wxEVT_BUTTON,
        wxCommandEventHandler( ColDetailsDialog::OnSubTitleDefaultClick ) );

    Connect( m_titleHelper->GetTitleCheckbox( )->GetId( ),
        wxEVT_CHECKBOX,
        wxCommandEventHandler( ColDetailsDialog::OnNameCheckboxClick ) );

    Connect( m_titleHelper->GetSubTitleCheckbox( )->GetId( ),
        wxEVT_CHECKBOX,
        wxCommandEventHandler( ColDetailsDialog::OnSubTitleCheckboxClick ) );
    //@@@

    m_TitleLocationBox = new wxStaticBox( theDialog, wxID_ANY, _( "Member Title Location" ) );
    m_titleLocationVSizer = new wxStaticBoxSizer( m_TitleLocationBox, wxVERTICAL );
    m_dialogVerticalSizer->Add( m_titleLocationVSizer, 1, wxGROW | wxALL, 5 );

    m_titleLocationHSizer = new wxBoxSizer( wxHORIZONTAL );
    m_titleLocationVSizer->Add( m_titleLocationHSizer, 1, wxGROW | wxALL, 0 );

    m_defaultButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_DEFAULTRADIOBUTTON, _( "Default" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_defaultButton->SetValue( false );
    m_titleLocationHSizer->Add( m_defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_topButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_TOPRADIOBUTTON, _( "Top" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_topButton->SetValue( true );
    m_titleLocationHSizer->Add( m_topButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_bottomButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_BOTTOMRADIOBUTTON, _( "Bottom" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_bottomButton->SetValue( false );
    m_titleLocationHSizer->Add( m_bottomButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );



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


    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    m_dialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* itemButton6 = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton6, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton7 = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  
}

//--------------
Design::TitleLocation  ColDetailsDialog::GetTitleLocation( )
{
    if ( m_topButton->GetValue( ) )
    {
        return Design::AT_TitleLocationTop;
    }
    if ( m_bottomButton->GetValue( ) )
    {
        return Design::AT_TitleLocationBottom;
    }
    return Design::AT_TitleLocationDefault;
}

void ColDetailsDialog::SetTitleLocation( )
{
    Design::TitleLocation titleLocation = m_col->GetTitleLocation( );
    if ( titleLocation == Design::AT_TitleLocationTop )
    {
        m_topButton->SetValue( true );
    }
    else if ( titleLocation == Design::AT_TitleLocationBottom )
    {
        m_bottomButton->SetValue( true );
    }
    else if ( titleLocation == Design::AT_TitleLocationDefault )
    {
        m_defaultButton->SetValue( true );;
    }
}

//--------------


void ColDetailsDialog::UpdateControls( )
{
    SetTitle( m_col->GetTitleString( ) );
    SetShowTitle( m_col->GetShowTitle( ) );
    SetShowSubTitle( m_col->GetShowSubTitle( ) );
    SetShowFrame( m_col->GetShowFrame( ) );
    SetTitleFont( m_col->GetTitleFrame( )->GetFont( ) );
    SetTitleColor( m_col->GetTitleFrame( )->GetColor( ) );
    m_col->GetTitleLocation( );
}


//--------------

void ColDetailsDialog::SetupDialog( wxTreeItemId treeID )
{
    if ( treeID.IsOk( ) )
    {
        m_designTreeID = treeID;
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( m_designTreeID );
        m_col = ( Design::Column* ) data->GetNodeElement( );
        UpdateControls( );

        wxArrayString* errors = m_col->GetErrorArray( );
        // positionTextCtrl->AlwaysShowScrollbars( );
        // // m_row->DumpRow( positionTextCtrl );
        // positionTextCtrl->ShowPosition( 0 );

        if ( !errors->IsEmpty( ) )
        {
            m_statusList->InsertItems( *errors, 0 );
        }
    }
};

//--------------

bool ColDetailsDialog::GetShowTitle( ) { return m_titleCheckbox->IsChecked( ); };;

bool ColDetailsDialog::GetShowSubTitle( ) { return m_subTitleCheckbox->IsChecked( ); };;

//--------------

bool ColDetailsDialog::GetShowFrame( ) { return m_frameCheckbox->IsChecked( ); };

//--------------

void ColDetailsDialog::SetNameModified( bool state ) { m_titleLabel->SetModified( state ); };

//--------------

void ColDetailsDialog::SetShowTitle( bool state ) { m_titleCheckbox->SetValue( state ); };
void ColDetailsDialog::SetShowSubTitle( bool state ) { m_subTitleCheckbox->SetValue( state ); };

//--------------

void ColDetailsDialog::SetShowFrame( bool state ) { m_frameCheckbox->SetValue( state ); };

//--------------

//--------------

wxFont ColDetailsDialog::GetTitleFont( ) { return m_titleFontPicker->GetSelectedFont( ); }

//--------------

wxColour ColDetailsDialog::GetTitleColor( ) { return m_titleColorPicker->GetColour( ); }

//--------------

void ColDetailsDialog::Init( )
{
    m_titleLabel = NULL;
    m_titleCheckbox = NULL;
    m_frameCheckbox = NULL;
    m_statusList = NULL;
}

//--------------

bool ColDetailsDialog::IsNameModified( ) { return m_titleLabel->IsModified( ); };

//--------------

void ColDetailsDialog::OnOkClick( wxCommandEvent& event )
{

    m_col->SetTitleString( GetTitle( ) );

    m_col->SetShowFrame( GetShowFrame( ) );
    m_col->SetShowTitle( GetShowTitle( ) );
    m_col->SetShowSubTitle( GetShowSubTitle( ) );

    m_col->GetTitleFrame( )->SetFont( GetTitleFont( ), GetTitleColor( ) );
    // m_col->SetTitleLocation( m_titleLocation );
    m_col->SetCalculateSpacing( CalculateSpacing( ) );
    m_col->SetFixedSpacingSize( GetFixedSpacing( ) );

    event.Skip( );

}

//--------------

void ColDetailsDialog::OnBottomRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationBottom;
    event.Skip( );

}

//--------------

void ColDetailsDialog::OnDefaultRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationDefault;
    event.Skip( );
}

//--------------

void ColDetailsDialog::OnTopRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationTop;
    event.Skip( );
}

//--------------

void ColDetailsDialog::SetCalculateSpacing( bool val )
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

void ColDetailsDialog::SetTitleFont( wxFont font ) { m_titleFontPicker->SetSelectedFont( font ); }

//--------------

void ColDetailsDialog::SetTitleColor( wxColour color ) { m_titleColorPicker->SetColour( color ); }


void ColDetailsDialog::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    event.Skip( );
}




void ColDetailsDialog::OnNameDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_NameFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    event.Skip( );
}


void ColDetailsDialog::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );
    event.Skip( );
}


void ColDetailsDialog::OnNameCheckboxClick( wxCommandEvent& event )
{
    m_titleHelper->UpdateTitleState( );

    m_dialogVerticalSizer->Layout( );
}



void ColDetailsDialog::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    m_titleHelper->UpdateSubTitleState( );
    m_dialogVerticalSizer->Layout( );
};
