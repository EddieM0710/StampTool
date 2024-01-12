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
namespace Utils {
    class StampLink;
};


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
    wxString GetDesc( ) const {
        return m_desc;
    };

    ///  @brief Get the Node Element object
    ///  
    ///  @return Design::AlbumBase* 
    Design::AlbumBase* GetNodeElement( void ) {
        return m_element;
    };


    ///  @brief Get the Type object
    ///  
    ///  @return Design::AlbumBaseType 
    Design::AlbumBaseType GetType( ) {
        if ( !IsOk( ) )
        {
            int a = 0;
        }
        return m_type;
    };

    ///  @brief Get the Stamp Link object
    ///  
    ///  @return Utils::StampLink* 
    Utils::StampLink* GetStampLink( ) {
        if ( !IsOk( ) )
        {
            int a = 0;
        }
        return m_stampLink;
    };

    ///  @brief 
    ///  
    ///  @return true 
    ///  @return false 
    bool IsOk( )
    {
        if ( m_ok == 0x12345 )return true;
        return false;
    }

    ///  @brief Set the Desc object
    ///  
    ///  @param desc 
    void SetDesc( wxString desc ) {
        if ( !IsOk( ) )
        {
            int a = 0;
        }
        m_desc = desc;
    };

    ///  @brief Set the Node Element object
    ///  
    ///  @param ele 
    void SetNodeElement( Design::AlbumBase* ele ) {
        if ( !IsOk( ) )
        {
            int a = 0;
        }
        m_element = ele;
    };

    ///  @brief Set the Stamp Link object
    ///  
    ///  @param link 
    void SetStampLink( Utils::StampLink* link );


    ///  @brief Set the Type object
    ///  
    ///  @param type 
    void SetType( Design::AlbumBaseType type ) {
        if ( !IsOk( ) )
        {
            int a = 0;
        }
        m_type = type;
    };

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



    AlbumTreeCtrl( ) {
        m_OK = 0x12345;
    }

    AlbumTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );


    virtual ~AlbumTreeCtrl( void ) {
        m_OK = 0;
    }

    bool IsOk( )
    {
        if ( m_OK == 0x12345 )return true;
        return false;
    }

    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );

    wxTreeItemId AddNode( Design::AlbumBaseType nodeType, wxTreeItemId parent, wxXmlNode* child );

    void AddColTreeItem( wxTreeItemId node );

    void AddPageTreeItem( wxTreeItemId node );

    void AddRowTreeItem( wxTreeItemId node );

    wxTreeItemId AddStampNodeToTree( wxTreeItemId parent, wxXmlNode* child );

    Design::Stamp* AddStampTreeItem( wxTreeItemId node, Design::Stamp* stamp );

    Design::TextBox* AddTextTreeItem( wxTreeItemId parentID, Design::TextBox* newText );

    Utils::StampLink* AppendStamp( wxTreeItemId id );

    void Clear( );

    void CopyItem( wxTreeItemId dstID, wxTreeItemId srcID );

    void CreateImageList( );

    Design::Stamp* CreateNewStamp( wxTreeItemId catTreeID );

    Design::TextBox* CreateNewText( );

    void CreateStateImageList( );

    void DeleteItem( wxTreeItemId id );

    wxTreeItemId FindTreeItemID( Design::AlbumBase* node );

    wxTreeItemId FindTreeItemID( Design::AlbumBase* node, wxTreeItemId id );

    wxTreeItemId FindFirstStampChild( wxTreeItemId id );

    wxTreeItemId GetCurrentTreeID( ) {
        return m_currentTreeID;
    };

    wxTreeItemId GetPageTreeID( ) {
        return m_currPageID;
    };
    Design::IconID GetIconId( Design::Stamp* stamp );

    //wxString GetImageFullPath( wxTreeItemId catTreeID );

    wxString GetItemDesc( wxTreeItemId albumID );

    wxString GetLabel( Design::AlbumBase* catalogVolume );

    Design::AlbumBase* GetItemNode( wxTreeItemId albumID );

    Utils::StampLink* GetItemStampLink( wxTreeItemId albumID );

    Design::AlbumBaseType GetItemType( wxTreeItemId albumID );

    wxTreeItemId GetPage( wxTreeItemId id );

    Design::LayoutBase* GetSelectedNode( );

    Design::AlbumBase* GetStampNode( wxTreeItemId itemID );

    bool GetValidateStatus( );

    int ImageSize( void ) const {
        return m_imageSize;
    };

    bool IsElement( wxTreeItemId item, Design::AlbumBase* node );

    void LoadTree( void );

    wxString MakeItemLabel( wxTreeItemId id );

    void MoveItem( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    void MakePage( wxTreeItemId id );

    wxArrayPtrVoid* MakeParentList( Design::LayoutBase* catalogVolume,
        Catalog::FormatType parentType );

    void OnBeginDrag( wxTreeEvent& event );

    virtual int OnCompareItems( const wxTreeItemId& i1, const wxTreeItemId& i2 ) wxOVERRIDE;

    void OnEndDrag( wxTreeEvent& event );

    void OnDeleteItem( wxTreeItemId id );

    void OnItemContextMenu( wxTreeEvent& event );

    void OnItemMenu( wxTreeEvent& event );

    void OnItemRClick( wxTreeEvent& event );

    void OnItemStateClick( wxTreeEvent& event );

    void OnSelChanged( wxTreeEvent& event );

    void OnTreectrlItemCollapsed( wxTreeEvent& event );

    void OnTreectrlItemExpanded( wxTreeEvent& event );

    void ResetValidateStatus( );

    void Save( );

    void SaveNodeData( wxXmlNode* parent, wxTreeItemId treeItemId );

    void SetItemStampLink( wxTreeItemId albumID, Utils::StampLink* link );

    void SetValidateStatus( bool status );

    // void ShowAlbumDetails( wxTreeItemId treeID, Design::AlbumBase* node );

    // void ShowPageDetails( wxTreeItemId treeID, Design::AlbumBase* node );

    // void ShowColDetails( wxTreeItemId id, Design::AlbumBase* node );

    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst, bool asChild = false );

    void ShowMenu( wxTreeItemId id, const wxPoint& pt );

    // void ShowStampDetails( wxTreeItemId id );

    // void ShowRowDetails( wxTreeItemId id, Design::AlbumBase* node );
    void Update( );

    void UpdateItemPageLayout( wxTreeItemId id );

    void UpdateStampList( );

    void UpdateStampList( wxTreeItemId& treeItemId );

    Design::NodeStatus UpdateTreeItem( wxTreeItemId childID, Design::AlbumBase* ele, Design::IconID icon );

    void Validate( wxTreeItemId id );

    void ValidateTree( );

    void ValidateLink( wxTreeItemId& childId, wxString albIDNbr );

    void UpdateAlbumStampEntries( wxTreeItemId treeID );

private:
    int m_OK;

    void LogEvent( const wxString& name, const wxTreeEvent& event );

    int m_imageSize;            // current size of images
    bool m_reverseSort;         // flag for OnCompareItems
    wxTreeItemId m_draggedItem; // item being dragged right now
    wxColour m_defaultBackgroundColour;
    wxTreeItemId m_currPageID;
    bool ValidateStatus;
    wxTreeItemId m_currentTreeID;

    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS( );
    //     if you want your overloaded OnCompareItems( ) to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default ( alphabetical ) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS( AlbumTreeCtrl );
    wxDECLARE_EVENT_TABLE( );

};

#endif
