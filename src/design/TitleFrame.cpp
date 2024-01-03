/**
 * @file LabelFrame.cpp
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

#include "design/TitleFrame.h"
#include "design/LayoutBase.h"
#include "design/Album.h"
#include "utils/FontList.h"

#include "gui/GuiUtils.h"


namespace Design {

    TitleFrame::TitleFrame( LayoutBase* parent )
    {
        m_parent = parent;
        m_headingFrame = new Design::LabelFrame( Design::AT_TitleFontType );
        m_subHeadingFrame = new Design::LabelFrame( Design::AT_SubTitleFontType );
    };

    TitleFrame::~TitleFrame( )
    {
        delete m_headingFrame;
        delete m_subHeadingFrame;
    };

    void TitleFrame::Draw( wxDC& dc, double x, double y )
    {
        m_headingFrame->Draw( dc, x + GetXPos( ), y + GetYPos( ) );
        if ( m_parent->GetShowSubTitle( ) )
        {
            m_subHeadingFrame->Draw( dc, x + GetXPos( ), y + GetYPos( ) );
        }
    };

    void TitleFrame::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        m_headingFrame->DrawPDF( doc, x + GetXPos( ), y + GetYPos( ) );
        if ( m_parent->GetShowSubTitle( ) )
        {
            m_subHeadingFrame->DrawPDF( doc, x + GetXPos( ), y + GetYPos( ) );
        }
    };

    void TitleFrame::LoadFonts( wxXmlNode* node )
    {
        m_headingFrame->LoadFont( node );
        m_subHeadingFrame->LoadFont( node );
    }

    void TitleFrame::SaveFonts( wxXmlNode* parent )
    {
        int headingNdx = m_headingFrame->GetFontNdx( );
        int subHeadingNdx = m_headingFrame->GetFontNdx( );
        if ( ( headingNdx >= 0 ) || ( subHeadingNdx >= 0 ) )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                if ( headingNdx >= 0 )
                    m_headingFrame->SaveFont( fonts );
                if ( subHeadingNdx >= 0 )
                    m_subHeadingFrame->SaveFont( fonts );
            }
        }
    }


    wxString TitleFrame::GetHeadingString( )
    {
        return m_headingFrame->GetString( );
    };

    wxString TitleFrame::GetSubHeadingString( )
    {
        return m_subHeadingFrame->GetString( );
    };


    void TitleFrame::SetHeadingString( wxString str )
    {
        m_headingFrame->SetString( str );
    };

    void TitleFrame::SetSubHeadingString( wxString str )
    {
        m_subHeadingFrame->SetString( str );
    };

    void TitleFrame::UpdateString( double titleWidth, double subTitleWidth )
    {
        if ( m_parent->GetShowTitle( ) )
        {
            m_headingFrame->UpdateString( titleWidth );

            if ( m_parent->GetShowSubTitle( ) )
            {
                m_subHeadingFrame->UpdateString( subTitleWidth );
            }
            else
            {
                m_subHeadingFrame->Init( );
            }

            // set 2 * subHeading height to allow for spacing between title and subtitle
            SetMinHeight( m_headingFrame->GetMinHeight( )
                + 2 + m_subHeadingFrame->GetMinHeight( ) );
            SetMinWidth( std::max( titleWidth, subTitleWidth ) );

            SetHeight( GetMinHeight( ) );
            SetWidth( GetMinWidth( ) );

            SetXPos( m_headingFrame->GetXPos( ) );
            SetYPos( m_headingFrame->GetYPos( ) );

            if ( m_subHeadingFrame->GetHeight( ) > 0 )
            {
                m_subHeadingFrame->SetYPos( m_headingFrame->GetHeight( )
                    + 2 );//m_subHeadingFrame->GetMinHeight( ) ); //allow for space between title and subtitle
            }
        }
    };
}
