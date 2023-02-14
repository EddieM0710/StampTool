/**
 * @file CatalogData.cpp
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
#include "StampToolApp.h"
#include "gui/ToolData.h"

wxDECLARE_APP( StampToolApp );

namespace Catalog { 

    Catalog::CatalogSectionData* CatalogData::NewCatalogSectionData( )
    { 
        Catalog::CatalogSectionData* catalogSectionData = Catalog::NewCatalogSectionDataInstance( );
        m_catalogArray.push_back( catalogSectionData );
        m_catalogSectionDataNdx = m_catalogArray.size( ) - 1;
        return catalogSectionData;
    };

    bool CatalogData::ClearCatalogArray( )
    { 
        while( !m_catalogArray.empty( ) )
        { 
            CatalogSectionData* data = m_catalogArray.back( );
            delete data;
            m_catalogArray.pop_back( );
        }
        return true;
    } 
    Catalog::CatalogSectionData* CatalogData::GetCatalogSectionData( )
    { 
        if ( m_catalogSectionDataNdx >= 0 )
        { 
            if ( !m_catalogArray.empty( ) ) 
            { 
                return m_catalogArray.at( m_catalogSectionDataNdx );
            }
        }
        return ( Catalog::CatalogSectionData* )0;
    };

int wayToSort( Catalog::CatalogSectionData* sect1, Catalog::CatalogSectionData* sect2 ) 
{ 
    wxString name1 = sect1->GetSectionName( );
    wxString name2 = sect2->GetSectionName( );
    return name1.compare( name2 ); 
}

    void CatalogData::LoadCatalogSections( )
    { 

        for ( Catalog::CatalogSectionDataArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        { 
            Catalog::CatalogSectionData* section = ( Catalog::CatalogSectionData* )( *it );
            section->LoadXML( );
            wxString name = section->GetSectionName( );
            if ( !name.IsEmpty( ) )
            { 
                name = section->GetSectionFilename( );
                wxFileName fn( name );
                section->SetSectionName( fn.GetName( ) );
            }
        }

        if ( m_catalogArray.size( ) > 1 )
        { 
            sort( m_catalogArray.begin( ), m_catalogArray.end( ), wayToSort );
        }
        m_sectionNameStrings.Clear( );
        for ( Catalog::CatalogSectionDataArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        { 
            Catalog::CatalogSectionData* section = ( Catalog::CatalogSectionData* )( *it );
            m_sectionNameStrings.Add( section->GetSectionName( ) );
        }
        CatalogPanel* catPanel = wxGetApp( ).GetFrame( )->GetCatalogPagePanel( );
        CatalogPanel* albPanel = wxGetApp( ).GetFrame( )->GetAlbumPagePanel( );
        catPanel->SetSectionListStrings( m_sectionNameStrings );
        albPanel->SetSectionListStrings( m_sectionNameStrings );
        m_catalogSectionDataNdx = 0;
        catPanel->SetSectionListSelection( m_catalogSectionDataNdx );
        albPanel->SetSectionListSelection( m_catalogSectionDataNdx );

    };

    void CatalogData::SaveCatalogSections( )
    { 
        for ( Catalog::CatalogSectionDataArray::iterator it = std::begin( m_catalogArray );
            it != std::end( m_catalogArray );
            ++it )
        { 
            Catalog::CatalogSectionData* section = ( Catalog::CatalogSectionData* )( *it );
            section->Save( );
        }
    };

    void CatalogData::SetCatalogSectionDataNdx( int i ) { 
        m_catalogSectionDataNdx = i;
        GetToolData( )->LoadCatalogTree( );
    };
}