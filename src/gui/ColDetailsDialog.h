/*
 * @file src/gui/ColDetailsDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
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
 */

#ifndef _COLDETAILSDIALOG_H_
#define _COLDETAILSDIALOG_H_


 /*!
  * Includes
  */

  // includes
#include "wx/listctrl.h"
// includes

#include "gui/DesignTreeCtrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
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
#define ID_COLDETAILSDIALOG 10000
#define ID_NAMELABELEDTEXTBOX 10009
#define ID_COLTITLECHECKBOX 10004
#define ID_FRAMECHECKBOX 10006
#define ID_LISTCTRL 10006
#define ID_COLNOTEBOOK 10020
#define ID_COLNAMEPANEL 10021
#define ID_COLDEFAULTFONTBUTTON 10022
#define ID_COLLAYOUTPANEL 10023
#define ID_COLLAYOUTTEXTCTRL 10024
#define SYMBOL_COLDETAILSDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_COLDETAILSDIALOG_TITLE _("Col Details Dialog")
#define SYMBOL_COLDETAILSDIALOG_IDNAME ID_COLDETAILSDIALOG
#define SYMBOL_COLDETAILSDIALOG_SIZE wxSize(400, 300)
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

    // ColDetailsDialog member variables
};

#endif
// _COLDETAILSDIALOG_H_
