/**
 * @file CompareTreeCtrl.cpp
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

 //#include "StampToolApp.h"
#include "catalog/CatalogVolume.h"
//#include "catalog/CatalogCode.h"
#include "catalog/CatalogData.h"
#include "catalog/Entry.h"
#include "catalog/MergeList.h"
#include "collection/CollectionList.h"
#include "gui/GuiDefs.h"
#include "gui/StampToolFrame.h"
#include "gui/StampToolPanel.h"
#include "gui/CompareTreeCtrl.h"
#include "gui/CatalogTOCTreeCtrl.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/NewStampDialog.h"
#include "gui/ComparePanel.h"

//wxDECLARE_APP( StampToolApp );

wxIMPLEMENT_CLASS( CompareTreeCtrl, wxTreeCtrl );

wxBEGIN_EVENT_TABLE( CompareTreeCtrl, wxTreeCtrl )

EVT_TREE_SEL_CHANGED( ID_COMPARETREECTRL, CompareTreeCtrl::OnSelChanged )
EVT_TREE_ITEM_MENU( ID_COMPARETREECTRL, CompareTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_COLLAPSED( ID_COMPARETREECTRL, CompareTreeCtrl::OnTreectrlItemCollapsed )
EVT_TREE_ITEM_EXPANDED( ID_COMPARETREECTRL, CompareTreeCtrl::OnTreectrlItemExpanded )
wxEND_EVENT_TABLE( )



//-------------

int CompareTreeItemData::Cmp( CompareTreeItemData* itemData2 )
{
    Catalog::CatalogBaseType type2 = itemData2->GetType( );

    if ( m_type != type2 )
    {
        return 0;//( int ) m_type - ( int ) type2;
    }
    else
    {
        // they are the same type
        if ( m_type == Catalog::NT_Entry )
        {
            // they are both entries

            Catalog::Entry entry1( m_element );
            wxString id1 = entry1.GetID( );
            // wxString date1 = entry1.GetIssuedDate( );
            // wxString desc1 = m_desc;
            // wxString series1 = entry1.GetSeries( );
            wxXmlNode* node2 = itemData2->GetNodeElement( );
            Catalog::Entry entry2( node2 );
            wxString id2 = entry2.GetID( );
            // wxString date2 = entry2.GetIssuedDate( );
            // wxString desc2 = itemData2->GetDesc( );
            // wxString series2 = entry2.GetSeries( );
            return CompareID( id1, id2 );
        }
        return 0;
    }
};

//------------

CompareTreeItemData::CompareTreeItemData( wxWindow* parent, Catalog::CatalogBaseType type, const wxString desc,
    wxXmlNode* ele, wxXmlNode* mergeNode )
{
    m_type = type;
    m_desc = desc;
    m_element = ele;
    m_parent = ( CompareTreeCtrl* ) parent;
    if ( ele )
    {
        m_imageFullPath = Utils::GetAttrStr( ele, Catalog::DataTypeNames[ Catalog::DT_ImageName ] );
    }
    else
    {
        m_imageFullPath = "";
    }
    if ( m_imageFullPath.IsEmpty( ) )
    {
        Catalog::Entry stamp( ele );
        wxString m_imageFullPath = stamp.FindImageName( );
    }
    if ( m_type == Catalog::NT_Entry )
    {

        m_mergeData = new Catalog::MergeData( m_parent->GetComparePanel( ) );
        m_mergeData->SetTargetEntry( m_element );
        m_mergeData->SetMergeEntry( mergeNode );
    }
    m_ok = 12345;
};

//------------

CompareTreeCtrl::CompareTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )
{
    m_parent = parent;
    CreateImageList( );
    CreateStateImageList( );
    Connect( id, wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler( CompareTreeCtrl::OnSelChanged ) );
    Connect( id, wxEVT_TREE_ITEM_MENU, wxTreeEventHandler( CompareTreeCtrl::OnItemMenu ) );

}
//--------------

void  CompareTreeCtrl::SetComparePanel( ComparePanel* comparePanel ){
    m_comparePanel = comparePanel;
}

ComparePanel* CompareTreeCtrl::GetComparePanel( )
{
    return m_comparePanel;
};

//     icons[ Catalog::Icon_StampUnknown ] = wxIcon( StampBrown );
//     icons[ Catalog::Icon_StampMissing ] = wxIcon( StampRed );
//     icons[ Catalog::Icon_StampOrdered ] = wxIcon( StampBlue );
//     icons[ Catalog::Icon_StampOwn ] = wxIcon( StampGreen );
//     icons[ Catalog::Icon_StampOwnVariant ] = wxIcon( StampYellow );
//     icons[ Catalog::Icon_StampExclude ] = wxIcon( StampBlack );
// //------------
//  wxTreeItemIcon GetIcon( Catalog::MergeStatus status )
//  {
//        if (  status == MS_Undefined )
//        wxTreeItemIcon
//                if (  MS_Same = 0,
//                if (  MS_Different,
//                if (  MS_TargetMissing,
//                if (  MS_MergeMissing)
//  }

Catalog::IconID CompareTreeCtrl::GetIconId( Catalog::Entry* entry, Catalog::MergeStatus status )
{
    int format = entry->GetFormatType( );
    return Catalog::CatalogImageSelection[ format ][ status ];
}


wxTreeItemId CompareTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child )
{
    Catalog::IconID icon;
    wxString label;
    Catalog::CatalogBaseType nodeType;
    CompareTreeItemData* itemData = CreateChildData( child, 0, label, icon, nodeType );

    if ( !itemData )
    {
        return 0;
    }
    wxTreeItemId childID = AppendItem( parent, label, icon, -1, itemData );



    if ( nodeType == Catalog::NT_Entry )
    {
        Catalog::MergeData* entry = new Catalog::MergeData( m_comparePanel );
        entry->SetTargetEntry( child );
        Catalog::MergeStatus status = entry->SetStatus( );

        Catalog::Entry* catEntry = new Catalog::Entry( child );
        Catalog::IconID icon = GetIconId( catEntry, status );
        //set the icon for the appropriate state
        SetItemImage( childID, icon );

    }
    else
    {
        // not a entry just add the appropriate image
        SetItemImage( childID, Catalog::Icon_Folder );
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

//------------

void CompareTreeCtrl::AddEntry( wxTreeItemId id )
{
    NewStampDialog newEntryDialog( this, 12345, _( "Add New Entry" ) );

    Catalog::CatalogBaseType  type = GetItemType( id );
    if ( type == Catalog::NT_Entry )
    {
        id = GetItemParent( id );
    }
    wxXmlNode* parent = GetItemNode( id );
    wxXmlNode* stampNode = Utils::NewNode( ( wxXmlNode* ) 0, Catalog::CatalogBaseNames[ Catalog::NT_Entry ] );
    Catalog::Entry  stamp( stampNode );
    newEntryDialog.SetStamp( &stamp );
    if ( newEntryDialog.ShowModal( ) == wxID_CANCEL )
    {
        return; // the user changed idea..
    }
    //      newEntryDialog.get
    parent->AddChild( stampNode );
    AddChild( id, stampNode );

}

//-------------

//--------------

CompareTreeItemData* CompareTreeCtrl::CreateChildData( wxXmlNode* targetNode, wxXmlNode* mergeNode,
    wxString& label,
    Catalog::IconID& icon,
    Catalog::CatalogBaseType& nodeType )
{
    wxXmlNode* node = targetNode;
    if ( !targetNode )
    {
        node = mergeNode;
    }

    wxString name = node->GetName( );
    nodeType = Catalog::FindCatalogBaseType( name );
    //wxString label;
    //Catalog::IconID icon;

    //if the child element is not a entry
    //if ( !name.Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Entry ] ) )
    if ( nodeType == Catalog::NT_Entry )
    {
        // then we add the appropriate icon and label
        Catalog::Entry entry( node );
        // entry combines the entryID and its name to form a label
        label = entry.GetLabel( );

        icon = Catalog::Icon_Stamp;
    }
    else
    {
        // if it is a specimen or catalog code return because 
        // they don't go in the tree.
        if ( ( nodeType == Catalog::NT_Inventory )
            || ( nodeType == Catalog::NT_Item )
            //  || ( nodeType == Catalog::NT_CatalogCode ) 
            )
        {
            return 0;
        }
        else
        {
            //otherwise get the label
            const wxXmlAttribute* attr = Utils::GetAttribute( node, "Name" );
            label = attr->GetValue( );
            icon = Catalog::Icon_Folder;
        }
    }

    // create the item data 
    return new CompareTreeItemData( this, nodeType, label, targetNode, mergeNode );
}

//--------------

void CompareTreeCtrl::Clear( )
{
    // first make sure all the links to the items are gone
    Utils::StampList* stampList = GetStampAlbumCatalogLink( );
    stampList->ClearCatalogLinks( );
    GetCatalogData( )->SetCurrentStamp( 0 );
    // then clobber all the tree items
    DeleteAllItems( );
}

//--------------

void CompareTreeCtrl::CreateImageList( )
{
    AssignImageList( CreateCatalogImageList( ) );
}

//--------------

void CompareTreeCtrl::CreateStateImageList( )
{
    AssignStateImageList( CreateCatalogStateImageList( ) );
}


//--------------

//--------------

wxTreeItemId CompareTreeCtrl::FindFirstEntryChild( wxTreeItemId id )
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

wxTreeItemId CompareTreeCtrl::FindTreeItemID( wxXmlNode* ele, wxTreeItemId id )
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

wxTreeItemId CompareTreeCtrl::FindTreeItemID( wxString entryID, wxTreeItemId id )
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

wxTreeItemId CompareTreeCtrl::FindTreeItemID( wxXmlNode* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//--------------

wxTreeItemId CompareTreeCtrl::FindTreeItemID( wxString entryID )
{
    wxTreeItemId root = GetRootItem( );
    if ( root.IsOk( ) )
    {

        return FindTreeItemID( entryID, root );
    }
    return ( wxTreeItemId ) 0;
}

//--------------

wxString CompareTreeCtrl::GetAttribute( wxTreeItemId catTreeID, wxString name )
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

//--------------

wxString CompareTreeCtrl::GetID( wxTreeItemId catTreeID )
{
    if ( !catTreeID.IsOk( ) ) return "";
    wxXmlNode* node = GetItemNode( catTreeID );
    if ( node && !node->GetName( ).Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Entry ] ) )
    {
        Catalog::Entry stamp( node );
        wxString val = stamp.GetID( );
        //Utils::GetAttrStr( node, name );
        return val;
    }
    return "";
}

//--------------

wxString CompareTreeCtrl::GetImage( wxTreeItemId catTreeID )
{
    if ( !catTreeID.IsOk( ) ) return "";
    wxXmlNode* node = GetItemNode( catTreeID );
    if ( node && !node->GetName( ).Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Entry ] ) )
    {
        Catalog::Entry stamp( node );
        wxString val = stamp.FindImageName( );
        //Utils::GetAttrStr( node, name );
        return val;
    }
    return "";
}

//--------------

wxString CompareTreeCtrl::GetItemDesc( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetDesc( );
        }
    }
    return "";
};

//--------------

wxString CompareTreeCtrl::GetItemImageFullName( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetImageFullName( );
        }
    }
    return "";
};

//--------------

wxXmlNode* CompareTreeCtrl::GetItemNode( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetNodeElement( );
        }
    }
    return ( wxXmlNode* ) 0;
};

//--------------

Catalog::CatalogBaseType  CompareTreeCtrl::GetItemType( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->GetType( );
        }
    }
    return Catalog::CatalogBaseType::NT_None;;
};
//--------------

wxXmlNode* CompareTreeCtrl::GetNewEntry( wxTreeItemId itemId )
{
    return GetItemNode( itemId );
}

//--------------

wxXmlNode* CompareTreeCtrl::GetSelectionNode( )
{
    wxTreeItemId id = GetSelection( );
    return GetItemNode( id );
}

//--------------

wxString CompareTreeCtrl::GetImageFullName( wxTreeItemId catTreeID )
{

    if ( catTreeID.IsOk( ) )
    {
        wxString imageName = GetItemImageFullName( catTreeID );
        if ( imageName.IsEmpty( ) )
        {
            wxString id = GetImage( catTreeID );
            wxString imageName = GetProject( )->GetImageFullPath( id );
            SetItemImageFullName( catTreeID, id );
        }
        return imageName;
    }
    return "";
}

//--------------

void CompareTreeCtrl::GoToColnect( wxTreeItemId id )
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
            int a = system( cmd.fn_str( ) );
        }

    }
}

//--------------

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId CompareTreeCtrl::InsertChild( wxTreeItemId sibling, wxXmlNode* child, bool after )
{
    Catalog::IconID icon;
    wxString label;
    Catalog::CatalogBaseType nodeType;
    CompareTreeItemData* itemData = CreateChildData( child, 0, label, icon, nodeType );

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

        // Catalog::MergeStatus status = entry->SetStatus( );
        // Catalog::Entry* catEntry = new Catalog::Entry(child);
        SetItemImage( childID, Catalog::Icon_Stamp );

    }
    else
    {
        // not a entry just add the appropriate image
        SetItemImage( childID, Catalog::Icon_Folder );
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

bool CompareTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
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

bool CompareTreeCtrl::IsElement( wxTreeItemId item, wxString entryID )
{
    if ( item.IsOk( ) )
    {
        CompareTreeItemData* itemData = ( CompareTreeItemData* ) GetItemData( item );
        Catalog::CatalogBaseType  type = itemData->GetType( );
        if ( type == Catalog::NT_Entry )
        {
            Catalog::Entry stamp( itemData->GetNodeElement( ) );
            return stamp.IsCatalogCode( entryID );

        }
    }
    return false;
}
//--------------

//--------------

void CompareTreeCtrl::LoadCompareTree( wxXmlNode* root )
{
    Clear( );

    if ( root )
    {
        wxString name = root->GetName( );
        wxString catVolName = "";
        if ( root->GetAttribute( "Name", &catVolName ) )
        {
            name += " - " + catVolName;
        }

        // Create the tree root item
        CompareTreeItemData* itemData
            = new CompareTreeItemData( this, Catalog::NT_Catalog, name, root, 0 );
        wxTreeItemId rootID = AddRoot( name, Catalog::Icon_Folder, 1, itemData );

        //iterate through the xml volume entries and add them to the tree
        wxXmlNode* child = root->GetChildren( );
        while ( child )
        {
            // start adding child elements to it.
            AddChild( rootID, child );
            child = child->GetNext( );
        }

        Expand( rootID );
    }

}

wxTreeItemId  CompareTreeCtrl::FindTargetEntryForNewEntry( wxXmlNode* node, Catalog::DataTypes type )
{
    wxTreeItemId id = this->GetRootItem( );
    wxString searchVal = node->GetAttribute( Catalog::DataTypeNames[ type ] );
    return FindTargetEntryForNewEntry( id, type, searchVal );
}

//--------------

wxTreeItemId  CompareTreeCtrl::FindTargetEntryForNewEntry(
    wxTreeItemId id, Catalog::DataTypes type, wxString searchVal )
{
    if ( id.IsOk( ) )
    {
        wxXmlNode* node = GetItemNode( id );
        if ( node )
        {
            wxString nodeval = node->GetAttribute( Catalog::DataTypeNames[ type ] );
            if ( !searchVal.Cmp( nodeval ) )
            {
                return id;
            }

        }
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child.IsOk( ) )
        {
            wxTreeItemId found = FindTargetEntryForNewEntry( child, type, searchVal );
            if ( found.IsOk( ) )
            {
                return found;
            }
            child = GetNextChild( id, cookie );
        }
    }
    return 0;
}
//
wxTreeItemId CompareTreeCtrl::FindForiegn( ){
    wxTreeItemId rootId = GetRootItem( );
    wxTreeItemIdValue  	cookie;
    wxTreeItemId child = wxTreeCtrl::GetFirstChild( rootId, cookie );
    while ( child.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( child );
        Catalog::CatalogBaseType type = data->GetType( );
        if ( type == Catalog::NT_Foriegn )
        {
            return child;
        }
        child = GetNextSibling( child );
    }
    return 0;
}


void CompareTreeCtrl::AddMergeToEntryList( wxXmlNode* node )
{
    if ( node )
    {
        // Entry entry( node );

        wxTreeItemId  id = FindTargetEntryForNewEntry( node, Catalog::DT_Link );
        if ( id.IsOk( ) )
        {
            CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
            if ( data )
            {
                Catalog::MergeData* mergeData = data->GetMergeData( );
                mergeData->SetMergeEntry( node );
                return;
            }

        }
        wxTreeItemId rootId = GetRootItem( );

        wxTreeItemId foriegnRootID = FindForiegn( );

        if ( foriegnRootID.IsOk( ) )
        {

            //    AppendItem( foriegnRootID, foriegnRootName, -1, -1, foriegnRootData );
            CompareTreeItemData* foriegnRootData = ( CompareTreeItemData* ) GetItemData( foriegnRootID );
            wxXmlNode* foriegnNode = foriegnRootData->GetNodeElement( );
            Catalog::IconID icon;
            wxString label;
            Catalog::CatalogBaseType nodeType;
            CompareTreeItemData* foriegnItemData = CreateChildData( 0, node, label, icon, nodeType );
            Catalog::MergeData* mergeData = foriegnItemData->GetMergeData( );
            mergeData->SetMergeEntry( node );

            foriegnRootID = AppendItem( foriegnRootID, label, icon, -1, foriegnItemData );

        }
        else
        {
            // didnt find the foriegn root so make one
            wxString foriegnRootName = m_comparePanel->m_mergeVolume->GetName( );
            CompareTreeItemData* foriegnRootData = new CompareTreeItemData( this, Catalog::NT_Foriegn, foriegnRootName, 0 );

            if ( !foriegnRootData )
            {
                return;
            }
            foriegnRootID = AppendItem( rootId, foriegnRootName, -1, -1, foriegnRootData );
            Catalog::IconID icon;
            wxString label;
            Catalog::CatalogBaseType nodeType;
            CompareTreeItemData* foriegnItemData = CreateChildData( 0, node, label, icon, nodeType );
            Catalog::MergeData* mergeData = foriegnItemData->GetMergeData( );
            mergeData->SetMergeEntry( node );
            foriegnRootID = AppendItem( foriegnRootID, label, icon, -1, foriegnItemData );
        }

        wxXmlNode* child = node->GetChildren( );
        while ( child )
        {
            AddMergeToEntryList( child );
            child = child->GetNext( );
        }
    }
};

wxTreeItemId CompareTreeCtrl::CopyForiegnChild( wxTreeItemId parent, wxXmlNode* child )
{
    Catalog::IconID icon;
    wxString label;
    Catalog::CatalogBaseType nodeType;
    CompareTreeItemData* itemData = CreateChildData( child, 0, label, icon, nodeType );

    if ( !itemData )
    {
        return 0;
    }
    wxTreeItemId childID = AppendItem( parent, label, icon, -1, itemData );



    if ( nodeType == Catalog::NT_Entry )
    {
        Catalog::MergeData* entry = new Catalog::MergeData( m_comparePanel );
        entry->SetTargetEntry( child );

        Catalog::MergeStatus status = entry->SetStatus( );
        Catalog::Entry* catEntry = new Catalog::Entry( child );
        Catalog::IconID icon = GetIconId( catEntry, status );

        //set the icon for the appropriate state
        SetItemImage( childID, icon );

    }
    else
    {
        // not a entry just add the appropriate image
        SetItemImage( childID, Catalog::Icon_Folder );
    }


    // now do it all again for this entrys children
    wxXmlNode* grandChild = child->GetChildren( );
    while ( grandChild )
    {

        if ( !grandChild->GetName( ).Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Entry ] ) )
        {
            // start adding child elements to it.
            //Add only non-Entry ChildrenClosing
            AddChild( childID, grandChild );
        }
        grandChild = grandChild->GetNext( );
    }
    SetTreeItemCollapseState( childID );
    return childID;
}


//--------------

void CompareTreeCtrl::LoadMergeToCompareTree( wxXmlNode* mergeRoot )
{
    if ( mergeRoot )
    {
        wxXmlNode* child = mergeRoot->GetChildren( );
        while ( child )
        {
            AddMergeToEntryList( child );
            child = child->GetNext( );
        }
    }
};
//--------------

int CompareTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    CompareTreeItemData* itemData1 = ( CompareTreeItemData* ) 0;
    CompareTreeItemData* itemData2 = ( CompareTreeItemData* ) 0;
    if ( item1.IsOk( ) && item2.IsOk( ) )
    {
        void* ptr2 = item2.GetID( );
        void* ptr1 = item1.GetID( );
        if ( ( ptr1 < ( void* ) 0xFFFF ) || ( ptr2 < ( void* ) 0xFFFF ) )return 0;
        bool b1 = item1.IsOk( );
        bool b2 = item2.IsOk( );

        itemData1 = ( CompareTreeItemData* ) GetItemData( item1 );

        itemData2 = ( CompareTreeItemData* ) GetItemData( item2 );

        return itemData1->Cmp( itemData2 );
    }
    return 0;
}

//--------------

void CompareTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

//--------------
bool CompareTreeCtrl::IsEntryNode( wxTreeItemId itemId )
{
    CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( itemId );
    if ( data->GetType( ) == Catalog::NT_Entry )
    {
        return true;
    }
    return false;
}
wxTreeItemId CompareTreeCtrl::FindNextEntryItem( wxTreeItemId itemId )
{
    wxTreeItemId next = FindNextItem( itemId );
    while ( next.IsOk( ) )
    {
        if ( IsEntryNode( next ) )
        {
            std::cout << "next" << GetDesc( next ) << "\n";
            return next;
        }
        next = FindNextItem( next );
    }
    return next;

}
wxTreeItemId CompareTreeCtrl::FindPrevEntryItem( wxTreeItemId itemId )
{
    wxTreeItemId prev = FindPrevItem( itemId );
    wxTreeItemId lastOK = itemId;
    while ( prev.IsOk( ) )
    {
        lastOK = prev;
        if ( IsEntryNode( prev ) )
        {
            std::cout << "prev" << GetDesc( prev ) << "\n";
            return prev;
        }
        prev = FindPrevItem( prev );
    }
    return itemId;
}


wxTreeItemId CompareTreeCtrl::FindPrevItem( wxTreeItemId itemId )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId prev = GetPrevSibling( itemId );
    if ( prev.IsOk( ) )
    {
        std::cout << "prev" << GetDesc( prev ) << "\n";
        return prev;
    }

    wxTreeItemId parent = GetItemParent( itemId );
    if ( parent.IsOk( ) )
    {
        std::cout << "parent" << GetDesc( parent ) << "\n";
        return parent;
    }
    return parent;
}
wxString CompareTreeCtrl::GetDesc( wxTreeItemId item )
{
    CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( item );
    return data->GetDesc( );
}

wxTreeItemId CompareTreeCtrl::FindNextItem( wxTreeItemId itemId )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId next = GetFirstChild( itemId, cookie );
    if ( next.IsOk( ) )
    {
        std::cout << "next" << GetDesc( next ) << "\n";
        return next;
    }

    wxTreeItemId sibling = GetNextSibling( itemId );
    if ( sibling.IsOk( ) )
    {
        std::cout << "sibling" << GetDesc( sibling ) << "\n";
        return sibling;
    }

    wxTreeItemId parent = GetItemParent( itemId );
    if ( parent.IsOk( ) )
    {
        sibling = GetNextSibling( parent );
        //     std::cout << "sibling" << GetDesc( sibling ) << "\n";
        return sibling;
    }
    return parent;
}

void CompareTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxXmlNode* xmlNode = GetItemNode( itemId );

    CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( itemId );
    if ( data->GetType( ) == Catalog::NT_Entry )
    {
        Catalog::MergeData* mergeData = data->GetMergeData( );
        m_comparePanel->UpdateCompEntryTable( mergeData );
    }
    else
    {
        //first search all following nodes
        wxTreeItemId next = FindNextEntryItem( itemId );
        if ( next.IsOk( ) )
        {
            CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( next );
            Catalog::MergeData* mergeData = data->GetMergeData( );
            m_comparePanel->UpdateCompEntryTable( mergeData );
            SelectItem( next );
        }
        else
        {
            //go back to the beginning and try again
            itemId = GetRootItem( );
            wxTreeItemId next = FindNextEntryItem( itemId );
            if ( next.IsOk( ) )
            {
                CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( next );
                Catalog::MergeData* mergeData = data->GetMergeData( );
                m_comparePanel->UpdateCompEntryTable( mergeData );
                SelectItem( next );
            }
        }
    }
    event.Skip( );
}

//--------------

void CompareTreeCtrl::OnTreectrlItemCollapsed( wxTreeEvent& event )
{

    wxTreeItemId id = event.GetItem( );
    if ( !id.IsOk( ) )
    {
        while ( 1 )
        {
        }
    }
    wxString before = GetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ] );
    SetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ], "true" );
    wxString after = GetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ] );
    event.Skip( );
}

//--------------

void CompareTreeCtrl::OnTreectrlItemExpanded( wxTreeEvent& event )
{
    wxTreeItemId id = event.GetItem( );
    wxString   a = GetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ] );
    SetAttribute( id, Catalog::XMLDataNames[ Catalog::DT_CollapseState ], "false" );

    event.Skip( );

}

//--------------

//--------------
void CompareTreeCtrl::SelectStamp( wxString id )
{
    wxTreeItemId item = FindTreeItemID( id );
    if ( item.IsOk( ) )
    {
        this->SelectItem( item );
    }
}

//--------------

void  CompareTreeCtrl::SetAttribute( wxTreeItemId catTreeID, wxString name, wxString val )
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

void CompareTreeCtrl::SetItemNode( wxTreeItemId id, wxXmlNode* ele )
{
    if ( id.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
        if ( data )
        {
            data->SetCatNode( ele );
        }
    }
};

//--------------

//--------------

void CompareTreeCtrl::SetItemImageFullName( wxTreeItemId id, wxString str )
{
    if ( id.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
        if ( data )
        {
            data->SetImageFullName( str );
        }
    }
};

//--------------


//--------------

void CompareTreeCtrl::SetNextState( const wxTreeItemId& itemId )
{
    wxXmlNode* element = GetItemNode( itemId );
    Catalog::Entry entry( element );
    if ( entry.IsOK( ) )
    {
        SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
        int state = GetItemState( itemId );

        GetFrame( )->UpdateStatus( );
    }
}

//Find th node ad select it
void CompareTreeCtrl::SetSelection( wxXmlNode* node ){

    wxTreeItemId newID = FindTreeItemID( node );
    if ( newID.IsOk( ) )
    {
        SelectItem( newID );
    }
}
//--------------

//--------------

void CompareTreeCtrl::SetTreeItemCollapseState( wxTreeItemId childID )
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

//--------------

void CompareTreeCtrl::SetType( wxTreeItemId id, Catalog::CatalogBaseType type )
{
    if ( id.IsOk( ) )
    {
        CompareTreeItemData* data = ( CompareTreeItemData* ) GetItemData( id );
        if ( data )
        {
            return data->SetType( type );
        }
    }
};


//--------------

void CompareTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
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

        }
        else
        {
            menu.AppendSeparator( );
            menu.Append( CatalogListTree_Colnect, "GoTo Colnect" );
            menu.AppendSeparator( );
        }
    }

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {


        case CatalogListTree_Colnect:
        {
            GoToColnect( id );
        }
        break;

        default:
        // Fall through.
        break;
    }
}

//--------------
