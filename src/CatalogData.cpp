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

//

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
    bool errCode = m_stampDoc->Load( filename );

    if ( !errCode  )
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
 
    }

    GetSettings()->SetLastFile( filename );
    //Get the file global Prefs
    wxXmlNode* root = m_stampDoc->GetRoot( );
    wxString name = root->GetName( );
    if ( ! name.Cmp( NodeNameStrings[ NT_Catalog ] ) )
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
        docRoot = new wxXmlNode( wxXML_ELEMENT_NODE , NodeNameStrings[ NT_Catalog ] );
        m_stampDoc->SetRoot(docRoot);
    }

    docRoot->AddAttribute( DT_DataNames[DT_Name], filename.char_str( ) );
  
    csv->DoLoad( filename, docRoot );
    delete csv;
}

// wxXmlNode *CatalogData::Root()
// {
//     return m_stampDoc->RootElement();
// };
