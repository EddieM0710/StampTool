/* 
 * @file gui/GalleryPanel.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-02-21
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

#ifndef _GALLERYPANEL_H_
#define _GALLERYPANEL_H_


/*!
 * Includes
 */

// includes
// includes

/*!
 * Forward declarations
 */

// forward declarations
class wxGridSizer;
// forward declarations

/*!
 * Control identifiers
 */

// control identifiers
#define ID_GALLERYPANEL 10000
#define ID_IMAGEGALLERYSCROLLEDWINDOW 10001
#define SYMBOL_GALLERYPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_GALLERYPANEL_TITLE _( "GalleryPanel" )
#define SYMBOL_GALLERYPANEL_IDNAME ID_GALLERYPANEL
#define SYMBOL_GALLERYPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_GALLERYPANEL_POSITION wxDefaultPosition
// control identifiers


/*!
 * GalleryPanel class declaration
 */

class GalleryPanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( GalleryPanel )
    DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    GalleryPanel( );
    GalleryPanel( wxWindow* parent, wxWindowID id = SYMBOL_GALLERYPANEL_IDNAME, const wxPoint& pos = SYMBOL_GALLERYPANEL_POSITION, const wxSize& size = SYMBOL_GALLERYPANEL_SIZE, long style = SYMBOL_GALLERYPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GALLERYPANEL_IDNAME, const wxPoint& pos = SYMBOL_GALLERYPANEL_POSITION, const wxSize& size = SYMBOL_GALLERYPANEL_SIZE, long style = SYMBOL_GALLERYPANEL_STYLE );

    /// Destructor
    ~GalleryPanel( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

// GalleryPanel event handler declarations
// GalleryPanel event handler declarations

// GalleryPanel member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// GalleryPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips( );

// GalleryPanel member variables
    wxScrolledWindow* m_scrolledWindow;
    wxGridSizer* m_sizer;
// GalleryPanel member variables
};

#endif
    // _GALLERYPANEL_H_
