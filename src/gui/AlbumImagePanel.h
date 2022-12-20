/**
 * @file AlbumImagePanel.h
 * @author Eddie Monroe ()
 * @brief This is the class that manages the image displayed on the StampDescriptionPanel.
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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
 *
 **************************************************/

#ifndef _ALBUMIMAGEPANEL_H_
#define _ALBUMIMAGEPANEL_H_

 /*
  * Includes
  */
#include "gui/GuiDefs.h"
#include "design/LayoutBase.h"
  /*
   * Forward declarations
   */


   /*
    * Control identifiers
    */


#define SYMBOL_ALBUMIMAGEPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_ALBUMIMAGEPANEL_TITLE _( "AlbumImagePanel" )
#define SYMBOL_ALBUMIMAGEPANEL_IDNAME ID_ALBUMIMAGEPANEL
#define SYMBOL_ALBUMIMAGEPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_ALBUMIMAGEPANEL_POSITION wxDefaultPosition


enum
{
    ID_ROTATE_LEFT = wxID_HIGHEST + 1,
    ID_ROTATE_RIGHT,
    ID_RESIZE,
    ID_PAINT_BG
};

/**
 * @brief This is the class that manages the image displayed on the StampDescriptionPanel.
 *
 **************************************************/
class AlbumImagePanel : public wxScrolledWindow
{
    DECLARE_DYNAMIC_CLASS( AlbumImagePanel )
        DECLARE_EVENT_TABLE( )

public:
    // Constructors
    /**
     * @brief Default Constructor a new AlbumImagePanel object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
    AlbumImagePanel( );

    /**
     * @brief Construct a new AlbumImagePanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    AlbumImagePanel( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMIMAGEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_ALBUMIMAGEPANEL_POSITION,
        const wxSize& size = SYMBOL_ALBUMIMAGEPANEL_SIZE,
        long style = SYMBOL_ALBUMIMAGEPANEL_STYLE );

    /**
     * @brief  Used for two-step panel construction.
     * Use with default constructor.
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @return bool
     *
     **************************************************/
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMIMAGEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_ALBUMIMAGEPANEL_POSITION,
        const wxSize& size = SYMBOL_ALBUMIMAGEPANEL_SIZE,
        long style = SYMBOL_ALBUMIMAGEPANEL_STYLE );

    /**
     * @brief Destroy the Image Panel object
     *
     **************************************************/
    ~AlbumImagePanel( );


    /**
     * @brief Initialises member variables
     *
     **************************************************/
    void Init( );

    /**
     * @brief Creates the controls and sizers
     *
     **************************************************/
    void CreateControls( );

    // AlbumImagePanel event handler declarations


    /**
     * @brief wxEVT_PAINT event handler for ID_ALBUMIMAGEPANEL
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnPaint( wxPaintEvent& event );

    wxRealPoint GetLogicalTextExtent( wxString text, wxFont font );

    void MakeMultiLine( wxString& text, wxFont font, double width );


    /**
     * @brief wxEVT_CONTEXT_MENU event handler for ID_ALBUMIMAGEPANEL
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnContextMenu( wxContextMenuEvent& event );


    /**
     * @brief Retrieves bitmap resources
     *
     * @param  name (autogenerated. Dummy.)
     * @return wxBitmap null
     **************************************************/
    wxBitmap GetBitmapResource( const wxString& name );

    /**
     * @brief Get the Icon Resource objectRetrieves icon resources
     *
     * @param  name (autogenerated. Dummy.)
     * @return wxIcon null
     **************************************************/
    wxIcon GetIconResource( const wxString& name );


    // AlbumImagePanel member function declarations

    // Should we show tooltips?
    static bool ShowToolTips( );


    /**
     * @brief Resize the image to fit in the clientspace
     *
     * @param WXUNUSED
     **************************************************/
    void OnResize( wxCommandEvent& WXUNUSED( event ) );

    /**
     * @brief Zoom requested
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnZoom( wxCommandEvent& event );


    /**
     * @brief Set the Zoom object
     *
     * @param zoom new value to set the zoom factor to.
     **************************************************/
    void SetZoom( double zoom );

    void Draw( wxDC& dc, Design::LayoutBase* node, wxPoint pt );

private:
    double m_pixelsPerIn;
    wxBitmap m_bitmap; ///< current bitmap to display
    double m_zoom; ///< current zoom factor
    bool m_once;
};

#endif
// _ALBUMIMAGEPANEL_H_
