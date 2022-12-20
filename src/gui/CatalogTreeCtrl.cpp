/**
 * @file CatalogTreeCtrl.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/log.h"
#include "wx/wx.h"
#endif

#include <iostream>

#include "wx/artprov.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/math.h"
#include "wx/menu.h"
#include "wx/renderer.h"
#include "wx/wupdlock.h"
#include <wx/clipbrd.h>

#include "Defs.h"
#include "gui/GuiDefs.h"
#include "utils/StampList.h"

#include "utils/Project.h"

#include "AlbumGenApp.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogCode.h"
#include "catalog/Classification.h"
#include "catalog/Specimen.h"
#include "catalog/Entry.h"
#include "gui/AlbumGenFrame.h"
#include "gui/AlbumGenPanel.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/StampDescriptionPanel.h"
#include "gui/NewStampDialog.h"

wxDECLARE_APP( AlbumGenApp );


wxIMPLEMENT_CLASS( CatalogTreeCtrl, wxTreeCtrl );


wxBEGIN_EVENT_TABLE( CatalogTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemStateClick )
EVT_TREE_ITEM_MENU( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_RIGHT_CLICK( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemRClick )

wxEND_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

// CatalogTreeCtrl implementation

//*****
CatalogTreeCtrl::CatalogTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )
{
    m_reverseSort = false;

    CreateImageList( );
    CreateStateImageList( false );
}

//*****
void CatalogTreeCtrl::CreateImageList( )
{
    AssignImageList( CreateCatalogImageList( ) );
}

//*****
void CatalogTreeCtrl::CreateStateImageList( bool del )
{
    AssignStateImageList( CreateCatalogStateImageList( del ) );
}

ComparisonResultType CatalogTreeCtrl::CompareDates( wxString date1, wxString date2 )
{
    wxDateTime dt1;
    wxDateTime dt2;
    wxString::const_iterator end;
    if ( !dt1.ParseFormat( date1, "%Y-%m-%d", &end ) )
    {
        if ( !dt1.ParseFormat( date1, "%Y", &end ) )
        {
            if ( !dt1.ParseFormat( date1, "%Y-%m", &end ) )
            {
                return CompareInvalid;
            }
        }
    }
    if ( !dt2.ParseFormat( date2, "%Y-%m-%d", &end ) )
    {
        if ( !dt2.ParseFormat( date2, "%Y", &end ) )
        {
            if ( !dt2.ParseFormat( date2, "%Y-%m", &end ) )
            {
                return CompareInvalid;
            }
        }
    }
    if ( !dt1.IsValid( ) || !dt2.IsValid( ) )
    {
        return CompareInvalid;
    }

    if ( dt1.IsSameDate( dt2 ) )
    {
        return CompareEqual;
    }
    else if ( dt1.IsEarlierThan( dt2 ) )
    {
        return CompareLess;
    }
    else
    {
        return CompareGreater;
    }
}

//*****
int CatalogTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    if ( item1.IsOk( ) && item2.IsOk( ) )
    {
        CatalogTreeItemData* itemData1 = ( CatalogTreeItemData* )GetItemData( item1 );
        Catalog::CatalogBaseType type1 = itemData1->GetType( );

        CatalogTreeItemData* itemData2 = ( CatalogTreeItemData* )GetItemData( item2 );
        Catalog::CatalogBaseType type2 = itemData2->GetType( );

        if ( type1 != type2 )
        {
            return ( int )type1 - ( int )type2;
        }
        else
        {
            // they are the same type
            if ( type1 == Catalog::NT_Entry )
            {
                // they are both entries

                wxXmlNode* node1 = itemData1->GetNodeElement( );
                Catalog::Entry entry1( node1 );
                wxString date1 = entry1.GetIssuedDate( );
                wxString id1 = itemData1->GetDesc( );
                wxString series1 = entry1.GetSeries( );
                wxXmlNode* node2 = itemData2->GetNodeElement( );
                Catalog::Entry entry2( node2 );
                wxString date2 = entry2.GetIssuedDate( );
                wxString id2 = itemData2->GetDesc( );
                wxString series2 = entry2.GetSeries( );

               ComparisonResultType result = CompareDates( date1, date2 );
               if ( ( result == CompareInvalid ) || ( result == CompareEqual ) )
               {
                int val = series1.Cmp( series2 );
                    if ( !val )
                    {
                        int val = id1.Cmp( id2 );
                        if ( !val )
                        {
                            std::cout << "(" << id1 << " " << date1 << ") = (" << id2 << " " << date2 << ")\n";
                        }   
                        else if ( val < 0 )
                        {
                            std::cout << "(" << id1 << " " << date1 << ") < (" << id2 << " " << date2 << ")\n";
                        }
                        else 
                        {
                            std::cout << "(" << id1 << " " << date1 << ") > (" << id2 << " " << date2 << ")\n";
                        }
                    }
                    else if ( val < 0 )
                    {
                        std::cout << "(" << id1 << " " << date1 << ") < (" << id2 << " " << date2 << ")\n";
                    }
                    else 
                    {
                        std::cout << "(" << id1 << " " << date1 << ") > (" << id2 << " " << date2 << ")\n";
                    }

                //    if ( m_reverseSort )
                //    {
                        return val;
                //    }
                //    else
                //    {
                //        return val * -1;
                //    }

                }
                else if ( result == CompareLess )
                {
                    std::cout << "(" << id1 << " " << date1 << ") < (" << id2 << " " << date2 << ")\n";
                //    if ( m_reverseSort )
                //    {
                        return -1;
                    // }
                    // else
                    // {
                    //     return 1;
                    // }
                }
                // else if ( result == CompareEqual )
                // {
                //     std::cout << "(" << id1 << " " << date1 << ") = (" << id2 << " " << date2 << ")\n";
                //     return 0;
                // }
                else
                {
                    std::cout << "(" << id1 << " " << date1 << ") > (" << id2 << " " << date2 << ")\n";
                //    if ( m_reverseSort )
                //    {
                //        return -1;
                //    }
                 //   else
                //    {
                        return 1;
                //    }
                }
            }
        }
    }
    return 0;
}


//*****
Utils::StampLink* CatalogTreeCtrl::AppendAlbumStamp( wxTreeItemId itemId )
{
    Utils::StampLink* link = GetDesignTreeCtrl( )->AppendStamp( itemId );
    if ( link )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
        data->SetStampLink( link );
        //        wxXmlNode* catNode = GetEntryNode( itemId );
                // link->SetCatNode( catNode );
        link->SetCatTreeID( itemId );
    }
    return link;
}

//*****
wxXmlNode* CatalogTreeCtrl::GetEntryNode( wxTreeItemId itemId )
{
    wxXmlNode* node = 0;
    if ( itemId.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
        node = data->GetNodeElement( );
    }
    return node;
}

//*****
wxString CatalogTreeCtrl::GetEntryID( wxTreeItemId itemId )
{
    wxXmlNode* element = GetEntryNode( itemId );
    return element->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
}

//*****
Utils::StampLink* CatalogTreeCtrl::FindStampLink( wxTreeItemId itemId )
{
    wxString id = GetEntryID( itemId );
    Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
    Utils::StampLink* stampLink = stampList->FindStampLink( id );
    return stampLink;
}

//*****
void CatalogTreeCtrl::DeleteAlbumStamp( wxTreeItemId itemId )
{
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
    Utils::StampLink* stampLink = data->GetStampLink( );
    if ( stampLink )
    {
        wxTreeItemId itemID = stampLink->GetDesignTreeID( );
        if ( itemID.IsOk( ) ) GetDesignTreeCtrl( )->DeleteItem( itemID );
    }
}

//*****
void CatalogTreeCtrl::RemoveStampLink( wxTreeItemId itemId )
{
    if ( itemId.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
        data->SetStampLink( 0 );
    }
}


//*****
void CatalogTreeCtrl::SetNextState( const wxTreeItemId& itemId )
{
    wxXmlNode* element = GetEntryNode( itemId );
    Catalog::Entry* entry = new Catalog::Entry( element );
    if ( entry->IsOK( ) )
    {
        SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
        int state = GetItemState( itemId );
        entry->SetCheckedStatusType( ( Catalog::CheckedStatusType )state );
        wxGetApp( ).GetFrame( )->UpdateStatus( );
        if ( state )
        {
            Utils::StampLink* link = AppendAlbumStamp( itemId );
            if ( !link )
            {
                SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
            }
        }
        else
        {
            DeleteAlbumStamp( itemId );
        }
    }
}

//*****
Catalog::IconID CatalogTreeCtrl::GetInventoryIconId( Catalog::Entry* entry )
{
    int format = entry->GetFormatType( );
    int type = entry->GetInventoryStatusType( );
    return Catalog::CatalogImageSelection[ format ][ type ];
}

Catalog::Entry* CatalogTreeCtrl::GetNewEntry( wxTreeItemId itemId )
{
    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );
    wxXmlNode* element = item->GetNodeElement( );
    return new Catalog::Entry( element );
}
//*****
void CatalogTreeCtrl::SetInventoryStatusImage( )
{
    wxTreeItemId itemId = GetFocusedItem( );
    Catalog::Entry* entry = GetNewEntry( itemId );
    if ( entry->IsOK( ) )
    {
        int status = entry->GetInventoryStatusType( );
        int format = entry->GetFormatType( );
        Catalog::IconID iconID = Catalog::CatalogImageSelection[ format ][ status ];
        SetItemImage( itemId, GetInventoryIconId( entry ) );
    }
}

//*****
void CatalogTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}

//*****
void CatalogTreeCtrl::OnBeginDrag( wxTreeEvent& event )
{
    // need to explicitly allow drag
    if ( event.GetItem( ) != GetRootItem( ) )
    {
        m_draggedItem = event.GetItem( );

        wxPoint clientpt = event.GetPoint( );
        wxPoint screenpt = ClientToScreen( clientpt );

        event.Allow( );
    }
    else
    {
    }
}

//*****
void CatalogTreeCtrl::OnEndDrag( wxTreeEvent& event )
{
    wxTreeItemId itemSrc = m_draggedItem;
    wxTreeItemId itemDst = event.GetItem( );
    m_draggedItem = ( wxTreeItemId )0l;

    if ( itemSrc == itemDst )
    {
        return;
    }

    if ( !itemDst.IsOk( ) )
    {
        return;
    }
    ShowDropMenu( itemSrc, itemDst );
}

//*****
void CatalogTreeCtrl::ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst )
{
    wxString title;
    if ( !itemSrc.IsOk( ) || !itemDst.IsOk( ) )
    {
        return;
    }

    title << "Drop Item " << GetItemText( itemSrc );

    wxMenu menu( title );
    wxString label = "Insert Before " + GetItemText( itemDst );
    menu.Append( CatalogDataTree_Before, label );
    label = "Insert After " + GetItemText( itemDst );
    menu.Append( CatalogDataTree_After, label );
    label = "Insert as Child of " + GetItemText( itemDst );
    menu.Append( CatalogDataTree_AsChild, label );
    menu.Append( CatalogDataTree_Cancel, "Cancel Drag" );

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
    case CatalogDataTree_Before:
    {

        wxXmlNode* srcElement = GetEntryNode( itemSrc );
        wxXmlNode* dstElement = GetEntryNode( itemDst );

        // move the element
        // this means making a copy and deleting the old one so old pointers are
        // trash
        wxXmlNode* newElement = Catalog::InsertEntry( dstElement, srcElement, false );

        // now update the tree with the new one
        wxTreeItemId id = InsertChild( itemDst, newElement, false );
        //wxTreeItemId id = AddChild( itemDst, newElement );
        SelectItem( itemDst );
        Delete( itemSrc );

        break;
    }
    case CatalogDataTree_After:
    {

        wxXmlNode* srcElement = GetEntryNode( itemSrc );
        wxXmlNode* dstElement = GetEntryNode( itemDst );

        // move the element
        // this means making a copy and deleting the old one so old pointers are
        // trash
        wxXmlNode* newElement = Catalog::InsertEntry( dstElement, srcElement, true );

        // now update the tree with the new one
        wxTreeItemId id = InsertChild( itemDst, newElement, true );
        //wxTreeItemId id = AddChild( itemDst, newElement );
        SelectItem( itemDst );
        Delete( itemSrc );

        break;
    }
    case CatalogDataTree_AsChild:
    {

        wxXmlNode* srcElement = GetEntryNode( itemSrc );
        wxXmlNode* dstElement = GetEntryNode( itemDst );

        // move the element
        // this means making a copy and deleting the old one so old pointers are
        // trash
        wxXmlNode* newElement = Catalog::MoveEntry( dstElement, srcElement );

        // now update the tree with the new one
        wxTreeItemId id = AddChild( itemDst, newElement );
        SelectItem( itemDst );
        Delete( itemSrc );
        break;
    }
    case CatalogDataTree_Cancel:
    {

        break;
    }
    }
}

//*****
void CatalogTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );
    SetNextState( itemId );
}

//*****
void CatalogTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxXmlNode* entry = GetEntryNode( itemId );
    //    wxGetApp( ).GetFrame( )->SetEntry( entry );
    GetGeneratorData( )->GetDescriptionPanel( )->SetStamp( entry );
    event.Skip( );
}

//*****
void CatalogTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );
    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

//*****
void CatalogTreeCtrl::DoTreeContextSelection( )
{
}

//*****
void CatalogTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
{
    wxString title;
    if ( id.IsOk( ) )
    {
        title << "Menu for " << GetItemText( id );
    }
    else
    {
        title = "Menu for no particular item";
    }

    wxMenu menu( title );
    menu.Append( CatalogDataTree_About, "&About" );
    menu.AppendSeparator( );
    menu.Append( CatalogDataTree_Colnect, "GoTo Colnect" );
    menu.AppendSeparator( );
    //   menu.Append( CatalogDataTree_Move, "Move" );
    menu.Append( CatalogDataTree_Delete, "Delete Entry" );
    menu.Append( CatalogDataTree_Add, "Add New Entry" );


    menu.Append( CatalogDataTree_StructureStamps, "Re-Group Multiples" );
    menu.Append( CatalogDataTree_ResortTree, "Re-Sort Tree" );
    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
    case CatalogDataTree_StructureStamps:
    {
        wxXmlNode* entry = GetEntryNode( id );

        Utils::XMLDumpNode( entry,"3" );

        StructureEntry( entry );
 //       Utils::XMLDumpNode( entry,"4" );
        ReSortTree( );

        wxTreeItemId newID = FindTreeItemID( entry );
        if ( newID )
        {
            Expand( newID );
            SelectItem( newID );
        }
        break;
    }
    case CatalogDataTree_ResortTree:
    {
        ReSortTree( );
        break;
    }
    case CatalogDataTree_Colnect:
    {
        GoToColnect( id );
        break;
    }
    case CatalogDataTree_Delete:
    {
        DeleteEntry( id );
        break;
    }
    case CatalogDataTree_Add:
    {
        AddEntry( id );
        break;
    }
    default:
        // Fall through.
        break;
    }
}

//*****
void CatalogTreeCtrl::AddEntry( wxTreeItemId id )
{
    NewStampDialog newEntryDialog( this, 12345, _( "Add New Entry" ) );
    if ( newEntryDialog.ShowModal( ) == wxID_CANCEL ) return; // the user changed idea..
}
//*****
void CatalogTreeCtrl::DeleteEntry( wxTreeItemId id )
{
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
    wxXmlNode* node = data->GetNodeElement( );
    if ( data && data->GetType( ) == Catalog::NT_Entry )
    {
        wxString txt = wxString::Format( "Delete Entry %s?\n\n", GetItemText( id ) );
        wxMessageDialog* dlg = new wxMessageDialog(
            wxGetApp( ).GetFrame( ), txt,
            wxT( "Warning! Entry will be deleted.\ No undo available.n" ),
            wxOK | wxCANCEL | wxCENTER );
        int rsp = dlg->ShowModal( );
        if ( rsp == wxOK )
        {
            wxXmlNode* parent = node->GetParent( );
            parent->RemoveChild( node );
            Utils::StampLink* stampLink = FindStampLink( id );
            if ( stampLink )
            {
                stampLink->SetCatTreeID( 0 );
            }
            Delete( id );
        }
    }
}

//*****
void CatalogTreeCtrl::GoToColnect( wxTreeItemId id )
{
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
    wxXmlNode* node = data->GetNodeElement( );
    if ( node )
    {
        wxString nodeName = node->GetName( );
        if ( !nodeName.Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Entry ] ) )
        {
            Catalog::Entry entry( node );
            wxString entryID = entry.GetID( );
            entryID = entryID.Trim( true );
            entryID = entryID.Trim( false );
            entryID.Replace( ":", "_" );
            entryID.Replace( " ", "_" );
            if ( wxTheClipboard->Open( ) )
            {
                // This data objects are held by the clipboard,
                // so do not delete them in the app.
                wxTheClipboard->SetData( new wxTextDataObject( entryID ) );
                wxTheClipboard->Close( );
            }

            wxString link = entry.GetLink( );
            wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s", link );
            system( cmd.fn_str( ) );
        }

    }
}

//*****
void CatalogTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );

    event.Skip( );
}

CatalogTreeItemData* CatalogTreeCtrl::CreateChildData( wxXmlNode* child,
    wxString& label,
    Catalog::IconID& icon,
    Catalog::CatalogBaseType& nodeType )
{
    wxString name = child->GetName( );
    nodeType = Catalog::FindCatalogBaseType( name );
    //wxString label;
    //Catalog::IconID icon;

    //if the child element is not a entry
    if ( !name.Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Entry ] ) )
    {
        // then we add the appropriate icon and label
        Catalog::Entry entry( child );

        // entry combines the entryID and its name to form a label
        label = entry.GetLabel( );

        icon = GetInventoryIconId( &entry );
    }
    else
    {
        // if it is a specimen or catalog code return because 
        // they don't go in the tree.
        if ( ( nodeType == Catalog::NT_Specimen )
            || ( nodeType == Catalog::NT_CatalogCode ) )
        {
            return 0;
        }
        else
        {
            //otherwise get the label
            const wxXmlAttribute* attr = Utils::GetAttribute( child, "Name" );
            label = attr->GetValue( );
            icon = Catalog::Icon_Folder;
        }
    }

    // create the item data 
    return new CatalogTreeItemData( nodeType, label, child );

}
//*****
// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId CatalogTreeCtrl::InsertChild( wxTreeItemId sibling, wxXmlNode* child, bool after )
{
    Catalog::IconID icon;
    wxString label;
    Catalog::CatalogBaseType nodeType;
    CatalogTreeItemData* itemData = CreateChildData( child, label, icon, nodeType );

    if ( !itemData )
    {
        return 0;
    }

    wxTreeItemIdValue cookie;
    wxTreeItemId parent = GetItemParent( sibling );
    wxTreeItemId  childID;
    if ( after )
    {
        // insert after sibling
        childID = InsertItem( parent, sibling, label, icon, -1, itemData );
    }
    else
    {
        wxTreeItemId prevSibling = GetPrevSibling( sibling );
        if ( prevSibling.IsOk( ) )
        {
            childID = InsertItem( parent, prevSibling, label, icon, -1, itemData );
        }
        else
        {
            childID = InsertItem( parent, 0, label, icon, -1, itemData );
        }
    }


    if ( nodeType == Catalog::NT_Entry )
    {
        //set the icon for the appropriate state

        // if there is a stamplink then set the stamplink data and the item state as checked

        Utils::StampLink* stampLink = FindStampLink( childID );
        if ( stampLink )
        {
            itemData->SetStampLink( stampLink );
            stampLink->SetCatTreeID( childID );
            SetItemState( childID, Catalog::ST_Checked );
            // and the entry as checked
            Catalog::Entry entry( child );
            entry.SetCheckedStatus( Catalog::ST_CheckedStatusStrings[ Catalog::ST_Checked ] );
        }
        else
        {
            itemData->SetStampLink( 0 );
            SetItemState( childID, Catalog::ST_Unchecked );
        }
    }
    else
    {
        // not a entry just add the appropriate image
        SetItemImage( childID, Catalog::Icon_Folder );
        SetItemState( childID, wxTREE_ITEMSTATE_NEXT );
    }
    if ( wxGetApp( ).GetFrame( )->GetAlbumGenPanel( )->ShouldShowStates( ) )
    {
        EnableState( childID );
    }
    else
    {
        DisableState( childID );
    }
    // now do it all again for this entrys children
    wxXmlNode* grandChild = child->GetChildren( );
    while ( grandChild )
    {

        // start adding child elements to it.
        AddChild( childID, grandChild );
        grandChild = grandChild->GetNext( );
    }

    return childID;
}

//*****
// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId CatalogTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child )
{
    Catalog::IconID icon;
    wxString label;
    Catalog::CatalogBaseType nodeType;
    CatalogTreeItemData* itemData = CreateChildData( child, label, icon, nodeType );

    if ( !itemData )
    {
        return 0;
    }

    wxTreeItemId childID = AppendItem( parent, label, icon, -1, itemData );


    if ( nodeType == Catalog::NT_Entry )
    {
        //set the icon for the appropriate state

        // if there is a stamplink then set the stamplink data and the item state as checked
        Utils::StampLink* stampLink = FindStampLink( childID );
        if ( stampLink )
        {
            itemData->SetStampLink( stampLink );
            stampLink->SetCatTreeID( childID );
            SetItemState( childID, Catalog::ST_Checked );

            // and the entry as checked
            Catalog::Entry entry( child );
            entry.SetCheckedStatus( Catalog::ST_CheckedStatusStrings[ Catalog::ST_Checked ] );
        }
        else
        {
            itemData->SetStampLink( 0 );
            SetItemState( childID, Catalog::ST_Unchecked );
        }
    }
    else
    {
        // not a entry just add the appropriate image
        SetItemImage( childID, Catalog::Icon_Folder );
        SetItemState( childID, wxTREE_ITEMSTATE_NEXT );
    }

    if ( wxGetApp( ).GetFrame( )->GetAlbumGenPanel( )->ShouldShowStates( ) )
    {
        EnableState( childID );
    }
    else
    {
        DisableState( childID );
    }

    // now do it all again for this entrys children
    wxXmlNode* grandChild = child->GetChildren( );
    while ( grandChild )
    {

        // start adding child elements to it.
        AddChild( childID, grandChild );
        grandChild = grandChild->GetNext( );
    }

    return childID;
}

//*****
// SortTree decends through the tree and sorts the children
// of each item.
void CatalogTreeCtrl::SortTree( wxTreeItemId parent )
{
    // decend into the tree and sort its children
    wxTreeItemIdValue cookie;
    wxTreeItemId childItem = GetFirstChild( parent, cookie );
    while ( childItem.IsOk( ) )
    {
        //        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( childItem );
        //        wxString str = data->GetDesc();
        //        std::cout << str << "\n";

        if ( GetChildrenCount( childItem, false ) >= 1 )
        {
            // descend and do it again
            SortTree( childItem );
        }
        childItem = GetNextChild( parent, cookie );
    }
    if ( this->HasChildren( parent ) )
    {
              CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( parent );
               wxString str = data->GetDesc();
               std::cout << " SortChildren for "<<str << "\n";
        SortChildren( parent );
    }
}

//*****
//Delete the tree and resort it with the new sort order data.
// Probably doint this because the sort order was changed.
void CatalogTreeCtrl::ReSortTree( )
{
    // if (m_reverseSort)
    // {
    //     std::cout << "m_reverseSort = true;\n";
    // }
    // else        
    // {
    //     std::cout << "m_reverseSort = false;\n";
    // }
    ClearCatalogTree( );

    wxXmlDocument* newDoc = new wxXmlDocument( );
    wxXmlNode* newRoot = newDoc->GetRoot( );
    if ( !newRoot )
    {
        newRoot = Utils::NewNode( newDoc, Catalog::CatalogBaseNames[ Catalog::NT_Catalog ] );
    }
    //newDoc->SetRoot( newRoot );

    Catalog::CatalogData* catalogData = GetCatalogData( );
    wxXmlDocument* doc = catalogData->GetDoc( );
    wxXmlNode* root = doc->GetRoot( );

    wxXmlAttribute* attr = Utils::GetAttribute( root, Catalog::DT_DataNames[ Catalog::DT_Name ] );
    if ( attr ) {
        wxString name = attr->GetName( );
        wxString value = attr->GetValue( );
        Utils::SetAttrStr( newRoot, name, value );
    }
    else
    {
        Utils::SetAttrStr( newRoot, Catalog::DT_DataNames[ Catalog::DT_Name ], "" );
    }
 //   Utils::XMLDumpNode( root,"0" );

    Catalog::SortData( newRoot, root );
    // std::cout << "*******************************************\n";
  //  Utils::XMLDumpNode( newRoot,"1" );
    GetCatalogData( )->ReplaceDocument( newDoc );
    LoadTree( );
}


//*****
void CatalogTreeCtrl::ClearCatalogTree( )
{
    Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
    stampList->ClearCatalogLinks( );
    DeleteAllItems( );
}

//*****
// basic load of the tree
void CatalogTreeCtrl::LoadTree( )
{
    ClearCatalogTree( );
    Catalog::CatalogData* catalogData = GetCatalogData( );
    if ( catalogData )
    {
        wxXmlDocument* entryDoc = catalogData->GetDoc( );
        //   XMLDump( entryDoc );
        wxXmlNode* root = entryDoc->GetRoot( );
        wxString name = root->GetName( );
        // Create the root item
        CatalogTreeItemData* itemData
            = new CatalogTreeItemData( Catalog::NT_Catalog, name, root );
        wxTreeItemId rootID = AddRoot( name, Catalog::Icon_Folder, 1, itemData );

        wxXmlNode* child = root->GetChildren( );
        while ( child )
        {
            // start adding child elements to it.
            AddChild( rootID, child );
            child = child->GetNext( );
        }
        SortTree( rootID );
        SetStates( wxGetApp( ).GetFrame( )->GetAlbumGenPanel( )->ShouldShowStates( ) );
        ExpandAll( );
    }
}

//*****
// this makes a list of the children entry elements that can have childrem
wxXmlNodeArray* CatalogTreeCtrl::MakeParentList( wxXmlNode* catalogData,
    Catalog::FormatType parentType )
{
    //Catalog::Entry parentEntry;
    wxXmlNodeArray* parentList = new wxXmlNodeArray( );
    wxXmlNode* child = catalogData->GetChildren( );
    while ( child )
    {
        Catalog::Entry parentEntry( child );
        if ( parentEntry.GetFormat( ) == Catalog::FT_FormatStrings[ parentType ] )
        {
//            std::cout << parentEntry.GetFormat( ) << " " << parentEntry.GetID() << "\n";
            parentList->push_back( child );
        }
        child = child->GetNext( );
    }
    return parentList;
}


//*****
// this is an attempt to group the entrys;
// i.e., an item of type entry can be a child of an item SeTenent type.
void CatalogTreeCtrl::StructureEntry( wxXmlNode* catalogData )
{
    StructureCatalogData( catalogData, Catalog::FT_Se_tenant, Catalog::FT_Stamp );
    StructureCatalogData( catalogData, Catalog::FT_Gutter_Pair, Catalog::FT_Stamp );
    StructureCatalogData( catalogData, Catalog::FT_Booklet_Pane, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Souvenir_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Booklet, Catalog::FT_Stamp, Catalog::FT_Booklet_Pane );
    SortTree( GetRootItem( ) );
}

//*****
// this looks through the xml tree and makes related entries of childType a child of the parent type
void CatalogTreeCtrl::StructureCatalogData( wxXmlNode* catalogData,
    Catalog::FormatType parentType,
    Catalog::FormatType childType,
    Catalog::FormatType secondChildType )
{
    // Make a list of all nodes that are of parentType
    wxXmlNodeArray* parentList = MakeParentList( catalogData, parentType );
    // now find all the entrys that go into each parent by comparing the issue date, series and face value
    for ( int i = 0; i < parentList->size( ); i++ )
    {
        wxXmlNode* parentNode = ( wxXmlNode* )parentList->at( i );
        Catalog::Entry* parentEntry = new Catalog::Entry( parentNode );
        wxString parentIssue = parentEntry->GetIssuedDate( );
        wxString parentSeries = parentEntry->GetSeries( );
        wxString parentFace = parentEntry->GetFaceValue( );
        wxString id = parentEntry->GetID();
 //       std::cout << "Looking for children of " << id << " "<< parentIssue << "  series:"<<parentSeries<<"  face:" <<parentFace <<"\n";
        long nbrEntrys;
        parentFace.ToLong( &nbrEntrys );
        if ( nbrEntrys <= 0 )
        {
            // if we can't figure out the face then assume a setenant is no bigger than 50 entrys
            nbrEntrys = 50;
        }
        long count = 0;
        long searchRange = 0;

        wxXmlNode* childNode = catalogData->GetChildren( );

        while ( childNode && ( searchRange < 1005 ) && ( count < nbrEntrys ) )
        {
            Catalog::Entry* childEntry = new Catalog::Entry( childNode );

            // figure out what the next sibling is because we may move childNode
            wxXmlNode* nextSibling = childNode->GetNext( );

            if ( parentNode != childNode )
            {
                // only search a reasonable distance after the first one is found
                if ( count > 1 )
                {
                    searchRange++;
                }
                // only look at children of childType
                wxString format = childEntry->GetFormat( );
                if ( ( format == Catalog::FT_FormatStrings[ childType ] )
                    || ( secondChildType
                        && ( format == Catalog::FT_FormatStrings[ secondChildType ] ) ) )
                {
                    wxString issue = childEntry->GetIssuedDate( );
                    wxString series = childEntry->GetSeries( );
                    // if the issue date and the series match the parent assume
                    // that the childNode goes in the parent
                    if ( !issue.Cmp( parentIssue )
                        && !series.Cmp( parentSeries ) )
                    {
//                        std::cout << childEntry->GetID() << " should be a child of "<<parentEntry->GetID() <<"\n";
                        //remove it from the old place
                        count++;
                        wxXmlNode* currParent = childNode->GetParent( );
                        if ( currParent )
                        {
 //                           Catalog::Entry currParentEntry( currParent );
//                            std::cout << "Removing "<< childEntry->GetID() << " from" << currParentEntry.GetID() <<"\n";
                            currParent->RemoveChild( childNode );
                        }
                        //and add it to new place
                        parentNode->AddChild( childNode );
//                        std::cout << "Adding "<< childEntry->GetID() << " to" << parentEntry->GetID() <<"\n";                       
                    }
                }
            }
            childNode = nextSibling;
        }
    }
}
void CatalogTreeCtrl::XMLDumpNode(  wxTreeItemId item, wxString str  )
{

    if ( !item.IsOk( ) )
    {
        return ;
    }
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( item );
    wxXmlNode* ele = data->GetNodeElement( );
    Utils::XMLDumpNode( ele,str );
}
//*****
bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
{
    if ( !item.IsOk( ) )
    {
        return false;
    }

    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( item );
    wxXmlNode* dataEle = data->GetNodeElement( );
    if ( dataEle != ele )
    {
        return false;
    }
    return true;
}

//*****
bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxString entryID )
{
    if ( item.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( item );
        wxXmlNode* dataEle = data->GetNodeElement( );
        wxString id = dataEle->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
        if ( entryID.Cmp( id ) )
        {
            return false;
        }
    }
    return true;
}

//*****
wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxXmlNode* ele, wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child )
        {
            if ( IsElement( child, ele ) )
            {
                return child;
            }
            if ( this->HasChildren( child ) )
            {
                wxTreeItemId idFound = FindTreeItemID( ele, child );
                if ( idFound )
                {
                    return idFound;
                }
            }
            child = this->GetNextChild( id, cookie );
        }
    }
    return 0;
}


//*****
wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxString entryID, wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child )
        {
            if ( IsElement( child, entryID ) )
            {
                return child;
            }
            if ( this->HasChildren( child ) )
            {
                wxTreeItemId idFound = FindTreeItemID( entryID, child );
                if ( idFound )
                {
                    return idFound;
                }
            }
            child = this->GetNextChild( id, cookie );
        }
    }
    return 0;
}

//*****
wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxXmlNode* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//*****
wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxString entryID )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( entryID, root );
}

//*****
wxTreeItemId CatalogTreeCtrl::FindFirstEntryChild( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child )
        {
            CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( child );
            if ( data->GetType( ) == Catalog::NT_Entry )
            {
                return child;
            }
            if ( HasChildren( child ) )
            {
                wxTreeItemId id = FindFirstEntryChild( child );
                if ( id )
                {
                    return id;
                }
            }
            child = GetNextChild( id, cookie );
        }
    }
    return 0;
}

//*****
void CatalogTreeCtrl::SetStates( bool enable )
{
    wxTreeItemId id = GetRootItem( );
    if ( id.IsOk( ) && enable )
    {
        EnableState( id );
    }
    else
    {
        DisableState( id );
    }
}

//*****
void CatalogTreeCtrl::EnableState( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
        if ( data->GetType( ) == Catalog::NT_Entry )
        {
            wxXmlNode* node = data->GetNodeElement( );
            wxString status = node->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_CheckedStatus ] );
            if ( status.Cmp( Catalog::ST_CheckedStatusStrings[ Catalog::ST_Checked ] ) )
            {
                SetItemState( id, Catalog::ST_Unchecked );
            }
            else
            {
                SetItemState( id, Catalog::ST_Checked );
            }
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child.IsOk( ) )
        {
            EnableState( child );
            child = GetNextChild( id, cookie );
        }
    }
}

//*****
void CatalogTreeCtrl::DisableState( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        SetItemState( id, wxTREE_ITEMSTATE_NONE );
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child.IsOk( ) )
        {
            DisableState( child );
            child = GetNextChild( id, cookie );
        }
    }
}