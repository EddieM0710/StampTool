/**
 * @file gui/CatalogTreeCtrl.h
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
 *
 **************************************************/

#ifndef CatalogTreeCtrl_H
#define CatalogTreeCtrl_H

#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include "gui/IconDefs.h"
#include "catalog/Entry.h"
#include "design/AlbumBase.h"
 /**
  *
  *  @brief menu and control ids
  **************************************************/
enum
{
    CatalogDataTree_Quit = wxID_EXIT,
    CatalogDataTree_About = wxID_ABOUT,
    CatalogDataTree_StructureStamps,
    CatalogDataTree_ResortTree,
    CatalogDataTree_EditDetails,
    CatalogDataTree_Delete,
    CatalogDataTree_Add,
    CatalogDataTree_Colnect,
    CatalogDataTree_Before,
    CatalogDataTree_After,
    CatalogDataTree_AsChild,
    CatalogDataTree_Cancel,
    CatalogDataTree_Inventory,
    CatalogDataTree_InventoryStatusNone,
    CatalogDataTree_InventoryStatusMissing,
    CatalogDataTree_InventoryStatusOrdered,
    CatalogDataTree_InventoryStatusOwn,
    CatalogDataTree_InventoryStatusOwnVariant,
    CatalogDataTree_InventoryStatusExclude
};


class Stamp;
class Classification;
namespace Utils { class StampLink; }

typedef enum {
    CompareInvalid,
    CompareEqual,
    CompareLess,
    CompareGreater
}ComparisonResultType;


/**
 * data associated with each node in the tree
 *
 **************************************************/
class CatalogTreeItemData: public wxTreeItemData
{
public:

    CatalogTreeItemData( Catalog::CatalogBaseType type, const wxString desc,
        wxXmlNode* ele = 0 )
    {
        m_type = type;
        m_desc = desc;
        m_element = ele;
        m_imageFullPath = 0;
    }
    ~CatalogTreeItemData( ) { if ( m_imageFullPath ) delete m_imageFullPath; }
    wxString const& GetDesc( ) const { return m_desc; };
    void SetCatNode( wxXmlNode* ele ) { m_element = ele; };
    wxXmlNode* GetNodeElement( void ) { return m_element; };

    void SetType( Catalog::CatalogBaseType type ) { m_type = type; };

    Catalog::CatalogBaseType GetType( ) { return m_type; };

    Utils::StampLink* GetStampLink( ) { return m_stampLink; }
    void SetStampLink( Utils::StampLink* link ) { m_stampLink = link; }

    wxString* GetImageFullName( ) { return m_imageFullPath; };
    void SetImageFullName( wxString* str ) { m_imageFullPath = str; };

    bool IsChecked( ) { return m_isChecked; };
    void SetChecked( bool state = true )
    {
        m_isChecked = state;
    };
private:
    wxXmlNode* m_element;
    wxString m_desc;
    Catalog::CatalogBaseType m_type;
    Utils::StampLink* m_stampLink;
    bool m_isChecked;
    wxString* m_imageFullPath;
};

/**
 * @brief Class to manage a wxTreeCtrl for Stamp
 *
 **************************************************/
class CatalogTreeCtrl: public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( CatalogTreeCtrl )
    //    DECLARE_EVENT_TABLE( )

public:

    /**
     * @brief Construct a new Stamp Tree Ctrl object
     *
     **************************************************/
    CatalogTreeCtrl( ) { }


    /*
     * @brief Construct a new Catalog Tree Ctrl object
     *
     * @param parent
     * @param id
     * @param pos
     * @param size
     * @param style
     */
    CatalogTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~CatalogTreeCtrl( void ) { }

    /*
     * @brief OnBeginDrag
     *
     * @param event
     */
    void OnBeginDrag( wxTreeEvent& event );

    /*
     * @brief OnEndDrag
     *
     * @param event
     */
    void OnEndDrag( wxTreeEvent& event );

    /*
     * @brief  Show the dropdown menu for moving items in the catalog tree
     *
     * @param itemSrc
     * @param itemDst
     */
    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst );

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
    void OnSelChanged( wxTreeEvent& event );

    /*
     * @brief Event handler for when the item checkbox is clicked
     *
     * @param event
     */
    void OnItemStateClick( wxTreeEvent& event );

    //void OnItemRClick( wxTreeEvent& event );
    /*
     * @brief Create a item sState icon List object
     *
     */
    void CreateStateImageList( );

    /*
     * @brief Create a Image List object
     *
     */
    void CreateImageList( );

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
     * @brief Set the checkbox of the item to the next state. Saves the new state.
     Sends message to Album tree to update
     *
     * @param itemID
     */
    void SetNextState( const wxTreeItemId& itemID );

    /*
     * @brief Updates the item data and the link list with new id
     *
     * @param itemId
     * @return Utils::StampLink*
     */
    Utils::StampLink* AppendAlbumStamp( wxTreeItemId itemId );

    /*
     * @brief Deletes the item from the stamp link list and sends a message to
     the design tree to remove it.
     *
     * @param itemId
     */
    void DeleteAlbumStamp( wxTreeItemId itemId );

    /*
     * @brief removes the cat item id from the link list
     *
     * @param itemId
     */
    void RemoveStampLink( wxTreeItemId itemId );

    /*
     * @brief make a New Entry from the element in the item data
     *
     * @param itemId
     * @return Catalog::Entry*
     */
    Catalog::Entry* GetNewEntry( wxTreeItemId itemId );

    /*
     * @brief Set the item Inventory Status Icon
     *
     */
    void SetInventoryStatusImage( void );

    /*
     * @brief Get the CatalogImageSelection icon based on info in entry
     *
     * @param stamp
     * @return Catalog::IconID
     */
    Catalog::IconID GetInventoryIconId( Catalog::Entry* stamp );
    /*
     * @brief Show the popup menu for the cat tree
     *
     * @param id
     * @param pt
     */
    void ShowMenu( wxTreeItemId id, const wxPoint& pt );


    // int ImageSize( void ) const { return m_imageSize; };

    /*
     * @brief performs a std::cout dump from this item thru all children
     *
     * @param item
     * @param str
     */
    void XMLDumpNode( wxTreeItemId item, wxString str );

    //wxTreeItemId AddStampNodeToTree( wxTreeItemId parent, wxXmlNode* child );

    /*
     * @brief AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
     * create sort nodes as necessary to find the proper place for the child
     *
     * @param parent
     * @param child
     * @return wxTreeItemId
     */
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );

    /*
     * @brief Similar to AddChild except inserts before or after a given child.
     *
     * @param parent
     * @param child
     * @param after
     * @return wxTreeItemId
     */
    wxTreeItemId InsertChild( wxTreeItemId parent, wxXmlNode* child, bool after = true );

    /*
     * @brief Creates a new item user data for the child
     *
     * @param child
     * @param label
     * @param icon
     * @param nodeType
     * @return CatalogTreeItemData*
     */
    CatalogTreeItemData* CreateChildData( wxXmlNode* child,
        wxString& label,
        Catalog::IconID& icon,
        Catalog::CatalogBaseType& nodeType );

    /*
     * @brief Clears the entire tree
     *
     */
    void ClearCatalogTree( );

    /*
     * @brief Loads the tree with current catalog section data.
     *
     */
    void LoadTree( void );

    //wxString GetLabel( wxXmlNode* catalogSectionData );

    //wxTreeItemId AddTreeNode( wxTreeItemId parent, wxXmlNode* node );


/*
 * @brief SortTree decends through the tree and sorts the children of each item.
 *
 * @param parent
 */
    void SortTree( wxTreeItemId parent );
    
    /*
     * @brief Delete the tree and resort it with the new sort order data.
     * Probably doing this because the sort order was changed.
     *
     */
    void ReSortTree( );

    /*
     * @brief In Browser GoTo Colnect page for this item
     *
     * @param id
     */
    void GoToColnect( wxTreeItemId id );


    /*
     * @brief Popup up a dialog to add a new entry into the tree
     *
     * @param id
     */
    void AddEntry( wxTreeItemId id );

    /*
     * @brief Deletes the item from the tree
     *
     * @param id
     */
    void DeleteEntry( wxTreeItemId id );

    //void EditDetailsDialog( );

    wxTreeItemId FindTreeItemID( wxXmlNode* node );

    wxTreeItemId FindTreeItemID( wxXmlNode* node, wxTreeItemId id );

    bool IsElement( wxTreeItemId item, wxXmlNode* node );
    wxTreeItemId FindTreeItemID( wxString stampID );

    wxTreeItemId FindTreeItemID( wxString stampID, wxTreeItemId id );
    bool IsElement( wxTreeItemId item, wxString stampID );

    wxTreeItemId FindFirstEntryChild( wxTreeItemId id );

    /*
     * @brief Get the full filename of the image
     *
     * @param catID
     * @return wxString
     */
    wxString GetImageFullName( wxTreeItemId catID );

    /*
     * @brief Get the entry id of the stamp. This is typically a catalog id.
     *
     * @param catID
     * @return wxString
     */
    wxString GetIdText( wxTreeItemId catID );


    // wxXmlNode* GetNode( wxTreeItemId catID );

     /*
      * @brief Get the  value of the Attribute named name from item catId
      *
      * @param catID
      * @param name
      * @return wxString
      */
    wxString GetAttribute( wxTreeItemId catID, wxString name );

    /*
     * @brief An attempt to compare two date strings
     *
     * @param date1
     * @param date2
     * @return ComparisonResultType
     */
    ComparisonResultType CompareDates( wxString date1, wxString date2 );

    /*
     * @brief Tries to compare 2 tre entries. right now only looking at date and series.
     * Only used for sorting but could be much better.
     *
     * @param i1
     * @param i2
     * @return int
     */
    virtual int OnCompareItems( const wxTreeItemId& i1,
        const wxTreeItemId& i2 ) wxOVERRIDE;

    /*
     * @brief returns the stamp node associated with the item
     *
     * @param itemId
     * @return wxXmlNode*
     */
    wxXmlNode* GetEntryNode( wxTreeItemId itemId );

    //wxString GetEntryID( wxTreeItemId itemId );

    Utils::StampLink* FindStampLink( wxTreeItemId itemId );

    /* 
     * @brief If this tree id item is catalg entry id IDNbr then set the link
     * 
     * @param catID 
     * @param link 
     * @param IDNbr 
     */
    void SetCatalogLink( wxTreeItemId catID, Utils::StampLink* link, wxString IDNbr );

    void UpdateStamp( Stamp* newStamp, wxTreeItemId catID );

    /*
     * @brief Enables the check box on all the tree items
     * from itemId on down, so should start from root.
     *
     * @param id
     */
    void EnableState( wxTreeItemId id );

    /*
     * @brief Disables the check box on all the tree items
     * from itemId on down, so should start from root.
     *
     * @param id
     */
    void DisableState( wxTreeItemId id );

    /*
     * @brief calls EnableState or DisableState startig at root.
     *
     * @param enable
     */
    void SetStates( bool enable );
    bool StrSame( wxString str1, wxString str2 );

private:

    void LogEvent( const wxString& name, const wxTreeEvent& event );

    //    int m_imageSize;            // current size of images
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
