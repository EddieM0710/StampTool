/**
 * @file gui/AlbumTreeCtrl.h
 * @author Eddie Monroe ()
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 **************************************************/

#ifndef AlbumTreeCtrl_H
#define AlbumTreeCtrl_H

#include "album/Stamp.h"
#include "album/AlbumNode.h"
#include "album/LayoutNode.h"
#include "album/AlbumDefs.h"
#include <wx/treectrl.h>
#include <wx/imaglist.h>


/**
 * 
 *  @brief menu and control ids
 **************************************************/ 
enum
{
    AlbumDataTree_Quit = wxID_EXIT,
    AlbumDataTree_About = wxID_ABOUT,
    AlbumDataTree_AddPage,
    AlbumDataTree_AddCol,
    AlbumDataTree_AddRow,
    AlbumDataTree_AddStamp,
    AlbumDataTree_AddTitle,
    AlbumDataTree_DeleteItem,
    AlbumDataTree_EditDetails,
};


typedef enum
{
    Icon_Stamp = 0,
    Icon_StampSelected,
    Icon_StampBlock,
    Icon_StampBlockSelected,
    Icon_StampMiniSheet,
    Icon_StampMiniSheetSelected,
    Icon_StampSouvenirSheet,
    Icon_StampSouvenirSheetSelected,
    Icon_Folder
} IconID;

class Stamp;
class Classification;


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
class AlbumTreeItemData : public wxTreeItemData
{
  public:
    /**
     * @brief AlbumTreeItemData Constructor
     *
     * @param   type    :
     * @param   desc    :
     * @param   ele :
     **************************************************/
    AlbumTreeItemData( Layout::AlbumNodeType type, const wxString desc,
                       Layout::AlbumNode* ele = 0 )
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
    void SetNodeElement( Layout::AlbumNode* ele ) { m_element = ele; };



    /**
     * 
     * @return {wxXmlNode*}    : 
     **************************************************/
    Layout::AlbumNode* GetNodeElement( void ) { return m_element; };

    /**
     *
     * @param   type :
     **************************************************/
    void SetType( Layout::AlbumNodeType type ) { m_type = type; };

    /**
     *
     * @return {CatalogNodeType}   :
     **************************************************/
    Layout::AlbumNodeType GetType( ) { return m_type; };

  private:
    Layout::AlbumNode* m_element;
    wxString m_desc;
    Layout::AlbumNodeType m_type;
};

/**
 * @brief Class to manage a wxTreeCtrl for Stamp
 * 
 **************************************************/
class AlbumTreeCtrl : public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( AlbumTreeCtrl )
    //    DECLARE_EVENT_TABLE()

  public:

  /**
   * @brief Construct a new Stamp Tree Ctrl object
   * 
   **************************************************/
    AlbumTreeCtrl( ) {}

    /**
     * AlbumTreeCtrl Constructor
     *
     * @param   parent :
     * @param   id    :
     * @param   pos      :
     * @param   size      :
     * @param   style       :
     **************************************************/
    AlbumTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
                   const wxSize& size, long style );

    /**
     * ~AlbumTreeCtrl 
     * 
     **************************************************/
    virtual ~AlbumTreeCtrl( void ) {}

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
    void CreateStateImageList( bool del);
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
    // void DoSortChildren( const wxTreeItemId& item, bool reverse = true )
    // {
    //     m_reverseSort = reverse;
    //     wxTreeCtrl::SortChildren( item );
    // };

    /**
     *
     * @param  itemID :
     **************************************************/
    void SetNextState( const wxTreeItemId& itemID );



    void SetStatusImage( void );

    /**
     *
     * @param   stamp :
     * @return {IconID}       :
     **************************************************/
    IconID GetIconId( Layout::Stamp* stamp );

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
    wxTreeItemId AddChild( wxTreeItemId parent,  Layout::AlbumNode* child );


    /**
     * 
     **************************************************/
    void LoadTree(void );

    /**
     *
     * @param   catalogData :
     * @return {wxString}              :
     **************************************************/
    wxString GetLabel(  Layout::AlbumNode* catalogData );

    /**
     *
     * @param   parent :
     * @param   node    :
     * @return {wxTreeItemId}        :
     **************************************************/
    wxTreeItemId AddTreeNode( wxTreeItemId parent, Layout::LayoutNode** node );

    /**
     *
     * @param   parent :
     **************************************************/
//    void SortTree( wxTreeItemId parent );

    /**
     *
     **************************************************/
//    void ReSortTree( );

    /**
     *
     * @param   catalogData :
     **************************************************/
//    void StructureStamp( wxXmlNode* catalogData );


    /**
     * StructureCatalogData 
     * @param   catalogData      : 
     * @param  parentType      : 
     * @param  childType       : 
     * @param   secondChildType : 
     **************************************************/
    // void StructureCatalogData( wxXmlNode* catalogData, FormatType parentType,
    //                          FormatType childType,
    //                          FormatType secondChildType = FT_FormatUnknown );


    /**
     * 
     * @param   catalogData : 
     * @param   parentType : 
     * @return {wxArrayPtrVoid*}       : 
     **************************************************/
    wxArrayPtrVoid* MakeParentList( Layout::LayoutNode* catalogData,
                                    Catalog::FormatType parentType );

    /**
     *
     * @param   node :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( Layout::AlbumNode* node );

    /**
     *
     * @param   node :
     * @param   id  :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( Layout::AlbumNode* node, wxTreeItemId id );

    /**
     *
     * @param   item :
     * @param   node  :
     * @return {bool}              :
     **************************************************/
    bool IsElement( wxTreeItemId item, Layout::AlbumNode* node );

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

  //  AlbumNode* MoveStamp( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    Layout::LayoutNode* GetSelectedNode( );
    void ShowStampDetails( Layout::AlbumNode* node );

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
    wxDECLARE_DYNAMIC_CLASS( AlbumTreeCtrl );
    wxDECLARE_EVENT_TABLE( );

    // wxXmlDocument *m_stampDoc;
};

#endif
