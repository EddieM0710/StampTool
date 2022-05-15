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

#include "utils/Project.h"

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
            m_defaultSortOrder.Add( Catalog::NT_Period );
            m_defaultSortOrder.Add( Catalog::NT_Decade );
            m_defaultSortOrder.Add( Catalog::NT_Year );
            m_defaultSortOrder.Add( Catalog::NT_Emission );

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

    };

    //(((((((((((((((((((((((-)))))))))))))))))))))))    
    void Settings::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetProject( )->SetDirty( true );
        }
    }

    //(((((((((((((((((((((((-)))))))))))))))))))))))    
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

    //(((((((((((((((((((((((-)))))))))))))))))))))))    
    void Settings::SetLastFile( wxString file )
    {
        AddRecent( m_lastFile );
        AlbumGenFrame* frame = wxGetApp( ).GetFrame( );
        if ( frame )
        {
            frame->SetupRecentMenu( );
        }
        m_lastFile = file;
        SetDirty();
    };


    //(((((((((((((((((((((((-))))))))))))))))))))))) 
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

    //(((((((((((((((((((((((-))))))))))))))))))))))) 
    void Settings::Save( )
    {
        wxFileName* filename = new wxFileName( GetConfigurationDirectory( ), "Settings", "xml" );
        wxString fullPath = filename->GetFullPath( );
        wxXmlDocument doc;

        wxXmlNode* settings = NewNode( &doc, "Settings" );

        wxXmlNode* child = NewNode( settings, "ImageDirectory" );
        if ( child )
        {
            child = NewNode( child, "File" );
            child->AddAttribute("Name", GetImageDirectory());
        }

        child = NewNode( settings, "LastFile" );
        if ( child )
        {
            child->AddAttribute( "LoadLastFileAtStartUp", Bool2String( GetLoadLastFileAtStartUp( )));
            child = NewNode( child, "File" );
            child->AddAttribute("Name", GetLastFile());
        }

        wxXmlNode* sortOrder = NewNode( settings, "SortOrder" );
        wxArrayInt* sortOrderArray = GetSortOrder( );
        for ( int i = 0; i < sortOrderArray->Count( ); i++ )
        {
            if ( sortOrderArray->Item( i ) >= 0 )
            {
                child = NewNode( sortOrder, "Classification" );
                child->AddAttribute( "Name", Catalog::CatalogBaseNames[sortOrderArray->Item( i ) ] );
            }
        }

        wxXmlNode* division = NewNode( settings, "PeriodDivision" );
        if(division)
        {
            division->AddAttribute("LowerDivision", GetLowerDivision( ) );
            division->AddAttribute("UpperDivision", GetUpperDivision( ) );
        }

        wxXmlNode* periods = NewNode( settings, "Periods" );
        if ( periods )
        {
            periods->AddAttribute("LowerPeriod", GetLowerPeriod( ) );
            periods->AddAttribute("MiddlePeriod", GetMiddlePeriod( ) );
            periods->AddAttribute("UpperPeriod", GetUpperPeriod( ) );
        }

        wxArrayString* recentArray = GetRecentArray( );
        wxXmlNode* recent = NewNode( settings, "RecentFileList" );
        if ( recent )
        {
            int nbr = GetNbrRecentPreference( );
            char str[ 20 ];
            sprintf( str, "%d", nbr );
            recent->AddAttribute("NbrRecentPreference", str);

            for ( int i = 0; i < recentArray->Count( ); i++ )
            {
                wxXmlNode* recentFile = NewNode( recent, "File" );
                recentFile->AddAttribute("Name",  recentArray->Item( i ));
            }
        }

        wxXmlNode* idPref = NewNode( settings, "IDPreference" );
        if ( recent )
        {
            idPref->AddAttribute("CatalogID", m_catalogID);      
            idPref->AddAttribute("CountryID", m_countryID);
        }
        const char* file = fullPath.c_str( );
        doc.Save( file );
        SetDirty(false);
    }

    //(((((((((((((((((((((((-))))))))))))))))))))))) 
    void Settings::SetSettingValue( wxString& setting, wxXmlNode* parent, wxString childName, wxString defaultVal )
    {
        wxXmlNode* childNode = FirstChildElement( parent, childName );
        if ( childNode )
        {
            setting = childNode->GetNodeContent( );
            if ( setting.IsEmpty() ) 
            {
                SetDirty();
                setting = defaultVal;                
            }
        }
        else
        {
            SetDirty();
            setting = defaultVal;
        }
    }

    //(((((((((((((((((((((((-))))))))))))))))))))))) 
    void Settings::SetDefaults()
    {

        if (m_sortOrder.Count() <= 0 )
        {
            SetDirty();
            m_sortOrder.Add( Catalog::NT_Period );
            m_sortOrder.Add( Catalog::NT_Decade );
            m_sortOrder.Add( Catalog::NT_Year );
            m_sortOrder.Add( Catalog::NT_Emission );
        }
        if ( m_lowerDivision.IsEmpty() ) 
        {
            SetDirty();
            m_lowerDivision = m_defaultLowerDivision;
        }
        if ( m_upperDivision.IsEmpty() ) 
        {
            SetDirty();
            m_upperDivision = m_defaultUpperDivision;
        }
        if ( m_lowerPeriod.IsEmpty() )  
        {
            SetDirty();
            m_lowerPeriod = m_defaultLowerPeriod;
        }
        if ( m_middlePeriod.IsEmpty() )  
        {
            SetDirty();
            m_middlePeriod = m_defaultMiddlePeriod;
        }
        if ( m_upperPeriod.IsEmpty() )  
        {
            SetDirty();
            m_upperPeriod = m_defaultUpperPeriod;
        }
        if ( m_countryID.IsEmpty() )  
        {
            SetDirty();
            m_countryID = m_defaultCountryID;
        }
        if ( m_catalogID.IsEmpty() )  
        {
            SetDirty();
            m_catalogID = m_defaultCatalogID;
        }

        if ( m_nbrRecentPreference <= 0 )  
        {
            SetDirty();
            m_nbrRecentPreference = m_defaultNbrRecentPreference;
        }
    }

    //(((((((((((((((((((((((-))))))))))))))))))))))) 
    void Settings::Load( )
    {
        wxFileName* filename
            = new wxFileName( GetConfigurationDirectory( ), "Settings", "xml" );
        wxString fullPath = filename->GetFullPath( );
        wxXmlDocument doc;
        bool ok = doc.Load( fullPath );

        if ( !ok )
        {
            SetDirty();
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
            Save();
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
                wxString name = child->GetAttribute( "Name");
                Catalog::CatalogBaseType type = Catalog::FindCatalogBaseType( name );
                if ( type > -1 )
                {
                    sortOrderArray->Add( type );
                }
                child = GetNext( child, "Classification" );
            }
        }

        wxXmlNode* division = FirstChildElement( root, "PeriodDivision" );
        if ( division )
        {
            m_lowerDivision = division->GetAttribute( "LowerDivision");
            if( m_lowerDivision.IsEmpty() )
            {
               m_lowerDivision = m_defaultLowerDivision; 
            }
            m_upperDivision = division->GetAttribute( "UpperDivision");
            if( m_upperDivision.IsEmpty() )
            {
               m_upperDivision = m_defaultUpperDivision; 
            }
        }
        wxXmlNode* periods = FirstChildElement( root, "Periods" );
        if ( periods )
        {
            m_lowerPeriod = periods->GetAttribute( "LowerPeriod");
            if( m_lowerPeriod.IsEmpty() )
            {
               m_lowerPeriod = m_defaultLowerPeriod; 
            }
            m_middlePeriod = periods->GetAttribute( "MiddlePeriod");
            if( m_middlePeriod.IsEmpty() )
            {
               m_middlePeriod = m_defaultMiddlePeriod; 
            }
            m_upperPeriod = periods->GetAttribute( "UpperPeriod");
            if( m_upperPeriod.IsEmpty() )
            {
               m_upperPeriod = m_defaultUpperPeriod; 
            }
        }

        wxXmlNode* lastFile = FirstChildElement( root, "LastFile" );
        if ( lastFile )
        {
            wxString loadLastFile = lastFile->GetAttribute( "LoadLastFileAtStartUp");
            bool isTrue = !loadLastFile.Cmp("true" );
            SetLoadLastFileAtStartUp( isTrue );

            wxXmlNode* child = FirstChildElement( lastFile, "File" );
            if ( child )
            {
                m_lastFile = child->GetAttribute("Name");
            }
        }

        SetSettingValue( m_imageDirectory, root, "ImageDirectory", "" );

        wxXmlNode* imageDirectory = FirstChildElement( root, "ImageDirectory" );
        if ( imageDirectory )
        {

            wxXmlNode* child = FirstChildElement( imageDirectory, "File" );
            if ( child )
            {
                m_imageDirectory = child->GetAttribute("Name");
            }
        }

        wxXmlNode* idPref = FirstChildElement( root, "IDPreference" );
        if ( idPref )
        {
            m_catalogID = idPref->GetAttribute( "CatalogID");
            if( m_catalogID.IsEmpty() )
            {
               m_catalogID = m_defaultCatalogID; 
            }
            m_countryID = idPref->GetAttribute( "CountryID");
            if( m_countryID.IsEmpty() )
            {
               m_countryID = m_defaultCountryID; 
            }
        }
        wxArrayString* recentArray = GetRecentArray( );

        wxXmlNode* recentList = FirstChildElement( root, "RecentFileList" );
        if ( recentList )
        {
            wxString nbeRecentPref = recentList->GetAttribute( "NbrRecentPreference");
            long nbr;
            nbeRecentPref.ToLong( &nbr );
            m_nbrRecentPreference = nbr;

            child = FirstChildElement( recentList, "File" );
            while ( child )
            {
                wxString name = child->GetAttribute( "Name");
                recentArray->Add( name );
                child = GetNext( child, "File" );
            }
        }

        SetDefaults();  
        Save();
    }
}