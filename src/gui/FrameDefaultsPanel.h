/*
 * @file         FrameDefaultsPanel.h
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

#ifndef _FrameDefaultsPanel_H_
#define _FrameDefaultsPanel_H_


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


#define SYMBOL_FrameDefaultsPanel_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_FrameDefaultsPanel_TITLE _( "FrameDefaultsPanel" )
#define SYMBOL_FrameDefaultsPanel_IDNAME ID_FRAMEDEFAULTSDIALOG
#define SYMBOL_FrameDefaultsPanel_SIZE wxSize( -1, -1 )
#define SYMBOL_FrameDefaultsPanel_POSITION wxDefaultPosition


/*
 * FrameDefaultsPanel class declaration
 */

class FrameDefaultsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( FrameDefaultsPanel )
    DECLARE_EVENT_TABLE( )

public:

    /*
    * Control identifiers
    */
    enum FrameDefaultsPanelGuiDefs {
        //#define  10000
        ID_NOTEBOOKPOSITIONPANEL = ID_FRAMEDEFAULTSDIALOG + 1,
        ID_LastID
    };




    FrameDefaultsPanel( );
    FrameDefaultsPanel( wxWindow* parent, wxWindowID id = SYMBOL_FrameDefaultsPanel_IDNAME, const wxString& caption = SYMBOL_FrameDefaultsPanel_TITLE, const wxPoint& pos = SYMBOL_FrameDefaultsPanel_POSITION, const wxSize& size = SYMBOL_FrameDefaultsPanel_SIZE, long style = SYMBOL_FrameDefaultsPanel_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FrameDefaultsPanel_IDNAME, const wxString& caption = SYMBOL_FrameDefaultsPanel_TITLE, const wxPoint& pos = SYMBOL_FrameDefaultsPanel_POSITION, const wxSize& size = SYMBOL_FrameDefaultsPanel_SIZE, long style = SYMBOL_FrameDefaultsPanel_STYLE );

    ~FrameDefaultsPanel( );

    void Init( );

    void CreateControls( );

    void UpdateControls( );

    void SetupDialog( Design::Page* page );

    static bool ShowToolTips( );

    void OnTitleCheckboxClick( wxCommandEvent& event );

    void OnSubTitleCheckboxClick( wxCommandEvent& event );

    void OnNameLocationButtonSelected( wxCommandEvent& event );

    void OnAlignmentButtonSelected( wxCommandEvent& event );

    void OnTopContentMargin( wxCommandEvent& event );

    void OnBottomContentMargin( wxCommandEvent& event );

    void OnLeftContentMargin( wxCommandEvent& event );

    void OnRightContentMargin( wxCommandEvent& event );

    void OnFrameCheckboxClick( wxCommandEvent& event );

    void SetFixedSpacing( );

    void SetFixedSpacingSize( wxString str ) {
        m_fixedSpaceSize->ChangeValue( str );
    };

    wxString GetFixedSpacingSize( ) {
        return m_fixedSpaceSize->GetValue( );
    };


    void OnCalculatedClick( wxCommandEvent& event );

    void OnFixedClick( wxCommandEvent& event );

    void SetAlignmentMode( );

    void OnAlignmentModeButtonSelected( wxCommandEvent& event );

    void SetTopContentMargin( wxString contentMargin );

    void SetBottomContentMargin( wxString contentMargin );

    void SetLeftContentMargin( wxString contentMargin );

    void SetRightContentMargin( wxString contentMargin );

    void Update( );




private:


    wxRadioButton* m_topButton;
    wxRadioButton* m_bottomButton;
    wxCheckBox* m_frameCheckbox;
    TitleHelper* m_titleHelper;
    wxTextCtrl* m_topContentMargin;
    wxTextCtrl* m_bottomContentMargin;
    wxTextCtrl* m_rightContentMargin;
    wxTextCtrl* m_leftContentMargin;

    wxRadioButton* m_alignTopButton;
    wxRadioButton* m_alignMiddleButton;
    wxRadioButton* m_alignBottomButton;
    wxCheckBox* m_fixedSpacingCheckbox;

    wxTextCtrl* m_fixedSpaceSize;

};

#endif
// _FrameDefaultsPanel_H_
