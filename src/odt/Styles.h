/* 
 * @file Styles.h
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
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
 */
#ifndef Styles_h
#define Styles_h


#include "odt/ODTDefs.h"
#include <wx/xml/xml.h>

namespace ODT {

    class Styles
    {
    public:

        Styles( );
        ~Styles( ) {};

        wxXmlNode* FindOfficeStyles( );

        /**
         * @brief Reads the template styles.xml document
         * and returns the wxXmlDocument pointer for it, All
         * new styles needed by the Album ODT will be added to it.
         *
         * @return wxXmlDocument*
         **************************************************/
        wxXmlDocument* GetStyles( );

        /**
         * @brief Add the necessary styles to the styles doc
         *
         * @param filename - Path of border image
         * @return true
         * @return false
         **************************************************/
        bool AddBorderStyle( wxString filename, wxString& width,
            wxString& height,
            wxString& topMargin,
            wxString& bottomMargin,
            wxString& rightMargin,
            wxString& leftMargin );

        /**
         * @brief Finds the wxXmlNode of the office:automatic-styles in the content
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* FindAutomaticStylesLayoutProperties( );

        /**
         * @brief Finds the wxXmlNode of the office:styles with draw:name of "bkgnd" in the content
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* FindOfficeStylesDrawFillImage( );

        /**
         * @brief Adds the necessary styles to office:styles
         *
         * @return true
         * @return false
         **************************************************/
        bool AddFrameStyles( );

        bool Save( );

        wxXmlDocument* StylesXML( ) { return m_styles; };

    private:
        wxXmlDocument* m_styles;

    };
}
#endif
