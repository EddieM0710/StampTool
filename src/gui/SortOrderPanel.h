/**
 * @file gui/SortOrderPanel.h
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


#ifndef _SORTORDERPANEL_H_
#define _SORTORDERPANEL_H_

#include "gui/GuiDefs.h"


#define SYMBOL_SORTORDERPANEL_STYLE  wxTAB_TRAVERSAL
#define SYMBOL_SORTORDERPANEL_TITLE _( "SortOrderPanel" )
#define SYMBOL_SORTORDERPANEL_IDNAME ID_SORTORDERPANEL
#define SYMBOL_SORTORDERPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_SORTORDERPANEL_POSITION wxDefaultPosition


class SortOrderPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( SortOrderPanel )
    DECLARE_EVENT_TABLE( )

public:
    enum SortOrderPanelGuiDefs
    {
        ID_SORTORDERTEXTCTRL = ID_SORTORDERPANEL + 1,
        ID_CHOICE,
        ID_CHOICE1,
        ID_CHOICE2,
        ID_CHOICE3,
        ID_CHOICE4
    };



    /**
     * @brief Default Constructor a new SortOrderPanel object
     * @details Must be used in conjunction with Create.
     *
     */
    SortOrderPanel( );

    /**
     * @brief Construct a new SortOrderPanel object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     */
    SortOrderPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_SORTORDERPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_SORTORDERPANEL_POSITION,
        const wxSize& size = SYMBOL_SORTORDERPANEL_SIZE,
        long style = SYMBOL_SORTORDERPANEL_STYLE );

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
        wxWindowID id = SYMBOL_SORTORDERPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_SORTORDERPANEL_POSITION,
        const wxSize& size = SYMBOL_SORTORDERPANEL_SIZE,
        long style = SYMBOL_SORTORDERPANEL_STYLE );


    ~SortOrderPanel( );

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


    void OnChoiceSelected( wxCommandEvent& event );

    void OnChoice1Selected( wxCommandEvent& event );

    void OnChoice2Selected( wxCommandEvent& event );

    void OnChoice3Selected( wxCommandEvent& event );

    void OnChoice4Selected( wxCommandEvent& event );

    void OnOkClick( );


    static bool ShowToolTips( );
    bool IsDirty( ) { return m_dirty; };





    wxChoice* m_firstSort;
    wxChoice* m_secondSort;
    wxChoice* m_thirdSort;
    wxChoice* m_forthSort;
    wxChoice* m_fifthSort;
    wxArrayString m_sortStrings;
    bool m_dirty;
};

#endif
