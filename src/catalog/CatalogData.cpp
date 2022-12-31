/**
 * @file CatalogData.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
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

#include "catalog/CatalogData.h"
#include "gui/CatalogPanel.h"


#include "Defs.h"

// #include "catalog/CatalogDefs.h"
// #include "catalog/Classification.h"
// #include "catalog/Entry.h"

// #include "utils/CSV.h"
// #include "utils/Settings.h"
// #include "utils/Project.h"
// #include "utils/XMLUtilities.h"
#include "AlbumGenApp.h"
#include "gui/GeneratorData.h"

wxDECLARE_APP( AlbumGenApp );

namespace Catalog {

    Catalog::CatalogVolumeData* CatalogData::NewCatalogVolumeData( )
    {
        Catalog::CatalogVolumeData* catalogVolumeData = Catalog::NewCatalogVolumeDataInstance( );
        m_catalogArray.push_back( catalogVolumeData );
        m_catalogVolumeDataNdx = m_catalogArray.size( ) - 1;
        return catalogVolumeData;
    };

    Catalog::CatalogVolumeData* CatalogData::GetCatalogVolumeData( )
    {
        if ( m_catalogVolumeDataNdx >= 0 )
        {
        return m_catalogArray.at( m_catalogVolumeDataNdx );
        }
        return (Catalog::CatalogVolumeData*)0;
    };

int wayToSort(Catalog::CatalogVolumeData* vol1, Catalog::CatalogVolumeData* vol2) 
{ 
    wxString name1 = vol1->GetVolumeName();
    wxString name2 = vol2->GetVolumeName();
    return name1.compare(name2); 
}

    void CatalogData::LoadCatalogVolumes( )
    {
        for ( Catalog::CatalogVolumeDataArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolumeData* volume = ( Catalog::CatalogVolumeData* )( *it );
            volume->LoadXML( );
            wxString name = volume->GetVolumeName();
            if ( name.IsEmpty() )
            {
                name = volume->GetVolumeFilename();
                wxFileName fn(name);
                volume->SetVolumeName(fn.GetName());
            }
        }

        if (m_catalogArray.size() > 1 )
        {
            sort(m_catalogArray.begin(), m_catalogArray.end(), wayToSort);
        }
        m_volumeNameStrings.Clear();
        for ( Catalog::CatalogVolumeDataArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolumeData* volume = ( Catalog::CatalogVolumeData* )( *it );
            m_volumeNameStrings.Add( volume->GetVolumeName() );
        }
        CatalogPanel* catPanel = wxGetApp().GetFrame()->GetCatalogPanel();
        catPanel->SetVolumeListStrings( m_volumeNameStrings );
        m_catalogVolumeDataNdx = 0;
        catPanel->SetVolumeListSelection(m_catalogVolumeDataNdx);

    };

    void CatalogData::SaveCatalogVolumes( )
    {
        for ( Catalog::CatalogVolumeDataArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        {
            Catalog::CatalogVolumeData* volume = ( Catalog::CatalogVolumeData* )( *it );
            volume->Save( );
        }
    };

    void CatalogData::SetCatalogVolumeDataNdx( int i ) {
        m_catalogVolumeDataNdx = i;
        GetGeneratorData( )->LoadCatalogTree( );
    };
}