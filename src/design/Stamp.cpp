/**
 * @file Stamp.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#include "design/Stamp.h"
#include "design/Title.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
#include "art/NotFound.xpm"
#include "gui/StampDescriptionPanel.h"

#include "catalog/CatalogVolumeData.h"
#include "catalog/Entry.h"
#include "Defs.h"
#include "gui/GuiUtils.h"

namespace Design {


    const double BorderAllowance = .2;
    const double ImagePercentOfActual = .75;
    const char* StampErrorStrings[ AT_NbrStampErrorTypes ] = {
        "Invalid Image Link",
        "Invalid Height",
        "Invalid Width" };

    void Stamp::CalcFrame( )
    {
        m_frame.WriteLayout( "Stamp::CalcFrame <");
        SetWidth( m_stampFrame.GetWidth( ) * ( 1.0 + BorderAllowance ) );
        wxFont titleFont( *wxNORMAL_FONT );
        titleFont.SetPointSize( 10 );;
        UpdateTitleSize( GetWidth( ), &titleFont );

        SetHeight( ( m_stampFrame.GetHeight( ) * ( 1.0 + BorderAllowance ) ) + GetTitleHeight( ) / 2 );
        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );
        m_stampFrame.SetXPos( ( GetWidth( ) - m_stampFrame.GetWidth( ) ) / 2 );
        m_stampFrame.SetYPos( 0.0 );
        m_stampImageFrame.SetWidth( m_stampFrame.GetWidth( ) * ImagePercentOfActual );
        m_stampImageFrame.SetHeight( m_stampFrame.GetHeight( ) * ImagePercentOfActual );
        m_stampImageFrame.SetXPos( ( m_stampFrame.GetWidth( ) - m_stampImageFrame.GetWidth( ) ) / 2 );
        m_stampImageFrame.SetYPos( ( m_stampFrame.GetHeight( ) - m_stampImageFrame.GetHeight( ) ) / 2 );
        m_frame.WriteLayout( "Stamp::CalcFrame >");
    }

    bool Stamp::UpdateMinimumSize( )
    {
        m_frame.WriteLayout( "Stamp::UpdateMinimumSize <");
        CalcFrame( );
        m_frame.WriteLayout( "Stamp::UpdateMinimumSize >");

        if ( ValidateNode( ) == AT_FATAL )
        {
            return false;
        }
        return true;
    }

    void Stamp::UpdateSizes( )
    {
                m_frame.WriteLayout( "Stamp::UpdateSizes <>");
    }

    void Stamp::UpdatePositions( )
    {
        m_frame.WriteLayout( "Stamp::UpdatePositions <>");
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
            width, m_titleSize.y,
            ODT::FrameCenteredFromTopNoBorder,  // fr1
            ODT::TextAnchorParagraph, // "page", "paragraph"
            ODT::Normal10PtTextStyle,
            "10", GetAttrStr( AT_Name ) );

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



        wxString stampID = GetAttrStr( Design::AT_CatNbr );

        wxString link = GetAttrStr( Design::AT_ImageName );

        wxXmlNode* image = ODT::ContentDoc( )->WriteImage( frame,
            0, 0,
            width, height,
            ODT::FrameWithImage, ODT::TextAnchorParagraph, ODT::Frame20Content, link );

        int pos = stampID.First( ' ' );
        stampID = stampID.Mid( pos + 1 );

        double idWidth = m_stampFrame.GetWidth( ) * .8;
        wxXmlNode* idNode = ODT::ContentDoc( )->WriteTextBox( parent,
            0, height,
            idWidth, 4,
            ODT::FrameCenteredFromTopNoBorder,  // fr1
            ODT::TextAnchorParagraph, // "page", "paragraph"
            ODT::Normal8PtTextStyle,
            "8", stampID );

        return image;
    }
    NodeStatus Stamp::ValidateNode( )
    {
        NodeStatus status = AT_OK;

        wxImage* image = GetStampImage( );
        if ( image && !image->IsOk( ) )
        {
            SetError( AT_InvalidImage, AT_WARING );
            status = AT_WARING;
        }
        if ( GetHeight( ) <= 0.01 )
        {
            SetError( AT_InvalidHeight, AT_FATAL );
            status = AT_FATAL;
        }
        if ( GetWidth( ) <= 0.01 )
        {
            SetError( AT_InvalidWidth, AT_FATAL );
            status = AT_FATAL;
        }
        m_nodeValid = status;
        return status;
    }

    void Stamp::ClearError( )
    {
        m_error[ AT_InvalidImage ] = AT_OK;
        m_error[ AT_InvalidHeight ] = AT_OK;
        m_error[ AT_InvalidWidth ] = AT_OK;
    };

    void Stamp::SetError( StampErrorType type, NodeStatus status )
    {
        m_error[ type ] = status;
    };

    NodeStatus Stamp::GetStatus( )
    {
        NodeStatus status = AT_OK;
        if ( m_error[ AT_InvalidImage ] > status )
        {
            status = m_error[ AT_InvalidImage ];
            if ( status == AT_FATAL )
                return status;
        }
        if ( m_error[ AT_InvalidHeight ] > status )
        {
            status = m_error[ AT_InvalidHeight ];
            if ( status == AT_FATAL )
                return status;
        }
        if ( m_error[ AT_InvalidWidth ] > status )
        {
            status = m_error[ AT_InvalidWidth ];
            if ( status == AT_FATAL )
                return status;
        }
    };

    void Stamp::SetStampHeight( double val )
    {
        m_stampFrame.SetHeight( val );
        wxString str = wxString::Format( "%d", val );
        SetAttrStr( Design::AT_Height, str );
        //        CalcFrame( );
    };

    void Stamp::SetStampHeight( wxString str )
    {
        SetAttrStr( Design::AT_Height, str );
        double val;
        bool ok = str.ToDouble( &val );
        m_stampFrame.SetHeight( val );
        //        CalcFrame( );
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
        ;
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

    wxImage* Stamp::GetStampImage( )
    {
 
        wxFileName fn;
        wxString filename;
        wxImage* image;
        bool fileOK = false;
        wxString fileID = GetAttrStr( Design::AT_CatNbr );
        if ( fileID.IsEmpty( ) )
        {
            fileOK = false;
        }
        else
        {
            wxString imageName = GetAttrStr( AT_ImageName );  
            filename = imageName;//GetGeneratorData( )->GetImageFilename( fileID );
            fn.Assign( filename );
            wxString fullpath = fn.GetFullPath( );
            wxFileName fn3 = fn;
            fn3.MakeAbsolute();
            wxString str = fn3.GetFullPath();
            if ( fn.FileExists( ) )
            {
                if ( image->CanRead( filename ) )
                {
                    fileOK = true;
                }
            }
        }
        if ( fileOK )
        {
            image = new wxImage( filename );
        }
        else
        {
            image = new wxImage( NotFound );
        }

        return image;
    }

    void Stamp::draw( wxDC& dc, double x, double y )
    {
        //Draw the outer frame transparent
        //dc.SetPen( *wxRedPen );
        //m_frame.draw( dc, x, y );

        dc.SetPen( *wxBLACK_PEN );

        //drar the Stamp frame
        double xPos = x + GetXPos( );
        double yPos = y + GetYPos( );

        m_stampFrame.draw( dc, xPos, yPos );

        wxImage* image = GetStampImage( );
        if ( image && image->IsOk( ) )
        {
            //Draw the stamp image

            double xPos1 = xPos + m_stampFrame.GetXPos( ) + m_stampImageFrame.GetXPos( );
            double yPos1 = yPos + m_stampFrame.GetYPos( );
            double height = m_stampImageFrame.GetHeight( );
            double width = m_stampImageFrame.GetWidth( );
            if ( width <= 0.01 || height <= 0.01 )
            {
                height = 10;
                width = 10;
            }

            image->Rescale( width * PpMM.x, height * PpMM.y );
            wxBitmap bitmap = *image;

            dc.DrawBitmap( bitmap, xPos1 * PpMM.x, yPos1 * PpMM.y, true );
            if ( image )
            {
                delete image;
            }
        }
        else
        {
            // draw missing image frame transparent
            dc.SetPen( *wxGREEN_PEN );
            double xPos1 = xPos + m_stampFrame.GetXPos( );
            double yPos1 = yPos + m_stampFrame.GetYPos( );
            m_stampImageFrame.draw( dc, xPos1, yPos1 );
        }

        RealPoint pos( xPos, ( yPos + m_stampFrame.GetHeight( ) ) );
        RealSize size( GetWidth( ), GetHeight()- m_stampFrame.GetHeight() );

        DrawTitle( dc, m_title, pos, size );

        if ( m_showCatNbr )
        {
        double xPos2 = xPos + m_stampFrame.GetXPos( ) + m_stampImageFrame.GetXPos( );

        double yPos2 = yPos + m_stampFrame.GetYPos( ) + m_stampImageFrame.GetHeight( );
        DrawID( dc, xPos2, yPos2 );

        }
    }


    void Stamp::DrawID( wxDC& dc, double x, double y )
    {
        wxFont currFont = dc.GetFont( );
        wxFont* font = new wxFont( *wxNORMAL_FONT );
        font->SetPointSize( 8 );
        dc.SetFont( *font );
        wxString id = GetAttrStr( AT_CatNbr );
        id.Trim( );
        id.Trim( false );
        int pos = id.First( ' ' );
        id = id.Mid( pos + 1 );
        wxSize ext = dc.GetTextExtent( id );
        wxSize  m_idTextExtent(ext.x/Design::PpMM.x, ext.y/Design::PpMM.y );

        x = x + ( m_stampImageFrame.GetWidth( ) - m_idTextExtent.x ) / 2;

        dc.DrawText( id, x*PpMM.x, y*PpMM.y );
        dc.SetFont( currFont );

        delete font;
    }


    void Stamp::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_CatNbr );
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_Width );
        SetAttribute( xmlNode, AT_Height );
        SetAttribute( xmlNode, AT_Link );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowCatNbr );
        SetAttribute( xmlNode, AT_ImageName );
    }

}