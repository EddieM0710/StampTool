/*
 * @file RowDetailsDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-04-29
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

#ifndef _ROWDETAILSDIALOG_H_
#define _ROWDETAILSDIALOG_H_


 /*
  * Includes
  */

#include "wx/listctrl.h"

#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/DesignTreeCtrl.h"
#include "gui/GuiDefs.h"


  /*
   * Forward declarations
   */
class LabeledTextBox;
class wxListCtrl;
namespace Design { class Row; };

/*
 * Control identifiers
 */



#define SYMBOL_ROWDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_ROWDETAILSDIALOG_TITLE _( "Row Details Dialog" )
#define SYMBOL_ROWDETAILSDIALOG_IDNAME ID_ROWDETAILSDIALOG
#define SYMBOL_ROWDETAILSDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_ROWDETAILSDIALOG_POSITION wxDefaultPosition



 /*
  * RowDetailsDialog class declaration
  */

class RowDetailsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( RowDetailsDialog )
        DECLARE_EVENT_TABLE( )

public:
    enum RowDetailsDialogGuiDefs {

        ID_NAMELABELEDTEXTBOX = ID_ROWDETAILSDIALOG,
        ID_ROWTITLECHECKBOX,
        ID_FRAMECHECKBOX,
        ID_LISTCTRL,
        ID_DEFAULTFONTBUTTON,
        ID_ROWNAMEPANEL,
        ID_ROWLAYOUTPANEL,
        ID_ROWLAYOUTTEXTCTRL,
        ID_ROWNOTEBOOK,
        ID_NOTEBOOK,
        ID_NOTEBOOKPOSITIONPANEL,
        ID_NOTEBOOKDETAILSPANEL,
        ID_POSITIONTEXTCTRL
    };


    RowDetailsDialog( );
    RowDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_ROWDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ROWDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ROWDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ROWDETAILSDIALOG_SIZE, long style = SYMBOL_ROWDETAILSDIALOG_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ROWDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ROWDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ROWDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ROWDETAILSDIALOG_SIZE, long style = SYMBOL_ROWDETAILSDIALOG_STYLE );


    ~RowDetailsDialog( );


    void Init( );


    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( wxTreeItemId treeID );

    // RowDetailsDialog event handler declarations

    ///   wxID_OK
    void OnOkClick( wxCommandEvent& event );


    static bool ShowToolTips( );
    void SetNameModified( bool state );
    void SetShowTitle( bool state = false );
    void SetShowFrame( bool state = false );
    void SetTitleColor( wxColour color );
    void SetTitleFont( wxFont font );
    bool GetShowTitle( );
    bool GetShowFrame( );

    wxString GetName( );

    bool IsNameModified( );

private:

    LabeledTextBox* m_name;
    wxCheckBox* m_titleCheckbox;
    wxCheckBox* m_frameCheckbox;
    wxListBox* m_statusList;
    wxFontPickerCtrl* m_titleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxTextCtrl* positionTextCtrl;
    Design::Row* m_row;
    wxTreeItemId m_designTreeID;
};

#endif
// _ROWDETAILSDIALOG_H_
