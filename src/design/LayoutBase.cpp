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

    //----------------

    LayoutBase::LayoutBase( ) : AlbumBase( )
    {
        // SetTitleLocation( Design::AT_StampNamePositionDefault );
    };

    //----------------

    LayoutBase::LayoutBase( wxXmlNode* node ) : AlbumBase( node )
    {
        // SetTitleLocation( Design::AT_StampNamePositionDefault );
    };



    //----------------

    LayoutBase* LayoutBase::FindObjectByPos( double x, double y, wxString indent )
    {
        indent += "    ";
        Design::AlbumBaseType type = GetNodeType( );
        wxString name = Design::AlbumBaseNames[ type ];
        std::cout << indent << name
            << " pnt(" << x << "," << y << ") "
            << " pos(" << m_clientDimensions.GetXPos( ) << "," << m_clientDimensions.GetYPos( ) << ") "
            << " size(" << m_clientDimensions.GetWidth( ) << "," << m_clientDimensions.GetHeight( ) << ")  \n";
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
                //if ( type != AT_Title )
                //{
                LayoutBase* foundChild = child->FindObjectByPos( x, y, indent );
                if ( foundChild )
                {
                    Design::AlbumBaseType type = foundChild->GetNodeType( );
                    std::cout << indent << "foundChild " << child->GetText( ) << " \n";

                    return foundChild;
                }
                // }
                childID = GetAlbumTreeCtrl( )->GetNextChild( thisID, cookie );
            }

            std::cout << indent << "Success \n";
            return this;
        }
        std::cout << indent << "fail \n";
        return ( LayoutBase* ) 0;
    }

    //----------------

    bool LayoutBase::IsInClient( double x, double y, wxString indent )
    {
        Design::AlbumBaseType type = GetNodeType( );
        wxString name = AlbumBaseNames[ type ];
        double minx = m_clientDimensions.GetXPos( );
        double maxx = minx + m_clientDimensions.GetWidth( );
        double miny = m_clientDimensions.GetYPos( );
        double maxy = miny + m_clientDimensions.GetHeight( );


        if ( x >= minx && x <= maxx )
        {
            if ( y >= miny && y <= maxy )
            {
                return true;
            }
            else
            {
                std::cout << indent << name << " Failed y" << y << " min:" << miny << " max:" << maxy << "\n";
                //  std::cout << indent << name << " Failed x" << x << " min:" << minx << " max:" << maxx << "\n";
            }
        }
        else
        {
            std::cout << indent << name << " Failed x" << x << " min:" << minx << " max:" << maxx << "\n";
            // std::cout << indent << name << " Failed y" << y << " min:" << miny << " max:" << maxy << "\n";
        }
        return false;
    }

    //----------------

    void LayoutBase::ReportLayoutFrame( wxString indent )
    {
        m_frame.ReportLayout( indent );
        // wxString str = wxString::Format( "%sTitle Size: width:%7.2f  height:%7.2f \n",
        //     indent, m_titleFrame->GetWidth( ), m_titleFrame->GetHeight( ) );
        std::cout << "\n" << indent << "Client Dimensions ";
        m_clientDimensions.ReportLayout( indent );
    };

    //----------------

    void LayoutBase::ReportLayoutError( wxString funct, wxString err, bool fatal )
    {
        wxString funcStr = wxString::Format( "%s::%s", AttrNameStrings[ GetNodeType( ) ], funct );
        wxString msgStr = wxString::Format( "InputLine: %d;  %s", GetLineNumber( ), err );
        ReportError( funcStr, msgStr, fatal );
    }

    //----------------

    void LayoutBase::SetClientDimensions( wxDC& dc, double x, double y, double width, double height, double minWidth, double minHeight )
    {
        wxPoint pnt = dc.LogicalToDevice( x, y );
        wxSize size = dc.LogicalToDeviceRel( width, height );
        wxSize minSize = dc.LogicalToDeviceRel( minWidth, minHeight );

        m_clientDimensions.SetXPos( pnt.x );
        m_clientDimensions.SetYPos( pnt.y );
        m_clientDimensions.SetHeight( size.y );
        m_clientDimensions.SetWidth( size.x );
        m_clientDimensions.SetMinHeight( minSize.y );
        m_clientDimensions.SetMinWidth( minSize.x );
    };

    //----------------

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

    //----------------

        // calculate the label frame based on the available width and the text length
    void LayoutBase::UpdateString( Design::LabelFrame* frame, double width )
    {
        frame->UpdateString( width );
    };

    //----------------

}
