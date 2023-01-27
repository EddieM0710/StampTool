/* 
 * @file gui/GalleryImagePanel.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-02-21
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

#ifndef _GALLERYALBUMIMAGEPANEL_H_
#define _GALLERYALBUMIMAGEPANEL_H_


/*!
 * Includes
 */

// includes
// includes

/*!
 * Forward declarations
 */

// forward declarations
// forward declarations

/*!
 * Control identifiers
 */

// control identifiers
#define ID_GALLERYALBUMIMAGEPANEL 10000
#define wxID_BITMAPSTATIC 10026
#define wxID_IDSTATIC 10025
#define wxID_TITLESTATIC 10024
#define SYMBOL_GALLERYALBUMIMAGEPANEL_STYLE wxNO_BORDER | wxTAB_TRAVERSAL
#define SYMBOL_GALLERYALBUMIMAGEPANEL_TITLE _( "GalleryImagePanel" )
#define SYMBOL_GALLERYALBUMIMAGEPANEL_IDNAME ID_GALLERYALBUMIMAGEPANEL
#define SYMBOL_GALLERYALBUMIMAGEPANEL_SIZE wxSize( 70, 70 )
#define SYMBOL_GALLERYALBUMIMAGEPANEL_POSITION wxDefaultPosition
// control identifiers


/*!
 * GalleryImagePanel class declaration
 */

class GalleryImagePanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( GalleryImagePanel )
    DECLARE_EVENT_TABLE( )

public:
    /// Constructors
    GalleryImagePanel( );
    GalleryImagePanel( wxWindow* parent, wxWindowID id = SYMBOL_GALLERYALBUMIMAGEPANEL_IDNAME, const wxPoint& pos = SYMBOL_GALLERYALBUMIMAGEPANEL_POSITION, const wxSize& size = SYMBOL_GALLERYALBUMIMAGEPANEL_SIZE, long style = SYMBOL_GALLERYALBUMIMAGEPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GALLERYALBUMIMAGEPANEL_IDNAME, const wxPoint& pos = SYMBOL_GALLERYALBUMIMAGEPANEL_POSITION, const wxSize& size = SYMBOL_GALLERYALBUMIMAGEPANEL_SIZE, long style = SYMBOL_GALLERYALBUMIMAGEPANEL_STYLE );

    /// Destructor
    ~GalleryImagePanel( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

// GalleryImagePanel event handler declarations
    /// wxEVT_LEFT_UP event handler for ID_GALLERYALBUMIMAGEPANEL
    void OnLeftUp( wxMouseEvent& event );

    /// wxEVT_LEFT_DCLICK event handler for ID_GALLERYALBUMIMAGEPANEL
    void OnLeftDClick( wxMouseEvent& event );

    /// wxEVT_CONTEXT_MENU event handler for ID_GALLERYALBUMIMAGEPANEL
    void OnContextMenu( wxContextMenuEvent& event );

// GalleryImagePanel event handler declarations

// GalleryImagePanel member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// GalleryImagePanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips( );

// GalleryImagePanel member variables
    wxStaticBitmap* m_bitmapCtrl;
    wxStaticText* m_ID;
    wxStaticText* m_title;
// GalleryImagePanel member variables
};

#endif
    // _GALLERYALBUMIMAGEPANEL_H_
