/**
 * @file Specimen.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
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
        if ( GetElement( ) )
        {
            if ( Utils::IsCatalogNodeType( GetElement( ), Catalog::NT_Specimen ) )
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
            Utils::SetAttribute( GetElement( ), ItemDataNames[ type ], val );
        };
    }

    wxString Specimen::GetAttr( ItemDataTypes type )
    {
        if ( IsOK( ) )
        {
            const wxXmlAttribute* attr = Utils::GetAttribute( GetElement( ), ItemDataNames[ type ] );
            if ( attr )
            {
                return wxString::FromUTF8Unchecked( attr->GetValue( ) );
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
        return GetElement( );
    }
}