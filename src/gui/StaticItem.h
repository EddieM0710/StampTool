/* 
 * @file gui/StaticItem.h
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
#ifndef _STATICITEM_H_
#define _STATICITEM_H_


/*!
 * Includes
 */

#include "gui/GuiDefs.h"

/*!
 * Forward declarations
 */

// forward declarations
// forward declarations

/*!
 * Control identifiers
 */

// control identifiers
#define wxID_TITLESTATIC ID_STATICITEM+1
#define wxID_COLONSTATIC ID_STATICITEM+2
#define wxID_VALSTATIC ID_STATICITEM+3
#define SYMBOL_STATICITEM_STYLE wxTAB_TRAVERSAL
#define SYMBOL_STATICITEM_TITLE _( "StaticItem" )
#define SYMBOL_STATICITEM_IDNAME ID_STATICITEM
#define SYMBOL_STATICITEM_SIZE wxSize( 400, 300 )
#define SYMBOL_STATICITEM_POSITION wxDefaultPosition
// control identifiers


/*!
 * StaticItem class declaration
 */

class StaticItem: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( StaticItem )
    DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    StaticItem( );
    StaticItem( wxWindow* parent, wxWindowID id = SYMBOL_STATICITEM_IDNAME, const wxPoint& pos = SYMBOL_STATICITEM_POSITION, const wxSize& size = SYMBOL_STATICITEM_SIZE, long style = SYMBOL_STATICITEM_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STATICITEM_IDNAME, const wxPoint& pos = SYMBOL_STATICITEM_POSITION, const wxSize& size = SYMBOL_STATICITEM_SIZE, long style = SYMBOL_STATICITEM_STYLE );

    /// Destructor
    ~StaticItem( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

// StaticItem event handler declarations

    /// wxEVT_CONTEXT_MENU event handler for ID_STATICITEM
    void OnContextMenu( wxContextMenuEvent& event );

// StaticItem event handler declarations

// StaticItem member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// StaticItem member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips( );

// StaticItem member variables
    wxStaticText* m_title;
    wxStaticText* m_data;
// StaticItem member variables
};

#endif
    // _STATICITEM_H_
