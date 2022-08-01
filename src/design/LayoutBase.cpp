/**
 * @file LayoutBase.cpp
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

#include "design/AlbumBase.h"

#include <iostream>


#include "LayoutBase.h"
#include "design/TitlePage.h"
#include "design/Page.h"
#include "design/Title.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "gui/AlbumImagePanel.h"
#include "gui/DesignTreeCtrl.h"

namespace Design {


    void LayoutBase::UpdateTitleSize( double width, wxFont* font )
    {
        wxString text = m_title;

        // first break into lines if necessary
        GetAlbumImagePanel( )->MakeMultiLine( text, *font, width );

        // then get the actual multi line text extent
        m_titleSize = GetAlbumImagePanel( )->GetLogicalTextExtent( text, *font );
    }

    void LayoutBase::ReportLayoutError( wxString funct, wxString err, bool fatal )
    {
        wxString funcStr = wxString::Format( "%s::%s", AttrNameStrings[ GetNodeType( ) ], funct );
        wxString msgStr = wxString::Format( "InputLine: %d;  %s", GetLineNumber( ), err );
        ReportError( funcStr, msgStr, fatal );
    }

    void LayoutBase::ValidateChildType( int& nbrRows, int& nbrCols, int& nbrStamps )
    {
        // count the number of rows/cols planned
        nbrRows = 0;
        nbrCols = 0;
        nbrStamps = 0;

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            switch ( type )
            {
            case AT_Row:
            {
                nbrRows++;
                break;
            }
            case AT_Col:
            {
                nbrCols++;
                break;
            }
            case AT_Stamp:
            {
                nbrStamps++;
                break;
            }
            }
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        if ( ( nbrRows > 0 ) && ( nbrCols > 0 ) )
        {
            ReportLayoutError( "ValidateChildType", "Only Rows or Columns are allowed as the children, not both" );
        }
    }


    void LayoutBase::DumpLayout( double x, double y )
    {
        AlbumBaseType type = GetNodeType( );
        std::cout << GetObjectName( ) << " Pos (x:" << x << " y:" << y << ") ";
        m_frame.WriteLayout( GetObjectName( ) );
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            double xPos = x + GetXPos( );
            double yPos = y + GetYPos( );

            child->DumpLayout( xPos, yPos );

            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }
}