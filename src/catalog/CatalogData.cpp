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
#include "wx/xml/xml.h"
#include <wx/msgdlg.h>

#include "catalog/CatalogData.h"

#include "Defs.h"

#include "catalog/CatalogDefs.h"
#include "catalog/Classification.h"
#include "catalog/Stamp.h"

#include "utils/CSV.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "utils/XMLUtilities.h"
#include "AlbumGenApp.h"

wxDECLARE_APP( AlbumGenApp );

namespace Catalog {

    //(((((((((((((((((((((((-)))))))))))))))))))))))

    CatalogData::CatalogData(/* args */ )
    {
        m_stampDoc = 0;
    }

    //(((((((((((((((((((((((-)))))))))))))))))))))))

    CatalogData::~CatalogData( )
    {
        delete m_stampDoc;
    }

    //(((((((((((((((((((((((-)))))))))))))))))))))))

    bool CatalogData::IsOK( )
    {
        if ( m_stampDoc )
        {
            return true;
        }
        return false;
    }

    //(((((((((((((((((((((((-)))))))))))))))))))))))   

    void CatalogData::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetProject( )->SetDirty( true );
        }
    }
     //(((((((((((((((((((((((-)))))))))))))))))))))))

    wxXmlDocument* CatalogData::NewDocument( )
    {
        delete m_stampDoc;
        m_stampDoc = new wxXmlDocument( );
        return m_stampDoc;
    };

    //(((((((((((((((((((((((-)))))))))))))))))))))))

    wxXmlDocument* CatalogData::ReplaceDocument( wxXmlDocument* doc )
    {
        delete m_stampDoc;
        m_stampDoc = doc;
        return m_stampDoc;
    };

    //(((((((((((((((((((((((-)))))))))))))))))))))))

    void CatalogData::Save( )
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
    
    //(((((((((((((((((((((((-)))))))))))))))))))))))

    void CatalogData::NewCatalog()
    {     
        m_stampDoc = NewDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Catalog" );
        m_stampDoc->SetRoot( root );
    }
    
    //(((((((((((((((((((((((-)))))))))))))))))))))))

    void CatalogData::LoadXML( wxString filename )
    {

        bool ok = false;
        if ( filename.length( ) > 0 )
        {
            if ( !m_stampDoc )
            {
                m_stampDoc = NewDocument( );
            }

            wxString cwd = wxGetCwd( );
            //ok = m_stampDoc->Load( filename );
            wxFileInputStream stream( filename );
            if ( !stream.IsOk( ) )
            {
            wxString txt = wxString::Format( "%s Stream Create Failed. Error: %s.\n\n", filename, stream.GetLastError( ) );
                wxMessageDialog* dlg = new wxMessageDialog(
                    wxGetApp( ).GetFrame( ), txt,
                    wxT( "Warning! Stream Create Failed.\n" ),
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }
            if ( !m_stampDoc->Load( stream ) )
            {
            wxString txt = wxString::Format( "\n%s Stream  Failed. Error: %s.\n\n", filename, stream.GetLastError( ) );
                wxMessageDialog* dlg = new wxMessageDialog(
                    wxGetApp( ).GetFrame( ), txt,
                    wxT( "Warning! Stream Create Failed.\n" ),
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }
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


        //Get the file global Prefs
        wxXmlNode* root = m_stampDoc->GetRoot( );
        const char* name = root->GetName( );
        if ( !strcmp( name, CatalogBaseNames[ NT_Catalog ] ) )
        {
            Classification catalog( root );
            m_title = catalog.GetTitle( );
        }

        SetDirty( false );
    }

    //(((((((((((((((((((((((-)))))))))))))))))))))))

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
            docRoot = Utils::NewNode( m_stampDoc, CatalogBaseNames[ NT_Catalog ] );
        }

        Utils::SetAttrStr( docRoot, DT_DataNames[ DT_Name ], filename );

        csv->DoLoad( filename, m_stampDoc->GetRoot( ) );
        SetDirty( );
        delete csv;
    }


    //(((((((((((((((((((((((-)))))))))))))))))))))))

    wxXmlNode* CatalogData::FindNodeWithPropertyAndValue( wxString property, wxString value )
    {
        return FindNodeWithPropertyAndValue( m_stampDoc->GetRoot( ), property, value );
    }

    //(((((((((((((((((((((((-)))))))))))))))))))))))

    wxXmlNode* CatalogData::FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value )
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