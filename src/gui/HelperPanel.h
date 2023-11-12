//
// @file         HelperPanel.h
// @brief
// @author      Eddie Monroe
// Modified by :
//@date     Wed 23 Nov 2022 11:31 : 39 CST
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

#ifndef _HELPERPANEL_H_
#define _HELPERPANEL_H_

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
#include <wx/radiobut.h>
#include <wx/checklst.h>

#include "gui/GuiDefs.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/FontPickerHelper.h"

class LabeledTextBox;
class wxListCtrl;
namespace Design {
    class Album;
};

#define HasTextCtrl 0x1
#define HasSubTitle  0x2
#define NoHideTextCtrl 0x4
#define DefaultTitleHelperStyle HasTextCtrl | HasSubTitle

#define SYMBOL_HELPERPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_HELPERPANEL_TITLE _( "HelperPanel" )
#define SYMBOL_HELPERPANEL_IDNAME ID_ALBUMDETAILSDIALOG
#define SYMBOL_HELPERPANEL_SIZE wxDefaultSize
#define SYMBOL_HELPERPANEL_POSITION wxDefaultPosition
class HelperPanel;

///  @brief
///  
class HelperPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( HelperPanel )
    DECLARE_EVENT_TABLE( )

public:
    typedef struct
    {
        wxCheckBox* titleCheckbox;
        wxCheckBox* subTitleCheckbox;
        wxTextCtrl* subTitleLabel;
        wxTextCtrl* titleLabel;
    }TitleHelper;


    HelperPanel( );


    HelperPanel( wxWindow* parent, wxWindowID id = SYMBOL_HELPERPANEL_IDNAME, const wxString& caption = SYMBOL_HELPERPANEL_TITLE, const wxPoint& pos = SYMBOL_HELPERPANEL_POSITION, const wxSize& size = SYMBOL_HELPERPANEL_SIZE, long style = SYMBOL_HELPERPANEL_STYLE );


    ~HelperPanel( );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_HELPERPANEL_IDNAME, const wxString& caption = SYMBOL_HELPERPANEL_TITLE, const wxPoint& pos = SYMBOL_HELPERPANEL_POSITION, const wxSize& size = SYMBOL_HELPERPANEL_SIZE, long style = SYMBOL_HELPERPANEL_STYLE );


    void CreateControls( );

    void Init( );

    wxStaticBox* SetupBoxSizer( wxWindow* parent, wxBoxSizer* inSizer, wxString name,
        int& lastID, wxBoxSizer*& boxSizer, wxOrientation orientation );

    wxCheckBox* SetupCheckBox( wxWindow* parent, wxBoxSizer* sizer,
        int& lastID, wxString label, wxObjectEventFunction  eventHandler );

    wxCheckListBox* SetupCheckListBox( wxWindow* parent, wxBoxSizer* inSizer, int& lastID,
        wxString label, wxArrayString& array,
        wxObjectEventFunction  allButtonEventHandler,
        wxObjectEventFunction  clearButtonEventHandler );

    wxChoice* SetupChoice( wxWindow* parent, wxBoxSizer* sizer,
        int& lastID, wxString label,
        wxArrayString choiceStrings, wxObjectEventFunction  eventHandler );

    FontPicker* SetupFontPicker( wxWindow* parent, wxBoxSizer* verticalSizer, int& lastID,
        wxString staticText, wxString buttonText,
        wxFontPickerCtrl*& fontCtrl,
        wxColourPickerCtrl*& colorCtrl,
        wxObjectEventFunction  fontPicker,
        wxObjectEventFunction  colorPicker,
        wxObjectEventFunction  defaultButtonHandler );

    wxTextCtrl* SetupLabelText( wxWindow* parent, wxBoxSizer* verticalSizer,
        int& lastID, wxString label, bool grow, wxObjectEventFunction  eventHandler );

    wxTextCtrl* SetupMultilineLabeledText( wxWindow* parent, wxBoxSizer* inSizer, int& lastID, wxString label, bool grow,
        wxObjectEventFunction  eventHandler );

    wxRadioButton* SetupRadioButton( wxWindow* parent, wxBoxSizer* sizer, int& lastID,
        wxString label, bool initValue, wxObjectEventFunction  eventHandler );

    TitleHelper* SetupTitleHelper( wxWindow* parent, wxBoxSizer* verticalSizer, int& idLast,
        int style = DefaultTitleHelperStyle,
        wxObjectEventFunction  titleCheckBoxEventHandler = ( wxEventFunction ) 0,
        wxObjectEventFunction  titleEventHandler = ( wxEventFunction ) 0,
        wxObjectEventFunction  subTitleCheckBoxEeventHandler = ( wxEventFunction ) 0,
        wxObjectEventFunction  subTitleEventHandler = ( wxEventFunction ) 0 );

    void UpdateSubTitleState( HelperPanel::TitleHelper* titleHelper );

    void UpdateTitleState( HelperPanel::TitleHelper* titleHelper );

    void SetSubTitleCheckboxValue( HelperPanel::TitleHelper* titleHelper, bool state );

    void SetTitleCheckboxValue( HelperPanel::TitleHelper* titleHelper, bool state );

    wxStaticBox* SetupStaticBox( wxWindow* parent, wxBoxSizer* inSizer, wxBoxSizer* outBoxSizer );

    void HorizontalSpacer( wxBoxSizer* inSizer );

    void VerticalSpacer( wxBoxSizer* inSizer );
private:
};
#endif