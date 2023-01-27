/* 
 * @file SettingsPanel.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-11
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

// includes
// includes

#include "gui/SettingsPanel.h"

// XPM images
// XPM images


/*
 * SettingsPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SettingsPanel, wxPanel )


/*
 * SettingsPanel event table definition
 */

BEGIN_EVENT_TABLE( SettingsPanel, wxPanel )

// SettingsPanel event table entries
    EVT_BUTTON( wxID_CANCEL, SettingsPanel::OnCancelClick )
    EVT_BUTTON( wxID_OK, SettingsPanel::OnOkClick )
// SettingsPanel event table entries

END_EVENT_TABLE( )


/*
 * SettingsPanel constructors
 */

SettingsPanel::SettingsPanel( )
{ 
    Init( );
}

SettingsPanel::SettingsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}


/*
 * SettingsPanel creator
 */

bool SettingsPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
// SettingsPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    { 
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
// SettingsPanel creation
    return true;
}


/*
 * SettingsPanel destructor
 */

SettingsPanel::~SettingsPanel( )
{ 
// SettingsPanel destruction
// SettingsPanel destruction
}


/*
 * Member initialisation
 */

void SettingsPanel::Init( )
{ 
// SettingsPanel member initialisation
    m_imageDirectory = NULL;
    m_country = NULL;
    m_catalog = NULL;
    m_loadLastFileAtStartUp = NULL;
// SettingsPanel member initialisation
}


/*
 * Control creation for SettingsPanel
 */

void SettingsPanel::CreateControls( )
{    
// SettingsPanel content construction

    SettingsPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 1, wxGROW | wxALL, 5 );

    m_imageDirectory = new LabeledTextBox( itemPanel1, ID_IMAGEDIRECTORTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
    itemBoxSizer1->Add( m_imageDirectory, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer3, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer7, 1, wxGROW | wxALL, 5 );

    m_country = new LabeledTextBox( itemPanel1, ID_COUNTRYTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
    itemBoxSizer7->Add( m_country, 1, wxGROW | wxALL, 5 );

    m_catalog = new LabeledTextBox( itemPanel1, ID_CATALOGTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
    itemBoxSizer7->Add( m_catalog, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer10, 1, wxGROW | wxALL, 5 );

    m_loadLastFileAtStartUp = new wxCheckBox( itemPanel1, ID_OPENLASTCHECKBOX, _( "Load Last File at Startup" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_loadLastFileAtStartUp->SetValue( false );
    itemBoxSizer10->Add( m_loadLastFileAtStartUp, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton5 = new wxButton( itemPanel1, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add( itemButton5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton6 = new wxButton( itemPanel1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add( itemButton6, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

// SettingsPanel content construction
}


/*
 * Should we show tooltips?
 */

bool SettingsPanel::ShowToolTips( )
{ 
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SettingsPanel::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
// SettingsPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
// SettingsPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SettingsPanel::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
// SettingsPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
// SettingsPanel icon retrieval
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void SettingsPanel::OnCancelClick( wxCommandEvent& event )
{ 
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in SettingsPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in SettingsPanel. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void SettingsPanel::OnOkClick( wxCommandEvent& event )
{ 
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in SettingsPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in SettingsPanel. 
}

