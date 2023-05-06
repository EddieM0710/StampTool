/**
 * @file CatalogCode.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2021-03-01
 *
 * @copyright Copyright ( c ) 2021
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

#include "catalog/CatalogCode.h"
#include <wx/strconv.h>
#include "utils/XMLUtilities.h"

namespace Catalog {

    wxString CatalogCode::GetAttr( CatalogCodeTypes type )
    {
        if ( IsOK( ) )
        {
            wxXmlAttribute* attr = Utils::GetAttribute( GetCatXMLNode( ), CatalogCodeNames[ type ] );
            if ( attr )
            {
                return attr->GetValue( );
            }
        }
        return wxString( "" );
    }

    wxString CatalogCode::GetCatalog( )
    {
        return GetAttr( CC_Catalog );
    };

    wxString CatalogCode::GetCountry( )
    {
        return GetAttr( CC_Country );
    };

    wxXmlNode* CatalogCode::GetData( wxVector<wxVariant>* data )
    {
        data->push_back( GetCatalog( ) );
        data->push_back( GetCountry( ) );
        data->push_back( GetID( ) );
        return GetCatXMLNode( );
    }

    wxString CatalogCode::GetID( )
    {
        return GetAttr( CC_ID );
    };

    bool CatalogCode::IsOK( )
    {
        if ( GetCatXMLNode( ) )
        {
            return true;
        }
        return false;
    }

    void CatalogCode::SetAttr( CatalogCodeTypes type, wxString val )
    {
        if ( IsOK( ) )
        {
            Utils::SetAttrStr( GetCatXMLNode( ), CatalogCodeNames[ type ], val );
        };
    }

    void CatalogCode::SetCatalog( wxString val )
    {
        SetAttr( CC_Catalog, val );
    };

    void CatalogCode::SetCountry( wxString val )
    {
        SetAttr( CC_Country, val );
    };

    void CatalogCode::SetID( wxString val )
    {
        SetAttr( CC_ID, val );
    };

}