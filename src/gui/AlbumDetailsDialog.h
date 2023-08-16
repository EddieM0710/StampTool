/*
 * @file         AlbumDetailsDialog.h
 * @brief
 * @author      Eddie Monroe
 * Modified by:
 * @date     Wed 23 Nov 2022 11:31:39 CST
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

#ifndef _ALBUMDETAILSDIALOG_H_
#define _ALBUMDETAILSDIALOG_H_

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/GuiDefs.h"
#include "gui/AlbumTreeCtrl.h"

class LabeledTextBox;
class wxListCtrl;
namespace Design { class Album; };

#define SYMBOL_ALBUMDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_ALBUMDETAILSDIALOG_TITLE _( "AlbumDetailsDialog" )
#define SYMBOL_ALBUMDETAILSDIALOG_IDNAME ID_ALBUMDETAILSDIALOG
#define SYMBOL_ALBUMDETAILSDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_ALBUMDETAILSDIALOG_POSITION wxDefaultPosition

///  @brief
///  
class AlbumDetailsDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( AlbumDetailsDialog )
    DECLARE_EVENT_TABLE( )

public:

    enum AlbumDetailDialogDefs {
        ID_NAMELABELEDTEXTBOX = ID_ALBUMDETAILSDIALOG + 1,
        ID_OVERSIZECHECKBOX,
        ID_PAPERHEIGHTLABELEDTEXTBOX123,
        ID_PAPERWIDTHLABELEDTEXTBOX123,
        ID_HEIGHTLABELEDTEXTBOX123,
        ID_WIDTHLABELEDTEXTBOX123,
        ID_TOPMARGINLABELEDTEXTBOX,
        ID_BOTTOMMARGINLABELEDTEXTBOX,
        ID_RIGHTMARGINLABELEDTEXTBOX,
        ID_LEFTMARGINLABELEDTEXTBOX,
        ID_BORDERSIZELABELEDTEXTBOX,
        ID_BORDERFILENAMELABELEDTEXTBOX,
        ID_REFRESHBUTTON123,
        ID_VALIDATEBUTTON123,
        ID_LISTCTRL123,
        ID_NBRFONTPICKER,
        ID_NBRCOLORPICKER,
        ID_NAMEFONTPICKER,
        ID_NAMECOLORPICKER,
        ID_TITLEFONTPICKER,
        ID_TITLECOLORPICKER,
        ID_TEXTFONTPICKER,
        ID_TEXTCOLORPICKER,
        ID_NBRDEFAULTFONTBUTTON,
        ID_NAMEDEFAULTFONTBUTTON,
        ID_TITLEDEFAULTFONTBUTTON,
        ID_TEXTDEFAULTFONTBUTTON,
        ID_NOTEBOOK,
        ID_PAGEDETAILSPANEL,
        ID_ROWCOLDETAILSPANEL,
        ID_STAMPDETAILSPANEL,
        ID_DEFAULTRADIOBUTTON,
        ID_TOPRADIOBUTTON,
        ID_BOTTOMRADIOBUTTON,
        ID_NBRDEFAULTCHECKBOX,
        ID_STAMPTITLEDEFAULTCHECKBOX,
        ID_STAMPSUBTITLEDEFAULTCHECKBOX,
        ID_ROWCOLTITLEDEFAULTCHECKBOX,
        ID_FRAMEDEFAULTCHECKBOX,
        ID_GRAYSCALECHECKBOX,
        ID_ORIENTATIONCHOICE,
        ID_TITLEFONTPANEL,
        ID_ALBUMLAYOUTTEXTCTRL,
        ID_ALBUMLAYOUTPANEL,
        ID_ALBUMNOTEBOOK,
        ID_ALBUMNAMEPANEL,
        ID_LastID
    };

    ///  @brief Construct a new Album Details Dialog object
    ///  
    AlbumDetailsDialog( );

    ///  @brief Construct a new Album Details Dialog object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    AlbumDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSDIALOG_SIZE, long style = SYMBOL_ALBUMDETAILSDIALOG_STYLE );

    ///  @brief Destroy the Album Details Dialog object
    ///  
    ~AlbumDetailsDialog( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSDIALOG_SIZE, long style = SYMBOL_ALBUMDETAILSDIALOG_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief Get the Border Size object
    ///  
    ///  @return wxString 
    wxString GetBorderSize( );

    wxString GetBorderFilename( );

    ///  @brief Get the Bottom PageMargin object
    ///  
    ///  @return wxString 
    wxString GetBottomPageMargin( );

    ///  @brief Get the Gray Scale Images object
    ///  
    ///  @return true 
    ///  @return false 
    bool GetGrayScaleImages( );

    ///  @brief Get the Left PageMargin object
    ///  
    ///  @return wxString 
    wxString GetLeftPageMargin( );

    ///  @brief Get the Name object
    ///  
    ///  @return wxString 
    wxString GetName( );

    ///  @brief Get the Name Color object
    ///  
    ///  @return wxColour 
    wxColour GetNameColor( );

    ///  @brief Get the Name Font object
    ///  
    ///  @return wxFont 
    wxFont GetNameFont( );

    ///  @brief Get the Nbr Color object
    ///  
    ///  @return wxColour 
    wxColour GetNbrColor( );

    ///  @brief Get the Nbr Font object
    ///  
    ///  @return wxFont 
    wxFont GetNbrFont( );

    ///  @brief Get the Page Height object
    ///  
    ///  @return wxString 
    wxString GetPageHeight( );

    ///  @brief Get the Page Width object
    ///  
    ///  @return wxString 
    wxString GetPageWidth( );

    wxString GetPaperHeight( );

    wxString GetPaperWidth( );

    ///  @brief Get the Right PageMargin object
    ///  
    ///  @return wxString 
    wxString GetRightPageMargin( );

    ///  @brief Get the Show Nbr object
    ///  
    ///  @return true 
    ///  @return false 
    bool GetShowNbr( );

    ///  @brief Get the Show Stamp Title object
    ///  
    ///  @return true 
    ///  @return false 
    bool GetShowStampTitle( );
    bool GetShowStampSubTitle( );

    wxColour GetTextColor( );

    bool GetOverSizePaper( );

    ///  @brief Get the Text Font object
    ///  
    ///  @return wxFont 
    wxFont GetTextFont( );

    ///  @brief Get the Title Color object
    ///  
    ///  @return wxColour 
    wxColour GetTitleColor( );
    wxColour GetSubTitleColor( );

    ///  @brief Get the Title Font object
    ///  
    ///  @return wxFont 
    wxFont GetTitleFont( );
    wxFont GetSubTitleFont( );

    ///  @brief Get the Top PageMargin object
    ///  
    ///  @return wxString 
    wxString GetTopPageMargin( );

    ///  @brief 
    ///  
    void Init( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsBorderSizeModified( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsBottomPageMarginModified( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsLeftPageMarginModified( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsNameModified( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsPageHeightModified( );
    bool IsPaperHeightModified( );
    bool IsPaperWidthModified( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsPageWidthModified( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsRightPageMarginModified( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsTopPageMarginModified( );

    ///  @brief 
    ///  
    ///  @param id 
    void SetupDialog( wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

    ///  @brief Set the Album object
    ///  
    ///  @param album 
    void SetAlbum( Design::Album* album ) { m_album = album; };

    ///  @brief Set the Border Size object
    ///  
    ///  @param size 
    void SetBorderSize( wxString size );

    void SetBorderFilename( wxString filename );

    ///  @brief Set the Border Size Modified object
    ///  
    ///  @param state 
    void SetBorderSizeModified( bool state );

    ///  @brief Set the Bottom PageMargin object
    ///  
    ///  @param pageMargin 
    void SetBottomPageMargin( wxString pageMargin );


    ///  @brief Set the Bottom PageMargin Modified object
    ///  
    ///  @param state 
    void SetBottomPageMarginModified( bool state );

    void SetGrayScaleImages( bool val );

    ///  @brief Set the Left PageMargin object
    ///  
    ///  @param pageMargin 
    void SetLeftPageMargin( wxString pageMargin );

    ///  @brief Set the Left PageMargin Modified object
    ///  
    ///  @param state 
    void SetLeftPageMarginModified( bool state );

    ///  @brief Set the Name object
    ///  
    ///  @param name 
    void SetName( wxString name );

    ///  @brief Set the Name Color object
    ///  
    ///  @param color 
    void SetNameColor( wxColour color );

    ///  @brief Set the Name Font object
    ///  
    ///  @param font 
    void SetNameFont( wxFont font );

    ///  @brief Set the Name Modified object
    ///  
    ///  @param state 
    void SetNameModified( bool state );

    ///  @brief Set the Nbr Color object
    ///  
    ///  @param color 
    void SetNbrColor( wxColour color );

    ///  @brief Set the Nbr Font object
    ///  
    ///  @param font 
    void SetNbrFont( wxFont font );

    ///  @brief Set the Page Height object
    ///  
    ///  @param height 
    void SetPageHeight( wxString height );

    ///  @brief Set the Page Height Modified object
    ///  
    ///  @param state 
    void SetPageHeightModified( bool state );

    void SetPaperHeightModified( bool state );

    void SetPaperWidthModified( bool state );

    ///  @brief Set the Page Width object
    ///  
    ///  @param width 
    void SetPageWidth( wxString width );
    void SetPaperWidth( wxString width );
    void SetPaperHeight( wxString height );

    ///  @brief Set the Page Width Modified object
    ///  
    ///  @param state 
    void SetPageWidthModified( bool state );

    ///  @brief Set the Right PageMargin object
    ///  
    ///  @param pageMargin 
    void SetRightPageMargin( wxString pageMargin );

    ///  @brief Set the Right PageMargin Modified object
    ///  
    ///  @param state 
    void SetRightPageMarginModified( bool state );

    ///  @brief Set the Show Nbr object
    ///  
    ///  @param state 
    void SetShowNbr( bool state );
    void SetOverSizePaper( bool state );

    ///  @brief Set the Show Stamp Title object
    ///  
    ///  @param state 
    void SetShowStampTitle( bool state );

    ///  @brief Set the Text Color object
    ///  
    ///  @param color 
    void SetTextColor( wxColour color );

    ///  @brief Set the Text Font object
    ///  
    ///  @param font 
    void SetTextFont( wxFont font );

    ///  @brief Set the Title Color object
    ///  
    ///  @param color 
    void SetTitleColor( wxColour color );
    void SetSubTitleColor( wxColour color );

    ///  @brief Set the Title Font object
    ///  
    ///  @param font 
    void SetTitleFont( wxFont font );
    void SetSubTitleFont( wxFont font );

    ///  @brief Set the Top PageMargin object
    ///  
    ///  @param pageMargin 
    void SetTopPageMargin( wxString pageMargin );

    ///  @brief Set the Top PageMargin Modified object
    ///  
    ///  @param state 
    void SetTopPageMarginModified( bool state );

    ///  @brief 
    ///  
    ///  @param event 
    void OnCancelClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnNameDefaultClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnNbrDefaultClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnOkClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnTextDefaultClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnTitleDefaultClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    void UpdateControls( );

    void OnOrientationchoiceSelected( wxCommandEvent& event );
    wxString GetOrientation( ) { return  m_orientationChoice->GetStringSelection( ); };
    void SetOrientation( wxString sel ) { m_orientationChoice->SetStringSelection( sel ); }

    Design::TitleLocation GetDefaultStampNameLocation( )
    {
        return m_stampNameLocation;
    }
    void SetStampNameLocation( );

    void OnTopRadioButtonSelected( wxCommandEvent& event );
    void OnBottomRadioButtonSelected( wxCommandEvent& event );

private:
    LabeledTextBox* m_name;
    LabeledTextBox* m_paperHeight;
    LabeledTextBox* m_paperWidth;
    LabeledTextBox* m_height;
    LabeledTextBox* m_width;
    LabeledTextBox* m_topPageMargin;
    LabeledTextBox* m_bottomPageMargin;
    LabeledTextBox* m_rightPageMargin;
    LabeledTextBox* m_leftPageMargin;
    LabeledTextBox* m_borderSize;
    LabeledTextBox* m_borderFilename;
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

    wxRadioButton* m_defaultButton;
    wxButton* m_validate;
    wxListBox* m_statusList;

    AlbumDetailsDialog* theDialog;
    Design::Album* m_album;
};

#endif
