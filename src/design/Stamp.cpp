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
#include "gui/DesignTreeCtrl.h"

#include "catalog/CatalogData.h"
#include "catalog/Stamp.h"

namespace Design {


    const double BorderAllowance = .2;
    const double ImagePercentOfActual = .75;

    void Stamp::CalcFrame( )
    {
        UpdateTitleSize( );
        SetWidth( m_stampFrame.GetWidth( ) * ( 1.0 + BorderAllowance ) );
        SetHeight( m_stampFrame.GetHeight( ) * ( 1.0 + BorderAllowance ) );//+ GetTitleHeight( ) );
        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );
        m_stampFrame.SetXPos( ( GetWidth( ) - m_stampFrame.GetWidth( ) ) / 2 );
        m_stampFrame.SetYPos( 0.0 );
        m_stampImageFrame.SetWidth( m_stampFrame.GetWidth( ) * ImagePercentOfActual );
        m_stampImageFrame.SetHeight( m_stampFrame.GetHeight( ) * ImagePercentOfActual );
        m_stampImageFrame.SetXPos( ( m_stampFrame.GetWidth( ) - m_stampImageFrame.GetWidth( ) ) / 2 );
        m_stampImageFrame.SetYPos( ( m_stampFrame.GetHeight( ) - m_stampImageFrame.GetHeight( ) ) / 2 );
    }

    bool Stamp::UpdateMinimumSize( )
    {
        CalcFrame( );
        if ( ValidateNode( ) == AT_FATAL )
        {
            return false;
        }
    }

    void Stamp::UpdateSizes( )
    {
    }

    void Stamp::UpdatePositions( )
    {

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
        double xPos = m_stampFrame.GetXPos( );
        double yPos = m_stampFrame.GetYPos( );
        double width = m_stampFrame.GetWidth( );
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
            "8", GetAttrStr( AT_Name ) );

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
        double width = m_stampImageFrame.GetWidth( );
        double height = m_stampImageFrame.GetHeight( ); // allow for caption

        wxXmlNode* frame = ODT::ContentDoc( )->WriteFrameFixedSize( parent,
            xPos, yPos,
            width, height,
            ODT::FrameCenteredAtTopNoBorder,
            ODT::TextAnchorParagraph );


        wxString link = GetAttrStr( AT_Link );

        wxXmlNode* image = ODT::ContentDoc( )->WriteImage( frame,
            0, 0,
            width, height,
            ODT::FrameWithImage, ODT::TextAnchorParagraph, ODT::Frame20Content, link );

        wxString stampID = Utils::GetAttrStr( parent, "ID" );
        // stampFrame->SetContent( stampID );
        double idWidth = m_stampFrame.GetWidth( ) * .8;
        wxXmlNode* idNode = ODT::ContentDoc( )->WriteTextBox( parent,
            0, height,
            idWidth, .15,
            ODT::FrameCenteredFromTopNoBorder,  // fr1
            ODT::TextAnchorParagraph, // "page", "paragraph"
            ODT::Normal8PtTextStyle,
            "8", stampID );

        return image;
    }
    NodeStatus Stamp::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        if ( GetHeight( ) <= 0.0 )
        {

            std::cout << "Terminal leaf node must define the height.\n";
            status = AT_FATAL;
        }
        if ( GetWidth( ) <= 0.0 )
        {

            std::cout << "Terminal leaf node must define the width.\n";
            status = AT_FATAL;
        }
        m_nodeValid = status;
        return status;
    }

    void Stamp::SetStampHeight( double val )
    {
        m_stampFrame.SetHeight( val );
        wxString str = wxString::Format( "%d", val );
        SetAttrStr( Design::AT_Height, str );
        CalcFrame( );
    };

    void Stamp::SetStampHeight( wxString str )
    {
        SetAttrStr( Design::AT_Height, str );
        double val;
        bool ok = str.ToDouble( &val );
        m_stampFrame.SetHeight( val );
        CalcFrame( );
    };

    double Stamp::GetStampHeight( )
    {
        return m_stampFrame.GetHeight( );
    };

    wxString Stamp::GetStampHeightStr( )
    {
        return GetAttrStr( Design::AT_Height );
    };

    void Stamp::SetStampWidth( double val )
    {
        m_stampFrame.SetWidth( val );
        wxString str = wxString::Format( "%d", val );
        SetAttrStr( Design::AT_Width, str );
        CalcFrame( );
    };

    void Stamp::SetStampWidth( wxString str )
    {
        SetAttrStr( Design::AT_Width, str );
        double val;
        bool ok = str.ToDouble( &val );
        m_stampFrame.SetWidth( val );
        CalcFrame( );
    };

    double Stamp::GetStampWidth( )
    {
        return m_stampFrame.GetWidth( );
    };
    wxString Stamp::GetStampWidthStr( )
    {
        return GetAttrStr( Design::AT_Width );
    };

    void Stamp::draw( wxDC& dc, double x, double y )
    {

        dc.SetPen( *wxRED_PEN );
        m_frame.draw( dc, x, y );

        dc.SetPen( *wxYELLOW_PEN );
        double xPos = x + GetXPos( );
        double yPos = y + GetYPos( );
        m_stampFrame.draw( dc, xPos, yPos );
        //@@@@@@

        wxString link = GetAttrStr( Design::AT_Link );

        wxFileName fn;
        fn.SetFullName( link );
        fn.SetPath( "/sandbox/Documents/Stamps/Art" );
        wxImage image = wxImage( fn.GetFullPath( ) );
        if ( image.IsOk( ) )
        {
    
            double xPos1 = xPos + m_stampFrame.GetXPos( )+m_stampImageFrame.GetXPos( );
            double yPos1 = yPos + m_stampFrame.GetYPos( )+m_stampImageFrame.GetYPos( );
      //  wxSize size( m_stampImageFrame.GetWidth( ), m_stampImageFrame.GetHeight( ) );
            image.Rescale( m_stampImageFrame.GetWidth( )* PpMM.x, m_stampImageFrame.GetHeight( )* PpMM.y );
            wxBitmap bitmap = image;
            //    const wxSize size = GetClientSize( );
            // double scale = 1.;
            // int width = bitmap.GetWidth( );
            // int height = bitmap.GetHeight( );

            // if ( m_stampImageFrame.GetWidth( ) * PpMM.x < width )
            // {
            //     scale = ( double )m_stampImageFrame.GetWidth( ) * PpMM.x / ( double )width;
            // }
            // if ( m_stampImageFrame.GetHeight( ) * PpMM.y < ( height * scale ) )
            // {
            //     scale = ( double )m_stampImageFrame.GetHeight( ) * PpMM.y / ( ( double )height * scale ) * scale;
            // }

            // dc.SetUserScale( scale, scale );
            dc.DrawBitmap( bitmap, xPos1* PpMM.x, yPos1* PpMM.y,
                // dc.DeviceToLogicalX((size.x - m_zoom*scale *
                // m_bitmap.GetWidth()) / 2), dc.DeviceToLogicalY((size.y -
                // m_zoom*scale * m_bitmap.GetHeight()) / 2),
                true /* use mask */
            );
        }
        else
        {
            dc.SetPen( *wxGREEN_PEN );
            double xPos1 = xPos + m_stampFrame.GetXPos( );
            double yPos1 = yPos + m_stampFrame.GetYPos( );
            m_stampImageFrame.draw( dc, xPos1, yPos1 );
        }


        //@@@@@@@

                // wxTreeItemIdValue cookie;
                // wxTreeItemId parentID = GetTreeItemId();
                // wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);
                // while ( childID.IsOk( ) )
                // {
                //     AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl( )->GetItemType( childID );
                //     LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl( )->GetItemNode( childID );
                //     child->draw( dc, x + GetXPos( ), y + GetYPos( ) );
                //     childID = GetDesignTreeCtrl( )->GetNextChild( parentID, cookie );
                // }

    };
    void Stamp::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_ID );
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_Width );
        SetAttribute( xmlNode, AT_Height );
        SetAttribute( xmlNode, AT_Link );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowId );
    }

}