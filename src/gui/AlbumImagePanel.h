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
 */

#ifndef _ALBUMIMAGEPANEL_H_
#define _ALBUMIMAGEPANEL_H_

#include "gui/GuiDefs.h"
#include "design/LayoutBase.h"

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


/**
 * @brief This is the class that manages the image displayed on the StampDescriptionPanel.
 *
 */
class AlbumImagePanel : public wxScrolledWindow
{
    DECLARE_DYNAMIC_CLASS( AlbumImagePanel )
    DECLARE_EVENT_TABLE( )

public:

    AlbumImagePanel( );

    AlbumImagePanel( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMIMAGEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_ALBUMIMAGEPANEL_POSITION,
        const wxSize& size = SYMBOL_ALBUMIMAGEPANEL_SIZE,
        long style = SYMBOL_ALBUMIMAGEPANEL_STYLE );

    ~AlbumImagePanel( );

    void Clear( );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMIMAGEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_ALBUMIMAGEPANEL_POSITION,
        const wxSize& size = SYMBOL_ALBUMIMAGEPANEL_SIZE,
        long style = SYMBOL_ALBUMIMAGEPANEL_STYLE );

    void CreateControls( );

    void Draw( wxDC& dc, Design::LayoutBase* node, wxPoint pt );

    wxSize GetLogicalTextExtent( wxString text, wxFont font );

    double GetUserScale( ) {
        return m_userScale;
    };

    double GetZoom( ) {
        return m_zoom;
        m_once = false;
    };

    void Init( );

    wxSize  MakeMultiLine( wxString& text, wxFont font, double width );

    void PaintPDF( );

    void OnContextMenu( wxContextMenuEvent& event );

    void OnDeleteItem( );

    void OnEditDetails( );

    void OnLeftDown( wxMouseEvent& event );

    void OnPaint( wxPaintEvent& event );

    void OnResize( wxCommandEvent& WXUNUSED( event ) );

    void SetZoom( double zoom );

    static bool ShowToolTips( );

private:
    double m_pixelsPerIn;
    wxBitmap m_bitmap; ///< current bitmap to display
    double m_zoom; ///< current zoom 
    double m_userScale;
    bool m_once;
};

#endif
// _ALBUMIMAGEPANEL_H_
