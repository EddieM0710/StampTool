/**
 * @file TitlePage.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "album/TitlePage.h"

namespace Layout {


    void TitlePage::UpdateMinimumSize( )
    {
        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );;
            child->UpdateMinimumSize( );
        }
    }
    
    void TitlePage::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page) 
        // and begin filling in position relative to the parent
        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );
            child->UpdatePositions( );
        }
    }
    void TitlePage::UpdateSizes( )
    {

    }

    AlbumNodeStatus TitlePage::ValidateNode()
     {
        AlbumNodeStatus status = AT_OK;
        if ( !HasChildren() )
        {
            if ( GetHeight() <= 0.0)
            {
                std::cout << "Terminal leaf node must define the height.\n";
                status = AT_FATAL;
            }
            if ( GetWidth() <= 0.0)
            {
                std::cout << "Terminal leaf node must define the width.\n";
                status = AT_FATAL;
            }
        }
        return status;
    }
}