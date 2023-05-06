/**
 * @file Node.cpp
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

#include "catalog/CatalogBase.h"
#include "utils/XMLUtilities.h"

  
namespace Catalog {

    double CatalogBase::GetNodeAttrDbl( wxString name )
    {
        return Utils::GetAttrDbl( m_catXMLNode, name );
    };

    wxString CatalogBase::GetNodeAttrStr( wxString name )
    {
        return Utils::GetAttrStr( m_catXMLNode, name );
    };

    void CatalogBase::SetNodeAttrDbl( wxString name, double val )
    {
        Utils::SetAttrDbl( m_catXMLNode, name, val );
    };

    void CatalogBase::SetNodeAttrStr( wxString name, wxString val )
    {
        Utils::SetAttrStr( m_catXMLNode, name, val );
    };

}
