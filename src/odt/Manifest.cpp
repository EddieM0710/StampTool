/* 
 * @file Manifest.cpp
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
#include "utils/Settings.h"
#include "utils/XMLUtilities.h"
#include "odt/Manifest.h"
#include "Document.h"
#include <iostream>
#include "Defs.h"

//***********************************

namespace ODT {

    Manifest::Manifest( )
    {
        m_manifest = new wxXmlDocument( );
        wxString configDir = GetGeneratorData()->GetSettings()->GetConfigurationDirectory( );
        wxString manifestTemplate = configDir + "/template/META-INF/manifest.xml";
        if ( !m_manifest->Load( manifestTemplate ) )
        {
            // debug message
            ReportError( "Document::GetManifest", "get Manifest failed", true );
        }
    }

    //***********************************


    void Manifest::AddManifestFileEntry( wxString fullPath, wxString mediaType )
    {
        wxXmlNode* manifestRoot = m_manifest->GetRoot( );
        wxString name = manifestRoot->GetName( );
        wxXmlNode* fileEntry = Utils::AddNewNode( manifestRoot, wxXML_ELEMENT_NODE, "manifest:file-entry" );
        Utils::SetAttrStr( fileEntry, "manifest:full-path", fullPath );
        Utils::SetAttrStr( fileEntry, "manifest:media-type", mediaType );
    }

    bool Manifest::Save( )
    {
        wxString str = ODTDoc( )->MakeAbsolute( "META-INF/manifest.xml" );
        if ( !m_manifest->Save( str ) )
        {
            ReportError( "Manifest::Save", "ODT Manifest failed to save", true );
        }
        return true;
    }
}