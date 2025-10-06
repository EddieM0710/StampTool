/*
 * @file ColnectWxClient.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
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
 */

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/wx.h>
#include <wx/webrequest.h>
#include <wx/filesys.h>
//#include <wx/stream.h> // for wxCopyStream
#include <wx/stdpaths.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.h"
#include "defs.h"
#include "ColnectWxClient.h"
#include "external\nlohmann\json.hpp"

// Fixed per your choice:
static const wxString kAppId = "Eddie3Fs"; // your app id
static const wxString kLang = "en";
static const wxString kCat = "stamps";

bool ColnectWxClient::OnInit( )  
{
    bool full = true;
    return true;
}

void ColnectWxClient::FetchAndDownload( wxString itemId, 
                                       const wxString &outPath )
{
    m_itemId = itemId;
    m_outPath = outPath;
    CallFields( );
}

// ---- Build Colnect path and auth headers ----
wxString ColnectWxClient::BuildFieldsPath( ) const
{
    return wxString::Format( "/%s/api/%s/fields/cat/%s", kLang, kAppId, kCat );
}

wxString ColnectWxClient::BuildItemPath( ) const
{
    return wxString::Format( "/%s/api/%s/item/cat/%s/id/%s", kLang, kAppId, kCat, m_itemId );
}


wxString ColnectWxClient::Create_Hmac( wxString msg )
{
    wxString appSecret = wxGetenv( "COLNECT_APP_SECRET" );
    if ( appSecret.empty( ) )
    { 
        wxPrintf( "Set COLNECT_APP_SECRET env var.\n" ); return ""; 
    }   
    return HmacSha256Hex( appSecret, msg );
}

wxVector<WebRequestHeader> ColnectWxClient::MakeAuthHeaders( wxString &pathNoDomain ) 
{
    long ts = ( long )wxDateTime::Now( ).GetTicks( );
    wxString msg = pathNoDomain + ">|<" + wxString::Format( "%ld", ts );

    wxString hmac = Create_Hmac( msg );

    wxVector<WebRequestHeader> hs;
    hs.push_back( {"Capi-Timestamp", wxString::Format( "%ld", ts )} );
    hs.push_back( {"Capi-Hash", hmac} );
    // Long UA is required by Colnect
    hs.push_back( {"User-Agent", "StampTool-Colnect/1.0 ( wxWidgets ) Eddie"} );
    return hs;
}

// ---- Step 1: /fields ( array of names, we find positions ) ----
void ColnectWxClient::CallFields( )
{
    wxString path = BuildFieldsPath( );
    wxWebRequest req = m_session.CreateRequest( this, "https://api.colnect.net" + path );
    for ( auto &h : MakeAuthHeaders( path ) )
        req.SetHeader( h.name, h.value );
    Bind( wxEVT_WEBREQUEST_STATE, &ColnectWxClient::OnFields, this, req.GetId( ) );
    req.Start( );
}

void ColnectWxClient::OnFields( wxWebRequestEvent &e )
{
    if ( e.GetState( ) == wxWebRequest::State_Completed )
    {
        wxString body = e.GetResponse( ).AsString( );
        // Parse as JSON array ( no 3rd-party needed if you prefer; but you already have nlohmann/json )
        // Here, just simple parsing using nlohmann if you keep it; otherwise, look for names by string search.
        // For brevity, assume you still use json.hpp:
        auto j = nlohmann::json::parse( std::string( body.utf8_string( ) ), nullptr, false );
        if ( !j.is_array( ) )
        {
            wxLogError( "Fields: non-array" );
            return;
        }

        m_idxItemName = m_idxFrontPic = -1;
        for ( size_t i = 0; i < j.size( ); ++i )
        {
            if ( j[i].is_string( ) )
            {
                wxString name = wxString::FromUTF8( j[i].get<std::string>( ) );
                // Your API returned "FrontPicture" / "BackPicture"
                if ( name.CmpNoCase( "Name" ) == 0 )
                    m_idxItemName = ( int )i;
                if ( name.CmpNoCase( "FrontPicture" ) == 0 )
                    m_idxFrontPic = ( int )i;
            }
        }
        if ( m_idxItemName < 0 || m_idxFrontPic < 0 )
        {
            wxLogError( "Fields missing: item_name=%d front=%d", m_idxItemName, m_idxFrontPic );
            return;
        }
        CallItem( ); // proceed
    }
    else if ( e.GetState( ) == wxWebRequest::State_Failed )
    {
        wxLogError( "Fields request failed: %s", e.GetErrorDescription( ) );
    }
}

// ---- Step 2: /item …/id/<ID> ( array with values ) ----
void ColnectWxClient::CallItem( )
{
    wxString path = BuildItemPath( );
    auto req = m_session.CreateRequest( this, "https://api.colnect.net" + path );
    for ( auto &h : MakeAuthHeaders( path ) )
        req.SetHeader( h.name, h.value );
    Bind( wxEVT_WEBREQUEST_STATE, &ColnectWxClient::OnItem, this, req.GetId( ) );
    req.Start( );
}

void ColnectWxClient::OnItem( wxWebRequestEvent &e )
{
    if ( e.GetState( ) == wxWebRequest::State_Completed )
    {
        wxString body = e.GetResponse( ).AsString( );
        auto j = nlohmann::json::parse( std::string( body.utf8_string( ) ), nullptr, false );
        if ( !j.is_array( ) || j.empty( ) )
        {
            wxLogError( "Item: unexpected JSON" );
            return;
        }
        const auto &arr = j[0].is_array( ) ? j[0] : j;
        if ( !arr.is_array( ) )
        {
            wxLogError( "Item: inner not array" );
            return;
        }

        // Extract needed positions:
        if ( ( int )arr.size( ) <= m_idxItemName || ( int )arr.size( ) <= m_idxFrontPic )
        {
            wxLogError( "Item: array too short" );
            return;
        }
        wxString itemName = wxString::FromUTF8( arr[m_idxItemName].dump( ) );
        // remove quotes if dump( )
        if ( itemName.length( ) >= 2 && itemName.StartsWith( "\"" ) && itemName.EndsWith( "\"" ) )
            itemName = itemName.Mid( 1, itemName.length( ) - 2 );

        unsigned long long picId = 0;
        if ( arr[m_idxFrontPic].is_string( ) )
        {
            wxString s = wxString::FromUTF8( arr[m_idxFrontPic].get<std::string>( ) );
            s.ToULongLong( &picId );
        }
        else if ( arr[m_idxFrontPic].is_number_integer( ) )
        {
            picId = ( unsigned long long )arr[m_idxFrontPic].get<long long>( );
        }
        else
        {
            wxLogError( "front picture not numeric/string" );
            return;
        }

        m_imgUrl = BuildImageUrl( picId, itemName, m_full );
        CallImage( ); // proceed
    }
    else if ( e.GetState( ) == wxWebRequest::State_Failed )
    {
        wxLogError( "Item request failed: %s", e.GetErrorDescription( ) );
    }
}

// ---- Step 3: GET the image and save it ----
void ColnectWxClient::CallImage( )
{
    auto req = m_session.CreateRequest( this, m_imgUrl );
    req.SetStorage( wxWebRequest::Storage_File );
    // no auth needed
    Bind( wxEVT_WEBREQUEST_STATE, &ColnectWxClient::OnImage, this, req.GetId( ) );
    req.Start( );
}

void ColnectWxClient::OnImage( wxWebRequestEvent& e )
{
    if ( e.GetState( ) == wxWebRequest::State_Completed )
    {
        wxFileName out( m_outPath );
        if ( out.GetFullPath( ) == "." || out.DirExists( ) ) {
            wxURI uri( m_imgUrl );
        } else {
            wxFileName( out ).Mkdir( wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL );
        }

        // wx saved the response to a temp file:
        wxString tmp = e.GetResponse( ).GetDataFile( );
        if ( tmp.empty( ) ) {
            wxLogError( "No data file provided by response ( did you call SetStorage( wxWEBREQUEST_STORE_FILE )? )" );
            return;
        }

        if ( !wxCopyFile( tmp, out.GetFullPath( ), /*overwrite*/true ) ) {
            wxLogError( "Failed to copy %s to %s", tmp, out.GetFullPath( ) );
            return;
        }

        wxLogMessage( "Saved: %s", out.GetFullPath( ) );
    }
    else if ( e.GetState( ) == wxWebRequest::State_Failed )
    {
        wxLogError( "Image request failed: %s", e.GetErrorDescription( ) );
    }
}
