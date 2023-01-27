/* 
 * @file Meta.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * This file is part of StampTool.
 * 
 * StampTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 * 
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with 
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 * 
 */
#include <wx/sstream.h>
#include <iostream>
#include <wx/datetime.h>

#include "odt/Meta.h"
#include "odt/ODTDefs.h"
#include "odt/Template.h"
#include "odt/Document.h"
#include "utils/Project.h"
#include "utils/Settings.h"
#include "Defs.h"

namespace ODT { 

    Meta::Meta( )
    { 
        m_meta = new wxXmlDocument( );
        wxStringInputStream textStream( ODT::MetaTemplate );

        //wxString configDir = GetToolData( )->GetSettings( )->GetConfigurationDirectory( );
        //wxString metaTemplate = configDir + "/template/meta.xml";
        if ( !m_meta->Load( textStream ) )
        { 
            // debug message
            ReportError( "Meta::Meta", " Meta Load failed", true );
        }
    }
    //***********************************
    bool Meta::Save( )
    { 
        wxString str = ODTDoc( )->GetDocFilesDir( ) +  "/meta.xml" ;
        if ( !m_meta->Save( str ) )
        { 
            ReportError( "Meta::Save", " Mata save file failed", true );
        }
        return true;
    }

    //***********************************


    // void UpdataMetaDoc( )
    // { 
    //     wxDateTime now = wxDateTime::Now( );
    //     wxString timeDate = now.Format( );
    // }
}