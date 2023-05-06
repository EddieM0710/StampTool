/**
 * @file CharacteristicsPanel.h
 * @author Eddie Monroe ( )
 * @brief Inherits from wxPanel. This class manages the widgets that
 * display the physical characteristics
 * of the stamp
 * @version 0.1
 * @date 2021-02-24
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
 */


#ifndef _CHARACTERISTICSPANEL_H_
#define _CHARACTERISTICSPANEL_H_

#include "gui/GuiDefs.h"
#include "catalog/Entry.h"

class LabeledTextBox;


#define SYMBOL_CHARACTERISTICSPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_CHARACTERISTICSPANEL_TITLE _( "CharacteristicsPanel" )
#define SYMBOL_CHARACTERISTICSPANEL_IDNAME ID_CHARACTERISTICSPANEL
#define SYMBOL_CHARACTERISTICSPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_CHARACTERISTICSPANEL_POSITION wxDefaultPosition


/**
 * CharacteristicsPanel class declaration
 *
 * Inherits from wxPanel. This class manages the widgets that
 * display the physical characteristics of the stamp.
 */
class CharacteristicsPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( CharacteristicsPanel )
        DECLARE_EVENT_TABLE( )

public:

    enum CharacteristicsPanelGuiDefs {
        ID_FACETEXTBOX = ID_CHARACTERISTICSPANEL + 1,
        ID_CURRENCYTEXTBOX,
        ID_HEIGHTEXTBOX,
        ID_WIDTHTEXTBOX,
        ID_PERFORATIONTEXTBOX,
        ID_WATERMARKEXTBOX,
        ID_GUMTEXTBOX,
        ID_VARIANTTEXTBOX,
        ID_COLORSTEXTBOX,
        ID_PAPERTEXTBOX,
        ID_PRINTINGTEXTBOX,
        ID_PRINTRUNTEXTBOX,
        ID_EXPIRYDATEEXTBOX
    };

    /**
     * @brief Default Constructor for a new CharacteristicsPanel object
     *
     */
    CharacteristicsPanel( void );

    /**
     * @brief Construct a new CharacteristicsPanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     */
    CharacteristicsPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_CHARACTERISTICSPANEL_IDNAME,
        const wxPoint& pos
        = SYMBOL_CHARACTERISTICSPANEL_POSITION,
        const wxSize& size = SYMBOL_CHARACTERISTICSPANEL_SIZE,
        long style = SYMBOL_CHARACTERISTICSPANEL_STYLE );

    /**
     * @brief Destroy the Characteristics Panel object
     *
     */
    ~CharacteristicsPanel( void );

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
        wxWindowID id = SYMBOL_CHARACTERISTICSPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_CHARACTERISTICSPANEL_POSITION,
        const wxSize& size = SYMBOL_CHARACTERISTICSPANEL_SIZE,
        long style = SYMBOL_CHARACTERISTICSPANEL_STYLE );

    /// @brief Creates the controls and sizers
    void CreateControls( );

    ///@brief Initialises member variables
    void Init( );

    ///  @brief 
    ///  
    ///  @param event 
    void OnTextctrlTextUpdated( wxCommandEvent& event );

    ///  @brief Set the Data Editable object
    ///  
    ///  @param val 
    void SetDataEditable( bool val );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

    /// @brief Initializes the CharacteristicsPanel with new stamp values
    void UpdatePanel( );

    ///  @brief 
    ///  
    ///  @param dt 
    ///  @param textBox 
    void UpdateStampValue( Catalog::DataTypes dt, LabeledTextBox* textBox );

private:

    LabeledTextBox* m_height;  ///< widget to display stamp height
    LabeledTextBox* m_width;  ///< widget to display stamp width

};

#endif
// _PHYSICALPANEL_H_
