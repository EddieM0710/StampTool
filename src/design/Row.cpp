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
 //#include "design/Title.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
#include "gui/GuiUtils.h"
#include "design/DesignDefs.h"
#include "design/Album.h"


namespace Design {

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

                // std::cout << " Row::Draw id:" << m_titleFrame->GetString( )
                //     << " y:" << y
                //     << " Height:" << GetHeight( ) << "\n";

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
            //RealPoint pos( x + GetXPos( ), y + GetYPos( ) );
            //RealSize size( GetWidth( ), GetTitleFrame( )->GetHeight( ) );
            m_titleFrame->DrawPDF( doc, xPos, yPos );
            //DrawTitlePDF( doc, m_title, pos, size );
 //           y = yPos + GetTitleFrame( )->GetHeight( );
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {

            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->DrawPDF( doc, xPos, yPos );

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    };


    void Row::LoadFonts( wxXmlNode* node )
    {
        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {
            m_titleFrame->LoadFont( fonts );
        }
    }

    void Row::ReportLayout( )
    {
        std::cout << "Layout for Row " << "\n ";
        ReportLayoutFrame( );
    };

    LabelFrame* Row::GetTitleFrame( ) { return m_titleFrame; };

    wxString  Row::GetTitleString( ) { return GetAttrStr( AT_Name ); };
    void  Row::SetTitleString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_titleFrame->SetString( str );
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
        if ( m_titleFrame->GetFontNdx( ) >= 0 )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                m_titleFrame->SaveFont( fonts );
            }
        }
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
            double leftPadding = 0;
            double rightPadding = 0;
            double topPadding = 0;
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->UpdateMinimumSize( );
            if ( child->GetMinHeight( ) > minHeight )
            {
                minHeight = child->GetMinHeight( );
            }
            minWidth += child->GetMinWidth( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        minHeight = minHeight;
        minWidth = minWidth;

        if ( GetShowTitle( ) )
        {
            // update the title frame
            UpdateString( GetTitleFrame( ), minWidth );

            // Add the title height
            minHeight += GetTitleFrame( )->GetHeight( );
            GetTitleFrame( )->SetYPos( 0 );
        }
        else
        {
            GetTitleFrame( )->Init( );
        }

        // row min height and width
        SetMinHeight( minHeight
            + GetTopContentMargin( )
            + GetBottomContentMargin( ) );
        SetMinWidth( minWidth );
        return true;
    }

    void Row::UpdateSizes( )
    {
        if ( GetShowTitle( ) )
        {
            // if showing the title then make room for it
            SetHeight( GetMinHeight( )
                + GetTitleFrame( )->GetHeight( ) );
        }
        else
        {
            SetHeight( GetMinHeight( ) );
        }

        // Set the height and width of each child column
        // Stamps have fixed height and width
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( child->IsNodeType( AT_Col ) )
            {
                child->SetWidth( GetMinWidth( ) );
                child->SetHeight( GetMinHeight( ) );
            }
            child->UpdateSizes( );

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    // calculate the row layout based on child parameters
    void Row::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page ) 
        // and begin filling in position relative to the parent

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        double xPos = 0;

        //allow for top margin
        double yPos = GetTopContentMargin( );

        //First calc title position  
        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->SetXPos( ( GetWidth( ) - GetTitleFrame( )->GetWidth( ) ) / 2 );
            GetTitleFrame( )->SetYPos( yPos );
            // allow for space above title, title height and that much again for nice spaing
            yPos += GetTitleFrame( )->GetHeight( );
        }
        else
        {
            GetTitleFrame( )->Init( );
        }
        double spacing = 4;
        if ( CalculateSpacing( ) )
        {
            // this is a row so we are positioning children across the page
            spacing = ( GetWidth( ) - GetMinWidth( ) ) / ( nbrCols + nbrStamps + 1 );

            // inital x/y pos within the row
            xPos += spacing;
        }
        else
        {
            spacing = GetFixedSpacingDbl( );
            //find the extra space to go on each end
            //it is the amount from the width of items - the minwidth - amount of total space between items  
            //then divide the remaining by 2 to go on each end
            xPos += ( ( GetWidth( ) - GetMinWidth( ) ) - ( nbrCols + nbrStamps - 1 ) * spacing ) / 2;
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            child->SetXPos( xPos );
            child->SetYPos( yPos );
            if ( ( ( Stamp* ) child )->GetTitleLocation( ) == AT_TitleLocationBottom )
            {
                child->SetYPos( yPos
                    + ( GetHeight( )
                        - GetTitleFrame( )->GetHeight( )
                        - GetTopContentMargin( )
                        - GetBottomContentMargin( )
                        - child->GetHeight( ) ) / 2 );
            }
            else
            {
                child->SetYPos( yPos
                    + GetHeight( )
                    - GetTitleFrame( )->GetHeight( )
                    - GetTopContentMargin( )
                    - GetBottomContentMargin( )
                    - child->GetHeight( ) );
            }

            // ( ( Stamp* ) child )->CalculateYPos( yPos,
            //     GetHeight( ) - GetTitleFrame( )->GetHeight( ) - GetTopContentMargin( ) - GetBottomContentMargin( ) );
            // std::cout << " Row::UpdatePositions id:" << m_titleFrame->GetString( )
            //     << " child->yPos:" << child->GetYPos( ) << "\n";
            child->UpdatePositions( );

            xPos += child->GetWidth( ) + spacing;

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        ValidateNode( );

    }


    NodeStatus Row::ValidateNode( )
    {

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
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << "Warning\n";
            }
        }

        return status;
    }

    TitleLocation  Row::GetTitleLocation( )
    {
        TitleLocation loc = FindTitleLocationType( GetAttrStr( AT_StampNameLocation ) );
        TitleLocation defaultLoc = GetAlbum( )->GetTitleLocation( );
        if ( ( loc == defaultLoc ) && ( loc != AT_TitleLocationDefault ) )
        {
            SetTitleLocation( AT_TitleLocationDefault );
        }
        return loc;
    };

    void Row::SetTitleLocation( TitleLocation loc )
    {
        TitleLocation defaultLoc = GetAlbum( )->GetTitleLocation( );
        if ( ( loc == defaultLoc ) && ( loc != AT_TitleLocationDefault ) )
        {
            loc = AT_TitleLocationDefault;
        }
        SetAttrStr( AT_StampNameLocation, StampTitleLocationStrings[ loc ] );
    };
}