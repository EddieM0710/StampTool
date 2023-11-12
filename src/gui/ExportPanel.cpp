/*
 * @file  ExportPanel.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright ( c ) 2022
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "wx/imaglist.h"
#include "wx/notebook.h"

#include "gui/ExportPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/FontPickerHelper.h"
#include "design/Row.h"
 //#include "design/DesignDefs.h"
#include "design/Album.h"
#include "utils/FontList.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogList.h"


 /*
  * ExportPanel type definition
  */
IMPLEMENT_DYNAMIC_CLASS( ExportPanel, HelperPanel )


/*
 * ExportPanel event table definition
 */
    BEGIN_EVENT_TABLE( ExportPanel, HelperPanel )
    END_EVENT_TABLE( )
    ;

/*
 * ExportPanel constructors
 */

ExportPanel::ExportPanel( )
{
    Init( );
}

ExportPanel::ExportPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * ExportPanel creator
 */

bool ExportPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // ExportPanel creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // ExportPanel creation
    return true;
}



ExportPanel::~ExportPanel( )
{

}


void ExportPanel::Init( )
{
    m_emissionListCtrl = NULL;

    for ( int i = 0; i < Catalog::ET_NbrTypes; i++ )
    {
        m_emissionListCtrlStrings.Add( _( Catalog::EmissionStrings[ i ] ) );
    }

    GetCatalogData( )->GetCatalogList( )->MakeNameArray( m_catalogListCtrlStrings );
}


void ExportPanel::CreateControls( )
{
    ExportPanel* thePanel = this;

    wxBoxSizer* verticalSizer = new wxBoxSizer( wxVERTICAL );
    thePanel->SetSizer( verticalSizer );

    wxBoxSizer* horizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    verticalSizer->Add( horizontalSizer, 1, wxGROW | wxALL, 0 );

    int lastID = ID_LastID;

    m_emissionListCtrl = SetupCheckListBox( thePanel, horizontalSizer, lastID,
        "Emission", m_emissionListCtrlStrings,
        wxCommandEventHandler( ExportPanel::OnEmissionAllButtonClick ),
        wxCommandEventHandler( ExportPanel::OnEmissionClearButtonClick ) );

    m_catalogListCtrl = SetupCheckListBox( thePanel, horizontalSizer, lastID,
        "Catalogs", m_catalogListCtrlStrings,
        wxCommandEventHandler( ExportPanel::OnCatalogAllButtonClick ),
        wxCommandEventHandler( ExportPanel::OnCatalogClearButtonClick ) );

    m_inventorycheckBox = SetupCheckBox( thePanel, verticalSizer,
        lastID, "Include Inventory",
        wxCommandEventHandler( ExportPanel::OnIncludeInventoryButtonClick ) );



}


void ExportPanel::UpdateControls( )
{


}


//--------------

void ExportPanel::OnCatalogAllButtonClick( wxCommandEvent& event )
{
    // int base = 1;
    // for ( int i = 0; i < Catalog::ET_NbrTypes; i++ )
    // {
    //     m_emissionListCtrl->Check( i );
    //     base = base <<= 1;
    // }

    event.Skip( );

}

//--------------

void ExportPanel::OnCatalogClearButtonClick( wxCommandEvent& event )
{
    // int base = 1;
    // for ( int i = 0; i < Catalog::ET_NbrTypes; i++ )
    // {
    //     m_emissionListCtrl->Check( i, false );
    //     base = base <<= 1;
    // }
    event.Skip( );

}
void ExportPanel::OnIncludeInventoryButtonClick( wxCommandEvent& event )
{
    event.Skip( );

}

//--------------

void ExportPanel::OnEmissionAllButtonClick( wxCommandEvent& event )
{
    int base = 1;
    for ( int i = 0; i < Catalog::ET_NbrTypes; i++ )
    {
        m_emissionListCtrl->Check( i );
        base = base <<= 1;
    }

    event.Skip( );

}

//--------------

void ExportPanel::OnEmissionClearButtonClick( wxCommandEvent& event )
{
    int base = 1;
    for ( int i = 0; i < Catalog::ET_NbrTypes; i++ )
    {
        m_emissionListCtrl->Check( i, false );
        base = base <<= 1;
    }
    event.Skip( );

}
void ExportPanel::SetupDialog( Design::Row* row )
{

    UpdateControls( );

};

