/**
 * @file InventoryPanel.h
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
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
 *
 */


#ifndef _INVENTORY_H_
#define _INVENTORY_H_



#include <vector>
#include "wx/grid.h"
#include <wx/dataview.h>
#include <wx/dynarray.h>


#include "catalog/Entry.h"
#include "gui/GuiDefs.h"
#include "gui/HelperPanel.h"

class wxGrid;

namespace Inventory
{
    class Collection;
}

#define SYMBOL_INVENTORYPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_INVENTORYPANEL_TITLE _( "Inventory" )
#define SYMBOL_INVENTORYPANEL_IDNAME ID_INVENTORYPANEL
#define SYMBOL_INVENTORYPANEL_SIZE wxSize( 800, 200 )
#define SYMBOL_INVENTORYPANEL_POSITION wxDefaultPosition


#define ID_INVENTORYLISTCTRL ID_INVENTORYPANEL+2


class InventoryPanel : public HelperPanel
{
    DECLARE_DYNAMIC_CLASS( InventoryPanel )
    DECLARE_EVENT_TABLE( )

public:
    enum InventoryPanelGuiDefs
    {
        ID_INVENTORYGRID = ID_INVENTORYPANEL + 1,
        ID_COLLECTIONALLBUTTON,
        ID_COLLECTIONCLEARBUTTON,
        ID_COLLECTIONLISTBOX,
        ID_COLLECTIONCHOICE,
        ID_AddItem,
        ID_DeleteItem,
        ID_MoveItemUp,
        ID_MoveItemDown,
        ID_MoveItemTop,
        ID_MoveItemBottom,
        ID_Move,
        ID_Last
    };

    InventoryPanel( );

    InventoryPanel( wxWindow* parent,
        wxWindowID id = SYMBOL_INVENTORYPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_INVENTORYPANEL_POSITION,
        const wxSize& size = SYMBOL_INVENTORYPANEL_SIZE,
        long style = SYMBOL_INVENTORYPANEL_STYLE );


    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_INVENTORYPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_INVENTORYPANEL_POSITION,
        const wxSize& size = SYMBOL_INVENTORYPANEL_SIZE,
        long style = SYMBOL_INVENTORYPANEL_STYLE );

    ~InventoryPanel( );

    int AddRow( wxXmlNode* ele );

    wxXmlNode* AddNewInventoryItem( );

    void Clear( );

    void CreateControls( );

    int GetCheckedCollectionItems( );

    void Init( );

    void InitRow( int row );

    static bool ShowToolTips( );

    int MakeBitPatern( wxArrayInt& array );

    void OnCellChanged( wxGridEvent& event );

    void OnCollectionChanged( wxCommandEvent& event );

    void OnContextPopup( wxCommandEvent& event );

    void OnContextMenu( wxContextMenuEvent& event );

    void OnDescriptionChanged( wxCommandEvent& event );

    void OnLocationChanged( wxCommandEvent& event );

    void OnRowBeginMove( wxGridEvent& ev );

    void SetDataEditable( bool val );

    bool SetCollectionListCtrl( Inventory::Collection* collection );

    void ShowRow( int row );

    void UpdateCollectionChoice( );

    void UpdateInventory( );

    void UpdateInventoryGrid( );

private:

    wxGrid* m_grid;  ///< wxGrid to display item entries
    wxChoice* m_collectionListCtrl;
    std::vector<wxXmlNode*> m_specimenList;  ///< list containing each of the entries
    wxTextCtrl* m_description;
    wxTextCtrl* m_location;
    // wxRadioBox* m_collectionChoice;
};

#endif
// _INVENTORY_H_
