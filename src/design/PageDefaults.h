/**
 * @file layout/PageDefaults.h
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

#ifndef PageDefaults_H
#define PageDefaults_H

#include "design/XMLBase.h"
#include "design/DesignDefs.h"
#include "design/Defaults.h"


namespace Design {

    class PageDefaults : public Defaults
    {

    public:



        PageDefaults( );

        PageDefaults( wxXmlNode* xmlNode );

        ~PageDefaults( );

        void SetApplicationDefaults( );

        void Save( wxXmlNode* xmlNode );

        double BorderSize( ) {
            return GetDefaultDbl( AT_BorderSize );
        };
        wxString BorderSizeStr( ) {
            return GetDefault( AT_BorderSize );
        };

        void BorderSize( wxString str ) {
            SetDefault( AT_BorderSize, str );
        };

        void BorderSize( double val ) {
            SetDefaultDbl( AT_BorderSize, val );
        };




        double ShowBorder( ) {
            return GetDefaultDbl( AT_ShowBorder );
        };
        bool   ShowBorderBool( ) {
            return GetDefaultBool( AT_ShowBorder, true );
        };

        void ShowBorder( wxString str ) {
            SetDefault( AT_ShowBorder, str );
        };

        void ShowBorder( bool val ) {
            SetDefault( AT_ShowBorder, val );
        };

        void BorderFilename( wxString str ) {
            SetDefault( AT_BorderFileName, str );
        };
        wxString BorderFilename( ) {
            return GetDefault( AT_BorderFileName );
        };

        double BottomMargin( ) {
            return GetDefaultDbl( AT_BottomPageMargin );
        };

        wxString BottomMarginStr( ) {
            return GetDefault( AT_BottomPageMargin );
        };

        void BottomMargin( double val ) {
            SetDefaultDbl( AT_BottomPageMargin, val );
        };

        void BottomMargin( wxString str ) {
            SetDefault( AT_BottomPageMargin, str );
        };



        double LeftMargin( ) {
            return GetDefaultDbl( AT_LeftPageMargin );
        };

        wxString LeftMarginStr( ) {
            return GetDefault( AT_LeftPageMargin );
        };

        void LeftMargin( double val ) {
            SetDefaultDbl( AT_LeftPageMargin, val );
        };

        void LeftMargin( wxString str ) {
            SetDefault( AT_LeftPageMargin, str );
        };



        double RightMargin( ) {
            return GetDefaultDbl( AT_RightPageMargin );
        };

        wxString RightMarginStr( ) {
            return GetDefault( AT_RightPageMargin );
        };

        void RightMargin( double val ) {
            SetDefaultDbl( AT_RightPageMargin, val );
        };

        void RightMargin( wxString str ) {
            SetDefault( AT_RightPageMargin, str );
        };

        double TopMargin( ) {
            return GetDefaultDbl( AT_TopPageMargin );
        };

        wxString TopMarginStr( ) {
            return GetDefault( AT_TopPageMargin );
        };

        void TopMargin( double val ) {
            SetDefaultDbl( AT_TopPageMargin, val );
        };

        void TopMargin( wxString str ) {
            SetDefault( AT_TopPageMargin, str );
        };

        double BottomContentMargin( ) {
            return GetDefaultDbl( AT_BottomContentMargin );
        };

        wxString BottomContentMarginStr( ) {
            return GetDefault( AT_BottomContentMargin );
        };

        void BottomContentMargin( double val ) {
            SetDefaultDbl( AT_BottomContentMargin, val );
        };

        void BottomContentMargin( wxString str ) {
            SetDefault( AT_BottomContentMargin, str );
        };

        double LeftContentMargin( ) {
            return GetDefaultDbl( AT_LeftContentMargin );
        };

        wxString LeftContentMarginStr( ) {
            return GetDefault( AT_LeftContentMargin );
        };

        void LeftContentMargin( double val ) {
            SetDefaultDbl( AT_LeftContentMargin, val );
        };

        void LeftContentMargin( wxString str ) {
            SetDefault( AT_LeftContentMargin, str );
        };

        double RightContentMargin( ) {
            return GetDefaultDbl( AT_RightContentMargin );
        };

        wxString RightContentMarginStr( ) {
            return GetDefault( AT_RightContentMargin );
        };

        void RightContentMargin( double val ) {
            SetDefaultDbl( AT_RightContentMargin, val );
        };

        void RightContentMargin( wxString str ) {
            SetDefault( AT_RightContentMargin, str );
        };

        double GetTopContentMargin( ) {
            return GetDefaultDbl( AT_TopContentMargin );
        };

        wxString TopContentMarginStr( ) {
            return GetDefault( AT_TopContentMargin );
        };

        void TopContentMargin( double val ) {
            SetDefaultDbl( AT_TopContentMargin, val );
        };

        void TopContentMargin( wxString str ) {
            SetDefault( AT_TopContentMargin, str );
        };

        double PageHeight( ) {
            return GetDefaultDbl( AT_PageHeight );
        };

        wxString PageHeightStr( ) {
            return GetDefault( AT_PageHeight );
        };

        void PageHeight( double val ) {
            SetDefaultDbl( AT_PageHeight, val );
        };

        void PageHeight( wxString str ) {
            SetDefault( AT_PageHeight, str );
        };



        double PageWidth( ) {
            return GetDefaultDbl( AT_PageWidth );
        };

        wxString PageWidthStr( ) {
            return GetDefault( AT_PageWidth );
        };

        void PageWidth( double val ) {
            SetDefaultDbl( AT_PageWidth, val );
        };

        void PageWidth( wxString str ) {
            SetDefault( AT_PageWidth, str );
        };



        double PaperHeight( ) {
            return GetDefaultDbl( AT_PaperHeight );
        };

        wxString PaperHeightStr( ) {
            return GetDefault( AT_PaperHeight );
        };

        void PaperHeight( double val ) {
            SetDefaultDbl( AT_PaperHeight, val );
        };

        void PaperHeight( wxString str ) {
            SetDefault( AT_PaperHeight, str );
        };


        double PaperWidth( ) {
            return GetDefaultDbl( AT_PaperWidth );
        };

        wxString PaperWidthStr( ) {
            return GetDefault( AT_PaperWidth );
        };

        void PaperWidth( double val ) {
            SetDefaultDbl( AT_PaperWidth, val );
        };

        void PaperWidth( wxString str ) {
            SetDefault( AT_PaperWidth, str );
        };


        double GetHeight( ) {
            return PageHeight( );
        };

        double GetWidth( ) {
            return PageWidth( );
        };


        void AlbumPageDefaults( wxString& width, wxString& height, wxString& topPageMargin,
            wxString& bottomPageMargin, wxString& rightPageMargin, wxString& leftPageMargin );

        bool ShowTitle( ) {
            return String2Bool( GetDefault( AT_ShowTitle ) );
        };

        void ShowTitle( bool val ) {
            SetDefault( AT_ShowTitle, Bool2String( val ) );
        };


        bool ShowSubTitle( ) {
            return String2Bool( GetDefault( AT_ShowSubTitle ) );
        };

        void ShowSubTitle( bool val ) {
            SetDefault( AT_ShowSubTitle, Bool2String( val ) );
        };


        bool OverSizePaper( ) {
            return String2Bool( GetDefault( AT_OverSizePaper ) );
        };

        void OverSizePaper( bool val ) {
            SetDefault( AT_OverSizePaper, Bool2String( val ) );
        };



        void SetShowNbr( bool val ) {
            SetDefault( AT_ShowCatNbr, Bool2String( val ) );
        };

        wxString Orientation( ) {
            return GetDefault( Design::AT_Orientation );
        };

        void Orientation( wxString orientation )
        {
            SetDefault( Design::AT_Orientation, orientation );
        };

        bool IsOrientation( wxString orientation )
        {
            return ( !orientation.Cmp( Orientation( ) ) );
        };

    };
};
#endif