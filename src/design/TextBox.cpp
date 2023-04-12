/**
 * @file Text.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright ( c ) 2022
 *
 * This file is part of Sta@mpTool.
 *
 * Sta@mpTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * Sta@mpTool is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Sta@mpTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#include "Defs.h"

#include "design/TextBox.h"
 //include "design/Title.h"
#include "design/Album.h"

#include "utils/XMLUtilities.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/AlbumImagePanel.h"
#include "gui/StampDescriptionPanel.h"
#include "gui/GuiUtils.h"


#include "art/NotFound.xpm"

namespace Design {


    const double BorderAllowancePercent = .2;
    const double ImagePercentOfActual = .75;

    void TextBox::CalcFrame( )
    {

        SetMinHeight( GetHeight( ) );
        SetMinWidth( GetWidth( ) );

        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;
        if ( GetShowFrame( ) )
        {
            leftPadding = GetLeftContentPadding( );
            rightPadding = GetRightContentPadding( );
            topPadding = GetTopContentPadding( );
            bottomPadding = GetBottomContentPadding( );
        }
        double contentWidth = GetWidth( ) - leftPadding - rightPadding;

        GetTitleFrame( )->UpdateString( contentWidth );

        GetTextFrame( )->UpdateString( contentWidth );

        if ( IsTitleLocation( AT_TitleLocationBottom ) )
        {
            m_textFrame.SetXPos( ( GetWidth( ) - m_textFrame.GetWidth( ) ) / 2 );
            m_textFrame.SetYPos( topPadding );
            GetTitleFrame( )->SetXPos( ( GetWidth( ) - GetTitleFrame( )->GetWidth( ) ) / 2 );
            GetTitleFrame( )->SetYPos( GetHeight( ) - bottomPadding - GetTitleFrame( )->GetHeight( ) );
        }
        else
        {
            GetTitleFrame( )->SetXPos( ( GetWidth( ) - GetTitleFrame( )->GetWidth( ) ) / 2 );
            GetTitleFrame( )->SetYPos( topPadding );
            GetTextFrame( )->SetXPos( ( GetWidth( ) - GetTextFrame( )->GetWidth( ) ) / 2 );
            GetTextFrame( )->SetYPos( GetTitleFrame( )->GetYPos( ) + GetTitleFrame( )->GetHeight( ) );
        }

    }



    bool TextBox::UpdateMinimumSize( )
    {
        CalcFrame( );

        if ( ValidateNode( ) == AT_FATAL )
        {
            return false;
        }
        return true;
    }

    void TextBox::UpdateSizes( )
    {
        //        m_frame.WriteLayout( "Text::UpdateSizes <>" );
    }

    void TextBox::UpdatePositions( )
    {
        //        m_frame.WriteLayout( "Text::UpdatePositions <>" );
    }

    NodeStatus TextBox::ValidateNode( )
    {
        NodeStatus status = AT_OK;
        // wxString str;

        // if ( GetHeight( ) <= 0.01 )
        // {
        //     str = wxString::Format( "Invalid TextBox Height.\n" );
        //     GetErrorArray( )->Add( str );
        //     status = AT_FATAL;
        // }
        // if ( GetWidth( ) <= 0.01 )
        // {
        //     str = wxString::Format( "Invalid TextBox Width.\n" );
        //     GetErrorArray( )->Add( str );
        //     status = AT_FATAL;
        // }
        // m_nodeValid = status;
        return status;
    }

    void TextBox::ClearError( )
    {

    };


    NodeStatus TextBox::GetStatus( )
    {
        NodeStatus status = AT_OK;

        // if ( m_error[ AT_InvalidHeight ] > status )
        // {
        //     status = m_error[ AT_InvalidHeight ];
        //     if ( status == AT_FATAL )
        //         return status;
        // }
        // if ( m_error[ AT_InvalidWidth ] > status )
        // {
        //     status = m_error[ AT_InvalidWidth ];
        //     if ( status == AT_FATAL )
        //         return status;
        // }

        return status;

    };

    void TextBox::DrawPDF( wxPdfDocument* doc, double x, double y )
    {


        //Draw the outer frame transparent
//        m_frame.DrawPDF( doc, x, y );

        //Draw the TextBox frame
        double xPos = x + GetXPos( );
        double yPos = y + GetYPos( );

        m_textFrame.DrawPDF( doc, xPos, yPos );


        RealPoint pos( GetTitleFrame( )->GetXPos( ) + xPos, GetTitleFrame( )->GetYPos( ) + yPos );
        RealSize size( GetTitleFrame( )->GetWidth( ), GetTitleFrame( )->GetHeight( ) );

        //  GetTitleFrame( )->DrawTitlePDF( doc, GetTitle( ), pos, size );


        pos = RealPoint( m_textFrame.GetXPos( ) + xPos, m_textFrame.GetYPos( ) + yPos );
        size = RealSize( m_textFrame.GetWidth( ), m_textFrame.GetHeight( ) );

        DrawTitlePDF( doc, m_text, pos, size );

    }

    void TextBox::Draw( wxDC& dc, double x, double y )
    {


        //Draw the outer frame transparent
    //        dc.SetPen( *wxRED_PEN );
        SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetMinWidth( ), GetMinHeight( ) );
        //        m_frame.Draw( dc, x, y );


        dc.SetPen( *wxBLACK_PEN );

        //Draw the TextBox frame

        m_frame.Draw( dc, x, y );

        double xPos = x + GetXPos( );
        double yPos = y + GetYPos( );

        GetTitleFrame( )->Draw( dc, xPos, yPos );

        GetTextFrame( )->Draw( dc, xPos, yPos + m_textFrame.GetYPos( ) );

    }



    void TextBox::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_Width );
        SetAttribute( xmlNode, AT_Height );
        //   SetAttribute( xmlNode, AT_Link );
        SetAttribute( xmlNode, AT_ShowTitle );
        //   SetAttribute( xmlNode, AT_ImageName );
        SaveFonts( xmlNode );
        xmlNode->SetContent( m_text );
    }

    void TextBox::ReportLayout( )
    {

        std::cout << "Layout for TextBox :";
        ReportLayoutFrame( );
    };

    void TextBox::DumpText( wxTextCtrl* ctrl )
    {
        *ctrl << DumpFrame( );
    }

}