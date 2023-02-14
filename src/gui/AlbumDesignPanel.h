/*
 * @file AlbumSplitterWiindow.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
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

#ifndef _ALBUMSPLITTERWIINDOW_H_
#define _ALBUMSPLITTERWIINDOW_H_


 /*!
  * Includes
  */

#include "wx/splitter.h"
#include "wx/treectrl.h"
#include "gui/GuiDefs.h"

/*!
 * Forward declarations
 */

 // forward declarations
class wxSplitterWindow;
class wxTreeCtrl;
class wxWindow;
// forward declarations
class DesignTreeCtrl;
class AlbumDesignTreePanel;
class AlbumImagePanel;
/*!
 * Control identifiers
 */
#define SYMBOL_STAMPTOOLDESIGNPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_STAMPTOOLDESIGNPANEL_TITLE _( "StampToolPanel" )
#define SYMBOL_STAMPTOOLDESIGNPANEL_IDNAME ID_ALBUMDESIGNPANEL
#define SYMBOL_STAMPTOOLDESIGNPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_STAMPTOOLDESIGNPANEL_POSITION wxDefaultPosition
// control identifiers


/*!
 * AlbumDesignPanel class declaration
 */

class AlbumDesignPanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( AlbumDesignPanel )
        DECLARE_EVENT_TABLE( )

public:
    enum AlbumDesignPanelGuiDefs
    {
        ID_SECONDARYSPLITTERWINDOW = ID_ALBUMDESIGNPANEL * 1,
        ID_SCROLLEDWINDOW,
        ID_AECMDTREECTRL,
        ID_PANEL,
        ID_CDDATATEXTCTRL,
        ID_ALBUMALBUMIMAGEPANEL,
        ID_ALBUMZOOMSLIDER
    };
    /// Constructors
    AlbumDesignPanel( );
    AlbumDesignPanel( wxWindow* parent, wxWindowID id = SYMBOL_STAMPTOOLDESIGNPANEL_IDNAME, const wxPoint& pos = SYMBOL_STAMPTOOLDESIGNPANEL_POSITION, const wxSize& size = SYMBOL_STAMPTOOLDESIGNPANEL_SIZE, long style = SYMBOL_STAMPTOOLDESIGNPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STAMPTOOLDESIGNPANEL_IDNAME, const wxPoint& pos = SYMBOL_STAMPTOOLDESIGNPANEL_POSITION, const wxSize& size = SYMBOL_STAMPTOOLDESIGNPANEL_SIZE, long style = SYMBOL_STAMPTOOLDESIGNPANEL_STYLE );

    /// Destructor
    ~AlbumDesignPanel( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

    // AlbumDesignPanel event handler declarations

    // AlbumDesignPanel event handler declarations

    // AlbumDesignPanel member function declarations

        /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
    // AlbumDesignPanel member function declarations

    AlbumDesignTreePanel* GetAlbumDesignTreePanel( ) { return m_albumDesignTreePanel; };
    void OnZoomsliderUpdated( wxCommandEvent& event );

    /// Should we show tooltips?
    static bool ShowToolTips( );
    void SetSashPosition( int pos ) { m_secondarySplitterWindow->SetSashPosition( pos ); };
    // AlbumDesignPanel member variables
    wxSplitterWindow* m_secondarySplitterWindow;
    AlbumImagePanel* m_albumImagePanel;
    // AlbumDesignPanel member variables
    wxSlider* m_zoomSlider; ///< Pointer to image soom slider
    AlbumDesignTreePanel* m_albumDesignTreePanel;
};

#endif
// _ALBUMSPLITTERWIINDOW_H_
