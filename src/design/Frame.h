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
 */

#ifndef Frame_h
#define Frame_h

#include "wx/graphics.h"
#include <wx/dcclient.h>
#include "wx/textctrl.h"
#include <wx/pdfdocument.h>



namespace Design {

    class Frame
    {

    public:

        Frame( );

        ~Frame( );

        void Init( );

        /*
          * @brief Draw object on screen
          *
          * @param dc current device context
          * @param x position in MM
          * @param y position in MM
          */
        void Draw( wxDC& dc, double x, double y );

        void DrawPDF( wxPdfDocument* doc, double x, double y );

        //void DrawRectangle( wxDC &dc, double x, double y, double width, double height );

        //void drawBorder( wxDC &dc, double x, double y );

        double GetHeight( );

        double GetMinHeight( );

        double GetMinWidth( );

        RealPoint GetPosition( ) {
            return RealPoint( GetXPos( ), GetYPos( ) );
        };

        RealSize GetSize( ) {
            return RealSize( GetWidth( ), GetHeight( ) );
        };

        double GetXPos( );

        double GetYPos( );

        double GetWidth( );


        wxString ReportLayout( wxString indent = "" );
        wxString LayoutString( );

        void SetHeight( double val );

        void SetMinWidth( double val );

        void SetMinHeight( double val );

        void SetXPos( double val );

        void SetYPos( double val );

        void SetWidth( double val );

        wxString WriteLayout( wxString prefix );
        wxString Layout( );
        //   void Check( );

        wxRect GetRect( ) {
            return wxRect( GetXPos( ), GetYPos( ), GetWidth( ), GetHeight( ) );
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