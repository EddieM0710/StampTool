

/**
 * @file CatalogCode.cpp
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

 //#include "catalog/CatalogCode.h"
#include "Defs.h"
#include "Settings.h"
#include "utils/Project.h"
#include "catalog/CatalogCode.h"
#include <wx/datetime.h>
#include <wx/strconv.h>
#include <wx/tokenzr.h>
#include <cstdio>
#include "utils/XMLUtilities.h"
#include "collection/CollectionList.h"


namespace Catalog {

    wxString MakeImageName( wxString catCode )
    {
        catCode.Trim( true );
        catCode.Trim( false );

        catCode.Replace( ":", "_" );
        catCode.Replace( " ", "_" );
        catCode.Append( ".jpg" );
        return catCode;
    }
    void GetCodes( wxString catCodeStr, wxString& catalog, wxString& country, wxString& code )
    {
        catCodeStr.Trim( );
        catCodeStr.Trim( false );

        int pos = catCodeStr.Find( ":" );
        catalog = catCodeStr.Mid( 0, pos );
        catCodeStr = catCodeStr.Mid( pos + 1 );
        pos = catCodeStr.Find( " " );
        country = catCodeStr.Mid( 0, pos );
        code = catCodeStr.Mid( pos + 1 );
    }
    CatalogCode::CatalogCode( wxString codeList )
    {
        m_codeList = codeList;
        // m_codes.Empty( );
        m_codes.Clear( );
        wxString delim = ",";
        if ( !m_codeList.IsEmpty( ) )
        {
            int cnt = 0;
            wxStringTokenizer tokenizer( m_codeList, delim, wxTOKEN_DEFAULT );
            while ( tokenizer.HasMoreTokens( ) )
            {
                wxString token = tokenizer.GetNextToken( );
                m_codes.Add( token );
                m_codes[ cnt ].Trim( true );
                m_codes[ cnt ].Trim( false );
                cnt++;
            }
        }
    };

    wxString CatalogCode::GetPreferredCatalogCode( wxString cat )
    {
        if ( m_codes.IsEmpty( ) )  return "";
        for ( size_t k = 0; k < m_codes.GetCount( ); k++ )
        {
            if ( m_codes[ k ].StartsWith( cat ) )
            {
                return m_codes[ k ];
            }
        }
        return m_codes[ 0 ];
    }


    wxString CatalogCode::FindImageName( )
    {
        wxString preferredName = MakeImageName(
            GetPreferredCatalogCode(
                GetSettings( )->GetCatalogID( ) ) );
        wxString  str = GetProject( )->GetImageFullPath( preferredName );

        if ( GetProject( )->ImageExists( str ) )
        {
            return preferredName;
        }
        // preferred dosent exist so keep lookng ;
        for ( size_t k = 0; k < m_codes.GetCount( ); k++ )
        {
            wxString filename = MakeImageName( m_codes[ k ] );

            wxString str = GetProject( )->GetImageFullPath( filename );

            if ( GetProject( )->ImageExists( str ) )
            {
                return filename;
            }
        }

        return preferredName;
    }

    bool CatalogCode::IsCatalogCode( wxString catCode )
    {
        for ( size_t k = 0; k < m_codes.GetCount( ); k++ )
        {
            if ( !catCode.Cmp( m_codes[ k ] ) )
            {
                return true;
            }
        }
        return false;
    }
}
