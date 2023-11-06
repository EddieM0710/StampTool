
/*
 * @file AlbumSplitterWiindow.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
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

#include "wx/imaglist.h"
#include <wx/filedlg.h> 

#include "gui/AlbumPanel.h"

#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumTreePanel.h"
#include "gui/AlbumImagePanel.h"
#include "gui/AlbumDetailsPanel.h"
#include "gui/PageDetailsPanel.h"
#include "gui/ColDetailsPanel.h"
#include "gui/RowDetailsPanel.h"
 //#include "gui/TestDetailsPanel.h"
#include "gui/StampDetailsPanel.h"
#include "gui/AppData.h" 
#include "gui/LabeledTextBox.h"
#include "gui/FileCreateDialog.h"
#include "design/AlbumData.h"
#include "design/Album.h"
#include "design/AlbumVolume.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/Project.h"
#include "catalog/CatalogData.h"
#include "Defs.h"
#include "gui/AlbumTOCTreeCtrl.h"


IMPLEMENT_DYNAMIC_CLASS( AlbumPanel, wxPanel )

BEGIN_EVENT_TABLE( AlbumPanel, wxPanel )
EVT_SLIDER( ID_ALBUMZOOMSLIDER, AlbumPanel::OnZoomsliderUpdated )
//EVT_CHOICE( ID_LISTCHOICE, AlbumPanel::OnAlbumChoiceSelected )
EVT_BUTTON( ID_MANAGEBUTTON, AlbumPanel::OnManageClick )
//EVT_SPLITTER_SASH_POS_CHANGED( ID_SECONDARYSPLITTERWINDOW, AlbumPanel::OnSplitterwindowSashPosChanged )
END_EVENT_TABLE( )


//--------------


AlbumPanel::AlbumPanel( )
{
    Init( );
}

//--------------

AlbumPanel::AlbumPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//--------------

AlbumPanel::~AlbumPanel( )
{
}

void AlbumPanel::Clear( )
{

}


//--------------

bool AlbumPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    Centre( );
    return true;
}

//--------------

void AlbumPanel::CreateControls( )
{

    AlbumPanel* theAlbumPanel = this;

    wxBoxSizer* theAlbumLayoutPanelVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theAlbumPanel->SetSizer( theAlbumLayoutPanelVerticalSizer );

    wxBoxSizer* SplitterWindowHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    theAlbumLayoutPanelVerticalSizer->Add( SplitterWindowHorizontalSizer, 0, wxGROW | wxALL, 0 );

    m_albumVerticalSplitterWindow = new wxSplitterWindow( theAlbumPanel, ID_SECONDARYSPLITTERWINDOW, wxDefaultPosition, wxDefaultSize, wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    m_albumVerticalSplitterWindow->SetMinimumPaneSize( 50 );
    theAlbumLayoutPanelVerticalSizer->Add( m_albumVerticalSplitterWindow, 1, wxGROW | wxALL, 5 );

    // Album Tree Panel
    m_albumTreePanel = new AlbumTreePanel( m_albumVerticalSplitterWindow, ID_SCROLLEDWINDOW, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );

    m_imageDetailsSplitterWindow = CreateImageDetailsSplitterWindow( m_albumVerticalSplitterWindow );

    // put the tree and the image panel into t he splitter window
    m_albumVerticalSplitterWindow->SplitVertically( m_albumTreePanel, m_imageDetailsSplitterWindow, 400 );

    ////

    ////




    GetAlbumData( )->SetAlbumImagePanel( m_albumImagePanel );
    GetAlbumData( )->SetAlbumPanel( this );

}

void AlbumPanel::OnSplitterwindowSashPosChanged( wxSplitterEvent& event )
{
    Layout( );
    Fit( );

    ////@begin wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED event handler for ID_SPLITTERWINDOW1 in SplitterTest.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED event handler for ID_SPLITTERWINDOW1 in SplitterTest. 
}


wxSplitterWindow* AlbumPanel::CreateImageDetailsSplitterWindow( wxWindow* parent )
{

    wxBoxSizer* splitterWindowVerticalSizer = new wxBoxSizer( wxVERTICAL );
    parent->SetSizer( splitterWindowVerticalSizer );

    wxSplitterWindow* imageDetailsSplitterWindow = new wxSplitterWindow( parent, ID_HORIZONTALALBUMSPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    // imageDetailsSplitterWindow->SetMinimumPaneSize( 50 );
     ////
    splitterWindowVerticalSizer->Add( imageDetailsSplitterWindow, 1, wxGROW | wxALL, 5 );

    // album Image Layout Panel
    wxPanel* albumImageLayoutPanel = CreateAlbumImageLayoutPanel( imageDetailsSplitterWindow );

    m_detailsScrolledWindow = CreateDetailsScrolledWindow( imageDetailsSplitterWindow );
    imageDetailsSplitterWindow->SplitHorizontally( albumImageLayoutPanel, m_detailsScrolledWindow, 550 );
    return imageDetailsSplitterWindow;
}

wxPanel* AlbumPanel::CreateDetailsScrolledWindow( wxWindow* parent )
{
    wxPanel* detailsScrolledWindow = new wxPanel( parent, ID_DETAILSSCROLLEDWINDOW,
        wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER );

    // wxScrolledWindow* detailsScrolledWindow = new wxScrolledWindow( parent, ID_DETAILSSCROLLEDWINDOW, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );
     //detailsScrolledWindow->SetScrollbars( 1, 1, 0, 0 );

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer( wxVERTICAL );
    detailsScrolledWindow->SetSizer( itemBoxSizer7 );

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer7->Add( itemBoxSizer8, 1, wxGROW | wxALL, 5 );

    m_albumDetailsPanel = new AlbumDetailsPanel( detailsScrolledWindow, 23150, "str", wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_albumDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer8->Add( m_albumDetailsPanel, 1, wxGROW | wxALL, 0 );

    m_pageDetailsPanel = new PageDetailsPanel( detailsScrolledWindow, 23251, "str", wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_pageDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer8->Add( m_pageDetailsPanel, 1, wxGROW | wxALL, 0 );

    m_colDetailsPanel = new ColDetailsPanel( detailsScrolledWindow, 23352, "str", wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_colDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer8->Add( m_colDetailsPanel, 1, wxGROW | wxALL, 0 );

    m_rowDetailsPanel = new RowDetailsPanel( detailsScrolledWindow, 23353, "str", wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_rowDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer8->Add( m_rowDetailsPanel, 1, wxGROW | wxALL, 0 );

    m_stampDetailsPanel = new StampDetailsPanel( detailsScrolledWindow, 25454, "str", wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    m_stampDetailsPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    itemBoxSizer8->Add( m_stampDetailsPanel, 1, wxGROW | wxALL, 0 );

    m_albumDetailsPanel->Hide( );
    m_pageDetailsPanel->Hide( );
    m_colDetailsPanel->Hide( );
    m_rowDetailsPanel->Hide( );
    m_stampDetailsPanel->Hide( );

    Layout( );

    return detailsScrolledWindow;
}
void AlbumPanel::ShowDetails( Design::AlbumBase* albumBase )
{
    Design::AlbumBaseType type = albumBase->GetNodeType( );
    m_albumDetailsPanel->Hide( );
    m_pageDetailsPanel->Hide( );
    m_colDetailsPanel->Hide( );
    m_rowDetailsPanel->Hide( );
    m_stampDetailsPanel->Hide( );
    // m_testDetailsPanel->Hide( );

    switch ( type )
    {
        case   Design::AT_Album:
        {
            Design::Album* album = ( Design::Album* ) albumBase;
            m_albumDetailsPanel->SetupDialog( album );
            m_albumDetailsPanel->Show( );
            m_albumDetailsPanel->GetParent( )->Layout( );
        }
        break;
        case   Design::AT_Page:
        {
            Design::Page* page = ( Design::Page* ) albumBase;
            m_pageDetailsPanel->SetupDialog( page );
            m_pageDetailsPanel->Show( );
            m_pageDetailsPanel->GetParent( )->Layout( );
        }
        break;
        case   Design::AT_Row:
        {
            Design::Row* row = ( Design::Row* ) albumBase;
            m_rowDetailsPanel->SetupDialog( row );
            m_rowDetailsPanel->Show( );
            m_rowDetailsPanel->GetParent( )->Layout( );

            //m_testDetailsPanel->SetupDialog( );
            //m_testDetailsPanel->Show( );

            // m_testDetailsPanel->GetParent( )->Refresh( );
            //m_testDetailsPanel->GetParent( )->Layout( );
            //m_testDetailsPanel->GetParent( )->SetFocus( );
        }
        break;
        case   Design::AT_Col:
        {
            Design::Column* col = ( Design::Column* ) albumBase;
            m_colDetailsPanel->SetupDialog( col );
            m_colDetailsPanel->Show( );
            m_colDetailsPanel->GetParent( )->Layout( );
        }
        break;
        // case  AT_Text,
       // /* code */
       //  break;
        case   Design::AT_Stamp:
        {
            Design::Stamp* stamp = ( Design::Stamp* ) albumBase;
            m_stampDetailsPanel->SetupDialog( stamp );
            m_stampDetailsPanel->Show( );
            m_stampDetailsPanel->GetParent( )->Layout( );
        }
        break;
        // case  /* constant-expression */:
        //     /* code */
        //     break;

        default:
        // Design::Stamp* stamp = ( Design::Stamp* ) albumBase;
        break;
    }
}

wxPanel* AlbumPanel::CreateAlbumImageLayoutPanel( wxWindow* parent )
{
    wxPanel* albumImageLayoutPanel =
        new wxPanel( parent, ID_STAMPDESCRIPTIONPANEL, wxDefaultPosition,
            wxDefaultSize, wxTAB_TRAVERSAL );
    albumImageLayoutPanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer( wxVERTICAL );
    albumImageLayoutPanel->SetSizer( itemBoxSizer5 );

    wxBoxSizer* imagePanelHorizontalalSizer = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer5->Add( imagePanelHorizontalalSizer, 1, wxGROW | wxALL, 5 );

    wxBoxSizer* imagePanelVerticalSizer = new wxBoxSizer( wxVERTICAL );
    imagePanelHorizontalalSizer->Add( imagePanelVerticalSizer, 1, wxGROW | wxALL, 5 );
    wxBoxSizer* zoomHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    imagePanelVerticalSizer->Add( zoomHorizontalSizer, 0, wxGROW | wxALL, 0 );

    wxStaticText* zoomStatic = new wxStaticText(
        albumImageLayoutPanel, wxID_STATIC, _( "Zoom" ), wxDefaultPosition, wxDefaultSize, 0 );
    zoomHorizontalSizer->Add( zoomStatic, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_zoomSlider =
        new wxSlider( albumImageLayoutPanel, ID_ALBUMZOOMSLIDER, 50, 10, 100, wxDefaultPosition,
            wxDefaultSize, wxSL_HORIZONTAL );
    zoomHorizontalSizer->Add( m_zoomSlider, 2, wxGROW | wxALL, 0 );

    m_albumImagePanel =
        new AlbumImagePanel( albumImageLayoutPanel, ID_ALBUMALBUMIMAGEPANEL, wxDefaultPosition,
            wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL | wxFULL_REPAINT_ON_RESIZE | wxHSCROLL | wxVSCROLL );

    m_albumImagePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );

    imagePanelVerticalSizer->Add( m_albumImagePanel, 1, wxGROW | wxALL, 0 );

    m_albumImagePanel->SetScrollbars( 3, 3, 400, 400, 0, 0 );

    return albumImageLayoutPanel;
}
//--------------

void AlbumPanel::Init( )
{
    m_albumVerticalSplitterWindow = NULL;

}

//--------------

// void AlbumPanel::OnAlbumChoiceSelected( wxCommandEvent& event )
// {
//     int sel = m_albumListCtrl->GetSelection( );

//     GetAlbumData( )->GetAlbumList( ).

//     GetCatalogData( )->GetCatalogTreeCtrl( )->SetStates( true );
//     GetCatalogData( )->GetCatalogTreeCtrl( )->LoadTree( );

//     event.Skip( );

// }

//--------------

void AlbumPanel::OnZoomsliderUpdated( wxCommandEvent& event )
{
    int val = m_zoomSlider->GetValue( );
    double zoom = ( double ) val / 100.0;
    m_albumImagePanel->SetZoom( zoom );

    event.Skip( );
}

//--------------

void AlbumPanel::OnManageClick( wxCommandEvent& event )
{

    wxMenu m_designMenu;
    m_designMenu.Append( ID_NEWDESIGN, _( "New Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_OPENDESIGN, _( "Open Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_GENERATEPDF, _( "Generate PDF Album" ), wxEmptyString, wxITEM_NORMAL );

    switch ( GetPopupMenuSelectionFromUser( m_designMenu ) )
    {
        case ID_NEWDESIGN:
        {
            NewDesign( );
            break;
        }
        case ID_OPENDESIGN:
        {
            OpenDesign( );
            break;
        }

        case ID_GENERATEPDF:
        {
            break;
        }
    }
}



//GUI interface for creating new design
void AlbumPanel::NewDesign( )
{
    Design::AlbumVolume* vol = GetAlbumVolume( );

    if ( vol && !vol->ContinueIfDirty( this ) )
    {
        return;
    }
    FileCreateDialog fileDialog( this, 12355, _( "Select the Filename and Directory for the Design file." ) );
    wxGetCwd( );
    fileDialog.SetDefaultDirectory( wxGetCwd( ) );
    fileDialog.SetDefaultFilename( _( "unnamed.alb" ) );
    fileDialog.SetWildCard( _( "Album Design files(*.alb)|*.alb" ) );

    if ( fileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return;
    }
    wxString cwd = wxGetCwd( );
    wxFileName designFile( fileDialog.GetPath( ) );
    designFile.MakeRelativeTo( cwd );
    GetAlbumData( )->LoadNew( designFile.GetFullPath( ) );
    //vol->SetDirty( true );

}

void AlbumPanel::OpenDesign( )
{

    wxString path = wxGetCwd( );

    wxFileDialog openFileDialog(
        this, _( "Open Album Design file" ),
        path, "",
        "Album Design files(*.alb)|*.alb", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return; // the user changed idea...
    }

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxString filename = openFileDialog.GetPath( );

    GetAlbumData( )->FileOpen( filename );
}

void AlbumPanel::SaveAsDesign( )
{
    if ( GetAlbumVolume( ) )
    {
        Design::AlbumVolume* vol = GetAlbumData( )->GetAlbumVolume( );
        wxString filename = "";
        if ( vol )
        {
            filename = vol->GetFilename( );
        }

        wxFileName lastFile( filename );
        lastFile.SetExt( "alb" );
        wxFileDialog saveFileDialog(
            this, _( "Album Design file" ),
            lastFile.GetPath( ), lastFile.GetFullName( ),
            "Album Design files (*.alb)|*.alb", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
        if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
            return;

        wxString newPath = saveFileDialog.GetPath( );
        GetAlbumData( )->FileSaveAs( newPath );
    }
}

//--------------

void AlbumPanel::OnGeneratePDFClick( wxCommandEvent& event )
{
    GetAlbumData( )->GetAlbumVolume( )->GetAlbum( )->MakePDFAlbum( );
}

//--------------

bool AlbumPanel::ShowToolTips( )
{
    return true;
}