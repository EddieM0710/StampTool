/*
 * @file src/gui/CatalogPanel.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-22
 *
 * @copyright Copyright ( c ) 2021
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

#ifndef _CATALOGSECTIONDATAPANEL_H_
#define _CATALOGSECTIONDATAPANEL_H_


 /*
  * Includes
  */

#include "wx/treectrl.h"
#include <wx/tglbtn.h>

#include "Defs.h"
#include "gui/GuiDefs.h"
#include "utils/Project.h"
#include "catalog/CatalogSectionData.h"

  /*
  * Forward declarations
  */


class CatalogTreeCtrl;


class Stamp;

/*
* Control identifiers
*/



#define SYMBOL_CATALOGSECTIONDATAPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_CATALOGSECTIONDATAPANEL_TITLE _( "CatalogPanel" )
#define SYMBOL_CATALOGSECTIONDATAPANEL_IDNAME ID_CATALOGPANEL
#define SYMBOL_CATALOGSECTIONDATAPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_CATALOGSECTIONDATAPANEL_POSITION wxDefaultPosition



/*
* CatalogPanel class declaration
*/

class CatalogPanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( CatalogPanel )
        DECLARE_EVENT_TABLE( )

public:

    enum CatalogPanelGuiDefs {
        ID_CATALOGSECTIONDATAPANEL = ID_CATALOGPANEL + 1,
        ID_TEXTCTRL,
        ID_TREECTRL,
        ID_NEXTBUTTON,
        ID_CHECKLISTBOX,
        ID_SEARCHSTRINGTEXTCTRL,
        ID_TOGGLEBUTTON,
        ID_SECTIONCHOICE
    };

    CatalogPanel( );

    CatalogPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_CATALOGSECTIONDATAPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_CATALOGSECTIONDATAPANEL_POSITION,
        const wxSize& size = SYMBOL_CATALOGSECTIONDATAPANEL_SIZE,
        long style = SYMBOL_CATALOGSECTIONDATAPANEL_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGSECTIONDATAPANEL_IDNAME, const wxPoint& pos = SYMBOL_CATALOGSECTIONDATAPANEL_POSITION, const wxSize& size = SYMBOL_CATALOGSECTIONDATAPANEL_SIZE, long style = SYMBOL_CATALOGSECTIONDATAPANEL_STYLE );

    ~CatalogPanel( );

    void Init( );

    void CreateControls( );

    void OnTextctrlTextUpdated( wxCommandEvent& event );

    void OnTogglebuttonClick( wxCommandEvent& event );

    void OnSectionChoiceSelected( wxCommandEvent& event );

    static bool ShowToolTips( );

    void InitCatalogSectionData( );
    CatalogTreeCtrl* GetCatalogTree( ) { return m_catalogTreeCtrl; };

    void SetSectionListStrings( wxArrayString& choices )
    {
        m_sectionListCtrl->Clear( );
        m_sectionListCtrl->Append( choices );
    };

    void SetSectionListSelection( int i )
    {
        m_sectionListCtrl->SetSelection( i );
    };

    // wxTextCtrl* m_title;
    wxChoice* m_sectionListCtrl;
    CatalogTreeCtrl* m_catalogTreeCtrl;

    wxTreeItemId m_draggedItem;
    wxBoxSizer* m_searchSizer;
    wxBoxSizer* m_catPanelSizer;
    wxToggleButton* m_toggleButton;
};

#endif
// _CATALOGSECTIONDATAPANEL_H_
