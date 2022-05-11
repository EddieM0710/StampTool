#include "odt/Document.h"
#include "utils/Project.h"
#include "utils/Settings.h"
#include <iostream>
#include "Defs.h"
#include <wx/datetime.h>

namespace ODT {

    Meta::Meta( )
    {
        m_meta = new wxXmlDocument( );
        wxString configDir = GetProject( )->GetSettings()->GetConfigurationDirectory( );
        wxString metaTemplate = configDir + "/template/meta.xml";
        if ( !m_meta->Load( metaTemplate ) )
        {
            // debug message
            ReportError( "Meta::Meta", " Meta Load failed", true );
        }
    }
    //***********************************
    bool Meta::Save( )
    {
        wxString str = ODTDoc( )->MakeAbsolute( "meta.xml" );
        if ( !m_meta->Save( str ) )
        {
            ReportError( "Meta::Save", " Mata save file failed", true );
        }
        return true;
    }

    //***********************************


    // void UpdataMetaDoc()
    // {
    //     wxDateTime now = wxDateTime::Now();
    //     wxString timeDate = now.Format();
    // }
}