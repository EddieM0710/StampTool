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

void Column::UpdateMinimumSize()
{


    Title* title = GetTitle();
    if ( title )
    {
        title->UpdateMinimumSize();
    }

    SetMinWidth( 0.0 );
    SetMinHeight( 0.0 );

    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        LayoutNode* childObject = (LayoutNode*)ChildItem( i );

        childObject->UpdateMinimumSize();

        if ( childObject->GetWidth() > m_minWidth )
        {
            m_minWidth = childObject->GetWidth();
        }
        m_minHeight += childObject->GetHeight();
    }

}


void Column::UpdateSizes()
{

    int nbrRows = 0;
    int nbrCols = 0;
    int nbrStamps = 0;
    ValidateChildType( nbrRows, nbrCols, nbrStamps );

    Title* title =GetTitle();
    double titleHeight = GetTitleHeight();
    if ( title )
    {
        title->SetWidth(GetWidth());
        title-> UpdatePositions();
    }


    // Set the height and width of each child  column
    // Stamps have fixed height and width
    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        LayoutNode* item = (LayoutNode*)ChildItem( i );
        wxString childType = item->GetObjectName();
        if ( !childType.Cmp( "Row" ) )
        {
          
            item->SetWidth( m_minWidth );
            item->SetHeight( m_minHeight - titleHeight );
        }
        item->UpdateSizes();
    }
}



// calculate the column layout based on child parameters
bool Column:: UpdatePositions()
{
    // go to the bottom of each child container object ( row, column, page) 
    // and begin filling in position relative to the parent

    int nbrRows = 0;
    int nbrCols = 0;
    int nbrStamps = 0;
    ValidateChildType( nbrRows, nbrCols, nbrStamps );

    // inital x/y pos within the row

    double titleHeight = GetTitleHeight();


    // this is a col so we are positioning children down the page
    double spacing = (  GetHeight()  - m_minHeight ) / ( nbrRows + nbrStamps + 1 );

    double xPos = 0;
    double yPos = titleHeight + spacing;

    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        LayoutNode* item = (LayoutNode*)ChildItem( i );

        item->UpdatePositions();
   
        wxString childType = item->GetObjectName();
        if ( !childType.Cmp( "Row" ) )
        {
            Row* row = (Row*)ChildItem( i );
            row->SetXPos( xPos );
            row->SetYPos( yPos );
            //calc position of next row
            yPos +=  GetHeight() + spacing;
        }
        else if ( !childType.Cmp( "Stamp" ) )
        {
 
            Stamp* stamp = (Stamp*)item;

            // each stamp is positioned in the cell

            double xBorder = ( m_width - stamp->GetWidth() ) / 2;
            stamp->SetXPos( xPos + xBorder );
            stamp->SetYPos( yPos );
            // get xpos of next cell
            yPos +=  stamp->GetHeight() + spacing;
        }
    }

    return true;
}

// build the frame container for the column
wxXmlNode* Column::Write( wxXmlNode* parent )
{
    Utils::AddComment(  parent, "Column", "Inserting a Column.");

    double xPos = GetXPos();
    double yPos = GetYPos();
    double width = GetWidth();
    double height = GetHeight(); // allow for caption

    wxString drawStyleName = ODT::FrameNoBorder;
    wxString textAnchorType = ODT::TextAnchorParagraph; // "page", "paragraph"
    wxString textStyleName = ODT::NormalTextStyle;

    wxXmlNode* frame = ODT::ContentDoc()->WriteFrame( parent, xPos,
        yPos,
        width,
        height,
        drawStyleName,  // fr1
        textAnchorType ); // "page", "paragraph"


    for ( int i = 0; i < ObjectArrayCount(); i++ )
    {
        wxString childType = ChildItem( i )->GetObjectName();
        if ( !childType.Cmp( "Row" ) )
        {
            // set the layout parameters into the child
            Row* child = (Row*)ChildItem( i );
            child->Write( frame );
        }
        else if ( !childType.Cmp( "Column" ) )
        {
            // set the layout parameters into the child
            Column* child = (Column*)ChildItem( i );
            child->Write( frame );
        }
        else if ( !childType.Cmp( "Stamp" ) )
        {
            // set the layout parameters into the child
            Stamp* child = (Stamp*)ChildItem( i );
            child->Write( frame );
        }
    }
    return frame;
}
}