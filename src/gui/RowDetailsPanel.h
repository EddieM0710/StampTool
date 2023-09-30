/*
 * @file RowDetailsPanel.h
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

#ifndef _ROWDETAILSPANEL_H_
#define _ROWDETAILSPANEL_H_

#include "wx/listctrl.h"

#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"
#include "gui/HelperPanel.h"


 /*
  * Forward declarations
  */
class LabeledTextBox;
class wxListCtrl;
class TitleHelper;
namespace Design {
    class Row;
};

/*
 * Control identifiers
 */



#define SYMBOL_ROWDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_ROWDETAILSDIALOG_TITLE _( "Row Details Dialog" )
#define SYMBOL_ROWDETAILSDIALOG_IDNAME ID_ROWDETAILSDIALOG
#define SYMBOL_ROWDETAILSDIALOG_SIZE wxSize( -1, -1 )
#define SYMBOL_ROWDETAILSDIALOG_POSITION wxDefaultPosition



 /*
  * RowDetailsPanel class declaration
  */

class RowDetailsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( RowDetailsPanel )
    DECLARE_EVENT_TABLE( )

public:
    enum RowDetailsPanelGuiDefs {

        ID_NAMELABELEDTEXTBOX = ID_ROWDETAILSDIALOG,
        ID_ROWTITLECHECKBOX,
        ID_ROWSUBTITLECHECKBOX,
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
        ID_POSITIONTEXTCTRL,
        ID_TITLELOCATION,
        ID_DEFAULTRADIOBUTTON,
        ID_TOPRADIOBUTTON,
        ID_BOTTOMRADIOBUTTON,
        ID_LEFTRADIOBUTTON,
        ID_RIGHTRADIOBUTTON,
        ID_CALCULATEDRADIOBUTTON,
        ID_FIXEDRADIOBUTTON,
        ID_FIXEDSIZETEXTCTRL,
        ID_LastID
    };



    RowDetailsPanel( );
    RowDetailsPanel( wxWindow* parent, wxWindowID id = SYMBOL_ROWDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ROWDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ROWDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ROWDETAILSDIALOG_SIZE, long style = SYMBOL_ROWDETAILSDIALOG_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ROWDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ROWDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ROWDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ROWDETAILSDIALOG_SIZE, long style = SYMBOL_ROWDETAILSDIALOG_STYLE );

    ~RowDetailsPanel( );

    void Init( );


    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( Design::Row* row );

    // RowDetailsPanel event handler declarations

    //   wxID_OK
    void OnOkClick( wxCommandEvent& event );
    void OnDefaultRadioButtonSelected( wxCommandEvent& event );
    void OnTopRadioButtonSelected( wxCommandEvent& event );
    void OnBottomRadioButtonSelected( wxCommandEvent& event );
    void OnTitleDefaultClick( wxCommandEvent& event );

    void OnFixedClick( wxCommandEvent& event );
    void OnCalculatedClick( wxCommandEvent& event );

    void SetNameModified( bool state );
    void SetShowTitle( bool state = false );
    void SetShowSubTitle( bool state = false );
    void SetShowFrame( bool state = false );
    void SetColor( wxColour color );
    void SetFont( wxFont font );
    bool GetShowTitle( );
    bool GetShowSubTitle( );
    bool GetShowFrame( );
    void SetTitleLocation( );
    Design::TitleLocation GetTitleLocationType( );
    void SetCalculateSpacing( bool val );
    void SetFixedSpacingSize( wxString str ) {
        //     m_positionFixedSize->SetValue( str );
    };
    wxString GetFixedSpacing( ) {
        return m_positionFixedSize->GetValue( );
    };
    bool CalculateSpacing( ) {
        return m_positionCalculated->GetValue( );
    };

    wxString GetTitle( );
    void SetTitle( wxString str );

    bool IsNameModified( );


    // void OnTitleDefaultClick( wxCommandEvent& event );
    void OnSubTitleDefaultClick( wxCommandEvent& event );
    void OnTitleCheckboxClick( wxCommandEvent& event );
    void OnSubTitleCheckboxClick( wxCommandEvent& event );



    void OnTitleFontPicker( wxFontPickerEvent& event );
    void OnTitleColorPicker( wxColourPickerEvent& event );

    void OnSubTitleFontPicker( wxFontPickerEvent& event );
    void OnSubTitleColorPicker( wxColourPickerEvent& event );

    void OnTitleTextChanged( wxCommandEvent& event );
    void OnSubTitleTextChanged( wxCommandEvent& event );
private:


    wxCheckBox* m_frameCheckbox;
    wxListBox* m_statusList;
    wxFontPickerCtrl* m_titleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxTextCtrl* positionTextCtrl;
    Design::Row* m_row;
    wxTreeItemId m_designTreeID;
    wxStaticBox* m_TitleLocationBox;
    wxStaticBoxSizer* m_titleLocationVSizer;
    wxBoxSizer* m_titleLocationHSizer;
    Design::TitleLocation m_titleLocation;
    wxRadioButton* m_topButton;
    wxRadioButton* m_bottomButton;

    wxRadioButton* m_defaultButton;
    wxRadioButton* m_positionCalculated;
    wxRadioButton* m_positionFixed;
    wxTextCtrl* m_positionFixedSize;

    wxBoxSizer* m_dialogVerticalSizer;

    //wxTextCtrl* positionTextCtrl;
    wxFontPickerCtrl* m_nbrFontPicker;
    wxFontPickerCtrl* m_nameFontPicker;
    wxFontPickerCtrl* m_subTitleFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
    wxColourPickerCtrl* m_subTitleColorPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    TitleHelper* m_titleHelper;
};

#endif
// _ROWDETAILSDIALOG_H_
