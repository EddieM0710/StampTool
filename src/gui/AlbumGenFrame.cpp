/**
 * @file AlbumGenFrame.cpp
 * @author Eddie Monroe ()
 * @brief This is the application main frame.
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "gui/AlbumGenPanel.h"
#include "gui/CatalogPanel.h"
#include "gui/DefinePeriodsDialog.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/wfstream.h>

#include "utils/CSV.h"
#include "catalog/Classification.h"
#include "catalog/Entry.h"
#include "Defs.h"
#include "Settings.h"
#include "utils/Project.h"
#include "gui/AlbumPanel.h"
#include "gui/SortOrderDialog.h"
#include "gui/SettingsDialog.h"
#include "catalog/CatalogData.h"
#include "gui/AlbumGenFrame.h"
#include "utils/XMLUtilities.h"
#include "design/DesignDefs.h"
#include "design/DesignData.h"
#include "design/AlbumBase.h"
#include "design/Album.h"
#include "design/Stamp.h"

//#include <curl/curl.h>

/*
 * AlbumGenFrame type definition
 */

IMPLEMENT_CLASS( AlbumGenFrame, wxFrame )
; // silly business; The above macro screws up the formatter

/*
 * AlbumGenFrame event table definition
 */

BEGIN_EVENT_TABLE( AlbumGenFrame, wxFrame )

// AlbumGenFrame event table entries
EVT_CLOSE( AlbumGenFrame::OnCloseWindow )
EVT_ICONIZE( AlbumGenFrame::OnIconize )
EVT_MAXIMIZE( AlbumGenFrame::OnMaximize )
EVT_MENU( ID_NEWPROJECT, AlbumGenFrame::OnNewProjectClick )
EVT_MENU( ID_NEWDESIGN, AlbumGenFrame::OnNewDesignClick )
EVT_MENU( ID_NEWCATALOG, AlbumGenFrame::OnNewCatalogClick )
EVT_MENU( ID_OPENPROJECT, AlbumGenFrame::OnOpenProjectClick )
EVT_MENU( ID_OPENDESIGN, AlbumGenFrame::OnOpenDesignClick )
EVT_MENU( ID_OPENCATALOG, AlbumGenFrame::OnOpenCatalogClick )
EVT_MENU( ID_SAVEPROJECT, AlbumGenFrame::OnSaveProjectClick )
EVT_MENU( ID_SAVEDESIGN, AlbumGenFrame::OnSaveDesignClick )
EVT_MENU( ID_SAVECATALOG, AlbumGenFrame::OnSaveCatalogClick )
EVT_MENU( ID_SAVEASPROJECT, AlbumGenFrame::OnSaveasProjectClick )
EVT_MENU( ID_SAVEASDESIGN, AlbumGenFrame::OnSaveasDesignClick )
EVT_MENU( ID_SAVEASCATALOG, AlbumGenFrame::OnSaveasCatalogClick )
EVT_MENU( ID_GENERATEODT, AlbumGenFrame::OnGenerateODTClick )
EVT_MENU( ID_CSVIMPORT, AlbumGenFrame::OnCSVImportClick )
//EVT_MENU( ID_MERGE, AlbumGenFrame::OnCSVImportClick )
EVT_MENU( wxID_EXIT, AlbumGenFrame::OnExitClick )
EVT_MENU( ID_TEXTSERCHMENUITEM, AlbumGenFrame::OnTextserchmenuitemClick )
EVT_MENU( ID_SORTORDER, AlbumGenFrame::OnSortOrderClick )
EVT_MENU( ID_ITEMVIEW, AlbumGenFrame::OnItemviewClick )
EVT_MENU( ID_DEFINEPERIOD, AlbumGenFrame::OnDefineperiodClick )
EVT_MENU( ID_SETTINGS, AlbumGenFrame::OnSettingsClick )
// AlbumGenFrame event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter




AlbumGenFrame::AlbumGenFrame( )
{
    Init( );
}


void AlbumGenFrame::InitLoad( )
{
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    {
        GetProject( )->LoadProjectXML( );
        GetGeneratorData( )->LoadData( );
    }
}



AlbumGenFrame::AlbumGenFrame( wxWindow* parent, wxWindowID id,
    const wxString& caption,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}


bool AlbumGenFrame::Create( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos,
    const wxSize& size, long style )
{
    // AlbumGenFrame creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    this->SetFont( wxFont( 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL, false, wxT( "Ubuntu" ) ) );
    CreateControls( );
    Centre( );
    // AlbumGenFrame creation
    return true;
}


AlbumGenFrame::~AlbumGenFrame( )
{

}

/*
 * Member initialisation
 */

void AlbumGenFrame::Init( )
{
    //    m_stamp = new Catalog::Stamp( );
    m_albumGeneratorPanel = NULL;
    m_catalogPanel = NULL;
}

/*
 * Control creation for AlbumGenFrame
 */

void AlbumGenFrame::CreateControls( )
{
    // AlbumGenFrame content construction

    AlbumGenFrame* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    m_fileMenu = new wxMenu;
    m_newMenu = new wxMenu;
    m_fileMenu->Append( ID_NEWPROJECT, _( "New Project File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_OPENPROJECT, _( "Open Project File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->AppendSeparator( );
    m_fileMenu->Append( ID_SAVEPROJECT, _( "Save Project File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_SAVEASPROJECT, _( "Save Project File As" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->AppendSeparator( );

    wxMenu* m_catalogMenu = new wxMenu;
     
    m_catalogMenu->Append( ID_NEWCATALOG, _( "New Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_catalogMenu->Append( ID_OPENCATALOG, _( "Open Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_catalogMenu->Append( ID_SAVECATALOG, _( "Save Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_catalogMenu->Append( ID_SAVEASCATALOG, _( "Save Catalog File As" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_CATALOGMENU, _( "Catalog" ), m_catalogMenu );


    wxMenu* m_designMenu = new wxMenu;
    m_designMenu->Append( ID_NEWDESIGN, _( "New Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu->Append( ID_OPENDESIGN, _( "Open Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu->Append( ID_SAVEDESIGN, _( "Save Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu->Append( ID_SAVEASDESIGN, _( "SaveAs Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_DESIGNMENU, _( "Design" ), m_designMenu );

    m_fileMenu->AppendSeparator( );
    m_fileMenu->Append( ID_GENERATEODT, _( "Generate ODT Album" ), wxEmptyString, wxITEM_NORMAL );

    m_fileMenu->AppendSeparator( );

    m_fileMenu->Append( ID_CSVIMPORT, _( "Import CSV" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_MERGE, _( "Merge" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->AppendSeparator( );
  //  m_recentMenu = new wxMenu;
  //  m_fileMenu->Append( ID_RECENT, _( "Recent" ), m_recentMenu );
    m_fileMenu->AppendSeparator( );
    m_preferencesMenu = new wxMenu;
    m_preferencesMenu->Append( ID_DEFINEPERIOD, _( "Define Period" ), wxEmptyString, wxITEM_NORMAL );
    m_preferencesMenu->Append( ID_SETTINGS, _( "Settings" ), wxEmptyString, wxITEM_NORMAL );
    m_preferencesMenu->Append( ID_SORTORDER, _( "Sort Order" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_PREFERENCES, _( "Preferences" ), m_preferencesMenu );
    m_fileMenu->AppendSeparator( );
    
    m_fileMenu->Append( wxID_EXIT, _( "Exit" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( m_fileMenu, _( "File" ) );
    wxMenu* itemMenu3 = new wxMenu;
    itemMenu3->Append( ID_TEXTSERCHMENUITEM, _( "Text Search" ), wxEmptyString, wxITEM_NORMAL );
    // itemMenu3->Append( ID_IMAGEGALERYMENUITEM, _( "Image Gallery" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu3, _( "Search" ) );

    wxMenu* itemMenu1 = new wxMenu;
    itemMenu1->Append( ID_SORTORDER, _( "Sort Order" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu1->Append( ID_ITEMVIEW, _( "Item View" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu1->Append( ID_DEFINEPERIOD, _( "Define Period" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu1, _( "Setup" ) );
    wxMenu* itemMenu7 = new wxMenu;
    itemMenu7->Append( wxID_ABOUT, _( "About" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu7, _( "Help" ) );
    itemFrame1->SetMenuBar( menuBar );

    wxGridSizer* itemGridSizer1 = new wxGridSizer( 1, 1, 0, 0 );
    itemFrame1->SetSizer( itemGridSizer1 );

    m_albumGeneratorPanel = new AlbumGenPanel(
        itemFrame1, ID_ALBUMGENERATORPANELFOREIGN, wxDefaultPosition,
        wxSize( 100, 100 ), wxSIMPLE_BORDER );
    itemGridSizer1->Add( m_albumGeneratorPanel, 1, wxGROW | wxALL, 0 );
    m_catalogPanel = m_albumGeneratorPanel->GetCatalogPanel( );
    m_albumPanel = m_albumGeneratorPanel->GetAlbumPanel( );
}


bool AlbumGenFrame::ShowToolTips( )
{
    return true;
}

wxBitmap AlbumGenFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    // AlbumGenFrame bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // AlbumGenFrame bitmap retrieval
}

wxIcon AlbumGenFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
    // AlbumGenFrame icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // AlbumGenFrame icon retrieval
}

int AlbumGenFrame::DoQueryMerge( int& mergeMethod )
{
    wxXmlNode* docRoot = 0;
    int mergeOverwriteQuery;

    Catalog::CatalogData* catalogData = GetCatalogData( );
    if ( catalogData )
    {
        mergeOverwriteQuery = QueryMerge( mergeMethod );
    }
    else
    {
        mergeOverwriteQuery = Catalog::MO_Cancel;
    }
    return mergeOverwriteQuery;
}

void AlbumGenFrame::DoRecentSelection( wxCommandEvent& event )
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
        wxLogError( "Cannot open file '%s'.", filename );
        return;
    }

    //    m_catalogPanel->LoadCatalog( );


    event.Skip( );
}


void AlbumGenFrame::DoCSVImport( )
{

    if ( IsDirty( ) )
    {
        // query whether to save first 
    }

    wxFileDialog openFileDialog(
        this, _( "Open Colnect CSV file" ),
        "", "",
        "CSV files (*.csv)|*.csv", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
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
        wxLogError( "Cannot open file '%s'.", filename );
        return;
    }

    GetGeneratorData()->ReadCatalogCSV( filename );
    GetGeneratorData()->LoadCatalogTree( );
    Dirty = true;
}

void AlbumGenFrame::DoDefinePeriodDialog( )
{
    DefinePeriodsDialog definePeriodsDialog( this, ID_DEFINEPERIODS,
        _( "Define Periods Order" ) );

    if ( definePeriodsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( definePeriodsDialog.IsDirty( ) )
    {
        // Save settings
        // resort tree
    }
}


void AlbumGenFrame::OnNewProjectClick( wxCommandEvent& event )
{
    NewProject( );
    event.Skip( );
}

void AlbumGenFrame::OnNewDesignClick( wxCommandEvent& event )
{
    NewDesign( );
    event.Skip( );
}
void AlbumGenFrame::OnNewCatalogClick( wxCommandEvent& event )
{
    NewCatalog( );
    event.Skip( );
}



void AlbumGenFrame::OnOpenProjectClick( wxCommandEvent& event )
{
    OpenProject( );
    event.Skip( );
}

void AlbumGenFrame::OnOpenDesignClick( wxCommandEvent& event )
{
    OpenDesign( );
    event.Skip( );
}
void AlbumGenFrame::OnOpenCatalogClick( wxCommandEvent& event )
{
    OpenCatalog( );
    event.Skip( );
}

void AlbumGenFrame::OnSaveProjectClick( wxCommandEvent& event )
{
    GetGeneratorData()->FileSaveProject( );
    event.Skip( );
}

void AlbumGenFrame::OnSaveDesignClick( wxCommandEvent& event )
{
    GetGeneratorData()->FileSaveDesign( );
    event.Skip( );
}
void AlbumGenFrame::OnSaveCatalogClick( wxCommandEvent& event )
{
    GetGeneratorData()->FileSaveCatalog( );
    event.Skip( );
}


void AlbumGenFrame::OnCSVImportClick( wxCommandEvent& event )
{
    DoCSVImport( );
    event.Skip( );
}

void AlbumGenFrame::OnExitClick( wxCommandEvent& event )
{
    Close( );
    event.Skip( );
}

void AlbumGenFrame::OnSaveasProjectClick( wxCommandEvent& event )
{
    SaveAsProject( );
    event.Skip( );
}

void AlbumGenFrame::OnCloseWindow( wxCloseEvent& event )
{
    event.Skip( );
}



void AlbumGenFrame::OnDefineperiodClick( wxCommandEvent& event )
{
    DoDefinePeriodDialog( );
    event.Skip( );
}

void AlbumGenFrame::OnIconize( wxIconizeEvent& event )
{
    event.Skip( );
}



void AlbumGenFrame::OnItemviewClick( wxCommandEvent& event )
{
    event.Skip( );
}


void AlbumGenFrame::OnMaximize( wxMaximizeEvent& event )
{
    event.Skip( );
}


void AlbumGenFrame::OnMergeClick( wxCommandEvent& event )
{
    event.Skip( );
}

void AlbumGenFrame::OnSaveasDesignClick( wxCommandEvent& event )
{
    SaveAsDesign( );
    event.Skip( );
}
void AlbumGenFrame::OnSaveasCatalogClick( wxCommandEvent& event )
{
    SaveAsCatalog( );
    event.Skip( );
}

void AlbumGenFrame::OnGenerateODTClick( wxCommandEvent& event )
{
    GenerateODTAlbum( );
    event.Skip( );
}

void AlbumGenFrame::OnSettingsClick( wxCommandEvent& event )
{
    DoSettingsDialog( );
    event.Skip( );
}

void AlbumGenFrame::DoSettingsDialog( )
{
    SettingsDialog settingsDialog( this, ID_SETTINGSDIALOG,
        _( "Define Sort Order" ) );

    if ( settingsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( settingsDialog.IsDirty( ) )
    {
        // Save settings
        // resort tree
    }
}

void AlbumGenFrame::DoSortOrderDialog( )
{
    SortOrderDialog sortOrderDialog( this, ID_SORTORDERDIALOG,
        _( "Define Sort Order" ) );

    if ( sortOrderDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( sortOrderDialog.IsDirty( ) )
    {
        // Save settings
        // resort tree
    }
}


void AlbumGenFrame::OnSortOrderClick( wxCommandEvent& event )
{
    DoSortOrderDialog( );
    event.Skip( );
}



void AlbumGenFrame::OnTextserchmenuitemClick( wxCommandEvent& event )
{
    event.Skip( );
}

void AlbumGenFrame::NewProject( )
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
    GetGeneratorData()->FileNewProject();



}

//GUI interface for creating new design
void AlbumGenFrame::NewDesign( )
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
    GetGeneratorData()->LoadNewDesign();
    SetDirty();

}



void AlbumGenFrame::NewCatalog( )
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

    GetGeneratorData()->LoadNewCatalog();
    SetDirty();
}

void AlbumGenFrame::OpenProject( )
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
        this, _( "Open Project XML file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "Project XML files (*.prj.xml)|*.prj.xml|All XML(&.xml)|*.xml", 
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
        wxLogError( "Cannot open file '%s'.", filename );
        return;
    }

    GetGeneratorData( )->FileOpenProject( filename);

}


void AlbumGenFrame::OpenDesign( )
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

    wxFileName lastFile( GetProject( )->GetDesignFilename( ) );
    lastFile.SetExt( "xml" );
    wxFileDialog openFileDialog(
        this, _( "Open Design XML file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "Project XML files (*.alb.xml)|*.alb.xml|All XML(&.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return; // the user changed idea...
    }

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxString filename = openFileDialog.GetPath( );

    GetGeneratorData( )->FileOpenDesign( filename );

}


void AlbumGenFrame::OpenCatalog( )
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
    wxFileName lastFile( GetProject( )->GetCatalogFilename( ) );
    lastFile.SetExt( "xml" );
    wxFileDialog openFileDialog(
        this, _( "Open Catalog XML file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "Catalog XML files (*.cat.xml)|*.cat.xml|All XML(&.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return; // the user changed idea...
    }

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxString filename = openFileDialog.GetPath( );

    GetGeneratorData( )->FileOpenCatalog( filename );
}



int AlbumGenFrame::QueryMerge( int& mergeMethod )
{
    const wxString choices[] = { "Merge", "Overwrite" };

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
            const wxString DispositionChoices[] = {
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











// void AlbumGenFrame::SaveDesign( )
// {
//     GetDesignData( )->SaveXML( GetProject( )->GetDesignFilename( ) );
// }

// void AlbumGenFrame::SaveCatalog( )
// {
//     GetCatalogData( )->Save( );
//     SetDirty( false );

// }
void AlbumGenFrame::SaveAsProject( )
{

    if ( GetCatalogData( ) )
    {
        wxFileName lastFile( GetSettings( )->GetLastFile( ) );
        lastFile.SetExt( "xml" );
        wxFileDialog saveFileDialog(
            this, _( "AlbumGenerator Project XML file" ),
            lastFile.GetPath( ), lastFile.GetFullName( ),
            "XML files (*.prj.xml)|*.prj.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
        if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
            return;

        wxString filename = saveFileDialog.GetPath( );
        GetGeneratorData( )->FileSaveAsProject( filename );
    }
}
void AlbumGenFrame::SaveAsCatalog( )
{

    if ( GetCatalogData( ) )
    {
        wxFileName lastFile( GetProject( )->GetCatalogFilename( ) );
        lastFile.SetExt( "xml" );
        wxFileDialog saveFileDialog(
            this, _( "Stamp List XML file" ),
            lastFile.GetPath( ), lastFile.GetFullName( ),
            "XML files (*.cat.xml)|*.cat.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
        if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
            return;

        wxString filename = saveFileDialog.GetPath( );
        GetGeneratorData()->FileSaveAsCatalog( filename );
    }
}
void AlbumGenFrame::SaveAsDesign( )
{

    if ( GetCatalogData( ) )
    {
        wxFileName lastFile( GetProject( )->GetDesignFilename( ) );
        lastFile.SetExt( "xml" );
        wxFileDialog saveFileDialog(
            this, _( "Stamp List XML file" ),
            lastFile.GetPath( ), lastFile.GetFullName( ),
            "XML files (*.alb.xml)|*.alb.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
        if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
            return;

        wxString filename = saveFileDialog.GetPath( );
        GetGeneratorData()->FileSaveAsDesign( filename );
    }
}
void AlbumGenFrame::GenerateODTAlbum( )
{
    ODT::ODTDoc()->InitODTFiles( );
    Design::GetAlbum()->MakeAlbum();
    ODT::ODTDoc()->MakeDocument();

}

void AlbumGenFrame::SetupRecentMenu( )
{
    // // first clobber each of the current menuItems and unbind them.
    // if ( m_menuItemList.size( ) > 0 )
    // {
    //     for ( int i = 0; i < m_menuItemList.size( ); i++ )
    //     {
    //         RecentListItem* item = m_menuItemList[ i ];
    //         bool val = Unbind( wxEVT_MENU, &AlbumGenFrame::DoRecentSelection, this, item->id );
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

    //         Bind( wxEVT_MENU, &AlbumGenFrame::DoRecentSelection, this, listItem->id );
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




void AlbumGenFrame::UpdateStatus( ) { m_albumGeneratorPanel->UpdateStatus( ); }

