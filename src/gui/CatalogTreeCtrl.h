/**
 * @file gui/CatalogTreeCtrl.h
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
#ifndef CatalogTreeCtrl_H
#define CatalogTreeCtrl_H

#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include "gui/IconDefs.h"
#include "gui/GuiUtils.h"
#include "catalog/Entry.h"
#include "design/AlbumBase.h"


class Stamp;

namespace Utils {
    class StampLink;
}


//-------------
class CatalogTreeItemData : public wxTreeItemData
{
public:

    CatalogTreeItemData( Catalog::CatalogBaseType type, const wxString desc, wxXmlNode* ele = 0 );

    ~CatalogTreeItemData( )
    {
        m_ok = 0;
    };

    int Cmp( CatalogTreeItemData* itemData2 );

    wxString const& GetDesc( ) const {
        return m_desc;
    };

    wxString GetImageFullName( ) {
        return m_imageFullPath;
    };

    wxXmlNode* GetNodeElement( void ) {
        return m_element;
    };


    Utils::StampLink* GetStampLink( ) {
        return m_stampLink;
    }


    Catalog::CatalogBaseType GetType( ) {
        return m_type;
    };

    bool IsChecked( ) {
        return m_isChecked;
    };

    bool IsOK( )
    {
        if ( m_ok == 12345 )
        {
            return true;
        }
        return false;
    };


    void SetCatNode( wxXmlNode* ele ) {
        m_element = ele;
    };


    void SetType( Catalog::CatalogBaseType type ) {
        m_type = type;
    };

    void SetStampLink( Utils::StampLink* link ) {
        m_stampLink = link;
    };


    void SetImageFullName( wxString str ) {
        m_imageFullPath = str;
    };


    void SetChecked( bool state = true )
    {
        m_isChecked = state;
    };

private:
    double m_ok;
    wxXmlNode* m_element;
    wxString m_desc;
    Catalog::CatalogBaseType m_type;
    Utils::StampLink* m_stampLink;
    bool m_isChecked;
    wxString m_imageFullPath;
};


//-----------

class CatalogTreeCtrl : public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( CatalogTreeCtrl )
    //    DECLARE_EVENT_TABLE( )

public:
    enum
    {
        CatalogListTree_Quit = wxID_EXIT,
        CatalogListTree_About = wxID_ABOUT,
        CatalogListTree_Sort,
        CatalogListTree_StructureStamps,
        CatalogListTree_ResortTree,
        CatalogListTree_EditDetails,
        CatalogListTree_Delete,
        CatalogListTree_Add,
        CatalogListTree_Colnect,
        CatalogListTree_Before,
        CatalogListTree_After,
        CatalogListTree_AsChild,
        CatalogListTree_Cancel,
        CatalogListTree_Inventory,
        CatalogListTree_InventoryStatusNone,
        CatalogListTree_InventoryStatusMissing,
        CatalogListTree_InventoryStatusOrdered,
        CatalogListTree_InventoryStatusOwn,
        CatalogListTree_InventoryStatusOwnVariant,
        CatalogListTree_InventoryStatusExclude
    };



    CatalogTreeCtrl( ) { }

    CatalogTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~CatalogTreeCtrl( void ) { }

    /// @brief AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
    /// create sort nodes as necessary to find the proper place for the child
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );


    void AddEntry( wxTreeItemId id );


    Utils::StampLink* AppendAlbumStamp( wxTreeItemId itemId );

    void Clear( );

    ComparisonResultType CompareDates( wxString date1, wxString date2 );

    void CountEntryTypes( );

    void  CountEntryTypes( wxTreeItemId parent, int& count );


    CatalogTreeItemData* CreateChildData( wxXmlNode* child,
        wxString& label,
        Catalog::IconID& icon,
        Catalog::CatalogBaseType& nodeType );

    void CreateStateImageList( );

    void CreateImageList( );

    /// @brief Deletes the item from the stamp link list and sends a message to
    /// the design tree to remove it.
    void DeleteAlbumStamp( wxTreeItemId itemId );


    void DeleteEntry( wxTreeItemId id );

    /// @brief Disables the check box on all the tree items
     ///from itemId on down, so should start from root.
    void DisableState( wxTreeItemId id );

    void DoSortChildren( const wxTreeItemId& item, bool reverse = true )
    {
        m_reverseSort = reverse;
        wxTreeCtrl::SortChildren( item );
    };


    void DumpTree( );

    void DumpTree( wxTreeItemId id );

    void EnableState( wxTreeItemId id );

    wxTreeItemId FindFirstEntryChild( wxTreeItemId id );

    wxTreeItemId FindTreeItemID( wxXmlNode* node );

    wxTreeItemId FindTreeItemID( wxXmlNode* node, wxTreeItemId id );

    Utils::StampLink* FindStampLink( wxTreeItemId itemId );

    wxTreeItemId FindTreeItemID( wxString stampID );

    wxTreeItemId FindTreeItemID( wxString stampID, wxTreeItemId id );

    wxString GetAttribute( wxTreeItemId catTreeID, wxString name );

    wxString GetID( wxTreeItemId catTreeID );

    wxString GetImage( wxTreeItemId catTreeID );

    wxString GetImageFullName( wxTreeItemId catTreeID );

    Catalog::IconID GetInventoryIconId( Catalog::Entry* stamp );

    wxString GetItemDesc( wxTreeItemId id );

    wxString GetItemImageFullName( wxTreeItemId id );

    wxXmlNode* GetItemNode( wxTreeItemId id );

    Utils::StampLink* GetItemStampLink( wxTreeItemId id );

    Catalog::CatalogBaseType GetItemType( wxTreeItemId id );

    wxXmlNode* GetNewEntry( wxTreeItemId itemId );

    int GetNbrEntryTypes( ){
        return m_nbrEntryTypes;
    };

    wxXmlNode* GetSelectionNode( );

    void GoToColnect( wxTreeItemId id );

    wxTreeItemId InsertChild( wxTreeItemId parent, wxXmlNode* child, bool after = true );

    bool IsElement( wxTreeItemId item, wxString stampID );

    bool IsElement( wxTreeItemId item, wxXmlNode* node );

    bool IsItemChecked( wxTreeItemId id );

    void LoadCatalogTree( void );

    void OnBeginDrag( wxTreeEvent& event );

    virtual int OnCompareItems( const wxTreeItemId& i1, const wxTreeItemId& i2 ) wxOVERRIDE;

    void OnEndDrag( wxTreeEvent& event );

    void OnItemMenu( wxTreeEvent& event );

    void OnItemStateClick( wxTreeEvent& event );

    void OnSelChanged( wxTreeEvent& event );

    void OnTreectrlItemCollapsed( wxTreeEvent& event );

    void OnTreectrlItemExpanded( wxTreeEvent& event );

    void PrintTreeNodeData( wxTreeItemId id );

    void RemoveStampLink( wxTreeItemId itemId );

    /// @brief Delete the tree and resort it with the new sort order data.
     /// Probably doing this because the sort order was changed.
    void ReSortTree( );

    void SetAttribute( wxTreeItemId catTreeID, wxString name, wxString val );

    void SelectStamp( wxString id );

    void SetCatalogLink( wxTreeItemId catTreeID, Utils::StampLink* link, wxString IDNbr );

    void SetTreeItemCollapseState( wxTreeItemId childID );

    void SetInventoryStatusImage( void );

    void SetItemNode( wxTreeItemId id, wxXmlNode* ele );

    void SetItemChecked( wxTreeItemId id, bool state = true );

    void SetItemImageFullName( wxTreeItemId id, wxString str );

    void SetInventoryStatus( wxXmlNode* node, Catalog::InventoryStatusType newType );

    void SetItemStampLink( wxTreeItemId id, Utils::StampLink* link );

    /// @brief Set the checkbox of the item to the next state. Saves the new state.
    /// Sends message to Album tree to update
    void SetNextState( const wxTreeItemId& itemID );

    //Find th node and select it
    void SetSelection( wxXmlNode* node );

    void SetType( wxTreeItemId id, Catalog::CatalogBaseType type );

    void SetStates( bool enable );

    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    void ShowMenu( wxTreeItemId id, const wxPoint& pt );

    /// @brief SortTree decends through the tree and sorts the children of each item.
    void SortTree( wxTreeItemId parent );

    //void UpdateStamp( Stamp* newStamp, wxTreeItemId catTreeID );

    void XMLDumpNode( wxTreeItemId item, wxString str );

private:

    int m_nbrEntryTypes;

    void LogEvent( const wxString& name, const wxTreeEvent& event );

    bool m_reverseSort;         // flag for OnCompareItems

    wxTreeItemId m_draggedItem; // item being dragged right now

    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS( );
    //     if you want your overloaded OnCompareItems( ) to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default ( alphabetical ) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS( CatalogTreeCtrl );
    wxDECLARE_EVENT_TABLE( );
};

#endif
