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

#include "gui/DesignTreeCtrl.h"
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
class StampDetailsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( StampDetailsDialog )
        DECLARE_EVENT_TABLE( )

public:

    enum StampDetailsDialogGuiDefs {
        ID_IDLABELTEXTBOX = ID_STAMPDETAILSDIALOG,
        ID_NAMELABELEDTEXTBOX1,
        ID_HEIGHTLABELEDTEXTBOX,
        ID_WIDTHLABELEDTEXTBOX,
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
        ID_POSITIONTEXTCTRL,
        ID_STAMPCATNBRFONTPICKER,
        ID_STAMPCATNBRCOLORPICKER,
        ID_STAMPTEXTFONTPICKER,
        ID_STAMPTEXTCOLORPICKER,
        ID_STAMPTEXTEDEFAULTFONTBUTTON,
        ID_STAMPCATNBRDEFAULTFONTBUTTON
    };

    StampDetailsDialog( );
    StampDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_STAMPDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_STAMPDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_STAMPDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_STAMPDETAILSDIALOG_SIZE, long style = SYMBOL_STAMPDETAILSDIALOG_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STAMPDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_STAMPDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_STAMPDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_STAMPDETAILSDIALOG_SIZE, long style = SYMBOL_STAMPDETAILSDIALOG_STYLE );


    ~StampDetailsDialog( );


    void Init( );


    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( wxTreeItemId id );

    // StampDetailsDialog event handler declarations

        ///   ID_REFRESHBUTTON
    void OnRefreshButtonClick( wxCommandEvent& event );

    ///   wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    ///   wxID_OK
    void OnOkClick( wxCommandEvent& event );

    void OnNbrDefaultClick( wxCommandEvent& event );
    void OnTextDefaultClick( wxCommandEvent& event );
    void OnCatNbrCheckboxClicked( wxCommandEvent& event );



    static bool ShowToolTips( );

    void SetImageFilename( wxString filename );
    void SetHeight( wxString height );
    void SetWidth( wxString width );
    void SetCatNbr( wxString catNbr );
    void SetName( wxString name );
    void SetShowCatNbr( bool state = false );
    void SetShowTitle( bool state = false );
    void SetCatNbrFont( wxFont font );
    void SetTextFont( wxFont font );
    void SetCatNbrColor( wxColour color );
    void SetTextColor( wxColour color );

    wxString GetImageFilename( );
    wxString GetHeight( );
    wxString GetWidth( );
    wxString GetCatNbr( );
    wxString GetName( );
    wxFont GetCatNbrFont( );
    wxFont GetTextFont( );
    wxColour GetCatNbrColor( );
    wxColour GetTextColor( );
    bool GetShowCatNbr( );
    bool GetShowTitle( );

    bool IsNameModified( );
    bool IsIDModified( );
    bool IsHeightModified( );
    bool IsWidthModified( );
    void SetHeightModified( bool state = true );
    void SetWidthModified( bool state = true );
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
    wxButton* m_validate;
    wxListBox* m_statusList;
    wxTreeItemId m_designTreeID;
    wxCheckBox* m_catNbrCheckbox;
    wxCheckBox* m_titleCheckbox;
    wxTextCtrl* positionTextCtrl;
    wxFontPickerCtrl* m_catNbrFontPicker;
    wxFontPickerCtrl* m_textFontPicker;
    wxColourPickerCtrl* m_textColorPicker;
    wxColourPickerCtrl* m_catNbrColorPicker;
    Design::Stamp* m_stamp;



};

#endif
// _STAMPDETAILSDIALOG_H_
