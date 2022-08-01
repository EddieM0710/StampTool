/**
 * @file AlbumGenPanel.h
 * @author Eddie Monroe ()
 * @brief
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

#ifndef _ALBUMGENERATORPANEL_H_
#define _ALBUMGENERATORPANEL_H_

/*!
 * Includes
 */

#include "wx/notebook.h"
#include "wx/splitter.h"
#include "wx/treectrl.h"

#include "gui/GuiDefs.h"

#include "gui/AlbumSplitterWindow.h"
//#include "CatalogDefs.h"
/*!
 * Forward declarations
 */

class CatalogPanel;
class wxNotebook;
class wxFlexGridSizer;
class DescriptionPanel;
//class AlbumGenDialog;

//namespace Catalog { class Stamp;}

/*!
 * Control identifiers
 */

#define ID_SPLITTERWINDOW ID_ALBUMGENERATORPANEL + 1
#define ID_PANEL1 ID_ALBUMGENERATORPANEL + 2
#define ID_STAMPTREECTRL ID_ALBUMGENERATORPANEL + 3
#define ID_NOTEBOOK ID_ALBUMGENERATORPANEL + 4
#define ID_DESCRIPTIONPANELFOREIGN ID_ALBUMGENERATORPANEL + 5
#define ID_GALLERYSCROLLEDWINDOW ID_ALBUMGENERATORPANEL + 6
#define ID_TITLETEXTCTRL ID_ALBUMGENERATORPANEL + 7
#define ID_ALBUMGENERATOR ID_ALBUMGENERATORPANEL + 8
#define ID_ALBUMSPLITTERWINDOWFOREIGN ID_ALBUMGENERATORPANEL + 9
#define SYMBOL_ALBUMGENERATORPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_ALBUMGENERATORPANEL_TITLE _( "AlbumGenPanel" )
//#define SYMBOL_ALBUMGENERATORPANEL_IDNAME ID_ALBUMGENERATORPANEL
#define SYMBOL_ALBUMGENERATORPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_ALBUMGENERATORPANEL_POSITION wxDefaultPosition

/**
 * @brief AlbumGenPanel is the main window class for the application,
 * It contains a splitter window with the CatalogTreeCtrl on one side and a 
 * wxNotebook on the other with the the DescriptionPanel and wxScrolledWindow m_galleryPage as pages.
 * m_galleryPage manages a list of GalleryImagePanel images. 
 * AlbumGenPanel inherits from wxPanel.
 */
class AlbumGenPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( AlbumGenPanel )
    DECLARE_EVENT_TABLE( )

  public:
    // Constructors
    /**
     * @brief Default Constructor a new AlbumGenPanel object
     * @details Must be used in conjunction with Create.
     * 
     **************************************************/
    AlbumGenPanel( );

    /**
     * @brief Construct a new AlbumGenPanel object
     * 
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style. 
     * @see wxPanel.
     **************************************************/
    AlbumGenPanel( wxWindow* parent,
                       wxWindowID id = ID_ALBUMGENERATORPANEL,
                       const wxPoint& pos = SYMBOL_ALBUMGENERATORPANEL_POSITION,
                       const wxSize& size = SYMBOL_ALBUMGENERATORPANEL_SIZE,
                       long style = SYMBOL_ALBUMGENERATORPANEL_STYLE );

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
    bool Create( wxWindow* parent,
                 wxWindowID id = ID_ALBUMGENERATORPANEL,
                 const wxPoint& pos = SYMBOL_ALBUMGENERATORPANEL_POSITION,
                 const wxSize& size = SYMBOL_ALBUMGENERATORPANEL_SIZE,
                 long style = SYMBOL_ALBUMGENERATORPANEL_STYLE );

    // Destructor
    ~AlbumGenPanel( );

    /**
     * @brief   Initialises member variables
     * 
     **************************************************/
    void Init( );

    /**
     * @brief Creates the controls and sizers
     * 
     **************************************************/
    void CreateControls( );

    // AlbumGenPanel event handler declarations

    // wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
    void OnNotebookPageChanged( wxNotebookEvent& event );

    void OnTitleTextUpdated( wxCommandEvent& event );

    // AlbumGenPanel event handler declarations

    // AlbumGenPanel member function declarations

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
    // AlbumGenPanel member function declarations

    // Should we show tooltips?
    static bool ShowToolTips( );

//    void SetStamp( Catalog::Stamp* stamp );
    void UpdateStatus( );


    CatalogPanel* GetCatalogPanel(){ return m_mngCatalogData;};
    AlbumPanel* GetAlbumPanel(){ m_albumSplitterWindow->GetAlbumPanel();};
   // * GetCatalogTree( ) { return m_catalogTreeCtrl; };

    // AlbumGenPanel member variables
    wxNotebook* m_notebook;
   // AlbumGenDialog* m_albumGenDialog;
    wxFlexGridSizer* m_sizer;
    // AlbumGenPanel member variables
    CatalogPanel* m_mngCatalogData;
    wxTreeItemId m_draggedItem;
//    Catalog::Stamp* m_stamp;
    wxTreeItemId m_currentItem;
    AlbumSplitterWindow* m_albumSplitterWindow;
    DescriptionPanel* m_descriptionPanel;
};

#endif
// _ALBUMGENERATORPANEL_H_
