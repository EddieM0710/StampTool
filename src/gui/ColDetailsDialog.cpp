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

 // For compilers that support precompilation, includes "wx/wx.h".
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

#include "gui/ColDetailsDialog.h"
#include "gui/LabeledTextBox.h"

// XPM images
// XPM images


/*
 * ColDetailsDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ColDetailsDialog, wxDialog )
;

/*
 * ColDetailsDialog event table definition
 */

BEGIN_EVENT_TABLE( ColDetailsDialog, wxDialog )

// ColDetailsDialog event table entries
EVT_BUTTON( wxID_OK, ColDetailsDialog::OnOkClick )
// ColDetailsDialog event table entries

END_EVENT_TABLE( )


/*
 * ColDetailsDialog constructors
 */

    ColDetailsDialog::ColDetailsDialog( )
{ 
    Init( );
}

ColDetailsDialog::ColDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * ColDetailsDialog creator
 */

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


/*
 * ColDetailsDialog destructor
 */

ColDetailsDialog::~ColDetailsDialog( )
{ 
    // ColDetailsDialog destruction
    // ColDetailsDialog destruction
}


/*
 * Member initialisation
 */

void ColDetailsDialog::Init( )
{ 
    // ColDetailsDialog member initialisation
    m_name = NULL;
    m_titleCheckbox = NULL;
    m_frameCheckbox = NULL;
    m_statusList = NULL;
    // ColDetailsDialog member initialisation
}


/*
 * Control creation for ColDetailsDialog
 */

void ColDetailsDialog::CreateControls( )
{ 

    ColDetailsDialog* detailsPanel = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    detailsPanel->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer2, 1, wxGROW | wxALL, 0 );

    //     wxNotebook* itemNotebook3 = new wxNotebook( detailsPanel, ID_COLNOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    // //>> details panel
    //     wxPanel* detailsPanel = new wxPanel( itemNotebook3, ID_COLNAMEPANEL, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER | wxTAB_TRAVERSAL );
    //     detailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxVERTICAL );
    detailsPanel->SetSizer( detailsVerticalSizer );

    //>> first row ctrls
    wxBoxSizer* firstRowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( firstRowHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_name = new LabeledTextBox( detailsPanel, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    firstRowHorizontalSizer->Add( m_name, 1, wxGROW | wxALL, 5 );


    m_titleCheckbox = new wxCheckBox( detailsPanel, ID_COLTITLECHECKBOX, _( "Show Title" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckbox->SetValue( false );
    firstRowHorizontalSizer->Add( m_titleCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_frameCheckbox = new wxCheckBox( detailsPanel, ID_FRAMECHECKBOX, _( "Show Frame" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_frameCheckbox->SetValue( false );
    firstRowHorizontalSizer->Add( m_frameCheckbox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>> first row ctrls
    //>>second row ctrls
    wxBoxSizer* SecondRowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( SecondRowHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticText* TitleFontStatic = new wxStaticText( detailsPanel, wxID_STATIC, _( "Title Font" ), wxDefaultPosition, wxDefaultSize, 0 );
    SecondRowHorizontalSizer->Add( TitleFontStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_titleFontPicker = new wxFontPickerCtrl( detailsPanel, 12345, 
        *wxNORMAL_FONT, wxDefaultPosition, 
        wxDefaultSize, wxFNTP_DEFAULT_STYLE );
    SecondRowHorizontalSizer->Add( m_titleFontPicker, 5, wxGROW | wxALL, 5 );

    m_titleColorPicker = new wxColourPickerCtrl( detailsPanel, 12346, 
        *wxBLACK, wxDefaultPosition, 
        wxDefaultSize, wxCLRP_DEFAULT_STYLE );
    SecondRowHorizontalSizer->Add( m_titleColorPicker, 1, wxGROW | wxALL, 5 );

    wxButton* defaultButton = new wxButton( detailsPanel, ID_COLDEFAULTFONTBUTTON, _( "Default" ), wxDefaultPosition, wxDefaultSize, 0 );
    SecondRowHorizontalSizer->Add( defaultButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    //>>error list ctrls

    wxBoxSizer* errorListSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( errorListSizer, 2, wxGROW | wxALL, 5 );

    m_statusList = new wxListCtrl( detailsPanel, ID_LISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT | wxLC_EDIT_LABELS | wxSIMPLE_BORDER );
    errorListSizer->Add( m_statusList, 2, wxGROW | wxALL, 5 );
    //<<error list ctrls


    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* itemButton6 = new wxButton( detailsPanel, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton6, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton7 = new wxButton( detailsPanel, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  

    // ColDetailsDialog content construction
}


/*
 * Should we show tooltips?
 */

bool ColDetailsDialog::ShowToolTips( )
{ 
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap ColDetailsDialog::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
// ColDetailsDialog bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // ColDetailsDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon ColDetailsDialog::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
// ColDetailsDialog icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // ColDetailsDialog icon retrieval
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void ColDetailsDialog::OnOkClick( wxCommandEvent& event )
{ 
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in ColDetailsDialog.
        // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in ColDetailsDialog. 
}

void ColDetailsDialog::SetNameModified( bool state ) { m_name->SetModified( state ); };
void ColDetailsDialog::SetDesignTreeID( wxTreeItemId id ) { if ( id.IsOk( ) ) m_designTreeID = id; };
bool ColDetailsDialog::IsNameModified( ) { return m_name->IsModified( ); };

void ColDetailsDialog::SetShowTitle( bool state ) { m_titleCheckbox->SetValue( state ); };
void ColDetailsDialog::SetShowFrame( bool state ) { m_frameCheckbox->SetValue( state ); };
bool ColDetailsDialog::GetShowTitle( ) { return m_titleCheckbox->IsChecked( ); };;
bool ColDetailsDialog::GetShowFrame( ) { return m_frameCheckbox->IsChecked( ); };
