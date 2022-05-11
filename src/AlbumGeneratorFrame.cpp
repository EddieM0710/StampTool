/**
 * @file AlbumGeneratorFrame.cpp
 * @author Eddie Monroe ()
 * @brief This is the application main frame.
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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

#include "AlbumGeneratorPanel.h"
#include "ManageCatalogData.h"
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/wfstream.h>

#include "CSV.h"
#include "Classification.h"
#include "Defs.h"
#include "Settings.h"
#include "DefinePeriodsDialog.h"
#include "SortOrderDialog.h"
#include "SettingsDialog.h"
#include "CatalogData.h"
#include "AECmdData.h"
#include "AlbumGeneratorFrame.h"
#include "XMLUtilities.h"

#include <curl/curl.h>

/*
 * AlbumGeneratorFrame type definition
 */

IMPLEMENT_CLASS( AlbumGeneratorFrame, wxFrame )
; // silly business; The above macro screws up the formatter

/*
 * AlbumGeneratorFrame event table definition
 */

BEGIN_EVENT_TABLE( AlbumGeneratorFrame, wxFrame )

// AlbumGeneratorFrame event table entries
EVT_CLOSE( AlbumGeneratorFrame::OnCloseWindow )
EVT_ICONIZE( AlbumGeneratorFrame::OnIconize )
EVT_MAXIMIZE( AlbumGeneratorFrame::OnMaximize )
EVT_MENU( wxID_OPEN, AlbumGeneratorFrame::OnOpenClick )
EVT_MENU( wxID_SAVE, AlbumGeneratorFrame::OnSaveClick )
EVT_MENU( wxID_SAVEAS, AlbumGeneratorFrame::OnSaveasClick )
EVT_MENU( ID_CSVIMPORT, AlbumGeneratorFrame::OnCSVImportClick )
EVT_MENU( ID_AEIMPORT, AlbumGeneratorFrame::OnAEImportClick )
EVT_MENU( wxID_REVERT_TO_SAVED, AlbumGeneratorFrame::OnRevertToSavedClick )
EVT_MENU( wxID_EXIT, AlbumGeneratorFrame::OnExitClick )
EVT_MENU( ID_TEXTSERCHMENUITEM, AlbumGeneratorFrame::OnTextserchmenuitemClick )
EVT_MENU( ID_IMAGEGALERYMENUITEM, AlbumGeneratorFrame::OnImagegalerymenuitemClick )
EVT_MENU( ID_MENUITEM, AlbumGeneratorFrame::OnCVSReportMenuItemClick )
EVT_MENU( ID_ALBUMGENMENUITEM, AlbumGeneratorFrame::OnAlbumGenMenuItemClick )
EVT_MENU( ID_SORTORDER, AlbumGeneratorFrame::OnSortOrderClick )
EVT_MENU( ID_ITEMVIEW, AlbumGeneratorFrame::OnItemviewClick )
EVT_MENU( ID_DEFINEPERIOD, AlbumGeneratorFrame::OnDefineperiodClick )
EVT_MENU( ID_LOADIMAGESMENUITEM, AlbumGeneratorFrame::OnLoadimagesmenuitemClick )
EVT_MENU( ID_TESTXMLMENUITEM, AlbumGeneratorFrame::OnTestXMLClick )
EVT_MENU( ID_SETTINGS, AlbumGeneratorFrame::OnSettingsClick )
// AlbumGeneratorFrame event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

    /*
     * AlbumGeneratorFrame constructors
     */

AlbumGeneratorFrame::AlbumGeneratorFrame( )
{
    Init( );
}

void AlbumGeneratorFrame::InitLoad( )
{
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    {
        wxFileName filename( GetSettings( )->GetLastFile( ) );
        wxString ext = filename.GetExt( );
        if ( !ext.CmpNoCase( "xml" ) )
        {
            m_catalogDataManager->InitCatalogData( );
            m_catalogDataManager->LoadCatalog( filename.GetFullPath( ) );
        }
    }
}

AlbumGeneratorFrame::AlbumGeneratorFrame( wxWindow* parent, wxWindowID id,
    const wxString& caption,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );

}

/*
 * AlbumGeneratorFrame creator
 */

bool AlbumGeneratorFrame::Create( wxWindow* parent, wxWindowID id,
    const wxString& caption, const wxPoint& pos,
    const wxSize& size, long style )
{
    // AlbumGeneratorFrame creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    this->SetFont( wxFont( 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL, false, wxT( "Ubuntu" ) ) );
    CreateControls( );
    Centre( );
    // AlbumGeneratorFrame creation
    return true;
}

/*
 * AlbumGeneratorFrame destructor
 */

AlbumGeneratorFrame::~AlbumGeneratorFrame( )
{

}

/*
 * Member initialisation
 */

void AlbumGeneratorFrame::Init( )
{
    m_stamp = new Stamp( );
    m_albumGeneratorPanel = NULL;
    m_catalogDataManager = NULL;
}

/*
 * Control creation for AlbumGeneratorFrame
 */

void AlbumGeneratorFrame::CreateControls( )
{
    // AlbumGeneratorFrame content construction

    AlbumGeneratorFrame* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    m_fileMenu = new wxMenu;
    m_fileMenu->Append( wxID_OPEN, _( "Open Data File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( wxID_SAVE, _( "Save Data File" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( wxID_SAVEAS, _( "Save As" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->AppendSeparator( );
    m_importMenu = new wxMenu;
    m_importMenu->Append( ID_CSVIMPORT, _( "CSV" ), wxEmptyString, wxITEM_NORMAL );
    m_importMenu->Append( ID_AEIMPORT, _( "AlbumEasy" ), wxEmptyString, wxITEM_NORMAL );

    m_fileMenu->Append( ID_IMPORT, _( "Import" ), m_importMenu );
    m_fileMenu->Append( wxID_REVERT_TO_SAVED, _( "Export" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->Append( ID_MERGE, _( "Merge" ), wxEmptyString, wxITEM_NORMAL );
    m_fileMenu->AppendSeparator( );
    m_recentMenu = new wxMenu;
    m_fileMenu->Append( ID_RECENT, _( "Recent" ), m_recentMenu );
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
    itemMenu3->Append( ID_IMAGEGALERYMENUITEM, _( "Image Gallery" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu3, _( "Search" ) );
    wxMenu* itemMenu2 = new wxMenu;
    itemMenu2->Append( ID_MENUITEM, _( "CSV Report" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu2->Append( ID_ALBUMGENMENUITEM, _( "Album Generator" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu2, _( "Report" ) );
    wxMenu* itemMenu1 = new wxMenu;
    itemMenu1->Append( ID_SORTORDER, _( "Sort Order" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu1->Append( ID_ITEMVIEW, _( "Item View" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu1->Append( ID_DEFINEPERIOD, _( "Define Period" ), wxEmptyString, wxITEM_NORMAL );
    itemMenu1->Append( ID_LOADIMAGESMENUITEM, _( "Load Images" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu1, _( "Setup" ) );
    wxMenu* itemMenu13 = new wxMenu;
    itemMenu13->Append( ID_TESTXMLMENUITEM, _( "Test XML" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu13, _( "Test" ) );
    wxMenu* itemMenu7 = new wxMenu;
    itemMenu7->Append( wxID_ABOUT, _( "About" ), wxEmptyString, wxITEM_NORMAL );
    menuBar->Append( itemMenu7, _( "Help" ) );
    itemFrame1->SetMenuBar( menuBar );

    wxGridSizer* itemGridSizer1 = new wxGridSizer( 1, 1, 0, 0 );
    itemFrame1->SetSizer( itemGridSizer1 );

    m_albumGeneratorPanel = new AlbumGeneratorPanel(
        itemFrame1, ID_ALBUMGENERATORPANELFOREIGN, wxDefaultPosition,
        wxSize( 100, 100 ), wxSIMPLE_BORDER );
    itemGridSizer1->Add( m_albumGeneratorPanel, 1, wxGROW | wxALL, 0 );
    m_catalogDataManager = m_albumGeneratorPanel->GetCatalogDataManager();
}

/*
 * Should we show tooltips?
 */

bool AlbumGeneratorFrame::ShowToolTips( ) { return true; }

/*
 * Get bitmap resources
 */

wxBitmap AlbumGeneratorFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    // AlbumGeneratorFrame bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // AlbumGeneratorFrame bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumGeneratorFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
    // AlbumGeneratorFrame icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // AlbumGeneratorFrame icon retrieval
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN
 */

void AlbumGeneratorFrame::OnOpenClick( wxCommandEvent& event )
{
    Open( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE
 */

void AlbumGeneratorFrame::OnSaveClick( wxCommandEvent& event )
{
    Save( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT
 */

void AlbumGeneratorFrame::OnCSVImportClick( wxCommandEvent& event )
{
    DoCSVImport( );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT
 */

void AlbumGeneratorFrame::OnAEImportClick( wxCommandEvent& event )
{
    DoAEImport( );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_EXPORT
 */

void AlbumGeneratorFrame::OnRevertToSavedClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_EXPORT in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_EXPORT in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
 */

void AlbumGeneratorFrame::OnExitClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS
 */

void AlbumGeneratorFrame::OnSaveasClick( wxCommandEvent& event )
{
    SaveAs( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS in
    // AlbumGeneratorFrame.
}

void AlbumGeneratorFrame::SetStamp( XMLElement* stamp )
{
    m_stamp->SetElement( stamp );
    m_albumGeneratorPanel->SetStamp( m_stamp );
}

void AlbumGeneratorFrame::UpdateStatus( ) { m_albumGeneratorPanel->UpdateStatus( ); }

// StampTreeCtrl* AlbumGeneratorFrame::GetStampTree( )
// {
//     return m_mngCatalogData->GetStampTree( );
// };

// void AlbumGeneratorFrame::LoadTree(Catalog *catalogData)
// {
//     m_selectionPanel->ClearTree();
//     m_selectionPanel->LoadTree(catalogData);
// }

void AlbumGeneratorFrame::SaveCatalogXML( wxString filename )
{
    GetCatalogData( )->SaveXML( filename );

    SetDirty( false );

    wxFileName newFile( filename );
    GetSettings( )->SetLastFile( newFile.GetFullName( ) );
    GetSettings( )->Save( );
}

void AlbumGeneratorFrame::Save( )
{
    if ( GetCatalogData( ) )
        // if (m_stampData && Dirty)
    {
        wxFileName filename( GetSettings( )->GetLastFile( ) );
        filename.SetExt( "xml" ); // make sure it is an xml

        SaveCatalogXML( filename.GetFullPath( ) );
    }
}

void AlbumGeneratorFrame::SaveAs( )
{

    if ( GetCatalogData( ) )
    {
        wxFileName lastFile( GetSettings( )->GetLastFile( ) );
        lastFile.SetExt( "xml" );
        wxFileDialog saveFileDialog(
            this, _( "Stamp List XML file" ),
            lastFile.GetPath( ), lastFile.GetFullName( ),
            "XML files (*.xml)|*.xml", wxFD_SAVE );
        if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
            return;

        wxString filename = saveFileDialog.GetPath( );
        SaveCatalogXML( filename );
    }
}

int AlbumGeneratorFrame::ImageGallery( ) { }



int AlbumGeneratorFrame::DoQueryMerge( int& mergeMethod )
{
    XMLElement* docRoot = 0;
    int mergeOverwriteQuery;

    CatalogData* catalogData = GetCatalogData( );
    if ( catalogData )
    {
        mergeOverwriteQuery = QueryMerge( mergeMethod );
    }
    else
    {
        mergeOverwriteQuery = MO_Cancel;
    }
    return mergeOverwriteQuery;
}


int AlbumGeneratorFrame::QueryMerge( int& mergeMethod )
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
            return MO_Overwrite;
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
                return MO_Merge;
            }
            else
            {
                return MO_Cancel;
            }
        }
    }
    else
    {
        return MO_Cancel;
    }
}

void AlbumGeneratorFrame::Open( )
{

    // int mergeMethod;

    // int mergeOverwriteQuery = DoQueryMerge( mergeMethod );
    // if ( mergeOverwriteQuery == MO_Cancel )
    // {
    //     return;
    // }

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
        this, _( "Open Stamp List XML file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "XML files (*.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
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


    // if ( mergeOverwriteQuery == MO_Overwrite )
    // {
    m_catalogDataManager->InitCatalogData( );
    m_catalogDataManager->LoadCatalog( filename );
    // }
    // else // merge
    // {
    //     CatalogData* mergeCatalogData = NewCatalogData( );
    //     mergeCatalogData->LoadCatalog( filename );   
    //     CatalogData* catalogData = GetCatalogData( );
    //     m_catalogDataManager->ClearTree( );

    //     MergeStampsDialog mergeDialog;
    //     mergeDialog.InitializeMerge( mergeMethod, catalogData, mergeCatalogData );
    //     if ( mergeDialog.Create( this ) )
    //     {
    //         mergeDialog.ShowModal( );
    //     }
    //     delete mergeCatalogData;   
    //     m_catalogDataManager->LoadTree( );

    // }
}



void AlbumGeneratorFrame::DoCSVImport( )
{
    // CatalogData* mergeCatalogData;
    // int mergeMethod;
    // int mergeOverwriteQuery = DoQueryMerge( mergeMethod );
    // if ( mergeOverwriteQuery == MO_Cancel )
    // {
    //     return;
    // }
    if ( IsDirty( ) )
    {
        // query whether to save first 
    }

    wxFileName lastFile( GetSettings( )->GetLastFile( ) );
    lastFile.SetExt( "csv" );
    wxFileDialog openFileDialog(
        this, _( "Open Colnect CSV file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
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

    m_catalogDataManager->LoadCatalogCSV( filename );
    Dirty = true;
}

void AlbumGeneratorFrame::DoAEImport( )
{

    if ( IsDirty( ) )
    {
        // query whether to save first 
    }

    wxFileName lastFile( GetSettings( )->GetLastFile( ) );
    lastFile.SetExt( "txt" );
    wxFileDialog openFileDialog(
        this, _( "Open AlbumEasy Text file" ),
        lastFile.GetPath( ), lastFile.GetFullName( ),
        "AlbumEasy files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
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


    m_albumGeneratorPanel->ClearAECmdTree( );
    AECmdData* aeCmdData = NewAECmdData( );
    SetAECmdData( aeCmdData );
    aeCmdData->LoadAEFile( filename );

    m_albumGeneratorPanel->LoadAECmdTree( );
    Dirty = true;
}

// /*
//  * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
//  */

// void AlbumGeneratorFrame::OnButtonClick(wxCommandEvent &event)
// {
//      // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in
//     AlbumGeneratorFrame.
//     // Before editing this code, remove the block markers.
//     event.Skip();
//      // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in
//     AlbumGeneratorFrame.
// }
void AlbumGeneratorFrame::DoDefinePeriodDialog( )
{
    DefinePeriodsDialog definePeriodsDialog( this, ID_DEFINEPERIODS,
        _( "Define Sort Order" ) );

    if ( definePeriodsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( definePeriodsDialog.IsDirty( ) )
    {
        // Save persistent
        // resort tree
    }
}
void AlbumGeneratorFrame::DoSettingsDialog( )
{
    SettingsDialog settingsDialog( this, ID_SETTINGSDIALOG,
        _( "Define Sort Order" ) );

    if ( settingsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( settingsDialog.IsDirty( ) )
    {
        // Save persistent
        // resort tree
    }
}
void AlbumGeneratorFrame::DoSortOrderDialog( )
{
    SortOrderDialog sortOrderDialog( this, ID_SORTORDERDIALOG,
        _( "Define Sort Order" ) );

    if ( sortOrderDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( sortOrderDialog.IsDirty( ) )
    {
        // Save persistent
        // resort tree
    }
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER
 */

void AlbumGeneratorFrame::OnSortOrderClick( wxCommandEvent& event )
{
    DoSortOrderDialog( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW
 */

void AlbumGeneratorFrame::OnItemviewClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD
 */

void AlbumGeneratorFrame::OnDefineperiodClick( wxCommandEvent& event )
{
    DoDefinePeriodDialog( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD in
    // AlbumGeneratorFrame.
}

static size_t write_data( void* ptr, size_t size, size_t nmemb, void* stream )
{
    size_t written = fwrite( ptr, size, nmemb, ( FILE* )stream );
    return written;
}

bool AlbumGeneratorFrame::GetFile( wxString newFile, wxString imageName )
{
    CURL* curl_handle;

    FILE* pagefile;

    curl_global_init( CURL_GLOBAL_ALL );

    /* init the curl session */
    curl_handle = curl_easy_init( );

    /* set URL to get here */
    wxString URLName1;
    // const char* str =  (char*)imageName.ToAscii();
    URLName1 = URLName1.Format(
        "https://www.mysticstamp.com/pictures/stamps_default/USA-%s", newFile );
    const char* ptr = URLName1.c_str( );
    const char* ptr2 = URLName1.ToUTF8( );
    curl_easy_setopt( curl_handle, CURLOPT_URL, ptr );

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt( curl_handle, CURLOPT_VERBOSE, 1L );

    /* disable progress meter, set to 0L to enable it */
    curl_easy_setopt( curl_handle, CURLOPT_NOPROGRESS, 1L );

    /* send all data to this function  */
    curl_easy_setopt( curl_handle, CURLOPT_WRITEFUNCTION, write_data );

    /* open the file */
    pagefile = fopen( imageName.c_str( ), "wb" );
    if ( pagefile )
    {
        /* write the page body to this file handle */
        curl_easy_setopt( curl_handle, CURLOPT_WRITEDATA, pagefile );

        /* get it! */
        curl_easy_perform( curl_handle );

        /* close the header file */
        fclose( pagefile );
    }

    /* cleanup curl stuff */
    curl_easy_cleanup( curl_handle );

    curl_global_cleanup( );

    return 0;
}
/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_LOADIMAGESMENUITEM
 */

void AlbumGeneratorFrame::OnLoadimagesmenuitemClick( wxCommandEvent& event )
{
    // XMLIterator* parentIter = 0;
    // XMLDocument* doc = GetCatalogData( )->GetDoc( );
    // XMLElement* parent = doc->RootElement( );
    // XMLIterator* iterator = new XMLIterator( parent );
    // XMLElement* item = iterator->First( );
    // while ( item )
    // {
    //     wxString name = item->Name( );
    //     if ( !name.Cmp( "Stamp" ) )
    //     {
    //         const XMLAttribute* attr = item->FindAttribute( "ID_Nbr" );
    //         if ( attr )
    //         {
    //             const char* idStr = attr->Value( );
    //             wxString id = idStr;
    //             int i = id.Find( " " );
    //             if ( i >= 0 )
    //             {
    //                 wxString sp = " ";
    //                 wxString nullStr = "";
    //                 size_t size = id.Replace( sp, nullStr, true );
    //                 item->SetAttribute( "ID_Nbr", id.fn_str( ) );
    //             }
    //             std::cout << "Info: AlbumGeneratorFrame Loadimages " << attr->Value( )
    //                 << "\n";
    //             wxFileName fileName;

    //             // fileName.SetPath(wxGetCwd());
    //             // fileName.AppendDir(wxT("Art"));
    //             // if (!fileName.DirExists())
    //             // {
    //             //     wxMkdir(wxString("Art"));
    //             // }
    //             wxString str = GetCatalogData( )->GetImageDirectory( );
    //             wxString imageName = wxString::Format( "%s/%s.jpg", str, attr->Value( ) );
    //             fileName.Assign( imageName );
    //             std::cout << "Info: AlbumGeneratorFrame Loadimages "
    //                 << fileName.GetFullPath( ) << "\n";

    //             if ( !fileName.FileExists( ) )
    //             {
    //                 GetFile( fileName.GetFullName( ), imageName );
    //             }
    //         }
    //     }
    //     item = iterator->Next( );
    // }

    // wxEVT_COMMAND_MENU_SELECTED event handler for
    // ID_LOADIMAGESMENUITEM in AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_LOADIMAGESMENUITEM
    // in AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TESTXMLMENUITEM
 */

void AlbumGeneratorFrame::OnTestXMLClick( wxCommandEvent& event )
{
    wxFileName* filename = new wxFileName(
        GetSettings( )->GetWorkingDirectory( ), "XMLTest", "xml" );
    wxString fullPath = filename->GetFullPath( );
    XMLDocument doc;
    int errCode = doc.LoadFile( fullPath.c_str( ) );

    if ( errCode != XML_SUCCESS )
    {
        wxString errorStr = doc.ErrorStr( );
        std::cout << errorStr << "\n";
    }
    wxString name = doc.Value( );
    std::cout << "Doc Name: " << name << "\n";

    XMLElement* root = doc.FirstChildElement( );
    // start processing the XML file
    wxString rootName = root->Value( );
    wxString child = root->Attribute( "Child" );
    wxString id = root->Attribute( "id" );
    std::cout << "Root Value: " << rootName << "  Child:" << child
        << "  id:" << id << "\n";
    std::cout << " Testing decending entire file\n";
    std::cout << " ID numbers should be in order 1 thru 120\n";

    XMLIterator* iter = new XMLIterator( root );
    XMLElement* ele = iter->First( );
    while ( ele )
    {
        wxString eleName = ele->Name( );
        child = ele->Attribute( "Child" );
        id = ele->Attribute( "id" );
        std::cout << eleName << "  Child:" << child << "  id:" << id << "\n";
        ele = iter->Next( );
    }
    delete iter;

    std::cout << " Testing No decend \n";
    std::cout
        << " first level is iterated and second level within each of those \n";

    iter = new XMLIterator( root, false );
    ele = iter->First( );
    while ( ele )
    {
        name = ele->Name( );
        child = ele->Attribute( "Child" );
        id = ele->Attribute( "id" );
        std::cout << name << "  Child:" << child << "  id:" << id << "\n";
        std::cout << "      Do next level only\n";
        XMLIterator* iter2 = new XMLIterator( ele, false );
        XMLElement* ele2 = iter2->First( );
        while ( ele2 )
        {
            name = ele2->Name( );
            child = ele2->Attribute( "Child" );
            id = ele2->Attribute( "id" );
            std::cout << name << "        Child:" << child << "  id:" << id << "\n";

            ele2 = iter2->Next( );
        }
        ele = iter->Next( );
    }
    delete iter;

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TESTXMLMENUITEM
    // in AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TESTXMLMENUITEM in
    // AlbumGeneratorFrame.
}


void AlbumGeneratorFrame::OnAlbumGenMenuItemClick( wxCommandEvent& event )
{

}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM
 */

void AlbumGeneratorFrame::OnCVSReportMenuItemClick( wxCommandEvent& event )
{
    wxFileName imageFileName;
    imageFileName.SetPath( wxGetCwd( ) );
    imageFileName.AppendDir( wxT( "Art" ) );
    if ( !imageFileName.DirExists( ) )
    {
        wxMkdir( wxString( "Art" ) );
    }

    wxFileName filename( GetSettings( )->GetWorkingDirectory( ),
        "CSVReport", "csv" );

    wxString fullPath = filename.GetFullPath( );

    wxFileOutputStream l_file( fullPath );

    if ( l_file.IsOk( ) )
    {
        wxTextOutputStream text( l_file );
        wxString id;
        wxString link;
        wxString imageName;
        XMLDocument* doc = GetCatalogData( )->GetDoc( );
        XMLElement* root = doc->RootElement( );
        XMLIterator* iter = new XMLIterator( root );
        XMLElement* item = iter->First( );
        while ( item )
        {
            wxString name = item->Name( );
            if ( !name.Cmp( NodeNameStrings[ NT_Stamp ] ) )
            {
                Stamp stamp( item );
                id = stamp.GetID( );
                link = stamp.GetLink( );
                imageName = wxString::Format( "%s.jpg", id );
                imageFileName.SetFullName( imageName );
                if ( !imageFileName.FileExists( ) )
                {
                    if ( id.Len( ) > 0 && link.Len( ) > 0 )
                    {
                        text << id << ", " << link << "\n";
                    }
                }
            }
            item = iter->Next( );
        }
        l_file.Close( );
    }
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME
 */

void AlbumGeneratorFrame::OnCloseWindow( wxCloseEvent& event )
{
    // wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME
 */

void AlbumGeneratorFrame::OnIconize( wxIconizeEvent& event )
{
    // wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME
 */

void AlbumGeneratorFrame::OnMaximize( wxMaximizeEvent& event )
{
    // wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TEXTSERCHMENUITEM
 */

void AlbumGeneratorFrame::OnTextserchmenuitemClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for
    // ID_TEXTSERCHMENUITEM in AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TEXTSERCHMENUITEM
    // in AlbumGeneratorFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMAGEGALERYMENUITEM
 */

void AlbumGeneratorFrame::OnImagegalerymenuitemClick( wxCommandEvent& event )
{
    ImageGallery( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for
    // ID_IMAGEGALERYMENUITEM in AlbumGeneratorFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for
    // ID_IMAGEGALERYMENUITEM in AlbumGeneratorFrame.
}


void AlbumGeneratorFrame::DoRecentSelection( wxCommandEvent& event )
{

    int mergeMethod;
    int mergeOverwriteQuery = DoQueryMerge( mergeMethod );
    if ( mergeOverwriteQuery == MO_Cancel )
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

    m_catalogDataManager->LoadCatalog( filename );


    event.Skip( );
}

void AlbumGeneratorFrame::SetupRecentMenu( )
{
    // first clobber each of the current menuItems and unbind them.
    if ( m_menuItemList.size( ) > 0 )
    {
        for ( int i = 0; i < m_menuItemList.size( ); i++ )
        {
            RecentListItem* item = m_menuItemList[ i ];
            bool val = Unbind( wxEVT_MENU, &AlbumGeneratorFrame::DoRecentSelection, this, item->id );
            m_recentMenu->Delete( item->item );
            //  item->item->~wxMenuItem( );
        }
        m_menuItemList.clear( ); // then clobber the list
    }
    // then create all the new menuItems and bind them
    wxArrayString* recentList = GetSettings( )->GetRecentArray( );
    for ( int i = 0; i < recentList->Count( ); i++ )
    {
        RecentListItem* listItem = new RecentListItem( );
        listItem->id = ID_RECENT + i + 1;
        listItem->item = m_recentMenu->Append( listItem->id, recentList->Item( i ), wxEmptyString, wxITEM_NORMAL );

        Bind( wxEVT_MENU, &AlbumGeneratorFrame::DoRecentSelection, this, listItem->id );
        m_menuItemList.push_back( listItem );
    }
    if ( recentList->Count( ) > 0 )
    {
        m_fileMenu->Enable( ID_RECENT, true );
    }
    else
    {
        m_fileMenu->Enable( ID_RECENT, false );
    }
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS
 */

void AlbumGeneratorFrame::OnSettingsClick( wxCommandEvent& event )
{
    DoSettingsDialog( );
    ////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS in AlbumGeneratorFrame.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS in AlbumGeneratorFrame. 
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE
 */

void AlbumGeneratorFrame::OnMergeClick( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE in AlbumGeneratorFrame.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE in AlbumGeneratorFrame. 
}

