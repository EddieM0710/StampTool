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
 **************************************************/
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "design/AlbumBase.h"

#include "design/TitlePage.h"
#include "design/Page.h"
#include "design/Title.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "gui/DesignTreeCtrl.h"
#include "utils/Settings.h"

namespace Design { 

    AlbumBase::AlbumBase( wxXmlNode* ele ) : XMLBase( ele )
    { 
    }

    AlbumBase::~AlbumBase( )
    { 
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            AlbumBase* child = ( AlbumBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            child->~AlbumBase( );
//            m_layoutChildArray.erase( it );
            childID = GetDesignTreeCtrl( )->GetNextChild( childID, cookie );
        }
    };

    NodeStatus AlbumBase::ValidateChildren( AlbumBase* node )
    { 
        if ( !node->IsStatusOK( ) )
        { 
            return AT_FATAL;
        }
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            if ( ValidateChildren( ( AlbumBase* )child ) == AT_FATAL )
            { 
                return AT_FATAL;
            }

            childID = GetDesignTreeCtrl( )->GetNextChild( childID, cookie );
        }
        return AT_OK;
    }


    int  AlbumBase::GetNbrChildren( ) {            
        if( m_treeID.IsOk( ) )
        { 
            return GetDesignTreeCtrl( )->GetChildrenCount( m_treeID, false );;
        }
        return -1;
    };

    AlbumBase* AlbumBase::GetParent( )
    { 
        if( m_treeID.IsOk( ) )
        { 
            wxTreeItemId parentID = GetDesignTreeCtrl( )->GetItemParent( m_treeID );
            if( parentID.IsOk( ) )
            { 
                return GetDesignTreeCtrl( )->GetItemNode( parentID );
            }
        }
        return ( AlbumBase* )0;
    };       
      
    bool AlbumBase::HasChildren( )
    { 
        if( m_treeID.IsOk( ) )
        { 
            return GetDesignTreeCtrl( )->HasChildren( m_treeID );
        }
        return false;
    };
}