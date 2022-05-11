/**
 * @file Title.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "album/Title.h"
#include "odt/Document.h"

namespace Layout {

    void  Title::UpdateMinimumSize( )
    {
        double height = GetAttrValDbl( "height" );
        double width = 1.;
        SetHeight( height );
        SetMinHeight( height );
        // default width is completely arbitrary at this point
        SetWidth( width );
        SetMinWidth( width );

    }


    bool Title::UpdatePositions( )
    {
        SetXPos( 0 );
        SetYPos( 0 );

        return true;
    }

    void Title::UpdateSizes( )
    {

    }

    wxXmlNode* Title::Write( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Title", "Insert a title here." );

        wxXmlNode* contentElement = ODT::ContentDoc( )->WriteFrame( parent,
            GetXPos( ),
            GetYPos( ),
            GetWidth( ),
            GetHeight( ),
            ODT::FrameNoBorder,
            ODT::TextAnchorParagraph,
            ODT::Bold18PtTextStyle );
        contentElement->SetType( wxXML_TEXT_NODE );
        contentElement->SetContent( GetObjectText( ) );

        return contentElement;
    }
}