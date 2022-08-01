/* 
 * @file CatalogPanel.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-22
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
#include "gui/CatalogTreeCtrl.h"
#include "wx/imaglist.h"
// includes

#include "gui/CatalogPanel.h"
#include "Defs.h"
#include <wx/filename.h>

// XPM images
// XPM images


/*
 * CatalogPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CatalogPanel, wxPanel )


/*
 * CatalogPanel event table definition
 */

BEGIN_EVENT_TABLE( CatalogPanel, wxPanel )

// CatalogPanel event table entries
    EVT_TEXT( ID_TEXTCTRL, CatalogPanel::OnTextctrlTextUpdated )
// CatalogPanel event table entries

END_EVENT_TABLE()


/*
 * CatalogPanel constructors
 */

CatalogPanel::CatalogPanel()
{
    Init();
}

CatalogPanel::CatalogPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * CatalogPanel creator
 */

bool CatalogPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
// CatalogPanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
// CatalogPanel creation
    return true;
}


/*
 * CatalogPanel destructor
 */

CatalogPanel::~CatalogPanel()
{
// CatalogPanel destruction
// CatalogPanel destruction
}


/*
 * Member initialisation
 */

void CatalogPanel::Init()
{
// CatalogPanel member initialisation
    m_title = NULL;
    m_catalogTreeCtrl = NULL;
// CatalogPanel member initialisation
}


/*
 * Control creation for CatalogPanel
 */

void CatalogPanel::CreateControls()
{    

    CatalogPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 0, wxGROW|wxALL, 0);

    wxStaticText* itemStaticText2 = new wxStaticText( itemPanel1, wxID_STATIC, _("Title"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_title = new wxTextCtrl( itemPanel1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(m_title, 0, wxGROW|wxALL, 0);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 2, wxGROW|wxALL, 0);

    m_catalogTreeCtrl = new CatalogTreeCtrl( itemPanel1, ID_CATALOGTREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS |wxTR_FULL_ROW_HIGHLIGHT|wxTR_SINGLE|wxSUNKEN_BORDER|wxTR_DEFAULT_STYLE );
    itemBoxSizer3->Add(m_catalogTreeCtrl, 2, wxGROW|wxALL, 0);

// CatalogPanel content construction
    GetGeneratorData( )->SetCatalogTreeCtrl(m_catalogTreeCtrl);

}


/*
 * Should we show tooltips?
 */

bool CatalogPanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap CatalogPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
// CatalogPanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
// CatalogPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CatalogPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
// CatalogPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
// CatalogPanel icon retrieval
}


/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL
 */

void CatalogPanel::OnTextctrlTextUpdated( wxCommandEvent& event )
{
// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL in CatalogPanel.
    // Before editing this code, remove the block markers.
    event.Skip();
// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL in CatalogPanel. 
}


