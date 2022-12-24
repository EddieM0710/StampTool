/**
 * @file gui/AlbumGenFrame.h
 * @author Eddie Monroe ()
 * @brief This is the application main frame.
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


#ifndef _ALBUMGENERATORFRAME_H_
#define _ALBUMGENERATORFRAME_H_

 /*!
  * Includes
  */


#include "wx/frame.h"

#include "gui/GuiDefs.h"
  //#include <wx/dynarray.h>
#include <vector>

//#include "catalog/Classification.h"
//#include "catalog/Entry.h"

//#include <wx/dnd.h>
/*!
 * Forward declarations
 */
 //namespace Catalog { class Stamp; };

class AlbumGenPanel;

class wxButton;
////class CatalogVolumeData;

class CatalogPanel;
//class CatalogTreeCtrl;
class AlbumDesignTreePanel;
/*!
 * Control identifiers
 */

 //#define ID_IMPORT ID_ALBUMGENERATORFRAME+1
#define ID_TEXTSERCHMENUITEM ID_ALBUMGENERATORFRAME+2
#define ID_SORTORDER ID_ALBUMGENERATORFRAME+3
#define ID_ITEMVIEW ID_ALBUMGENERATORFRAME+4
#define ID_DEFINEPERIOD ID_ALBUMGENERATORFRAME+5
#define ID_RECENT ID_ALBUMGENERATORFRAME+6
#define ID_RECENTMENU ID_ALBUMGENERATORFRAME+7
#define ID_SETTINGS ID_ALBUMGENERATORFRAME+8
#define ID_MERGE ID_ALBUMGENERATORFRAME+9
#define ID_PREFERENCES  ID_ALBUMGENERATORFRAME+10
#define ID_CSVIMPORT ID_ALBUMGENERATORFRAME+12
#define ID_OPENPROJECT ID_ALBUMGENERATORFRAME+13
#define ID_OPENDESIGN ID_ALBUMGENERATORFRAME+14
#define ID_OPENCATALOG ID_ALBUMGENERATORFRAME+15
#define ID_SAVEPROJECT ID_ALBUMGENERATORFRAME+16
#define ID_SAVEDESIGN ID_ALBUMGENERATORFRAME+17
#define ID_SAVECATALOG ID_ALBUMGENERATORFRAME+18
#define ID_SAVEASPROJECT ID_ALBUMGENERATORFRAME+19
#define ID_SAVEASDESIGN ID_ALBUMGENERATORFRAME+20
#define ID_SAVEASCATALOG ID_ALBUMGENERATORFRAME+21
#define ID_GENERATEODT ID_ALBUMGENERATORFRAME+22
#define ID_NEWPROJECT ID_ALBUMGENERATORFRAME+23
#define ID_NEWDESIGN ID_ALBUMGENERATORFRAME+24
#define ID_NEWCATALOG ID_ALBUMGENERATORFRAME+25
#define ID_CATALOGMENU ID_ALBUMGENERATORFRAME+26
#define ID_DESIGNMENU ID_ALBUMGENERATORFRAME+27
#define ID_ALBUMGENERATORPANELFOREIGN ID_ALBUMGENERATORPANEL
#define SYMBOL_ALBUMGENERATORFRAME_STYLE                                         \
    wxDEFAULT_FRAME_STYLE | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU        \
        | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
#define SYMBOL_ALBUMGENERATORFRAME_TITLE _( "AlbumGenFrame" )
#define SYMBOL_ALBUMGENERATORFRAME_IDNAME ID_ALBUMGENERATORFRAME
#define SYMBOL_ALBUMGENERATORFRAME_SIZE wxSize( 1800, 1200 )
#define SYMBOL_ALBUMGENERATORFRAME_POSITION wxDefaultPosition

/**
 * @todo rework main menu
 *
 **************************************************/


 /**
  * @brief  This is the application main frame.
  * @details This class contains the main menu and main window, AlbumGenPanel.
  * It inherits from wxFrame.
  *
  */
class AlbumGenFrame: public wxFrame
{
    DECLARE_CLASS( AlbumGenFrame )
        DECLARE_EVENT_TABLE( )

public:
    // Constructors
    /**
     * @brief Default Constructor a new AlbumGenFrame object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
    AlbumGenFrame( );

    /**
     * @brief Construct a new AlbumGenFrame object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    AlbumGenFrame( wxWindow* parent,
        wxWindowID id = SYMBOL_ALBUMGENERATORFRAME_IDNAME,
        const wxString& caption = SYMBOL_ALBUMGENERATORFRAME_TITLE,
        const wxPoint& pos = SYMBOL_ALBUMGENERATORFRAME_POSITION,
        const wxSize& size = SYMBOL_ALBUMGENERATORFRAME_SIZE,
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
    bool Create( wxWindow* parent,
        wxWindowID id = SYMBOL_ALBUMGENERATORFRAME_IDNAME,
        const wxString& caption = SYMBOL_ALBUMGENERATORFRAME_TITLE,
        const wxPoint& pos = SYMBOL_ALBUMGENERATORFRAME_POSITION,
        const wxSize& size = SYMBOL_ALBUMGENERATORFRAME_SIZE,
        long style = SYMBOL_ALBUMGENERATORFRAME_STYLE );

    // Destructor
    ~AlbumGenFrame( );

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

    // AlbumGenFrame event handler declarations

   // wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME
    void OnCloseWindow( wxCloseEvent& event );

    // wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME
    void OnIconize( wxIconizeEvent& event );

    // wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME
    void OnMaximize( wxMaximizeEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_NEW
    void OnNewProjectClick( wxCommandEvent& event );
    void OnNewDesignClick( wxCommandEvent& event );
    void OnNewCatalogClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN
    void OnOpenProjectClick( wxCommandEvent& event );
    void OnOpenDesignClick( wxCommandEvent& event );
    void OnOpenCatalogClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE
    void OnSaveProjectClick( wxCommandEvent& event );
    void OnSaveDesignClick( wxCommandEvent& event );
    void OnSaveCatalogClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS
    void OnSaveasProjectClick( wxCommandEvent& event );
    void OnSaveasDesignClick( wxCommandEvent& event );
    void OnSaveasCatalogClick( wxCommandEvent& event );

    void OnGenerateODTClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT
    void OnCSVImportClick( wxCommandEvent& event );
    //   void OnAEImportClick( wxCommandEvent &event );

       // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_REVERT_TO_SAVED
    void OnRevertToSavedClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
    void OnExitClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TEXTSERCHMENUITEM
    void OnTextserchmenuitemClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER
    void OnSortOrderClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW
    void OnItemviewClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD
    void OnDefineperiodClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS
    void OnSettingsClick( wxCommandEvent& event );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE
    void OnMergeClick( wxCommandEvent& event );

    void SetupRecentMenu( );
    void DoRecentSelection( wxCommandEvent& event );
    void OnRecentmenuUpdate( wxUpdateUIEvent& event );
    void DoDefinePeriodDialog( );
    void DoSettingsDialog( );
    // AlbumGenFrame event handler declarations

    // AlbumGenFrame member function declarations

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


    // AlbumGenFrame member function declarations

    // Should we show tooltips?
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
    //void LinkAlbumToCat( Design::LayoutBase* child, Catalog::CatalogVolumeData* stampData );
   // void LinkNodes( Design::LayoutBase* child, Catalog::CatalogVolumeData* stampData  );

    void GenerateODTAlbum( );

    void DoSortOrderDialog( );

    int QueryMerge( int& mergeMethod );
    int DoQueryMerge( int& mergeMethod );


    void GetSetupData( int& mergeProcedure, wxXmlNode** currItem,
        wxXmlNode** mergeItem );

    int ImageGallery( );

    AlbumGenPanel* GetAlbumGenPanel( ) { return m_albumGeneratorPanel; }
    CatalogPanel* GetCatalogPanel( );

    // AlbumGenFrame member variables
    AlbumGenPanel* m_albumGeneratorPanel;
    CatalogPanel* m_catalogPanel;
    AlbumDesignTreePanel* m_albumDesignTreePanel;
    // AlbumGenFrame member variables

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
// _ALBUMGENERATORFRAME_H_
