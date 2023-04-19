/**
 * @file gui/DesignTreeCtrl.h
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
 *
 **************************************************/

#ifndef DesignTreeCtrl_H
#define DesignTreeCtrl_H

#include "design/Stamp.h"
#include "design/TextBox.h"
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
    DesignTree_AddText,
    DesignTree_DeleteItem,
    DesignTree_EditDetails,
    DesignTree_Before,
    DesignTree_After,
    DesignTree_AsChild,
    DesignTree_Cancel
};

class Stamp;
namespace Utils { class StampLink; };


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
        Design::AlbumBase* ele = 0, Utils::StampLink* stampLink = 0 )
    {
        m_ok = 0x12345;
        m_type = type;
        m_desc = desc;
        m_element = ele;
        m_stampLink = stampLink;
    }

    DesignTreeItemData( DesignTreeItemData& data )
    {
        m_ok = 0x12345;
        m_type = data.GetType( );
        m_desc = data.GetDesc( );
        m_element = data.GetNodeElement( );
        m_stampLink = data.GetStampLink( );
    }

    ~DesignTreeItemData( )
    {
        m_ok = 0;
        m_type = Design::AT_None;
        m_desc = "";
        m_element = 0;
        m_stampLink = 0;
    }

    /**
     *
     * @return { wxString| :
     **************************************************/
    wxString GetDesc( ) const { return m_desc; };
    void SetDesc( wxString desc ) { m_desc = desc; };

    /**
     *
     * @param  ele :
     ***************************************************/
    void SetNodeElement( Design::AlbumBase* ele ) { m_element = ele; };


    bool IsOk( )
    {
        this->m_ok;
        if ( m_ok == 0x12345 )return true;
        return false;
    }
    /**
     *
     * @return { wxXmlNode*|  :
     **************************************************/
    Design::AlbumBase* GetNodeElement( void ) { return m_element; };

    /**
     *
     * @param   type :
     **************************************************/
    void SetType( Design::AlbumBaseType type ) { m_type = type; };

    /**
     *
     * @return { CatalogBaseType| :
     **************************************************/
    Design::AlbumBaseType GetType( ) { return m_type; };

    Utils::StampLink* GetStampLink( ) { return m_stampLink; };
    void SetStampLink( Utils::StampLink* link ) { m_stampLink = link; };

private:
    int m_ok;
    Design::AlbumBase* m_element;
    wxString m_desc;
    Design::AlbumBaseType m_type;
    Utils::StampLink* m_stampLink;

};

/**
 * @brief Tree for displaying Album design
 *
 **************************************************/
class DesignTreeCtrl : public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( DesignTreeCtrl )
    //    DECLARE_EVENT_TABLE( )

public:

    /**
     * @brief Construct a new Stamp Tree Ctrl object
     *
     **************************************************/
    DesignTreeCtrl( ) { m_OK = 0x12345; }

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
    virtual ~DesignTreeCtrl( void ) { m_OK = 0; }

    void OnDeleteItem( wxTreeItemId id );
    void DeleteItem( wxTreeItemId id );

    Design::AlbumBase* GetStampNode( wxTreeItemId itemID );

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

    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst, bool asChild = false );

    /**
     *
     * @param   event :
     **************************************************/
     //void OnContextMenu( wxContextMenuEvent& event );

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
    void CreateStateImageList( );
    void CreateImageList( );
    void UpdateStampList( );
    void UpdateStampList( wxTreeItemId& treeItemId );

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
     * @return { IconID|     :
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
     * @return { int|          :
     **************************************************/
    int ImageSize( void ) const { return m_imageSize; };

    /**
     *
     * @param   parent :
     * @param   child   :
     * @return { wxTreeItemId|      :
     **************************************************/
    wxTreeItemId AddStampNodeToTree( wxTreeItemId parent, wxXmlNode* child );


    void AddPageTreeItem( wxTreeItemId node );
    Design::Stamp* CreateNewStamp( wxTreeItemId catTreeID );
    Design::Stamp* AddStampTreeItem( wxTreeItemId node, Design::Stamp* stamp );
    void AddRowTreeItem( wxTreeItemId node );
    void AddColTreeItem( wxTreeItemId node );
    Utils::StampLink* AppendStamp( wxTreeItemId id );
    wxString GetImageFullPath( wxTreeItemId catTreeID );
    void UpdateItemPageLayout( wxTreeItemId id );
    Design::TextBox* CreateNewText( );
    Design::TextBox* AddTextTreeItem( wxTreeItemId parentID, Design::TextBox* newText );

    wxTreeItemId GetPage( wxTreeItemId id );
    void MakePage( wxTreeItemId id );

    /**
     *
     * @param   parent :
     * @param  child   :
     * @return { wxTreeItemId|      :
     */
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );


    /**
     * Load the Design tree with current xml document
     **************************************************/
    void LoadTree( void );

    void ClearDesignTree( );

    /**
     *
     * @param   catalogVolume :
     * @return { wxString|            :
     **************************************************/
    wxString GetLabel( Design::AlbumBase* catalogVolume );

    /**
     *
     * @param   parent :
     * @param   node    :
     * @return { wxTreeItemId|      :
     **************************************************/
    wxTreeItemId AddTreeNode( wxTreeItemId parent, Design::LayoutBase** node );


    /**
     *
     * @param   catalogVolume :
     * @param   parentType :
     * @return { wxArrayPtrVoid*|     :
     **************************************************/
    wxArrayPtrVoid* MakeParentList( Design::LayoutBase* catalogVolume,
        Catalog::FormatType parentType );

    /**
     *
     * @param   node :
     * @return { wxTreeItemId|   :
     **************************************************/
    wxTreeItemId FindTreeItemID( Design::AlbumBase* node );

    /**
     *
     * @param   node :
     * @param   id  :
     * @return { wxTreeItemId|   :
     **************************************************/
    wxTreeItemId FindTreeItemID( Design::AlbumBase* node, wxTreeItemId id );

    /**
     *
     * @param   item :
     * @param   node  :
     * @return { bool|            :
     **************************************************/
    bool IsElement( wxTreeItemId item, Design::AlbumBase* node );

    /**
     *
     * @param   id :
     * @return { wxTreeItemId|  :
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
    void ShowAlbumDetails( wxTreeItemId treeID, Design::AlbumBase* node );
    void ShowStampDetails( wxTreeItemId id );
    void ShowPageDetails( wxTreeItemId treeID, Design::AlbumBase* node );
    void ShowRowDetails( wxTreeItemId id, Design::AlbumBase* node );
    void ShowColDetails( wxTreeItemId id, Design::AlbumBase* node );
    void Validate( wxTreeItemId id );
    void ValidateTree( );
    void SetValidateStatus( bool status );
    void ResetValidateStatus( );
    bool GetValidateStatus( );
    //Utils::StampLink* GetStampLink( wxTreeItemId albumID );

    Design::AlbumBase* GetItemNode( wxTreeItemId albumID );
    wxString GetItemDesc( wxTreeItemId albumID );
    Utils::StampLink* GetItemStampLink( wxTreeItemId albumID );
    void SetItemStampLink( wxTreeItemId albumID, Utils::StampLink* link );
    Design::AlbumBaseType GetItemType( wxTreeItemId albumID );
    wxString MakeItemLabel( wxTreeItemId id );
    void CopyItem( wxTreeItemId dstID, wxTreeItemId srcID );
    void MoveItem( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    void Save( );
    void SaveNodeData( wxXmlNode* parent, wxTreeItemId treeItemId );



private:
    int m_OK;
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
    wxTreeItemId m_currPageID;
    bool ValidateStatus;
    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS( );
    //     if you want your overloaded OnCompareItems( ) to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default ( alphabetical ) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS( DesignTreeCtrl );
    wxDECLARE_EVENT_TABLE( );

};

#endif
