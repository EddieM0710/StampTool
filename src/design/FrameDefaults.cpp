/**
 * @file FrameDefaults.cpp
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "utils/XMLUtilities.h"
#include "utils/Settings.h"
#include "design/FrameDefaults.h"


namespace Design {

    //----------------

    FrameDefaults::FrameDefaults( ) : Defaults( ( wxXmlNode* ) 0 )
    {
        ApplicationDefault = GetSettings( )->GetLayoutPreferences( Design::LT_Frame );
        //InitParameters( );
    };

    //----------------

    FrameDefaults::FrameDefaults( wxXmlNode* xmlNode ) : Defaults( xmlNode )
    {
        ApplicationDefault = GetSettings( )->GetLayoutPreferences( Design::LT_Frame );
        //InitParameters( );
    };

    //----------------

    FrameDefaults::~FrameDefaults( )
    {
    };

    //----------------

    void FrameDefaults::Save( wxXmlNode* xmlNode )
    {
        Defaults::SaveDefault( xmlNode, AT_ShowTitle );
        Defaults::SaveDefault( xmlNode, AT_ShowSubTitle );
        Defaults::SaveDefault( xmlNode, AT_ShowFrame );
        Defaults::SaveDefault( xmlNode, AT_TopContentMargin );
        Defaults::SaveDefault( xmlNode, AT_BottomContentMargin );
        Defaults::SaveDefault( xmlNode, AT_LeftContentMargin );
        Defaults::SaveDefault( xmlNode, AT_RightContentMargin );
        Defaults::SaveDefault( xmlNode, AT_CalculateSpacing );
        Defaults::SaveDefault( xmlNode, AT_FixedSpacingSize );
        Defaults::SaveDefault( xmlNode, AT_StampAlignmentMode );
    };

    //----------------

    void FrameDefaults::InitParameters( )
    {


        ApplicationDefault[ AT_ShowTitle ] = "false";
        ApplicationDefault[ AT_ShowSubTitle ] = "false";
        ApplicationDefault[ AT_ShowFrame ] = "false";
        ApplicationDefault[ AT_TopContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_BottomContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_LeftContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_RightContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_CalculateSpacing ] = "true";
        ApplicationDefault[ AT_FixedSpacingSize ] = Dbl2String( 5 );
        ApplicationDefault[ AT_StampAlignmentMode ] = StampAlignmentModeStrings[ AlignTop ];
        /***/ //NameLocation
    }

    //----------------

    Design::AlignmentModeType  FrameDefaults::GetAlignmentModeType( )
    {
        AlignmentModeType loc = FindAlignmentModeType( GetAttrStr( AT_StampAlignmentMode ) );
        if ( ( loc != AlignBottom ) && ( loc != AlignMiddle ) && ( loc != AlignTop ) )
        {
            loc = AlignTop;
            SetAlignmentModeType( loc );
        }
        return FindAlignmentModeType( GetAttrStr( AT_StampAlignmentMode ) );
    };

    //----------------

    void FrameDefaults::SetAlignmentMode( AlignmentModeType loc )
    {
        SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ loc ] );
    }

    //----------------

    void FrameDefaults::SetAlignmentModeType( AlignmentModeType loc )
    {
        if ( ( loc != AlignBottom ) && ( loc != AlignTop ) )
        {
            loc = AlignTop;
        }
        SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ loc ] );
    };

    //----------------

}