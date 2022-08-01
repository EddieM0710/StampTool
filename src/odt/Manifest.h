/**
 * @file Manifest.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-08
 *
 * @copyright Copyright (c) 2022
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
 **************************************************/
#ifndef Manifest_h
#define Manifest_h

#include "odt/ODTDefs.h"

#include <wx/xml/xml.h>

namespace ODT {

    class Manifest
    {
    public:

        Manifest( );
        ~Manifest( ) {};


        void AddManifestFileEntry( wxString fullPath, wxString mediaType );
        bool Save( );
        wxXmlDocument* ManifestXML( ) { return m_manifest; };
    private:
        wxXmlDocument* m_manifest;
    };
}
#endif