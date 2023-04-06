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
#include "gui/DesignTreeCtrl.h"

/*
 * Forward declarations
 */
class LabeledTextBox;
class wxListCtrl;
namespace Design { class Album; };

#define SYMBOL_ALBUMDETAILSDIALOG_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_ALBUMDETAILSDIALOG_TITLE _( "AlbumDetailsDialog" )
#define SYMBOL_ALBUMDETAILSDIALOG_IDNAME ID_ALBUMDETAILSDIALOG
#define SYMBOL_ALBUMDETAILSDIALOG_SIZE wxSize( 400, 300 )
#define SYMBOL_ALBUMDETAILSDIALOG_POSITION wxDefaultPosition


//
// AlbumDetailsDialog class declaration
//

class AlbumDetailsDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( AlbumDetailsDialog )
        DECLARE_EVENT_TABLE( )

public:

    enum AlbumDetailDialogDefs {
        ID_NAMELABELEDTEXTBOX = ID_ALBUMDETAILSDIALOG + 1,
        ID_HEIGHTLABELEDTEXTBOX123,
        ID_WIDTHLABELEDTEXTBOX123,
        ID_TOPMARGINLABELEDTEXTBOX,
        ID_BOTTOMMARGINLABELEDTEXTBOX,
        ID_RIGHTMARGINLABELEDTEXTBOX,
        ID_LEFTMARGINLABELEDTEXTBOX,
        ID_BORDERSIZELABELEDTEXTBOX,
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

        ID_NBRDEFAULTCHECKBOX,
        ID_STAMPTITLEDEFAULTCHECKBOX,
        ID_ROWCOLTITLEDEFAULTCHECKBOX,
        ID_FRAMEDEFAULTCHECKBOX,
        ID_GRAYSCALECHECKBOX,

        ID_TITLEFONTPANEL,
        ID_ALBUMLAYOUTTEXTCTRL,
        ID_ALBUMLAYOUTPANEL,
        ID_ALBUMNOTEBOOK,
        ID_ALBUMNAMEPANEL
    };


    AlbumDetailsDialog( );
    AlbumDetailsDialog( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSDIALOG_SIZE, long style = SYMBOL_ALBUMDETAILSDIALOG_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ALBUMDETAILSDIALOG_IDNAME, const wxString& caption = SYMBOL_ALBUMDETAILSDIALOG_TITLE, const wxPoint& pos = SYMBOL_ALBUMDETAILSDIALOG_POSITION, const wxSize& size = SYMBOL_ALBUMDETAILSDIALOG_SIZE, long style = SYMBOL_ALBUMDETAILSDIALOG_STYLE );

    ~AlbumDetailsDialog( );

    void Init( );

    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( wxTreeItemId id );


    static bool ShowToolTips( );
    void SetName( wxString name );
    void SetPageHeight( wxString height );
    void SetPageWidth( wxString width );
    void SetTopMargin( wxString margin );
    void SetBottomMargin( wxString margin );
    void SetLeftMargin( wxString margin );
    void SetRightMargin( wxString margin );
    void SetBorderSize( wxString size );
    void SetShowNbr( bool state );
    void SetShowStampTitle( bool state );
    void SetNbrFont( wxFont font );
    void SetNameFont( wxFont font );
    void SetTextFont( wxFont font );
    void SetTitleFont( wxFont font );
    void SetNbrColor( wxColour color );
    void SetNameColor( wxColour color );
    void SetTextColor( wxColour color );
    void SetTitleColor( wxColour color );
    void SetGrayScaleImages( bool val );

    wxString GetName( );
    wxString GetPageHeight( );
    wxString GetPageWidth( );
    wxString GetTopMargin( );
    wxString GetBottomMargin( );
    wxString GetLeftMargin( );
    wxString GetRightMargin( );
    wxString GetBorderSize( );
    bool GetShowNbr( );
    bool GetShowStampTitle( );
    bool GetGrayScaleImages( );


    bool IsNameModified( );
    bool IsPageHeightModified( );
    bool IsPageWidthModified( );
    bool IsTopMarginModified( );
    bool IsBottomMarginModified( );
    bool IsLeftMarginModified( );
    bool IsRightMarginModified( );
    bool IsBorderSizeModified( );

    void SetNameModified( bool state );
    void SetPageHeightModified( bool state );
    void SetPageWidthModified( bool state );
    void SetTopMarginModified( bool state );
    void SetBottomMarginModified( bool state );
    void SetLeftMarginModified( bool state );
    void SetRightMarginModified( bool state );
    void SetBorderSizeModified( bool state );

    wxFont GetNbrFont( );
    wxFont GetNameFont( );
    wxFont GetTextFont( );
    wxFont GetTitleFont( );
    wxColour GetNbrColor( );
    wxColour GetNameColor( );
    wxColour GetTextColor( );
    wxColour GetTitleColor( );

    void OnOkClick( wxCommandEvent& event );
    void OnCancelClick( wxCommandEvent& event );
    void OnNbrDefaultClick( wxCommandEvent& event );
    void OnNameDefaultClick( wxCommandEvent& event );
    void OnTitleDefaultClick( wxCommandEvent& event );
    void OnTextDefaultClick( wxCommandEvent& event );
    void SetAlbum( Design::Album* album ) { m_album = album; };

private:
    LabeledTextBox* m_name;
    LabeledTextBox* m_height;
    LabeledTextBox* m_width;
    LabeledTextBox* m_topMargin;
    LabeledTextBox* m_bottomMargin;
    LabeledTextBox* m_rightMargin;
    LabeledTextBox* m_leftMargin;
    LabeledTextBox* m_borderSize;

    wxCheckBox* m_nbrCheckbox;
    wxCheckBox* m_stampTitleCheckbox;
    wxCheckBox* m_grayScaleImagesCheckbox;
    wxFontPickerCtrl* m_titleFontPicker;
    wxColourPickerCtrl* m_titleColorPicker;
    wxFontPickerCtrl* m_nbrFontPicker;
    wxColourPickerCtrl* m_nbrColorPicker;
    wxFontPickerCtrl* m_nameFontPicker;
    wxColourPickerCtrl* m_nameColorPicker;
    wxFontPickerCtrl* m_textFontPicker;
    wxColourPickerCtrl* m_textColorPicker;

    wxButton* m_validate;
    wxListCtrl* m_statusList;
    AlbumDetailsDialog* theDialog;
    Design::Album* m_album;
};

#endif
