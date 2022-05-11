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

#include "CSV.h"
#include "Classification.h"


bool Classification::IsOK( void )
{
    if ( GetElement( ) )
    {
        const char* name = GetElement( )->GetName( );
        if ( !NodeNameStrings.Item( NT_Catalog ).Cmp( name )
            || !NodeNameStrings.Item( NT_Period ).Cmp( name )
            || !NodeNameStrings.Item( NT_Year ).Cmp( name )
            || !NodeNameStrings.Item( NT_Emission ).Cmp( name ) )
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
        GetElement( )->DeleteAttribute(CT_Names[ type ]);
        GetElement( )->AddAttribute( CT_Names[ type ], val.char_str( ) );
    }
}

wxString Classification::GetAttr( ClassificationTypes type )
{
    if ( IsOK( ) )
    {
         return  GetElement( )->GetAttribute( CT_Names[ type ] );
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
