/**
 * @file AlbumGenFrame.cpp
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

#include "gui/AlbumGenPanel.h"
#include "gui/CatalogPanel.h"
#include "gui/DefinePeriodsDialog.h"
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/wfstream.h>

#include "utils/CSV.h"
#include "catalog/Classification.h"
#include "catalog/Stamp.h"
#include "Defs.h"
#include "Settings.h"
#include "utils/Project.h"
#include "gui/AlbumPanel.h"
#include "gui/SortOrderDialog.h"
#include "gui/SettingsDialog.h"
#include "catalog/CatalogData.h"
#include "gui/AlbumGenFrame.h"
#include "utils/XMLUtilities.h"
#include "album/AlbumDefs.h"
#include "album/AlbumData.h"
#include "album/AlbumNode.h"
#include "album/Album.h"
#include "album/Stamp.h"
#include "gui/CatalogTreeCtrl.h"
#include <curl/curl.h>

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
EVT_MENU( wxID_OPEN, AlbumGenFrame::OnOpenClick )
EVT_MENU( wxID_SAVE, AlbumGenFrame::OnSaveClick )
EVT_MENU( wxID_SAVEAS, AlbumGenFrame::OnSaveasClick )
EVT_MENU( ID_CSVIMPORT, AlbumGenFrame::OnCSVImportClick )
EVT_MENU( ID_AEIMPORT, AlbumGenFrame::OnAEImportClick )
EVT_MENU( wxID_REVERT_TO_SAVED, AlbumGenFrame::OnRevertToSavedClick )
EVT_MENU( wxID_EXIT, AlbumGenFrame::OnExitClick )
EVT_MENU( ID_TEXTSERCHMENUITEM, AlbumGenFrame::OnTextserchmenuitemClick )
EVT_MENU( ID_IMAGEGALERYMENUITEM, AlbumGenFrame::OnImagegalerymenuitemClick )
EVT_MENU( ID_MENUITEM, AlbumGenFrame::OnCVSReportMenuItemClick )
EVT_MENU( ID_ALBUMGENMENUITEM, AlbumGenFrame::OnAlbumGenMenuItemClick )
EVT_MENU( ID_SORTORDER, AlbumGenFrame::OnSortOrderClick )
EVT_MENU( ID_ITEMVIEW, AlbumGenFrame::OnItemviewClick )
EVT_MENU( ID_DEFINEPERIOD, AlbumGenFrame::OnDefineperiodClick )
EVT_MENU( ID_LOADIMAGESMENUITEM, AlbumGenFrame::OnLoadimagesmenuitemClick )
EVT_MENU( ID_TESTXMLMENUITEM, AlbumGenFrame::OnTestXMLClick )
EVT_MENU( ID_SETTINGS, AlbumGenFrame::OnSettingsClick )
// AlbumGenFrame event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

    /*
     * AlbumGenFrame constructors
     */

AlbumGenFrame::AlbumGenFrame( )
{
    Init( );
}

void AlbumGenFrame::InitLoad( )
{
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    {
        m_albumPanel->LoadAlbumLayout( );

        m_catalogPanel->InitCatalogData( );
        m_catalogPanel->LoadCatalog( );

        Layout::Album* album = GetProject( )->GetAlbumData( )->GetAlbum( );
        Catalog::CatalogData* stampData = GetProject( )->GetCatalogData( );
       // LinkAlbumToCat( album, stampData );
    }
}



// void AlbumGenFrame::LinkNodes(Layout::LayoutNode* child, Catalog::CatalogData* stampData  )
// {           
//     if ( child->GetNodeType( ) == Layout::AT_Stamp )
//     {
//         Layout::Stamp* albumStamp = ( Layout::Stamp* )child;
//         wxString id = albumStamp->GetAttrStr( Layout::AT_ID );
//         wxXmlNode* catStamp = stampData->FindNodeWithPropertyAndValue(
//             Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ], id );
//         CatalogTreeCtrl* treeCtrl = m_catalogPanel->GetCatalogDataTree( );
//         wxTreeItemId catTreeID = treeCtrl->FindTreeItemID( id );
//         treeCtrl->SetItemState( catTreeID, 1 );
//         CatalogDataTreeItemData* item = ( CatalogDataTreeItemData* )treeCtrl->GetItemData( catTreeID );
//         item->SetAlbumNode( albumStamp );
//         albumStamp->SetCatalogStamp( catStamp );
//     }
// }
// void AlbumGenFrame::LinkAlbumToCat(Layout::LayoutNode* child, Catalog::CatalogData* stampData )
// {
//     for ( Layout::AlbumNodeList::iterator it = child->BeginAlbumNodeList( ); it != child->EndAlbumNodeList( ); ++it )
//     {
//         Layout::AlbumNode* child =( *it );
//         if ( child->GetNodeType( ) == Layout::AT_Stamp )
//         {
//             LinkNodes( (Layout::LayoutNode* )child, stampData );
//         }
//         LinkAlbumToCat( (Layout::LayoutNode* )child, stampData );
//     }
// }

AlbumGenFrame::AlbumGenFrame( wxWindow* parent, wxWindowID id,
    const wxString& caption,
    const wxPoint& pos, const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

/*
 * AlbumGenFrame creator
 */

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

/*
 * AlbumGenFrame destructor
 */

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

    m_albumGeneratorPanel = new AlbumGenPanel(
        itemFrame1, ID_ALBUMGENERATORPANELFOREIGN, wxDefaultPosition,
        wxSize( 100, 100 ), wxSIMPLE_BORDER );
    itemGridSizer1->Add( m_albumGeneratorPanel, 1, wxGROW | wxALL, 0 );
    m_catalogPanel = m_albumGeneratorPanel->GetCatalogPanel( );
    m_albumPanel = m_albumGeneratorPanel->GetAECmdDataManager( );
}

/*
 * Should we show tooltips?
 */

bool AlbumGenFrame::ShowToolTips( ) { return true; }

/*
 * Get bitmap resources
 */

wxBitmap AlbumGenFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    // AlbumGenFrame bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
    // AlbumGenFrame bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AlbumGenFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
    // AlbumGenFrame icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
    // AlbumGenFrame icon retrieval
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN
 */

void AlbumGenFrame::OnOpenClick( wxCommandEvent& event )
{
    Open( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE
 */

void AlbumGenFrame::OnSaveClick( wxCommandEvent& event )
{
    Save( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT
 */

void AlbumGenFrame::OnCSVImportClick( wxCommandEvent& event )
{
    DoCSVImport( );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT
 */

void AlbumGenFrame::OnAEImportClick( wxCommandEvent& event )
{
    ImportAlbumLayout( );

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMPORT in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_EXPORT
 */

void AlbumGenFrame::OnRevertToSavedClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_EXPORT in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_EXPORT in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
 */

void AlbumGenFrame::OnExitClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS
 */

void AlbumGenFrame::OnSaveasClick( wxCommandEvent& event )
{
    SaveAs( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVEAS in
    // AlbumGenFrame.
}

// void AlbumGenFrame::SetStamp( wxXmlNode* stamp )
// {
//     m_stamp->SetNodeElement( stamp );
//     m_albumGeneratorPanel->SetStamp( m_stamp );
// }

void AlbumGenFrame::UpdateStatus( ) { m_albumGeneratorPanel->UpdateStatus( ); }

// CatalogTreeCtrl* AlbumGenFrame::GetCatalogDataTree( )
// {
//     return m_mngCatalogData->GetCatalogDataTree( );
// };

// void AlbumGenFrame::LoadTree(Catalog *catalogData)
// {
//     m_selectionPanel->ClearTree();
//     m_selectionPanel->LoadTree(catalogData);
// }

void AlbumGenFrame::SaveCatalogXML( wxString filename )
{
    GetProject( )->GetCatalogData( )->SaveXML( filename );

    SetDirty( false );

    wxFileName newFile( filename );
    GetSettings( )->SetLastFile( newFile.GetFullName( ) );
    GetSettings( )->Save( );
}

void AlbumGenFrame::Save( )
{
    if ( GetProject( )->GetCatalogData( ) )
        // if (m_stampData && Dirty)
    {
        wxFileName filename( GetSettings( )->GetLastFile( ) );
        filename.SetExt( "xml" ); // make sure it is an xml

        SaveCatalogXML( filename.GetFullPath( ) );
    }
}

void AlbumGenFrame::SaveAs( )
{

    if ( GetProject( )->GetCatalogData( ) )
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

int AlbumGenFrame::ImageGallery( ) { }



int AlbumGenFrame::DoQueryMerge( int& mergeMethod )
{
    wxXmlNode* docRoot = 0;
    int mergeOverwriteQuery;

    Catalog::CatalogData* catalogData = GetProject( )->GetCatalogData( );
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

void AlbumGenFrame::Open( )
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
//    m_catalogPanel->InitCatalogData( );
//    m_catalogPanel->LoadCatalog( );
    // }
    // else // merge
    // {
    //     CatalogData* mergeCatalogData = NewCatalogData( );
    //     mergeCatalogData->LoadCatalog(  );   
    //     CatalogData* catalogData = GetCatalogData( );
    //     m_catalogPanel->ClearTree( );

    //     MergeStampsDialog mergeDialog;
    //     mergeDialog.InitializeMerge( mergeMethod, catalogData, mergeCatalogData );
    //     if ( mergeDialog.Create( this ) )
    //     {
    //         mergeDialog.ShowModal( );
    //     }
    //     delete mergeCatalogData;   
    //     m_catalogPanel->LoadTree( );

    // }
}



void AlbumGenFrame::DoCSVImport( )
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

//    m_catalogPanel->LoadCatalogCSV( filename );
    Dirty = true;
}

void AlbumGenFrame::ImportAlbumLayout( )
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

    m_albumPanel->LoadAlbumLayout( );

    Dirty = true;
}

// /*
//  * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
//  */

// void AlbumGenFrame::OnButtonClick(wxCommandEvent &event)
// {
//      // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in
//     AlbumGenFrame.
//     // Before editing this code, remove the block markers.
//     event.Skip();
//      // wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in
//     AlbumGenFrame.
// }
void AlbumGenFrame::DoDefinePeriodDialog( )
{
    DefinePeriodsDialog definePeriodsDialog( this, ID_DEFINEPERIODS,
        _( "Define Sort Order" ) );

    if ( definePeriodsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( definePeriodsDialog.IsDirty( ) )
    {
        // Save settings
        // resort tree
    }
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

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER
 */

void AlbumGenFrame::OnSortOrderClick( wxCommandEvent& event )
{
    DoSortOrderDialog( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_SORTORDER in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW
 */

void AlbumGenFrame::OnItemviewClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_ITEMVIEW in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD
 */

void AlbumGenFrame::OnDefineperiodClick( wxCommandEvent& event )
{
    DoDefinePeriodDialog( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_DEFINEPERIOD in
    // AlbumGenFrame.
}

static size_t write_data( void* ptr, size_t size, size_t nmemb, void* stream )
{
    size_t written = fwrite( ptr, size, nmemb, ( FILE* )stream );
    return written;
}

bool AlbumGenFrame::GetFile( wxString newFile, wxString imageName )
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
    const char* ptr = URLName1;
    const char* ptr2 = URLName1.ToUTF8( );
    curl_easy_setopt( curl_handle, CURLOPT_URL, ptr );

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt( curl_handle, CURLOPT_VERBOSE, 1L );

    /* disable progress meter, set to 0L to enable it */
    curl_easy_setopt( curl_handle, CURLOPT_NOPROGRESS, 1L );

    /* send all data to this function  */
    curl_easy_setopt( curl_handle, CURLOPT_WRITEFUNCTION, write_data );

    /* open the file */
    pagefile = fopen( imageName, "wb" );
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

void AlbumGenFrame::OnLoadimagesmenuitemClick( wxCommandEvent& event )
{
    // XMLIterator* parentIter = 0;
    // wxXmlDocument* doc = GetCatalogData( )->GetDoc( );
    // wxXmlNode* parent = doc->GetRoot( );
    // XMLIterator* iterator = new XMLIterator( parent );
    // wxXmlNode* item = iterator->First( );
    // while ( item )
    // {
    //     wxString name = item->GetName( );
    //     if ( !name.Cmp( "Stamp" ) )
    //     {
    //         const wxXmlAttribute* attr = item->GetAttribute( "ID_Nbr" );
    //         if ( attr )
    //         {
    //             const char* idStr = attr->GetValue( );
    //             wxString id = idStr;
    //             int i = id.Find( " " );
    //             if ( i >= 0 )
    //             {
    //                 wxString sp = " ";
    //                 wxString nullStr = "";
    //                 size_t size = id.Replace( sp, nullStr, true );
    //                 item->SetAttrStr( "ID_Nbr", id   );
    //             }
    //             std::cout << "Info: AlbumGenFrame Loadimages " << attr->GetValue( )
    //                 << "\n";
    //             wxFileName fileName;

    //             // fileName.SetPath(wxGetCwd());
    //             // fileName.AppendDir(wxT("Art"));
    //             // if (!fileName.DirExists())
    //             // {
    //             //     wxMkdir(wxString("Art"));
    //             // }
    //             wxString str = GetCatalogData( )->GetImageDirectory( );
    //             wxString imageName = wxString::Format( "%s/%s.jpg", str, attr->GetValue( ) );
    //             fileName.Assign( imageName );
    //             std::cout << "Info: AlbumGenFrame Loadimages "
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
    // ID_LOADIMAGESMENUITEM in AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_LOADIMAGESMENUITEM
    // in AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TESTXMLMENUITEM
 */

void AlbumGenFrame::OnTestXMLClick( wxCommandEvent& event )
{
    wxFileName* filename = new wxFileName(
        GetSettings( )->GetWorkingDirectory( ), "XMLTest", "xml" );
    wxString fullPath = filename->GetFullPath( );
    wxXmlDocument doc;
    bool ok = doc.Load( fullPath );

    if ( ok )
    {

        std::cout << fullPath << "Load Failed.\n";
    }

    wxXmlNode* root = doc.GetRoot( );
    // start processing the XML file
    wxString rootName = root->GetName( );
    wxString child = Utils::GetAttribute( root, "Child" )->GetValue( );
    wxString id = Utils::GetAttrStr( root, "id" );
    std::cout << "Root Value: " << rootName << "  Child:" << child
        << "  id:" << id << "\n";
    std::cout << " Testing decending entire file\n";
    std::cout << " ID numbers should be in order 1 thru 120\n";

    Utils::XMLIterator* iter = new Utils::XMLIterator( root );
    wxXmlNode* ele = iter->First( );
    while ( ele )
    {
        wxString eleName = ele->GetName( );
        child = Utils::GetAttrStr( ele, "Child" );
        id = Utils::GetAttrStr( ele, "id" );
        std::cout << eleName << "  Child:" << child << "  id:" << id << "\n";
        ele = iter->Next( );
    }
    delete iter;

    std::cout << " Testing No decend \n";
    std::cout
        << " first level is iterated and second level within each of those \n";

    iter = new Utils::XMLIterator( root, false );
    ele = iter->First( );
    while ( ele )
    {
        wxString name = ele->GetName( );
        child = Utils::GetAttrStr( ele, "Child" );
        id = Utils::GetAttrStr( ele, "id" );
        std::cout << name << "  Child:" << child << "  id:" << id << "\n";
        std::cout << "      Do next level only\n";
        Utils::XMLIterator* iter2 = new Utils::XMLIterator( ele, false );
        wxXmlNode* ele2 = iter2->First( );
        while ( ele2 )
        {
            name = ele2->GetName( );
            child = Utils::GetAttrStr( ele2, "Child" );
            id = Utils::GetAttrStr( ele2, "id" );
            std::cout << name << "        Child:" << child << "  id:" << id << "\n";

            ele2 = iter2->Next( );
        }
        ele = iter->Next( );
    }
    delete iter;

    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TESTXMLMENUITEM
    // in AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TESTXMLMENUITEM in
    // AlbumGenFrame.
}


void AlbumGenFrame::OnAlbumGenMenuItemClick( wxCommandEvent& event )
{

}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM
 */

void AlbumGenFrame::OnCVSReportMenuItemClick( wxCommandEvent& event )
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
        wxXmlDocument* doc = GetProject( )->GetCatalogData( )->GetDoc( );
        wxXmlNode* root = doc->GetRoot( );
        Utils::XMLIterator* iter = new Utils::XMLIterator( root );
        wxXmlNode* item = iter->First( );
        while ( item )
        {
            wxString name = item->GetName( );
            if ( !name.Cmp( Catalog::CatalogNodeNames[ Catalog::NT_Stamp ] ) )
            {
                Catalog::Stamp stamp( item );
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
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUITEM in
    // AlbumGenFrame.
}

/*
 * wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME
 */

void AlbumGenFrame::OnCloseWindow( wxCloseEvent& event )
{
    // wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_CLOSE_WINDOW event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGenFrame.
}

/*
 * wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME
 */

void AlbumGenFrame::OnIconize( wxIconizeEvent& event )
{
    // wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_ICONIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGenFrame.
}

/*
 * wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME
 */

void AlbumGenFrame::OnMaximize( wxMaximizeEvent& event )
{
    // wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_MAXIMIZE event handler for ID_ALBUMGENERATORFRAME in
    // AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TEXTSERCHMENUITEM
 */

void AlbumGenFrame::OnTextserchmenuitemClick( wxCommandEvent& event )
{
    // wxEVT_COMMAND_MENU_SELECTED event handler for
    // ID_TEXTSERCHMENUITEM in AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for ID_TEXTSERCHMENUITEM
    // in AlbumGenFrame.
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_IMAGEGALERYMENUITEM
 */

void AlbumGenFrame::OnImagegalerymenuitemClick( wxCommandEvent& event )
{
    ImageGallery( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for
    // ID_IMAGEGALERYMENUITEM in AlbumGenFrame.
    // Before editing this code, remove the block markers.
    event.Skip( );
    // wxEVT_COMMAND_MENU_SELECTED event handler for
    // ID_IMAGEGALERYMENUITEM in AlbumGenFrame.
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

void AlbumGenFrame::SetupRecentMenu( )
{
    // first clobber each of the current menuItems and unbind them.
    if ( m_menuItemList.size( ) > 0 )
    {
        for ( int i = 0; i < m_menuItemList.size( ); i++ )
        {
            RecentListItem* item = m_menuItemList[ i ];
            bool val = Unbind( wxEVT_MENU, &AlbumGenFrame::DoRecentSelection, this, item->id );
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

        Bind( wxEVT_MENU, &AlbumGenFrame::DoRecentSelection, this, listItem->id );
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

void AlbumGenFrame::OnSettingsClick( wxCommandEvent& event )
{
    DoSettingsDialog( );
    ////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS in AlbumGenFrame.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS in AlbumGenFrame. 
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE
 */

void AlbumGenFrame::OnMergeClick( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE in AlbumGenFrame.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_MENU_SELECTED event handler for ID_MERGE in AlbumGenFrame. 
}

