/**
 * @file CatalogData.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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

#include "catalog/Classification.h"
#include "utils/CSV.h"
#include "Defs.h"
#include "catalog/CatalogDefs.h"
#include "Settings.h"
#include "utils/Project.h"
#include "catalog/Stamp.h"
#include "catalog/CatalogData.h"
#include "AlbumGenApp.h"
#include "utils/XMLUtilities.h"

#include "wx/xml/xml.h"


namespace Catalog {


    CatalogData::CatalogData(/* args */ )
    {
        m_stampDoc = 0;
    }

    CatalogData::~CatalogData( )
    {
        delete m_stampDoc;
    }

    bool CatalogData::IsOK( )
    {
        if ( m_stampDoc )
        {
            return true;
        }
        return false;
    }
    wxXmlDocument* CatalogData::NewDocument( )
    {
        delete m_stampDoc;
        m_stampDoc = new wxXmlDocument( );
        return m_stampDoc;
    };
    wxXmlDocument* CatalogData::ReplaceDocument( wxXmlDocument* doc )
    {
        delete m_stampDoc;
        m_stampDoc = doc;
        return m_stampDoc;
    };

    void CatalogData::SaveXML( wxString filename )
    {
        GetProject( )->SetCatalogFilename( filename );
        if ( wxFileExists( filename ) )
        {
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak" );
            wxRenameFile( filename, bakFile.GetFullName( ) );
        }
        m_stampDoc->Save( filename );
    }
    void CatalogData::LoadXML( wxString filename )
    {
        GetProject( )->SetCatalogFilename( filename );
        if ( !m_stampDoc )
        {
            m_stampDoc = NewDocument( );
        }
        bool ok = m_stampDoc->Load( filename );

        if ( !ok )
        {
            std::cout << filename << " Load Failed.\n";
        }
        else
        {
            wxXmlNode* catalogData = m_stampDoc->GetRoot( );
            wxString name = catalogData->GetName( );

            if ( name.Length( ) == 0 )
            {
                catalogData->SetName( filename );
            }

        }

        GetSettings( )->SetLastFile( filename );
        //Get the file global Prefs
        wxXmlNode* root = m_stampDoc->GetRoot( );
        const char* name = root->GetName( );
        if ( !strcmp( name, CatalogNodeNames[ NT_Catalog ] ) )
        {
            Classification catalog( root );
            m_title = catalog.GetTitle( );
            //        m_imageDirectory = catalog.GetImageDirectory( );
            //        m_preferredCatalog = catalog.GetPreferredCatalog( );
        }
    }

    void CatalogData::LoadCSV( wxString filename )
    {
        if ( !m_stampDoc )
        {
            NewDocument( );
        }

        Utils::CSVData* csv = new Utils::CSVData( );
        wxXmlNode* docRoot = m_stampDoc->GetRoot( );
        if ( !docRoot )
        {
            docRoot = Utils::NewNode( m_stampDoc, CatalogNodeNames[ NT_Catalog ] );
        }

        Utils::SetAttrStr( docRoot, DT_DataNames[ DT_Name ], filename );

        csv->DoLoad( filename, m_stampDoc->GetRoot( ) );
        delete csv;
    }

    // wxXmlNode *CatalogData::Root()
    // {
    //     return m_stampDoc->GetRoot();
    // };

wxXmlNode* CatalogData::FindNodeWithPropertyAndValue( wxString property, wxString value )
    {
        return FindNodeWithPropertyAndValue( m_stampDoc->GetRoot(),  property,  value );
    }

  wxXmlNode* CatalogData::FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value )
    {
        wxString   	attr;
        wxXmlNode* child = element->GetChildren();
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