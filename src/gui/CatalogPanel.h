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

#ifndef _CATALOGVOLUMEPANEL_H_
#define _CATALOGVOLUMEPANEL_H_


 /*
  * Includes
  */

#include "wx/treectrl.h"
#include <wx/tglbtn.h>

#include "Defs.h"
#include "gui/GuiDefs.h"
#include "utils/Project.h"
#include "catalog/CatalogVolume.h"

  /*
  * Forward declarations
  */


class CatalogTreeCtrl;


class Stamp;

/*
* Control identifiers
*/



#define SYMBOL_CATALOGVOLUMEPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_CATALOGVOLUMEPANEL_TITLE _( "CatalogPanel" )
#define SYMBOL_CATALOGVOLUMEPANEL_IDNAME ID_CATALOGPANEL
#define SYMBOL_CATALOGVOLUMEPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_CATALOGVOLUMEPANEL_POSITION wxDefaultPosition



/*
* CatalogPanel class declaration
*/

class CatalogPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( CatalogPanel )
        DECLARE_EVENT_TABLE( )

public:

    enum CatalogPanelGuiDefs {
        ID_CATALOGVOLUMEPANEL = ID_CATALOGPANEL + 1,
        ID_TEXTCTRL,
        ID_TREECTRL,
        ID_NEXTBUTTON,
        ID_CHECKLISTBOX,
        ID_SEARCHSTRINGTEXTCTRL,
        ID_TOGGLEBUTTON,
        ID_VOLUMECHOICE,
        ID_MANAGEBUTTON,
        ID_NEWCATALOG,
        ID_OPENCATALOG,
        ID_REMOVECATALOG
    };

    CatalogPanel( );

    CatalogPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_CATALOGVOLUMEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_CATALOGVOLUMEPANEL_POSITION,
        const wxSize& size = SYMBOL_CATALOGVOLUMEPANEL_SIZE,
        long style = SYMBOL_CATALOGVOLUMEPANEL_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGVOLUMEPANEL_IDNAME, const wxPoint& pos = SYMBOL_CATALOGVOLUMEPANEL_POSITION, const wxSize& size = SYMBOL_CATALOGVOLUMEPANEL_SIZE, long style = SYMBOL_CATALOGVOLUMEPANEL_STYLE );

    ~CatalogPanel( );

    void Init( );

    void CreateControls( );

    void OnTextctrlTextUpdated( wxCommandEvent& event );

    void OnTogglebuttonClick( wxCommandEvent& event );

    void OnVolumeChoiceSelected( wxCommandEvent& event );

    void OnManageClick( wxCommandEvent& event );

    static bool ShowToolTips( );

    void InitCatalogVolume( );
    CatalogTreeCtrl* GetCatalogTree( ) { return m_catalogTreeCtrl; };

    void SetVolumeListStrings( wxArrayString& choices )
    {
        m_volumeListCtrl->Clear( );
        m_volumeListCtrl->Append( choices );
    };

    void SetVolumeListSelection( int i )
    {
        m_volumeListCtrl->SetSelection( i );
    };

    // wxTextCtrl* m_title;
    wxChoice* m_volumeListCtrl;
    CatalogTreeCtrl* m_catalogTreeCtrl;

    wxTreeItemId m_draggedItem;
    wxBoxSizer* m_searchSizer;
    wxBoxSizer* m_catPanelSizer;
    wxToggleButton* m_toggleButton;
    wxButton* m_manageButton;
};

#endif
// _CATALOGVOLUMEPANEL_H_
