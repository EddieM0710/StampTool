/**
 * @file DesignTreeCtrl.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
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
#include <wx/filename.h>

#include "Defs.h"
#include "gui/GuiDefs.h"

#include "utils/Project.h"

#include "AlbumGenApp.h"
#include "design/DesignData.h"
#include "design/LayoutBase.h"
#include "design/Album.h"
#include "design/Page.h"
#include "design/Stamp.h"
#include "design/Row.h"
#include "design/Column.h"
#include "gui/AlbumGenFrame.h"
#include "gui/DesignTreeCtrl.h"
#include "utils/XMLUtilities.h"
#include "utils/StampList.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/StampDetailsDialog.h"
#include "gui/AlbumDetailsDialog.h"
#include "gui/PageDetailsDialog.h"
#include "gui/RowDetailsDialog.h"
#include "gui/ColDetailsDialog.h"
#include "gui/IconDefs.h"
#include"gui/AlbumImagePanel.h"

 /*
  * AlbumGenFrame type definition
  */

IMPLEMENT_CLASS( DesignTreeCtrl, wxTreeCtrl );

wxDECLARE_APP( AlbumGenApp );

wxBEGIN_EVENT_TABLE( DesignTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( ID_DESIGNTREECTRL, DesignTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_DESIGNTREECTRL, DesignTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_DESIGNTREECTRL, DesignTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( ID_DESIGNTREECTRL, DesignTreeCtrl::OnItemStateClick )
EVT_TREE_ITEM_MENU( ID_DESIGNTREECTRL, DesignTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_RIGHT_CLICK( ID_DESIGNTREECTRL, DesignTreeCtrl::OnItemRClick )

wxEND_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

// DesignTreeCtrl implementation

//*****

wxColour ItemBackgroundColour[ 3 ] = { wxNullColour, *wxYELLOW, *wxRED };

DesignTreeCtrl::DesignTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )

{
    m_reverseSort = true;

    CreateImageList( );
    CreateStateImageList( false );
    ItemBackgroundColour[ Design::AT_OK ] = GetBackgroundColour( );
}

//*****

wxString DesignTreeCtrl::MakeItemLabel( wxTreeItemId id )
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

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId DesignTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child )
{
    wxString name = child->GetName( );
    Design::AlbumBaseType nodeType = Design::FindAlbumBaseType( name );;
    if ( Design::IsAlbumBaseTypeValid( nodeType ) )
    {
        Design::AlbumBase* node = Design::MakeNode( child );
        if ( node )
        {
            Design::IconID icon;
            wxString label;

            //if the child element is not a stamp
            if ( nodeType == Design::AT_Stamp )
            {
                // then we add the appropriate icon and label
                Design::Stamp* stamp = ( Design::Stamp* )node;
                // stamp combines the stampID and its name to form a label
                label = stamp->GetAttrStr( Design::AT_CatNbr );
                wxString title = stamp->GetAttrStr( Design::AT_Name );
                label += " - " + title;
                icon = GetIconId( stamp );
            }
            else
            {
                if ( nodeType == Design::AT_Album )
                {
                    GetDesignData( )->SetAlbum( ( Design::Album* )node );
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
                Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
                wxString nodeId = node->GetAttrStr( Design::AT_CatNbr );
                if ( !nodeId.IsEmpty( ) )
                {
                    Utils::StampLink* link = stampList->AddStamp( nodeId );
                    link->SetDesignTreeID( childID );
                    itemData->SetStampLink( link );
                }
                //set the icon for the appropriate state
                SetItemImage( childID, icon );
                //       SetItemState( childID, 0 );
            }
            else
            {
                // not a stamp just add the appropriate image
                itemData->SetStampLink( 0 );
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
    return ( wxTreeItemId )0;
}

void DesignTreeCtrl::AddPageTreeItem( wxTreeItemId parentID )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Page* newPage = new Design::Page( ( wxXmlNode* )0 );;
    if ( newPage )
    {
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Page, "Page", newPage );
        wxTreeItemId childID = AppendItem( parentID, "Page", Design::Icon_Folder, -1, itemData );
        newPage->SetTreeItemId( childID );
        SetItemImage( childID, Design::Icon_Folder );
        Expand(childID);
        SelectItem(childID);
        Design::NodeStatus status = newPage->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );
    }
}

void DesignTreeCtrl::AddColTreeItem( wxTreeItemId parentID )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Column* newCol = new Design::Column( ( wxXmlNode* )0 );;
    if ( newCol )
    {
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Col, "Column", newCol );
        wxTreeItemId childID = AppendItem( parentID, "Column", Design::Icon_Folder, -1, itemData );
        newCol->SetTreeItemId( childID );
        SetItemImage( childID, Design::Icon_Folder );
        Expand(childID);
        SelectItem(childID);        Design::NodeStatus status = newCol->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );
        status = newCol->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}

void DesignTreeCtrl::AddRowTreeItem( wxTreeItemId parentID )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Row* newRow = new Design::Row( ( wxXmlNode* )0 );
    if ( newRow )
    {
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Row, "Row", newRow );
        wxTreeItemId childID = AppendItem( parentID, "Row", Design::Icon_Folder, -1, itemData );
        newRow->SetTreeItemId( childID );
        SetItemImage( childID, Design::Icon_Folder );
        Expand(childID);
        SelectItem(childID);
        Design::NodeStatus status = newRow->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );

        status = newRow->GetParent( )->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}

Design::Stamp* DesignTreeCtrl::AddStampTreeItem( wxTreeItemId parentID )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Stamp* newStamp = new Design::Stamp( ( wxXmlNode* )0 );;
    if ( newStamp )
    {

        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Stamp, "Stamp", newStamp );
        wxTreeItemId childID = AppendItem( parentID, "Stamp", Design::Icon_Folder, -1, itemData );
        newStamp->SetTreeItemId( childID );
        Design::IconID icon = GetIconId( newStamp );
        SetItemImage( childID, icon );
        Expand(childID);
        SelectItem(childID);
        Design::NodeStatus status = newStamp->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );

        status = newStamp->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
    return newStamp;
}


Utils::StampLink* DesignTreeCtrl::AppendStamp( wxTreeItemId catID )
{
    Utils::StampLink* newLink = ( Utils::StampLink* )0;
    wxTreeItemId currAlbumID = GetSelection( );
    if ( currAlbumID.IsOk( ) && catID.IsOk( ) )
    {
        wxString catStr = GetGeneratorData()->GetCatalogVolumeData()->GetVolumeFilename();
        Design::AlbumBaseType type = GetItemType( currAlbumID );
        // A stamp cant have children. so get its parent
        if ( type == Design::AT_Stamp || type == Design::AT_Title )
        {
            currAlbumID = GetItemParent( currAlbumID );
        }

        Design::Stamp* newStamp = AddStampTreeItem( currAlbumID );
        if ( newStamp )
        {
            wxTreeItemId newStampID = newStamp->GetTreeItemId( );
            wxFileName catFileName( catStr );
            wxString imageName = GetCatalogTreeCtrl( )->GetImageFullName(  catID );
            wxFileName imageFileName ( imageName );
            imageFileName.MakeRelativeTo(catFileName.GetFullPath() );
            wxString idText = GetCatalogTreeCtrl( )->GetIdText( catID );

            SetItemText( newStampID, idText );
            CatalogTreeCtrl* catTree = GetCatalogTreeCtrl( );
            newStamp->SetAttrStr( Design::AT_Name, idText );
            newStamp->SetAttrStr( Design::AT_CatNbr, catTree->GetAttribute( catID,Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] ) );
            newStamp->SetAttrStr( Design::AT_Name, catTree->GetAttribute( catID,Catalog::DT_XMLDataNames[ Catalog::DT_Name ] ) );
            newStamp->SetAttrStr( Design::AT_Height, catTree->GetAttribute( catID,Catalog::DT_XMLDataNames[ Catalog::DT_Height ] ) );
            newStamp->SetAttrStr( Design::AT_Width, catTree->GetAttribute( catID,Catalog::DT_XMLDataNames[ Catalog::DT_Width ] ) );
            newStamp->SetAttrStr( Design::AT_ImageName, imageFileName.GetFullPath() ) ;

            wxString height = newStamp->GetAttrStr( Design::AT_Height );
            newStamp->SetStampHeight( height );
            wxString width = newStamp->GetAttrStr( Design::AT_Width );
            newStamp->SetStampWidth( width );

            // stamp combines the stampID and its name to form a label
            wxString label = newStamp->GetAttrStr( Design::AT_CatNbr );
            wxString title = newStamp->GetAttrStr( Design::AT_Name );
            label += " - " + title;
            this->SetItemText( newStampID, label );

            Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
            newLink = stampList->AddStamp( idText );
            wxTreeItemId albumID = newStamp->GetTreeItemId( );
            DesignTreeItemData* newStampData = ( DesignTreeItemData* )GetItemData( albumID );
            newStampData->SetStampLink( newLink );
            newLink->SetDesignTreeID( albumID );
            newLink->SetCatTreeID( catID );
            Design::NodeStatus status = newStamp->ValidateNode( );
            SetItemBackgroundColour( albumID, ItemBackgroundColour[ status ] );
        }
    }
    return newLink;
}


//*****

void DesignTreeCtrl::CreateImageList( )
{
    wxImageList* images = CreateAlbumImageList( );
    AssignImageList( images );
}


//*****

void DesignTreeCtrl::CreateStateImageList( bool del )
{
    AssignStateImageList( CreateAlbumStateImageList( del ) );
}


//*****

void DesignTreeCtrl::DeleteItem( wxTreeItemId childID )
{
    wxTreeItemId parentID = GetItemParent( childID );
    Design::AlbumBase* child = GetItemNode( childID );
    Design::AlbumBase* parent = child->GetParent( );

    //    parent->DeleteChild( child );
    this->DeleteChildren( childID );
}


//*****

wxTreeItemId DesignTreeCtrl::FindTreeItemID( Design::AlbumBase* ele, wxTreeItemId id )
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
//*****

wxTreeItemId DesignTreeCtrl::FindTreeItemID( Design::AlbumBase* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//*****

wxTreeItemId DesignTreeCtrl::FindFirstStampChild( wxTreeItemId id )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( id, cookie );
    while ( child )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* )GetItemData( child );
        if ( data->GetType( ) == Design::AT_Stamp )
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

//*****

Design::LayoutBase* DesignTreeCtrl::GetSelectedNode( )
{
    wxTreeItemId id = GetSelection( );
    if ( id.IsOk( ) )
    {
        DesignTreeItemData* itemData = ( DesignTreeItemData* )GetItemData( id );
        return ( Design::LayoutBase* )itemData->GetNodeElement( );
    }
    return ( Design::LayoutBase* )0;
}

//*****


Design::IconID DesignTreeCtrl::GetIconId( Design::Stamp* stamp )
{
    int format = stamp->GetNodeType( );
    return Design::AlbumImageSelection[ format ][ 0 ];
}

//*****

void DesignTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}
//*****



bool DesignTreeCtrl::IsElement( wxTreeItemId item, Design::AlbumBase* ele )
{
    Design::AlbumBase* dataEle = GetItemNode( item );
    if ( dataEle == ele )
    {
        return false;
    }
    return true;
}
//*****

void DesignTreeCtrl::LoadTree( )
{
    wxXmlDocument* doc = GetDesignData( )->GetDoc( );
    if ( doc && doc->IsOk() )
    {
        wxXmlNode* docRoot = doc->GetRoot( );
        if ( docRoot)
        {
            AddChild( 0, docRoot );
            GetDesignData( )->UpdateAlbum( );
            wxTreeItemId id = FindFirstStampChild( GetRootItem( ) );
            if ( id.IsOk( ) ) SelectItem( id );
            GetAlbumImagePanel( )->Refresh( );

            ExpandAll( );
        }
    }
}

//*****

void DesignTreeCtrl::OnBeginDrag( wxTreeEvent& event )
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


void DesignTreeCtrl::OnEndDrag( wxTreeEvent& event )
{
    wxTreeItemId srcID = m_draggedItem, dstID = event.GetItem( );
    m_draggedItem = ( wxTreeItemId )0l;

    if ( srcID == dstID )
    {
        return;
    }

    if ( !dstID.IsOk( ) || !srcID.IsOk( ) )
    {
        return;
    }

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

    //DesignTreeItemData* data = (DesignTreeItemData*)GetItemData( srcID );
    CopyItem( dstID, srcID );
    SelectItem( dstID );
    Delete( srcID );
}
void DesignTreeCtrl::CopyItem( wxTreeItemId dstID, wxTreeItemId srcID )
{
    if ( !dstID.IsOk( ) || !srcID.IsOk( ) )
    {
        return;
    }
    DesignTreeItemData* data = ( DesignTreeItemData* )GetItemData( srcID );
    DesignTreeItemData* itemData = new DesignTreeItemData( *data );

    wxTreeItemId id = AppendItem( dstID,
        GetItemText( srcID ),
        GetItemImage( srcID ),
        -1,
        itemData );
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( srcID, cookie );
    Design::AlbumBase* node = itemData->GetNodeElement( );
    if ( node )
    {
        node->SetTreeItemId( id );
    }
    Utils::StampLink* link = itemData->GetStampLink( );
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
//*****

void DesignTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );

    //    SetNextState( itemId );
}

//*****

void DesignTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    DesignTreeItemData* data = (DesignTreeItemData*)GetItemData( itemId );
    wxString desc = data->GetDesc();
    
    Design::LayoutBase* layout = (Design::LayoutBase*)data->GetNodeElement();
    std::cout << "\n\nSelected " << desc << "\n";
    layout->ReportLayoutFrame();
    std::cout << "\n\n";
    wxTreeItemId pageId = GetPage( itemId );
    if ( pageId.IsOk( ) )
    {
 //       if ( pageId != m_currPageID )
        {
//    if ( m_currPageID.IsOk( ) ) 
//    std::cout << "m_currPageID >" << GetItemText(m_currPageID) << "<\n";
//            std::cout << "pageId >" << GetItemText(pageId) << "<\n";
            m_currPageID = pageId;
            MakePage( pageId );
        }
    }
    else
    {
        std::cout << "invalid pageId\n";
    }
    event.Skip( );
}

//*****

void DesignTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );
    std::cout << "DesignTreeCtrl::OnItemMenu\n";
    DesignTreeItemData* item = ( DesignTreeItemData* )GetItemData( itemId );
    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

//*****

int DesignTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    DesignTreeItemData* itemData1 = ( DesignTreeItemData* )GetItemData( item1 );
    Design::AlbumBaseType type1 = itemData1->GetType( );

    DesignTreeItemData* itemData2 = ( DesignTreeItemData* )GetItemData( item2 );
    Design::AlbumBaseType type2 = itemData2->GetType( );

    if ( type1 != type2 )
    {
        return ( int )type1 - ( int )type2;
    }
    else
    {
        wxString id1 = itemData1->GetDesc( );
        wxString id2 = itemData2->GetDesc( );

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

//*****

void DesignTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    DesignTreeItemData* item = ( DesignTreeItemData* )GetItemData( itemId );

    event.Skip( );
}

//*****

void DesignTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
{
    if ( id.IsOk( ) )
    {
        wxString title = "Design Tree Menu";


        Design::DesignData* designData = GetDesignData( );
        Design::AlbumBase* node = GetItemNode( id );
        Design::AlbumBaseType type = node->GetNodeType( );
        wxMenu menu( title );
        wxMenu* addSubMenu = new wxMenu( );
        wxMenu deleteSubMenu( "Delete" );
        menu.AppendSubMenu( addSubMenu, "Add Item" );
        menu.Append( DesignTree_DeleteItem, "Delete Item" );
        menu.Append( DesignTree_EditDetails, "Edit Details" );
        wxMenuItem* addPageItem = addSubMenu->Append( DesignTree_AddPage, "Add Page" );
        wxMenuItem* addRowItem = addSubMenu->Append( DesignTree_AddRow, "Add Row" );
        wxMenuItem* addColItem = addSubMenu->Append( DesignTree_AddCol, "Add Column" );
        wxMenuItem* addStampItem = addSubMenu->Append( DesignTree_AddStamp, "Add Stamp" );

        switch ( type )
        {
        case Design::AT_Album:
        {
            addPageItem->Enable( true );
            addRowItem->Enable( false );
            addColItem->Enable( false );
            addStampItem->Enable( false );
            break;
        }
        case Design::AT_Page:
        {
            addPageItem->Enable( false );
            addRowItem->Enable( true );
            addColItem->Enable( true );
            addStampItem->Enable( false );
            break;
        }
        case Design::AT_Row:
        {
            addPageItem->Enable( false );
            addRowItem->Enable( false );
            addColItem->Enable( true );
            addStampItem->Enable( true );
            break;
        }
        case Design::AT_Col:
        {
            addPageItem->Enable( false );
            addRowItem->Enable( true );
            addColItem->Enable( false );
            addStampItem->Enable( true );
            break;
        }
        case Design::AT_Stamp:
        {
            addPageItem->Enable( false );
            addRowItem->Enable( false );
            addColItem->Enable( false );
            addStampItem->Enable( false );
            break;
        }
        default:
        {
            addPageItem->Enable( false );
            addRowItem->Enable( false );
            addColItem->Enable( false );
            addStampItem->Enable( false );
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
            AddStampTreeItem( id );
            break;
        }

        case DesignTree_EditDetails:
        {
            if ( type == Design::AT_Stamp )
            {
                ShowStampDetails( id, node );
                GetDesignData( )->MakePage( (Design::LayoutBase*)node );
            }
            else if ( type == Design::AT_Row )
            {
                ShowRowDetails( id, node );
                GetDesignData( )->MakePage( (Design::LayoutBase*)node );
            }
            else if ( type == Design::AT_Col )
            {
                ShowColDetails( id, node );
                GetDesignData( )->MakePage( (Design::LayoutBase*)node );
            }
            else if ( type == Design::AT_Page )
            {
                ShowPageDetails( id, node );
                GetDesignData( )->MakePage( (Design::LayoutBase*)node );
            }
            else if ( type == Design::AT_Album )
            {
                ShowAlbumDetails( id, node );
                GetDesignData( )->MakePage( (Design::LayoutBase*)node );
            }


            break;

        }
        default:
            // Fall through.
            break;
        }
    }
}

//*****

void DesignTreeCtrl::ShowAlbumDetails( wxTreeItemId treeID, Design::AlbumBase* node )
{
    Design::Album* album = ( Design::Album* )node;
    album->GetHeight( );
    AlbumDetailsDialog albumDetailsDialog( this, 12345,
        _( "View Edit Album Details" ) );
    wxString height = album->GetPageHeightStr( );
    albumDetailsDialog.SetPageHeight( height );
    wxString width = album->GetPageWidthStr( );
    albumDetailsDialog.SetPageWidth( width );
    wxString topMargin = album->GetTopMarginStr( );
    albumDetailsDialog.SetTopMargin( topMargin );
    wxString bottomMargin = album->GetTopMarginStr( );
    albumDetailsDialog.SetBottomMargin( bottomMargin );
    wxString leftMargin = album->GetLeftMarginStr( );
    albumDetailsDialog.SetLeftMargin( leftMargin );
    wxString rightMargin = album->GetRightMarginStr( );
    albumDetailsDialog.SetRightMargin( rightMargin );
    wxString borderSize = album->GetBorderSizeStr( );
    albumDetailsDialog.SetBorderSize( borderSize );

    wxString name = node->GetAttrStr( Design::AT_Name );
    albumDetailsDialog.SetName( name );


    if ( albumDetailsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( albumDetailsDialog.IsNameModified( ) )
    {
        node->SetAttrStr( Design::AT_Name, albumDetailsDialog.GetName( ) );
    }
    if ( albumDetailsDialog.IsPageHeightModified( ) )
    {
        album->SetPageHeight( albumDetailsDialog.GetPageHeight( ) );
    }
    if ( albumDetailsDialog.IsPageWidthModified( ) )
    {
        album->SetPageWidth( albumDetailsDialog.GetPageWidth( ) );
    }
    if ( albumDetailsDialog.IsTopMarginModified( ) )
    {
        album->SetTopMargin( albumDetailsDialog.GetTopMargin( ) );
    }
    if ( albumDetailsDialog.IsBottomMarginModified( ) )
    {
        album->SetBottomMargin( albumDetailsDialog.GetBottomMargin( ) );
    }
    if ( albumDetailsDialog.IsLeftMarginModified( ) )
    {
        album->SetLeftMargin( albumDetailsDialog.GetLeftMargin( ) );
    }
    if ( albumDetailsDialog.IsRightMarginModified( ) )
    {
        album->SetRightMargin( albumDetailsDialog.GetRightMargin( ) );
    }
    if ( albumDetailsDialog.IsBorderSizeModified( ) )
    {
        album->SetBorderSize( albumDetailsDialog.GetBorderSize( ) );
    }

    Design::NodeStatus status = album->ValidateNode( );
    SetItemBackgroundColour( node->GetTreeItemId( ), ItemBackgroundColour[ status ] );
    //album->MakeAlbum();
    MakePage( m_currPageID );
    // GetAlbumImagePanel( )->Refresh( );
}

void DesignTreeCtrl::ShowStampDetails( wxTreeItemId treeID, Design::AlbumBase* node )
{
    Design::Stamp* stamp = ( Design::Stamp* )node;
    stamp->GetHeight( );
    StampDetailsDialog stampDetailsDialog( this, 12345,
        _( "View Edit Stamp Details" ) );
    wxString height = stamp->GetStampHeightStr( );
    stampDetailsDialog.SetHeight( height );
    wxString width = stamp->GetStampWidthStr( );
    stampDetailsDialog.SetWidth( width );
    wxString catNbr = node->GetAttrStr( Design::AT_CatNbr );
    stampDetailsDialog.SetCatNbr( catNbr );
    wxString name = node->GetAttrStr( Design::AT_Name );
    stampDetailsDialog.SetName( name );

    stampDetailsDialog.SetShowCatNbr( stamp->GetShowCatNbr( ) );
    stampDetailsDialog.SetShowTitle( stamp->GetShowTitle( ) );

    stampDetailsDialog.SetDesignTreeID( treeID );
    stamp->ReportLayout();

   // stamp->ReportLayout( stampDetailsDialog.GetLayoutTextCtrl() );

    if ( stampDetailsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..
    if ( stampDetailsDialog.IsIDModified( ) )
    {
        node->SetAttrStr( Design::AT_CatNbr, stampDetailsDialog.GetCatNbr( ) );
    }
    if ( stampDetailsDialog.IsNameModified( ) )
    {
        node->SetAttrStr( Design::AT_Name, stampDetailsDialog.GetName( ) );
    }
    if ( stampDetailsDialog.IsHeightModified( ) )
    {
        stamp->SetStampHeight( stampDetailsDialog.GetHeight( ) );
    }
    if ( stampDetailsDialog.IsWidthModified( ) )
    {
        stamp->SetStampWidth( stampDetailsDialog.GetWidth( ) );
    }
    stamp->SetShowCatNbr( stampDetailsDialog.GetShowCatNbr( ) );
    stamp->SetShowTitle( stampDetailsDialog.GetShowTitle( ) );

    Design::NodeStatus status = stamp->ValidateNode( );
    SetItemBackgroundColour( node->GetTreeItemId( ), ItemBackgroundColour[ status ] );

}
void DesignTreeCtrl::ShowPageDetails( wxTreeItemId treeID, Design::AlbumBase* node )
{

    Design::Page* page = ( Design::Page* )node;
    PageDetailsDialog pageDetailsDialog( this, 12345,
        _( "View/Edit Page Details" ) );

    pageDetailsDialog.SetName( page->GetTitle( ) );

    pageDetailsDialog.SetDesignTreeID( treeID );

    pageDetailsDialog.SetShowTitle( page->GetShowTitle( ) );
    pageDetailsDialog.SetShowFrame( page->GetShowFrame( ) );
    page->ReportLayout();
    if ( pageDetailsDialog.ShowModal( ) == wxID_OK )
    {
        if ( pageDetailsDialog.IsNameModified( ) )
        {
            page->SetTitle( pageDetailsDialog.GetName( ) );
        }
        page->SetShowTitle( pageDetailsDialog.GetShowTitle( ) );
        page->SetShowFrame( pageDetailsDialog.GetShowFrame( ) );

        Design::NodeStatus status = page->ValidateNode( );
        SetItemBackgroundColour( page->GetTreeItemId( ), ItemBackgroundColour[ status ] );
    }
    else
    {
        return; // the user changed idea..
    }

}

void DesignTreeCtrl::ShowRowDetails( wxTreeItemId treeID, Design::AlbumBase* node )
{

    Design::Row* row = ( Design::Row* )node;
    RowDetailsDialog rowDetailsDialog( this, 12345,
        _( "View/Edit Row Details" ) );

    rowDetailsDialog.SetName( row->GetTitle( ) );

    rowDetailsDialog.SetDesignTreeID( treeID );

    rowDetailsDialog.SetShowTitle( row->GetShowTitle( ) );
    rowDetailsDialog.SetShowFrame( row->GetShowFrame( ) );
    row->ReportLayout();

    if ( rowDetailsDialog.ShowModal( ) == wxID_OK )
    {
        if ( rowDetailsDialog.IsNameModified( ) )
        {
            row->SetTitle( rowDetailsDialog.GetName( ) );
        }
        row->SetShowTitle( rowDetailsDialog.GetShowTitle( ) );
        row->SetShowFrame( rowDetailsDialog.GetShowFrame( ) );

        Design::NodeStatus status = row->ValidateNode( );
        SetItemBackgroundColour( row->GetTreeItemId( ), ItemBackgroundColour[ status ] );
    }
    else
    {
        return; // the user changed idea..
    }

}
void DesignTreeCtrl::ShowColDetails( wxTreeItemId treeID, Design::AlbumBase* node )
{

    ColDetailsDialog colDetailsDialog( this, 12345,
        _( "View/Edit Col Details" ) );
    wxString name = node->GetAttrStr( Design::AT_Name );
    colDetailsDialog.SetName( name );

    colDetailsDialog.SetDesignTreeID( treeID );

    if ( colDetailsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..

    if ( colDetailsDialog.IsNameModified( ) )
    {
        node->SetAttrStr( Design::AT_Name, colDetailsDialog.GetName( ) );
    }

    Design::NodeStatus status = node->ValidateNode( );
    SetItemBackgroundColour( node->GetTreeItemId( ), ItemBackgroundColour[ status ] );

}
void DesignTreeCtrl::ValidateTree( )
{
    wxTreeItemId id = GetRootItem( );
    if ( id.IsOk( ) )
    {
        ResetValidateStatus( );
        Validate( id );
    }
}

void DesignTreeCtrl::Validate( wxTreeItemId id )
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

void DesignTreeCtrl::SetValidateStatus( bool status )
{
    if ( ValidateStatus == true )
    {
        ValidateStatus = status;
    }
}

void DesignTreeCtrl::ResetValidateStatus( )
{
    ValidateStatus = true;
}

bool DesignTreeCtrl::GetValidateStatus( )
{
    return ValidateStatus;
}

Design::AlbumBase* DesignTreeCtrl::GetItemNode( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {
        DesignTreeItemData* data = ( DesignTreeItemData* )GetItemData( albumID );
        if ( data )
        {
            return data->GetNodeElement( );
        }
    }
    return ( Design::AlbumBase* )0;
};

wxString DesignTreeCtrl::GetItemDesc( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {
        return ( ( DesignTreeItemData* )GetItemData( albumID ) )->GetDesc( );
    };
    return "";
};

Utils::StampLink* DesignTreeCtrl::GetItemStampLink( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {
        return ( ( DesignTreeItemData* )GetItemData( albumID ) )->GetStampLink( );
    }
    return ( Utils::StampLink* )0;
};

Design::AlbumBaseType DesignTreeCtrl::GetItemType( wxTreeItemId albumID )
{
    if ( albumID.IsOk( ) )
    {

        DesignTreeItemData* data = ( DesignTreeItemData* )GetItemData( albumID );
        if ( !data->IsOk( ) )
        {
            int a = 1;
        }
        return data->GetType( );
    }
    return ( Design::AlbumBaseType )Design::AT_NOTYPE;
};


// iterate thru the tree and save all data to XML doc
void DesignTreeCtrl::SaveNodeData( wxXmlNode* parent, wxTreeItemId treeItemId )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId childID = GetFirstChild( treeItemId, cookie );
    while ( childID.IsOk( ) )
    {
        Design::LayoutBase* child = ( Design::LayoutBase* )GetItemNode( childID );
        wxXmlNode* xmlNode = Utils::NewNode( ( wxXmlNode* )0, Design::AlbumBaseNames[ child->GetNodeType( ) ] );
        // NewNode inserts a new node as the first child. Passing a null parent then using 
        // AddChild preserves the child node order.
        parent->AddChild( xmlNode );
        child->Save( xmlNode );
        SaveNodeData( xmlNode, childID );
        childID = GetNextChild( treeItemId, cookie );
    }
}


wxTreeItemId DesignTreeCtrl::GetPage( wxTreeItemId id )
{
    while ( id.IsOk( ) )
    {
        Design::AlbumBaseType type = GetItemType( id );
        if ( type == Design::AT_Album )
        {
            wxTreeItemIdValue cookie;
            wxTreeItemId childID = GetFirstChild( id, cookie);
            if ( childID.IsOk() )
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
    return ( wxTreeItemId )0;
}

void DesignTreeCtrl::MakePage( wxTreeItemId id )
{

    Design::AlbumBase* node = GetItemNode( id );
    GetDesignData( )->MakePage( (Design::LayoutBase*)node );

}