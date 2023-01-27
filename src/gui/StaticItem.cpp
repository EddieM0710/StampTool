/* 
 * @file StaticItem.cpp
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-21
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

#include "gui/StaticItem.h"

// XPM images
// XPM images


/*
 * StaticItem type definition
 */

IMPLEMENT_DYNAMIC_CLASS( StaticItem, wxPanel )


/*
 * StaticItem event table definition
 */

BEGIN_EVENT_TABLE( StaticItem, wxPanel )

// StaticItem event table entries
    EVT_CONTEXT_MENU( StaticItem::OnContextMenu )
// StaticItem event table entries

END_EVENT_TABLE( )


/*
 * StaticItem constructors
 */

StaticItem::StaticItem( )
{ 
    Init( );
}

StaticItem::StaticItem( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}


/*
 * StaticItem creator
 */

bool StaticItem::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{ 
// StaticItem creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    { 
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
// StaticItem creation
    return true;
}


/*
 * StaticItem destructor
 */

StaticItem::~StaticItem( )
{ 
// StaticItem destruction
// StaticItem destruction
}


/*
 * Member initialisation
 */

void StaticItem::Init( )
{ 
// StaticItem member initialisation
    m_title = NULL;
    m_data = NULL;
// StaticItem member initialisation
}


/*
 * Control creation for StaticItem
 */

void StaticItem::CreateControls( )
{    
// StaticItem content construction

    StaticItem* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    m_title = new wxStaticText( itemPanel1, wxID_TITLESTATIC, _( "Title" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_title, 0, wxGROW, 5 );

    wxStaticText* itemStaticText3 = new wxStaticText( itemPanel1, wxID_COLONSTATIC, _( ":" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( itemStaticText3, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5 );

    m_data = new wxStaticText( itemPanel1, wxID_VALSTATIC, _( "val" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_data, 1, wxGROW, 5 );

// StaticItem content construction
}


/*
 * Should we show tooltips?
 */

bool StaticItem::ShowToolTips( )
{ 
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap StaticItem::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
// StaticItem bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
// StaticItem bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon StaticItem::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
// StaticItem icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
// StaticItem icon retrieval
}


/*
 * wxEVT_CONTEXT_MENU event handler for ID_STATICITEM
 */

void StaticItem::OnContextMenu( wxContextMenuEvent& event )
{ 
// wxEVT_CONTEXT_MENU event handler for ID_STATICITEM in StaticItem.
    // Before editing this code, remove the block markers.
    event.Skip( );
// wxEVT_CONTEXT_MENU event handler for ID_STATICITEM in StaticItem. 
}

