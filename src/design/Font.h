/**
 * @file layout/Font.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#ifndef Font_H
#define Font_H

#include "design/DesignDefs.h"
#include "design/XMLBase.h"
#include <wx/font.h>
#include <wx/colour.h>
#include "design/FontInfo.h"



namespace Design {


    /**
     * @brief Font layout object; In
     *
     **************************************************/
    class Font: public XMLBase
    {
    public:

        // font frame constructor
        /**
         * @brief Construct a new Font frame object.
         *
         * @param parent
         **************************************************/
        Font( wxXmlNode* node )
        {
            SetNodeType( AlbumBaseType::AT_Font );
            m_fontNdx = -1;
            SetAttrStr( AT_FontType, AT_FontUsageTypeStrings[ AT_UnspecifiedFontType ] );
            // m_family = (AT_FontFamilyType)UnknownFontVal;
            // m_face.Clear();
            // m_size = 0;
            // m_weight = (AT_FontWeightType)UnknownFontVal;
            // m_color = wxNullColour;
            // m_style = (AT_FontStyleType)UnknownFontVal;
        };

        void SetNativeFontString( wxString nativeFontString );

        wxFont* GetFont( );
        wxString GetNativeFontString( );

        void SetFamily( wxString nativeFontString );
        void SetFamily( AT_FontFamilyType type );
        wxString GetFamilyString( );

        /**
         * @brief Destroy the Font object
         *
         **************************************************/
        ~Font( ) {};



        // build the frame container for the font

        void Save( wxXmlNode* xmlNode );



        void Init( );


    private:
        // index of font in FontList
        int m_fontNdx;
        // title or CatNbr font
        // AT_FontUsageType m_type;
        // wxString m_nativeFontInfoDesc;
        // AT_FontFamilyType m_family;
        // wxString m_face;
        // int m_size;
        // AT_FontWeightType m_weight;
        // wxColor m_color;
        // AT_FontStyleType m_style;
    };
}

#endif
