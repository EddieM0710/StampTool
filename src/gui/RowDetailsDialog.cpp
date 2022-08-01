/* 
 * @file  RowDetailsDialog.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022  
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
 */

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

#include "gui/RowDetailsDialog.h"
#include "gui/LabeledTextBox.h"

// XPM images
// XPM images


/*
 * RowDetailsDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( RowDetailsDialog, wxDialog )


/*
 * RowDetailsDialog event table definition
 */

BEGIN_EVENT_TABLE( RowDetailsDialog, wxDialog )

// RowDetailsDialog event table entries
    EVT_BUTTON( wxID_OK, RowDetailsDialog::OnOkClick )
// RowDetailsDialog event table entries

END_EVENT_TABLE()


/*
 * RowDetailsDialog constructors
 */

RowDetailsDialog::RowDetailsDialog()
{
    Init();
}

RowDetailsDialog::RowDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * RowDetailsDialog creator
 */

bool RowDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
// RowDetailsDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
// RowDetailsDialog creation
    return true;
}


/*
 * RowDetailsDialog destructor
 */

RowDetailsDialog::~RowDetailsDialog()
{
// RowDetailsDialog destruction
// RowDetailsDialog destruction
}


/*
 * Member initialisation
 */

void RowDetailsDialog::Init()
{
// RowDetailsDialog member initialisation
    m_name = NULL;
    m_titleCheckbox = NULL;
    m_frameCheckbox = NULL;
    m_statusList = NULL;
// RowDetailsDialog member initialisation
}


/*
 * Control creation for RowDetailsDialog
 */

void RowDetailsDialog::CreateControls()
{    
// RowDetailsDialog content construction

    RowDetailsDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 0, wxGROW|wxALL, 0);

    m_name = new LabeledTextBox( itemDialog1, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    m_name->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    itemBoxSizer1->Add(m_name, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_titleCheckbox = new wxCheckBox( itemDialog1, ID_ROWTITLECHECKBOX, _("Show Title"), wxDefaultPosition, wxDefaultSize, 0 );
    m_titleCheckbox->SetValue(false);
    itemBoxSizer3->Add(m_titleCheckbox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_frameCheckbox = new wxCheckBox( itemDialog1, ID_FRAMECHECKBOX, _("Show Frame"), wxDefaultPosition, wxDefaultSize, 0 );
    m_frameCheckbox->SetValue(false);
    itemBoxSizer3->Add(m_frameCheckbox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer4, 2, wxGROW|wxALL, 5);

    m_statusList = new wxListCtrl( itemDialog1, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxLC_NO_HEADER );
    itemBoxSizer4->Add(m_statusList, 2, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxButton* itemButton6 = new wxButton( itemDialog1, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton7 = new wxButton( itemDialog1, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

// RowDetailsDialog content construction
}


/*
 * Should we show tooltips?
 */

bool RowDetailsDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap RowDetailsDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
// RowDetailsDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
// RowDetailsDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon RowDetailsDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
// RowDetailsDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
// RowDetailsDialog icon retrieval
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void RowDetailsDialog::OnOkClick( wxCommandEvent& event )
{
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in RowDetailsDialog.
    // Before editing this code, remove the block markers.
    event.Skip();
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in RowDetailsDialog. 
}

void RowDetailsDialog::SetNameModified( bool state ) { m_name->SetModified( state ); };
void RowDetailsDialog::SetDesignTreeID(wxTreeItemId id ){ if ( id.IsOk() ) m_designTreeID = id;};
bool RowDetailsDialog::IsNameModified( ) { return m_name->IsModified( ); };
void RowDetailsDialog::SetShowTitle( bool state ) { m_titleCheckbox->SetValue(state); };
void RowDetailsDialog::SetShowFrame( bool state ) { m_frameCheckbox->SetValue(state); };
bool RowDetailsDialog::GetShowTitle(){ return m_titleCheckbox->IsChecked();};;
bool RowDetailsDialog::GetShowFrame(){ return m_frameCheckbox->IsChecked();};
