/*
 * @file  PageDetailsDialog.cpp
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

#include "gui/PageDetailsDialog.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "design/Page.h"
#include "design/Album.h"
#include "design/DesignDefs.h"
#include "utils/FontList.h"

 /*
  * PageDetailsDialog type definition
  */

IMPLEMENT_DYNAMIC_CLASS( PageDetailsDialog, wxDialog )


/*
 * PageDetailsDialog event table definition
 */

    BEGIN_EVENT_TABLE( PageDetailsDialog, wxDialog )
    EVT_BUTTON( wxID_OK, PageDetailsDialog::OnOkClick )
    EVT_BUTTON( ID_TITLEDEFAULTBUTTON, PageDetailsDialog::OnTitleDefaultClick )
    EVT_CHOICE( ID_ORIENTATIONCHOICE, PageDetailsDialog::OnOrientationchoiceSelected )
    END_EVENT_TABLE( )

    ;

/*
 * PageDetailsDialog constructors
 */

PageDetailsDialog::PageDetailsDialog( )
{
    Init( );
}

PageDetailsDialog::PageDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * PageDetailsDialog creator
 */

bool PageDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    //  PageDetailsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    //  PageDetailsDialog creation
    return true;
}


/*
 * PageDetailsDialog destructor
 */

PageDetailsDialog::~PageDetailsDialog( )
{
    //  PageDetailsDialog destruction
    //  PageDetailsDialog destruction
}


/*
 * Member initialisation
 */

void PageDetailsDialog::Init( )
{
    //  PageDetailsDialog member initialisation
    m_name = NULL;
    m_titleCheckbox = NULL;
    m_frameCheckbox = NULL;
    m_name = NULL;
    m_titleCheckbox = NULL;
    m_statusList = NULL;
    //  PageDetailsDialog member initialisation
}


/*
 * Control creation for PageDetailsDialog
 */

void PageDetailsDialog::CreateControls( )
{
    //   std::cout << "PageDetailsDialog" << "\n";

    PageDetailsDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* nameHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( nameHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_name = new LabeledTextBox( theDialog, ID_PAGENAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    nameHorizontalSizer->Add( m_name, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 2, wxGROW | wxALL, 5 );

    wxNotebook* notebook = new wxNotebook( theDialog, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* notebookDetailsPanel = new wxPanel( notebook, ID_NOTEBOOKDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    notebookDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookDetailsPanel->SetSizer( detailsVerticalSizer );

    //>> first row ctrls
    wxBoxSizer* firstRowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( firstRowHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_titleCheckbox = new wxCheckBox( notebookDetailsPanel, ID_SHOWTITLECHECKBOX, _( "Show Title" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckbox->SetValue( false );
    firstRowHorizontalSizer->Add( m_titleCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_frameCheckbox = new wxCheckBox( notebookDetailsPanel, ID_SHOWFRAMECHECKBOX, _( "Show Frame" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_frameCheckbox->SetValue( false );
    firstRowHorizontalSizer->Add( m_frameCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    wxStaticText* orientationStatic = new wxStaticText(
        notebookDetailsPanel, wxID_STATIC, _( "Orientation:" ), wxDefaultPosition, wxDefaultSize, 0 );
    firstRowHorizontalSizer->Add( orientationStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxArrayString m_orientationChoiceStrings( 2, Design::OrientationStrings );
    m_orientationChoice = new wxChoice( notebookDetailsPanel, ID_ORIENTATIONCHOICE, wxDefaultPosition, wxDefaultSize, m_orientationChoiceStrings, 0 );
    m_orientationChoice->SetSelection( Design::AT_Portrait );

    firstRowHorizontalSizer->Add( m_orientationChoice, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    //>> first row ctrls

    //>>second row ctrls

    FontPicker* titleFontPickerHelper = new FontPicker(
        notebookDetailsPanel, detailsVerticalSizer,
        _( "Title Font" ), wxID_STATIC,
        12345, 12345,
        _( "Default" ), ID_TITLEDEFAULTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_titleFontPicker = titleFontPickerHelper->GetFontPickerCtrl( );
    m_titleColorPicker = titleFontPickerHelper->GetColourPickerCtrl( );

    //<<second row ctrls

    //>>error list ctrls
    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( itemBoxSizer3, 2, wxGROW | wxALL, 0 );

    wxArrayString m_statusListStrings;
    m_statusList = new wxListBox( notebookDetailsPanel, ID_ERRORLISTCTRL, wxDefaultPosition, wxDefaultSize, m_statusListStrings, wxLB_SINGLE );
    //m_statusList = new wxListBox( theDialog, ID_ERRORLISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT | wxLC_EDIT_LABELS | wxSIMPLE_BORDER );
    itemBoxSizer3->Add( m_statusList, 2, wxGROW | wxALL, 0 );

    //<<error list ctrls

    notebook->AddPage( notebookDetailsPanel, _( "Details" ) );

    wxPanel* notebookPositionPanel = new wxPanel( notebook, ID_NOTEBOOKPOSITIONPANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    notebookPositionPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* positionVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookPositionPanel->SetSizer( positionVerticalSizer );

    wxBoxSizer* positionHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    positionVerticalSizer->Add( positionHorizontalSizer, 1, wxGROW | wxALL, 0 );

    positionTextCtrl = new wxTextCtrl( notebookPositionPanel, ID_POSITIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxVSCROLL | wxALWAYS_SHOW_SB | wxTE_RICH2 );
    positionTextCtrl->Clear( );
    positionHorizontalSizer->Add( positionTextCtrl, 1, wxGROW | wxALL, 0 );

    notebook->AddPage( notebookPositionPanel, _( "Position" ) );

    notebookHorizontalSizer->Add( notebook, 2, wxGROW | wxALL, 5 );


    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* itemButton9 = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton9, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton10 = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton10, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons    
    //  PageDetailsDialog content construction
}




void PageDetailsDialog::UpdateControls( )
{
    SetName( m_page->GetAttrStr( Design::AT_Name ) );
    SetShowTitle( m_page->GetShowTitle( ) );
    SetShowFrame( m_page->GetShowFrame( ) );
    SetTitleFont( m_page->GetTitleFrame( )->GetFont( ) );
    SetTitleColor( m_page->GetTitleFrame( )->GetColor( ) );
    SetOrientation( m_page->GetOrientation( ) );
    wxListBox* m_statusList;


}


void PageDetailsDialog::SetupDialog( wxTreeItemId treeID )
{
    if ( treeID.IsOk( ) )
    {
        m_designTreeID = treeID;
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( m_designTreeID );
        m_page = ( Design::Page* ) data->GetNodeElement( );
        wxArrayString* errors = m_page->GetErrorArray( );
        if ( !errors->IsEmpty( ) )
        {
            m_statusList->InsertItems( *errors, 0 );
        }

        UpdateControls( );
    }
};



bool PageDetailsDialog::ShowToolTips( )
{
    return true;
}



void PageDetailsDialog::SetTitleFont( wxFont font )
{
    m_titleFontPicker->SetSelectedFont( font );
}

void PageDetailsDialog::SetTitleColor( wxColour color )
{
    m_titleColorPicker->SetColour( color );
}

void PageDetailsDialog::OnOkClick( wxCommandEvent& event )
{
    m_page->SetAttrStr( Design::AT_Name, GetName( ) );
    m_page->SetShowFrame( GetShowFrame( ) );
    m_page->SetShowTitle( GetShowTitle( ) );
    m_page->SetOrientation( GetOrientation( ) );

    m_page->GetTitleFrame( )->SetFont( m_titleFontPicker->GetSelectedFont( ), m_titleColorPicker->GetColour( ) );

    event.Skip( );
}

void PageDetailsDialog::SetName( wxString name )
{
    m_name->SetValue( name );
    m_name->SetModified( false );
}

wxString PageDetailsDialog::GetName( )
{
    return m_name->GetValue( );
}

void PageDetailsDialog::SetNameModified( bool state )
{
    m_name->SetModified( state );
};


bool PageDetailsDialog::IsNameModified( )
{
    return m_name->IsModified( );
};

void PageDetailsDialog::SetShowTitle( bool state )
{
    m_titleCheckbox->SetValue( state );
};
void PageDetailsDialog::SetShowFrame( bool state )
{
    m_frameCheckbox->SetValue( state );
};

bool PageDetailsDialog::GetShowTitle( )
{
    return m_titleCheckbox->IsChecked( );
};;

bool PageDetailsDialog::GetShowFrame( )
{
    return m_frameCheckbox->IsChecked( );
};


void PageDetailsDialog::OnTitleDefaultClick( wxCommandEvent& event )
{
    int ndx = Design::GetAlbum( )->GetFontNdx( Design::AT_TitleFontType );
    Utils::FontList* fontList = GetFontList( );
    wxFont font = fontList->GetFont( ndx );
    wxColour color = fontList->GetColor( ndx );
    m_titleFontPicker->SetSelectedFont( font );
    m_titleColorPicker->SetColour( color );
    event.Skip( );
}


void PageDetailsDialog::OnOrientationchoiceSelected( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_ORIENTATIONCHOICE in PageDetailsDialog.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_ORIENTATIONCHOICE in PageDetailsDialog. 
}
