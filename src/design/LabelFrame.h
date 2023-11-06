/**
 * @file design/LabelFrame.h
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

#ifndef LabelFrame_H
#define LabelFrame_H

#include <wx/string.h>
#include <wx/pdfdocument.h>

#include "Defs.h"
#include "design/Frame.h"
 //#include "utils/FontNdx.h"
#include "gui/AlbumImagePanel.h"
#include "utils/Font.h"

namespace Design {


    /**
     * @brief
     *
     */
    class LabelFrame : public Frame
    {

    private:

        LabelFrame( ) {
            m_FontNdx = -1;
        };

    public:

        LabelFrame( Design::FontUsageType fontType ) : Frame( )
        {
            m_fontType = fontType;
            m_FontNdx = -1;
        };

        ~LabelFrame( ) { };

        void Draw( wxDC& dc, double x, double y );

        void DrawPDF( wxPdfDocument* doc, double x, double y );

        wxColour GetColor( );

        wxFont GetFont( );

        int GetFontNdx( ) {
            return m_FontNdx;
        };

        wxString GetString( ) {
            return m_string;
        };

        Design::FontUsageType GetStringType( ) {
            return m_fontType;
        };

        void LoadFont( wxXmlNode* node );

        /// @brief resets the Font to the default Font
//        void MakeDefaultFont( ) { m_FontNdx.MakeDefault( ); };

        void SaveFont( wxXmlNode* node );

        int SetFont( wxFont newFont, wxColour newColor );

        void SetFontNdx( int ndx );

        void SetString( wxString str ) {
            m_string = str;
        };

        // calculate the string frame based on the available width and the text length
        void UpdateString( double width );
    private:

        wxString m_string;

        wxString m_multiLineString;

        wxSize m_stringTextExtent;

        FontUsageType m_fontType;

        int m_FontNdx;

        double m_maxWidth;

    };

}
#endif