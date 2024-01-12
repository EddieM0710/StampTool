/**
 * @file AlbumBase.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
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

#include <iostream>

#include "design/DesignDefs.h"
#include "design/AlbumBase.h"

 // #include "design/Page.h"
 // #include "design/Row.h"
 // #include "design/Column.h"
 // #include "design/Stamp.h"
#include "gui/AlbumTreeCtrl.h"
#include "utils/Settings.h"


namespace Design {

    AlbumBase::~AlbumBase( )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            AlbumBase* child = ( AlbumBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            child->~AlbumBase( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( childID, cookie );
        }
    };

    int  AlbumBase::GetNbrChildren( ) {
        if ( m_treeID.IsOk( ) )
        {
            return GetAlbumTreeCtrl( )->GetChildrenCount( m_treeID, false );;
        }
        return -1;
    };


    AlbumBase* AlbumBase::GetParent( )
    {
        if ( m_treeID.IsOk( ) )
        {
            wxTreeItemId parentID = GetAlbumTreeCtrl( )->GetItemParent( m_treeID );
            if ( parentID.IsOk( ) )
            {
                return GetAlbumTreeCtrl( )->GetItemNode( parentID );
            }
        }
        return ( AlbumBase* ) 0;
    };

    bool AlbumBase::HasChildren( )
    {
        if ( m_treeID.IsOk( ) )
        {
            return GetAlbumTreeCtrl( )->HasChildren( m_treeID );
        }
        return false;
    };

    NodeStatus AlbumBase::ValidateChildren( AlbumBase* node )
    {
        if ( !node->IsStatusOK( ) )
        {
            return AT_FATAL;
        }
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( ValidateChildren( ( AlbumBase* ) child ) == AT_FATAL )
            {
                return AT_FATAL;
            }

            childID = GetAlbumTreeCtrl( )->GetNextChild( childID, cookie );
        }
        return AT_OK;
    }

    //----------------

    double AlbumBase::GetAlbumAttributeDbl( Design::AlbumAttrType type )
    {
        wxString val = GetAttrStr( type );
        if ( val.IsEmpty( ) )
        {
            return  m_albumDefaults->GetDefaultDbl( type );
        }
        return  GetAttrDbl( type );
    }

    //----------------

    wxString AlbumBase::GetAlbumAttributeStr( Design::AlbumAttrType type )
    {
        wxString val = GetAttrStr( type );
        if ( val.IsEmpty( ) )
        {
            return  GetDefaults( )->GetDefault( type );
        }
        return val;
    }

    //--------------


    bool AlbumBase::GetAlbumAttributeBool( Design::AlbumAttrType type, bool defVal )
    {
        wxString catStr = GetAttrStr( type );
        if ( catStr.IsEmpty( ) )
        {
            catStr = m_albumDefaults->GetDefault( type );
            if ( catStr.IsEmpty( ) )
            {
                return defVal;
            }
        }
        return String2Bool( catStr );
    }

    //----------------

    void AlbumBase::SetAlbumAttributeStr( Design::AlbumAttrType type, wxString val )
    {
        if ( IsDefaultVal( type, val ) )
        {
            DeleteAttribute( AttrNameStrings[ type ] );
        }
        else
        {
            SetAttrStr( type, val );
        }
    }

    //----------------

    void AlbumBase::SetAlbumAttributeDbl( Design::AlbumAttrType type, double val )
    {
        SetAlbumAttributeStr( type, Dbl2String( val ) );
    }

    //----------------

    void AlbumBase::SetAlbumAttributeBool( Design::AlbumAttrType type, bool val )
    {
        wxString str = Bool2String( val );
        SetAlbumAttributeStr( type, str );

    }

    //--------------

    bool AlbumBase::IsDefaultVal( AlbumAttrType type )
    {
        return m_albumDefaults->IsEqual( type, GetAttrStr( type ) );
    }

    //----------------

    bool AlbumBase::IsDefaultVal( AlbumAttrType type, wxString val )
    {
        return m_albumDefaults->IsEqual( type, val );
    }

}