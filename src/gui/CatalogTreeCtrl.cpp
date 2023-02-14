/**
 * @file CatalogTreeCtrl.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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
#include <wx/filename.h>

#include "Defs.h"
#include "gui/GuiDefs.h"
#include "utils/StampList.h"

#include "utils/Project.h"

#include "StampToolApp.h"
#include "catalog/CatalogSectionData.h"
#include "catalog/CatalogCode.h"
#include "catalog/Classification.h"
#include "catalog/Specimen.h"
#include "catalog/Entry.h"
#include "gui/StampToolFrame.h"
#include "gui/StampToolPanel.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/StampDescriptionPanel.h"
#include "gui/NewStampDialog.h"

wxDECLARE_APP( StampToolApp );


wxIMPLEMENT_CLASS( CatalogTreeCtrl, wxTreeCtrl );


wxBEGIN_EVENT_TABLE( CatalogTreeCtrl, wxTreeCtrl )

EVT_TREE_BEGIN_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnBeginDrag )
EVT_TREE_END_DRAG( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnEndDrag )
EVT_TREE_SEL_CHANGED( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnSelChanged )
EVT_TREE_STATE_IMAGE_CLICK( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemStateClick )
EVT_TREE_ITEM_MENU( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemMenu )
//EVT_TREE_ITEM_RIGHT_CLICK( ID_CATALOGTREECTRL, CatalogTreeCtrl::OnItemRClick )

wxEND_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

// CatalogTreeCtrl implementation

//*****

CatalogTreeCtrl::CatalogTreeCtrl( wxWindow* parent, const wxWindowID id, 
    const wxPoint& pos, const wxSize& size, 
    long style )
    : wxTreeCtrl( parent, id, pos, size, style )
{ 
    m_reverseSort = false;

    CreateImageList( );
    CreateStateImageList(  );
}

//*****

void CatalogTreeCtrl::CreateImageList( )
{ 
    AssignImageList( CreateCatalogImageList( ) );
}

//*****

void CatalogTreeCtrl::CreateStateImageList( )
{ 
    AssignStateImageList( CreateCatalogStateImageList(  ) );
}

ComparisonResultType CatalogTreeCtrl::CompareDates( wxString date1, wxString date2 )
{ 
    wxDateTime dt1;
    wxDateTime dt2;
    wxString::const_iterator end;
    if ( !dt1.ParseFormat( date1, "%Y-%m-%d", &end ) )
    { 
        if ( !dt1.ParseFormat( date1, "%Y", &end ) )
        { 
            if ( !dt1.ParseFormat( date1, "%Y-%m", &end ) )
            { 
                return CompareInvalid;
            }
        }
    }
    if ( !dt2.ParseFormat( date2, "%Y-%m-%d", &end ) )
    { 
        if ( !dt2.ParseFormat( date2, "%Y", &end ) )
        { 
            if ( !dt2.ParseFormat( date2, "%Y-%m", &end ) )
            { 
                return CompareInvalid;
            }
        }
    }
    if ( !dt1.IsValid( ) || !dt2.IsValid( ) )
    { 
        return CompareInvalid;
    }

    if ( dt1.IsSameDate( dt2 ) )
    { 
        return CompareEqual;
    }
    else if ( dt1.IsEarlierThan( dt2 ) )
    { 
        return CompareLess;
    }
    else
    { 
        return CompareGreater;
    }
}

//*****

int CatalogTreeCtrl::OnCompareItems( const wxTreeItemId& item1, 
    const wxTreeItemId& item2 )
{ 
    if ( item1.IsOk( ) && item2.IsOk( ) )
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
            // they are the same type
            if ( type1 == Catalog::NT_Entry )
            { 
                // they are both entries

                wxXmlNode* node1 = itemData1->GetNodeElement( );
                Catalog::Entry entry1( node1 );
                wxString date1 = entry1.GetIssuedDate( );
                wxString id1 = itemData1->GetDesc( );
                wxString series1 = entry1.GetSeries( );
                wxXmlNode* node2 = itemData2->GetNodeElement( );
                Catalog::Entry entry2( node2 );
                wxString date2 = entry2.GetIssuedDate( );
                wxString id2 = itemData2->GetDesc( );
                wxString series2 = entry2.GetSeries( );

                ComparisonResultType result = CompareDates( date1, date2 );
                if ( ( result == CompareInvalid ) || ( result == CompareEqual ) )
                { 
                    int val = series1.Cmp( series2 );
                    // if ( !val )
                    // { 
                    //     int val = id1.Cmp( id2 );
                    //     if ( !val )
                    //     { 
                    //         std::cout << "( " << id1 << " " << date1 << " ) = ( " << id2 << " " << date2 << " )\n";
                    //     | 
                    //     else if ( val < 0 )
                    //     { 
                    //         std::cout << "( " << id1 << " " << date1 << " ) < ( " << id2 << " " << date2 << " )\n";
                    //     }
                    //     else 
                    //     { 
                    //         std::cout << "( " << id1 << " " << date1 << " ) > ( " << id2 << " " << date2 << " )\n";
                    //     }
                    // }
                    // else if ( val < 0 )
                    // { 
                    //     std::cout << "( " << id1 << " " << date1 << " ) < ( " << id2 << " " << date2 << " )\n";
                    // }
                    // else 
                    // { 
                    //     std::cout << "( " << id1 << " " << date1 << " ) > ( " << id2 << " " << date2 << " )\n";
                    // }

                //    if ( m_reverseSort )
                //    { 
                    return val;
                    //    }
                    //    else
                    //    { 
                    //        return val * -1;
                    //    }

                }
                else if ( result == CompareLess )
                { 
                    //   std::cout << "( " << id1 << " " << date1 << " ) < ( " << id2 << " " << date2 << " )\n";
                   //    if ( m_reverseSort )
                   //    { 
                    return -1;
                    // }
                    // else
                    // { 
                    //     return 1;
                    // }
                }
                // else if ( result == CompareEqual )
                // { 
                //     std::cout << "( " << id1 << " " << date1 << " ) = ( " << id2 << " " << date2 << " )\n";
                //     return 0;
                // }
                else
                { 
                    //    std::cout << "( " << id1 << " " << date1 << " ) > ( " << id2 << " " << date2 << " )\n";
                    //    if ( m_reverseSort )
                    //    { 
                    //        return -1;
                    //    }
                     //   else
                    //    { 
                    return 1;
                    //    }
                }
            }
        }
    }
    return 0;
}


//*****

Utils::StampLink* CatalogTreeCtrl::AppendAlbumStamp( wxTreeItemId itemId )
{ 
    Utils::StampLink* link = GetDesignTreeCtrl( )->AppendStamp( itemId );
    if ( link )
    { 
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
        data->SetStampLink( link );
        link->SetCatTreeID( itemId );
    }
    return link;
}

//*****

wxXmlNode* CatalogTreeCtrl::GetEntryNode( wxTreeItemId itemId )
{ 
    wxXmlNode* node = 0;
    if ( itemId.IsOk( ) )
    { 
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
        node = data->GetNodeElement( );
    }
    return node;
}

void CatalogTreeCtrl::SetCatalogLink( wxTreeItemId catID, Utils::StampLink* link, wxString IDNbr )
{
    // find the catdata for this link
    CatalogTreeItemData* catData = ( CatalogTreeItemData* )GetItemData( catID );
    if ( catData )
    {
        //Get the catalog stamp id
        wxXmlNode* ele = catData->GetNodeElement();
        if ( ele )
        {
            wxString catIDNbr = ele->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
            if ( !catIDNbr.Cmp( IDNbr ) )
            {
                link->SetCatTreeID( catID ); 
                catData->SetStampLink( link );
                catData->SetChecked();
            }
            else
            {
                link->SetCatTreeID( 0 ); 
                catData->SetStampLink( 0 );
            }
        }
        else
        {
            link->SetCatTreeID( 0 ); 
            catData->SetStampLink( 0 );
        }
    }
    else
    {
        link->SetCatTreeID( 0 ); 
    }

}

//*****

Utils::StampLink* CatalogTreeCtrl::FindStampLink( wxTreeItemId itemId )
{ 
    wxString id = GetIdText( itemId );
    Utils::StampList* stampList = GetToolData( )->GetStampAlbumCatalogLink( );
    Utils::StampLink* stampLink = stampList->FindStampLink( id );
    return stampLink;
}

//*****

void CatalogTreeCtrl::DeleteAlbumStamp( wxTreeItemId itemId )
{ 
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
    Utils::StampLink* stampLink = data->GetStampLink( );
    if ( stampLink )
    { 
        wxTreeItemId itemID = stampLink->GetDesignTreeID( );
        if ( itemID.IsOk( ) ) GetDesignTreeCtrl( )->DeleteItem( itemID );
    }
}

//*****

void CatalogTreeCtrl::RemoveStampLink( wxTreeItemId itemId )
{ 
    if ( itemId.IsOk( ) )
    { 
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( itemId );
        data->SetStampLink( 0 );
    }
}


//*****

void CatalogTreeCtrl::SetNextState( const wxTreeItemId& itemId )
{ 
    wxXmlNode* element = GetEntryNode( itemId );
    Catalog::Entry* entry = new Catalog::Entry( element );
    if ( entry->IsOK( ) )
    { 
        SetItemState( itemId, wxTREE_ITEMSTATE_NEXT );
        int state = GetItemState( itemId );
        CatalogTreeItemData* data = (CatalogTreeItemData*)GetItemData( itemId );
        data->SetChecked( state );
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

//*****

Catalog::IconID CatalogTreeCtrl::GetInventoryIconId( Catalog::Entry* entry )
{ 
    int format = entry->GetFormatType( );
    int type = entry->GetInventoryStatusType( );
    return Catalog::CatalogImageSelection[ format ][ type ];
}

Catalog::Entry* CatalogTreeCtrl::GetNewEntry( wxTreeItemId itemId )
{ 
    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );
    wxXmlNode* element = item->GetNodeElement( );
    return new Catalog::Entry( element );
}
//*****

void CatalogTreeCtrl::SetInventoryStatusImage( )
{ 
    wxTreeItemId itemId = GetFocusedItem( );
    Catalog::Entry* entry = GetNewEntry( itemId );
    if ( entry->IsOK( ) )
    { 
        int status = entry->GetInventoryStatusType( );
        int format = entry->GetFormatType( );
        //Catalog::IconID iconID = Catalog::CatalogImageSelection[ format ][ status ];
        SetItemImage( itemId, GetInventoryIconId( entry ) );
    }
}

//*****

void CatalogTreeCtrl::LogEvent( const wxString& name, const wxTreeEvent& event )
{ 
    wxTreeItemId item = event.GetItem( );
    wxString text;
    if ( item.IsOk( ) )
        text << '"' << GetItemText( item ) << '"';
    else
        text = "invalid item";
}

//*****

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

//*****

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
    ShowDropMenu( itemSrc, itemDst );
}

//*****

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
    menu.Append( CatalogDataTree_Before, label );
    label = "    AFTER " + GetItemText( itemDst );
    menu.Append( CatalogDataTree_After, label );
    label = "    as CHILD of " + GetItemText( itemDst );
    menu.Append( CatalogDataTree_AsChild, label );
    menu.Append( CatalogDataTree_Cancel, "Cancel Drag" );


    switch ( GetPopupMenuSelectionFromUser( menu ) )
    { 
    case CatalogDataTree_Before:
    { 

        wxXmlNode* srcElement = GetEntryNode( itemSrc );
        wxXmlNode* dstElement = GetEntryNode( itemDst );

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
    case CatalogDataTree_After:
    { 

        wxXmlNode* srcElement = GetEntryNode( itemSrc );
        wxXmlNode* dstElement = GetEntryNode( itemDst );

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
    case CatalogDataTree_AsChild:
    { 

        wxXmlNode* srcElement = GetEntryNode( itemSrc );
        wxXmlNode* dstElement = GetEntryNode( itemDst );

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
    case CatalogDataTree_Cancel:
    { 

        break;
    }
    }
}

//*****

void CatalogTreeCtrl::OnItemStateClick( wxTreeEvent& event )
{ 
    // toggle item state
    wxTreeItemId itemId = event.GetItem( );
    SetNextState( itemId );
}

//*****

void CatalogTreeCtrl::OnSelChanged( wxTreeEvent& event )
{ 
    wxTreeItemId itemId = event.GetItem( );
    wxXmlNode* entry = GetEntryNode( itemId );
    //    wxGetApp( ).GetFrame( )->SetEntry( entry );
    GetToolData( )->GetDescriptionPanel( )->SetStamp( entry );
    event.Skip( );
}

//*****

void CatalogTreeCtrl::OnItemMenu( wxTreeEvent& event )
{ 
    wxTreeItemId itemId = event.GetItem( );
    wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

    CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );
    wxPoint clientpt = event.GetPoint( );
    wxPoint screenpt = ClientToScreen( clientpt );

    ShowMenu( itemId, clientpt );
    event.Skip( );
}


//*****

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
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
        wxXmlNode* node = data->GetNodeElement( );
        if ( data && data->GetType( ) == Catalog::NT_Entry )
        { 
            wxMenu* inventoryMenu = new wxMenu( );

            inventoryMenu->Append( CatalogDataTree_InventoryStatusNone, "None" );
            inventoryMenu->Append( CatalogDataTree_InventoryStatusMissing, "Missing" );
            inventoryMenu->Append( CatalogDataTree_InventoryStatusOrdered, "Ordered" );
            inventoryMenu->Append( CatalogDataTree_InventoryStatusOwn, "Own" );
            inventoryMenu->Append( CatalogDataTree_InventoryStatusOwnVariant, "OwnVariant" );
            inventoryMenu->Append( CatalogDataTree_InventoryStatusExclude, "Exclude" );
            menu.Append( CatalogDataTree_Inventory, "Inventory Status", inventoryMenu );
            menu.AppendSeparator( );
            menu.Append( CatalogDataTree_Colnect, "GoTo Colnect" );
            menu.AppendSeparator( );
            menu.Append( CatalogDataTree_Delete, "Delete Entry" );
            menu.Append( CatalogDataTree_Add, "Add New Entry" );
        }
        else
        { 
            menu.AppendSeparator( );
            menu.Append( CatalogDataTree_Colnect, "GoTo Colnect" );
            menu.AppendSeparator( );
            menu.Append( CatalogDataTree_StructureStamps, "Re-Group Multiples" );
            menu.Append( CatalogDataTree_ResortTree, "Re-Sort Tree" );
            menu.Append( CatalogDataTree_EditDetails, "Edit Catalog Details" );
        }
    }

    switch ( GetPopupMenuSelectionFromUser( menu ) )
    { 
    case CatalogDataTree_Inventory:
    case CatalogDataTree_InventoryStatusNone:
    { 
        Catalog::InventoryStatusType newType = Catalog::ST_None;
        Catalog::Entry* entry = new Catalog::Entry( GetEntryNode( id ) );
        Catalog::InventoryStatusType type = entry->GetInventoryStatusType( );
        if ( type != newType )
        { 
            entry->SetInventoryStatusType( newType );
            SetInventoryStatusImage( );
            wxGetApp( ).GetFrame( )->UpdateStatus( );
        }
    }
    break;
    case CatalogDataTree_InventoryStatusMissing:
    { 
        Catalog::InventoryStatusType newType = Catalog::ST_Missing;
        Catalog::Entry* entry = new Catalog::Entry( GetEntryNode( id ) );
        Catalog::InventoryStatusType type = entry->GetInventoryStatusType( );
        if ( type != newType )
        { 
            entry->SetInventoryStatusType( newType );
            SetInventoryStatusImage( );
            wxGetApp( ).GetFrame( )->UpdateStatus( );

        }
    }
    break;

    case CatalogDataTree_InventoryStatusOrdered:
    { 
        Catalog::InventoryStatusType newType = Catalog::ST_Ordered;
        Catalog::Entry* entry = new Catalog::Entry( GetEntryNode( id ) );
        Catalog::InventoryStatusType type = entry->GetInventoryStatusType( );
        if ( type != newType )
        { 
            entry->SetInventoryStatusType( newType );
            SetInventoryStatusImage( );
            wxGetApp( ).GetFrame( )->UpdateStatus( );

        }
    }
    break;

    case CatalogDataTree_InventoryStatusOwn:
    { 
        Catalog::InventoryStatusType newType = Catalog::ST_Own;
        Catalog::Entry* entry = new Catalog::Entry( GetEntryNode( id ) );
        Catalog::InventoryStatusType type = entry->GetInventoryStatusType( );
        if ( type != newType )
        { 
            entry->SetInventoryStatusType( newType );
            SetInventoryStatusImage( );
            wxGetApp( ).GetFrame( )->UpdateStatus( );

        }
    }
    break;

    case CatalogDataTree_InventoryStatusOwnVariant:
    { 
        Catalog::InventoryStatusType newType = Catalog::ST_OwnVariant;
        Catalog::Entry* entry = new Catalog::Entry( GetEntryNode( id ) );
        Catalog::InventoryStatusType type = entry->GetInventoryStatusType( );
        if ( type != newType )
        { 
            entry->SetInventoryStatusType( newType );
            SetInventoryStatusImage( );
            wxGetApp( ).GetFrame( )->UpdateStatus( );

        }
    }
    break;

    case CatalogDataTree_InventoryStatusExclude:
    { 
        Catalog::InventoryStatusType newType = Catalog::ST_Exclude;
        Catalog::Entry* entry = new Catalog::Entry( GetEntryNode( id ) );
        Catalog::InventoryStatusType type = entry->GetInventoryStatusType( );
        if ( type != newType )
        { 
            entry->SetInventoryStatusType( newType );
            SetInventoryStatusImage( );
            wxGetApp( ).GetFrame( )->UpdateStatus( );

        }
    }
    break;
    // m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_None ] );
    // m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Missing ] );
    // m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Ordered ] );
    // m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Own ] );
    // m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_OwnVariant ] );
    // m_statusStrings.Add( Catalog::ST_InventoryStatusStrings[ Catalog::ST_Exclude ] );

    case CatalogDataTree_StructureStamps:
    { 
        wxXmlNode* entry = GetEntryNode( id );

        GetCatalogSectionData( )->ReGroupMultiples( );
        ReSortTree( );

        wxTreeItemId newID = FindTreeItemID( entry );
        if ( newID )
        { 
            Expand( newID );
            SelectItem( newID );
        }
    }
    break;
    case CatalogDataTree_ResortTree:
    { 
        ReSortTree( );
    }
    break;
    case CatalogDataTree_EditDetails:
    { 
        GetCatalogSectionData( )->EditDetailsDialog( this );
    }
    break;


    case CatalogDataTree_Colnect:
    { 
        GoToColnect( id );
    }
    break;
    case CatalogDataTree_Delete:
    { 
        DeleteEntry( id );
    }
    break;
    case CatalogDataTree_Add:
    { 
        AddEntry( id );
    }
    break;
    default:
        // Fall through.
        break;
    }
}
// void CatalogTreeCtrl::EditDetailsDialog( )
// { 
//     SectionDetailsDialog sectionDetailsDialog( this, 12345, 
//         _( "View Edit Catalog Details" ) );

//     Catalog::CatalogSectionData* sectData = GetCatalogSectionData( );
//     sectionDetailsDialog.SetImagePath( sectData->GetImagePath( ) );
//     sectionDetailsDialog.SetName( sectData->GetSectionName( ) ) ;


//     if ( sectionDetailsDialog.ShowModal( ) == wxID_CANCEL )
//         return; // the user changed idea..

//     if ( sectionDetailsDialog.IsNameModified( ) )
//     { 
//     sectData->SetImagePath( sectionDetailsDialog.GetImagePath( ) );
//     sectData->SetSectionName( sectionDetailsDialog.GetName( ) ) ;
//     }
// }


//*****

void CatalogTreeCtrl::AddEntry( wxTreeItemId id )
{ 
    NewStampDialog newEntryDialog( this, 12345, _( "Add New Entry" ) );
    if ( newEntryDialog.ShowModal( ) == wxID_CANCEL ) return; // the user changed idea..
}
//*****

void CatalogTreeCtrl::DeleteEntry( wxTreeItemId id )
{ 
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
    wxXmlNode* node = data->GetNodeElement( );
    if ( data && data->GetType( ) == Catalog::NT_Entry )
    { 
        wxString txt = wxString::Format( "Delete Entry %s?\n\n", GetItemText( id ) );
        wxMessageDialog* dlg = new wxMessageDialog( 
            wxGetApp( ).GetFrame( ), txt, 
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

//*****

void CatalogTreeCtrl::GoToColnect( wxTreeItemId id )
{ 
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
    wxXmlNode* node = data->GetNodeElement( );
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

// //*****

// void CatalogTreeCtrl::OnItemRClick( wxTreeEvent& event )
// { 
//     wxTreeItemId itemId = event.GetItem( );
//     wxCHECK_RET( itemId.IsOk( ), "should have a valid item" );

//     CatalogTreeItemData* item = ( CatalogTreeItemData* )GetItemData( itemId );

//     event.Skip( );
// }

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
//*****

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
        CatalogTreeItemData* data = (CatalogTreeItemData*)GetItemData( childID );
        if ( stampLink )
        { 
            itemData->SetStampLink( stampLink );
            stampLink->SetCatTreeID( childID );
            SetItemState( childID, Catalog::ST_Checked );
            // and the entry as checked
            data->SetChecked( true );
        }
        else
        { 
            data->SetChecked( false );
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
    if ( wxGetApp( ).GetFrame( )->GetStampToolPanel( )->ShouldShowStates( ) )
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

//*****


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
        CatalogTreeItemData* data = (CatalogTreeItemData*)GetItemData( childID );
        if ( stampLink )
        { 
            itemData->SetStampLink( stampLink );
            stampLink->SetCatTreeID( childID );
            SetItemState( childID, Catalog::ST_Checked );

            // and the entry as checked

            data->SetChecked( true );
        }
        else
        { 
            data->SetChecked( false );
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

    if ( wxGetApp( ).GetFrame( )->GetStampToolPanel( )->ShouldShowStates( ) )
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


void CatalogTreeCtrl::SortTree( wxTreeItemId parent )
{ 
    // decend into the tree and sort its children
    wxTreeItemIdValue cookie;
    wxTreeItemId childItem = GetFirstChild( parent, cookie );
    while ( childItem.IsOk( ) )
    { 
        //        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( childItem );
        //        wxString str = data->GetDesc( );
        //        std::cout << str << "\n";

        if ( GetChildrenCount( childItem, false ) >= 1 )
        { 
            // descend and do it again
            SortTree( childItem );
        }
        childItem = GetNextChild( parent, cookie );
    }
    if ( this->HasChildren( parent ) )
    { 
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( parent );
        wxString str = data->GetDesc( );
        //               std::cout << " SortChildren for "<<str << "\n";
        SortChildren( parent );
    }
}


void CatalogTreeCtrl::ReSortTree( )
{ 

    ClearCatalogTree( );

    Catalog::CatalogSectionData* catalogSectionData = GetCatalogSectionData( );
    catalogSectionData->ReSortTree( );

    LoadTree( );
}


void CatalogTreeCtrl::ClearCatalogTree( )
{ 
    // first make sure all the links to the items are gone
    Utils::StampList* stampList = GetToolData( )->GetStampAlbumCatalogLink( );
    stampList->ClearCatalogLinks( );

    // then clobber all the tree items
    DeleteAllItems( );
}

//*****



void CatalogTreeCtrl::LoadTree( )
{ 
    ClearCatalogTree( );
    Catalog::CatalogSectionData* catalogSectionData = GetCatalogSectionData( );
    if ( catalogSectionData )
    { 
        wxXmlDocument* entryDoc = catalogSectionData->GetDoc( );
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
        SortTree( rootID );
        GetDesignTreeCtrl( )->UpdateStampList( );
        SetStates( wxGetApp( ).GetFrame( )->GetStampToolPanel( )->ShouldShowStates( ) );
        ExpandAll( );
    }
}

void CatalogTreeCtrl::XMLDumpNode( wxTreeItemId item, wxString str )
{ 

    if ( !item.IsOk( ) )
    { 
        return;
    }
    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( item );
    wxXmlNode* ele = data->GetNodeElement( );
    Utils::XMLDumpNode( ele, str );
}
//*****


bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxXmlNode* ele )
{ 
    if ( !item.IsOk( ) )
    { 
        return false;
    }

    CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( item );
    wxXmlNode* dataEle = data->GetNodeElement( );
    if ( dataEle != ele )
    { 
        return false;
    }
    return true;
}

//*****

bool CatalogTreeCtrl::IsElement( wxTreeItemId item, wxString entryID )
{ 
    if ( item.IsOk( ) )
    { 
        wxString id = GetAttribute( item, Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
        if ( entryID.Cmp( id ) )
        { 
            return false;
        }
    }
    return true;
}

//*****

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


//*****

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
            if ( this->HasChildren( child ) )
            { 
                wxTreeItemId idFound = FindTreeItemID( entryID, child );
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

//*****

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxXmlNode* ele )
{ 
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( ele, root );
}

//*****

wxTreeItemId CatalogTreeCtrl::FindTreeItemID( wxString entryID )
{ 
    wxTreeItemId root = GetRootItem( );
    return FindTreeItemID( entryID, root );
}

//*****

wxTreeItemId CatalogTreeCtrl::FindFirstEntryChild( wxTreeItemId id )
{ 
    if ( id.IsOk( ) )
    { 
        wxTreeItemIdValue cookie;
        wxTreeItemId child = GetFirstChild( id, cookie );
        while ( child )
        { 
            CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( child );
            if ( data->GetType( ) == Catalog::NT_Entry )
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

//*****

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

//*****

void CatalogTreeCtrl::EnableState( wxTreeItemId id )
{ 
    if ( id.IsOk( ) )
    { 
        CatalogTreeItemData* data = ( CatalogTreeItemData* )GetItemData( id );
        if ( data->GetType( ) == Catalog::NT_Entry )
        { 
            wxXmlNode* node = data->GetNodeElement( );
            if ( data->IsChecked() )
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

//*****

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
wxString CatalogTreeCtrl::GetIdText( wxTreeItemId catID )
{ 
    wxXmlNode* catNode = GetEntryNode( catID );
    wxString idText = "";
    if ( catNode )
    { 
        idText = catNode->GetAttribute( Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );
    }
    return idText;
}

wxString CatalogTreeCtrl::GetAttribute( wxTreeItemId catID, wxString name )
{ 
    return GetEntryNode( catID )->GetAttribute( name );
}
wxString CatalogTreeCtrl::GetImageFullName( wxTreeItemId catID )
{ 
    if ( catID.IsOk( ) )
    { 
        CatalogTreeItemData* itemData = ( CatalogTreeItemData* )this->GetItemData( catID );
        wxString* imageFullName = itemData->GetImageFullName( );
        if ( !imageFullName )
        { 
            Catalog::CatalogSectionData* sectData = GetToolData( )->GetCatalogSectionData( );
            wxString catFilename = sectData->GetSectionFilename( );
            wxString imageFile = sectData->GetCatalogSectionImagePath( );;

            wxString id = GetAttribute( catID, Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] );

            id = id.Trim( true );
            id = id.Trim( false );
            id.Replace( ":", "_" );
            id.Replace( " ", "_" );
            id.Append( ".jpg" );

            imageFullName = new wxString( wxFileName( catFilename ).GetFullPath( ) + "/" + imageFile + "/" + id );
            itemData->SetImageFullName( imageFullName );
        }
        return *imageFullName;
    }
    return "";
}

