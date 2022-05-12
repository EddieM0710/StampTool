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
#include "catalog/Stamp.h"
#include "gui/AlbumGenFrame.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/DescriptionPanel.h"

 // #include "art/StampBlack.xpm"
 // #include "art/StampBlue.xpm"
 // #include "art/StampBrown.xpm"
 // #include "art/StampGreen.xpm"
 // #include "art/StampPurple.xpm"
 // #include "art/StampRed.xpm"
 // #include "art/StampYellow.xpm"

 // #include "art/StampBlackBlock.xpm"
 // #include "art/StampBlueBlock.xpm"
 // #include "art/StampBrownBlock.xpm"
 // #include "art/StampGreenBlock.xpm"
 // #include "art/StampPurpleBlock.xpm"
 // #include "art/StampRedBlock.xpm"
 // #include "art/StampYellowBlock.xpm"

 // #include "art/StampBlackMiniSheet.xpm"
 // #include "art/StampBlueMiniSheet.xpm"
 // #include "art/StampBrownMiniSheet.xpm"
 // #include "art/StampGreenMiniSheet.xpm"
 // #include "art/StampPurpleMiniSheet.xpm"
 // #include "art/StampRedMiniSheet.xpm"
 // #include "art/StampYellowMiniSheet.xpm"

 // #include "art/StampBlackSouvenirSheet.xpm"
 // #include "art/StampBlueSouvenirSheet.xpm"
 // #include "art/StampBrownSouvenirSheet.xpm"
 // #include "art/StampGreenSouvenirSheet.xpm"
 // #include "art/StampPurpleSouvenirSheet.xpm"
 // #include "art/StampRedSouvenirSheet.xpm"
 // #include "art/StampYellowSouvenirSheet.xpm"
 // #include "art/folder.xpm"

 // #include "art/unchecked.xpm"
 // #include "art/checked.xpm"

/*
  * AlbumGenFrame type definition
 */

IMPLEMENT_CLASS( CatalogTreeCtrl, wxTreeCtrl );

wxDECLARE_APP( AlbumGenApp );

wxBEGIN_EVENT_TABLE( CatalogTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemStateClick )
//EVT_CONTEXT_MENU( CatalogTreeCtrl::OnContextMenu )
// EVT_TREE_ITEM_MENU is the preferred event for creating context menus
// on a tree control, because it includes the point of the click or item,
// meaning that no additional placement calculations are required.
EVT_TREE_ITEM_MENU( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_RIGHT_CLICK( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemRClick )

wxEND_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

// CatalogTreeCtrl implementation

CatalogTreeCtrl::CatalogTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )

{
    m_reverseSort = true;

    CreateImageList( );
    CreateStateImageList( false );

}

void CatalogTreeCtrl::CreateImageList( )
    {
    AssignImageList( CreateCatalogImageList( ) );
    }
void CatalogTreeCtrl::CreateStateImageList( bool del )
{
    AssignStateImageList( CreateCatalogStateImageList( del ) );
}

int CatalogTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
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


Utils::StampLink* CatalogTreeCtrl::AppendAlbumStamp( wxTreeItemId itemId )
{
    Utils::StampLink* link = GetDesignTreeCtrl( )->AppendStamp( itemId );
    if ( link )
    {
        CatalogTreeItemData* data = (CatalogTreeItemData*)GetItemData( itemId );
        data->SetStampLink(link);
        wxXmlNode* catNode = GetStampNode( itemId );
       // link->SetCatNode( catNode );
        link->SetCatTreeID( itemId );
    }
    return link;
}

wxXmlNode* CatalogTreeCtrl::GetStampNode( wxTreeItemId itemId )
        {
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
    return data->GetNodeElement( );
        }

wxString CatalogTreeCtrl::GetStampID( wxTreeItemId itemId )
{
    wxXmlNode* element = GetStampNode( itemId );
    return element->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
}

Utils::StampLink* CatalogTreeCtrl::FindStampLink( wxTreeItemId itemId )
{
    wxString id = GetStampID( itemId );
    Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
    Utils::StampLink* stampLink = stampList->FindStampLink( id );
    return stampLink;
}

void CatalogTreeCtrl::DeleteAlbumStamp( wxTreeItemId itemId )
{
    CatalogTreeItemData* data = (CatalogTreeItemData*)GetItemData( itemId );
    Utils::StampLink* stampLink = data->GetStampLink( );
    if ( stampLink )
    {
        wxTreeItemId itemID = stampLink->GetDesignTreeID( );
        if ( itemID.IsOk( ) ) GetDesignTreeCtrl( )->DeleteItem( itemID );
    }
}

void CatalogTreeCtrl::RemoveStampLink( wxTreeItemId itemId )
{
    if ( itemId.IsOk() )
    {
        CatalogTreeItemData* data = (CatalogTreeItemData*)GetItemData( itemId );
        data->SetStampLink( 0 );
    }
}


void CatalogTreeCtrl::SetNextState( const wxTreeItemId& itemId )
{

    wxXmlNode* element = GetStampNode( itemId );
    Catalog::Stamp* stamp = new Catalog::Stamp( element );
    if ( stamp->IsOK( ) )
    {
        SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
        int state = GetItemState( itemId );
        stamp->SetCheckedStatusType( ( Catalog::CheckedStatusType )state );
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

Catalog::IconID CatalogTreeCtrl::GetInventoryIconId( Catalog::Stamp* stamp )
{
    int format = stamp->GetFormatType( );
    int type = stamp->GetInventoryStatusType();
    return Catalog::CatalogImageSelection[ format ][ type ];
}

void CatalogTreeCtrl::SetInventoryStatusImage( )
{
    wxTreeItemId itemId = GetFocusedItem( );
    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );
    wxXmlNode* element = item->GetNodeElement( );
    Catalog::Stamp* stamp = new Catalog::Stamp( element );
    if ( stamp->IsOK( ) )
    {
        int status = stamp->GetInventoryStatusType( );
        int format = stamp->GetFormatType( );
        Catalog::IconID iconID = Catalog::CatalogImageSelection[ format ][ status ];
        SetItemImage( itemId, GetInventoryIconId( stamp ) );
    }
}

void CatalogTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}

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
    ShowDropMenu(  itemSrc,  itemDst );

}

void CatalogTreeCtrl::ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst  )
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

        wxXmlNode* srcElement = GetStampNode( itemSrc );
        wxXmlNode* dstElement = GetStampNode( itemDst );

        // move the element
        // this means making a copy and deleting the old one so old pointers are
        // trash
        wxXmlNode* newElement = Catalog::InsertStamp( dstElement, srcElement, false );

        // now update the tree with the new one
        wxTreeItemId id = InsertChild( itemDst, newElement, false );
        //wxTreeItemId id = AddChild( itemDst, newElement );
        SelectItem( itemDst );
        Delete( itemSrc );

        break;
    }
    case CatalogDataTree_After:
    {

        wxXmlNode* srcElement = GetStampNode( itemSrc );
        wxXmlNode* dstElement = GetStampNode( itemDst );

        // move the element
        // this means making a copy and deleting the old one so old pointers are
        // trash
        wxXmlNode* newElement = Catalog::InsertStamp( dstElement, srcElement, true );

        // now update the tree with the new one
        wxTreeItemId id = InsertChild( itemDst, newElement, true );
        //wxTreeItemId id = AddChild( itemDst, newElement );
        SelectItem( itemDst );
        Delete( itemSrc );

        break;
    }
    case CatalogDataTree_AsChild:
    {

        wxXmlNode* srcElement = GetStampNode( itemSrc );
        wxXmlNode* dstElement = GetStampNode( itemDst );

        // move the element
        // this means making a copy and deleting the old one so old pointers are
        // trash
        wxXmlNode* newElement = Catalog::MoveStamp( dstElement, srcElement );

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

void CatalogTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );
    SetNextState( itemId );
}

void CatalogTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxXmlNode* stamp = GetStampNode( itemId );
    //    wxGetApp( ).GetFrame( )->SetStamp( stamp );
    GetGeneratorData( )->GetDescriptionPanel()->SetStamp(stamp);
    event.Skip( );
}

void CatalogTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );
    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    // wxLogMessage("OnItemMenu for item \"%s\" at screen coords (%i, %i)",
    //              item ? item->GetDesc() : wxString("unknown"), screenpt.x,
    //              screenpt.y);

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

void CatalogTreeCtrl::DoTreeContextSelection( )
{
}

// void CatalogTreeCtrl::OnContextMenu( wxContextMenuEvent& event )
// {
//     wxPoint pt = event.GetPosition( );

//     int id = event.GetId( );
//     if ( id == CatalogDataTree_StructureStamps )
//     {
//         wxTreeItemId id = HitTest( pt );
//         if ( id.IsOk( ) )
//         {
//             wxXmlNode* stamp = GetStampNode( id );
//             StructureStamp( stamp );
//         }
//     }
//     else if ( id == CatalogDataTree_ResortTree )
//     {
//         ReSortTree( );
//     }

//     event.Skip( );
// }

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
 //   menu.Append( CatalogDataTree_Delete, "Delete" );


    menu.Append( CatalogDataTree_StructureStamps, "Re-Group Multiples" );
    menu.Append( CatalogDataTree_ResortTree, "Re-Sort Tree" );
    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
    case CatalogDataTree_StructureStamps:
    {
        wxXmlNode* stamp = GetStampNode( id );
        StructureStamp( stamp );
        ReSortTree( );

        wxTreeItemId newID = FindTreeItemID( stamp );
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
    default:
        // Fall through.
        break;
    }
}
void CatalogTreeCtrl::GoToColnect( wxTreeItemId id )
{
CatalogTreeItemData* data = (CatalogTreeItemData*)GetItemData(id);
    wxXmlNode* node = data->GetNodeElement();
    if ( node )
    {
        wxString nodeName = node->GetName( );
        if (!nodeName.Cmp(Catalog::CatalogBaseNames[Catalog::NT_Stamp]))
        {
            Catalog::Stamp stamp(node);
            wxString stampID = stamp.GetID();
            stampID = stampID.Trim(true);
            stampID = stampID.Trim(false);
            stampID.Replace(":","_");
            stampID.Replace(" ","_");
            if (wxTheClipboard->Open())
            {
                // This data objects are held by the clipboard,
                // so do not delete them in the app.
                wxTheClipboard->SetData( new wxTextDataObject(stampID) );
                wxTheClipboard->Close();
            }     

            wxString link = stamp.GetLink();
            wxString cmd = wxString::Format( "/usr/bin/firefox --new-tab %s", link );
            system( cmd.fn_str( ) );
        }
            
    }
}

void CatalogTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );

    event.Skip( );
}

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId CatalogTreeCtrl::InsertChild( wxTreeItemId sibling, wxXmlNode* child, bool after )
{
    //wxString stampID ;
    //wxString stampName ;
    wxString name = child->GetName( );
    Catalog::CatalogBaseType nodeType = Catalog::FindCatalogBaseType( name );
    wxString label;
    Catalog::IconID icon;

    //if the child element is not a stamp
    if ( !name.Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Stamp ] ) )
    {
        // then we add the appropriate icon and label
        Catalog::Stamp stamp( child );
        // stamp combines the stampID and its name to form a label
        label = stamp.GetLabel( );
        //stampID =  stamp.GetID();
        //bool ok = !stampID.Cmp( "5339");
        //stampName = stamp.GetName();
        icon = GetInventoryIconId( &stamp );
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


    // create the item data and add it to the tree
    CatalogTreeItemData* itemData
        = new CatalogTreeItemData( nodeType, label, child );
    wxTreeItemIdValue cookie; 
    wxTreeItemId parent = GetItemParent(sibling) ;
    wxTreeItemId  childID ;
    if ( after )
    {
        // insert after sibling
        childID = InsertItem( parent, sibling, label, icon, -1, itemData );
    } 
    else
    {
        wxTreeItemId prevSibling = GetPrevSibling ( sibling );
        if ( prevSibling.IsOk() )
        {
            childID = InsertItem( parent, prevSibling, label, icon, -1, itemData );
        }
        else
        {
           childID = InsertItem( parent, 0, label, icon, -1, itemData ) ;
        }
    }
    if ( nodeType == Catalog::NT_Stamp )
    {
        //set the icon for the appropriate state
        Utils::StampLink* stampLink = FindStampLink( childID );
        if ( stampLink )
        {
            itemData->SetStampLink( stampLink );
            //stampLink->SetCatNode( child );
            stampLink->SetCatTreeID( childID );
            SetItemState( childID, Catalog::ST_Checked );
            Catalog::Stamp stamp(child);
            stamp.SetCheckedStatus( Catalog::ST_CheckedStatusStrings[Catalog::ST_Checked]);
        }
        else
        {
            itemData->SetStampLink( 0 );
            SetItemState( childID, Catalog::ST_Unchecked );
        }
    }
    else
    { 
        // not a stamp just add the appropriate image
        SetItemImage( childID, Catalog::Icon_Folder );
        SetItemState( childID, wxTREE_ITEMSTATE_NEXT );
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

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId CatalogTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child )
{
    //wxString stampID ;
    //wxString stampName ;
    wxString name = child->GetName( );
    Catalog::CatalogBaseType nodeType = Catalog::FindCatalogBaseType( name );
    wxString label;
    Catalog::IconID icon;

    //if the child element is not a stamp
    if ( !name.Cmp( Catalog::CatalogBaseNames[ Catalog::NT_Stamp ] ) )
    {
        // then we add the appropriate icon and label
        Catalog::Stamp stamp( child );
        // stamp combines the stampID and its name to form a label
        label = stamp.GetLabel( );
        //stampID =  stamp.GetID();
        //bool ok = !stampID.Cmp( "5339");
        //stampName = stamp.GetName();
        icon = GetInventoryIconId( &stamp );
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


    // create the item data and add it to the tree
    CatalogTreeItemData* itemData
        = new CatalogTreeItemData( nodeType, label, child );
    wxTreeItemId childID = AppendItem( parent, label, icon, -1, itemData );

    if ( nodeType == Catalog::NT_Stamp )
    {
        //set the icon for the appropriate state
        Utils::StampLink* stampLink = FindStampLink( childID );
        if ( stampLink )
        {
            itemData->SetStampLink( stampLink );
            //stampLink->SetCatNode( child );
            stampLink->SetCatTreeID( childID );
            SetItemState( childID, Catalog::ST_Checked );
            Catalog::Stamp stamp(child);
            stamp.SetCheckedStatus( Catalog::ST_CheckedStatusStrings[Catalog::ST_Checked]);
        }
        else
        {
            itemData->SetStampLink( 0 );
            SetItemState( childID, Catalog::ST_Unchecked );
        }
    }
    else
    { 
        // not a stamp just add the appropriate image
        SetItemImage( childID, Catalog::Icon_Folder );
        SetItemState( childID, wxTREE_ITEMSTATE_NEXT );
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

void CatalogTreeCtrl::SortTree( wxTreeItemId parent )
{
    // decend into the tree and sort its children
    wxTreeItemIdValue cookie;
    wxTreeItemId childItem = GetFirstChild( parent, cookie );
    while ( childItem.IsOk( ) )
    {
        if ( GetChildrenCount( childItem, false ) > 1 )
        {
            // descend and do it again
            SortTree( childItem );
        }
        childItem = GetNextChild( parent, cookie );
    }
    SortChildren( parent );
}

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
    if ( attr ){
        wxString name = attr->GetName( );
        wxString value = attr->GetValue( );
        Utils::SetAttrStr( newRoot, name, value );
    }
    else
    {
        Utils::SetAttrStr( newRoot, Catalog::DT_DataNames[ Catalog::DT_Name ], "" );
    }

    Catalog::SortData( newRoot, root );
   // std::cout << "*******************************************\n";
   // Utils::XMLDumpNode( newRoot,"" );
    GetCatalogData( )->ReplaceDocument( newDoc );
    LoadTree( );
}


void CatalogTreeCtrl::ClearCatalogTree( )
{
    Utils::StampList* stampList = GetGeneratorData( )->GetStampAlbumCatalogLink( );
    stampList->ClearCatalogLinks();
    DeleteAllItems( );
}

// basic load of the tree
void CatalogTreeCtrl::LoadTree( )
{
    ClearCatalogTree( );

    wxXmlDocument* stampDoc = GetCatalogData( )->GetDoc( );
    //   XMLDump( stampDoc );
    wxXmlNode* catalogData = stampDoc->GetRoot( );
    wxString name = catalogData->GetName( );
    // Create the root item
    CatalogTreeItemData* itemData
        = new CatalogTreeItemData( Catalog::NT_Catalog, name, catalogData );
    wxTreeItemId rootID = AddRoot( name, Catalog::Icon_Folder, 1, itemData );

    wxXmlNode* child = catalogData->GetChildren( );
    while ( child )
    {
        // start adding child elementss to it.
        AddChild( rootID, child );
        child = child->GetNext( );
    }
    SortTree( GetRootItem( ) );
    ExpandAll( );

}

// this makes a list of the children stamp elements that can have childrem
wxXmlNodeArray* CatalogTreeCtrl::MakeParentList( wxXmlNode* catalogData,
    Catalog::FormatType parentType )
{
    //Catalog::Stamp parentStamp;
    wxXmlNodeArray* parentList = new wxXmlNodeArray( );
    wxXmlNode* child = catalogData->GetChildren( );
    while ( child )
    {
        Catalog::Stamp parentStamp( child );
        if ( parentStamp.GetFormat( ) == Catalog::FT_FormatStrings[ parentType ] )
        {
            parentList->push_back( child );
        }
        child = child->GetNext( );
    }
    return parentList;
}


// this is an attempt to group the stamps;
// i.e., an item of type stamp can be a child of an item SeTenent type.
void CatalogTreeCtrl::StructureStamp( wxXmlNode* catalogData )
{
    StructureCatalogData( catalogData, Catalog::FT_Se_tenant, Catalog::FT_Stamp );
    StructureCatalogData( catalogData, Catalog::FT_Stamp_with_Attached_Label, Catalog::FT_Stamp );
    StructureCatalogData( catalogData, Catalog::FT_Gutter_Pair, Catalog::FT_Stamp );
    StructureCatalogData( catalogData, Catalog::FT_Booklet_Pane, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Souvenir_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Mini_Sheet, Catalog::FT_Stamp, Catalog::FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Booklet, Catalog::FT_Stamp, Catalog::FT_Booklet_Pane );
    SortTree( GetRootItem( ) );
}

void CatalogTreeCtrl::StructureCatalogData( wxXmlNode* catalogData,
    Catalog::FormatType parentType,
    Catalog::FormatType childType,
    Catalog::FormatType secondChildType )
{
   // Catalog::Stamp childStamp;
   // Catalog::Stamp parentStamp;
 
    // Make a list of all nodes that are of parentType
    wxXmlNodeArray* parentList = MakeParentList( catalogData, parentType );
    // now find all the stamps that go into each parent by comparing the issue date, series and face value
    for ( int i = 0; i < parentList->size( ); i++ )
    {
        wxXmlNode* parentNode = ( wxXmlNode* )parentList->at( i );
        Catalog::Stamp* parentStamp = new Catalog::Stamp( parentNode );
        wxString parentIssue = parentStamp->GetIssuedDate( );
        wxString parentSeries = parentStamp->GetSeries( );
        wxString parentFace = parentStamp->GetFaceValue( );
        long nbrStamps;
        parentFace.ToLong( &nbrStamps );
        if ( nbrStamps <= 0 )
        {
            // if we can't figure out the face then assume a setenant is no bigger than 50 stamps
            nbrStamps = 50;
        }
        long count = 0;
        long searchRange = 0;

        wxXmlNode* childNode = catalogData->GetChildren( );

        while ( childNode && ( searchRange < 105 ) && ( count < nbrStamps ) )
        {
            Catalog::Stamp* childStamp = new Catalog::Stamp( childNode );

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
                wxString format = childStamp->GetFormat( );
                    if ( ( format == Catalog::FT_FormatStrings[ childType ] )
                    || ( secondChildType
                            && ( format == Catalog::FT_FormatStrings[ secondChildType ] ) ) )
                {
                    wxString issue = childStamp->GetIssuedDate( );
                    wxString series = childStamp->GetSeries( );
                    // if the issue date and the series match the parent assume
                    // that the childNode goes in the parent
                    if ( !issue.Cmp( parentIssue )
                        && !series.Cmp( parentSeries ) )
                    {
                        count++;
                        //catalogData->RemoveChild( childNode );
                        wxXmlNode* currParent = childNode->GetParent( );
                        if ( currParent )
                        {
                            currParent->RemoveChild( childNode );
                        }
                        parentNode->AddChild( childNode );
                    }
                }
            }
            childNode = nextSibling;
        }
    }
}

bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
{
    if ( !item.IsOk() )
    {
        return false;
    }

    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( item );
    wxXmlNode* dataEle = data->GetNodeElement( );
    if ( dataEle == ele )
    {
        return false;
    }
    return true;

    
}

bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxString stampID )
{
    if ( item.IsOk() )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( item );
        wxXmlNode* dataEle = data->GetNodeElement( );
        wxString id = dataEle->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
        if ( stampID.Cmp( id ) )
        {
            return false;
        }
    }
    return true;
}

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxXmlNode* ele, wxTreeItemId id )
{
    if ( id.IsOk() )
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


wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxString stampID, wxTreeItemId id )
{
    if ( id.IsOk() )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child )
        {
            if ( IsElement( child, stampID ) )
            {
                return child;
            }
            if ( this->HasChildren( child ) )
            {
                wxTreeItemId idFound = FindTreeItemID( stampID, child );
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

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxXmlNode* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxString stampID )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( stampID, root );
}

wxTreeItemId CatalogTreeCtrl::FindFirstStampChild( wxTreeItemId id )
{
    if ( id.IsOk() )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( id, cookie );
    while ( child )
    {
            CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( child );
            if ( data->GetType( ) == Catalog::NT_Stamp )
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
    }
    return 0;
}

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

void CatalogTreeCtrl::EnableState( wxTreeItemId id )
{
    if ( id.IsOk() )
    {
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
        if ( data->GetType( ) == Catalog::NT_Stamp )
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

void CatalogTreeCtrl::DisableState( wxTreeItemId id )
{
    if ( id.IsOk() )
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