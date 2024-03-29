/*
 * @file CatalogPanel.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-22
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

#include <wx/filedlg.h> 
#include <wx/filename.h>
#include "wx/imaglist.h"
#include <wx/wfstream.h>

#include "Defs.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/CatalogTOCTreeCtrl.h"
#include "gui/CatalogPanel.h"
#include "gui/InventoryPanel.h"
#include "catalog/CatalogData.h"
#include "collection/CollectionList.h"
#include "collection/Collection.h"
#include "gui/FileCreateDialog.h"
#include "gui/RemoveVolumeDialog.h"
#include "gui/ComparePanel.h"

IMPLEMENT_DYNAMIC_CLASS( CatalogPanel, wxPanel )


BEGIN_EVENT_TABLE( CatalogPanel, wxPanel )
EVT_TEXT( ID_TEXTCTRL, CatalogPanel::OnTextctrlTextUpdated )
EVT_TOGGLEBUTTON( ID_TOGGLEBUTTON, CatalogPanel::OnTogglebuttonClick )
EVT_CHOICE( ID_VOLUMECHOICE, CatalogPanel::OnVolumeChoiceSelected )
//EVT_CHOICE( ID_COLLECTIONCHOICE, CatalogPanel::OnCollectionChoiceSelected )
EVT_BUTTON( ID_MANAGEBUTTON, CatalogPanel::OnManageClick )
//EVT_SPIN( ID_SPINBUTTON, CatalogPanel::OnSpinbuttonUpdated )
EVT_SPIN_UP( ID_SPINBUTTON, CatalogPanel::OnSpinbuttonUp )
EVT_SPIN_DOWN( ID_SPINBUTTON, CatalogPanel::OnSpinbuttonDown )
END_EVENT_TABLE( )

//--------------

CatalogPanel::CatalogPanel( )
{
    Init( );
}

//--------------

CatalogPanel::CatalogPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init( );
    Create( parent, id, pos, size, style );
}

//--------------

CatalogPanel::~CatalogPanel( )
{
}

//--------------

void CatalogPanel::Clear( )
{
    m_volumeListCtrl->ChangeValue( "" );

    //  m_collectionListCtrl->SetSelection( 0 );
    m_catalogTreeCtrl->Clear( );
    m_tocTreeCtrl->Clear( );

}

//--------------

bool CatalogPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
    return true;
}

//--------------

void CatalogPanel::CreateControls( )
{
    //   std::cout << "CatalogPanel" << "\n";

    CatalogPanel* itemPanel1 = this;

    m_catPanelSizer = new wxBoxSizer( wxVERTICAL );
    itemPanel1->SetSizer( m_catPanelSizer );
    // //@@@@@;
    // wxBoxSizer* collectionBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    // m_catPanelSizer->Add( collectionBoxSizer, 0, wxGROW | wxALL, 0 );

    // wxStaticText* collectionStaticText = new wxStaticText( itemPanel1, wxID_STATIC, _( "Collection" ), wxDefaultPosition, wxDefaultSize, 0 );
    // collectionBoxSizer->Add( collectionStaticText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    // m_collectionListCtrl = new wxChoice( itemPanel1, ID_COLLECTIONCHOICE, wxDefaultPosition, wxSize( -1, -1 ), GetCollectionList( )->GetNameArray( ), wxLB_HSCROLL );
    // collectionBoxSizer->Add( m_collectionListCtrl, 1, wxGROW | wxALL, 5 );

    // //@@@@@@@
    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    m_catPanelSizer->Add( itemBoxSizer1, 0, wxGROW | wxALL, 0 );

    // m_manageButton = new wxButton( itemPanel1, ID_MANAGEBUTTON, _( "Manage" ), wxDefaultPosition, wxDefaultSize, 0 );
    // itemBoxSizer1->Add( m_manageButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // itemBoxSizer1->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    //

    m_toggleButton = new wxToggleButton( itemPanel1, ID_TOGGLEBUTTON, _( "Search" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_toggleButton->SetValue( false );
    itemBoxSizer1->Add( m_toggleButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );


    m_searchSizer = new wxBoxSizer( wxHORIZONTAL );
    m_catPanelSizer->Add( m_searchSizer, 0, wxGROW | wxALL, 5 );
    wxBoxSizer* searchVerticalSizer = new wxBoxSizer( wxVERTICAL );
    m_searchSizer->Add( searchVerticalSizer, 1, wxGROW | wxALL, 5 );
    wxButton* itemButton9 = new wxButton( itemPanel1, ID_NEXTBUTTON, _( "Next" ), wxDefaultPosition, wxDefaultSize, 0 );
    searchVerticalSizer->Add( itemButton9, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxBoxSizer* searchHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    searchVerticalSizer->Add( searchHorizontalSizer, 1, wxGROW | wxALL, 5 );
    wxStaticText* itemStaticText11 = new wxStaticText( itemPanel1, wxID_STATIC, _( "Search\nString" ), wxDefaultPosition, wxDefaultSize, 0 );
    searchHorizontalSizer->Add( itemStaticText11, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxTextCtrl* itemTextCtrl12 = new wxTextCtrl( itemPanel1, ID_SEARCHSTRINGTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    searchHorizontalSizer->Add( itemTextCtrl12, 2, wxGROW | wxALL, 5 );

    wxArrayString itemCheckListBox13Strings;
    itemCheckListBox13Strings.Add( _( "Titles" ) );
    itemCheckListBox13Strings.Add( _( "Series" ) );
    itemCheckListBox13Strings.Add( _( "Themes" ) );
    wxCheckListBox* itemCheckListBox13 = new wxCheckListBox( itemPanel1, ID_CHECKLISTBOX, wxDefaultPosition, wxDefaultSize, itemCheckListBox13Strings, wxLB_SINGLE );
    m_searchSizer->Add( itemCheckListBox13, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    int lastID = ID_CatalogTOCTreeCtrl + 10;
    m_catalogPanelNotebook = new wxNotebook( itemPanel1, ++lastID, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
    m_catPanelSizer->Add( m_catalogPanelNotebook, 1, wxGROW | wxALL, 5 );

    m_tocTreeCtrl = new CatalogTOCTreeCtrl( m_catalogPanelNotebook, ID_CatalogTOCTreeCtrl, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxSUNKEN_BORDER | wxTR_DEFAULT_STYLE );
    m_catalogPanelNotebook->AddPage( m_tocTreeCtrl, _( "TOC" ) );



    wxPanel* catalogPanel = new wxPanel( m_catalogPanelNotebook, 12345, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
    wxBoxSizer* catPanelSizer = new wxBoxSizer( wxVERTICAL );
    catalogPanel->SetSizer( catPanelSizer );

    // wxStaticText* itemStaticText2 = new wxStaticText( itemPanel1, wxID_STATIC, _( "Volume" ), wxDefaultPosition, wxDefaultSize, 0 );
    // itemBoxSizer1->Add( itemStaticText2, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    wxBoxSizer* textboxSizer = new wxBoxSizer( wxHORIZONTAL );
    catPanelSizer->Add( textboxSizer, 0, wxGROW | wxALL, 0 );

    m_volumeListCtrl = new wxTextCtrl( catalogPanel, ID_VOLUMECHOICE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
    m_volumeListCtrl->SetEditable( false );
    Connect( ID_VOLUMECHOICE, wxEVT_CONTEXT_MENU, wxContextMenuEventHandler( CatalogPanel::OnContextMenu ) );//, NULL, this );
    // m_volumeListCtrl = new wxChoice( itemPanel1, ID_VOLUMECHOICE, wxDefaultPosition, wxSize( -1, -1 ), GetCatalogData( )->GetVolumeNameStrings( ), wxLB_HSCROLL );
    textboxSizer->Add( m_volumeListCtrl, 1, wxGROW | wxALL, 0 );

    m_spinButton = new wxSpinButton( catalogPanel, ID_SPINBUTTON, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL | wxSP_ARROW_KEYS | wxSP_WRAP );
    m_spinButton->SetRange( -0x8000, 0x7fff );
    m_spinButton->SetValue( 0 );
    textboxSizer->Add( m_spinButton, 0, wxLeft | wxALL, 0 );


    m_catalogTreeCtrl = new CatalogTreeCtrl( catalogPanel, ID_CATALOGTREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxSUNKEN_BORDER | wxTR_DEFAULT_STYLE );
    catPanelSizer->Add( m_catalogTreeCtrl, 1, wxGROW | wxALL, 0 );
    m_catalogTreeCtrl->SetToolTip( _( "Page layout height in mm." ) );

    m_catalogPanelNotebook->AddPage( catalogPanel, _( "Catalog" ) );


    m_searchSizer->Show( false );
    m_catPanelSizer->Layout( );
}

//--------------


void CatalogPanel::DoMergeCatalog( )
{
    ComparePanel comparePanel( this, ID_PREFERENCESDIALOG,
        _( "Merge Catalogs" ) );

    if ( comparePanel.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

}

void CatalogPanel::DoCSVImport( )
{
    Catalog::CatalogVolume* vol = GetCatalogVolume( );

    if ( vol && !vol->ContinueIfDirty( this ) )
    {
        return;
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
    if ( !wxFileExists( filename ) )
    {
        wxLogError( "DoCSVImport: File doesn't exist: '%s'.", filename );
        return;
    }

    if ( GetCatalogData( )->GetCatalogList( )->ImportCSV( filename ) )
    {
        GetCatalogData( )->GetCatalogList( )->GetVolume( )->SetDirty( true );
    }
}

//--------------

wxTreeItemId CatalogPanel::GetNext( wxTreeItemId& currID )
{

    wxTreeItemId nextID = m_tocTreeCtrl->GetNextSibling( currID );
    if ( nextID.IsOk( ) )
    {
        //the next entry is good
        TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( nextID );
        wxString name = m_tocTreeCtrl->GetItemText( nextID );
        //std::cout << name << "\n";
        if ( data->GetType( ) == Utils::TOC_Volume )
        {
            // and it is a volume entry
            return nextID;
        }
        else
        {
            // and it is a section entry
            return GetNextFirstChild( nextID );
        }
    }
    else
    {
        // no more children
        // go up a level and go to next entry
        return GetNextFirstChild( currID );
    }
}

//--------------

wxTreeItemId CatalogPanel::GetNextFirstChild( wxTreeItemId& currID )
{
    wxTreeItemId parentID = m_tocTreeCtrl->GetItemParent( currID );

    if ( !parentID.IsOk( ) )
    {
        return 0;
    }
    wxString name = m_tocTreeCtrl->GetItemText( parentID );
    //std::cout << name << "\n\n";


    wxTreeItemId nextID = m_tocTreeCtrl->GetNextSibling( parentID );
    if ( nextID.IsOk( ) )
    {
        wxString name = m_tocTreeCtrl->GetItemText( nextID );
        //std::cout << name << "\n";


        wxTreeItemIdValue cookie;
        nextID = m_tocTreeCtrl->GetFirstChild( nextID, cookie );
        if ( nextID.IsOk( ) )
        {
            wxString name = m_tocTreeCtrl->GetItemText( nextID );
            //std::cout << name << "\n";
            TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( nextID );

            if ( data->GetType( ) == Utils::TOC_Volume )
            {
                return nextID;
            }
            else
            {

                wxTreeItemIdValue cookie;
                nextID = m_tocTreeCtrl->GetFirstChild( nextID, cookie );
                //nextID = GetNext( nextID );
                return nextID;
            }
        }
        else
            return 0;
    }
    nextID = GetNextFirstChild( parentID );
    return nextID;
}

//--------------

wxTreeItemId CatalogPanel::GetPrev( wxTreeItemId& currID )
{

    wxTreeItemId nextID = m_tocTreeCtrl->GetPrevSibling( currID );
    if ( nextID.IsOk( ) )
    {
        //the next entry is good
        TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( nextID );
        wxString name = m_tocTreeCtrl->GetItemText( nextID );
        //std::cout << name << "\n";
        if ( data->GetType( ) == Utils::TOC_Volume )
        {
            // and it is a volume entry
            return nextID;
        }
        else
        {
            // and it is a section entry
            return GetPrevLastChild( nextID );
        }
    }
    else
    {
        // no more children
        // go up a level and go to next entry
        return GetPrevLastChild( currID );
    }
}

//--------------

wxTreeItemId CatalogPanel::GetPrevLastChild( wxTreeItemId& currID )
{
    wxTreeItemId parentID = m_tocTreeCtrl->GetItemParent( currID );

    if ( !parentID.IsOk( ) )
    {
        return 0;
    }
    wxString name = m_tocTreeCtrl->GetItemText( parentID );
    //std::cout << name << "\n\n";


    wxTreeItemId nextID = m_tocTreeCtrl->GetPrevSibling( parentID );
    if ( nextID.IsOk( ) )
    {
        wxString name = m_tocTreeCtrl->GetItemText( nextID );
        // std::cout << name << "\n";

        nextID = m_tocTreeCtrl->GetLastChild( nextID );
        if ( nextID.IsOk( ) )
        {
            wxString name = m_tocTreeCtrl->GetItemText( nextID );
            //std::cout << name << "\n";
            TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( nextID );

            if ( data->GetType( ) == Utils::TOC_Volume )
            {
                return nextID;
            }
            else
            {
                nextID = m_tocTreeCtrl->GetLastChild( nextID );
                //nextID = GetNext( nextID );
                return nextID;
            }
        }
        else
            return 0;
    }
    nextID = GetPrevLastChild( parentID );
    return nextID;
}

//--------------

void CatalogPanel::Init( )
{
    // m_title = NULL;
    m_catalogTreeCtrl = NULL;
}

//--------------

void CatalogPanel::NewCatalogDialog( )
{
    Catalog::CatalogVolume* vol = GetCatalogVolume( );

    if ( vol && !vol->ContinueIfDirty( this ) )
    {
        return;
    }

    FileCreateDialog fileDialog( this, 12355, _( "Select the Filename and Directory for the Design file." ) );
    wxGetCwd( );
    fileDialog.SetDefaultDirectory( wxGetCwd( ) );
    fileDialog.SetDefaultFilename( _( "unnamed.cat" ) );
    fileDialog.SetWildCard( _( "Design files(*.cat)|*.cat" ) );

    if ( fileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return;
    }

    wxString cwd = wxGetCwd( );
    wxFileName catFile( fileDialog.GetPath( ) );
    catFile.MakeRelativeTo( cwd );

    vol = GetCatalogData( )->GetCatalogList( )->AddNewVolume( catFile.GetFullPath( ) );

    GetCatalogTreeCtrl( )->LoadCatalogTree( );

    vol->SetDirty( );
}

//--------------

// void CatalogPanel::OnCollectionChoiceSelected( wxCommandEvent& event )
// {
//     wxTreeItemId id = m_catalogTreeCtrl->GetSelection( );
//     wxXmlNode* ele = m_catalogTreeCtrl->GetItemNode( id );

//     //m_catalogTreeCtrl->GetItemData( );
//     //int sel = m_collectionListCtrl->GetSelection( );
//     wxString sel = m_collectionListCtrl->GetStringSelection( );
//     GetCollectionList( )->SetCurrentCollection( sel );
//     GetCatalogData( )->GetInventoryPanel( )->UpdatePanel( );
//     m_catalogTreeCtrl->LoadTree( );
//     wxTreeItemId newID = m_catalogTreeCtrl->FindTreeItemID( ele );
//     if ( newID.IsOk( ) )
//         m_catalogTreeCtrl->SelectItem( newID );
//     event.Skip( );
// }

//--------------
void copyMenu( wxMenu* fromMenu, wxMenu* toMenu )
{
    wxMenuItemList& list = fromMenu->GetMenuItems( );
    wxMenuItemList::iterator iter;
    for ( iter = list.begin( ); iter != list.end( ); ++iter )
    {
        wxMenuItem* item = *iter;
        int itemID = item->GetId( );
        wxString label = item->GetItemLabelText( );
        wxMenu* oldMenu = item->GetSubMenu( );
        if ( oldMenu )
        {
            wxMenu* newMenu = new wxMenu( );
            toMenu->Append( itemID, label, newMenu );
            copyMenu( oldMenu, newMenu );
        }
        else
        {
            toMenu->Append( itemID, label );
        }
    }
}
void CatalogPanel::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint point = event.GetPosition( );

    point = ScreenToClient( point );

    wxMenu contextMenu;
    wxMenu* newSubmenu = new wxMenu( );
    contextMenu.AppendSubMenu( newSubmenu, " Select Collection" );
    wxArrayString& collectionList = GetCollectionList( )->GetNameArray( );
    for ( int i = 0; i < collectionList.size( ); i++ )
    {
        wxString collection = collectionList.Item( i );
        wxMenuItem* item = newSubmenu->Append( i, collection );
    }
    wxMenu* newVolMenu = new wxMenu( );
    contextMenu.AppendSubMenu( newVolMenu, " Select Volume" );

    wxMenu* menu = m_tocTreeCtrl->GetMenu( );
    copyMenu( menu, newVolMenu );

    int id = GetPopupMenuSelectionFromUser( contextMenu, point.x, point.y );

    if ( id >= IDCatalogMenuID )
    {
        wxTreeItemId treeId = GetCatalogData( )->GetCatalogList( )->FindMenuID( id );
        if ( treeId.IsOk( ) )
        {
            m_tocTreeCtrl->SelectItem( treeId );

            //TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( treeId );
            //wxString name = m_tocTreeCtrl->GetItemText( treeId );
            SetVolumeListCtrl( );
        }
    }
    else
    {
        if ( id >= 0 && id < collectionList.Count( ) )
        {
            Inventory::Collection* collection = GetCollectionList( )->FindCollection( collectionList.Item( id ) );
            GetCatalogData( )->SetCollection( collection->GetName( ) );
            //GetCollectionList( )->SetCurrentCollection( collectionList.Item( id ) );

        }
    }
}
//--------------

void CatalogPanel::OnCSVImportClick( wxCommandEvent& event )
{
    DoCSVImport( );
    event.Skip( );
}


//--------------

void CatalogPanel::OnManageClick( wxCommandEvent& event )
{
    wxMenu m_designMenu;
    m_designMenu.Append( ID_NEWCATALOG, _( "New Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_OPENCATALOG, _( "Open Catalog File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_CSVIMPORTCATALOG, _( "Import Catalog from CSV File" ), wxEmptyString, wxITEM_NORMAL );
    m_designMenu.Append( ID_REMOVECATALOG, _( "Remove Catalog File" ), wxEmptyString, wxITEM_NORMAL );

    switch ( GetPopupMenuSelectionFromUser( m_designMenu ) )
    {
        case ID_NEWCATALOG:
        {
            NewCatalogDialog( );
            break;
        }
        case ID_OPENCATALOG:
        {
            OpenCatalog( );
            break;
        }
        case ID_CSVIMPORTCATALOG:
        {
            DoCSVImport( );
            break;
        }
        case ID_REMOVECATALOG:
        {

            RemoveVolume( );
            break;
        }
    }
}

//--------------

void CatalogPanel::OnTextctrlTextUpdated( wxCommandEvent& event )
{

    event.Skip( );

}

//--------------

void CatalogPanel::OnTogglebuttonClick( wxCommandEvent& event )
{
    if ( m_toggleButton->GetValue( ) )
    {
        m_searchSizer->Show( true );
        //m_searchSizer->Hide( m_catPanelSizer, true );
    }
    else
    {
        m_searchSizer->Show( false );
        //    m_searchSizer->Hide( m_catPanelSizer, false );
    }
    m_catPanelSizer->Layout( );

    event.Skip( );

}

//--------------

void CatalogPanel::OnVolumeChoiceSelected( wxCommandEvent& event )
{
    Catalog::CatalogList* list = GetCatalogData( )->GetCatalogList( );
    wxString sel = m_volumeListCtrl->GetStringSelection( );
    Catalog::CatalogVolume* vol = ( Catalog::CatalogVolume* ) list->FindVolume( sel );
    list->SetCurrentVolume( vol );
    // wxString strSel = m_status->GetStringSelection( );
    // if ( m_stamp )
    // { 
    //     m_stamp->SetInventoryStatus( strSel );
    //     GetCatalogTreeCtrl( )->SetInventoryStatusImage( );
    // }

    event.Skip( );

}

//--------------

void CatalogPanel::OpenCatalog( )
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
        _( "unnamed.cat" ),
        "Catalog XML files(*.cat)|*.cat", wxFD_OPEN | wxFD_FILE_MUST_EXIST );
    if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
    {
        return; // the user changed idea...
    }

    wxString cwd = wxGetCwd( );
    wxFileName catFile( openFileDialog.GetPath( ) );
    catFile.MakeRelativeTo( cwd );
    GetCatalogData( )->FileOpen( catFile.GetFullPath( ) );
}

//--------------

void CatalogPanel::RemoveVolume( )
{
    // wxArrayString array = GetCatalogData( )->GetVolumeNameStrings( );
    // RemoveVolumeDialog  dialog( ( wxWindow* ) this,
    //     "Remove Catalog Volume From Project",
    //     "Select Volume to remove:",
    //     array );
    // dialog.ShowModal( );

}

//--------------

void CatalogPanel::SaveAsCatalog( )
{

    // if ( GetCatalogVolume( ) )
    // { 
    //     wxFileName lastFile( GetProject( )->GetCatalogFilename( ) );
    //     lastFile.SetExt( "xml" );
    //     wxFileDialog saveFileDialog( 
    //         this, _( "Stamp List XML file" ), 
    //         lastFile.GetPath( ), lastFile.GetFullName( ), 
    //         "XML files (*.cat)|*.cat", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
    //     if ( saveFileDialog.ShowModal( ) == wxID_CANCEL )
    //         return;

    //     wxString filename = saveFileDialog.GetPath( );
    //     GetFrame( )->FileSaveAsCatalog( filename );
    // }
}

//--------------

// void CatalogPanel::SetCollectionListSelection( )
// {
//     m_collectionListCtrl->SetStringSelection( GetCollectionList( )->GetCurrentName( ) );
// };

//--------------

void CatalogPanel::OnSpinbuttonDown( wxSpinEvent& event )
{

    wxTreeItemId currID = m_tocTreeCtrl->GetSelection( );
    wxTreeItemId nextID = GetNext( currID );

    // wxTreeItemId nextID = m_tocTreeCtrl->GetNextSibling( currID );
    if ( nextID.IsOk( ) )
    {
        m_tocTreeCtrl->SelectItem( nextID );
        SetVolumeListCtrl( );

        //     TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( nextID );
        // wxString name = m_tocTreeCtrl->GetItemText( nextID );
        // //std::cout << name << "\n";
        // m_volumeListCtrl->SetValue( name );
    }

}

//--------------

void CatalogPanel::OnSpinbuttonUp( wxSpinEvent& event )
{

    wxTreeItemId currID = m_tocTreeCtrl->GetSelection( );
    wxTreeItemId prevID = GetPrev( currID );
    if ( prevID.IsOk( ) )
    {
        m_tocTreeCtrl->SelectItem( prevID );
        SetVolumeListCtrl( );
        // TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( prevID );
        // wxString name = m_tocTreeCtrl->GetItemText( prevID );
        // m_volumeListCtrl->SetValue( name );
    }

    //   event.Skip( );
}

//--------------

void CatalogPanel::OnSpinbuttonUpdated( wxSpinEvent& event )
{

    event.Skip( );
}

//--------------

void CatalogPanel::SetVolumeListCtrl( )
{
    wxTreeItemId treeId = GetCatalogTOCTreeCtrl( )->GetSelection( );
    // TOCTreeItemData* data = ( TOCTreeItemData* ) m_tocTreeCtrl->GetItemData( treeId );
    wxString volName = m_tocTreeCtrl->GetItemText( treeId );

    wxString colName = "";
    Inventory::Collection* collection = GetCollectionList( )->GetCurrentCollection( );
    if ( collection )
    {
        colName = collection->GetName( );
    }

    m_volumeListCtrl->SetValue( volName + " - " + colName );
}

//--------------

bool CatalogPanel::ShowToolTips( )
{
    return true;
}

//--------------
