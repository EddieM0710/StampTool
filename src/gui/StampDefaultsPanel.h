/*
 * @file         StampDefaultsPanel.h
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

#ifndef _StampDefaultsPanel_H_
#define _StampDefaultsPanel_H_


/*
 * Includes
 */

#include "wx/listctrl.h"

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


#define SYMBOL_StampDefaultsPanel_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_StampDefaultsPanel_TITLE _( "StampDefaultsPanel" )
#define SYMBOL_StampDefaultsPanel_IDNAME ID_STAMPDEFAULTSDIALOG
#define SYMBOL_StampDefaultsPanel_SIZE wxSize( -1, -1 )
#define SYMBOL_StampDefaultsPanel_POSITION wxDefaultPosition


/*
 * StampDefaultsPanel class declaration
 */

class StampDefaultsPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( StampDefaultsPanel )
    DECLARE_EVENT_TABLE( )

public:

    /*
    * Control identifiers
    */
    enum StampDefaultsPanelGuiDefs {
        //#define  10000
        ID_NOTEBOOKPOSITIONPANEL = ID_STAMPDEFAULTSDIALOG + 1,
        ID_LastID
    };




    StampDefaultsPanel( );
    StampDefaultsPanel( wxWindow* parent, wxWindowID id = SYMBOL_StampDefaultsPanel_IDNAME, const wxString& caption = SYMBOL_StampDefaultsPanel_TITLE, const wxPoint& pos = SYMBOL_StampDefaultsPanel_POSITION, const wxSize& size = SYMBOL_StampDefaultsPanel_SIZE, long style = SYMBOL_StampDefaultsPanel_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_StampDefaultsPanel_IDNAME, const wxString& caption = SYMBOL_StampDefaultsPanel_TITLE, const wxPoint& pos = SYMBOL_StampDefaultsPanel_POSITION, const wxSize& size = SYMBOL_StampDefaultsPanel_SIZE, long style = SYMBOL_StampDefaultsPanel_STYLE );


    ~StampDefaultsPanel( );


    void Init( );

    void CreateControls( );

    wxString GetCatalog( );


    bool GetGrayScaleImages( );

    wxString GetName( );

    bool GetShowNbr( );

    bool GetShowStampTitle( );

    bool GetShowStampSubTitle( );


    void OnNameDefaultClick( wxCommandEvent& event );

    void OnNameClick( wxCommandEvent& event );


    void OnNbrDefaultClick( wxCommandEvent& event );


    void OnNameLocationButtonSelected( wxCommandEvent& event );

    void OnAlignmentButtonSelected( wxCommandEvent& event );

    void OnTopContentMargin( wxCommandEvent& event );

    void OnBottomContentMargin( wxCommandEvent& event );

    void OnLeftContentMargin( wxCommandEvent& event );

    void OnRightContentMargin( wxCommandEvent& event );

    void OnStampMargin( wxCommandEvent& event );

    void OnCatalogCode( wxCommandEvent& event );

    void OnGrayscale( wxCommandEvent& event );

    void OnShowNbr( wxCommandEvent& event );

    void OnShowName( wxCommandEvent& event );

    void OnShowImages( wxCommandEvent& event );

    void OnTextDefaultClick( wxCommandEvent& event );

    void OnSelvageHeight( wxCommandEvent& event );

    void OnSelvageWidth( wxCommandEvent& event );

    void OnMountAllowanceHeight( wxCommandEvent& event );

    void OnMountAllowanceWidth( wxCommandEvent& event );


    Design::StampNamePosType GetDefaultStampNamePosition( )
    {
        return m_StampNamePosition;
    }

    void UpdateControls( );

    void SetupDialog( Design::Page* page );


    static bool ShowToolTips( );


    void SetAlignmentMode( );

    void SetShowStampTitle( bool state );

    void SetStampNamePosition( Design::StampNamePosType type );

    void SetGrayScaleImages( bool val );
    // bool GetGrayScaleImages( );

    void SetCatalog( wxString catCode );

    void SetName( wxString name );

    void SetTopContentMargin( wxString contentMargin );

    void SetBottomContentMargin( wxString contentMargin );

    void SetLeftContentMargin( wxString contentMargin );

    void SetRightContentMargin( wxString contentMargin );

    void SetShowNbr( bool state );

    void SetSelvageHeight( wxString selvageHeight );

    void SetSelvageWidth( wxString selvageWidth );

    void SetMountAllowanceHeight( wxString mountAllowanceHeight );

    void SetMountAllowanceWidth( wxString mountAllowanceWidth );

    void SetStampMargin( wxString m_StampMargin );

    void Update( );


private:

    wxCheckBox* m_nbrCheckbox;
    wxCheckBox* m_stampTitleCheckbox;
    wxCheckBox* m_stampSubTitleCheckbox;
    wxCheckBox* m_ImagesCheckbox;
    wxCheckBox* m_grayScaleImagesCheckbox;

    wxRadioButton* m_topButton;
    wxRadioButton* m_bottomButton;

    wxTextCtrl* m_selvageHeight;
    wxTextCtrl* m_selvageWidth;
    wxTextCtrl* m_mountAllowanceHeight;
    wxTextCtrl* m_mountAllowanceWidth;
    wxTextCtrl* m_StampMargin;
    wxTextCtrl* m_topContentMargin;
    wxTextCtrl* m_bottomContentMargin;
    wxTextCtrl* m_rightContentMargin;
    wxTextCtrl* m_leftContentMargin;


    Design::StampNamePosType m_StampNamePosition;

    Design::AlignmentModeType m_alignmentMode;
    wxRadioButton* m_alignTop;
    wxRadioButton* m_alignMiddle;
    wxRadioButton* m_alignBottom;
    wxTextCtrl* m_catalog;
};

#endif
// _StampDefaultsPanel_H_
