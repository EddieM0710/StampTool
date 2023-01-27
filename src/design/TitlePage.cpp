/**
 * @file TitlePage.cpp
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

#include "design/TitlePage.h"
#include "gui/DesignTreeCtrl.h"

namespace Design { 


    bool TitlePage::UpdateMinimumSize( )
    { 
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            child->UpdateMinimumSize( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        return true;
    }
    
    void TitlePage::UpdatePositions( )
    { 
        // go to the bottom of each child container object ( row, column, page ) 
        // and begin filling in position relative to the parent
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            child->UpdatePositions( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }
    void TitlePage::UpdateSizes( )
    { 

    }

    NodeStatus TitlePage::ValidateNode( )
     { 
        NodeStatus status = AT_OK;
        if ( !HasChildren( ) )
        { 
            if ( GetHeight( ) <= 0.0 )
            { 
                std::cout << "Terminal leaf node must define the height.\n";
                status = AT_FATAL;
            }
            if ( GetWidth( ) <= 0.0 )
            { 
                std::cout << "Terminal leaf node must define the width.\n";
                status = AT_FATAL;
            }
        }
        m_nodeValid = status;
        return status;
    }
}