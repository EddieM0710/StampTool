/**
 * @file AlbumGeneratorFrame.h
 * @author Eddie Monroe ()
 * @brief This is the application main frame.
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 **************************************************/


#ifndef _ALBUMGENERATORFRAME_H_
#define _ALBUMGENERATORFRAME_H_

/*!
 * Includes
 */

 
#include "wx/frame.h"
 

#include <wx/dynarray.h>
#include <vector>

#include "Classification.h"
#include "Stamp.h"

//#include <wx/dnd.h>
/*!
 * Forward declarations
 */

 
class AlbumGeneratorPanel;
 
class wxButton;
class CatalogData;

class ManageCatalogData;
class CatalogDataTreeCtrl;
class ManageAECmdData;
/*!
 * Control identifiers
 */

 

#define ID_IMPORT ID_ALBUMGENERATORFRAME+1
#define ID_TEXTSERCHMENUITEM ID_ALBUMGENERATORFRAME+2
#define ID_IMAGEGALERYMENUITEM ID_ALBUMGENERATORFRAME+3
#define ID_MENUITEM ID_ALBUMGENERATORFRAME+4

#define ID_SORTORDER ID_ALBUMGENERATORFRAME+5
#define ID_ITEMVIEW ID_ALBUMGENERATORFRAME+6
#define ID_DEFINEPERIOD ID_ALBUMGENERATORFRAME+7
#define ID_LOADIMAGESMENUITEM ID_ALBUMGENERATORFRAME+8
#define ID_TESTXMLMENUITEM ID_ALBUMGENERATORFRAME+9
#define ID_RECENT ID_ALBUMGENERATORFRAME+10
#define ID_RECENTMENU ID_ALBUMGENERATORFRAME+19
#define ID_SETTINGS ID_ALBUMGENERATORFRAME+20
#define ID_MERGE ID_ALBUMGENERATORFRAME+21
#define ID_PREFERENCES  ID_ALBUMGENERATORFRAME+22
#define ID_ALBUMGENMENUITEM ID_ALBUMGENERATORFRAME+23
#define ID_CSVIMPORT ID_ALBUMGENERATORFRAME+24
#define ID_AEIMPORT ID_ALBUMGENERATORFRAME+25
#define ID_ALBUMGENERATORPANELFOREIGN ID_ALBUMGENERATORPANEL
#define SYMBOL_ALBUMGENERATORFRAME_STYLE                                         \
    wxDEFAULT_FRAME_STYLE | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU        \
        | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
#define SYMBOL_ALBUMGENERATORFRAME_TITLE _( "AlbumGeneratorFrame" )
#define SYMBOL_ALBUMGENERATORFRAME_IDNAME ID_ALBUMGENERATORFRAME
#define SYMBOL_ALBUMGENERATORFRAME_SIZE wxSize( 1200, 600 )
#define SYMBOL_ALBUMGENERATORFRAME_POSITION wxDefaultPosition
 
/**
 * @todo rework main menu
 * 
 **************************************************/


/**
 * @brief  This is the application main frame.
 * @details This class contains the main menu and main window, AlbumGeneratorPanel. 
 * It inherits from wxFrame.
 * 
 */
class AlbumGeneratorFrame : public wxFrame
{
    DECLARE_CLASS( AlbumGeneratorFrame )
    DECLARE_EVENT_TABLE( )

  public:
    // Constructors
    /**
     * @brief Default Constructor a new AlbumGeneratorFrame object
     * @details Must be used in conjunction with Create.
     * 
     **************************************************/
    AlbumGeneratorFrame( );

    /**
     * @brief Construct a new AlbumGeneratorFrame object
     * 
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style. 
     * @see wxPanel.
     **************************************************/
    AlbumGeneratorFrame( wxWindow *parent,
                       wxWindowID id = SYMBOL_ALBUMGENERATORFRAME_IDNAME,
                       const wxString &caption = SYMBOL_ALBUMGENERATORFRAME_TITLE,
                       const wxPoint &pos = SYMBOL_ALBUMGENERATORFRAME_POSITION,
                       const wxSize &size = SYMBOL_ALBUMGENERATORFRAME_SIZE,
                       long style = SYMBOL_ALBUMGENERATORFRAME_STYLE );

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
    bool Create( wxWindow *parent,
                 wxWindowID id = SYMBOL_ALBUMGENERATORFRAME_IDNAME,
                 const wxString &caption = SYMBOL_ALBUMGENERATORFRAME_TITLE,
                 const wxPoint &pos = SYMBOL_ALBUMGENERATORFRAME_POSITION,
                 const wxSize &size = SYMBOL_ALBUMGENERATORFRAME_SIZE,
                 long style = SYMBOL_ALBUMGENERATORFRAME_STYLE );

    // Destructor
    ~AlbumGeneratorFrame( );

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

     // AlbumGeneratorFrame event handler declarations

    // wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME
    void OnCloseWindow( wxCloseEvent &event );

    // wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME
    void OnIconize( wxIconizeEvent &event );

    // wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME
    void OnMaximize( wxMaximizeEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN
    void OnOpenClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE
    void OnSaveClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS
    void OnSaveasClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT
    void OnCSVImportClick( wxCommandEvent &event );
    void OnAEImportClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_REVERT_TO_SAVED
    void OnRevertToSavedClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
    void OnExitClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TEXTSERCHMENUITEM
    void OnTextserchmenuitemClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMAGEGALERYMENUITEM
    void OnImagegalerymenuitemClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM
    void OnCVSReportMenuItemClick( wxCommandEvent &event );

    void OnAlbumGenMenuItemClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER
    void OnSortOrderClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW
    void OnItemviewClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD
    void OnDefineperiodClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_LOADIMAGESMENUITEM
    void OnLoadimagesmenuitemClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TESTXMLMENUITEM
    void OnTestXMLClick( wxCommandEvent &event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS
    void OnSettingsClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE
    void OnMergeClick( wxCommandEvent& event );

    void SetupRecentMenu(  );
    void DoRecentSelection(wxCommandEvent& event);
    void OnRecentmenuUpdate( wxUpdateUIEvent& event );
    void DoDefinePeriodDialog();
    void DoSettingsDialog();
     // AlbumGeneratorFrame event handler declarations

     // AlbumGeneratorFrame member function declarations

    /**
     * @brief Retrieves bitmap resources
     * 
     * @param  name (autogenerated. Dummy.)
     * @return wxBitmap null
     **************************************************/
    wxBitmap GetBitmapResource( const wxString &name );

    /**
     * @brief Get the Icon Resource objectRetrieves icon resources
     * 
     * @param  name (autogenerated. Dummy.)
     * @return wxIcon null
     **************************************************/
    wxIcon GetIconResource( const wxString &name );


    // AlbumGeneratorFrame member function declarations

    // Should we show tooltips?
    static bool ShowToolTips( );

    void SetStamp( wxXmlNode *stamp );
    void UpdateStatus( );

    void DoCSVImport( );
    void DoAEImport( );
    void Open( );
    void Save( );
    void SaveAs( );
    void SaveCatalogXML( wxString filename );
    void LoadXML( wxString filename );
    void InitLoad( );

    void DoSortOrderDialog( );
    bool GetFile( wxString newFile, wxString imageName );

    int QueryMerge( int &mergeMethod );
    int DoQueryMerge( int& mergeMethod  );


    void GetSetupData( int &mergeProcedure, wxXmlNode **currItem,
                       wxXmlNode **mergeItem );
//    CatalogDataTreeCtrl *GetCatalogDataTree( );
    int ImageGallery( );

     // AlbumGeneratorFrame member variables
    AlbumGeneratorPanel *m_albumGeneratorPanel;
    ManageCatalogData* m_catalogDataManager;
    ManageAECmdData* m_AECmdDataManager;
     // AlbumGeneratorFrame member variables

    // container data classification sort order
    wxArrayInt m_sortOrder;
    wxMenu* m_fileMenu;
    wxMenu* m_recentMenu;
    wxMenu* m_preferencesMenu;
    wxMenu* m_importMenu;
    typedef struct {
        wxMenuItem* item;
        int id;
    } RecentListItem;
    std::vector<RecentListItem*> m_menuItemList;
    Stamp *m_stamp;
};

#endif
// _ALBUMGENERATORFRAME_H_
