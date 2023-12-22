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
            return GetDbl( AT_BorderSize );
        };
        wxString BorderSizeStr( ) {
            return Get( AT_BorderSize );
        };

        void BorderSize( wxString str ) {
            Set( AT_BorderSize, str );
        };

        void BorderSize( double val ) {
            SetDbl( AT_BorderSize, val );
        };

        void BorderFilename( wxString str ) {
            Set( AT_BorderFileName, str );
        };
        wxString BorderFilename( ) {
            return Get( AT_BorderFileName );
        };

        double BottomMargin( ) {
            return GetDbl( AT_BottomPageMargin );
        };

        wxString BottomMarginStr( ) {
            return Get( AT_BottomPageMargin );
        };

        void BottomMargin( double val ) {
            SetDbl( AT_BottomPageMargin, val );
        };

        void BottomMargin( wxString str ) {
            Set( AT_BottomPageMargin, str );
        };



        double LeftMargin( ) {
            return GetDbl( AT_LeftPageMargin );
        };

        wxString LeftMarginStr( ) {
            return Get( AT_LeftPageMargin );
        };

        void LeftMargin( double val ) {
            SetDbl( AT_LeftPageMargin, val );
        };

        void LeftMargin( wxString str ) {
            Set( AT_LeftPageMargin, str );
        };



        double RightMargin( ) {
            return GetDbl( AT_RightPageMargin );
        };

        wxString RightMarginStr( ) {
            return Get( AT_RightPageMargin );
        };

        void RightMargin( double val ) {
            SetDbl( AT_RightPageMargin, val );
        };

        void RightMargin( wxString str ) {
            Set( AT_RightPageMargin, str );
        };

        double GetTopMargin( ) {
            return GetDbl( AT_TopPageMargin );
        };

        wxString TopMarginStr( ) {
            return Get( AT_TopPageMargin );
        };

        void TopMargin( double val ) {
            SetDbl( AT_TopPageMargin, val );
        };

        void TopMargin( wxString str ) {
            Set( AT_TopPageMargin, str );
        };

        double BottomContentMargin( ) {
            return GetDbl( AT_BottomContentMargin );
        };

        wxString BottomContentMarginStr( ) {
            return Get( AT_BottomContentMargin );
        };

        void BottomContentMargin( double val ) {
            SetDbl( AT_BottomContentMargin, val );
        };

        void BottomContentMargin( wxString str ) {
            Set( AT_BottomContentMargin, str );
        };

        double LeftContentMargin( ) {
            return GetDbl( AT_LeftContentMargin );
        };

        wxString LeftContentMarginStr( ) {
            return Get( AT_LeftContentMargin );
        };

        void LeftContentMargin( double val ) {
            SetDbl( AT_LeftContentMargin, val );
        };

        void LeftContentMargin( wxString str ) {
            Set( AT_LeftContentMargin, str );
        };

        double RightContentMargin( ) {
            return GetDbl( AT_RightContentMargin );
        };

        wxString RightContentMarginStr( ) {
            return Get( AT_RightContentMargin );
        };

        void RightContentMargin( double val ) {
            SetDbl( AT_RightContentMargin, val );
        };

        void RightContentMargin( wxString str ) {
            Set( AT_RightContentMargin, str );
        };

        double GetTopContentMargin( ) {
            return GetDbl( AT_TopContentMargin );
        };

        wxString TopContentMarginStr( ) {
            return Get( AT_TopContentMargin );
        };

        void TopContentMargin( double val ) {
            SetDbl( AT_TopContentMargin, val );
        };

        void TopContentMargin( wxString str ) {
            Set( AT_TopContentMargin, str );
        };

        double PageHeight( ) {
            return GetDbl( AT_PageHeight );
        };

        wxString PageHeightStr( ) {
            return Get( AT_PageHeight );
        };

        void PageHeight( double val ) {
            SetDbl( AT_PageHeight, val );
        };

        void PageHeight( wxString str ) {
            Set( AT_PageHeight, str );
        };



        double PageWidth( ) {
            return GetDbl( AT_PageWidth );
        };

        wxString PageWidthStr( ) {
            return Get( AT_PageWidth );
        };

        void PageWidth( double val ) {
            SetDbl( AT_PageWidth, val );
        };

        void PageWidth( wxString str ) {
            Set( AT_PageWidth, str );
        };



        double PaperHeight( ) {
            return GetDbl( AT_PaperHeight );
        };

        wxString PaperHeightStr( ) {
            return Get( AT_PaperHeight );
        };

        void PaperHeight( double val ) {
            SetDbl( AT_PaperHeight, val );
        };

        void PaperHeight( wxString str ) {
            Set( AT_PaperHeight, str );
        };


        double PaperWidth( ) {
            return GetDbl( AT_PaperWidth );
        };

        wxString PaperWidthStr( ) {
            return Get( AT_PaperWidth );
        };

        void PaperWidth( double val ) {
            SetDbl( AT_PaperWidth, val );
        };

        void PaperWidth( wxString str ) {
            Set( AT_PaperWidth, str );
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
            return String2Bool( Get( AT_ShowTitle ) );
        };

        void ShowTitle( bool val ) {
            Set( AT_ShowTitle, Bool2String( val ) );
        };


        bool ShowSubTitle( ) {
            return String2Bool( Get( AT_ShowSubTitle ) );
        };

        void ShowSubTitle( bool val ) {
            Set( AT_ShowSubTitle, Bool2String( val ) );
        };


        bool OverSizePaper( ) {
            return String2Bool( Get( AT_OverSizePaper ) );
        };

        void OverSizePaper( bool val ) {
            Set( AT_OverSizePaper, Bool2String( val ) );
        };



        void SetShowNbr( bool val ) {
            Set( AT_ShowCatNbr, Bool2String( val ) );
        };

        wxString Orientation( ) {
            return Get( Design::AT_Orientation );
        };

        void Orientation( wxString orientation )
        {
            Set( Design::AT_Orientation, orientation );
        };

        bool IsOrientation( wxString orientation )
        {
            return ( !orientation.Cmp( Orientation( ) ) );
        };

    };
};
#endif