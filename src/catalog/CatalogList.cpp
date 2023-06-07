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

#include "Defs.h"

 //#include "StampToolApp.h"
 //#include "gui/StampToolFrame.h"
 //#include "gui/AppData.h"

 //wxDECLARE_APP( StampToolApp );

namespace Catalog {

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

    void CatalogList::BuildVolumeNameStrings( )
    {
        m_volumeNameStrings.Clear( );
        for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
            m_volumeNameStrings.Add( volume->GetVolumeName( ) );
        }
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

    void CatalogList::Load( )
    {

        for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
            volume->Load( );
            // std::cout << " Loaded " << volume->GetVolumeName( ) << "\n";
        }

        if ( m_catalogArray.size( ) > 1 )
        {
            sort( std::begin( m_catalogArray ), std::end( m_catalogArray ) );
        }

        m_volumeNameStrings.Clear( );
        for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
            m_volumeNameStrings.Add( volume->GetVolumeName( ) );
        }
        m_catalogVolumeNdx = 0;

    };

    Catalog::CatalogVolume* CatalogList::NewCatalogVolume( )
    {
        Catalog::CatalogVolume* catalogVolume = Catalog::NewCatalogVolumeInstance( );
        m_catalogArray.push_back( catalogVolume );
        m_catalogVolumeNdx = m_catalogArray.size( ) - 1;
        return catalogVolume;
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

    int WayToSort( Catalog::CatalogVolume* sect1, Catalog::CatalogVolume* sect2 )
    {
        wxString name1 = sect1->GetVolumeName( );
        wxString name2 = sect2->GetVolumeName( );
        return name1.compare( name2 );
    }

}