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
#include "utils/Settings.h"
#include "design/PageDefaults.h"


namespace Design {

    PageDefaults::PageDefaults( ) : Design::Defaults( ( wxXmlNode* ) 0 )
    {
        ApplicationDefault = GetSettings( )->GetLayoutPreferences( Design::LT_Page );
        //SetApplicationDefaults( );
    };

    PageDefaults::PageDefaults( wxXmlNode* xmlNode ) : Defaults( xmlNode )
    {
        ApplicationDefault = GetSettings( )->GetLayoutPreferences( Design::LT_Page );
        //SetApplicationDefaults( );
    };

    PageDefaults::~PageDefaults( )
    {
    };

    void PageDefaults::SetApplicationDefaults( )
    {

        /***/        ApplicationDefault[ AT_PageWidth ] = Dbl2String( 208.25 );
        /***/       ApplicationDefault[ AT_PageHeight ] = Dbl2String( 269.5 );
        /***/       ApplicationDefault[ AT_TopPageMargin ] = Dbl2String( 12.0 );
        /***/        ApplicationDefault[ AT_BottomPageMargin ] = Dbl2String( 12 );
        /***/       ApplicationDefault[ AT_RightPageMargin ] = Dbl2String( 12 );
        /***/       ApplicationDefault[ AT_LeftPageMargin ] = Dbl2String( 18 );
        /***/       ApplicationDefault[ AT_BorderFileName ] = "big_and_little_line.jpg";
        /***/        ApplicationDefault[ AT_BorderSize ] = Dbl2String( 4 );
        /***/        ApplicationDefault[ AT_ShowBorder ] = "true";
        ApplicationDefault[ AT_ShowTitle ] = "true";
        ApplicationDefault[ AT_ShowSubTitle ] = "true";
        /***/       ApplicationDefault[ AT_Orientation ] = OrientationStrings[ Design::AT_Portrait ];
        ApplicationDefault[ AT_TopContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_BottomContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_LeftContentMargin ] = Dbl2String( 2 );
        ApplicationDefault[ AT_RightContentMargin ] = Dbl2String( 2 );
        /***/       ApplicationDefault[ AT_OverSizePaper ] = "false";
        /***/        ApplicationDefault[ AT_PaperHeight ] = Dbl2String( 269.5 );
        /***/        ApplicationDefault[ AT_PaperWidth ] = Dbl2String( 208.25 );
    }



    void PageDefaults::Save( wxXmlNode* xmlNode )
    {
        Defaults::SaveDefault( xmlNode, AT_OverSizePaper );
        Defaults::SaveDefault( xmlNode, AT_PaperHeight );
        Defaults::SaveDefault( xmlNode, AT_PaperWidth );
        Defaults::SaveDefault( xmlNode, AT_PageWidth );
        Defaults::SaveDefault( xmlNode, AT_PageHeight );
        Defaults::SaveDefault( xmlNode, AT_TopPageMargin );
        Defaults::SaveDefault( xmlNode, AT_BottomPageMargin );
        Defaults::SaveDefault( xmlNode, AT_RightPageMargin );
        Defaults::SaveDefault( xmlNode, AT_LeftPageMargin );
        Defaults::SaveDefault( xmlNode, AT_BorderFileName );
        Defaults::SaveDefault( xmlNode, AT_BorderSize );
        Defaults::SaveDefault( xmlNode, AT_ShowCatNbr );
        Defaults::SaveDefault( xmlNode, AT_ShowTitle );
        Defaults::SaveDefault( xmlNode, AT_ShowTitle );
        Defaults::SaveDefault( xmlNode, AT_ShowTitle );
        Defaults::SaveDefault( xmlNode, AT_ShowSubTitle );
        Defaults::SaveDefault( xmlNode, AT_ShowSubTitle );
        Defaults::SaveDefault( xmlNode, AT_GrayScaleImages );
        Defaults::SaveDefault( xmlNode, AT_StampNamePosition );
        Defaults::SaveDefault( xmlNode, AT_Orientation );

    }

}