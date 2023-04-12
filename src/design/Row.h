/**
 * @file layout/Row.h
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

#ifndef Row_H
#define Row_H

#include <wx/pdfdocument.h>

#include "design/LayoutBase.h"
#include "utils/DebugString.h"
namespace Design {

    /**
     * @brief Row layout object; Inherits from LayoutBase.  The Row can contain Column or Stamp objects.
     *
     **************************************************/
    class Row: public LayoutBase
    {
    public:

        Row( wxXmlNode* node ): LayoutBase( node )
        {
            SetNodeType( AT_Row );
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
            SetShowFrame( false );
            SetShowTitle( false );
            SetFixedSpacingSize( "4" );
            SetCalculateSpacing( true );
        };

        ~Row( ) { };

        /**
         * @brief Calculate the row layout based on child parameters
         *
         * @return true
         * @return false
         **************************************************/
        void UpdatePositions( );

        /**
        * @brief UpdateMinimumSize
        * Calculates the minimum Height and width of the object. It drills down to
        * the lowest layout object with an actual size and begins calculating the
        * min size of its parents as it progresses back up the heirarchy.
        * @return true
        * @return false
        **************************************************/
        bool UpdateMinimumSize( );

        void UpdateSizes( );


        NodeStatus ValidateNode( );

        /*
         * @brief Draw object on screen
         *
         * @param dc current device context
         * @param x position in MM
         * @param y position in MM
         */
        void Draw( wxDC& dc, double x, double y );
        void DrawPDF( wxPdfDocument* doc, double x, double y );

        void Save( wxXmlNode* xmlNode );

        void ReportLayout( );

        void SetFixedSpacingSize( wxString str ) { SetAttrStr( AT_FixedSpacingSize, str ); };
        wxString GetFixedSpacing( ) { return GetAttrStr( AT_FixedSpacingSize ); };
        double GetFixedSpacingDbl( ) { return GetAttrDbl( AT_FixedSpacingSize ); };

        bool CalculateSpacing( ) { return String2Bool( GetAttrStr( AT_CalculateSpacing ) ); };
        void SetCalculateSpacing( bool val ) { SetAttrStr( AT_CalculateSpacing, Bool2String( val ) ); };

    private:
        //        bool m_showTitle;
        //        bool m_calculateSpacing;
        //        double m_fixedSpacing;
        DebugString m_debugString;
        //        StampAlignment m_stampAlignment;
    };

}
#endif