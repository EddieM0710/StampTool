/**
 * @file Classification.cpp
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

#include "utils/CSV.h"
#include "Classification.h"
#include "utils/XMLUtilities.h"


namespace Catalog {


    bool Classification::IsOK( void )
    {
        if ( GetNodeElement( ) )
        {
            const char* name = GetNodeElement( )->GetName( );
            if ( !CatalogNodeNames[ NT_Catalog ].Cmp( name )
                || !CatalogNodeNames[ NT_Period ].Cmp( name )
                || !CatalogNodeNames[ NT_Year ].Cmp( name )
                || !CatalogNodeNames[ NT_Emission ].Cmp( name ) )
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
            Utils::SetAttrStr( GetNodeElement( ), CT_Names[ type ], val );
        }
    }

    wxString Classification::GetAttr( ClassificationTypes type )
    {
        if ( IsOK( ) )
        {
            const wxXmlAttribute* attr = Utils::GetAttribute( GetNodeElement( ), CT_Names[ type ] );
            if ( attr )
            {
                return wxString( attr->GetValue( ) );
            }
        }
        return wxString( "" );
    }


    ClassificationTypes Classification::FindDataType( wxString name )
    {
        for ( int i = CT_Title; i < CT_NbrTypes; i++ )
        {
            if ( !name.Cmp( CT_Names[ i ] ) )
            {
                return ( ClassificationTypes )i;
            }
        }
        return ( ClassificationTypes )-1;
    }

    bool Classification::IsMultiple( void )
    {
        return true;
    }

}