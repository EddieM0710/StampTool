/**
 * @file gui/AlbumTreeCtrl.h
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
 */

#ifndef AlbumTreeCtrl_H
#define AlbumTreeCtrl_H

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
  */
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
 * data associated with each node in the tree
 *
 */
class DesignTreeItemData : public wxTreeItemData
{
public:

    ///  @brief Construct a new Design Tree Item Data object
    ///  
    ///  @param type 
    ///  @param desc 
    ///  @param ele 
    ///  @param stampLink 
    DesignTreeItemData( Design::AlbumBaseType type, const wxString desc,
        Design::AlbumBase* ele = 0, Utils::StampLink* stampLink = 0 )
    {
        m_ok = 0x12345;
        m_type = type;
        m_desc = desc;
        m_element = ele;
        m_stampLink = stampLink;
    }

    ///  @brief Construct a new Design Tree Item Data object
    ///  
    ///  @param data 
    DesignTreeItemData( DesignTreeItemData& data )
    {
        m_ok = 0x12345;
        m_type = data.GetType( );
        m_desc = data.GetDesc( );
        m_element = data.GetNodeElement( );
        m_stampLink = data.GetStampLink( );
    }

    ///  @brief Destroy the Design Tree Item Data object
    ///  
    ~DesignTreeItemData( )
    {
        m_ok = 0;
        m_type = Design::AT_None;
        m_desc = "";
        m_element = 0;
        m_stampLink = 0;
    }

    ///  @brief Get the Desc object
    ///  
    ///  @return wxString 
    wxString GetDesc( ) const { return m_desc; };

    ///  @brief Get the Node Element object
    ///  
    ///  @return Design::AlbumBase* 
    Design::AlbumBase* GetNodeElement( void ) { return m_element; };

    ///  @brief Get the Type object
    ///  
    ///  @return Design::AlbumBaseType 
    Design::AlbumBaseType GetType( ) { return m_type; };

    ///  @brief Get the Stamp Link object
    ///  
    ///  @return Utils::StampLink* 
    Utils::StampLink* GetStampLink( ) { return m_stampLink; };

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsOk( )
    {
        this->m_ok;
        if ( m_ok == 0x12345 )return true;
        return false;
    }

    ///  @brief Set the Desc object
    ///  
    ///  @param desc 
    void SetDesc( wxString desc ) { m_desc = desc; };

    ///  @brief Set the Node Element object
    ///  
    ///  @param ele 
    void SetNodeElement( Design::AlbumBase* ele ) { m_element = ele; };

    ///  @brief Set the Stamp Link object
    ///  
    ///  @param link 
    void SetStampLink( Utils::StampLink* link ) { m_stampLink = link; };

    ///  @brief Set the Type object
    ///  
    ///  @param type 
    void SetType( Design::AlbumBaseType type ) { m_type = type; };

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
 */
class AlbumTreeCtrl : public wxTreeCtrl
{

public:



    ///  @brief Construct a new Album Tree Ctrl object
    ///  
    AlbumTreeCtrl( ) { m_OK = 0x12345; }


    ///  @brief Construct a new Album Tree Ctrl object
    ///  
    ///  @param parent 
    ///  @param id 
    ///  @param pos 
    ///  @param size 
    ///  @param style 
    AlbumTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );


    ///  @brief Destroy the Album Tree Ctrl object
    ///  
    virtual ~AlbumTreeCtrl( void ) { m_OK = 0; }

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param child 
    ///  @return wxTreeItemId 
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );

    ///  @brief 
    ///  
    ///  @param node 
    void AddColTreeItem( wxTreeItemId node );

    ///  @brief 
    ///  
    ///  @param node 
    void AddPageTreeItem( wxTreeItemId node );

    ///  @brief 
    ///  
    ///  @param node 
    void AddRowTreeItem( wxTreeItemId node );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param child 
    ///  @return wxTreeItemId 
    wxTreeItemId AddStampNodeToTree( wxTreeItemId parent, wxXmlNode* child );

    ///  @brief 
    ///  
    ///  @param node 
    ///  @param stamp 
    ///  @return Design::Stamp* 
    Design::Stamp* AddStampTreeItem( wxTreeItemId node, Design::Stamp* stamp );

    ///  @brief 
    ///  
    ///  @param parentID 
    ///  @param newText 
    ///  @return Design::TextBox* 
    Design::TextBox* AddTextTreeItem( wxTreeItemId parentID, Design::TextBox* newText );

    ///  @brief 
    ///  
    ///  @param id 
    ///  @return Utils::StampLink* 
    Utils::StampLink* AppendStamp( wxTreeItemId id );

    ///  @brief 
    ///  
    void ClearDesignTree( );

    ///  @brief 
    ///  
    ///  @param dstID 
    ///  @param srcID 
    void CopyItem( wxTreeItemId dstID, wxTreeItemId srcID );

    ///  @brief Create a Image List object
    ///  
    void CreateImageList( );

    ///  @brief Create a New Stamp object
    ///  
    ///  @param catTreeID 
    ///  @return Design::Stamp* 
    Design::Stamp* CreateNewStamp( wxTreeItemId catTreeID );

    ///  @brief Create a New Text object
    ///  
    ///  @return Design::TextBox* 
    Design::TextBox* CreateNewText( );

    ///  @brief Create a State Image List object
    ///  
    void CreateStateImageList( );

    ///  @brief 
    ///  
    ///  @param id 
    void DeleteItem( wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param node 
    ///  @return wxTreeItemId 
    wxTreeItemId FindTreeItemID( Design::AlbumBase* node );

    ///  @brief 
    ///  
    ///  @param node 
    ///  @param id 
    ///  @return wxTreeItemId 
    wxTreeItemId FindTreeItemID( Design::AlbumBase* node, wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param id 
    ///  @return wxTreeItemId 
    wxTreeItemId FindFirstStampChild( wxTreeItemId id );

    ///  @brief Get the Icon Id object
    ///  
    ///  @param stamp 
    ///  @return Design::IconID 
    Design::IconID GetIconId( Design::Stamp* stamp );

    ///  @brief Get the Image Full Path object
    ///  
    ///  @param catTreeID 
    ///  @return wxString 
    wxString GetImageFullPath( wxTreeItemId catTreeID );

    ///  @brief Get the Item Desc object
    ///  
    ///  @param albumID 
    ///  @return wxString 
    wxString GetItemDesc( wxTreeItemId albumID );

    ///  @brief Get the Label object
    ///  
    ///  @param catalogVolume 
    ///  @return wxString 
    wxString GetLabel( Design::AlbumBase* catalogVolume );

    ///  @brief Get the Item Node object
    ///  
    ///  @param albumID 
    ///  @return Design::AlbumBase* 
    Design::AlbumBase* GetItemNode( wxTreeItemId albumID );

    ///  @brief Get the Item Stamp Link object
    ///  
    ///  @param albumID 
    ///  @return Utils::StampLink* 
    Utils::StampLink* GetItemStampLink( wxTreeItemId albumID );

    ///  @brief Set the Item Stamp Link object
    ///  
    ///  @param albumID 
    ///  @param link 
    void SetItemStampLink( wxTreeItemId albumID, Utils::StampLink* link );

    ///  @brief Get the Item Type object
    ///  
    ///  @param albumID 
    ///  @return Design::AlbumBaseType 
    Design::AlbumBaseType GetItemType( wxTreeItemId albumID );

    ///  @brief Get the Page object
    ///  
    ///  @param id 
    ///  @return wxTreeItemId 
    wxTreeItemId GetPage( wxTreeItemId id );

    ///  @brief Get the Selected Node object
    ///  
    ///  @return Design::LayoutBase* 
    Design::LayoutBase* GetSelectedNode( );

    ///  @brief Get the Stamp Node object
    ///  
    ///  @param itemID 
    ///  @return Design::AlbumBase* 
    Design::AlbumBase* GetStampNode( wxTreeItemId itemID );

    ///  @brief Get the Validate Status object
    ///  
    ///  @return true 
    ///  @return false 
    bool GetValidateStatus( );

    ///  @brief 
    ///  
    ///  @return int 
    int ImageSize( void ) const { return m_imageSize; };

    ///  @brief 
    ///  
    ///  @param item 
    ///  @param node 
    ///  @return true 
    ///  @return false 
    bool IsElement( wxTreeItemId item, Design::AlbumBase* node );

    ///  @brief 
    ///  
    void LoadTree( void );

    ///  @brief 
    ///  
    ///  @param id 
    ///  @return wxString 
    wxString MakeItemLabel( wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param itemSrc 
    ///  @param itemDst 
    void MoveItem( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    ///  @brief 
    ///  
    ///  @param id 
    void MakePage( wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param catalogVolume 
    ///  @param parentType 
    ///  @return wxArrayPtrVoid* 
    wxArrayPtrVoid* MakeParentList( Design::LayoutBase* catalogVolume,
        Catalog::FormatType parentType );

    ///  @brief 
    ///  
    ///  @param event 
    void OnBeginDrag( wxTreeEvent& event );

    ///  @brief 
    ///  
    ///  @param i1 
    ///  @param i2 
    ///  @return int 
    virtual int OnCompareItems( const wxTreeItemId& i1, const wxTreeItemId& i2 ) wxOVERRIDE;

    ///  @brief 
    ///  
    ///  @param event 
    void OnEndDrag( wxTreeEvent& event );

    ///  @brief 
    ///  
    ///  @param id 
    void OnDeleteItem( wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param event 
    void OnItemContextMenu( wxTreeEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnItemMenu( wxTreeEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnItemRClick( wxTreeEvent& event );

    ///  @brief 
    ///  
    ///  @param event 
    void OnItemStateClick( wxTreeEvent& event );

    ///  @brief Event handler for tree item selection change
    ///  
    ///  @param event 
    void OnSelChanged( wxTreeEvent& event );

    ///  @brief 
    ///  
    void ResetValidateStatus( );

    ///  @brief 
    ///  
    void Save( );

    ///  @brief 
    ///  
    ///  @param parent 
    ///  @param treeItemId 
    void SaveNodeData( wxXmlNode* parent, wxTreeItemId treeItemId );

    ///  @brief Set the Validate Status object
    ///  
    ///  @param status 
    void SetValidateStatus( bool status );

    ///  @brief 
    ///  
    ///  @param treeID 
    ///  @param node 
    void ShowAlbumDetails( wxTreeItemId treeID, Design::AlbumBase* node );

    ///  @brief 
    ///  
    ///  @param treeID 
    ///  @param node 
    void ShowPageDetails( wxTreeItemId treeID, Design::AlbumBase* node );

    ///  @brief 
    ///  
    ///  @param id 
    ///  @param node 
    void ShowColDetails( wxTreeItemId id, Design::AlbumBase* node );

    ///  @brief 
    ///  
    ///  @param itemSrc 
    ///  @param itemDst 
    ///  @param asChild 
    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst, bool asChild = false );

    ///  @brief 
    ///  
    ///  @param id 
    ///  @param pt 
    void ShowMenu( wxTreeItemId id, const wxPoint& pt );

    ///  @brief 
    ///  
    ///  @param id 
    void ShowStampDetails( wxTreeItemId id );

    ///  @brief 
    ///  
    ///  @param id 
    ///  @param node 
    void ShowRowDetails( wxTreeItemId id, Design::AlbumBase* node );

    ///  @brief 
    ///  
    ///  @param id 
    void UpdateItemPageLayout( wxTreeItemId id );

    ///  @brief 
    ///  
    void UpdateStampList( );

    ///  @brief 
    ///  
    ///  @param treeItemId 
    void UpdateStampList( wxTreeItemId& treeItemId );

    ///  @brief 
    ///  
    ///  @param childID 
    ///  @param ele 
    ///  @param icon 
    ///  @return Design::NodeStatus 
    Design::NodeStatus UpdateTreeItem( wxTreeItemId childID, Design::AlbumBase* ele, Design::IconID icon );

    ///  @brief 
    ///  
    ///  @param id 
    void Validate( wxTreeItemId id );

    ///  @brief 
    ///  
    void ValidateTree( );

    ///  @brief 
    ///  
    ///  @param childId 
    ///  @param albIDNbr 
    void ValidateLink( wxTreeItemId& childId, wxString albIDNbr );

private:
    int m_OK;
    /**
     * @brief
     *
     * @param  name
     * @param  event
     */
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
    wxDECLARE_DYNAMIC_CLASS( AlbumTreeCtrl );
    wxDECLARE_EVENT_TABLE( );

};

#endif
