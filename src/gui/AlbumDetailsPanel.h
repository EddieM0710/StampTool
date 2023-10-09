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
        ID_NAMELABELEDTEXTBOX = ID_ALBUMDETAILSDIALOG + 1
    };


    AlbumDetailsPanel( );


    AlbumDetailsPanel( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSPANEL_SIZE, long style = SYMBOL_ALBUMDETAILSPANEL_STYLE );


    ~AlbumDetailsPanel( );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSPANEL_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSPANEL_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSPANEL_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSPANEL_SIZE, long style = SYMBOL_ALBUMDETAILSPANEL_STYLE );

    /// @brief Create a Controls object
    /// 
    void CreateControls( );
    wxString GetBorderSize( );

    wxString GetBorderFilename( );

    wxString GetCatalog( );

    wxString GetBottomPageMargin( );

    bool GetGrayScaleImages( );

    wxString GetLeftPageMargin( );

    wxString GetName( );

    wxColour GetNameColor( );

    wxFont GetNameFont( );

    wxColour GetNbrColor( );

    wxFont GetNbrFont( );

    wxString GetPageHeight( );

    wxString GetPageWidth( );

    wxString GetPaperHeight( );

    wxString GetPaperWidth( );

    wxString GetRightPageMargin( );

    bool GetShowNbr( );

    bool GetShowStampTitle( );

    bool GetShowStampSubTitle( );

    wxColour GetTextColor( );

    bool GetOverSizePaper( );

    wxFont GetTextFont( );

    wxColour GetTitleColor( );

    wxColour GetSubTitleColor( );

    wxFont GetTitleFont( );

    wxFont GetSubTitleFont( );

    wxString GetTopPageMargin( );

    Design::TitleLocation GetDefaultStampNameLocation( )
    {
        return m_stampNameLocation;
    }

    void Init( );


    void OnCancelClick( wxCommandEvent& event );

    void OnNameDefaultClick( wxCommandEvent& event );

    void OnNameClick( wxCommandEvent& event );

    void OnPaperHeight( wxCommandEvent& event );

    void OnOverSizeCheckBoxClick( wxCommandEvent& event );

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

    void OnOkClick( wxCommandEvent& event );

    void OnTextDefaultClick( wxCommandEvent& event );

    void OnTextFontPicker( wxFontPickerEvent& event );

    void OnTextColorPicker( wxColourPickerEvent& event );

    void OnTitleDefaultClick( wxCommandEvent& event );

    void OnTitleFontPicker( wxFontPickerEvent& event );

    void OnTitleColorPicker( wxColourPickerEvent& event );

    void OnTopRadioButtonSelected( wxCommandEvent& event );

    void OnBottomRadioButtonSelected( wxCommandEvent& event );


    void OnOrientationchoiceSelected( wxCommandEvent& event );

    wxString GetOrientation( ) {
        return m_orientationChoice->GetStringSelection( );
    };

    void SetAlbum( Design::Album* album ) {
        m_album = album;
    };

    void SetBorderSize( wxString size );

    void SetBorderFilename( wxString filename );


    void SetBottomPageMargin( wxString pageMargin );

    void SetCatalog( wxString catCode );

    void SetGrayScaleImages( bool val );

    void SetLeftPageMargin( wxString pageMargin );

    void SetName( wxString name );

    void SetNameColor( wxColour color );

    void SetNameFont( wxFont font );

    void SetNbrColor( wxColour color );

    void SetNbrFont( wxFont font );

    void SetPageHeight( wxString height );

    void SetPageWidth( wxString width );

    void SetPaperWidth( wxString width );

    void SetPaperHeight( wxString height );

    void SetRightPageMargin( wxString pageMargin );

    void SetShowNbr( bool state );

    void SetOrientation( wxString sel ) {
        m_orientationChoice->SetStringSelection( sel );
    }

    void SetOverSizePaper( bool state );

    void SetShowStampTitle( bool state );

    void SetTextColor( wxColour color );

    void SetTextFont( wxFont font );

    void SetTitleColor( wxColour color );

    void SetSubTitleColor( wxColour color );

    void SetSubTitleFont( wxFont font );

    void SetTitleFont( wxFont font );

    void SetTopPageMargin( wxString pageMargin );

    void SetupDialog( Design::Album* album );

    wxPanel* SetupAlbumDetailsPanel( wxWindow* parent, int& lastID );

    wxPanel* SetupPageDetailsPanel( wxWindow* parent, int& lastID );

    wxPanel* SetupRowColDetailsPanel( wxWindow* parent, int& lastID );

    wxPanel* SetupStampDetailsPanel( wxWindow* parent, int& lastID );

    void SetStampNameLocation( );

    static bool ShowToolTips( );

    void UpdateControls( );

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
