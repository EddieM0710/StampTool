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

#include "album/Page.h"
#include "album/Album.h"
#include "album/Title.h"
#include "album/Row.h"
#include "album/Column.h"
#include "album/Stamp.h"
#include "album/AlbumData.h"
#include "odt/Document.h"
#include "gui/AlbumTreeCtrl.h"
namespace Layout {


    void Page::UpdateMinimumSize( )
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


        Title* title = GetTitle( );
        double titleHeight = GetTitleHeight( );
        if ( title )
        {
            title->UpdateMinimumSize( );
            title->SetWidth( pageFrameWidth );
        }

        m_minWidth = 0.0;
        m_minHeight = 0.0;

        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            //layout everything except the title
            if ( child->GetNodeType( ) != AT_Title )
            {
                child->UpdateMinimumSize( );

                if ( nbrCols > 0 )
                {
                    if ( child->GetMinHeight( ) > m_minHeight )
                    {
                        m_minHeight = child->GetMinHeight( );
                    }
                    m_minWidth += child->GetMinWidth( );
                }
                else
                {
                    if ( child->GetMinWidth( ) > m_minWidth )
                    {
                        m_minWidth = child->GetMinWidth( );
                    }
                    m_minHeight += child->GetMinHeight( );
                }
            }
        }

        if ( pageFrameWidth < m_minWidth )
        {
            ReportLayoutError( "UpdateMinimumSize", "Children too big for row", true );
        }
        if ( pageFrameHeight < m_minHeight )
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

        // setup the titlenbrCols
        Title* title = GetTitle( );
        double titleHeight = GetTitleHeight( );
        if ( title )
        {
            title->UpdateSizes( );

            // the title can be as wide as this frame
            title->SetWidth( GetWidth( ) );
        }
        // Set the height and width of each child row or column
        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* node = ( LayoutNode* )( *it );

            AlbumAttrType childType = ( AlbumAttrType )node->GetNodeType( );
            switch ( childType )
            {
            case AT_Row:
            {
                Row* row = ( Row* )node;
                row->SetWidth( GetWidth( ) );
                row->SetHeight( m_minHeight + titleHeight );
            }
            case AT_Col:
            {
                Column* col = ( Column* )node;
                col->SetWidth( m_minWidth );
                col->SetHeight( GetHeight( ) - titleHeight );
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
            spacing = ( GetWidth( ) - m_minWidth ) / ( nbrCols + nbrStamps + 1 );
        }
        else // we are positioning them down the page
        {
            spacing = ( GetHeight( ) - titleHeight - m_minHeight ) / ( nbrRows + nbrStamps + 1 );
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


        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* node = ( LayoutNode* )( *it );
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

        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* node = ( LayoutNode* )( *it );
            node->Write( parent );
        }

        return contentElement;
    }
    
    AlbumNodeStatus Page::ValidateNode()
    {
        AlbumNodeStatus status = AT_OK;
        if ( !HasChildren() )
        {
            if ( GetHeight() <= 0.0)
            {
                std::cout << "Terminal leaf node must define the height.\n";
                status = AT_FATAL;
            }
            if ( GetWidth() <= 0.0)
            {
                std::cout << "Terminal leaf node must define the width.\n";
                status = AT_FATAL;
            }
        }

        return status;
    }
}