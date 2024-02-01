/*
 * @file src/gui/ComparePanel.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
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


#include "ComparePanel.h"
#include "Defs.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogList.h"
#include "gui/CompEntry.h"
#include "gui/CompareTreeCtrl.h"
#include "art/down.xpm"
#include "art/up.xpm"
#include "art/copy.xpm"
#include "art/redo.xpm"
#include "art/back.xpm"



IMPLEMENT_DYNAMIC_CLASS( ComparePanel, wxDialog )

BEGIN_EVENT_TABLE( ComparePanel, wxDialog )

EVT_LIST_ITEM_SELECTED( ID_LISTCTRL, ComparePanel::OnListCtrlSelected )
EVT_RADIOBUTTON( ID_DEEPRADIOBUTTON, ComparePanel::OnDeepRadioButton )
EVT_RADIOBUTTON( ID_SELECTEDRADIOBUTTON, ComparePanel::OnSelectedRadioButton )
EVT_LISTBOX_DCLICK( ID_CHECKLISTBOX, ComparePanel::OnChecklistboxDoubleClicked )
EVT_LISTBOX( ID_CHECKLISTBOX, ComparePanel::OnChecklistboxSelected )
EVT_CHECKLISTBOX( ID_CHECKLISTBOX, ComparePanel::OnCheckListBoxToggled )
END_EVENT_TABLE( )



ComparePanel::ComparePanel( )
{
    Init( );
}

ComparePanel::ComparePanel( wxWindow* parent,
    wxWindowID id,
    const wxString& caption,
    const wxPoint& pos,
    const wxSize& size,
    long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}



bool ComparePanel::Create( wxWindow* parent,
    wxWindowID id,
    const wxString& caption,
    const wxPoint& pos,
    const wxSize& size,
    long style )
{

    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    Centre( );

    return true;
}



ComparePanel::~ComparePanel( )
{

}



void ComparePanel::Init( )
{

    m_targetFile = NULL;
    m_typeName = NULL;
    m_typeName = NULL;
    m_targetVal = NULL;
    m_copyAllButton = NULL;
    //   m_undo = NULL;
    m_mergeVal = NULL;
    m_typeName = NULL;

    m_mergeList = new Catalog::MergeList( this );
    m_mergeList->SetComparePanel( this );

}




void ComparePanel::CreateControls( )
{


    ComparePanel* theDialog = this;

    wxBoxSizer* topVerticalSizer = new wxBoxSizer( wxVERTICAL );
    theDialog->SetSizer( topVerticalSizer );

    // control buttons

    wxBoxSizer* ctrlButtonHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    topVerticalSizer->Add( ctrlButtonHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxButton* updateTargetButton = new wxButton( theDialog, wxID_UPDATETAEGET, _( "Update Target File" ), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlButtonHorizontalSizer->Add( updateTargetButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( wxID_UPDATETAEGET, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnUpdateTarget ) );


    wxButton* updateMergeFileButton = new wxButton( theDialog, wxID_UPDATEMERGE, _( "Update Merge File" ), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlButtonHorizontalSizer->Add( updateMergeFileButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( wxID_UPDATEMERGE, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnUpdateMerge ) );

    wxButton* clearButton = new wxButton( theDialog, wxID_CLEAR, _( "Clear" ), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlButtonHorizontalSizer->Add( clearButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( wxID_CLEAR, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnClear ) );


    // target file select

    wxBoxSizer* fileHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    topVerticalSizer->Add( fileHorizontalSizer, 0, wxGROW | wxALL, 5 );

    wxStaticBox* targetStaticBoxSizer = new wxStaticBox( theDialog, wxID_ANY, _( "Target File" ) );
    wxStaticBoxSizer* targetFileSizer = new wxStaticBoxSizer( targetStaticBoxSizer, wxHORIZONTAL );
    fileHorizontalSizer->Add( targetFileSizer, 1, wxGROW | wxLEFT, 5 );

    GetCatalogData( )->GetCatalogList( )->MakeNameArray( m_catalogListCtrlStrings );

    m_targetFile = new wxChoice( targetFileSizer->GetStaticBox( ), ID_TARGETFILE,
        wxDefaultPosition, wxDefaultSize,
        m_catalogListCtrlStrings );
    m_targetFile->SetSelection( 0 );
    Connect( ID_TARGETFILE, wxEVT_CHOICE, wxCommandEventHandler( ComparePanel::OnTargetFileTextUpdated ) );

    targetFileSizer->Add( m_targetFile, 1, wxGROW | wxTOP, 5 );


    // merge file select



    wxStaticBox* mergeStaticBoxSizer = new wxStaticBox( theDialog, wxID_ANY, _( "Merge File" ) );
    wxStaticBoxSizer* mergeFileSizer = new wxStaticBoxSizer( mergeStaticBoxSizer, wxHORIZONTAL );
    fileHorizontalSizer->Add( mergeFileSizer, 1, wxGROW | wxLEFT, 5 );


    m_mergeFile = new wxChoice( mergeFileSizer->GetStaticBox( ), ID_MERGEFILE,
        wxDefaultPosition, wxDefaultSize,
        m_catalogListCtrlStrings );
    m_mergeFile->SetSelection( 0 );
    Connect( ID_MERGEFILE, wxEVT_CHOICE, wxCommandEventHandler( ComparePanel::OnMergeFileTextUpdated ) );

    mergeFileSizer->Add( m_mergeFile, 1, wxGROW | wxTOP, 5 );




    wxSplitterWindow* mainSplitterWindow = new wxSplitterWindow( theDialog, ID_SPLITTERWINDOW, wxDefaultPosition, wxSize( 100, 100 ), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER );
    mainSplitterWindow->SetMinimumPaneSize( 0 );


    // Merge entry list

   // wxScrolledWindow* entryListScrolledWindow = new wxScrolledWindow( mainSplitterWindow, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxSize( 100, 100 ), wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );
   // entryListScrolledWindow->SetScrollbars( 1, 1, 0, 0 );
    wxPanel* entryListScrolledWindow = new wxPanel( mainSplitterWindow, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );



    wxBoxSizer* entryListVerticalSizer = new wxBoxSizer( wxVERTICAL );
    entryListScrolledWindow->SetSizer( entryListVerticalSizer );


    //wxListCtrl* itemListCtrl4 = new wxListCtrl( itemScrolledWindow2, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );

    // m_listBox = new wxListView( entryListScrolledWindow, ID_LISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL );
    // entryListVerticalSizer->Add( m_listBox, 1, wxGROW | wxALL, 5 );

    m_compareTreeCtrl = new CompareTreeCtrl( entryListScrolledWindow, ID_LISTCTRL, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE | wxSUNKEN_BORDER | wxTR_DEFAULT_STYLE );
    entryListVerticalSizer->Add( m_compareTreeCtrl, 1, wxGROW | wxALL, 0 );
    m_compareTreeCtrl->SetComparePanel( this );

    entryListScrolledWindow->FitInside( );


    //Attrib Diff panel


    wxPanel* mainAttributePanel = new wxPanel( mainSplitterWindow, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL );
    mainAttributePanel->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
    wxBoxSizer* entryDiffVerticalSizer = new wxBoxSizer( wxVERTICAL );
    mainAttributePanel->SetSizer( entryDiffVerticalSizer );

    wxBoxSizer* controlButtonHorizontalSizer = new wxBoxSizer( wxHORIZONTAL );
    entryDiffVerticalSizer->Add( controlButtonHorizontalSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxStaticBox* entryStaticBoxSizer = new wxStaticBox( mainAttributePanel, wxID_ANY, _( "Entry" ) );
    wxStaticBoxSizer* entrySelectBoxSizer = new wxStaticBoxSizer( entryStaticBoxSizer, wxHORIZONTAL );
    controlButtonHorizontalSizer->Add( entrySelectBoxSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBitmapButton* downButton = new wxBitmapButton( entrySelectBoxSizer->GetStaticBox( ), ID_NEXTENTRY, wxBitmap( down_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    entrySelectBoxSizer->Add( downButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( ID_NEXTENTRY, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnNextentryClick ) );

    wxBitmapButton* upButton = new wxBitmapButton( entrySelectBoxSizer->GetStaticBox( ), ID_PREVENTRY, wxBitmap( up_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    entrySelectBoxSizer->Add( upButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( ID_PREVENTRY, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnPrevEntryClick ) );


    wxStaticBox* compareStaticBox = new wxStaticBox( entrySelectBoxSizer->GetStaticBox( ), wxID_ANY, _( "Compare Type" ) );
    wxStaticBoxSizer* compareStaticBoxSizer = new wxStaticBoxSizer( compareStaticBox, wxHORIZONTAL );
    entrySelectBoxSizer->Add( compareStaticBoxSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* radioButtonVSizer = new wxBoxSizer( wxVERTICAL );
    compareStaticBoxSizer->Add( radioButtonVSizer, 0, wxALIGN_TOP | wxALL, 5 );

    m_deepCompare = new wxRadioButton( compareStaticBoxSizer->GetStaticBox( ), ID_DEEPRADIOBUTTON, _( "Deep" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_deepCompare->SetValue( false );
    radioButtonVSizer->Add( m_deepCompare, 0, wxALIGN_LEFT | wxALL, 5 );

    m_SelectedCompare = new wxRadioButton( compareStaticBoxSizer->GetStaticBox( ), ID_SELECTEDRADIOBUTTON, _( "Selected" ), wxDefaultPosition, wxDefaultSize, 0 );
    m_SelectedCompare->SetValue( false );
    radioButtonVSizer->Add( m_SelectedCompare, 0, wxALIGN_LEFT | wxALL, 5 );

    wxBoxSizer* checkBoxVSizer = new wxBoxSizer( wxVERTICAL );
    compareStaticBoxSizer->Add( checkBoxVSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );



    wxArrayString m_CompareCheckBoxStrings;
    for ( int i = 0; i < Catalog::DT_NbrTypes; i++ )
    {
        m_CompareCheckBoxStrings.Add( Catalog::DataTypeNames[ ( Catalog::DataTypes ) i ] );
    }
    m_CompareCheckBox = new wxCheckListBox( compareStaticBoxSizer->GetStaticBox( ), ID_CHECKLISTBOX, wxDefaultPosition, wxSize( -1, 40 ), m_CompareCheckBoxStrings, wxLB_MULTIPLE | wxLB_ALWAYS_SB );
    checkBoxVSizer->Add( m_CompareCheckBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );


    // wxStaticBox* showStaticBoxSizer = new wxStaticBox( mainAttributePanel, wxID_ANY, _( "Show" ) );
    // wxStaticBoxSizer* showSelectBoxSizer = new wxStaticBoxSizer( showStaticBoxSizer, wxHORIZONTAL );
    // controlButtonHorizontalSizer->Add( showSelectBoxSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // wxRadioButton* diffButton = new wxRadioButton( showSelectBoxSizer->GetStaticBox( ), ID_SHOWDIFFSONLY, _( "Differences" ), wxDefaultPosition, wxDefaultSize, 0 );
    // diffButton->SetValue( false );
    // showSelectBoxSizer->Add( diffButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    // Connect( ID_SHOWDIFFSONLY, wxEVT_RADIOBUTTON, wxCommandEventHandler( ComparePanel::OnShowDiffsOnlySelected ) );

    // wxRadioButton* allButton = new wxRadioButton( showSelectBoxSizer->GetStaticBox( ), ID_SHOWALL, _( "All" ), wxDefaultPosition, wxDefaultSize, 0 );
    // allButton->SetValue( false );
    // showSelectBoxSizer->Add( allButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    // Connect( ID_SHOWALL, wxEVT_RADIOBUTTON, wxCommandEventHandler( ComparePanel::OnShowallSelected ) );




    wxBoxSizer* attributeHeaderBoxSizer = new wxBoxSizer( wxHORIZONTAL );
    entryDiffVerticalSizer->Add( attributeHeaderBoxSizer, 0, wxGROW | wxALL, 0 );

    m_typeName = new wxStaticText( mainAttributePanel, wxID_STATIC, _( "Attribute" ), wxDefaultPosition, wxSize( 150, -1 ), wxALIGN_RIGHT );
    attributeHeaderBoxSizer->Add( m_typeName, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5 );

    wxStaticText* targetStatic = new wxStaticText( mainAttributePanel, wxID_STATIC, _( "Target" ), wxDefaultPosition, wxDefaultSize, 0 );
    attributeHeaderBoxSizer->Add( targetStatic, 6, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    m_copyAllButton = new wxBitmapButton( mainAttributePanel, ID_COPYALL, wxBitmap( copy_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    if ( ComparePanel::ShowToolTips( ) )
        m_copyAllButton->SetToolTip( _( "Merge All" ) );
    m_copyAllButton->SetName( wxT( "mergeAll" ) );
    attributeHeaderBoxSizer->Add( m_copyAllButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    // EVT_BUTTON( ID_COPYALL, ComparePanel::OnCopyAllClick )
    Connect( ID_COPYALL, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnCopyAllClick ) );

    wxBitmapButton* undoCopyAllButton = new wxBitmapButton( mainAttributePanel, ID_UNDOCOPYALL, wxBitmap( redo_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    if ( ComparePanel::ShowToolTips( ) )
        undoCopyAllButton->SetToolTip( _( "Undo Merge All" ) );
    attributeHeaderBoxSizer->Add( undoCopyAllButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* mergeStatic = new wxStaticText( mainAttributePanel, wxID_STATIC, _( "Merge" ), wxDefaultPosition, wxDefaultSize, 0 );
    attributeHeaderBoxSizer->Add( mergeStatic, 6, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( ID_UNDOCOPYALL, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnUndoCopyAllClick ) );





    wxScrolledWindow* attributeScrolledWindow = new wxScrolledWindow( mainAttributePanel, ID_SCROLLEDWINDOW, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL );
    entryDiffVerticalSizer->Add( attributeScrolledWindow, 2, wxGROW | wxALL, 5 );
    attributeScrolledWindow->SetScrollbars( 1, 1, 0, 0 );
    wxBoxSizer* attribiteVerticalSizer = new wxBoxSizer( wxVERTICAL );
    attributeScrolledWindow->SetSizer( attribiteVerticalSizer );

    int lastID = ID_LISTCTRL + 1;
    for ( int i = 0; i < Catalog::DT_NbrTypes; i++ )
    {
        m_compEntry[ i ] = new CompEntry( attributeScrolledWindow, lastID++ );
        m_compEntry[ i ]->SetComparePanel( this );
        m_compEntry[ i ]->SetTypeName( Catalog::DataTypeNames[ ( Catalog::DataTypes ) i ] );
        attribiteVerticalSizer->Add( m_compEntry[ i ], 1, /*wxALIGN_CENTER_HORIZONTAL*/ wxGROW | wxALL, 0 );
    }

    attributeScrolledWindow->FitInside( );




    mainSplitterWindow->SplitVertically( entryListScrolledWindow, mainAttributePanel, 200 );
    topVerticalSizer->Add( mainSplitterWindow, 1, wxGROW | wxALL, 5 );


    wxBoxSizer* dialogCtrlButtonSizer = new wxBoxSizer( wxHORIZONTAL );
    topVerticalSizer->Add( dialogCtrlButtonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

    wxButton* cancelButton = new wxButton( theDialog, wxID_CANCEL, _( "Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( cancelButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( wxID_CANCEL, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnCancelClick ) );

    wxButton* okButton = new wxButton( theDialog, wxID_OK, _( "OK" ), wxDefaultPosition, wxDefaultSize, 0 );
    dialogCtrlButtonSizer->Add( okButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    Connect( wxID_OK, wxEVT_BUTTON, wxCommandEventHandler( ComparePanel::OnOkClick ) );


}


bool ComparePanel::ShowToolTips( )
{
    return true;
}

wxBitmap ComparePanel::GetBitmapResource( const wxString& name )
{
    wxUnusedVar( name );
    if ( name == wxT( "../../../../sandbox/Applications/wx/wxWidgets-3.2.3/art/down.xpm" ) )
    {
        wxBitmap bitmap( down_xpm );
        return bitmap;
    }
    else if ( name == wxT( "../../../../sandbox/Applications/wx/wxWidgets-3.2.3/art/up.xpm" ) )
    {
        wxBitmap bitmap( up_xpm );
        return bitmap;
    }
    else if ( name == wxT( "../../../../sandbox/Applications/wx/wxWidgets-3.2.3/art/copy.xpm" ) )
    {
        wxBitmap bitmap( copy_xpm );
        return bitmap;
    }
    else if ( name == wxT( "../../../../sandbox/Applications/wx/wxWidgets-3.2.3/art/redo.xpm" ) )
    {
        wxBitmap bitmap( redo_xpm );
        return bitmap;
    }
    else if ( name == wxT( "../../../../sandbox/Applications/wx/wxWidgets-3.2.3/art/back.xpm" ) )
    {
        wxBitmap bitmap( back_xpm );
        return bitmap;
    }
    return wxNullBitmap;
}

wxIcon ComparePanel::GetIconResource( const wxString& name )
{
    wxUnusedVar( name );
    return wxNullIcon;
}

void ComparePanel::OnTargetFileTextUpdated( wxCommandEvent& event )
{
    m_mergeList->SetTargetRoot( ( wxXmlNode* ) 0 );
    m_compareTreeCtrl->Clear( );
    m_mergeList->Clear( );

    // wxListItem itemCol;
    // itemCol.SetText( "Entries                                  " );
    // itemCol.SetImage( -1 );
    // itemCol.SetWidth( 300 );
    // m_listBox->InsertColumn( 0, itemCol );
    // m_listBox->SetColumnWidth( 0, wxLIST_AUTOSIZE_USEHEADER );

    int sel = m_targetFile->GetSelection( );

    wxString str = m_catalogListCtrlStrings[ sel ];
    m_targetVolume = GetCatalogData( )->GetCatalogList( )->FindVolume( str );
    // m_mergeList->SetTargetRoot( m_targetVolume->GetDoc( )->GetRoot( ) );
    if ( m_targetVolume )
        m_compareTreeCtrl->LoadCompareTree( m_targetVolume->GetDoc( )->GetRoot( ) );


    sel = m_mergeFile->GetSelection( );
    if ( sel >= 0 && sel < m_catalogListCtrlStrings.Count( ) )
    {
        str = m_catalogListCtrlStrings[ sel ];
        m_mergeVolume = GetCatalogData( )->GetCatalogList( )->FindVolume( str );
        if ( m_mergeVolume )
            m_compareTreeCtrl->LoadMergeToCompareTree( m_mergeVolume->GetDoc( )->GetRoot( ) );

        m_mergeList->SetStatus( );
    }
    event.Skip( );
}

void ComparePanel::SetBackground( )
{

    // m_mergeList->SetStatus( );

    // int pos = 0;
    // Catalog::MergeEntryList* list = m_mergeList->GetMergeList( );
    // for ( Catalog::MergeEntryList::iterator it = std::begin( *list );
    //     it != std::end( *list );
    //     ++it )
    // {
    //     Catalog::MergeData* mergeEntry = ( Catalog::MergeData* ) ( *it );
    //     m_listBox->SetItemBackgroundColour( pos, mergeEntry->GetColour( ) );

    // }
}

void ComparePanel::OnMergeFileTextUpdated( wxCommandEvent& event )
{
    m_compareTreeCtrl->Clear( );
    m_mergeList->Clear( );


    // wxListItem itemCol;
    // itemCol.SetText( "Entries                                  " );
    // itemCol.SetImage( -1 );
    // itemCol.SetWidth( 300 );
    // m_listBox->InsertColumn( 0, itemCol );
    // m_listBox->SetColumnWidth( 0, wxLIST_AUTOSIZE_USEHEADER );


    int sel = m_targetFile->GetSelection( );
    wxString str = m_catalogListCtrlStrings[ sel ];
    if ( m_targetVolume )
        m_targetVolume = GetCatalogData( )->GetCatalogList( )->FindVolume( str );

    m_compareTreeCtrl->LoadCompareTree( m_targetVolume->GetDoc( )->GetRoot( ) );

    sel = m_mergeFile->GetSelection( );
    if ( sel >= 0 && sel < m_catalogListCtrlStrings.Count( ) )
    {
        str = m_catalogListCtrlStrings[ sel ];
        m_mergeVolume = GetCatalogData( )->GetCatalogList( )->FindVolume( str );
        if ( m_mergeVolume )
            m_compareTreeCtrl->LoadMergeToCompareTree( m_mergeVolume->GetDoc( )->GetRoot( ) );

        m_mergeList->SetStatus( );
    }
    event.Skip( );
}



void ComparePanel::OnNextentryClick( wxCommandEvent& event )
{

    wxTreeItemId sel = m_compareTreeCtrl->GetSelection( );
    sel = m_compareTreeCtrl->FindNextEntryItem( sel );
    if ( sel.IsOk( ) )
    {
        m_compareTreeCtrl->SelectItem( sel );
    }

    event.Skip( );
}


void ComparePanel::OnPrevEntryClick( wxCommandEvent& event )
{

    wxTreeItemId sel = m_compareTreeCtrl->GetSelection( );
    sel = m_compareTreeCtrl->FindPrevEntryItem( sel );
    if ( sel.IsOk( ) )
    {
        m_compareTreeCtrl->SelectItem( sel );
    }
    event.Skip( );
}


void ComparePanel::OnShowDiffsOnlySelected( wxCommandEvent& event )
{
    event.Skip( );
}



void ComparePanel::OnShowallSelected( wxCommandEvent& event )
{
    event.Skip( );
}


void ComparePanel::OnCopyAllClick( wxCommandEvent& event )
{
    // long sel = m_listBox->GetFocusedItem( );
    wxTreeItemId sel = m_compareTreeCtrl->GetSelection( );


    CompareTreeItemData* data = ( CompareTreeItemData* ) m_compareTreeCtrl->GetItemData( sel );
    Catalog::MergeData* mergeEntry = ( Catalog::MergeData* ) data->GetMergeData( );;
    Catalog::Entry* targetCatEntry = mergeEntry->GetTargetEntry( );
    Catalog::Entry* mergeCatEntry = mergeEntry->GetMergeEntry( );
    if ( !targetCatEntry )
    {
        wxXmlNode* node = mergeCatEntry->GetCatXMLNode( );

        wxXmlNode* newTargetNode = new wxXmlNode( 0, wxXML_ELEMENT_NODE, node->GetName( ) );

        Utils::CopyNode( node, newTargetNode );
        wxXmlNode* root = m_mergeList->GetTargetRoot( );
        Catalog::AddEntry( root, newTargetNode, 0 );
    }
    else
    {
        for ( int i = 0; i < Catalog::DT_NbrTypes; i++ )
        {
            m_compEntry[ i ]->CopyAttribute( );
        }
    }
    event.Skip( );
}



void ComparePanel::OnUndoCopyAllClick( wxCommandEvent& event )
{
    for ( int i = 0; i < Catalog::DT_NbrTypes; i++ )
    {
        m_compEntry[ i ]->UndoAttribCopy( );
    }

    event.Skip( );
}

void ComparePanel::OnOkClick( wxCommandEvent& event )
{
    event.Skip( );
}
void ComparePanel::OnCancelClick( wxCommandEvent& event )
{
    event.Skip( );
}

void ComparePanel::OnUpdateTarget( wxCommandEvent& event )
{
    event.Skip( );
}

void ComparePanel::OnUpdateMerge( wxCommandEvent& event )
{
    event.Skip( );
}
void ComparePanel::OnClear( wxCommandEvent& event )
{
    event.Skip( );
}

void ComparePanel::OnListCtrlSelected( wxListEvent& event )
{
    // wxListItem item = event.GetItem( );
    // Catalog::MergeData* mergeEntry = ( Catalog::MergeData* ) item.GetData( );
    // UpdateCompEntryTable(  mergeEntry  );
}

void ComparePanel::UpdateCompEntryTable( Catalog::MergeData* mergeEntry )
{
    Catalog::Entry* targetCatEntry = mergeEntry->GetTargetEntry( );
    Catalog::Entry* mergeCatEntry = mergeEntry->GetMergeEntry( );
    if ( !mergeCatEntry )
    {
        m_copyAllButton->Disable( );
        //    m_undo->Disable( );
    }
    else
    {
        m_copyAllButton->Enable( );
        //    m_undo->Enable( );
    }

    for ( int i = 0; i < Catalog::DT_NbrTypes; i++ )
    {
        m_compEntry[ i ]->Update( mergeEntry, ( Catalog::DataTypes ) i );
    }

}


/*
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_DEEPRADIOBUTTON
 */

void ComparePanel::OnDeepRadioButton( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_DEEPRADIOBUTTON in ComparePanel2.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_DEEPRADIOBUTTON in ComparePanel2. 
}


/*
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_SELECTEDRADIOBUTTON
 */

void ComparePanel::OnSelectedRadioButton( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_SELECTEDRADIOBUTTON in ComparePanel2.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_SELECTEDRADIOBUTTON in ComparePanel2. 
}


/*
 * wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for ID_CHECKLISTBOX
 */

void ComparePanel::OnChecklistboxDoubleClicked( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for ID_CHECKLISTBOX in ComparePanel2.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for ID_CHECKLISTBOX in ComparePanel2. 
}


/*
 * wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_CHECKLISTBOX
 */

void ComparePanel::OnChecklistboxSelected( wxCommandEvent& event )
{
    ////@begin wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_CHECKLISTBOX in ComparePanel2.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_CHECKLISTBOX in ComparePanel2. 
}


/*
 * wxEVT_COMMAND_CHECKLISTBOX_TOGGLED event handler for ID_CHECKLISTBOX
 */

wxArrayInt ComparePanel::GetCheckedItems( )
{
    wxArrayInt checkedItems;
    m_CompareCheckBox->GetCheckedItems( checkedItems );
    return checkedItems;
}
bool ComparePanel::CompareEnabled( int i )
{
    if ( m_deepCompare->GetValue( ) )
    {
        return true;
    }
    else
    {
        return m_CompareCheckBox->IsChecked( i );
    }
}

void ComparePanel::OnCheckListBoxToggled( wxCommandEvent& event )
{

    unsigned int nbr = m_CompareCheckBox->GetCheckedItems( m_checkedItems );
    SetBackground( );
    ////@begin wxEVT_COMMAND_CHECKLISTBOX_TOGGLED event handler for ID_CHECKLISTBOX in ComparePanel2.
        // Before editing this code, remove the block markers.
    event.Skip( );
    ////@end wxEVT_COMMAND_CHECKLISTBOX_TOGGLED event handler for ID_CHECKLISTBOX in ComparePanel2. 
}
