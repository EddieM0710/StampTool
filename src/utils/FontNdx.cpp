/**
 * @file FontNdx.cpp
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

 //#include <iostream>
 //#include <wx/pen.h>

//#include "utils/FontNdx.h"
#include "utils/FontList.h"
// #include "design/AlbumVolume.h"
// #include "utils/XMLUtilities.h"
// #include "utils/Settings.h"
// #include "gui/GuiUtils.h"


#include "utils/Font.h"


namespace Utils {

    // int FontCount = -1;
    // int GetFontCount( ) { FontCount++; return FontCount; };

     // int FontList::FindFont( FontMap& list, wxFont* font, wxColor color )
     // { 
     //     for ( int i = 0; i < list.size( ); i++ )
     //     { 
     //         if ( ( *font == *( list.at( i )->GetFont( ) ) )
     //             && ( color == list.at( i )->GetColor( ) ) )
     //             return i;
     //     }
     //     return -1;
     // }

    FontNdx::FontNdx( )
    {
        m_fontList = GetFontList( );
        m_ndx = -1;
    }

    int FontNdx::Get( )
    {
        return m_ndx;
    };

    void FontNdx::Set( int ndx )
    {
        if ( m_fontList->IsValidFontNdx( ndx ) )
        {
            Font* font;
            if ( IsOk( ) )
            {
                font = m_fontList->GetMyFont( m_ndx );
                if ( ndx != m_ndx )
                {
                    if ( m_fontList->IsValidFontNdx( m_ndx ) )
                    {
                        int cnt = font->Decrement( );
                        if ( cnt <= 0 )
                        {
                            m_fontList->Erase( m_ndx );
                        }
                    }
                    m_ndx = ndx;
                }
                else
                {
                    int cnt = font->Increment( );
                }
            }
            else
            {
                m_ndx = ndx;
                font = m_fontList->GetMyFont( m_ndx );
                int cnt = font->Increment( );
            }
        }
        //        std::cout << "FontNdx::Set  ndx:" << m_ndx << " " << GetFont( )->GetNativeInfoStr( ) << "\n";
    }
    Utils::Font* FontNdx::GetFont( )
    {
        return m_fontList->GetMyFont( m_ndx );
    };

    void FontNdx::MakeDefault( )
    {
        if ( m_fontList->IsValidFontNdx( m_ndx ) )
        {
            Font* font = m_fontList->GetMyFont( m_ndx );
            if ( font )
            {
                int cnt = font->Decrement( );
                if ( cnt <= 0 )
                {
                    m_fontList->Erase( m_ndx );
                }
            }
        }
        m_ndx = -1;
    }
}