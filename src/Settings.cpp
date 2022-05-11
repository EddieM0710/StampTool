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

#include "Settings.h"

#include "AlbumGeneratorApp.h"

#include <iostream>
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/utils.h> 
#include "tinyxml2.h"

using namespace tinyxml2;

wxDECLARE_APP( AlbumGeneratorApp );

    Settings::Settings()
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
        fileName->AppendDir( "AlbumGenerator" );
        if ( !fileName->DirExists( ) )
        {
            fileName->Mkdir( );
        }
        wxString str = fileName->GetFullPath();
        SetConfigurationDirectory( fileName->GetFullPath( ) );
    }

    SetWorkingDirectory( wxGetCwd( ) );
    Load( );
    SetDirty(false);
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
    AlbumGeneratorFrame* frame = wxGetApp( ).GetFrame( );
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
        int cnt1 = m_recentFiles.Count();
        for ( int i = cnt1-1; i >= 0 ; i--)
        {
            wxString str = m_recentFiles.Item(i);
            if ( !m_recentFiles.Item(i).Cmp(filename))
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
            m_recentFiles.RemoveAt( m_nbrRecentPreference-1, cnt );
        }
    }
}

void Settings::Save( )
{
    wxFileName* filename
        = new wxFileName( GetConfigurationDirectory( ), "Persistent", "xml" );
    wxString fullPath = filename->GetFullPath( );
    XMLDocument doc;

    XMLElement* persistent = doc.NewElement( "Persistent" );
    doc.InsertEndChild( persistent );

    XMLElement* child = persistent->InsertNewChildElement( "ImageDirectory" );
    child->InsertNewText( GetImageDirectory( ).char_str( ) );

    child = persistent->InsertNewChildElement( "LastFile" );
    child->InsertNewText( GetLastFile( ).char_str( ) );

    child = persistent->InsertNewChildElement( "LoadLastFileAtStartUp" );
    child->InsertNewText( Bool2String( GetLoadLastFileAtStartUp( ) ) );

    XMLElement* sortOrder = persistent->InsertNewChildElement( "SortOrder" );
    wxArrayInt* sortOrderArray = GetSortOrder( );
    for ( int i = 0; i < sortOrderArray->Count( ); i++ )
    {
        if ( sortOrderArray->Item( i ) >= 0 )
        {
            child = sortOrder->InsertNewChildElement( "Classification" );
            child->InsertNewText( NodeNameStrings.Item( sortOrderArray->Item( i ) ) );
        }
    }
    XMLElement* division = persistent->InsertNewChildElement( "PeriodDivision" );
    XMLElement* lowerDivision = division->InsertNewChildElement( "LowerDivision" );
    lowerDivision->InsertNewText( GetLowerDivision( ).char_str( ) );
    XMLElement* upperDivision = division->InsertNewChildElement( "UpperDivision" );
    upperDivision->InsertNewText( GetUpperDivision( ).char_str( ) );

    XMLElement* periods = persistent->InsertNewChildElement( "Periods" );
    XMLElement* lowerPeriod = periods->InsertNewChildElement( "LowerPeriod" );
    lowerPeriod->InsertNewText( GetLowerPeriod( ).char_str( ) );
    XMLElement* middlePeriod = periods->InsertNewChildElement( "MiddlePeriod" );
    middlePeriod->InsertNewText( GetMiddlePeriod( ).char_str( ) );
    XMLElement* upperPeriod = periods->InsertNewChildElement( "UpperPeriod" );
    upperPeriod->InsertNewText( GetUpperPeriod( ).char_str( ) );

    wxArrayString* recentArray = GetRecentArray( );
    if ( !recentArray->IsEmpty( ) )
    {
        XMLElement* recent = persistent->InsertNewChildElement( "RecentFileList" );
        if ( recent )
        {
            for ( int i = 0; i < recentArray->Count( ); i++ )
            {
                XMLElement* recentFile = recent->InsertNewChildElement( "File" );
                recentFile->InsertNewText( recentArray->Item( i ) );
            }
        }
    }

    child = persistent->InsertNewChildElement( "NbrRecentPreference" );
    int nbr =  GetNbrRecentPreference( ) ;
    char str[20];
    sprintf( str, "%d", nbr);
    child->InsertNewText( str );
    const char* file = fullPath.c_str();
    doc.SaveFile( file );
}

void Settings::Load( )
{
    wxFileName* filename
        = new wxFileName( GetConfigurationDirectory( ), "Persistent", "xml" );
    wxString fullPath = filename->GetFullPath( );
    XMLDocument doc;
    int errCode = doc.LoadFile( fullPath.c_str( ) );

    if ( errCode != XML_SUCCESS )
    {
        wxString errorStr = doc.ErrorStr( );
        std::cout << errorStr << "\n";
        // Loading the Persistent.xml file failed
        // add defaults here and return
        SetLoadLastFileAtStartUp( true );
        SetImageDirectory( "" ) ;
        SetCatalogID( "" ) ;
        SetCountryID( "" ) ;

        wxArrayInt* sortOrderArray = GetSortOrder( );
        sortOrderArray->Add( NT_Period );
        sortOrderArray->Add( NT_Decade );
        sortOrderArray->Add( NT_Year );
        sortOrderArray->Add( NT_Emission );
        SetLowerDivision( "1950" );
        SetUpperDivision( "2000" );
        SetLowerPeriod( "Antique" );
        SetMiddlePeriod( "Classical" );
        SetUpperPeriod( "Modern" );
        //  SetImageDirectory( "" );
        SetLastFile( "" );
        SetNbrRecentPreference( 4 );

        return;

    }
    wxString name = doc.Value( );

    std::cout << name << "\n";
    XMLElement* root = doc.FirstChildElement( );
    // start processing the XML file
    name = root->Value( );

    std::cout << name << "\n";

    XMLElement* child;

    wxArrayInt* sortOrderArray = GetSortOrder( );

    XMLElement* sortOrder = root->FirstChildElement( "SortOrder" );
    if ( sortOrder )
    {
        child = sortOrder->FirstChildElement( "Classification" );
        while ( child )
        {
            wxString name = child->GetText( );
            NodeType type = FindNodeType( name );
            if ( type > -1 )
            {
                sortOrderArray->Add( type );
            }
            child = child->NextSiblingElement( "Classification" );
        }
    }
    for ( int i = sortOrderArray->Count( ); i < 5; i++ )
    {
        sortOrderArray->Add( -1 );
    }

    XMLElement* division = root->FirstChildElement( "PeriodDivision" );
    if ( division )
    {
        XMLElement* lowerDivision = division->FirstChildElement( "LowerDivision" );
        if ( lowerDivision )
        {
            SetLowerDivision( lowerDivision->GetText( ) );
        }
        else
        {
            SetLowerDivision( "1950" );
        }
        XMLElement* upperDivision = division->FirstChildElement( "UpperDivision" );
        if ( upperDivision )
        {
            SetUpperDivision( upperDivision->GetText( ) );
        }
        else
        {
            SetUpperDivision( "2000" );
        }
    }
    XMLElement* periods = root->FirstChildElement( "Periods" );
    if ( periods )
    {
        XMLElement* firstPeriod = periods->FirstChildElement( "LowerPeriod" );
        if ( firstPeriod )
        {
            SetLowerPeriod( firstPeriod->GetText( ) );
        }
        else
        {
            SetLowerPeriod( "Antique" );
        }
        XMLElement* middlePeriod = periods->FirstChildElement( "MiddlePeriod" );
        if ( middlePeriod )
        {
            SetMiddlePeriod( middlePeriod->GetText( ) );
        }
        else
        {
            SetMiddlePeriod( "Classical" );
        }
        XMLElement* upperPeriod = periods->FirstChildElement( "UpperPeriod" );
        if ( upperPeriod )
        {
            SetUpperPeriod( upperPeriod->GetText( ) );
        }
        else
        {
            SetUpperPeriod( "Modern" );
        }
    }
    XMLElement* lastFile = root->FirstChildElement( "LastFile" );
    if ( lastFile )
    {
        SetLastFile( lastFile->GetText( ) );
    }
    else
    {
        SetLastFile( "" );
    }
    XMLElement* loadLastFile = root->FirstChildElement( "LoadLastFileAtStartUp" );
    if ( loadLastFile )
    {
        bool isTrue = !strcmp(loadLastFile->GetText( ),"true"); 
        SetLoadLastFileAtStartUp( isTrue );
    }
    else
    {
        SetLoadLastFileAtStartUp( true );
    }
    std::cout << "LastFile: " << GetLastFile( ) << "\n";
    std::cout << "LoadLastFileAtStartUp: " << GetLoadLastFileAtStartUp( ) << "\n";

    XMLElement* imageDirectory = root->FirstChildElement( "ImageDirectory" );
    if ( imageDirectory )
    {
        SetImageDirectory( imageDirectory->GetText( ) );
    }
    else
    {
        SetImageDirectory( "" );
    }      

    XMLElement* catalogID = root->FirstChildElement( "CatalogID" );
    if ( catalogID )
    {

        SetCatalogID( catalogID->GetText( ) );
    }
    else
    {
        SetCatalogID( "SN" );
    }      

    XMLElement* countryID = root->FirstChildElement( "CountryID" );
    if ( countryID )
    {

        SetCountryID( countryID->GetText( ) );
    }
    else
    {
        SetCountryID( "US" );
    }      

    child = root->FirstChildElement( "NbrRecentPreference" );
    if ( child )
    {
        wxString str = child->GetText( );
        long nbr;
        str.ToLong(&nbr);
        SetNbrRecentPreference( nbr );
    }
 
    wxArrayString* recentArray = GetRecentArray( );
    XMLElement* recent = root->FirstChildElement( "RecentFileList" );
    if ( recent )
    {
        XMLElement* recentFile = recent->FirstChildElement( "File" );
        while ( recentFile )
        {
            recentArray->Add( recentFile->GetText( ) );
            recentFile = recent->NextSiblingElement( "File" );
        }
    }

   child = root->FirstChildElement( "LastFile" );
    if ( child )
    {
        SetLastFile( child->GetText( ) );
    }
    else
    {
        // it would be a strange case if there were no last 
        // file but were recent files. However the SetLastFile()
        // calls the frame to setup the recent menu so call it.
        SetLastFile( "" );
    }

    child = root->FirstChildElement( "LoadLastFileAtStartUp" );
    if ( child )
    {
        SetLoadLastFileAtStartUp( String2Bool( child->GetText( ) ) );
    }

}