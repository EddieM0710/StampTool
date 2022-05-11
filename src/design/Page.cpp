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
        double pageFrameWidth = GetWidth( ) - m_leftMargin - m_rightMargin - .2;
        double pageFrameHeight = GetHeight( ) - m_topMargin - m_bottomMargin - .2;
        SetWidth( pageFrameWidth );
        SetHeight( pageFrameHeight );

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );
        // count the number of rows/cols planned



        double minWidth = 0.0;
        double minHeight = 0.0;

        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );

            //layout everything except the title
            if ( child->GetNodeType( ) != AT_Title )
            {
                child->UpdateMinimumSize( );

                if ( nbrCols > 0 )
                {
                    if ( child->GetMinHeight( ) > minHeight )
                    {
                        minHeight = child->GetMinHeight( );
                    }
                    minWidth += child->GetMinWidth( );
                }
                else
                {
                    if ( child->GetMinWidth( ) > minWidth )
                    {
                        minWidth = child->GetMinWidth( );
                    }
                    minHeight += child->GetMinHeight( );
                }
            }
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

    }


    void Page::UpdateSizes( )
    {

        //figure out how many rows or cols ther are to calculate the child spacing
        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );


        // Set the height and width of each child row or column
        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* node = ( LayoutBase* )( *it );

            AlbumAttrType childType = ( AlbumAttrType )node->GetNodeType( );
            switch ( childType )
            {
                case AT_Row:
                {
                    Row* row = ( Row* )node;
                    row->SetWidth( GetWidth( ) );
                    row->SetHeight( GetMinHeight( ) );
                    if ( row->ShowTitle( ) )
                    {
                        row->SetHeight( GetMinHeight( ) + GetTitleHeight() );
                    }
                    else
                    {
                        row->SetHeight( GetMinHeight( ) ) ;
                    }
                    break;
                }
                case AT_Col:
                {
                    Column* col = ( Column* )node;
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
            node->UpdateSizes( );
        }
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
            //        yPos = spacing;
        }
        else
        {
            xPos += spacing;
        }


        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* node = ( LayoutBase* )( *it );
            node->UpdatePositions( );

            //layout everything except the title
            if ( node->GetNodeType( ) != AT_Title )
            {

                if ( nbrRows > 0 )
                {
                    node->SetXPos( 0 );
                    node->SetYPos( yPos );
                    yPos = yPos + spacing + node->GetHeight( );
                }
                else if ( nbrCols > 0 || nbrStamps > 0 )
                {
                    node->SetXPos( xPos );
                    node->SetYPos( 0 );
                    xPos = xPos + spacing + node->GetWidth( );
                }
            }
        }
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

        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* node = ( LayoutBase* )( *it );
            node->Write( parent );
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

    void Page::draw( wxPaintDC &dc, int x, int y )
    {
        m_frame.draw( dc, x, y );

        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            child->draw( dc, x+GetXPos(), y+GetYPos() );
        }
    }
}