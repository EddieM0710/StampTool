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

#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "design/Title.h"
#include "odt/Document.h"

namespace Design {


    bool Row::UpdateMinimumSize( )
    {


        double minWidth = 0.0;
        double minHeight = 0.0;
        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            child->UpdateMinimumSize( );
            if ( child->GetMinHeight( ) > minHeight )
            {
                minHeight = child->GetMinHeight( );
            }
            minWidth += child->GetMinWidth( );
        }
        if ( ShowTitle() )
        {
          minHeight += GetTitleHeight();  
        }
        SetMinHeight( minHeight );
        SetMinWidth( minWidth );
    }

    void Row::UpdateSizes( )
    {

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        // ValidateChildType( nbrRows, nbrCols, nbrStamps );

        // Set the height and width of each child  column
        // Stamps have fixed height and width
        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            AlbumBaseType childType = (AlbumBaseType)child->GetNodeType( );
            if (childType == AT_Col)
            {
                child->SetWidth( GetMinWidth() );
                child->SetHeight( GetMinHeight() );
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


        // this is a row so we are positioning children across the page
        double spacing = ( GetWidth( ) - GetMinWidth() ) / ( nbrCols + nbrStamps + 1 );

        // inital x/y pos within the row
        double xPos = spacing;
        double yPos = GetTitleHeight();

        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );

            child->UpdatePositions( );

            AlbumBaseType childType = (AlbumBaseType)child->GetNodeType( );

            switch (childType)
            {
                case AT_Col:
                {
                    Column* col = ( Column* )child;
                    col->SetXPos( xPos );
                    col->SetYPos( yPos );
                    xPos += col->GetWidth( ) + spacing;
                    break;
                }
                case AT_Stamp:
                {

                    Stamp* stamp = ( Stamp* )child;

                    // each stamp is positioned in the cell

                    double yBorder = ( GetHeight( ) - stamp->GetHeight( ) ) / 2;
                    stamp->SetXPos( xPos );
                    stamp->SetYPos( yPos + yBorder );
                    // get xpos of next cell
                    xPos += stamp->GetWidth( ) + spacing;
                    break;
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

        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );

            AlbumBaseType childType = (AlbumBaseType)child->GetNodeType( );
            switch( childType)
            {
                case AT_Row:
                {
                    // set the layout parameters into the child
                    Row* row = ( Row* )child;
                    row->Write( frame );
                    break;
                }
                case AT_Col:
                {
                    // set the layout parameters into the child
                    Column* col = ( Column* )child;
                    col->Write( frame );
                    break;
                }
            case AT_Stamp:
                {
                    // set the layout parameters into the child
                    Stamp*  stamp = ( Stamp* )child;
                    stamp->Write( frame );
                    break;
                }
            }
        }
        return frame;
    }

    NodeStatus Row::ValidateNode()
    {
        NodeStatus status = AT_OK;
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
        m_nodeValid = status;
        return status;
    }

    void Row::draw( wxPaintDC &dc, int x, int y )
    {
        m_frame.draw( dc, x, y );

        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            child->draw( dc, x+GetXPos(), y+GetYPos() );
        }
    }

}