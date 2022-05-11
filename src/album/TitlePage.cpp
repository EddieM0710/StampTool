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
        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            LayoutNode* childItem = ( LayoutNode* )ChildItem( i );
            childItem->UpdateMinimumSize( );
        }
    }
    bool TitlePage::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page) 
        // and begin filling in position relative to the parent
        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            LayoutNode* childItem = ( LayoutNode* )ChildItem( i );
            childItem->UpdatePositions( );
        }
        return true;
    }
    void TitlePage::UpdateSizes( )
    {

    }
}