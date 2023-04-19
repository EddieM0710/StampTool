/**
 * @file ToolData.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright ( c ) 2022
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
 **************************************************/
#include <wx/log.h>

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogVolume.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"
#include "gui/ToolData.h" 
#include "utils/Settings.h"
#include "utils/Project.h"

#include "design/AlbumVolume.h"


ToolData::ToolData( ) {

    // m_albumVolume = 0;
    // m_catalogPageTreeCtrl = 0;
    // m_albumPageTreeCtrl = 0;
    // m_designTreeCtrl = 0;
    // m_stampDescriptionPanel = 0;
    // m_project = 0;
    // m_settings = 0;
    m_catalogData = new Catalog::CatalogData( );
    m_albumData = new Design::AlbumData( this );

};

void ToolData::InitToolData( )
{
    // m_albumVolume = 0;
    // m_catalogPageTreeCtrl = 0;
    // m_albumPageTreeCtrl = 0;
    // m_designTreeCtrl = 0;
    // m_stampDescriptionPanel = 0;
    m_settings = new Utils::Settings( );
    m_project = new Utils::Project( );
    m_StampAlbumCatalogLink = new Utils::StampList( );

    m_project->InitProject( );
    m_settings->InitSettings( );

    if ( m_settings->GetLoadLastFileAtStartUp( ) )
    {
        m_project->SetProjectFilename( m_settings->GetLastFile( ) );
    }
}


void ToolData::FileNewProject( wxString prjName )
{
    m_project->SetProjectFilename( prjName );
    wxString lastFile = wxGetCwd( );
    lastFile += "/" + prjName;
    GetSettings( )->SetLastFile( lastFile );
    //LoadNewDesign( );
   // LoadNewCatalog( );
}

// Load the Catalog and Design data then populate trees
void ToolData::LoadData( )
{
    bool state = wxLog::IsEnabled( );
    m_catalogData->LoadData( );
    m_albumData->LoadData( );
    ;
}

void ToolData::FileOpenProject( wxString filename )
{
    m_project->SetProjectFilename( filename );
    wxString lastFile = wxGetCwd( );
    lastFile += "/" + filename;
    GetSettings( )->SetLastFile( lastFile );
    m_project->LoadProjectXML( );
    LoadData( );
}

void ToolData::FileSaveProject( )
{
    m_settings->Save( );
    m_project->Save( );
}

void ToolData::FileSaveAsProject( wxString filename )
{
    m_project->SetProjectFilename( filename );
    wxString lastFile = wxGetCwd( );
    lastFile += "/" + filename;
    GetSettings( )->SetLastFile( lastFile );
    FileSaveProject( );
}


