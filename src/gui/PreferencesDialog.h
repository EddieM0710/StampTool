/*
 * @file gui/PreferencesDialog.h
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

#ifndef _PreferencesDialog_H_
#define _PreferencesDialog_H_





#include "gui/GuiDefs.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
#include "wx/grid.h"




class SortOrderPanel;
class DefinePeriodsPanel;


#define SYMBOL_PreferencesDialog_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_PreferencesDialog_TITLE _( "PreferencesDialog" )
#define SYMBOL_PreferencesDialog_IDNAME ID_PREFERENCESDIALOG
#define SYMBOL_PreferencesDialog_SIZE wxSize( 100, 100 )
#define SYMBOL_PreferencesDialog_POSITION wxDefaultPosition


class PreferencesDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( PreferencesDialog )
    DECLARE_EVENT_TABLE( )

public:
    enum PreferencesDialogGuiDefs
    {
        ID_IMAGEDIRECTORTEXTBOX = ID_PREFERENCESDIALOG + 1,
        ID_DIRPICKERBTN,
        ID_COUNTRYTEXTBOX,
        ID_CATALOGTEXTBOX,
        ID_OPENLASTCHECKBOX,
        ID_RECENTSIZETEXTCTRL,
        ID_NOTEBOOK,
        ID_NOTEBOOKDETAILSPANEL,
        ID_NOTEBOOKFONTSPANEL,
        ID_NOTEBOOKCOLLECTIONPANEL,
        ID_NBRFONTPICKER,
        ID_NBRCOLORPICKER,
        ID_TITLEFONTPICKER,
        ID_TITLECOLORPICKER,
        ID_TEXTFONTPICKER,
        ID_TEXTCOLORPICKER,
        ID_NAMEFONTPICKER,
        ID_NAMECOLORPICKER,
        ID_NBRDEFAULTFONTBUTTON,
        ID_TITLEDEFAULTFONTBUTTON,
        ID_TEXTDEFAULTFONTBUTTON,
        ID_NAMEDEFAULTFONTBUTTON,
        ID_COLLECTIONGRID,
        ID_LastID
    };



    PreferencesDialog( );
    PreferencesDialog( wxWindow* parent,
        wxWindowID id = SYMBOL_PreferencesDialog_IDNAME,
        const wxString& caption = SYMBOL_PreferencesDialog_TITLE,
        const wxPoint& pos = SYMBOL_PreferencesDialog_POSITION,
        const wxSize& size = SYMBOL_PreferencesDialog_SIZE,
        long style = SYMBOL_PreferencesDialog_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PreferencesDialog_IDNAME, const wxString& caption = SYMBOL_PreferencesDialog_TITLE, const wxPoint& pos = SYMBOL_PreferencesDialog_POSITION, const wxSize& size = SYMBOL_PreferencesDialog_SIZE, long style = SYMBOL_PreferencesDialog_STYLE );


    ~PreferencesDialog( );


    void Init( );


    void CreateControls( );
    wxPanel* CreateNotebookDetailsPanel( wxWindow* parent );

    wxPanel* CreateNotebookFontsPanel( wxWindow* parent );
    wxPanel* CreateCollectionPanel( wxWindow* parent );

    // PreferencesDialog event handler declarations

        //   ID_IMAGEDIRECTORTEXTBOX
    void OnImagedirectortextboxTextUpdated( wxCommandEvent& event );

    //   ID_COUNTRYTEXTBOX
    void OnCountrytextboxTextUpdated( wxCommandEvent& event );

    //   ID_CATALOGTEXTBOX
    void OnCatalogtextboxTextUpdated( wxCommandEvent& event );

    //   ID_OPENLASTCHECKBOX
    void OnOpenlastcheckboxClick( wxCommandEvent& event );

    void OnNotebookPageChanged( wxNotebookEvent& event );

    //   ID_RECENTSIZETEXTCTRL
    void OnRecentsizetextctrlTextUpdated( wxCommandEvent& event );

    // PreferencesDialog event handler declarations
    void OnOkClick( wxCommandEvent& event );

    void BrowseForDir( wxCommandEvent& event );

    static bool ShowToolTips( );

    bool IsDirty( ) {
        return m_dirty;
    };

    void UpdateDetails();

    void InitDetailsPanel( );

    void UpdateFonts();

   // void UpdateFonts( );

    void UpdateCollectionList();

    void InitCollectionGrid();




    // PreferencesDialog member variables
    wxNotebook* m_notebook;
    wxPanel* m_DetailsPanel;
    SortOrderPanel* m_SortOrderPanel;
    DefinePeriodsPanel* m_DefinePeriodsPanel;
    wxPanel* m_FontsPanel;
    wxPanel* m_CollectionPanel;
    wxTextCtrl* m_imageDirectory;
    wxTextCtrl* m_country;
    wxTextCtrl* m_catalog;
    wxCheckBox* m_loadLastFileAtStartUp;
    wxTextCtrl* m_recentListSize;
    wxFontPickerCtrl* m_titleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxFontPickerCtrl* m_nbrFontPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    wxFontPickerCtrl* m_textFontPicker;
    wxColourPickerCtrl* m_textColorPicker;
    wxFontPickerCtrl* m_nameFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
    wxGrid* m_grid;  ///< wxGrid to display item entries

    // PreferencesDialog member variables
    bool m_dirty;

};

#endif
// _PreferencesDialog_H_
