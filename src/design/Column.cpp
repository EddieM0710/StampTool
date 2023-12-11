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
 */
#include <wx/pen.h>

#include "design/Column.h"
#include "design/Row.h"
#include "design/Stamp.h"
#include "design/Album.h"
#include "design/TitleFrame.h"
#include "design/DesignDefs.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
#include "gui/GuiUtils.h"

namespace Design {



    Column::Column( wxXmlNode* node ) : LayoutBase( node ) {
        SetNodeType( AT_Col );
        SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
        SetShowFrame( false );
        SetShowTitle( false );
        SetShowSubTitle( false );
        SetFixedSpacingSize( "4" );
        SetCalculateSpacing( true );
        m_titleFrame = new TitleFrame( this );
        m_titleFrame->SetHeadingString( GetAttrStr( AT_Name ) );
        m_titleFrame->SetSubHeadingString( GetAttrStr( AT_SubTitle ) );

    };


    void Column::InitParameters( )
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

        wxString location = GetStampNameLocation( );
        if ( location.Cmp( Design::StampNameLocationStrings[ AT_StampNameLocationTop ] ) &&
            location.Cmp( Design::StampNameLocationStrings[ AT_StampNameLocationBottom ] ) &&
            location.Cmp( Design::StampNameLocationStrings[ AT_StampNameLocationDefault ] ) )
        {
            SetDefaultStampNameLocation( AT_StampNameLocationDefault );
        }


        // CalculateSpacing="true">

    }

    TitleFrame* Column::GetTitleFrame( )
    {
        return m_titleFrame;
    };

    wxString Column::GetTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    void Column::SetTitleString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_titleFrame->SetHeadingString( str );
    };

    wxString Column::GetSubTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    void Column::SetSubTitleString( wxString str )
    {
        SetAttrStr( AT_SubTitle, str );
        m_titleFrame->SetSubHeadingString( str );
    };




    void Column::Draw( wxDC& dc, double x, double y )
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
                m_titleFrame->Draw( dc, xPos, yPos );
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
    void Column::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        double leftPadding = 0;
        double topPadding = 0;
        //  dc.SetPen( *wxBLACK_PEN );
        if ( GetShowFrame( ) )
        {
            wxPdfLineStyle currStyle = PDFLineStyle( doc, *wxBLACK, .2 );
            m_frame.DrawPDF( doc, x, y );
            doc->SetLineStyle( currStyle );
        }

        double xPos = x + GetXPos( );
        double yPos = y + GetYPos( );

        if ( GetShowTitle( ) )
        {
            m_titleFrame->DrawPDF( doc, xPos, yPos );
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->DrawPDF( doc, xPos, yPos );

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }


    void Column::LoadFonts( wxXmlNode* node )
    {
        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {
            m_titleFrame->LoadFonts( fonts );
        }
    }

    void Column::ReportLayout( )
    {
        std::cout << "Layout for Column " << "\n ";
        ReportLayoutFrame( );
    };


    void Column::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_ShowFrame );
        SaveFonts( xmlNode );
    }

    void Column::SaveFonts( wxXmlNode* parent )
    {
        m_titleFrame->SaveFonts( parent );
    }

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
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            // calc the min size ror this items children
            child->UpdateMinimumSize( );

            // keep the max min width

            if ( child->GetMinWidth( ) > minWidth )
            {
                minWidth = child->GetMinWidth( );
            }

            // keep running total of min child height
            minHeight += child->GetMinHeight( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        GetTitleFrame( )->Init( );
        if ( GetShowTitle( ) )
        {
            // update the title frame
            m_titleFrame->UpdateString( minWidth, minWidth );

            //***
            // SetHeight( GetHeight( ) + GetTitleFrame( )->GetHeight( ) );

                        // add the title height
            minHeight += GetTitleFrame( )->GetHeight( );

            GetTitleFrame( )->SetYPos( 0 );
        }

        SetMinHeight( minHeight
            + GetTopContentMargin( )
            + GetBottomContentMargin( ) );
        SetMinWidth( minWidth
            + GetLeftContentMargin( )
            + GetRightContentMargin( ) );

        GetErrorArray( )->Empty( );

        return true;
    }

    // calculate the column layout based on child parameters
    void Column::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page ) 
        // and begin filling in position relative to the parent

       // calc space used by children
         // this means looping through the children and getting the actual sizes 
         // of the children, not their calculated min size
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        LayoutBase* parent = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( parentID );
        int nbrChildren = parent->GetNbrChildren( );

        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        double actualWidth = 0;
        double actualHeight = 0;
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            actualHeight += child->GetHeight( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        double xPos = 0;
        double yPos = GetTopContentMargin( );//0;
        //First calc title position  
        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->SetXPos( ( GetWidth( ) - GetTitleFrame( )->GetWidth( ) ) / 2 );
            GetTitleFrame( )->SetYPos( 2 );
            // allow for space above title, title height and that much again for nice spaing
            yPos += GetTitleFrame( )->GetHeight( ) + 2 * GetTopContentMargin( );
        }
        else
        {
            GetTitleFrame( )->Init( );
            yPos = GetTopContentMargin( );
        }

        // this is a col so we are positioning children down the page
        //double spacing = ( GetHeight( ) - GetMinHeight( ) ) / ( nbrRows + nbrStamps + 1 );
        double spacing = 4;
        if ( CalculateSpacing( ) )
        {
            spacing = ( GetHeight( ) - actualHeight ) / ( nbrChildren + 1 );

            // inital x/y pos within the row
            yPos += spacing;
        }
        else
        {
            spacing = GetFixedSpacingDbl( );
            yPos += ( ( GetHeight( )
                - actualHeight )
                - ( nbrChildren - 1 ) * spacing ) / 2;
        }

        childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->SetXPos( xPos );
            child->SetYPos( yPos );


            child->UpdatePositions( );

            yPos += child->GetHeight( ) + spacing;

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        ValidateNode( );
    }

    void Column::UpdateSizes( )
    {
        // Set the height and width of each child  column
        // Stamps have fixed height and width
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        LayoutBase* parent = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( parentID );
        int nbrChildren = parent->GetNbrChildren( );

        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( child->IsNodeType( AT_Row ) ) // i.e., stamps are fixed don't try to change them
            {
                child->SetWidth( GetWidth( )
                    - GetLeftContentMargin( )
                    - GetRightContentMargin( ) );
                child->SetHeight( child->GetMinHeight( )
                    + ( GetHeight( ) - GetMinHeight( ) ) / ( 2 * nbrChildren )
                    - GetLeftContentMargin( )
                    - GetRightContentMargin( ) );
            }
            child->UpdateSizes( );

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

    }

    NodeStatus Column::ValidateNode( )
    {
        CheckLayout( );

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

    //*******

    wxString Column::GetStampNameLocation( )
    {
        return GetAttrStr( AT_StampNameLocation );
    }

    //*******

    // void Column::SetDefaultStampNameLocation( StampNameLocation loc )
    // {
    //     SetAttrStr( AT_StampNameLocation, StampNameLocationStrings[ loc ] );
    // }

    //*******

    StampNameLocation  Column::GetDefaultStampNameLocationType( )
    {
        StampNameLocation loc = FindStampLocationType( GetAttrStr( AT_StampNameLocation ) );
        StampNameLocation defaultLoc = GetAlbum( )->GetDefaultStampNameLocationType( );
        if ( ( loc == defaultLoc ) && ( loc != AT_StampNameLocationDefault ) )
        {
            SetDefaultStampNameLocation( AT_StampNameLocationDefault );
        }
        return loc;
    };

    //*******

    void Column::SetDefaultStampNameLocation( StampNameLocation loc )
    {
        StampNameLocation defaultLoc = GetAlbum( )->GetDefaultStampNameLocationType( );
        if ( ( loc == defaultLoc ) && ( loc != AT_StampNameLocationDefault ) )
        {
            loc = AT_StampNameLocationDefault;
        }
        SetAttrStr( AT_StampNameLocation, StampNameLocationStrings[ loc ] );
    };
}