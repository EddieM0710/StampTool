/* 
 * @file AlbumSplitterWiindow.h
 * @author Eddie Monroe 
 * @brief 
 * @version 0.1
 * @date 2022-01-19
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
 */

#ifndef _ALBUMSPLITTERWIINDOW_H_
#define _ALBUMSPLITTERWIINDOW_H_


/*!
 * Includes
 */

// includes
#include "wx/splitter.h"
#include "wx/treectrl.h"
// includes

/*!
 * Forward declarations
 */

// forward declarations
class wxSplitterWindow;
class wxTreeCtrl;
class wxWindow;
// forward declarations
class DesignTreeCtrl;
class AlbumPanel;
class AlbumImagePanel;
/*!
 * Control identifiers
 */

// control identifiers
#define ID_ALBUMSPLITTERWINDOW 10000
#define ID_SECONDARYSPLITTERWINDOW 13005
#define ID_SCROLLEDWINDOW 10003
#define ID_AECMDTREECTRL 10001
#define ID_PANEL 10002
#define ID_CDDATATEXTCTRL 10005
#define ID_ALBUMALBUMIMAGEPANEL 10004
#define ID_ALBUMZOOMSLIDER 10006
#define SYMBOL_ALBUMSPLITTERWINDOW_STYLE wxTAB_TRAVERSAL
#define SYMBOL_ALBUMSPLITTERWINDOW_TITLE _("AlbumSplitterWindow")
#define SYMBOL_ALBUMSPLITTERWINDOW_IDNAME ID_ALBUMSPLITTERWINDOW
#define SYMBOL_ALBUMSPLITTERWINDOW_SIZE wxSize(400, 300)
#define SYMBOL_ALBUMSPLITTERWINDOW_POSITION wxDefaultPosition
// control identifiers


/*!
 * AlbumSplitterWindow class declaration
 */

class AlbumSplitterWindow: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( AlbumSplitterWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AlbumSplitterWindow();
    AlbumSplitterWindow( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMSPLITTERWINDOW_IDNAME, const wxPoint& pos = SYMBOL_ALBUMSPLITTERWINDOW_POSITION, const wxSize& size = SYMBOL_ALBUMSPLITTERWINDOW_SIZE, long style = SYMBOL_ALBUMSPLITTERWINDOW_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMSPLITTERWINDOW_IDNAME, const wxPoint& pos = SYMBOL_ALBUMSPLITTERWINDOW_POSITION, const wxSize& size = SYMBOL_ALBUMSPLITTERWINDOW_SIZE, long style = SYMBOL_ALBUMSPLITTERWINDOW_STYLE );

    /// Destructor
    ~AlbumSplitterWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

// AlbumSplitterWindow event handler declarations

// AlbumSplitterWindow event handler declarations

// AlbumSplitterWindow member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
// AlbumSplitterWindow member function declarations

    AlbumPanel* GetAlbumPanel(){ return m_albumPanel;} ;
    void OnZoomsliderUpdated( wxCommandEvent& event );

    /// Should we show tooltips?
    static bool ShowToolTips();
    void SetSashPosition( int pos ){ m_secondarySplitterWindow->SetSashPosition( pos ); };
// AlbumSplitterWindow member variables
    wxSplitterWindow* m_secondarySplitterWindow;
    AlbumImagePanel* m_albumImagePanel;
// AlbumSplitterWindow member variables
    wxSlider* m_zoomSlider; ///< Pointer to image soom slider
    AlbumPanel* m_albumPanel ;
};

#endif
    // _ALBUMSPLITTERWIINDOW_H_
