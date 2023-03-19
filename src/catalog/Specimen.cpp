/**
 * @file Specimen.cpp
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
 **************************************************/

 
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Specimen.h"
#include "utils/XMLUtilities.h"
#include <wx/strconv.h>

namespace Catalog { 

    bool Specimen::IsOK( )
    { 
        if ( GetCatXMLNode( ) )
        { 
            if ( Catalog::IsCatalogBaseType( GetCatXMLNode( ), Catalog::NT_Specimen ) )
            { 
                return true;
            }
        }
        return false;
    }

    void Specimen::SetAttr( ItemDataTypes type, wxString val )
    { 
        if ( IsOK( ) )
        { 
            Utils::SetAttrStr( GetCatXMLNode( ), ItemDataNames[ type ], val );
        };
    }

    wxString Specimen::GetAttr( ItemDataTypes type )
    { 
        if ( IsOK( ) )
        { 
            const wxXmlAttribute* attr = Utils::GetAttribute( GetCatXMLNode( ), ItemDataNames[ type ] );
            if ( attr )
            { 
                return attr->GetValue( );
            }
        }
        return wxString( "" );
    }

    wxXmlNode* Specimen::GetData( wxVector<wxVariant>* data )
    { 
        data->push_back( GetType( ) );
        data->push_back( GetCondition( ) );
        data->push_back( GetValue( ) );
        data->push_back( GetLocation( ) );
        data->push_back( GetRemarks( ) );
        return GetCatXMLNode( );
    }
}