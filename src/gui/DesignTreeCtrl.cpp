/**
 * @file DesignTreeCtrl.cpp
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
#include "gui/IconDefs.h"

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
EVT_CONTEXT_MENU( DesignTreeCtrl::OnContextMenu )
// EVT_TREE_ITEM_MENU is the preferred event for creating context menus
// on a tree control, because it includes the point of the click or item,
// meaning that no additional placement calculations are required.
EVT_TREE_ITEM_MENU( ID_DESIGNTREECTRL, DesignTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_RIGHT_CLICK( ID_DESIGNTREECTRL, DesignTreeCtrl::OnItemRClick )

wxEND_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

// DesignTreeCtrl implementation

//******************************************************

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

//******************************************************

wxString DesignTreeCtrl::MakeItemLabel ( wxTreeItemId id )
{
    if (id.IsOk() )
    {
        Design::AlbumBase * node = GetItemNode(id );
        if ( node )
        {           
            if ( GetItemType(id) == Design::AT_Stamp)
            {   
                    return node->GetAttrStr(Design::AT_ID) + " - " + node->GetAttrStr(Design::AT_Name) ;
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
wxTreeItemId DesignTreeCtrl::AddChild( wxTreeItemId parent, Design::AlbumBase* child )
{
    wxString name = child->GetObjectName( );
    Design::AlbumBaseType nodeType = child->GetNodeType( );
    Design::IconID icon;
    wxString label;
    //if the child element is not a stamp
    if ( nodeType == Design::AT_Stamp )
    {
        // then we add the appropriate icon and label
        Design::Stamp* stamp = ( Design::Stamp* )child;
        // stamp combines the stampID and its name to form a label
        label = stamp->GetAttrStr( Design::AT_ID );
        icon = GetIconId( stamp );
    }
    else
    {

        label = child->GetObjectName( );
        icon = Design::Icon_Folder;
    }


    // create the item data and add it to the tree
    DesignTreeItemData* itemData = new DesignTreeItemData( nodeType, "", child );
    wxTreeItemId childID = AppendItem( parent, label, icon, -1, itemData );

    child->SetTreeItemId( childID );
    Design::NodeStatus status = child->ValidateNode( );
    SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );


    if ( nodeType == Design::AT_Stamp )
    {
        Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
        Utils::StampLink* link = stampList->AddStamp( ( Design::Stamp* )child );
        itemData->SetStampLink(link);
        //set the icon for the appropriate state
        SetItemImage( childID, icon );
        //       SetItemState( childID, 0 );
    }
    else
    {
        // not a stamp just add the appropriate image
        itemData->SetStampLink(0);
        SetItemImage( childID, Design::Icon_Folder );
        //       SetItemState( childID, wxTREE_ITEMSTATE_NEXT );
    }

    // now do it all again for this stamps children
    for ( Design::AlbumBaseList::iterator it = child->BeginAlbumBaseList( ); it != child->EndAlbumBaseList( ); ++it )
    {
        Design::LayoutBase* grandChild = ( Design::LayoutBase* )( *it );
        // start adding child elements to it.
        AddChild( childID, grandChild );
    }

    return childID;
}

void DesignTreeCtrl::AddPage( Design::AlbumBase* node )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Page* newPage = designData->AddPage( ( Design::LayoutBase* )node );
    if ( newPage )
    {
        wxTreeItemId parentID = newPage->GetParent( )->GetTreeItemId( );
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Page, "Page", newPage );
        wxTreeItemId childID = AppendItem( parentID, "Page", Design::Icon_Folder, -1, itemData );
        newPage->SetTreeItemId( childID );
        SetItemImage( childID, Design::Icon_Folder );
        Design::NodeStatus status = newPage->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );
    }
}

void DesignTreeCtrl::AddCol( Design::AlbumBase* node )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Column* newCol = designData->AddCol( ( Design::LayoutBase* )node );
    if ( newCol )
    {
        wxTreeItemId parentID = newCol->GetParent( )->GetTreeItemId( );
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Col, "Column", newCol );
        wxTreeItemId childID = AppendItem( parentID, "Column", Design::Icon_Folder, -1, itemData );
        newCol->SetTreeItemId( childID );
        SetItemImage( childID, Design::Icon_Folder );
        Design::NodeStatus status = newCol->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );
        status = node->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}

void DesignTreeCtrl::AddRow( Design::AlbumBase* node )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Row* newRow = designData->AddRow( ( Design::LayoutBase* )node );
    if ( newRow )
    {
        wxTreeItemId parentID = newRow->GetParent( )->GetTreeItemId( );
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Row, "Row", newRow );
        wxTreeItemId childID = AppendItem( parentID, "Row", Design::Icon_Folder, -1, itemData );
        newRow->SetTreeItemId( childID );
        SetItemImage( childID, Design::Icon_Folder );

        Design::NodeStatus status = newRow->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );

        status = node->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
}
Design::Stamp* DesignTreeCtrl::AddStamp( Design::AlbumBase* node )
{
    Design::DesignData* designData = GetDesignData( );

    Design::Stamp* newStamp = designData->AddStamp( ( Design::LayoutBase* )node );
    if ( newStamp )
    {

        wxTreeItemId parentID = newStamp->GetParent( )->GetTreeItemId( );
        DesignTreeItemData* itemData = new DesignTreeItemData( Design::AT_Stamp, "Stamp", newStamp );
        wxTreeItemId childID = AppendItem( parentID, "Stamp", Design::Icon_Folder, -1, itemData );
        newStamp->SetTreeItemId( childID );
        Design::IconID icon = GetIconId( newStamp );
        SetItemImage( childID, icon );

        Design::NodeStatus status = newStamp->ValidateNode( );
        SetItemBackgroundColour( childID, ItemBackgroundColour[ status ] );

        status = node->ValidateNode( );
        SetItemBackgroundColour( parentID, ItemBackgroundColour[ status ] );
    }
    return newStamp;
}

Utils::StampLink* DesignTreeCtrl::AppendStamp( wxTreeItemId catID )
{
    Utils::StampLink* newLink = (Utils::StampLink*)0;
    wxTreeItemId currAlbumID = GetSelection( );
    if ( currAlbumID.IsOk( ) && catID.IsOk() )
    {

        Design::AlbumBaseType type = GetItemType(currAlbumID );
        if ( type == Design::AT_Stamp || type == Design::AT_Title )
        {
            currAlbumID = GetItemParent( currAlbumID );
        }


        Design::AlbumBase* node = GetItemNode( currAlbumID );
        Design::Stamp* newStamp = AddStamp( node );
        if ( newStamp )
        {
            wxTreeItemId newStampID = newStamp->GetTreeItemId( );
            wxXmlNode* catNode = ( ( CatalogTreeItemData* )GetCatalogTreeCtrl( )->GetItemData( catID ) )->GetNodeElement( );
            wxString idText = catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
            SetItemText( newStampID, idText );
            newStamp->SetAttrStr( Design::AT_ID, idText );
            newStamp->SetAttrStr( Design::AT_Name, catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_Name ] ) );
            newStamp->SetAttrStr( Design::AT_Height, catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_Height ] ) );
            newStamp->SetAttrStr( Design::AT_Width, catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_Width ] ) );
            Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
            newLink = stampList->AddStamp( newStamp );
            wxTreeItemId albumID = newStamp->GetTreeItemId( );
            DesignTreeItemData*  newStampData = ( DesignTreeItemData* )GetItemData( albumID );
            newStampData->SetStampLink( newLink );
            newLink->SetDesignTreeID( albumID );
            newLink->SetCatTreeID( catID );
            Design::NodeStatus status = newStamp->ValidateNode( );
            SetItemBackgroundColour( albumID, ItemBackgroundColour[ status ] );
        }
    }
    return newLink;
}


//******************************************************

void DesignTreeCtrl::CreateImageList( )
{
    wxImageList* images = CreateAlbumImageList( );
    AssignImageList( images );
}


//******************************************************

void DesignTreeCtrl::CreateStateImageList( bool del )
{
    AssignStateImageList( CreateAlbumStateImageList( del ) );
}


//******************************************************

void DesignTreeCtrl::DeleteItem( wxTreeItemId childID )
{
    wxTreeItemId parentID = GetItemParent( childID );
    Design::AlbumBase* child = GetItemNode( childID );
    Design::AlbumBase* parent = child->GetParent( );

    parent->DeleteChild( child );
    this->DeleteChildren( childID );
}


//******************************************************

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

wxTreeItemId DesignTreeCtrl::FindTreeItemID( Design::AlbumBase* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//******************************************************

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
        child = GetNextChild( child, cookie );
    }
    return 0;
}

//******************************************************

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

//******************************************************


Design::IconID DesignTreeCtrl::GetIconId( Design::Stamp* stamp )
{
    int format = stamp->GetNodeType( );
    return Design::AlbumImageSelection[ format ][ 0 ];
}

//******************************************************

void DesignTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}
//******************************************************



bool DesignTreeCtrl::IsElement( wxTreeItemId item, Design::AlbumBase* ele )
{
    Design::AlbumBase* dataEle = GetItemNode( item );
    if ( dataEle == ele )
    {
        return false;
    }
    return true;
}
//******************************************************

// basic load of the tree
void DesignTreeCtrl::LoadTree( )
{
    Design::Album* album = GetDesignData( )->GetAlbum( );
    wxString name = album->GetAttrStr( Design::AT_Name );
    // Create the root item
    DesignTreeItemData* itemData
        = new DesignTreeItemData( Design::AT_Album, name, ( Design::AlbumBase* )album );
    wxTreeItemId rootID = AddRoot( name, Design::Icon_Folder, 1, itemData );
    AddChild( rootID, album );
    ExpandAll( );
}

//******************************************************

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

//******************************************************


void DesignTreeCtrl::OnEndDrag( wxTreeEvent& event )
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

    Design::AlbumBase* srcElement = GetItemNode( srcID );
    Design::AlbumBase* dstElement = GetItemNode( dstID );

    wxTreeItemId parentID = GetItemParent( srcID );
    Design::AlbumBase* srcParentElement = GetItemNode( parentID );

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

void DesignTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );

    //    SetNextState( itemId );
}

//******************************************************

void DesignTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    Design::AlbumBase* stamp = GetItemNode( itemId );
    // wxGetApp( ).GetFrame( )->SetStamp( stamp );

    event.Skip( );
}

//******************************************************

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

//******************************************************

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

//******************************************************

void DesignTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    DesignTreeItemData* item = ( DesignTreeItemData* )GetItemData( itemId );

    event.Skip( );
}

//******************************************************

void DesignTreeCtrl::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint pt = event.GetPosition( );

    int id = event.GetId( );

    wxTreeItemId treeID = HitTest( pt );
    if ( treeID.IsOk( ) )
    {
        Design::AlbumBase* node = GetItemNode( treeID );
        Design::DesignData* designData = GetDesignData( );
        if ( id == DesignTree_AddPage )
        {

        }
        else if ( id == DesignTree_AddCol )
        {

        }
        else if ( id == DesignTree_AddRow )
        {

            Design::Row* newRow = designData->AddRow( ( Design::LayoutBase* )node );

        }
        else if ( id == DesignTree_AddStamp )
        {

        }
        else if ( id == DesignTree_AddTitle )
        {

        }
    }


    event.Skip( );
}

//******************************************************

void DesignTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
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

    Design::DesignData* designData = GetDesignData( );
    Design::AlbumBase* node = GetItemNode( id );
    Design::AlbumBaseType type = node->GetNodeType( );
    wxMenu menu( title );
    wxMenu* addSubMenu = new wxMenu( );
    wxMenu deleteSubMenu( "Delete" );
    menu.AppendSubMenu( addSubMenu, "Add Item" );
    menu.Append( DesignTree_DeleteItem, "Delete Item" );
    menu.Append( DesignTree_EditDetails, "EditDetails" );
    addSubMenu->Append( DesignTree_AddPage, "Add Page" );
    addSubMenu->Append( DesignTree_AddTitle, "Add Title" );
    addSubMenu->Append( DesignTree_AddRow, "Add Row" );
    addSubMenu->Append( DesignTree_AddCol, "Add Col" );
    addSubMenu->Append( DesignTree_AddStamp, "Add Stamp" );

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
    case DesignTree_AddPage:
    {
        AddPage( node );

        break;
    }
    case DesignTree_AddCol:
    {
        AddCol( node );

        break;
    }
    case DesignTree_AddRow:
    {
        AddRow( node );
        break;
    }
    case DesignTree_AddStamp:
    {
        AddStamp( node );
        break;
    }

    case DesignTree_EditDetails:
    {
        if ( type == Design::AT_Stamp )
        {
            ShowStampDetails( id, node );
        }
        break;

    }
    default:
        // Fall through.
        break;
    }
}

//******************************************************

void DesignTreeCtrl::ShowStampDetails( wxTreeItemId treeID, Design::AlbumBase* node )
{

    StampDetailsDialog stampDetailsDialog( this, 12345,
        _( "View Edit Stamp Details" ) );
    wxString height = node->GetAttrStr( Design::AT_Height );
    stampDetailsDialog.SetHeight( height );
    wxString width = node->GetAttrStr( Design::AT_Width );
    stampDetailsDialog.SetWidth( width );
    wxString id = node->GetAttrStr( Design::AT_ID );
    stampDetailsDialog.SetID( id );
    wxString name = node->GetAttrStr( Design::AT_Name );
    stampDetailsDialog.SetName( name );

    stampDetailsDialog.SetDesignTreeID(treeID);

    if ( stampDetailsDialog.ShowModal( ) == wxID_CANCEL )
        return; // the user changed idea..
    if ( stampDetailsDialog.IsIDModified( ) )
    {
        node->SetAttrStr( Design::AT_ID, stampDetailsDialog.GetID( ) );
    }
    if ( stampDetailsDialog.IsNameModified( ) )
    {
        node->SetAttrStr( Design::AT_Name, stampDetailsDialog.GetName( ) );
    }
    if ( stampDetailsDialog.IsHeightModified( ) )
    {
        node->SetAttrStr( Design::AT_Height, stampDetailsDialog.GetHeight( ) );
    }
    if ( stampDetailsDialog.IsWidthModified( ) )
    {
        node->SetAttrStr( Design::AT_Width, stampDetailsDialog.GetWidth( ) );
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

    Design::AlbumBase* DesignTreeCtrl::GetItemNode( wxTreeItemId albumID ) { 
        if ( albumID.IsOk( ) ) { return ( ( DesignTreeItemData* )GetItemData( albumID ) )->GetNodeElement( ); } return (Design::AlbumBase*)0;};

    wxString DesignTreeCtrl::GetItemDesc( wxTreeItemId albumID ) {
        if ( albumID.IsOk( ) ) {  return ( ( DesignTreeItemData* )GetItemData( albumID ) )->GetDesc( );}; return "";};

    Utils::StampLink* DesignTreeCtrl::GetItemStampLink( wxTreeItemId albumID ) { 
        if ( albumID.IsOk( ) ) { return ( ( DesignTreeItemData* )GetItemData( albumID ) )->GetStampLink( ); } return (Utils::StampLink*)0;};
  
    Design::AlbumBaseType DesignTreeCtrl::GetItemType( wxTreeItemId albumID ) { 
        if ( albumID.IsOk( ) ) { return ( ( DesignTreeItemData* )GetItemData( albumID ) )->GetType( ); } return (Design::AlbumBaseType)Design::AT_NOTYPE;};
