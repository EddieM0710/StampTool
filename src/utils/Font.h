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

#ifndef Font_H
#define Font_H

#include <wx/font.h>
#include <wx/colour.h>
#include "design/DesignDefs.h"

#include <unordered_map>

class wxXmlNode;


namespace Utils {


    /**
        * @brief Font layout object; In
        *
        */
    class Font
    {
    public:


        // Font frame constructor
        /**
         * @brief Construct a new Font frame object.
         *
         * @param parent
         */
        Font( );

        Font( wxFont font, wxString colorStr );

        Font( wxFont font, wxColor color );
        /**
         * @brief Destroy the Font object
         *
         */
        ~Font( );



        // build the frame container for the font

 //       void Write( wxXmlNode* xmlNode );

        wxFont GetFont( );


        void SetFont( wxFont font );

        wxColor GetColor( );

        void SetColor( wxColor color );

        void SetColor( wxString colorStr );

        //        Design::FontFamilyType GetFamily( );

        wxString GetNativeInfoStr( );

        //        Design::FontWeightType GetWeight( );

        int GetPointSize( );

        // wxString GetFaceName( );

        // wxString GetFamilyName( );

        // Design::FontStyleType GetStyle( );

        bool IsEqual( wxFont font, wxColor color );

        bool IsFontEqual( wxFont font );

        bool IsColorEqual( wxColor color );
        int Increment( );
        int Decrement( );

        void SaveFont( wxXmlNode* parent, Design::FontUsageType type );

        int Count( ) { return m_count; };



    private:

        wxFont m_font;
        wxColor m_color;
        int m_count;

    };


    typedef std::unordered_map< int, Font* > FontMap;

}

#endif
