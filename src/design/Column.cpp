/**
 * @file Column.cpp
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
#include <wx/pen.h>

#include "design/Column.h"
#include "design/Row.h"
#include "design/Stamp.h"
 //#include "design/Title.h"
  //#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
#include "gui/GuiUtils.h"


namespace Design {

    bool Column::UpdateMinimumSize( )
    {

        //Positioning down the col.
        //The min width of the col is the size of the widest child 
        //The min height is the sum of the min heights of the children. 
        //plus the title if used
        double minWidth = 0.0;
        double minHeight = 0.0;

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetDesignTreeCtrl( )->GetItemNode( childID );
            child->UpdateMinimumSize( );
            if ( child->GetMinWidth( ) > minWidth )
            {
                minWidth = child->GetMinWidth( );
            }
            minHeight += child->GetMinHeight( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;
        if ( GetShowFrame( ) )
        {
            leftPadding = GetLeftContentPadding( );
            rightPadding = GetRightContentPadding( );
            topPadding = GetTopContentPadding( );
            bottomPadding = GetBottomContentPadding( );
        }

        minHeight = minHeight + topPadding + bottomPadding;
        minWidth = minWidth + leftPadding + rightPadding;

        GetTitleFrame( )->UpdateString( minWidth );

        if ( GetShowTitle( ) )
        {
            // Allow 3 times the title height
            minHeight += 3 * GetTitleFrame( )->GetHeight( );
        }

        SetMinHeight( minHeight );
        SetMinWidth( minWidth );
        return true;
    }

    void Column::UpdateSizes( )
    {

        // Set the height and width of each child  column
        // Stamps have fixed height and width
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            //AlbumBaseType type = ( AlbumBaseType ) GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetDesignTreeCtrl( )->GetItemNode( childID );
            if ( child->IsNodeType( AT_Row ) )
            {
                child->SetWidth( GetMinWidth( ) );
                child->SetHeight( child->GetMinHeight( ) );
            }
            child->UpdateSizes( );

            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }



    // calculate the column layout based on child parameters
    void Column::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page ) 
        // and begin filling in position relative to the parent

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        double xPos = 0;
        double yPos = 0;
        //First calc title position  
        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->SetXPos( 0 + ( GetWidth( ) - GetTitleFrame( )->GetWidth( ) ) / 2 );
            GetTitleFrame( )->SetYPos( GetTitleFrame( )->GetHeight( ) );
            // allow for space above title, title height and that much again for nice spaing
            yPos = GetTitleFrame( )->GetHeight( );
        }

        // this is a col so we are positioning children down the page
        //double spacing = ( GetHeight( ) - GetMinHeight( ) ) / ( nbrRows + nbrStamps + 1 );
        double spacing = 4;
        if ( CalculateSpacing( ) )
        {
            // this is a row so we are positioning children across the page
            spacing = ( GetHeight( ) - GetMinHeight( ) ) / ( nbrRows + nbrStamps + 1 );

            // inital x/y pos within the row
            yPos += spacing;
        }
        else
        {
            spacing = GetFixedSpacingDbl( );
            yPos += ( ( GetHeight( ) - GetMinHeight( ) ) - ( nbrRows + nbrStamps - 1 ) * spacing ) / 2;
        }

        //  if ( GetShowTitle( ) ) yPos += GetTitleFrame( )->GetHeight( );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetDesignTreeCtrl( )->GetItemNode( childID );
            child->UpdatePositions( );

            AlbumBaseType childType = ( AlbumBaseType ) child->GetNodeType( );
            switch ( childType )
            {
            case AT_Row:
            {
                Row* row = ( Row* ) child;
                row->SetXPos( xPos );
                row->SetYPos( yPos );
                //calc position of next row
                yPos += row->GetHeight( ) + spacing;
                break;
            }
            case AT_Stamp:
            {

                Stamp* stamp = ( Stamp* ) child;

                // each stamp is positioned in the cell

                double xBorder = 0;//( GetWidth( ) - stamp->GetWidth( ) ) / 2;
                stamp->SetXPos( xPos + xBorder );
                stamp->SetYPos( yPos );
                // get xpos of next cell
                yPos += stamp->GetHeight( ) + spacing;
                break;
            }
            case AT_Text:
            {
                TextBox* text = ( TextBox* ) child;

                double xBorder = 0;//( GetWidth( ) - text->GetWidth( ) ) / 2;
                text->SetXPos( xPos + xBorder );
                text->SetYPos( yPos );
                // get xpos of next cell
                yPos += text->GetHeight( ) + spacing;
                break;
            }
            }
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }


    NodeStatus Column::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        if ( !HasChildren( ) )
        {
            GetErrorArray( )->Empty( );
            if ( GetHeight( ) <= 0.0 )
            {
                wxString str;
                str.Format( "Terminal leaf node must define the height. height:>>%7.2f<< \n", GetHeight( ) );
                GetErrorArray( )->Add( str );
                m_debugString.Append( str );
                status = AT_FATAL;
            }
            if ( GetWidth( ) <= 0.0 )
            {
                wxString str;
                str.Format( "Terminal leaf node must define the width. width:>>%7.2f<< \n", GetWidth( ) );
                GetErrorArray( )->Add( str );
                m_debugString.Append( str );
                //                std::cout << "Terminal leaf node must define the width.\n";
                status = AT_FATAL;
            }
        }
        m_nodeValid = status;
        return status;
    }

    void Column::Draw( wxDC& dc, double x, double y )
    {
        double leftPadding = 0;
        double topPadding = 0;
        dc.SetPen( *wxBLACK_PEN );
        if ( GetShowFrame( ) )
        {

            leftPadding = GetLeftContentPadding( );
            topPadding = GetTopContentPadding( );

            m_frame.Draw( dc, x, y );
        }

        SetClientDimensions( dc, x, y, GetWidth( ), GetHeight( ) );

        double xPos = x + GetXPos( ) + leftPadding;
        double yPos = y + GetYPos( ) + topPadding;


        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->Draw( dc, xPos, yPos );
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {

            LayoutBase* child = ( LayoutBase* ) GetDesignTreeCtrl( )->GetItemNode( childID );
            child->Draw( dc, xPos, yPos );

            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    void Column::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowFrame );
        SaveFonts( xmlNode );
    }

    void Column::ReportLayout( )
    {
        std::cout << "Layout for Column " << "\n ";
        ReportLayoutFrame( );
    };
}