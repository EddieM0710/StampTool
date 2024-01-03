/**
 * @file PageDefaults.cpp
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
#include "design/PageDefaults.h"


namespace Design {

    PageDefaults::PageDefaults( ) : Design::Defaults( ( wxXmlNode* ) 0 )
    {
        SetApplicationDefaults( );
    };

    PageDefaults::PageDefaults( wxXmlNode* xmlNode ) : Defaults( xmlNode )
    {
        SetApplicationDefaults( );
    };

    PageDefaults::~PageDefaults( )
    {
    };

    void PageDefaults::SetApplicationDefaults( )
    {

        /***/        ApplicationDefault[ AT_PageWidth ] = "208.25";
        /***/       ApplicationDefault[ AT_PageHeight ] = "269.5";
        /***/       ApplicationDefault[ AT_TopPageMargin ] = "12";
        /***/        ApplicationDefault[ AT_BottomPageMargin ] = "12";
        /***/       ApplicationDefault[ AT_RightPageMargin ] = "12";
        /***/       ApplicationDefault[ AT_LeftPageMargin ] = "18";
        /***/       ApplicationDefault[ AT_BorderFileName ] = "big_and_little_line.jpg";
        /***/        ApplicationDefault[ AT_BorderSize ] = "4";
        /***/        ApplicationDefault[ AT_ShowBorder ] = "true";
        ApplicationDefault[ AT_ShowTitle ] = "true";
        ApplicationDefault[ AT_ShowSubTitle ] = "true";
        /***/       ApplicationDefault[ AT_Orientation ] = OrientationStrings[ Design::AT_Portrait ];
        ApplicationDefault[ AT_TopContentMargin ] = "2";
        ApplicationDefault[ AT_BottomContentMargin ] = "2";
        ApplicationDefault[ AT_LeftContentMargin ] = "2";
        ApplicationDefault[ AT_RightContentMargin ] = "2";
        /***/       ApplicationDefault[ AT_OverSizePaper ] = "false";
        /***/        ApplicationDefault[ AT_PaperHeight ] = "269.5";
        /***/        ApplicationDefault[ AT_PaperWidth ] = "208.25";
    }



    void PageDefaults::Save( wxXmlNode* xmlNode )
    {
        Defaults::Save( xmlNode, AT_OverSizePaper );
        Defaults::Save( xmlNode, AT_PaperHeight );
        Defaults::Save( xmlNode, AT_PaperWidth );
        Defaults::Save( xmlNode, AT_PageWidth );
        Defaults::Save( xmlNode, AT_PageHeight );
        Defaults::Save( xmlNode, AT_TopPageMargin );
        Defaults::Save( xmlNode, AT_BottomPageMargin );
        Defaults::Save( xmlNode, AT_RightPageMargin );
        Defaults::Save( xmlNode, AT_LeftPageMargin );
        Defaults::Save( xmlNode, AT_BorderFileName );
        Defaults::Save( xmlNode, AT_BorderSize );
        Defaults::Save( xmlNode, AT_ShowCatNbr );
        Defaults::Save( xmlNode, AT_ShowTitle );
        Defaults::Save( xmlNode, AT_ShowTitle );
        Defaults::Save( xmlNode, AT_ShowTitle );
        Defaults::Save( xmlNode, AT_ShowSubTitle );
        Defaults::Save( xmlNode, AT_ShowSubTitle );
        Defaults::Save( xmlNode, AT_GrayScaleImages );
        Defaults::Save( xmlNode, AT_StampNamePosition );
        Defaults::Save( xmlNode, AT_Orientation );

    }

}