/*
 * @file  AlbumDetailsPanel.cpp
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
#include "wx/imaglist.h"
// includes
#include "wx/treectrl.h"
#include <wx/fontdlg.h>
#include <wx/fontdata.h>

#include "gui/AlbumDetailsPanel.h"
#include "gui/FontDefaultsPanel.h"
#include "gui/PageDefaultsPanel.h"
#include "gui/FrameDefaultsPanel.h"
#include "gui/StampDefaultsPanel.h"
#include "gui/LabeledTextBox.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/FontPickerHelper.h"
#include "design/DesignDefs.h"
#include "design/Album.h"
#include "utils/StampList.h"
#include "utils/Settings.h"
#include "utils/FontList.h"
#include "Defs.h"


IMPLEMENT_DYNAMIC_CLASS( AlbumDetailsPanel, HelperPanel )


BEGIN_EVENT_TABLE( AlbumDetailsPanel, HelperPanel )

END_EVENT_TABLE( )

//--------------

AlbumDetailsPanel::AlbumDetailsPanel( )
{
    Init( );
}

//--------------

AlbumDetailsPanel::AlbumDetailsPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

//--------------

AlbumDetailsPanel::~AlbumDetailsPanel( )
{
}

//--------------

bool AlbumDetailsPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    // wxDialog::Create( parent, id, caption, pos, size, style );
    wxPanel::Create( parent, id, pos, size, style );

    //( notebook, ID_PAGEDETAILSPANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );


    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

void AlbumDetailsPanel::CreateControls( )
{
    theDialog = this;

    int lastID = ID_ALBUMDETAILSDIALOG + 1;


    wxBoxSizer* theDialogVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( theDialogVerticalSizer );

    wxBoxSizer* notebookHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theDialogVerticalSizer->Add( notebookHorizontalSizer, 1, wxGROW | wxALL, 0 );

    wxNotebook* notebook = new wxNotebook( theDialog, ++lastID,
        wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
    notebookHorizontalSizer->Add( notebook, 1, wxGROW | wxALL, 0 );

    wxPanel* m_albumSettingsPanel = new wxPanel( notebook, ++lastID, wxDefaultPosition,
        wxDefaultSize, wxTAB_TRAVERSAL );
    m_albumSettingsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    wxBoxSizer* detailsVerticalSizer = new wxBoxSizer( wxHORIZONTAL );
    m_albumSettingsPanel->SetSizer( detailsVerticalSizer );

    wxBoxSizer* detailsHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    detailsVerticalSizer->Add( detailsHorizontalSizer, 1, wxGROW | wxALL, 5 );

    // m_name = SetupLabelText( m_albumSettingsPanel, detailsVerticalSizer, ++lastID,
     //    _( "Name" ), true, wxCommandEventHandler( AlbumDetailsPanel::OnNameClick ) );

    wxStaticBox* itemStaticBoxSizerStatic = new wxStaticBox( m_albumSettingsPanel, wxID_ANY, _( "Name" ) );
    wxStaticBoxSizer* itemStaticBoxSizer = new wxStaticBoxSizer( itemStaticBoxSizerStatic, wxHORIZONTAL );
    detailsHorizontalSizer->Add( itemStaticBoxSizer, 1, wxGROW | wxALL, 2 );

    m_name = new wxTextCtrl( itemStaticBoxSizer->GetStaticBox( ), ++lastID,
        wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
    itemStaticBoxSizer->Add( m_name, 1, wxGROW | wxALL, 2 );

    Connect( m_name->GetId( ), wxEVT_TEXT, wxCommandEventHandler( AlbumDetailsPanel::OnNameClick ) );



    notebook->AddPage( m_albumSettingsPanel, _( "Album Settings" ) );


    m_fontDetailsPanel = new FontDefaultsPanel( notebook, ++lastID, "",
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_fontDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    notebook->AddPage( m_fontDetailsPanel, _( "Font Defaults" ) );


    m_pageDetailsPanel = new PageDefaultsPanel( notebook, ++lastID, "",
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_pageDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    notebook->AddPage( m_pageDetailsPanel, _( "Page Defaults" ) );


    m_frameDetailsPanel = new FrameDefaultsPanel( notebook, ++lastID, "",
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_frameDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    notebook->AddPage( m_frameDetailsPanel, _( "Row/Col Defaults" ) );

    m_stampDetailsPanel = new StampDefaultsPanel( notebook, ++lastID, "",
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL );
    m_stampDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    notebook->AddPage( m_stampDetailsPanel, _( "Stamp Defaults" ) );

    Layout( );

    m_name->SetToolTip( "Name of Album" );
    // m_paperHeight->SetToolTip( "Height of paper in printer (in mm)" );
}

//--------------

wxString AlbumDetailsPanel::GetName( ) {
    return m_name->GetValue( );
}

//--------------

void AlbumDetailsPanel::Init( )
{
    m_name = NULL;
    // m_pageHeight = NULL;
    // m_pageWidth = NULL;
    // m_topPageMargin = NULL;
    // m_bottomPageMargin = NULL;
    // m_rightPageMargin = NULL;
    // m_leftPageMargin = NULL;
    // m_borderSize = NULL;
    m_validate = NULL;
}

//--------------

void AlbumDetailsPanel::SetupDialog( Design::Album* album )
{
    m_album = album;
    UpdateControls( );

};

//--------------

bool AlbumDetailsPanel::ShowToolTips( )
{
    return true;
}

//--------------

void AlbumDetailsPanel::OnNameClick( wxCommandEvent& event )
{
    wxString docName = m_album->GetDocName( );
    wxString name = m_name->GetValue( );
    if ( docName.Cmp( name ) )
    {
        m_album->SetDocName( name );
    }
    event.Skip( );

}

//--------------

void AlbumDetailsPanel::UpdateControls( )
{
    m_pageDetailsPanel->UpdateControls( );
    m_frameDetailsPanel->UpdateControls( );
    m_stampDetailsPanel->UpdateControls( );

    SetName( m_album->AlbumStampDefaults( )->GetAttrStr( Design::AT_Name ) );
}

