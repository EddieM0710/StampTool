/**
 * @file layout/Frame.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
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


    void Frame::WriteLayout( wxString str )
    {
        std::cout << str << " ( x:"
            << GetXPos( ) << ", y:" << GetYPos( )
            << ", w:" << GetWidth( ) << ", h:" << GetHeight( )
            << ", minW:" << GetMinWidth( ) << ", minH:" << GetMinHeight( ) << " )\n";
    };
}
