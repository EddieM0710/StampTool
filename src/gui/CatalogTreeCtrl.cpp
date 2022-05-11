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
#include "gui/AlbumTreeCtrl.h"

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
EVT_CONTEXT_MENU( CatalogTreeCtrl::OnContextMenu )
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
    CreateStateImageList(false);

}

void CatalogTreeCtrl::CreateImageList( )
{
    AssignImageList( CreateCatalogImageList() );
}
void CatalogTreeCtrl::CreateStateImageList(bool del)
{
    AssignStateImageList(CreateCatalogStateImageList( del) );
}

int CatalogTreeCtrl::OnCompareItems( const wxTreeItemId& item1,
    const wxTreeItemId& item2 )
{
    CatalogDataTreeItemData* itemData1 = ( CatalogDataTreeItemData* )GetItemData( item1 );
    Catalog::CatalogNodeType type1 = itemData1->GetType( );

    CatalogDataTreeItemData* itemData2 = ( CatalogDataTreeItemData* )GetItemData( item2 );
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


void CatalogTreeCtrl::AppendAlbumStamp( wxTreeItemId itemId )
{
    Utils::StampLink* link = GetAlbumTreeCtrl()->AppendStamp( itemId );
    if ( link )
    {
        wxXmlNode* element = GetStampNode( itemId);
        link->SetCatStamp( element );
        link->SetCatTreeID( itemId );
    }
}

wxXmlNode* CatalogTreeCtrl::GetStampNode(wxTreeItemId itemId)
{
        CatalogDataTreeItemData* data = ( CatalogDataTreeItemData* )GetItemData( itemId );
        wxXmlNode* element = data->GetNodeElement();
}

wxString CatalogTreeCtrl::GetStampID(wxTreeItemId itemId)
{
    wxXmlNode* element = GetStampNode( itemId);
    return element->GetAttribute(Catalog::DT_XMLDataNames[Catalog::DT_ID_Nbr]);
}

Utils::StampLink* CatalogTreeCtrl::GetStampLink(wxTreeItemId itemId)
{
    wxString id = GetStampID( itemId);
    Utils::StampList& stampList = GetGeneratorData()->GetStampAlbumCatalogLink();
    Utils::StampLink* stampLink = stampList.GetStampLink( id );
    return stampLink;
}

void CatalogTreeCtrl::DeleteAlbumStamp(wxTreeItemId itemId)
{
    Utils::StampLink* stampLink = GetStampLink( itemId);
    if ( stampLink )
    {
        wxTreeItemId itemID = stampLink->GetAlbumtTreeID();
        if ( itemID.IsOk() ) GetAlbumTreeCtrl()->DeleteItem( itemID );
    }
}

void CatalogTreeCtrl::SetNextState( const wxTreeItemId& itemId )
{
    wxXmlNode* element = GetStampNode( itemId );
    Catalog::Stamp* stamp = new Catalog::Stamp( element );
    if ( stamp->IsOK( ) )
    {
        int status = stamp->GetStatusType( );
        status++;
        if ( status >= Catalog::ST_NbrTypes )
        {
            status = 0;
        }
        stamp->SetStatusType( ( Catalog::StatusType )status );
        wxGetApp( ).GetFrame( )->UpdateStatus( );
        SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
        int state = GetItemState(itemId);
        if( state )
        {
            AppendAlbumStamp(itemId);
        }
        else
        {
            DeleteAlbumStamp(itemId);
        }
   }
}

IconID CatalogTreeCtrl::GetIconId( Catalog::Stamp* stamp )
{
    int format = stamp->GetFormatType( );
    return CatalogImageSelection[ format ][ 0 ];
}

void CatalogTreeCtrl::SetStatusImage( )
{
    // wxTreeItemId itemId = GetFocusedItem( );
    // CatalogDataTreeItemData* item = ( CatalogDataTreeItemData* )GetItemData( itemId );
    // wxXmlNode* element = item->GetNodeElement( );
    // Stamp* stamp = new Stamp( element );
    // if ( stamp->IsOK( ) )
    // {
    //     int status = stamp->GetStatusType( );
    //     int format = stamp->GetFormatType( );
    //     IconID iconID = ImageSelection[ format ][ status ];
    //     SetItemState( itemId, GetIconId( stamp ) );
    // }
}

void CatalogTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item )  << '"';
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

    event.Skip( );
}

void CatalogTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    CatalogDataTreeItemData* item = ( CatalogDataTreeItemData* )GetItemData( itemId );
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

void CatalogTreeCtrl::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint pt = event.GetPosition( );

    int id = event.GetId( );
    if ( id == CatalogDataTree_StructureStamps )
    {
        wxTreeItemId id = HitTest( pt );
        if ( id.IsOk( ) )
        {
            wxXmlNode* stamp = GetStampNode( id );
            StructureStamp( stamp );
        }
    }
    else if ( id == CatalogDataTree_ResortTree )
    {
        ReSortTree( );
    }

    event.Skip( );
}

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

    menu.Append( CatalogDataTree_StructureStamps, "Re-Group Multiples" );
    menu.Append( CatalogDataTree_ResortTree, "Re-Sort Tree" );
    switch ( GetPopupMenuSelectionFromUser( menu ) )
    {
    case CatalogDataTree_StructureStamps:
    {
        wxXmlNode* stamp =GetStampNode( id );
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
    default:
        // Fall through.
        break;
    }
}

void CatalogTreeCtrl::OnItemRClick( wxTreeEvent& event )
{
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    CatalogDataTreeItemData* item = ( CatalogDataTreeItemData* )GetItemData( itemId );

    event.Skip( );
}

// AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
// create sort nodes as necessary to find the proper place for the child
wxTreeItemId CatalogTreeCtrl::AddChild( wxTreeItemId parent, wxXmlNode* child )
{
    wxString name = child->GetName( );
    Catalog::CatalogNodeType nodeType = Catalog::FindCatalogNodeType( name );
    wxString label;
    IconID icon;

    //if the child element is not a stamp
    if ( !name.Cmp( Catalog::CatalogNodeNames[Catalog:: NT_Stamp ] ) )
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
            icon = Icon_Folder;        
        }
    }

 
    // create the item data and add it to the tree
    CatalogDataTreeItemData* itemData
        = new CatalogDataTreeItemData( nodeType, label, child );
    wxTreeItemId childID = AppendItem( parent, label, icon, 1, itemData );

    if ( nodeType == Catalog::NT_Stamp )
    {
        //set the icon for the appropriate state
        Utils::StampLink* stampLink = GetStampLink( childID );
        if ( stampLink )
        {
            stampLink->SetCatStamp(child); 
            stampLink->SetCatTreeID( childID );
            SetItemState(childID, 1);  
        }
        else 
        {
            SetItemState(childID, 0);  
        }
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

void CatalogTreeCtrl::SortTree( wxTreeItemId parent )
{
    // decend into the tree and sort its children
    wxTreeItemIdValue cookie;
    wxTreeItemId childItem = GetFirstChild( parent, cookie );
    while ( childItem.IsOk( ) )
    {
        if ( GetChildrenCount( childItem, false ) > 1 )
        {
            // decend and do it again
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

    DeleteAllItems( );

    wxXmlDocument* newDoc = new wxXmlDocument( );
    wxXmlNode* newRoot = newDoc->GetRoot();
    if ( !newRoot )
    {
        newRoot = Utils::NewNode( newDoc, Catalog::CatalogNodeNames[ Catalog::NT_Catalog ] );
    }
    //newDoc->SetRoot( newRoot );

    Catalog::CatalogData* catalogData = GetCatalogData( );
    wxXmlDocument* doc = catalogData->GetDoc( );
    wxXmlNode* root = doc->GetRoot( );

    wxXmlAttribute* attr = Utils::GetAttribute( root, Catalog::DT_DataNames[Catalog::DT_Name] );
    if ( attr ){
        wxString name = attr->GetName( );
        wxString value = attr->GetValue( );
        Utils::SetAttrStr( newRoot, name, value );
    }
    else
    {
        Utils::SetAttrStr( newRoot, Catalog::DT_DataNames[Catalog::DT_Name], "" );
    }
   
    Catalog::SortData( newRoot, root );
    GetCatalogData( )->ReplaceDocument( newDoc );
    LoadTree( );
}

// basic load of the tree
void CatalogTreeCtrl::LoadTree( )
{
    wxXmlDocument* stampDoc = GetCatalogData( )->GetDoc( );
 //   XMLDump( stampDoc );
    wxXmlNode* catalogData = stampDoc->GetRoot( );
    wxString name = catalogData->GetName( );
    // Create the root item
    CatalogDataTreeItemData* itemData
        = new CatalogDataTreeItemData( Catalog::NT_Catalog, name, catalogData );
    wxTreeItemId rootID = AddRoot( name, Icon_Folder, 1, itemData );

    wxXmlNode* child = catalogData->GetChildren( );
    while ( child )
    {
        // start adding child elementss to it.
        AddChild( rootID, child );
        child = child->GetNext( );
    }
    SortTree( GetRootItem( ) );
}

// this makes a list of the children stamp elements that can have childrem
wxArrayPtrVoid* CatalogTreeCtrl::MakeParentList( wxXmlNode* catalogData,
    Catalog::FormatType parentType )
{
    Catalog::Stamp parentStamp;
    wxArrayPtrVoid* parentList = new wxArrayPtrVoid( );
    wxXmlNode* child = catalogData->GetChildren( );
    while ( child )
    {
        parentStamp.SetNodeElement( child );
        if ( parentStamp.GetFormat( ) == Catalog::FT_FormatStrings[ parentType ] )
        {
            parentList->Add( ( void* )child );
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
    StructureCatalogData( catalogData, Catalog::FT_Mini_Sheet, Catalog::FT_Stamp,Catalog:: FT_Se_tenant );
    StructureCatalogData( catalogData, Catalog::FT_Booklet, Catalog::FT_Stamp, Catalog::FT_Booklet_Pane );
    SortTree( GetRootItem( ) );
}

void CatalogTreeCtrl::StructureCatalogData( wxXmlNode* catalogData,
    Catalog::FormatType parentType,
    Catalog::FormatType childType,
    Catalog::FormatType secondChildType )
{
    Catalog::Stamp childTypeStamp;
    Catalog::Stamp parentTypeStamp;

    // Make a list of all nodes that are of parentType
    wxArrayPtrVoid* parentTypeList = MakeParentList( catalogData, parentType );
    wxXmlNode* child = catalogData->GetChildren( );
    wxXmlNode* start = child;
    // now find all the stamps that go into each parent by comparing the issue date, series and face value
    for ( int i = 0; i < parentTypeList->GetCount( ); i++ )
    {
        wxXmlNode* parentTypeElement = ( wxXmlNode* )parentTypeList->Item( i );
        parentTypeStamp.SetNodeElement( parentTypeElement );
        wxString parentIssue = parentTypeStamp.GetIssuedDate( );
        wxString parentSeries = parentTypeStamp.GetSeries( );
        wxString parentFace = parentTypeStamp.GetFaceValue( );
        long nbrStamps;
        parentFace.ToLong( &nbrStamps );
        if ( nbrStamps <= 0 )
        {
            // if we can't figure out the face then assume a setenant is no bigger than 50 stamps
            nbrStamps = 50;
        }
        long count = 0;
        long searchRange = 0;
        wxXmlNode* child = start;
        ;
        while ( child && ( searchRange < 105 ) && ( count < nbrStamps ) )
        {
            childTypeStamp.SetNodeElement( child );

            // figure out what the next sibling is because we may move child
            wxXmlNode* nextSibling = child->GetNext( );

            if ( parentTypeElement != child )
            {
                // only search a reasonable distance after the first one is found
                if ( count > 1 )
                {
                    searchRange++;
                }
                // only look at children of childType
                wxString format = childTypeStamp.GetFormat( );
                if ( ( format == Catalog::FT_FormatStrings[ childType ] )
                    || ( secondChildType
                        && ( format == Catalog::FT_FormatStrings[ secondChildType ] ) ) )
                {
                    wxString issue = childTypeStamp.GetIssuedDate( );
                    wxString series = childTypeStamp.GetSeries( );
                    // if the issue date and the series match the parent assume
                    // that the child goes in the parent
                    if ( !issue.Cmp( parentIssue )
                        && !series.Cmp( parentSeries ) )
                    {
                        count++;
                        wxXmlNode* currParent = child->GetParent();
                        if (currParent )
                        {
                            currParent->RemoveChild(child);
                        }
                        parentTypeElement->AddChild( child );
                        

                        // this is a hack so the loop doesn't start at the beginning
                        // next time.
                        //                    start = child;
                    }
                }
            }
            child = nextSibling;
        }
    }
}

bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
{
    CatalogDataTreeItemData* data = ( CatalogDataTreeItemData* )GetItemData( item );
    wxXmlNode* dataEle = data->GetNodeElement( );
    if ( dataEle == ele )
    {
        return false;
    }
    return true;
}

bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxString stampID )
{
    CatalogDataTreeItemData* data = ( CatalogDataTreeItemData* )GetItemData( item );
    wxXmlNode* dataEle = data->GetNodeElement( );
    wxString id = dataEle->GetAttribute(Catalog::DT_XMLDataNames[Catalog::DT_ID_Nbr]);
    if ( stampID.Cmp( id ) )
    {
        return false;
    }
    return true;
}

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxXmlNode* ele, wxTreeItemId id )

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
        child = this->GetNextChild( child, cookie );
    }
    return 0;
}


wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxString stampID, wxTreeItemId id )

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
        child = this->GetNextChild( child, cookie );
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
    wxTreeItemIdValue cookie;
    wxTreeItemId child = GetFirstChild( id, cookie );
    while ( child )
    {
        CatalogDataTreeItemData* data = ( CatalogDataTreeItemData* )GetItemData( child );
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
        child = GetNextChild( child, cookie );
    }
    return 0;
}
