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
 **************************************************/
#include <wx/pen.h>

#include "design/FontInfo.h"
#include "utils/XMLUtilities.h"
#include "utils/Settings.h"
#include "gui/GuiUtils.h"


namespace Design { 

    // int FontList::FindFont( FontArray& list, wxFont* font, wxColor color )
    // { 
    //     for ( int i = 0; i < list.size( ); i++ )
    //     { 
    //         if ( ( *font == *( list.at( i )->GetFont( ) ) )
    //             && ( color == list.at( i )->GetColor( ) ) )
    //             return i;
    //     }
    //     return -1;
    // }

    void FontList::InitFonts( )
    {
        wxString nativeFontString;
        wxString color;
        nativeFontString = GetSettings( )->GetCatNbrFontString( );
        color = GetSettings( )->GetCatNbrColorString( );
        GetSettings( )->SetDefaultCatNbrFontNdx( AddNewFont( nativeFontString, color ) );

        nativeFontString = GetSettings( )->GetTextFontString( );
        color = GetSettings( )->GetTextColorString( );
        GetSettings( )->SetDefaultTextFontNdx( AddNewFont( nativeFontString, color ) );
            
        nativeFontString = GetSettings( )->GetTitleFontString( );
        color = GetSettings( )->GetTitleColorString( );
        GetSettings( )->SetDefaultTitleFontNdx( AddNewFont( nativeFontString, color ) );
    }

    Design::AT_FontUsageType FontList::Load( wxXmlNode* fontNode, wxString nativeString, wxString color )
    {
        wxString name = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_FontType ] );
        Design::AT_FontUsageType type = Design::FindFontUsageType( name );

        nativeString = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_NativeFontString ] );
        color  = fontNode->GetAttribute( Design::AttrNameStrings[ Design::AT_FontColor ] );

        return type;
    }

    int FontList::AddNewFont(  wxString nativeDesc, wxString colorStr )
    { 
        wxFont* font = new wxFont( nativeDesc );
        if ( !font->IsOk( ) )
        { 
            delete font;
            font = new wxFont( *wxNORMAL_FONT );
        }
        FontInfo* info = new FontInfo( );
        info->SetFont( font );
        wxColor color = wxTheColourDatabase->Find( colorStr );
        info->SetColor( color );
        int ndx = FindFont( info );
        if ( IsValidFontNdx( ndx ) )
        { 
            return ndx;
        }
        else
        { 
            m_FontArray.push_back( info );
            return m_FontArray.size( ) - 1;
        }
    }

    
    int FontList::FindFont( FontInfo* info )
    { 
        return FindFont( info->GetFont( ), info->GetColor( ) );
    }

    int FontList::FindFont( wxFont* font, wxColor color )
    { 
        for ( int i = 0; i < m_FontArray.size( ); i++ )
        { 
            if ( ( *font == *( m_FontArray.at( i )->GetFont( ) ) )
                && ( color == m_FontArray.at( i )->GetColor( ) ) )
                return i;
        }
        return -1;
    }


    FontInfo* FontList::GetFontInfo( int index )
    { 
        if ( index < m_FontArray.size( ) )
        { 
            return m_FontArray.at( index );
        }
        return ( FontInfo* )0;
    };

 

    FontInfo* FontList::FindFontInfo( wxFont* font, wxColor color )
    { 
        FontInfo* fontInfo = ( FontInfo* )0;
        for ( int i = 0; i < m_FontArray.size( ); i++ )
        { 
            fontInfo = m_FontArray.at( i );
            if ( fontInfo->IsEqual( font, color ) )
            { 
                return fontInfo;
            }
        }
        return fontInfo;
    };

}