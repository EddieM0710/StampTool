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
        Defaults::SaveDefault( xmlNode, AT_ShowCatNbr );
        Defaults::SaveDefault( xmlNode, AT_ShowTitle );
        Defaults::SaveDefault( xmlNode, AT_ShowImage );
        Defaults::SaveDefault( xmlNode, AT_GrayScaleImages );
        Defaults::SaveDefault( xmlNode, AT_StampNamePosition );
        Defaults::SaveDefault( xmlNode, AT_TopContentMargin );
        Defaults::SaveDefault( xmlNode, AT_BottomContentMargin );
        Defaults::SaveDefault( xmlNode, AT_LeftContentMargin );
        Defaults::SaveDefault( xmlNode, AT_RightContentMargin );
        Defaults::SaveDefault( xmlNode, AT_Orientation );
        Defaults::SaveDefault( xmlNode, AT_SelvageHeight );
        Defaults::SaveDefault( xmlNode, AT_SelvageWidth );
        Defaults::SaveDefault( xmlNode, AT_MountAllowanceHeight );
        Defaults::SaveDefault( xmlNode, AT_MountAllowanceWidth );
        Defaults::SaveDefault( xmlNode, AT_StampNamePosition );
        Defaults::SaveDefault( xmlNode, AT_StampMargin );
        Defaults::SaveDefault( xmlNode, AT_Catalog );
    };

    void StampDefaults::InitParameters( )
    {

        ApplicationDefault[ AT_ShowTitle ] = "true";
        ApplicationDefault[ AT_ShowCatNbr ] = "true";
        ApplicationDefault[ AT_ShowImage ] = "true";
        ApplicationDefault[ AT_GrayScaleImages ] = "false";
        ApplicationDefault[ AT_TopContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_BottomContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_LeftContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_RightContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_SelvageHeight ] = Dbl2String( 0 );
        ApplicationDefault[ AT_SelvageWidth ] = Dbl2String( 0 );
        ApplicationDefault[ AT_MountAllowanceHeight ] = Dbl2String( 5 );
        ApplicationDefault[ AT_MountAllowanceWidth ] = Dbl2String( 4 );
        ApplicationDefault[ AT_StampNamePosition ] = Design::StampNamePositionStrings[ AT_StampNamePositionTop ];
        ApplicationDefault[ AT_StampMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_Catalog ] = "Mi";
    }



}