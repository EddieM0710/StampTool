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
        int ndx = m_FontNdx.Get( );
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
        int ndx = m_FontNdx.Get( );
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            // std::cout << "LabelFrame::GetFont from ndx " << GetFontList( )->GetMyFont( ndx )->GetNativeInfoStr( ) << "\n";

            return GetFontList( )->GetFont( ndx );
        }
        else
        {
            ndx = GetAlbum( )->GetFontNdx( m_fontType );
            return GetFontList( )->GetFont( GetAlbum( )->GetFontNdx( m_fontType ) );
        }
    }

    void LabelFrame::Draw( wxDC& dc, double x, double y )
    {
        wxString id = m_multiLineString;
        wxFont font( GetFont( ) );
        int point = font.GetPointSize( );
        font.SetPointSize( point - 2 );
        dc.SetFont( font );
        RealPoint pos = GetPosition( );
        RealSize size = GetSize( );
        pos.x += x;
        pos.y += y;
        //std::cout << m_string << " (" << pos.x << "," << pos.y << ")  point " << point << "\n";

        DrawLabel( dc, id, pos, size, wxALIGN_CENTER );
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
            if ( m_FontNdx.IsOk( ) && !GetAlbum( )->IsDefaultFont( AT_TitleFontType, m_FontNdx.Get( ) ) )
            {
                GetFontList( )->SaveFont( fonts, m_FontNdx, m_fontType );
            }
        }
    }

    int LabelFrame::SetFont( wxFont newFont, wxColour newColor )
    {
        int ndx = GetFontList( )->AddNewFont( newFont, newColor );
        //m_FontNdx = GetFontList( )->GetFont( ndx );
        //std::cout << "LabelFrame::SetFont " << m_FontNdx->GetNativeInfoStr( ) << "\n";
        return ndx;
    };

    void LabelFrame::UpdateString( double width )
    {
        m_multiLineString = m_string;
        m_maxWidth = width;

        wxFont font = GetFont( );
        int point = font.GetPointSize( );
        if ( font == wxNullFont )
        {
            font = *wxNORMAL_FONT;
        }


        //   GetAlbumImagePanel( )->MakeMultiLine( m_multiLineString, font, width );
        // first break into lines if necessary then get the actual multi line text extent
        m_stringTextExtent = GetAlbumImagePanel( )->MakeMultiLine( m_multiLineString, font, width );
        // std::cout << m_string << "  " << width << "  x:" << m_stringTextExtent.x << " y" << m_stringTextExtent.y << "\n";
        SetWidth( m_maxWidth );
        SetHeight( m_stringTextExtent.y );
        SetMinWidth( m_maxWidth );
        SetMinHeight( m_stringTextExtent.y );
        SetXPos( 0 );
        SetYPos( 0 );
    };
}
