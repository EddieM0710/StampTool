/*
 * @file         FileCreateDialog.cpp
 *@brief
* @author      Eddie Monroe
* Modified by:
* @author     Fri 20 Jan 2023 19:33:48 CST
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

//  includes
//  includes

#include "FileCreateDialog.h"


#include <wx/filepicker.h>
#include <wx/filectrl.h>
#include "utils/Settings.h"
#include "Defs.h"

//#define wxUSE_FILECTRL 1
//  XPM images
//  XPM images


/*
 * FileCreateDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( FileCreateDialog, wxDialog )


/*
 * FileCreateDialog event table definition
 */

    BEGIN_EVENT_TABLE( FileCreateDialog, wxDialog )

    //  FileCreateDialog event table entries
    EVT_BUTTON( wxID_CANCEL, FileCreateDialog::OnCancelClick )
    EVT_BUTTON( wxID_OK, FileCreateDialog::OnOKClick )
    //  FileCreateDialog event table entries

    END_EVENT_TABLE( )


    /*
     * FileCreateDialog constructors
     */

    FileCreateDialog::FileCreateDialog( )
{
    Init( );
}

FileCreateDialog::FileCreateDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


/*
 * FileCreateDialog creator
 */

bool FileCreateDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    //  FileCreateDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    //  FileCreateDialog creation
    return true;
}


/*
 * FileCreateDialog destructor
 */

FileCreateDialog::~FileCreateDialog( )
{
    //  FileCreateDialog destruction
    //  FileCreateDialog destruction
}


/*
 * Member initialisation
 */

void FileCreateDialog::Init( )
{

    m_defaultDirectory = wxEmptyString;
    m_defaultFilename = wxEmptyString;
    m_wildCard = wxFileSelectorDefaultWildcardStr;
    //  FileCreateDialog member initialisation
    //  FileCreateDialog member initialisation
}


/*
 * Control creation for FileCreateDialog
 */

void FileCreateDialog::CreateControls( )
{

    FileCreateDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 0, wxGROW | wxALL, 5 );

    m_fileCtrl = new wxFileCtrl( this, ID_FILECREATEDIALOG, m_defaultDirectory, m_defaultFilename, m_wildCard, wxFD_SAVE );
    itemBoxSizer2->Add( m_fileCtrl, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* itemButton4 = new wxButton( itemDialog1, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( itemButton4, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxButton* itemButton5 = new wxButton( itemDialog1, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( itemButton5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    //  FileCreateDialog content construction
}




bool FileCreateDialog::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */



 /*
  *   wxID_CANCEL
  */

void FileCreateDialog::OnCancelClick( wxCommandEvent& event )
{
    event.Skip( );
}
wxString FileCreateDialog::GetPath( ) { return m_path; };
wxString FileCreateDialog::GetFile( ) { return m_file; };
wxString FileCreateDialog::GetDir( ) { return m_dir; };

void FileCreateDialog::OnOKClick( wxCommandEvent& event )
{
    m_path = m_fileCtrl->GetPath( );
    m_file = m_fileCtrl->GetFilename( );
    m_dir = m_fileCtrl->GetDirectory( );
    wxFileName prjFile( m_path );
    if ( prjFile.Exists( ) )
    {
        wxMessageDialog* dlg = new wxMessageDialog(
            this,
            wxT( "The selected file exists. \n"\
                "Select \"OK\" to overwrite the existing file losing the contents.\n"\
                "Or select \"Cancel\" to choose another name.\n" ),
            wxT( "Warning! File Exists.\n" ),
            wxOK | wxCANCEL | wxCENTER );
        int rsp = dlg->ShowModal( );
        if ( rsp == wxID_CANCEL )
        {
            return;
        }
    }

    event.Skip( );
}

