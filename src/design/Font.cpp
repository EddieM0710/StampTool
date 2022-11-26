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

 
    // build the frame container for the font
    wxXmlNode* Font::Write( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Font", "Inserting a Font." );

        double xPos = GetXPos( );
        double yPos = GetYPos( );
        double width = GetWidth( );
        double height = GetHeight( ); // allow for caption

        wxString drawStyleName = ODT::FrameNoBorder;
        wxString textAnchorType = ODT::TextAnchorParagraph; // "page", "paragraph"
        wxString textStyleName = ODT::NormalTextStyle;

        wxXmlNode* frame = ODT::ContentDoc( )->WriteFrame( parent, xPos,
            yPos,
            width,
            height,
            drawStyleName,  // fr1
            textAnchorType ); // "page", "paragraph"


        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            AlbumBaseType childType = ( AlbumBaseType )child->GetNodeType( );
            switch ( childType )
            {
            case AT_Row:
            {
                // set the layout parameters into the child
                Row* row = ( Row* )child;
                row->Write( frame );
                break;
            }
            case AT_Col:
            {
                // set the layout parameters into the child
                Font* col = ( Font* )child;
                col->Write( frame );
                break;
            }
            case AT_Stamp:
            {
                // set the layout parameters into the child
                Stamp* stamp = ( Stamp* )child;
                stamp->Write( frame );
                break;
            }
            }
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        return frame;
    }


    void Font::Save( wxXmlNode* xmlNode )
    {
        if ( !m_type.compare("Default"))
        {
        SetAttribute( xmlNode, Design::FT_Type );
        SetAttribute( xmlNode, Design::FT_Name );
        }

    }
}