/**
 * @file StampDefaults.cpp
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
#include "design/StampDefaults.h"


namespace Design {

    StampDefaults::StampDefaults( ) : Defaults( ( wxXmlNode* ) 0 )
    {
        InitParameters( );
    };

    StampDefaults::StampDefaults( wxXmlNode* xmlNode ) : Defaults( xmlNode )
    {
        InitParameters( );
    };

    StampDefaults::~StampDefaults( )
    {
    };

    void StampDefaults::Save( wxXmlNode* xmlNode )
    {
    };

    void StampDefaults::InitParameters( )
    {
        SetAttrStr( AT_ShowTitle, "true" );
        SetAttrStr( AT_ShowCatNbr, "true" );
        SetAttrStr( AT_ShowImage, "true" );
        SetAttrStr( AT_GrayScaleImages, "false" );
        SetAttrStr( AT_TopContentMargin, "2" );
        SetAttrStr( AT_BottomContentMargin, "2" );
        SetAttrStr( AT_LeftContentMargin, "2" );
        SetAttrStr( AT_RightContentMargin, "2" );
        SetAttrStr( AT_SelvageHeight, "0" );
        SetAttrStr( AT_SelvageWidth, "0" );
        SetAttrStr( AT_MountAllowanceHeight, "5" );
        SetAttrStr( AT_MountAllowanceWidth, "4" );
        SetAttrStr( AT_StampNamePosition, Design::StampNamePositionStrings[ AT_StampNamePositionTop ] );
        SetAttrStr( AT_StampMargin, "2" );
        SetAttrStr( AT_Catalog, "Mi" );
    }



}