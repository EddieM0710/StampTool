/**
 * @file TOCDefs.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-28
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
 * *
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "toc/TOCDefs.h"
#include "utils/XMLUtilities.h"

namespace Utils {

    const wxString TOCBaseNames[ TOC_NbrTypes ] = {
        "Section",
        "Volume", "None" };

    TOCBaseType FindTOCBaseType( wxXmlNode* element )
    {
        wxString name = element->GetName( );

        for ( int i = 0; i < TOC_NbrTypes; i++ )
        {
            if ( !name.Cmp( TOCBaseNames[ i ] ) )
            {
                return ( Utils::TOCBaseType ) i;
            }
        }
        return ( Utils::TOCBaseType ) -1;
    };
    TOCBaseType FindTOCBaseType( wxString name )
    {
        wxString baseName;

        for ( int i = 0; i < TOC_NbrTypes; i++ )
        {
            baseName = TOCBaseNames[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( Utils::TOCBaseType ) i;
            }
        }
        return ( Utils::TOCBaseType ) -1;
    };

}