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

#include <iostream>
#include <wx/pen.h>

#include "utils/FontList.h"
#include "design/AlbumVolume.h"
#include "design/Album.h"
#include "utils/XMLUtilities.h"
#include "utils/Settings.h"
#include "gui/GuiUtils.h"

namespace Utils {

    int FontCount = -1;
    int GetFontCount( ) { FontCount++; return FontCount; };

    void FontList::InitFonts( )
    {
        wxFont font;
        wxColour color;

        font = GetSettings( )->GetNbrFont( );
        color = GetSettings( )->GetNbrColor( );
        int ndx = AddNewFont( font, color );
        GetSettings( )->SetFontNdxPreference( Design::AT_NbrFontType, ndx );

        font = GetSettings( )->GetTextFont( );
        color = GetSettings( )->GetTextColor( );
        ndx = AddNewFont( font, color );
        GetSettings( )->SetFontNdxPreference( Design::AT_TextFontType, ndx );

        font = GetSettings( )->GetTitleFont( );
        color = GetSettings( )->GetTitleColor( );
        ndx = AddNewFont( font, color );
        GetSettings( )->SetFontNdxPreference( Design::AT_TitleFontType, ndx );

        font = GetSettings( )->GetNameFont( );
        color = GetSettings( )->GetNameColor( );
        ndx = AddNewFont( font, color );
        GetSettings( )->SetFontNdxPreference( Design::AT_NameFontType, ndx );

    }

    Design::FontUsageType FontList::Load( wxXmlNode* fontNode, wxString nativeString, wxString color )
    {
        wxString name = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_FontType ] );
        Design::FontUsageType type = Design::FindFontUsageType( name );

        nativeString = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_NativeFontString ] );
        color = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_FontColor ] );

        return type;
    }

    bool FontList::IsValidFontNdx( int ndx )
    {
        if ( m_fontMap.find( ndx ) == m_fontMap.end( ) )
        {
            return false;
        }
        return true;
    }

    wxFont FontList::GetFont( int ndx )
    {
        if ( IsValidFontNdx( ndx ) )
        {
            return GetMyFont( ndx )->GetFont( );
        }
        return wxNullFont;
    };

    wxColour FontList::GetColor( int ndx )
    {
        if ( IsValidFontNdx( ndx ) )
        {
            return GetMyFont( ndx )->GetColor( );
        }
        return *wxBLACK;
    };

    int FontList::AddNewFont( wxFont newFont, wxColour newColor )
    {
        wxFont font = newFont;
        if ( !font.IsOk( ) )
        {
            //delete font;
            font = wxFont( *wxNORMAL_FONT );
        }
        Font* info = new Font( font, newColor );
        int ndx = FindFont( info );
        if ( IsValidFontNdx( ndx ) )
        {
            delete info;
            return ndx;
        }
        else
        {
            ndx = GetFontCount( );
            m_fontMap.insert( std::make_pair( ndx, info ) );
            return ndx;
        }
    }


    int FontList::FindFont( Font* info )
    {
        FontMap::iterator itr = FindFontIterator( info->GetFont( ), info->GetColor( ) );
        if ( itr != m_fontMap.end( ) )
        {
            return itr->first;
        }
        else
        {
            return -1;
        }
    }

    FontMap::iterator FontList::FindFontIterator( wxFont font, wxColor color )
    {
        FontMap::iterator itr;

        for ( itr = m_fontMap.begin( );
            itr != m_fontMap.end( ); itr++ )
        {
            if ( font == itr->second->GetFont( ) &&
                color == itr->second->GetColor( ) )
            {
                return itr;
            }
        }
        return m_fontMap.end( );
    };


    void FontList::DumpFonts( )
    {
        FontMap::iterator itr;

        for ( itr = m_fontMap.begin( );
            itr != m_fontMap.end( ); itr++ )
        {
            int key = itr->first;
            wxFont font = itr->second->GetFont( );
            wxColour color = itr->second->GetColor( );
            int count = itr->second->Count( );
        }

    };


    Font* FontList::GetMyFont( int ndx )
    {
        FontMap::iterator itr = m_fontMap.find( ndx );
        if ( itr != m_fontMap.end( ) )
        {
            return itr->second;
        }
        return ( Font* ) 0;
    }

    Font* FontList::GetMyFont( FontMap::iterator itr )
    {
        return itr->second;
    }

    Font* FontList::FindMyFont( wxFont font, wxColor color )
    {
        FontMap::iterator itr = FindFontIterator( font, color );
        if ( itr != m_fontMap.end( ) )
        {
            return itr->second;
        }

        return ( Font* ) 0;
    };

    int FontList::LoadFont( wxXmlNode* parent, Design::FontUsageType type )
    {
        int fontNdx;
        wxXmlNode* fontNode = FindFirstChildWithPropertyofValue( parent,
            Design::AttrNameStrings[ Design::AT_FontType ],
            Design::FontUsageTypeStrings[ type ] );
        if ( fontNode )
        {
            wxString nativeString = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_NativeFontString ] );
            wxString colorStr = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_FontColor ] );
            wxFont font = wxFont( nativeString );
            wxColour color = wxColour( colorStr );
            if ( font.IsOk( ) && color.IsOk( ) )
            {
                fontNdx = AddNewFont( font, color );

                std::cout << " FontList::LoadFont " << Design::FontUsageTypeStrings[ type ]
                    << " " << fontNdx << "  " << nativeString << "\n";
                return fontNdx;
            }
        }
        fontNdx = -1;
        // GetSettings()->GetFontNdxPreference( type );
        std::cout << " FontList::LoadFont(default) " << Design::FontUsageTypeStrings[ type ]
            << " " << fontNdx << "\n";
        return fontNdx;
    }
    void FontList::SaveFont( wxXmlNode* parent, int ndx, Design::FontUsageType type )
    {
        if ( IsValidFontNdx( ndx ) )
        {
            GetMyFont( ndx )->SaveFont( parent, type );
        }
    };

    int FontList::DefaultFont( int pointSize )
    {
        wxFont font = *wxNORMAL_FONT;
        if ( pointSize < 1 || pointSize > 30 )
        {
            pointSize = 6;
        }
        font.SetPointSize( pointSize );
        wxColour color = *wxBLACK;
        return AddNewFont( font, color );
    }

    void FontList::MakeDefault( int ndx )
    {
        if ( IsValidFontNdx( ndx ) )
        {
            Font* font = GetMyFont( ndx );
            if ( font )
            {
                int cnt = font->Decrement( );
                if ( cnt <= 0 )
                {
                    Erase( ndx );
                }
            }
        }
        ndx = -1;
    }
}