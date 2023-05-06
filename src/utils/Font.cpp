/**
 * @file Font.cpp
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
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "utils/Font.h"
#include "utils/XMLUtilities.h"


namespace Utils {

    Font::Font( )
    {
        m_count = 0;
    };

    Font::Font( wxFont font, wxString colorStr )
    {
        m_font = font;
        m_color = wxTheColourDatabase->Find( colorStr );
        m_count = 0;
    };

    Font::Font( wxFont font, wxColor color )
    {
        m_font = font;
        m_color = color;
        m_count = 0;
    };
    /**
     * @brief Destroy the Font object
     *
     */
    Font::~Font( ) { };



    // build the frame container for the font

//       void Write( wxXmlNode* xmlNode );

    wxFont Font::GetFont( )
    {
        return m_font;
    };


    void Font::SetFont( wxFont font )
    {
        m_font = font;
    };

    wxColor Font::GetColor( )
    {
        return m_color;
    };

    void Font::SetColor( wxColor color )
    {
        m_color = color;
    };

    void Font::SetColor( wxString colorStr )
    {
        m_color = wxTheColourDatabase->Find( colorStr );
    };

    // Design::FontFamilyType Font::GetFamily( )
    // {
    //     return  Design::GetFamily( m_font.GetFamily( ) );
    // };

    wxString Font::GetNativeInfoStr( )
    {
        return m_font.GetNativeFontInfoDesc( );
    };

    // Design::FontWeightType Font::GetWeight( )
    // {
    //     return  Design::GetATWeight( m_font.GetWeight( ) );
    // };

    int Font::GetPointSize( )
    {
        return m_font.GetPointSize( );
    };

    // wxString Font::GetFaceName( )
    // {
    //     return m_font.GetFaceName( );
    // };

    // wxString Font::GetFamilyName( )
    // {
    //     return m_font.GetFamilyString( );
    // };

    // Design::FontStyleType Font::GetStyle( )
    // {
    //     return  Design::GetStyle( m_font.GetStyle( ) );
    // };

    bool Font::IsEqual( wxFont font, wxColor color )
    {
        if ( IsFontEqual( font ) &&
            IsColorEqual( color ) )
        {
            return true;
        }
        return false;
    }
    bool Font::IsFontEqual( wxFont font )
    {
        if ( m_font == font )
        {
            return true;
        }
        return false;
    }

    bool Font::IsColorEqual( wxColor color )
    {
        if ( m_color == color )
        {
            return true;
        }
        return false;
    };
    int Font::Increment( )
    {
        m_count++;
        return m_count;
    }
    int Font::Decrement( )
    {
        m_count--;
        return m_count;
    }

    void Font::SaveFont( wxXmlNode* parent, Design::FontUsageType type )
    {
        wxXmlNode* child = Utils::NewNode( parent, Design::AlbumBaseNames[ Design::AT_Font ] );
        if ( child )
        {
            child->AddAttribute( Design::AttrNameStrings[ Design::AT_FontType ],
                Design::FontUsageTypeStrings[ type ] );
            child->AddAttribute( Design::AttrNameStrings[ Design::AT_NativeFontString ],
                m_font.GetNativeFontInfoDesc( ) );
            child->AddAttribute( Design::AttrNameStrings[ Design::AT_FontColor ],
                m_color.GetAsString( ) );
        }
    }

}
