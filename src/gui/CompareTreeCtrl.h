/**
 * @file gui/CompareTreeCtrl.h
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
#ifndef CompareTreeCtrl_H
#define CompareTreeCtrl_H

#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include "gui/IconDefs.h"
#include "gui/GuiUtils.h"
#include "catalog/Entry.h"
#include "catalog/MergeList.h"
#include "design/AlbumBase.h"



class Stamp;
class CompareEntry;
class CompareTreeCtrl;


//-------------
class CompareTreeItemData : public wxTreeItemData
{
public:

    CompareTreeItemData( wxWindow* parent, Catalog::CatalogBaseType type, const wxString desc, wxXmlNode* targetNode = 0, wxXmlNode* mergeNode = 0 );

    ~CompareTreeItemData( )
    {
        m_ok = 0;
    };

    int Cmp( CompareTreeItemData* itemData2 );

    wxString const& GetDesc( ) const {
        return m_desc;
    };

    wxString GetImageFullName( ) {
        return m_imageFullPath;
    };

    wxXmlNode* GetNodeElement( void ) {
        return m_element;
    };


    Catalog::CatalogBaseType GetType( ) {
        return m_type;
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


    void SetImageFullName( wxString str ) {
        m_imageFullPath = str;
    };

    void SetMergeData( Catalog::MergeData* mergeData )
    {
        m_mergeData = mergeData;
    }

    Catalog::MergeData* GetMergeData( )
    {
        return m_mergeData;
    }

    void SetTargetEntry( wxXmlNode* node )
    {
        m_mergeData->SetTargetEntry( node );
    }

private:
    CompareTreeCtrl* m_parent;
    Catalog::MergeData* m_mergeData;
    double m_ok;
    wxXmlNode* m_element;
    wxString m_desc;
    Catalog::CatalogBaseType m_type;
    wxString m_imageFullPath;
};


//-----------

class CompareTreeCtrl : public wxTreeCtrl
{
    //    DECLARE_DYNAMIC_CLASS( CompareTreeCtrl )
    //    DECLARE_EVENT_TABLE( )

public:
    enum
    {
        CatalogListTree_Quit = wxID_EXIT,
        CatalogListTree_About = wxID_ABOUT,
        CatalogListTree_Colnect

    };



    CompareTreeCtrl( ) { }

    CompareTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~CompareTreeCtrl( void ) { }

    /// @brief AddChild adds wxXmlNode as a item in the tree.  It is recursively called to
    /// create sort nodes as necessary to find the proper place for the child
    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child );

    Catalog::IconID GetIconId( Catalog::Entry* entry, Catalog::MergeStatus status );

    void AddEntry( wxTreeItemId id );

    void Clear( );

    ComparisonResultType CompareDates( wxString date1, wxString date2 );

    CompareTreeItemData* CreateChildData( wxXmlNode* targetNode, wxXmlNode* mergeNode,
        wxString& label,
        Catalog::IconID& icon,
        Catalog::CatalogBaseType& nodeType );

    void CreateStateImageList( );

    void CreateImageList( );


    wxTreeItemId FindFirstEntryChild( wxTreeItemId id );

    wxTreeItemId FindTreeItemID( wxXmlNode* node );

    wxTreeItemId FindTreeItemID( wxXmlNode* node, wxTreeItemId id );

    wxTreeItemId FindTreeItemID( wxString stampID );

    wxTreeItemId FindTreeItemID( wxString stampID, wxTreeItemId id );

    wxString GetAttribute( wxTreeItemId catTreeID, wxString name );

    wxString GetID( wxTreeItemId catTreeID );

    wxString GetImage( wxTreeItemId catTreeID );

    wxString GetImageFullName( wxTreeItemId catTreeID );

    wxString GetItemDesc( wxTreeItemId id );

    wxString GetItemImageFullName( wxTreeItemId id );

    wxXmlNode* GetItemNode( wxTreeItemId id );


    Catalog::CatalogBaseType GetItemType( wxTreeItemId id );

    wxXmlNode* GetNewEntry( wxTreeItemId itemId );

    wxXmlNode* GetSelectionNode( );

    void GoToColnect( wxTreeItemId id );

    wxTreeItemId InsertChild( wxTreeItemId parent, wxXmlNode* child, bool after = true );

    bool IsElement( wxTreeItemId item, wxString stampID );

    bool IsElement( wxTreeItemId item, wxXmlNode* node );

    void LoadCompareTree( wxXmlNode* root );

    virtual int OnCompareItems( const wxTreeItemId& i1, const wxTreeItemId& i2 ) wxOVERRIDE;

    void OnItemMenu( wxTreeEvent& event );

    void OnSelChanged( wxTreeEvent& event );

    wxString GetDesc( wxTreeItemId item );

    wxTreeItemId FindNextItem( wxTreeItemId itemId );

    wxTreeItemId FindPrevItem( wxTreeItemId itemId );

    wxTreeItemId FindNextEntryItem( wxTreeItemId itemId );

    wxTreeItemId FindPrevEntryItem( wxTreeItemId itemId );

    bool IsEntryNode( wxTreeItemId itemId );

    void OnTreectrlItemCollapsed( wxTreeEvent& event );

    void OnTreectrlItemExpanded( wxTreeEvent& event );

    void SetAttribute( wxTreeItemId catTreeID, wxString name, wxString val );

    void SelectStamp( wxString id );

    void SetTreeItemCollapseState( wxTreeItemId childID );

    void SetItemNode( wxTreeItemId id, wxXmlNode* ele );

    void SetItemImageFullName( wxTreeItemId id, wxString str );

    /// @brief Set the checkbox of the item to the next state. Saves the new state.
    /// Sends message to Album tree to update
    void SetNextState( const wxTreeItemId& itemID );

    //Find th node and select it
    void SetSelection( wxXmlNode* node );

    void SetType( wxTreeItemId id, Catalog::CatalogBaseType type );

    void ShowMenu( wxTreeItemId id, const wxPoint& pt );

    void  SetComparePanel( ComparePanel* comparePanel );

    ComparePanel* GetComparePanel( );


    wxTreeItemId  FindTargetEntryForNewEntry( wxTreeItemId id, Catalog::DataTypes type, wxString searchVal );
    wxTreeItemId  FindTargetEntryForNewEntry( wxXmlNode* node, Catalog::DataTypes type );

    void AddMergeToEntryList( wxXmlNode* node );

    void LoadMergeToCompareTree( wxXmlNode* mergeRoot );

    wxTreeItemId FindForiegn( );
    wxTreeItemId CopyForiegnChild( wxTreeItemId parent, wxXmlNode* child );

private:
    ComparePanel* m_comparePanel;

    // NB: due to an ugly wxMSW hack you _must_ use wxDECLARE_DYNAMIC_CLASS( );
    //     if you want your overloaded OnCompareItems( ) to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default ( alphabetical ) sorting much faster under wxMSW.
    wxDECLARE_DYNAMIC_CLASS( CompareTreeCtrl );
    wxDECLARE_EVENT_TABLE( );
};

#endif
