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

#include "catalog/Stamp.h"
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
    CatalogDataTree_ResortTree
};


class Stamp;
class Classification;
namespace Utils { class StampLink; }

/**
 *
 * @todo  fix variable names so that wxXmlNode refs are called elements,
 * stamps, classifications, etc are called nodes;  and Tree item references are called items.
 * @todo  ?? mostly done. watch for needed changes
 *
 **************************************************/


 /**
  * data associated with each node in the tree
  *
  **************************************************/
class CatalogTreeItemData : public wxTreeItemData
{
public:
    /**
     * @brief CatalogTreeItemData Constructor
     *
     * @param   type    :
     * @param   desc    :
     * @param   ele :
     **************************************************/
    CatalogTreeItemData( Catalog::CatalogBaseType type, const wxString desc,
        wxXmlNode* ele = 0 )
    {
        m_type = type;
        m_desc = desc;
        m_element = ele;
    }
    /**
     *
     * @return {wxString}   :
     **************************************************/
    wxString const& GetDesc( ) const { return m_desc; };

    /**
     *
     * @param  ele :
     ***************************************************/
    void SetCatNode( wxXmlNode* ele ) { m_element = ele; };



    /**
     *
     * @return {wxXmlNode*}    :
     **************************************************/
    wxXmlNode* GetNodeElement( void ) { return m_element; };

    /**
     *
     * @param   type :
     **************************************************/
    void SetType( Catalog::CatalogBaseType type ) { m_type = type; };

    /**
     *
     * @return {CatalogBaseType}   :
     **************************************************/
    Catalog::CatalogBaseType GetType( ) { return m_type; };

    Utils::StampLink* GetStampLink( ) { return m_stampLink; }
    void SetStampLink( Utils::StampLink* link ) { m_stampLink = link; }

private:
    wxXmlNode* m_element;
    wxString m_desc;
    Catalog::CatalogBaseType m_type;
    Utils::StampLink* m_stampLink;
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

    /**
     * CatalogTreeCtrl Constructor
     *
     * @param   parent :
     * @param   id    :
     * @param   pos      :
     * @param   size      :
     * @param   style       :
     **************************************************/
    CatalogTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    /**
     * ~CatalogTreeCtrl
     *
     **************************************************/
    virtual ~CatalogTreeCtrl( void ) {}

    /**
     *
     * @param   event :
     **************************************************/
    void OnBeginDrag( wxTreeEvent& event );

    /**
     * @brief
     *
    * @param   event :
    **************************************************/
    void OnEndDrag( wxTreeEvent& event );

    /**
     *
     * @param   event :
     **************************************************/
    void OnContextMenu( wxContextMenuEvent& event );

    /**
     *
     * @param  event :
     *******************************************bool del*******/
    void OnItemMenu( wxTreeEvent& event );

    /**
     * @brief Event handler for tree item selection change
     * @param   event :
     **************************************************/
    void OnSelChanged( wxTreeEvent& event );

    /**
     *
     * @param   event :
     **************************************************/
    void OnItemStateClick( wxTreeEvent& event );

    /**
     *
     * @param   event :
     **************************************************/
    void OnItemRClick( wxTreeEvent& event );

    /**
     *
     * @param   event :
     **************************************************/
    void OnItemContextMenu( wxTreeEvent& event );

    /**
     *
     **************************************************/
    void CreateStateImageList( bool del );
    void CreateImageList( );

    /**
     *
     **************************************************/
    void DoTreeContextSelection( );

    /**
     *
     * @param   item :
     * @param   reverse      :
     **************************************************/
    void DoSortChildren( const wxTreeItemId& item, bool reverse = true )
    {
        m_reverseSort = reverse;
        wxTreeCtrl::SortChildren( item );
    };

    /**
     *
     * @param  itemID :
     **************************************************/
    void SetNextState( const wxTreeItemId& itemID );
    Utils::StampLink* AppendAlbumStamp( wxTreeItemId itemId );
    void DeleteAlbumStamp( wxTreeItemId itemId );
    void RemoveStampLink( wxTreeItemId itemId );


    /**
     *
     **************************************************/
    void SetStatusImage( void );

    /**
     *
     * @param   stamp :
     * @return {IconID}       :
     **************************************************/
    IconID GetIconId( Catalog::Stamp* stamp );

    /**
     *
     * @param   id :
     * @param   pt      :
     **************************************************/
    void ShowMenu( wxTreeItemId id, const wxPoint& pt );

    /**
     *
     * @return {int}            :
     **************************************************/
    int ImageSize( void ) const { return m_imageSize; };

    /**
     *
     * @param   parent :
     * @param   child   :
     * @return {wxTreeItemId}        :
     **************************************************/
    wxTreeItemId AddStampNodeToTree( wxTreeItemId parent, wxXmlNode* child );

    /**
     *
     * @param   parent :
     * @param  child   :
     * @return {wxTreeItemId}        :
     */
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );

    void ClearCatalogTree( );   

    /**
     *
     **************************************************/
    void LoadTree( void );

    /**
     *
     * @param   catalogData :
     * @return {wxString}              :
     **************************************************/
    wxString GetLabel( wxXmlNode* catalogData );

    /**
     *
     * @param   parent :
     * @param   node    :
     * @return {wxTreeItemId}        :
     **************************************************/
    wxTreeItemId AddTreeNode( wxTreeItemId parent, wxXmlNode* node );

    /**
     *
     * @param   parent :
     **************************************************/
    void SortTree( wxTreeItemId parent );

    /**
     *
     **************************************************/
    void ReSortTree( );

    /**
     *
     * @param   catalogData :
     **************************************************/
    void StructureStamp( wxXmlNode* catalogData );


    /**
     * StructureCatalogData
     * @param   catalogData      :
     * @param  parentType      :
     * @param  childType       :
     * @param   secondChildType :
     **************************************************/
    void StructureCatalogData( wxXmlNode* catalogData, Catalog::FormatType parentType,
        Catalog::FormatType childType,
        Catalog::FormatType secondChildType = Catalog::FT_FormatUnknown );


    /**
     *
     * @param   catalogData :
     * @param   parentType :
     * @return {wxArrayPtrVoid*}       :
     **************************************************/
    wxArrayPtrVoid* MakeParentList( wxXmlNode* catalogData,
        Catalog::FormatType parentType );

    /**
     *
     * @param   node :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( wxXmlNode* node );

    /**
     *
     * @param   node :
     * @param   id  :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( wxXmlNode* node, wxTreeItemId id );

    /**
     *
     * @param   item :
     * @param   node  :
     * @return {bool}              :
     **************************************************/
    bool IsElement( wxTreeItemId item, wxXmlNode* node );



    /**
     *
     * @param   node :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( wxString stampID );

    /**
     *
     * @param   node :
     * @param   id  :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( wxString stampID, wxTreeItemId id );

    /**
     *
     * @param   item :
     * @param   node  :
     * @return {bool}              :
     **************************************************/
    bool IsElement( wxTreeItemId item, wxString stampID );



    /**
     *
     * @param   id :
     * @return {wxTreeItemId}    :
     **************************************************/
    wxTreeItemId FindFirstStampChild( wxTreeItemId id );


    /**
     * @brief
     *
     * @param  i1
     * @param  i2
     * @return int
     **************************************************/
    virtual int OnCompareItems( const wxTreeItemId& i1,
        const wxTreeItemId& i2 ) wxOVERRIDE;


    wxXmlNode* GetStampNode( wxTreeItemId itemId );
    wxString GetStampID( wxTreeItemId itemId );
    Utils::StampLink* FindStampLink( wxTreeItemId itemId );
    void EnableState( wxTreeItemId id );
    void DisableState( wxTreeItemId id );
    void SetStates( bool enable );

private:

    /**
     * @brief
     *
     * @param  name
     * @param  event
     **************************************************/
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

    // wxXmlDocument *m_stampDoc;
};

#endif
