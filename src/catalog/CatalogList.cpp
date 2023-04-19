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
 **************************************************/


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

 // #include <iostream>
#include <wx/filename.h>
// #include <wx/string.h>
// #include "wx/xml/xml.h"
// #include <wx/msgdlg.h>

#include "catalog/CatalogList.h"
#include "gui/CatalogPanel.h"


#include "Defs.h"

// #include "catalog/CatalogDefs.h"
// #include "catalog/Entry.h"

// #include "utils/CSV.h"
// #include "utils/Settings.h"
// #include "utils/Project.h"
// #include "utils/XMLUtilities.h"
#include "StampToolApp.h"
#include "gui/ToolData.h"

wxDECLARE_APP( StampToolApp );

namespace Catalog {

    Catalog::CatalogVolume* CatalogList::NewCatalogVolume( )
    {
        Catalog::CatalogVolume* catalogVolume = Catalog::NewCatalogVolumeInstance( );
        m_catalogArray.push_back( catalogVolume );
        m_catalogVolumeNdx = m_catalogArray.size( ) - 1;
        return catalogVolume;
    };

    bool CatalogList::ClearCatalogArray( )
    {
        while ( !m_catalogArray.empty( ) )
        {
            CatalogVolume* data = m_catalogArray.back( );
            delete data;
            m_catalogArray.pop_back( );
        }
        return true;
    }
    Catalog::CatalogVolume* CatalogList::GetCatalogVolume( )
    {
        if ( m_catalogVolumeNdx >= 0 )
        {
            if ( !m_catalogArray.empty( ) )
            {
                return m_catalogArray.at( m_catalogVolumeNdx );
            }
        }
        return ( Catalog::CatalogVolume* ) 0;
    };

    int wayToSort( Catalog::CatalogVolume* sect1, Catalog::CatalogVolume* sect2 )
    {
        wxString name1 = sect1->GetVolumeName( );
        wxString name2 = sect2->GetVolumeName( );
        return name1.compare( name2 );
    }

    void CatalogList::LoadCatalogVolumes( )
    {

        for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
            volume->LoadXML( );
            wxString name = volume->GetVolumeName( );
            if ( !name.IsEmpty( ) )
            {
                name = volume->GetVolumeFilename( );
                wxFileName fn( name );
                volume->SetVolumeName( fn.GetName( ) );
            }
        }

        if ( m_catalogArray.size( ) > 1 )
        {
            sort( m_catalogArray.begin( ), m_catalogArray.end( ), wayToSort );
        }
        m_volumeNameStrings.Clear( );
        for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
            m_volumeNameStrings.Add( volume->GetVolumeName( ) );
        }
        CatalogPanel* catPanel = wxGetApp( ).GetFrame( )->GetCatalogPagePanel( );
        CatalogPanel* albPanel = wxGetApp( ).GetFrame( )->GetAlbumPagePanel( );
        catPanel->SetVolumeListStrings( m_volumeNameStrings );
        albPanel->SetVolumeListStrings( m_volumeNameStrings );
        m_catalogVolumeNdx = 0;
        catPanel->SetVolumeListSelection( m_catalogVolumeNdx );
        albPanel->SetVolumeListSelection( m_catalogVolumeNdx );

    };

    void CatalogList::SaveCatalogVolumes( )
    {
        for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
            volume->Save( );
        }
    };

    void CatalogList::SetCatalogVolumeNdx( int i ) {
        m_catalogVolumeNdx = i;
        GetCatalogData( )->LoadCatalogTree( );
    };
}