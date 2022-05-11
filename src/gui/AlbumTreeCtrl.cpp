/**
 * @file AlbumTreeCtrl.cpp
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

#include "Defs.h"
#include "gui/GuiDefs.h"

#include "utils/Project.h"

#include "AlbumGenApp.h"
#include "album/AlbumData.h"
#include "album/LayoutNode.h"
#include "album/Album.h"
#include "album/Page.h"
#include "album/Stamp.h"
#include "album/Row.h"
#include "album/Column.h"
#include "gui/AlbumGenFrame.h"
#include "gui/AlbumTreeCtrl.h"
#include "utils/XMLUtilities.h"
#include "utils/StampList.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/StampDetailsDialog.h"
#include "gui/IconDefs.h"

 /*
  * AlbumGenFrame type definition
  */

IMPLEMENT_CLASS( AlbumTreeCtrl, wxTreeCtrl );

wxDECLARE_APP( AlbumGenApp );

wxBEGIN_EVENT_TABLE( AlbumTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnItemStateClick )
EVT_CONTEXT_MENU( AlbumTreeCtrl::OnContextMenu )
// EVT_TREE_ITEM_MENU is the preferred event for creating context menus
// on a tree control, because it includes the point of the click or item,
// meaning that no additional placement calculations are required.
EVT_TREE_ITEM_MENU( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_RIGHT_CLICK( ID_ALBUMTREECTRL, AlbumTreeCtrl::OnItemRClick )

wxEND_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

// AlbumTreeCtrl implementation

//******************************************************

wxColour ItemBackgroundColour[ 3 ] = { wxNullColour, *wxYELLOW, *wxRED };

AlbumTreeCtrl::AlbumTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )

{
    m_reverseSort = true;

    CreateImageList( );
    CreateStateImageList( false );
    ItemBackgroundColour[ Layout::AT_OK ] = GetBackgroundColour( );
}

//******************************************************


// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId AlbumTreeCtrl::AddChild( wxTreeItemId parent, Layout::AlbumNode* child )
{
    wxString name = child->GetObjectName( );
    Layout::AlbumNodeType nodeType = child->GetNodeType( );
    wxString label;
    IconID icon;

    //if the child element is not a stamp
    if ( nodeType == Layout::AT_Stamp )
    {
        // then we add the appropriate icon and label
        Layout::Stamp* stamp = ( Layout::Stamp* )child;
        // stamp combines the stampID and its name to form a label
        label = stamp->GetAttrStr( Layout::AT_ID );
        icon = GetIconId( stamp );
    }
    else
    {

        label = child->GetObjectName( );
        icon = Icon_Folder;
    }


    // create the item data and add it to the tree
    AlbumTreeItemData* itemData = new AlbumTreeItemData( nodeType, label, child );
    wxTreeItemId childID = AppendItem( parent, label, icon, -1, itemData );
    child->SetTreeItemId( childID );
    Layout::AlbumNodeStatus status = child->ValidateNode( );
    SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );


    if ( nodeType == Layout::AT_Stamp )
    {
        Utils::StampList& stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
        stampList.AddStamp( ( Layout::Stamp* )child );
        //set the icon for the appropriate state
        SetItemImage( childID, icon );
        //       SetItemState( childID, 0 );
    }
    else
    {
        // not a stamp just add the appropriate image
        SetItemImage( childID, Icon_Folder );
        //       SetItemState( childID, wxTREE_ITEMSTATE_NEXT );
    }

    // now do it all again for this stamps children
    for ( Layout::AlbumNodeList::iterator it = child->BeginAlbumNodeList( ); it != child->EndAlbumNodeList( ); ++it )
    {
        Layout::LayoutNode* grandChild = ( Layout::LayoutNode* )( *it );
        // start adding child elements to it.
        AddChild( childID, grandChild );
    }

    return childID;
}

void AlbumTreeCtrl::AddPage( Layout::AlbumNode* node )
{
    Layout::AlbumData* albumData = GetAlbumData( );

    Layout::Page* newPage = albumData->AddPage( ( Layout::LayoutNode* )node );
    if ( newPage )
    {
        wxTreeItemId parentID = newPage->GetParent( )->GetTreeItemId( );
        AlbumTreeItemData* itemData = new AlbumTreeItemData( Layout::AT_Page, "Page", newPage );
        wxTreeItemId childID = AppendItem( parentID, "Page", Icon_Folder, -1, itemData );
        newPage->SetTreeItemId( childID );
        SetItemImage( childID, Icon_Folder );
        Layout::AlbumNodeStatus status = newPage->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );
    }
}

void AlbumTreeCtrl::AddCol( Layout::AlbumNode* node )
{
    Layout::AlbumData* albumData = GetAlbumData( );

    Layout::Column* newCol = albumData->AddCol( ( Layout::LayoutNode* )node );
    if ( newCol )
    {
        wxTreeItemId parentID = newCol->GetParent( )->GetTreeItemId( );
        AlbumTreeItemData* itemData = new AlbumTreeItemData( Layout::AT_Col, "Column", newCol );
        wxTreeItemId childID = AppendItem( parentID, "Column", Icon_Folder, -1, itemData );
        newCol->SetTreeItemId( childID );
        SetItemImage( childID, Icon_Folder );
        Layout::AlbumNodeStatus status = newCol->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );
        status = node->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}

void AlbumTreeCtrl::AddRow( Layout::AlbumNode* node )
{
    Layout::AlbumData* albumData = GetAlbumData( );

    Layout::Row* newRow = albumData->AddRow( ( Layout::LayoutNode* )node );
    if ( newRow )
    {
        wxTreeItemId parentID = newRow->GetParent( )->GetTreeItemId( );
        AlbumTreeItemData* itemData = new AlbumTreeItemData( Layout::AT_Row, "Row", newRow );
        wxTreeItemId childID = AppendItem( parentID, "Row", Icon_Folder, -1, itemData );
        newRow->SetTreeItemId( childID );
        SetItemImage( childID, Icon_Folder );

        Layout::AlbumNodeStatus status = newRow->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );

        status = node->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}
Layout::Stamp* AlbumTreeCtrl::AddStamp( Layout::AlbumNode* node )
{
    Layout::AlbumData* albumData = GetAlbumData( );

    Layout::Stamp* newStamp = albumData->AddStamp( ( Layout::LayoutNode* )node );
    if ( newStamp )
    {

        wxTreeItemId parentID = newStamp->GetParent( )->GetTreeItemId( );
        AlbumTreeItemData* itemData = new AlbumTreeItemData( Layout::AT_Stamp, "Stamp", newStamp );
        wxTreeItemId childID = AppendItem( parentID, "Stamp", Icon_Folder, -1, itemData );
        newStamp->SetTreeItemId( childID );
        IconID icon = GetIconId( newStamp );
        SetItemImage( childID, icon );

        Layout::AlbumNodeStatus status = newStamp->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );

        status = node->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
    return newStamp;
}

Utils::StampLink* AlbumTreeCtrl::AppendStamp( wxTreeItemId catID )
{
    wxTreeItemId currAlbumID = GetSelection( );
    if ( currAlbumID.IsOk( ) && catID.IsOk() )
    {
        AlbumTreeItemData* data = ( AlbumTreeItemData* )GetItemData( currAlbumID );
        Layout::AlbumNodeType type = data->GetType( );
        if ( type == Layout::AT_Stamp || type == Layout::AT_Title )
        {
            currAlbumID = GetItemParent( currAlbumID );
        }
        data = ( AlbumTreeItemData* )GetItemData( currAlbumID );
        Layout::AlbumNode* node = data->GetNodeElement( );
        Layout::Stamp* newStamp = AddStamp( node );
        if ( newStamp )
        {
            wxTreeItemId newStampID = newStamp->GetTreeItemId( );
            wxXmlNode* catNode = ( ( CatalogDataTreeItemData* )GetCatalogTreeCtrl( )->GetItemData( catID ) )->GetNodeElement( );
            wxString idText = catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
            SetItemText( newStampID, idText );
            newStamp->SetAttrStr( Layout::AT_ID, idText );
            newStamp->SetAttrStr( Layout::AT_Name, catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_Name ] ) );
            newStamp->SetAttrStr( Layout::AT_Height, catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_Height ] ) );
            newStamp->SetAttrStr( Layout::AT_Width, catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_Width ] ) );

            Utils::StampList& stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
            Utils::StampLink* newLink = stampList.AddStamp( newStamp );
            wxTreeItemId albumID = newStamp->GetTreeItemId( );
            newLink->SetAlbumTreeID( albumID );
            newLink->SetCatTreeID( catID );
            Layout::AlbumNodeStatus status = newStamp->ValidateNode( );
            SetItemBackgroundColour( albumID, ItemBackgroundColour[ status ] );
        }
    }
}



//******************************************************

void AlbumTreeCtrl::CreateImageList( )
{
    wxImageList* images = CreateAlbumImageList( );
    AssignImageList( images );
}

//******************************************************
void AlbumTreeCtrl::CreateStateImageList( bool del )
{
    AssignStateImageList( CreateAlbumStateImageList( del ) );
}

//******************************************************
Layout::AlbumNode* AlbumTreeCtrl::GetStampNode( wxTreeItemId itemID )
{
    AlbumTreeItemData* data = ( AlbumTreeItemData* )GetItemData( itemID );
    Layout::AlbumNode* child = data->GetNodeElement( );
}
void AlbumTreeCtrl::DeleteItem( wxTreeItemId childID )
{
    wxTreeItemId parentID = GetItemParent( childID );
    Layout::AlbumNode* child = GetStampNode( childID );
    Layout::AlbumNode* parent = child->GetParent( );

    parent->DeleteChild( child );
    this->DeleteChildren( childID );
}


//******************************************************

wxTreeItemId AlbumTreeCtrl::FindTreeItemID( Layout::AlbumNode* ele, wxTreeItemId id )
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
            wxTreeItemId id = FindTreeItemID( ele, child );
            if ( id )
            {
                return id;
            }
        }
        child = this->GetNextChild( child, cookie );
    }
    return 0;
}
//******************************************************

wxTreeItemId AlbumTreeCtrl::FindTreeItemID( Layout::AlbumNode* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//******************************************************

wxTreeItemId AlbumTreeCtrl::FindFirstStampChild( wxTreeItemId id )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( id, cookie );
    while ( child )
    {
        AlbumTreeItemData* data = ( AlbumTreeItemData* )GetItemData( child );
        if ( data->GetType( ) == Layout::AT_Stamp )
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
        child = GetNextChild( child, cookie );
    }
    return 0;
}

//******************************************************

Layout::LayoutNode* AlbumTreeCtrl::GetSelectedNode( )
{
    wxTreeItemId id = GetSelection( );
    if ( id.IsOk( ) )
    {
        AlbumTreeItemData* itemData = ( AlbumTreeItemData* )GetItemData( id );
        return ( Layout::LayoutNode* )itemData->GetNodeElement( );
    }
    return ( Layout::LayoutNode* )0;
}

//******************************************************


IconID AlbumTreeCtrl::GetIconId( Layout::Stamp* stamp )
{
    int format = stamp->GetNodeType( );
    return AlbumImageSelection[ format ][ 0 ];
}

//******************************************************

void AlbumTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}
//******************************************************



bool AlbumTreeCtrl::IsElement( wxTreeItemId item, Layout::AlbumNode* ele )
{
    Layout::AlbumNode* dataEle = GetStampNode( item );
    if ( dataEle == ele )
    {
        return false;
    }
    return true;
}
//******************************************************

// basic load of the tree
void AlbumTreeCtrl::LoadTree( )
{
    Layout::Album* album = GetAlbumData( )->GetAlbum( );
    wxString name = album->GetAttrStr( Layout::AT_Name );
    // Create the root item
    AlbumTreeItemData* itemData
        = new AlbumTreeItemData( Layout::AT_Album, name, ( Layout::AlbumNode* )album );
    wxTreeItemId rootID = AddRoot( name, Icon_Folder, 1, itemData );
    AddChild( rootID, album );

}

//******************************************************

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

//******************************************************


void AlbumTreeCtrl::OnEndDrag( wxTreeEvent& event )
{
    wxTreeItemId srcID = m_draggedItem, dstID = event.GetItem( );
    m_draggedItem = ( wxTreeItemId )0l;

    if ( srcID == dstID )
    {
        return;
    }

    if ( !dstID.IsOk( ) )
    {
        return;
    }

    Layout::AlbumNode* srcElement = GetStampNode( srcID );
    Layout::AlbumNode* dstElement = GetStampNode( dstID );

    wxTreeItemId parentID = GetItemParent( srcID );
    Layout::AlbumNode* srcParentElement = GetStampNode( parentID );

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

    srcParentElement->DeleteChild( srcElement );
    dstElement->AddChild( srcElement );

    // now update the tree with the new one
    wxTreeItemId id = AddChild( dstID, srcElement );
    SelectItem( dstID );
    Delete( srcID );
}

//******************************************************

void AlbumTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );

    //    SetNextState( itemId );
}

//******************************************************

void AlbumTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    Layout::AlbumNode* stamp = GetStampNode( itemId );
    // wxGetApp( ).GetFrame( )->SetStamp( stamp );

    event.Skip( );
}

//******************************************************

void AlbumTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );
    std::cout << "AlbumTreeCtrl::OnItemMenu\n";
    AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemId );
    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    // wxLogMessage("OnItemMenu for item \"%s\" at screen coords (%i, %i)",
    //              item ? item->GetDesc() : wxString("unknown"), screenpt.x,
    //              screenpt.y);

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

//******************************************************

int AlbumTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    AlbumTreeItemData* itemData1 = ( AlbumTreeItemData* )GetItemData( item1 );
    Layout::AlbumNodeType type1 = itemData1->GetType( );

    AlbumTreeItemData* itemData2 = ( AlbumTreeItemData* )GetItemData( item2 );
    Layout::AlbumNodeType type2 = itemData2->GetType( );

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

//******************************************************

void AlbumTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemId );

    event.Skip( );
}

//******************************************************

void AlbumTreeCtrl::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint pt = event.GetPosition( );

    int id = event.GetId( );

    wxTreeItemId treeID = HitTest( pt );
    if ( treeID.IsOk( ) )
    {
        Layout::AlbumNode* node = GetStampNode( treeID );
        Layout::AlbumData* albumData = GetAlbumData( );
        if ( id == AlbumDataTree_AddPage )
        {

        }
        else if ( id == AlbumDataTree_AddCol )
        {

        }
        else if ( id == AlbumDataTree_AddRow )
        {

            Layout::Row* newRow = albumData->AddRow( ( Layout::LayoutNode* )node );

        }
        else if ( id == AlbumDataTree_AddStamp )
        {

        }
        else if ( id == AlbumDataTree_AddTitle )
        {

        }
    }


    event.Skip( );
}

//******************************************************

void AlbumTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
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

    Layout::AlbumData* albumData = GetAlbumData( );
    Layout::AlbumNode* node = GetStampNode( id );
    Layout::AlbumNodeType type = node->GetNodeType( );
    wxMenu menu( title );
    wxMenu* addSubMenu = new wxMenu( );
    wxMenu deleteSubMenu( "Delete" );
    menu.AppendSubMenu( addSubMenu, "Add Item" );
    menu.Append( AlbumDataTree_DeleteItem, "Delete Item" );
    menu.Append( AlbumDataTree_EditDetails, "EditDetails" );
    addSubMenu->Append( AlbumDataTree_AddPage, "Add Page" );
    addSubMenu->Append( AlbumDataTree_AddTitle, "Add Title" );
    addSubMenu->Append( AlbumDataTree_AddRow, "Add Row" );
    addSubMenu->Append( AlbumDataTree_AddCol, "Add Col" );
    addSubMenu->Append( AlbumDataTree_AddStamp, "Add Stamp" );

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
    case AlbumDataTree_AddPage:
    {
        AddPage( node );

        break;
    }
    case AlbumDataTree_AddCol:
    {
        AddCol( node );

        break;
    }
    case AlbumDataTree_AddRow:
    {
        AddRow( node );
        break;
    }
    case AlbumDataTree_AddStamp:
    {
        AddStamp( node );
        break;
    }

    case AlbumDataTree_EditDetails:
    {
        if ( type == Layout::AT_Stamp )
        {
            ShowStampDetails( node );
        }
        break;

    }
    default:
        // Fall through.
        break;
    }
}

//******************************************************

void AlbumTreeCtrl::ShowStampDetails( Layout::AlbumNode* node )
{

    StampDetailsDialog stampDetailsDialog( this, 12345,
        _( "View Edit Stamp Details" ) );
    wxString height = node->GetAttrStr( Layout::AT_Height );
    stampDetailsDialog.SetHeight( height );
    wxString width = node->GetAttrStr( Layout::AT_Width );
    stampDetailsDialog.SetWidth( width );
    wxString id = node->GetAttrStr( Layout::AT_ID );
    stampDetailsDialog.SetID( id );
    wxString name = node->GetAttrStr( Layout::AT_Name );
    stampDetailsDialog.SetName( name );

    if ( stampDetailsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..
    if ( stampDetailsDialog.IsIDModified( ) )
    {
        node->SetAttrStr( Layout::AT_ID, stampDetailsDialog.GetID( ) );
    }
    if ( stampDetailsDialog.IsNameModified( ) )
    {
        node->SetAttrStr( Layout::AT_Name, stampDetailsDialog.GetName( ) );
    }
    if ( stampDetailsDialog.IsHeightModified( ) )
    {
        node->SetAttrStr( Layout::AT_Height, stampDetailsDialog.GetHeight( ) );
    }
    if ( stampDetailsDialog.IsWidthModified( ) )
    {
        node->SetAttrStr( Layout::AT_Width, stampDetailsDialog.GetWidth( ) );
    }
    Layout::AlbumNodeStatus status = node->ValidateNode( );
    SetItemBackgroundColour( node->GetTreeItemId( ), ItemBackgroundColour[ status ] );

}

void AlbumTreeCtrl::ValidateTree( )
{
    wxTreeItemId id = GetRootItem( );
    if ( id.IsOk( ) )
    {
        ResetValidateStatus( );
        Validate( id );
    }
}

void AlbumTreeCtrl::Validate( wxTreeItemId id )
{
    if ( id.IsOk( ) )
    {
        Layout::AlbumNode* node = GetStampNode( id );
        Layout::AlbumNodeStatus status = node->ValidateNode( );
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

void AlbumTreeCtrl::SetValidateStatus( bool status )
{
    if ( ValidateStatus == true )
    {
        ValidateStatus = status;
    }
}

void AlbumTreeCtrl::ResetValidateStatus( )
{
    ValidateStatus = true;
}
bool AlbumTreeCtrl::GetValidateStatus( )
{
    return ValidateStatus;
}