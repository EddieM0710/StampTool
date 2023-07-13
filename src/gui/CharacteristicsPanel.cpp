/**
 * @file CharacteristicsPanel.cpp
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
 */

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Defs.h"
#include "gui/CharacteristicsPanel.h"
#include "gui/LabeledTextBox.h"
#include "catalog/CatalogData.h"
#include "utils/Settings.h"


IMPLEMENT_DYNAMIC_CLASS( CharacteristicsPanel, wxPanel )

BEGIN_EVENT_TABLE( CharacteristicsPanel, wxPanel )

EVT_TEXT( ID_HEIGHTEXTBOX, CharacteristicsPanel::OnTextctrlTextUpdated )
EVT_TEXT( ID_WIDTHTEXTBOX, CharacteristicsPanel::OnTextctrlTextUpdated )

END_EVENT_TABLE( )

//--------------

CharacteristicsPanel::CharacteristicsPanel( ) { Init( ); }

CharacteristicsPanel::CharacteristicsPanel( wxWindow* parent, wxWindowID id,
    const wxPoint& pos,
    const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//--------------

CharacteristicsPanel::~CharacteristicsPanel( void )
{
}

//--------------

bool CharacteristicsPanel::Create( wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
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

void CharacteristicsPanel::CreateControls( void )
{
    //   std::cout << "CharacteristicsPanel" << "\n";
    CharacteristicsPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemPanel1->SetSizer( itemBoxSizer1 );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer2, 1, wxGROW | wxALL, 5 );

    m_height = new LabeledTextBox( itemPanel1, ID_HEIGHTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_height, 0, wxGROW | wxALL, 2 );

    m_width = new LabeledTextBox( itemPanel1, ID_WIDTHTEXTBOX, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add( m_width, 0, wxGROW | wxALL, 2 );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxVERTICAL );
    itemBoxSizer1->Add( itemBoxSizer7, 1, wxGROW | wxALL, 5 );

    m_width->SetValue( "40" );
    m_height->SetValue( "40" );

    m_height->SetLabel( "Height" );
    m_width->SetLabel( "Width" );

    SetDataEditable( GetSettings( )->IsCatalogVolumeEditable( ) );
}

//--------------

void CharacteristicsPanel::Init( void )
{
    m_height = NULL;
    m_width = NULL;
}

//--------------

void CharacteristicsPanel::OnTextctrlTextUpdated( wxCommandEvent& event )
{
    void* eventObject = event.GetClientData( );

    if ( eventObject == m_height )
    {
        UpdateStampValue( Catalog::DT_Height, m_height );
    }
    else if ( eventObject == m_width )
    {
        UpdateStampValue( Catalog::DT_Width, m_width );
    }

    event.Skip( );
}

//--------------

void CharacteristicsPanel::SetDataEditable( bool val )
{
    m_height->SetEditable( val );
    m_width->SetEditable( val );
}

//--------------

bool CharacteristicsPanel::ShowToolTips( void ) { return true; }

//--------------
/// initializes the CharacteristicsPanel with new stamp values
void CharacteristicsPanel::UpdatePanel( )
{
    Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );

    if ( stamp.IsOK( ) )
    {
        m_height->SetValue( stamp.GetAttr( Catalog::DT_Height ) );
        m_width->SetValue( stamp.GetAttr( Catalog::DT_Width ) );
    }
}

//--------------

void CharacteristicsPanel::UpdateStampValue( Catalog::DataTypes dt, LabeledTextBox* textBox )
{
    if ( textBox->IsModified( ) )
    {
        wxString val = textBox->GetValue( );
        Catalog::Entry stamp( GetCatalogData( )->GetCurrentStamp( ) );
        stamp.SetAttr( dt, val );
        textBox->SetModified( false );
    }
}
