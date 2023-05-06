/**
 * @file Classification.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
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

#include "utils/CSV.h"
#include "Classification.h"
#include "utils/XMLUtilities.h"



namespace Catalog {

    ClassificationTypes Classification::FindDataType( wxString name )
    {
        for ( int i = CT_Title; i < CT_NbrTypes; i++ )
        {
            if ( !name.Cmp( ClassificationNames[ i ] ) )
            {
                return ( ClassificationTypes ) i;
            }
        }
        return ( ClassificationTypes ) -1;
    }

    wxString Classification::GetAttr( ClassificationTypes type )
    {
        if ( IsOK( ) )
        {
            const wxXmlAttribute* attr = Utils::GetAttribute( GetCatXMLNode( ), ClassificationNames[ type ] );
            if ( attr )
            {
                return wxString( attr->GetValue( ) );
            }
        }
        return wxString( "" );
    }

    bool Classification::IsMultiple( void )
    {
        return true;
    }

    bool Classification::IsOK( void )
    {
        if ( GetCatXMLNode( ) )
        {
            const char* name = GetCatXMLNode( )->GetName( );
            if ( !CatalogBaseNames[ NT_Catalog ].Cmp( name )
                || !CatalogBaseNames[ NT_Period ].Cmp( name )
                || !CatalogBaseNames[ NT_Year ].Cmp( name )
                || !CatalogBaseNames[ NT_Emission ].Cmp( name ) )
            {
                return true;
            }
        }
        return false;
    };

    void Classification::SetAttr( ClassificationTypes type, wxString val )
    {
        if ( IsOK( ) )
        {
            Utils::SetAttrStr( GetCatXMLNode( ), ClassificationNames[ type ], val );
        }
    }

}