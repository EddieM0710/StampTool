/**
 * @file gui/CatalogTOCTreeCtrl.h
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
#ifndef TOCTreeCtrl_H
#define TOCTreeCtrl_H

#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include "gui/IconDefs.h"
#include "gui/GuiUtils.h"
#include "toc/TOCDefs.h"


class Stamp;

namespace Utils {
    class StampLink;
}

typedef void* VolumePtr;
/**
 * data associated with each node in the tree
 *
 */
class TOCTreeItemData : public wxTreeItemData
{
public:

    ///  @brief Construct a new Catalog Tree Item Data object
    ///  
    ///  @param type 
    ///  @param desc 
    ///  @param ele 
    TOCTreeItemData( Utils::TOCBaseType type, const wxString desc,
        wxXmlNode* ele = 0, int menuID = 0, VolumePtr vol = 0 )
    {
        m_type = type;
        m_desc = desc;
        m_element = ele;
        m_volume = vol;
        m_menuID = menuID;
        m_ok = 12345;
    };

    ///  @brief Destroy the Catalog Tree Item Data object
    ///  
    ~TOCTreeItemData( )
    {
        m_ok = 0;
    };

    ///  @brief 
    ///  
    ///  @param itemData2 
    ///  @return int 
    int Cmp( TOCTreeItemData* itemData2 )
    {

        Utils::TOCBaseType type2 = itemData2->GetType( );

        if ( m_type != type2 )
        {
            return 0;//( int ) m_type - ( int ) type2;
        }
        else
        {
            // they are the same type

            return 0;
        }
    };


    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsOK( )
    {
        if ( m_ok == 12345 )
        {
            return true;
        }
        return false;
    };

    ///  @brief Get the Desc object
    ///  
    ///  @return wxString const& 
    wxString const& GetDesc( ) const {
        return m_desc;
    };

    ///  @brief Get the Node Element object
    ///  
    ///  @return wxXmlNode* 
    wxXmlNode* GetNodeElement( void ) {
        return m_element;
    };

    VolumePtr GetVolume( ) {
        return m_volume;
    };


    ///  @brief Get the Type object
    ///  
    ///  @return Utils::TOCBaseType 
    Utils::TOCBaseType GetType( ) {
        return m_type;
    };

    ///  @brief Set the Cat Node object
    ///  
    ///  @param ele 
    void SetCatNode( wxXmlNode* ele ) {
        m_element = ele;
    };

    ///  @brief Set the Type object
    ///  
    ///  @param type 
    void SetType( Utils::TOCBaseType type ) {
        m_type = type;
    };

    int GetMenuID( ){
        return m_menuID;
    };

private:
    double m_ok;
    wxXmlNode* m_element;
    VolumePtr m_volume;
    int m_menuID;
    wxString m_desc;
    Utils::TOCBaseType m_type;

};

/**
 * @brief Class to manage a wxTreeCtrl for Stamp
 *
 */
class TOCTreeCtrl : public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( TOCTreeCtrl )
    //    DECLARE_EVENT_TABLE( )

public:
    enum
    {
        CatalogListTree_Quit = wxID_EXIT,
        CatalogListTree_About = wxID_ABOUT,
        CatalogListTree_ResortTree,
        CatalogListTree_EditDetails,
        CatalogListTree_Delete,
        CatalogListTree_Add,
        CatalogListTree_Before,
        CatalogListTree_After,
        CatalogListTree_AsChild,
        CatalogListTree_Cancel,

    };


    ///  @brief Construct a new Catalog Tree Ctrl object
    ///  
    TOCTreeCtrl( ) { }


    ///  @brief Construct a new Catalog Tree Ctrl object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    TOCTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~TOCTreeCtrl( void ) { }

    /*
     * @brief AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
     * create sort nodes as necessary to find the proper place for the child
     *
     * @param parent
     * @param child
     * @return wxTreeItemId
     */
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child, wxMenu* menu );

    /*
     * @brief Popup up a dialog to add a new entry into the tree
     *
     * @param id
     */
    void AddEntry( wxTreeItemId id );

    /*
     * @brief Updates the item data and the link list with new id
     *
     * @param itemId
     * @return Utils::StampLink*
     */
    Utils::StampLink* AppendAlbumStamp( wxTreeItemId itemId );

    /*
     * @brief Clears the entire tree
     *
     */
    void ClearTree( );


    /*
     * @brief Creates a new item user data for the child
     *
     * @param child
     * @param label
     * @param icon
     * @param nodeType
     * @return TOCTreeItemData*
     */
    TOCTreeItemData* CreateChildData( wxXmlNode* child,
        wxString& label,
        Catalog::IconID& icon,
        Utils::TOCBaseType& nodeType );


    /*
     * @brief Create a Image List object
     *
     */
    void CreateImageList( );


    /*
     * @brief Deletes the item from the tree
     *
     * @param id
     */
    void DeleteEntry( wxTreeItemId id );


    /*
     * @brief Sort the items in he tree based on Settings sort vriteria
     *
     * @param item
     * @param reverse
     */
    void DoSortChildren( const wxTreeItemId& item, bool reverse = true )
    {
        m_reverseSort = reverse;
        wxTreeCtrl::SortChildren( item );
    };

    /*
     * @brief Enables the check box on all the tree items
     * from itemId on down, so should start from root.
     *
     * @param id
     */
    void EnableState( wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param node 
    ///  @return wxTreeItemId 
    wxTreeItemId FindTreeItemID( wxXmlNode* node );

    ///  @brief 
    ///  
    ///  @param node 
    ///  @param id 
    ///  @return wxTreeItemId 
    wxTreeItemId FindTreeItemID( wxXmlNode* node, wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param item 
    ///  @param node 
    ///  @return true 
    ///  @return false 
    bool IsElement( wxTreeItemId item, wxXmlNode* node );


    ///  @brief 
    ///  
    ///  @param id 
    ///  @return wxTreeItemId 
    wxTreeItemId FindFirstEntryChild( wxTreeItemId id );

    /*
     * @brief Get the  value of the Attribute named name from item catTreeID
     *
     * @param catTreeID
     * @param name
     * @return wxString
     */
    wxString GetAttribute( wxTreeItemId catTreeID, wxString name );
    void  SetAttribute( wxTreeItemId catTreeID, wxString name, wxString val );
    wxString GetID( wxTreeItemId catTreeID );
    wxString GetImage( wxTreeItemId catTreeID );


    ///  @brief Get the Item Desc object
    ///  
    ///  @param id 
    ///  @return wxString 
    wxString GetItemDesc( wxTreeItemId id );

    ///  @brief Get the Item Image Full Name object
    ///  
    ///  @param id 
    ///  @return wxString* 
    wxString GetItemImageFullName( wxTreeItemId id );

    ///  @brief Get the Item Node object
    ///  
    ///  @param id 
    ///  @return wxXmlNode* 
    wxXmlNode* GetItemNode( wxTreeItemId id );


    ///  @brief Get the Item Type object
    ///  
    ///  @param id 
    ///  @return Utils::TOCBaseType 
    Utils::TOCBaseType GetItemType( wxTreeItemId id );

    /*
     * @brief make a New Entry from the element in the item data
     *
     * @param itemId
     * @return Catalog::Entry*
     */
    wxXmlNode* GetNewEntry( wxTreeItemId itemId );


    /*
     * @brief Similar to AddChild except inserts before or after a given child.
     *
     * @param parent
     * @param child
     * @param after
     * @return wxTreeItemId
     */
    wxTreeItemId InsertChild( wxTreeItemId parent, wxXmlNode* child, bool after = true );

    ///  @brief 
    ///  
    ///  @param item 
    ///  @param stampID 
    ///  @return true 
    ///  @return false 
    bool IsElement( wxTreeItemId item, wxString stampID );

    /*
     * @brief Loads the tree with current catalog volume data.
     *
     */
    void LoadTree( wxXmlNode* TOCNode, wxString str );

    /*
     * @brief Tries to compare 2 tre entries. right now only looking at date and series.
     * Only used for sorting but could be much better.
     *
     * @param i1
     * @param i2
     * @return int
     */
    void OnBeginDrag( wxTreeEvent& event );

    ///  @brief 
    ///  
    ///  @param i1 
    ///  @param i2 
    ///  @return int 
    virtual int OnCompareItems( const wxTreeItemId& i1, const wxTreeItemId& i2 ) wxOVERRIDE;

    /*
     * @brief OnEndDrag
     *
     * @param event
     */
    void OnEndDrag( wxTreeEvent& event );

    /*
    * @brief Event handler for Cat tree popup mwnu
    *
    * @param event
    * @return * void
    */
    void OnItemMenu( wxTreeEvent& event );

    /*
     * @brief event handler for cat tree selecton change
     *
     * @param event
     */
     //   void OnSelChanged( wxTreeEvent& event );



    void SelectStamp( wxString id );

    void SetTreeItemCollapseState( wxTreeItemId childID );


    ///  @brief Set the Item Node object
    ///  
    ///  @param id 
    ///  @param ele 
    void SetItemNode( wxTreeItemId id, wxXmlNode* ele );

    ///  @brief Set the Item Checked object
    ///  
    ///  @param id 
    ///  @param state 
    void SetItemChecked( wxTreeItemId id, bool state = true );

    ///  @brief 
    ///  
    void SetItemImageFullName( wxTreeItemId id, wxString str );



    ///  @brief Set the Type object
    ///  
    ///  @param id 
    ///  @param type 
    void SetType( wxTreeItemId id, Utils::TOCBaseType type );


    /*
    * @brief  Show the dropdown menu for moving items in the catalog tree
    *
    * @param itemSrc
    * @param itemDst
    */
    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    /*
     * @brief Show the popup menu for the cat tree
     *
     * @param id
     * @param pt
     */
    void ShowMenu( wxTreeItemId id, const wxPoint& pt );


    /*
     * @brief SortTree decends through the tree and sorts the children of each item.
     *
     * @param parent
     */
    void SortTree( wxTreeItemId parent );





    /*
     * @brief performs a std::cout dump from this item thru all children
     *
     * @param item
     * @param str
     */
    void XMLDumpNode( wxTreeItemId item, wxString str );

    void OnTreectrlItemCollapsed( wxTreeEvent& event );

    void OnTreectrlItemExpanded( wxTreeEvent& event );

    wxTreeItemId GetCurrentTreeID( ){
        return m_currVolumeID;
    };

    void SetCurrentTreeID( wxTreeItemId id ){
        m_currVolumeID = id;
    };
    // wxXmlNode* GetCurrVolumeRoot( );

    wxMenu* GetMenu( ) {
        return m_menu;
    };

    /*
     * @brief Delete the tree and resort it with the new sort order data.
     * Probably doing this because the sort order was changed.
     *
     */
    virtual void ReSortTree( ) = 0;

    virtual VolumePtr FindVolume( wxString str ) = 0;
    virtual wxString GetVolumeName( VolumePtr catVolume ) = 0;
    virtual wxXmlNode* GetCurrVolumeRoot( ) = 0;
    virtual void LinkMenuItemToTreeItem( int id, wxTreeItemId treeId ) = 0;
    virtual void EditDetailsDialog( TOCTreeCtrl* parent ) = 0;

private:

    wxMenu* m_menu;

    wxTreeItemId m_currVolumeID;
    //    int m_imageSize;            // current size of images
    bool m_reverseSort;         // flag for OnCompareItems
    wxTreeItemId m_draggedItem; // item being dragged right now

    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS( );
    //     if you want your overloaded OnCompareItems( ) to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default ( alphabetical ) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS( TOCTreeCtrl );
    wxDECLARE_EVENT_TABLE( );
};

#endif
