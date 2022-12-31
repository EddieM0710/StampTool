/* 
 * @file Settings.cpp
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
#include "odt/Document.h"
#include "utils/Project.h"
#include "utils/Settings.h"
#include <iostream>
#include "Defs.h"

namespace ODT {

    Settings::Settings( )
    {
        m_settings = new wxXmlDocument( );
        wxString configDir = GetGeneratorData()->GetSettings()->GetConfigurationDirectory();
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

        wxString str = ODTDoc( )->GetDocFilesDir() + "/settings.xml";
        if ( !m_settings->Save( str ) )
        {
            ReportError( "Settings::Save", "Failed to save Settings", true );
        }
        return true;
    }
}