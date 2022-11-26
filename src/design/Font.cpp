/**
 * @file Font.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#include "design/Font.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"
#include <wx/pen.h>
#include "gui/GuiUtils.h"


namespace Design {


    void Font::Save( wxXmlNode* xmlNode )
    {
        if ( !m_type.compare("Default"))
        {
        SetAttribute( xmlNode, Design::AT_FontType );
        SetAttribute( xmlNode, Design::AT_FontName );
        }

    }
}