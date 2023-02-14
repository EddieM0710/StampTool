/*
 * @file src/gui/ColDetailsDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright ( c ) 2022
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

#ifndef _COLDETAILSDIALOG_H_
#define _COLDETAILSDIALOG_H_


 /*!
  * Includes
  */

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/DesignTreeCtrl.h"
#include "gui/GuiDefs.h"

  /*!
   * Forward declarations
   */

   // forward declarations
class LabeledTextBox;
class wxListCtrl;
// forward declarations

/*!
 * Control identifiers
 */

 // control identifiers

#define SYMBOL_COLDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_COLDETAILSDIALOG_TITLE _( "Col Details Dialog" )
#define SYMBOL_COLDETAILSDIALOG_IDNAME ID_COLDETAILSDIALOG
#define SYMBOL_COLDETAILSDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_COLDETAILSDIALOG_POSITION wxDefaultPosition
// control identifiers


/*!
 * ColDetailsDialog class declaration
 */

class ColDetailsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( ColDetailsDialog )
        DECLARE_EVENT_TABLE( )

public:

    enum ColDetailsDialogGuiDefs {
        ID_NAMELABELEDTEXTBOX = ID_COLDETAILSDIALOG + 1,
        ID_COLTITLECHECKBOX,
        ID_FRAMECHECKBOX,
        ID_LISTCTRL,
        ID_COLNOTEBOOK,
        ID_COLNAMEPANEL,
        ID_COLDEFAULTFONTBUTTON,
        ID_COLLAYOUTPANEL,
        ID_COLLAYOUTTEXTCTRL,
        ID_NOTEBOOKPOSITIONPANEL,
        ID_POSITIONTEXTCTRL,
        ID_NOTEBOOK,
        ID_NOTEBOOKDETAILSPANEL
    };
    
    /// Constructors
    ColDetailsDialog( );
    ColDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_COLDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_COLDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_COLDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_COLDETAILSDIALOG_SIZE, long style = SYMBOL_COLDETAILSDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_COLDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_COLDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_COLDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_COLDETAILSDIALOG_SIZE, long style = SYMBOL_COLDETAILSDIALOG_STYLE );

    /// Destructor
    ~ColDetailsDialog( );

    /// Initialises member variables
    void Init( );

    /// Creates the controls and sizers
    void CreateControls( );

    // ColDetailsDialog event handler declarations

    // wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

    // ColDetailsDialog event handler declarations

    // ColDetailsDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
    // ColDetailsDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips( );
    void SetNameModified( bool state );
    void SetDesignTreeID( wxTreeItemId id );
    bool IsNameModified( );

    void SetShowTitle( bool state = false );
    void SetShowFrame( bool state = false );
    bool GetShowTitle( );
    bool GetShowFrame( );


    // ColDetailsDialog member variables
private:
    wxTreeItemId m_designTreeID;
    LabeledTextBox* m_name;
    wxCheckBox* m_titleCheckbox;
    wxCheckBox* m_frameCheckbox;
    wxListCtrl* m_statusList;
    wxFontPickerCtrl* m_titleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxTextCtrl* positionTextCtrl;
    // ColDetailsDialog member variables
};

#endif
// _COLDETAILSDIALOG_H_
