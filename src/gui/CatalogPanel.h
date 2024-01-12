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

#include "wx/treectrl.h"
#include <wx/tglbtn.h>
#include <wx/choice.h>
#include <wx/sizer.h>

#include "Defs.h"
#include "gui/GuiDefs.h"
#include "utils/Project.h"
#include "catalog/CatalogVolume.h"
#include "wx/spinbutt.h"
#include "wx/notebook.h"

class CatalogTreeCtrl;
class CatalogTOCTreeCtrl;
class Stamp;

#define SYMBOL_CATALOGVOLUMEPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_CATALOGVOLUMEPANEL_TITLE _( "CatalogPanel" )
#define SYMBOL_CATALOGVOLUMEPANEL_IDNAME ID_CATALOGPANEL
#define SYMBOL_CATALOGVOLUMEPANEL_SIZE wxSize( 400, 300 )
#define SYMBOL_CATALOGVOLUMEPANEL_POSITION wxDefaultPosition

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
        ID_COLLECTIONCHOICE,
        ID_VOLUMECHOICE,
        ID_MANAGEBUTTON,
        ID_CSVIMPORTCATALOG,
        ID_NEWCATALOG,
        ID_OPENCATALOG,
        ID_REMOVECATALOG,
        ID_SPINBUTTON
    };


    CatalogPanel( );


    CatalogPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_CATALOGVOLUMEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_CATALOGVOLUMEPANEL_POSITION,
        const wxSize& size = SYMBOL_CATALOGVOLUMEPANEL_SIZE,
        long style = SYMBOL_CATALOGVOLUMEPANEL_STYLE );


    ~CatalogPanel( );

    void Clear( );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGVOLUMEPANEL_IDNAME, const wxPoint& pos = SYMBOL_CATALOGVOLUMEPANEL_POSITION, const wxSize& size = SYMBOL_CATALOGVOLUMEPANEL_SIZE, long style = SYMBOL_CATALOGVOLUMEPANEL_STYLE );

    void CreateControls( );

    void DoCSVImport( );

    void DoMergeCatalog( );

    CatalogTreeCtrl* GetCatalogTree( ) {
        return m_catalogTreeCtrl;
    };

    wxTextCtrl* GetVolumeListCtrl( ) {
        return m_volumeListCtrl;
    };

    wxTreeItemId GetNext( wxTreeItemId& currID );

    wxTreeItemId GetNextFirstChild( wxTreeItemId& currID );


    wxTreeItemId GetPrev( wxTreeItemId& currID );

    wxTreeItemId GetPrevLastChild( wxTreeItemId& currID );

    CatalogTOCTreeCtrl* GetTOCTree( ) {
        return m_tocTreeCtrl;
    };

    void Init( );

    void NewCatalogDialog( );

    //void OnCollectionChoiceSelected( wxCommandEvent& event );

    void OnCSVImportClick( wxCommandEvent& event );

    void OnManageClick( wxCommandEvent& event );

    void DoMergeCatalog( wxCommandEvent& event );

    void OnContextMenu( wxContextMenuEvent& event );

    void OnSpinbuttonUpdated( wxSpinEvent& event );

    void OnSpinbuttonUp( wxSpinEvent& event );

    void OnSpinbuttonDown( wxSpinEvent& event );

    void OnTextctrlTextUpdated( wxCommandEvent& event );

    void OnTogglebuttonClick( wxCommandEvent& event );

    void OnVolumeChoiceSelected( wxCommandEvent& event );

    void OpenCatalog( );

    void RemoveVolume( );

    void SaveAsCatalog( );

    // void SetCollectionListSelection( );

    void SetNotebookPage( int i ){
        m_catalogPanelNotebook->SetSelection( i );
    };

    void SetVolumeListStrings( wxArrayString& choices )
    {
        // m_volumeListCtrl->Clear( );
        // m_volumeListCtrl->Append( choices );
    };

    void SetVolumeListSelection( int i )
    {
        //       m_volumeListCtrl->SetSelection( i );
    };

    void SetVolumeListSelection( wxString str )
    {
        //       m_volumeListCtrl->SetStringSelection( str );
    };

    void SetVolumeListCtrl( );

    static bool ShowToolTips( );

private:
    wxTextCtrl* m_volumeListCtrl;

    wxSpinButton* m_spinButton;
    //wxChoice* m_collectionListCtrl;
    CatalogTreeCtrl* m_catalogTreeCtrl;
    CatalogTOCTreeCtrl* m_tocTreeCtrl;
    wxTreeItemId m_draggedItem;
    wxBoxSizer* m_searchSizer;
    wxBoxSizer* m_catPanelSizer;
    wxToggleButton* m_toggleButton;
    wxButton* m_manageButton;


    wxNotebook* m_catalogPanelNotebook;

};

#endif
