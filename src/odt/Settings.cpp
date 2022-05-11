#include "odt/Settings.h"
#include "odt/Document.h"
#include "utils/Project.h"
#include "utils/Settings.h"
#include <iostream>
#include "Defs.h"

namespace ODT {

    Settings::Settings( )
    {
        m_settings = new wxXmlDocument( );
        wxString configDir = GetProject()->GetLSettings()->GetConfigurationDirectory();
        wxString settingsTemplate = configDir + "/template/settings.xml";
        if ( !m_settings->Load( settingsTemplate ) )
        {
            ReportError( "Settings::Settings", "Settings failed on Load", true );
        }
        // std::cout << "dump Settings input\n";
        //  dump(m_settings);
        // std::cout << "***********************************************\n";
    }

    bool Settings::Save( )
    {
        // std::cout << "dump Settings output\n";
        //     dump(m_settings);
        // std::cout << "***********************************************\n";

        wxString str = ODTDoc( )->MakeAbsolute( "settings.xml" );
        if ( !m_settings->Save( str ) )
        {
            ReportError( "Settings::Save", "Failed to save Settings", true );
        }
        return true;
    }
}