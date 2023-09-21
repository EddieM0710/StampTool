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
        m_titleFrame = new LabelFrame( Design::AT_TitleFontType );
        m_titleFrame->SetString( GetAttrStr( AT_Name ) );
    };


    void Column::InitParameters( )
    {
        SetTitleString( GetAttrStr( AT_Name ) );
        if ( GetShowTitle( ) )
        {
            m_titleFrame->SetString( GetAttrStr( AT_Name ) );
        }
        else
        {
            m_titleFrame->Init( );
        }
        SetTopContentMargin( 2 );
        SetBottomContentMargin( 2 );
        SetLeftContentMargin( 2 );
        SetRightContentMargin( 2 );

        wxString location = GetTitleLocation( );
        if ( location.Cmp( Design::StampTitleLocationStrings[ AT_TitleLocationTop ] ) &&
            location.Cmp( Design::StampTitleLocationStrings[ AT_TitleLocationBottom ] ) &&
            location.Cmp( Design::StampTitleLocationStrings[ AT_TitleLocationDefault ] ) )
        {
            SetTitleLocation( AT_TitleLocationDefault );
        }


        // CalculateSpacing="true">

    }
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
            m_frame.DrawPDF( doc, x, y );
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

    LabelFrame* Column::GetTitleFrame( ) {
        return m_titleFrame;
    };

    wxString Column::GetTitleString( ) {
        return m_titleFrame->GetString( );
    };

    void Column::LoadFonts( wxXmlNode* node )
    {
        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {
            m_titleFrame->LoadFont( fonts );
        }
    }

    void Column::ReportLayout( )
    {
        std::cout << "Layout for Column " << "\n ";
        ReportLayoutFrame( );
    };

    void  Column::SetTitleString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_titleFrame->SetString( str );
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
        if ( m_titleFrame->GetFontNdx( ) >= 0 )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                m_titleFrame->SaveFont( fonts );
            }
        }
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
            child->UpdateMinimumSize( );
            if ( child->GetMinWidth( ) > minWidth )
            {
                minWidth = child->GetMinWidth( );
            }
            minHeight += child->GetMinHeight( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;
        // //if ( GetShowFrame( ) )
        // {
        //     leftPadding = GetLeftContentMargin( );
        //     rightPadding = GetRightContentMargin( );
        //     topPadding = GetTopContentMargin( );
        //     bottomPadding = GetBottomContentMargin( );
        // }

        minHeight = minHeight + topPadding + bottomPadding;
        minWidth = minWidth;//+ leftPadding + rightPadding;

        m_titleFrame->UpdateString( minWidth );

        if ( GetShowTitle( ) )
        {
            // update the title frame
            UpdateString( GetTitleFrame( ), minWidth );

            SetHeight( GetHeight( ) + GetTitleFrame( )->GetHeight( ) );

            // Allow 3 times the title height
            minHeight += GetTitleFrame( )->GetHeight( );
            GetTitleFrame( )->SetYPos( 0 );// GetTitleFrame( )->GetHeight( ) );
        }

        SetMinHeight( minHeight );
        SetMinWidth( minWidth );
        return true;
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
            GetTitleFrame( )->SetYPos( 2 );
            // allow for space above title, title height and that much again for nice spaing
            yPos = GetTitleFrame( )->GetHeight( );
        }

        // this is a col so we are positioning children down the page
        //double spacing = ( GetHeight( ) - GetMinHeight( ) ) / ( nbrRows + nbrStamps + 1 );
        double spacing = 4;
        if ( CalculateSpacing( ) )
        {
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
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->SetXPos( xPos );
            child->SetYPos( yPos );
            //calc position of next child

            child->UpdatePositions( );

            yPos += child->GetHeight( ) + spacing;

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        ValidateNode( );
    }

    void Column::UpdateSizes( )
    {
        SetWidth( GetMinWidth( ) - GetLeftContentMargin( ) - GetRightContentMargin( ) );

        // Set the height and width of each child  column
        // Stamps have fixed height and width
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            //AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( child->IsNodeType( AT_Row ) )
            {
                child->SetWidth( GetMinWidth( ) );
                child->SetHeight( GetMinHeight( ) );

            }
            child->UpdateSizes( );


            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
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

    wxString Column::GetTitleLocation( )
    {
        return GetAttrStr( AT_StampNameLocation );
    }
    void Column::SetTitleLocation( TitleLocation loc )
    {
        SetAttrStr( AT_StampNameLocation, StampTitleLocationStrings[ loc ] );
    }

    TitleLocation  Column::GetTitleLocationType( )
    {
        TitleLocation loc = FindTitleLocationType( GetAttrStr( AT_StampNameLocation ) );
        TitleLocation defaultLoc = GetAlbum( )->GetTitleLocationType( );
        if ( ( loc == defaultLoc ) && ( loc != AT_TitleLocationDefault ) )
        {
            SetTitleLocationType( AT_TitleLocationDefault );
        }
        return loc;
    };

    void Column::SetTitleLocationType( TitleLocation loc )
    {
        TitleLocation defaultLoc = GetAlbum( )->GetTitleLocationType( );
        if ( ( loc == defaultLoc ) && ( loc != AT_TitleLocationDefault ) )
        {
            loc = AT_TitleLocationDefault;
        }
        SetAttrStr( AT_StampNameLocation, StampTitleLocationStrings[ loc ] );
    };
}