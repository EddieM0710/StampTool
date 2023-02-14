/**
 * @file Title.cpp
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

#include "design/Title.h"

namespace Design { 

    bool  Title::UpdateMinimumSize( )
    { 
        double height = GetAttrDbl( AT_Height );
        double width = 1.;
        SetHeight( height );
        SetMinHeight( height );
        // default width is completely arbitrary at this point
        SetWidth( width );
        SetMinWidth( width );
    }


    void Title::UpdatePositions( )
    { 
        SetXPos( 0 );
        SetYPos( 0 );
    }

    void Title::UpdateSizes( )
    { 

    }

        
    NodeStatus Title::ValidateNode( )
    { 
        NodeStatus status = AT_OK;
        m_nodeValid = status;


        return status;
    }
}