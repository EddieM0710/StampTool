/**
 * @file CatalogList.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/filename.h>

#include "catalog/CatalogList.h"
#include "gui/CatalogPanel.h"
#include "catalog/CatalogData.h"
#include "utils/XMLUtilities.h"
#include "gui/CatalogTOCTreeCtrl.h"

#include "Defs.h"


namespace Catalog {


    Catalog::CatalogVolume* CatalogList::NewVolumeInstance( wxString filename )
    {
        Catalog::CatalogVolume* catalogVolume = new Catalog::CatalogVolume( );
        SetCurrentVolume( catalogVolume );
        catalogVolume->SetFilename( filename );
        return catalogVolume;
    }

    Catalog::CatalogVolume* CatalogList::AddNewVolume( wxString filename )
    {
        // make the volume
        Catalog::CatalogVolume* vol = NewVolumeInstance( filename );

        wxFileName catFile( filename );
        wxString volName = catFile.GetName( );
        vol->LoadDefaultDocument( volName );

        // Add it to the ProjectList
        wxXmlNode* newNode = GetProject( )->AddNewCatalogVolume( filename, volName );

        // Add it to the catalog List
        Insert( volName, vol );

        // Add it to the tree
        wxTreeItemId treeRootID = GetCatalogTOCTreeCtrl( )->GetRootItem( );

        GetCatalogTOCTreeCtrl( )->AddChild( treeRootID, newNode, GetCatalogTOCTreeCtrl( )->GetMenu( ) );

        return vol;
    }


    bool CatalogList::ImportCSV( wxString csvFilename )
    {
        wxFileName csvFile( csvFilename );
        wxString ext = csvFile.GetExt( );
        if ( !ext.CmpNoCase( "csv" ) )
        {

            wxString cwd = wxGetCwd( );
            wxFileName catalogFile;// = csvFile;
            catalogFile.SetPath( cwd );

            wxString volName = csvFile.GetName( );
            catalogFile.SetName( volName );
            catalogFile.SetExt( "cat" );

            // Get then name to save as
            wxFileDialog openFileDialog(
                GetFrame( ), _( "Select directory and file to save the new cat file to." ),
                wxGetCwd( ),
                catalogFile.GetFullName( ),
                "Catalog XML files(*.cat)|*.cat", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
            if ( openFileDialog.ShowModal( ) == wxID_CANCEL )
            {
                return  false; // the user changed idea...
            }
            wxFileName catFile( openFileDialog.GetPath( ) );
            catFile.MakeRelativeTo( cwd );

            // Make a new volume
            wxString newFile = catFile.GetFullPath( );
            Catalog::CatalogVolume* catalogVolume = NewVolumeInstance( newFile );
            bool readStatus = catalogVolume->LoadCSV( csvFile.GetFullPath( ) );
            if ( readStatus )
            {
                // Add it to the ProjectList
                wxXmlNode* newNode = GetProject( )->AddNewCatalogVolume( newFile, volName );


                // Add it to the catalog List
                Insert( volName, catalogVolume );

                // Add it to the tree
                wxTreeItemId treeRootID = GetCatalogTOCTreeCtrl( )->GetRootItem( );
                GetCatalogTOCTreeCtrl( )->AddChild( treeRootID, newNode, GetCatalogTOCTreeCtrl( )->GetMenu( ) );

            }
            return readStatus;
        }
        return false;
    }


    Catalog::CatalogVolume* CatalogList::NewCatalogVolume( wxString filename )
    {
        CatalogVolume* vol = new CatalogVolume( );
        vol->SetFilename( filename );
        vol->Load( );

        wxString volName = vol->GetName( );
        Catalog::CatalogList* list = GetCatalogData( )->GetCatalogList( );
        list->SetCurrentVolume( vol );
        return vol;
    }
}