/*
 * @file gui/SettingsDialog.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-12
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

#ifndef _SETTINGSDIALOG_H_
#define _SETTINGSDIALOG_H_


 /*
  * Includes
  */




#include "gui/GuiDefs.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
  /*
   * Forward declarations
   */



class SortOrderPanel;
class DefinePeriodsPanel;
/*
 * Control identifiers
 */


#define SYMBOL_SETTINGSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_SETTINGSDIALOG_TITLE _( "SettingsDialog" )
#define SYMBOL_SETTINGSDIALOG_IDNAME ID_SETTINGSDIALOG
#define SYMBOL_SETTINGSDIALOG_SIZE wxSize( 600, 300 )
#define SYMBOL_SETTINGSDIALOG_POSITION wxDefaultPosition



 /*
  * SettingsDialog class declaration
  */

class SettingsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( SettingsDialog )
        DECLARE_EVENT_TABLE( )

public:
    enum SettingsDialogGuiDefs
    {
        ID_IMAGEDIRECTORTEXTBOX = ID_SETTINGSDIALOG + 1,
        ID_COUNTRYTEXTBOX,
        ID_CATALOGTEXTBOX,
        ID_OPENLASTCHECKBOX,
        ID_RECENTSIZETEXTCTRL,
        ID_NOTEBOOK,
        ID_NOTEBOOKDETAILSPANEL,
        ID_NOTEBOOKFONTSPANEL,
        ID_NBRFONTPICKER,
        ID_NBRCOLORPICKER,
        ID_TITLEFONTPICKER,
        ID_TITLECOLORPICKER,
        ID_TEXTFONTPICKER,
        ID_TEXTCOLORPICKER,
        ID_NBRDEFAULTFONTBUTTON,
        ID_TITLEDEFAULTFONTBUTTON,
        ID_TEXTDEFAULTFONTBUTTON
    };

    SettingsDialog( );
    SettingsDialog( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGSDIALOG_IDNAME, const wxString& caption = SYMBOL_SETTINGSDIALOG_TITLE, const wxPoint& pos = SYMBOL_SETTINGSDIALOG_POSITION, const wxSize& size = SYMBOL_SETTINGSDIALOG_SIZE, long style = SYMBOL_SETTINGSDIALOG_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGSDIALOG_IDNAME, const wxString& caption = SYMBOL_SETTINGSDIALOG_TITLE, const wxPoint& pos = SYMBOL_SETTINGSDIALOG_POSITION, const wxSize& size = SYMBOL_SETTINGSDIALOG_SIZE, long style = SYMBOL_SETTINGSDIALOG_STYLE );


    ~SettingsDialog( );


    void Init( );


    void CreateControls( );

    // SettingsDialog event handler declarations

        ///   ID_IMAGEDIRECTORTEXTBOX
    void OnImagedirectortextboxTextUpdated( wxCommandEvent& event );

    ///   ID_COUNTRYTEXTBOX
    void OnCountrytextboxTextUpdated( wxCommandEvent& event );

    ///   ID_CATALOGTEXTBOX
    void OnCatalogtextboxTextUpdated( wxCommandEvent& event );

    ///   ID_OPENLASTCHECKBOX
    void OnOpenlastcheckboxClick( wxCommandEvent& event );

    ///   ID_RECENTSIZETEXTCTRL
    void OnRecentsizetextctrlTextUpdated( wxCommandEvent& event );

    // SettingsDialog event handler declarations

    void OnOkClick( wxCommandEvent& event );



    static bool ShowToolTips( );

    bool IsDirty( ) { return m_dirty; };

    void UpdateSettings( );

    // SettingsDialog member variables
    wxTextCtrl* m_imageDirectory;
    wxTextCtrl* m_country;
    wxTextCtrl* m_catalog;
    wxCheckBox* m_loadLastFileAtStartUp;
    wxTextCtrl* m_recentListSize;
    SortOrderPanel* m_sortOrderPanel;
    DefinePeriodsPanel* m_definePeriodsPanel;
    wxFontPickerCtrl* m_titleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxFontPickerCtrl* m_nbrFontPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    wxFontPickerCtrl* m_textFontPicker;
    wxColourPickerCtrl* m_textColorPicker;
    // SettingsDialog member variables
    bool m_dirty;

};

#endif
// _SETTINGSDIALOG_H_
