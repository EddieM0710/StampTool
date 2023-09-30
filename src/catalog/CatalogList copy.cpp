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
#include "gui/TOCTreeCtrl.h"

#include "Defs.h"


namespace Catalog {

    bool CatalogList::ClearCatalogArray( )
    {
        m_catalogArray.clear( );
        return true;
    }

    void CatalogList::dumpArray( wxArrayString& array )
    {
        for ( int j = 0; j < array.Count( ); j++ )
        {
            wxString str = array.Item( j );
            std::cout << str << " ";
        }
        std::cout << "\n";
    }
    // void CatalogList::SortNameArray( )
    // {
    //     wxArrayString oldNameStrings = m_volumeNameStrings;
    //     m_volumeNameStrings.Clear( );
    //     for ( int j = 0; j < oldNameStrings.Count( ); j++ )
    //     {
    //         wxString str = oldNameStrings.Item( j );
    //         if ( j == 0 )
    //         {
    //             m_volumeNameStrings.Add( str );
    //         }
    //         else
    //         {
    //             bool done = false;
    //             for ( int i = 0; i < m_volumeNameStrings.Count( ); i++ )
    //             {
    //                 wxString test = m_volumeNameStrings.Item( i );
    //                 if ( test.Cmp( str ) < 0 )
    //                 {
    //                     m_volumeNameStrings.Insert( str, i );
    //                     done = true;
    //                     break;
    //                 }
    //             }
    //             if ( !done )
    //             {
    //                 m_volumeNameStrings.Add( str );
    //             }
    //         }
    //         // dumpArray( m_volumeNameStrings );
    //     }
    // }

    // void CatalogList::BuildVolumeNameStrings( )
    // {
    //     // m_volumeNameStrings.Clear( );
    //     // for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
    //     //     it != std::end( m_catalogArray );
    //     //     ++it )
    //     // {
    //     //     Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
    //     //     m_volumeNameStrings.Add( volume->GetVolumeName( ) );
    //     // }
    //     // SortNameArray( );
    // }

    Catalog::CatalogVolume* CatalogList::GetCatalogVolume( )
    {
        if ( m_currVolume )
        {
            if ( !m_catalogArray.empty( ) )
            {
                return m_currVolume;
            }
        }
        return ( Catalog::CatalogVolume* ) 0;
    };

    // void CatalogList::Load( )
    // {

    //     for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
    //         it != std::end( m_catalogArray );
    //         ++it )
    //     {
    //         Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
    //         volume->Load( );
    //         // std::cout << " Loaded " << volume->GetVolumeName( ) << "\n";
    //     }

    //     // if ( m_catalogArray.size( ) > 1 )
    //     // {
    //     //     sort( std::begin( m_catalogArray ), std::end( m_catalogArray ) );
    //     // }

    //     m_volumeNameStrings.Clear( );
    //     for ( Catalog::CatalogVolumeArray::iterator it = std::begin( m_catalogArray );
    //         it != std::end( m_catalogArray );
    //         ++it )
    //     {
    //         Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *it );
    //         m_volumeNameStrings.Add( volume->GetVolumeName( ) );
    //     }
    //     Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( *std::begin( m_catalogArray ) );

    //     m_currVolume = volume;

    // };


    // Catalog::CatalogVolume* CatalogList::FindVolume( wxString str )
    // {


    //     Catalog::CatalogVolume* vol = m_catalogArray.at( str.ToStdString( ) );
    //     return m_catalogArray[ str.ToStdString( ) ];

    // }
    void CatalogList::Insert( int id, wxTreeItemId treeId )
    {
        m_menuIDArray.insert( std::make_pair( id, treeId ) );
    }

    wxTreeItemId CatalogList::FindMenuID( int id )
    {
        CatalogMenuIDArray::iterator itr = FindMenuIDIterator( id );
        if ( itr != m_menuIDArray.end( ) )
        {
            return itr->second;
        }

        return wxTreeItemId( 0 );
    }

    CatalogMenuIDArray::iterator CatalogList::FindMenuIDIterator( int id )
    {
        CatalogMenuIDArray::iterator itr;
        int i = m_menuIDArray.size( );

        for ( itr = m_menuIDArray.begin( );
            itr != m_menuIDArray.end( ); itr++ )
        {
            int currID = itr->first;
            if ( currID == id )
            {
                return itr;
            }
        }
        return m_menuIDArray.end( );
    };

    void CatalogList::Insert( wxString str, Catalog::CatalogVolume* vol )
    {
        m_catalogArray.insert( std::make_pair( str, vol ) );
    }

    Catalog::CatalogVolume* CatalogList::FindVolume( wxString str )
    {
        CatalogVolumeArray::iterator itr = FindVolumeIterator( str );
        if ( itr != m_catalogArray.end( ) )
        {
            return itr->second;
        }

        return ( Catalog::CatalogVolume* ) 0;
    }

    CatalogVolumeArray::iterator CatalogList::FindVolumeIterator( wxString str )
    {
        CatalogVolumeArray::iterator itr;
        int i = m_catalogArray.size( );

        for ( itr = m_catalogArray.begin( );
            itr != m_catalogArray.end( ); itr++ )
        {
            CatalogVolume* vol = itr->second;
            if ( !str.Cmp( vol->GetVolumeName( ) ) )
            {
                return itr;
            }
        }
        return m_catalogArray.end( );
    };

    // int CatalogList::FindVolumeNameArrayNdx( wxString str )
    // {
    //     for ( int i = 0; i < m_volumeNameStrings.Count( ); i++ )
    //     {
    //         wxString name = ( Catalog::CatalogVolume* ) ( m_volumeNameStrings.Item( i ) );
    //         if ( !str.Cmp( name ) )
    //         {
    //             return i;
    //         }
    //     }
    //     return 0;
    // }
    // Catalog::CatalogVolume* CatalogList::NewCatalogVolume( )
    // {
    //     Catalog::CatalogVolume* catalogVolume = Catalog::NewCatalogVolumeInstance( );
    //     m_catalogArray.insert( catalogVolume );
    //     return catalogVolume;
    // };

    void CatalogList::SaveCatalogVolumes( )
    {
        Catalog::CatalogVolumeArray::iterator it = m_catalogArray.begin( );

        // Iterate through the map and print the elements
        while ( it != m_catalogArray.end( ) )
        {
            Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( it->second );
            volume->Save( );
            ++it;
        }
    };

    void CatalogList::SetCatalogVolume( CatalogVolume* vol ) {
        m_currVolume = vol;
        //        GetCatalogData( )->LoadCatalogTree( );
    };

    int WayToSort( Catalog::CatalogVolume* sect1, Catalog::CatalogVolume* sect2 )
    {
        wxString name1 = sect1->GetVolumeName( );
        wxString name2 = sect2->GetVolumeName( );
        return name1.compare( name2 );
    }
    //

    wxXmlNode* CatalogList::AddChild( wxXmlNode* child )
    {
        wxString label;

        wxString nodeName = child->GetName( );
        Utils::TOCBaseType  nodeType = Utils::FindTOCBaseType( nodeName );
        if ( nodeType == Utils::TOC_Volume )
        {
            wxString filename = Utils::GetAttrStr( child, "FileName" );
            Catalog::CatalogVolume* vol = Catalog::NewCatalogVolumeInstance( );
            vol->SetVolumeFilename( filename );
            vol->Load( );
            wxString volName = vol->GetVolumeName( );
            Utils::SetAttrStr( child, "VolumeName", volName );

            Insert( volName, vol );
            SetCatalogVolume( vol );
        }
        // else if ( nodeType == Utils::TOC_Section )
        // {
        //     wxString volName = GetAttrStr( child, "Name" );
        // }
        // now do it all again for this entrys children
        wxXmlNode* grandChild = child->GetChildren( );
        while ( grandChild )
        {

            // start adding child elements to it.
            AddChild( grandChild );
            grandChild = grandChild->GetNext( );
        }
        return child;
    }

}