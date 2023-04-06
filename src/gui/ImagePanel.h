/**
 * @file ImagePanel.h
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

#ifndef _IMAGEPANEL_H_
#define _IMAGEPANEL_H_


#include "gui/GuiDefs.h"
#include "catalog/Entry.h"

#include "gui/GuiDefs.h"
 // #include "wx/webrequest.h"

 // #if !wxUSE_WEBREQUEST
 // #error "wxUSE_WEBREQUEST must be 1 for web access"
 // #endif


#define SYMBOL_IMAGEPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_IMAGEPANEL_TITLE _( "ImagePanel" )
#define SYMBOL_IMAGEPANEL_IDNAME ID_IMAGEPANEL
#define SYMBOL_IMAGEPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_IMAGEPANEL_POSITION wxDefaultPosition


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
class ImagePanel: public wxScrolledWindow
{
    DECLARE_DYNAMIC_CLASS( ImagePanel )
        DECLARE_EVENT_TABLE( )

public:

    /**
     * @brief Default Constructor a new ImagePanel object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
    ImagePanel( );

    /**
     * @brief Construct a new ImagePanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    ImagePanel( wxWindow* parent, wxWindowID id = SYMBOL_IMAGEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IMAGEPANEL_POSITION,
        const wxSize& size = SYMBOL_IMAGEPANEL_SIZE,
        long style = SYMBOL_IMAGEPANEL_STYLE );

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
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_IMAGEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IMAGEPANEL_POSITION,
        const wxSize& size = SYMBOL_IMAGEPANEL_SIZE,
        long style = SYMBOL_IMAGEPANEL_STYLE );

    /**
     * @brief Destroy the Image Panel object
     *
     **************************************************/
    ~ImagePanel( );


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

    // ImagePanel event handler declarations


    /**
     * @brief  PAINT event handler for ID_IMAGEPANEL
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnPaint( wxPaintEvent& event );

    /**
     * @brief  ID_IMAGEPANEL
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnContextMenu( wxContextMenuEvent& event );



    // 
    static bool ShowToolTips( );

    /**
     * @brief Set the Bitmap
     *
     * @param filename  fullname and path for the bitmap file
     **************************************************/
    void SetBitmap( wxString filename );

    void SetStamp( Catalog::Entry* stamp );

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

    //    void StartWebRequest( RequestType page, wxString url );
    //    void OnWebRequestState( wxWebRequestEvent& evt );
     //   wxBitmap GetWebImage( ) { return m_imageBitmap; };
    //    wxString GetWebText( ) { return m_webText; };
        //void LoadImageFromWeb( Catalog::Entry* stamp );

private:
    wxBitmap m_bitmap; ///< current bitmap to display
    double m_zoom; ///< current zoom factor

    Catalog::Entry* m_stamp; ///< Pointer to currently displayed stamp
    //    RequestType m_page;
    wxBitmap m_imageBitmap;
    //    wxString m_webText;
    //    wxWebRequest m_currentRequest;
};

#endif
// _IMAGEPANEL_H_
