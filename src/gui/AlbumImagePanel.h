/**
 * @file AlbumImagePanel.h
 * @author Eddie Monroe ( )
 * @brief This is the class that manages the image displayed on the StampDescriptionPanel.
 * @version 0.1
 * @date 2021-02-25
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
    AlbumImagePanel_DeleteItem,
    AlbumImagePanel_EditDetails
};
// };

/**
 * @brief This is the class that manages the image displayed on the StampDescriptionPanel.
 *
 **************************************************/
class AlbumImagePanel: public wxScrolledWindow
{
    DECLARE_DYNAMIC_CLASS( AlbumImagePanel )
        DECLARE_EVENT_TABLE( )

public:

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
     * @brief ID_ALBUMIMAGEPANEL
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnPaint( wxPaintEvent& event );
    void PaintPDF( );

    void OnLeftDown( wxMouseEvent& event );

    wxRealPoint GetLogicalTextExtent( wxString text, wxFont font );

    wxSize GetTextSize( wxFont font, wxString text );

    void MakeMultiLine( wxString& text, wxFont font, double width );


    /**
     * @brief  ID_ALBUMIMAGEPANEL
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnContextMenu( wxContextMenuEvent& event );

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
     // void OnZoom( wxCommandEvent& event );


    void OnDeleteItem( );
    void OnEditDetails( );

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
