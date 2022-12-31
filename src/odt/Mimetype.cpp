/* 
 * @file Mimetype.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * This file is part of AlbumGenerator.
 * 
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 * 
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#include "odt/Mimetype.h"
#include "odt/Document.h"
#include <iostream>
#include "Defs.h"
#include "ODTDefs.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include "wx/string.h"



#define  MIMETYPE  "application/vnd.oasis.opendocument.text"

namespace ODT {

    //***********************************


    bool MimeType::Save( )
    {

        bool status = false;

        wxString str = ODTDoc( )->GetDocFilesDir() + "/mimetype";
       wxFileOutputStream l_file( str );

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