/*
 * @file CatalogPanel.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-22
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


#include "gui/CatalogTreeCtrl.h"
#include "wx/imaglist.h"


#include "gui/CatalogPanel.h"
#include "Defs.h"
#include <wx/filename.h>


 /*
  * CatalogPanel type definition
  */

IMPLEMENT_DYNAMIC_CLASS( CatalogPanel, wxPanel )


/*
 * CatalogPanel event table definition
 */

    BEGIN_EVENT_TABLE( CatalogPanel, wxPanel )
    EVT_TEXT( ID_TEXTCTRL, CatalogPanel::OnTextctrlTextUpdated )
    EVT_TOGGLEBUTTON( ID_TOGGLEBUTTON, CatalogPanel::OnTogglebuttonClick )
    EVT_CHOICE( ID_VOLUMECHOICE, CatalogPanel::OnVolumeChoiceSelected )
    EVT_BUTTON( ID_MANAGEBUTTON, CatalogPanel::OnManageClick )
    END_EVENT_TABLE( )


    CatalogPanel::CatalogPanel( )
{
    Init( );
}

CatalogPanel::CatalogPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

bool CatalogPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
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


CatalogPanel::~CatalogPanel( )
{
}


void CatalogPanel::Init( )
{
    // m_title = NULL;
    m_catalogTreeCtrl = NULL;
}

void CatalogPanel::CreateControls( )
{

    CatalogPanel* itemPanel1 = this;

    m_catPanelSizer = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( m_catPanelSizer );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    m_catPanelSizer->Add( itemBoxSizer1, 0, wxGROW | wxALL, 0 );

    m_manageButton = new wxButton( itemPanel1, ID_MANAGEBUTTON, _( "Manage" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_manageButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer1->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText2 = new wxStaticText( itemPanel1, wxID_STATIC, _( "Volume" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( itemStaticText2, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    m_volumeListCtrl = new wxChoice( itemPanel1, ID_VOLUMECHOICE, wxDefaultPosition, wxSize( -1, -1 ), GetCatalogData( )->GetVolumeNameStrings( ), wxLB_HSCROLL );
    itemBoxSizer1->Add( m_volumeListCtrl, 1, wxGROW | wxALL, 5 );


    m_toggleButton = new wxToggleButton( itemPanel1, ID_TOGGLEBUTTON, _( "Search" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_toggleButton->SetValue( false );
    itemBoxSizer1->Add( m_toggleButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    m_searchSizer = new wxBoxSizer( wxHORIZONTAL );
    m_catPanelSizer->Add( m_searchSizer, 0, wxGROW | wxALL, 5 );
    wxBoxSizer* searchVerticalSizer = new wxBoxSizer( wxVERTICAL );
    m_searchSizer->Add( searchVerticalSizer, 1, wxGROW | wxALL, 5 );
    wxButton* itemButton9 = new wxButton( itemPanel1, ID_NEXTBUTTON, _( "Next" ), wxDefaultPosition, wxDefaultSize, 0 );
    searchVerticalSizer->Add( itemButton9, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxBoxSizer* searchHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    searchVerticalSizer->Add( searchHorizontalSizer, 1, wxGROW | wxALL, 5 );
    wxStaticText* itemStaticText11 = new wxStaticText( itemPanel1, wxID_STATIC, _( "Search\nString" ), wxDefaultPosition, wxDefaultSize, 0 );
    searchHorizontalSizer->Add( itemStaticText11, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxTextCtrl* itemTextCtrl12 = new wxTextCtrl( itemPanel1, ID_SEARCHSTRINGTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    searchHorizontalSizer->Add( itemTextCtrl12, 2, wxGROW | wxALL, 5 );

    wxArrayString itemCheckListBox13Strings;
    itemCheckListBox13Strings.Add( _( "Titles" ) );
    itemCheckListBox13Strings.Add( _( "Series" ) );
    itemCheckListBox13Strings.Add( _( "Themes" ) );
    wxCheckListBox* itemCheckListBox13 = new wxCheckListBox( itemPanel1, ID_CHECKLISTBOX, wxDefaultPosition, wxDefaultSize, itemCheckListBox13Strings, wxLB_SINGLE );
    m_searchSizer->Add( itemCheckListBox13, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    wxBoxSizer* catTreeHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    m_catPanelSizer->Add( catTreeHorizontalSizer, 2, wxGROW | wxALL, 0 );

    m_catalogTreeCtrl = new CatalogTreeCtrl( itemPanel1, ID_CATALOGTREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxSUNKEN_BORDER | wxTR_DEFAULT_STYLE );
    catTreeHorizontalSizer->Add( m_catalogTreeCtrl, 2, wxGROW | wxALL, 0 );

    m_searchSizer->Show( false );
    m_catPanelSizer->Layout( );
}

bool CatalogPanel::ShowToolTips( )
{
    return true;
}

/*
 *   ID_TEXTCTRL
 */

void CatalogPanel::OnTextctrlTextUpdated( wxCommandEvent& event )
{

    event.Skip( );

}




/*
 *   ID_TOGGLEBUTTON
 */

void CatalogPanel::OnTogglebuttonClick( wxCommandEvent& event )
{
    if ( m_toggleButton->GetValue( ) )
    {
        m_searchSizer->Show( true );
        //m_searchSizer->Hide( m_catPanelSizer, true );
    }
    else
    {
        m_searchSizer->Show( false );
        //    m_searchSizer->Hide( m_catPanelSizer, false );
    }
    m_catPanelSizer->Layout( );

    event.Skip( );

}

void CatalogPanel::OnVolumeChoiceSelected( wxCommandEvent& event )
{
    int sel = m_volumeListCtrl->GetSelection( );

    GetCatalogData( )->GetCatalogList( )->SetCatalogVolumeNdx( sel );
    // wxString strSel = m_status->GetStringSelection( );
    // if ( m_stamp )
    // { 
    //     m_stamp->SetInventoryStatus( strSel );
    //     GetCatalogTreeCtrl( )->SetInventoryStatusImage( );
    // }

    event.Skip( );

}
void CatalogPanel::OnManageClick( wxCommandEvent& event )
{

    wxMenu m_designMenu;
    m_designMenu.Append( ID_NEWCATALOG, _( "New Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_OPENCATALOG, _( "Open Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_REMOVECATALOG, _( "Remove Catalog File" ), wxEmptyString, wxITEM_NORMAL );


    switch ( GetPopupMenuSelectionFromUser( m_designMenu ) )
    {
    case ID_NEWCATALOG:
    {
        break;
    }
    case ID_OPENCATALOG:
    {
        break;
    }
    case ID_REMOVECATALOG:
    {
        break;
    }

    }
}