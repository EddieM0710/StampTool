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
#include "design/Column.h"


 /*
  * ColDetailsDialog type definition
  */

IMPLEMENT_DYNAMIC_CLASS( ColDetailsDialog, wxDialog )
;

/*
 * ColDetailsDialog event table definition
 */

BEGIN_EVENT_TABLE( ColDetailsDialog, wxDialog )
EVT_BUTTON( wxID_OK, ColDetailsDialog::OnOkClick )
END_EVENT_TABLE( )


ColDetailsDialog::ColDetailsDialog( )
{
    Init( );
}

ColDetailsDialog::ColDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

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


ColDetailsDialog::~ColDetailsDialog( )
{
}


void ColDetailsDialog::Init( )
{
    m_name = NULL;
    m_titleCheckbox = NULL;
    m_frameCheckbox = NULL;
    m_statusList = NULL;
}

void ColDetailsDialog::CreateControls( )
{

    ColDetailsDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 1, wxGROW | wxALL, 0 );

    //     wxNotebook* itemNotebook3 = new wxNotebook( theDialog, ID_COLNOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    // //>> details panel
    //     wxPanel* theDialog = new wxPanel( itemNotebook3, ID_COLNAMEPANEL, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER | wxTAB_TRAVERSAL );
    //     theDialog->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

   // wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
   // theDialog->SetSizer( detailsVerticalSizer );

    wxBoxSizer* nameHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( nameHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_name = new LabeledTextBox( theDialog, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    nameHorizontalSizer->Add( m_name, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 2, wxGROW | wxALL, 5 );

    wxNotebook* notebook = new wxNotebook( theDialog, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* notebookDetailsPanel = new wxPanel( notebook, ID_NOTEBOOKDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    notebookDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    notebookDetailsPanel->SetSizer( detailsVerticalSizer );

    //>> first row ctrls


    wxBoxSizer* firstRowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( firstRowHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_titleCheckbox = new wxCheckBox( notebookDetailsPanel, ID_COLTITLECHECKBOX, _( "Show Title" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckbox->SetValue( false );
    firstRowHorizontalSizer->Add( m_titleCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_frameCheckbox = new wxCheckBox( notebookDetailsPanel, ID_FRAMECHECKBOX, _( "Show Frame" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_frameCheckbox->SetValue( false );
    firstRowHorizontalSizer->Add( m_frameCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>> first row ctrls

    //>>second row ctrls
    FontPicker* titleFontPickerHelper = new FontPicker(
        notebookDetailsPanel, detailsVerticalSizer,
        _( "Title Font" ), wxID_STATIC,
        12345, 12346,
        _( "Default" ), ID_COLDEFAULTFONTBUTTON,
        *wxNORMAL_FONT, *wxBLACK );
    m_titleFontPicker = titleFontPickerHelper->GetFontPickerCtrl( );
    m_titleColorPicker = titleFontPickerHelper->GetColourPickerCtrl( );

    //>>error list ctrls

    wxBoxSizer* errorListSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( errorListSizer, 2, wxGROW | wxALL, 5 );

    m_statusList = new wxListBox( notebookDetailsPanel, ID_LISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT | wxLC_EDIT_LABELS | wxSIMPLE_BORDER );
    errorListSizer->Add( m_statusList, 2, wxGROW | wxALL, 5 );
    //<<error list ctrls

    notebook->AddPage( notebookDetailsPanel, _( "Details" ) );

    wxPanel* notebookPositionPanel = new wxPanel( notebook, ID_NOTEBOOKPOSITIONPANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
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

    wxButton* itemButton6 = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton6, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton7 = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  

}


void ColDetailsDialog::UpdateControls( )
{
    SetName( m_col->GetAttrStr( Design::AT_Name ) );
    SetShowTitle( m_col->GetShowTitle( ) );
    SetTitleFont( m_col->GetTitleFont( ) );
    SetTitleColor( m_col->GetTitleColor( ) );

}


void ColDetailsDialog::SetupDialog( wxTreeItemId treeID )
{
    if ( treeID.IsOk( ) )
    {
        m_designTreeID = treeID;
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetDesignTreeCtrl( )->GetItemData( m_designTreeID );
        m_col = ( Design::Column* ) data->GetNodeElement( );

        wxArrayString* errors = m_col->GetErrorArray( );
        positionTextCtrl->AlwaysShowScrollbars( );
        // m_row->DumpRow( positionTextCtrl );
        positionTextCtrl->ShowPosition( 0 );

        if ( !errors->IsEmpty( ) )
        {
            m_statusList->InsertItems( *errors, 0 );
        }
    }
};

bool ColDetailsDialog::ShowToolTips( )
{
    return true;
}

void ColDetailsDialog::OnOkClick( wxCommandEvent& event )
{
    event.Skip( );
}

void ColDetailsDialog::SetNameModified( bool state ) { m_name->SetModified( state ); };
bool ColDetailsDialog::IsNameModified( ) { return m_name->IsModified( ); };

void ColDetailsDialog::SetShowTitle( bool state ) { m_titleCheckbox->SetValue( state ); };
void ColDetailsDialog::SetShowFrame( bool state ) { m_frameCheckbox->SetValue( state ); };
bool ColDetailsDialog::GetShowTitle( ) { return m_titleCheckbox->IsChecked( ); };;
bool ColDetailsDialog::GetShowFrame( ) { return m_frameCheckbox->IsChecked( ); };
void ColDetailsDialog::SetTitleFont( wxFont font ) { m_titleFontPicker->SetSelectedFont( font ); }
void ColDetailsDialog::SetTitleColor( wxColour color ) { m_titleColorPicker->SetColour( color ); }
