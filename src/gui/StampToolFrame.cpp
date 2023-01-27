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
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "gui/StampToolPanel.h"
#include "gui/CatalogPanel.h"
#include "gui/DefinePeriodsDialog.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/filedlg.h> 
#include <wx/log.h>
#include <wx/wfstream.h>

#include "utils/CSV.h"
#include "catalog/Classification.h"
#include "catalog/Entry.h"
#include "Defs.h"
#include "Settings.h"
#include "utils/Project.h"
#include "gui/AlbumDesignTreePanel.h"
#include "gui/SortOrderDialog.h"
#include "gui/SettingsDialog.h"
#include "catalog/CatalogSectionData.h"
#include "gui/StampToolFrame.h"
#include "utils/XMLUtilities.h"
#include "design/DesignDefs.h"
#include "design/DesignData.h"
#include "design/AlbumBase.h"
#include "design/Album.h"
#include "design/Stamp.h"
#include "gui/FileCreateDialog.h"

//#include <curl/curl.h>

/*
 * StampToolFrame type definition
 */

IMPLEMENT_CLASS( StampToolFrame, wxFrame )
; // silly business; The above macro screws up the formatter

/*
 * StampToolFrame event table definition
 */

BEGIN_EVENT_TABLE( StampToolFrame, wxFrame )

// StampToolFrame event table entries
EVT_CLOSE( StampToolFrame::OnCloseWindow )
EVT_ICONIZE( StampToolFrame::OnIconize )
EVT_MAXIMIZE( StampToolFrame::OnMaximize )
EVT_MENU( ID_NEWPROJECT, StampToolFrame::OnNewProjectClick )
EVT_MENU( ID_NEWDESIGN, StampToolFrame::OnNewDesignClick )
EVT_MENU( ID_NEWCATALOG, StampToolFrame::OnNewCatalogClick )
EVT_MENU( ID_OPENPROJECT, StampToolFrame::OnOpenProjectClick )
EVT_MENU( ID_OPENDESIGN, StampToolFrame::OnOpenDesignClick )
EVT_MENU( ID_OPENCATALOG, StampToolFrame::OnOpenCatalogClick )
EVT_MENU( ID_SAVEPROJECT, StampToolFrame::OnSaveProjectClick )
EVT_MENU( ID_SAVEDESIGN, StampToolFrame::OnSaveDesignClick )
EVT_MENU( ID_SAVECATALOG, StampToolFrame::OnSaveCatalogClick )
EVT_MENU( ID_SAVEASPROJECT, StampToolFrame::OnSaveasProjectClick )
EVT_MENU( ID_SAVEASDESIGN, StampToolFrame::OnSaveasDesignClick )
EVT_MENU( ID_SAVEASCATALOG, StampToolFrame::OnSaveasCatalogClick )
EVT_MENU( ID_GENERATEODT, StampToolFrame::OnGenerateODTClick )
EVT_MENU( ID_CSVIMPORT, StampToolFrame::OnCSVImportClick )
//EVT_MENU( ID_MERGE, StampToolFrame::OnCSVImportClick )
EVT_MENU( wxID_EXIT, StampToolFrame::OnExitClick )
EVT_MENU( ID_TEXTSERCHMENUITEM, StampToolFrame::OnTextserchmenuitemClick )
EVT_MENU( ID_SORTORDER, StampToolFrame::OnSortOrderClick )
EVT_MENU( ID_ITEMVIEW, StampToolFrame::OnItemviewClick )
EVT_MENU( ID_DEFINEPERIOD, StampToolFrame::OnDefineperiodClick )
EVT_MENU( ID_SETTINGS, StampToolFrame::OnSettingsClick )
// StampToolFrame event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter




StampToolFrame::StampToolFrame( )
{ 
    Init( );
}


void StampToolFrame::InitLoad( )
{ 
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    { 
        GetProject( )->LoadProjectXML( );
        GetToolData( )->LoadData( );
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
    // StampToolFrame creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    this->SetFont( wxFont( 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, 
        wxFONTWEIGHT_NORMAL, false, wxT( "Ubuntu" ) ) );
    CreateControls( );
    Centre( );
    // StampToolFrame creation
    return true;
}


StampToolFrame::~StampToolFrame( )
{ 

}

/*
 * Member initialisation
 */

void StampToolFrame::Init( )
{ 
    //    m_stamp = new Catalog::Stamp( );
    m_stampToolPanel = NULL;
    m_catalogPanel = NULL;
}

/*
 * Control creation for StampToolFrame
 */

void StampToolFrame::CreateControls( )
{ 
    // StampToolFrame content construction

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

    wxMenu* m_catalogMenu = new wxMenu;    
    m_catalogMenu->Append( ID_NEWCATALOG, _( "New Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_catalogMenu->Append( ID_CSVIMPORT, _( "Create Catalog from CSV" ), wxEmptyString, wxITEM_NORMAL );
    m_catalogMenu->Append( ID_OPENCATALOG, _( "Add Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_CATALOGMENU, _( "Catalog" ), m_catalogMenu );


    wxMenu* m_designMenu = new wxMenu;
    m_designMenu->Append( ID_NEWDESIGN, _( "New Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu->Append( ID_OPENDESIGN, _( "Open Design File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_DESIGNMENU, _( "Design" ), m_designMenu );

    m_fileMenu->AppendSeparator( );
    m_fileMenu->Append( ID_GENERATEODT, _( "Generate ODT Album" ), wxEmptyString, wxITEM_NORMAL );

    m_fileMenu->AppendSeparator( );


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
    menuBar->Append( itemMenu3, _( "Search" ) );

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
    m_catalogPanel = m_stampToolPanel->GetCatalogPanel( );
    m_albumDesignTreePanel = m_stampToolPanel->GetAlbumDesignTreePanel( );
}

CatalogPanel* StampToolFrame::GetCatalogPanel( )
{ 
    return m_stampToolPanel->GetCatalogPanel( );
}

bool StampToolFrame::ShowToolTips( )
{ 
    return true;
}

wxBitmap StampToolFrame::GetBitmapResource( const wxString& name )
{ 
    // Bitmap retrieval
    // StampToolFrame bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // StampToolFrame bitmap retrieval
}

wxIcon StampToolFrame::GetIconResource( const wxString& name )
{ 
    // Icon retrieval
    // StampToolFrame icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // StampToolFrame icon retrieval
}

int StampToolFrame::DoQueryMerge( int& mergeMethod )
{ 
    wxXmlNode* docRoot = 0;
    int mergeOverwriteQuery;

    Catalog::CatalogSectionData* catalogSectionData = GetCatalogSectionData( );
    if ( catalogSectionData )
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


void StampToolFrame::DoCSVImport( )
{ 

    if ( IsDirty( ) )
    { 
        // query whether to save first 
    }

    wxFileDialog openFileDialog( 
        this, _( "Open Colnect CSV file" ), 
        "", "", 
        "CSV files ( *.csv ) | *.csv", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
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
        wxLogError( "DoCSVImport: Cannot open file '%s'.", filename );
        return;
    }

    if ( GetToolData( )->ReadCatalogCSV( filename ) )
    { 
        GetCatalogSectionData( )->EditDetailsDialog( this );
        GetToolData( )->LoadCatalogTree( );
    }  
    Dirty = true;
}

void StampToolFrame::DoDefinePeriodDialog( )
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


void StampToolFrame::OnNewProjectClick( wxCommandEvent& event )
{ 
    NewProject( );
    event.Skip( );
}

void StampToolFrame::OnNewDesignClick( wxCommandEvent& event )
{ 
    NewDesign( );
    event.Skip( );
}
void StampToolFrame::OnNewCatalogClick( wxCommandEvent& event )
{ 
    NewCatalog( );
    event.Skip( );
}



void StampToolFrame::OnOpenProjectClick( wxCommandEvent& event )
{ 
    OpenProject( );
    event.Skip( );
}

void StampToolFrame::OnOpenDesignClick( wxCommandEvent& event )
{ 
    OpenDesign( );
    event.Skip( );
}
void StampToolFrame::OnOpenCatalogClick( wxCommandEvent& event )
{ 
    OpenCatalog( );
    event.Skip( );
}

void StampToolFrame::OnSaveProjectClick( wxCommandEvent& event )
{ 
    GetToolData( )->FileSaveProject( );
    event.Skip( );
}

void StampToolFrame::OnSaveDesignClick( wxCommandEvent& event )
{ 
    GetToolData( )->FileSaveDesign( );
    event.Skip( );
}
void StampToolFrame::OnSaveCatalogClick( wxCommandEvent& event )
{ 
    GetToolData( )->FileSaveCatalog( );
    event.Skip( );
}


void StampToolFrame::OnCSVImportClick( wxCommandEvent& event )
{ 
    DoCSVImport( );
    event.Skip( );
}

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



void StampToolFrame::OnDefineperiodClick( wxCommandEvent& event )
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

void StampToolFrame::OnSaveasDesignClick( wxCommandEvent& event )
{ 
    SaveAsDesign( );
    event.Skip( );
}
void StampToolFrame::OnSaveasCatalogClick( wxCommandEvent& event )
{ 
    SaveAsCatalog( );
    event.Skip( );
}

void StampToolFrame::OnGenerateODTClick( wxCommandEvent& event )
{ 
    GenerateODTAlbum( );
    event.Skip( );
}

void StampToolFrame::OnSettingsClick( wxCommandEvent& event )
{ 
    DoSettingsDialog( );
    event.Skip( );
}

void StampToolFrame::DoSettingsDialog( )
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

void StampToolFrame::DoSortOrderDialog( )
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


void StampToolFrame::OnSortOrderClick( wxCommandEvent& event )
{ 
    DoSortOrderDialog( );
    event.Skip( );
}



void StampToolFrame::OnTextserchmenuitemClick( wxCommandEvent& event )
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
 
    FileCreateDialog fileDialog( this, 12355, _( "Select the Filename and Directory for the Project file." )  );
    wxGetCwd( );
    fileDialog.SetDefaultDirectory( wxGetCwd( ) );
    fileDialog.SetDefaultFilename( _( "unnamed.prj.xml" ) ); 
    fileDialog.SetWildCard( _("Project files(*.prj.xml)|*.prj.xml") );

    if (  fileDialog.ShowModal( ) == wxID_CANCEL )
    { 
        return;
    }
    wxString dir = fileDialog.GetDir( );
    wxSetWorkingDirectory( dir );


    GetToolData( )->FileNewProject( fileDialog.GetFile( ) );



}

//GUI interface for creating new design
void StampToolFrame::NewDesign( )
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
     
    FileCreateDialog fileDialog( this, 12355, _( "Select the Filename and Directory for the Design file." )  );
    wxGetCwd( );
    fileDialog.SetDefaultDirectory( wxGetCwd( ) );
    fileDialog.SetDefaultFilename( _( "unnamed.alb.xml" ) ); 
    fileDialog.SetWildCard( _( "Design files(*.alb.xml)|*.alb.xml" ) );

    if (  fileDialog.ShowModal( ) == wxID_CANCEL )
    { 
        return;
    }
    wxString cwd = wxGetCwd( );
    wxFileName designFile( fileDialog.GetPath( ) );
    designFile.MakeRelativeTo( cwd );
    GetToolData( )->LoadNewDesign( designFile.GetFullPath( ) );
    SetDirty( );

}



void StampToolFrame::NewCatalog( )
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
     
    FileCreateDialog fileDialog( this, 12355, _( "Select the Filename and Directory for the Design file." )  );
    wxGetCwd( );
    fileDialog.SetDefaultDirectory( wxGetCwd( ) );
    fileDialog.SetDefaultFilename( _( "unnamed.alb.xml" ) ); 
    fileDialog.SetWildCard( _( "Design files(*.alb.xml)|*.alb.xml" ) );

    if (  fileDialog.ShowModal( ) == wxID_CANCEL )
    { 
        return;
    }

    wxString cwd = wxGetCwd( );
    wxFileName catFile( fileDialog.GetPath( ) );
    catFile.MakeRelativeTo( cwd );

    GetToolData( )->LoadNewCatalog( catFile.GetFullPath( ) );
    SetDirty( );
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
        wxLogError( "StampToolFrame::OpenProject Cannot open file '%s'.", filename );
        return;
    }


    GetToolData( )->FileOpenProject( filename );

}



void StampToolFrame::OpenDesign( )
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
        "Project XML files(*.alb.xml)|*.alb.xml|All XML(&.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    { 
        return; // the user changed idea...
    }

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxString filename = openFileDialog.GetPath( );

    GetToolData( )->FileOpenDesign( filename );

}


void StampToolFrame::OpenCatalog( )
{ 
    // if ( IsDirty( ) )
    // { 
    //     // query whether to save first 
    //     wxMessageDialog* dlg = new wxMessageDialog( 
    //         this, 
    //         wxT( "The current data has been changed but not saved. \n"\
    //             "Select \"OK\" to close the file losing the changes.\n"\
    //             "Or select \"Cancel\" to quit file open process.\n" ), 
    //         wxT( "Warning! Unsaved modifications.\n" ), 
    //         wxOK | wxCANCEL | wxCENTER );
    //     int rsp = dlg->ShowModal( );
    //     if ( rsp == wxID_CANCEL )
    //     { 
    //         return;
    //     }
    // };

    wxFileDialog openFileDialog( 
        this, _( "Open Catalog XML file" ), 
        wxGetCwd( ), 
        _( "unnamed.cat.xml" ), 
        "Catalog XML files(*.cat.xml)|*.cat.xml|All XML(&.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    { 
        return; // the user changed idea...
    }

    wxString cwd = wxGetCwd( );
    wxFileName catFile( openFileDialog.GetPath( ) );
    catFile.MakeRelativeTo( cwd );
    GetToolData( )->FileOpenCatalog( catFile.GetFullPath( ) );
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











// void StampToolFrame::SaveDesign( )
// { 
//     GetDesignData( )->SaveXML( GetProject( )->GetDesignFilename( ) );
// }

// void StampToolFrame::SaveCatalog( )
// { 
//     GetCatalogSectionData( )->Save( );
//     SetDirty( false );

// }
void StampToolFrame::SaveAsProject( )
{ 

    //if ( GetCatalogSectionData( ) )
    //{ 
        wxFileName lastFile( GetSettings( )->GetLastFile( ) );
        lastFile.SetExt( "xml" );
        wxFileDialog saveFileDialog( 
            this, _( "StampTool Project XML file" ), 
            lastFile.GetPath( ), lastFile.GetFullName( ), 
            "XML files(*.prj.xml)|*.prj.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
        if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
            return;

        wxString filename = saveFileDialog.GetPath( );
        GetToolData( )->FileSaveAsProject( filename );
    //}
}
void StampToolFrame::SaveAsCatalog( )
{ 

    // if ( GetCatalogSectionData( ) )
    // { 
    //     wxFileName lastFile( GetProject( )->GetCatalogFilename( ) );
    //     lastFile.SetExt( "xml" );
    //     wxFileDialog saveFileDialog( 
    //         this, _( "Stamp List XML file" ), 
    //         lastFile.GetPath( ), lastFile.GetFullName( ), 
    //         "XML files (*.cat.xml)|*.cat.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
    //     if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
    //         return;

    //     wxString filename = saveFileDialog.GetPath( );
    //     GetToolData( )->FileSaveAsCatalog( filename );
    // }
}
void StampToolFrame::SaveAsDesign( )
{ 

    if ( GetCatalogSectionData( ) )
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
        GetToolData( )->FileSaveAsDesign( filename );
    }
}
void StampToolFrame::GenerateODTAlbum( )
{ 
    Design::Album* album = Design::GetAlbum( );
    if ( album )
    { 
        Design::GetAlbum( )->MakeAlbum( );
        ODT::ODTDoc( )->MakeDocument( );
    }
}

void StampToolFrame::SetupRecentMenu( )
{ 
    // // first clobber each of the current menuItems and unbind them.
    // if ( m_menuItemList.size( ) > 0 )
    // { 
    //     for ( int i = 0; i < m_menuItemList.size( ); i++ )
    //     { 
    //         RecentListItem* item = m_menuItemList[ i ];
    //         bool val = Unbind( wxEVT_MENU, &StampToolFrame::DoRecentSelection, this, item->id );
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

    //         Bind( wxEVT_MENU, &StampToolFrame::DoRecentSelection, this, listItem->id );
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

