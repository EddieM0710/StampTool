/**
 * @file layout/StampDefaults.h
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

#ifndef StampDefaults_H
#define StampDefaults_H

#include "design/XMLBase.h"
#include "design/DesignDefs.h"
#include "design/Defaults.h"



namespace Design {

    class StampDefaults : public Defaults
    {

    public:

        StampDefaults( );

        StampDefaults( wxXmlNode* xmlNode );

        ~StampDefaults( );

        void InitParameters( );

        void Save( wxXmlNode* xmlNode );


        void Catalog( wxString str ) {
            SetDefault( AT_Catalog, str );
        };

        wxString Catalog( ) {
            return GetDefault( AT_Catalog );
        };



        bool ShowName( ) {
            return String2Bool( GetAttrStr( AT_ShowTitle ) );
        };

        void ShowName( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };


        // bool ShowSubTitle( ) {
        //     return String2Bool( GetAttrStr( AT_ShowSubTitle ) );
        // };

        // void ShowSubTitle( bool val ) {
        //     SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        // };

       // void SetDefaultStampNamePosition( StampNamePositionType loc );

       // void SetDefaultStampNamePositionType( StampNamePositionType loc );

        bool ShowNbr( ) {
            return String2Bool( GetAttrStr( AT_ShowCatNbr ) );
        };

        void ShowNbr( bool val ) {
            SetAttrStr( AT_ShowCatNbr, Bool2String( val ) );
        };


        bool ShowImage( ) {
            return String2Bool( GetAttrStr( AT_ShowImage ) );
        };

        void ShowImage( bool val ) {
            SetAttrStr( AT_ShowImage, Bool2String( val ) );
        };


        double SelvageHeight( )
        {
            return GetDefaultDbl( AT_SelvageHeight );
        }

        wxString SelvageHeightStr( )
        {
            return GetDefault( AT_SelvageHeight );
        }

        void SelvageHeight( double val )
        {
            SetDefaultDbl( AT_SelvageHeight, val );
        }

        bool IsDefaultSelvageHeight( wxString str )
        {
            return IsEqual( AT_SelvageHeight, str );
        }



        double SelvageWidth( )
        {
            return GetDefaultDbl( AT_SelvageWidth );
        }

        wxString SelvageWidthStr( )
        {
            return GetDefault( AT_SelvageWidth );
        }

        void SelvageWidth( double val )
        {
            SetDefaultDbl( AT_SelvageWidth, val );
        }

        bool IsDefaultSelvageWidth( wxString str )
        {
            return IsEqual( AT_SelvageWidth, str );
        }

        double MountAllowanceHeight( )
        {
            return GetDefaultDbl( AT_MountAllowanceHeight );
        }

        wxString MountAllowanceHeightStr( )
        {
            return GetDefault( AT_MountAllowanceHeight );
        }

        void MountAllowanceHeight( double val )
        {
            SetDefaultDbl( AT_MountAllowanceHeight, val );
        }

        void MountAllowanceHeight( wxString str ) {
            SetDefault( AT_MountAllowanceHeight, str );
        };

        bool IsDefaultMountAllowanceHeight( wxString str )
        {
            return IsEqual( AT_MountAllowanceHeight, str );
        }


        double MountAllowanceWidth( )
        {
            return GetDefaultDbl( AT_MountAllowanceWidth );
        }

        wxString MountAllowanceWidthStr( )
        {
            return GetDefault( AT_MountAllowanceWidth );
        }

        void MountAllowanceWidth( double val )
        {
            SetDefaultDbl( AT_MountAllowanceWidth, val );
        }

        bool IsDefaultMountAllowanceWidth( wxString str )
        {
            return IsEqual( AT_MountAllowanceWidth, str );
        }

        StampNamePosType StampNamePositionType( )
        {
            return FindStampLocationType( GetAttrStr( AT_StampNamePosition ) );
        }

        wxString StampNamePosition( )
        {
            return GetAttrStr( AT_StampNamePosition );
        }
        void StampNamePosition( wxString str )
        {
            SetAttrStr( AT_StampNamePosition, str );
        }

        void StampNamePosition( Design::StampNamePosType loc )
        {
            SetAttrStr( AT_StampNamePosition, StampNamePositionStrings[ loc ] );
        }


        // void AlignmentMode( AlignmentModeType loc )
        // {
        //     if ( ( loc != AlignBottom ) && ( loc != AlignTop ) )
        //     {
        //         loc = AlignTop;
        //     }
        //     SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ loc ] );
        // }

        // wxString AlignmentMode( )
        // {
        //     return GetAttrStr( AT_StampAlignmentMode );
        // }


        bool ShowStampName( ) {
            return String2Bool( GetAttrStr( AT_ShowTitle ) );
        };

        void ShowStampName( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };


        bool GetShowNbr( ) {
            return String2Bool( GetAttrStr( AT_ShowCatNbr ) );
        };

        bool GrayScaleImages( ) {
            return String2Bool( GetAttrStr( AT_GrayScaleImages ) );
        };

        void GrayScaleImages( bool val ) {
            SetAttrStr( AT_GrayScaleImages, Bool2String( val ) );
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



        double StampMargin( ) {
            return GetDefaultDbl( AT_StampMargin );
        };

        wxString StampMarginStr( ) {
            return GetDefault( AT_StampMargin );
        };

        void StampMargin( double val ) {
            SetDefaultDbl( AT_StampMargin, val );
        };

        void StampMargin( wxString str ) {
            SetDefault( AT_StampMargin, str );
        };

    };
};
#endif