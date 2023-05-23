/**
* @file layout / Font.h
* @author Eddie Monroe
* @brief
* @version 0.1
* @date 2022 - 02 - 04
*
*@copyright Copyright( c ) 2022
*
*This file is part of StampTool.
*
*StampTool is free software : you can redistribute it and /or modify it under the
* terms of the GNU General Public License as published by the Free Software Foundation,
* either version 3 of the License, or any later version.
*
*StampTool is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
* PARTICULAR PURPOSE.See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* StampTool.If not, see <https://www.gnu.org/licenses/>.
*
*/

#ifndef ImageZip_H
#define ImageZip_H

#include <wx/string.h>
#include <wx/datstrm.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <iostream>
#include <wx/wfstream.h>


namespace Utils {

    // int FindFont( FontMap& list, wxFont font, wxColor color );

    class ImageZip
    {
    public:

        ImageZip( )
        {

        };
        ~ImageZip( ) {};
        void CopyFileToZip( wxString file, bool flat = true );
        void InitZipOutFile( wxString zipOutFullName );
        wxFFileOutputStream& m_out;
        wxZipOutputStream& m_zipOut;
        wxTextOutputStream& m_imageOut;
    };
}
#endif