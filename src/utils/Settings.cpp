/**
 * @file Settings.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Defs.h"
#include "utils/Settings.h"

#include "AlbumGenApp.h"
#include "utils/XMLUtilities.h"

#include <iostream>
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/utils.h> 
#include "wx/xml/xml.h"



wxDECLARE_APP( AlbumGenApp );

namespace Utils {

    Settings::Settings( )
    {

        wxString homeDir = wxGetHomeDir( );
        wxFileName* fileName = new wxFileName( homeDir, "" );
        if ( fileName->DirExists( ) )
        {
            fileName->AppendDir( ".config" );
            if ( !fileName->DirExists( ) )
            {
                fileName->Mkdir( );
            }
            fileName->AppendDir( "AlbumGen" );
            if ( !fileName->DirExists( ) )
            {
                fileName->Mkdir( );
            }
            wxString str = fileName->GetFullPath( );
            SetConfigurationDirectory( fileName->GetFullPath( ) );
        }


        Load( );
        SetDirty( false );
    };

    int Settings::GetNextSortClassification( int current )
    {
        if ( current == 0 )
        {
            return m_sortOrder.Item( 0 );
        }
        // find where the current sort classification is
        for ( int i = 0; i < m_sortOrder.GetCount( ); i++ )
        {
            int item = m_sortOrder.Item( i );
            if ( item == current )
            {
                // and get the next one
                i++;
                if ( i < m_sortOrder.GetCount( ) )
                {
                    return m_sortOrder.Item( i );
                }
                else
                {
                    // oops, that was the last one
                    return -1;
                }
            }
        }
        // apparently no sorting is going on.
        return -1;
    }

    void Settings::SetLastFile( wxString file )
    {
        AddRecent( m_lastFile );
        AlbumGenFrame* frame = wxGetApp( ).GetFrame( );
        if ( frame )
        {
            frame->SetupRecentMenu( );
        }
        m_lastFile = file;
    };


    void Settings::AddRecent( wxString filename )
    {
        if ( !filename.IsEmpty( ) ) // add an empty file
        {
            // if this is already in the list somewhere then delete it
            int cnt1 = m_recentFiles.Count( );
            for ( int i = cnt1 - 1; i >= 0; i-- )
            {
                wxString str = m_recentFiles.Item( i );
                if ( !m_recentFiles.Item( i ).Cmp( filename ) )
                {
                    m_recentFiles.RemoveAt( i );
                }
            }

            int index = m_recentFiles.Index( filename );
            if ( index != wxNOT_FOUND )
            {
                m_recentFiles.RemoveAt( index );
            }
            else
            {
                int a = 1;
            }

            // and add this to te beginning
            m_recentFiles.Insert( filename, 0 );

            int cnt = m_recentFiles.Count( ) - m_nbrRecentPreference;
            if ( cnt > 0 )
            {
                m_recentFiles.RemoveAt( m_nbrRecentPreference - 1, cnt );
            }
        }
    }

    void Settings::Save( )
    {
        wxFileName* filename = new wxFileName( GetConfigurationDirectory( ), "Settings", "xml" );
        wxString fullPath = filename->GetFullPath( );
        wxXmlDocument doc;

        wxXmlNode* settings = NewNode( &doc, "Settings" );

        wxXmlNode* child = NewNode( settings, "ImageDirectory" );
        child->SetContent( GetImageDirectory( ) );

        child = NewNode( settings, "LastFile" );
        child->SetContent( GetLastFile( ) );

        child = NewNode( settings, "LoadLastFileAtStartUp" );
        child->SetContent( Bool2String( GetLoadLastFileAtStartUp( ) ) );

        wxXmlNode* sortOrder = NewNode( settings, "SortOrder" );
        wxArrayInt* sortOrderArray = GetSortOrder( );
        for ( int i = 0; i < sortOrderArray->Count( ); i++ )
        {
            if ( sortOrderArray->Item( i ) >= 0 )
            {
                child = NewNode( sortOrder, "Classification" );
                child->SetContent( Catalog::CatalogNodeNames[sortOrderArray->Item( i ) ] );
            }
        }
        wxXmlNode* division = NewNode( settings, "PeriodDivision" );
        wxXmlNode* lowerDivision = NewNode( division, "LowerDivision" );
        lowerDivision->SetContent( GetLowerDivision( ) );
        wxXmlNode* upperDivision = NewNode( division, "UpperDivision" );
        upperDivision->SetContent( GetUpperDivision( ) );

        wxXmlNode* periods = NewNode( settings, "Periods" );
        wxXmlNode* lowerPeriod = NewNode( periods, "LowerPeriod" );
        lowerPeriod->SetContent( GetLowerPeriod( ) );
        wxXmlNode* middlePeriod = NewNode( periods, "MiddlePeriod" );
        middlePeriod->SetContent( GetMiddlePeriod( ) );
        wxXmlNode* upperPeriod = NewNode( periods, "UpperPeriod" );
        upperPeriod->SetContent( GetUpperPeriod( ) );

        wxArrayString* recentArray = GetRecentArray( );
        if ( !recentArray->IsEmpty( ) )
        {
            wxXmlNode* recent = NewNode( settings, "RecentFileList" );
            if ( recent )
            {
                for ( int i = 0; i < recentArray->Count( ); i++ )
                {
                    wxXmlNode* recentFile = NewNode( recent, "File" );
                    recentFile->SetContent( recentArray->Item( i ) );
                }
            }
        }

        child = NewNode( settings, "NbrRecentPreference" );
        int nbr = GetNbrRecentPreference( );
        char str[ 20 ];
        sprintf( str, "%d", nbr );
        child->SetContent( str );
        const char* file = fullPath.c_str( );
        doc.Save( file );
    }

    void Settings::SetSettingValue( wxString& setting, wxXmlNode* parent, wxString childName, wxString defaultVal )
    {
        wxXmlNode* childNode = FirstChildElement( parent, childName );
        if ( childNode )
        {
            setting = childNode->GetNodeContent( );
        }
        else
        {
            setting = defaultVal;
        }
    }

    void Settings::SetDefaults()
    {

        if (m_sortOrder.Count() <= 0 )
        {
            m_sortOrder.Add( Catalog::NT_Period );
            m_sortOrder.Add( Catalog::NT_Decade );
            m_sortOrder.Add( Catalog::NT_Year );
            m_sortOrder.Add( Catalog::NT_Emission );
        }
        if ( m_lowerDivision.IsEmpty() ) m_lowerDivision = "1950";
        if ( m_upperDivision.IsEmpty() )m_upperDivision = "2000";
        if ( m_lowerPeriod.IsEmpty() ) m_lowerPeriod = "Antique";
        if ( m_middlePeriod.IsEmpty() ) m_middlePeriod = "Classical";
        if ( m_upperPeriod.IsEmpty() ) m_upperPeriod = "Modern";
        if ( m_countryID.IsEmpty() ) m_countryID = "US";
        if ( m_catalogID.IsEmpty() ) m_catalogID = "SN";

        if ( m_nbrRecentPreference <= 0 ) m_nbrRecentPreference = 0;;
    }
    void Settings::Load( )
    {
        wxFileName* filename
            = new wxFileName( GetConfigurationDirectory( ), "Settings", "xml" );
        wxString fullPath = filename->GetFullPath( );
        wxXmlDocument doc;
        bool ok = doc.Load( fullPath );

        if ( !ok )
        {
            std::cout << fullPath << " Load Failed.\n";
            // Loading the ettings.xml file failed
            // add defaults here and return
            SetLoadLastFileAtStartUp( true );
            SetImageDirectory( "" );
            SetCatalogID( "" );
            SetCountryID( "" );

            SetDefaults();

            SetLastFile( "" );
            SetNbrRecentPreference( 4 );

            return;

        }
        wxString name = doc.GetRoot( )->GetName( );

        std::cout << name << "\n";
        wxXmlNode* root = doc.GetRoot( );
        // start processing the XML file
        name = root->GetName( );

        std::cout << name << "\n";

        wxXmlNode* child;

        wxArrayInt* sortOrderArray = GetSortOrder( );

        wxXmlNode* sortOrder = FirstChildElement( root, "SortOrder" );
        if ( sortOrder )
        {
            child = FirstChildElement( sortOrder, "Classification" );
            while ( child )
            {
                wxString name = child->GetNodeContent( );
                Catalog::CatalogNodeType type = Catalog::FindCatalogNodeType( name );
                if ( type > -1 )
                {
                    sortOrderArray->Add( type );
                }
                child = GetNext( child, "Classification" );
            }
        }
        for ( int i = sortOrderArray->Count( ); i < 5; i++ )
        {
            sortOrderArray->Add( -1 );
        }

        wxXmlNode* division = FirstChildElement( root, "PeriodDivision" );
        if ( division )
        {
            SetSettingValue( m_lowerDivision, division, "LowerDivision", "1950" );
            SetSettingValue( m_upperDivision, division, "UpperDivision", "2000" );
        }
        wxXmlNode* periods = FirstChildElement( root, "Periods" );
        if ( periods )
        {
            SetSettingValue( m_lowerPeriod, periods, "LowerPeriod", "Antique" );
            SetSettingValue( m_middlePeriod, periods, "MiddlePeriod", "Classical" );
            SetSettingValue( m_upperPeriod, periods, "UpperPeriod", "Modern" );
        }
        SetSettingValue( m_lastFile, root, "LastFile", "" );

        wxXmlNode* loadLastFile = FirstChildElement( root, "LoadLastFileAtStartUp" );
        if ( loadLastFile )
        {
            bool isTrue = !strcmp( loadLastFile->GetNodeContent( ), "true" );
            SetLoadLastFileAtStartUp( isTrue );
        }
        else
        {
            SetLoadLastFileAtStartUp( true );
        }
        std::cout << "LastFile: " << GetLastFile( ) << "\n";
        std::cout << "LoadLastFileAtStartUp: " << GetLoadLastFileAtStartUp( ) << "\n";

        SetSettingValue( m_imageDirectory, root, "ImageDirectory", "" );

        SetSettingValue( m_catalogID, root, "CatalogID", "SN" );

        SetSettingValue( m_countryID, root, "CountryID", "US" );

        wxString str;
        SetSettingValue( str, root, "NbrRecentPreference", "4" );
        long nbr;
        str.ToLong( &nbr );
        m_nbrRecentPreference = nbr;

        wxArrayString* recentArray = GetRecentArray( );
        wxXmlNode* recent = FirstChildElement( root, "RecentFileList" );
        if ( recent )
        {
            wxXmlNode* recentFile = FirstChildElement( recent, "File" );
            while ( recentFile )
            {
                recentArray->Add( recentFile->GetNodeContent( ) );
                recentFile = GetNext( recent, "File" );
            }
        }
        SetSettingValue( m_lastFile, root, "LastFile", "" );

        SetSettingValue( str, root, "LoadLastFileAtStartUp", "true" );
        m_loadLastFileAtStartUp = String2Bool( str );
        SetDefaults();  
    }
}