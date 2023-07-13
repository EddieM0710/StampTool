/**
 * @file StampToolFrame.cpp
 * @author Eddie Monroe ( )
 * @brief This is the application main frame.
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
 *
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif



#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/filedlg.h> 
#include <wx/log.h>
#include <wx/wfstream.h>

#include "Defs.h"
#include "Settings.h"

#include "gui/StampToolPanel.h"
#include "gui/CatalogPanel.h"
#include "gui/AlbumPanel.h"
#include "catalog/CatalogData.h"
#include "design/AlbumData.h"
 //#include "gui/DefinePeriodsDialog.h"
#include "gui/AlbumTreePanel.h"
#include "gui/SortOrderPanel.h"
#include "gui/SettingsDialog.h"
#include "gui/FileCreateDialog.h"
#include "gui/StampToolFrame.h"
#include "gui/AlbumImagePanel.h"


#include "catalog/CatalogVolume.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"


#include "utils/Project.h"
#include "utils/CSV.h"
#include "utils/XMLUtilities.h"
#include "catalog/Entry.h"
#include "catalog/CatalogVolume.h"
#include "design/AlbumData.h"


#include "design/DesignDefs.h"
#include "design/AlbumVolume.h"
#include "design/AlbumBase.h"
#include "design/Album.h"
#include "design/Stamp.h"


IMPLEMENT_CLASS( StampToolFrame, wxFrame )

BEGIN_EVENT_TABLE( StampToolFrame, wxFrame )
EVT_CLOSE( StampToolFrame::OnCloseWindow )
EVT_ICONIZE( StampToolFrame::OnIconize )
EVT_MAXIMIZE( StampToolFrame::OnMaximize )
EVT_MENU( ID_NEWPROJECT, StampToolFrame::OnNewProjectClick )
EVT_MENU( ID_OPENPROJECT, StampToolFrame::OnOpenProjectClick )
EVT_MENU( ID_SAVEPROJECT, StampToolFrame::OnSaveProjectClick )
EVT_MENU( ID_SAVEASPROJECT, StampToolFrame::OnSaveasProjectClick )
EVT_MENU( wxID_EXIT, StampToolFrame::OnExitClick )
EVT_MENU( ID_TEXTSERCHMENUITEM, StampToolFrame::OnTextSearchMenuItemClick )
EVT_MENU( ID_SORTORDER, StampToolFrame::OnSortOrderClick )
EVT_MENU( ID_ITEMVIEW, StampToolFrame::OnItemviewClick )
EVT_MENU( ID_DEFINEPERIOD, StampToolFrame::OnDefinePeriodClick )
EVT_MENU( ID_SETTINGS, StampToolFrame::OnSettingsClick )
EVT_MENU( ID_NEWCATALOG, StampToolFrame::OnNewCatalogClick )
EVT_MENU( ID_OPENCATALOG, StampToolFrame::OnOpenCatalogClick )
EVT_MENU( ID_CSVIMPORT, StampToolFrame::OnImportCatalogClick )
EVT_MENU( ID_REMOVECATALOG, StampToolFrame::OnRemoveCatalogClick )
EVT_MENU( ID_NEWDESIGN, StampToolFrame::OnNewDesignClick )
EVT_MENU( ID_OPENDESIGN, StampToolFrame::OnOpenDesignClick )
EVT_MENU( ID_GENERATEPDF, StampToolFrame::OnGeneratePDFClick )
EVT_MENU( ID_OPENPDF, StampToolFrame::OnOpenPDFClick )
EVT_MENU( ID_REMOVEDESIGN, StampToolFrame::OnRemoveDesignClick )
END_EVENT_TABLE( )


StampToolFrame::StampToolFrame( )
{
    Init( );
}


void StampToolFrame::InitLoad( )
{
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    {
        GetProject( )->LoadProjectXML( );
        GetProject( )->LoadData( );
    }
}



StampToolFrame::StampToolFrame( wxWindow* parent, wxWindowID id,
    const wxString& caption,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );

}


bool StampToolFrame::Create( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos,
    const wxSize& size, long style )
{

    wxFrame::Create( parent, id, caption, pos, size, style );

    this->SetFont( wxFont( 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL, false, wxT( "Ubuntu" ) ) );
    CreateControls( );
    Centre( );

    return true;
}


StampToolFrame::~StampToolFrame( )
{

}

void StampToolFrame::Init( )
{
    //    m_stamp = new Catalog::Stamp( );
    m_stampToolPanel = NULL;


    // m_settings = new Utils::Settings( );
    // m_project = new Utils::Project( );
    // m_StampAlbumCatalogLink = new Utils::StampList( );

    // m_project->InitProject( );
    // m_settings->InitSettings( );

    // if ( m_settings->GetLoadLastFileAtStartUp( ) )
    // {
    //     m_project->SetProjectFilename( m_settings->GetLastFile( ) );
    // }

}



void StampToolFrame::CreateControls( )
{
    //   std::cout << "StampToolFrame" << "\n";

    StampToolFrame* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    m_fileMenu = new wxMenu;
    m_newMenu = new wxMenu;
    m_fileMenu->Append( ID_NEWPROJECT, _( "New" ), "New Project", wxITEM_NORMAL );
    m_fileMenu->Append( ID_OPENPROJECT, _( "Open" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->AppendSeparator( );
    m_fileMenu->Append( ID_SAVEPROJECT, _( "Save" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_SAVEASPROJECT, _( "Save As" ), wxEmptyString, wxITEM_NORMAL );

    m_fileMenu->AppendSeparator( );
    m_fileMenu->Append( ID_SETTINGS, _( "Preferences" ), wxEmptyString, wxITEM_NORMAL );

    m_fileMenu->AppendSeparator( );

    m_fileMenu->Append( ID_OPENCATALOG, _( "Open Catalog" ), wxEmptyString, wxITEM_NORMAL );

    m_fileMenu->AppendSeparator( );

    m_fileMenu->Append( wxID_EXIT, _( "Exit" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( m_fileMenu, _( "Project" ) );

    wxMenu* itemMenu5 = new wxMenu;

    itemMenu5->Append( ID_ADDCOLLECTION, _( "Add Collection File" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu5->Append( ID_OPENCOLLECTION, _( "Open Collection File" ), wxEmptyString, wxITEM_NORMAL );


    wxMenu* itemMenu3 = new wxMenu;
    //itemMenu3->Append( ID_TEXTSERCHMENUITEM, _( "Text Search" ), wxEmptyString, wxITEM_NORMAL );

    itemMenu3->Append( ID_NEWCATALOG, _( "New Catalog" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu3->Append( ID_OPENCATALOG, _( "Open Catalog" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu3->Append( ID_CSVIMPORT, _( "Import Catalog From CSV file" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu3->Append( ID_REMOVECATALOG, _( "Remove Catalog" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu3->Append( ID_SAVECATALOG, _( "Save Catalog" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu3, _( "Catalog" ) );

    wxMenu* itemMenu4 = new wxMenu;

    itemMenu4->Append( ID_NEWDESIGN, _( "New Album" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu4->Append( ID_OPENDESIGN, _( "Open Album" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu4->Append( ID_GENERATEPDF, _( "Generate Album PDF" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu4->Append( ID_OPENPDF, _( "Open PDF" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu4->Append( ID_REMOVEDESIGN, _( "Remove Album" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu4->Append( ID_SAVEDESIGN, _( "Save Album" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu4, _( "Album" ) );

    wxMenu* itemMenu7 = new wxMenu;
    itemMenu7->Append( wxID_ABOUT, _( "About" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu7, _( "Help" ) );
    itemFrame1->SetMenuBar( menuBar );

    wxGridSizer* itemGridSizer1 = new wxGridSizer( 1, 1, 0, 0 );
    itemFrame1->SetSizer( itemGridSizer1 );

    m_stampToolPanel = new StampToolPanel(
        itemFrame1, ID_STAMPTOOLPANELFOREIGN, wxDefaultPosition,
        wxSize( 100, 100 ), wxSIMPLE_BORDER );
    itemGridSizer1->Add( m_stampToolPanel, 1, wxGROW | wxALL, 0 );

    m_albumTreePanel = m_stampToolPanel->GetAlbumTreePanel( );
}

CatalogPanel* StampToolFrame::GetCatalogPagePanel( )
{
    return m_stampToolPanel->GetCatalogPagePanel( );
}


AlbumPanel* StampToolFrame::GetAlbumPanel( )
{
    return m_stampToolPanel->GetAlbumPanel( );
}

bool StampToolFrame::ShowToolTips( )
{
    return true;
}


int StampToolFrame::DoQueryMerge( int& mergeMethod )
{
    wxXmlNode* docRoot = 0;
    int mergeOverwriteQuery;

    Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
    if ( catalogVolume )
    {
        mergeOverwriteQuery = QueryMerge( mergeMethod );
    }
    else
    {
        mergeOverwriteQuery = Catalog::MO_Cancel;
    }
    return mergeOverwriteQuery;
}


void StampToolFrame::DoRecentSelection( wxCommandEvent& event )
{

    int mergeMethod;
    int mergeOverwriteQuery = DoQueryMerge( mergeMethod );
    if ( mergeOverwriteQuery == Catalog::MO_Cancel )
    {
        return;
    }

    // the id was calculated as ID_RECENT + ndx + 1, so...
    int id = event.GetId( );
    int rcnt = ID_RECENT;
    int ndx = event.GetId( ) - rcnt - 1;
    wxArrayString* recentList = GetSettings( )->GetRecentArray( );
    wxString filename = recentList->Item( ndx );
    wxFileInputStream input_stream( filename );
    if ( !input_stream.IsOk( ) )
    {
        wxLogError( "StampToolFrame::DoRecentSelection Cannot open file '%s'.", filename );
        return;
    }

    //    m_catalogPanel->LoadCatalog( );


    event.Skip( );
}



void StampToolFrame::DoDefinePeriodDialog( )
{
    // DefinePeriodsDialog definePeriodsDialog( this, ID_DEFINEPERIODSDIALOG,  _( "Define Periods Order" ) );

    // if ( definePeriodsDialog.ShowModal( ) == wxID_CANCEL )
    //     return; // the user changed idea..

    // if ( definePeriodsDialog.IsDirty( ) )
    // { 
    //     // Save settings
    //     // resort tree
    // }
}


void StampToolFrame::OnNewProjectClick( wxCommandEvent& event )
{
    NewProject( );
    event.Skip( );
}

void StampToolFrame::OnOpenProjectClick( wxCommandEvent& event )
{
    OpenProject( );
    event.Skip( );
}

void StampToolFrame::OnSaveProjectClick( wxCommandEvent& event )
{
    GetProject( )->FileSaveProject( );
    event.Skip( );
}

// void StampToolFrame::OnSaveDesignClick( wxCommandEvent& event )
// {
//     GetAlbumData( )->FileSave( );
//     event.Skip( );
// }

void StampToolFrame::OnExitClick( wxCommandEvent& event )
{
    GetSettings( )->Save( );
    Close( );
    event.Skip( );
}

void StampToolFrame::OnSaveasProjectClick( wxCommandEvent& event )
{
    SaveAsProject( );
    event.Skip( );
}

void StampToolFrame::OnCloseWindow( wxCloseEvent& event )
{
    event.Skip( );
}



void StampToolFrame::OnDefinePeriodClick( wxCommandEvent& event )
{
    DoDefinePeriodDialog( );
    event.Skip( );
}

void StampToolFrame::OnIconize( wxIconizeEvent& event )
{
    event.Skip( );
}



void StampToolFrame::OnItemviewClick( wxCommandEvent& event )
{
    event.Skip( );
}


void StampToolFrame::OnMaximize( wxMaximizeEvent& event )
{
    event.Skip( );
}


void StampToolFrame::OnMergeClick( wxCommandEvent& event )
{
    event.Skip( );
}

// void StampToolFrame::OnGeneratePDFClick( wxCommandEvent& event )
// {
//     //AlbumImagePanel*
//     GetAlbumVolume( )->GetAlbum( )->MakePDFAlbum( );
// }
void StampToolFrame::OnSettingsClick( wxCommandEvent& event )
{
    DoSettingsDialog( );
    event.Skip( );
}

void StampToolFrame::OnOpenCatalogClick( wxCommandEvent& event )
{
    GetCatalogPagePanel( )->OpenCatalog( );
    event.Skip( );
}
void StampToolFrame::OnNewCatalogClick( wxCommandEvent& event )
{
    GetCatalogPagePanel( )->NewCatalogDialog( );
    event.Skip( );
}

void StampToolFrame::OnImportCatalogClick( wxCommandEvent& event )
{
    GetCatalogPagePanel( )->DoCSVImport( );
    event.Skip( );
}

void StampToolFrame::OnRemoveCatalogClick( wxCommandEvent& event )
{
    GetCatalogPagePanel( )->RemoveVolume( );
    event.Skip( );
}
void StampToolFrame::OnNewDesignClick( wxCommandEvent& event )
{
    GetAlbumPanel( )->NewDesign( );
    event.Skip( );
}
void StampToolFrame::OnOpenDesignClick( wxCommandEvent& event )
{
    GetAlbumPanel( )->OpenDesign( );
    event.Skip( );
}

void StampToolFrame::OnGeneratePDFClick( wxCommandEvent& event )
{
    GetAlbumVolume( )->GetAlbum( )->MakePDFAlbum( );
    //GetAlbumPanel( )->OnGeneratePDFClick( );
    event.Skip( );
}

void StampToolFrame::OnOpenPDFClick( wxCommandEvent& event )
{
    OpenPdf( );
    event.Skip( );
}


void StampToolFrame::OnRemoveDesignClick( wxCommandEvent& event )
{
    GetCatalogPagePanel( )->RemoveVolume( );
    event.Skip( );
}
void StampToolFrame::DoSettingsDialog( )
{
    SettingsDialog settingsDialog( this, ID_SETTINGSDIALOG,
        _( "Define Preferences" ) );

    if ( settingsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( settingsDialog.IsDirty( ) )
    {
        // Save settings
        // resort tree
    }
}

void StampToolFrame::DoSortOrderDialog( )
{
    //     SortOrderDialog sortOrderDialog( this, ID_SORTORDERDIALOG, 
    //         _( "Define Sort Order" ) );

    //     if ( sortOrderDialog.ShowModal( ) == wxID_CANCEL )
    //         return; // the user changed idea..

    //     if ( sortOrderDialog.IsDirty( ) )
    //     { 
    //         // Save settings
    //         // resort tree
    //     }
}


void StampToolFrame::OnSortOrderClick( wxCommandEvent& event )
{
    DoSortOrderDialog( );
    event.Skip( );
}



void StampToolFrame::OnTextSearchMenuItemClick( wxCommandEvent& event )
{
    event.Skip( );
}

void StampToolFrame::NewProject( )
{

    if ( IsDirty( ) )
    {
        // query whether to save first 
        wxMessageDialog* dlg = new wxMessageDialog(
            this,
            wxT( "The current data has been changed but not saved. \n"\
                "Select \"OK\" to close the file losing the changes.\n"\
                "Or select \"Cancel\" to quit file open process.\n" ),
            wxT( "Warning! Unsaved modifications.\n" ),
            wxOK | wxCANCEL | wxCENTER );
        int rsp = dlg->ShowModal( );
        if ( rsp == wxID_CANCEL )
        {
            return;
        }
    }

    FileCreateDialog fileDialog( this, 12355, _( "Select the Filename and Directory for the Project file." ) );
    wxGetCwd( );
    fileDialog.SetDefaultDirectory( wxGetCwd( ) );
    fileDialog.SetDefaultFilename( _( "unnamed.spt" ) );
    fileDialog.SetWildCard( _( "Stamp Tools Project files(*.spt)|*.spt" ) );

    if ( fileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return;
    }
    wxString dir = fileDialog.GetDir( );
    wxSetWorkingDirectory( dir );

    GetProject( )->FileNewProject( fileDialog.GetFile( ) );
}


void StampToolFrame::OpenProject( )
{

    if ( IsDirty( ) )
    {
        // query whether to save first 
        wxMessageDialog* dlg = new wxMessageDialog(
            this,
            wxT( "The current data has been changed but not saved. \n"\
                "Select \"OK\" to close the file losing the changes.\n"\
                "Or select \"Cancel\" to quit file open process.\n" ),
            wxT( "Warning! Unsaved modifications.\n" ),
            wxOK | wxCANCEL | wxCENTER );
        int rsp = dlg->ShowModal( );
        if ( rsp == wxID_CANCEL )
        {
            return;
        }
    };
    wxFileName lastFile( GetSettings( )->GetLastFile( ) );
    lastFile.SetExt( "xml" );
    wxFileDialog openFileDialog(
        this, _( "Open Stamp Tools Project file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "Stamp Tools Project files (*.spt)|*.spt",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return; // the user changed idea...
    }

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxString filename = openFileDialog.GetPath( );

    wxFileInputStream input_stream( filename );
    if ( !input_stream.IsOk( ) )
    {
        wxLogError( "StampToolFrame::OpenProject Cannot open file '%s'.", filename );
        return;
    }


    GetProject( )->FileOpenProject( filename );

}


void StampToolFrame::OpenPdf( )
{

    wxFileName lastFile( GetSettings( )->GetLastFile( ) );
    lastFile.SetExt( "pdf" );
    wxFileDialog openFileDialog(
        this, _( "Open PDF file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "PDF files (*.pdf)|*.pdf",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return; // the user changed idea...
    }

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxString filename = openFileDialog.GetPath( );

    wxFileInputStream input_stream( filename );
    if ( !input_stream.IsOk( ) )
    {
        wxLogError( "StampToolFrame::OpenPdf Cannot open file '%s'.", filename );
        return;
    }

    GetStampToolPanel( )->OnPDF( filename );

}


int StampToolFrame::QueryMerge( int& mergeMethod )
{
    const wxString choices[ ] = { "Merge", "Overwrite" };

    wxSingleChoiceDialog dialog(
        this,
        "Data already exists\n"
        "What do you want to do with the existing data?",
        "Please select a value", WXSIZEOF( choices ), choices, NULL,
        wxDEFAULT_DIALOG_STYLE | wxOK | wxCANCEL | wxCENTRE );

    if ( dialog.ShowModal( ) == wxID_OK )
    {
        int sel = dialog.GetSelection( );
        if ( sel == 1 ) // overwrite
        {
            return Catalog::MO_Overwrite;
        }
        else // merge
        {
            const wxString DispositionChoices[ ] = {
                "Add missing entries only.",
                "Add missing entries and missing fields in existing entries",
                "Add missing entries and overwrite exixting fields in existing "
                "entries",
                "Add missing entries and query if fields differ.", "Query All." };

            wxSingleChoiceDialog dispositionDialog(
                this,
                "Merging Data\n"
                "What do you want to do with the incoming data?",
                "Please select a value", WXSIZEOF( DispositionChoices ),
                DispositionChoices, NULL,
                wxDEFAULT_DIALOG_STYLE | wxOK | wxCANCEL | wxCENTRE );

            if ( dispositionDialog.ShowModal( ) == wxID_OK )
            {
                mergeMethod = dispositionDialog.GetSelection( );
                return Catalog::MO_Merge;
            }
            else
            {
                return Catalog::MO_Cancel;
            }
        }
    }
    else
    {
        return Catalog::MO_Cancel;
    }
}

void StampToolFrame::SaveAsProject( )
{
    wxFileName lastFile( GetSettings( )->GetLastFile( ) );
    lastFile.SetExt( "spt" );
    wxFileDialog saveFileDialog(
        this, _( "StampTool Project spt file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "Stamp Tool Project files(*.spt)|*.spt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
    if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
        return;

    wxString filename = saveFileDialog.GetPath( );
    GetProject( )->FileSaveAsProject( filename );
}


void StampToolFrame::SetupRecentMenu( )
{
    // // first clobber each of the current menuItems and unbind them.
    // if ( m_menuItemList.size( ) > 0 )
    // { 
    //     for ( int i = 0; i < m_menuItemList.size( ); i++ )
    //     { 
    //         RecentListItem* item = m_menuItemList[ i ];
    //         bool val = Unbind(  MENU, &StampToolFrame::DoRecentSelection, this, item->id );
    //         m_recentMenu->Delete( item->item );
    //         //  item->item->~wxMenuItem( );
    //     }
    //     m_menuItemList.clear( ); // then clobber the list
    // }
    // // then create all the new menuItems and bind them
    // wxArrayString* recentList = GetSettings( )->GetRecentArray( );
    // int cnt = 0;
    // for ( int i = 0; i < recentList->Count( ); i++ )
    // { 
    //     RecentListItem* listItem = new RecentListItem( );
    //     listItem->id = ID_RECENT + i + 1;
    //     wxString item = recentList->Item( i );
    //     if ( item.length( ) > 0 )
    //     { 
    //         cnt++;
    //         listItem->item = m_recentMenu->Append( listItem->id, item, wxEmptyString, wxITEM_NORMAL );

    //         Bind(  MENU, &StampToolFrame::DoRecentSelection, this, listItem->id );
    //         m_menuItemList.push_back( listItem );
    //     }
    // }
    // if ( cnt > 0 )
    // { 
    //     m_fileMenu->Enable( ID_RECENT, true );
    // }
    // else
    // { 
    //     m_fileMenu->Enable( ID_RECENT, false );
    // }
}





void StampToolFrame::UpdateStatus( ) { m_stampToolPanel->UpdateStatus( ); }


