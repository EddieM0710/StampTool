/**
 * @file layout/Frame.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef Frame_h
#define Frame_h

#include "wx/graphics.h"
#include <wx/dcclient.h>

namespace Design {

    class Frame
    {
    public:
        Frame( ) {};
        ~Frame( ) {};

        double GetXPos( ) { return m_xPos; };
        void SetXPos( double val ) { m_xPos = val; };
        double GetYPos( ) { return m_yPos; };
        void SetYPos( double val ) { m_yPos = val; };
        double GetWidth( ) { return m_width; };
        void SetWidth( double val ) { m_width = val; };
        double GetHeight( ) { return m_height; };
        void SetHeight( double val ) { m_height = val; };
        double GetMinWidth( ) { return m_minWidth; };
        void SetMinWidth( double val ) { m_minWidth = val; };
        double GetMinHeight( ) { return m_minHeight; };
        void SetMinHeight( double val ) { m_minHeight = val; };

    void draw( wxPaintDC &dc, int x, int y )
    {
        wxRect rect( x+GetXPos(), y+GetYPos(), GetWidth( ), GetHeight( ) );
        dc.DrawRectangle( rect );
    };



    protected:

        double m_xPos;
        double m_yPos;
        double m_width;
        double m_height;
        double m_minWidth;
        double m_minHeight;
    };
}

#endif