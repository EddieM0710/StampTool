/* 
 * @file GalleryImagePanel.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-02-21
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
// includes

#include "gui/GalleryImagePanel.h"

// XPM images

// XPM images


/*
 * GalleryImagePanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( GalleryImagePanel, wxPanel )


/*
 * GalleryImagePanel event table definition
 */

BEGIN_EVENT_TABLE( GalleryImagePanel, wxPanel )

// GalleryImagePanel event table entries
    EVT_LEFT_UP( GalleryImagePanel::OnLeftUp )
    EVT_LEFT_DCLICK( GalleryImagePanel::OnLeftDClick )
    EVT_CONTEXT_MENU( GalleryImagePanel::OnContextMenu )
// GalleryImagePanel event table entries

END_EVENT_TABLE()


/*
 * GalleryImagePanel constructors
 */

GalleryImagePanel::GalleryImagePanel()
{
    Init();
}

GalleryImagePanel::GalleryImagePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * GalleryImagePanel creator
 */

bool GalleryImagePanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
// GalleryImagePanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
// GalleryImagePanel creation
    return true;
}


/*
 * GalleryImagePanel destructor
 */

GalleryImagePanel::~GalleryImagePanel()
{
// GalleryImagePanel destruction
// GalleryImagePanel destruction
}


/*
 * Member initialisation
 */

void GalleryImagePanel::Init()
{
// GalleryImagePanel member initialisation
    m_bitmapCtrl = NULL;
    m_ID = NULL;
    m_title = NULL;
// GalleryImagePanel member initialisation
}


/*
 * Control creation for GalleryImagePanel
 */

void GalleryImagePanel::CreateControls()
{    
// GalleryImagePanel content construction

    GalleryImagePanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_bitmapCtrl = new wxStaticBitmap( itemPanel1, wxID_BITMAPSTATIC, wxNullBitmap, wxDefaultPosition, wxSize(100, 100), 0 );
    itemBoxSizer2->Add(m_bitmapCtrl, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_ID = new wxStaticText( itemPanel1, wxID_IDSTATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(m_ID, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    m_title = new wxStaticText( itemPanel1, wxID_TITLESTATIC, wxEmptyString, wxDefaultPosition, wxSize(-1, 40), 0 );
    m_title->Wrap(90);
    itemBoxSizer1->Add(m_title, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);


    // Connect events and objects
    m_bitmapCtrl->Connect(wxID_BITMAPSTATIC, wxEVT_LEFT_UP, wxMouseEventHandler(GalleryImagePanel::OnLeftUp), NULL, this);
    m_bitmapCtrl->Connect(wxID_BITMAPSTATIC, wxEVT_LEFT_DCLICK, wxMouseEventHandler(GalleryImagePanel::OnLeftDClick), NULL, this);
    m_bitmapCtrl->Connect(wxID_BITMAPSTATIC, wxEVT_CONTEXT_MENU, wxContextMenuEventHandler(GalleryImagePanel::OnContextMenu), NULL, this);
// GalleryImagePanel content construction
}


/*
 * wxEVT_LEFT_UP event handler for ID_GALLERYALBUMIMAGEPANEL
 */

void GalleryImagePanel::OnLeftUp( wxMouseEvent& event )
{
// wxEVT_LEFT_UP event handler for ID_GALLERYALBUMIMAGEPANEL in GalleryImagePanel.
    // Before editing this code, remove the block markers.
    event.Skip();
// wxEVT_LEFT_UP event handler for ID_GALLERYALBUMIMAGEPANEL in GalleryImagePanel. 
}


/*
 * wxEVT_LEFT_DCLICK event handler for ID_GALLERYALBUMIMAGEPANEL
 */

void GalleryImagePanel::OnLeftDClick( wxMouseEvent& event )
{
// wxEVT_LEFT_DCLICK event handler for ID_GALLERYALBUMIMAGEPANEL in GalleryImagePanel.
    // Before editing this code, remove the block markers.
    event.Skip();
// wxEVT_LEFT_DCLICK event handler for ID_GALLERYALBUMIMAGEPANEL in GalleryImagePanel. 
}


/*
 * wxEVT_CONTEXT_MENU event handler for ID_GALLERYALBUMIMAGEPANEL
 */

void GalleryImagePanel::OnContextMenu( wxContextMenuEvent& event )
{
// wxEVT_CONTEXT_MENU event handler for ID_GALLERYALBUMIMAGEPANEL in GalleryImagePanel.
    // Before editing this code, remove the block markers.
    event.Skip();
// wxEVT_CONTEXT_MENU event handler for ID_GALLERYALBUMIMAGEPANEL in GalleryImagePanel. 
}


/*
 * Should we show tooltips?
 */

bool GalleryImagePanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap GalleryImagePanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
// GalleryImagePanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
// GalleryImagePanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon GalleryImagePanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
// GalleryImagePanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
// GalleryImagePanel icon retrieval
}
