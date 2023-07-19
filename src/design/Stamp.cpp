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
#include "utils/Project.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
//#include "gui/StampDescriptionPanel.h"
#include "gui/GuiUtils.h"

#include "catalog/CatalogVolume.h"
#include "catalog/Entry.h"
#include "art/NotFound.xpm"

#include <wx/dcmemory.h>
#include <wx/dcgraph.h>

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
    void Stamp::InitParameters( )
    {
        wxString height = GetAttrStr( Design::AT_Height );
        if ( height.IsEmpty( ) )
        {
            SetStampHeight( "10.0" );
        }
        else
        {
            SetStampHeight( height );
        }

        wxString width = GetAttrStr( Design::AT_Width );
        if ( height.IsEmpty( ) )
        {
            SetStampWidth( "10.0" );
        }
        else
        {
            SetStampWidth( width );
        }

        wxString str = GetAttrStr( AT_SelvageHeight );
        if ( str.IsEmpty( ) )
        {
            SetSelvageHeight( GetAlbum( )->GetDefaultVal( AT_SelvageHeight ) );
        }
        else
        {
            bool ok = str.ToDouble( &m_selvageHeight );
        }

        str = GetAttrStr( AT_SelvageWidth );
        if ( str.IsEmpty( ) )
        {
            SetSelvageWidth( GetAlbum( )->GetDefaultVal( AT_SelvageWidth ) );
        }
        else
        {
            bool ok = str.ToDouble( &m_selvageWidth );
        }

        str = GetAttrStr( AT_MountAllowanceHeight );
        if ( str.IsEmpty( ) )
        {
            SetMountAllowanceHeight( GetAlbum( )->GetDefaultVal( AT_MountAllowanceHeight ) );
        }
        else
        {
            bool ok = str.ToDouble( &m_mountAllowanceHeight );
        }

        str = GetAttrStr( AT_MountAllowanceWidth );
        if ( str.IsEmpty( ) )
        {
            SetMountAllowanceWidth( GetAlbum( )->GetDefaultVal( AT_MountAllowanceWidth ) );
        }
        else
        {
            bool ok = str.ToDouble( &m_mountAllowanceWidth );
        }
    }

    Stamp::Stamp( wxXmlNode* node ) : LayoutBase( node )
    {
        SetNodeType( AT_Stamp );
        SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
        SetShowNbr( true );
        SetShowTitle( true );
        InitParameters( );

        m_nameFrame = new LabelFrame( Design::AT_NameFontType );
        m_nameFrame->SetString( GetAttrStr( AT_Name ) );
        m_nbrFrame = new LabelFrame( Design::AT_NbrFontType );
        m_nbrFrame->SetString( GetAttrStr( AT_CatNbr ) );
        //  CalcFrame( );

    };

    Stamp::Stamp( ) : LayoutBase( ( wxXmlNode* ) 0 )
    {
        SetNodeType( AT_Stamp );
        SetObjectName( AlbumBaseNames[ AT_Stamp ] );
        SetShowNbr( true );
        SetShowTitle( true );
        InitParameters( );

        m_nameFrame = new LabelFrame( Design::AT_NameFontType );
        m_nameFrame->SetString( "name" );
        m_nbrFrame = new LabelFrame( Design::AT_NbrFontType );
        m_nbrFrame->SetString( "Nbr" );
        //     CalcFrame( );
    }

    //--------------
    void Stamp::CalcFrame( )
    {
        //  border allowance for one edge
        double borderAllowance = 0;//m_stampFrame.GetWidth( ) * BorderAllowancePercent / 2;
        TitleLocation titleLocation = GetTitleLayoutLocation( );

        m_borderFrame.SetHeight( m_stampFrame.GetHeight( ) + GetSelvageHeight( ) + GetMountAllowanceHeight( ) );
        m_borderFrame.SetWidth( m_stampFrame.GetWidth( ) + GetSelvageWidth( ) + GetMountAllowanceWidth( ) );

        // The width of the frame is the stamp width * border
        SetWidth( m_borderFrame.GetWidth( ) + 2 * borderAllowance );

        // the NameFrame vals are determined by the outer stamp frame width, the text and the font.
        UpdateString( GetNameFrame( ), GetWidth( ) );

        // the height of the frame is the stamp height + border + title height 
        SetHeight( ( m_borderFrame.GetHeight( ) + 2 * borderAllowance ) + GetNameFrame( )->GetHeight( ) );
        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );

        //the Frame is positioned  the border allowance over
        m_borderFrame.SetXPos( borderAllowance );
        m_borderFrame.SetYPos( borderAllowance );
        GetNameFrame( )->SetXPos( 0 );

        // the NbrFrame vals are determined by stamp frame width, the text and the font
        UpdateString( GetNbrFrame( ), m_borderFrame.GetWidth( ) );
        GetNbrFrame( )->SetXPos( m_borderFrame.GetXPos( ) );

        m_stampImageFrame.SetWidth( m_stampFrame.GetWidth( ) * ImagePercentOfActual );
        m_stampImageFrame.SetHeight( m_stampFrame.GetHeight( ) * ImagePercentOfActual );
        m_stampImageFrame.SetXPos( m_borderFrame.GetXPos( ) + ( m_borderFrame.GetWidth( ) - m_stampImageFrame.GetWidth( ) ) / 2 );
        if ( GetShowNbr( ) )
        {
            double yOffset = m_borderFrame.GetYPos( ) + ( m_borderFrame.GetHeight( ) - m_stampImageFrame.GetHeight( ) - GetNbrFrame( )->GetHeight( ) - 1 ) / 2;
            m_stampImageFrame.SetYPos( yOffset );
        }
        else
        {
            m_stampImageFrame.SetYPos( m_borderFrame.GetYPos( ) + ( m_borderFrame.GetHeight( ) - m_stampImageFrame.GetHeight( ) ) / 2 );
        }
        // the nbr ypos is just below the image
        GetNbrFrame( )->SetYPos( m_stampImageFrame.GetYPos( ) + m_stampImageFrame.GetHeight( ) + 1 );

        //the name ypos is just below the stampframe
        GetNameFrame( )->SetYPos( m_borderFrame.GetHeight( ) + 1 );

    }


    wxImage Stamp::GetImage( )
    {
        if ( m_image.IsOk( ) )
        {
            return m_image;
        }
        else
        {

            wxString imageName = GetStampImageFilename( );
            wxString str = GetProject( )->GetImageFullPath( imageName );
            if ( GetProject( )->ImageExists( str ) )
            {
                m_image = wxImage( str );
            }
            return m_image;
        }
    }


    wxImage Stamp::RescaleImage( )
    {
        if ( !m_image.IsOk( ) )
        {
            GetImage( );
        }
        wxImage image = m_image;
        wxSize size = m_image.GetSize( );
        if ( size.GetX( ) != m_stampImageFrame.GetWidth( )
            || size.GetY( ) != m_stampImageFrame.GetHeight( ) )
        {

            image.Rescale( m_stampImageFrame.GetWidth( ), m_stampImageFrame.GetHeight( ), wxIMAGE_QUALITY_HIGH );
            //image = m_image.Scale( m_stampImageFrame.GetWidth( ), m_stampImageFrame.GetHeight( ), wxIMAGE_QUALITY_HIGH );
        }
        return image;
    }

    void DrawRotated( wxDC& dc, double x, double y )
    {

    }

    //--------------
    void Stamp::Draw( wxDC& dc, double x, double y )
    {
        Design::NodeStatus status = GetNodeStatus( );
        if ( status != Design::AT_FATAL ) {
            //Draw the outer frame transparent
            // m_frame.Draw( dc, x, y );

            SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetMinWidth( ), GetMinHeight( ) );

            //Draw the Stamp frame
            double xInnerPos = x + GetXPos( );
            double yInnerPos = y + GetYPos( );
            //wxPen pen = dc.GetPen( );
            //pen.SetColour( *wxBLACK );
            wxPen pen( *wxBLACK, 1, wxPENSTYLE_DOT );

            dc.SetPen( pen );
            m_borderFrame.Draw( dc, xInnerPos, yInnerPos );

            double xImagePos = xInnerPos + m_stampImageFrame.GetXPos( );
            double yImagePos = yInnerPos + m_stampImageFrame.GetYPos( );
            if ( xImagePos < 0.0 )xImagePos = .01;
            if ( yImagePos < 0.0 )yImagePos = .01;

            wxString filename = GetStampImageFilename( );

            //wxImage image = GetImage( );
            wxImage image;
            wxString imageName = GetStampImageFilename( );
            wxString str = GetProject( )->GetImageFullPath( imageName );
            if ( GetProject( )->ImageExists( str ) )
            {
                image = wxImage( str, wxBITMAP_TYPE_JPEG );
            }

            //= Utils::GetImageFromFilename( filename );
            if ( image.IsOk( ) )
            {
                //Draw the stamp image
                if ( GetAlbum( )->GetGrayScaleImages( ) )
                {
                    image = image.ConvertToGreyscale( );
                }

                DrawImage( dc, image,
                    xImagePos, yImagePos,
                    m_stampImageFrame.GetWidth( ), m_stampImageFrame.GetHeight( ) );
            }
            else
            {
                // Draw missing image frame transparent

                dc.SetPen( *wxTRANSPARENT_PEN );
                m_stampImageFrame.Draw( dc, xImagePos, yImagePos );
                pen.SetColour( *wxBLACK );
            }

            double borderAllowance = m_borderFrame.GetYPos( );
            GetNameFrame( )->Draw( dc, xInnerPos, yInnerPos );


            if ( GetShowNbr( ) )
            {

                GetNbrFrame( )->Draw( dc, xInnerPos, yInnerPos );

            }
        }
        else
        {
            int a = 0;
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

        wxPdfLineStyle currStyle = PDFLineStyle( doc, *wxBLACK, .2, defaultDash );

        m_borderFrame.DrawPDF( doc, xInnerPos, yInnerPos );
        doc->SetLineStyle( currStyle );

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
        *ctrl << m_borderFrame.LayoutString( );
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

    void Stamp::SetStampImageFilename( wxString filename )
    {
        SetAttrStr( AT_ImageName, filename );
        m_image = GetImageFromFilename( filename );
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
        wxString str = wxString::Format( "%4.1f", val );
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
        wxString str = wxString::Format( "%4.1f", val );
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

    void Stamp::SetSelvageHeight( double val )
    {
        m_selvageHeight = val;
        wxString str = wxString::Format( "%4.1f", val );
        SetAttrStr( Design::AT_SelvageHeight, str );

    };

    //--------------

    void Stamp::SetSelvageHeight( wxString str )
    {
        SetAttrStr( Design::AT_SelvageHeight, str );
        bool ok = str.ToDouble( &m_selvageHeight );
    };

    //--------------

    void Stamp::SetSelvageWidth( double val )
    {
        m_selvageWidth = val;
        wxString str = wxString::Format( "%4.1f", val );
        SetAttrStr( Design::AT_SelvageWidth, str );
        SetSelvageWidth( str );
    };
    void Stamp::SetSelvageWidth( wxString str )
    {
        SetAttrStr( Design::AT_SelvageWidth, str );
        bool ok = str.ToDouble( &m_selvageWidth );
    };

    //--------------

    void Stamp::SetMountAllowanceHeight( double val )
    {
        m_mountAllowanceHeight = val;
        wxString str = wxString::Format( "%4.1f", val );
        SetAttrStr( Design::AT_MountAllowanceHeight, str );
    };

    void Stamp::SetMountAllowanceHeight( wxString str )
    {
        SetAttrStr( Design::AT_MountAllowanceHeight, str );
        bool ok = str.ToDouble( &m_mountAllowanceHeight );
    };

    //--------------

    void Stamp::SetMountAllowanceWidth( double val )
    {
        m_mountAllowanceWidth = val;
        wxString str = wxString::Format( "%4.1f", val );
        SetAttrStr( Design::AT_MountAllowanceWidth, str );
    };

    void Stamp::SetMountAllowanceWidth( wxString str )
    {
        SetAttrStr( Design::AT_MountAllowanceWidth, str );
        bool ok = str.ToDouble( &m_mountAllowanceWidth );
    };

    //--------------

    double Stamp::GetSelvageHeight( )
    {
        return m_selvageHeight;
    };

    wxString Stamp::GetSelvageHeightStr( )
    {
        return GetAttrStr( Design::AT_SelvageHeight );
    };

    //--------------

    double Stamp::GetSelvageWidth( )
    {
        return m_selvageWidth;
    };

    wxString Stamp::GetSelvageWidthStr( )
    {
        return GetAttrStr( Design::AT_SelvageWidth );;
    };


    //--------------


    double Stamp::GetMountAllowanceHeight( )
    {
        return m_mountAllowanceHeight;
    };

    wxString Stamp::GetMountAllowanceHeightStr( )
    {
        return  GetAttrStr( Design::AT_MountAllowanceHeight );
    };

    //--------------

    double Stamp::GetMountAllowanceWidth( )
    {
        return m_mountAllowanceWidth;
    };

    //--------------

    wxString Stamp::GetMountAllowanceWidthStr( )
    {
        return  GetAttrStr( Design::AT_MountAllowanceWidth );
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

    bool Stamp::IsDefaultVal( AlbumAttrType type )
    {
        return !GetAlbum( )->GetDefaultValStr( type ).Cmp( GetAttrStr( type ) );
    }
    void Stamp::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_CatNbr );
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_Width );
        SetAttribute( xmlNode, AT_Height );
        if ( IsDefaultVal( AT_SelvageHeight ) ) SetAttribute( xmlNode, AT_SelvageHeight );
        if ( IsDefaultVal( AT_SelvageWidth ) ) SetAttribute( xmlNode, AT_SelvageWidth );
        if ( IsDefaultVal( AT_MountAllowanceHeight ) ) SetAttribute( xmlNode, AT_MountAllowanceHeight );
        if ( IsDefaultVal( AT_MountAllowanceWidth ) ) SetAttribute( xmlNode, AT_MountAllowanceWidth );
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
        ValidateNode( );
    }

    //--------------

    NodeStatus Stamp::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        wxString filename = GetStampImageFilename( );
        wxString str;// = GetProject( )->GetImageFullPath( filename );
        wxImage image = GetAlbumVolume( )->GetImage( filename );
        if ( !image.IsOk( ) )
        {
            str = wxString::Format( "Invalid Stamp Image.\n" );
            GetErrorArray( )->Add( str );
            //SetError( AT_InvalidImage, AT_WARNING );
            status = AT_WARNING;
        }

        if ( m_stampFrame.GetHeight( ) <= 0.01 )
        {
            str = wxString::Format( "Invalid Stamp Height.\n" );
            GetErrorArray( )->Add( str );
            //SetError( AT_InvalidHeight, AT_FATAL );
            status = AT_FATAL;
        }
        if ( m_stampFrame.GetWidth( ) <= 0.01 )
        {
            str = wxString::Format( "Invalid Stamp Width.\n" );
            GetErrorArray( )->Add( str );
            status = AT_FATAL;
        }
        m_nodeValid = status;
        wxTreeItemId id = GetTreeItemId( );
        if ( id.IsOk( ) )
        {
            if ( status == AT_FATAL )
            {
                GetAlbumTreeCtrl( )->SetItemBackgroundColour( id, *wxRED );
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << "Fatal\n";
            }
            else if ( status == AT_WARNING )
            {
                GetAlbumTreeCtrl( )->SetItemBackgroundColour( id, *wxYELLOW );
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << "Warning\n";
            }
        }

        return status;

    }

    //--------------

}