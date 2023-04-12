/**
 * @file layout/DisplayString.h
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

#ifndef DisplayString_H
#define DisplayString_H

#include <wx/string.h>
#include <wx/pdfdocument.h>

#include "Defs.h"
#include "design/Frame.h"
#include "design/LayoutBase.h"
#include "gui/AlbumImagePanel.h"

namespace Design {


    /**
     * @brief Design for the page DisplayString text box; Inherits from LayoutBase.
     *
     **************************************************/
    class DisplayString: public Frame
    {

    private:
        DisplayString( ) { };

    public:

        /**
         * @brief Construct a new DisplayString object
         *
         * @param parent
         **************************************************/
        DisplayString( LayoutBase* parent, Design::AT_FontUsageType fontType ): Frame( )
        {
            m_parent = parent;
            m_fontType = fontType;
        };

        /**
         * @brief Destroy the DisplayString object
         *
         **************************************************/
        ~DisplayString( ) { };
        void SetString( wxString str ) { m_string = str; };

        wxFont GetFont( );

        void GetString( );

        void drawPDF( wxPdfDocument* doc, double x, double y );

        void Draw( wxDC& dc, double x, double y );

        void UpdateString( double width );

    private:

        wxString m_string;

        wxString m_multiLineString;

        wxRealPoint m_stringTextExtent;

        LayoutBase* m_parent;

        AT_FontUsageType m_fontType;

        double m_maxWidth;

    };
}
#endif