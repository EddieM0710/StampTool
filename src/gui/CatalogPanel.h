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

class CatalogTreeCtrl;

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
        ID_REMOVECATALOG
    };

    ///  @brief Construct a new Catalog Panel object
    ///  
    CatalogPanel( );

    ///  @brief Construct a new Catalog Panel object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    CatalogPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_CATALOGVOLUMEPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_CATALOGVOLUMEPANEL_POSITION,
        const wxSize& size = SYMBOL_CATALOGVOLUMEPANEL_SIZE,
        long style = SYMBOL_CATALOGVOLUMEPANEL_STYLE );

    ///  @brief Destroy the Catalog Panel object
    ///  
    ~CatalogPanel( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    ///  @return true 
    ///  @return false 
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CATALOGVOLUMEPANEL_IDNAME, const wxPoint& pos = SYMBOL_CATALOGVOLUMEPANEL_POSITION, const wxSize& size = SYMBOL_CATALOGVOLUMEPANEL_SIZE, long style = SYMBOL_CATALOGVOLUMEPANEL_STYLE );

    ///  @brief Create a Controls object
    ///  
    void CreateControls( );

    ///  @brief Get the Catalog Tree object
    ///  
    ///  @return CatalogTreeCtrl* 
    CatalogTreeCtrl* GetCatalogTree( ) { return m_catalogTreeCtrl; };

    ///  @brief 
    ///  
    void Init( );

    void DoCSVImport( );

    ///  @brief 
    ///  
    void InitCatalogVolume( );

    void NewCatalogDialog( );

    void OnCSVImportClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnTextctrlTextUpdated( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnTogglebuttonClick( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnVolumeChoiceSelected( wxCommandEvent& event );

    void OnCollectionChoiceSelected( wxCommandEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnManageClick( wxCommandEvent& event );

    ///  @brief Set the Volume List Strings object
    ///  
    ///  @param choices 
    void SetVolumeListStrings( wxArrayString& choices )
    {
        m_volumeListCtrl->Clear( );
        m_volumeListCtrl->Append( choices );
    };

    ///  @brief Set the Volume List Selection object
    ///  
    ///  @param i 
    void SetVolumeListSelection( int i )
    {
        m_volumeListCtrl->SetSelection( i );
    };

    void SetVolumeListSelection( wxString str )
    {
        m_volumeListCtrl->SetStringSelection( str );
    };

    ///  @brief Set the Volume List Strings object
    ///  
    ///  @param choices 
    void SetCollectionListStrings( );

    ///  @brief Set the Volume List Selection object
    ///  
    ///  @param i 
    void SetCollectionListSelection( );

    void OpenCatalog( );

    void RemoveVolume( );

    void SaveAsCatalog( );



    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    static bool ShowToolTips( );
    ;
private:
    wxChoice* m_volumeListCtrl;
    wxChoice* m_collectionListCtrl;
    CatalogTreeCtrl* m_catalogTreeCtrl;

    wxTreeItemId m_draggedItem;
    wxBoxSizer* m_searchSizer;
    wxBoxSizer* m_catPanelSizer;
    wxToggleButton* m_toggleButton;
    wxButton* m_manageButton;
};

#endif
