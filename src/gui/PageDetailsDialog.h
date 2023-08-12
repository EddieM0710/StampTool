/*
 * @file         PageDetailsDialog.h
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

#ifndef _PAGEDETAILSDIALOG_H_
#define _PAGEDETAILSDIALOG_H_


/*
 * Includes
 */

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"
#include "design/Album.h"

 /*
  * Forward declarations
  */

class LabeledTextBox;
class wxListCtrl;
class TitleHelper;
namespace Design { class Page; };


#define SYMBOL_PAGEDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_PAGEDETAILSDIALOG_TITLE _( "PageDetailsDialog" )
#define SYMBOL_PAGEDETAILSDIALOG_IDNAME ID_PAGEDETAILSDIALOG
#define SYMBOL_PAGEDETAILSDIALOG_SIZE wxSize( 600, 800 )
#define SYMBOL_PAGEDETAILSDIALOG_POSITION wxDefaultPosition


/*
 * PageDetailsDialog class declaration
 */

class PageDetailsDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( PageDetailsDialog )
    DECLARE_EVENT_TABLE( )

public:

    /*
    * Control identifiers
    */
    enum PageDetailsDialogGuiDefs {
        //#define  10000
        ID_NOTEBOOKPOSITIONPANEL = ID_PAGEDETAILSDIALOG + 1,
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




    PageDetailsDialog( );
    PageDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_PAGEDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_PAGEDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_PAGEDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_PAGEDETAILSDIALOG_SIZE, long style = SYMBOL_PAGEDETAILSDIALOG_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PAGEDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_PAGEDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_PAGEDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_PAGEDETAILSDIALOG_SIZE, long style = SYMBOL_PAGEDETAILSDIALOG_STYLE );


    ~PageDetailsDialog( );


    void Init( );

    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( wxTreeItemId treeID );


    static bool ShowToolTips( );

    void OnOkClick( wxCommandEvent& event );

    void OnTitleDefaultClick( wxCommandEvent& event );

    void SetNameModified( bool state );
    bool IsNameModified( );
    void SetName( wxString name );
    wxString GetName( );
    void SetSubTitle( wxString subTitle );
    wxString GetSubTitle( );
    void SetShowTitle( bool state = false );
    void SetShowSubTitle( bool state = false );
    void SetShowFrame( bool state = false );
    void SetTitleColor( wxColour color );
    void SetTitleFont( wxFont font );
    void SetSubTitleColor( wxColour color );
    void SetSubTitleFont( wxFont font );
    bool GetShowTitle( );
    bool GetShowSubTitle( );
    bool GetShowFrame( );

    void OnOrientationchoiceSelected( wxCommandEvent& event );
    wxString GetOrientation( ) { return  m_orientationChoice->GetStringSelection( ); };
    void SetOrientation( wxString sel ) { m_orientationChoice->SetStringSelection( sel ); }
    void OnSubTitleDefaultClick( wxCommandEvent& event );
    void OnNameCheckboxClick( wxCommandEvent& event );
    void OnSubTitleCheckboxClick( wxCommandEvent& event );
    void OnNameDefaultClick( wxCommandEvent& event );

private:
    LabeledTextBox* m_name;
    wxCheckBox* m_titleCheckbox;
    wxCheckBox* m_subTitleCheckbox;
    wxCheckBox* m_frameCheckbox;
    wxChoice* m_orientationChoice;
    wxListBox* m_statusList;
    //wxFontPickerCtrl* m_titleFontPicker;
    //wxColourPickerCtrl* m_titleColorPicker;
    wxTextCtrl* positionTextCtrl;
    Design::Page* m_page;
    wxTreeItemId m_designTreeID;
    TitleHelper* m_titleHelper;
    LabeledTextBox* m_subTitleLabel;
    wxFontPickerCtrl* m_nameFontPicker;
    wxFontPickerCtrl* m_subTitleFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
    wxColourPickerCtrl* m_subTitleColorPicker;
    wxBoxSizer* m_dialogVerticalSizer;
};

#endif
// _PAGEDETAILSDIALOG_H_
