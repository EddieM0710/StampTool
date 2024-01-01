/**
 * @file AlbumTreeCtrl.cpp
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
 *
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
#include <wx/filename.h>

#include "Defs.h"
#include "gui/GuiDefs.h"

#include "utils/Project.h"

 //#include "StampToolApp.h"
#include "design/AlbumVolume.h"
#include "design/DesignDefs.h"
#include "design/LayoutBase.h"
#include "design/Album.h"
#include "design/Page.h"
#include "design/Stamp.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/TextBox.h"
#include "gui/StampToolFrame.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumPanel.h"
#include "utils/XMLUtilities.h"
#include "utils/StampList.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/IconDefs.h"
#include "gui/AlbumImagePanel.h"
#include "catalog/CatalogDefs.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogCode.h"

IMPLEMENT_CLASS( AlbumTreeCtrl, wxTreeCtrl );

//wxDECLARE_APP( StampToolApp );

wxBEGIN_EVENT_TABLE( AlbumTreeCtrl, wxTreeCtrl )
EVT_TREE_BEGIN_DRAG( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnItemStateClick )
EVT_TREE_ITEM_MENU( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_RIGHT_CLICK( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnItemRClick )
EVT_TREE_ITEM_COLLAPSED( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnTreectrlItemCollapsed )
EVT_TREE_ITEM_EXPANDED( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnTreectrlItemExpanded )
wxEND_EVENT_TABLE( )

wxColour ItemBackgroundColour[ 3 ] = { wxNullColour, *wxYELLOW, *wxRED };

//--------------

void DesignTreeItemData::SetStampLink( Utils::StampLink* link ) {
    if ( !IsOk( ) )
    {
        int a = 0;
    }
    m_stampLink = link;
};

//----------------

AlbumTreeCtrl::AlbumTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )

{
    m_OK = 0x12345;
    m_reverseSort = true;

    CreateImageList( );
    CreateStateImageList( );
    ItemBackgroundColour[ Design::AT_OK ] = GetBackgroundColour( );
}

//--------------
void AlbumTreeCtrl::UpdateAlbumStampEntries( wxTreeItemId treeID )
{

    DesignTreeItemData* data = ( DesignTreeItemData* ) this->GetItemData( treeID );
    Design::AlbumBaseType nodeType = data->GetType( );
    if ( Design::IsAlbumBaseTypeValid( nodeType ) )
    {
        //std::cout << Design::AlbumBaseNames[ nodeType ] << "\n";
        //if the child element is not a stamp
        if ( nodeType == Design::AT_Stamp )
        {
            Utils::StampLink* link = data->GetStampLink( );
            if ( link )
            {
                wxTreeItemId catTreeID = link->GetCatTreeID( );
                if ( catTreeID.IsOk( ) )
                {
                    wxXmlNode* node = GetCatalogTreeCtrl( )->GetItemNode( catTreeID );
                    if ( node )
                    {
                        Catalog::Entry catStamp( node );
                        wxString catCodeStr = catStamp.GetCatalogCodes( );
                        Catalog::CatalogCode catCodeArray( catCodeStr );
                        Design::Stamp* albumStamp = ( Design::Stamp* ) data->GetNodeElement( );
                        wxString albumCatCodes = albumStamp->GetCatalogCodes( );
                        if ( albumCatCodes.IsEmpty( ) )
                        {
                            albumStamp->SetCatalogCodes( catCodeStr );
                        }
                        wxString preferredID = catCodeArray.GetPreferredCatalogCode( Design::GetAlbum( )->GetCatalog( ) );
                        albumStamp->SetNbrString( preferredID );
                        wxString label = preferredID;
                        wxString title = albumStamp->GetAttrStr( Design::AT_Name );
                        label += " - " + title;
                        SetItemText( treeID, label );
                    }
                }
            }
        }

        if ( this->HasChildren( treeID ) )
        {
            wxTreeItemIdValue cookie;
            wxTreeItemId childID = GetFirstChild( treeID, cookie );
            while ( childID.IsOk( ) )
            {
                UpdateAlbumStampEntries( childID );
                childID = GetNextChild( treeID, cookie );
            }
        }
    }
}

//--------------

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId AlbumTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child )
{
    wxString name = child->GetName( );
    Design::AlbumBaseType nodeType = Design::FindAlbumBaseType( name );

    if ( Design::IsAlbumBaseTypeValid( nodeType ) )
    {
        Design::AlbumBase* node = Design::MakeNode( child );
        if ( node )
        {
            node->LoadFonts( child );

            Design::IconID icon;
            wxString label;

            //if the child element is not a stamp
            if ( nodeType == Design::AT_Stamp )
            {
                // then we add the appropriate icon and label
                Design::Stamp* stamp = ( Design::Stamp* ) node;
                // stamp combines the stampID and its name to form a label

                label = stamp->GetCatalogNbr( );
                wxString title = stamp->GetAttrStr( Design::AT_Name );
                label += " - " + title;
                icon = GetIconId( stamp );
            }
            else
            {
                if ( nodeType == Design::AT_Album )
                {
                    GetAlbumVolume( )->SetAlbum( ( Design::Album* ) node );
                    ( ( Design::Album* ) node )->FixupNode( );
                }
                label = name;
                wxString title = node->GetAttrStr( Design::AT_Name );
                label += " - " + title;
                icon = Design::Icon_Folder;
            }


            // create the item data and add it to the tree
            DesignTreeItemData* itemData = new DesignTreeItemData( nodeType, "", node );
            wxTreeItemId childID;
            if ( parent.IsOk( ) )
            {
                childID = AppendItem( parent, label, icon, -1, itemData );
            }
            else
            {
                childID = AddRoot( label, icon, -1, itemData );
            }
            node->SetTreeItemId( childID );


            if ( nodeType == Design::AT_Stamp )
            {
                Utils::StampList* stampList = GetStampAlbumCatalogLink( );
                wxString nodeId = node->GetAttrStr( Design::AT_CatNbr );
                if ( !nodeId.IsEmpty( ) )
                {
                    Utils::StampLink* link = stampList->AddStamp( nodeId );
                    link->SetDesignTreeID( childID );
                    SetItemStampLink( childID, link );
                }
                //set the icon for the appropriate state
                SetItemImage( childID, icon );
                //       SetItemState( childID, 0 );
            }
            else
            {
                // not a stamp just add the appropriate image
                SetItemStampLink( childID, 0 );
                SetItemImage( childID, Design::Icon_Folder );
                //       SetItemState( childID, wxTREE_ITEMSTATE_NEXT );
            }

            // now do it all again for this stamps children
            wxXmlNode* grandChild = child->GetChildren( );
            while ( grandChild )
            {
                // start adding child elements to it.
                AddChild( childID, grandChild );
                grandChild = grandChild->GetNext( );
            }
            return childID;
        }
    }
    return ( wxTreeItemId ) 0;
}

//--------------

void AlbumTreeCtrl::AddColTreeItem( wxTreeItemId parentID )
{
    Design::AlbumVolume* albumVolume = GetAlbumVolume( );

    Design::Column* newCol = new Design::Column( ( wxXmlNode* ) 0 );;
    if ( newCol )
    {
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Col, "Column", newCol );
        wxTreeItemId childID = AppendItem( parentID, "Column", Design::Icon_Folder, -1, itemData );
        newCol->SetTreeItemId( childID );
        Design::NodeStatus status = UpdateTreeItem( childID, newCol, Design::Icon_Folder );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}

//--------------

void AlbumTreeCtrl::AddPageTreeItem( wxTreeItemId parentID )
{
    Design::AlbumVolume* albumVolume = GetAlbumVolume( );

    Design::Page* newPage = new Design::Page( ( wxXmlNode* ) 0 );;
    if ( newPage )
    {
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Page, "Page", newPage );
        wxTreeItemId childID = AppendItem( parentID, "Page", Design::Icon_Folder, -1, itemData );
        UpdateTreeItem( childID, newPage, Design::Icon_Folder );
    }
}

//--------------

void AlbumTreeCtrl::AddRowTreeItem( wxTreeItemId parentID )
{
    Design::AlbumVolume* albumVolume = GetAlbumVolume( );

    Design::Row* newRow = new Design::Row( ( wxXmlNode* ) 0 );
    if ( newRow )
    {
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Row, "Row", newRow );
        wxTreeItemId childID = AppendItem( parentID, "Row", Design::Icon_Folder, -1, itemData );
        newRow->SetTreeItemId( childID );
        Design::NodeStatus status = UpdateTreeItem( childID, newRow, Design::Icon_Folder );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}

//--------------

Design::Stamp* AlbumTreeCtrl::AddStampTreeItem( wxTreeItemId parentID, Design::Stamp* newStamp )
{
    wxXmlNode* parentNode = ( wxXmlNode* ) GetItemNode( parentID );

    if ( newStamp )
    {

        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Stamp, "Stamp", newStamp );
        wxTreeItemId childID = AppendItem( parentID, "Stamp", Design::Icon_Folder, -1, itemData );
        newStamp->SetTreeItemId( childID );
        Design::IconID icon = GetIconId( newStamp );
        Design::NodeStatus status = UpdateTreeItem( childID, newStamp, icon );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
    return newStamp;
}

//--------------

Design::TextBox* AlbumTreeCtrl::AddTextTreeItem( wxTreeItemId parentID, Design::TextBox* newText )
{
    wxXmlNode* parentNode = ( wxXmlNode* ) GetItemNode( parentID );

    if ( newText )
    {
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Text, "TextBox", newText );
        wxTreeItemId childID = AppendItem( parentID, "TextBox", Design::Icon_Folder, -1, itemData );
        newText->SetTreeItemId( childID );
        Design::NodeStatus status = UpdateTreeItem( childID, newText, Design::Icon_Menu );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
    return newText;
}

//----------------

Utils::StampLink* AlbumTreeCtrl::AppendStamp( wxTreeItemId catTreeID )
{

    Utils::StampLink* newLink = ( Utils::StampLink* ) 0;
    wxTreeItemId currAlbumID = GetSelection( );
    if ( currAlbumID.IsOk( ) && catTreeID.IsOk( ) )
    {

        // A stamp can't have children. so get its parent
        Design::AlbumBaseType type = GetItemType( currAlbumID );
        if ( type == Design::AT_Stamp ) //@@@ || type == Design::AT_Title )
        {
            currAlbumID = GetItemParent( currAlbumID );
        }

        Design::Stamp* newStamp = CreateNewStamp( catTreeID );

        if ( newStamp )
        {
            // gather info from the catalog item entry and update thenew stamp
            wxString catStr = GetCatalogData( )->GetCatalogVolume( )->GetFilename( );
            wxFileName catFileName( catStr );


            CatalogTreeCtrl* catTree = GetCatalogTreeCtrl( );
            wxString idText = catTree->GetID( catTreeID );
            wxString str = newStamp->MakeDisplayNbr( );

            newStamp->GetNbrFrame( )->SetString( str );
            newStamp->GetNameFrame( )->SetString( newStamp->GetAttrStr( Design::AT_Name ) );


            AddStampTreeItem( currAlbumID, newStamp );
            wxTreeItemId newStampID = newStamp->GetTreeItemId( );

            SetItemText( newStampID, idText );
            newStamp->SetAttrStr( Design::AT_CatNbr, idText );

            // stamp item text combines the stampID and its name to form a label
            wxString label = newStamp->GetAttrStr( Design::AT_CatNbr );
            label += " - " + newStamp->GetAttrStr( Design::AT_Name );
            SetItemText( newStampID, label );

            //Add the StampList link 
            Utils::StampList* stampList = GetStampAlbumCatalogLink( );
            newLink = stampList->AddStamp( idText );
            wxTreeItemId albumID = newStamp->GetTreeItemId( );
            SetItemStampLink( albumID, newLink );
            newLink->SetDesignTreeID( albumID );
            newLink->SetCatTreeID( catTreeID );

            UpdateItemPageLayout( albumID );

            Design::NodeStatus status = newStamp->ValidateNode( );
            SetItemBackgroundColour( albumID, ItemBackgroundColour[ status ] );
        }
    }
    return newLink;
}

//--------------

void AlbumTreeCtrl::Clear( )
{
    // first make sure all the links to the items are gone
    Utils::StampList* stampList = GetStampAlbumCatalogLink( );
    stampList->Clear( );

    // then clobber all the tree items
    DeleteAllItems( );
}

//--------------

void AlbumTreeCtrl::CreateImageList( )
{
    wxImageList* images = CreateAlbumImageList( );
    AssignImageList( images );
}

//--------------

void AlbumTreeCtrl::CopyItem( wxTreeItemId dstID, wxTreeItemId srcID )
{
    if ( !dstID.IsOk( ) || !srcID.IsOk( ) )
    {
        return;
    }
    DesignTreeItemData* data = ( DesignTreeItemData* ) GetItemData( srcID );
    DesignTreeItemData* itemData = new DesignTreeItemData( *data );
    Design::AlbumBaseType srcType = AlbumTreeCtrl::GetItemType( srcID );
    Design::AlbumBaseType destType = AlbumTreeCtrl::GetItemType( dstID );
    wxTreeItemId id;
    if ( srcType == destType )
    {
        wxTreeItemId parent = GetItemParent( dstID );
        id = InsertItem( parent, dstID,
            GetItemText( srcID ),
            GetItemImage( srcID ),
            -1,
            itemData );
    }
    else
    {
        id = AppendItem( dstID,
            GetItemText( srcID ),
            GetItemImage( srcID ),
            -1,
            itemData );
    }
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( srcID, cookie );
    Design::AlbumBase* node = GetItemNode( id );
    if ( node )
    {
        node->SetTreeItemId( id );
    }
    Utils::StampLink* link = GetItemStampLink( id );
    if ( link )
    {
        link->SetDesignTreeID( id );
    }
    while ( child )
    {
        CopyItem( id, child );
        child = GetNextChild( srcID, cookie );
    }
}

//--------------

Design::Stamp* AlbumTreeCtrl::CreateNewStamp( wxTreeItemId catTreeID )
{
    Design::Stamp* newStamp = new Design::Stamp( );

    if ( catTreeID.IsOk( ) )
    {
        // load stamp from catalog
        CatalogTreeCtrl* catTree = GetCatalogTreeCtrl( );
        wxXmlNode* node = catTree->GetItemNode( catTreeID );
        Catalog::Entry stamp( node );
        //create a stamp with the catalog data

        newStamp->SetAttrStr( Design::AT_CatNbr, stamp.GetID( ) );
        newStamp->SetAttrStr( Design::AT_Name, stamp.GetName( ) );
        newStamp->SetActualStampHeight( stamp.GetHeight( ) );
        newStamp->SetActualStampWidth( stamp.GetWidth( ) );
        newStamp->SetStampImageFilename( stamp.FindImageName( ) );
        newStamp->SetShowTitle( newStamp->GetShowTitle( ) );
        newStamp->SetShowNbr( newStamp->GetShowNbr( ) );

    }
    else
    {
        // create a default Stamp

        //create a new xml node with the catalog data
        CatalogTreeCtrl* catTree = GetCatalogTreeCtrl( );
        wxString label = "New ID";
        newStamp->SetAttrStr( Design::AT_CatNbr, label );
        wxString title = "New Title";
        newStamp->SetAttrStr( Design::AT_Name, title );
        wxString height = "10.0";
        newStamp->SetActualStampHeight( height );
        wxString width = "10.0";
        newStamp->SetActualStampWidth( width );
    }
    return newStamp;
}

//--------------

void AlbumTreeCtrl::CreateStateImageList( )
{
    AssignStateImageList( CreateAlbumStateImageList( ) );
}

//--------------

Design::TextBox* AlbumTreeCtrl::CreateNewText( )
{
    Design::TextBox* newText = new Design::TextBox( );
    newText->SetAttrStr( Design::AT_Name, "TextBox Title" );
    return newText;
}

//--------------

void AlbumTreeCtrl::DeleteItem( wxTreeItemId currID )
{
    wxTreeItemId parentID = this->GetItemParent( currID );
    wxTreeItemIdValue cookie;
    wxTreeItemId childID = GetFirstChild( currID, cookie );
    while ( childID.IsOk( ) )
    {
        DeleteItem( childID );
        childID = GetNextChild( currID, cookie );
    }
    Design::AlbumBase* child = GetItemNode( currID );

    DeleteChildren( currID );

    Utils::StampLink* link = GetItemStampLink( currID );
    if ( link )
    {
        wxTreeItemId catTreeID = link->GetCatTreeID( );
        if ( catTreeID.IsOk( ) )
        {
            GetCatalogTreeCtrl( )->SetItemState( catTreeID, Catalog::ST_Unchecked );
        }
        Utils::StampList* stampList = GetStampAlbumCatalogLink( );
        stampList->DeleteLink( link );

    }
    Delete( currID );
    delete child;
    UpdateItemPageLayout( parentID );
}

//--------------

wxTreeItemId AlbumTreeCtrl::FindFirstStampChild( wxTreeItemId id )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( id, cookie );
    while ( child )
    {
        if ( GetItemType( child ) == Design::AT_Stamp )
        {
            return child;
        }
        if ( HasChildren( child ) )
        {
            wxTreeItemId id = FindFirstStampChild( child );
            if ( id )
            {
                return id;
            }
        }
        child = GetNextChild( id, cookie );
    }
    return 0;
}

//--------------

wxTreeItemId AlbumTreeCtrl::FindTreeItemID( Design::AlbumBase* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//--------------

wxTreeItemId AlbumTreeCtrl::FindTreeItemID( Design::AlbumBase* ele, wxTreeItemId id )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( id, cookie );
    while ( child )
    {
        if ( IsElement( child, ele ) )
        {
            return child;
        }
        if ( HasChildren( child ) )
        {
            wxTreeItemId id = FindTreeItemID( ele, child );
            if ( id )
            {
                return id;
            }
        }
        child = GetNextChild( id, cookie );
    }
    return 0;
}

//--------------

Design::LayoutBase* AlbumTreeCtrl::GetSelectedNode( )
{
    wxTreeItemId id = GetSelection( );
    if ( id.IsOk( ) )
    {
        return ( Design::LayoutBase* ) GetItemNode( id );
    }
    return ( Design::LayoutBase* ) 0;
}

//--------------

wxTreeItemId AlbumTreeCtrl::GetPage( wxTreeItemId id )
{
    while ( id.IsOk( ) )
    {
        Design::AlbumBaseType type = GetItemType( id );
        if ( type == Design::AT_Album )
        {
            wxTreeItemIdValue cookie;
            wxTreeItemId childID = GetFirstChild( id, cookie );
            if ( childID.IsOk( ) )
            {
                Design::AlbumBaseType childType = GetItemType( childID );
                return childID;
            }
        }
        else if ( type == Design::AT_Page )
        {
            return id;
        }
        id = GetItemParent( id );
    }
    return ( wxTreeItemId ) 0;
}

//--------------

Design::IconID AlbumTreeCtrl::GetIconId( Design::Stamp* stamp )
{
    int format = stamp->GetNodeType( );
    return Design::AlbumImageSelection[ format ][ 0 ];
}

//--------------

bool AlbumTreeCtrl::GetValidateStatus( )
{
    return ValidateStatus;
}

//--------------

Design::AlbumBase* AlbumTreeCtrl::GetItemNode( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetItemData( albumID );
        if ( data )
        {
            return data->GetNodeElement( );
        }
    }
    return ( Design::AlbumBase* ) 0;
};

//--------------

wxString AlbumTreeCtrl::GetItemDesc( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetItemData( albumID );
        if ( data )
        {
            return data->GetDesc( );
        }
    }
    return "";
};

//--------------

Design::AlbumBaseType AlbumTreeCtrl::GetItemType( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {

        DesignTreeItemData* data = ( DesignTreeItemData* ) GetItemData( albumID );
        if ( !data->IsOk( ) )
        {
            int a = 1;
        }
        return data->GetType( );
    }
    return ( Design::AlbumBaseType ) Design::AT_NOTYPE;
};

//--------------

Utils::StampLink* AlbumTreeCtrl::GetItemStampLink( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {
        return ( ( DesignTreeItemData* ) GetItemData( albumID ) )->GetStampLink( );
    }
    return ( Utils::StampLink* ) 0;
};

//--------------

bool AlbumTreeCtrl::IsElement( wxTreeItemId item, Design::AlbumBase* ele )
{
    Design::AlbumBase* dataEle = GetItemNode( item );
    if ( dataEle == ele )
    {
        return false;
    }
    return true;
}

//--------------

void AlbumTreeCtrl::LoadTree( )
{
    Clear( );
    Design::AlbumVolume* volume = GetAlbumVolume( );
    if ( volume )
    {
        wxXmlDocument* doc = volume->GetDoc( );
        if ( doc && doc->IsOk( ) )
        {
            wxXmlNode* docRoot = doc->GetRoot( );
            if ( docRoot )
            {
                AddChild( 0, docRoot );
                GetAlbumVolume( )->UpdateAlbum( );
                wxTreeItemId id = FindFirstStampChild( GetRootItem( ) );
                if ( id.IsOk( ) ) SelectItem( id );
                GetAlbumImagePanel( )->Refresh( );

                // ExpandAll( );
            }
        }
    }
}

//--------------

void AlbumTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}

//--------------

void AlbumTreeCtrl::MakePage( wxTreeItemId id )
{

    Design::AlbumBase* node = GetItemNode( id );
    GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) node );

}

//--------------

void AlbumTreeCtrl::MoveItem( wxTreeItemId srcID, wxTreeItemId dstID )
{
    wxTreeItemId srcParentID = GetItemParent( srcID );
    wxTreeItemId dstParentID = GetItemParent( dstID );

    if ( srcParentID == srcID )
    {
        // can't be a child of itself
        return;
    }

    wxTreeItemId parent = srcParentID;
    while ( parent )
    {
        if ( srcID == parent )
        {
            // child can't be an ancestor of itself
            return;
        }
        parent = GetItemParent( parent );
    }

    CopyItem( dstID, srcID );
    SelectItem( dstID );
    UpdateItemPageLayout( srcParentID );
    if ( srcParentID != dstParentID )
    {
        UpdateItemPageLayout( dstParentID );
    }
    Delete( srcID );
}

//--------------

wxString AlbumTreeCtrl::MakeItemLabel( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        Design::AlbumBase* node = GetItemNode( id );
        if ( node )
        {
            if ( GetItemType( id ) == Design::AT_Stamp )
            {
                return node->GetAttrStr( Design::AT_CatNbr ) + " - " + node->GetAttrStr( Design::AT_Name );
            }
            else
            {
                return node->GetObjectName( );
            }
        }
    }
    return "";
}

//--------------

void AlbumTreeCtrl::OnDeleteItem( wxTreeItemId currID )
{
    wxMessageDialog* dialog = new wxMessageDialog( this,
        "Are you sure you want to delete this item? This and all child Items will be deleted. There is no UnDo.", " Delete Item.",
        wxYES_NO | wxCENTRE );
    int ret = dialog->ShowModal( );
    if ( ret == wxID_YES )
    {
        DeleteItem( currID );
    }
}

//--------------

void AlbumTreeCtrl::OnBeginDrag( wxTreeEvent& event )
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

void AlbumTreeCtrl::OnEndDrag( wxTreeEvent& event )
{
    wxTreeItemId srcID = m_draggedItem;
    wxTreeItemId dstID = event.GetItem( );
    m_draggedItem = ( wxTreeItemId ) 0l;

    if ( srcID == dstID )
    {
        return;
    }

    if ( !dstID.IsOk( ) || !srcID.IsOk( ) )
    {
        return;
    }
    // ShowDropMenu( srcID, dstID );

    wxTreeItemId parentID = GetItemParent( srcID );

    if ( parentID == srcID )
    {
        // can't be a child of itself
        return;
    }

    wxTreeItemId parent = parentID;
    while ( parent )
    {
        if ( srcID == parent )
        {
            // child can't be an ancestor of itself
            return;
        }
        parent = GetItemParent( parent );
    }


    Design::AlbumBaseType srcType = AlbumTreeCtrl::GetItemType( srcID );
    Design::AlbumBaseType destType = AlbumTreeCtrl::GetItemType( dstID );

    switch ( destType )
    {
        case  Design::AT_Album:
        if ( srcType == Design::AT_Page )
        {
            MoveItem( srcID, dstID );
        }
        break;
        case  Design::AT_Page:
        if ( srcType == Design::AT_Row
            || srcType == Design::AT_Col )
        {
            MoveItem( srcID, dstID );
        }
        else if ( srcType == Design::AT_Page )
        {
            ShowDropMenu( srcID, dstID, false );
        }
        break;
        case  Design::AT_Row:
        if ( srcType == Design::AT_Stamp
            || srcType == Design::AT_Col )
        {
            MoveItem( srcID, dstID );
        }
        else if ( srcType == Design::AT_Row )
        {
            ShowDropMenu( srcID, dstID, false );
        }
        break;
        case  Design::AT_Col:
        if ( srcType == Design::AT_Stamp
            || srcType == Design::AT_Row )
        {
            MoveItem( srcID, dstID );
        }
        else if ( srcType == Design::AT_Col )
        {
            ShowDropMenu( srcID, dstID, false );
        }
        break;
        case  Design::AT_Stamp:
        if ( srcType == Design::AT_Col
            || srcType == Design::AT_Row )
        {
            MoveItem( srcID, dstID );
        }
        else if ( srcType == Design::AT_Stamp )
        {
            ShowDropMenu( srcID, dstID, false );
        }
        break;
    }
}

//--------------

void AlbumTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );

    //    SetNextState( itemId );
}

//--------------

void AlbumTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxString desc = GetItemDesc( itemId );

    Design::AlbumBase* albumBase = ( Design::AlbumBase* ) GetItemNode( itemId );
    GetFrame( )->GetAlbumPanel( )->ShowDetails( albumBase );
    bool status1 = itemId.IsOk( );
    wxTreeItemId pageId = GetPage( itemId );
    bool status2 = pageId.IsOk( );
    if ( pageId.IsOk( ) )
    {
        m_currPageID = pageId;
        bool status3 = m_currPageID.IsOk( );
        MakePage( pageId );
        GetAlbumImagePanel( )->Refresh( );
    }
    else
    {
        std::cout << "AlbumTreeCtrl::OnSelChanged invalid pageId" << std::endl;
    }

    event.Skip( );
}

//--------------

void AlbumTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );
    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

//--------------

int AlbumTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    Design::AlbumBaseType type1 = GetItemType( item1 );
    Design::AlbumBaseType type2 = GetItemType( item2 );

    if ( type1 != type2 )
    {
        return ( int ) type1 - ( int ) type2;
    }
    else
    {
        wxString id1 = GetItemDesc( item1 );
        wxString id2 = GetItemDesc( item2 );

        int val = id1.Cmp( id2 );
        if ( m_reverseSort )
        {
            return val * -1;
        }
        else
        {
            return val;
        }
    }
}

//--------------

void AlbumTreeCtrl::ResetValidateStatus( )
{
    ValidateStatus = true;
}

//--------------

void AlbumTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );
    event.Skip( );
}

//--------------

// iterate thru the tree and save all data to XML doc
void AlbumTreeCtrl::SaveNodeData( wxXmlNode* parent, wxTreeItemId treeItemId )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId childID = GetFirstChild( treeItemId, cookie );
    while ( childID.IsOk( ) )
    {
        Design::LayoutBase* child = ( Design::LayoutBase* ) GetItemNode( childID );
        wxXmlNode* xmlNode = Utils::NewNode( ( wxXmlNode* ) 0, Design::AlbumBaseNames[ child->GetNodeType( ) ] );
        // NewNode inserts a new node as the first child. Passing a null parent then using 
        // AddChild preserves the child node order.
        parent->AddChild( xmlNode );
        child->Save( xmlNode );
        SaveNodeData( xmlNode, childID );
        childID = GetNextChild( treeItemId, cookie );
    }
}

//--------------

void AlbumTreeCtrl::ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst, bool asChild )
{
    wxString title;


    title << "Insert Item " << GetItemText( itemSrc );

    wxMenu menu( title );
    wxString label = "    BEFORE " + GetItemText( itemDst );
    menu.Append( DesignTree_Before, label );
    label = "    AFTER " + GetItemText( itemDst );
    menu.Append( DesignTree_After, label );
    if ( asChild )
    {
        label = "    as CHILD of " + GetItemText( itemDst );
        menu.Append( DesignTree_AsChild, label );
    }
    menu.Append( DesignTree_Cancel, "    CANCEL Drag" );


    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
        case DesignTree_Before:
        {

            wxTreeItemIdValue cookie;
            wxTreeItemId parent = GetItemParent( itemDst );
            wxTreeItemId  currID;

            wxTreeItemId prevSibling = GetPrevSibling( itemDst );
            if ( prevSibling.IsOk( ) )
            {
                MoveItem( itemSrc, prevSibling );

            }
            else
            {
                MoveItem( itemSrc, itemDst );
            }
            break;
        }
        case DesignTree_After:
        {
            MoveItem( itemSrc, itemDst );
            break;
        }
        case DesignTree_AsChild:
        {
            MoveItem( itemSrc, itemDst );
            break;
        }
        case DesignTree_Cancel:
        {

            break;
        }
    }
}

//--------------

void AlbumTreeCtrl::SetItemStampLink( wxTreeItemId albumID, Utils::StampLink* link )
{
    if ( albumID.IsOk( ) )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* ) GetItemData( albumID );
        if ( data->IsOk( ) )
        {
            data->SetStampLink( link );
        }
    }
};

//--------------

void AlbumTreeCtrl::SetValidateStatus( bool status )
{
    if ( ValidateStatus == true )
    {
        ValidateStatus = status;
    }
}

//--------------

void AlbumTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
{
    if ( id.IsOk( ) )
    {
        wxString title = "Design Tree Menu";

        Design::AlbumVolume* albumVolume = GetAlbumVolume( );
        Design::AlbumBase* node = GetItemNode( id );
        Design::AlbumBaseType type = node->GetNodeType( );
        wxMenu menu( title );
        wxMenu* addSubMenu = new wxMenu( );
        menu.Append( DesignTree_DeleteItem, "    Delete Item" );
        menu.Append( DesignTree_EditDetails, "    Edit Details" );
        wxMenuItem* addPageItem;// = addSubMenu->Append( DesignTree_AddPage, "Add Page" );
        wxMenuItem* addRowItem;// = addSubMenu->Append( DesignTree_AddRow, "Add Row" );
        wxMenuItem* addColItem;// = addSubMenu->Append( DesignTree_AddCol, "Add Column" );
        wxMenuItem* addStampItem;// = addSubMenu->Append( DesignTree_AddStamp, "Add Stamp" );
        wxMenuItem* addTextItem;// = addSubMenu->Append( DesignTree_AddText, "Add TextBox" );

        switch ( type )
        {
            case Design::AT_Album:
            {
                menu.AppendSubMenu( addSubMenu, "    Add Item" );
                addPageItem = addSubMenu->Append( DesignTree_AddPage, "Add Page" );;
                addPageItem->Enable( true );
                break;
            }
            case Design::AT_Page:
            {
                menu.AppendSubMenu( addSubMenu, "    Add Item" );
                addRowItem = addSubMenu->Append( DesignTree_AddRow, "Add Row" );
                addColItem = addSubMenu->Append( DesignTree_AddCol, "Add Column" );
                addRowItem->Enable( true );
                addColItem->Enable( true );

                break;
            }
            case Design::AT_Row:
            {
                menu.AppendSubMenu( addSubMenu, "    Add Item" );
                addColItem = addSubMenu->Append( DesignTree_AddCol, "Add Column" );
                addStampItem = addSubMenu->Append( DesignTree_AddStamp, "Add Stamp" );
                addTextItem = addSubMenu->Append( DesignTree_AddText, "Add TextBox" );
                addColItem->Enable( true );
                addStampItem->Enable( true );
                addTextItem->Enable( true );
                break;
            }
            case Design::AT_Col:
            {
                menu.AppendSubMenu( addSubMenu, "    Add Item" );
                addRowItem = addSubMenu->Append( DesignTree_AddRow, "Add Row" );
                addStampItem = addSubMenu->Append( DesignTree_AddStamp, "Add Stamp" );
                addTextItem = addSubMenu->Append( DesignTree_AddText, "Add TextBox" );
                addRowItem->Enable( true );
                addStampItem->Enable( true );
                addTextItem->Enable( true );
                break;
            }
            case Design::AT_Stamp:
            {
                break;
            }
            case Design::AT_Text:
            {
                break;
            }        default:
            {
                break;
            }
        }


        switch ( GetPopupMenuSelectionFromUser( menu ) )
        {
            case DesignTree_AddPage:
            {
                AddPageTreeItem( id );

                break;
            }
            case DesignTree_AddCol:
            {
                AddColTreeItem( id );

                break;
            }
            case DesignTree_AddRow:
            {
                AddRowTreeItem( id );
                break;
            }
            case DesignTree_AddStamp:
            {
                Design::Stamp* newStamp = CreateNewStamp( 0 );
                AddStampTreeItem( id, newStamp );
                break;
            }
            case DesignTree_AddText:
            {
                Design::TextBox* newText = CreateNewText( );
                AddTextTreeItem( id, newText );
                break;
            }
            case DesignTree_DeleteItem:
            {
                DeleteItem( id );
                break;
            }
            // case DesignTree_EditDetails:
            // {
            //     if ( type == Design::AT_Stamp )
            //     {
            //         ShowStampDetails( id );
            //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) node );
            //     }
            //     else if ( type == Design::AT_Row )
            //     {
            //         ShowRowDetails( id, node );
            //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) node );
            //     }
            //     else if ( type == Design::AT_Col )
            //     {
            //         ShowColDetails( id, node );
            //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) node );
            //     }
            //     else if ( type == Design::AT_Page )
            //     {
            //         ShowPageDetails( id, node );
            //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) node );
            //     }
            //     else if ( type == Design::AT_Album )
            //     {
            //         ShowAlbumDetails( id, node );
            //         GetAlbumVolume( )->MakePage( ( Design::LayoutBase* ) node );
            //     }


            //     break;

            //}
            default:
            // Fall through.
            break;
        }
    }
}

//--------------

// void AlbumTreeCtrl::ShowAlbumDetails( wxTreeItemId treeID, Design::AlbumBase* node )
//     {
//     Design::Album* album = ( Design::Album* ) node;

//     AlbumDetailsDialog albumDetailsDialog( this, 12345, _( "View Edit Album Details" ) );

//     albumDetailsDialog.SetupDialog( treeID );

//     if ( albumDetailsDialog.ShowModal( ) == wxID_OK )
//         {

//         wxString newName = album->GetAttrStr( Design::AT_Name );
//         SetItemText( treeID, newName );

//         DesignTreeItemData* data = ( DesignTreeItemData* ) GetItemData( treeID );
//         data->SetDesc( newName );


//         album->MakeAlbum( );
//         Design::NodeStatus status = album->ValidateNode( );
//         SetItemBackgroundColour( node->GetTreeItemId( ), ItemBackgroundColour[ status ] );
//         GetAlbumImagePanel( )->Refresh( );
//         }
//     return;

//     //    MakePage( m_currPageID );

//     }

// //--------------

// void AlbumTreeCtrl::ShowStampDetails( wxTreeItemId treeID )
//     {
//     m_currentTreeID = treeID;
//     StampDetailsDialog stampDetailsDialog( this, 12345,
//         _( "View Edit Stamp Details" ) );

//     stampDetailsDialog.SetupDialog( treeID );
//     //    stamp->ReportLayout( );

//     if ( stampDetailsDialog.ShowModal( ) == wxID_OK )
//         {
//         DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( treeID );
//         Design::Stamp* stamp = ( Design::Stamp* ) data->GetNodeElement( );

//         if ( stampDetailsDialog.IsNameModified( ) )
//             {
//             wxString newName = stamp->GetAttrStr( Design::AT_Name );
//             SetItemText( treeID, newName );
//             data->SetDesc( newName );
//             }

//         Design::NodeStatus status = stamp->ValidateNode( );
//         SetItemBackgroundColour( treeID, ItemBackgroundColour[ status ] );
//         GetAlbumImagePanel( )->Refresh( );
//         }
//     return;

//     }

//----------------

void AlbumTreeCtrl::Update( )
{

    //update layout
    UpdateItemPageLayout( m_currPageID );

    //force a repaint of the current page
    GetAlbumImagePanel( )->Refresh( );

    // Design::NodeStatus status = stamp->ValidateNode( );

     //SetItemBackgroundColour( treeID, ItemBackgroundColour[ status ] );
}

// //--------------

// void AlbumTreeCtrl::ShowPageDetails( wxTreeItemId treeID, Design::AlbumBase* node )
//     {

//     PageDetailsDialog pageDetailsDialog( this, 12345,
//         _( "View/Edit Page Details" ) );

//     pageDetailsDialog.SetupDialog( treeID );

//     //page->ReportLayout( );
//     if ( pageDetailsDialog.ShowModal( ) == wxID_OK )
//         {
//         DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( treeID );
//         Design::Page* page = ( Design::Page* ) data->GetNodeElement( );
//         if ( pageDetailsDialog.IsNameModified( ) )
//             {
//             wxString desc = "Page - " + page->GetAttrStr( Design::AT_Name );
//             SetItemText( treeID, desc );
//             data->SetDesc( desc );
//             }

//         page->UpdateLayout( );

//         Design::NodeStatus status = page->ValidateNode( );
//         SetItemBackgroundColour( page->GetTreeItemId( ), ItemBackgroundColour[ status ] );
//         GetAlbumImagePanel( )->Refresh( );
//         }
//     return;
//     }

// //--------------

// void AlbumTreeCtrl::ShowRowDetails( wxTreeItemId treeID, Design::AlbumBase* node )
//     {

//     RowDetailsDialog rowDetailsDialog( this, 12345,
//         _( "View/Edit Row Details" ) );

//     rowDetailsDialog.SetupDialog( treeID );

//     if ( rowDetailsDialog.ShowModal( ) == wxID_OK )
//         {
//         DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( treeID );
//         Design::Row* row = ( Design::Row* ) data->GetNodeElement( );
//         if ( rowDetailsDialog.IsNameModified( ) )
//             {
//             wxString newName = row->GetAttrStr( Design::AT_Name );
//             SetItemText( treeID, newName );
//             data->SetDesc( newName );
//             }

//         GetAlbumVolume( )->UpdatePage( row );
//         //row->UpdateLayout();

//         Design::NodeStatus status = row->ValidateNode( );
//         SetItemBackgroundColour( row->GetTreeItemId( ), ItemBackgroundColour[ status ] );
//         GetAlbumImagePanel( )->Refresh( );
//         }
//     return; // the user changed idea..

//     }

// //--------------

// void AlbumTreeCtrl::ShowColDetails( wxTreeItemId treeID, Design::AlbumBase* node )
//     {

//     ColDetailsDialog colDetailsDialog( this, 12345,
//         _( "View/Edit Col Details" ) );

//     colDetailsDialog.SetupDialog( treeID );

//     if ( colDetailsDialog.ShowModal( ) == wxID_OK )
//         {

//         DesignTreeItemData* data = ( DesignTreeItemData* ) GetAlbumTreeCtrl( )->GetItemData( treeID );
//         Design::Column* col = ( Design::Column* ) data->GetNodeElement( );

//         if ( colDetailsDialog.IsNameModified( ) )
//             {
//             wxString newName = col->GetAttrStr( Design::AT_Name );
//             SetItemText( treeID, newName );
//             data->SetDesc( newName );
//             node->SetAttrStr( Design::AT_Name, colDetailsDialog.GetName( ) );
//             }
//         GetAlbumImagePanel( )->Refresh( );
//         }
//     Design::NodeStatus status = node->ValidateNode( );
//     SetItemBackgroundColour( node->GetTreeItemId( ), ItemBackgroundColour[ status ] );

//     }

//--------------

void AlbumTreeCtrl::UpdateItemPageLayout( wxTreeItemId id )
{
    wxTreeItemId  pageID = GetPage( id );
    Design::Page* page = ( Design::Page* ) GetItemNode( pageID );
    page->UpdateLayout( );
}

//--------------

void AlbumTreeCtrl::UpdateStampList( )
{
    wxTreeItemId treeItemId = GetRootItem( );
    if ( treeItemId.IsOk( ) )
    {
        UpdateStampList( treeItemId );
    }
}

//--------------

void AlbumTreeCtrl::UpdateStampList( wxTreeItemId& treeItemId )
{
    CatalogTreeCtrl* catTree = GetCatalogTreeCtrl( );

    wxTreeItemIdValue cookie;
    wxTreeItemId childID = GetFirstChild( treeItemId, cookie );
    while ( childID.IsOk( ) )
    {

        Design::AlbumBaseType type = GetItemType( childID );
        if ( type == Design::AT_Stamp )
        {
            Design::AlbumBase* node = GetItemNode( childID );
            if ( node )
            {
                wxString albIDNbr = node->GetAttrStr( Design::AT_CatNbr );
                ValidateLink( childID, albIDNbr );
            }
        }

        UpdateStampList( childID );
        childID = GetNextChild( treeItemId, cookie );
    }

}

//--------------

Design::NodeStatus  AlbumTreeCtrl::UpdateTreeItem( wxTreeItemId childID, Design::AlbumBase* ele, Design::IconID icon )
{
    ele->SetTreeItemId( childID );
    SetItemImage( childID, icon );
    Expand( childID );
    SelectItem( childID );
    wxTreeItemId  pageID = GetPage( childID );
    Design::Page* page = ( Design::Page* ) GetItemNode( pageID );
    page->Init( );
    page->SetBorderFilename( Design::AlbumPageDefaults( )->BorderFilename( ) );
    page->UpdateMinimumSize( );
    page->UpdateSizes( );
    page->UpdatePositions( );
    Design::NodeStatus status = ele->ValidateNode( );
    // std::cout << "AlbumTreeCtrl::UpdateTreeItem Set backGround color " << ItemBackgroundColour[ status ] << "  status " << status << "\n";
    SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );
    return status;
}

//--------------

void AlbumTreeCtrl::Validate( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        Design::AlbumBase* node = GetItemNode( id );
        Design::NodeStatus status = node->ValidateNode( );
        SetItemBackgroundColour( id, ItemBackgroundColour[ status ] );
        SetValidateStatus( status );
    }
    wxTreeItemIdValue cookie;
    id = GetFirstChild( id, cookie );
    while ( id.IsOk( ) )
    {
        Validate( id );
        id = GetNext( id );
    }
}

//--------------

void AlbumTreeCtrl::ValidateLink( wxTreeItemId& childID, wxString albIDNbr )
{
    CatalogTreeCtrl* catTree = GetCatalogTreeCtrl( );

    Utils::StampLink* link = GetItemStampLink( childID );
    // if link exists validate it
    if ( link )
    {
        if ( childID != link->GetDesignTreeID( ) )
        {
            //link is pointing to wrong tree item; fix it.
            link->SetDesignTreeID( childID );
        }
        wxTreeItemId catTreeID = link->GetCatTreeID( );
        if ( catTreeID.IsOk( ) )
        {
            catTree->SetCatalogLink( catTreeID, link, albIDNbr );
        }
        else
        {
            catTreeID = catTree->FindTreeItemID( albIDNbr );
            if ( catTreeID.IsOk( ) )
            {
                catTree->SetCatalogLink( catTreeID, link, albIDNbr );
            }
        }
    }
    else // if not create a new one
    {
        Utils::StampList* stampList = GetStampAlbumCatalogLink( );
        if ( stampList )
        {
            Utils::StampLink* link = stampList->AddStamp( albIDNbr );
            link->SetDesignTreeID( childID );
            SetItemStampLink( childID, link );
            wxTreeItemId catTreeID = catTree->FindTreeItemID( albIDNbr );
            if ( catTreeID.IsOk( ) )
            {
                catTree->SetCatalogLink( catTreeID, link, albIDNbr );
            }
        }
    }
}

//--------------

void AlbumTreeCtrl::ValidateTree( )
{
    wxTreeItemId id = GetRootItem( );
    if ( id.IsOk( ) )
    {
        ResetValidateStatus( );
        Validate( id );
    }
}

//----------------

void AlbumTreeCtrl::OnTreectrlItemCollapsed( wxTreeEvent& event )
{

    event.Skip( );
}

//----------------

void AlbumTreeCtrl::OnTreectrlItemExpanded( wxTreeEvent& event )
{

    event.Skip( );

}

