/**
 * @file Column.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "album/Column.h"
#include "album/Row.h"
#include "album/Stamp.h"
#include "album/Title.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"

namespace Layout {

    void Column::UpdateMinimumSize( )
    {


        Title* title = GetTitle( );
        if ( title )
        {
            title->UpdateMinimumSize( );
        }

        SetMinWidth( 0.0 );
        SetMinHeight( 0.0 );

        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            child->UpdateMinimumSize( );

            if ( child->GetWidth( ) > m_minWidth )
            {
                m_minWidth = child->GetWidth( );
            }
            m_minHeight += child->GetHeight( );
        }

    }


    void Column::UpdateSizes( )
    {

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        Title* title = GetTitle( );
        double titleHeight = GetTitleHeight( );
        if ( title )
        {
            title->SetWidth( GetWidth( ) );
            title->UpdatePositions( );
        }


        // Set the height and width of each child  column
        // Stamps have fixed height and width
        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );
            AlbumNodeType childType = ( AlbumNodeType )child->GetNodeType( );
            if ( childType == AT_Row )
            {

                child->SetWidth( m_minWidth );
                child->SetHeight( m_minHeight - titleHeight );
            }
            child->UpdateSizes( );
        }
    }



    // calculate the column layout based on child parameters
    void Column::UpdatePositions( )
    {
        // go to the bottom of each child container object ( row, column, page) 
        // and begin filling in position relative to the parent

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        // inital x/y pos within the row

        double titleHeight = GetTitleHeight( );


        // this is a col so we are positioning children down the page
        double spacing = ( GetHeight( ) - m_minHeight ) / ( nbrRows + nbrStamps + 1 );

        double xPos = 0;
        double yPos = titleHeight + spacing;

        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            child->UpdatePositions( );

            AlbumNodeType childType = (AlbumNodeType)child->GetNodeType( );
            switch ( childType )
            {
            case AT_Row:
            {
                Row* row = ( Row* )child;
                row->SetXPos( xPos );
                row->SetYPos( yPos );
                //calc position of next row
                yPos += GetHeight( ) + spacing;
            }
            case AT_Stamp:
            {

                Stamp* stamp = ( Stamp* )child;

                // each stamp is positioned in the cell

                double xBorder = ( m_width - stamp->GetWidth( ) ) / 2;
                stamp->SetXPos( xPos + xBorder );
                stamp->SetYPos( yPos );
                // get xpos of next cell
                yPos += stamp->GetHeight( ) + spacing;
            }
            }
        }
    }

    // build the frame container for the column
    wxXmlNode* Column::Write( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Column", "Inserting a Column." );

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


        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );

            AlbumNodeType childType = (AlbumNodeType)child->GetNodeType( );
            switch ( childType )
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
                Stamp* stamp = ( Stamp* )child;
                stamp->Write( frame );
                }
            }
        }
        return frame;
    }

    AlbumNodeStatus Column::ValidateNode()
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