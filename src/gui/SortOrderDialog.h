/**
 * @file gui/SortOrderDialog.h
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


#ifndef _SORTORDERDIALOG_H_
#define _SORTORDERDIALOG_H_

 /*!
  * Includes
  */
#include "gui/GuiDefs.h"



  /*!
   * Forward declarations
   */




   /*!
    * Control identifiers
    */
#define SYMBOL_SORTORDERDIALOG_STYLE                                           \
    wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_SORTORDERDIALOG_TITLE _( "SortOrderDialog" )
#define SYMBOL_SORTORDERDIALOG_IDNAME ID_SORTORDERDIALOG
#define SYMBOL_SORTORDERDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_SORTORDERDIALOG_POSITION wxDefaultPosition


    /*!
     * SortOrderDialog class declaration
     */

class SortOrderDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( SortOrderDialog )
        DECLARE_EVENT_TABLE( )

public:
    enum SortOrderDialogGuiDefs
    {
        ID_SORTORDERTEXTCTRL = ID_SORTORDERDIALOG + 1,
        ID_CHOICE,
        ID_CHOICE1,
        ID_CHOICE2,
        ID_CHOICE3,
        ID_CHOICE4
    };
    // Constructors
    /**
     * @brief Default Constructor a new SortOrderDialog object
     * @details Must be used in conjunction with Create.
     *
     **************************************************/
    SortOrderDialog( );

    /**
     * @brief Construct a new SortOrderDialog object
     *
     * @param  parent	The parent window.
     * @param  id	An identifier for the panel. wxID_ANY is taken to mean a default.
     * @param  pos	The panel position. The value wxDefaultPosition indicates a default position, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  size	The panel size. The value wxDefaultSize indicates a default size, chosen by either the windowing system or wxWidgets, depending on platform.
     * @param  style	The window style.
     * @see wxPanel.
     **************************************************/
    SortOrderDialog( wxWindow* parent,
        wxWindowID id = SYMBOL_SORTORDERDIALOG_IDNAME,
        const wxString& caption = SYMBOL_SORTORDERDIALOG_TITLE,
        const wxPoint& pos = SYMBOL_SORTORDERDIALOG_POSITION,
        const wxSize& size = SYMBOL_SORTORDERDIALOG_SIZE,
        long style = SYMBOL_SORTORDERDIALOG_STYLE );

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
        wxWindowID id = SYMBOL_SORTORDERDIALOG_IDNAME,
        const wxString& caption = SYMBOL_SORTORDERDIALOG_TITLE,
        const wxPoint& pos = SYMBOL_SORTORDERDIALOG_POSITION,
        const wxSize& size = SYMBOL_SORTORDERDIALOG_SIZE,
        long style = SYMBOL_SORTORDERDIALOG_STYLE );

    // Destructor
    ~SortOrderDialog( );

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

    // SortOrderDialog event handler declarations

   // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
    void OnChoiceSelected( wxCommandEvent& event );

    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1
    void OnChoice1Selected( wxCommandEvent& event );

    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2
    void OnChoice2Selected( wxCommandEvent& event );

    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE3
    void OnChoice3Selected( wxCommandEvent& event );

    // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE4
    void OnChoice4Selected( wxCommandEvent& event );

    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

    // SortOrderDialog event handler declarations

    // SortOrderDialog member function declarations

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
    // SortOrderDialog member function declarations

   // Should we show tooltips?
    static bool ShowToolTips( );
    bool IsDirty( ) { return m_dirty; };

    // SortOrderDialog member variables
    wxChoice* m_firstSort;
    wxChoice* m_secondSort;
    wxChoice* m_thirdSort;
    wxChoice* m_forthSort;
    wxChoice* m_fifthSort;
    // SortOrderDialog member variables
    wxArrayString m_sortStrings;
    bool m_dirty;
};

#endif
// _SORTORDERDIALOG_H_
