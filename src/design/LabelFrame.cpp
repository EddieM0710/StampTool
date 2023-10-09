/**
 * @file LabelFrame.cpp
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

#include "design/LabelFrame.h"
#include "design/LayoutBase.h"
#include "design/Album.h"
#include "utils/FontList.h"

#include "gui/GuiUtils.h"


namespace Design {

    wxColour LabelFrame::GetColor( )
    {
        int ndx = m_FontNdx;
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            return GetFontList( )->GetColor( ndx );
        }
        else
        {
            return GetFontList( )->GetColor( GetAlbum( )->GetFontNdx( m_fontType ) );
        }
    }

    wxFont LabelFrame::GetFont( )
    {
        wxString usage = FontUsageTypeStrings[ m_fontType ];
        int ndx = m_FontNdx;
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            //std::cout << "LabelFrame::GetFont from this. " << m_string << "  usage:" << usage << " ndx:" << ndx << " " << GetFontList( )->GetMyFont( ndx )->GetNativeInfoStr( ) << "\n";

            return GetFontList( )->GetFont( ndx );
        }
        else
        {
            ndx = GetAlbum( )->GetFontNdx( m_fontType );
            //std::cout << "LabelFrame::GetFont from album. usage:" << usage << " ndx:" << ndx << " " << GetFontList( )->GetMyFont( ndx )->GetNativeInfoStr( ) << "\n";
            return GetFontList( )->GetFont( GetAlbum( )->GetFontNdx( m_fontType ) );
        }
    }

    void LabelFrame::Draw( wxDC& dc, double x, double y )
    {
        RealPoint pos = GetPosition( );
        RealSize size = GetSize( );
        pos.x += x;
        pos.y += y;
        wxString id = m_multiLineString;

        wxFont font( GetFont( ) );
        if ( font.IsOk( ) )
        {
            wxDCFontChanger( dc, font );

            wxFont origFont = font;
            wxColor origColor = dc.GetTextForeground( );
            wxColor color = GetColor( );
            dc.SetTextForeground( color );
            int point = font.GetPointSize( );
            font.SetPointSize( point );
            wxSize pixelSize = font.GetPixelSize( );
            double usX, usY;
            dc.GetUserScale( &usX, &usY );
            pixelSize.x = pixelSize.x * usX;
            pixelSize.y = pixelSize.y * usY;
            font.SetPixelSize( pixelSize );
            dc.SetFont( font );
            DrawLabel( dc, id, pos, size, wxALIGN_CENTER );
            dc.SetTextForeground( origColor );
        }
    };

    void LabelFrame::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        RealPoint pos = GetPosition( );
        pos.x += x;
        pos.y += y;

        wxFont font( GetFont( ) );
        int pointSize = font.GetPointSize( ) + 1;
        RealSize size( GetWidth( ), 0 + pointSize * .31 );
        font.SetPointSize( pointSize );
        doc->SetFont( font );
        doc->SetXY( pos.x, pos.y );
        double h = GetHeightChars( pointSize );
        doc->MultiCell( GetWidth( ), h, m_multiLineString, 0, wxPDF_ALIGN_CENTER );
    };

    void LabelFrame::LoadFont( wxXmlNode* node )
    {
        m_FontNdx = GetFontList( )->LoadFont( node, m_fontType );
        SetFontNdx( m_FontNdx );
    };

    void LabelFrame::SaveFont( wxXmlNode* fonts )
    {
        if ( fonts )
        {
            if ( !GetAlbum( )->IsDefaultFont( AT_TitleFontType, m_FontNdx ) )
            {
                GetFontList( )->SaveFont( fonts, m_FontNdx, m_fontType );
            }
        }
    }

    int LabelFrame::SetFont( wxFont newFont, wxColour newColor )
    {
        //std::cout << m_string << " " << newColor.GetAsString( ) << "\n";
        m_FontNdx = GetFontList( )->AddNewFont( newFont, newColor );

        // std::cout << "LabelFrame::SetFont ndx:" << m_FontNdx << " " << newFont.GetNativeFontInfoDesc( ) << "\n";
        Utils::Font* font = GetFontList( )->GetMyFont( m_FontNdx );
        //std::cout << "LabelFrame::SetFont " << Design::FontUsageTypeStrings[ m_FontNdx ] << " " << font->GetNativeInfoStr( ) << "\n";
        return m_FontNdx;
    };

    void LabelFrame::SetFontNdx( int ndx )
    {
        Utils::Font* font = GetFontList( )->GetMyFont( ndx );
        if ( font )
        {
            int pnt = font->GetPointSize( );

            // std::cout << "LabelFrame::SetFontNdx " << m_string
            //     << " ndx:" << ndx
            //     << " pnt:" << pnt
            //     << " family:" << font->GetNativeInfoStr( ) << "\n";

            m_FontNdx = ndx;
            return;
        }
        m_FontNdx = -1;

    };
    void LabelFrame::UpdateString( double width )
    {
        m_multiLineString = m_string;
        m_maxWidth = width;

        if ( width > 0 )
        {
            wxFont font = GetFont( );
            int point = font.GetPointSize( );
            if ( font == wxNullFont )
            {
                font = *wxNORMAL_FONT;
            }

            //   GetAlbumImagePanel( )->MakeMultiLine( m_multiLineString, font, width );
            // first break into lines if necessary then get the actual multi line text extent
            m_stringTextExtent = GetAlbumImagePanel( )->MakeMultiLine( m_multiLineString, font, width );
            // std::cout << "LabelFrame::UpdateString " << m_string << "  "
            //     << width << "  x:" << m_stringTextExtent.x
            //     << " y" << m_stringTextExtent.y
            //     << "point:" << point << "\n";
            SetWidth( m_maxWidth );
            SetHeight( m_stringTextExtent.y );
            SetMinWidth( m_maxWidth );
            SetMinHeight( m_stringTextExtent.y );
            SetXPos( 0 );
            SetYPos( 0 );
        }
        else
        {
            SetWidth( 0 );
            SetHeight( 0 );
            SetMinWidth( 0 );
            SetMinHeight( 0 );
            SetXPos( 0 );
            SetYPos( 0 );
        }
    };
}
