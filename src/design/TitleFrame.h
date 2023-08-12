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

#ifndef Title_H
#define Title_H

#include <wx/string.h>
#include <wx/pdfdocument.h>

#include "Defs.h"
#include "design/DesignDefs.h"

#include "design/LabelFrame.h"


namespace Design
{

    class TitleFrame : public Frame
    {
    public:
        TitleFrame( LayoutBase* parent );

        ~TitleFrame( );

        void Draw( wxDC& dc, double x, double y );

        void DrawPDF( wxPdfDocument* doc, double x, double y );

        wxString GetHeadingString( );
        wxString GetSubHeadingString( );

        void SetHeadingString( wxString str );
        void SetSubHeadingString( wxString str );

        void UpdateString( double titleWidth, double subTitleWidth = 0 );

        bool GetShowHeading( ) { return m_parent->GetShowTitle( ); };
        bool GetShowSubHeading( ) { return m_parent->GetShowSubTitle( ); };

        void LoadFonts( wxXmlNode* node );
        void SaveFonts( wxXmlNode* parent );

        wxColour GetHeadingColor( ) { return m_headingFrame->GetColor( ); };
        wxColour GetSubHeadingColor( ) { return m_subHeadingFrame->GetColor( ); };
        void SetHeadingFont( wxFont newFont, wxColour newColor ) { m_headingFrame->SetFont( newFont, newColor ); };
        void SetSubHeadingFont( wxFont newFont, wxColour newColor ) {
            //std::cout << "TitleFrame::SetSubHeadingFont " << newFont.GetNativeFontInfoDesc( ) << "\n";
            m_subHeadingFrame->SetFont( newFont, newColor );
        };

        wxFont GetHeadingFont( ) { return m_headingFrame->GetFont( ); };
        wxFont GetSubHeadingFont( ) { return m_subHeadingFrame->GetFont( ); };

        int GetHeadingFontNdx( ) { return m_headingFrame->GetFontNdx( ); };
        int GetSubHeadingFontNdx( ) { return m_subHeadingFrame->GetFontNdx( ); };

        Design::LabelFrame* GetHeadingFrame( ) { return m_headingFrame; };
        Design::LabelFrame* GetSubHeadingFrame( ) { return m_subHeadingFrame; };

    private:
        LayoutBase* m_parent;

        Design::LabelFrame* m_headingFrame;
        Design::LabelFrame* m_subHeadingFrame;
    };
}

#endif