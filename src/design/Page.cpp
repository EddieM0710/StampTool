/**
 * @file Page.cpp
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

#include "Defs.h"

#include "design/Page.h"
#include "design/Album.h"
#include "design/Title.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "design/DesignData.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/GuiUtils.h"

namespace Design { 


    bool Page::UpdateMinimumSize( )
    { 
        //        m_frame.WriteLayout( "Page::UpdateMinimumSize <" );


        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );
        // count the number of rows/cols planned

        double minWidth = 0.0;
        double minHeight = 0.0;

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );

            //layout everything except the title
            if ( child->GetNodeType( ) != AT_Title )
            { 
                child->UpdateMinimumSize( );

                if ( nbrCols > 0 )
                { 
                    //positioning across the page
                    //the min height of the page is the size of the tallest child 
                    //the min width is the sum of the min widths of the children 
                    if ( child->GetMinHeight( ) > minHeight )
                    { 
                        minHeight = child->GetMinHeight( );
                    }
                    minWidth += child->GetMinWidth( );
                }
                else
                { 
                    // positioning down the page
                    //the min width of the page is the size of the widest child 
                    //the min height is the sum of the min heights of the children 
                    if ( child->GetMinWidth( ) > minWidth )
                    { 
                        minWidth = child->GetMinWidth( );
                    }
                    minHeight += child->GetMinHeight( );
                }
            }

            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );

        }

        SetMinWidth( minWidth );
        SetMinHeight( minHeight );

        GetErrorArray( )->Empty( );

        m_frame.WriteLayout( "Page::UpdateMinimumSize >" );

        return ValidateNode( );
    }

    NodeStatus Page::ValidateNode( )
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
                std::cout << "Terminal leaf node must define the height.\n";
                status = AT_FATAL;
            }
            if ( GetWidth( ) <= 0.0 )
            { 
                wxString str;
                str = wxString::Format( "Terminal leaf node must define the width. width:>>%7.2f<< \n", GetWidth( ) );
                GetErrorArray( )->Add( str );
                std::cout << "Terminal leaf node must define the width.\n";
                status = AT_FATAL;
            }
        }
        if ( GetWidth( ) < GetMinWidth( ) )
        { 
            wxString str;
            str = wxString::Format( "Children too big for page. width:%7.2f  min width:%7.2f\n", GetWidth( ), GetMinWidth( ) );
            GetErrorArray( )->Add( str );
            ReportLayoutError( "UpdateMinimumSize", "Children too big for page", true );
        }
        //            if ( m_pageFrame.GetHeight( ) < minHeight )
        if ( GetHeight( ) < GetMinHeight( ) )
        { 
            wxString str;
            str = wxString::Format( "Children too big for page. height:%7.2f  min height:%7.2f\n", GetHeight( ), GetMinHeight( ) );
            GetErrorArray( )->Add( str );
            ReportLayoutError( "UpdateMinimumSize", "Children too big for page", true );
        }
        return status;
    }
    void Page::UpdateSizes( )
    { 
        //        m_frame.WriteLayout( "Page::UpdateSizes <" );

                //figure out how many rows or cols there are to calculate the child spacing
        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );


        // Set the height and width of each child row or column
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
                Row* row = ( Row* )child;
                double leftPadding = 0;
                double rightPadding = 0;
                double topPadding = 0;
                double bottomPadding = 0;
                if ( 1 )//row->GetShowFrame( ) ) 
                { 
                    leftPadding = row->GetLeftContentPadding( );
                    rightPadding = row->GetRightContentPadding( );
                    topPadding = row->GetTopContentPadding( );
                    bottomPadding = row->GetBottomContentPadding( );
                }
                row->SetWidth( GetWidth( )
                    - leftPadding
                    - rightPadding -2*GetBorderSize( ) );
                row->SetHeight( row->GetMinHeight( ) + topPadding + bottomPadding );
                if ( row->GetShowTitle( ) )
                { 
                    row->SetHeight( row->GetHeight( ) + row->GetTitleHeight( ) );
                }

                break;
            }
            case AT_Col:
            { 
                Column* col = ( Column* )child;
                col->SetWidth( GetMinWidth( ) );
                if ( col->GetShowTitle( ) )
                { 
                    col->SetHeight( GetHeight( ) + GetTitleHeight( ) - 2*GetBorderSize( ) );
                }
                else
                { 
                    col->SetHeight( GetHeight( ) - 2*GetBorderSize( ) );
                }
                break;
            }
            }
            child->UpdateSizes( );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        m_frame.WriteLayout( "Page::UpdateSizes >" );
    }

    void Page::UpdatePositions( )
    { 
        //        m_frame.WriteLayout( "Page::UpdatePositions <" );

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        double titleHeight = GetTitleHeight( );

        // if there are cols then we are positioning them across the page
        double spacing = 0;
        if ( nbrCols > 0 )
        { 
            spacing = ( GetWidth( ) - GetMinWidth( ) ) / ( nbrCols + nbrStamps + 1 );
        }
        else // we are positioning them down the page
        { 
            double totalExtraSpace = GetHeight( ) - GetMinHeight( );
            if ( GetShowTitle( ) )
            { 
                totalExtraSpace -= GetTitleHeight( );
            }
            spacing = totalExtraSpace / ( nbrRows + nbrStamps + 1 );
        }

        double xPos = 0;
        double yPos = titleHeight;
        if ( nbrRows > 0 )
        { 
            yPos = spacing;
        }
        else
        { 
            xPos += spacing;
        }


        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            child->UpdatePositions( );

            //layout everything except the title
            if ( type != AT_Title )
            { 

                if ( nbrRows > 0 )
                { 
                    child->SetXPos( 0 );
                    child->SetYPos( yPos );
                    yPos = yPos + spacing + child->GetHeight( );
                }
                else if ( nbrCols > 0 || nbrStamps > 0 )
                { 
                    child->SetXPos( xPos );
                    child->SetYPos( 0 );
                    xPos = xPos + spacing + child->GetWidth( );
                }
            }
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
        m_frame.WriteLayout( "Page::UpdatePositions >" );
    }


    void Page::UpdateLayout( )
    {
        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
    }


    void Page::DrawPDF( wxPdfDocument* doc, double x, double y )
    { 

        wxString borderName = GetBorderFileName( );
        double xPos = GetLeftMargin( );
        double yPos = GetTopMargin( );


        DrawImagePDF( doc, borderName, xPos, yPos, 
            GetWidth( ), 
            GetHeight( ) );

        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;
        if ( 1 )//row->GetShowFrame( ) ) 
        { 
            leftPadding = GetLeftContentPadding( );
            rightPadding = GetRightContentPadding( );
            topPadding = GetTopContentPadding( );
            bottomPadding = GetBottomContentPadding( );
        }
        
        xPos = xPos + GetBorderSize( );
        yPos = yPos + GetBorderSize( );
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            child->DrawPDF( doc, xPos + leftPadding, yPos + topPadding );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }
    
    void Page::Draw( wxDC& dc, double x, double y )
    { 

        dc.SetPen( *wxBLACK_PEN );

        //        std::cout << "Page ";      
        SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetWidth( ), GetHeight( ) );

        wxString borderName = GetBorderFileName( );
        double xPos = x + GetLeftMargin( );
        double yPos = y + GetTopMargin( );


        DrawImage( dc, borderName, xPos, yPos, 
            GetWidth( ), 
            GetHeight( ) );

        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;
        if ( 1 )//row->GetShowFrame( ) ) 
        { 
            leftPadding = GetLeftContentPadding( );
            rightPadding = GetRightContentPadding( );
            topPadding = GetTopContentPadding( );
            bottomPadding = GetBottomContentPadding( );
        }
        
        xPos = xPos + GetBorderSize( );
        yPos = yPos + GetBorderSize( );
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        { 
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
            child->Draw( dc, xPos + leftPadding, yPos + topPadding );
            childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    void Page::Save( wxXmlNode* xmlNode )
    { 
        SetAttribute( xmlNode, AT_Name );
    }

    void Page::ReportLayout( )
    { 
        std::cout << "Layout for Page " << "\nPage ";
        //ReportLayout( );
        std::cout << "\nBase ";
        ReportLayoutFrame( );

        wxString str = wxString::Format( "Border Size:%7.2f\n ", m_borderSize );
        std::cout << str;
        str = wxString::Format( "Top Margin:%7.2f  Bottom Margin:%7.2f\n  Right Margin:%7.2f  Left Margin:%7.2f\n", 
            m_topMargin, m_bottomMargin, m_rightMargin, m_leftMargin );
        std::cout << str;

    };

}