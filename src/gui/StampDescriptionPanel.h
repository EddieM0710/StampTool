/**
 * @file StampDescriptionPanel.h
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


#ifndef _DISCRIPTIONPANEL_H_
#define _DISCRIPTIONPANEL_H_

 /*!
  * Includes
  */


#include "wx/notebook.h"
#include "wx/splitter.h"
#include <wx/slider.h>

#include "catalog/Entry.h"
#include "Defs.h"
#include "gui/GuiDefs.h"
  /*
   * Forward declarations
   */

class CatalogCodePanel;
class CharacteristicsPanel;
class IdentificationPanel;
class ImagePanel;
class InventoryPanel;
class MiscellaneousDataPanel;

/*
 * Control identifiers
 */

#define ID_HORIZONTALLITTERWINDOW ID_DESCRIPTIONPANEL+1
#define ID_DESCRIPTIONSPLITTERWINDOW ID_DESCRIPTIONPANEL+2
#define ID_IDENTIFICATIONPANELFORIEGN ID_DESCRIPTIONPANEL+3
#define ID_HORIZONTALPLITTERWINDOW ID_DESCRIPTIONPANEL+4
#define ID_ZOOMSLIDER ID_DESCRIPTIONPANEL+5
#define ID_STAMPIMAGEPANEL ID_DESCRIPTIONPANEL+6
#define ID_DESCRIPTIONLNOTEBOOK ID_DESCRIPTIONPANEL+7
#define ID_INVENTORYFOREIGN ID_DESCRIPTIONPANEL+8
#define ID_CATALOGCODEFOREIGN ID_DESCRIPTIONPANEL+8
#define ID_CHARACTERISTICSWINDOW ID_DESCRIPTIONPANEL+9
#define ID_MISCELLANEOUSDATAFORIEGN ID_DESCRIPTIONPANEL+10
#define ID_DESCRIPTIONSCROLLEDWINDOW ID_DESCRIPTIONPANEL+11
#define ID_DESCRIPTIONTEXTCTRL ID_DESCRIPTIONPANEL+12
#define ID_BACKGROUNDPANEL1 ID_DESCRIPTIONPANEL+13
#define ID_BKGNDSCROLLEDWINDOW ID_DESCRIPTIONPANEL+14
#define ID_BKGNDTEXTCTRL ID_DESCRIPTIONPANEL+15
#define ID_NOTEBOOKPANEL  ID_DESCRIPTIONPANEL+16
#define SYMBOL_DESCRIPTIONPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_DESCRIPTIONPANEL_TITLE _( "DescriptionPanel" )
#define SYMBOL_DESCRIPTIONPANEL_IDNAME ID_DESCRIPTIONPANEL
#define SYMBOL_DESCRIPTIONPANEL_SIZE wxDefaultSize
#define SYMBOL_DESCRIPTIONPANEL_POSITION wxDefaultPosition



 /**
  * @brief StampDescriptionPanel class declaration.
  * @details This panel contains ImagePanel to display the stamp, An
  * IdentificationPanel to display the ID info and a wxNotebook that manages the
  * InventoryPanel, the CharacteristicsPanel,the MiscellaneousDataPanel and pages for
  * displaying discription and background info. This class inherits from wxPanel.
  *
  **************************************************/
class StampDescriptionPanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( StampDescriptionPanel )
    DECLARE_EVENT_TABLE( )

public:
    /**
     * @brief Default Constructor for a new Description Panel object
     *
     **************************************************/
    StampDescriptionPanel( void );


    /**
     * @brief Construct a new Description Panel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    StampDescriptionPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_DESCRIPTIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_DESCRIPTIONPANEL_POSITION,
        const wxSize& size = SYMBOL_DESCRIPTIONPANEL_SIZE,
        long style = SYMBOL_DESCRIPTIONPANEL_STYLE );

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
        wxWindowID id = SYMBOL_DESCRIPTIONPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_DESCRIPTIONPANEL_POSITION,
        const wxSize& size = SYMBOL_DESCRIPTIONPANEL_SIZE,
        long style = SYMBOL_DESCRIPTIONPANEL_STYLE );

    /**
     * @brief Destroy the Description Panel object
     *
     **************************************************/
    ~StampDescriptionPanel( void );


    /**
     * @brief   Initialises member variables
     *
     **************************************************/
    void Init( void );

    /**
     * @brief Creates the controls and sizers
     *
     **************************************************/
    void CreateControls( void );

    // StampDescriptionPanel event handler declarations


   /**
    * @brief wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_ZOOMSLIDER
    *
    * @param  event contains information about command events
    **************************************************/
    void OnZoomsliderUpdated( wxCommandEvent& event );

    /**
     * @brief wxEVT_COMMAND_TEXT_UPDATED event handler for ID_DESCRIPTIONTEXTCTRL
     *
     * @param  event  Contains information about command events
     **************************************************/
    void OnDescriptionTextctrlTextUpdated( wxCommandEvent& event );

    /**
     * @brief wxEVT_COMMAND_TEXT_UPDATED event handler for ID_BKGNDTEXTCTRL
     *
     * @param  event : Contains information about command events
     **************************************************/
    void OnBkGndTextUpdated( wxCommandEvent& event );

    /**
     * @brief wxEVT_COMMAND_TEXT_MAXLEN event handler for ID_BKGNDTEXTCTRL
     *
     * @param  event : Contains information about command events
     **************************************************/
    void OnBkgndtextctrlMaxLen( wxCommandEvent& event );

    /**
     * @brief wxEVT_LEAVE_WINDOW event handler for ID_BKGNDTEXTCTRL
     *
     * @param  event  Contains information about command events
     **************************************************/
    void OnLeaveWindow( wxMouseEvent& event );

    // StampDescriptionPanel event handler declarations

    // StampDescriptionPanel member function declarations

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

    // StampDescriptionPanel member function declarations

   /**
    * @brief Should we show tooltips?
    *
    * @return true (autogenerated. Returns true.)
    **************************************************/
    static bool ShowToolTips( void );


    /**
     * @brief Initializes the StampDescriptionPanel with new stamp values
     * @param stamp   pointer to current atamp
     **************************************************/
    void SetStamp(  wxXmlNode* stamp );

    void SetDataEditable( bool val );

    /**
     * @brief Update the Status display with the current statss of the selected stamp
     *
     **************************************************/
    void UpdateStatus( void );
private:
    // StampDescriptionPanel member variables
    IdentificationPanel* m_identificationPanel; ///< Pointer to IdentificationPanel
    wxSlider* m_zoomSlider; ///< Pointer to image soom slider
    ImagePanel* m_stampImage; ///< Pointer to stamp image
    InventoryPanel* m_inventoryPanel; ///< Pointer to InventoryPanel
    CatalogCodePanel* m_catalogCodePanel; ///< Pointer to CatalogCodePanel
    CharacteristicsPanel* m_characteristicsPanel; ///< Pointer to CharacteristicsPanel
    MiscellaneousDataPanel* m_miscellaneousDataPanel; ///< Pointer to MiscellaneousDataPanel
 //$     wxTextCtrl* m_description; ///< Pointer to description wxTextCtrl
 //$     wxTextCtrl* m_bkgndText; ///< Pointer to background wxTextCtrl
    // StampDescriptionPanel member variables

    Catalog::Entry* m_stamp; ///< Pointer to currently displayed stamp
};

#endif
// _STAMPDISCRIPTIONPANEL_H_
