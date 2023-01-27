/**
 * @file SortOrderDialog.cpp
 * @author Eddie Monroe ( )
 * @brief 
 * @version 0.1
 * @date 2021-02-25
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


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

 
 

#include "Defs.h"
#include "Settings.h"
#include "gui/SortOrderDialog.h"
#include "StampToolApp.h"
#include "catalog/CatalogDefs.h"

 
 

/*
 * SortOrderDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SortOrderDialog, wxDialog )
; // silly business; The above macro screws up the formatter

/*
 * SortOrderDialog event table definition
 */

BEGIN_EVENT_TABLE( SortOrderDialog, wxDialog )

 // SortOrderDialog event table entries
EVT_CHOICE( ID_CHOICE, SortOrderDialog::OnChoiceSelected )
EVT_CHOICE( ID_CHOICE1, SortOrderDialog::OnChoice1Selected )
EVT_CHOICE( ID_CHOICE2, SortOrderDialog::OnChoice2Selected )
EVT_CHOICE( ID_CHOICE3, SortOrderDialog::OnChoice3Selected )
EVT_CHOICE( ID_CHOICE4, SortOrderDialog::OnChoice4Selected )
EVT_BUTTON( wxID_CANCEL, SortOrderDialog::OnCancelClick )
EVT_BUTTON( wxID_OK, SortOrderDialog::OnOkClick )
 // SortOrderDialog event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * SortOrderDialog constructors
 */

SortOrderDialog::SortOrderDialog( )
{ 
    Init( );
}

SortOrderDialog::SortOrderDialog( wxWindow *parent, wxWindowID id, 
                                  const wxString &caption, const wxPoint &pos, 
                                  const wxSize &size, long style )
{ 
    Init( );
    Create( parent, id, caption, pos, size, style );
}

/*
 * SortOrderDialog creator
 */

bool SortOrderDialog::Create( wxWindow *parent, wxWindowID id, 
                              const wxString &caption, const wxPoint &pos, 
                              const wxSize &size, long style )
{ 
     // SortOrderDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    { 
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
     // SortOrderDialog creation
    return true;
}

/*
 * SortOrderDialog destructor
 */

SortOrderDialog::~SortOrderDialog( )
{ 
     // SortOrderDialog destruction
     // SortOrderDialog destruction
}

/*
 * Member initialisation
 */

void SortOrderDialog::Init( )
{ 
     // SortOrderDialog member initialisation
    m_firstSort = NULL;
    m_secondSort = NULL;
    m_thirdSort = NULL;
    m_forthSort = NULL;
    m_fifthSort = NULL;
     // SortOrderDialog member initialisation

    m_dirty = false;

    m_sortStrings.Add( _( "None" ) );
    m_sortStrings.Add( _( "Country" ) );
    m_sortStrings.Add( _( "Period" ) );
    m_sortStrings.Add( _( "Decade" ) );
    m_sortStrings.Add( _( "Year" ) );
    m_sortStrings.Add( _( "Emission" ) );
    m_sortStrings.Add( _( "Status" ) );
    m_sortStrings.Add( _( "Condition" ) );
}

/*
 * Control creation for SortOrderDialog
 */

void SortOrderDialog::CreateControls( )
{ 
     // SortOrderDialog content construction

    SortOrderDialog *itemDialog1 = this;

    wxBoxSizer *itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxTextCtrl *itemTextCtrl3 = new wxTextCtrl( 
        itemDialog1, ID_SORTORDERTEXTCTRL, 
        _( "Select the order of the levels of the tree. Selecting none will remove the level from view. Use the Item view dialog to determine what items will be displayed." ), 
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    itemTextCtrl3->Enable( false );
    itemBoxSizer2->Add( itemTextCtrl3, 2, wxGROW | wxALL, 5 );

    wxBoxSizer *itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer4, 0, wxALIGN_RIGHT | wxALL, 5 );

    wxStaticText *itemStaticText5
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "First Sort" ), 
                            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add( itemStaticText5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 
                        5 );

    wxArrayString m_firstSortStrings;
    m_firstSort = new wxChoice( itemDialog1, ID_CHOICE, wxDefaultPosition, 
                                wxDefaultSize, m_firstSortStrings, 0 );
    m_firstSort->SetName( wxT( "sdfsddf" ) );
    itemBoxSizer4->Add( m_firstSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer *itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer7, 0, wxALIGN_RIGHT | wxALL, 5 );

    wxStaticText *itemStaticText8
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Second Sort" ), 
                            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add( itemStaticText8, 0, wxALIGN_CENTER_VERTICAL | wxALL, 
                        5 );

    wxArrayString m_secondSortStrings;
    m_secondSort = new wxChoice( itemDialog1, ID_CHOICE1, wxDefaultPosition, 
                                 wxDefaultSize, m_secondSortStrings, 0 );
    itemBoxSizer7->Add( m_secondSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer *itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer10, 1, wxALIGN_RIGHT | wxALL, 5 );

    wxStaticText *itemStaticText11
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Third Sort" ), 
                            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add( itemStaticText11, 0, wxALIGN_CENTER_VERTICAL | wxALL, 
                         5 );

    wxArrayString m_thirdSortStrings;
    m_thirdSort = new wxChoice( itemDialog1, ID_CHOICE2, wxDefaultPosition, 
                                wxDefaultSize, m_thirdSortStrings, 0 );
    itemBoxSizer10->Add( m_thirdSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer *itemBoxSizer13 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer13, 1, wxALIGN_RIGHT | wxALL, 5 );

    wxStaticText *itemStaticText14
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Forth Sort" ), 
                            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add( itemStaticText14, 0, wxALIGN_CENTER_VERTICAL | wxALL, 
                         5 );

    wxArrayString m_forthSortStrings;
    m_forthSort = new wxChoice( itemDialog1, ID_CHOICE3, wxDefaultPosition, 
                                wxDefaultSize, m_forthSortStrings, 0 );
    itemBoxSizer13->Add( m_forthSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer *itemBoxSizer16 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer16, 1, wxALIGN_RIGHT | wxALL, 5 );

    wxStaticText *itemStaticText17
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Fifth Sort" ), 
                            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add( itemStaticText17, 0, wxALIGN_CENTER_VERTICAL | wxALL, 
                         5 );

    wxArrayString m_fifthSortStrings;
    m_fifthSort = new wxChoice( itemDialog1, ID_CHOICE4, wxDefaultPosition, 
                                wxDefaultSize, m_fifthSortStrings, 0 );
    itemBoxSizer16->Add( m_fifthSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer *itemBoxSizer19 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer19, 0, wxALIGN_RIGHT | wxALL, 5 );

    wxButton *itemButton20
        = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ), 
                        wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer19->Add( itemButton20, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer19->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton *itemButton22 = new wxButton( 
        itemDialog1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer19->Add( itemButton22, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

     // SortOrderDialog content construction
    wxArrayInt *sortOrder = GetSettings( )->GetSortOrder( );

    m_firstSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 0 )
    { 
        m_firstSort->SetSelection( sortOrder->Item( 0 ) );
    }
    else
    { 
        m_firstSort->SetSelection( Catalog::NT_None );
    }

    m_secondSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 1 )
    { 
        m_secondSort->SetSelection( sortOrder->Item( 1 ) );
    }
    else
    { 
        m_secondSort->SetSelection( Catalog::NT_None  );
    }

    m_thirdSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 2 )
    { 
        m_thirdSort->SetSelection( sortOrder->Item( 2 ) );
    }
    else
    { 
        m_thirdSort->SetSelection( Catalog::NT_None  );
    }

    m_forthSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 3 )
    { 
        m_forthSort->SetSelection( sortOrder->Item( 3 ) );
    }
    else
    { 
        m_forthSort->SetSelection( Catalog::NT_None  );
    }

    m_fifthSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 4 )
    { 
        m_fifthSort->SetSelection( sortOrder->Item( 4 ) );
    }
    else
    { 
        m_fifthSort->SetSelection( Catalog::NT_None  );
    }
}

/*
 * Should we show tooltips?
 */

bool SortOrderDialog::ShowToolTips( )
{ 
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SortOrderDialog::GetBitmapResource( const wxString &name )
{ 
    // Bitmap retrieval
     // SortOrderDialog bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
     // SortOrderDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SortOrderDialog::GetIconResource( const wxString &name )
{ 
    // Icon retrieval
     // SortOrderDialog icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
     // SortOrderDialog icon retrieval
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

void SortOrderDialog::OnChoiceSelected( wxCommandEvent &event )
{ 
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE in
    //SortOrderDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE in
    //SortOrderDialog.
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1
 */

void SortOrderDialog::OnChoice1Selected( wxCommandEvent &event )
{ 
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1 in
    //SortOrderDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1 in
    //SortOrderDialog.
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2
 */

void SortOrderDialog::OnChoice2Selected( wxCommandEvent &event )
{ 
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2 in
    //SortOrderDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2 in
    //SortOrderDialog.
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE3
 */

void SortOrderDialog::OnChoice3Selected( wxCommandEvent &event )
{ 
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE3 in
    //SortOrderDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE3 in
    //SortOrderDialog.
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE4
 */

void SortOrderDialog::OnChoice4Selected( wxCommandEvent &event )
{ 
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE4 in
    //SortOrderDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE4 in
    //SortOrderDialog.
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void SortOrderDialog::OnCancelClick( wxCommandEvent &event )
{ 
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in
    //SortOrderDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in
    //SortOrderDialog.
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void SortOrderDialog::OnOkClick( wxCommandEvent &event )
{ 
    wxArrayInt *sortOrder = GetSettings( )->GetSortOrder( );

    if (  sortOrder->Count( ) >= 1 && sortOrder->Item( 0 ) != m_firstSort->GetSelection( ) )
    { 
    sortOrder->Item( 0 ) = m_firstSort->GetSelection( );
       GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 2 && sortOrder->Item( 1 ) != m_secondSort->GetSelection( ) )
    { 
        sortOrder->Item( 1 ) = m_secondSort->GetSelection( );
        GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 3 && sortOrder->Item( 2 ) != m_thirdSort->GetSelection( ) )
    { 
        sortOrder->Item( 2 ) = m_thirdSort->GetSelection( );
        GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 4 && sortOrder->Item( 3 ) != m_forthSort->GetSelection( ) )
    { 
        sortOrder->Item( 3 ) = m_forthSort->GetSelection( );
       GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 5 && sortOrder->Item( 4 ) != m_fifthSort->GetSelection( ) )
    { 
        sortOrder->Item( 4 ) = m_fifthSort->GetSelection( );
        GetSettings( )->SetDirty( );
    }
    if( GetSettings( )->isDirty( ) )  
        GetSettings( )->Save( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in
    //SortOrderDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in
    //SortOrderDialog.
}
