/**
 * @file  CatalogDetailsDialog.cpp
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

#include "wx/filename.h"
#include "wx/imaglist.h"

#include "wx/notebook.h"

#include "gui/CatalogDetailsDialog.h"
#include "gui/LabeledTextBox.h"
//#include "gui/AppData.h" 
#include "catalog/CatalogData.h"

IMPLEMENT_DYNAMIC_CLASS( CatalogDetailsDialog, wxDialog )

BEGIN_EVENT_TABLE( CatalogDetailsDialog, wxDialog )

EVT_BUTTON( wxID_OK, CatalogDetailsDialog::OnOkClick )
EVT_BUTTON( ID_DIRBUTTON, CatalogDetailsDialog::OnDirClick )

END_EVENT_TABLE( )



//--------------

///  @brief Construct a new Catalog Details Dialog:: Catalog Details Dialog object
///  
CatalogDetailsDialog::CatalogDetailsDialog( )
{
    Init( );
}

///--------------

//  @brief Construct a new Catalog Details Dialog:: Catalog Details Dialog object
///  
///  @param parent 
///  @param id 
///  @param caption 
///  @param pos 
///  @param size 
///  @param style 
CatalogDetailsDialog::CatalogDetailsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

CatalogDetailsDialog::~CatalogDetailsDialog( )
{
    // CatalogDetailsDialog destruction
    // CatalogDetailsDialog destruction
}


///  @brief 
///  
///  @param parent 
///  @param id 
///  @param caption 
///  @param pos 
///  @param size 
///  @param style 
///  @return true 
///  @return false 
bool CatalogDetailsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // CatalogDetailsDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    // CatalogDetailsDialog creation
    return true;
}

//--------------

void CatalogDetailsDialog::CreateControls( )
{

    CatalogDetailsDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    m_name = new LabeledTextBox( theDialog, ID_NAMELABELEDTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_name->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    theDialogVerticalSizer->Add( m_name, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* theDialogHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theDialogHorizontalSizer, 1, wxGROW | wxALL, 0 );

    m_imagePath = new LabeledTextBox( theDialog, ID_IMAGEPATHTEXTBOX, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_imagePath->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    theDialogHorizontalSizer->Add( m_imagePath, 1, wxGROW | wxALL, 5 );

    wxButton* dirButton = new wxButton( theDialog, ID_DIRBUTTON, _( "Dir" ), wxDefaultPosition, wxDefaultSize, 0 );
    theDialogHorizontalSizer->Add( dirButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    //>>dialog Ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //>>dialog Ctrl buttons  
    m_name->SetLabel( "Name" );
    m_imagePath->SetLabel( "ImageName" );
}

//--------------

wxString CatalogDetailsDialog::GetName( ) { return m_name->GetValue( ); };

//--------------

wxString CatalogDetailsDialog::GetImagePath( ) { return m_imagePath->GetValue( ); };

//--------------

void CatalogDetailsDialog::Init( )
{
    m_name = NULL;
    m_imagePath = NULL;
}

//--------------

void CatalogDetailsDialog::OnOkClick( wxCommandEvent& event )
{
    event.Skip( );
}

//--------------

void CatalogDetailsDialog::OnDirClick( wxCommandEvent& event )
{
    wxDirDialog dirDialog( this, "Select the art directory", GetCatalogData( )->GetImagePath( ) );

    if ( dirDialog.ShowModal( ) == wxID_CANCEL )
        return;

    wxString filename = dirDialog.GetPath( );
    wxString sectFilename = GetCatalogVolume( )->GetVolumeFilename( );
    wxFileName vFn( sectFilename );
    vFn.ClearExt( );
    vFn.SetName( "" );
    wxFileName fn;
    fn.SetPath( filename );
    fn.ClearExt( );
    fn.SetName( "" );
    wxString str1 = vFn.GetPath( );
    wxString str2 = fn.GetPath( );
    fn.MakeRelativeTo( vFn.GetPath( ) );
    wxString str3 = fn.GetPath( );
    SetImagePath( fn.GetPath( ) );
}

//--------------

bool CatalogDetailsDialog::IsNameModified( ) { return m_name->IsModified( ); };

//--------------

void CatalogDetailsDialog::SetImagePath( wxString str )
{
    m_imagePath->SetValue( str );
};

//--------------

void CatalogDetailsDialog::SetName( wxString str )
{
    m_name->SetValue( str );
};

//--------------

void CatalogDetailsDialog::SetNameModified( bool state ) { m_name->SetModified( state ); };

//--------------

void CatalogDetailsDialog::SetDesignTreeID( wxTreeItemId id ) { if ( id.IsOk( ) ) m_designTreeID = id; };

//--------------

bool CatalogDetailsDialog::ShowToolTips( )
{
    return true;
}
