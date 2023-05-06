/**
 * @file LayoutBase.cpp
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

#include "design/AlbumBase.h"

#include <iostream>


#include "LayoutBase.h"
#include "design/Page.h"
#include "design/LabelFrame.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "gui/AlbumImagePanel.h"
#include "gui/AlbumTreeCtrl.h"


namespace Design {

    LayoutBase::LayoutBase( ) : AlbumBase( )
    {

        SetTopContentPadding( 0 );
        SetBottomContentPadding( 0 );
        SetLeftContentPadding( 0 );
        SetRightContentPadding( 0 );
        SetTitleLocation( Design::AT_TitleLocationDefault );
    };


    LayoutBase::LayoutBase( wxXmlNode* node ) : AlbumBase( node )
    {

        SetTopContentPadding( 0 );
        SetBottomContentPadding( 0 );
        SetLeftContentPadding( 0 );
        SetRightContentPadding( 0 );
        SetTitleLocation( Design::AT_TitleLocationDefault );
    };




    void LayoutBase::DumpLayout( double x, double y )
    {
        AlbumBaseType type = GetNodeType( );
        m_frame.WriteLayout( GetObjectName( ) );
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            double xPos = x + GetXPos( );
            double yPos = y + GetYPos( );

            child->DumpLayout( xPos, yPos );

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    void LayoutBase::DumpObjectLayout( wxString indent )
    {
        indent += "    ";
        Design::AlbumBaseType type = GetNodeType( );
        wxString name = Design::AlbumBaseNames[ type ];
        std::cout << "\n" << indent << name << " Pos( " << m_clientDimensions.GetXPos( )
            << ", " << m_clientDimensions.GetYPos( )
            << " ) Size( " << m_clientDimensions.GetWidth( ) << ", " << m_clientDimensions.GetHeight( ) << " )\n";

        wxTreeItemId thisID = GetTreeItemId( );
        wxTreeItemIdValue cookie;
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( thisID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            //layout everything except the title
            if ( type != AT_Title )
            {
                child->DumpObjectLayout( indent );
            }
            childID = GetAlbumTreeCtrl( )->GetNextChild( thisID, cookie );
        }

    }

    LayoutBase* LayoutBase::FindObjectByPos( double x, double y, wxString indent )
    {
        indent += "    ";
        Design::AlbumBaseType type = GetNodeType( );
        wxString name = Design::AlbumBaseNames[ type ];
        std::cout << indent << name
            << " pnt(" << x << "," << y << ") "
            << " pos(" << m_clientDimensions.GetXPos( ) << "," << m_clientDimensions.GetYPos( ) << ") "
            << " size(" << m_clientDimensions.GetWidth( ) << "," << m_clientDimensions.GetHeight( ) << ")\n";
        if ( IsInClient( x, y, indent ) )
        {
            wxTreeItemId thisID = GetTreeItemId( );
            wxTreeItemIdValue cookie;
            wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( thisID, cookie );
            while ( childID.IsOk( ) )
            {
                AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
                LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
                //layout everything except the title
                if ( type != AT_Title )
                {
                    LayoutBase* foundChild = child->FindObjectByPos( x, y, indent );
                    if ( foundChild )
                    {
                        Design::AlbumBaseType type = foundChild->GetNodeType( );
                        std::cout << indent << "foundChild \n";
                        return foundChild;
                    }
                }
                childID = GetAlbumTreeCtrl( )->GetNextChild( thisID, cookie );
            }
            std::cout << indent << "Success \n";
            return this;
        }
        std::cout << indent << "fail \n";
        return ( LayoutBase* ) 0;
    }


    TitleLocation LayoutBase::GetTitleLayoutLocation( )
    {
        if ( m_titleLocation == AT_TitleLocationDefault )
        {
            LayoutBase* parent = ( LayoutBase* ) GetParent( );
            if ( !parent )
            {
                return AT_TitleLocationBottom;
            }
            TitleLocation parentLoc = parent->GetTitleLayoutLocation( );
            if ( parentLoc != AT_TitleLocationDefault )
            {
                return parentLoc;
            }
            else if ( parent->IsNodeType( AT_Col ) )
            {
                return AT_TitleLocationLeft;
            }
            else
            {
                return AT_TitleLocationBottom;
            }
        }
        else
        {
            return m_titleLocation;
        }
    }
    bool LayoutBase::IsInClient( double x, double y, wxString indent )
    {
        Design::AlbumBaseType type = GetNodeType( );
        wxString name = AlbumBaseNames[ type ];
        double minx = m_clientDimensions.GetXPos( );
        double maxx = minx + m_clientDimensions.GetWidth( );
        double miny = m_clientDimensions.GetYPos( );
        double maxy = miny + m_clientDimensions.GetHeight( );

        if ( x > minx && x < maxx )
        {
            if ( y > miny && y < maxy )
            {

                return true;
            }
            else
            {
                std::cout << indent << name << " Failed y" << y << " min:" << miny << " max:" << maxy << "\n";
                std::cout << indent << name << " Failed x" << x << " min:" << minx << " max:" << maxx << "\n";

            }
        }
        else
        {
            std::cout << indent << name << " Failed x" << x << " min:" << minx << " max:" << maxx << "\n";
            std::cout << indent << name << " Failed y" << y << " min:" << miny << " max:" << maxy << "\n";

        }
        return false;
    }

    bool LayoutBase::IsTitleLocation( TitleLocation loc )
    {
        return( GetTitleLayoutLocation( ) == loc );
    }

    void LayoutBase::ReportLayoutFrame( wxString indent )
    {
        m_frame.ReportLayout( indent );
        // wxString str = wxString::Format( "%sTitle Size: width:%7.2f  height:%7.2f \n",
        //     indent, m_titleFrame->GetWidth( ), m_titleFrame->GetHeight( ) );
        std::cout << "\n" << indent << "Client Dimensions ";
        m_clientDimensions.ReportLayout( indent );
    };

    void LayoutBase::ReportLayoutError( wxString funct, wxString err, bool fatal )
    {
        wxString funcStr = wxString::Format( "%s::%s", AttrNameStrings[ GetNodeType( ) ], funct );
        wxString msgStr = wxString::Format( "InputLine: %d;  %s", GetLineNumber( ), err );
        ReportError( funcStr, msgStr, fatal );
    }

    // void LayoutBase::SetClientDimensions( Frame *frame )
    // { 
    //     m_clientDimensions.SetXPos( frame->GetXPos( ) *  Design::ScaleFactor.x );
    //     m_clientDimensions.SetYPos( frame->GetYPos( ) *  Design::ScaleFactor.y );
    //     m_clientDimensions.SetHeight( frame->GetHeight( ) *  Design::ScaleFactor.y );
    //     m_clientDimensions.SetWidth( frame->GetWidth( ) *  Design::ScaleFactor.x );
    //     m_clientDimensions.SetMinHeight( frame->GetMinHeight( ) *  Design::ScaleFactor.y );
    //     m_clientDimensions.SetMinWidth( frame->GetMinWidth( ) *  Design::ScaleFactor.x );
    // };

    void LayoutBase::SetClientDimensions( wxDC& dc, double x, double y, double width, double height, double minWidth, double minHeight )
    {
        //std::cout << "pos ( " << x <<", "<< y <<" )  size ( "<< width <<", "<< height << " )\n";
        wxPoint pnt = dc.LogicalToDevice( x * Design::ScaleFactor.x, y * Design::ScaleFactor.y );
        wxSize size = dc.LogicalToDeviceRel( width * Design::ScaleFactor.x, height * Design::ScaleFactor.y );
        wxSize minSize = dc.LogicalToDeviceRel( minWidth * Design::ScaleFactor.x, minHeight * Design::ScaleFactor.y );

        //std::cout << "           pos ( " << pnt.x <<", "<< pnt.y <<" )  size ( "<< size.GetX( ) <<", "<< size.GetY( ) << " )\n";

        m_clientDimensions.SetXPos( pnt.x );
        m_clientDimensions.SetYPos( pnt.y );
        m_clientDimensions.SetHeight( size.y );
        m_clientDimensions.SetWidth( size.x );
        m_clientDimensions.SetMinHeight( minSize.y );
        m_clientDimensions.SetMinWidth( minSize.x );
    };

    void LayoutBase::ValidateChildType( int& nbrRows, int& nbrCols, int& nbrLeaf )
    {
        // count the number of rows/cols planned
        nbrRows = 0;
        nbrCols = 0;
        nbrLeaf = 0;

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
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
                    nbrLeaf++;
                    break;
                }
                case AT_Text:
                {
                    nbrLeaf++;
                    break;
                }
            }
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        if ( ( nbrRows > 0 ) && ( nbrCols > 0 ) )
        {
            ReportLayoutError( "ValidateChildType", "Only Rows or Columns are allowed as the children, not both" );
        }
    }


    void LayoutBase::UpdateString( Design::LabelFrame* frame, double width )
    {

        frame->UpdateString( width );
    };



}