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
#include "design/Row.h"
#include "design/Column.h"

#include "utils/XMLUtilities.h"
#include "utils/Project.h"
#include "utils/Settings.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
//#include "gui/StampDescriptionPanel.h"
#include "gui/GuiUtils.h"

#include "catalog/CatalogVolume.h"
#include "catalog/Entry.h"
#include "catalog/CatalogCode.h"
#include "art/NotFound.xpm"

#include <wx/dcmemory.h>
#include <wx/dcgraph.h>

namespace Design {


    const double BorderAllowancePercent = .1;
    const double ImagePercentOfActual = .75;



    //--------------

    Stamp::Stamp( ) : LayoutBase( ( wxXmlNode* ) 0 )
    {
        SetNodeType( AT_Stamp );
        SetObjectName( AlbumBaseNames[ AT_Stamp ] );
        // SetShowNbr( true );
        //SetShowTitle( true );
        //SetShowSubTitle( false );

        m_nameFrame = new LabelFrame( Design::AT_NameFontType );
        m_nameFrame->SetString( "name" );
        m_nbrFrame = new LabelFrame( Design::AT_NbrFontType );
        m_nbrFrame->SetString( "Nbr" );
        m_frame.Init( );
        InitParameters( );

    }


    //--------------

    Stamp::Stamp( wxXmlNode* node ) : LayoutBase( node )
    {
        SetNodeType( AT_Stamp );
        SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
        //SetShowNbr( true );
        //SetShowTitle( true );
        //SetShowSubTitle( false );

        m_nameFrame = new LabelFrame( Design::AT_NameFontType );
        m_nbrFrame = new LabelFrame( Design::AT_NbrFontType );
        m_frame.Init( );

        InitParameters( );
        //  GetNameString
        m_nameFrame->SetString( GetAttrStr( AT_Name ) );
        wxFont font = m_nameFrame->GetFont( );
        int point = font.GetPointSize( );

        wxString str = MakeDisplayNbr( );

        // int pos = str.Find( " " );
        // str = str.substr( pos + 1 );
        m_nbrFrame->SetString( str );
        //  CalcFrame( );
    };


    //--------------

    void Stamp::CalculateYPos( double yPos, double height )
    {
        if ( GetStampNameLocationType( ) == AT_StampNameLocationBottom )
        {
            SetYPos( yPos );
        }
        else
        {
            SetYPos( yPos + height - GetHeight( ) );
        }
    }


    //--------------

    void DrawRotated( wxDC& dc, double x, double y )
    {

    }


    //--------------

    void Stamp::Draw( wxDC& dc, double x, double y )
    {
        Design::NodeStatus status = GetNodeStatus( );
        if ( status != Design::AT_FATAL )
        {
            //Draw the outer frame transparent
            //m_frame.Draw( dc, x, y );

            SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetMinWidth( ), GetMinHeight( ) );


            //Draw the Stamp frame
            double xInnerPos = x + GetXPos( );
            double yInnerPos = y + GetYPos( );

            dc.SetPen( *wxBLACK_PEN );
            m_borderFrame.Draw( dc, xInnerPos, yInnerPos );

            double xImagePos = xInnerPos + m_stampImageFrame.GetXPos( );
            double yImagePos = yInnerPos + m_stampImageFrame.GetYPos( );
            if ( xImagePos < 0.0 )xImagePos = .01;
            if ( yImagePos < 0.0 )yImagePos = .01;

            wxString filename = GetStampImageFilename( );

            wxImage image;
            wxString imageName = GetStampImageFilename( );
            wxString str = GetProject( )->GetImageFullPath( imageName );
            if ( GetProject( )->ImageExists( str ) )
            {
                image = wxImage( str, wxBITMAP_TYPE_JPEG );
            }

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
            }
            if ( GetShowTitle( ) )
            {
                GetNameFrame( )->Draw( dc, xInnerPos, yInnerPos );
            }
            else
            {
                //                std::cout << GetNameFrame( )->GetString( ) << "\n";
                int a = 1;
            }

            if ( GetShowNbr( ) )
            {
                GetNbrFrame( )->Draw( dc, xInnerPos, yInnerPos );
            }
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

        wxImage image = GetProject( )->GetImage( filename );
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

        if ( GetShowTitle( ) )
        {
            GetNameFrame( )->DrawPDF( doc, xInnerPos, yInnerPos );
        }

        if ( GetShowNbr( ) )
        {
            GetNbrFrame( )->DrawPDF( doc, xInnerPos, yInnerPos );
        }
    }


    //--------------

    void Stamp::DumpStamp( wxTextCtrl* ctrl )
    {
        *ctrl << DumpFrame( );
        *ctrl << m_borderFrame.Layout( );
        *ctrl << m_stampImageFrame.Layout( );
    }


    //--------------

    wxString Stamp::GetCatalog( )
    {
        wxString cat = GetAttrStr( Design::AT_Catalog );;
        if ( cat.IsEmpty( ) )
        {
            cat = GetAlbum( )->GetCatalog( );
        }
        return cat;
    };


    //--------------

    wxString Stamp::GetCatalogCodes( )
    {
        return GetAttrStr( Design::AT_Catalog_Codes );;
    };



    //--------------

    wxString  Stamp::GetCatalogNbr( ) {
        return GetAttrStr( AT_CatNbr );
    };


    //--------------  

    StampNameLocation  Stamp::GetDefaultStampNameLocation( )
    {
        Design::AlbumBase* node = GetParent( );
        Design::AlbumBaseType type = node->GetNodeType( );
        StampNameLocation defaultLoc = AT_StampNameLocationDefault;
        if ( type == Design::AT_Row )
        {
            Design::Row* row = ( Design::Row* ) node;
            defaultLoc = row->GetDefaultStampNameLocationType( );
        }
        else if ( type = Design::AT_Col )
        {
            Design::Column* col = ( Design::Column* ) node;
            defaultLoc = col->GetDefaultStampNameLocationType( );
        }
        else
        {
            defaultLoc = GetAlbum( )->GetDefaultStampNameLocationType( );
        }
        return  defaultLoc;
    }


    //--------------

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

    //--------------

    double Stamp::GetMountAllowanceHeight( )
    {
        return m_mountAllowanceHeight;
    };


    //--------------

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

    LabelFrame* Stamp::GetNameFrame( ) {
        return m_nameFrame;
    };


    //--------------

    wxString  Stamp::GetNameString( ) {
        return m_nameFrame->GetString( );
    };


    //--------------

    LabelFrame* Stamp::GetNbrFrame( ) {
        return m_nbrFrame;
    };


    //--------------

    wxString  Stamp::GetNbrString( ) {
        return GetAttrStr( AT_CatNbr );
    };


    //--------------

    double Stamp::GetSelvageHeight( )
    {
        return m_selvageHeight;
    };


    //--------------

    wxString Stamp::GetSelvageHeightStr( )
    {
        return GetAttrStr( Design::AT_SelvageHeight );
    };


    //--------------

    double Stamp::GetSelvageWidth( )
    {
        return m_selvageWidth;
    };


    //--------------

    wxString Stamp::GetSelvageWidthStr( )
    {
        return GetAttrStr( Design::AT_SelvageWidth );;
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

    wxString Stamp::GetStampNameLocation( )
    {
        return GetAttrStr( AT_StampNameLocation );
    }

    //--------------

    StampNameLocation Stamp::GetStampNameLocationType( )
    {
        StampNameLocation loc = FindStampLocationType( GetStampNameLocation( ) );
        if ( loc == AT_StampNameLocationDefault )
        {
            return GetDefaultStampNameLocation( );
        }
        return loc;
    };


    //--------------

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
        str = GetCatalogCodes( );
        if ( !str.IsEmpty( ) )
        {
            wxString cat = GetCatalog( );
            Catalog::CatalogCode catCodeArray( str );
            wxString preferredID = catCodeArray.GetPreferredCatalogCode( cat );
            SetNbrString( preferredID );
        }
    }


    //--------------

    bool Stamp::IsDefaultVal( AlbumAttrType type )
    {
        return !GetAlbum( )->GetDefaultValStr( type ).Cmp( GetAttrStr( type ) );
    }


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

    wxString Stamp::MakeDisplayNbr( )
    {
        wxString str = GetCatalogNbr( );
        wxString catalog;
        wxString country;
        wxString code;
        Catalog::GetCodes( str, catalog, country, code );
        wxString preferredCatalog = GetProject( )->GetProjectCatalogCode( );
        if ( !preferredCatalog.Cmp( catalog ) )
        {
            return code;
        }
        else
        {
            return catalog + ":" + code;
        }
    }


    //--------------

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
        }
        return image;
    }


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
        SetAttribute( xmlNode, Design::AT_Catalog_Codes );
        if ( IsDefaultVal( AT_Catalog ) ) SetAttribute( xmlNode, AT_Catalog );
        if ( GetAttrStr( AT_Catalog_Codes ).IsEmpty( ) )SetAttribute( xmlNode, AT_CatNbr );
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_Width );
        SetAttribute( xmlNode, AT_Height );
        if ( IsDefaultVal( AT_SelvageHeight ) ) SetAttribute( xmlNode, AT_SelvageHeight );
        if ( IsDefaultVal( AT_SelvageWidth ) ) SetAttribute( xmlNode, AT_SelvageWidth );
        if ( IsDefaultVal( AT_MountAllowanceHeight ) ) SetAttribute( xmlNode, AT_MountAllowanceHeight );
        if ( IsDefaultVal( AT_MountAllowanceWidth ) ) SetAttribute( xmlNode, AT_MountAllowanceWidth );
        SetAttribute( xmlNode, AT_Link );
        SetAttribute( xmlNode, AT_ShowTitle );
        //SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_ShowCatNbr );
        SetAttribute( xmlNode, AT_ImageName );
        SaveFonts( xmlNode );
    }


    //--------------

    void Stamp::SaveFonts( wxXmlNode* parent )
    {
        if ( m_nameFrame->GetFontNdx( ) >= 0 || m_nbrFrame->GetFontNdx( ) >= 0 )
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

    void Stamp::SetCatalog( wxString cat )
    {
        wxString albumCat = GetAlbum( )->GetCatalog( );
        if ( cat.Cmp( albumCat ) )
        {
            SetAttrStr( AT_Catalog, cat );
        }
        else
        {
            DeleteAttribute( AttrNameStrings[ AT_Catalog ] );
        }
    }


    //--------------

    void Stamp::SetCatalogCodes( wxString catCodes )
    {
        SetAttrStr( AT_Catalog_Codes, catCodes );
    }


    //--------------

    void Stamp::SetMountAllowanceHeight( double val )
    {
        m_mountAllowanceHeight = val;
        wxString str = wxString::Format( "%4.1f", val );
        SetAttrStr( Design::AT_MountAllowanceHeight, str );
    };


    //--------------

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


    //--------------

    void Stamp::SetMountAllowanceWidth( wxString str )
    {
        SetAttrStr( Design::AT_MountAllowanceWidth, str );
        bool ok = str.ToDouble( &m_mountAllowanceWidth );
    };


    //--------------

    void  Stamp::SetNameString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_nameFrame->SetString( str );
    };


    //--------------

    void  Stamp::SetNbrString( wxString str )
    {
        SetAttrStr( AT_CatNbr, str );
        wxString displalyString = MakeDisplayNbr( );
        GetNbrFrame( )->SetString( displalyString );
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


    //--------------

    void Stamp::SetSelvageWidth( wxString str )
    {
        SetAttrStr( Design::AT_SelvageWidth, str );
        bool ok = str.ToDouble( &m_selvageWidth );
    };


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

    void Stamp::SetStampImageFilename( wxString filename )
    {
        SetAttrStr( AT_ImageName, filename );
        m_imageFilename = filename;
        m_image = GetImageFromFilename( filename );
    }


    //--------------

    void Stamp::SetStampWidth( double val )
    {
        m_stampFrame.SetWidth( val );
        wxString str = wxString::Format( "%4.1f", val );
        SetAttrStr( Design::AT_Width, str );
        UpdateMinimumSize( );
        UpdatePositions( );
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

    void Stamp::SetStampNameLocation( StampNameLocation loc )
    {
        StampNameLocation defaultLoc = GetDefaultStampNameLocation( );
        if ( loc == defaultLoc )
        {
            loc = AT_StampNameLocationDefault;
        }
        SetAttrStr( AT_StampNameLocation, StampNameLocationStrings[ loc ] );
    };


    //--------------

    bool Stamp::UpdateMinimumSize( )
    {
        //  border allowance for one edge
        SetStampMargin( 4 );

        // everything is basedfrom the actual stamp m_stampFrame
        m_borderFrame.SetHeight( m_stampFrame.GetHeight( ) + GetSelvageHeight( ) + GetMountAllowanceHeight( ) );
        m_borderFrame.SetWidth( m_stampFrame.GetWidth( ) + GetSelvageWidth( ) + GetMountAllowanceWidth( ) );

        // The width of the stamp object is the m_borderFrame width + margin
        SetWidth( m_borderFrame.GetWidth( ) + 2 * GetStampMargin( ) );

        // the height of the stamp object is the border frame height + border + title height 
        if ( GetShowTitle( ) )
        {
            SetHeight( GetNameFrame( )->GetHeight( ) + m_borderFrame.GetHeight( ) + 1 /** GetStampMargin( )*/ );
        }
        else
        {
            SetHeight( m_borderFrame.GetHeight( ) + 1 /** GetStampMargin( )*/ );
        }

        SetMinWidth( GetWidth( ) );
        SetMinHeight( GetHeight( ) );


        // the NameFrame vals are determined by the outer stamp object width, the text and the font.
        // note the name is centered in the outside stamp object
        UpdateString( GetNameFrame( ), GetWidth( ) );

        // the NbrFrame vals are determined by stamp frame width, the text and the font
        // note the nbr is centered in the m_borderFrame
        UpdateString( GetNbrFrame( ), m_borderFrame.GetWidth( ) );

        m_stampImageFrame.SetWidth( m_stampFrame.GetWidth( ) * ImagePercentOfActual );
        m_stampImageFrame.SetHeight( m_stampFrame.GetHeight( ) * ImagePercentOfActual );

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
        // the xPos and yPos are offsets from the containing frame
     //the m_borderFrame is offset by the margin.
        m_borderFrame.SetXPos( GetStampMargin( ) );

        // the name frame has 0 x offset but is centered in its frame
        GetNameFrame( )->SetXPos( 0 );

        // the number g=frame is centered within the border frame
        GetNbrFrame( )->SetXPos( m_borderFrame.GetXPos( ) + ( m_borderFrame.GetWidth( ) - m_nbrFrame->GetWidth( ) ) / 2 );

        // the image is horizontally centered within the m_borderFrame.
        m_stampImageFrame.SetXPos( m_borderFrame.GetXPos( ) + ( m_borderFrame.GetWidth( ) - m_stampImageFrame.GetWidth( ) ) / 2 );
        if ( GetShowTitle( ) )
        {
            if ( GetStampNameLocationType( ) == AT_StampNameLocationBottom )
            {
                //if the title is on the bottom then the border frame is on top
                m_borderFrame.SetYPos( 0 );
                // and the name is just below the m_borderFrame
                m_nameFrame->SetYPos( m_borderFrame.GetHeight( ) + 1 );
            }
            else
            {
                // if the name is on top then no offset for the name frame
                m_nameFrame->SetYPos( 0 );
                // and the border is just under that

                m_borderFrame.SetYPos( GetNameFrame( )->GetHeight( ) + 1 );
            }
        }
        else
        {
            m_borderFrame.SetYPos( 0 );
        }
        // center the image vertically within the m_borderFrame
        // note the image offsets from the m_borderFrame
        m_stampImageFrame.SetYPos( m_borderFrame.GetYPos( ) + ( m_borderFrame.GetHeight( ) - m_stampImageFrame.GetHeight( ) - 4 ) / 2 );
        m_nbrFrame->SetYPos( m_stampImageFrame.GetYPos( ) + m_stampImageFrame.GetHeight( ) );

        ValidateNode( );

    }


    //--------------

    NodeStatus Stamp::ValidateNode( )
    {
        CheckLayout( );

        NodeStatus status = AT_OK;
        wxString filename = GetStampImageFilename( );
        wxString str;// = GetProject( )->GetImageFullPath( filename );
        wxImage image = GetProject( )->GetImage( filename );
        if ( !image.IsOk( ) )
        {
            std::cout << "\nInvalid Stamp Image. " << filename << "\n";
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
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << " Warning\n";
            }
        }
        return status;
    }

}
