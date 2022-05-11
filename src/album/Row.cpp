/**
 * @file Row.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "album/Row.h"
#include "album/Column.h"
#include "album/Stamp.h"
#include "album/Title.h"
#include "odt/Document.h"

namespace Layout {


    void Row::UpdateMinimumSize( )
    {

        Title* title = GetTitle( );
        if ( title )
        {
            title->UpdateMinimumSize( );
        }

        m_minWidth = 0.0;
        m_minHeight = 0.0;
        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );
            child->UpdateMinimumSize( );
            if ( child->GetMinHeight( ) > m_minHeight )
            {
                m_minHeight = child->GetMinHeight( );
            }
            m_minWidth += child->GetMinWidth( );
        }
    }

    void Row::UpdateSizes( )
    {

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        // ValidateChildType( nbrRows, nbrCols, nbrStamps );

        Title* title = GetTitle( );
        double titleHeight = GetTitleHeight( );
        if ( title )
        {
            title->SetWidth( GetWidth( ) );
            title->UpdateSizes( );
        }

        // Set the height and width of each child  column
        // Stamps have fixed height and width
        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );
            AlbumNodeType childType = (AlbumNodeType)child->GetNodeType( );
            if (childType == AT_Col)
            {
                child->SetWidth( m_minWidth );
                child->SetHeight( m_minHeight + titleHeight );
            }
            child->UpdateSizes( );
        }

    }

    // calculate the row layout based on child parameters
    void Row::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page) 
        // and begin filling in position relative to the parent

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        double titleHeight = GetTitleHeight( );


        // this is a row so we are positioning children across the page
        double spacing = ( GetWidth( ) - m_minWidth ) / ( nbrCols + nbrStamps + 1 );

        // inital x/y pos within the row
        double xPos = spacing;
        double yPos = titleHeight;

        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            child->UpdatePositions( );

            AlbumNodeType childType = (AlbumNodeType)child->GetNodeType( );

            switch (childType)
            {
                case AT_Col:
                {
                    Column* col = ( Column* )child;
                    col->SetXPos( xPos );
                    col->SetYPos( yPos );
                    xPos += col->GetWidth( ) + spacing;
                }
                case AT_Stamp:
                {

                    Stamp* stamp = ( Stamp* )child;

                    // each stamp is positioned in the cell

                    double yBorder = ( m_height - stamp->GetHeight( ) ) / 2;
                    stamp->SetXPos( xPos );
                    stamp->SetYPos( yPos + yBorder );
                    // get xpos of next cell
                    xPos += stamp->GetWidth( ) + spacing;
                }
            }
        }

    }

    // build the frame container for the row
    wxXmlNode* Row::Write( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Row", "Inserting a Row." );
        double xPos = GetXPos( );
        double yPos = GetYPos( );
        double width = GetWidth( );
        double height = GetHeight( ); // allow for caption

        wxString drawStyleName = ODT::FrameNoBorder;
        wxString textAnchorType = ODT::TextAnchorParagraph; // "page", "paragraph"
        wxString textStyleName = ODT::NormalTextStyle;

        wxXmlNode* frame = ODT::ContentDoc( )->WriteFrame( parent, xPos,
            yPos,
            width,
            height,
            drawStyleName,  // fr1
            textAnchorType ); // "page", "paragraph"

        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            AlbumNodeType childType = (AlbumNodeType)child->GetNodeType( );
            switch( childType)
            {
                case AT_Row:
                {
                    // set the layout parameters into the child
                    Row* row = ( Row* )child;
                    row->Write( frame );
                }
                case AT_Col:
                {
                    // set the layout parameters into the child
                    Column* col = ( Column* )child;
                    col->Write( frame );
                }
            case AT_Stamp:
                {
                    // set the layout parameters into the child
                    Stamp*  stamp = ( Stamp* )child;
                    stamp->Write( frame );
                }
            }
        }
        return frame;
    }

    AlbumNodeStatus Row::ValidateNode()
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