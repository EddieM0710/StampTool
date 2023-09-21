/*
 * @file  TestDetailsPanel.cpp
 *@brief
* @author Eddie Monroe
* Modified by:
* @author Wed 23 Nov 2022 12:01:34 CST
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
#include "wx/notebook.h"

// includes
// includes

#include "gui/TestDetailsPanel.h"


IMPLEMENT_DYNAMIC_CLASS( TestDetailsPanel, HelperPanel )


BEGIN_EVENT_TABLE( TestDetailsPanel, HelperPanel )

END_EVENT_TABLE( )

//--------------

TestDetailsPanel::TestDetailsPanel( )
{
    Init( );
}

//--------------

TestDetailsPanel::TestDetailsPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

TestDetailsPanel::~TestDetailsPanel( )
{
}

//--------------

bool TestDetailsPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    // wxDialog::Create( parent, id, caption, pos, size, style );
    wxPanel::Create( parent, id, pos, size, style );



    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}


void TestDetailsPanel::CreateControls( )
{
    theDialog = this;

    int lastID = 23456 + 1;


    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 1, wxGROW | wxALL, 5 );

    panel = new wxPanel( theDialog, ++lastID, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    panel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    notebookHorizontalSizer->Add( panel, 0, wxGROW | wxALL, 5 );

    wxBoxSizer* theVerticalSizer = new wxBoxSizer( wxVERTICAL );
    panel->SetSizer( theVerticalSizer );


    text = SetupLabelText( panel, theVerticalSizer, lastID,
        _( "Text" ), false, wxCommandEventHandler( TestDetailsPanel::OnText ) );



}

//--------------
void TestDetailsPanel::OnText( wxCommandEvent& event )
{

    event.Skip( );

}


void TestDetailsPanel::Init( )
{

}


//--------------

void TestDetailsPanel::SetupDialog( )
{

};

