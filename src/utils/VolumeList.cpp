/**
 * @file VolumeList.cpp
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

#include "Defs.h"
#include "utils/VolumeList.h"
#include "utils/XMLUtilities.h"
#include "toc/TOCDefs.h"


namespace Utils {


    wxXmlNode* VolumeList::AddChild( wxXmlNode* child )
    {
        wxString label;

        wxString nodeName = child->GetName( );
        Utils::TOCBaseType  nodeType = Utils::FindTOCBaseType( nodeName );
        if ( nodeType == Utils::TOC_Volume )
        {

            // make the volume
            wxString filename = Utils::GetAttrStr( child, "FileName" );
            Utils::Volume* vol = NewVolumeInstance( filename );

            vol->Load( );

            wxString volName = vol->GetName( );
            Utils::SetAttrStr( child, "VolumeName", volName );

            // Add it to the catalog List
            Insert( volName, vol );

        }

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

    bool VolumeList::Clear( )
    {
        // I'm not clear on whether this does a delete on the underlying object
        // i.e., this may be a huge memory leak
        m_volumeArray.clear( );
        m_menuIDArray.clear( );
        return true;
    }

    void VolumeList::dumpArray( wxArrayString& array )
    {
        for ( int j = 0; j < array.Count( ); j++ )
        {
            wxString str = array.Item( j );
            std::cout << str << " ";
        }
        std::cout << "\n";
    }

    wxTreeItemId VolumeList::FindMenuID( int id )
    {
        MenuIDArray::iterator itr = FindMenuIDIterator( id );
        if ( itr != m_menuIDArray.end( ) )
        {
            return itr->second;
        }

        return wxTreeItemId( 0 );
    }

    MenuIDArray::iterator VolumeList::FindMenuIDIterator( int id )
    {
        MenuIDArray::iterator itr;
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


    Utils::Volume* VolumeList::FindVolume( wxString str )
    {
        VolumeArray::iterator itr = FindVolumeIterator( str );
        if ( itr != m_volumeArray.end( ) )
        {
            return itr->second;
        }

        return ( Utils::Volume* ) 0;
    }

    VolumeArray::iterator VolumeList::FindVolumeIterator( wxString str )
    {
        VolumeArray::iterator itr;
        int i = m_volumeArray.size( );

        for ( itr = m_volumeArray.begin( );
            itr != m_volumeArray.end( ); itr++ )
        {
            Volume* vol = itr->second;
            if ( !str.Cmp( vol->GetName( ) ) )
            {
                return itr;
            }
        }
        return m_volumeArray.end( );
    };

    Utils::Volume* VolumeList::GetVolume( )
    {
        if ( m_currVolume )
        {
            if ( !m_volumeArray.empty( ) )
            {
                return m_currVolume;
            }
        }
        return ( Utils::Volume* ) 0;
    };


    void VolumeList::Insert( int id, wxTreeItemId treeId )
    {
        m_menuIDArray.insert( std::make_pair( id, treeId ) );
    }

    void VolumeList::Insert( wxString str, Utils::Volume* vol )
    {
        m_volumeArray.insert( std::make_pair( str, vol ) );
    }

    void VolumeList::RemoveVolume( wxString name )
    {
        VolumeArray::iterator itr = FindVolumeIterator( name );
        m_volumeArray.erase( itr );
    }

    void VolumeList::RemoveVolume( Volume* vol )
    {
        wxString name = vol->GetName( );
        RemoveVolume( name );
    }

    void VolumeList::SaveDirtyVolumes( )
    {
        Utils::VolumeArray::iterator it = m_volumeArray.begin( );

        // Iterate through the map and print the elements
        while ( it != m_volumeArray.end( ) )
        {
            Utils::Volume* volume = ( Utils::Volume* ) ( it->second );
            if ( volume->IsDirty( ) )
            {
                volume->Save( );
            }
            ++it;
        }
    };

    void VolumeList::SaveVolumes( )
    {
        Utils::VolumeArray::iterator it = m_volumeArray.begin( );

        // Iterate through the map and print the elements
        while ( it != m_volumeArray.end( ) )
        {
            Utils::Volume* volume = ( Utils::Volume* ) ( it->second );
            volume->Save( );
            ++it;
        }
    };

    void VolumeList::SetCurrentVolume( Volume* vol ) {
        m_currVolume = vol;
    };

    int WayToSort( Utils::Volume* sect1, Utils::Volume* sect2 )
    {
        wxString name1 = sect1->GetName( );
        wxString name2 = sect2->GetName( );
        return name1.compare( name2 );
    }

}