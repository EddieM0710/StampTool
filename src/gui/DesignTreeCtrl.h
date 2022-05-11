/**
 * @file gui/DesignTreeCtrl.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef DesignTreeCtrl_H
#define DesignTreeCtrl_H

#include "design/Stamp.h"
#include "design/AlbumBase.h"
#include "design/LayoutBase.h"
#include "design/DesignDefs.h"
#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include <wx/colour.h>
#include "gui/IconDefs.h"

 /**
  *
  *  @brief menu and control ids
  **************************************************/
enum
{
    DesignTree_Quit = wxID_EXIT,
    DesignTree_About = wxID_ABOUT,
    DesignTree_AddPage,
    DesignTree_AddCol,
    DesignTree_AddRow,
    DesignTree_AddStamp,
    DesignTree_AddTitle,
    DesignTree_DeleteItem,
    DesignTree_EditDetails,
};

class Stamp;
class Classification;
namespace Utils { class StampLink;};


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
class DesignTreeItemData : public wxTreeItemData
{
public:
    /**
     * @brief DesignTreeItemData Constructor
     *
     * @param   type    :
     * @param   desc    :
     * @param   ele :
     **************************************************/
    DesignTreeItemData( Design::AlbumBaseType type, const wxString desc,
        Design::AlbumBase* ele = 0 )
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
    void SetNodeElement( Design::AlbumBase* ele ) { m_element = ele; };



    /**
     *
     * @return {wxXmlNode*}    :
     **************************************************/
    Design::AlbumBase* GetNodeElement( void ) { return m_element; };

    /**
     *
     * @param   type :
     **************************************************/
    void SetType( Design::AlbumBaseType type ) { m_type = type; };

    /**
     *
     * @return {CatalogBaseType}   :
     **************************************************/
    Design::AlbumBaseType GetType( ) { return m_type; };

    Utils::StampLink* GetStampLink( ) { return m_stampLink; };
    void SetStampLink( Utils::StampLink* link ) { m_stampLink = link; };

private:
    Design::AlbumBase* m_element;
    wxString m_desc;
    Design::AlbumBaseType m_type;
    Utils::StampLink* m_stampLink;

};

/**
 * @brief Class to manage a wxTreeCtrl for Stamp
 *
 **************************************************/
class DesignTreeCtrl : public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( DesignTreeCtrl )
    //    DECLARE_EVENT_TABLE()

public:

    /**
     * @brief Construct a new Stamp Tree Ctrl object
     *
     **************************************************/
    DesignTreeCtrl( ) {}

    /**
     * DesignTreeCtrl Constructor
     *
     * @param   parent :
     * @param   id    :
     * @param   pos      :
     * @param   size      :
     * @param   style       :
     **************************************************/
    DesignTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    /**
     * ~DesignTreeCtrl
     *
     **************************************************/
    virtual ~DesignTreeCtrl( void ) {}


    void DeleteItem( wxTreeItemId id) ;
    
    Design::AlbumBase* GetStampNode(wxTreeItemId itemID);

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
      * @param  itemID :
      **************************************************/
    void SetNextState( const wxTreeItemId& itemID );



    void SetStatusImage( void );

    /**
     *
     * @param   stamp :
     * @return {IconID}       :
     **************************************************/
    Design::IconID GetIconId( Design::Stamp* stamp );

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


    void AddPage( Design::AlbumBase* node );
    Design::Stamp* AddStamp( Design::AlbumBase* node );
    void AddRow( Design::AlbumBase* node );
    void AddCol( Design::AlbumBase* node );
    Utils::StampLink* AppendStamp( wxTreeItemId id );

    /**
     *
     * @param   parent :
     * @param  child   :
     * @return {wxTreeItemId}        :
     */
    wxTreeItemId AddChild( wxTreeItemId parent, Design::AlbumBase* child );


    /**
     *
     **************************************************/
    void LoadTree( void );

    /**
     *
     * @param   catalogData :
     * @return {wxString}              :
     **************************************************/
    wxString GetLabel( Design::AlbumBase* catalogData );

    /**
     *
     * @param   parent :
     * @param   node    :
     * @return {wxTreeItemId}        :
     **************************************************/
    wxTreeItemId AddTreeNode( wxTreeItemId parent, Design::LayoutBase** node );


                    /**
                     *
                     * @param   catalogData :
                     * @param   parentType :
                     * @return {wxArrayPtrVoid*}       :
                     **************************************************/
    wxArrayPtrVoid* MakeParentList( Design::LayoutBase* catalogData,
        Catalog::FormatType parentType );

    /**
     *
     * @param   node :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( Design::AlbumBase* node );

    /**
     *
     * @param   node :
     * @param   id  :
     * @return {wxTreeItemId}     :
     **************************************************/
    wxTreeItemId FindTreeItemID( Design::AlbumBase* node, wxTreeItemId id );

    /**
     *
     * @param   item :
     * @param   node  :
     * @return {bool}              :
     **************************************************/
    bool IsElement( wxTreeItemId item, Design::AlbumBase* node );

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

    //  AlbumBase* MoveStamp( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    Design::LayoutBase* GetSelectedNode( );
    void ShowStampDetails( wxTreeItemId id, Design::AlbumBase* node );
    void Validate( wxTreeItemId id );
    void ValidateTree( );
    void SetValidateStatus( bool status );
    void ResetValidateStatus( );
    bool GetValidateStatus( );
    //Utils::StampLink* GetStampLink( wxTreeItemId albumID );

    Design::AlbumBase* GetItemNode( wxTreeItemId albumID ) ;
    wxString GetItemDesc( wxTreeItemId albumID ) ;
    Utils::StampLink* GetItemStampLink( wxTreeItemId albumID ) ;
    Design::AlbumBaseType GetItemType( wxTreeItemId albumID ) ; 
    wxString MakeItemLabel ( wxTreeItemId id );



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
    wxColour m_defaultBackgroundColour;
    bool ValidateStatus;
    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS();
    //     if you want your overloaded OnCompareItems() to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default (alphabetical) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS( DesignTreeCtrl );
    wxDECLARE_EVENT_TABLE( );

};

#endif
