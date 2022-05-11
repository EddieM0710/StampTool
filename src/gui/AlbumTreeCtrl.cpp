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

#include "catalog/CatalogCode.h"
#include "catalog/Classification.h"
#include "utils/Project.h"
#include "catalog/Specimen.h"
#include "catalog/Stamp.h"
#include "catalog/CatalogData.h"
#include "AlbumGenApp.h"
#include "gui/AlbumGenFrame.h"
#include "gui/AlbumTreeCtrl.h"
#include "utils/XMLUtilities.h"

#include "art/StampBlack.xpm"
#include "art/StampBlue.xpm"
#include "art/StampBrown.xpm"
#include "art/StampGreen.xpm"
#include "art/StampPurple.xpm"
#include "art/StampRed.xpm"
#include "art/StampYellow.xpm"

#include "art/StampBlackBlock.xpm"
#include "art/StampBlueBlock.xpm"
#include "art/StampBrownBlock.xpm"
#include "art/StampGreenBlock.xpm"
#include "art/StampPurpleBlock.xpm"
#include "art/StampRedBlock.xpm"
#include "art/StampYellowBlock.xpm"

#include "art/StampBlackMiniSheet.xpm"
#include "art/StampBlueMiniSheet.xpm"
#include "art/StampBrownMiniSheet.xpm"
#include "art/StampGreenMiniSheet.xpm"
#include "art/StampPurpleMiniSheet.xpm"
#include "art/StampRedMiniSheet.xpm"
#include "art/StampYellowMiniSheet.xpm"

#include "art/StampBlackSouvenirSheet.xpm"
#include "art/StampBlueSouvenirSheet.xpm"
#include "art/StampBrownSouvenirSheet.xpm"
#include "art/StampGreenSouvenirSheet.xpm"
#include "art/StampPurpleSouvenirSheet.xpm"
#include "art/StampRedSouvenirSheet.xpm"
#include "art/StampYellowSouvenirSheet.xpm"
#include "art/folder.xpm"

#include "art/unchecked.xpm"
#include "art/checked.xpm"

IconID AlbumImageSelection[ Catalog::FT_NbrTypes ][ 2 ] = {
    { Icon_Stamp, Icon_StampSelected }, //   FT_FormatUnknown = 0,
    { Icon_Stamp, Icon_StampSelected }, //   FT_Stamp,
    { Icon_StampBlock, Icon_StampBlockSelected }, //   FT_Se_tenant,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Mini_Sheet,
    { Icon_StampSouvenirSheet, Icon_StampSouvenirSheetSelected }, //   FT_Souvenir_Sheet,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Booklet,
    { Icon_StampMiniSheet, Icon_StampMiniSheetSelected }, //   FT_Booklet_Pane,
    { Icon_StampBlock, Icon_StampBlockSelected }, //   FT_Gutter_Pair,
    { Icon_StampSouvenirSheet, Icon_StampSouvenirSheetSelected }, //    FT_Stamp_with_Attached_Label,
    { Icon_StampBlock, Icon_StampBlockSelected } }; //   FT_Tete_Beche,

/*
 * AlbumGenFrame type definition
 */

IMPLEMENT_CLASS( AlbumTreeCtrl, wxTreeCtrl );

wxDECLARE_APP( AlbumGenApp );

wxBEGIN_EVENT_TABLE( AlbumTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( CatalogDataTree_Ctrl, AlbumTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( CatalogDataTree_Ctrl, AlbumTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( CatalogDataTree_Ctrl, AlbumTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( CatalogDataTree_Ctrl, AlbumTreeCtrl::OnItemStateClick )
EVT_CONTEXT_MENU( AlbumTreeCtrl::OnContextMenu )
// EVT_TREE_ITEM_MENU is the preferred event for creating context menus
// on a tree control, because it includes the point of the click or item,
// meaning that no additional placement calculations are required.
EVT_TREE_ITEM_MENU( CatalogDataTree_Ctrl, AlbumTreeCtrl::OnItemMenu )
EVT_TREE_ITEM_RIGHT_CLICK( CatalogDataTree_Ctrl, AlbumTreeCtrl::OnItemRClick )

wxEND_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

// AlbumTreeCtrl implementation

AlbumTreeCtrl::AlbumTreeCtrl( wxWindow* parent, const wxWindowID id,
    const wxPoint& pos, const wxSize& size,
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )

{
    m_reverseSort = true;

    CreateImageList( );
    CreateStateImageList(false);

}

void AlbumTreeCtrl::CreateImageList( )
{
    wxImageList* images;
    wxBusyCursor wait;

    wxIcon icons[ 9 ];

    icons[ Icon_StampSelected ] = wxIcon( StampRed );
    icons[ Icon_Stamp ] = wxIcon( StampBlue );
    icons[ Icon_StampBlockSelected ] = wxIcon( StampRedBlock );
    icons[ Icon_StampBlock ] = wxIcon( StampBlueBlock );
    icons[ Icon_StampMiniSheetSelected ] = wxIcon( MiniSheetRed );
    icons[ Icon_StampMiniSheet ] = wxIcon( MiniSheetBlue );
    icons[ Icon_StampSouvenirSheetSelected ] = wxIcon( SouvenirSheetRed );
    icons[ Icon_StampSouvenirSheet ] = wxIcon( SouvenirSheetBlue );
    icons[ Icon_Folder ] = wxIcon( folder_xpm );

    int width = icons[ 0 ].GetWidth( ), height = icons[ 0 ].GetHeight( );

    // Make an state image list containing small icons
    images = new wxImageList( width, height, true );

    for ( size_t i = 0; i < WXSIZEOF( icons ); i++ )
    {
        images->Add( icons[ i ] );
    }

    AssignImageList( images );
 }
void AlbumTreeCtrl::CreateStateImageList(bool del)
{


    wxImageList *states;
    wxBusyCursor wait;

  
        wxIcon icons[2];
        icons[0] = wxIcon(unchecked_xpm);
        icons[1] = wxIcon(checked_xpm);

        int width  = icons[0].GetWidth();
        int height = icons[0].GetHeight();

        // Make an state image list containing small icons
        states = new wxImageList(width, height, true);

        for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
            states->Add(icons[i]);
    

    AssignStateImageList(states);
}

int AlbumTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    AlbumTreeItemData* itemData1 = ( AlbumTreeItemData* )GetItemData( item1 );
    Catalog::CatalogNodeType type1 = itemData1->GetType( );

    AlbumTreeItemData* itemData2 = ( AlbumTreeItemData* )GetItemData( item2 );
     Catalog::CatalogNodeType type2 = itemData2->GetType( );

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

 void AlbumTreeCtrl::SetNextState( const wxTreeItemId& itemId )
 {
//     AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemId );
//     wxXmlNode* element = item->GetElement( );
//     Stamp* stamp = new Stamp( element );
//     if ( stamp->IsOK( ) )
//     {
//         int status = stamp->GetStatusType( );
//         status++;
//         if ( status >= ST_NbrTypes )
//         {
//             status = 0;
//         }
//         stamp->SetStatusType( ( StatusType )status );
//         wxGetApp( ).GetFrame( )->UpdateStatus( );
         SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
//     }
 }

IconID AlbumTreeCtrl::GetIconId(  Catalog::Stamp* stamp )
{
    int format = stamp->GetFormatType( );
    return AlbumImageSelection[ format ][ 0 ];
}

void AlbumTreeCtrl::SetStatusImage( )
{
     wxTreeItemId itemId = GetFocusedItem( );
    // AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemId );
    // wxXmlNode* element = item->GetElement( );
    // Stamp* stamp = new Stamp( element );
    // if ( stamp->IsOK( ) )
    // {
    //     int status = stamp->GetStatusType( );
    //     int format = stamp->GetFormatType( );
    //     IconID iconID = AlbumImageSelection[ format ][ status ];
    //     SetItemState( itemId, GetIconId( stamp ) );
    // }
}

void AlbumTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item )  << '"';
    else
        text = "invalid item";
}

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

void AlbumTreeCtrl::OnEndDrag( wxTreeEvent& event )
{
    wxTreeItemId itemSrc = m_draggedItem, itemDst = event.GetItem( );
    m_draggedItem = ( wxTreeItemId )0l;

    if ( itemSrc == itemDst )
    {
        return;
    }

    if ( !itemDst.IsOk( ) )
    {
        return;
    }

    AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemSrc );
    wxXmlNode* srcElement = item->GetElement( );
    item = ( AlbumTreeItemData* )GetItemData( itemDst );
    wxXmlNode* dstElement = item->GetElement( );

    // move the element
    // this means making a copy and deleting the old one so old pointers are
    // trash
    wxXmlNode* newElement = Catalog::MoveStamp( dstElement, srcElement );

    // now update the tree with the new one
    wxTreeItemId id = AddChild( itemDst, newElement );
    SelectItem( itemDst );
    Delete( itemSrc );
}

void AlbumTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );

    SetNextState( itemId );
}

void AlbumTreeCtrl::OnSelChanged( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemId );
    wxXmlNode* stamp = item->GetElement( );
    wxGetApp( ).GetFrame( )->SetStamp( stamp );

    event.Skip( );
}

void AlbumTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemId );
    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    // wxLogMessage("OnItemMenu for item \"%s\" at screen coords (%i, %i)",
    //              item ? item->GetDesc() : wxString("unknown"), screenpt.x,
    //              screenpt.y);

    ShowMenu( itemId, clientpt );
    event.Skip( );
}

void AlbumTreeCtrl::DoTreeContextSelection( )
{
}

void AlbumTreeCtrl::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint pt = event.GetPosition( );

    int id = event.GetId( );
    // if ( id == CatalogDataTree_StructureStamps )
    // {
    //     wxTreeItemId id = HitTest( pt );
    //     if ( id.IsOk( ) )
    //     {
    //         AlbumTreeItemData* data = ( AlbumTreeItemData* )GetItemData( id );
    //         wxXmlNode* stamp = data->GetElement( );
    //         StructureStamp( stamp );
    //     }
    // }
    // else if ( id == CatalogDataTree_ResortTree )
    // {
    //     ReSortTree( );
    // }

    event.Skip( );
}

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

    wxMenu menu( title );
    menu.Append( CatalogDataTree_About, "&About" );
    menu.AppendSeparator( );

    menu.Append( CatalogDataTree_StructureStamps, "Re-Group Multiples" );
    menu.Append( CatalogDataTree_ResortTree, "Re-Sort Tree" );
    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
    // case CatalogDataTree_StructureStamps:
    // {
    //     AlbumTreeItemData* data = ( AlbumTreeItemData* )GetItemData( id );
    //     wxXmlNode* stamp = data->GetElement( );
    //     StructureStamp( stamp );
    //     ReSortTree( );

    //     wxTreeItemId newID = FindTreeItemID( stamp );
    //     if ( newID )
    //     {
    //         Expand( newID );
    //         SelectItem( newID );
    //     }
    //     break;
    // }
    // case CatalogDataTree_ResortTree:
    // {
    //     ReSortTree( );
    //     break;
    // }
    default:
        // Fall through.
        break;
    }
}

void AlbumTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    AlbumTreeItemData* item = ( AlbumTreeItemData* )GetItemData( itemId );

    event.Skip( );
}

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId AlbumTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child )
{
    wxString name = child->GetName( );
     Catalog::CatalogNodeType nodeType = Catalog::FindCatalogNodeType( name );
    wxString label;
    IconID icon;

    //if the child element is not a stamp
    if ( !name.Cmp(  Catalog::CatalogNodeNames[  Catalog::NT_Stamp ] ) )
    {
        // then we add the appropriate icon and label
         Catalog::Stamp stamp( child );
        // stamp combines the stampID and its name to form a label
        label = stamp.GetLabel( );
        icon = GetIconId( &stamp );
    }
    else
    {
        // if it is a specimen or catalog code return because 
        // they don't go in the tree.
        if ( ( nodeType ==  Catalog::NT_Specimen )
        || ( nodeType ==  Catalog::NT_CatalogCode ) )
        {
            return 0;
        }
        else
        {
            //otherwise get the label
            const wxXmlAttribute* attr = Utils::GetAttribute( child, "Name" );
            label = attr->GetValue( );
            icon = Icon_Folder;        }
    }

 
    // create the item data and add it to the tree
    AlbumTreeItemData* itemData
        = new AlbumTreeItemData( nodeType, label, child );
    wxTreeItemId childID = AppendItem( parent, label, icon, 1, itemData );

    if ( nodeType ==  Catalog::NT_Stamp )
    {
        //set the icon for the appropriate state
        SetItemImage( childID,  icon );
        SetItemState(childID, 0);    
    }
    else
    { 
        // not a stamp just add the appropriate image
        SetItemImage( childID, Icon_Folder );
        SetItemState(childID, wxTREE_ITEMSTATE_NEXT);   
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

// void AlbumTreeCtrl::SortTree( wxTreeItemId parent )
// {
//     // decend into the tree and sort its children
//     wxTreeItemIdValue cookie;
//     wxTreeItemId childItem = GetFirstChild( parent, cookie );
//     while ( childItem.IsOk( ) )
//     {
//         if ( GetChildrenCount( childItem, false ) > 1 )
//         {
//             // decend and do it again
//             SortTree( childItem );
//         }
//         childItem = GetNextChild( parent, cookie );
//     }
//     SortChildren( parent );
// }

// //Delete the tree and resort it with the new sort order data.
// // Probably doint this because the sort order was changed.
// void AlbumTreeCtrl::ReSortTree( )
// {
//     CatalogData* catalogData = GetCatalogData( );
//     wxXmlDocument* doc = catalogData->GetDoc( );
//     wxXmlNode* root = doc->GetRoot( );

//     DeleteAllItems( );

//     wxXmlDocument* newDoc = new wxXmlDocument( );
//     wxXmlNode* newRoot = newDoc->NewNode( CatalogNodeNames[ NT_Catalog ] );
//     const wxXmlAttribute* attr = root->GetAttribute( DT_DataNames[DT_Name] );
//     if ( attr ){
//         const char* name = attr->GetName( );
//         const char* value = attr->GetValue( );
//         newRoot->SetAttribute( name, value );
//         newDoc->InsertFirstChild( newRoot );
//     }
//     else
//     {
//         newRoot->SetAttribute( DT_DataNames[DT_Name], "" );
//         newDoc->InsertFirstChild( newRoot );
//     }


//     SortData( newRoot, root );
//     GetCatalogData( )->ReplaceDocument( newDoc );
//     LoadTree( );
// }

// basic load of the tree
void AlbumTreeCtrl::LoadTree( )
{
    wxXmlDocument* stampDoc = GetProject()->GetCatalogData( )->GetDoc( );
    wxXmlNode* catalogData = stampDoc->GetRoot( );
    wxString name = catalogData->GetName( );
    // Create the root item
    AlbumTreeItemData* itemData
        = new AlbumTreeItemData(  Catalog::NT_Catalog, name, catalogData );
    wxTreeItemId rootID = AddRoot( name, Icon_Folder, 1, itemData );

    wxXmlNode* child = catalogData->GetChildren( );
    while ( child )
    {
        // start adding child elementss to it.
        AddChild( rootID, child );
        child = child->GetNext( );
    }
 //   SortTree( GetRootItem( ) );
}

// this makes a list of the children stamp elements that can have childrem
wxArrayPtrVoid* AlbumTreeCtrl::MakeParentList( wxXmlNode* catalogData,
    Catalog::FormatType parentType )
{
     Catalog::Stamp parentStamp;
    wxArrayPtrVoid* parentList = new wxArrayPtrVoid( );
    wxXmlNode* child = catalogData->GetChildren( );
    while ( child )
    {
        parentStamp.SetElement( child );
        if ( parentStamp.GetFormat( ) ==  Catalog::FT_FormatStrings[ parentType ] )
        {
            parentList->Add( ( void* )child );
        }
        child = child->GetNext( );
    }
    return parentList;
}


// // this is an attempt to group the stamps;
// // i.e., an item of type stamp can be a child of an item SeTenent type.
// void AlbumTreeCtrl::StructureStamp( wxXmlNode* catalogData )
// {
//     StructureCatalogData( catalogData, FT_Se_tenant, FT_Stamp );
//     StructureCatalogData( catalogData, FT_Stamp_with_Attached_Label, FT_Stamp );
//     StructureCatalogData( catalogData, FT_Gutter_Pair, FT_Stamp );
//     StructureCatalogData( catalogData, FT_Booklet_Pane, FT_Stamp, FT_Se_tenant );
//     StructureCatalogData( catalogData, FT_Mini_Sheet, FT_Stamp, FT_Se_tenant );
//     StructureCatalogData( catalogData, FT_Souvenir_Sheet, FT_Stamp, FT_Se_tenant );
//     StructureCatalogData( catalogData, FT_Mini_Sheet, FT_Stamp, FT_Se_tenant );
//     StructureCatalogData( catalogData, FT_Booklet, FT_Stamp, FT_Booklet_Pane );
//     SortTree( GetRootItem( ) );
// }

// void AlbumTreeCtrl::StructureCatalogData( wxXmlNode* catalogData,
//     FormatType parentType,
//     FormatType childType,
//     FormatType secondChildType )
// {
//     Stamp childTypeStamp;
//     Stamp parentTypeStamp;

//     // Make a list of all nodes that are of parentType
//     wxArrayPtrVoid* parentTypeList = MakeParentList( catalogData, parentType );
//     wxXmlNode* child = catalogData->FirstChildElement( );
//     wxXmlNode* start = child;
//     // now find all the stamps that go into each parent by comparing the issue date, series and face value
//     for ( int i = 0; i < parentTypeList->GetCount( ); i++ )
//     {
//         wxXmlNode* parentTypeElement = ( wxXmlNode* )parentTypeList->Item( i );
//         parentTypeStamp.SetElement( parentTypeElement );
//         wxString parentIssue = parentTypeStamp.GetIssuedDate( );
//         wxString parentSeries = parentTypeStamp.GetSeries( );
//         wxString parentFace = parentTypeStamp.GetFaceValue( );
//         long nbrStamps;
//         parentFace.ToLong( &nbrStamps );
//         if ( nbrStamps <= 0 )
//         {
//             // if we can't figure out the face then assume a setenant is no bigger than 50 stamps
//             nbrStamps = 50;
//         }
//         long count = 0;
//         long searchRange = 0;
//         wxXmlNode* child = start;
//         ;
//         while ( child && ( searchRange < 105 ) && ( count < nbrStamps ) )
//         {
//             childTypeStamp.SetElement( child );

//             // figure out what the next sibling is because we may move child
//             wxXmlNode* nextSibling = child->GetNext( );

//             // only search a reasonable distance after the first one is found
//             if ( count > 1 )
//             {
//                 searchRange++;
//             }
//             // only look at children of childType
//             wxString format = childTypeStamp.GetFormat( );
//             if ( ( format == FT_FormatStrings[ childType ] )
//                 || ( secondChildType
//                     && ( format == FT_FormatStrings[ secondChildType ] ) ) )
//             {
//                 wxString issue = childTypeStamp.GetIssuedDate( );
//                 wxString series = childTypeStamp.GetSeries( );
//                 // if the issue date and the series match the parent assume
//                 // that the child goes in the parent
//                 if ( !issue.Cmp( parentIssue )
//                     && !series.Cmp( parentSeries ) )
//                 {
//                     count++;
//                     parentTypeElement->AddChild( child );
//                     // this is a hack so the loop doesn't start at the beginning
//                     // next time.
//                     //                    start = child;
//                 }
//             }
//             child = nextSibling;
//         }
//     }
// }

bool AlbumTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
{
    AlbumTreeItemData* data = ( AlbumTreeItemData* )GetItemData( item );
    wxXmlNode* dataEle = data->GetElement( );
    if ( dataEle == ele )
    {
        return false;
    }
    return true;
}
wxTreeItemId AlbumTreeCtrl::FindTreeItemID( wxXmlNode* ele, wxTreeItemId id )

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
wxTreeItemId AlbumTreeCtrl::FindTreeItemID( wxXmlNode* ele )
{
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

wxTreeItemId AlbumTreeCtrl::FindFirstStampChild( wxTreeItemId id )
{
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( id, cookie );
    while ( child )
    {
        AlbumTreeItemData* data = ( AlbumTreeItemData* )GetItemData( child );
        if ( data->GetType( ) ==  Catalog::NT_Stamp )
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
