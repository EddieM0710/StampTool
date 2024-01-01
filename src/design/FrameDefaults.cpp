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
#include "design/FrameDefaults.h"


namespace Design {

    //----------------

    FrameDefaults::FrameDefaults( ) : Defaults( ( wxXmlNode* ) 0 )
    {
        InitParameters( );
    };

    //----------------

    FrameDefaults::FrameDefaults( wxXmlNode* xmlNode ) : Defaults( xmlNode )
    {
        InitParameters( );
    };

    //----------------

    FrameDefaults::~FrameDefaults( )
    {
    };

    //----------------

    void FrameDefaults::Save( wxXmlNode* xmlNode )
    {
    };

    //----------------

    void FrameDefaults::InitParameters( )
    {

        SetAttrStr( AT_ShowTitle, "false" );
        SetAttrStr( AT_ShowSubTitle, "false" );
        SetAttrStr( AT_ShowFrame, "false" );
        SetAttrStr( AT_TopContentMargin, "2" );
        SetAttrStr( AT_BottomContentMargin, "2" );
        SetAttrStr( AT_LeftContentMargin, "2" );
        SetAttrStr( AT_RightContentMargin, "2" );
        SetAttrStr( AT_CalculateSpacing, "true" );
        SetAttrStr( AT_FixedSpacingSize, "5" );
        SetAttrStr( AT_StampAlignmentMode, StampAlignmentModeStrings[ AlignTop ] );
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