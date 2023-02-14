/**
 * @file CatalogCodePanel.h
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
 *
 **************************************************/


#ifndef _CatalogCode_H_
#define _CatalogCode_H_

 /*!
  * Includes
  */

#include <vector>
#include <wx/dataview.h>
#include "wx/grid.h"

#include "catalog/Entry.h"
#include "gui/GuiDefs.h"
  /*!
   * Forward declarations
   */


class wxGrid;


/*!
 * Control identifiers
 */

#define SYMBOL_CATALOGCODEPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_CATALOGCODEPANEL_TITLE _( "CatalogCode" )
#define SYMBOL_CATALOGCODEPANEL_IDNAME ID_CATALOGCODEPANEL
#define SYMBOL_CATALOGCODEPANEL_SIZE wxSize( 800, 200 )
#define SYMBOL_CATALOGCODEPANEL_POSITION wxDefaultPosition

 /*!
  * CatalogCodePanel class declaration
  */

class CatalogCodePanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( CatalogCodePanel )
        DECLARE_EVENT_TABLE( )

public:
    enum  CatalogCodePanelGuiDefs
    {
        ID_GRID = ID_CATALOGCODEPANEL + 1,
    };
    
    // Constructors
    /**
     * @brief Default Constructor a new CatalogCodePanel object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
    CatalogCodePanel( );

    /**
     * @brief Construct a new CatalogCodePanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    CatalogCodePanel( wxWindow* parent,
        wxWindowID id = SYMBOL_CATALOGCODEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_CATALOGCODEPANEL_POSITION,
        const wxSize& size = SYMBOL_CATALOGCODEPANEL_SIZE,
        long style = SYMBOL_CATALOGCODEPANEL_STYLE );

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
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGCODEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_CATALOGCODEPANEL_POSITION,
        const wxSize& size = SYMBOL_CATALOGCODEPANEL_SIZE,
        long style = SYMBOL_CATALOGCODEPANEL_STYLE );

    // Destructor
    ~CatalogCodePanel( );

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


    /**
     * @brief wxEVT_CONTEXT_MENU event handler for ID_CatalogCodePANEL
     *
     * @param event  Contains information about context menu events
     **************************************************/
    void OnContextMenu( wxContextMenuEvent& event );


    /**
     * @brief wxEVT_GRID_CELL_CHANGED event handler for ID_GRID
     *
     * @param event   Contains information about grid events
     **************************************************/
    void OnCellChanged( wxGridEvent& event );


    /**
     * @brief Retrieves bitmap resources
     *
     * @param  name ( autogenerated. Dummy. )
     * @return wxBitmap null
     **************************************************/
    wxBitmap GetBitmapResource( const wxString& name );

    /**
     * @brief Get the Icon Resource objectRetrieves icon resources
     *
     * @param  name ( autogenerated. Dummy. )
     * @return wxIcon null
     **************************************************/
    wxIcon GetIconResource( const wxString& name );
    // CatalogCodePanel member function declarations

   /**
    * @brief Should we show tooltips?
    *
    * @return bool ( autogenerated. Dummy. Always true )
    **************************************************/
    static bool ShowToolTips( );

    /**
     * @brief Load the grid with the CatalogCode items
     *
     **************************************************/
    void ShowEntry( );

    /**
     * @brief Set the Entry object
     *
     * @param entry  set the currently displayed entry to this
     **************************************************/
    void SetStamp( Catalog::Entry* entry );

    void SetDataEditable( bool val );

    /**
     * @brief shows context menu to add or remove CatalogCode entries
     *
     * @param event   Contains information about command events
     **************************************************/
    void OnContextPopup( wxCommandEvent& event );

    /**
     * @brief Add an intery to the wxGrid
     *
     * @return int index of the new row
     **************************************************/
    int AddNewRow( );

    /**
     * @brief creates a new empty catalog code
     *
     **************************************************/
    wxXmlNode* InitNewCatCode( );

    /**
     * @brief gets the item from the CatalogCode list and populates the columns with it
     *
     * @param row index of row to populate
     **************************************************/
    void ShowRow( int row );

private:

    wxGrid* m_grid;  ///< wxGrid to display item entries
    Catalog::Entry* m_entry; ///< pointer to the currently displayed entry 
    std::vector<wxXmlNode*> m_catCodeList;  ///< list containing each of the entries
};

#endif
// _CatalogCode_H_
