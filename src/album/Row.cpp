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

        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            LayoutNode* childObject = ( LayoutNode* )ChildItem( i );

            childObject->UpdateMinimumSize( );
            if ( childObject->GetMinHeight( ) > m_minHeight )
            {
                m_minHeight = childObject->GetMinHeight( );
            }
            m_minWidth += childObject->GetMinWidth( );
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
            title->UpdatePositions( );
        }

        // Set the height and width of each child  column
        // Stamps have fixed height and width
        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            LayoutNode* item = ( LayoutNode* )ChildItem( i );
            wxString childType = item->GetObjectName( );
            if ( !childType.Cmp( "Column" ) )
            {
                item->SetWidth( m_minWidth );
                item->SetHeight( m_minHeight + titleHeight );
            }
            item->UpdateSizes( );
        }

    }

    // calculate the row layout based on child parameters
    bool Row::UpdatePositions( )
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

        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            LayoutNode* item = ( LayoutNode* )ChildItem( i );

            item->UpdatePositions( );

            wxString childType = item->GetObjectName( );

            if ( !childType.Cmp( "Column" ) )
            {
                Column* col = ( Column* )ChildItem( i );
                col->SetXPos( xPos );
                col->SetYPos( yPos );
                xPos += col->GetWidth( ) + spacing;
            }
            else if ( !childType.Cmp( "Stamp" ) )
            {

                Stamp* stamp = ( Stamp* )item;

                // each stamp is positioned in the cell

                double yBorder = ( m_height - stamp->GetHeight( ) ) / 2;
                stamp->SetXPos( xPos );
                stamp->SetYPos( yPos + yBorder );
                // get xpos of next cell
                xPos += stamp->GetWidth( ) + spacing;
            }
        }

        return true;
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

        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {

            wxString childType = ChildItem( i )->GetObjectName( );
            if ( !childType.Cmp( "Row" ) )
            {
                // set the layout parameters into the child
                Row* child = ( Row* )ChildItem( i );
                child->Write( frame );
            }
            else if ( !childType.Cmp( "Column" ) )
            {
                // set the layout parameters into the child
                Column* child = ( Column* )ChildItem( i );
                child->Write( frame );
            }
            else if ( !childType.Cmp( "Stamp" ) )
            {
                // set the layout parameters into the child
                Stamp* child = ( Stamp* )ChildItem( i );
                child->Write( frame );
            }
        }
        return frame;
    }
}