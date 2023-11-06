/*
 * @file EditProjectDetails.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-12
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



#include <wx/bmpbndl.h>
#include <wx/filepicker.h>

#include "Defs.h"
#include "Project.h"
#include "gui/EditProjectDetails.h"
#include "gui/SortOrderPanel.h"
#include "gui/DefinePeriodsPanel.h"
#include "gui/FontPickerHelper.h"
#include <wx/font.h>
#include <wx/colour.h>
#include "utils/FontList.h"

 // XPM images
 // XPM images


 /*
  * EditProjectDetails type definition
  */

IMPLEMENT_DYNAMIC_CLASS( EditProjectDetails, wxDialog )


BEGIN_EVENT_TABLE( EditProjectDetails, wxDialog )
EVT_BUTTON( wxID_OK, EditProjectDetails::OnOkClick )
END_EVENT_TABLE( )




EditProjectDetails::EditProjectDetails( )
{
    Init( );
}

EditProjectDetails::EditProjectDetails( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
    //m_imageDirectory->SetValue( GetSettings( )->GetImageDirectory( ) );
    m_country->ChangeValue( GetProject( )->GetProjectCountryID( ) );
    m_catalog->ChangeValue( GetProject( )->GetProjectCatalogCode( ) );
    m_imageDirectory->ChangeValue( GetProject( )->GetImageDirectory( ) );
}


bool EditProjectDetails::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // EditProjectDetails creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // EditProjectDetails creation
    return true;
}


EditProjectDetails::~EditProjectDetails( )
{

}


void EditProjectDetails::Init( )
{
    m_imageDirectory = NULL;
    m_country = NULL;
    m_catalog = NULL;
}



void EditProjectDetails::CreateControls( )
{

    EditProjectDetails* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 2, wxGROW | wxALL, 5 );

    wxBoxSizer* imageHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( imageHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText1 = new wxStaticText( theDialog, wxID_STATIC, _( "Image Directory" ), wxDefaultPosition, wxDefaultSize, 0 );
    imageHorizontalSizer->Add( itemStaticText1, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_imageDirectory = new wxTextCtrl( theDialog, ID_IMAGEDIRECTORTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    imageHorizontalSizer->Add( m_imageDirectory, 3, wxGROW | wxALL, 5 );

    wxBitmapButton* itemBitmapButton3 = new wxBitmapButton( theDialog, wxID_UP, wxBitmapBundle( wxBitmap( wxT( "/sandbox/Applications/wx/wxWidgets-3.2.3/art/folder.xpm" ) ) ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    imageHorizontalSizer->Add( itemBitmapButton3, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    Connect( wxID_UP, wxEVT_BUTTON, wxCommandEventHandler( EditProjectDetails::OnSelectDirectory ) );


    // wxDirPickerCtrl* dirPicker = new wxDirPickerCtrl( theDialog, ID_IMAGEDIRECTORTEXTBOX, GetProject( )->GetImageDirectory( ),
    //     "PromptStr", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "CtrlNameStr" );
    // imageHorizontalSizer->Add( dirPicker, 3, wxGROW | wxALL, 5 );


    wxBoxSizer* codePrefHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( codePrefHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticText* itemStaticText5 = new wxStaticText( theDialog, wxID_STATIC, _( "Country Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( itemStaticText5, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_country = new wxTextCtrl( theDialog, ID_COUNTRYTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( m_country, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    codePrefHorizontalSizer->Add( 10, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText8 = new wxStaticText( theDialog, wxID_STATIC, _( "Catalog Code" ), wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( itemStaticText8, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP | wxBOTTOM, 5 );

    m_catalog = new wxTextCtrl( theDialog, ID_CATALOGTEXTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    codePrefHorizontalSizer->Add( m_catalog, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton13 = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton13, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton14 = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( itemButton14, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

}


void EditProjectDetails::OnOkClick( wxCommandEvent& event )
{
    UpdateProject( );
    event.Skip( );
}

void EditProjectDetails::OnSelectDirectory( wxCommandEvent& event )
{
    wxString dir = GetProject( )->GetImageDirectory( );
    if ( dir.IsEmpty( ) )
    {
        dir = wxGetCwd( );
    }
    wxDirDialog dirDialog( this, "Select Directory for Project Art", dir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST,
        wxDefaultPosition, wxDefaultSize, "wxDirDialogNameStr " );
    if ( dirDialog.ShowModal( ) == wxID_OK )
    {
        GetProject( )->SetImageDirectory( dirDialog.GetPath( ) );
    }


    event.Skip( );

}

void EditProjectDetails::UpdateProject( )
{
    if ( m_imageDirectory->IsModified( ) )
    {
        GetProject( )->SetImageDirectory( m_imageDirectory->GetValue( ) );
        m_imageDirectory->SetModified( false );
    }

    if ( m_country->IsModified( ) )
    {
        GetProject( )->SetProjectCountryID( m_country->GetValue( ) );
        m_country->SetModified( false );
    }

    if ( m_catalog->IsModified( ) )
    {
        GetProject( )->SetProjectCatalogCode( m_catalog->GetValue( ) );
        m_catalog->SetModified( false );
    }
}