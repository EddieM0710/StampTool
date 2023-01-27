/**
 * @file Font.cpp
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

#include "design/FontInfo.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"
#include <wx/pen.h>
#include "gui/GuiUtils.h"


namespace Design { 

    int FindFont( FontList& list, wxFont* font, wxColor color )
    { 
        for ( int i = 0; i < list.size( ); i++ )
        { 
            if ( ( *font == *( list.at( i )->GetFont( ) ) )
                && ( color == list.at( i )->GetColor( ) ) )
                return i;
        }
        return -1;
    }
}