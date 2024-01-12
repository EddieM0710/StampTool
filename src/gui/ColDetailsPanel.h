/*
 * @file src/gui/ColDetailsPanel.h
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

#ifndef _COLDETAILSPANEL_H_
#define _COLDETAILSPANEL_H_

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/HelperPanel.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"

class LabeledTextBox;
class wxListCtrl;
class TitleHelper;
namespace Design {
    class Column;
};


#define SYMBOL_COLDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_COLDETAILSDIALOG_TITLE _( "Col Details Dialog" )
#define SYMBOL_COLDETAILSDIALOG_IDNAME ID_COLDETAILSDIALOG
#define SYMBOL_COLDETAILSDIALOG_SIZE wxSize( -1, -1 )
#define SYMBOL_COLDETAILSDIALOG_POSITION wxDefaultPosition

class ColDetailsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( ColDetailsPanel )
    DECLARE_EVENT_TABLE( )

public:

    enum ColDetailsPanelGuiDefs {
        ID_NAMELABELEDTEXTBOX = ID_COLDETAILSDIALOG + 1,
        ID_COLTITLECHECKBOX,
        ID_COLSUBTITLECHECKBOX,
        ID_FRAMECHECKBOX,
        ID_LISTCTRL,
        //  ID_COLNOTEBOOK,
        ID_COLNAMEPANEL,
        ID_COLDEFAULTFONTBUTTON,
        ID_COLLAYOUTPANEL,
        ID_COLLAYOUTTEXTCTRL,
        //    ID_NOTEBOOKPOSITIONPANEL,
    //ID_POSITIONTEXTCTRL,
           // ID_NOTEBOOK,
           // ID_NOTEBOOKDETAILSPANEL,
        ID_DEFAULTFONTBUTTON,
        ID_DEFAULTRADIOBUTTON,
        ID_TOPRADIOBUTTON,
        ID_BOTTOMRADIOBUTTON,
        //ID_LEFTRADIOBUTTON,
        //ID_RIGHTRADIOBUTTON,
        ID_CALCULATEDRADIOBUTTON,
        ID_FIXEDRADIOBUTTON,
        ID_FIXEDSIZETEXTCTRL,
        ID_LastID
    };

    ///  @brief Construct a new Col Details Dialog object
    ///  
    ColDetailsPanel( );

    ///  @brief Construct a new Col Details Dialog object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param caption 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ColDetailsPanel( wxWindow* parent, wxWindowID id = SYMBOL_COLDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_COLDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_COLDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_COLDETAILSDIALOG_SIZE, long style = SYMBOL_COLDETAILSDIALOG_STYLE );

    ///  @brief Destroy the Col Details Dialog object
    ///  
    ~ColDetailsPanel( );

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
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_COLDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_COLDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_COLDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_COLDETAILSDIALOG_SIZE, long style = SYMBOL_COLDETAILSDIALOG_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief Get the Fixed Spacing object
    ///  
    ///  @return wxString 
    wxString GetFixedSpacing( ) {
        return m_positionFixedSize->GetValue( );
    };

    ///  @brief Get the Show Title object
    ///  
    ///  @return true 
    ///  @return false 
    bool GetShowTitle( );
    bool GetShowSubTitle( );

    ///  @brief Get the Show Frame object
    ///  
    ///  @return true 
    ///  @return false 
    bool GetShowFrame( );

    ///  @brief Get the Title Font object
    ///  
    ///  @return wxFont 
    wxFont GetTitleFont( );
    wxString GetTitle( );

    ///  @brief Get the Title Color object
    ///  
    ///  @return wxColour 
    wxColour GetTitleColor( );

    ///  @brief 
    ///  
    void Init( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsNameModified( );

    ///  @brief 
    ///  
    ///  @param event 
    void OnOkClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnDefaultRadioButtonSelected( wxCommandEvent& event );

    void OnFrameCheckboxClick( wxCommandEvent& event );


    ///  @brief 
    ///  
    ///  @param event 
    void OnTitleDefaultClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnFixedClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnCalculatedClick( wxCommandEvent& event );

    ///  @brief Set the Calculate Spacing object
    ///  
    ///  @param val 
    void SetCalculateSpacing( bool val );

    ///  @brief Set the Fixed Spacing Size object
    ///  
    ///  @param str 
    void SetFixedSpacingSize( wxString str ) {
        m_positionFixedSize->SetValue( str );
    };

    ///  @brief Set the Name Modified object
    ///  
    ///  @param state 
    void SetNameModified( bool state );

    ///  @brief Set the Show Title object
    ///  
    ///  @param state 
    void SetShowTitle( bool state = false );
    void SetShowSubTitle( bool state = false );

    ///  @brief Set the Show Frame object
    ///  
    ///  @param state 
    void SetShow( bool state = false );

    ///  @brief Set the Title Color object
    ///  
    ///  @param color 
    void SetTitleColor( wxColour color );

    ///  @brief Set the Title Font object
    ///  
    ///  @param font 
    void SetTitleFont( wxFont font );

    ///  @brief Set the Title Layout Location object
    ///  
    void SetTitleLocation( );
    Design::StampNamePosType  GetTitleLocation( );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool CalculateSpacing( ) {
        return m_positionCalculated->GetValue( );
    };

    ///  @brief 
    ///  
    ///  @param treeID 
    void SetupDialog( Design::Column* col );

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );

    ///  @brief 
    ///  
    void UpdateControls( );

    void OnTopContentMargin( wxCommandEvent& event );

    void OnBottomContentMargin( wxCommandEvent& event );

    void OnLeftContentMargin( wxCommandEvent& event );

    void OnRightContentMargin( wxCommandEvent& event );

    void OnShowBorderCheckBoxClick( wxCommandEvent& event );

    void SetTopContentMargin( wxString contentMargin );

    void SetBottomContentMargin( wxString contentMargin );

    void SetLeftContentMargin( wxString contentMargin );

    void SetRightContentMargin( wxString contentMargin );

    void OnSubTitleDefaultClick( wxCommandEvent& event );
    void OnTitleCheckboxClick( wxCommandEvent& event );
    void OnSubTitleCheckboxClick( wxCommandEvent& event );
    void  OnTitleTextChanged( wxCommandEvent& event );
    void OnSubTitleTextChanged( wxCommandEvent& event );

    void OnTitleFontPicker( wxFontPickerEvent& event );
    void OnTitleColorPicker( wxColourPickerEvent& event );

    void OnSubTitleFontPicker( wxFontPickerEvent& event );
    void OnSubTitleColorPicker( wxColourPickerEvent& event );

    void SetStatusList( );

    void Update( );


private:


    wxTextCtrl* m_topContentMargin;
    wxTextCtrl* m_bottomContentMargin;
    wxTextCtrl* m_rightContentMargin;
    wxTextCtrl* m_leftContentMargin;


    wxCheckBox* m_frameCheckbox;
    wxListBox* m_statusList;
    wxFontPickerCtrl* m_titleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxTextCtrl* positionTextCtrl;
    Design::Column* m_col;
    wxTreeItemId m_designTreeID;


    wxRadioButton* m_defaultButton;
    wxRadioButton* m_positionCalculated;
    wxRadioButton* m_positionFixed;
    wxTextCtrl* m_positionFixedSize;
    // wxFontPickerCtrl* m_nameFontPicker;
    wxFontPickerCtrl* m_subTitleFontPicker;
    //  wxColourPickerCtrl* m_nameColorPicker;
    wxColourPickerCtrl* m_subTitleColorPicker;
    wxBoxSizer* m_dialogVerticalSizer;
    TitleHelper* m_titleHelper;
};

#endif
// _COLDETAILSDIALOG_H_
