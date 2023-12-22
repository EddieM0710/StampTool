/**
 * @file StampList.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright ( c ) 2022
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "utils/StampList.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/AlbumTreeCtrl.h"


namespace Utils {


    wxString StampLink::GetID( )
    {
        wxString id = "";
        AlbumTreeCtrl* albumTreeCtrl = GetAlbumTreeCtrl( );
        if ( albumTreeCtrl->IsOk( ) && m_designTreeID.IsOk( ) )
        {

            wxClientData* clientData = albumTreeCtrl->GetItemData( m_designTreeID );
            DesignTreeItemData* data = ( DesignTreeItemData* ) clientData;
            if ( data && data->IsOk( ) )
            {
                if ( data->GetType( ) == Design::AT_Stamp )
                {
                    Design::AlbumBase* node = data->GetNodeElement( );
                    if ( node )
                    {
                        Design::Stamp* stamp = ( Design::Stamp* ) node;
                        Design::AlbumBaseType tyoe = data->GetType( );
                        id = stamp->GetNbrString( );
                    }
                }
            }
        }
        return id;
    };

    bool StampLink::IsStamp( wxString id )
    {
        wxString linkID = GetID( );
        return !id.Cmp( linkID );
    };

    void StampLink::Clear( )
    {
        CatalogTreeCtrl* catTreeCtrl = GetCatalogTreeCtrl( );
        if ( catTreeCtrl )
        {
            wxTreeItemId catTreeID = GetCatTreeID( );
            if ( catTreeID.IsOk( ) )
            {
                CatalogTreeItemData* catData =
                    ( CatalogTreeItemData* ) catTreeCtrl->GetItemData( catTreeID );
                catData->SetStampLink( ( StampLink* ) 0 );
            }
        }
        AlbumTreeCtrl* albumTreeCtrl = GetAlbumTreeCtrl( );
        if ( albumTreeCtrl )
        {
            wxTreeItemId albumID = GetDesignTreeID( );
            if ( albumID.IsOk( ) )
            {
                DesignTreeItemData* itemData =
                    ( DesignTreeItemData* ) albumTreeCtrl->GetItemData( albumID );
                itemData->SetStampLink( ( StampLink* ) 0 );
            }
        }
    }

    void StampList::Clear( )
    {
        CatalogTreeCtrl* catTreeCtrl = GetCatalogTreeCtrl( );
        // AlbumTreeCtrl* albumTreeCtrl = GetAlbumTreeCtrl( );
        if ( catTreeCtrl )
        {
            for ( int i = 0; i < m_list.size( ); i++ )
            {
                StampLink* link = ( StampLink* ) m_list.at( i );
                catTreeCtrl->RemoveStampLink( link->GetCatTreeID( ) );
                link->Clear( );
                delete link;
            }
            m_list.erase( std::begin( m_list ), std::end( m_list ) );
        }
    }

    void StampList::ClearCatalogLinks( )
    {
        for ( int i = 0; i < m_list.size( ); i++ )
        {
            StampLink* link = ( StampLink* ) m_list.at( i );
            link->SetCatTreeID( ( wxTreeItemId ) 0 );
        }
    }


    int StampList::FindStamp( wxString stampID )
    {
        if ( !stampID.IsEmpty( ) )
        {
            for ( int i = 0; i < m_list.size( ); i++ )
            {
                StampLink* link = ( StampLink* ) m_list.at( i );
                if ( link->IsStamp( stampID ) )
                {
                    return i;
                }
            }
        }
        return -1;
    };

    StampLink* StampList::FindStampLink( wxString stampID )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            return m_list.at( pos );
        }
        return ( StampLink* ) 0;
    }

    StampLink* StampList::AddStamp( wxString stampId )
    {
        int pos = FindStamp( stampId );

        if ( pos >= 0 )
        {
            return m_list.at( pos );
        }
        StampLink* stampLink = new StampLink( );
        m_list.push_back( stampLink );
        return stampLink;
    };

    void StampList::SetCatTreeID( wxString stampID, wxTreeItemId treeID )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            m_list.at( pos )->SetCatTreeID( treeID );
        }
    }
    bool StampList::GetCatTreeID( wxString stampID, wxTreeItemId& treeID )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            treeID = m_list.at( pos )->GetCatTreeID( );
            return treeID.IsOk( );
        }
        return false;
    }

    // void StampList::SetCatNode( wxString stampID, wxXmlNode* catStamp )
    // { 
    //     int pos = FindStamp( stampID );
    //     if ( pos >= 0 )
    //     { 
    //         m_list.at( pos )->SetCatNode( catStamp );
    //     }
    // }

    // wxXmlNode* StampList::GetCatNode( wxString stampID )
    // { 
    //     int pos = FindStamp( stampID );
    //     if ( pos >= 0 )
    //     { 
    //         return m_list.at( pos )->GetCatNode( );
    //     }
    //     return ( wxXmlNode* )0;
    // }


    void StampLink::Update( wxTreeItemId catTreeID, wxTreeItemId albumID )
    {
        SetDesignTreeID( albumID );
        SetCatTreeID( catTreeID );
        // CatalogTreeCtrl* treeCtrl = GetCatalogTreeCtrl( );
        // CatalogTreeItemData* data = ( CatalogTreeItemData* )treeCtrl->GetItemData( catTreeID );
        // SetCatNode( data->GetNodeElement( ) );
    }
}