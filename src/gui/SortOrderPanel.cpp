/**
 * @file SortOrderPanel.cpp
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
 */



#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif




#include "Defs.h"
#include "Settings.h"
#include "gui/SortOrderPanel.h"
 //#include "StampToolApp.h"
#include "catalog/CatalogDefs.h"




/*
 * SortOrderPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SortOrderPanel, wxPanel )
; // silly business; The above macro screws up the formatter

/*
 * SortOrderPanel event table definition
 */

BEGIN_EVENT_TABLE( SortOrderPanel, wxPanel )
EVT_CHOICE( ID_CHOICE, SortOrderPanel::OnChoiceSelected )
EVT_CHOICE( ID_CHOICE1, SortOrderPanel::OnChoice1Selected )
EVT_CHOICE( ID_CHOICE2, SortOrderPanel::OnChoice2Selected )
EVT_CHOICE( ID_CHOICE3, SortOrderPanel::OnChoice3Selected )
EVT_CHOICE( ID_CHOICE4, SortOrderPanel::OnChoice4Selected )
END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * SortOrderPanel constructors
 */

SortOrderPanel::SortOrderPanel( )
{
    Init( );
}

SortOrderPanel::SortOrderPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 * SortOrderPanel creator
 */

bool SortOrderPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos,
    const wxSize& size, long style )
{
    // SortOrderPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // SortOrderPanel creation
    return true;
}

/*
 * SortOrderPanel destructor
 */

SortOrderPanel::~SortOrderPanel( )
{
    // SortOrderPanel destruction
    // SortOrderPanel destruction
}

/*
 * Member initialisation
 */

void SortOrderPanel::Init( )
{
    // SortOrderPanel member initialisation
    m_firstSort = NULL;
    m_secondSort = NULL;
    m_thirdSort = NULL;
    m_forthSort = NULL;
    m_fifthSort = NULL;
    // SortOrderPanel member initialisation

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
 * Control creation for SortOrderPanel
 */

void SortOrderPanel::CreateControls( )
{
    std::cout << "SortOrderPanel" << "\n";

    SortOrderPanel* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxTextCtrl* itemTextCtrl3 = new wxTextCtrl(
        itemDialog1, ID_SORTORDERTEXTCTRL,
        _( "Select the order of the levels of the tree. Selecting none will remove the level from view. Use the Item view dialog to determine what items will be displayed." ),
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    itemTextCtrl3->Enable( false );
    itemBoxSizer2->Add( itemTextCtrl3, 2, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxStaticText* itemStaticText5
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "First Sort" ),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add( itemStaticText5, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        5 );

    wxArrayString m_firstSortStrings;
    m_firstSort = new wxChoice( itemDialog1, ID_CHOICE, wxDefaultPosition,
        wxDefaultSize, m_firstSortStrings, 0 );
    m_firstSort->SetName( wxT( "sdfsddf" ) );
    itemBoxSizer4->Add( m_firstSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer7, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxStaticText* itemStaticText8
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Second Sort" ),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add( itemStaticText8, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        5 );

    wxArrayString m_secondSortStrings;
    m_secondSort = new wxChoice( itemDialog1, ID_CHOICE1, wxDefaultPosition,
        wxDefaultSize, m_secondSortStrings, 0 );
    itemBoxSizer7->Add( m_secondSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer10, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxStaticText* itemStaticText11
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Third Sort" ),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add( itemStaticText11, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        5 );

    wxArrayString m_thirdSortStrings;
    m_thirdSort = new wxChoice( itemDialog1, ID_CHOICE2, wxDefaultPosition,
        wxDefaultSize, m_thirdSortStrings, 0 );
    itemBoxSizer10->Add( m_thirdSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer13, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxStaticText* itemStaticText14
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Forth Sort" ),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add( itemStaticText14, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        5 );

    wxArrayString m_forthSortStrings;
    m_forthSort = new wxChoice( itemDialog1, ID_CHOICE3, wxDefaultPosition,
        wxDefaultSize, m_forthSortStrings, 0 );
    itemBoxSizer13->Add( m_forthSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer16, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxStaticText* itemStaticText17
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Fifth Sort" ),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add( itemStaticText17, 0, wxALIGN_CENTER_VERTICAL | wxALL,
        5 );

    wxArrayString m_fifthSortStrings;
    m_fifthSort = new wxChoice( itemDialog1, ID_CHOICE4, wxDefaultPosition,
        wxDefaultSize, m_fifthSortStrings, 0 );
    itemBoxSizer16->Add( m_fifthSort, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // wxBoxSizer *itemBoxSizer19 = new wxBoxSizer( wxHORIZONTAL );
    // itemBoxSizer2->Add( itemBoxSizer19, 0, wxALIGN_RIGHT | wxALL, 5 );

    // wxButton *itemButton20
    //     = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ), 
    //                     wxDefaultPosition, wxDefaultSize, 0 );
    // itemBoxSizer19->Add( itemButton20, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // itemBoxSizer19->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // wxButton *itemButton22 = new wxButton( 
    //     itemDialog1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    // itemBoxSizer19->Add( itemButton22, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

     // SortOrderPanel content construction
    wxArrayInt* sortOrder = GetSettings( )->GetSortOrder( );

    m_firstSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 0 )
    {
        m_firstSort->SetSelection( sortOrder->Item( 0 ) );
    }
    else
    {
        m_firstSort->SetSelection( 0 );
    }

    m_secondSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 1 )
    {
        m_secondSort->SetSelection( sortOrder->Item( 1 ) );
    }
    else
    {
        m_secondSort->SetSelection( 0 );
    }

    m_thirdSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 2 )
    {
        m_thirdSort->SetSelection( 0 );
    }
    else
    {
        m_thirdSort->SetSelection( 0 );
    }

    m_forthSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 3 )
    {
        m_forthSort->SetSelection( sortOrder->Item( 3 ) );
    }
    else
    {
        m_forthSort->SetSelection( 0 );
    }

    m_fifthSort->Set( m_sortStrings );
    if ( sortOrder->GetCount( ) > 4 )
    {
        m_fifthSort->SetSelection( sortOrder->Item( 4 ) );
    }
    else
    {
        m_fifthSort->SetSelection( 0 );
    }
}



bool SortOrderPanel::ShowToolTips( )
{
    return true;
}



/*
 *   ID_CHOICE
 */

void SortOrderPanel::OnChoiceSelected( wxCommandEvent& event )
{
    event.Skip( );
}

/*
 *   ID_CHOICE1
 */

void SortOrderPanel::OnChoice1Selected( wxCommandEvent& event )
{
    event.Skip( );
}

/*
 *   ID_CHOICE2
 */

void SortOrderPanel::OnChoice2Selected( wxCommandEvent& event )
{
    event.Skip( );
}

/*
 *   ID_CHOICE3
 */

void SortOrderPanel::OnChoice3Selected( wxCommandEvent& event )
{
    event.Skip( );
}

/*
 *   ID_CHOICE4
 */

void SortOrderPanel::OnChoice4Selected( wxCommandEvent& event )
{
    event.Skip( );
}

/*
 *   wxID_CANCEL
 */

void SortOrderPanel::OnOkClick( )
{
    wxArrayInt* sortOrder = GetSettings( )->GetSortOrder( );

    if ( sortOrder->Count( ) >= 1 && sortOrder->Item( 0 ) != m_firstSort->GetSelection( ) )
    {
        int sel = m_firstSort->GetSelection( );
        if ( sel == 0 )
        {
            sel = Catalog::NT_None;
        }
        sortOrder->Item( 0 ) = sel;
        GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 2 && sortOrder->Item( 1 ) != m_secondSort->GetSelection( ) )
    {
        int sel = m_secondSort->GetSelection( );
        if ( sel == 0 )
        {
            sel = Catalog::NT_None;
        }
        sortOrder->Item( 1 ) = sel;
        GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 3 && sortOrder->Item( 2 ) != m_thirdSort->GetSelection( ) )
    {
        int sel = m_thirdSort->GetSelection( );
        if ( sel == 0 )
        {
            sel = Catalog::NT_None;
        }
        sortOrder->Item( 2 ) = sel;
        GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 4 && sortOrder->Item( 3 ) != m_forthSort->GetSelection( ) )
    {
        int sel = m_forthSort->GetSelection( );
        if ( sel = 0 )
        {
            sel = Catalog::NT_None;
        }
        sortOrder->Item( 3 ) = sel;
        GetSettings( )->SetDirty( );
    }
    if ( sortOrder->Count( ) >= 5 && sortOrder->Item( 4 ) != m_fifthSort->GetSelection( ) )
    {
        int sel = m_fifthSort->GetSelection( );
        if ( sel == 0 )
        {
            sel = Catalog::NT_None;
        }
        sortOrder->Item( 4 ) = sel;
        GetSettings( )->SetDirty( );
    }

}
