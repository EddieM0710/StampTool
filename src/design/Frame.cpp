/**
 * @file layout/Frame.cpp
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


#include "gui/AlbumImagePanel.h"
#include "design/Frame.h"
#include "gui/GuiUtils.h"
#include <wx/math.h> 
#define LOOP 0
namespace Design {

    //----------------

    Frame::Frame( )
    {
        Init( );
    };

    //----------------

    Frame::~Frame( )
    {
    };

    //----------------

    void Frame::Init( double x, double y, double w, double h, double mw, double  mh )
    {
        m_xPos = x;
        m_yPos = y;
        m_width = w;
        m_height = h;
        m_minWidth = mw;
        m_minHeight = mh;
    }

    //----------------

    void Frame::Draw( wxDC& dc, double x, double y )
    {
        DrawRectangle( dc, x + GetXPos( ), y + GetYPos( ), GetWidth( ), GetHeight( ) );
    };

    //----------------

    void Frame::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        DrawRectanglePDF( doc, x + GetXPos( ), y + GetYPos( ), GetWidth( ), GetHeight( ) );
    };

    //----------------

    double Frame::GetHeight( ) {
        return m_height;
    };

    //----------------

    double Frame::GetMinWidth( ) {
        return m_minWidth;
    };

    //----------------

    double Frame::GetMinHeight( ) {
        return m_minHeight;
    };

    //----------------

    double Frame::GetXPos( ) {
        return m_xPos;
    };

    //----------------

    double Frame::GetYPos( ) {
        return m_yPos;
    };

    //----------------

    double Frame::GetWidth( ) {
        return m_width;
    };

    //----------------

    void Frame::SetHeight( double val )
    {
        m_height = val;
    };

    //----------------

    void Frame::SetMinHeight( double val )
    {
        m_minHeight = val;
    };

    //----------------

    void Frame::SetMinWidth( double val )
    {
        m_minWidth = val;
    };

    //----------------

    void Frame::SetXPos( double val )
    {
        m_xPos = val;
    };

    //----------------

    void Frame::SetYPos( double val )
    {
        m_yPos = val;
    };

    //----------------

    void Frame::SetWidth( double val )
    {
        m_width = val;
    };

    //----------------

    wxString Frame::DumpPos( )
    {
        wxString str = wxString::Format( "   pos( %.1f, %.1f)",
            m_xPos, m_yPos );
        return str;
    }

    //----------------

    wxString Frame::DumpSize( )
    {
        wxString str = wxString::Format( "   size( %.1f, %.1f)",
            m_width, m_height );
        return str;
    }

    //----------------

    wxString Frame::DumpMinSize( )
    {
        wxString str = wxString::Format( "   minSize( %.1f, %.1f)",
            m_minWidth, m_minHeight );
        return str;
    }

    //----------------

    wxString Frame::ReportLayout( wxString prefix )
    {
        wxString str = Layout( );;
        std::cout << prefix << str;
        return str;
    }

    //----------------

    wxString Frame::Layout( )
    {
        wxString str = DumpPos( ) + DumpSize( ) + DumpMinSize( );
        return str;
    }

    //----------------

    void Frame::CheckLayout( wxString prefix )
    {

        if ( ( GetXPos( ) < 0 ) || ( GetYPos( ) < 0 ) )
        {
            std::cout << prefix << " invalid position" << DumpPos( ) << "\n";
        }
        if ( ( GetWidth( ) < 0 ) || ( GetHeight( ) < 0 ) )
        {
            std::cout << prefix << " invalid Size" << DumpSize( ) << "\n";
        }
        if ( ( GetMinHeight( ) < 0 ) || ( GetMinWidth( ) < 0 ) )
        {
            std::cout << prefix << " invalid Height/width" << DumpMinSize( ) << "\n";
        }
    };

    //----------------

}
