/**
 * @file CatalogCodePanel.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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

#include "CatalogCodePanel.h"
#include "CatalogCode.h"
#include "catalog/CatalogDefs.h"
#include "XMLUtilities.h"
#include "Defs.h"
#include "utils/Settings.h"

/*
 * CatalogCodePanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CatalogCodePanel, wxPanel )
; // silly business; The above macro screws up the formatter

#define wxIDAddItem 17000
#define wxIDDeleteItem 17001
/*
 * CatalogCodePanel event table definition
 */

BEGIN_EVENT_TABLE( CatalogCodePanel, wxPanel )

EVT_CONTEXT_MENU( CatalogCodePanel::OnContextMenu )
EVT_GRID_CELL_CHANGED( CatalogCodePanel::OnCellChanged )
EVT_MENU( wxIDAddItem, CatalogCodePanel::OnContextPopup )
EVT_MENU( wxIDDeleteItem, CatalogCodePanel::OnContextPopup )

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter


/*
 *
 * CatalogCodePanel constructors
 *
 **************************************************/

CatalogCodePanel::CatalogCodePanel( ) { Init( ); }

/*
 *
 * CatalogCodePanel constructors
 *
 **************************************************/

CatalogCodePanel::CatalogCodePanel( wxWindow* parent, wxWindowID id, 
    const wxPoint& pos, const wxSize& size, 
    long style )
{ 
    Init( );
    Create( parent, id, pos, size, style );
}

/*
 *
 * CatalogCodePanel creation
 *
 **************************************************/

bool CatalogCodePanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, 
    const wxSize& size, long style )
{ 
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    return true;
}

/*
 *
 * CatalogCodePanel destructor
 *
 **************************************************/

CatalogCodePanel::~CatalogCodePanel( )
{ 

}

/*
 *
 * * Member initialisation
 *
 **************************************************/

void CatalogCodePanel::Init( )
{ 
    // CatalogCodePanel member initialisation
    m_grid = NULL;
    // CatalogCodePanel member initialisation
}

/*
 *
 * Control creation for CatalogCode
 *
 **************************************************/

void CatalogCodePanel::CreateControls( )
{ 
    // CatalogCodePanel content construction

    CatalogCodePanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer2, 1, wxGROW | wxALL, 5 );

    m_grid = new wxGrid( itemPanel1, ID_GRID, wxDefaultPosition, wxSize( 200, 150 ), 
        wxHSCROLL | wxVSCROLL );
    m_grid->SetDefaultColSize( 100 );
    m_grid->SetDefaultRowSize( 25 );
    m_grid->SetColLabelSize( 25 );
    m_grid->SetRowLabelSize( 50 );
    m_grid->CreateGrid( 0, 3, wxGrid::wxGridSelectCells );
    itemBoxSizer2->Add( m_grid, 1, wxGROW | wxALL, 5 );

    // Connect events and objects
    //    m_grid->Connect( ID_GRID, wxEVT_CONTEXT_MENU, 
    //    wxContextMenuEventHandler( CatalogCodePanel::OnContextMenu ), NULL, this );
    // CatalogCodePanel content construction
    for ( int i = 0; i < Catalog::CC_NbrTypes; i++ )
    { 
        m_grid->SetColLabelValue( i, Catalog::CC_CatalogCodeNames[ i ] );
    }
    
    SetDataEditable( GetSettings( )->IsCatalogSectionDataEditable( ) );

    m_grid->Refresh( );

}

/*
 *
 * InitRow
 *
 **************************************************/

wxXmlNode* CatalogCodePanel::InitNewCatCode( )
{ 
    wxXmlNode* ele = m_entry->AddCode( );
    Catalog::CatalogCode catCode( ele );
    for ( int col = 0; col < Catalog::CC_NbrTypes; col++ )
    { 
        catCode.SetAttr( ( Catalog::CatalogCodeTypes )col, "" );
    }
    return ele;
}
/*
 *
 * AddRow
 *
 **************************************************/

int CatalogCodePanel::AddNewRow( )
{ 
    if ( m_entry )
    { 
        int cnt = m_grid->GetNumberRows( );
        m_grid->InsertRows( cnt, 1 );
        wxXmlNode* ele = InitNewCatCode( );
        m_catCodeList.push_back( ele );
        ShowRow( cnt );
        return cnt;
    }
    return -1;
}
/*
 *
 * ShowRow
 *
 **************************************************/

void CatalogCodePanel::ShowRow( int row )
{ 
    wxXmlNode* ele = m_catCodeList[ row ];
    Catalog::CatalogCode catCode( ele );
    for ( int col = 0; col < Catalog::CC_NbrTypes; col++ )
    { 
        wxString str = catCode.GetAttr( ( Catalog::CatalogCodeTypes )col );
        m_grid->SetCellValue( row, col, str );
    }
}

/*
 *
 * Should we show tooltips?
 *
 **************************************************/

bool CatalogCodePanel::ShowToolTips( )
{ 
    return true;
}

/*
 *
 * Get bitmap resources
 *
 **************************************************/

wxBitmap CatalogCodePanel::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
    // CatalogCodePanel bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // CatalogCodePanel bitmap retrieval
}

/*
 *
 * Get icon resources
 *
 **************************************************/

wxIcon CatalogCodePanel::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
    // CatalogCodePanel icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // CatalogCodePanel icon retrieval
}

/*
 *
 *SetEntry
 *
 **************************************************/

void CatalogCodePanel::SetStamp( Catalog::Entry* entry )
{ 
    m_entry = entry;
    ShowEntry( );
}


/*
 * ShowEntry
 *
 **************************************************/

void CatalogCodePanel::ShowEntry( )
{ 
    // new entry to show; clean up the grid
    int row = m_grid->GetNumberRows( );
    m_grid->ClearGrid( );
    if ( row > 0 )
    { 
        m_grid->DeleteRows( 0, row );
    }
    m_catCodeList.clear( );
    row = m_grid->GetNumberRows( );  // better be 0 at this point

    // if the entry is valid
    if ( m_entry && m_entry->IsOK( ) )
    { 
        //and if it has catalog codes
        if ( m_entry->HasChildCode( ) )
        { 
            // loop through the codes and add them to the grid
            wxXmlNode* ele = m_entry->GetFirstChildCode( );
            while ( ele )
            { 
                m_grid->InsertRows( row, 1 );
                m_catCodeList.push_back( ele );

                ShowRow( row );
                row++;
                ele = m_entry->GetNextChildCode( ele );
            }
        }
    }
}

/*
 * wxEVT_CONTEXT_MENU event handler for ID_LISTCTRL
 *
 **************************************************/

void CatalogCodePanel::OnContextMenu( wxContextMenuEvent& event )
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
    event.Skip( );
}

/*
 * wxEVT_GRID_CELL_CHANGED event handler for ID_GRID
 *
 **************************************************/

void CatalogCodePanel::OnCellChanged( wxGridEvent& event )
{ 
    int col = event.GetCol( );
    int row = event.GetRow( );
    wxString str = m_grid->GetCellValue( row, col );
    wxXmlNode* ele = m_catCodeList[ row ];
    Catalog::CatalogCode catCode( ele );
    catCode.SetAttr( ( Catalog::CatalogCodeTypes )col, str );

    event.Skip( );
}

/*
 *
 * OnContextPopup( wxCommandEvent& event )
 *
 **************************************************/

void CatalogCodePanel::OnContextPopup( wxCommandEvent& event )
{ 
    int id = event.GetId( );
    switch ( id )
    { 
    case wxIDAddItem:
    { 
        AddNewRow( );
        break;
    }
    case wxIDDeleteItem:
    { 
        break;
    }
    }
}

void CatalogCodePanel::SetDataEditable( bool val )
{ 
     m_grid->EnableEditing( val );
}