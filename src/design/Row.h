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
 */

#ifndef Row_H
#define Row_H

#include <wx/pdfdocument.h>

#include "design/LayoutBase.h"
#include "utils/DebugString.h"

namespace Design {

    class TitleFrame;
    /**
     * @brief Row layout object; Inherits from LayoutBase.  The Row can contain Column or Stamp objects.
     *
     */
    class Row : public LayoutBase
    {


    public:

        Row( wxXmlNode* node );


        ~Row( ) { };

        void InitParameters( );

        bool CalculateSpacing( ) {
            wxString str = GetAttrStr( AT_CalculateSpacing );
            if ( str.IsEmpty( ) )
            {
                return true;
            }
            return String2Bool( str, true );
        };
        wxString GetTitleString( );

        wxString GetSubTitleString( );

        void SetTitleString( wxString str );

        void SetSubTitleString( wxString str );

        TitleFrame* GetTitleFrame( );

        void Draw( wxDC& dc, double x, double y );

        void DrawPDF( wxPdfDocument* doc, double x, double y );

        wxString GetFixedSpacing( ) {
            return GetAttrStr( AT_FixedSpacingSize );
        };

        double GetFixedSpacingDbl( ) {
            return GetAttrDbl( AT_FixedSpacingSize );
        };



        void LoadFonts( wxXmlNode* node );

        void ReportLayout( );

        void SaveFonts( wxXmlNode* parent );

        void Save( wxXmlNode* xmlNode );

        void SetFixedSpacingSize( wxString str ) {
            SetAttrStr( AT_FixedSpacingSize, str );
        };

        void SetCalculateSpacing( bool val ) {
            SetAttrStr( AT_CalculateSpacing, Bool2String( val ) );
        };


        bool UpdateMinimumSize( );

        /**
         * @brief Calculate the row layout based on child parameters
         *
         * @return true
         * @return false
         */
        void UpdatePositions( );

        void UpdateSizes( );

        NodeStatus ValidateNode( );

        void SetTitleLocation( TitleLocation loc );
        wxString GetTitleLocation( );

        TitleLocation  GetTitleLocationType( );
        void SetTitleLocationType( TitleLocation loc );

    private:

        DebugString m_debugString;
        TitleFrame* m_titleFrame;

    };

}
#endif