/**
 * @file AECmdData.cpp
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
#include "AECmdData.h"
#include "AlbumGeneratorApp.h"
#include "XMLUtilities.h"

#include "tinyxml2.h"

using namespace tinyxml2;

AECmdData::AECmdData(/* args */ )
{
    m_AECmdDoc = 0;
}

AECmdData::~AECmdData( )
{
    delete m_AECmdDoc;
}

bool AECmdData::IsOK( )
{
    if ( m_AECmdDoc )
    {
        return true;
    }
    return false;
}
XMLDocument* AECmdData::NewDocument( )
{
    delete m_AECmdDoc;
    m_AECmdDoc = new XMLDocument( );
    return m_AECmdDoc;
};
XMLDocument* AECmdData::ReplaceDocument( XMLDocument* doc )
{
    delete m_AECmdDoc;
    m_AECmdDoc = doc;
    return m_AECmdDoc;
};

void AECmdData::SaveXML( wxString filename )
{
    if ( wxFileExists( filename ) )
    {
        wxFileName bakFile( filename );
        bakFile.SetExt( "bak" );
        wxRenameFile( filename, bakFile.GetFullName( ) );
    }

    m_AECmdDoc->SaveFile( filename );
}
void AECmdData::LoadXML( wxString filename )
{
    if ( !m_AECmdDoc )
    {
         m_AECmdDoc = NewDocument( );
    }
    int errCode = m_AECmdDoc->LoadFile( filename );

    if ( errCode != XML_SUCCESS )
    {
        wxString errorStr = m_AECmdDoc->ErrorStr( );
        std::cout << errorStr << "\n";
    }
    else
    {
        m_AECmdDoc->RootElement( );
        XMLElement* aeCommandData = m_AECmdDoc->RootElement( );
        wxString name = aeCommandData->Name( );
        
        if ( name.Length() == 0 )
        {
            aeCommandData->SetName( filename.c_str());
        }
        /**
         * @todo Remove this block
         * This code is to process aeCommand codes to the new way i'm handling it.
         * It will be unnecessary once all the XMLs i've generated get updated.
         *
         **************************************************/
        XMLElement* root = m_AECmdDoc->RootElement( );
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
    XMLElement* root = m_AECmdDoc->RootElement( );
    const char* name = root->Name( );
    if ( !strcmp( name, NodeNameStrings[ NT_Catalog ] ) )
    {
        Classification aeCommand( root );
        m_title = aeCommand.GetTitle( );
    }
}

void AECmdData::LoadAEFile( wxString filename )
{
    if ( !m_AECmdDoc )
    {
        NewDocument( );
    }

    CSVData* csv = new CSVData( );
    XMLElement* docRoot = m_AECmdDoc->RootElement( );
    if ( !docRoot )
    {
        docRoot = m_AECmdDoc->NewElement( NodeNameStrings[ NT_Catalog ] );
        m_AECmdDoc->InsertFirstChild( docRoot );
    }

    docRoot->SetAttribute( DT_DataNames[DT_Name], filename.char_str( ) );
  
    csv->DoLoad( filename, m_AECmdDoc->RootElement( ) );
    delete csv;
}


