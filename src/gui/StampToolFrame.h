/**
 * @file gui/StampToolFrame.h
 * @author Eddie Monroe ( )
 * @brief This is the application main frame.
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


#ifndef _STAMPTOOLFRAME_H_
#define _STAMPTOOLFRAME_H_


#include <vector>
#include "wx/frame.h"
#include "gui/GuiDefs.h"
#include "utils/StampList.h"

 //namespace Catalog { class Stamp; };

class StampToolPanel;

class wxButton;
//class CatalogVolume;

class CatalogPanel;
//class CatalogTreeCtrl;
class AlbumTreePanel;
class AlbumPanel;
//class WebViewPanel;
namespace {
    class StampList;
}



enum {
    ID_TEXTSERCHMENUITEM = ID_STAMPTOOLFRAME,
    ID_SORTORDER,
    ID_ITEMVIEW,
    ID_DEFINEPERIOD,
    ID_RECENT,
    ID_RECENTMENU,
    ID_SETTINGS,
    ID_MERGE,
    ID_PREFERENCES,
    ID_CSVIMPORT,
    ID_OPENPROJECT,
    ID_OPENDESIGN,
    ID_OPENCATALOG,
    ID_REMOVECATALOG,
    ID_REMOVEDESIGN,
    ID_SAVEPROJECT,
    ID_SAVEDESIGN,
    ID_SAVECATALOG,
    ID_SAVEASPROJECT,
    ID_SAVEASDESIGN,
    ID_SAVEASCATALOG,
    ID_NEWPROJECT,
    ID_NEWDESIGN,
    ID_NEWCATALOG,
    ID_OPENCOLLECTION,
    ID_ADDCOLLECTION,
    ID_CATALOGMENU,
    ID_GENERATEPDF,
    ID_OPENPDF,
    ID_DESIGNMENU,
    ID_STAMPTOOLPANELFOREIGN = ID_STAMPTOOLPANEL
};

#define SYMBOL_STAMPTOOLFRAME_STYLE                                         \
    wxDEFAULT_FRAME_STYLE | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU        \
        | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
#define SYMBOL_STAMPTOOLFRAME_TITLE _( "Stamp Tool" )
#define SYMBOL_STAMPTOOLFRAME_IDNAME ID_STAMPTOOLFRAME
#define SYMBOL_STAMPTOOLFRAME_SIZE wxSize( 1800, 1200 )
#define SYMBOL_STAMPTOOLFRAME_POSITION wxDefaultPosition

/**
 * @brief  This is the application main frame.
 * @details This class contains the main menu and main window, StampToolPanel.
 * It inherits from wxFrame.
 *
 */
class StampToolFrame : public wxFrame
{
    DECLARE_CLASS( StampToolFrame )
    DECLARE_EVENT_TABLE( )

public:

    /**
     * @brief Default Constructor a new StampToolFrame object
     * @details Must be used in conjunction with Create.
     *
     */
    StampToolFrame( );

    /**
     * @brief Construct a new StampToolFrame object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     */
    StampToolFrame( wxWindow* parent,
        wxWindowID id = SYMBOL_STAMPTOOLFRAME_IDNAME,
        const wxString& caption = SYMBOL_STAMPTOOLFRAME_TITLE,
        const wxPoint& pos = SYMBOL_STAMPTOOLFRAME_POSITION,
        const wxSize& size = SYMBOL_STAMPTOOLFRAME_SIZE,
        long style = SYMBOL_STAMPTOOLFRAME_STYLE );

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
        wxWindowID id = SYMBOL_STAMPTOOLFRAME_IDNAME,
        const wxString& caption = SYMBOL_STAMPTOOLFRAME_TITLE,
        const wxPoint& pos = SYMBOL_STAMPTOOLFRAME_POSITION,
        const wxSize& size = SYMBOL_STAMPTOOLFRAME_SIZE,
        long style = SYMBOL_STAMPTOOLFRAME_STYLE );

    ~StampToolFrame( );

    void SetCaption( wxString caption )
    {
        wxString str = SYMBOL_STAMPTOOLFRAME_TITLE + " - " + caption;
        SetTitle( str );
    }
    /**
     * @brief   Initialises member variables
     *
     */
    void Init( );

    /**
     * @brief Creates the controls and sizers
     *
     */
    void CreateControls( );

    void OnCloseWindow( wxCloseEvent& event );

    void OnIconize( wxIconizeEvent& event );

    void OnMaximize( wxMaximizeEvent& event );

    void OnNewProjectClick( wxCommandEvent& event );

    void OnOpenProjectClick( wxCommandEvent& event );

    void OnSaveProjectClick( wxCommandEvent& event );

    void OnSaveCatalogClick( wxCommandEvent& event );

    void OnSaveasProjectClick( wxCommandEvent& event );

    //void OnGeneratePDFClick( wxCommandEvent& event );

    void OnExitClick( wxCommandEvent& event );

    void OnTextSearchMenuItemClick( wxCommandEvent& event );

    void OnSortOrderClick( wxCommandEvent& event );

    void OnItemviewClick( wxCommandEvent& event );

    void OnDefinePeriodClick( wxCommandEvent& event );

    void OnSettingsClick( wxCommandEvent& event );

    void OnOpenCatalogClick( wxCommandEvent& event );
    void OnNewCatalogClick( wxCommandEvent& event );
    void OnImportCatalogClick( wxCommandEvent& event );
    void OnRemoveCatalogClick( wxCommandEvent& event );
    void OnNewDesignClick( wxCommandEvent& event );
    void OnOpenDesignClick( wxCommandEvent& event );
    void OnGeneratePDFClick( wxCommandEvent& event );
    void OnOpenPDFClick( wxCommandEvent& event );
    void OnRemoveDesignClick( wxCommandEvent& event );
    void OnSaveDesignClick( wxCommandEvent& event );
    void OnMergeClick( wxCommandEvent& event );

    void SetupRecentMenu( );

    void DoRecentSelection( wxCommandEvent& event );

    void OnRecentmenuUpdate( wxUpdateUIEvent& event );

    void DoDefinePeriodDialog( );

    void DoSettingsDialog( );

    static bool ShowToolTips( );

    void UpdateStatus( );

    void NewProject( );

    void OpenPdf( );
    void OpenProject( );

    void SaveProject( );

    void SaveAsProject( );

    void InitLoad( );

    void DoSortOrderDialog( );

    int QueryMerge( int& mergeMethod );

    int DoQueryMerge( int& mergeMethod );

    StampToolPanel* GetStampToolPanel( ) {
        return m_stampToolPanel;
    };

    CatalogPanel* GetCatalogPagePanel( );

    AlbumPanel* GetAlbumPanel( );

    StampToolPanel* m_stampToolPanel;

    AlbumTreePanel* m_albumTreePanel;

    AlbumPanel* m_albumAlbumPanel;

    // container data classification sort order
    wxArrayInt m_sortOrder;
    wxMenu* m_fileMenu;
    wxMenu* m_newMenu;
    wxMenu* m_openMenu;
    wxMenu* m_saveMenu;
    wxMenu* m_saveAsMenu;
    wxMenu* m_recentMenu;
    wxMenu* m_preferencesMenu;
    wxMenu* m_importMenu;
    typedef struct {
        wxMenuItem* item;
        int id;
    } RecentListItem;
    std::vector<RecentListItem*> m_menuItemList;

};

#endif

