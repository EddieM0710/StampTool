/* 
 * @file SettingsDialog.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-12
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

#include "Defs.h"
#include "Settings.h"
#include "gui/SettingsDialog.h"

// XPM images
// XPM images


/*
 * SettingsDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SettingsDialog, wxDialog )


/*
 * SettingsDialog event table definition
 */

BEGIN_EVENT_TABLE( SettingsDialog, wxDialog )

// SettingsDialog event table entries
    EVT_TEXT( ID_IMAGEDIRECTORTEXTBOX, SettingsDialog::OnImagedirectortextboxTextUpdated )
    EVT_TEXT( ID_COUNTRYTEXTBOX, SettingsDialog::OnCountrytextboxTextUpdated )
    EVT_TEXT( ID_CATALOGTEXTBOX, SettingsDialog::OnCatalogtextboxTextUpdated )
    EVT_CHECKBOX( ID_OPENLASTCHECKBOX, SettingsDialog::OnOpenlastcheckboxClick )
    EVT_TEXT( ID_RECENTSIZETEXTCTRL, SettingsDialog::OnRecentsizetextctrlTextUpdated )
    EVT_BUTTON( wxID_OK, SettingsDialog::OnOkClick )
// SettingsDialog event table entries

END_EVENT_TABLE( )


/*
 * SettingsDialog constructors
 */

SettingsDialog::SettingsDialog( )
{ 
    Init( );
}

SettingsDialog::SettingsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, caption, pos, size, style );
    //m_imageDirectory->SetValue( GetSettings( )->GetImageDirectory( ) );
    m_country->SetValue( GetSettings( )->GetCountryID( ) );
    m_catalog->SetValue( GetSettings( )->GetCatalogID( ) );
    m_loadLastFileAtStartUp->SetValue( GetSettings( )->GetLoadLastFileAtStartUp( ) );
    wxString str = wxString::Format( "%i", GetSettings( )->GetNbrRecentPreference( ) );
    m_recentListSize->SetValue( str );
}


/*
 * SettingsDialog creator
 */

bool SettingsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{ 
// SettingsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    { 
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
// SettingsDialog creation
    return true;
}


/*
 * SettingsDialog destructor
 */

SettingsDialog::~SettingsDialog( )
{ 
// SettingsDialog destruction
// SettingsDialog destruction
}


/*
 * Member initialisation
 */

void SettingsDialog::Init( )
{ 
// SettingsDialog member initialisation
    m_imageDirectory = NULL;
    m_country = NULL;
    m_catalog = NULL;
    m_loadLastFileAtStartUp = NULL;
    m_recentListSize = NULL;
// SettingsDialog member initialisation
}


/*
 * Control creation for SettingsDialog
 */

void SettingsDialog::CreateControls( )
{    
// SettingsDialog content construction

    SettingsDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer3, 1, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText1 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Image Directory" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( itemStaticText1, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_imageDirectory = new wxTextCtrl( itemDialog1, ID_IMAGEDIRECTORTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( m_imageDirectory, 3, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer5, 1, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Working Directory" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add( itemStaticText3, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer7, 1, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Country Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add( itemStaticText5, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_country = new wxTextCtrl( itemDialog1, ID_COUNTRYTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add( m_country, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer7->Add( 10, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Catalog Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add( itemStaticText8, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_catalog = new wxTextCtrl( itemDialog1, ID_CATALOGTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add( m_catalog, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer10, 1, wxGROW | wxALL, 5 );

    m_loadLastFileAtStartUp = new wxCheckBox( itemDialog1, ID_OPENLASTCHECKBOX, _( "Load Last File at Startup" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_loadLastFileAtStartUp->SetValue( false );
    itemBoxSizer10->Add( m_loadLastFileAtStartUp, 2, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer10->Add( 20, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Size of RecentList" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add( itemStaticText2, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_recentListSize = new wxTextCtrl( itemDialog1, ID_RECENTSIZETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add( m_recentListSize, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer1->Add( itemBoxSizer12, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add( itemButton13, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add( itemButton14, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

// SettingsDialog content construction
}


/*
 * Should we show tooltips?
 */

bool SettingsDialog::ShowToolTips( )
{ 
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SettingsDialog::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
// SettingsDialog bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
// SettingsDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SettingsDialog::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
// SettingsDialog icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
// SettingsDialog icon retrieval
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_IMAGEDIRECTORTEXTBOX
 */

void SettingsDialog::OnImagedirectortextboxTextUpdated( wxCommandEvent& event )
{ 

    m_dirty = true;

// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_IMAGEDIRECTORTEXTBOX in SettingsDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_IMAGEDIRECTORTEXTBOX in SettingsDialog. 
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_COUNTRYTEXTBOX
 */

void SettingsDialog::OnCountrytextboxTextUpdated( wxCommandEvent& event )
{ 

    m_dirty = true;

// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_COUNTRYTEXTBOX in SettingsDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_COUNTRYTEXTBOX in SettingsDialog. 
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_CATALOGTEXTBOX
 */

void SettingsDialog::OnCatalogtextboxTextUpdated( wxCommandEvent& event )
{ 

    m_dirty = true;

// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_CATALOGTEXTBOX in SettingsDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_CATALOGTEXTBOX in SettingsDialog. 
}


/*
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_OPENLASTCHECKBOX
 */

void SettingsDialog::OnOpenlastcheckboxClick( wxCommandEvent& event )
{ 

    m_dirty = true;

// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_OPENLASTCHECKBOX in SettingsDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_OPENLASTCHECKBOX in SettingsDialog. 
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_RECENTSIZETEXTCTRL
 */

void SettingsDialog::OnRecentsizetextctrlTextUpdated( wxCommandEvent& event )
{ 

    m_dirty = true;

// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_RECENTSIZETEXTCTRL in SettingsDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_RECENTSIZETEXTCTRL in SettingsDialog. 
}

void SettingsDialog::OnOkClick( wxCommandEvent& event )
{ 
    UpdateSettings( );
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in DefinePeriodsDialog.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK in DefinePeriodsDialog. 

 }

void SettingsDialog::UpdateSettings( )
{ 
 
    if ( m_imageDirectory->IsModified( ) )
    { 
        GetSettings( )->SetDirty( );
        //GetSettings( )->SetImageDirectory( m_imageDirectory->GetValue( ) );
        m_imageDirectory->SetModified( false );
    }

    if ( m_country->IsModified( ) )
    { 
        GetSettings( )->SetDirty( );
        GetSettings( )->SetCountryID( m_country->GetValue( ) );
        m_country->SetModified( false );
    }


    if ( m_catalog->IsModified( ) )
    { 
        GetSettings( )->SetDirty( );
        GetSettings( )->SetCatalogID( m_catalog->GetValue( ) );
        m_catalog->SetModified( false );
    }

    if ( m_loadLastFileAtStartUp->GetValue( ) != GetSettings( )->GetLoadLastFileAtStartUp( ) )
    { 
        GetSettings( )->SetDirty( );
        GetSettings( )->SetLoadLastFileAtStartUp( m_loadLastFileAtStartUp->GetValue( ) );
    }


    if ( m_recentListSize->IsModified( ) )
    { 
        GetSettings( )->SetDirty( );
        long val;
        if ( m_recentListSize->GetValue( ).ToLong( &val ) )
        { 
           GetSettings( )->SetNbrRecentPreference( val );
        }
        else
        { 
            GetSettings( )->SetNbrRecentPreference( 1 );
        }
        m_recentListSize->SetModified( false );  
    } 
    if( GetSettings( )->isDirty( ) )  
    GetSettings( )->Save( );
}