/*
 * @file         GenerateList.cpp
 *@brief
* @author      Eddie Monroe
* Modified by:
* @author     Thu 08 Dec 2022 20:20:21 CST
 *
* @copyright Copyright ( c ) 2024
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
 ///////////////////////////////////////


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "Defs.h"
#include "GenerateList.h"
#include "GenerateListSettings.h"
#include "catalog/CatalogDefs.h"
#include "catalog/CatalogVolume.h"
#include "catalog/Entry.h"
#include "utils/XMLUtilities.h"
#include "gui/CatalogTreeCtrl.h"

IMPLEMENT_DYNAMIC_CLASS( GenerateList, wxPanel )

BEGIN_EVENT_TABLE( GenerateList, wxPanel )
EVT_BUTTON( ID_SETLISTPREFSBUTTON, GenerateList::OnSetListPrefsButtonClick )
EVT_BUTTON( ID_WRITEBUTTON, GenerateList::OnWriteButtonClick )
EVT_TEXT( ID_FILENAMETEXTCTRL, GenerateList::OnFileNameTextUpdated )
EVT_GRID_CELL_LEFT_CLICK( GenerateList::OnCellLeftClick )
EVT_GRID_LABEL_LEFT_CLICK( GenerateList::OnLabelLeftClick )
END_EVENT_TABLE( )

//--------------

GenerateList::GenerateList( )
{
    Init( );
}

//--------------

GenerateList::GenerateList( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//--------------

GenerateList::~GenerateList( )
{
}

//--------------

bool GenerateList::AddEntry( Catalog::Entry* entry )
{

    m_gridCtrl->SetCellValue( m_currRow, 0, entry->GetID( ) );
    m_gridCtrl->SetCellValue( m_currRow, 1, entry->GetInventoryStatus( ) );
    m_gridCtrl->SetCellValue( m_currRow, 2, entry->GetName( ) );
    m_gridCtrl->SetCellValue( m_currRow, 3, entry->GetIssuedDate( ) );
    m_gridCtrl->SetCellValue( m_currRow, 4, entry->GetEmission( ) );
    m_gridCtrl->SetCellValue( m_currRow, 5, entry->GetFormat( ) );
    m_gridCtrl->SetCellValue( m_currRow, 6, entry->GetIssuedDate( ) );

    return true;
}

void GenerateList::ClearList( )
{
    m_currRow = 0;
    m_gridCtrl->ClearGrid( );

}
//--------------

bool GenerateList::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

//--------------

void GenerateList::CreateControls( )
{
    GenerateList* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton1 = new wxButton( itemPanel1, ID_SETLISTPREFSBUTTON, _( "Set List Preferences" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( itemButton1, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_gridCtrl = new wxGrid( itemPanel1, ID_GRIDCTRL, wxDefaultPosition, wxSize( 200, 150 ), wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );
    m_gridCtrl->SetDefaultColSize( 100 );
    m_gridCtrl->SetDefaultRowSize( 25 );
    m_gridCtrl->SetColLabelSize( 25 );
    m_gridCtrl->SetRowLabelSize( 50 );
    m_gridCtrl->CreateGrid( 0, 9, wxGrid::wxGridSelectCells );
    itemBoxSizer2->Add( m_gridCtrl, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer8, 0, wxGROW | wxALL, 5 );

    m_writeButton = new wxButton( itemPanel1, ID_WRITEBUTTON, _( "Write" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add( m_writeButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel1, wxID_STATIC, _( "file name" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add( itemStaticText10, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_filename = new wxTextCtrl( itemPanel1, ID_FILENAMETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add( m_filename, 1, wxGROW | wxALL, 5 );

    // GenerateList content construction
    m_gridCtrl->SetColLabelValue( 0, "ID" );
    m_gridCtrl->SetColLabelValue( 1, Catalog::DataTypeNames[ Catalog::DT_InventoryStatus ] );
    m_gridCtrl->SetColLabelValue( 2, "Name" );
    m_gridCtrl->SetColLabelValue( 3, Catalog::DataTypeNames[ Catalog::DT_Issued_on ] );
    m_gridCtrl->SetColLabelValue( 4, Catalog::DataTypeNames[ Catalog::DT_Emission ] );
    m_gridCtrl->SetColLabelValue( 5, Catalog::DataTypeNames[ Catalog::DT_Format ] );
    m_gridCtrl->SetColLabelValue( 6, Catalog::DataTypeNames[ Catalog::DT_Width ] );
    m_gridCtrl->SetColLabelValue( 7, Catalog::DataTypeNames[ Catalog::DT_Height ] );
    m_gridCtrl->SetColLabelValue( 8, Catalog::DataTypeNames[ Catalog::DT_StampMount ] );

}

//--------------

bool GenerateList::CheckStatus( Catalog::Entry* entry )
{
    if ( m_checkedStatusItems == 0 )
    {
        return true;
    }
    wxString emission = entry->GetInventoryStatus( );
    int i = Catalog::FindStatusType( emission );
    if ( i >= 0 )
    {
        int base = 1;
        base = base <<= i;
        return m_checkedStatusItems & base;
    }
    return true;
}

//--------------

bool GenerateList::CheckFormat( Catalog::Entry* entry )
{
    if ( m_checkedFormatItems == 0 )
    {
        return true;
    }
    wxString emission = entry->GetFormat( );
    int i = Catalog::FindFormatType( emission );
    if ( i >= 0 )
    {
        int base = 1;
        base = base <<= i;
        return m_checkedFormatItems & base;
    }
    return true;
}

//--------------

bool GenerateList::CheckEmission( Catalog::Entry* entry )
{
    if ( m_checkedEmissionItems == 0 )
    {
        return true;
    }
    wxString emission = entry->GetEmission( );
    int i = Catalog::FindEmissionType( emission );
    if ( i >= 0 )
    {
        int base = 1;
        base = base <<= i;
        return m_checkedEmissionItems & base;
    }
    return true;
}

//--------------

void GenerateList::DoListPrefs( )
{
    GenerateListSettings* settings = new GenerateListSettings( this, 12349,
        _( "Edit Report Settings" ) );

    settings->SetCheckedStatusItems( m_checkedStatusItems );
    settings->SetCheckedFormatItems( m_checkedFormatItems );
    settings->SetCheckedEmissionItems( m_checkedEmissionItems );
    settings->SetFromYear( m_fromYear );
    settings->SetToYear( m_toYear );

    if ( settings->ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    m_checkedStatusItems = settings->GetCheckedStatusItems( );
    m_checkedFormatItems = settings->GetCheckedFormatItems( );
    m_checkedEmissionItems = settings->GetCheckedEmissionItems( );


    m_fromYear = settings->GetFromYear( );
    m_toYear = settings->GetToYear( );

    UpdateGrid( );

    return;
}
//#include "wx/graphics.h"

//--------------

int GenerateList::GetStringLen( wxFont& font, wxString text )
{

    wxClientDC dc( this );//= this->GetDC( );
    dc.SetMapMode( wxMM_METRIC );
    dc.SetFont( font );

    PrepareDC( dc );

    //SetUserScale( dc );

    text.Trim( );
    text.Trim( false );
    int len = text.length( );
    if ( len > 0 )
    {
        wxSize ext = dc.GetTextExtent( text );
        return ext.GetX( );
    }
    return 25;
}

//--------------

void GenerateList::Init( )
{
    m_gridCtrl = NULL;
    m_writeButton = NULL;
    m_filename = NULL;
    m_checkedStatusItems = 0;
    m_checkedFormatItems = 0;
    m_checkedEmissionItems = 0;
    m_fromYear = "";
    m_toYear = "";
}

//--------------

int MakeBitPatern( wxArrayInt& array )
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

void GenerateList::OnFileNameTextUpdated( wxCommandEvent& event )
{

    event.Skip( );

}

//--------------

void GenerateList::OnSetListPrefsButtonClick( wxCommandEvent& event )
{
    DoListPrefs( );
    event.Skip( );

}

//--------------

void GenerateList::OnWriteButtonClick( wxCommandEvent& event )
{
    UpdateGrid( );

    event.Skip( );
}

//--------------

void GenerateList::ShowRow( Catalog::Entry* entry, int row )
{
    wxFont font = m_gridCtrl->GetCellFont( row, 2 );

    m_gridCtrl->AppendRows( 1 );
    m_gridCtrl->SetCellValue( row, 0, entry->GetID( ) );
    m_gridCtrl->SetCellValue( row, 1, entry->GetInventoryStatus( ) );
    m_gridCtrl->SetCellValue( row, 2, entry->GetName( ) );

    int size = GetStringLen( font, entry->GetName( ) );
    int curr = m_gridCtrl->GetColSize( 2 );
    if ( size > curr )
    {
        m_gridCtrl->SetColSize( 2, size );
    }

    m_gridCtrl->SetCellValue( row, 3, entry->GetIssuedDate( ) );
    m_gridCtrl->SetCellValue( row, 4, entry->GetEmission( ) );
    size = GetStringLen( font, entry->GetEmission( ) );
    curr = m_gridCtrl->GetColSize( 4 );
    if ( size > curr )
    {
        m_gridCtrl->SetColSize( 4, size );
    }
    m_gridCtrl->SetCellValue( row, 5, entry->GetFormat( ) );
    m_gridCtrl->SetCellValue( row, 6, entry->GetWidth( ) );
    m_gridCtrl->SetCellValue( row, 7, entry->GetHeight( ) );
    m_gridCtrl->SetCellValue( row, 8, entry->GetMount( ) );

    // wxString height = entry->GetHeight( );
    // wxString width = entry->GetWidth( );
    // if ( height.IsEmpty( ) || width.IsEmpty( ) )
    // {
    //     m_gridCtrl->SetCellValue( row, 6, "Size Missing" );
    // }
    // else
    // {
    //     m_gridCtrl->SetCellValue( row, 6, "" );

    // }

}

//--------------

bool GenerateList::ShowToolTips( )
{
    return true;
}

//--------------

void GenerateList::UpdateGrid( )
{
    m_gridCtrl->ClearGrid( );
    int nbrRows = m_gridCtrl->GetNumberRows( );
    if ( nbrRows > 0 ) m_gridCtrl->DeleteRows( 0, nbrRows );
    int row = 0;
    Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
    if ( catalogVolume )
    {
        wxXmlDocument* entryDoc = catalogVolume->GetDoc( );
        wxXmlNode* root = entryDoc->GetRoot( );


        if ( root )
        {
            WriteEntries( root, row );
        }
    }
}

//--------------

void GenerateList::WriteEntries( wxXmlNode* parent, int& row )
{
    wxXmlNode* child = parent->GetChildren( );
    while ( child )
    {
        if ( !child->GetName( ).compare( "Entry" ) )
        {
            Catalog::Entry entry( child );
            if ( CheckStatus( &entry ) && CheckEmission( &entry ) && CheckFormat( &entry ) )
            {
                ShowRow( &entry, row );
                row++;
            }
        }
        WriteEntries( child, row );
        child = child->GetNext( );
    }
}


void GenerateList::OnCellLeftClick( wxGridEvent& event )
{
    int row = event.GetRow( );
    wxString id = m_gridCtrl->GetCellValue( row, 0 );
    GetCatalogTreeCtrl( )->SelectStamp( id );
    event.Skip( );
}


void GenerateList::OnLabelLeftClick( wxGridEvent& event )
{

    event.Skip( );

}
