/**
 * @file Column.cpp
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

#include "design/Column.h"
#include "design/Row.h"
#include "design/Stamp.h"
#include "design/Title.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include <wx/pen.h>
#include "gui/AlbumImagePanel.h"
#include "gui/GuiUtils.h"


namespace Design {

    bool Column::UpdateMinimumSize( )
    {
        m_frame.WriteLayout( "Col::UpdateMinimumSizes <" );

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
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            child->UpdateMinimumSize( );

            if ( child->GetWidth( ) > GetMinWidth( ) )
            {
                minWidth = child->GetWidth( );
            }
            minHeight += child->GetHeight( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        SetMinHeight( minHeight );
        if ( GetShowTitle( ) )
        {

            wxFont* titleFont = new wxFont( *wxNORMAL_FONT );
            titleFont->SetPointSize( 8 );
            UpdateTitleSize( minWidth, titleFont );
            delete titleFont;
            minHeight += GetTitleHeight( );
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

        SetMinHeight( minHeight + topPadding + bottomPadding );
        SetMinWidth( minWidth + leftPadding + rightPadding );
        m_frame.WriteLayout( "Col::UpdateMinimumSizes >" );
    }

    void Column::UpdateSizes( )
    {
        m_frame.WriteLayout( "Col::UpdateSizes <" );

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );



        // Set the height and width of each child  column
        // Stamps have fixed height and width
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            AlbumBaseType childType = ( AlbumBaseType )child->GetNodeType( );
            if ( childType == AT_Row )
            {
                child->SetWidth( GetMinWidth( ) );
                double minHeight = GetMinHeight( );
                if ( child->GetShowTitle( ) )
                {
                    minHeight = GetTitleHeight( );
                }
                child->SetHeight( minHeight );
            }
            child->UpdateSizes( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        m_frame.WriteLayout( "Col::UpdateSizes >" );

    }



    // calculate the column layout based on child parameters
    void Column::UpdatePositions( )
    {
        m_frame.WriteLayout( "Col::UpdatePositions <" );
        // go to the bottom of each child container object ( row, column, page) 
        // and begin filling in position relative to the parent

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        // inital x/y pos within the row


        // this is a col so we are positioning children down the page
        double spacing = ( GetHeight( ) - GetMinHeight( ) ) / ( nbrRows + nbrStamps + 1 );

        double xPos = 0;
        double yPos = spacing;
        if ( GetShowTitle( ) ) yPos += GetTitleHeight( );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            child->UpdatePositions( );

            AlbumBaseType childType = ( AlbumBaseType )child->GetNodeType( );
            switch ( childType )
            {
            case AT_Row:
            {
                Row* row = ( Row* )child;
                row->SetXPos( xPos );
                row->SetYPos( yPos );
                //calc position of next row
                yPos += GetHeight( ) + spacing;
                break;
            }
            case AT_Stamp:
            {

                Stamp* stamp = ( Stamp* )child;

                // each stamp is positioned in the cell

                double xBorder = ( GetWidth( ) - stamp->GetWidth( ) ) / 2;
                stamp->SetXPos( xPos + xBorder );
                stamp->SetYPos( yPos );
                // get xpos of next cell
                yPos += stamp->GetHeight( ) + spacing;
                break;
            }
            }
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        m_frame.WriteLayout( "Col::UpdatePositions >" );

    }

    // build the frame container for the column
    wxXmlNode* Column::Write( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Column", "Inserting a Column." );

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
                Column* col = ( Column* )child;
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
                std::cout << "Terminal leaf node must define the height.\n";
                status = AT_FATAL;
            }
            if ( GetWidth( ) <= 0.0 )
            {
                wxString str;
                str.Format( "Terminal leaf node must define the width. width:>>%7.2f<< \n", GetWidth( ) );
                GetErrorArray( )->Add( str );
                //                std::cout << "Terminal leaf node must define the width.\n";
                status = AT_FATAL;
            }
        }
        m_nodeValid = status;
        return status;
    }

    void Column::draw( wxDC& dc, double x, double y )
    {
        double leftPadding = 0;
        double topPadding = 0;
        dc.SetPen( *wxTRANSPARENT_PEN );
        if ( GetShowFrame( ) )
        {
            dc.SetPen( *wxBLACK_PEN );
            leftPadding = GetLeftContentPadding( );
            topPadding = GetTopContentPadding( );
        }

        m_frame.draw( dc, x, y );
        SetClientDimensions( dc, x, y, GetWidth(), GetHeight());

        if ( GetShowTitle( ) )
        {
            RealPoint pos( x, y );
            RealSize size( GetWidth( ), m_titleSize.y );
            //wxRect rect( pos, size );
            DrawTitle( dc, m_title, pos, size );
            y = y + m_titleSize.y;
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {

            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            double xPos = x + GetXPos( ) + leftPadding;
            double yPos = y + GetYPos( ) + topPadding;
            child->draw( dc, xPos, yPos );

            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    void Column::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowFrame );
    }

    void Column::ReportLayout(  )
    {
        std::cout << "Layout for Column " << "\n ";
        ReportLayoutFrame(  ) ;  
    };
}