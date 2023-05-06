/*
 * @file src/gui/DefinePeriodsDialog.cpp
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

#include "gui/DefinePeriodsDialog.h"
#include "Settings.h"
#include "Defs.h"


IMPLEMENT_DYNAMIC_CLASS( DefinePeriodsDialog, wxDialog )

BEGIN_EVENT_TABLE( DefinePeriodsDialog, wxDialog )
EVT_TEXT( ID_ANTIQUE, DefinePeriodsDialog::OnAntiqueTextUpdated )
EVT_TEXT( ID_ANTIQUEYEAR, DefinePeriodsDialog::OnAntiqueYearTextUpdated )
EVT_TEXT( ID_CLASSIC, DefinePeriodsDialog::OnClassicTextUpdated )
EVT_TEXT( ID_MODERN, DefinePeriodsDialog::OnModernTextUpdated )
EVT_TEXT( ID_MODERNYEAR, DefinePeriodsDialog::OnModernYearTextUpdated )
EVT_BUTTON( wxID_CANCEL, DefinePeriodsDialog::OnCancelClick )
EVT_BUTTON( wxID_OK, DefinePeriodsDialog::OnOkClick )
END_EVENT_TABLE( )

//--------------

DefinePeriodsDialog::DefinePeriodsDialog( )
{
    Init( );
}

//--------------

DefinePeriodsDialog::DefinePeriodsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
    m_antiqueTextBox->SetValue( GetSettings( )->GetLowerPeriod( ) );
    m_AntiqueYear->SetValue( GetSettings( )->GetLowerDivision( ) );
    m_classicTextBox->SetValue( GetSettings( )->GetMiddlePeriod( ) );
    m_modernTextBox->SetValue( GetSettings( )->GetUpperPeriod( ) );
    m_modernYear->SetValue( GetSettings( )->GetUpperDivision( ) );

}

//--------------

DefinePeriodsDialog::~DefinePeriodsDialog( )
{
}

//--------------

bool DefinePeriodsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

//--------------

void DefinePeriodsDialog::CreateControls( )
{
    DefinePeriodsDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 0, wxALIGN_LEFT | wxALL, 5 );

    wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _( "First Period" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( itemStaticText2, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_antiqueTextBox = new wxTextCtrl( itemDialog1, ID_ANTIQUE, _( "Antique" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_antiqueTextBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _( "before " ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( itemStaticText4, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_AntiqueYear = new wxTextCtrl( itemDialog1, ID_ANTIQUEYEAR, _( "1920" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( m_AntiqueYear, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer6, 0, wxALIGN_LEFT | wxALL, 5 );

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Second Period" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add( itemStaticText7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_classicTextBox = new wxTextCtrl( itemDialog1, ID_CLASSIC, _( "Classic" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add( m_classicTextBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer9, 0, wxALIGN_LEFT | wxALL, 5 );

    wxStaticText* itemStaticText10 = new wxStaticText( itemDialog1, wxID_STATIC, _( "Last Period" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add( itemStaticText10, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_modernTextBox = new wxTextCtrl( itemDialog1, ID_MODERN, _( "Modern" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add( m_modernTextBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _( "after" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add( itemStaticText12, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_modernYear = new wxTextCtrl( itemDialog1, ID_MODERNYEAR, _( "1960" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add( m_modernYear, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add( itemButton15, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    itemBoxSizer14->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton17 = new wxButton( itemDialog1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add( itemButton17, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

}

//--------------

void DefinePeriodsDialog::Init( )
{
    m_antiqueTextBox = NULL;
    m_AntiqueYear = NULL;
    m_classicTextBox = NULL;
    m_modernTextBox = NULL;
    m_modernYear = NULL;
}

//--------------

void DefinePeriodsDialog::OnAntiqueTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

//--------------

void DefinePeriodsDialog::OnAntiqueYearTextUpdated( wxCommandEvent& event )
{
    event.Skip( );

}

//--------------

void DefinePeriodsDialog::OnClassicTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

//--------------

void DefinePeriodsDialog::OnModernTextUpdated( wxCommandEvent& event )
{
    event.Skip( );
}

//--------------

void DefinePeriodsDialog::OnModernYearTextUpdated( wxCommandEvent& event )
{
    event.Skip( );

}

//--------------

void DefinePeriodsDialog::OnCancelClick( wxCommandEvent& event )
{
    event.Skip( );
}

//--------------

void DefinePeriodsDialog::OnOkClick( wxCommandEvent& event )
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
    if ( GetSettings( )->isDirty( ) )
        GetSettings( )->Save( );

    event.Skip( );
}

//--------------

bool DefinePeriodsDialog::ShowToolTips( )
{
    return true;
}



