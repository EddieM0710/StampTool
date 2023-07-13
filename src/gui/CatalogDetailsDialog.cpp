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
EVT_BUTTON( ID_CATDIRBUTTON, CatalogDetailsDialog::OnCatDirClick )
//EVT_BUTTON( ID_IMAGEDIRBUTTON, CatalogDetailsDialog::OnImageDirClick )

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
    Create( parent, id, caption, pos, wxSize( 800, 800 ), style );
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
    //   std::cout << "CatalogDetailsDialog" << "\n";

    CatalogDetailsDialog* theDialog = this;

    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    // cat name
    wxBoxSizer* theCatNameHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theCatNameHorizontalSizer, 1, wxGROW | wxALL, 0 );


    wxStaticText* itemStaticText1 = new wxStaticText( theDialog, wxID_STATIC, _( "Catalog Display Name" ), wxDefaultPosition, wxDefaultSize, 0 );
    theCatNameHorizontalSizer->Add( itemStaticText1, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_name = new wxTextCtrl( theDialog, ID_NAMELABELEDTEXTBOX, wxEmptyString, wxDefaultPosition, wxSize( 400, -1 ), 0 );
    theCatNameHorizontalSizer->Add( m_name, 7, wxGROW | wxALL, 5 );

    //cat path
    wxBoxSizer* theCatPathHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theCatPathHorizontalSizer, 1, wxGROW | wxALL, 0 );

    m_catPath = new LabeledTextBox( theDialog, ID_IMAGEPATHTEXTBOX, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_catPath->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    theCatPathHorizontalSizer->Add( m_catPath, 2, wxGROW | wxALL, 5 );

    wxBitmapButton* catDirButton = new wxBitmapButton( theDialog, ID_CATDIRBUTTON,
        wxBitmap( folder_open_xpm ),
        wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxNO_BORDER );
    theCatPathHorizontalSizer->Add( catDirButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // image path
    wxBoxSizer* theImagePathHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( theImagePathHorizontalSizer, 1, wxGROW | wxALL, 0 );

    // m_imagePath = new LabeledTextBox( theDialog, ID_IMAGEPATHTEXTBOX, wxDefaultPosition, wxSize( -1, 100 ), wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    // m_imagePath->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    // theImagePathHorizontalSizer->Add( m_imagePath, 5, wxGROW | wxALL, 5 );

    // wxBitmapButton* imageDirButton = new wxBitmapButton( theDialog, ID_IMAGEDIRBUTTON,
    //     wxBitmap( folder_open_xpm ),
    //     wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxNO_BORDER );
    // theImagePathHorizontalSizer->Add( imageDirButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    //ctrl buttons
    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // m_name->SetLabel( "Catalog Display Name" );
    m_catPath->SetLabel( "Catalog Path" );
    //    m_imagePath->SetLabel( "Image Path" );
}

//--------------
wxString CatalogDetailsDialog::GetCatalogPath( ) { return m_catPath->GetValue( ); };

//--------------
wxString CatalogDetailsDialog::GetName( ) { return m_name->GetValue( ); };

//--------------

//wxString CatalogDetailsDialog::GetImagePath( ) { return m_imagePath->GetValue( ); };

//--------------

void CatalogDetailsDialog::Init( )
{
    m_name = NULL;
    //    m_imagePath = NULL;
}

//--------------

void CatalogDetailsDialog::OnOkClick( wxCommandEvent& event )
{
    event.Skip( );
}

//--------------

void CatalogDetailsDialog::OnCatDirClick( wxCommandEvent& event )
{
    wxString catfile = m_catPath->GetValue( );
    wxFileName filename1( catfile );
    wxString path = filename1.GetPath( );
    wxString name = filename1.GetFullName( );
    wxFileDialog dirDialog( this, "Select the art directory", path, name,
        "Catalog files (*.cat)|*.cat",
        wxFD_SAVE );

    if ( dirDialog.ShowModal( ) == wxID_CANCEL )
        return;

    wxString filename = dirDialog.GetPath( );
    m_catPath->SetValue( filename );
    // wxString sectFilename = GetCatalogVolume( )->GetVolumeFilename( );
    // wxFileName vFn( sectFilename );
    // vFn.ClearExt( );
    // vFn.SetName( "" );
    // wxFileName fn;
    // fn.SetPath( filename );
    // fn.ClearExt( );
    // fn.SetName( "" );
    //wxString str1 = vFn.GetPath( );
    //wxString str2 = fn.GetPath( );
    //fn.MakeRelativeTo( vFn.GetPath( ) );
    //wxString str3 = fn.GetPath( );
   // SetImagePath( fn.GetPath( ) );
}

//--------------

// void CatalogDetailsDialog::OnImageDirClick( wxCommandEvent& event )
// {
//     wxString name = "";
//     wxDirDialog dirDialog( this, "Select the art directory",
//         m_imagePath->GetValue( ), wxDD_CHANGE_DIR );

//     if ( dirDialog.ShowModal( ) == wxID_CANCEL )
//         return;

//     wxString filename = dirDialog.GetPath( );
//     wxString sectFilename = GetCatalogVolume( )->GetVolumeFilename( );
//     wxFileName vFn( sectFilename );
//     vFn.ClearExt( );
//     vFn.SetName( "" );
//     wxFileName fn;
//     fn.SetPath( filename );
//     fn.ClearExt( );
//     fn.SetName( "" );
//     wxString str1 = vFn.GetPath( );
//     wxString str2 = fn.GetPath( );
//     fn.MakeRelativeTo( vFn.GetPath( ) );
//     wxString str3 = fn.GetPath( );
//     SetImagePath( fn.GetPath( ) );
// }

//--------------

bool CatalogDetailsDialog::IsNameModified( ) { return m_name->IsModified( ); };

//--------------
void CatalogDetailsDialog::SetCatalogFilename( wxString filename )
{
    m_catPath->SetValue( filename );
}

//--------------
// void CatalogDetailsDialog::SetImagePath( wxString str )
// {
//     m_imagePath->SetValue( str );
// };

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
