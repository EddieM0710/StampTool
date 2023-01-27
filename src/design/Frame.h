/**
 * @file layout/Frame.h
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
 **************************************************/

#ifndef Frame_h
#define Frame_h

#include "wx/graphics.h"
#include <wx/dcclient.h>
#include "wx/textctrl.h"


namespace Design { 

    class Frame
    { 
    public:
        Frame( ) ;
        ~Frame( ) ;

        double GetXPos( ) ;
        void SetXPos( double val ) ;
        double GetYPos( ) ;
        void SetYPos( double val );
        double GetWidth( );
        void SetWidth( double val ) ;
        double GetHeight( ) ;
        void SetHeight( double val ) ;
        double GetMinWidth( );
        void SetMinWidth( double val );
        double GetMinHeight( );
        void SetMinHeight( double val );

        /* 
         * @brief draw object on screen
         * 
         * @param dc current device context
         * @param x position in MM
         * @param y position in MM
         */
    void draw( wxDC &dc, double x, double y );
    //void DrawRectangle( wxDC &dc, double x, double y, double width, double height );
     
    //void drawBorder( wxDC &dc, double x, double y );

    wxString ReportLayout(  wxString indent = "" );

    void WriteLayout( wxString str );
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