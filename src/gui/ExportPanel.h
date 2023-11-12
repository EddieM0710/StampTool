/*
 * @file ExportPanel.h
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



#define SYMBOL_EXPORTPANEL_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX | wxTAB_TRAVERSAL
#define SYMBOL_EXPORTPANEL_TITLE _( "Export" )
#define SYMBOL_EXPORTPANEL_IDNAME ID_EXPORTPANEL
#define SYMBOL_EXPORTPANEL_SIZE wxSize( -1, -1 )
#define SYMBOL_EXPORTPANEL_POSITION wxDefaultPosition



 /*
  * ExportPanel class declaration
  */

class ExportPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( ExportPanel )
    DECLARE_EVENT_TABLE( )

public:
    enum ExportPanelGuiDefs {

        ID_NAMELABELEDTEXTBOX = ID_EXPORTPANEL,
        ID_EMISSIONALLBUTTON,
        ID_EMISSIONCLEARBUTTON,
        ID_LastID
    };



    ExportPanel( );
    ExportPanel( wxWindow* parent, wxWindowID id = SYMBOL_EXPORTPANEL_IDNAME, const wxString& caption = SYMBOL_EXPORTPANEL_TITLE, const wxPoint& pos = SYMBOL_EXPORTPANEL_POSITION, const wxSize& size = SYMBOL_EXPORTPANEL_SIZE, long style = SYMBOL_EXPORTPANEL_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_EXPORTPANEL_IDNAME, const wxString& caption = SYMBOL_EXPORTPANEL_TITLE, const wxPoint& pos = SYMBOL_EXPORTPANEL_POSITION, const wxSize& size = SYMBOL_EXPORTPANEL_SIZE, long style = SYMBOL_EXPORTPANEL_STYLE );

    ~ExportPanel( );

    void Init( );


    void CreateControls( );

    void OnCatalogAllButtonClick( wxCommandEvent& event );

    void OnCatalogClearButtonClick( wxCommandEvent& event );

    void OnIncludeInventoryButtonClick( wxCommandEvent& event );

    void OnEmissionAllButtonClick( wxCommandEvent& event );

    void OnEmissionClearButtonClick( wxCommandEvent& event );

    void UpdateControls( );

    void SetupDialog( Design::Row* row );

    // ExportPanel event handler declarations

    //   wxID_OK

private:

    wxCheckListBox* m_emissionListCtrl;
    wxArrayString m_emissionListCtrlStrings;

    wxCheckListBox* m_catalogListCtrl;
    wxArrayString m_catalogListCtrlStrings;

    wxCheckBox* m_inventorycheckBox;
};

#endif
// _EXPORTPANEL_H_
