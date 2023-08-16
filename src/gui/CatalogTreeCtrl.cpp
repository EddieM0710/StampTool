/**
 * @file CatalogTreeCtrl.cpp
 * @author Eddie Monroe ( )
 * @brief
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
 */

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
#include <wx/filename.h>

#include "Defs.h"

#include "utils/StampList.h"
#include "utils/Project.h"
#include "utils/XMLUtilities.h"

 //#include "StampToolApp.h"
#include "catalog/CatalogVolume.h"
//#include "catalog/CatalogCode.h"
#include "catalog/CatalogData.h"
#include "catalog/Entry.h"
#include "collection/CollectionList.h"
#include "gui/GuiDefs.h"
#include "gui/StampToolFrame.h"
#include "gui/StampToolPanel.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/NewStampDialog.h"

//wxDECLARE_APP( StampToolApp );

wxIMPLEMENT_CLASS( CatalogTreeCtrl, wxTreeCtrl );

wxBEGIN_EVENT_TABLE( CatalogTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemStateClick )
EVT_TREE_ITEM_MENU( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_COLLAPSED( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnTreectrlItemCollapsed )
EVT_TREE_ITEM_EXPANDED( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnTreectrlItemExpanded )
wxEND_EVENT_TABLE( )

//--------------

CatalogTreeCtrl::CatalogTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )
{
    m_reverseSort = false;

    CreateImageList( );
    CreateStateImageList( );
}

void CatalogTreeCtrl::SetTreeItemCollapseState( wxTreeItemId childID )
{

    wxString state = GetAttribute( childID, Catalog::XMLDataNames[ Catalog::DT_CollapseState ] );
    if ( String2Bool( state ) )
    {
        Collapse( childID );
    }
    else
    {
        Expand( childID );
    }

}

//---------wxTreeItemId childID-----

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

            itemData->SetChecked( true );
        }
        else
        {
            //            SetItemState( childID, Catalog::ST_Checked );
            //            itemData->SetChecked( true );
            itemData->SetChecked( false );
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

    if ( GetFrame( )->GetStampToolPanel( )->ShouldShowStates( ) )
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
    SetTreeItemCollapseState( childID );
    return childID;
}

//--------------

void CatalogTreeCtrl::AddEntry( wxTreeItemId id )
{
    NewStampDialog newEntryDialog( this, 12345, _( "Add New Entry" ) );
    if ( newEntryDialog.ShowModal( ) == wxID_CANCEL ) return; // the user changed idea..
}

//--------------

Utils::StampLink* CatalogTreeCtrl::AppendAlbumStamp( wxTreeItemId itemId )
{
    Utils::StampLink* link = GetAlbumTreeCtrl( )->AppendStamp( itemId );
    if ( link )
    {
        SetItemStampLink( itemId, link );
        link->SetCatTreeID( itemId );
    }
    return link;
}

//--------------

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

//--------------

void CatalogTreeCtrl::ClearCatalogTree( )
{
    // first make sure all the links to the items are gone
    Utils::StampList* stampList = GetStampAlbumCatalogLink( );
    stampList->ClearCatalogLinks( );

    // then clobber all the tree items
    DeleteAllItems( );
}

//--------------

void CatalogTreeCtrl::CreateImageList( )
{
    AssignImageList( CreateCatalogImageList( ) );
}

//--------------

void CatalogTreeCtrl::CreateStateImageList( )
{
    AssignStateImageList( CreateCatalogStateImageList( ) );
}

//--------------

void CatalogTreeCtrl::DeleteAlbumStamp( wxTreeItemId itemId )
{
    Utils::StampLink* stampLink = GetItemStampLink( itemId );
    if ( stampLink )
    {
        wxTreeItemId itemID = stampLink->GetDesignTreeID( );
        if ( itemID.IsOk( ) ) GetAlbumTreeCtrl( )->DeleteItem( itemID );
    }
}

//--------------

void CatalogTreeCtrl::DeleteEntry( wxTreeItemId id )
{
    wxXmlNode* node = GetItemNode( id );
    if ( GetItemType( id ) == Catalog::NT_Entry )
    {
        wxString txt = wxString::Format( "Delete Entry %s?\n\n", GetItemText( id ) );
        wxMessageDialog* dlg = new wxMessageDialog(
            GetFrame( ), txt,
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

//--------------

void CatalogTreeCtrl::DumpTree( )
{
    wxTreeItemId id = this->GetRootItem( );
    DumpTree( id );
}

//--------------

void CatalogTreeCtrl::DumpTree( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        PrintTreeNodeData( id );
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child.IsOk( ) )
        {
            DumpTree( child );
            child = GetNextChild( id, cookie );
        }
    }
}

//--------------

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

//--------------

void CatalogTreeCtrl::EnableState( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        if ( GetItemType( id ) == Catalog::NT_Entry )
        {
            if ( IsItemChecked( id ) )
            {
                SetItemState( id, Catalog::ST_Checked );
            }
            else
            {
                SetItemState( id, Catalog::ST_Unchecked );
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

//--------------

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

//--------------

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
            if ( HasChildren( child ) )
            {
                wxTreeItemId idFound = FindTreeItemID( entryID, child );
                if ( idFound )
                {
                    return idFound;
                }
            }
            child = GetNextChild( id, cookie );
        }
    }
    return 0;
}

//--------------

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxXmlNode* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//--------------

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxString entryID )
{
    wxTreeItemId root = GetRootItem( );
    if ( root.IsOk( ) )
    {

        return FindTreeItemID( entryID, root );
    }
    return ( wxTreeItemId ) 0;
}

//--------------

wxTreeItemId CatalogTreeCtrl::FindFirstEntryChild( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child )
        {
            if ( GetItemType( child ) == Catalog::NT_Entry )
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

//--------------

Utils::StampLink* CatalogTreeCtrl::FindStampLink( wxTreeItemId itemId )
{
    wxString id = GetIdText( itemId );
    Utils::StampList* stampList = GetStampAlbumCatalogLink( );
    Utils::StampLink* stampLink = stampList->FindStampLink( id );
    return stampLink;
}

//--------------

Catalog::IconID CatalogTreeCtrl::GetInventoryIconId( Catalog::Entry* entry )
{
    int format = entry->GetFormatType( );
    int type = entry->GetInventoryStatusType( );
    return Catalog::CatalogImageSelection[ format ][ type ];
}

//--------------

wxString CatalogTreeCtrl::GetItemDesc( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetDesc( );
        }
    }
    return "";
};

//--------------

wxString CatalogTreeCtrl::GetItemImageFullName( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetImageFullName( );
        }
    }
    return "";
};

//--------------

wxXmlNode* CatalogTreeCtrl::GetItemNode( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetNodeElement( );
        }
    }
    return ( wxXmlNode* ) 0;
};

//--------------

Utils::StampLink* CatalogTreeCtrl::GetItemStampLink( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetStampLink( );
        }
    }
    return ( Utils::StampLink* ) 0;
};

//--------------

Catalog::CatalogBaseType  CatalogTreeCtrl::GetItemType( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetType( );
        }
    }
    return Catalog::CatalogBaseType::NT_None;;
};
//--------------

wxXmlNode* CatalogTreeCtrl::GetNewEntry( wxTreeItemId itemId )
{
    return GetItemNode( itemId );
}

//--------------

wxString CatalogTreeCtrl::GetIdText( wxTreeItemId catTreeID )
{
    wxXmlNode* catNode = GetItemNode( catTreeID );
    wxString idText = "";
    if ( catNode )
    {
        idText = catNode->GetAttribute( Catalog::XMLDataNames[ Catalog::DT_ID_Nbr ] );
    }
    return idText;
}

//--------------

wxString CatalogTreeCtrl::GetAttribute( wxTreeItemId catTreeID, wxString name )
{
    if ( !catTreeID.IsOk( ) ) return "";
    wxXmlNode* node = GetItemNode( catTreeID );
    if ( node )
    {
        wxString val = Utils::GetAttrStr( node, name );
        return val;
    }
    return "";
}

void  CatalogTreeCtrl::SetAttribute( wxTreeItemId catTreeID, wxString name, wxString val )
{
    if ( catTreeID.IsOk( ) )
    {
        wxXmlNode* node = GetItemNode( catTreeID );
        if ( node )
        {
            Utils::SetAttrStr( node, name, val );

        }
    }
}
//--------------

wxString CatalogTreeCtrl::GetImageFullName( wxTreeItemId catTreeID )
{

    if ( catTreeID.IsOk( ) )
    {
        wxString imageName = GetItemImageFullName( catTreeID );
        if ( !imageName )
        {
            Catalog::CatalogVolume* sectData = GetCatalogData( )->GetCatalogVolume( );
            wxString catFilename = sectData->GetVolumeFilename( );
            wxString imageFile = sectData->GetCatalogVolumeImagePath( );;

            wxString id = GetAttribute( catTreeID, Catalog::XMLDataNames[ Catalog::DT_ID_Nbr ] );

            id = id.Trim( true );
            id = id.Trim( false );
            id.Replace( ":", "_" );
            id.Replace( " ", "_" );
            id.Append( ".jpg" );
            imageName = id;// GetProject( )->GetImageFullPath( id );

            SetItemImageFullName( catTreeID, imageName );
        }
        return imageName;
    }
    return "";
}

//--------------

void CatalogTreeCtrl::GoToColnect( wxTreeItemId id )
{
    wxXmlNode* node = GetItemNode( id );
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

//--------------

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
            itemData->SetChecked( true );
        }
        else
        {
            //            SetItemState( childID, Catalog::ST_Checked );
            //            itemData->SetChecked( true );
            itemData->SetChecked( false );
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
    if ( GetFrame( )->GetStampToolPanel( )->ShouldShowStates( ) )
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

//--------------

bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
{
    if ( item.IsOk( ) )
    {
        wxXmlNode* dataEle = GetItemNode( item );
        if ( dataEle == ele )
        {
            return true;
        }
    }
    return false;
}

//--------------

bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxString entryID )
{
    if ( item.IsOk( ) )
    {
        wxString id = GetAttribute( item, Catalog::XMLDataNames[ Catalog::DT_ID_Nbr ] );
        if ( !entryID.Cmp( id ) )
        {
            return true;
        }
    }
    return false;
}

//--------------


bool CatalogTreeCtrl::IsItemChecked( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->IsChecked( );
        }
    }
    return false;
};
//--------------


void CatalogTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}

//--------------

void CatalogTreeCtrl::LoadTree( )
{
    ClearCatalogTree( );
    Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
    if ( catalogVolume )
    {
        wxXmlDocument* entryDoc = catalogVolume->GetDoc( );
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
        //        SortTree( rootID );
        GetAlbumTreeCtrl( )->UpdateStampList( );
        SetStates( GetFrame( )->GetStampToolPanel( )->ShouldShowStates( ) );
        Expand( rootID );
    }
}

//--------------

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

//--------------

void CatalogTreeCtrl::OnEndDrag( wxTreeEvent& event )
{
    wxTreeItemId itemSrc = m_draggedItem;
    wxTreeItemId itemDst = event.GetItem( );
    m_draggedItem = ( wxTreeItemId ) 0l;

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

//--------------

int CatalogTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    CatalogTreeItemData* itemData1 = ( CatalogTreeItemData* ) 0;
    CatalogTreeItemData* itemData2 = ( CatalogTreeItemData* ) 0;
    if ( item1.IsOk( ) && item2.IsOk( ) )
    {
        void* ptr2 = item2.GetID( );
        void* ptr1 = item1.GetID( );
        if ( ( ptr1 < ( void* ) 0xFFFF ) || ( ptr2 < ( void* ) 0xFFFF ) )return 0;
        bool b1 = item1.IsOk( );
        bool b2 = item2.IsOk( );

        itemData1 = ( CatalogTreeItemData* ) GetItemData( item1 );

        itemData2 = ( CatalogTreeItemData* ) GetItemData( item2 );

        return itemData1->Cmp( itemData2 );
    }
    return 0;
}

//--------------

void CatalogTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

//--------------

void CatalogTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );
    SetNextState( itemId );
}

//--------------

void CatalogTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxXmlNode* xmlNode = GetItemNode( itemId );
    GetCatalogData( )->SetCurrentStamp( xmlNode );

    event.Skip( );
}

//--------------

void CatalogTreeCtrl::RemoveStampLink( wxTreeItemId itemId )
{
    SetItemStampLink( itemId, 0 );
}

//--------------

void CatalogTreeCtrl::PrintTreeNodeData( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        wxString title = GetItemText( id );

        wxXmlNode* node = GetItemNode( id );
        if ( node )
        {
            wxString nodeName = node->GetName( );
        }
        else
        {

        }
    }
}

//--------------

void CatalogTreeCtrl::ReSortTree( )
{

    ClearCatalogTree( );

    Catalog::CatalogVolume* catalogVolume = GetCatalogVolume( );
    catalogVolume->ReSortTree( );

    LoadTree( );
}

//--------------

void CatalogTreeCtrl::SetCatalogLink( wxTreeItemId catTreeID, Utils::StampLink* link, wxString IDNbr )
{
    //Get the catalog stamp id
    wxXmlNode* ele = GetItemNode( catTreeID );
    if ( ele )
    {
        wxString catIDNbr = ele->GetAttribute( Catalog::XMLDataNames[ Catalog::DT_ID_Nbr ] );

        if ( !catIDNbr.Cmp( IDNbr ) )
        {
            link->SetCatTreeID( catTreeID );
            SetItemStampLink( catTreeID, link );
            SetItemChecked( catTreeID );
            SetItemState( catTreeID, 1 );
        }
        else
        {
            link->SetCatTreeID( 0 );
            SetItemStampLink( catTreeID, 0 );
        }
    }
    else
    {
        link->SetCatTreeID( 0 );
        SetItemStampLink( catTreeID, 0 );
    }
}

//--------------

void CatalogTreeCtrl::SetInventoryStatus( wxXmlNode* node, Catalog::InventoryStatusType newType )
{
    Catalog::Entry entry( node );
    wxString currCollection = GetCollectionList( )->GetCurrentName( );
    wxXmlNode* specimen = entry.GetSpecimen( currCollection );
    if ( specimen )
    {
        if ( newType == Catalog::ST_Exclude )
        {
            node->RemoveChild( specimen );
        }
        else
        {
            Utils::SetAttrStr( specimen,
                Catalog::ItemDataNames[ Catalog::IDT_InventoryStatus ],
                Catalog::InventoryStatusStrings[ newType ] );
        }
    }
    else
    {
        if ( newType != Catalog::ST_Exclude )
        {
            specimen = Utils::NewNode( node, Catalog::CatalogBaseNames[ Catalog::NT_Specimen ] );
            Utils::SetAttrStr( specimen,
                Catalog::ItemDataNames[ Catalog::IDT_Collection ],
                currCollection );
            Utils::SetAttrStr( specimen,
                Catalog::ItemDataNames[ Catalog::IDT_InventoryStatus ],
                Catalog::InventoryStatusStrings[ newType ] );
        }
    }
    SetInventoryStatusImage( );
    GetFrame( )->UpdateStatus( );
}
//--------------

void CatalogTreeCtrl::ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst )
{
    wxString title;
    if ( !itemSrc.IsOk( ) || !itemDst.IsOk( ) )
    {
        return;
    }

    title << "Insert Item " << GetItemText( itemSrc );

    wxMenu menu( title );
    wxString label = "    BEFORE " + GetItemText( itemDst );
    menu.Append( CatalogListTree_Before, label );
    label = "    AFTER " + GetItemText( itemDst );
    menu.Append( CatalogListTree_After, label );
    label = "    as CHILD of " + GetItemText( itemDst );
    menu.Append( CatalogListTree_AsChild, label );
    menu.Append( CatalogListTree_Cancel, "Cancel Drag" );

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
        case CatalogListTree_Before:
        {

            wxXmlNode* srcElement = GetItemNode( itemSrc );
            wxXmlNode* dstElement = GetItemNode( itemDst );

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
        case CatalogListTree_After:
        {

            wxXmlNode* srcElement = GetItemNode( itemSrc );
            wxXmlNode* dstElement = GetItemNode( itemDst );

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
        case CatalogListTree_AsChild:
        {

            wxXmlNode* srcElement = GetItemNode( itemSrc );
            wxXmlNode* dstElement = GetItemNode( itemDst );

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
        case CatalogListTree_Cancel:
        {

            break;
        }
    }
}

//--------------

void CatalogTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
{

    wxString title;

    wxMenu menu;
    if ( !id.IsOk( ) )
    {

    }
    else
    {
        //title = "Menu for no particular item";
        wxXmlNode* node = GetItemNode( id );
        if ( GetItemType( id ) == Catalog::NT_Entry )
        {
            wxMenu* inventoryMenu = new wxMenu( );

            inventoryMenu->Append( CatalogListTree_InventoryStatusNone, "None" );
            inventoryMenu->Append( CatalogListTree_InventoryStatusMissing, "Missing" );
            inventoryMenu->Append( CatalogListTree_InventoryStatusOrdered, "Ordered" );
            inventoryMenu->Append( CatalogListTree_InventoryStatusOwn, "Own" );
            inventoryMenu->Append( CatalogListTree_InventoryStatusOwnVariant, "OwnVariant" );
            inventoryMenu->Append( CatalogListTree_InventoryStatusExclude, "Exclude" );
            menu.Append( CatalogListTree_Inventory, "Inventory Status", inventoryMenu );
            menu.AppendSeparator( );
            menu.Append( CatalogListTree_Colnect, "GoTo Colnect" );
            menu.AppendSeparator( );
            menu.Append( CatalogListTree_Delete, "Delete Entry" );
            menu.Append( CatalogListTree_Add, "Add New Entry" );
        }
        else
        {
            menu.AppendSeparator( );
            menu.Append( CatalogListTree_Colnect, "GoTo Colnect" );
            menu.AppendSeparator( );
            menu.Append( CatalogListTree_StructureStamps, "Re-Group Multiples" );
            menu.Append( CatalogListTree_ResortTree, "Re-Sort Tree" );
            menu.Append( CatalogListTree_EditDetails, "Edit Catalog Details" );
        }
    }

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
        case CatalogListTree_Inventory:
        case CatalogListTree_InventoryStatusNone:
        {
            SetInventoryStatus( GetItemNode( id ), Catalog::ST_None );

        }
        break;
        case CatalogListTree_InventoryStatusMissing:
        {
            SetInventoryStatus( GetItemNode( id ), Catalog::ST_Missing );
        }
        break;

        case CatalogListTree_InventoryStatusOrdered:
        {
            SetInventoryStatus( GetItemNode( id ), Catalog::ST_Ordered );

        }
        break;

        case CatalogListTree_InventoryStatusOwn:
        {
            SetInventoryStatus( GetItemNode( id ), Catalog::ST_Own );
        }
        break;

        case CatalogListTree_InventoryStatusOwnVariant:
        {
            SetInventoryStatus( GetItemNode( id ), Catalog::ST_OwnVariant );

        }
        break;

        case CatalogListTree_InventoryStatusExclude:
        {
            SetInventoryStatus( GetItemNode( id ), Catalog::ST_Exclude );

        }
        break;
        // m_statusStrings.Add( Catalog::InventoryStatusStrings[ Catalog::ST_None ] );
        // m_statusStrings.Add( Catalog::InventoryStatusStrings[ Catalog::ST_Missing ] );
        // m_statusStrings.Add( Catalog::InventoryStatusStrings[ Catalog::ST_Ordered ] );
        // m_statusStrings.Add( Catalog::InventoryStatusStrings[ Catalog::ST_Own ] );
        // m_statusStrings.Add( Catalog::InventoryStatusStrings[ Catalog::ST_OwnVariant ] );
        // m_statusStrings.Add( Catalog::InventoryStatusStrings[ Catalog::ST_Exclude ] );

        case CatalogListTree_StructureStamps:
        {
            wxXmlNode* entry = GetItemNode( id );

            GetCatalogVolume( )->ReGroupMultiples( );
            ReSortTree( );

            wxTreeItemId newID = FindTreeItemID( entry );
            if ( newID )
            {
                Expand( newID );
                SelectItem( newID );
            }
        }
        break;
        case CatalogListTree_ResortTree:
        {
            ReSortTree( );
        }
        break;
        case CatalogListTree_EditDetails:
        {
            GetCatalogVolume( )->EditDetailsDialog( this );
        }
        break;


        case CatalogListTree_Colnect:
        {
            GoToColnect( id );
        }
        break;
        case CatalogListTree_Delete:
        {
            DeleteEntry( id );
        }
        break;
        case CatalogListTree_Add:
        {
            AddEntry( id );
        }
        break;
        default:
            // Fall through.
            break;
    }
}

//--------------

void CatalogTreeCtrl::SetInventoryStatusImage( )
{
    wxTreeItemId itemId = GetFocusedItem( );
    Catalog::Entry entry = GetNewEntry( itemId );
    if ( entry.IsOK( ) )
    {
        int status = entry.GetInventoryStatusType( );
        int format = entry.GetFormatType( );
        //Catalog::IconID iconID = Catalog::CatalogImageSelection[ format ][ status ];
        SetItemImage( itemId, GetInventoryIconId( &entry ) );
    }
}

//--------------

void CatalogTreeCtrl::SetItemNode( wxTreeItemId id, wxXmlNode* ele )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            data->SetCatNode( ele );
        }
    }
};

//--------------

void CatalogTreeCtrl::SetItemChecked( wxTreeItemId id, bool state )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            data->SetChecked( state );
            SetItemState( id, state );
        }
    }
};

//--------------

void CatalogTreeCtrl::SetItemImageFullName( wxTreeItemId id, wxString str )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            data->SetImageFullName( str );
        }
    }
};

//--------------

void CatalogTreeCtrl::SetItemStampLink( wxTreeItemId id, Utils::StampLink* link )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            data->SetStampLink( link );
        }
    }
};

//--------------

void CatalogTreeCtrl::SetNextState( const wxTreeItemId& itemId )
{
    wxXmlNode* element = GetItemNode( itemId );
    Catalog::Entry entry( element );
    if ( entry.IsOK( ) )
    {
        SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
        int state = GetItemState( itemId );
        SetItemChecked( itemId, state );
        GetFrame( )->UpdateStatus( );
        if ( state )
        {
            Utils::StampLink* link = AppendAlbumStamp( itemId );
            if ( !link )
            {
                SetItemState( itemId, Catalog::ST_Unchecked );
            }
        }
        else
        {
            DeleteAlbumStamp( itemId );
        }
    }
}

//--------------

void CatalogTreeCtrl::SetType( wxTreeItemId id, Catalog::CatalogBaseType type )
{
    if ( id.IsOk( ) )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->SetType( type );
        }
    }
};

//--------------

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

//--------------

void CatalogTreeCtrl::SortTree( wxTreeItemId parent )
{
    // std::cout << GetItemText( parent ) << "\n";
    // decend into the tree and sort its children
    wxTreeItemIdValue cookie;
    wxTreeItemId childItem = GetFirstChild( parent, cookie );
    while ( childItem.IsOk( ) )
    {
        // std::cout << "child:" << GetItemText( childItem ) << "\n";

        if ( GetChildrenCount( childItem, false ) >= 1 )
        {
            // descend and do it again
            SortTree( childItem );
        }
        childItem = GetNextChild( parent, cookie );
    }
    if ( HasChildren( parent ) )
    {
        //std::cout << "parent:" << GetItemText( parent ) << "\n";
        SortChildren( parent );
    }
}

//--------------

void CatalogTreeCtrl::XMLDumpNode( wxTreeItemId item, wxString str )
{

    if ( !item.IsOk( ) )
    {
        return;
    }
    wxXmlNode* ele = GetItemNode( item );
    Utils::XMLDumpNode( ele, str );
}

//--------------
void CatalogTreeCtrl::SelectStamp( wxString id )
{
    wxTreeItemId item = FindTreeItemID( id );
    if ( item.IsOk( ) )
    {
        this->SelectItem( item );
    }
}

void CatalogTreeCtrl::OnTreectrlItemCollapsed( wxTreeEvent& event )
{

    wxTreeItemId id = event.GetItem( );
    if ( !id.IsOk( ) )
    {
        while ( 1 ) { }
    }
    wxString before = GetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ] );
    SetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ], "true" );
    wxString after = GetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ] );
    event.Skip( );
}


void CatalogTreeCtrl::OnTreectrlItemExpanded( wxTreeEvent& event )
{
    wxTreeItemId id = event.GetItem( );
    wxString   a = GetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ] );
    SetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ], "false" );

    event.Skip( );

}

