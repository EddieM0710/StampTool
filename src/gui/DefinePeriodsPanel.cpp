/*
 * @file src/gui/DefinePeriodsPanel.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-11
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


#include "gui/DefinePeriodsPanel.h"
#include "Settings.h"
#include "Defs.h"
 /*
  * DefinePeriodsPanel type definition
  */

IMPLEMENT_DYNAMIC_CLASS( DefinePeriodsPanel, wxPanel )

BEGIN_EVENT_TABLE( DefinePeriodsPanel, wxPanel )
EVT_TEXT( ID_ANTIQUE, DefinePeriodsPanel::OnAntiqueTextUpdated )
EVT_TEXT( ID_ANTIQUEYEAR, DefinePeriodsPanel::OnAntiqueYearTextUpdated )
EVT_TEXT( ID_CLASSIC, DefinePeriodsPanel::OnClassicTextUpdated )
EVT_TEXT( ID_MODERN, DefinePeriodsPanel::OnModernTextUpdated )
EVT_TEXT( ID_MODERNYEAR, DefinePeriodsPanel::OnModernYearTextUpdated )
END_EVENT_TABLE( )

DefinePeriodsPanel::DefinePeriodsPanel( )
{
    Init( );
}

DefinePeriodsPanel::DefinePeriodsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
    m_antiqueTextBox->SetValue( GetSettings( )->GetLowerPeriod( ) );
    m_AntiqueYear->SetValue( GetSettings( )->GetLowerDivision( ) );
    m_classicTextBox->SetValue( GetSettings( )->GetMiddlePeriod( ) );
    m_modernTextBox->SetValue( GetSettings( )->GetUpperPeriod( ) );
    m_modernYear->SetValue( GetSettings( )->GetUpperDivision( ) );

}

bool DefinePeriodsPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
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

DefinePeriodsPanel::~DefinePeriodsPanel( )
{
}



void DefinePeriodsPanel::Init( )
{
    m_antiqueTextBox = NULL;
    m_AntiqueYear = NULL;
    m_classicTextBox = NULL;
    m_modernTextBox = NULL;
    m_modernYear = NULL;
}


void DefinePeriodsPanel::CreateControls( )
{

    DefinePeriodsPanel* thisPanel = this;

    wxBoxSizer* definePeriodVertialSizer = new wxBoxSizer( wxVERTICAL );
    thisPanel->SetSizer( definePeriodVertialSizer );

    wxBoxSizer* firstPeriodSizer = new wxBoxSizer( wxHORIZONTAL );
    definePeriodVertialSizer->Add( firstPeriodSizer, 0, wxALIGN_LEFT | wxALL, 5 );

    wxStaticText* firstStaticText = new wxStaticText( thisPanel, wxID_STATIC, _( "First Period" ), wxDefaultPosition, wxDefaultSize, 0 );
    firstPeriodSizer->Add( firstStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_antiqueTextBox = new wxTextCtrl( thisPanel, ID_ANTIQUE, _( "Antique" ), wxDefaultPosition, wxDefaultSize, 0 );
    firstPeriodSizer->Add( m_antiqueTextBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* beforeStaticText = new wxStaticText( thisPanel, wxID_STATIC, _( "before " ), wxDefaultPosition, wxDefaultSize, 0 );
    firstPeriodSizer->Add( beforeStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_AntiqueYear = new wxTextCtrl( thisPanel, ID_ANTIQUEYEAR, _( "1920" ), wxDefaultPosition, wxDefaultSize, 0 );
    firstPeriodSizer->Add( m_AntiqueYear, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* secondPeriodSizer = new wxBoxSizer( wxHORIZONTAL );
    definePeriodVertialSizer->Add( secondPeriodSizer, 0, wxALIGN_LEFT | wxALL, 5 );

    wxStaticText* secondStaticText = new wxStaticText( thisPanel, wxID_STATIC, _( "Second Period" ), wxDefaultPosition, wxDefaultSize, 0 );
    secondPeriodSizer->Add( secondStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_classicTextBox = new wxTextCtrl( thisPanel, ID_CLASSIC, _( "Classic" ), wxDefaultPosition, wxDefaultSize, 0 );
    secondPeriodSizer->Add( m_classicTextBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* lastPeriodSizer = new wxBoxSizer( wxHORIZONTAL );
    definePeriodVertialSizer->Add( lastPeriodSizer, 0, wxALIGN_LEFT | wxALL, 5 );

    wxStaticText* lastStaticText = new wxStaticText( thisPanel, wxID_STATIC, _( "Last Period" ), wxDefaultPosition, wxDefaultSize, 0 );
    lastPeriodSizer->Add( lastStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_modernTextBox = new wxTextCtrl( thisPanel, ID_MODERN, _( "Modern" ), wxDefaultPosition, wxDefaultSize, 0 );
    lastPeriodSizer->Add( m_modernTextBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* afterStaticText = new wxStaticText( thisPanel, wxID_STATIC, _( "after" ), wxDefaultPosition, wxDefaultSize, 0 );
    lastPeriodSizer->Add( afterStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_modernYear = new wxTextCtrl( thisPanel, ID_MODERNYEAR, _( "1960" ), wxDefaultPosition, wxDefaultSize, 0 );
    lastPeriodSizer->Add( m_modernYear, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

}

void DefinePeriodsPanel::OnAntiqueTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

void DefinePeriodsPanel::OnAntiqueYearTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

void DefinePeriodsPanel::OnClassicTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

void DefinePeriodsPanel::OnModernTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

void DefinePeriodsPanel::OnModernYearTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

void DefinePeriodsPanel::OnOkClick( )
{
    if ( m_antiqueTextBox->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetLowerPeriod( m_antiqueTextBox->GetValue( ) );
        m_antiqueTextBox->SetModified( false );
    }
    if ( m_AntiqueYear->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetLowerDivision( m_AntiqueYear->GetValue( ) );
        m_AntiqueYear->SetModified( false );
    }
    if ( m_modernTextBox->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetUpperPeriod( m_modernTextBox->GetValue( ) );
        m_modernTextBox->SetModified( false );
    }
    if ( m_classicTextBox->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetMiddlePeriod( m_classicTextBox->GetValue( ) );
        m_classicTextBox->SetModified( false );
    }
    if ( m_modernYear->IsModified( ) )
    {
        GetSettings( )->SetDirty( );
        GetSettings( )->SetUpperDivision( m_modernYear->GetValue( ) );
        m_modernYear->SetModified( false );
    }

}

bool DefinePeriodsPanel::ShowToolTips( )
{
    return true;
}
