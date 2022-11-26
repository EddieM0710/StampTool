/**
 * @file StampDetailsDialog.cpp
 * @author Eddie Monroe ()
 * @brief 
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
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

// includes
#include "wx/imaglist.h"
// includes

#include "gui/StampDetailsDialog.h"
#include "gui/LabeledTextBox.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/StampList.h"
#include "Defs.h"
#include "wx/treectrl.h"

// XPM images
// XPM images


/*
 * StampDetailsDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( StampDetailsDialog, wxDialog )


/*
 * StampDetailsDialog event table definition
 */

    BEGIN_EVENT_TABLE( StampDetailsDialog, wxDialog )

    // StampDetailsDialog event table entries
    EVT_BUTTON( ID_REFRESHBUTTON, StampDetailsDialog::OnRefreshButtonClick )
    EVT_BUTTON( wxID_CANCEL, StampDetailsDialog::OnCancelClick )
    EVT_BUTTON( wxID_OK, StampDetailsDialog::OnOkClick )
    // StampDetailsDialog event table entries

    END_EVENT_TABLE( )


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
    m_catNbrCheckbox = NULL;
    m_titleCheckbox = NULL;

    // StampDetailsDialog member initialisation
}


/*
 * Control creation for StampDetailsDialog
 */

void StampDetailsDialog::CreateControls( )
{
    // StampDetailsDialog content construction

    StampDetailsDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 0, wxGROW | wxALL, 0 );

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer4, 0, wxGROW | wxALL, 5 );

    m_catNbr = new LabeledTextBox( itemDialog1, ID_IDLABELTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_catNbr->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer4->Add( m_catNbr, 0, wxGROW | wxALL, 5 );

    m_catNbrCheckbox = new wxCheckBox( itemDialog1, ID_CATNBRCHECKBOX, _( "Show ID" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_catNbrCheckbox->SetValue( false );
    itemBoxSizer4->Add( m_catNbrCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer8, 1, wxGROW | wxALL, 5 );

    m_name = new LabeledTextBox( itemDialog1, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer8->Add( m_name, 1, wxGROW | wxALL, 5 );

    m_titleCheckbox = new wxCheckBox( itemDialog1, ID_TITLECHECKBOX, _( "Show Title" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckbox->SetValue( false );
    itemBoxSizer8->Add( m_titleCheckbox, 0, wxALIGN_LEFT | wxALL, 5 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer3, 0, wxGROW | wxALL, 0 );

    m_height = new LabeledTextBox( itemDialog1, ID_HEIGHTLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_height->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer3->Add( m_height, 1, wxGROW | wxALL, 5 );

    m_width = new LabeledTextBox( itemDialog1, ID_WIDTHLABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_width->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer3->Add( m_width, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* itemButton7 = new wxButton( itemDialog1, ID_REFRESHBUTTON, _( "Refresh from Catalog" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add( itemButton7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer6->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_validate = new wxButton( itemDialog1, ID_VALIDATEBUTTON, _( "Validate" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add( m_validate, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer10, 2, wxGROW | wxALL, 5 );

    m_statusList = new wxListCtrl( itemDialog1, ID_LISTCTRL, wxDefaultPosition, wxSize( 100, 100 ), wxLC_REPORT | wxLC_NO_HEADER );
    itemBoxSizer10->Add( m_statusList, 2, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer12, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add( itemButton13, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add( itemButton14, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // StampDetailsDialog content construction

    m_catNbr->SetLabel( "Catalog Nbr" );
    m_name->SetLabel( "Name" );;
    m_height->SetLabel( "Height" );;
    m_width->SetLabel( "Width" );;
}


/*
 * Should we show tooltips?
 */

bool StampDetailsDialog::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap StampDetailsDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
// StampDetailsDialog bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // StampDetailsDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon StampDetailsDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
// StampDetailsDialog icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // StampDetailsDialog icon retrieval
}

void StampDetailsDialog::SetHeight( wxString height )
{
    m_height->SetValue( height );
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

void StampDetailsDialog::SetShowCatNbr( bool state ) 
{
    m_catNbrCheckbox->SetValue( state );
}

void StampDetailsDialog::SetShowTitle( bool state ) 
{
    m_titleCheckbox->SetValue( state );
}

void StampDetailsDialog::SetDesignTreeID( wxTreeItemId id ) 
{
    if ( id.IsOk( ) ) 
        m_designTreeID = id;
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

bool StampDetailsDialog::GetShowCatNbr( ) 
{
    return m_catNbrCheckbox->IsChecked( );
}

bool StampDetailsDialog::GetShowTitle( ) 
{
    return m_titleCheckbox->IsChecked( );
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


void StampDetailsDialog::RefreshFromCatalog( )
{
    if ( m_designTreeID.IsOk( ) )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* )GetDesignTreeCtrl( )->GetItemData( m_designTreeID );

        Utils::StampLink* link = data->GetStampLink( );
        if ( link )
        {
            wxTreeItemId catTreeID = link->GetCatTreeID( );
            wxXmlNode* node = GetCatalogTreeCtrl( )->GetEntryNode( catTreeID );

            if ( node )
            {
                Catalog::Entry  stamp( node );
                SetHeight( stamp.GetHeight( ) );
                SetHeightModified( );
                SetWidth( stamp.GetWidth( ) );
                SetWidthModified( );
                SetName( stamp.GetName( ) );
                SetNameModified( );
                SetCatNbr( stamp.GetID( ) );
                SetCatNbrModified( );
                wxString label;
                label = GetCatNbr( ) + " - " + GetName( );
                GetDesignTreeCtrl( )->SetItemText( m_designTreeID, label );
            }
        }
    }
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void StampDetailsDialog::OnRefreshButtonClick( wxCommandEvent& event )
{
    RefreshFromCatalog( );
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in StampDetailsDialog.
        // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in StampDetailsDialog. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void StampDetailsDialog::OnCancelClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in StampDetailsDialog.
        // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in StampDetailsDialog. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void StampDetailsDialog::OnOkClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in StampDetailsDialog.
        // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in StampDetailsDialog. 
}

