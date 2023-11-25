/**
 * @file Row.cpp
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
 */


#include <wx/pen.h>

#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "design/TitleFrame.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
#include "gui/GuiUtils.h"
#include "design/DesignDefs.h"
#include "design/Album.h"


namespace Design {

    Row::Row( wxXmlNode* node ) : LayoutBase( node )
    {
        SetNodeType( AT_Row );

        m_titleFrame = new TitleFrame( this );
        m_titleFrame->SetHeadingString( GetAttrStr( AT_Name ) );
        m_titleFrame->SetSubHeadingString( GetAttrStr( AT_SubTitle ) );

        InitParameters( );
    };


    void Row::InitParameters( )
    {
        SetTitleString( GetAttrStr( AT_Name ) );
        if ( !GetShowTitle( ) )
        {
            m_titleFrame->Init( );
        }
        SetTopContentMargin( 2 );
        SetBottomContentMargin( 2 );
        SetLeftContentMargin( 2 );
        SetRightContentMargin( 2 );

        Design::StampNameLocation location = GetDefaultStampNameLocationType( );
        if ( location != AT_StampNameLocationTop &&
            location != AT_StampNameLocationBottom &&
            location != AT_StampNameLocationDefault )
        {
            SetDefaultStampNameLocation( AT_StampNameLocationDefault );
        }

        AlignmentMode align = GetAlignmentModeType( );
        if ( align != AlignTop && align != AlignBottom && align != AlignMiddle )
        {
            SetAlignmentMode( AlignDefault );
        }
        // CalculateSpacing="true">

    }



    wxString Row::GetTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    void Row::SetTitleString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_titleFrame->SetHeadingString( str );
    };

    wxString Row::GetSubTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    void Row::SetSubTitleString( wxString str )
    {
        SetAttrStr( AT_SubTitle, str );
        m_titleFrame->SetSubHeadingString( str );
    };


    TitleFrame* Row::GetTitleFrame( )
    {
        return m_titleFrame;
    };

    void Row::Draw( wxDC& dc, double x, double y )
    {
        Design::NodeStatus status = GetNodeStatus( );
        if ( status != Design::AT_FATAL )
        {

            double leftPadding = 0;
            double topPadding = 0;

            dc.SetPen( *wxBLACK_PEN );

            if ( GetShowFrame( ) )
            {
                m_frame.Draw( dc, x, y );
            }

            SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetWidth( ), GetHeight( ) );

            double xPos = x + GetXPos( );
            double yPos = y + GetYPos( );

            if ( GetShowTitle( ) )
            {
                GetTitleFrame( )->Draw( dc, xPos, yPos );
            }

            wxTreeItemIdValue cookie;
            wxTreeItemId parentID = GetTreeItemId( );
            wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
            while ( childID.IsOk( ) )
            {

                LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
                child->Draw( dc, xPos, yPos );

                childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
            }
        }
    }

    void Row::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        double leftPadding = 0;
        double topPadding = 0;
        if ( GetShowFrame( ) )
        {

            wxPdfLineStyle currStyle = PDFLineStyle( doc, *wxBLACK, .2 );
            m_frame.DrawPDF( doc, x, y );
            doc->SetLineStyle( currStyle );
        }
        //m_frame.DrawPDF( doc, x, y );

        double xPos = x + GetXPos( ) + leftPadding;
        double yPos = y + GetYPos( ) + topPadding;

        if ( GetShowTitle( ) )
        {
            m_titleFrame->DrawPDF( doc, xPos, yPos );
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {

            //            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->DrawPDF( doc, xPos, yPos );

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    };


    void Row::LoadFonts( wxXmlNode* node )
    {
        m_titleFrame->SaveFonts( node );
    }

    void Row::ReportLayout( )
    {
        std::cout << "Layout for Row " << "\n ";
        ReportLayoutFrame( );
    };




    void Row::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_ShowFrame );
        SetAttribute( xmlNode, AT_SubTitle );
        SetAttribute( xmlNode, AT_StampNameLocation );
        SetAttribute( xmlNode, AT_CalculateSpacing );
        SetAttribute( xmlNode, AT_ShowFrame );


        SaveFonts( xmlNode );
    }


    void Row::SaveFonts( wxXmlNode* parent )
    {
        m_titleFrame->SaveFonts( parent );
    }

    bool Row::UpdateMinimumSize( )
    {
        //Positioning across the row.
         //The min height of the row is the size of the tallest child 
         //plus the title if used
         //The min width is the sum of the min widths of the children. 
        double minWidth = 0.0;
        double minHeight = 0.0;

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {

            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            // calc the min size ror this items children
            child->UpdateMinimumSize( );


            // keep the max min height
            if ( child->GetMinHeight( ) > minHeight )
            {
                minHeight = child->GetMinHeight( );
            }

            // keep running total of min child width
            minWidth += child->GetMinWidth( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        //if this item shows its title then add that to the min height
        GetTitleFrame( )->Init( );
        if ( GetShowTitle( ) )
        {
            // update the title frame
            m_titleFrame->UpdateString( minWidth, minWidth );

            // Add the title height
            minHeight += GetTitleFrame( )->GetHeight( );

            GetTitleFrame( )->SetYPos( 0 );
        }

        // row min height and width
        SetMinHeight( minHeight
            + GetTopContentMargin( )
            + GetBottomContentMargin( ) );

        SetMinWidth( minWidth
            + GetLeftContentMargin( )
            + GetRightContentMargin( ) );

        GetErrorArray( )->Empty( );

        return true;
    }

    // calculate the row layout based on child parameters
    void Row::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page ) 
        // and begin filling in position relative to the parent

        // calc space used by children
         // this means looping through the children and getting the actual sizes 
         // of the children, not their calculated min size
        double actualWidth = 0;
        double maxHeight = 0;
        double maxTitleHeight = 0;
        double maxFrameHeight = 0;

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        LayoutBase* parent = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( parentID );
        int nbrChildren = parent->GetNbrChildren( );

        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );

        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            actualWidth += child->GetWidth( );
            if ( child->GetHeight( ) > maxHeight )
            {
                maxHeight = child->GetHeight( );
            }
            if ( child->IsNodeType( AT_Stamp ) )
            {
                Stamp* stamp = ( Stamp* ) child;
                //std::cout << stamp->GetNameFrame( )->GetString( ) << " max:" << maxTitleHeight << "  found:" << stamp->GetNameFrame( )->GetHeight( );

                if ( stamp->GetNameFrame( )->GetHeight( ) > maxTitleHeight )
                {
                    maxTitleHeight = stamp->GetNameFrame( )->GetHeight( );
                }
                //std::cout << "  new max:" << maxTitleHeight << "\n";

                if ( stamp->GetBorderFrame( )->GetHeight( ) > maxFrameHeight )
                {
                    maxFrameHeight = stamp->GetBorderFrame( )->GetHeight( );
                }
            }
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        double xPos = 0;
        double yPos = 0;

        //First calc title position  
        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->SetXPos( ( GetWidth( ) - GetTitleFrame( )->GetWidth( ) - GetLeftContentMargin( ) ) / 2 );
            GetTitleFrame( )->SetYPos( GetRightContentMargin( ) );
            // Children start just below the title Frame
            // allow for space above title and space above and below it
            yPos = GetTitleFrame( )->GetHeight( ) + GetTopContentMargin( ) + GetBottomContentMargin( );
        }
        else
        {
            GetTitleFrame( )->Init( );
            yPos = GetTopContentMargin( );
        }


        double spacing = 4;
        // this is a row so we are positioning children across the page
        if ( CalculateSpacing( ) )
        {
            spacing = ( GetWidth( )
                - GetLeftContentMargin( )
                - GetRightContentMargin( )
                - actualWidth )
                / ( nbrChildren + 1 );

            // inital x/y pos within the row
            xPos = spacing + GetLeftContentMargin( );

        }
        else
        {
            spacing = GetFixedSpacingDbl( );
            //find the extra space to go on each end
            //it is the amount from the width of items - the minwidth - amount of total space between items  
            //then divide the remaining by 2 to go on each end
            xPos = (
                GetWidth( ) // width of object
                - GetLeftContentMargin( ) //less left content
                - GetRightContentMargin( ) //less right content
                - actualWidth // actual width used by children
                - ( nbrChildren - 1 ) * spacing //less the width between the children
                )
                / 2; // and leave half on the beginning of the row

        }

        if ( xPos < 0 )xPos = 0;
        if ( yPos < 0 )yPos = 0;

        wxTreeItemIdValue cookie1;

        childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie1 );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->SetXPos( xPos );
            child->SetYPos( yPos );

            //  AlbumBaseType baseType =  GetAlbumTreeCtrl( )->GetItemType( childID );

            double childTop = ( GetHeight( ) - maxHeight ) / 2
                - GetTopContentMargin( )
                - GetBottomContentMargin( );

            if ( childTop < 0 )childTop = 0;


            if ( child->IsNodeType( AT_Stamp ) )
            {
                Design::AlignmentMode m_stampAlign = GetAlignmentModeType( );
                if ( m_stampAlign == AlignDefault )
                {
                    m_stampAlign = GetAlbum( )->GetAlignmentModeType( );
                }
                Stamp* stamp = ( Stamp* ) child;

                // std::cout << stamp->GetNameFrame( )->GetString( ) << "\n";

                if ( maxTitleHeight < stamp->GetNameFrame( )->GetHeight( ) )
                {
                    std::cout << "Error in Row::UpdatePosition  "
                        << stamp->GetNameFrame( )->GetString( ) << " "
                        << "  maxTitleHeight" << maxTitleHeight
                        << "  Height " << stamp->GetNameFrame( )->GetHeight( )
                        << "\n";
                    while ( 0 )
                    {
                    };
                }
                if ( stamp->GetStampNameLocationType( ) == AT_StampNameLocationTop )
                {
                    // align stamp top
                    if ( m_stampAlign == AlignTop )
                    {
                        child->SetYPos( yPos
                            + childTop
                            + maxTitleHeight
                            - stamp->GetNameFrame( )->GetHeight( ) );
                    }
                    // align stamp bottom
                    else if ( m_stampAlign == AlignBottom )
                    {
                        child->SetYPos( yPos
                            + childTop
                            + maxHeight
                            - stamp->GetHeight( ) );
                    }
                    // align stamp middle
                    else if ( m_stampAlign == AlignMiddle )
                    {
                        child->SetYPos( yPos
                            + childTop
                            + maxTitleHeight
                            - stamp->GetNameFrame( )->GetHeight( )
                            + maxFrameHeight / 2
                            - stamp->GetBorderFrame( )->GetHeight( ) / 2 );
                    }
                }
                else if ( stamp->GetStampNameLocationType( ) == AT_StampNameLocationBottom )
                {
                    // align stamp top
                    if ( m_stampAlign == AlignTop )
                    {
                        child->SetYPos( yPos
                            + childTop );
                    }
                    // align stamp bottom
                    if ( m_stampAlign == AlignBottom )
                    {
                        child->SetYPos( yPos
                            + childTop
                            + maxFrameHeight
                            - stamp->GetBorderFrame( )->GetHeight( ) );
                    }
                    // align stamp middle
                    if ( m_stampAlign == AlignMiddle )
                    {
                        child->SetYPos( yPos
                            + childTop
                            + maxFrameHeight / 2
                            - stamp->GetBorderFrame( )->GetHeight( ) / 2 );
                    }
                }
            }
            else
            {
                child->SetYPos( yPos + childTop );
            }


            child->UpdatePositions( );

            xPos += child->GetWidth( ) + spacing;

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie1 );
        }
        ValidateNode( );

    }

    void Row::UpdateSizes( )
    {
        // Set the height and width of each child column
        // Stamps have fixed height and width
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        LayoutBase* parent = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( parentID );
        int nbrChildren = parent->GetNbrChildren( );

        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            if ( child->IsNodeType( AT_Col ) ) // i.e., stamps are fixed don't try to change them
            {
                child->SetHeight( GetHeight( )
                    - GetTopContentMargin( )
                    - GetBottomContentMargin( ) );
                child->SetWidth( child->GetMinWidth( )
                    + ( GetWidth( ) - GetMinWidth( ) ) / ( 2 * nbrChildren ) // instead of just min width, make it a little bigger
                    - GetLeftContentMargin( )
                    - GetRightContentMargin( ) );
            }
            child->UpdateSizes( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

    }

    NodeStatus Row::ValidateNode( )
    {
        CheckLayout( );
        NodeStatus status = AT_OK;
        if ( !HasChildren( ) )
        {
            GetErrorArray( )->Empty( );
            if ( GetHeight( ) <= 0.0 )
            {
                wxString str;
                str = wxString::Format( "Terminal leaf node must define the height. height:>>%7.2f<< \n", GetHeight( ) );
                GetErrorArray( )->Add( str );
                m_debugString.Append( str );
                status = AT_FATAL;
            }
            if ( GetWidth( ) <= 0.0 )
            {
                wxString str;
                str = wxString::Format( "Terminal leaf node must define the height. width:>>%7.2f<< \n", GetWidth( ) );
                GetErrorArray( )->Add( str );
                m_debugString.Append( str );
                status = AT_FATAL;
            }
        }

        m_nodeValid = status;
        wxTreeItemId id = GetTreeItemId( );
        if ( id.IsOk( ) )
        {
            if ( status == AT_FATAL )
            {
                GetAlbumTreeCtrl( )->SetItemBackgroundColour( id, *wxRED );
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << "Fatal\n";
            }
            else if ( status == AT_WARNING )
            {
                GetAlbumTreeCtrl( )->SetItemBackgroundColour( id, *wxYELLOW );
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << " Warning\n";
            }
        }

        return status;
    }

    // Stamp Name Location functions

    //******* 

    wxString Row::GetStampNameLocation( )
    {
        return GetAttrStr( AT_StampNameLocation );
    }

    //******* 

    StampNameLocation  Row::GetDefaultStampNameLocationType( )
    {
        StampNameLocation loc = FindStampLocationType( GetStampNameLocation( ) );
        if ( loc == AT_StampNameLocationDefault )
        {
            return GetAlbum( )->GetDefaultStampNameLocationType( );
        }
        return loc;

    };

    //******* 

    void Row::SetDefaultStampNameLocation( StampNameLocation loc )
    {
        SetAttrStr( AT_StampNameLocation, StampNameLocationStrings[ loc ] );
    }

    //******* 

    void Row::SetDefaultStampNameLocationType( StampNameLocation loc )
    {
        StampNameLocation defaultLoc = GetAlbum( )->GetDefaultStampNameLocationType( );
        if ( loc == defaultLoc )
        {
            SetAttrStr( AT_StampNameLocation, "" );
        }
        else
        {
            SetDefaultStampNameLocation( loc );
        }
    };

    //******* 

    // Stamp Alignment functions

    // wxString Row::GetAlignmentMode( )
    // {
    //     return GetAttrStr( AT_StampAlignmentMode );
    // }

    //******* 

    void Row::SetAlignmentMode( AlignmentMode loc )
    {
        SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ loc ] );
    }

    //******* 

    AlignmentMode  Row::GetAlignmentModeType( )
    {
        return FindAlignmentModeType( GetAttrStr( AT_StampAlignmentMode ) );
    };

    //******* 

    void Row::SetAlignmentModeType( AlignmentMode loc )
    {
        AlignmentMode defaultLoc = GetAlbum( )->GetAlignmentModeType( );
        if ( loc == defaultLoc )
        {
            SetAttrStr( AT_StampAlignmentMode, "" );
        }
        else
        {
            SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ loc ] );
        }
    };

}