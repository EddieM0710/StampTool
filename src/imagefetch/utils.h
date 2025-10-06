// utils.h
#pragma once
#include <wx/string.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/mstream.h>
#include <wx/url.h>
#include <wx/file.h>
#include <wx/wfstream.h>
#include <wx/uri.h>
#include <wx/datetime.h>

#ifdef __WXMSW__
  #include <bcrypt.h>
  #pragma comment( lib, "bcrypt.lib" )
#endif

inline wxString Urlize( wxString s )
{
    // 1 ) zap simple HTML entities like &amp;
    while ( true ) {
        int amp = s.Find( '&' );
        if ( amp == wxNOT_FOUND ) break;
        int semi = s.find( ';', amp + 1 );
        if ( semi == wxNOT_FOUND ) break;
        s.replace( amp, semi - amp + 1, "_" );
    }
    // 2 ) remove forbidden chars
    const wxString bad = wxT( ".\"><\\:/?#[]@!$&'( )*+, ;=" );
    wxString out;
    out.reserve( s.length( ) );
    for ( auto ch : s ) {
        if ( bad.Find( ch ) == wxNOT_FOUND ) out.append( ch );
    }
    // 3 ) collapse spaces/underscores to single underscore
    wxString out2;
    const wxString space = wxT( " \t\n\r_" );
    bool prevUnd = false;

    for ( auto ch : out ) {
        bool spacey = ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '_' );
        if ( spacey ) {
            if ( !prevUnd ) { out2.append( '_' ); prevUnd = true; }
        } else {
            out2.append( ch );
            prevUnd = false;
        }
    }
    // 4 ) trim underscores
    while ( !out2.empty( ) && out2.at( 0 ) == '_' )
    {
        out2.erase( 0, 1 );
    }
    while ( !out2.empty( ) && out2.Last( ) == '_' ) 
    {
        out2.erase( out2.length( )-1, 1 );
    }
    return out2;
}

inline wxString SplitPicIdTwoParts( unsigned long long pid )
{
    wxString s = wxString::Format( "%llu", pid );
    if ( s.length( ) <= 3 ) return "0/" + s;
    return s.Left( s.length( )-3 ) + "/" + s.Right( 3 );
}

inline wxString BuildImageUrl( unsigned long long picId, const wxString& itemName, bool full=true )
{
    wxChar size = full ? 'f' : 't';
    return wxString::Format( "https://i.colnect.net/images/%c/%s/%s.jpg", 
                            size, SplitPicIdTwoParts( picId ), Urlize( itemName ) );
}

#ifdef __WXMSW__
// HMAC-SHA256 ( hex ) using Windows CNG
inline wxString HmacSha256Hex( const wxString& keyUtf8, const wxString& msgUtf8 )
{
    wxCharBuffer k = keyUtf8.utf8_str( );
    wxCharBuffer m = msgUtf8.utf8_str( );

    BCRYPT_ALG_HANDLE hAlg = nullptr;
    BCRYPT_HASH_HANDLE hHash = nullptr;
    if ( BCryptOpenAlgorithmProvider( &hAlg, BCRYPT_SHA256_ALGORITHM, nullptr, BCRYPT_ALG_HANDLE_HMAC_FLAG ) ) return {};

    DWORD objLen=0, cb=0;
    if ( BCryptGetProperty( hAlg, BCRYPT_OBJECT_LENGTH, ( PUCHAR )&objLen, sizeof( objLen ), &cb, 0 ) ) { BCryptCloseAlgorithmProvider( hAlg, 0 ); return {}; }
    std::vector<unsigned char> obj( objLen );

    DWORD hashLen=0;
    if ( BCryptGetProperty( hAlg, BCRYPT_HASH_LENGTH, ( PUCHAR )&hashLen, sizeof( hashLen ), &cb, 0 ) ) { BCryptCloseAlgorithmProvider( hAlg, 0 ); return {}; }
    std::vector<unsigned char> digest( hashLen );

    if ( BCryptCreateHash( hAlg, &hHash, obj.data( ), objLen, ( PUCHAR )k.data( ), ( ULONG )strlen( k ), 0 ) ) { BCryptCloseAlgorithmProvider( hAlg, 0 ); return {}; }
    if ( BCryptHashData( hHash, ( PUCHAR )m.data( ), ( ULONG )strlen( m ), 0 ) ) { BCryptDestroyHash( hHash ); BCryptCloseAlgorithmProvider( hAlg, 0 ); return {}; }
    if ( BCryptFinishHash( hHash, digest.data( ), hashLen, 0 ) ) { BCryptDestroyHash( hHash ); BCryptCloseAlgorithmProvider( hAlg, 0 ); return {}; }
    BCryptDestroyHash( hHash );
    BCryptCloseAlgorithmProvider( hAlg, 0 );

    static const char hex[] = "0123456789abcdef";
    wxString out; out.reserve( hashLen*2 );
    for ( auto b : digest ) {
        out.append( hex[( b>>4 )&0xF] );
        out.append( hex[b&0xF] );
    }
    return out;
}
#endif
