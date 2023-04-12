/**
 * @file DisplayString.cpp
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

#include "design/DisplayString.h"
#include "gui/GuiUtils.h"

namespace Design {

    wxFont DisplayString::GetFont( ) { return m_parent->GetFont( m_fontType ); };

    void DisplayString::GetString( )
    {
        if ( m_fontType == AT_TextFontType )
        {
            m_string = m_parent->GetText( );
        }
        else if ( m_fontType == AT_TitleFontType )
        {
            m_string = m_parent->GetAttrStr( AT_Name );
        }
        else if ( m_fontType == AT_NameFontType )
        {
            m_string = m_parent->GetAttrStr( AT_Name );
        }
        else if ( m_fontType == AT_NbrFontType )
        {
            m_string = m_parent->GetAttrStr( AT_CatNbr );
        }
    };



    void DisplayString::drawPDF( wxPdfDocument* doc, double x, double y )
    {
        //         wxString id;
        //         wxFont font( *m_font );

        //         id = m_string;
        //         id.Trim( );
        //         id.Trim( false );
        //         GetAlbumImagePanel( )->MakeMultiLine( id, font, GetWidth( ) );
        //         //font.SetPointSize( 6 );
        //         //dc.SetFont( font );
        // //        doc->Write( id, m_stringRect, wxALIGN_CENTER_HORIZONTAL );            
    };

    void DisplayString::Draw( wxDC& dc, double x, double y )
    {
        wxString id = m_multiLineString;
        wxFont font( GetFont( ) );
        int pointSize = font.GetPointSize( );


        dc.SetFont( font );
        RealPoint pos = GetPosition( );
        RealSize size = GetSize( );
        pos.x += x;
        pos.y += y;
        DrawLabel( dc, id, pos, size, wxALIGN_CENTER );
    };

    void DisplayString::UpdateString( double width )
    {
        m_maxWidth = width;
        GetString( );
        wxFont font = GetFont( );
        m_multiLineString = m_string;

        // first break into lines if necessary
        GetAlbumImagePanel( )->MakeMultiLine( m_multiLineString, font, width );
        // then get the actual multi line text extent
        m_stringTextExtent = GetAlbumImagePanel( )->GetLogicalTextExtent( m_multiLineString, font );
        SetWidth( m_maxWidth );
        SetHeight( m_stringTextExtent.y );
        SetMinWidth( m_maxWidth );
        SetMinHeight( m_stringTextExtent.y );
        SetXPos( 0 );
        SetYPos( 0 );
    };
}