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
 */

#include "Defs.h"

#include "design/Stamp.h"
 //#include "design/Title.h"
#include "design/Album.h"
#include "design/AlbumData.h"

#include "utils/XMLUtilities.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
//#include "gui/StampDescriptionPanel.h"
#include "gui/GuiUtils.h"

#include "catalog/CatalogVolume.h"
#include "catalog/Entry.h"
#include "art/NotFound.xpm"


namespace Design {


    const double BorderAllowancePercent = .1;
    const double ImagePercentOfActual = .75;
    // const char* StampErrorStrings[ AT_NbrStampErrorTypes ] = {
    //     "Invalid Image Link",
    //     "Invalid Height",
    //     "Invalid Width" };


    // void Stamp::ClearError( )
    // {
    //     m_error[ AT_InvalidImage ] = AT_OK;
    //     m_error[ AT_InvalidHeight ] = AT_OK;
    //     m_error[ AT_InvalidWidth ] = AT_OK;
    // };

    // void Stamp::SetError( StampErrorType type, NodeStatus status )
    // {
    //     m_error[ type ] = status;
    // };

    // NodeStatus Stamp::GetStatus( )
    // {
    //     NodeStatus status = AT_OK;
    //     if ( m_error[ AT_InvalidImage ] > status )
    //     {
    //         status = m_error[ AT_InvalidImage ];
    //         if ( status == AT_FATAL )
    //             return status;
    //     }
    //     if ( m_error[ AT_InvalidHeight ] > status )
    //     {
    //         status = m_error[ AT_InvalidHeight ];
    //         if ( status == AT_FATAL )
    //             return status;
    //     }
    //     if ( m_error[ AT_InvalidWidth ] > status )
    //     {
    //         status = m_error[ AT_InvalidWidth ];
    //         if ( status == AT_FATAL )
    //             return status;
    //     }

    //     return status;

    // };

    //--------------
    void Stamp::CalcFrame( )
    {
        //  border allowance for one edge
        double borderAllowance = 0;//m_stampFrame.GetWidth( ) * BorderAllowancePercent / 2;
        TitleLocation titleLocation = GetTitleLayoutLocation( );

        // The width of the frame is the stamp width * border
        SetWidth( m_stampFrame.GetWidth( ) + 2 * borderAllowance );

        // the NameFrame vals are determined by the outer stamp frame width, the text and the font.
        UpdateString( GetNameFrame( ), GetWidth( ) );

        // the height of the frame is the stamp height + border + title height 
        SetHeight( ( m_stampFrame.GetHeight( ) + 2 * borderAllowance ) + GetNameFrame( )->GetHeight( ) );
        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );

        //the Frame is positioned  the border allowance over
        m_stampFrame.SetXPos( borderAllowance );
        m_stampFrame.SetYPos( borderAllowance );
        GetNameFrame( )->SetXPos( 0 );

        // the NbrFrame vals are determined by stamp frame width, the text and the font
        UpdateString( GetNbrFrame( ), m_stampFrame.GetWidth( ) );
        GetNbrFrame( )->SetXPos( m_stampFrame.GetXPos( ) );

        m_stampImageFrame.SetWidth( m_stampFrame.GetWidth( ) * ImagePercentOfActual );
        m_stampImageFrame.SetHeight( m_stampFrame.GetHeight( ) * ImagePercentOfActual );
        m_stampImageFrame.SetXPos( m_stampFrame.GetXPos( ) + ( m_stampFrame.GetWidth( ) - m_stampImageFrame.GetWidth( ) ) / 2 );
        if ( GetShowNbr( ) )
        {
            double yOffset = m_stampFrame.GetYPos( ) + ( m_stampFrame.GetHeight( ) - m_stampImageFrame.GetHeight( ) - GetNbrFrame( )->GetHeight( ) - 1 ) / 2;
            m_stampImageFrame.SetYPos( yOffset );
        }
        else
        {
            m_stampImageFrame.SetYPos( m_stampFrame.GetYPos( ) + ( m_stampFrame.GetHeight( ) - m_stampImageFrame.GetHeight( ) ) / 2 );
        }
        // the nbr ypos is just below the image
        GetNbrFrame( )->SetYPos( m_stampImageFrame.GetYPos( ) + m_stampImageFrame.GetHeight( ) + 1 );

        //the name ypos is just below the stampframe
        GetNameFrame( )->SetYPos( m_stampFrame.GetHeight( ) + 1 );

    }

    //--------------
    void Stamp::Draw( wxDC& dc, double x, double y )
    {
        //Draw the outer frame transparent
        // m_frame.Draw( dc, x, y );

        SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetMinWidth( ), GetMinHeight( ) );

        //Draw the Stamp frame
        double xInnerPos = x + GetXPos( );
        double yInnerPos = y + GetYPos( );

        dc.SetPen( *wxBLACK_PEN );
        m_stampFrame.Draw( dc, xInnerPos, yInnerPos );

        double xImagePos = xInnerPos + m_stampImageFrame.GetXPos( );
        double yImagePos = yInnerPos + m_stampImageFrame.GetYPos( );

        wxString filename = GetStampImageFilename( );

        wxImage image = GetAlbumVolume( )->GetImage( filename );
        if ( image.IsOk( ) )
        {
            //Draw the stamp image
            if ( GetAlbum( )->GetGrayScaleImages( ) )
            {
                image = image.ConvertToGreyscale( );
            }

            DrawImage( dc, image, xImagePos, yImagePos, m_stampImageFrame.GetWidth( ), m_stampImageFrame.GetHeight( ) );
        }
        else
        {
            // Draw missing image frame transparent
            dc.SetPen( *wxTRANSPARENT_PEN );
            m_stampImageFrame.Draw( dc, xImagePos, yImagePos );
        }

        double borderAllowance = m_stampFrame.GetYPos( );
        GetNameFrame( )->Draw( dc, xInnerPos, yInnerPos );


        if ( GetShowNbr( ) )
        {

            GetNbrFrame( )->Draw( dc, xInnerPos, yInnerPos );

        }
    }

    //--------------

    void Stamp::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        //Draw the outer frame transparent
//        m_frame.DrawPDF( doc, x, y );

        //Draw the Stamp frame
        double xInnerPos = x + GetXPos( );
        double yInnerPos = y + GetYPos( );

        m_stampFrame.DrawPDF( doc, xInnerPos, yInnerPos );

        double xImagePos = xInnerPos + m_stampImageFrame.GetXPos( );
        double yImagePos = yInnerPos + m_stampImageFrame.GetYPos( );

        wxString filename = GetStampImageFilename( );

        wxImage image = GetAlbumVolume( )->GetImage( filename );
        if ( image.IsOk( ) )
        {
            //Draw the stamp image
            if ( GetAlbum( )->GetGrayScaleImages( ) )
            {
                image = image.ConvertToGreyscale( );
            }
            double height = m_stampImageFrame.GetHeight( );
            double width = m_stampImageFrame.GetWidth( );
            if ( width <= 0.01 || height <= 0.01 )
            {
                height = 10;
                width = 10;
            }

            doc->Image( filename, image, xImagePos, yImagePos, width, height );
        }
        else
        {
            // Draw missing image frame transparent
            //m_stampImageFrame.DrawPDF( dc, xImagePos, yImagePos );
        }


        GetNameFrame( )->DrawPDF( doc, xInnerPos, yInnerPos );

        if ( GetShowNbr( ) )
        {
            GetNbrFrame( )->DrawPDF( doc, xInnerPos, yInnerPos );
        }
    }

    //--------------

    void Stamp::DumpStamp( wxTextCtrl* ctrl )
    {
        *ctrl << DumpFrame( );
        *ctrl << m_stampFrame.LayoutString( );
        *ctrl << m_stampImageFrame.LayoutString( );
    }

    //--------------

    LabelFrame* Stamp::GetNameFrame( ) { return m_nameFrame; };

    //--------------

    wxString  Stamp::GetNameString( ) { return m_nameFrame->GetString( ); };
    void  Stamp::SetNameString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_nameFrame->SetString( str );
    };

    //--------------


    LabelFrame* Stamp::GetNbrFrame( ) { return m_nbrFrame; };

    wxString  Stamp::GetNbrString( ) { return m_nbrFrame->GetString( ); };
    void  Stamp::SetNbrString( wxString str )
    {
        SetAttrStr( AT_Name, str );
    };

    //--------------

    double Stamp::GetStampHeight( )
    {
        return m_stampFrame.GetHeight( );
    };

    //--------------

    wxString Stamp::GetStampHeightStr( )
    {
        return GetAttrStr( Design::AT_Height );
    };

    //--------------

    double Stamp::GetStampWidth( )
    {
        return m_stampFrame.GetWidth( );
    };

    //--------------

    wxString Stamp::GetStampWidthStr( )
    {
        return GetAttrStr( Design::AT_Width );
    };

    //--------------

    wxString Stamp::GetStampImageFilename( )
    {
        return GetAttrStr( AT_ImageName );
    }

    //--------------

    // wxImage Stamp::GetStampImage( wxString filename )
    // {
    //     wxImage image;
    //     if ( filename.IsEmpty( ) )
    //     {
    //         image = wxImage( NotFound );
    //     }
    //     else
    //     {

    //         Utils::ImageRepository* imageRepository = GetAlbumVolume( )->GetImageRepository( );

    //         if ( !imageRepository || !imageRepository->Exists( filename ) )
    //         {
    //             image = wxImage( NotFound );
    //         }
    //         else
    //         {
    //             image = imageRepository->GetImage( filename );

    //             if ( !image.IsOk( ) )
    //             {
    //                 image = wxImage( NotFound );
    //             }
    //         }
    //     }
    //     return image;
    // }

    //--------------

    void Stamp::LoadFonts( wxXmlNode* node )
    {
        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {
            m_nameFrame->LoadFont( fonts );
            m_nbrFrame->LoadFont( fonts );
        }
    }

    //--------------

    void Stamp::SetStampHeight( double val )
    {
        m_stampFrame.SetHeight( val );
        wxString str = wxString::Format( "%d", val );
        SetAttrStr( Design::AT_Height, str );
    };

    //--------------

    void Stamp::SetStampHeight( wxString str )
    {
        SetAttrStr( Design::AT_Height, str );
        double val;
        bool ok = str.ToDouble( &val );
        m_stampFrame.SetHeight( val );
    };

    //--------------

    void Stamp::SetStampWidth( double val )
    {
        m_stampFrame.SetWidth( val );
        wxString str = wxString::Format( "%d", val );
        SetAttrStr( Design::AT_Width, str );
        CalcFrame( );
    };

    //--------------

    void Stamp::SetStampWidth( wxString str )
    {
        SetAttrStr( Design::AT_Width, str );
        double val;
        bool ok = str.ToDouble( &val );
        m_stampFrame.SetWidth( val );
    };

    //--------------

    void Stamp::ReportLayout( )
    {
        wxString id = GetAttrStr( AT_CatNbr );

        std::cout << "Layout for Stamp ID " << id << "\nOuter ";
        ReportLayoutFrame( );
        std::cout << "\nInner ";
        m_stampFrame.ReportLayout( );
        std::cout << "\nImage ";
        m_stampImageFrame.ReportLayout( );
    };

    //--------------

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
        SaveFonts( xmlNode );
    }

    //--------------

    void Stamp::SaveFonts( wxXmlNode* parent )
    {
        if ( m_nameFrame->GetFontNdx( ).IsOk( ) || m_nbrFrame->GetFontNdx( ).IsOk( ) )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                m_nameFrame->SaveFont( fonts );
                m_nbrFrame->SaveFont( fonts );
            }
        }
    }

    //--------------

    bool Stamp::UpdateMinimumSize( )
    {
        CalcFrame( );

        if ( ValidateNode( ) == AT_FATAL )
        {
            return false;
        }
        return true;
    }

    //--------------

    void Stamp::UpdateSizes( )
    {
    }

    //--------------

    void Stamp::UpdatePositions( )
    {
    }

    //--------------

    NodeStatus Stamp::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        wxString str;
        wxImage image = GetAlbumVolume( )->GetImage( GetStampImageFilename( ) );
        if ( !image.IsOk( ) )
        {
            str = wxString::Format( "Invalid Stamp Image.\n" );
            GetErrorArray( )->Add( str );
            //           SetError( AT_InvalidImage, AT_WARING );
            status = AT_WARING;
        }
        if ( GetHeight( ) <= 0.01 )
        {
            str = wxString::Format( "Invalid Stamp Height.\n" );
            GetErrorArray( )->Add( str );
            //            SetError( AT_InvalidHeight, AT_FATAL );
            status = AT_FATAL;
        }
        if ( GetWidth( ) <= 0.01 )
        {
            str = wxString::Format( "Invalid Stamp Width.\n" );
            GetErrorArray( )->Add( str );
            status = AT_FATAL;
        }
        m_nodeValid = status;
        return status;
    }

    //--------------

}