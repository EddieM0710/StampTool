/**
 * @file layout/Album.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-02
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

#ifndef Album_H
#define Album_H
#include <wx/font.h>

#include "design/AlbumBase.h"
#include "design/DesignDefs.h"
 //#include "utils/Project.h"
//#include "utils/FontNdx.h"
#include <wx/pdfdc.h>


namespace Design {

    /**
     * @brief Album layout object; inherits from LayoutBase.
     *
     */
    class Album : public AlbumBase
    {

    public:


        Album( wxXmlNode* node );

        ~Album( ) { };

        void InitParameters( );

        wxString DrawPDF( );

        void DumpFont( wxString Level );

        void DumpLayout( );

        double GetBorderSize( );

        wxString GetBorderSizeStr( );

        void SetBorderSize( wxString str );

        //void SetBorderFilename( wxString str );

        wxString GetBorderFileName( );

        void SetBorderFilename( wxString filename );

        wxString GetCatalog( );

        wxColour GetColor( FontUsageType fontType );

        wxString GetDefaultValStr( AlbumAttrType type );

        double GetDefaultVal( AlbumAttrType type );

        wxString GetDocName( );

        wxFont GetFont( FontUsageType fontType );

        int GetFontNdx( FontUsageType fontType );

        int GetFontNdxPreference( FontUsageType fontType );

        bool GetGrayScaleImages( ) {
            return String2Bool( GetAttrStr( AT_GrayScaleImages ) );
        };

        double GetHeight( );

        double GetLeftPageMargin( );

        wxString GetLeftPageMarginStr( );

        double GetPageHeight( );

        wxString GetPageHeightStr( );

        wxString GetPaperHeightStr( );

        void GetPageParameters( wxString& width, wxString& height, wxString& topPageMargin,
            wxString& bottomPageMargin, wxString& rightPageMargin, wxString& leftPageMargin );

        double GetPageWidth( );

        wxString GetPageWidthStr( );

        double GetPaperWidth( );

        wxString GetPaperWidthStr( );

        double GetPaperHeight( );

        double GetRightPageMargin( );

        wxString GetRightPageMarginStr( );

        bool GetShowNbr( ) {
            return String2Bool( GetAttrStr( AT_ShowCatNbr ) );
        };

        wxString GetStampNameLocation( );

        StampNameLocation  GetDefaultStampNameLocationType( );

        Design::AlignmentMode  GetAlignmentModeType( );

        //wxString GetAlignmentMode( );

        double GetTopPageMargin( );

        wxString GetTopPageMarginStr( );

        double GetBottomPageMargin( );

        wxString GetBottomPageMarginStr( );

        bool GetShowTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowTitle ) );
        };

        bool GetShowSubTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowSubTitle ) );
        };

        bool GetOverSizePaper( ) {
            return String2Bool( GetAttrStr( AT_OverSizePaper ) );
        };

        double GetWidth( );

        bool IsDefaultFont( FontUsageType fontType, int ndx );

        void LoadFonts( wxXmlNode* node );

        void MakeAlbum( );

        void MakeDefaultFont( FontUsageType fontType );

        void MakePDFAlbum( );

        void Save( wxXmlNode* xmlNode );

        void SaveFonts( wxXmlNode* parent );

        void SetCatalog( wxString str );

        void SetDocName( wxString str );

        void SetFont( FontUsageType fontType, wxFont font, wxColour color );

        void SetFontNdx( FontUsageType fontType, int ndx );

        void SetGrayScaleImages( bool val = true ) {
            SetAttrStr( AT_GrayScaleImages, Bool2String( val ) );
        };

        void SetLeftPageMargin( wxString str );

        void SetPageHeight( wxString str );

        void SetPageWidth( wxString str );

        void SetPaperHeight( wxString str );

        void SetPaperWidth( wxString str );

        void SetRightPageMargin( wxString str );

        void SetBottomPageMargin( wxString str );

        void SetTopPageMargin( wxString str );

        void SetShowTitle( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };

        void SetShowSubTitle( bool val ) {
            SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        };

        void SetOverSizePaper( bool val ) {
            SetAttrStr( AT_OverSizePaper, Bool2String( val ) );
        };


        void SetShowNbr( bool val ) {
            SetAttrStr( AT_ShowCatNbr, Bool2String( val ) );
        };

        void SetDefaultStampNameLocation( StampNameLocation loc );

        void SetDefaultStampNameLocationType( StampNameLocation loc );

        void SetAlignmentMode( AlignmentMode loc );

        void SetAlignmentModeType( AlignmentMode loc );

        /**
         * @brief UpdateMinimumSize drills down to the lowest layout object with an actual size
         * and begins calculating the min size of its parents as it progresses
         * back up the heirarchy.
         */
        bool UpdateMinimumSize( );

        /**
         * @brief  Does the layout for each child. Goes to the bottom
         * of each child container object ( row, column, page )
         * and begin filling in position relative to the parent
         */
        void UpdatePositions( );

        void UpdateSizes( );

        NodeStatus ValidateNode( );

        wxString GetDefaultOrientation( ) {
            return GetAttrStr( Design::AT_Orientation );
        };

        void SetDefaultOrientation( wxString orientation )
        {
            SetAttrStr( Design::AT_Orientation, orientation );
        };

        bool IsDefaultOrientation( wxString orientation )
        {
            return ( !orientation.Cmp( GetAttrStr( Design::AT_Orientation ) ) );
        };

    private:

        int DefaultFonts[ AT_NbrFontUsageTypes ];

        const double m_defaultSelvageHeight = 0;
        const double m_defaultSelvageWidth = 0;
        const double m_defaultMountAllowanceHeight = 5;
        const double m_defaultMountAllowanceWidth = 4;
        //  PageOrientation m_defaultOrientation;

    };
}
#endif