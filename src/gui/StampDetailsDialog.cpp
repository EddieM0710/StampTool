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
 **************************************************/


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
#include "Defs.h"


 /*
  * StampDetailsDialog type definition
  */

IMPLEMENT_DYNAMIC_CLASS( StampDetailsDialog, wxDialog )


/*
 * StampDetailsDialog event table definition
 */

    BEGIN_EVENT_TABLE( StampDetailsDialog, wxDialog )
    EVT_BUTTON( ID_REFRESHBUTTON, StampDetailsDialog::OnRefreshButtonClick )
    EVT_BUTTON( wxID_CANCEL, StampDetailsDialog::OnCancelClick )
    EVT_BUTTON( wxID_OK, StampDetailsDialog::OnOkClick )
    EVT_CHECKBOX( ID_CATNBRCHECKBOX, StampDetailsDialog::OnCatNbrCheckboxClicked )
    EVT_BUTTON( ID_STAMPNBRDEFAULTFONTBUTTON, StampDetailsDialog::OnNbrDefaultClick )
    EVT_BUTTON( ID_STAMPNAMEDEFAULTFONTBUTTON, StampDetailsDialog::OnNameDefaultClick )
    EVT_RADIOBUTTON( ID_DEFAULTRADIOBUTTON, StampDetailsDialog::OnDefaultRadioButtonSelected )
    EVT_RADIOBUTTON( ID_TOPRADIOBUTTON, StampDetailsDialog::OnTopRadioButtonSelected )
    EVT_RADIOBUTTON( ID_BOTTOMRADIOBUTTON, StampDetailsDialog::OnBottomRadioButtonSelected )
    //EVT_RADIOBUTTON( ID_LEFTRADIOBUTTON, StampDetailsDialog::OnLeftRadioButtonSelected )
    //EVT_RADIOBUTTON( ID_RIGHTRADIOBUTTON, StampDetailsDialog::OnRightRadioButtonSelected )
    END_EVENT_TABLE( )

    void StampDetailsDialog::OnCatNbrCheckboxClicked( wxCommandEvent& event )
{

};

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
    // StampDetailsDialog content construction

    StampDetailsDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 0, wxGROW | wxALL, 0 );

    // wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    // theDialogVerticalSizer->Add( detailsVerticalSizer, 0, wxGROW | wxALL, 5 );

    m_catNbr = new LabeledTextBox( theDialog/*detailsPanel*/, ID_IDLABELTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_catNbr->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    theDialogVerticalSizer->Add( m_catNbr, 0, wxGROW | wxALL, 5 );

    //wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxVERTICAL );
    //detailsVerticalSizer->Add( itemBoxSizer8, 1, wxGROW | wxALL, 5 );

    m_name = new LabeledTextBox( theDialog/*detailsPanel*/, ID_NAMELABELEDTEXTBOX1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    theDialogVerticalSizer->Add( m_name, 0, wxGROW | wxALL, 5 );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 2, wxGROW | wxALL, 5 );

    wxNotebook* notebook = new wxNotebook( theDialog, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* notebookDetailsPanel = new wxPanel( notebook, ID_NOTEBOOKDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    notebookDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookDetailsPanel->SetSizer( detailsVerticalSizer );

    wxBoxSizer* checkBoxHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( checkBoxHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_nbrCheckbox = new wxCheckBox( notebookDetailsPanel/*detailsPanel*/, ID_CATNBRCHECKBOX, _( "Show ID" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_nbrCheckbox->SetValue( false );
    checkBoxHorizontalSizer->Add( m_nbrCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );

    m_titleCheckbox = new wxCheckBox( notebookDetailsPanel/*detailsPanel*/, ID_TITLECHECKBOX, _( "Show Title" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckbox->SetValue( false );
    checkBoxHorizontalSizer->Add( m_titleCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );

    FontPicker* catNbrFontPickerHelper = new FontPicker(
        notebookDetailsPanel, detailsVerticalSizer,
        _( "Catalog Nbr Font" ), wxID_STATIC,
        ID_STAMPNBRFONTPICKER, ID_STAMPNBRCOLORPICKER,
        _( "Default" ), ID_STAMPNBRDEFAULTFONTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_nbrFontPicker = catNbrFontPickerHelper->GetFontPickerCtrl( );
    m_nbrColorPicker = catNbrFontPickerHelper->GetColourPickerCtrl( );

    FontPicker* nameFontPickerHelper = new FontPicker(
        notebookDetailsPanel, detailsVerticalSizer,
        _( "Name Font" ), wxID_STATIC,
        ID_STAMPNAMEFONTPICKER, ID_STAMPNAMECOLORPICKER,
        _( "Default" ), ID_STAMPNAMEDEFAULTFONTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_nameFontPicker = nameFontPickerHelper->GetFontPickerCtrl( );
    m_nameColorPicker = nameFontPickerHelper->GetColourPickerCtrl( );



    m_TitleLocationBox = new wxStaticBox( notebookDetailsPanel, wxID_ANY, _( "Member Title Location" ) );
    m_titleLocationVSizer = new wxStaticBoxSizer( m_TitleLocationBox, wxVERTICAL );
    detailsVerticalSizer->Add( m_titleLocationVSizer, 1, wxGROW | wxALL, 5 );

    m_titleLocationHSizer = new wxBoxSizer( wxHORIZONTAL );
    m_titleLocationVSizer->Add( m_titleLocationHSizer, 1, wxGROW | wxALL, 0 );

    m_topButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_DEFAULTRADIOBUTTON, _( "Default" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_topButton->SetValue( true );
    m_titleLocationHSizer->Add( m_topButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_bottomButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_TOPRADIOBUTTON, _( "Top" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_bottomButton->SetValue( false );
    m_titleLocationHSizer->Add( m_bottomButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // m_leftButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_BOTTOMRADIOBUTTON, _( "Bottom" ), wxDefaultPosition, wxDefaultSize, 0 );
    // m_leftButton->SetValue( false );
    // m_titleLocationHSizer->Add( m_leftButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // m_rightButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_LEFTRADIOBUTTON, _( "Left" ), wxDefaultPosition, wxDefaultSize, 0 );
    // m_rightButton->SetValue( false );
    // m_titleLocationHSizer->Add( m_rightButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_defaultButton = new wxRadioButton( m_titleLocationVSizer->GetStaticBox( ), ID_RIGHTRADIOBUTTON, _( "Right" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_defaultButton->SetValue( false );
    m_titleLocationHSizer->Add( m_defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );



    m_imagePath = new LabeledTextBox( notebookDetailsPanel/*detailsPanel*/, ID_IMAGEPATHLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_imagePath->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    detailsVerticalSizer->Add( m_imagePath, 0, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( itemBoxSizer3, 0, wxGROW | wxALL, 0 );

    m_height = new LabeledTextBox( notebookDetailsPanel/*detailsPanel*/, ID_HEIGHTLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_height->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer3->Add( m_height, 1, wxGROW | wxALL, 5 );

    m_width = new LabeledTextBox( notebookDetailsPanel/*detailsPanel*/, ID_WIDTHLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_width->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer3->Add( m_width, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( itemBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* itemButton7 = new wxButton( notebookDetailsPanel/*detailsPanel*/, ID_REFRESHBUTTON, _( "Refresh from Catalog" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add( itemButton7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer6->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_validate = new wxButton( notebookDetailsPanel/*detailsPanel*/, ID_VALIDATEBUTTON, _( "Validate" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add( m_validate, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( itemBoxSizer10, 2, wxGROW | wxALL, 5 );


    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( notebookDetailsPanel, ID_LISTCTRL, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );


    //m_statusList = new wxListBox( theDialog/*detailsPanel*/, ID_LISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT | wxLC_NO_HEADER );
    itemBoxSizer10->Add( m_statusList, 2, wxGROW | wxALL, 5 );

    //wxBoxSizer* itemBoxSizer14 = new wxBoxSizer( wxHORIZONTAL );
    //detailsVerticalSizer->Add( itemBoxSizer14, 2, wxGROW | wxALL, 5 );

    //<<error list ctrls

    notebook->AddPage( notebookDetailsPanel, _( "Details" ) );

    wxPanel* notebookPositionPanel = new wxPanel( notebook, ID_NOTEBOOKPOSITIONPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    notebookPositionPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* positionVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookPositionPanel->SetSizer( positionVerticalSizer );

    wxBoxSizer* positionHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    positionVerticalSizer->Add( positionHorizontalSizer, 1, wxGROW | wxALL, 0 );

    positionTextCtrl = new wxTextCtrl( notebookPositionPanel, ID_POSITIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxVSCROLL | wxALWAYS_SHOW_SB | wxTE_RICH2 );
    //positionTextCtrl->Clear( );
    positionHorizontalSizer->Add( positionTextCtrl, 1, wxGROW | wxALL, 0 );

    notebook->AddPage( notebookPositionPanel, _( "Position" ) );

    notebookHorizontalSizer->Add( notebook, 2, wxGROW | wxALL, 5 );

    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  

    m_catNbr->SetLabel( "Catalog Nbr" );
    m_name->SetLabel( "Name" );
    m_height->SetLabel( "Height" );
    m_width->SetLabel( "Width" );
    m_imagePath->SetLabel( "ImageName" );
}

void StampDetailsDialog::SetTitleLayoutLocation( )
{

    m_titleLocation = m_stamp->GetTitleLayoutLocation( );
    if ( m_titleLocation == Design::AT_TitleLocationTop )
    {
        m_topButton->SetValue( true );
        m_bottomButton->SetValue( false );
        // m_leftButton->SetValue( false );;
        // m_rightButton->SetValue( false );;
        m_defaultButton->SetValue( false );;
    }
    else if ( m_titleLocation == Design::AT_TitleLocationBottom )
    {
        m_topButton->SetValue( false );
        m_bottomButton->SetValue( true );
        // m_leftButton->SetValue( false );;
        // m_rightButton->SetValue( false );;
        m_defaultButton->SetValue( false );;
    }
    // else if ( m_titleLocation == Design::AT_TitleLocationLeft )
    // {
    //     m_topButton->SetValue( false );
    //     m_bottomButton->SetValue( false );
    //     m_leftButton->SetValue( true );;
    //     m_rightButton->SetValue( false );;
    //     m_defaultButton->SetValue( false );;
    // }
    // else if ( m_titleLocation == Design::AT_TitleLocationRight )
    // {
    //     m_topButton->SetValue( false );
    //     m_bottomButton->SetValue( false );
    //     m_leftButton->SetValue( false );;
    //     m_rightButton->SetValue( true );;
    //     m_defaultButton->SetValue( false );;
    // }
    else if ( m_titleLocation == Design::AT_TitleLocationDefault )
    {
        m_topButton->SetValue( false );
        m_bottomButton->SetValue( false );
        // m_leftButton->SetValue( false );;
        // m_rightButton->SetValue( false );;
        m_defaultButton->SetValue( true );;
    }
}

void StampDetailsDialog::UpdateControls( )
{
    SetHeight( m_stamp->GetStampHeightStr( ) );
    SetWidth( m_stamp->GetStampWidthStr( ) );
    SetCatNbr( m_stamp->GetAttrStr( Design::AT_CatNbr ) );
    SetName( m_stamp->GetAttrStr( Design::AT_Name ) );
    SetShowNbr( m_stamp->GetShowNbr( ) );
    SetShowTitle( m_stamp->GetShowTitle( ) );
    SetNbrFont( m_stamp->GetFont( Design::AT_NbrFontType ) );
    SetNameFont( m_stamp->GetFont( Design::AT_NameFontType ) );
    SetNbrColor( m_stamp->GetColor( Design::AT_NbrFontType ) );
    SetNameColor( m_stamp->GetColor( Design::AT_NameFontType ) );
    m_stamp->GetTitleLayoutLocation( );


}


void StampDetailsDialog::SetupDialog( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        m_designTreeID = id;
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetDesignTreeCtrl( )->GetItemData( m_designTreeID );
        m_stamp = ( Design::Stamp* ) data->GetNodeElement( );
        UpdateControls( );

        wxArrayString* errors = m_stamp->GetErrorArray( );
        positionTextCtrl->AlwaysShowScrollbars( );
        m_stamp->DumpStamp( positionTextCtrl );
        positionTextCtrl->ShowPosition( 0 );

        if ( !errors->IsEmpty( ) )
        {
            m_statusList->InsertItems( *errors, 0 );
        }
        positionTextCtrl->ShowPosition( 0 );
    }
};

void StampDetailsDialog::RefreshFromCatalog( )
{
    if ( m_designTreeID.IsOk( ) )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetDesignTreeCtrl( )->GetItemData( m_designTreeID );

        Utils::StampLink* link = data->GetStampLink( );
        if ( link )
        {
            wxTreeItemId catTreeID = link->GetCatTreeID( );
            wxXmlNode* node = GetAlbumPageTreeCtrl( )->GetItemNode( catTreeID );

            if ( node )
            {
                Catalog::CatalogSectionData* catalogSectionData = GetCatalogSectionData( );
                Catalog::Entry  stamp( node );
                SetHeight( stamp.GetHeight( ) );
                SetWidth( stamp.GetWidth( ) );
                SetName( stamp.GetName( ) );
                SetCatNbr( stamp.GetID( ) );
                wxString label;
                label = GetCatNbr( ) + " - " + GetName( );
                GetDesignTreeCtrl( )->SetItemText( m_designTreeID, label );
            }
        }
    }
}


bool StampDetailsDialog::ShowToolTips( )
{
    return true;
}


void StampDetailsDialog::SetHeight( wxString height )
{
    m_height->SetValue( height );
    m_height->SetModified( false );
}

void StampDetailsDialog::SetImageFilename( wxString path )
{
    m_imagePath->SetValue( path );
    m_height->SetModified( false );
}
void StampDetailsDialog::SetWidth( wxString width )
{
    m_width->SetValue( width );
    m_width->SetModified( false );
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

void StampDetailsDialog::SetHeightModified( bool state )
{
    m_height->SetModified( state );
}

void StampDetailsDialog::SetWidthModified( bool state )
{
    m_width->SetModified( state );
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

    // m_stamp->ReportLayout( );


    if ( IsIDModified( ) )
    {
        m_stamp->SetAttrStr( Design::AT_CatNbr, GetCatNbr( ) );
    }
    if ( IsNameModified( ) )
    {
        m_stamp->SetAttrStr( Design::AT_Name, GetName( ) );
    }
    if ( IsHeightModified( ) )
    {
        m_stamp->SetStampHeight( GetHeight( ) );
    }
    if ( IsWidthModified( ) )
    {
        m_stamp->SetStampWidth( GetWidth( ) );
    }
    m_stamp->SetShowNbr( GetShowNbr( ) );
    m_stamp->SetShowTitle( GetShowTitle( ) );

    m_stamp->SetFont( Design::AT_NameFontType, GetNameFont( ), GetNameColor( ) );
    m_stamp->SetFont( Design::AT_NameFontType, GetNbrFont( ), GetNbrColor( ) );

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


// void StampDetailsDialog::OnLeftRadioButtonSelected( wxCommandEvent& event )
// {
//     m_titleLocation = Design::AT_TitleLocationLeft;
//     event.Skip( );
// }


// void StampDetailsDialog::OnRightRadioButtonSelected( wxCommandEvent& event )
// {
//     m_titleLocation = Design::AT_TitleLocationRight;
//     event.Skip( );
// }

void StampDetailsDialog::OnDefaultRadioButtonSelected( wxCommandEvent& event )
{
    m_titleLocation = Design::AT_TitleLocationDefault;
    event.Skip( );
}

void StampDetailsDialog::OnNbrDefaultClick( wxCommandEvent& event )
{
    m_stamp->MakeDefaultFont( Design::AT_NbrFontType );
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