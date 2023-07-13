/*
 * @file StampDetailsDialog.h
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
#ifndef _STAMPDETAILSDIALOG_H_
#define _STAMPDETAILSDIALOG_H_


 /*
  * Includes
  */

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"


  /*
   * Forward declarations
   */
class LabeledTextBox;
class wxListCtrl;
namespace Design { class Stamp; };

/*
 * Control identifiers
 */
#define SYMBOL_STAMPDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_STAMPDETAILSDIALOG_TITLE _( "StampDetailsDialog" )
#define SYMBOL_STAMPDETAILSDIALOG_IDNAME ID_STAMPDETAILSDIALOG
#define SYMBOL_STAMPDETAILSDIALOG_SIZE wxSize( 400, 800 )
#define SYMBOL_STAMPDETAILSDIALOG_POSITION wxDefaultPosition



 /*
  * StampDetailsDialog class declaration
  */
class StampDetailsDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( StampDetailsDialog )
    DECLARE_EVENT_TABLE( )

public:

    enum StampDetailsDialogGuiDefs {
        ID_IDLABELTEXTBOX = ID_STAMPDETAILSDIALOG,
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
        ID_TITLECHECKBOX,
        ID_IMAGEPATHLABELEDTEXTBOX,
        ID_STAMPNOTEBOOK,
        ID_STAMPNAMEPANEL,
        ID_STAMPLAYOUTPANEL,
        ID_STAMPLAYOUTTEXTCTRL,
        ID_NOTEBOOK,
        ID_NOTEBOOKDETAILSPANEL,
        ID_NOTEBOOKPOSITIONPANEL,
        //ID_POSITIONTEXTCTRL,
        ID_STAMPNBRFONTPICKER,
        ID_STAMPNBRCOLORPICKER,
        ID_STAMPNAMEFONTPICKER,
        ID_STAMPNAMECOLORPICKER,
        ID_STAMPNAMEDEFAULTFONTBUTTON,
        ID_STAMPNBRDEFAULTFONTBUTTON,
        ID_DEFAULTRADIOBUTTON,
        ID_TOPRADIOBUTTON,
        ID_BOTTOMRADIOBUTTON,
        ID_LEFTRADIOBUTTON,
        ID_RIGHTRADIOBUTTON
    };



    StampDetailsDialog( );
    StampDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_STAMPDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_STAMPDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_STAMPDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_STAMPDETAILSDIALOG_SIZE, long style = SYMBOL_STAMPDETAILSDIALOG_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STAMPDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_STAMPDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_STAMPDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_STAMPDETAILSDIALOG_SIZE, long style = SYMBOL_STAMPDETAILSDIALOG_STYLE );


    ~StampDetailsDialog( );


    void Init( );


    void CreateControls( );

    void SetTitleLayoutLocation( );


    void UpdateControls( );

    void SetupDialog( wxTreeItemId id );

    // StampDetailsDialog event handler declarations

        //   ID_REFRESHBUTTON
    void OnRefreshButtonClick( wxCommandEvent& event );

    //   wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    //   wxID_OK
    void OnOkClick( wxCommandEvent& event );
    void OnDefaultRadioButtonSelected( wxCommandEvent& event );
    void OnTopRadioButtonSelected( wxCommandEvent& event );
    void OnBottomRadioButtonSelected( wxCommandEvent& event );
    void OnLeftRadioButtonSelected( wxCommandEvent& event );
    void OnRightRadioButtonSelected( wxCommandEvent& event );
    void OnTitleDefaultClick( wxCommandEvent& event );
    void OnNbrDefaultClick( wxCommandEvent& event );
    void OnNameDefaultClick( wxCommandEvent& event );
    void OnCatNbrCheckboxClicked( wxCommandEvent& event );



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

    bool IsNameModified( );
    bool IsIDModified( );
    bool IsHeightModified( );
    bool IsWidthModified( );

    bool IsSelvageHeightModified( );
    bool IsSelvageWidthModified( );
    bool IsMountAllowanceHeightModified( );
    bool IsMountAllowanceWidthModified( );
    void SetHeightModified( bool state = true );
    void SetWidthModified( bool state = true );


    void SetSelvageHeightModified( bool state );
    void SetSelvageWidthModified( bool state );
    void SetMountAllowanceHeightModified( bool state );
    void SetMountAllowanceWidthModified( bool state );
    void SetCatNbrModified( bool state = true );
    void SetNameModified( bool state = true );
    void RefreshFromCatalog( );

    //  void SetStamp( Design::Stamp* stamp){ m_stamp = stamp; };




private:

    LabeledTextBox* m_catNbr;
    LabeledTextBox* m_name;
    LabeledTextBox* m_imagePath;
    LabeledTextBox* m_height;
    LabeledTextBox* m_width;
    LabeledTextBox* m_selvageHeight;
    LabeledTextBox* m_selvageWidth;
    LabeledTextBox* m_mountAllowanceHeight;
    LabeledTextBox* m_mountAllowanceWidth;
    wxButton* m_validate;
    wxListBox* m_statusList;
    wxArrayString m_statusListStrings;


    wxTreeItemId m_designTreeID;
    wxCheckBox* m_nbrCheckbox;
    wxCheckBox* m_titleCheckbox;
    //wxTextCtrl* positionTextCtrl;
    wxFontPickerCtrl* m_nbrFontPicker;
    wxFontPickerCtrl* m_nameFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    Design::Stamp* m_stamp;
    wxStaticBox* m_TitleLocationBox;
    wxStaticBoxSizer* m_titleLocationVSizer;
    wxBoxSizer* m_titleLocationHSizer;
    Design::TitleLocation m_titleLocation;
    wxRadioButton* m_topButton;
    wxRadioButton* m_bottomButton;
    //wxRadioButton* m_leftButton;
    //wxRadioButton* m_rightButton;
    wxRadioButton* m_defaultButton;


};

#endif
// _STAMPDETAILSDIALOG_H_
