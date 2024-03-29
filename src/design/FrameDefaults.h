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
            return GetAttrBool( AT_ShowTitle );
        };

        void ShowTitle( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };


        bool ShowSubTitle( ) {
            return GetAttrBool( AT_ShowSubTitle );
        };

        void ShowSubTitle( bool val ) {
            SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        };


        bool ShowFrame( ) {
            return GetAttrBool( AT_ShowFrame );
        };

        void ShowFrame( bool val ) {
            SetAttrBool( AT_ShowFrame, val );
        };

        void SetShowNbr( bool val )
        {
            SetAttrBool( AT_ShowCatNbr, val );
        };

        void SetAlignmentMode( AlignmentModeType loc );

        void SetAlignmentModeType( AlignmentModeType loc );



        Design::AlignmentModeType  GetAlignmentModeType( );


        bool CalculateSpacing( ) {
            return GetAttrBool( AT_CalculateSpacing, true );
        };

        void CalculateSpacing( bool val ) {
            SetAttrBool( AT_CalculateSpacing, val );
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



    };
};
#endif