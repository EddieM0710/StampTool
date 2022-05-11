/**
 * @file Page.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
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
#include "odt/Document.h"
#include "gui/DesignTreeCtrl.h"
namespace Design {


    bool Page::UpdateMinimumSize( )
    {
        //double xPosUseableFrame = m_leftMargin;
        //double yPosUseableFrame = m_topMargin;
        double pageFrameWidth = GetWidth( ) - m_leftMargin - m_rightMargin - .4;
        double pageFrameHeight = GetHeight( ) - m_topMargin - m_bottomMargin - .4;
        SetWidth( pageFrameWidth  );
        SetHeight( pageFrameHeight  );

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );
        // count the number of rows/cols planned

        double minWidth = 0.0;
        double minHeight = 0.0;

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );

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

            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);


        }

        SetMinWidth( minWidth );
        SetMinHeight( minHeight );

        if ( pageFrameWidth < minWidth )
        {
            ReportLayoutError( "UpdateMinimumSize", "Children too big for row", true );
        }
        if ( pageFrameHeight < minHeight )
        {
            ReportLayoutError( "UpdateMinimumSize", "Children too big for row", true );
        }
WriteFrame("Page::UpdateMinimumSize",  GetObjectName(), "", &m_frame );

    }


    void Page::UpdateSizes( )
    {

        //figure out how many rows or cols there are to calculate the child spacing
        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );


        // Set the height and width of each child row or column
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );

            switch ( type )
            {
                case AT_Row:
                {
                    Row* row = ( Row* )child;
                    row->SetWidth( GetWidth( ) );
                    row->SetHeight( row->GetMinHeight( ) );
                    if ( row->ShowTitle( ) )
                    {
                        row->SetHeight( row->GetMinHeight( ) + GetTitleHeight() );
                    }
                    else
                    {
                        row->SetHeight( row->GetMinHeight( ) ) ;
                    }
                    break;
                }
                case AT_Col:
                {
                    Column* col = ( Column* )child;
                    col->SetWidth( GetMinWidth( ) );
                    if ( col->ShowTitle( ) )
                    {
                        col->SetHeight( GetHeight( ) + GetTitleHeight() );
                    }
                    else
                    {
                        col->SetHeight( GetHeight( ) );
                    }
                    break;
                }
            }
            child->UpdateSizes( );
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);
        }
WriteFrame("Page::UpdateSizes",  GetObjectName(), "", &m_frame );

   }
    void Page::UpdatePositions( )
    {
        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        double titleHeight = GetTitleHeight( );

        // if there are cols then we are positioning them across the page
        double spacing = 0;
        if ( nbrCols > 0 )
        {
            spacing = ( GetWidth( ) - GetMinWidth() ) / ( nbrCols + nbrStamps + 1 );
        }
        else // we are positioning them down the page
        {
            double totalExtraSpace =  GetHeight( ) - GetMinHeight() ;
            if ( ShowTitle())
            {
                totalExtraSpace -= GetTitleHeight();
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
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );
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
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);
        }
WriteFrame("Page::UpdatePositions",  GetObjectName(), "", &m_frame );

    }
    wxXmlNode* Page::Write( wxXmlNode* parent )
    {
        // Add the Page frame
        // set the frame for the page parameters
        Utils::AddComment( parent, "Page", "Inserting a new Page." );

        wxXmlNode* contentElement = ODT::ContentDoc( )->WriteFrame( parent,
            GetXPos( ) + m_borderSize,
            GetYPos( ) + m_borderSize,
            GetWidth( ),
            GetHeight( ),
            ODT::FrameNoBorder,
            ODT::TextAnchorParagraph );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );
            child->Write( parent );
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);
        }

        return contentElement;
    }

    NodeStatus Page::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        if ( !HasChildren( ) )
        {
            if ( GetHeight( ) <= 0.0 )
            {
                std::cout << "Terminal leaf node must define the height.\n";
                status = AT_FATAL;
            }
            if ( GetWidth( ) <= 0.0 )
            {
                std::cout << "Terminal leaf node must define the width.\n";
                status = AT_FATAL;
            }
        }
        m_nodeValid = status;
        return status;
    }

    void Page::draw( wxDC &dc, double x, double y )
    {

        std::cout << "Page::draw x:" << x << " y:" << y <<"\n" ;

        dc.SetPen(*wxBLACK_PEN);

        m_frame.drawBorder( dc, x+GetAttrDbl( AT_LeftMargin ), y+GetAttrDbl( AT_TopMargin ) );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
        while ( childID.IsOk() )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );
            child->draw( dc, x+GetXPos()+.2, y+GetYPos()+.2 );
            childID = GetDesignTreeCtrl()->GetNextChild(parentID, cookie);
        }
    }

    void Page::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode,  AT_Name ) ;
    }

}