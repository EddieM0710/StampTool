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

        double GetRowAttributeDbl( Design::AlbumAttrType type );
        wxString GetRowAttributeStr( Design::AlbumAttrType type );
        bool GetRowAttributeBool( Design::AlbumAttrType type );

        void SetRowAttributeBool( Design::AlbumAttrType type, bool val );
        void SetRowAttributeDbl( Design::AlbumAttrType type, double val );
        void SetRowAttributeStr( Design::AlbumAttrType type, wxString val );

        bool CalculateSpacing( ) {
            return GetRowAttributeBool( AT_CalculateSpacing );
        };
        wxString GetTitleString( );

        wxString GetSubTitleString( );

        bool GetShowTitle( ) {
            return GetRowAttributeBool( AT_ShowTitle );
        };
        bool GetShowSubTitle( ) {
            return GetRowAttributeBool( AT_ShowSubTitle );
        };

        // void SetShowNbr( bool val ){};
        // bool GetShowNbr( ) {
        //     return false;
        // };

        void SetTitleString( wxString str );

        void SetSubTitleString( wxString str );

        void SetShowTitle( bool val ) {
            SetRowAttributeBool( AT_ShowTitle, val );
        };

        void SetShowSubTitle( bool val ) {
            SetRowAttributeBool( AT_ShowSubTitle, val );
        };

        bool IsDefaultVal( AlbumAttrType type );

        bool IsDefaultVal( AlbumAttrType type, wxString val );

        TitleFrame* GetTitleFrame( );

        void Draw( wxDC& dc, double x, double y );

        void DrawPDF( wxPdfDocument* doc, double x, double y );

        wxString GetFixedSpacing( ) {
            return GetRowAttributeStr( AT_FixedSpacingSize );
        };

        double GetFixedSpacingDbl( ) {
            return GetRowAttributeDbl( AT_FixedSpacingSize );
        };

        void LoadFonts( wxXmlNode* node );

        void ReportLayout( );

        void SaveFonts( wxXmlNode* parent );

        void Save( wxXmlNode* xmlNode );

        void SetFixedSpacingSize( wxString str ) {
            SetRowAttributeStr( AT_FixedSpacingSize, str );
        };

        void SetCalculateSpacing( bool val ) {
            SetRowAttributeBool( AT_CalculateSpacing, val );
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



        //  wxString GetAlignmentMode( );

        void SetAlignmentMode( AlignmentModeType loc );

        void SetAlignmentMode( wxString str );

        // void SetAlignmentModeType( AlignmentModeType loc );

        AlignmentModeType  GetAlignmentModeType( );



    private:

        DebugString m_debugString;
        TitleFrame* m_titleFrame;

    };

}
#endif