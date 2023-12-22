/*
 * @file         PageDefaultsPanel.h
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

#ifndef _PageDefaultsPANEL_H_
#define _PageDefaultsPANEL_H_

/*
 * Includes
 */

#include "wx/listctrl.h"
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>

#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiDefs.h"
#include "design/Album.h"
#include "gui/HelperPanel.h"

 /*
  * Forward declarations
  */

class LabeledTextBox;
class wxListCtrl;
class TitleHelper;
namespace Design {
    class Page;
};


#define SYMBOL_PageDefaultsPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_PageDefaultsPANEL_TITLE _( "PageDefaultsPanel" )
#define SYMBOL_PageDefaultsPANEL_IDNAME ID_PAGEDEFAULTSDIALOG
#define SYMBOL_PageDefaultsPANEL_SIZE wxSize( -1, -1 )
#define SYMBOL_PageDefaultsPANEL_POSITION wxDefaultPosition


//--------------

class PageDefaultsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( PageDefaultsPanel )
    DECLARE_EVENT_TABLE( )

public:

    /*
    * Control identifiers
    */
    enum PageDefaultsPanelGuiDefs {
        //#define  10000
        ID_NOTEBOOKPOSITIONPANEL = ID_PAGEDEFAULTSDIALOG + 1,
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

    PageDefaultsPanel( );

    PageDefaultsPanel( wxWindow* parent, wxWindowID id = SYMBOL_PageDefaultsPANEL_IDNAME,
        const wxString& caption = SYMBOL_PageDefaultsPANEL_TITLE,
        const wxPoint& pos = SYMBOL_PageDefaultsPANEL_POSITION,
        const wxSize& size = SYMBOL_PageDefaultsPANEL_SIZE,
        long style = SYMBOL_PageDefaultsPANEL_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PageDefaultsPANEL_IDNAME, const wxString& caption = SYMBOL_PageDefaultsPANEL_TITLE, const wxPoint& pos = SYMBOL_PageDefaultsPANEL_POSITION, const wxSize& size = SYMBOL_PageDefaultsPANEL_SIZE, long style = SYMBOL_PageDefaultsPANEL_STYLE );

    ~PageDefaultsPanel( );

    void Init( );

    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( Design::Page* page );

    static bool ShowToolTips( );

    wxString GetBorderSize( );

    wxString GetBorderFilename( );

    wxString GetBottomPageMargin( );

    wxString GetLeftPageMargin( );

    wxString GetPageHeight( );

    wxString GetPageWidth( );

    wxString GetPaperHeight( );

    wxString GetPaperWidth( );

    wxString GetRightPageMargin( );

    wxColour GetTextColor( );

    bool GetOverSizePaper( );

    wxFont GetTextFont( );

    wxColour GetTitleColor( );

    wxColour GetSubTitleColor( );

    wxFont GetTitleFont( );

    wxFont GetSubTitleFont( );

    wxString GetTopPageMargin( );

    void OnOrientationchoiceSelected( wxCommandEvent& event );
    void OnOrientationChoice( wxCommandEvent& event );

    wxString GetOrientation( ) {
        return  m_orientationChoice->GetStringSelection( );
    };
    void SetOrientation( wxString sel ) {
        m_orientationChoice->SetStringSelection( sel );
    }

    void OnTitleCheckboxClick( wxCommandEvent& event );
    void OnSubTitleCheckboxClick( wxCommandEvent& event );


    void OnPageWidth( wxCommandEvent& event );

    void OnPageHeight( wxCommandEvent& event );

    void OnPaperWidth( wxCommandEvent& event );

    void OnPaperHeight( wxCommandEvent& event );


    void OnOverSizeCheckBoxClick( wxCommandEvent& event );

    void OnTopPageMargin( wxCommandEvent& event );

    void OnBottomPageMargin( wxCommandEvent& event );

    void OnLeftPageMargin( wxCommandEvent& event );

    void OnRightPageMargin( wxCommandEvent& event );

    void OnBorderFilename( wxCommandEvent& event );

    void OnBorderSize( wxCommandEvent& event );

    void OnTopContentMargin( wxCommandEvent& event );

    void OnBottomContentMargin( wxCommandEvent& event );

    void OnLeftContentMargin( wxCommandEvent& event );

    void OnRightContentMargin( wxCommandEvent& event );

    void SetBorderSize( wxString size );

    void SetBorderFilename( wxString filename );

    void SetBottomPageMargin( wxString pageMargin );

    void SetCatalog( wxString catCode );

    void SetLeftPageMargin( wxString pageMargin );

    void SetNameColor( wxColour color );

    void SetPageHeight( wxString height );

    void SetPageWidth( wxString width );

    void SetPaperWidth( wxString width );

    void SetPaperHeight( wxString height );

    void SetRightPageMargin( wxString pageMargin );

    void SetOverSizePaper( bool state );

    void SetTopPageMargin( wxString pageMargin );

    void SetTopContentMargin( wxString contentMargin );

    void SetBottomContentMargin( wxString contentMargin );

    void SetLeftContentMargin( wxString contentMargin );

    void SetRightContentMargin( wxString contentMargin );

private:
    wxTextCtrl* m_paperHeight;
    wxTextCtrl* m_paperWidth;
    wxTextCtrl* m_pageHeight;
    wxTextCtrl* m_pageWidth;
    wxTextCtrl* m_topPageMargin;
    wxTextCtrl* m_bottomPageMargin;
    wxTextCtrl* m_rightPageMargin;
    wxTextCtrl* m_leftPageMargin;
    wxTextCtrl* m_topContentMargin;
    wxTextCtrl* m_bottomContentMargin;
    wxTextCtrl* m_rightContentMargin;
    wxTextCtrl* m_leftContentMargin;
    wxTextCtrl* m_borderSize;
    wxTextCtrl* m_borderFilename;
    wxCheckBox* m_overSizeCheckbox;
    wxChoice* m_orientationChoice;
    TitleHelper* m_titleHelper;

    wxRadioButton* m_topButton;
    wxRadioButton* m_bottomButton;

};

#endif
// _PageDefaultsPANEL_H_
