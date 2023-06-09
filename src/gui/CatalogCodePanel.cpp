/**
 * @file CatalogCodePanel.cpp
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

#include "CatalogCodePanel.h"
#include "CatalogCode.h"
#include "catalog/CatalogDefs.h"
#include "catalog/CatalogData.h"
#include "XMLUtilities.h"
#include "Defs.h"
#include "utils/Settings.h"

IMPLEMENT_DYNAMIC_CLASS( CatalogCodePanel, wxPanel )


#define wxIDAddItem 17000
#define wxIDDeleteItem 17001


BEGIN_EVENT_TABLE( CatalogCodePanel, wxPanel )

EVT_CONTEXT_MENU( CatalogCodePanel::OnContextMenu )
EVT_GRID_CELL_CHANGED( CatalogCodePanel::OnCellChanged )
EVT_MENU( ID_AddItem, CatalogCodePanel::OnContextPopup )
EVT_MENU( wxIDDeleteItem, CatalogCodePanel::OnContextPopup )

END_EVENT_TABLE( )

//--------------

CatalogCodePanel::CatalogCodePanel( ) { Init( ); }

//--------------

CatalogCodePanel::CatalogCodePanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//--------------

CatalogCodePanel::~CatalogCodePanel( )
{

}

//--------------

int CatalogCodePanel::AddNewRow( )
{
    Catalog::Entry* stamp = GetCatalogData( )->GetCurrentStamp( );

    if ( stamp )
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

//--------------

bool CatalogCodePanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    return true;
}

//--------------

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

    // CatalogCodePanel content construction
    for ( int i = 0; i < Catalog::CC_NbrTypes; i++ )
    {
        m_grid->SetColLabelValue( i, Catalog::CatalogCodeNames[ i ] );
    }

    SetDataEditable( GetSettings( )->IsCatalogVolumeEditable( ) );

    m_grid->Refresh( );

}

//--------------

void CatalogCodePanel::Init( )
{
    m_grid = NULL;
}

//--------------

wxXmlNode* CatalogCodePanel::InitNewCatCode( )
{
    Catalog::Entry* stamp = GetCatalogData( )->GetCurrentStamp( );

    wxXmlNode* ele = stamp->AddCode( );
    Catalog::CatalogCode catCode( ele );
    for ( int col = 0; col < Catalog::CC_NbrTypes; col++ )
    {
        catCode.SetAttr( ( Catalog::CatalogCodeTypes ) col, "" );
    }
    return ele;
}

//--------------

void CatalogCodePanel::OnContextMenu( wxContextMenuEvent& event )
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
        menu.Append( wxID_ANY, wxString::Format( "Menu1" ) );
        menu.Append( ID_AddItem, "Add Item" );
        menu.Append( wxIDDeleteItem, "Delete Item" );

        PopupMenu( &menu, point.x, point.y );
    }
    event.Skip( );
}

//--------------

void CatalogCodePanel::OnCellChanged( wxGridEvent& event )
{
    int col = event.GetCol( );
    int row = event.GetRow( );
    wxString str = m_grid->GetCellValue( row, col );
    wxXmlNode* ele = m_catCodeList[ row ];
    Catalog::CatalogCode catCode( ele );
    catCode.SetAttr( ( Catalog::CatalogCodeTypes ) col, str );

    event.Skip( );
}

//--------------

void CatalogCodePanel::OnContextPopup( wxCommandEvent& event )
{
    int id = event.GetId( );
    switch ( id )
    {
        case ID_AddItem:
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

//--------------

void CatalogCodePanel::SetDataEditable( bool val )
{
    m_grid->EnableEditing( val );
}

//--------------

void CatalogCodePanel::ShowRow( int row )
{
    wxXmlNode* ele = m_catCodeList[ row ];
    Catalog::CatalogCode catCode( ele );
    for ( int col = 0; col < Catalog::CC_NbrTypes; col++ )
    {
        wxString str = catCode.GetAttr( ( Catalog::CatalogCodeTypes ) col );
        m_grid->SetCellValue( row, col, str );
    }
}

//--------------

bool CatalogCodePanel::ShowToolTips( )
{
    return true;
}

//--------------

void CatalogCodePanel::UpdatePanel( )
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
    Catalog::Entry* stamp = GetCatalogData( )->GetCurrentStamp( );

    if ( stamp && stamp->IsOK( ) )
    {
        //and if it has catalog codes
        if ( stamp->HasChildCode( ) )
        {
            // loop through the codes and add them to the grid
            wxXmlNode* ele = stamp->GetFirstChildCode( );
            while ( ele )
            {
                m_grid->InsertRows( row, 1 );
                m_catCodeList.push_back( ele );

                ShowRow( row );
                row++;
                ele = stamp->GetNextChildCode( ele );
            }
        }
    }
}
