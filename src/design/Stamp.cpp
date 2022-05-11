/**
 * @file Stamp.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "design/Stamp.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"

#include "catalog/CatalogData.h"
#include "catalog/Stamp.h"

namespace Design {


    const double BorderAllowance = .2;
    const double ImagePercentOfActual = .75;


    bool Stamp::UpdateMinimumSize( )
    {
        if ( ValidateNode() == AT_FATAL )
        {
            return false;
        }

        SetWidth( m_stampFrame.GetWidth() * ( 1.0 + BorderAllowance ) );
        SetHeight( m_stampFrame.GetHeight() * ( 1.0 + BorderAllowance ) + GetTitleHeight() );
        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );
        m_stampFrame.SetXPos( ( GetWidth() - m_stampFrame.GetWidth() ) / 2 ); 
        m_stampFrame.SetYPos( 0.0 ); 
        m_stampImageFrame.SetWidth( m_stampFrame.GetWidth() * ImagePercentOfActual );
        m_stampImageFrame.SetHeight( m_stampFrame.GetHeight() * ImagePercentOfActual );
        m_stampImageFrame.SetXPos( ( m_stampFrame.GetWidth() - m_stampImageFrame.GetWidth() ) / 2 );
        m_stampImageFrame.SetYPos( ( m_stampFrame.GetHeight() - m_stampImageFrame.GetHeight() ) / 2 );
     
        //   m_imageLink = GetStampDataBase()->GetValue( S_Image, stampIndex);

        for ( ChildList::iterator it = BeginChildList(); it != EndChildList(); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );

            child->UpdateMinimumSize( );
        }
    }

    void Stamp::UpdateSizes( )
    {

    }

    void Stamp::UpdatePositions( )
    {
        //No layout necessary for Stamps; it's all performed in the Write.
        // // go to the bottom of each child container object ( row, column, page)
        // // and begin filling in position relative to the parent
        // for ( int i = 0; i < ObjectArrayCount(); i++ )
        // {
        //     LayoutBase* childItem = (LayoutBase*)ChildItem( i );
        //     if ( !childItem-> UpdatePositions() )
        //     {
        //         return false;
        //     }
        // }

        // A stamp shouldn't have any children  but check it.
        if ( GetNbrChildren() > 0 )
        {
            ReportError( "Stamp:: UpdatePositions()", "Stamps don't have a child.", true );
        }
    }

    // build the frame container for the stamp
    wxXmlNode* Stamp::Write( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Stamp", "Inserting a Stamp." );
        // the Object is built up of 3 objects. The outer object is the frame container 
    // for the stamp frame and the title text. The text is the only thing visible. 
    // The next is embedded in it and is tthe visible frame for the stamp.
    // The 3rd one is embedded in the 2nd one and is the image of the object.
    //
    // I need to make the stamp image optional if the image is not available.
        wxXmlNode* stampObjChild = StampObject( parent );
        if ( stampObjChild )
        {
            wxXmlNode* stampFrameObj = StampFrameObject( stampObjChild );
            if ( stampFrameObj )
            {
                wxXmlNode* stampImageObj = StampImageObject( stampFrameObj );
                if ( stampImageObj )
                {
                    //    stampObjChild->SetContent( m_name );
                    //    return stampImageObj;
                }
            }
        }
        return ( wxXmlNode* )0;
    }


    wxXmlNode* Stamp::StampObject( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Stamp", "Inserting ouside Frame of Stamp." );
        // the outside object width and height is 10% larger than the stamp
        // height has an extra .25in for the caption
        double xPos = GetXPos( );
        double yPos = GetYPos( );
        double width = GetWidth();
        double height = GetHeight( ); // allow for caption

        wxString drawStyleName = ODT::FrameNoBorder;
        wxString textAnchorType = ODT::TextAnchorParagraph; // "page", "paragraph"

        return ODT::ContentDoc( )->WriteFrame( parent,
            xPos, yPos,
            width, height,
            drawStyleName, textAnchorType ); // "page", "paragraph"
    }

    wxXmlNode* Stamp::StampFrameObject( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Stamp", "Inserting the Stamp Border." );
        double xPos = m_stampFrame.GetXPos( );
        double yPos = m_stampFrame.GetYPos( );
        double width = m_stampFrame.GetWidth();
        double height = m_stampFrame.GetHeight( ); // allow for caption

       // wxString drawStyleName = FrameWithBorder;
       // wxString textAnchorType = TextAnchorParagraph; // "page", "paragraph"

        wxXmlNode* stampFrame = ODT::ContentDoc( )->WriteFrameFixedSize( parent,
            xPos, yPos,
            width, height,
            ODT::FrameWithBorder, ODT::TextAnchorParagraph, ODT::Normal8PtTextStyle );

        wxXmlNode* idNode = ODT::ContentDoc( )->WriteTextBox( parent,
            0, height,
            width, .4,
            ODT::FrameCenteredFromTopNoBorder,  // fr1
            ODT::TextAnchorParagraph, // "page", "paragraph"
            ODT::Normal10PtTextStyle,
            "8", m_name );

        return stampFrame;

    }

    wxXmlNode* Stamp::StampImageObject( wxXmlNode* parent )
    {
        Utils::AddComment( parent, "Stamp", "Inserting the Stamp Image." );

        // <draw:frame draw:style-name="fr2" draw:name="Frame5" text:anchor-type="paragraph" svg:x="0.05in" svg:y="0.05in" svg:width="0.9252in" draw:z-index="4">
        //     <draw:text-box fo:min-height="1.2008in">

        //wxString drawStyleName = FrameCenteredAtTopNoBorder;
        //wxString textAnchorType = TextAnchorParagraph; // "page", "paragraph"

        // the stamp image is actually 10% less than the actual stamp.
        double xPos = m_stampImageFrame.GetXPos( );
        double yPos = m_stampImageFrame.GetYPos( );
        double width = m_stampImageFrame.GetWidth();
        double height = m_stampImageFrame.GetHeight( ); // allow for caption

        wxXmlNode* frame = ODT::ContentDoc( )->WriteFrameFixedSize( parent,
            xPos, yPos,
            width, height,
            ODT::FrameCenteredAtTopNoBorder,
            ODT::TextAnchorParagraph );


        wxString link = m_imageLink;

        wxXmlNode* image = ODT::ContentDoc( )->WriteImage( frame,
            0, 0,
            width, height,
            ODT::FrameWithImage, ODT::TextAnchorParagraph, ODT::Frame20Content, m_imageLink );

        wxString stampID = Utils::GetAttrStr( parent, "ID" );
        // stampFrame->SetContent( stampID );
        double idWidth =  m_stampFrame.GetWidth() * .8;
        wxXmlNode* idNode = ODT::ContentDoc( )->WriteTextBox( parent,
            0, height,
            idWidth, .15,
            ODT::FrameCenteredFromTopNoBorder,  // fr1
            ODT::TextAnchorParagraph, // "page", "paragraph"
            ODT::Normal8PtTextStyle,
            "8", stampID );

        return image;
    }
    NodeStatus Stamp::ValidateNode()
    {
        NodeStatus status = AT_OK;
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
        m_nodeValid = status;
        return status;
    }

    void Stamp::draw( wxPaintDC &dc, int x, int y )
    {
        m_frame.draw( dc, x, y );
        m_stampFrame.draw( dc,  x+GetXPos(), y+GetYPos() );
        m_stampImageFrame.draw( dc,  x+GetXPos()+m_stampFrame.GetXPos(), y+GetYPos()+m_stampFrame.GetYPos() );

        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            child->draw( dc, x+GetXPos(), y+GetYPos() );
        }
    }

}