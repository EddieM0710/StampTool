/**
 * @file TOCTreeCtrl.cpp
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

#include "utils/Project.h"
#include "utils/XMLUtilities.h"
#include "toc/TOCDefs.h"

#include "gui/GuiDefs.h"
#include "gui/StampToolFrame.h"
#include "gui/StampToolPanel.h"
#include "gui/TOCTreeCtrl.h"

wxIMPLEMENT_CLASS( TOCTreeCtrl, wxTreeCtrl );

wxBEGIN_EVENT_TABLE( TOCTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( ID_TOCTreeCtrl, TOCTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_TOCTreeCtrl, TOCTreeCtrl::OnEndDrag )
EVT_TREE_ITEM_MENU( ID_TOCTreeCtrl, TOCTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_COLLAPSED( ID_TOCTreeCtrl, TOCTreeCtrl::OnTreectrlItemCollapsed )
EVT_TREE_ITEM_EXPANDED( ID_TOCTreeCtrl, TOCTreeCtrl::OnTreectrlItemExpanded )
wxEND_EVENT_TABLE( )

//--------------

TOCTreeCtrl::TOCTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )
{
    m_reverseSort = false;

    CreateImageList( );
}

void TOCTreeCtrl::SetTreeItemCollapseState( wxTreeItemId childID )
{
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( childID );

    if ( data->GetCollapseState( ) )
    {
        Collapse( childID );
    }
    else
    {
        Expand( childID );
    }

}

wxXmlNode* TOCTreeCtrl::MakeNode( wxTreeItemId treeID, wxXmlNode* parent )
{
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( treeID );
    Utils::TOCBaseType type = data->GetType( );
    wxXmlNode* node = Utils::NewNode( parent, Utils::TOCBaseNames[ type ] );
    if ( type == Utils::TOC_Volume )
    {
        node->AddAttribute( "FileName", data->GetName( ) );
        node->AddAttribute( "CollapseState", Bool2String( data->GetCollapseState( ) ) );
    }
    else if ( type == Utils::TOC_Section )
    {
        node->AddAttribute( "Name", data->GetName( ) );
        node->AddAttribute( "CollapseState", Bool2String( data->GetCollapseState( ) ) );
    }

    return node;
}

void TOCTreeCtrl::MakeTree( wxTreeItemId parentID, wxXmlNode* parentNode ){
    wxXmlNode* node = MakeNode( parentID, parentNode );
    wxTreeItemIdValue cookie;
    wxTreeItemId childID = GetFirstChild( parentID, cookie );
    while ( childID.IsOk( ) )
    {
        MakeTree( childID, node );
        childID = GetNextChild( parentID, cookie );
    }
}

void TOCTreeCtrl::MakeTree( wxXmlNode* parentNode ){
    wxTreeItemId itemID = GetRootItem( );
    wxTreeItemIdValue cookie;

    wxTreeItemId childID = GetFirstChild( itemID, cookie );
    int i = 0;
    while ( childID.IsOk( ) )
    {
        MakeTree( childID, parentNode );
        childID = GetNextChild( itemID, cookie );
    }
}




//---------wxTreeItemId childID-----

wxTreeItemId TOCTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child, wxMenu* menu )
{
    Catalog::IconID icon;
    wxString label;
    wxMenu* subMenu;
    Utils::TOCBaseType nodeType;


    wxString nodeName = child->GetName( );
    nodeType = Utils::FindTOCBaseType( nodeName );

    TOCTreeItemData* itemData = CreateChildData( child, label, icon, nodeType );

    if ( !itemData )
    {
        return 0;
    }
    wxTreeItemId childID = AppendItem( parent, label, icon, -1, itemData );
    m_currVolumeID = childID;
    int id = itemData->GetMenuID( );
    itemData->GetType( );
    if ( nodeType == Utils::TOC_Volume )
    {
        menu->Append( id, label );
    }
    else if ( nodeType == Utils::TOC_Section )
    {
        subMenu = new wxMenu( );
        menu->Append( id, label, subMenu );
    }
    LinkMenuItemToTreeItem( id, childID );

    // not a entry just add the appropriate image
    SetItemImage( childID, Catalog::Icon_Folder );


    // now do it all again for this entrys children
    wxXmlNode* grandChild = child->GetChildren( );
    while ( grandChild )
    {

        // start adding child elements to it.
        AddChild( childID, grandChild, subMenu );
        grandChild = grandChild->GetNext( );
    }
    SetTreeItemCollapseState( childID );
    return childID;
}

//--------------


//--------------




TOCTreeItemData* TOCTreeCtrl::CreateChildData( wxXmlNode* child,
    wxString& label,
    Catalog::IconID& icon,
    Utils::TOCBaseType& nodeType )
{
    VolumePtr catalogVolume = 0;
    wxString name = child->GetName( );
    nodeType = Utils::FindTOCBaseType( name );
    //wxString label;
    //Catalog::IconID icon;
    int menuID = 0;
    bool collapseState = String2Bool( Utils::GetAttrStr( child, "CollapseState" ) );

    if ( nodeType == Utils::TOC_Volume )
    {
        wxXmlAttribute* attr = child->GetAttributes( );
        while ( attr )
        {
            attr = attr->GetNext( );
        }
        name = Utils::GetAttrStr( child, "FileName" );
        wxString volName = Utils::GetAttrStr( child, "VolumeName" );
        catalogVolume = FindVolume( volName );
        label = GetVolumeName( catalogVolume );
        menuID = GetNextVolumeID( );
    }
    else
    {
        //otherwise get the label
        const wxXmlAttribute* attr = Utils::GetAttribute( child, "Name" );
        label = attr->GetValue( );
        name = label;
        icon = Catalog::Icon_Folder;
        menuID = GetNextVolumeID( );
    }

    // create the item data 
    return new TOCTreeItemData( nodeType, collapseState, name, label, menuID, catalogVolume );
}

//--------------

void TOCTreeCtrl::ClearTree( )
{

    // then clobber all the tree items
    DeleteAllItems( );
}

//--------------

void TOCTreeCtrl::CreateImageList( )
{
    AssignImageList( CreateCatalogImageList( ) );
}

//--------------

void TOCTreeCtrl::DeleteEntry( wxTreeItemId id )
{
}


//--------------


void TOCTreeCtrl::EnableState( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child.IsOk( ) )
        {
            EnableState( child );
            child = GetNextChild( id, cookie );
        }
    }
}

// //--------------

// wxTreeItemId TOCTreeCtrl::FindTreeItemID( wxXmlNode* ele, wxTreeItemId id )
// {
//     if ( id.IsOk( ) )
//     {
//         wxTreeItemIdValue cookie;
//         wxTreeItemId child = GetFirstChild( id, cookie );
//         while ( child )
//         {
//             if ( IsElement( child, ele ) )
//             {
//                 return child;
//             }
//             if ( this->HasChildren( child ) )
//             {
//                 wxTreeItemId idFound = FindTreeItemID( ele, child );
//                 if ( idFound )
//                 {
//                     return idFound;
//                 }
//             }
//             child = this->GetNextChild( id, cookie );
//         }
//     }
//     return 0;
// }

//--------------

// wxTreeItemId TOCTreeCtrl::FindTreeItemID( wxXmlNode* ele )
// {
//     wxTreeItemId root = GetRootItem( );
//     return FindTreeItemID( ele, root );
// }


//--------------

wxTreeItemId TOCTreeCtrl::FindFirstEntryChild( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child )
        {
            if ( GetItemType( child ) == Utils::TOC_Volume )
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

wxString TOCTreeCtrl::GetItemDesc( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetDesc( );
        }
    }
    return "";
};

//--------------

wxString TOCTreeCtrl::GetItemImageFullName( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
        if ( data )
        {
        }
    }
    return "";
};

//--------------

// wxXmlNode* TOCTreeCtrl::GetItemNode( wxTreeItemId id )
// {
//     if ( id.IsOk( ) )
//     {
//         TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
//         if ( data )
//         {
//             return data->GetNodeElement( );
//         }
//     }
//     return ( wxXmlNode* ) 0;
// };

//--------------

Utils::TOCBaseType  TOCTreeCtrl::GetItemType( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetType( );
        }
    }
    return Utils::TOCBaseType::TOC_None;;
};
//--------------

// wxXmlNode* TOCTreeCtrl::GetNewEntry( wxTreeItemId itemId )
// {
//     return GetItemNode( itemId );
// }

//--------------

// wxString TOCTreeCtrl::GetAttribute( wxTreeItemId catTreeID, wxString name )
// {
//     if ( !catTreeID.IsOk( ) ) return "";
//     wxXmlNode* node = GetItemNode( catTreeID );
//     if ( node )
//     {
//         wxString val = Utils::GetAttrStr( node, name );
//         return val;
//     }
//     return "";
// }



// void  TOCTreeCtrl::SetAttribute( wxTreeItemId catTreeID, wxString name, wxString val )
// {
//     if ( catTreeID.IsOk( ) )
//     {
//         wxXmlNode* node = GetItemNode( catTreeID );
//         if ( node )
//         {
//             Utils::SetAttrStr( node, name, val );

//         }
//     }
// }
//--------------
wxTreeItemId TOCTreeCtrl::MoveItemAsChild( wxTreeItemId srcID, wxTreeItemId parentID )
{
    wxTreeItemId newID;
    if ( srcID.IsOk( ) && parentID.IsOk( ) )
    {

        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( srcID );
        TOCTreeItemData* newData = new TOCTreeItemData( *data );
        newID = AppendItem( parentID, GetItemText( srcID ), GetItemImage( srcID ), -1, newData );
        if ( HasChildren( srcID ) )
        {
            wxTreeItemIdValue   	cookie;
            wxTreeItemId child = GetFirstChild( srcID, cookie );
            while ( child )
            {
                MoveItemAsChild( child, newID );
                child = GetNextChild( srcID, cookie );
            }
        }
    }
    return newID;
}
wxTreeItemId TOCTreeCtrl::MoveItem( wxTreeItemId srcID, wxTreeItemId destID, bool after )
{
    wxTreeItemId newID = 0;
    if ( srcID.IsOk( ) && destID.IsOk( ) )
    {

        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( srcID );
        TOCTreeItemData* newData = new TOCTreeItemData( *data );
        wxTreeItemId parent = GetItemParent( destID );
        //copy itemData
        if ( after )
        {
            // insert after sibling
            newID = InsertItem( parent, destID, GetItemText( srcID ), GetItemImage( srcID ), -1, newData );
        }
        else
        {
            wxTreeItemId prevSibling = GetPrevSibling( destID );
            if ( prevSibling.IsOk( ) )
            {
                newID = InsertItem( parent, prevSibling, GetItemText( srcID ), GetItemImage( srcID ), -1, newData );
            }
            else
            {
                newID = InsertItem( parent, 0, GetItemText( srcID ), GetItemImage( srcID ), -1, newData );
            }
        }
        if ( HasChildren( srcID ) )
        {
            wxTreeItemIdValue cookie;
            wxTreeItemId child = GetFirstChild( srcID, cookie );
            while ( child )
            {
                MoveItemAsChild( srcID, newID );
                child = GetNextChild( srcID, cookie );
            }
        }
    }
    return newID;
}

//--------------

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId TOCTreeCtrl::InsertChild( wxTreeItemId sibling, wxXmlNode* child, bool after )
{
    Catalog::IconID icon;
    wxString label;
    Utils::TOCBaseType nodeType;
    TOCTreeItemData* itemData = CreateChildData( child, label, icon, nodeType );

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



    // not a entry just add the appropriate image
    SetItemImage( childID, Catalog::Icon_Folder );
    SetItemState( childID, wxTREE_ITEMSTATE_NEXT );


    EnableState( childID );

    // now do it all again for this entrys children
    wxXmlNode* grandChild = child->GetChildren( );
    while ( grandChild )
    {

        // start adding child elements to it.
        AddChild( childID, grandChild, 0 );
        grandChild = grandChild->GetNext( );
    }

    return childID;
}

//--------------

// bool TOCTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
// {
//     if ( item.IsOk( ) )
//     {
//         wxXmlNode* dataEle = GetItemNode( item );
//         if ( dataEle == ele )
//         {
//             return true;
//         }
//     }
//     return false;
// }

//--------------

// bool TOCTreeCtrl::IsElement( wxTreeItemId item, wxString entryID )
// {
//     if ( item.IsOk( ) )
//     {
//         TOCTreeItemData* itemData = ( TOCTreeItemData* ) GetItemData( item );
//         Utils::TOCBaseType  type = itemData->GetType( );
//         if ( type == Catalog::NT_Entry )
//         {
//             Catalog::Entry stamp( itemData->GetNodeElement( ) );
//             return stamp.IsCatalogCode( entryID );

//         }
//     }
//     return false;
// }

//--------------

void TOCTreeCtrl::LoadTree( wxXmlNode* TOCNode, wxString str )
{
    ClearTree( );
    if ( TOCNode )
    {

        wxString name = GetProject( )->GetProjectFilename( );
        // Create the root item
        bool collapseState = String2Bool( Utils::GetAttrStr( TOCNode, "CollapseState" ) );

        TOCTreeItemData* itemData = new TOCTreeItemData( Utils::TOC_Volume,
            collapseState, "TOC", name );
        wxTreeItemId rootID = AddRoot( "TOC", Catalog::Icon_Folder, 1, itemData );
        m_menu = new wxMenu( str );

        wxXmlNode* child = TOCNode->GetChildren( );
        while ( child )
        {
            // start adding child elements to it.
            AddChild( rootID, child, m_menu );
            child = child->GetNext( );
        }
        //        SortTree( rootID );

        Expand( rootID );
    }
}

//--------------

void TOCTreeCtrl::OnBeginDrag( wxTreeEvent& event )
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
    // event.Skip( );

}

//--------------

void TOCTreeCtrl::OnEndDrag( wxTreeEvent& event )
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
    //  event.Skip( );

}

//--------------

int TOCTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    TOCTreeItemData* itemData1 = ( TOCTreeItemData* ) 0;
    TOCTreeItemData* itemData2 = ( TOCTreeItemData* ) 0;
    if ( item1.IsOk( ) && item2.IsOk( ) )
    {
        void* ptr2 = item2.GetID( );
        void* ptr1 = item1.GetID( );
        if ( ( ptr1 < ( void* ) 0xFFFF ) || ( ptr2 < ( void* ) 0xFFFF ) )return 0;
        bool b1 = item1.IsOk( );
        bool b2 = item2.IsOk( );

        itemData1 = ( TOCTreeItemData* ) GetItemData( item1 );

        itemData2 = ( TOCTreeItemData* ) GetItemData( item2 );

        return itemData1->Cmp( itemData2 );
    }
    return 0;
}

//--------------

void TOCTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    ShowMenu( itemId, clientpt );
    event.Skip( );
}
// wxXmlNode* TOCTreeCtrl::GetCurrVolumeRoot( )
// {
//     TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( m_currVolumeID );
//     Utils::TOCBaseType type = data->GetType( );
//     if ( type == Utils::TOC_Volume )
//     {
//         Catalog::CatalogVolume* vol = ( Catalog::CatalogVolume* ) data->GetVolume( );
//         wxXmlNode* xmlNode = vol->GetDoc( )->GetRoot( );
//         return xmlNode;
//     }
//     return ( wxXmlNode* ) 0;
// }
//--------------

//--------------


//--------------

void TOCTreeCtrl::ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst )
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

            // wxXmlNode* srcElement = GetItemNode( itemSrc );
            // wxXmlNode* dstElement = GetItemNode( itemDst );

            // move the element
            // this means making a copy and deleting the old one so old pointers are
            // trash
          //  wxXmlNode* newElement = Catalog::InsertEntry( dstElement, srcElement, false );

            // now update the tree with the new one
            //wxTreeItemId id = InsertChild( itemDst, newElement, false );
            //wxTreeItemId id = InsertChild( itemDst, false );

            wxTreeItemId id = MoveItem( itemSrc, itemDst, false );
            //wxTreeItemId id = AddChild( itemDst, newElement );
            SelectItem( itemDst );
            Delete( itemSrc );

            break;
        }
        case CatalogListTree_After:
        {

            // wxXmlNode* srcElement = GetItemNode( itemSrc );
            // wxXmlNode* dstElement = GetItemNode( itemDst );

            // move the element
            // this means making a copy and deleting the old one so old pointers are
            // trash
            // wxXmlNode* newElement = Catalog::InsertEntry( dstElement, srcElement, true );

            // now update the tree with the new one
           // wxTreeItemId id = InsertChild( itemDst, newElement, true );
            //wxTreeItemId id = InsertChild( itemDst, true );
            wxTreeItemId id = MoveItem( itemSrc, itemDst, true );
            //wxTreeItemId id = AddChild( itemDst, newElement );
            SelectItem( itemDst );
            Delete( itemSrc );

            break;
        }
        case CatalogListTree_AsChild:
        {

            // wxXmlNode* srcElement = GetItemNode( itemSrc );
            // wxXmlNode* dstElement = GetItemNode( itemDst );

            // move the element
            // this means making a copy and deleting the old one so old pointers are
            // trash
        //    wxXmlNode* newElement = Catalog::MoveEntry( dstElement, srcElement );

            // now update the tree with the new one
            // wxTreeItemId newID;
            // TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( itemSrc );
            // TOCTreeItemData* newData = new TOCTreeItemData( *data );
            // newID = AppendItem( itemDst, GetItemText( itemSrc ), GetItemImage( itemSrc ), -1, newData );
            MoveItemAsChild( itemSrc, itemDst );

            // AppendItem( )
             //    wxTreeItemId id = AddChild( itemDst, newElement, 0 );
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

void TOCTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
{

    wxString title;

    wxMenu menu;
    if ( !id.IsOk( ) )
    {

    }
    else
    {
        //title = "Menu for no particular item";
       // wxXmlNode* node = GetItemNode( id );

        menu.AppendSeparator( );


        menu.Append( CatalogListTree_ResortTree, "Re-Sort Tree" );
        menu.Append( CatalogListTree_EditDetails, "Edit Catalog Details" );
    }

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {


        case CatalogListTree_ResortTree:
        {
            //            ReSortTree( );
        }
        break;
        case CatalogListTree_EditDetails:
        {
            EditDetailsDialog( this );
        }
        break;

        case CatalogListTree_Delete:
        {
            DeleteEntry( id );
        }
        break;
        case CatalogListTree_Add:
        {
            //       AddEntry( id );
        }
        break;
        default:
        // Fall through.
        break;
    }
}


//--------------

// void TOCTreeCtrl::SetItemNode( wxTreeItemId id, wxXmlNode* ele )
// {
//     if ( id.IsOk( ) )
//     {
//         TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
//         if ( data )
//         {
//             data->SetCatNode( ele );
//         }
//     }
// };

//--------------

void TOCTreeCtrl::SetItemImageFullName( wxTreeItemId id, wxString str )
{
    if ( id.IsOk( ) )
    {
        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
        if ( data )
        {
        }
    }
};

//--------------

void TOCTreeCtrl::SetType( wxTreeItemId id, Utils::TOCBaseType type )
{
    if ( id.IsOk( ) )
    {
        TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->SetType( type );
        }
    }
};

//--------------



// //--------------

// void TOCTreeCtrl::SortTree( wxTreeItemId parent )
// {
//     // std::cout << GetItemText( parent ) << "\n";
//     // decend into the tree and sort its children
//     wxTreeItemIdValue cookie;
//     wxTreeItemId childItem = GetFirstChild( parent, cookie );
//     while ( childItem.IsOk( ) )
//     {
//         // std::cout << "child:" << GetItemText( childItem ) << "\n";

//         if ( GetChildrenCount( childItem, false ) >= 1 )
//         {
//             // descend and do it again
//             SortTree( childItem );
//         }
//         childItem = GetNextChild( parent, cookie );
//     }
//     if ( HasChildren( parent ) )
//     {
//         //std::cout << "parent:" << GetItemText( parent ) << "\n";
//         SortChildren( parent );
//     }
// }

//--------------

// void TOCTreeCtrl::XMLDumpNode( wxTreeItemId item, wxString str )
// {

//     if ( !item.IsOk( ) )
//     {
//         return;
//     }
//     wxXmlNode* ele = GetItemNode( item );
//     Utils::XMLDumpNode( ele, str );
// }


void TOCTreeCtrl::OnTreectrlItemCollapsed( wxTreeEvent& event )
{

    wxTreeItemId id = event.GetItem( );
    if ( !id.IsOk( ) )
    {
        while ( 1 )
        {
        }
    }
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
    data->SetCollapseState( true );
    event.Skip( );
}


void TOCTreeCtrl::OnTreectrlItemExpanded( wxTreeEvent& event )
{
    wxTreeItemId id = event.GetItem( );
    TOCTreeItemData* data = ( TOCTreeItemData* ) GetItemData( id );
    data->SetCollapseState( false );
    event.Skip( );

}

