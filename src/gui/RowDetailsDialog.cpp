/*
 * @file  RowDetailsDialog.cpp
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

#include "gui/RowDetailsDialog.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "gui/TitleHelper.h"
#include "design/Row.h"
 //#include "design/DesignDefs.h"
#include "design/Album.h"
#include "utils/FontList.h"


 /*
  * RowDetailsDialog type definition
  */
IMPLEMENT_DYNAMIC_CLASS( RowDetailsDialog, wxDialog )


/*
 * RowDetailsDialog event table definition
 */
    BEGIN_EVENT_TABLE( RowDetailsDialog, wxDialog )
    EVT_BUTTON( wxID_OK, RowDetailsDialog::OnOkClick )
    EVT_RADIOBUTTON( ID_DEFAULTRADIOBUTTON, RowDetailsDialog::OnDefaultRadioButtonSelected )
    EVT_RADIOBUTTON( ID_TOPRADIOBUTTON, RowDetailsDialog::OnTopRadioButtonSelected )
    EVT_RADIOBUTTON( ID_BOTTOMRADIOBUTTON, RowDetailsDialog::OnBottomRadioButtonSelected )
    //  EVT_BUTTON( ID_DEFAULTFONTBUTTON, RowDetailsDialog::OnTitleDefaultClick )
    EVT_RADIOBUTTON( ID_CALCULATEDRADIOBUTTON, RowDetailsDialog::OnCalculatedClick )
    EVT_RADIOBUTTON( ID_FIXEDRADIOBUTTON, RowDetailsDialog::OnFixedClick )
    END_EVENT_TABLE( )
    ;

/*
 * RowDetailsDialog constructors
 */

RowDetailsDialog::RowDetailsDialog( )
{
    Init( );
}

RowDetailsDialog::RowDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * RowDetailsDialog creator
 */

bool RowDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // RowDetailsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // RowDetailsDialog creation
    return true;
}


/*
 * RowDetailsDialog destructor
 */

RowDetailsDialog::~RowDetailsDialog( )
{
    // RowDetailsDialog destruction
    // RowDetailsDialog destruction
}


/*
 * Member initialisation
 */

void RowDetailsDialog::Init( )
{
    // RowDetailsDialog member initialisation
    m_titleLabel = NULL;
    m_titleCheckbox = NULL;
    m_frameCheckbox = NULL;
    m_statusList = NULL;
    // RowDetailsDialog member initialisation
}


/*
 * Control creation for RowDetailsDialog
 */

void RowDetailsDialog::CreateControls( )
{//
    //std::cout << "RowDetailsDialog" << "\n";
    RowDetailsDialog* theDialog = this;

    m_dialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( m_dialogVerticalSizer );


    // //>> first row ctrls
    wxBoxSizer* firstRowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    m_dialogVerticalSizer->Add( firstRowHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_frameCheckbox = new wxCheckBox( theDialog, ID_FRAMECHECKBOX, _( "Show Frame" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_frameCheckbox->SetValue( false );
    firstRowHorizontalSizer->Add( m_frameCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //@@@

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
        wxCommandEventHandler( RowDetailsDialog::OnNameDefaultClick ) );

    Connect( m_titleHelper->GetSubTitleDefaultButton( )->GetId( ),
        wxEVT_BUTTON,
        wxCommandEventHandler( RowDetailsDialog::OnSubTitleDefaultClick ) );

    Connect( m_titleHelper->GetTitleCheckbox( )->GetId( ),
        wxEVT_CHECKBOX,
        wxCommandEventHandler( RowDetailsDialog::OnNameCheckboxClick ) );

    Connect( m_titleHelper->GetSubTitleCheckbox( )->GetId( ),
        wxEVT_CHECKBOX,
        wxCommandEventHandler( RowDetailsDialog::OnSubTitleCheckboxClick ) );
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
    errorListSizer->Add( m_statusList, 2, wxGROW | wxALL, 0 );
    //<<error list ctrls

    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    m_dialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  
    // RowDetailsDialog content construction
}
Design::TitleLocation  RowDetailsDialog::GetTitleLocation( )
{
    return m_titleLocation;
}


void RowDetailsDialog::SetTitleLocation( )
{

    m_titleLocation = m_row->GetTitleLocation( );
    if ( m_titleLocation == Design::AT_TitleLocationTop )
    {
        m_topButton->SetValue( true );
        // m_bottomButton->SetValue( false );
        // m_defaultButton->SetValue( false );;
    }
    else if ( m_titleLocation == Design::AT_TitleLocationBottom )
    {
        // m_topButton->SetValue( false );
        m_bottomButton->SetValue( true );
        // m_defaultButton->SetValue( false );;
    }

    else //if ( m_titleLocation == Design::AT_TitleLocationDefault )
    {
        // m_topButton->SetValue( false );
        // m_bottomButton->SetValue( false );
        m_defaultButton->SetValue( true );;
    }
}

void RowDetailsDialog::UpdateControls( )
{

    SetTitle( m_row->GetTitleString( ) );
    SetShowTitle( m_row->GetShowTitle( ) );
    SetShowSubTitle( m_row->GetShowSubTitle( ) );
    SetShowFrame( m_row->GetShowFrame( ) );
    SetColor( m_row->GetTitleFrame( )->GetColor( ) );
    SetTitleLocation( );
    SetCalculateSpacing( m_row->CalculateSpacing( ) );
    SetFixedSpacingSize( m_row->GetFixedSpacing( ) );

    wxListBox* m_statusList;
}


void RowDetailsDialog::SetupDialog( wxTreeItemId treeID )
{
    if ( treeID.IsOk( ) )
    {
        m_designTreeID = treeID;
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( m_designTreeID );
        m_row = ( Design::Row* ) data->GetNodeElement( );
        UpdateControls( );
        wxArrayString* errors = m_row->GetErrorArray( );
        // positionTextCtrl->AlwaysShowScrollbars( );
         //positionTextCtrl->WriteText(m_row->DumpFrame( ));
       //  positionTextCtrl->ShowPosition( 0 );

        if ( !errors->IsEmpty( ) )
        {
            m_statusList->InsertItems( *errors, 0 );
        }
    }
};
bool RowDetailsDialog::GetShowTitle( ) { return m_titleCheckbox->IsChecked( ); };;
bool RowDetailsDialog::GetShowSubTitle( ) { return m_subTitleCheckbox->IsChecked( ); };;
bool RowDetailsDialog::GetShowFrame( ) { return m_frameCheckbox->IsChecked( ); };


void RowDetailsDialog::SetNameModified( bool state ) { m_titleLabel->SetModified( state ); };

bool RowDetailsDialog::IsNameModified( ) { return m_titleLabel->IsModified( ); };
void RowDetailsDialog::SetShowTitle( bool state ) { m_titleCheckbox->SetValue( state ); };
void RowDetailsDialog::SetShowSubTitle( bool state ) { m_subTitleCheckbox->SetValue( state ); };
void RowDetailsDialog::SetShowFrame( bool state ) { m_frameCheckbox->SetValue( state ); };

wxString RowDetailsDialog::GetTitle( ) { return m_titleLabel->GetValue( ); };


void RowDetailsDialog::SetTitle( wxString str ) { m_titleLabel->SetValue( str ); };


void RowDetailsDialog::SetFont( wxFont font )
{
    m_titleFontPicker->SetSelectedFont( font );
}

void RowDetailsDialog::SetColor( wxColour color )
{
    m_titleColorPicker->SetColour( color );
}

void RowDetailsDialog::OnOkClick( wxCommandEvent& event )
{
    m_row->SetTitleString( GetTitle( ) );
    m_row->SetShowFrame( GetShowFrame( ) );
    m_row->SetShowTitle( GetShowTitle( ) );
    m_row->SetShowSubTitle( GetShowSubTitle( ) );

    m_row->GetTitleFrame( )->SetFont( m_titleFontPicker->GetSelectedFont( ), m_titleColorPicker->GetColour( ) );
    // m_row->SetTitleLocation( m_titleLocation );
    m_row->SetCalculateSpacing( CalculateSpacing( ) );
    m_row->SetFixedSpacingSize( GetFixedSpacing( ) );
    m_row->SetTitleLocation( GetTitleLocation( ) );

    event.Skip( );

}
void RowDetailsDialog::SetCalculateSpacing( bool val )
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


void RowDetailsDialog::OnTopRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationTop;
    event.Skip( );
}

void RowDetailsDialog::OnBottomRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationBottom;
    event.Skip( );
}



void RowDetailsDialog::OnDefaultRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationDefault;
    event.Skip( );
}


void RowDetailsDialog::OnCalculatedClick( wxCommandEvent& event )
{
    m_positionFixedSize->Enable( false );
    event.Skip( );
}
void RowDetailsDialog::OnFixedClick( wxCommandEvent& event )
{
    m_positionFixedSize->Enable( true );
    event.Skip( );
}



void RowDetailsDialog::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    event.Skip( );
}




void RowDetailsDialog::OnNameDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_NameFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    event.Skip( );
}


void RowDetailsDialog::OnSubTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_SubTitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_subTitleFontPicker->SetSelectedFont( font );
    m_subTitleColorPicker->SetColour( color );
    event.Skip( );
}


void RowDetailsDialog::OnNameCheckboxClick( wxCommandEvent& event )
{
    m_titleHelper->UpdateTitleState( );

    m_dialogVerticalSizer->Layout( );
}



void RowDetailsDialog::OnSubTitleCheckboxClick( wxCommandEvent& event )
{
    m_titleHelper->UpdateSubTitleState( );
    m_dialogVerticalSizer->Layout( );
};
