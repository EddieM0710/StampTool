/**
 * @file AlbumData.cpp
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
#include "Settings.h"
#include "catalog/Stamp.h"
#include "AlbumData.h"
#include "AlbumGenApp.h"
#include "utils/XMLUtilities.h"

#include "wx/xml/xml.h"


namespace Layout {

    AlbumData::AlbumData(/* args */ )
    {
        m_albumDoc = 0;
    }

    AlbumData::~AlbumData( )
    {
        delete m_albumDoc;
    }

    bool AlbumData::IsOK( )
    {
        if ( m_albumDoc )
        {
            return true;
        }
        return false;
    }
    wxXmlDocument* AlbumData::NewDocument( )
    {
        delete m_albumDoc;
        m_albumDoc = new wxXmlDocument( );
        return m_albumDoc;
    };
    wxXmlDocument* AlbumData::ReplaceDocument( wxXmlDocument* doc )
    {
        delete m_albumDoc;
        m_albumDoc = doc;
        return m_albumDoc;
    };

    void AlbumData::SaveXML( wxString filename )
    {
        if ( wxFileExists( filename ) )
        {
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak" );
            wxRenameFile( filename, bakFile.GetFullName( ) );
        }

        m_albumDoc->Save( filename );
    }
    void AlbumData::LoadXML( wxString filename )
    {
        if ( !m_albumDoc )
        {
            m_albumDoc = NewDocument( );
        }
        bool ok = m_albumDoc->Load( filename );

        if ( !ok )
        {
            std::cout << filename << " Load Failed.\n";
        }
        else
        {
            wxXmlNode* albumData = m_albumDoc->GetRoot( );
            wxString name = albumData->GetName( );

            if ( name.Length( ) == 0 )
            {
                albumData->SetName( filename );
            }


            GetSettings( )->SetLastFile( filename );
            //Get the file global Prefs
            wxXmlNode* root = m_albumDoc->GetRoot( );
            m_title = Utils::GetAttrStr( root, "Name" );
        }
    }


}