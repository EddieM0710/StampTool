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
        Frame( ) 
        {
        m_xPos = 0;
        m_yPos = 0;
        m_width = 0;
        m_height = 0;
        m_minWidth = 0;
        m_minHeight = 0;
        };
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

    void draw( wxDC &dc, double x, double y )
    {

// std::cout << "Frame::draw at (" << x <<" ,"<< y << ") x:" << GetXPos() << " y" << GetYPos()  << " w:" << 
//             GetWidth()  <<" h:" << GetHeight() << "\n";


        wxRect rect( x+GetXPos( ), 
                    y+GetYPos( ), 
                    GetWidth( ), 
                    GetHeight( ));

std::cout << "Frame::draw MM " << rect.x <<", "<< rect.y << ", " << rect.width << " ," << rect.height  << " )\n";

        rect.x = rect.x*Design::PpMM.x;
        rect.y = rect.y*Design::PpMM.y; 
        rect.width = rect.width*Design::PpMM.x; 
        rect.height = rect.height*Design::PpMM.y ;

//std::cout << "Frame::draw Pixels x:" << rect.x <<", y:"<< rect.y << ", width:" << rect.width << ", height:" << rect.height  << " )\n";
        dc.DrawRectangle( rect );
    };
    void drawBorder( wxDC &dc, double x, double y )
    {

        wxPen pen = dc.GetPen();
        pen.SetWidth(1);
        dc.SetPen(pen);   
        wxRect rect( x+GetXPos( ), 
                    y+GetYPos( ), 
                    GetWidth( ), 
                    GetHeight( ));

        rect.x = rect.x*Design::PpMM.x;
        rect.y = rect.y*Design::PpMM.y; 
        rect.width = rect.width*Design::PpMM.x; 
        rect.height = rect.height*Design::PpMM.y ;

        dc.DrawRectangle( rect );

        rect.x = rect.x+2;
        rect.y = rect.y+2; 
        rect.width = rect.width-4; 
        rect.height = rect.height-4 ;

        dc.DrawRectangle( rect );
    };

    void WriteLayout( )
    {
        std::cout << "  ( x:"
            << GetXPos( ) << ", y:" << GetXPos( )
            << ", w:" << GetWidth( ) << ", h:" << GetHeight( )
            << ", minW:" << GetMinWidth( ) << ", minH:" << GetMinHeight( ) << " )\n";
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