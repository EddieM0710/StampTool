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

#include "Classification.h"
#include "CSV.h"
#include "Defs.h"
#include "Settings.h"
#include "Stamp.h"
#include "CatalogData.h"
#include "AlbumGeneratorApp.h"
#include "XMLUtilities.h"

#include "tinyxml2.h"

using namespace tinyxml2;

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
XMLDocument* CatalogData::NewDocument( )
{
    delete m_stampDoc;
    m_stampDoc = new XMLDocument( );
    return m_stampDoc;
};
XMLDocument* CatalogData::ReplaceDocument( XMLDocument* doc )
{
    delete m_stampDoc;
    m_stampDoc = doc;
    return m_stampDoc;
};

void CatalogData::SaveXML( wxString filename )
{
    if ( wxFileExists( filename ) )
    {
        wxFileName bakFile( filename );
        bakFile.SetExt( "bak" );
        wxRenameFile( filename, bakFile.GetFullName( ) );
    }

    m_stampDoc->SaveFile( filename );
}
void CatalogData::LoadXML( wxString filename )
{
    if ( !m_stampDoc )
    {
         m_stampDoc = NewDocument( );
    }
    int errCode = m_stampDoc->LoadFile( filename );

    if ( errCode != XML_SUCCESS )
    {
        wxString errorStr = m_stampDoc->ErrorStr( );
        std::cout << errorStr << "\n";
    }
    else
    {
        m_stampDoc->RootElement( );
        XMLElement* catalogData = m_stampDoc->RootElement( );
        wxString name = catalogData->Name( );
        
        if ( name.Length() == 0 )
        {
            catalogData->SetName( filename.c_str());
        }
        /**
         * @todo Remove this block
         * This code is to process catalog codes to the new way i'm handling it.
         * It will be unnecessary once all the XMLs i've generated get updated.
         *
         **************************************************/
        XMLElement* root = m_stampDoc->RootElement( );
        XMLIterator* iterator = new XMLIterator( root );
        XMLElement* item = iterator->First( );
        Stamp stamp;

        while ( item )
        {
            if ( IsNodeType( item, NT_Stamp ) )
            {
                stamp.SetElement( item );
                stamp.ProcessCatalogCodes( );
            }
            wxString name = item->Name( );

            item = iterator->Next( );
        }
    }

    GetSettings()->SetLastFile( filename );
    //Get the file global Prefs
    XMLElement* root = m_stampDoc->RootElement( );
    const char* name = root->Name( );
    if ( !strcmp( name, NodeNameStrings[ NT_Catalog ] ) )
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

    CSVData* csv = new CSVData( );
    XMLElement* docRoot = m_stampDoc->RootElement( );
    if ( !docRoot )
    {
        docRoot = m_stampDoc->NewElement( NodeNameStrings[ NT_Catalog ] );
        m_stampDoc->InsertFirstChild( docRoot );
    }

    docRoot->SetAttribute( DT_DataNames[DT_Name], filename.char_str( ) );
  
    csv->DoLoad( filename, m_stampDoc->RootElement( ) );
    delete csv;
}

// XMLElement *CatalogData::Root()
// {
//     return m_stampDoc->RootElement();
// };
