/**
 * @file MiscellaneousDataPanel.h
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
 **************************************************/


#ifndef _MISCELLANEOUSDATA_H_
#define _MISCELLANEOUSDATA_H_

 /*!
  * Includes
  */

#include "catalog/Entry.h"
#include "gui/GuiDefs.h"

  /*!
   * Forward declarations
   */
class LabeledTextBox;


/*!
 * Control identifiers
 */


#define SYMBOL_MISCELLANEOUSDATAPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_MISCELLANEOUSDATAPANEL_TITLE _( "MiscellaneousData" )
#define SYMBOL_MISCELLANEOUSDATAPANEL_IDNAME ID_MISCELLANEOUSDATAPANEL
#define SYMBOL_MISCELLANEOUSDATAPANEL_SIZE wxDefaultSize
#define SYMBOL_MISCELLANEOUSDATAPANEL_POSITION wxDefaultPosition


 /*!
  * MiscellaneousDataPanel class declaration
  */

class MiscellaneousDataPanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( MiscellaneousDataPanel )
        DECLARE_EVENT_TABLE( )

public:
    enum MiscellaneousDataPanelGuiDefs
    {
        ID_SCORETEXTBOX = ID_MISCELLANEOUSDATAPANEL + 1,
        ID_ACCURACYTEXTBOX,
        ID_LINKTEXTBOX,
        ID_MYSTICBUTTON,
        ID_COLNECTBUTTON,
        ID_EBAYBUTTON,
        ID_NPMBUTTON,
        ID_CATCODETEXTBOX,
        ID_IMAGENAMETEXTBOX
    };
    // Constructors
    /**
     * @brief Default Constructor a new MiscellaneousDataPanel object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
    MiscellaneousDataPanel( );

    /**
     * @brief Construct a new MiscellaneousDataPanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    MiscellaneousDataPanel(
        wxWindow* parent, wxWindowID id = SYMBOL_MISCELLANEOUSDATAPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_MISCELLANEOUSDATAPANEL_POSITION,
        const wxSize& size = SYMBOL_MISCELLANEOUSDATAPANEL_SIZE,
        long style = SYMBOL_MISCELLANEOUSDATAPANEL_STYLE );

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
        wxWindowID id = SYMBOL_MISCELLANEOUSDATAPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_MISCELLANEOUSDATAPANEL_POSITION,
        const wxSize& size = SYMBOL_MISCELLANEOUSDATAPANEL_SIZE,
        long style = SYMBOL_MISCELLANEOUSDATAPANEL_STYLE );

    // Destructor
    ~MiscellaneousDataPanel( );

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

    // MiscellaneousDataPanel event handler declarations

   // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_MYSTICBUTTON
    void OnMysticButtonClick( wxCommandEvent& event );

    // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_COLNECTBUTTON
    void OnColnectButtonClick( wxCommandEvent& event );

    // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_EBAYBUTTON
    void OneBayButtonClick( wxCommandEvent& event );

    // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NPMBUTTON
    void OnNPMButtonClick( wxCommandEvent& event );

    // MiscellaneousDataPanel event handler declarations

    // MiscellaneousDataPanel member function declarations

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
    // MiscellaneousDataPanel member function declarations

   // Should we show tooltips?
    static bool ShowToolTips( );

    void ShowStamp( );
    void SetStamp( Catalog::Entry* stamp );
    void SetDataEditable( bool val );

    //void SetLabel( wxWindowID id, wxString val );

    Catalog::Entry* m_stamp;

    // MiscellaneousDataPanel member variables
//$   LabeledTextBox *m_score;
 //$   LabeledTextBox *m_accuracy;
    LabeledTextBox* m_link;
    LabeledTextBox* m_catCodes;
    LabeledTextBox* m_imageName;
    // MiscellaneousDataPanel member variables
};

#endif
// _MISCELLANEOUSDATA_H_
