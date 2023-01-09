/**
 * @file layout/Frame.cpp
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


#include "gui/AlbumImagePanel.h"
#include "design/Frame.h"
#include "gui/GuiUtils.h"

namespace Design {

    Frame::Frame( )
    {
        m_xPos = 0;
        m_yPos = 0;
        m_width = 0;
        m_height = 0;
        m_minWidth = 0;
        m_minHeight = 0;
    };
    Frame::~Frame( ) {};

    double Frame::GetXPos( ) { return m_xPos; };
    void Frame::SetXPos( double val ) { m_xPos = val; };
    double Frame::GetYPos( ) { return m_yPos; };
    void Frame::SetYPos( double val ) { m_yPos = val; };
    double Frame::GetWidth( ) { return m_width; };
    void Frame::SetWidth( double val ) { m_width = val; };
    double Frame::GetHeight( ) { return m_height; };
    void Frame::SetHeight( double val ) { m_height = val; };
    double Frame::GetMinWidth( ) { return m_minWidth; };
    void Frame::SetMinWidth( double val ) { m_minWidth = val; };
    double Frame::GetMinHeight( ) { return m_minHeight; };
    void Frame::SetMinHeight( double val ) { m_minHeight = val; };

    /*
     * @brief draw object on screen
     *
     * @param dc current device context
     * @param x position in MM
     * @param y position in MM
     */
    void Frame::draw( wxDC& dc, double x, double y )
    {
        DrawRectangle( dc, x + GetXPos( ), y + GetYPos( ), GetWidth( ), GetHeight( ) );
    };

    wxString Frame::ReportLayout( wxString indent )
    { 
        wxString str = wxString::Format( "%sFrame  xPos:%7.2f  yPos:%7.2f     width:%7.2f  height:%7.2f\n",
        indent, GetXPos( ), GetYPos( ),  GetWidth( ), GetHeight( ));
        std::cout << str;
        return str ;
    }

    void Frame::WriteLayout( wxString str )
    {
        std::cout << str << " Pos("
            << GetXPos( ) << ", " << GetYPos( )
            << ") , Size(" << GetWidth( ) << ", " << GetHeight( )
            << "), MinSize(" << GetMinWidth( ) << "," << GetMinHeight( ) << ")\n";
 
        if ((GetXPos()< 0)||(GetYPos()< 0))
        {
            std::cout << "invalid position\n";
        }
        if ((GetWidth()< 0)||(GetHeight()< 0))
        {
            std::cout << "invalid Size\n";
        }
        if ((GetMinHeight()< 0)||(GetMinWidth()< 0))
        {
            std::cout << "invalid Height/width\n";
        }
    };
}
