/**
 * @file Stamp.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright ( c ) 2022
 * 
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#include "Defs.h"

#include "design/Stamp.h"
#include "design/Title.h"
#include "design/Album.h"

#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
#include "gui/StampDescriptionPanel.h"
#include "gui/GuiUtils.h"

#include "catalog/CatalogSectionData.h"
#include "catalog/Entry.h"
#include "art/NotFound.xpm"

namespace Design { 


    const double BorderAllowance = .2;
    const double ImagePercentOfActual = .75;
    const char* StampErrorStrings[ AT_NbrStampErrorTypes ] = { 
        "Invalid Image Link", 
        "Invalid Height", 
        "Invalid Width" };

    void Stamp::CalcFrame( )
    { 
//        m_frame.WriteLayout( "Stamp::CalcFrame <" );
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
//        m_frame.WriteLayout( "Stamp::CalcFrame >" );
    }

    bool Stamp::UpdateMinimumSize( )
    { 
 //       m_frame.WriteLayout( "Stamp::UpdateMinimumSize <" );
        CalcFrame( );
        m_frame.WriteLayout( "Stamp::UpdateMinimumSize >" );

        if ( ValidateNode( ) == AT_FATAL )
        { 
            return false;
        }
        return true;
    }

    void Stamp::UpdateSizes( )
    { 
        m_frame.WriteLayout( "Stamp::UpdateSizes <>" );
    }

    void Stamp::UpdatePositions( )
    { 
        m_frame.WriteLayout( "Stamp::UpdatePositions <>" );
    }

    NodeStatus Stamp::ValidateNode( )
    { 
        NodeStatus status = AT_OK;
        wxString str;
        wxImage* image = GetStampImage( );
        if ( image && !image->IsOk( ) )
        { 
            str = wxString::Format( "Invalid Stamp Image.\n" );
            GetErrorArray( )->Add( str );
            std::cout << str;
            SetError( AT_InvalidImage, AT_WARING );
            status = AT_WARING;
        }
        if ( GetHeight( ) <= 0.01 )
        { 
            str = wxString::Format( "Invalid Stamp Height.\n" );
            GetErrorArray( )->Add( str );
            std::cout << str;
            SetError( AT_InvalidHeight, AT_FATAL );
            status = AT_FATAL;
        }
        if ( GetWidth( ) <= 0.01 )
        { 
            str = wxString::Format( "Invalid Stamp Width.\n" );
            GetErrorArray( )->Add( str );
            std::cout << str;
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
        
        return status;

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

    wxString Stamp::GetStampImageFilename( )
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
            filename = imageName;//GetToolData( )->GetImageFilename( fileID );
            fn.Assign( filename );
            wxString fullpath = fn.GetFullPath( );
            wxFileName fn3 = fn;
            fn3.MakeAbsolute( );
            wxString str = fn3.GetFullPath( );
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
            return filename ;
        }
        else
        { 
            return "" ;
        }
    }
    wxImage* Stamp::GetStampImage( )
    { 
        wxString filename = GetStampImageFilename( );
        wxImage* image ;
        if (filename.IsEmpty())
        {
            image = new wxImage( NotFound );
        }
        else 
        {
            image = new wxImage( filename );
        }
        return image;
    }

    void Stamp::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
 

        //Draw the outer frame transparent
        m_frame.DrawPDF( doc, x, y );

        //Draw the Stamp frame
        double xInnerPos = x + GetXPos( );
        double yInnerPos = y + GetYPos( );

        m_stampFrame.DrawPDF( doc, xInnerPos, yInnerPos );
        
        double xImagePos = xInnerPos + m_stampFrame.GetXPos( ) + m_stampImageFrame.GetXPos( );
        double yImagePos = yInnerPos + m_stampFrame.GetYPos( );

        wxString filename = GetStampImageFilename( );

        if ( !filename.IsEmpty( ) )
        { 
            //Draw the stamp image

            double height = m_stampImageFrame.GetHeight( );
            double width = m_stampImageFrame.GetWidth( );
            if ( width <= 0.01 || height <= 0.01 )
            { 
                height = 10;
                width = 10;
            }

            DrawImagePDF( doc, filename, xImagePos,  yImagePos + 1, width, height );
        }
        else
        { 
            // Draw missing image frame transparent
            //m_stampImageFrame.DrawPDF( dc, xImagePos, yImagePos );
        }

        RealPoint pos( xInnerPos, ( yInnerPos + m_stampFrame.GetHeight( ) ) );
        RealSize size( GetWidth( ), GetHeight( )- m_stampFrame.GetHeight( ) );

        DrawTitlePDF( doc, m_title, pos, size );

        if ( m_showCatNbr )
        {            
        double xIDPos = xInnerPos + m_stampFrame.GetXPos( ) + m_stampImageFrame.GetXPos( );
        double yIDPos = yImagePos + m_stampImageFrame.GetHeight( );
        DrawIDPDF( doc, xIDPos, yIDPos );
        }       
    }

    void Stamp::Draw( wxDC& dc, double x, double y )
    { 


        //Draw the outer frame transparent
        dc.SetPen( *wxRED_PEN );
//         std::cout << "       Stamp ";      
        SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetMinWidth( ), GetMinHeight( ) );
        m_frame.Draw( dc, x, y );

    
        dc.SetPen( *wxBLACK_PEN );

        //Draw the Stamp frame
        double xPos = x + GetXPos( );
        double yPos = y + GetYPos( );

        m_stampFrame.Draw( dc, xPos, yPos );

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

            image->Rescale( width * ScaleFactor.x, height * ScaleFactor.y );
            wxBitmap bitmap = *image;

            dc.DrawBitmap( bitmap, xPos1 * ScaleFactor.x, ( yPos1 * ScaleFactor.y )+1, true );
            if ( image )
            { 
                delete image;
            }
        }
        else
        { 
            // Draw missing image frame transparent
            dc.SetPen( *wxGREEN_PEN );
            double xPos1 = xPos + m_stampFrame.GetXPos( );
            double yPos1 = yPos + m_stampFrame.GetYPos( );
            m_stampImageFrame.Draw( dc, xPos1, yPos1 );
        }

        RealPoint pos( xPos, ( yPos + m_stampFrame.GetHeight( ) ) );
        RealSize size( GetWidth( ), GetHeight( )- m_stampFrame.GetHeight( ) );

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
        int ndx = id.First( ' ' );
        id = id.Mid( ndx + 1 );
        wxSize ext = dc.GetTextExtent( id );
        wxSize  m_idTextExtent( ext.x/Design::ScaleFactor.x, ext.y/Design::ScaleFactor.y );

        x = x + ( m_stampImageFrame.GetWidth( ) - m_idTextExtent.x ) / 2;

        dc.DrawText( id, x*ScaleFactor.x, y*ScaleFactor.y );
        dc.SetFont( currFont );

        delete font;
    }



    void Stamp::DrawIDPDF( wxPdfDocument* doc, double x, double y )
    { 

        Design::Album* album = GetAlbum( );
        wxFont *font;
        if ( album )
        {
            wxFont *defFont = album->GetFont(  album->GetDefaultCatNbrFontNdx( ) );
            if ( defFont )
            {
                font = new wxFont( *defFont );
            }
        }

        if ( !font )
        {
            font = new wxFont( *wxNORMAL_FONT );
            font->SetPointSize(8);
            font->SetStyle(wxFONTSTYLE_NORMAL);
        }
        doc->SetFont( *font );
        wxPdfFont pdfFont = doc->GetCurrentFont();
 

        wxPdfFontDescription desc = pdfFont.GetDescription();
        double textHeight = font->GetPointSize() * .26;

        wxString id = GetAttrStr( AT_CatNbr );
        id.Trim( );
        id.Trim( false );
        int ndx = id.First( ' ' );
        id = id.Mid( ndx + 1 );

        double idXmargin = ( m_stampImageFrame.GetWidth( ) - doc->GetStringWidth( id ) ) / 2.;
        RealPoint pos( x + idXmargin, y ) ;
        RealSize size( doc->GetStringWidth( id ), textHeight ); 
        DrawLabelPDF( doc, id, pos, size );
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

    void Stamp::ReportLayout(  )
    { 
        wxString id = GetAttrStr( AT_CatNbr );

        std::cout << "Layout for Stamp ID " << id << "\nOuter ";
        ReportLayoutFrame(  ) ;  
        std::cout << "\nInner ";
        m_stampFrame.ReportLayout(  );
        std::cout <<  "\nImage ";
        m_stampImageFrame.ReportLayout(  );
    };

    void Stamp::DumpStamp( wxTextCtrl* ctrl )
    {
        *ctrl << DumpFrame(  );
        *ctrl << m_stampFrame.LayoutString( );
        *ctrl << m_stampImageFrame.LayoutString( );
    }

}