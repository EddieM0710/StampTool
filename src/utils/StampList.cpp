/**
 * @file StampList.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "utils/StampList.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/DesignTreeCtrl.h"

namespace Utils {
    void StampLink::Clear( )
    {
        CatalogTreeCtrl* catTreeCtrl = GetCatalogTreeCtrl( );
        if ( catTreeCtrl )
        {
            wxTreeItemId catID = GetCatTreeID( );
            if ( catID.IsOk( ) )
            {
                CatalogTreeItemData* catData =
                    ( CatalogTreeItemData* )catTreeCtrl->GetItemData( catID );
                catData->SetStampLink( ( StampLink* )0 );
            }
        }
        DesignTreeCtrl* designTreeCtrl = GetDesignTreeCtrl( );
        if ( designTreeCtrl )
        {
            wxTreeItemId albumID = GetDesignTreeID( );
            if ( albumID.IsOk( ) )
            {
                DesignTreeItemData* albumData =
                    ( DesignTreeItemData* )designTreeCtrl->GetItemData( albumID );
                albumData->SetStampLink( ( StampLink* )0 );
            }
        }
    }

    void StampList::Clear( )
    {
        CatalogTreeCtrl* catTreeCtrl = GetCatalogTreeCtrl( );
        DesignTreeCtrl* designTreeCtrl = GetDesignTreeCtrl( );
        if ( catTreeCtrl )
        {
            for ( int i = 0; i < m_list.size( ); i++ )
            {
                StampLink* link = ( StampLink* )m_list.at( i );
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
            StampLink* link = ( StampLink* )m_list.at( i );
            link->SetCatTreeID( ( wxTreeItemId )0 );
        }
    }


    int StampList::FindStamp( wxString stampID )
    {
        for ( int i = 0; i < m_list.size( ); i++ )
        {
            StampLink* link = ( StampLink* )m_list.at( i );
            if ( link->IsStamp( stampID ) )
            {
                return i;
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
        return ( StampLink* )0;
    }

    StampLink* StampList::AddStamp( Design::Stamp* stamp )
    {
        int pos = FindStamp( stamp->GetAttrStr( Design::AT_ID ) );

        if ( pos >= 0 )
        {
            return m_list.at( pos );
        }
        StampLink* stampLink = new StampLink( stamp );
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

    void StampList::SetCatNode( wxString stampID, wxXmlNode* catStamp )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            m_list.at( pos )->SetCatNode( catStamp );
        }
    }

    wxXmlNode* StampList::GetCatNode( wxString stampID )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            return m_list.at( pos )->GetCatNode( );
        }
        return ( wxXmlNode* )0;
    }
    void StampLink::Update( wxTreeItemId catID, wxTreeItemId albumID )
    {
        SetDesignTreeID( albumID );
        SetCatTreeID( catID );
        CatalogTreeCtrl* treeCtrl = GetCatalogTreeCtrl( );
        CatalogTreeItemData* data = ( CatalogTreeItemData* )treeCtrl->GetItemData( catID );
        SetCatNode( data->GetNodeElement( ) );
    }
}