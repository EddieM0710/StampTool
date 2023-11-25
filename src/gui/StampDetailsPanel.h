/*
 * @file StampDetailsPanel.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-30
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
#ifndef _STAMPDETAILSPANEL_H_
#define _STAMPDETAILSPANEL_H_


#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/HelperPanel.h"

#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"


class LabeledTextBox;
class wxListCtrl;
class TitleHelper;
class FontPicker;

namespace Design {
    class Stamp;
};


#define SYMBOL_STAMPDETAILSPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_STAMPDETAILSPANEL_TITLE _( "StampDetailsPanel" )
#define SYMBOL_STAMPDETAILSPANEL_IDNAME ID_STAMPDETAILSDIALOG
#define SYMBOL_STAMPDETAILSPANEL_SIZE wxSize( -1, -1)
#define SYMBOL_STAMPDETAILSPANEL_POSITION wxDefaultPosition




class StampDetailsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( StampDetailsPanel )
    DECLARE_EVENT_TABLE( )

public:

    enum StampDetailsDialogGuiDefs {
        ID_IDLABELTEXTBOX = ID_STAMPDETAILSDIALOG,
        ID_CATCODETEXTBOX,
        ID_NAMELABELEDTEXTBOX1,
        ID_HEIGHTLABELEDTEXTBOX,
        ID_WIDTHLABELEDTEXTBOX,
        ID_SELVAGEHEIGHTLABELEDTEXTBOX,
        ID_SELVAGEWIDTHLABELEDTEXTBOX,
        ID_MOUNTHEIGHTLABELEDTEXTBOX,
        ID_MOUNTWIDTHLABELEDTEXTBOX,
        ID_REFRESHBUTTON,
        ID_VALIDATEBUTTON,
        ID_LISTCTRL,
        ID_CATNBRCHECKBOX,
        ID_IMAGEPATHLABELEDTEXTBOX,
        ID_STAMPNAMEPANEL,
        ID_STAMPLAYOUTPANEL,
        ID_STAMPLAYOUTTEXTCTRL,
        ID_DEFAULTRADIOBUTTON,
        ID_TOPRADIOBUTTON,
        ID_BOTTOMRADIOBUTTON,
        ID_LEFTRADIOBUTTON,
        ID_RIGHTRADIOBUTTON,
        ID_LastID
    };


    StampDetailsPanel( );

    StampDetailsPanel( wxWindow* parent, wxWindowID id = SYMBOL_STAMPDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_STAMPDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_STAMPDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_STAMPDETAILSPANEL_SIZE, long style = SYMBOL_STAMPDETAILSPANEL_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STAMPDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_STAMPDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_STAMPDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_STAMPDETAILSPANEL_SIZE, long style = SYMBOL_STAMPDETAILSPANEL_STYLE );

    ~StampDetailsPanel( );

    void CreateControls( );

    wxString GetImageFilename( );
    wxString GetHeight( );
    wxString GetWidth( );

    wxString GetSelvageHeight( );
    wxString GetSelvageWidth( );
    wxString GetMountAllowanceHeight( );

    wxString GetMountAllowanceWidth( );

    wxString GetCatNbr( );

    wxString GetName( );

    wxFont GetNbrFont( );

    wxFont GetNameFont( );

    wxColour GetNbrColor( );

    wxColour GetNameColor( );

    bool GetShowNbr( );

    bool GetShowTitle( );

    bool GetShowSubTitle( );

    void Init( );

    void SetupDialog( Design::Stamp* stamp );

    void SetCatCodes( );

    void OnDefaultRadioButtonSelected( wxCommandEvent& event );

    void OnTopRadioButtonSelected( wxCommandEvent& event );

    void OnBottomRadioButtonSelected( wxCommandEvent& event );

    void OnNameFontPicker( wxFontPickerEvent& event );

    void OnNameColorPicker( wxColourPickerEvent& event );

    void OnNbrFontPicker( wxFontPickerEvent& event );

    void OnNbrColorPicker( wxColourPickerEvent& event );

    void OnNbrDefaultClick( wxCommandEvent& event );

    void OnSubTitleDefaultClick( wxCommandEvent& event );

    void OnNameTextChanged( wxCommandEvent& event );

    void OnSubTitleTextChanged( wxCommandEvent& event );

    void OnNameCheckboxClick( wxCommandEvent& event );

    void OnSubTitleCheckboxClick( wxCommandEvent& event );

    void OnNameDefaultClick( wxCommandEvent& event );

    void OnCatNbrCheckboxClick( wxCommandEvent& event );

    void OnCatalogCodesChanged( wxCommandEvent& event );

    void OnCatNbrComboBoxSel( wxCommandEvent& event );

    void OnHeight( wxCommandEvent& event );

    void OnWidth( wxCommandEvent& event );

    void OnSelvageHeight( wxCommandEvent& event );

    void OnSelvageWidth( wxCommandEvent& event );

    void OnMountAllowanceHeight( wxCommandEvent& event );

    void OnMountAllowanceWidth( wxCommandEvent& event );

    static bool ShowToolTips( );

    void SetImageFilename( wxString filename );

    void SetHeight( wxString height );

    void SetWidth( wxString width );

    void SetSelvageHeight( wxString height );

    void SetSelvageWidth( wxString width );

    void SetMountAllowanceHeight( wxString height );

    void SetMountAllowanceWidth( wxString width );

    void SetCatNbr( wxString catNbr );

    void SetName( wxString name );

    void SetShowNbr( bool state = false );

    void SetShowTitle( bool state = false );

    void SetNbrFont( wxFont font );

    void SetNameFont( wxFont font );

    void SetNbrColor( wxColour color );

    void SetNameColor( wxColour color );

    void SetTitle( wxString name );

    void SetTitleLocation( );

    void UpdateControls( );

private:

    // LabeledTextBox* m_catNbr;
    wxComboBox* m_catNbr;
    //  LabeledTextBox* m_name;
    wxTextCtrl* m_imagePath;
    wxTextCtrl* m_height;
    wxTextCtrl* m_width;
    wxTextCtrl* m_selvageHeight;
    wxTextCtrl* m_selvageWidth;
    wxTextCtrl* m_mountAllowanceHeight;
    wxTextCtrl* m_mountAllowanceWidth;
    wxButton* m_validate;
    wxListBox* m_statusList;
    wxArrayString m_statusListStrings;

    TitleHelper* m_titleHelper;
    wxTreeItemId m_designTreeID;
    wxCheckBox* m_nbrCheckbox;
    wxCheckBox* m_titleCheckbox;
    wxCheckBox* m_subTitleCheckbox;
    wxBoxSizer* m_dialogVerticalSizer;
    wxStaticBox* m_fontBox;
    wxStaticBoxSizer* m_fontVSizer;
    wxFontPickerCtrl* m_nbrFontPicker;
    wxFontPickerCtrl* m_nameFontPicker;
    wxFontPickerCtrl* m_subTitleFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
    wxColourPickerCtrl* m_subTitleColorPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    Design::Stamp* m_stamp;
    wxStaticBox* m_TitleLocationBox;
    wxStaticBoxSizer* m_titleLocationVSizer;
    wxBoxSizer* m_titleLocationHSizer;
    Design::StampNameLocation m_titleLocation;
    wxRadioButton* m_topButton;
    wxRadioButton* m_bottomButton;
    wxRadioButton* m_defaultButton;

    FontPicker* m_catNbrFontPickerHelper;

    wxTextCtrl* m_catCode;
    wxString m_catCodesString;
    wxArrayString m_catCodesStringArray;

};

#endif
