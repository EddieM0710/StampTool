

#include "odt/Mimetype.h"
#include <iostream>
#include "Defs.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include "wx/string.h"



#define  MIMETYPE  "application/vnd.oasis.opendocument.text"

namespace ODT {

    //***********************************


    bool MimeType::Save( )
    {

        bool status = false;

        wxFileOutputStream l_file( "mimetype" );

        if ( l_file.IsOk( ) )
        {
            wxTextOutputStream text( l_file );
            //process Header
            text.WriteString( ( const char* )MIMETYPE );
            // if (!l_file.Eof())
            // {
            // }
        }
        l_file.Close( );
        return true;
    }
}