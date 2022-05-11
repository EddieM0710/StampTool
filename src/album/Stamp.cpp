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

#include "album/Stamp.h"
#include "StampData.h"
#include "odt/Document.h"

namespace Layout {


    const double BorderAllowance = .2;


    void Stamp::UpdateMinimumSize( )
    {
        // get this stamps id from the layout tree
        wxString stampID = GetAttrVal( "ID" );
        if ( stampID.Length( ) <= 0 )
        {
            // Debug Message
            // Stamp must have an "ID"
            return;
        }

        m_imageLink = GetAttrVal( "Link" );
        if ( m_imageLink.Length( ) <= 0 )
        {
            // Debug Message
            // Stamp must have a "Link" to an image
            return;
        }

        // find the index into the StampData
        int stampIndex = GetStampDataBase( )->FindItem( stampID, S_ID_Nbr );

        if ( stampIndex < 0 )
        {
            wxString str;
            str << "Stamp ID:" << stampID << "  Can't Find Stamp";
            ReportLayoutError( "UpdateMinimumSize", str );
        }
        // populate what we should know now
        m_name = GetStampDataBase( )->GetValue( S_Name, stampIndex );

        // my odt file was in inches when I started with it so i'm just converting the 
        // height and width here for ease.  I probably need to convert everything to metric.
        GetStampDataBase( )->GetValueDouble( S_Width, stampIndex, &m_widthStampImage );
        // convert to inches
        m_widthStampImage = m_widthStampImage * 0.03937;

        GetStampDataBase( )->GetValueDouble( S_Height, stampIndex, &m_heightStampImage );

        // convert to inches
        m_heightStampImage = m_heightStampImage * 0.03937;

        SetWidth( m_widthStampImage * ( 1.0 + BorderAllowance ) );
        SetHeight( m_heightStampImage * ( 1.0 + BorderAllowance ) + .4 );
        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );

        //   m_imageLink = GetStampDataBase()->GetValue( S_Image, stampIndex);

        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            LayoutNode* childObject = ( LayoutNode* )ChildItem( i );

            childObject->UpdateMinimumSize( );
        }
    }

    void Stamp::UpdateSizes( )
    {

    }

    bool Stamp::UpdatePositions( )
    {
        //No layout necessary for Stamps; it's all performed in the Write.
        // // go to the bottom of each child container object ( row, column, page)
        // // and begin filling in position relative to the parent
        // for ( int i = 0; i < ObjectArrayCount(); i++ )
        // {
        //     LayoutNode* childItem = (LayoutNode*)ChildItem( i );
        //     if ( !childItem-> UpdatePositions() )
        //     {
        //         return false;
        //     }
        // }

        // A stamp shouldn't have any children  but check it.
        if ( ObjectArrayCount( ) > 0 )
        {
            ReportError( "Stamp:: UpdatePositions()", "Stamps don't have a child.", true );
        }
        return true;
    }

    // build the frame container for the stamp
    wxXmlNode* Stamp::Write( wxXmlNode* parent )
    {
        AddComment( parent, "Stamp", "Inserting a Stamp." );
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
        AddComment( parent, "Stamp", "Inserting ouside Frame of Stamp." );
        // the outside object width and height is 10% larger than the stamp
        // height has an extra .25in for the caption
        double xPos = GetXPos( );
        double yPos = GetYPos( );
        double width = GetWidth( );
        double height = GetHeight( ); // allow for caption

        wxString drawStyleName = FrameNoBorder;
        wxString textAnchorType = TextAnchorParagraph; // "page", "paragraph"

        return ContentDoc( )->WriteFrame( parent,
            xPos, yPos,
            width, height,
            drawStyleName, textAnchorType ); // "page", "paragraph"
    }

    wxXmlNode* Stamp::StampFrameObject( wxXmlNode* parent )
    {
        AddComment( parent, "Stamp", "Inserting the Stamp Border." );
        double xPos = BorderAllowance / 2;
        double yPos = 0;
        double width = m_widthStampImage;
        double height = m_heightStampImage; // allow for caption

       // wxString drawStyleName = FrameWithBorder;
       // wxString textAnchorType = TextAnchorParagraph; // "page", "paragraph"

        wxXmlNode* stampFrame = ContentDoc( )->WriteFrameFixedSize( parent,
            xPos, yPos,
            width, height,
            FrameWithBorder, TextAnchorParagraph, Normal8PtTextStyle );

        wxXmlNode* idNode = ContentDoc( )->WriteTextBox( parent,
            0, height,
            width, .4,
            FrameCenteredFromTopNoBorder,  // fr1
            TextAnchorParagraph, // "page", "paragraph"
            Normal10PtTextStyle,
            "8", m_name );

        return stampFrame;

    }

    wxXmlNode* Stamp::StampImageObject( wxXmlNode* parent )
    {
        AddComment( parent, "Stamp", "Inserting the Stamp Image." );

        // <draw:frame draw:style-name="fr2" draw:name="Frame5" text:anchor-type="paragraph" svg:x="0.05in" svg:y="0.05in" svg:width="0.9252in" draw:z-index="4">
        //     <draw:text-box fo:min-height="1.2008in">

        //wxString drawStyleName = FrameCenteredAtTopNoBorder;
        //wxString textAnchorType = TextAnchorParagraph; // "page", "paragraph"

        // the stamp image is actually 10% less than the actual stamp.
        double width = m_widthStampImage * ( 1.0 - .25 );
        double height = m_heightStampImage * ( 1.0 - .25 );
        double xPos = ( m_widthStampImage - width ) / 2;
        double yPos = 0;

        wxXmlNode* frame = ContentDoc( )->WriteFrameFixedSize( parent,
            xPos, yPos,
            width, height,
            FrameCenteredAtTopNoBorder,
            TextAnchorParagraph );


        wxString link = m_imageLink;

        wxXmlNode* image = ContentDoc( )->WriteImage( frame,
            0, 0,
            width, height,
            FrameWithImage, TextAnchorParagraph, Frame20Content, m_imageLink );

        wxString stampID = GetAttrVal( "ID" );
        // stampFrame->SetContent( stampID );
        double idWidth = m_widthStampImage * .8;
        wxXmlNode* idNode = ContentDoc( )->WriteTextBox( parent,
            0, height,
            idWidth, .15,
            FrameCenteredFromTopNoBorder,  // fr1
            TextAnchorParagraph, // "page", "paragraph"
            Normal8PtTextStyle,
            "8", stampID );

        return image;
    }
}