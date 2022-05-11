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


    void Stamp::UpdateMinimumSize( )
    {
        // get this stamps id from the layout tree
        wxString stampID =  GetAttrStr( AT_ID );
        if ( stampID.Length( ) <= 0 )
        {
            // Debug Message
            // Stamp must have an "ID"
            return;
        }

        m_imageLink =  GetAttrStr( AT_Link );
        if ( m_imageLink.Length( ) <= 0 )
        {
            // Debug Message
            // Stamp must have a "Link" to an image
            return;
        }
        Catalog::CatalogData *catalog = GetGeneratorData()->GetCatalogData( ) ;
        if ( !catalog )
        {
            ReportLayoutError( "UpdateMinimumSize",  "Catalog Data Missing." );
        }

        // find the index into the StampData
        wxXmlNode* stampNode =  catalog->FindNodeWithPropertyAndValue(  Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ], stampID );
         if ( !stampNode )
        {
            wxString str;
            str << "Stamp ID:" << stampID << "  Can't Find Stamp";
            ReportLayoutError( "UpdateMinimumSize", str );
        }

       Catalog::Stamp stamp(stampNode);
 
        // populate what we should know now
        m_name = stamp.GetName();

        // my odt file was in inches when I started with it so i'm just converting the 
        // height and width here for ease.  I probably need to convert everything to metric.

 
        stamp.GetWidth().ToDouble(&m_widthStampImage);
        // convert to inches
        m_widthStampImage = m_widthStampImage * 0.03937;

        stamp.GetHeight().ToDouble(&m_heightStampImage);
        // convert to inches
        m_heightStampImage = m_heightStampImage * 0.03937;

        SetWidth( m_widthStampImage * ( 1.0 + BorderAllowance ) );
        SetHeight( m_heightStampImage * ( 1.0 + BorderAllowance ) + .4 );
        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );

        //   m_imageLink = GetStampDataBase()->GetValue( S_Image, stampIndex);

        for ( AlbumBaseList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
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
        double width = GetWidth( );
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
        double xPos = BorderAllowance / 2;
        double yPos = 0;
        double width = m_widthStampImage;
        double height = m_heightStampImage; // allow for caption

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
        double width = m_widthStampImage * ( 1.0 - .25 );
        double height = m_heightStampImage * ( 1.0 - .25 );
        double xPos = ( m_widthStampImage - width ) / 2;
        double yPos = 0;

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
        double idWidth = m_widthStampImage * .8;
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

}