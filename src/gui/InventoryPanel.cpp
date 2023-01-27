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
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "InventoryPanel.h"
#include "Specimen.h"
#include "Defs.h"
#include "utils/Settings.h"
/*
 * InventoryPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( InventoryPanel, wxPanel )
; // silly business; The above macro screws up the formatter

#define wxIDAddItem 17000
#define wxIDDeleteItem 17001
/*
 * InventoryPanel event table definition
 */

BEGIN_EVENT_TABLE( InventoryPanel, wxPanel )

// InventoryPanel event table entries
EVT_CONTEXT_MENU( InventoryPanel::OnContextMenu )
EVT_GRID_CELL_CHANGED( InventoryPanel::OnCellChanged )
// InventoryPanel event table entries
EVT_MENU( wxIDAddItem, InventoryPanel::OnContextPopup )
EVT_MENU( wxIDDeleteItem, InventoryPanel::OnContextPopup )

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter


/*
 *
 * InventoryPanel constructors
 *
 **************************************************/

InventoryPanel::InventoryPanel( ) { Init( ); }

/*
 *
 * InventoryPanel constructors
 *
 **************************************************/

InventoryPanel::InventoryPanel( wxWindow* parent, wxWindowID id, 
    const wxPoint& pos, const wxSize& size, 
    long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 *
 * Inventory creator
 *
 **************************************************/

bool InventoryPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, 
    const wxSize& size, long style )
{ 
    // InventoryPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    // InventoryPanel creation
    return true;
}

/*
 *
 * InventoryPanel destructor
 *
 **************************************************/

InventoryPanel::~InventoryPanel( )
{ 

}

/*
 *
 * * Member initialisation
 *
 **************************************************/

void InventoryPanel::Init( )
{ 
    // InventoryPanel member initialisation
    m_grid = NULL;
    // InventoryPanel member initialisation
}

/*
 *
 * Control creation for Inventory
 *
 **************************************************/

void InventoryPanel::CreateControls( )
{ 
    // InventoryPanel content construction

    InventoryPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer2, 1, wxGROW | wxALL, 5 );

    m_grid = new wxGrid( itemPanel1, ID_INVENTORYGRID, wxDefaultPosition, wxSize( 200, 150 ), 
        wxHSCROLL | wxVSCROLL );
    m_grid->SetDefaultColSize( 100 );
    m_grid->SetDefaultRowSize( 25 );
    m_grid->SetColLabelSize( 25 );
    m_grid->SetRowLabelSize( 50 );
    m_grid->CreateGrid( 0, 5, wxGrid::wxGridSelectCells );
    itemBoxSizer2->Add( m_grid, 1, wxGROW | wxALL, 5 );

    // Connect events and objects
    //    m_grid->Connect( ID_INVENTORYGRID, wxEVT_CONTEXT_MENU, 
    //    wxContextMenuEventHandler( InventoryPanel::OnContextMenu ), NULL, this );
    // InventoryPanel content construction
    for ( int i = 0; i < Catalog::IDT_NbrTypes; i++ )
    { 
        m_grid->SetColLabelValue( i, Catalog::ItemDataNames[ i ] );
    }
    wxString choices[ 5 ] = { wxT( "Mint" ), wxT( "MNH" ), wxT( "Unused" ), wxT( "Used" ), 
                           wxT( "OG" ) }; // Make table strings
    wxGridCellAttr* attr = new wxGridCellAttr( );
    attr->SetEditor( new wxGridCellChoiceEditor( 5, choices, true ) );
    m_grid->SetColAttr( Catalog::IDT_Type, attr );

    wxString choices2[ 5 ] = { wxT( "VF" ), wxT( "F" ), wxT( "VG" ), wxT( "G" ), 
                            wxT( "P" ) }; // Make table strings
    attr = new wxGridCellAttr( );
    attr->SetEditor( new wxGridCellChoiceEditor( 5, choices2, true ) );
    m_grid->SetColAttr( Catalog::IDT_Condition, attr );

    wxString choices3[ 3 ] = { wxT( "Album" ), wxT( "Stock Book" ), 
                            wxT( "File Box" ) }; // Make table strings
    attr = new wxGridCellAttr( );
    attr->SetEditor( new wxGridCellChoiceEditor( 3, choices3, true ) );
    m_grid->SetColAttr( Catalog::IDT_Location, attr );

    SetDataEditable( GetSettings( )->IsCatalogSectionDataEditable( ) );

    m_grid->Refresh( );

}

/*
 *
 * InitRow
 *
 **************************************************/

void InventoryPanel::InitRow( int row )
{ 
    wxXmlNode* ele = m_specimenList[ row ];
    Catalog::Specimen specimen( ele );
    for ( int i = 0; i < Catalog::IDT_NbrTypes; i++ )
    { 
        specimen.SetAttr( ( Catalog::ItemDataTypes )i, "" );
        m_grid->SetCellValue( row, i, "" );
    }
}
/*
 *
 * AddRow
 *
 **************************************************/

int InventoryPanel::AddRow( )
{ 
    if ( m_stamp )
    { 
        int cnt = m_grid->GetNumberRows( );
        m_grid->InsertRows( cnt, 1 );

        wxXmlNode* ele = m_stamp->AddSpecimen( );
        m_specimenList.push_back( ele );
        InitRow( cnt );
        return cnt;
    }
    return -1;
}
/*
 *
 * ShowRow
 *
 **************************************************/

void InventoryPanel::ShowRow( int row )
{ 
    wxXmlNode* ele = m_specimenList[ row ];
    Catalog::Specimen specimen( ele );
    for ( int i = 0; i < Catalog::IDT_NbrTypes; i++ )
    { 
        wxString str = specimen.GetAttr( ( Catalog::ItemDataTypes )i );
        m_grid->SetCellValue( row, i, str );
    }
}

/*
 *
 * Should we show tooltips?
 *
 **************************************************/

bool InventoryPanel::ShowToolTips( )
{ 
    return true;
}

/*
 *
 * Get bitmap resources
 *
 **************************************************/

wxBitmap InventoryPanel::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
    // InventoryPanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // InventoryPanel bitmap retrieval
}

/*
 *
 * Get icon resources
 *
 **************************************************/

wxIcon InventoryPanel::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
    // InventoryPanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // InventoryPanel icon retrieval
}

/*
 *
 *SetStamp
 *
 **************************************************/

void InventoryPanel::SetStamp( Catalog::Entry* stamp )
{ 
    m_stamp = stamp;
    ShowStamp( );
}

/*
 * ShowStamp
 *
 **************************************************/

void InventoryPanel::ShowStamp( )
{ 
    int cnt = m_grid->GetNumberRows( );
    m_grid->ClearGrid( );
    if ( cnt > 0 )
        m_grid->DeleteRows( 0, cnt );
    m_specimenList.clear( );
    cnt = m_grid->GetNumberRows( );
    int size = m_specimenList.size( );
    int row = 0;
    if ( m_stamp && m_stamp->IsOK( ) )
    { 
        if ( m_stamp->HasChildSpecimen( ) )
        { 
            wxXmlNode* ele = m_stamp->GetFirstChildSpecimen( );
            while ( ele )
            { 
                AddRow( );
                m_specimenList.push_back( ele );
                Catalog::Specimen specimen( ele );
                for ( int i = 0; i < Catalog::IDT_NbrTypes; i++ )
                { 
                    wxString str = specimen.GetAttr( ( Catalog::ItemDataTypes )i );
                    m_grid->SetCellValue( row, i, str );
                }
                ele = m_stamp->GetNextChildSpecimen( );
            }
        }
    }
}

/*
 * wxEVT_CONTEXT_MENU event handler for ID_INVENTORYLISTCTRL
 *
 **************************************************/

void InventoryPanel::OnContextMenu( wxContextMenuEvent& event )
{ 

    if ( GetSettings( )->IsCatalogSectionDataEditable( ) )
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
        menu.Append( wxID_ANY, wxString::Format( "Menu1" ) );
        menu.Append( wxIDAddItem, "Add Item" );
        menu.Append( wxIDDeleteItem, "Delete Item" );

        PopupMenu( &menu, point.x, point.y );
    }
    // wxEVT_CONTEXT_MENU event handler for ID_INVENTORYLISTCTRL in
    // InventoryPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_CONTEXT_MENU event handler for ID_INVENTORYLISTCTRL in InventoryPanel.
}

/*
 * wxEVT_GRID_CELL_CHANGED event handler for ID_INVENTORYGRID
 *
 **************************************************/

void InventoryPanel::OnCellChanged( wxGridEvent& event )
{ 
    int col = event.GetCol( );
    int row = event.GetRow( );
    wxString str = m_grid->GetCellValue( row, col );
    wxXmlNode* ele = m_specimenList[ row ];
    Catalog::Specimen specimen( ele );
    specimen.SetAttr( ( Catalog::ItemDataTypes )col, str );

    // wxEVT_GRID_CELL_CHANGED event handler for ID_INVENTORYGRID in
    // InventoryPanel.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_GRID_CELL_CHANGED event handler for ID_INVENTORYGRID in
    // InventoryPanel.
}

/*
 *
 * OnContextPopup( wxCommandEvent& event )
 *
 **************************************************/

void InventoryPanel::OnContextPopup( wxCommandEvent& event )
{ 
    int id = event.GetId( );
    switch ( id )
    { 
    case wxIDAddItem:
    { 
        AddRow( );
        break;
    }
    case wxIDDeleteItem:
    { 
        break;
    }
    }
}

void InventoryPanel::SetDataEditable( bool val )
{ 
    m_grid->EnableEditing( val );
}