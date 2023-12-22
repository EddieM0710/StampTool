/**
 * @file layout/FrameDefaults.h
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

#ifndef FrameDefaults_H
#define FrameDefaults_H

#include "design/XMLBase.h"
#include "design/DesignDefs.h"
#include "design/Defaults.h"


namespace Design {

    class FrameDefaults : public Defaults
    {

    public:

        FrameDefaults( );

        FrameDefaults( wxXmlNode* xmlNode );

        ~FrameDefaults( );

        void InitParameters( );

        void Save( wxXmlNode* xmlNode );


        bool ShowTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowTitle ) );
        };

        void ShowTitle( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };


        bool ShowSubTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowSubTitle ) );
        };

        void ShowSubTitle( bool val ) {
            SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        };


        bool ShowFrame( ) {
            return String2Bool( GetAttrStr( AT_ShowFrame ) );
        };

        void ShowFrame( bool val ) {
            SetAttrStr( AT_ShowFrame, Bool2String( val ) );
        };

        void SetShowNbr( bool val )
        {
            SetAttrStr( AT_ShowCatNbr, Bool2String( val ) );
        };

        void SetAlignmentMode( AlignmentModeType loc );

        void SetAlignmentModeType( AlignmentModeType loc );



        Design::AlignmentModeType  GetAlignmentModeType( );


        bool CalculateSpacing( ) {
            return String2Bool( GetAttrStr( AT_CalculateSpacing ) );
        };

        void CalculateSpacing( bool val ) {
            SetAttrStr( AT_CalculateSpacing, Bool2String( val ) );
        };

        double FixedSpacing( )
        {
            return GetAttrDbl( AT_FixedSpacingSize );
        }

        wxString FixedSpacingStr( )
        {
            return GetAttrStr( AT_FixedSpacingSize );
        }

        void FixedSpacing( double val )
        {
            SetAttrDbl( AT_FixedSpacingSize, val );
        }

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



    };
};
#endif