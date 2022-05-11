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

#include "design/TitlePage.h"

namespace Design {


    bool TitlePage::UpdateMinimumSize( )
    {
        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );;
            child->UpdateMinimumSize( );
        }
    }
    
    void TitlePage::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page) 
        // and begin filling in position relative to the parent
        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            child->UpdatePositions( );
        }
    }
    void TitlePage::UpdateSizes( )
    {

    }

    NodeStatus TitlePage::ValidateNode()
     {
        NodeStatus status = AT_OK;
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
        m_nodeValid = status;
        return status;
    }
}