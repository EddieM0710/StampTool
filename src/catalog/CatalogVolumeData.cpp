/**
 * @file CatalogVolumeData.cpp
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

#include <iostream>
#include <wx/filename.h>
#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/msgdlg.h>

#include "catalog/CatalogVolumeData.h"

#include "Defs.h"

#include "catalog/CatalogDefs.h"
#include "catalog/Classification.h"
#include "catalog/Entry.h"

#include "utils/CSV.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "utils/XMLUtilities.h"
#include "AlbumGenApp.h"

wxDECLARE_APP( AlbumGenApp );

namespace Catalog {

    CatalogVolumeData* NewCatalogVolumeDataInstance()
    {
        return new CatalogVolumeData();
    }

    CatalogVolumeData::CatalogVolumeData(/* args */ )
    {
        m_stampDoc = 0;
    }

    //*****

    CatalogVolumeData::~CatalogVolumeData( )
    {
        delete m_stampDoc;
    }

    //*****

    bool CatalogVolumeData::IsOK( )
    {
        if ( m_stampDoc )
        {
            return true;
        }
        return false;
    }

    //*****   

    void CatalogVolumeData::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetGeneratorData( )->SetDirty( true );
        }
    }
     //*****

    wxXmlDocument* CatalogVolumeData::NewDocument( )
    {
        delete m_stampDoc;
        m_stampDoc = new wxXmlDocument( );
        return m_stampDoc;
    };

    //*****

    wxXmlDocument* CatalogVolumeData::ReplaceDocument( wxXmlDocument* doc )
    {
        delete m_stampDoc;
        m_stampDoc = doc;
        return m_stampDoc;
    };

    //*****

    void CatalogVolumeData::Save( )
    {
        wxString filename = GetProject( )->GetCatalogFilename( );
        if ( wxFileExists( filename ) )
        {
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak" );
            wxRenameFile( filename, bakFile.GetFullName( ), true );
        }
        m_stampDoc->Save( filename );
        SetDirty( false );
    }
    
    //*****

    void CatalogVolumeData::NewCatalog()
    {     
        m_stampDoc = NewDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Catalog" );
        m_stampDoc->SetRoot( root );
    }
    
    //*****

    void CatalogVolumeData::LoadXML(  )
    {

        bool ok = false;
        if ( m_volumeFilename.length( ) > 0 )
        {
            if ( !m_stampDoc )
            {
                m_stampDoc = NewDocument( );
            }

            wxString cwd = wxGetCwd( );
            //ok = m_stampDoc->Load( filename );
            wxFileInputStream stream( m_volumeFilename );
            if ( !stream.IsOk( ) )
            {
            wxString txt = wxString::Format( "%s Stream Create Failed. Error: %s.\n\n", m_volumeFilename, stream.GetLastError( ) );
                wxMessageDialog* dlg = new wxMessageDialog(
                    wxGetApp( ).GetFrame( ), txt,
                    wxT( "Warning! Stream Create Failed.\n" ),
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }
            if ( !m_stampDoc->Load( stream ) )
            {
            wxString txt = wxString::Format( "\n%s Stream  Failed. Error: %s.\n\n", m_volumeFilename, stream.GetLastError( ) );
                wxMessageDialog* dlg = new wxMessageDialog(
                    wxGetApp( ).GetFrame( ), txt,
                    wxT( "Warning! Stream Load Failed.\n" ),
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }
        }
        else
        {
            // this creates an empty document
            wxXmlNode* catalogVolumeData = m_stampDoc->GetRoot( );
            wxString name = catalogVolumeData->GetName( );

            if ( name.Length( ) == 0 )
            {
                catalogVolumeData->SetName( m_volumeFilename );
            }
        }


//         //Get the file global Prefs
//         wxXmlNode* root = m_stampDoc->GetRoot( );
//         const char* name = root->GetName( );
//         if ( !strcmp( name, CatalogBaseNames[ NT_Catalog ] ) )
//         {
//             Classification catalog( root );
//   //          m_title = catalog.GetTitle( );
//         }

        SetDirty( false );
    }

    //*****

    void CatalogVolumeData::LoadCSV( wxString filename )
    {
        if ( !m_stampDoc )
        {
            NewDocument( );
        }

        Utils::CSVData* csv = new Utils::CSVData( );
        wxXmlNode* docRoot = m_stampDoc->GetRoot( );
        if ( !docRoot )
        {
            docRoot = Utils::NewNode( m_stampDoc, CatalogBaseNames[ NT_Catalog ] );
        }

        Utils::SetAttrStr( docRoot, DT_DataNames[ DT_Name ], filename );

        csv->DoLoad( filename, m_stampDoc->GetRoot( ) );
        SetDirty( );
        delete csv;
    }


    //*****

    wxXmlNode* CatalogVolumeData::FindNodeWithPropertyAndValue( wxString property, wxString value )
    {
        return FindNodeWithPropertyAndValue( m_stampDoc->GetRoot( ), property, value );
    }

    //*****

    wxXmlNode* CatalogVolumeData::FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value )
    {
        wxString   	attr;
        wxXmlNode* child = element->GetChildren( );
        while ( child )
        {
            if ( child->GetAttribute( property, &attr ) )
            {
                if ( !value.Cmp( attr ) )
                {
                    return child;
                }
            }
            wxXmlNode* foundChild = FindNodeWithPropertyAndValue( child, property, value );
            if ( foundChild )
            {
                return foundChild;
            }
            child = ( wxXmlNode* )child->GetNext( );
        }
        return ( wxXmlNode* )0;
    }

}