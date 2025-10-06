/**
 * @file ImageGalleryPanel.h
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
 */

#ifndef _IMAGEGALLERYPANEL_H_
#define _IMAGEGALLERYPANEL_H_


#include "gui/GuiDefs.h"
#include "catalog/Entry.h"

#include "gui/GuiDefs.h"
 // #include "wx/webrequest.h"

 // #if !wxUSE_WEBREQUEST
 // #error "wxUSE_WEBREQUEST must be 1 for web access"
 // #endif


#define SYMBOL_IMAGEGALLERYPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_IMAGEGALLERYPANEL_TITLE _( "ImageGalleryPanel" )
#define SYMBOL_IMAGEGALLERYPANEL_IDNAME ID_IMAGEGALLERYPANEL
#define SYMBOL_IMAGEGALLERYPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_IMAGEGALLERYPANEL_POSITION wxDefaultPosition
#define ID_IMAGEALLERYPANEL 12345



/**
 * @brief This is the class that manages the image displayed on the StampDescriptionPanel.
 *
 */
class ImageGalleryPanel : public wxScrolledWindow
{
    DECLARE_DYNAMIC_CLASS( ImageGalleryPanel )
    DECLARE_EVENT_TABLE( )

public:



    /**
     * @brief Default Constructor a new ImageGalleryPanel object
     * @details Must be used in conjunction with Create.
     *
     */
    ImageGalleryPanel( );

    ImageGalleryPanel( wxWindow* parent, wxWindowID id = SYMBOL_IMAGEGALLERYPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IMAGEGALLERYPANEL_POSITION,
        const wxSize& size = SYMBOL_IMAGEGALLERYPANEL_SIZE,
        long style = SYMBOL_IMAGEGALLERYPANEL_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_IMAGEGALLERYPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_IMAGEGALLERYPANEL_POSITION,
        const wxSize& size = SYMBOL_IMAGEGALLERYPANEL_SIZE,
        long style = SYMBOL_IMAGEGALLERYPANEL_STYLE );

    ~ImageGalleryPanel( );

    void Clear( );

    void CreateControls( );

    void Init( );
    void DrawGallery( wxDC& dc );
    void DrawGallery( wxDC& dc, wxTreeItemId child, int& row, int& col );
    void DrawStamp( wxDC& dc, wxTreeItemId child, int& row, int& col );

    void OnContextMenu( wxContextMenuEvent& event );

    void OnPaint( wxPaintEvent& event );

    void OnResize( wxCommandEvent& WXUNUSED( event ) );

    void OnZoom( wxCommandEvent& event );

    void SetBitmap( wxDC& dc, wxString filename, int& row, int& col );

    void SetZoom( double zoom );

    static bool ShowToolTips( );

    void DrawBitmap( );


private:
    wxBitmap m_bitmap; ///< current bitmap to display
    double m_zoom; ///< current zoom factor

    wxBitmap m_imageBitmap;
    wxScrolledWindow* m_scrolledPanel;
    wxWindowID m_scrolledId;
    wxBitmap* m_galleryBmp;
};

#endif
// _IMAGEGALLERYPANEL_H_
