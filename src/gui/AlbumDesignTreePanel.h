/* 
 * @file AlbumDesignTreePanel.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-22
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

#ifndef _ALBUMPANEL_H_
#define _ALBUMPANEL_H_


/*!
 * Includes
 */

// includes
#include "wx/treectrl.h"
// includes
#include "Defs.h"
#include <vector>
/*!
 * Forward declarations
 */

// forward declarations
class DesignTreeCtrl;
class StaticItem;
// forward declarations
class ReadAlbumEasyFile;
/*!
 * Control identifiers
 */

// control identifiers
#define ID_MANAGEAECMDDATA 10000
#define ID_AECMDTREECTRL 10001
#define ID_SCROLLEDWINDOW 10003
#define ID_CMDDATATEXTCTRL 10005
#define SYMBOL_MANAGEAECMDDATA_STYLE wxTAB_TRAVERSAL
#define SYMBOL_MANAGEAECMDDATA_TITLE _( "AlbumPanel" )
#define SYMBOL_MANAGEAECMDDATA_IDNAME ID_MANAGEAECMDDATA
#define SYMBOL_MANAGEAECMDDATA_SIZE wxSize( 400, 300 )
#define SYMBOL_MANAGEAECMDDATA_POSITION wxDefaultPosition
// control identifiers


/*!
 * AlbumDesignTreePanel class declaration
 */

class AlbumDesignTreePanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( AlbumDesignTreePanel )
    DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    AlbumDesignTreePanel( );
    AlbumDesignTreePanel( wxWindow* parent, wxWindowID id = SYMBOL_MANAGEAECMDDATA_IDNAME, const wxPoint& pos = SYMBOL_MANAGEAECMDDATA_POSITION, const wxSize& size = SYMBOL_MANAGEAECMDDATA_SIZE, long style = SYMBOL_MANAGEAECMDDATA_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MANAGEAECMDDATA_IDNAME, const wxPoint& pos = SYMBOL_MANAGEAECMDDATA_POSITION, const wxSize& size = SYMBOL_MANAGEAECMDDATA_SIZE, long style = SYMBOL_MANAGEAECMDDATA_STYLE );

    /// Destructor
    ~AlbumDesignTreePanel( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

// AlbumDesignTreePanel event handler declarations

// AlbumDesignTreePanel event handler declarations

// AlbumDesignTreePanel member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// AlbumDesignTreePanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips( );

    void LoadAlbumLayout( );

    void LoadAEData( wxString filename );

    DesignTreeCtrl* GetDesignTreeCtrl( ){ return m_designTreeCtrl; };

// AlbumDesignTreePanel member variables
    DesignTreeCtrl* m_designTreeCtrl;
// AlbumDesignTreePanel member variables
 //ArrayWrapper* m_AEItemArray;
};

#endif
    // _MANAGEAECMDDATA_H_
