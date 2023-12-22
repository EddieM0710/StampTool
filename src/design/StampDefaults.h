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
            Set( AT_Catalog, str );
        };

        wxString Catalog( ) {
            return Get( AT_Catalog );
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
            return GetAttrDbl( AT_SelvageHeight );
        }

        wxString SelvageHeightStr( )
        {
            return GetAttrStr( AT_SelvageHeight );
        }

        void SelvageHeight( double val )
        {
            SetAttrDbl( AT_SelvageHeight, val );
        }

        bool IsDefaultSelvageHeight( wxString str )
        {
            return IsEqual( AT_SelvageHeight, str );
        }



        double SelvageWidth( )
        {
            return GetAttrDbl( AT_SelvageWidth );
        }

        wxString SelvageWidthStr( )
        {
            return GetAttrStr( AT_SelvageWidth );
        }

        void SelvageWidth( double val )
        {
            SetAttrDbl( AT_SelvageWidth, val );
        }

        bool IsDefaultSelvageWidth( wxString str )
        {
            return IsEqual( AT_SelvageWidth, str );
        }

        double MountAllowanceHeight( )
        {
            return GetAttrDbl( AT_MountAllowanceHeight );
        }
        wxString MountAllowanceHeightStr( )
        {
            return GetAttrStr( AT_MountAllowanceHeight );
        }

        void MountAllowanceHeight( double val )
        {
            SetAttrDbl( AT_MountAllowanceHeight, val );
        }

        bool IsDefaultMountAllowanceHeight( wxString str )
        {
            return IsEqual( AT_MountAllowanceHeight, str );
        }


        double MountAllowanceWidth( )
        {
            return GetAttrDbl( AT_MountAllowanceWidth );
        }

        wxString MountAllowanceWidthStr( )
        {
            return GetAttrStr( AT_MountAllowanceWidth );
        }

        void MountAllowanceWidth( double val )
        {
            SetAttrDbl( AT_MountAllowanceWidth, val );
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



        double StampMargin( ) {
            return GetDbl( AT_StampMargin );
        };

        wxString StampMarginStr( ) {
            return Get( AT_StampMargin );
        };

        void StampMargin( double val ) {
            SetDbl( AT_StampMargin, val );
        };

        void StampMargin( wxString str ) {
            Set( AT_StampMargin, str );
        };

    };
};
#endif