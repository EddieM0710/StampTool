#include "utils/Project.h"
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