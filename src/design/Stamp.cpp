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
#include "art/NotFound.xpm"
#include "gui/DescriptionPanel.h"

#include "catalog/CatalogData.h"
#include "catalog/Entry.h"
#include "Defs.h"

namespace Design {


    const double BorderAllowance = .2;
    const double ImagePercentOfActual = .75;
    const char* StampErrorStrings[ AT_NbrStampErrorTypes ] = {
        "Invalid Image Link",
        "Invalid Height",
        "Invalid Width" };

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
        return true;
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
            width, 4,
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

        

        wxString stampID = GetAttrStr( Design::AT_ID );

        wxString link = GetGeneratorData( )->GetImageFilename( stampID );

        wxXmlNode* image = ODT::ContentDoc( )->WriteImage( frame,
            0, 0,
            width, height,
            ODT::FrameWithImage, ODT::TextAnchorParagraph, ODT::Frame20Content, link );

        //frame->SetContent( stampID );

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

    wxImage* Stamp::GetStampImage( )
    {

        wxFileName fn;
        wxString filename;
        wxImage* image;
        bool fileOK = false;
        wxString fileID = GetAttrStr( Design::AT_ID );
        if ( fileID.IsEmpty( ) )
        {
            fileOK = false;
        }
        else
        {
            filename = GetGeneratorData( )->GetImageFilename( fileID );
            fn.Assign( filename );
            wxString fullpath = fn.GetFullPath();
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

        dc.SetPen( *wxTRANSPARENT_PEN );
        m_frame.draw( dc, x, y );

        dc.SetPen( *wxBLACK_PEN );
        double xPos = x + GetXPos( );
        double yPos = y + GetYPos( );
        m_stampFrame.draw( dc, xPos, yPos );

        wxImage* image = GetStampImage( );
        if ( image && image->IsOk( ) )
        {

            //double xPos1 = xPos + m_stampFrame.GetXPos( ) + m_stampImageFrame.GetXPos( );
            //double yPos1 = yPos + m_stampFrame.GetYPos( ) + m_stampImageFrame.GetYPos( );
            double xPos1 = xPos + m_stampFrame.GetXPos( ) + m_stampImageFrame.GetXPos( );
            double yPos1 = yPos + m_stampFrame.GetYPos( ) ;
            double height = m_stampImageFrame.GetHeight( );
            double width = m_stampImageFrame.GetWidth( );
            if ( width <= 0.01 || height <=  0.01 )
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
            dc.SetPen( *wxGREEN_PEN );
            double xPos1 = xPos + m_stampFrame.GetXPos( );
            double yPos1 = yPos + m_stampFrame.GetYPos( );
            m_stampImageFrame.draw( dc, xPos1, yPos1 );
        }

       // DrawTitle(dc, xPos, yPos + m_stampFrame.GetHeight() );

        //if ( m_showID )
        //{
            double xPos2 = xPos + m_stampFrame.GetXPos( ) + m_stampImageFrame.GetXPos( );
            
            double yPos2 = yPos + m_stampFrame.GetYPos( ) + m_stampImageFrame.GetHeight( );
            DrawID( dc, xPos2, yPos2  );


        //}
    };


    void Stamp::DrawID( wxDC& dc, double x, double y  )
    {
        wxFont* font = new wxFont( *wxSMALL_FONT );
        font->SetPointSize( 8 );   
        dc.SetFont( *font );
        wxString id = GetAttrStr( AT_ID ); 
        id.Trim();
        id.Trim(false);
        int pos = id.First(' ');
        id = id.Mid(pos+1);
        m_idTextExtent = dc.GetTextExtent(id);
        x = x + ( m_stampImageFrame.GetWidth( ) - m_idTextExtent.GetX()/PpMM.x )/2;
        dc.DrawText ( id, x * PpMM.x, y * PpMM.y );
        delete font;
    }

    void Stamp::DrawTitle( wxDC& dc, double x, double y  )
    {
        wxFont* font = new wxFont( *wxNORMAL_FONT );
        dc.SetFont( *font );
        wxString id = GetAttrStr( AT_Name ); 
        id.Trim();
        id.Trim(false);
        int len = id.length();
        double width = m_stampFrame.GetWidth( ) * PpMM.x;
        if( len > 0 )
        {
            wxSize ext = dc.GetTextExtent(id); 
            if ( ext.x < width )
            {
                // if it fits print it
                x = x + ( m_stampFrame.GetWidth( ) - ext.GetX()/PpMM.x )/2;
                dc.DrawText ( id, x * PpMM.x, y * PpMM.y );
            }
            else 
            {
                // break the line up at word breaks; look for a space
                int start = 0;
                int pos = start;
                int origPos = start;
                
                wxString currStr = id;
                wxString workingStr = id;

                pos = workingStr.find(' ', pos); 

                while( len > 0 )
                {
                    if ( pos == wxNOT_FOUND )
                    {
                        // no space for break so print it.
                        x = x + ( m_stampFrame.GetWidth( ) - ext.GetX()/PpMM.x )/2;
                        dc.DrawText ( id, x * PpMM.x, y * PpMM.y );
                        len = 0;
                    }   
                    else
                    {   
                        // found a space so break into multiple lines
                        // Add words until length exceeded
                        workingStr = id.Mid(start,pos) ;
                        
                        wxSize ext = dc.GetTextExtent(workingStr); 
                        if ( ext.x/PpMM.x > width )
                        {
                            // it won't fit; decide what to do
                            if ( start == origPos )
                            {
                                // the distance to the first space was bigger than the size of the stamp so print it
                                // i.e., a really big word or little stamp
                                x = x + ( m_stampFrame.GetWidth( ) - ext.GetX()/PpMM.x )/2;
                                currStr = id.Mid(start,pos);
                                dc.DrawText ( currStr, x * PpMM.x, y * PpMM.y ); 
                                workingStr = id.Mid(pos+1); 
                                workingStr.Trim();
                                workingStr.Trim(false);
                                len = workingStr.length();
                                start = pos+1; 
                                origPos = pos+1;   
                                pos = id.find( ' ', start);                                                     
                            }
                            else
                            {
                                // backup to previous try
                                workingStr = workingStr.Mid( start, origPos );
                                pos = origPos;
                                wxSize ext = dc.GetTextExtent(workingStr); 
                                x = x + ( m_stampFrame.GetWidth( ) - ext.GetX()/PpMM.x )/2;
                                currStr = id.Mid(start,pos);
                                dc.DrawText ( currStr, x * PpMM.x, y * PpMM.y ); 
                                workingStr = id.Mid(pos+1); 
                                workingStr.Trim();
                                workingStr.Trim(false);
                                len = workingStr.length();
                                start = pos+1; 
                                origPos = pos+1;   
                                pos = id.find( ' ', start);  

                            }
                        }
                        else
                        {
                            // the word will fit; can another word fit?
                            origPos = pos;
                            pos = id.find( ' ', pos+1 );
                            if( pos == wxNOT_FOUND)
                            {
                                // no space for break so print it.
                                x = x + ( m_stampFrame.GetWidth( ) - ext.GetX()/PpMM.x )/2;
                                dc.DrawText ( workingStr, x * PpMM.x, y * PpMM.y );
                                workingStr.Empty(); 
                                len = 0;
                            }             
                        }   
                    }
                }          
            }
        }
        delete font;
    }
    // wxClientDC dc( this );
    // DoPrepareDC( dc );
    // wxSize size = dc.GetTextExtent( text );
    // wxRealPoint titleSize;
    // titleSize.x = size.x/Design::PpMM.x;
    // titleSize.y = size.y/Design::PpMM.y;
    // return titleSize;
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