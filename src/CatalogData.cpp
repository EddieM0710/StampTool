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

#include "wx/xml/xml.h"

 

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
    if ( !m_stampDoc )
    {
         m_stampDoc = NewDocument( );
    }
    bool ok = m_stampDoc->Load( filename );

    if ( !ok  )
    {
        std::cout << filename << " Load Failed.\n";
    }
    else
    {
        wxXmlNode* catalogData = m_stampDoc->GetRoot( );
        wxString name = catalogData->GetName( );
        
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
        wxXmlNode* root = m_stampDoc->GetRoot( );
        XMLIterator* iterator = new XMLIterator( root );
        wxXmlNode* item = iterator->First( );
        Stamp stamp;

        while ( item )
        {
            if ( IsCatalogNodeType( item, NT_Stamp ) )
            {
                stamp.SetElement( item );
                stamp.ProcessCatalogCodes( );
            }
            wxString name = item->GetName( );

            item = iterator->Next( );
        }
    }

    GetSettings()->SetLastFile( filename );
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

    CSVData* csv = new CSVData( );
    wxXmlNode* docRoot = m_stampDoc->GetRoot( );
    if ( !docRoot )
    {
        docRoot = NewNode( m_stampDoc, CatalogNodeNames[ NT_Catalog ] );
    }

    SetAttribute( docRoot, DT_DataNames[DT_Name], filename   );
  
    csv->DoLoad( filename, m_stampDoc->GetRoot( ) );
    delete csv;
}

// wxXmlNode *CatalogData::Root()
// {
//     return m_stampDoc->GetRoot();
// };
