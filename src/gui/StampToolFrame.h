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
 **************************************************/


#ifndef _STAMPTOOLFRAME_H_
#define _STAMPTOOLFRAME_H_

 /*
  * Includes
  */

#include <vector>
#include "wx/frame.h"
#include "gui/GuiDefs.h"
  //#include "gui/WebRequest.h"

    /*
     * Forward declarations
     */
     //namespace Catalog { class Stamp; };

class StampToolPanel;

class wxButton;
//class CatalogSectionData;

class CatalogPanel;
//class CatalogTreeCtrl;
class AlbumDesignTreePanel;

//class WebViewPanel;

/*
 * Control identifiers
 */


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
    ID_SAVEPROJECT,
    ID_SAVEDESIGN,
    ID_SAVECATALOG,
    ID_SAVEASPROJECT,
    ID_SAVEASDESIGN,
    ID_SAVEASCATALOG,
    ID_NEWPROJECT,
    ID_NEWDESIGN,
    ID_NEWCATALOG,
    ID_CATALOGMENU,
    ID_GENERATEPDF,
    ID_DESIGNMENU,
    ID_STAMPTOOLPANELFOREIGN = ID_STAMPTOOLPANEL
};

#define SYMBOL_STAMPTOOLFRAME_STYLE                                         \
    wxDEFAULT_FRAME_STYLE | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU        \
        | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
#define SYMBOL_STAMPTOOLFRAME_TITLE _( "StampToolFrame" )
#define SYMBOL_STAMPTOOLFRAME_IDNAME ID_STAMPTOOLFRAME
#define SYMBOL_STAMPTOOLFRAME_SIZE wxSize( 1800, 1200 )
#define SYMBOL_STAMPTOOLFRAME_POSITION wxDefaultPosition

/**
 * @todo rework main menu
 *
 **************************************************/


 /**
  * @brief  This is the application main frame.
  * @details This class contains the main menu and main window, StampToolPanel.
  * It inherits from wxFrame.
  *
  */
class StampToolFrame: public wxFrame
{
    DECLARE_CLASS( StampToolFrame )
        DECLARE_EVENT_TABLE( )

public:

    /**
     * @brief Default Constructor a new StampToolFrame object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
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
     **************************************************/
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
     **************************************************/
    bool Create( wxWindow* parent,
        wxWindowID id = SYMBOL_STAMPTOOLFRAME_IDNAME,
        const wxString& caption = SYMBOL_STAMPTOOLFRAME_TITLE,
        const wxPoint& pos = SYMBOL_STAMPTOOLFRAME_POSITION,
        const wxSize& size = SYMBOL_STAMPTOOLFRAME_SIZE,
        long style = SYMBOL_STAMPTOOLFRAME_STYLE );


    ~StampToolFrame( );

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

    // StampToolFrame event handler declarations

   //  CLOSE_WINDOW event handler for ID_STAMPTOOLFRAME
    void OnCloseWindow( wxCloseEvent& event );

    //  ICONIZE event handler for ID_STAMPTOOLFRAME
    void OnIconize( wxIconizeEvent& event );

    //  MAXIMIZE event handler for ID_STAMPTOOLFRAME
    void OnMaximize( wxMaximizeEvent& event );

    //  COMMAND_MENU_SELECTED event handler for wxID_NEW
    void OnNewProjectClick( wxCommandEvent& event );
    void OnNewDesignClick( wxCommandEvent& event );
    void OnNewCatalogClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for wxID_OPEN
    void OnOpenProjectClick( wxCommandEvent& event );
    void OnOpenDesignClick( wxCommandEvent& event );
    void OnOpenCatalogClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for wxID_SAVE
    void OnSaveProjectClick( wxCommandEvent& event );
    void OnSaveDesignClick( wxCommandEvent& event );
    void OnSaveCatalogClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for wxID_SAVEAS
    void OnSaveasProjectClick( wxCommandEvent& event );
    void OnSaveasDesignClick( wxCommandEvent& event );
    void OnSaveasCatalogClick( wxCommandEvent& event );

    void OnGeneratePDFClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for ID_IMPORT
    void OnCSVImportClick( wxCommandEvent& event );
    //   void OnAEImportClick( wxCommandEvent &event );

       //  COMMAND_MENU_SELECTED event handler for wxID_REVERT_TO_SAVED
    void OnRevertToSavedClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for wxID_EXIT
    void OnExitClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for ID_TEXTSERCHMENUITEM
    void OnTextserchmenuitemClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for ID_SORTORDER
    void OnSortOrderClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW
    void OnItemviewClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD
    void OnDefineperiodClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for ID_SETTINGS
    void OnSettingsClick( wxCommandEvent& event );

    //  COMMAND_MENU_SELECTED event handler for ID_MERGE
    void OnMergeClick( wxCommandEvent& event );

    void SetupRecentMenu( );
    void DoRecentSelection( wxCommandEvent& event );
    void OnRecentmenuUpdate( wxUpdateUIEvent& event );
    void DoDefinePeriodDialog( );
    void DoSettingsDialog( );


    // StampToolFrame member function declarations

    // 
    static bool ShowToolTips( );

    //void SetStamp( wxXmlNode *stamp );
    void UpdateStatus( );

    void DoCSVImport( );

    void NewProject( );
    void NewDesign( );
    void NewCatalog( );

    void OpenProject( );
    void OpenDesign( );
    void OpenCatalog( );

    void SaveProject( );
    void SaveDesign( );
    void SaveCatalog( );

    void SaveAsProject( );
    void SaveAsDesign( );
    void SaveAsCatalog( );

    void SaveCatalogXML( wxString filename );
    // void LoadXML( wxString filename );
    void InitLoad( );
    //void LinkAlbumToCat( Design::LayoutBase* child, Catalog::CatalogSectionData* stampData );
   // void LinkNodes( Design::LayoutBase* child, Catalog::CatalogSectionData* stampData  );

    //void ( );

    void DoSortOrderDialog( );

    int QueryMerge( int& mergeMethod );
    int DoQueryMerge( int& mergeMethod );


    void GetSetupData( int& mergeProcedure, wxXmlNode** currItem,
        wxXmlNode** mergeItem );

    int ImageGallery( );

    StampToolPanel* GetStampToolPanel( ) { return m_stampToolPanel; }
    CatalogPanel* GetAlbumPagePanel( );
    CatalogPanel* GetCatalogPagePanel( );
    //    WebViewPanel* GetWebViewPage( );
    //    WebRequest* GetWebRequest( ) { return &m_webRequest; };

    StampToolPanel* m_stampToolPanel;
    //CatalogPanel* m_catalogPagePanel;
    //CatalogPanel* m_albumPagePanel;
    AlbumDesignTreePanel* m_albumDesignTreePanel;
    //    WebRequest m_webRequest;

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
    //Catalog::Stamp *m_stamp;



};

#endif
// _STAMPTOOLFRAME_H_
