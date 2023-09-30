/*
 * @file AlbumDetailsPanel.h
 * @brief
 * @author Eddie Monroe
 * Modified by:
 * @date Wed 23 Nov 2022 11:31:39 CST
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
 //
 // @copyright Copyright ( c ) 2022 
 // 
 // This file is part of StampTool.
 //
 // StampTool is free software: you can redistribute it and/or modify it under the 
 // terms of the GNU General Public License as published by the Free Software Foundation, 
 // either version 3 of the License, or any later version.
 //
 // StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 // WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 // PARTICULAR PURPOSE. See the GNU General Public License for more details.
 //
 // You should have received a copy of the GNU General Public License along with 
 // StampTool. If not, see <https://www.gnu.org/licenses/>.
 ///////////////////////////////////////

#ifndef _ALBUMDETAILSPANEL_H_
#define _ALBUMDETAILSPANEL_H_

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/GuiDefs.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/FontPickerHelper.h"
#include "gui/HelperPanel.h"

class LabeledTextBox;
class wxListCtrl;
namespace Design {
    class Album;
};

#define SYMBOL_ALBUMDETAILSPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_ALBUMDETAILSPANEL_TITLE _( "AlbumDetailsPanel" )
#define SYMBOL_ALBUMDETAILSPANEL_IDNAME ID_ALBUMDETAILSDIALOG
#define SYMBOL_ALBUMDETAILSPANEL_SIZE wxSize( -1, -1)
#define SYMBOL_ALBUMDETAILSPANEL_POSITION wxDefaultPosition
class AlbumDetailsPanel;

/// @brief
/// 
class AlbumDetailsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( AlbumDetailsPanel )
    DECLARE_EVENT_TABLE( )

public:

    enum AlbumDetailDialogDefs {
        ID_NAMELABELEDTEXTBOX = ID_ALBUMDETAILSDIALOG + 1,
        // ID_OVERSIZECHECKBOX,
        // ID_PAPERHEIGHTLABELEDTEXTBOX123,
        // ID_PAPERWIDTHLABELEDTEXTBOX123,
        // ID_HEIGHTLABELEDTEXTBOX123,
        // ID_WIDTHLABELEDTEXTBOX123,
        // ID_TOPMARGINLABELEDTEXTBOX,
        // ID_BOTTOMMARGINLABELEDTEXTBOX,
        // ID_RIGHTMARGINLABELEDTEXTBOX,
        // ID_LEFTMARGINLABELEDTEXTBOX,
        // ID_BORDERSIZELABELEDTEXTBOX,
        // ID_BORDERFILENAMELABELEDTEXTBOX,
        // ID_REFRESHBUTTON123,
        // ID_VALIDATEBUTTON123,
        // ID_LISTCTRL123,
        // ID_NBRFONTPICKER,
        // ID_NBRCOLORPICKER,
        // ID_NAMEFONTPICKER,
        // ID_NAMECOLORPICKER,
        // ID_TITLEFONTPICKER,
        // ID_TITLECOLORPICKER,
        // ID_TEXTFONTPICKER,
        // ID_TEXTCOLORPICKER,
        // ID_NBRDEFAULTFONTBUTTON,
        // ID_NAMEDEFAULTFONTBUTTON,
        // ID_TITLEDEFAULTFONTBUTTON,
        // ID_TEXTDEFAULTFONTBUTTON,
        // ID_NOTEBOOK,
        // ID_PAGEDETAILSPANEL,
        // ID_ROWCOLDETAILSPANEL,
        // ID_STAMPDETAILSPANEL,
        // ID_DEFAULTRADIOBUTTON,
        // ID_TOPRADIOBUTTON,
        // ID_BOTTOMRADIOBUTTON,
        // ID_NBRDEFAULTCHECKBOX,
        // ID_STAMPTITLEDEFAULTCHECKBOX,
        // ID_STAMPSUBTITLEDEFAULTCHECKBOX,
        // ID_ROWCOLTITLEDEFAULTCHECKBOX,
        // ID_FRAMEDEFAULTCHECKBOX,
        // ID_GRAYSCALECHECKBOX,
        // ID_CATALOGTEXTBOX,
        // ID_ORIENTATIONCHOICE,
        // ID_TITLEFONTPANEL,
        // ID_ALBUMLAYOUTTEXTCTRL,
        // ID_ALBUMLAYOUTPANEL,
        // ID_ALBUMNOTEBOOK,
        // ID_ALBUMNAMEPANEL,
        // ID_LastID
    };

    /// @brief Construct a new Album Details Dialog object
    /// 
    AlbumDetailsPanel( );

    /// @brief Construct a new Album Details Dialog object
    /// 
    /// @param parent 
    /// @param id 
    /// @param caption 
    /// @param pos 
    /// @param size 
    /// @param style 
    AlbumDetailsPanel( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSPANEL_SIZE, long style = SYMBOL_ALBUMDETAILSPANEL_STYLE );

    /// @brief Destroy the Album Details Dialog object
    /// 
    ~AlbumDetailsPanel( );

    /// @brief 
    /// 
    /// @param parent 
    /// @param id 
    /// @param caption 
    /// @param pos 
    /// @param size 
    /// @param style 
    /// @return true 
    /// @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSPANEL_SIZE, long style = SYMBOL_ALBUMDETAILSPANEL_STYLE );

    /// @brief Create a Controls object
    /// 
    void CreateControls( );
    wxPanel* SetupAlbumDetailsPanel( wxWindow* parent, int& lastID );
    wxPanel* SetupPageDetailsPanel( wxWindow* parent, int& lastID );
    wxPanel* SetupRowColDetailsPanel( wxWindow* parent, int& lastID );
    wxPanel* SetupStampDetailsPanel( wxWindow* parent, int& lastID );

    // LabeledTextBox* SetupLabelText( wxWindow* parent, wxBoxSizer* verticalSizer, int& lastID, wxString label, wxObjectEventFunction eventHandler );
    // wxCheckBox* SetupCheckBox( wxWindow* parent, wxBoxSizer* sizer, int& lastID, wxString label, wxObjectEventFunction eventHandler );

    // FontPicker* SetupFontPicker( wxWindow* parent, wxBoxSizer* verticalSizer,
    // wxString staticText, wxString buttonText, int& lastID,
    // wxFontPickerCtrl*& fontCtrl,
    // wxColourPickerCtrl*& colorCtrl,
    // wxObjectEventFunction fontPicker,
    // wxObjectEventFunction colorPicker,
    // wxObjectEventFunction defaultButtonHandler );

    /// @brief Get the Border Size object
    /// 
    /// @return wxString 
    wxString GetBorderSize( );

    wxString GetBorderFilename( );

    wxString GetCatalog( );

    /// @brief Get the Bottom PageMargin object
    /// 
    /// @return wxString 
    wxString GetBottomPageMargin( );

    /// @brief Get the Gray Scale Images object
    /// 
    /// @return true 
    /// @return false 
    bool GetGrayScaleImages( );

    /// @brief Get the Left PageMargin object
    /// 
    /// @return wxString 
    wxString GetLeftPageMargin( );

    /// @brief Get the Name object
    /// 
    /// @return wxString 
    wxString GetName( );

    /// @brief Get the Name Color object
    /// 
    /// @return wxColour 
    wxColour GetNameColor( );

    /// @brief Get the Name Font object
    /// 
    /// @return wxFont 
    wxFont GetNameFont( );

    /// @brief Get the Nbr Color object
    /// 
    /// @return wxColour 
    wxColour GetNbrColor( );

    /// @brief Get the Nbr Font object
    /// 
    /// @return wxFont 
    wxFont GetNbrFont( );

    /// @brief Get the Page Height object
    /// 
    /// @return wxString 
    wxString GetPageHeight( );

    /// @brief Get the Page Width object
    /// 
    /// @return wxString 
    wxString GetPageWidth( );

    wxString GetPaperHeight( );

    wxString GetPaperWidth( );

    /// @brief Get the Right PageMargin object
    /// 
    /// @return wxString 
    wxString GetRightPageMargin( );

    /// @brief Get the Show Nbr object
    /// 
    /// @return true 
    /// @return false 
    bool GetShowNbr( );

    /// @brief Get the Show Stamp Title object
    /// 
    /// @return true 
    /// @return false 
    bool GetShowStampTitle( );
    bool GetShowStampSubTitle( );

    wxColour GetTextColor( );

    bool GetOverSizePaper( );

    /// @brief Get the Text Font object
    /// 
    /// @return wxFont 
    wxFont GetTextFont( );

    /// @brief Get the Title Color object
    /// 
    /// @return wxColour 
    wxColour GetTitleColor( );
    wxColour GetSubTitleColor( );

    /// @brief Get the Title Font object
    /// 
    /// @return wxFont 
    wxFont GetTitleFont( );
    wxFont GetSubTitleFont( );

    /// @brief Get the Top PageMargin object
    /// 
    /// @return wxString 
    wxString GetTopPageMargin( );

    /// @brief 
    /// 
    void Init( );

    /// @brief 
    /// 
    /// @param id 
    void SetupDialog( Design::Album* album );

    /// @brief 
    /// 
    /// @return true 
    /// @return false 
    static bool ShowToolTips( );

    /// @brief Set the Album object
    /// 
    /// @param album 
    void SetAlbum( Design::Album* album ) {
        m_album = album;
    };

    /// @brief Set the Border Size object
    /// 
    /// @param size 
    void SetBorderSize( wxString size );

    void SetBorderFilename( wxString filename );

    void SetCatalog( wxString catCode );

    /// @brief Set the Bottom PageMargin object
    /// 
    /// @param pageMargin 
    void SetBottomPageMargin( wxString pageMargin );


    void SetGrayScaleImages( bool val );

    /// @brief Set the Left PageMargin object
    /// 
    /// @param pageMargin 
    void SetLeftPageMargin( wxString pageMargin );

    /// @brief Set the Name object
    /// 
    /// @param name 
    void SetName( wxString name );

    /// @brief Set the Name Color object
    /// 
    /// @param color 
    void SetNameColor( wxColour color );

    /// @brief Set the Name Font object
    /// 
    /// @param font 
    void SetNameFont( wxFont font );

    /// @brief Set the Nbr Color object
    /// 
    /// @param color 
    void SetNbrColor( wxColour color );

    /// @brief Set the Nbr Font object
    /// 
    /// @param font 
    void SetNbrFont( wxFont font );

    /// @brief Set the Page Height object
    /// 
    /// @param height 
    void SetPageHeight( wxString height );

    /// @brief Set the Page Width object
    /// 
    /// @param width 
    void SetPageWidth( wxString width );
    void SetPaperWidth( wxString width );
    void SetPaperHeight( wxString height );


    /// @brief Set the Right PageMargin object
    /// 
    /// @param pageMargin 
    void SetRightPageMargin( wxString pageMargin );

    /// @brief Set the Show Nbr object
    /// 
    /// @param state 
    void SetShowNbr( bool state );
    void SetOverSizePaper( bool state );

    /// @brief Set the Show Stamp Title object
    /// 
    /// @param state 
    void SetShowStampTitle( bool state );

    /// @brief Set the Text Color object
    /// 
    /// @param color 
    void SetTextColor( wxColour color );

    /// @brief Set the Text Font object
    /// 
    /// @param font 
    void SetTextFont( wxFont font );

    /// @brief Set the Title Color object
    /// 
    /// @param color 
    void SetTitleColor( wxColour color );
    void SetSubTitleColor( wxColour color );

    /// @brief Set the Title Font object
    /// 
    /// @param font 
    void SetTitleFont( wxFont font );
    void SetSubTitleFont( wxFont font );

    /// @brief Set the Top PageMargin object
    /// 
    /// @param pageMargin 
    void SetTopPageMargin( wxString pageMargin );

    /// @brief 
    /// 
    /// @param event 
    void OnCancelClick( wxCommandEvent& event );

    /// @brief 
    /// 
    /// @param event 
    void OnNameDefaultClick( wxCommandEvent& event );

    void OnNameClick( wxCommandEvent& event );
    void OnPaperHeight( wxCommandEvent& event );
    void OnOverSizeCheckBoxClick( wxCommandEvent& event );

    /// @brief 
    /// 
    /// @param event 
    void OnNbrDefaultClick( wxCommandEvent& event );
    void OnSubTitleFontPicker( wxFontPickerEvent& event );

    void OnSubTitleColorPicker( wxColourPickerEvent& event );

    void OnSubTitleDefaultClick( wxCommandEvent& event );

    void OnNbrFontPicker( wxFontPickerEvent& event );
    void OnNbrColorPicker( wxColourPickerEvent& event );
    void OnNameFontPicker( wxFontPickerEvent& event );
    void OnNameColorPicker( wxColourPickerEvent& event );
    void OnPaperWidth( wxCommandEvent& event );
    void OnPageHeight( wxCommandEvent& event );
    void OnPageWidth( wxCommandEvent& event );
    void OnTopPageMargin( wxCommandEvent& event );
    void OnBottomPageMargin( wxCommandEvent& event );
    void OnLeftPageMargin( wxCommandEvent& event );
    void OnRightPageMargin( wxCommandEvent& event );
    void OnBorderFilename( wxCommandEvent& event );
    void OnBorderSize( wxCommandEvent& event );
    void OnOrientationChoice( wxCommandEvent& event );
    void OnNameLocationButtonSelected( wxCommandEvent& event );
    void OnCatalogCode( wxCommandEvent& event );

    /// @brief 
    /// 
    /// @param event 
    void OnOkClick( wxCommandEvent& event );

    /// @brief 
    /// 
    /// @param event 
    void OnTextDefaultClick( wxCommandEvent& event );

    void OnTextFontPicker( wxFontPickerEvent& event );

    void OnTextColorPicker( wxColourPickerEvent& event );

    /// @brief 
    /// 
    /// @param event 
    void OnTitleDefaultClick( wxCommandEvent& event );
    void OnTitleFontPicker( wxFontPickerEvent& event );
    void OnTitleColorPicker( wxColourPickerEvent& event );

    /// @brief 
    /// 
    void UpdateControls( );

    void OnOrientationchoiceSelected( wxCommandEvent& event );
    wxString GetOrientation( ) {
        return m_orientationChoice->GetStringSelection( );
    };
    void SetOrientation( wxString sel ) {
        m_orientationChoice->SetStringSelection( sel );
    }

    Design::TitleLocation GetDefaultStampNameLocation( )
    {
        return m_stampNameLocation;
    }
    void SetStampNameLocation( );

    void OnTopRadioButtonSelected( wxCommandEvent& event );
    void OnBottomRadioButtonSelected( wxCommandEvent& event );

private:
    wxTextCtrl* m_name;
    wxTextCtrl* m_paperHeight;
    wxTextCtrl* m_paperWidth;
    wxTextCtrl* m_pageHeight;
    wxTextCtrl* m_pageWidth;
    wxTextCtrl* m_topPageMargin;
    wxTextCtrl* m_bottomPageMargin;
    wxTextCtrl* m_rightPageMargin;
    wxTextCtrl* m_leftPageMargin;
    wxTextCtrl* m_borderSize;
    wxTextCtrl* m_borderFilename;
    wxCheckBox* m_overSizeCheckbox;
    wxCheckBox* m_nbrCheckbox;
    wxCheckBox* m_stampTitleCheckbox;
    wxCheckBox* m_stampSubTitleCheckbox;
    wxCheckBox* m_grayScaleImagesCheckbox;
    wxChoice* m_orientationChoice;
    wxFontPickerCtrl* m_titleFontPicker;
    wxFontPickerCtrl* m_subTitleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxColourPickerCtrl* m_subTitleColorPicker;
    wxFontPickerCtrl* m_nbrFontPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    wxFontPickerCtrl* m_nameFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
    wxFontPickerCtrl* m_textFontPicker;
    wxColourPickerCtrl* m_textColorPicker;

    wxStaticBox* m_stampNameLocationBox;
    wxStaticBoxSizer* m_stampNameLocationVSizer;
    wxBoxSizer* m_stampNameLocationHSizer;
    Design::TitleLocation m_stampNameLocation;
    wxRadioButton* m_topButton;
    wxRadioButton* m_bottomButton;

    wxTextCtrl* m_catalog;
    wxRadioButton* m_defaultButton;
    wxButton* m_validate;
    wxListBox* m_statusList;

    AlbumDetailsPanel* theDialog;
    Design::Album* m_album;
};

#endif
