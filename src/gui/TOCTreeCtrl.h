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
#include <wx/menu.h>

#include "gui/IconDefs.h"
#include "gui/GuiUtils.h"
#include "toc/TOCDefs.h"


class Stamp;

namespace Utils {
    class StampLink;
}

typedef void* VolumePtr;


extern int LastVolumeID;

int GetNextVolumeID( );

class TOCTreeItemData : public wxTreeItemData
{
public:


    TOCTreeItemData( Utils::TOCBaseType type, bool collapseState = false, wxString name = "",
        const wxString desc = "", int menuID = 0, VolumePtr vol = 0 )
    {
        m_type = type;
        m_desc = desc;
        m_collapseState = collapseState;
        m_name = name;

        m_volume = vol;
        m_menuID = menuID;
        m_ok = 12345;
    };


    TOCTreeItemData( TOCTreeItemData& src )
    {
        Copy( *this, src );
    };


    void Copy( TOCTreeItemData& lhs, TOCTreeItemData& rhs )
    {
        lhs.m_type = rhs.GetType( );
        lhs.m_desc = rhs.GetDesc( );
        lhs.m_collapseState = rhs.GetCollapseState( );
        lhs.m_name = rhs.GetName( );

        lhs.m_volume = rhs.GetVolume( );
        lhs.m_menuID = rhs.GetMenuID( );
        lhs.m_ok = rhs.GetOK( );
    }


    ~TOCTreeItemData( )
    {
        m_ok = 0;
    };


    int Cmp( TOCTreeItemData* itemData2 );

    bool IsOK( )
    {
        if ( m_ok == 12345 )
        {
            return true;
        }
        return false;
    };


    wxString const& GetDesc( ) const {
        return m_desc;
    };


    VolumePtr GetVolume( ) {
        return m_volume;
    };


    Utils::TOCBaseType GetType( ) {
        return m_type;
    };


    void SetType( Utils::TOCBaseType type ) {
        m_type = type;
    };

    int GetMenuID( ){
        return m_menuID;
    };

    void SetCollapseState( bool state ){
        m_collapseState = state;
    };

    bool GetCollapseState( ){
        return m_collapseState;
    };

    void SetName( wxString name ){
        m_name = name;
    };

    wxString GetName( ){
        return m_name;
    };

    double GetOK( ){
        return m_ok;
    };

    TOCTreeItemData& operator=( TOCTreeItemData& other ) noexcept
    {
        if ( this == &other )
            return *this;

        Copy( *this, other );
        return *this;
    };

private:
    double m_ok;

    bool m_collapseState;

    // filename for VolumeType; sectionName for SectionType
    wxString m_name;

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



    TOCTreeCtrl( ) { }

    TOCTreeCtrl( wxWindow* parent, const wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style );

    virtual ~TOCTreeCtrl( void ) { }


    wxTreeItemId AddChild( wxTreeItemId parent, wxXmlNode* child, wxMenu* menu );

    void AddEntry( wxTreeItemId id );

    //  Utils::StampLink* AppendAlbumStamp( wxTreeItemId itemId );

    void Clear( );

    TOCTreeItemData* CreateChildData( wxXmlNode* child,
        wxString& label,
        Catalog::IconID& icon,
        Utils::TOCBaseType& nodeType );

    void CreateImageList( );

    void DeleteEntry( wxTreeItemId id );

    void DoSortChildren( const wxTreeItemId& item, bool reverse = true )
    {
        m_reverseSort = reverse;
        wxTreeCtrl::SortChildren( item );
    };

    virtual void EditDetailsDialog( TOCTreeCtrl* parent ) = 0;

    void EnableState( wxTreeItemId id );

    wxTreeItemId FindFirstEntryChild( wxTreeItemId id );

    virtual VolumePtr FindVolume( wxString str ) = 0;

    wxTreeItemId GetCurrentTreeID( ){
        return m_currVolumeID;
    };

    // wxString GetID( wxTreeItemId catTreeID );

     //wxString GetImage( wxTreeItemId catTreeID );


    wxMenu* GetMenu( ) {
        if ( !m_contextMenu )
        {
            m_contextMenu = new wxMenu( );
        }
        return m_contextMenu;
    };

    wxString GetItemDesc( wxTreeItemId id );

    wxString GetItemImageFullName( wxTreeItemId id );

    Utils::TOCBaseType GetItemType( wxTreeItemId id );

    virtual wxString GetVolumeName( VolumePtr catVolume ) = 0;

    virtual wxXmlNode* GetCurrVolumeRoot( ) = 0;

    wxTreeItemId InitTOCTree( wxXmlNode* TOCNode );

    wxTreeItemId InsertChild( wxTreeItemId parent, wxXmlNode* child, bool after = true );

    void LoadTree( wxXmlNode* TOCNode, wxString str );

    virtual void LinkMenuItemToTreeItem( int id, wxTreeItemId treeId ) = 0;

    wxXmlNode* MakeNode( wxTreeItemId treeID, wxXmlNode* parent );

    void MakeTree( wxTreeItemId parentID, wxXmlNode* parentNode );

    void MakeTree( wxXmlNode* parentNode );

    wxTreeItemId MoveItemAsChild( wxTreeItemId srcID, wxTreeItemId parentID );

    wxTreeItemId MoveItem( wxTreeItemId srcID, wxTreeItemId destID, bool after );



    void OnBeginDrag( wxTreeEvent& event );

    virtual int OnCompareItems( const wxTreeItemId& i1, const wxTreeItemId& i2 ) wxOVERRIDE;

    void OnEndDrag( wxTreeEvent& event );

    void OnItemMenu( wxTreeEvent& event );

    void OnTreectrlItemCollapsed( wxTreeEvent& event );

    void OnTreectrlItemExpanded( wxTreeEvent& event );


    //  void SelectStamp( wxString id );

    void SetCurrentTreeID( wxTreeItemId id ){
        m_currVolumeID = id;
    };

    void SetTreeItemCollapseState( wxTreeItemId childID );

    //void SetItemNode( wxTreeItemId id, wxXmlNode* ele );

   // void SetItemChecked( wxTreeItemId id, bool state = true );

    void SetItemImageFullName( wxTreeItemId id, wxString str );

    void SetType( wxTreeItemId id, Utils::TOCBaseType type );

    void ShowDropMenu( wxTreeItemId itemSrc, wxTreeItemId itemDst );

    void ShowMenu( wxTreeItemId id, const wxPoint& pt );

    virtual void ReSortTree( ) = 0;

private:

    wxMenu* m_contextMenu;

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
