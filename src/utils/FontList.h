/**
 * @file layout/Font.h
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

#ifndef MyFont_H
#define MyFont_H

#include "design/DesignDefs.h"
#include "design/XMLBase.h"
#include "utils/Font.h"
 //#include "utils/FontNdx.h"

  //#include <vector>

namespace Utils {

    // int FindFont( FontMap& list, wxFont font, wxColor color );

    class FontList
    {
    public:

        FontList( )
        {
            m_fontMap.rehash( 10 );
        };

        ~FontList( ) {};

        int AddNewFont( wxFont font, wxColour color );

        void Clear( ){
            m_fontMap.clear( );
        };

        int DefaultFont( int pointSize );

        Font* FindMyFont( wxFont font, wxColor color );

        FontMap::iterator FindFontIterator( wxFont font, wxColor color );

        int FindFont( wxFont font, wxColor color );

        int FindFont( Font* info );

        wxFont GetFont( int ndx );

        int GetFontCount( );

        wxColour GetColor( int ndx );

        void InitFonts( );

        bool IsValidFontNdx( int ndx );

        //bool IsValidFontNdx( int ndx ) { return IsValidFontNdx( ndx.Get( ) ); };

        Font* GetMyFont( int ndx );

        Font* GetMyFont( FontMap::iterator itr );

        FontMap& GetFontMap( )
        {
            return m_fontMap;
        }

        Design::FontUsageType Load( wxXmlNode* fontNode, wxString nativeString, wxString color );

        std::size_t Erase( int ndx )
        {
            return m_fontMap.erase( ndx );
        };

        int LoadFont( wxXmlNode* parent, Design::FontUsageType type );

        void MakeDefault( int ndx );

        void SaveFont( wxXmlNode* parent, int ndx, Design::FontUsageType type );

    private:
        FontMap m_fontMap;
    };

}

#endif
