/**
 * @file StampToolPanel.h
 * @author Eddie Monroe ( )
 * @brief
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

#ifndef _STAMPTOOLPANEL_H_
#define _STAMPTOOLPANEL_H_

#include "wx/notebook.h"
#include "wx/splitter.h"
#include "wx/treectrl.h"

#include "gui/GuiDefs.h"

#include "gui/AlbumPanel.h"

 //#include "gui/WebViewPanel.h"

class CatalogPanel;
class wxNotebook;
class wxFlexGridSizer;
class StampDescriptionPanel;
class GenerateList;



#define SYMBOL_STAMPTOOLPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_STAMPTOOLPANEL_TITLE _( "StampToolPanel" )
#define SYMBOL_STAMPTOOLPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_STAMPTOOLPANEL_POSITION wxDefaultPosition

/**
 * @brief StampToolPanel is the main window class for the application,
 * It contains wxNotebook with the the StampDescriptionPanel and AlbumPanel as pages.
 * StampToolPanel inherits from wxPanel.
 */
class StampToolPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( StampToolPanel )
        DECLARE_EVENT_TABLE( )

public:

    enum StampToolPanelGuiDefs
    {
        ID_CATALOGSPLITTERWINDOW = ID_STAMPTOOLPANEL + 1,
        ID_CATALOGPAGE,
        ID_STAMPTREECTRL,
        ID_NOTEBOOK,
        ID_DESCRIPTIONPANELFOREIGN,
        ID_GALLERYSCROLLEDWINDOW,
        ID_TITLETEXTCTRL,
        ID_STAMPTOOL,
        ID_ALBUMSPLITTERWINDOWFOREIGN,
        ID_GENERTELISTFOREIGN,
        ID_DESIGNPAGE,
        ID_DESIGNSPLITTERWINDOW
    };

    

        /**
         * @brief Default Constructor a new StampToolPanel object
         * @details Must be used in conjunction with Create.
         *
         */
    StampToolPanel( );

    /**
     * @brief Construct a new StampToolPanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     */
    StampToolPanel( wxWindow* parent,
        wxWindowID id = ID_STAMPTOOLPANEL,
        const wxPoint& pos = SYMBOL_STAMPTOOLPANEL_POSITION,
        const wxSize& size = SYMBOL_STAMPTOOLPANEL_SIZE,
        long style = SYMBOL_STAMPTOOLPANEL_STYLE );

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
     */
    bool Create( wxWindow* parent,
        wxWindowID id = ID_STAMPTOOLPANEL,
        const wxPoint& pos = SYMBOL_STAMPTOOLPANEL_POSITION,
        const wxSize& size = SYMBOL_STAMPTOOLPANEL_SIZE,
        long style = SYMBOL_STAMPTOOLPANEL_STYLE );


    ~StampToolPanel( );

    void Init( );

    void CreateControls( );

    bool ShouldShowStates( );

    void OnNotebookPageChanged( wxNotebookEvent& event );

    void OnTitleTextUpdated( wxCommandEvent& event );

    static bool ShowToolTips( );

    void UpdateStatus( );

    CatalogPanel* GetCatalogPagePanel( ) { return m_catalogTreePanel; };
    CatalogPanel* GetAlbumPagePanel( ) { return m_albumPageCatTreePanel; };
    //    WebViewPanel* GetWebViewPage( ) { return m_webViewPanel; };
    AlbumTreePanel* GetAlbumTreePanel( ) { return m_albumAlbumPanel->GetAlbumTreePanel( ); };
    AlbumPanel* GetAlbumAlbumPanel( ) { return m_albumAlbumPanel; };

    

    wxNotebook* m_notebook;
    wxFlexGridSizer* m_sizer;
    CatalogPanel* m_catalogTreePanel;
    CatalogPanel* m_albumPageCatTreePanel;
    wxSplitterWindow* m_catalogNotebookPage;
    wxSplitterWindow* m_albumNotebookPage;
    wxTreeItemId m_draggedItem;
    wxTreeItemId m_currentItem;
    AlbumPanel* m_albumAlbumPanel;
    StampDescriptionPanel* m_stampDescriptionPanel;
    GenerateList* m_generateListPanel;
    //    WebViewPanel* m_webViewPanel;
};

#endif

