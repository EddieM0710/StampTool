/*
 * @file         FontDefaultsPanel.h
 *@brief
* @author      Eddie Monroe
* Modified by:
* @author     Mon 02 Jan 2023 08:34:03 CST
 *
* @copyright Copyright ( c ) 2024
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
 ///////////////////////////////////////

#ifndef _FONTDEFAULTSPANEL_H_
#define _FONTDEFAULTSPANEL_H_


/*
 * Includes
 */

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"
#include "design/Album.h"
#include "gui/HelperPanel.h"


class LabeledTextBox;
class wxListCtrl;
class TitleHelper;
namespace Design {
    class Page;
};

#define SYMBOL_FONTPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_FONTPANEL_TITLE _( "FontDefaultsPanel" )
#define SYMBOL_FONTPANEL_IDNAME ID_PAGEDEFAULTSDIALOG
#define SYMBOL_FONTPANEL_SIZE wxSize( -1, -1 )
#define SYMBOL_FONTPANEL_POSITION wxDefaultPosition

class FontDefaultsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( FontDefaultsPanel )
    DECLARE_EVENT_TABLE( )

public:


    enum FontDefaultsPanelGuiDefs {
        //#define  10000
        ID_NOTEBOOKPOSITIONPANEL = ID_PAGEDEFAULTSDIALOG + 1,
        ID_PAGENAMELABELEDTEXTBOX,
        ID_SHOWTITLECHECKBOX,
        ID_SHOWSUBTITLECHECKBOX,
        ID_SHOWFRAMECHECKBOX,
        ID_ORIENTATIONCHOICE,
        ID_DEFAULTBUTTON,
        ID_ERRORLISTCTRL,
        ID_NOTEBOOK,
        ID_DETAILSPANEL,
        ID_TITLEDEFAULTBUTTON,
        ID_LAYOUTPANEL,
        ID_LAYOUTTEXTCTRL,
        ID_POSITIONTEXTCTRL,
        ID_NOTEBOOKDETAILSPANEL,
        ID_LastID
    };


    FontDefaultsPanel( );
    FontDefaultsPanel( wxWindow* parent, wxWindowID id = SYMBOL_FONTPANEL_IDNAME,
        const wxString& caption = SYMBOL_FONTPANEL_TITLE,
        const wxPoint& pos = SYMBOL_FONTPANEL_POSITION,
        const wxSize& size = SYMBOL_FONTPANEL_SIZE,
        long style = SYMBOL_FONTPANEL_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FONTPANEL_IDNAME, const wxString& caption = SYMBOL_FONTPANEL_TITLE, const wxPoint& pos = SYMBOL_FONTPANEL_POSITION, const wxSize& size = SYMBOL_FONTPANEL_SIZE, long style = SYMBOL_FONTPANEL_STYLE );

    ~FontDefaultsPanel( );

    void Init( );

    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( Design::Page* page );

    static bool ShowToolTips( );

    wxColour GetTextColor( );

    wxFont GetTextFont( );

    wxColour GetTitleColor( );

    wxColour GetSubTitleColor( );

    wxFont GetTitleFont( );

    wxFont GetSubTitleFont( );

    void OnSubTitleDefaultClick( wxCommandEvent& event );

    void  OnSubTitleColorPicker( wxColourPickerEvent& event );

    void OnSubTitleFontPicker( wxFontPickerEvent& event );

    void OnTextDefaultClick( wxCommandEvent& event );

    void SetTextColor( wxColour color );

    void SetTextFont( wxFont font );

    void SetTitleColor( wxColour color );

    void SetSubTitleColor( wxColour color );

    void SetSubTitleFont( wxFont font );

    void SetTitleFont( wxFont font );

    wxColour GetNbrColor( );

    wxFont GetNbrFont( );

    void OnNbrFontPicker( wxFontPickerEvent& event );

    void OnNbrColorPicker( wxColourPickerEvent& event );

    void OnNameFontPicker( wxFontPickerEvent& event );

    void OnNameColorPicker( wxColourPickerEvent& event );

    void OnTextFontPicker( wxFontPickerEvent& event );

    void OnTextColorPicker( wxColourPickerEvent& event );

    void OnTitleDefaultClick( wxCommandEvent& event );

    void OnTitleFontPicker( wxFontPickerEvent& event );

    void OnTitleColorPicker( wxColourPickerEvent& event );

    wxColour GetNameColor( );

    wxFont GetNameFont( );

    void SetNameColor( wxColour color );

    void SetNameFont( wxFont font );


    void OnNbrDefaultClick( wxCommandEvent& event );

    void OnNameDefaultClick( wxCommandEvent& event );

    void SetNbrColor( wxColour color );

    void SetNbrFont( wxFont font );
private:

    wxFontPickerCtrl* m_titleFontPicker;
    wxFontPickerCtrl* m_subTitleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxColourPickerCtrl* m_subTitleColorPicker;

    wxFontPickerCtrl* m_textFontPicker;
    wxColourPickerCtrl* m_textColorPicker;

    wxFontPickerCtrl* m_nbrFontPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    wxFontPickerCtrl* m_nameFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
};

#endif
// _FONTDEFAULTSPANEL_H_
