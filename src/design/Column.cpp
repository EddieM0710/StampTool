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

#include "design/Column.h"
#include "design/Row.h"
#include "design/Stamp.h"
#include "design/Title.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"

namespace Design {

    bool Column::UpdateMinimumSize( )
    {



        SetMinWidth( 0.0 );
        SetMinHeight( 0.0 );

        double minHeight = 0.0;

        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );

            child->UpdateMinimumSize( );

            if ( child->GetWidth( ) > GetMinWidth() )
            {
                SetMinWidth( child->GetWidth( ) );
            }
            minHeight += child->GetHeight( );
        }
        SetMinHeight( minHeight );
    }


    void Column::UpdateSizes( )
    {

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );



        // Set the height and width of each child  column
        // Stamps have fixed height and width
        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            AlbumBaseType childType = ( AlbumBaseType )child->GetNodeType( );
            if ( childType == AT_Row )
            {
                child->SetWidth( GetMinWidth( ) );
                double minHeight = GetMinHeight();
                if ( child->ShowTitle() )
                {
                    minHeight = GetTitleHeight();
                }
                child->SetHeight( minHeight );
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


        // this is a col so we are positioning children down the page
        double spacing = ( GetHeight( ) - GetMinHeight() ) / ( nbrRows + nbrStamps + 1 );

        double xPos = 0;
        double yPos = spacing;
        if ( ShowTitle() ) yPos += GetTitleHeight();

        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );

            child->UpdatePositions( );

            AlbumBaseType childType = (AlbumBaseType)child->GetNodeType( );
            switch ( childType )
            {
                case AT_Row:
                {
                    Row* row = ( Row* )child;
                    row->SetXPos( xPos );
                    row->SetYPos( yPos );
                    //calc position of next row
                    yPos += GetHeight( ) + spacing;
                    break;
                }
                case AT_Stamp:
                {

                    Stamp* stamp = ( Stamp* )child;

                    // each stamp is positioned in the cell

                    double xBorder = ( GetWidth() - stamp->GetWidth( ) ) / 2;
                    stamp->SetXPos( xPos + xBorder );
                    stamp->SetYPos( yPos );
                    // get xpos of next cell
                    yPos += stamp->GetHeight( ) + spacing;
                    break;
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


        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );

            AlbumBaseType childType = (AlbumBaseType)child->GetNodeType( );
            switch ( childType )
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
                    Stamp* stamp = ( Stamp* )child;
                    stamp->Write( frame );
                    break;
                }
            }
        }
        return frame;
    }

    NodeStatus Column::ValidateNode()
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

    void Column::draw( wxPaintDC &dc, int x, int y )
    {
        m_frame.draw( dc, x, y );

        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            child->draw( dc, x+GetXPos(), y+GetYPos() );
        }
    }

}