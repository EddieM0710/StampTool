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
namespace Utils {

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

    StampLink* StampList::GetStampLink( wxString stampID )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            return m_list.at( pos );
        }
        return ( StampLink* )0;
    }

    StampLink* StampList::AddStamp( Layout::Stamp* stamp )
    {
        int pos = FindStamp( stamp->GetAttrStr( Layout::AT_ID ) );

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

    void StampList::SetCatStamp( wxString stampID, wxXmlNode* catStamp )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            m_list.at( pos )->SetCatStamp( catStamp );
        }
    }

    wxXmlNode* StampList::GetCatStamp( wxString stampID )
    {
        int pos = FindStamp( stampID );
        if ( pos >= 0 )
        {
            return m_list.at( pos )->GetCatStamp( );
        }
        return ( wxXmlNode* )0;
    }

}