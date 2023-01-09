/**
 * @file gui/CatalogTreeCtrl.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef CatalogTreeCtrl_H
#define CatalogTreeCtrl_H

#include "catalog/Entry.h"
#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include "gui/IconDefs.h"

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
class CatalogTreeItemData : public wxTreeItemData
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

    wxString* GetImageFullName(){ return m_imageFullPath;};
    void SetImageFullName(wxString* str ){ m_imageFullPath = str;};
private:
    wxXmlNode* m_element;
    wxString m_desc;
    Catalog::CatalogBaseType m_type;
    Utils::StampLink* m_stampLink;
    wxString* m_imageFullPath;
};

/**
 * @brief Class to manage a wxTreeCtrl for Stamp
 *
 **************************************************/
class CatalogTreeCtrl : public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( CatalogTreeCtrl )
    //    DECLARE_EVENT_TABLE()

public:

    /**
     * @brief Construct a new Stamp Tree Ctrl object
     *
     **************************************************/
    CatalogTreeCtrl( ) {}

    
    CatalogTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~CatalogTreeCtrl( void ) {}

    void OnBeginDrag( wxTreeEvent& event );
    void OnEndDrag( wxTreeEvent& event );
    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst  );


    void OnItemMenu( wxTreeEvent& event );
    void OnSelChanged( wxTreeEvent& event );
    void OnItemStateClick( wxTreeEvent& event );
    void OnItemRClick( wxTreeEvent& event );
    void OnItemContextMenu( wxTreeEvent& event );
    void CreateStateImageList( bool del );
    void CreateImageList( );
    void DoTreeContextSelection( );
    void DoSortChildren( const wxTreeItemId& item, bool reverse = true )
    {
        m_reverseSort = reverse;
        wxTreeCtrl::SortChildren( item );
    };

    void SetNextState( const wxTreeItemId& itemID );
    Utils::StampLink* AppendAlbumStamp( wxTreeItemId itemId );
    void DeleteAlbumStamp( wxTreeItemId itemId );
    void RemoveStampLink( wxTreeItemId itemId );

    Catalog::Entry* GetNewEntry( wxTreeItemId itemId );
    void SetInventoryStatusImage( void );
    Catalog::IconID GetInventoryIconId( Catalog::Entry* stamp );
    void ShowMenu( wxTreeItemId id, const wxPoint& pt );

    int ImageSize( void ) const { return m_imageSize; };
    void XMLDumpNode(  wxTreeItemId item, wxString str  );

    wxTreeItemId AddStampNodeToTree( wxTreeItemId parent, wxXmlNode* child );
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );
    wxTreeItemId InsertChild( wxTreeItemId parent, wxXmlNode* child, bool after = true );
    CatalogTreeItemData* CreateChildData( wxXmlNode* child, 
                        wxString& label, 
                        Catalog::IconID& icon,
                        Catalog::CatalogBaseType& nodeType );
    void ClearCatalogTree( );   
    void LoadTree( void );
    wxString GetLabel( wxXmlNode* catalogVolumeData );

    wxTreeItemId AddTreeNode( wxTreeItemId parent, wxXmlNode* node );
    void SortTree( wxTreeItemId parent );
    void ReSortTree( );
    void GoToColnect( wxTreeItemId id );
    void AddEntry( wxTreeItemId id );
    void DeleteEntry( wxTreeItemId id );

    wxTreeItemId FindTreeItemID( wxXmlNode* node );

    wxTreeItemId FindTreeItemID( wxXmlNode* node, wxTreeItemId id );

    bool IsElement( wxTreeItemId item, wxXmlNode* node );
    wxTreeItemId FindTreeItemID( wxString stampID );

    wxTreeItemId FindTreeItemID( wxString stampID, wxTreeItemId id );
    bool IsElement( wxTreeItemId item, wxString stampID );
    wxTreeItemId FindFirstEntryChild( wxTreeItemId id );

    wxString GetImageFullName( wxTreeItemId catID );
    wxString GetIdText( wxTreeItemId catID );
    wxXmlNode* GetNode(  wxTreeItemId catID );       
    wxString GetAttribute(  wxTreeItemId catID, wxString name );

    ComparisonResultType CompareDates(wxString date1,wxString date2 );

    virtual int OnCompareItems( const wxTreeItemId& i1,
        const wxTreeItemId& i2 ) wxOVERRIDE;


    wxXmlNode* GetEntryNode( wxTreeItemId itemId );
    wxString GetEntryID( wxTreeItemId itemId );
    Utils::StampLink* FindStampLink( wxTreeItemId itemId );
    void EnableState( wxTreeItemId id );
    void DisableState( wxTreeItemId id );
    void SetStates( bool enable );
    bool StrSame(wxString str1, wxString str2 );

private:

    void LogEvent( const wxString& name, const wxTreeEvent& event );

    int m_imageSize;            // current size of images
    bool m_reverseSort;         // flag for OnCompareItems
    wxTreeItemId m_draggedItem; // item being dragged right now

    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS();
    //     if you want your overloaded OnCompareItems() to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default (alphabetical) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS( CatalogTreeCtrl );
    wxDECLARE_EVENT_TABLE( );
};

#endif
