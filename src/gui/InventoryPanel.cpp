/**
 * @file InventoryPanel.cpp
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "InventoryPanel.h"
#include "catalog/CatalogData.h"
#include "gui/CatalogTreeCtrl.h"
#include "collection/CollectionList.h"
#include "collection/Collection.h"
 //#include "Specimen.h"
#include "Defs.h"
#include "utils/Settings.h"

IMPLEMENT_DYNAMIC_CLASS( InventoryPanel, HelperPanel )


BEGIN_EVENT_TABLE( InventoryPanel, HelperPanel )

EVT_CONTEXT_MENU( InventoryPanel::OnContextMenu )
EVT_GRID_CELL_CHANGED( InventoryPanel::OnCellChanged )
EVT_MENU( ID_AddItem, InventoryPanel::OnContextPopup )
EVT_MENU( ID_DeleteItem, InventoryPanel::OnContextPopup )
EVT_MENU( ID_MoveItemUp, InventoryPanel::OnContextPopup )
EVT_MENU( ID_MoveItemDown, InventoryPanel::OnContextPopup )
EVT_MENU( ID_MoveItemTop, InventoryPanel::OnContextPopup )
EVT_MENU( ID_MoveItemBottom, InventoryPanel::OnContextPopup )
EVT_GRID_ROW_MOVE( InventoryPanel::OnRowBeginMove )
EVT_GRID_CELL_BEGIN_DRAG( InventoryPanel::OnRowBeginMove )
//EVT_BUTTON( ID_COLLECTIONALLBUTTON, InventoryPanel::OnCollectionAllButtonClick )
//EVT_BUTTON( ID_COLLECTIONCLEARBUTTON, InventoryPanel::OnCollectionClearButtonClick )

END_EVENT_TABLE( )

//-------

InventoryPanel::InventoryPanel( ) {
    Init( );
}

//-------

InventoryPanel::InventoryPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//-------

bool InventoryPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    // InventoryPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    // InventoryPanel creation
    m_grid->SetSelectionMode( m_grid->wxGridSelectRows );

    return true;
}

//-------

InventoryPanel::~InventoryPanel( )
{

}

//-------

int InventoryPanel::AddRow( wxXmlNode* ele )
{
    if ( ele )
    {
        int cnt = m_grid->GetNumberRows( );
        m_grid->InsertRows( cnt, 1 );
        m_specimenList.push_back( ele );
        InitRow( cnt );
        return cnt;
    }
    return -1;
}

//-------

wxXmlNode* InventoryPanel::AddNewInventoryItem( )
{
    wxXmlNode* ele = GetCatalogData( )->GetCurrentStamp( );
    if ( ele )
    {
        Catalog::Entry entry( ele );
        wxString currCollection = GetCollectionList( )->GetCurrentName( );
        wxXmlNode* newChild = entry.AddNewInventoryItem( currCollection, Catalog::ST_Missing );
        return newChild;
    }
    return ( wxXmlNode* ) 0;
}

//-------

void InventoryPanel::Clear( )
{
    m_grid->ClearGrid( );
    m_specimenList.clear( );;  ///< list containing each of the entries
}

//-------

void InventoryPanel::CreateControls( )
{

    InventoryPanel* itemPanel = this;

    wxBoxSizer* inventoryHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    itemPanel->SetSizer( inventoryHorizontalSizer );

    wxBoxSizer* leftSizer = new wxBoxSizer( wxVERTICAL );
    inventoryHorizontalSizer->Add( leftSizer, 1, wxGROW | wxALL, 5 );

    // wxBoxSizer* leftcollectionSizer = new wxBoxSizer( wxHORIZONTAL );
     //leftSizer->Add( leftcollectionSizer, 0, wxGROW | wxALL, 5 );


    int lastID = ID_Last;

    m_collectionListCtrl = SetupChoice( itemPanel, leftSizer, lastID, _( "Collection" ),
        GetCollectionList( )->GetNameArray( ), wxCommandEventHandler( InventoryPanel::OnCollectionChanged ) );

    m_collectionListCtrl->SetStringSelection( _( "Unknown" ) );


    m_description = SetupMultilineLabeledText( itemPanel, leftSizer, ++lastID, "Description", true, wxCommandEventHandler( InventoryPanel::OnDescriptionChanged ) );


    m_location = SetupMultilineLabeledText( itemPanel, leftSizer, ++lastID, "Location", true, wxCommandEventHandler( InventoryPanel::OnLocationChanged ) );


    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    inventoryHorizontalSizer->Add( itemBoxSizer2, 3, wxGROW | wxALL, 5 );

    m_grid = new wxGrid( itemPanel, ID_INVENTORYGRID, wxDefaultPosition, wxSize( 300, 100 ),
        wxHSCROLL | wxVSCROLL );
    m_grid->SetDefaultColSize( 100 );
    m_grid->SetDefaultRowSize( 25 );
    m_grid->SetColLabelSize( 25 );
    m_grid->SetRowLabelSize( 50 );
    m_grid->CreateGrid( 0, 5, wxGrid::wxGridSelectCells );
    m_grid->SetColSize( 4, 400 );
    itemBoxSizer2->Add( m_grid, 1, wxGROW | wxALL, 5 );

    // Connect events and objects
    //    m_grid->Connect( ID_INVENTORYGRID,  CONTEXT_MENU, 
    //    wxContextMenuEventHandler( InventoryPanel::OnContextMenu ), NULL, this );
    // InventoryPanel content construction
    for ( int i = 1; i < Catalog::IDT_NbrTypes; i++ )
    {
        m_grid->SetColLabelValue( i - 1, Catalog::ItemDataNames[ i ] );
    }
    wxString choices[ 5 ] = { wxT( "Mint" ), wxT( "MNH" ), wxT( "Unused" ), wxT( "Used" ), wxT( "OG" ) }; // Make table strings
    wxGridCellAttr* attr = new wxGridCellAttr( );
    attr->SetEditor( new wxGridCellChoiceEditor( 5, choices, true ) );
    m_grid->SetColAttr( Catalog::IDT_Type - 1, attr );

    wxString choices2[ 5 ] = { wxT( "VF" ), wxT( "F" ), wxT( "VG" ), wxT( "G" ),
        wxT( "P" ) }; // Make table strings
    attr = new wxGridCellAttr( );
    attr->SetEditor( new wxGridCellChoiceEditor( 5, choices2, true ) );
    m_grid->SetColAttr( Catalog::IDT_Condition - 1, attr );


    wxString choices4[ Catalog::ST_NbrInventoryStatusTypes ];
    for ( int i = 0; i < Catalog::ST_NbrInventoryStatusTypes; i++ )
    {
        choices4[ i ] = Catalog::InventoryStatusStrings[ i ];
    }

    attr = new wxGridCellAttr( );
    attr->SetEditor( new wxGridCellChoiceEditor( Catalog::ST_NbrInventoryStatusTypes, choices4, true ) );
    m_grid->SetColAttr( Catalog::IDT_InventoryStatus - 1, attr );

    Inventory::Collection* col = GetCollectionList( )->GetCurrentCollection( );
    SetCollectionListCtrl( col );

    SetDataEditable( GetSettings( )->IsCatalogVolumeEditable( ) );
    m_grid->EnableDragRowMove( );
    m_grid->Refresh( );
}

//-------

void InventoryPanel::Init( )
{
    m_grid = NULL;
}

//-------

void InventoryPanel::InitRow( int row )
{
    wxXmlNode* ele = m_specimenList[ row ];
    for ( int i = 1; i < Catalog::IDT_NbrTypes; i++ )
    {
        m_grid->SetCellValue( row, i - 1, "" );
    }
}

//-------

int InventoryPanel::MakeBitPatern( wxArrayInt& array )
{
    int nbr = array.Count( );
    int val = 0;
    for ( int i = 0; i < nbr; i++ )
    {
        int base = 1;
        base = base <<= array[ i ];
        val = val | base;
    }
    return val;
}

//--------------

void InventoryPanel::OnCellChanged( wxGridEvent& event )
{
    int col = event.GetCol( );
    int row = event.GetRow( );
    wxString str = m_grid->GetCellValue( row, col );
    wxXmlNode* ele = m_specimenList[ row ];
    Utils::SetAttrStr( ele, Catalog::ItemDataNames[ ( Catalog::ItemDataTypes ) col + 1 ], str );
    if ( col + 1 == Catalog::IDT_InventoryStatus )
    {
        GetCatalogTreeCtrl( )->SetInventoryStatusImage( );
    }
    event.Skip( );

}

//-------

void InventoryPanel::OnContextMenu( wxContextMenuEvent& event )
{
    if ( GetSettings( )->IsCatalogVolumeEditable( ) )
    {
        wxPoint point = event.GetPosition( );
        // If from keyboard
        if ( ( point.x == -1 ) && ( point.y == -1 ) )
        {
            wxSize size = GetSize( );
            point.x = size.x / 2;
            point.y = size.y / 2;
        }
        else
        {
            point = ScreenToClient( point );
        }
        wxMenu menu;
        wxGridCellCoords coords = m_grid->GetGridCursorCoords( );
        menu.Append( wxID_ANY, wxString::Format( "Menu1" ) );

        if ( m_grid->IsInSelection( coords ) )
        {

            wxMenu* moveMenu = new wxMenu( );
            moveMenu->Append( ID_MoveItemTop, "To Top" );
            moveMenu->Append( ID_MoveItemUp, "Up" );
            moveMenu->Append( ID_MoveItemDown, "Down" );
            moveMenu->Append( ID_MoveItemBottom, "To Bottom" );
            menu.Append( ID_Move, "Move", moveMenu );

        }
        menu.Append( ID_AddItem, "Add Item" );
        menu.Append( ID_DeleteItem, "Delete Item" );

        PopupMenu( &menu, point.x, point.y );
    }
    event.Skip( );

}

//-------

void InventoryPanel::OnContextPopup( wxCommandEvent& event )
{
    int id = event.GetId( );
    switch ( id )
    {
        case ID_AddItem:
        {
            AddRow( AddNewInventoryItem( ) );
            break;
        }
        case ID_DeleteItem:
        {
            break;
        }
        case ID_MoveItemUp:
        {
            wxArrayInt array = m_grid->GetSelectedRows( );
            m_grid->IsSelection( );
            int row = array[ 0 ];
            if ( row > 0 && row < m_specimenList.size( ) )
            {
                int prevRow = row - 1;
                wxXmlNode* node = m_specimenList[ row ];
                wxXmlNode* prevNode = m_specimenList[ prevRow ];
                wxXmlNode* parent = node->GetParent( );
                parent->RemoveChild( node );
                parent->InsertChild( node, prevNode );
                UpdateInventoryGrid( );
            }
            break;
        }
        case ID_MoveItemBottom:
        {
            wxArrayInt array = m_grid->GetSelectedRows( );
            m_grid->IsSelection( );
            int row = array[ 0 ];
            if ( row >= 0 && row < m_specimenList.size( ) - 1 )
            {
                int lastRow = m_specimenList.size( ) - 1;
                wxXmlNode* node = m_specimenList[ row ];
                wxXmlNode* lastNode = m_specimenList[ lastRow ];
                wxXmlNode* parent = node->GetParent( );
                parent->RemoveChild( node );
                parent->InsertChildAfter( node, lastNode );
                UpdateInventoryGrid( );
            }
            break;
        }
        case ID_MoveItemDown:
        {
            wxArrayInt array = m_grid->GetSelectedRows( );
            m_grid->IsSelection( );
            int row = array[ 0 ];
            if ( row >= 0 && row < m_specimenList.size( ) - 1 )
            {
                int nextRow = row + 1;
                wxXmlNode* node = m_specimenList[ row ];
                wxXmlNode* nextNode = m_specimenList[ nextRow ];
                wxXmlNode* parent = node->GetParent( );
                parent->RemoveChild( node );
                parent->InsertChildAfter( node, nextNode );
                UpdateInventoryGrid( );
            }
            break;
        }
        case ID_MoveItemTop:
        {
            wxArrayInt array = m_grid->GetSelectedRows( );
            m_grid->IsSelection( );
            int row = array[ 0 ];
            if ( row > 0 && row < m_specimenList.size( ) )
            {
                int firstRow = 0;
                wxXmlNode* node = m_specimenList[ row ];
                wxXmlNode* firstNode = m_specimenList[ firstRow ];
                wxXmlNode* parent = node->GetParent( );
                parent->RemoveChild( node );
                parent->InsertChild( node, firstNode );
                UpdateInventoryGrid( );
            }
            break;
        }
    }
}

//-------

void InventoryPanel::OnCollectionChanged( wxCommandEvent& event )
{

    wxString sel = m_collectionListCtrl->GetStringSelection( );
    //set the new selection
    GetCatalogData( )->SetCollection( sel );

    event.Skip( );

}

//-------

void InventoryPanel::OnDescriptionChanged( wxCommandEvent& event )
{
}

//-------

void InventoryPanel::OnLocationChanged( wxCommandEvent& event )
{
}

//-------

void InventoryPanel::OnRowBeginMove( wxGridEvent& ev )
{
    //  ev.GetRow( ), ev.GetCol( ) );
    int sel = ev.GetSelection( );
    int row = ev.GetRow( );
    int cursorRow = m_grid->GetGridCursorRow( );

    ev.Skip( );
}

//-------

void InventoryPanel::SetDataEditable( bool val )
{
    m_grid->EnableEditing( val );
}

//-------

void InventoryPanel::ShowRow( int row )
{
    wxXmlNode* ele = m_specimenList[ row ];
    for ( int i = 1; i < Catalog::IDT_NbrTypes; i++ )
    {
        wxString str = Utils::GetAttrStr( ele, Catalog::ItemDataNames[ ( Catalog::ItemDataTypes ) i ] );
        m_grid->SetCellValue( row, i - 1, str );
    }
}

//-------

bool InventoryPanel::SetCollectionListCtrl( Inventory::Collection* collection )
{
    bool status = m_collectionListCtrl->SetStringSelection( collection->GetName( ) );
    if ( status )
    {
        m_location->SetValue( collection->GetLocation( ) );
        m_description->SetValue( collection->GetDescription( ) );
    }
    return status;
}

//------

void InventoryPanel::UpdateCollectionChoice( )
{

}

//-------

void InventoryPanel::UpdateInventoryGrid( )
{
    int cnt = m_grid->GetNumberRows( );
    m_grid->ClearGrid( );
    if ( cnt > 0 )
        m_grid->DeleteRows( 0, cnt );
    m_specimenList.clear( );
    int row = 0;
    wxTreeItemId currID = GetCatalogData( )->GetCatalogTreeCtrl( )->GetSelection( );
    if ( currID.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetCatalogData( )->GetCatalogTreeCtrl( )->GetItemData( currID );

        if ( data->GetType( ) == Catalog::NT_Entry )
        {
            wxXmlNode* entryNode = data->GetNodeElement( );// GetCatalogData( )->GetCurrentStamp( );
            if ( entryNode )
            {
                Catalog::Entry entry( entryNode );
                if ( entry.HasInventoryItem( ) )
                {
                    wxString currCollection = GetCollectionList( )->GetCurrentName( );
                    wxXmlNode* ele = entry.GetInventory( )->GetChildren( );
                    while ( ele )
                    {
                        wxString str = Utils::GetAttrStr( ele, Catalog::ItemDataNames[ Catalog::IDT_Collection ] );
                        if ( !currCollection.Cmp( str ) )
                        {
                            AddRow( ele );
                            for ( int i = 1; i < Catalog::IDT_NbrTypes; i++ )
                            {
                                wxString str = Utils::GetAttrStr( ele, Catalog::ItemDataNames[ ( Catalog::ItemDataTypes ) i ] );
                                m_grid->SetCellValue( row, i - 1, str );
                            }
                            row++;
                        }
                        ele = ele->GetNext( );
                    }
                }
            }
            //       }
        }
    }
}

//-------

void InventoryPanel::UpdateInventory( )
{
    //set the new selection
    Inventory::Collection* col = GetCollectionList( )->GetCurrentCollection( );

    if ( SetCollectionListCtrl( col ) )
    {
        //update the inventory
        UpdateInventoryGrid( );
    }
}
//-------
