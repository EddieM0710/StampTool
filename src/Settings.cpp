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
#include "XMLUtilities.h"

#include <iostream>
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/utils.h> 
#include "wx/xml/xml.h"

 

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
    wxXmlDocument doc;

    wxXmlNode* persistent = NewNode( &doc, "Persistent" );

    wxXmlNode* child = NewNode( persistent, "ImageDirectory" );
    child->SetContent( GetImageDirectory( )   );

    child = NewNode( persistent, "LastFile" );
    child->SetContent( GetLastFile( )   );

    child = NewNode( persistent, "LoadLastFileAtStartUp" );
    child->SetContent( Bool2String( GetLoadLastFileAtStartUp( ) ) );

    wxXmlNode* sortOrder = NewNode( persistent, "SortOrder" );
    wxArrayInt* sortOrderArray = GetSortOrder( );
    for ( int i = 0; i < sortOrderArray->Count( ); i++ )
    {
        if ( sortOrderArray->Item( i ) >= 0 )
        {
            child = NewNode( sortOrder, "Classification" );
            child->SetContent( NodeNameStrings.Item( sortOrderArray->Item( i ) ) );
        }
    }
    wxXmlNode* division = NewNode( persistent, "PeriodDivision" );
    wxXmlNode* lowerDivision = NewNode( division, "LowerDivision" );
    lowerDivision->SetContent( GetLowerDivision( )   );
    wxXmlNode* upperDivision = NewNode( division, "UpperDivision" );
    upperDivision->SetContent( GetUpperDivision( )   );

    wxXmlNode* periods = NewNode( persistent, "Periods" );
    wxXmlNode* lowerPeriod = NewNode( periods, "LowerPeriod" );
    lowerPeriod->SetContent( GetLowerPeriod( )   );
    wxXmlNode* middlePeriod = NewNode( periods, "MiddlePeriod" );
    middlePeriod->SetContent( GetMiddlePeriod( )   );
    wxXmlNode* upperPeriod = NewNode( periods, "UpperPeriod" );
    upperPeriod->SetContent( GetUpperPeriod( )   );

    wxArrayString* recentArray = GetRecentArray( );
    if ( !recentArray->IsEmpty( ) )
    {
        wxXmlNode* recent = NewNode( persistent, "RecentFileList" );
        if ( recent )
        {
            for ( int i = 0; i < recentArray->Count( ); i++ )
            {
                wxXmlNode* recentFile = NewNode( recent, "File" );
                recentFile->SetContent( recentArray->Item( i ) );
            }
        }
    }

    child = NewNode( persistent, "NbrRecentPreference" );
    int nbr =  GetNbrRecentPreference( ) ;
    char str[20];
    sprintf( str, "%d", nbr);
    child->SetContent( str );
    const char* file = fullPath.c_str();
    doc.Save( file );
}

void Settings::Load( )
{
    wxFileName* filename
        = new wxFileName( GetConfigurationDirectory( ), "Persistent", "xml" );
    wxString fullPath = filename->GetFullPath( );
    wxXmlDocument doc;
    bool errCode = doc.Load( fullPath  );

    if ( errCode )
    {
        std::cout << fullPath << "Load Failed.\n";
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
    wxString name = doc.GetRoot( )->GetName();

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
            wxString name = child->GetContent( );
            NodeType type = FindNodeType( name );
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
        wxXmlNode* lowerDivision = FirstChildElement( division, "LowerDivision" );
        if ( lowerDivision )
        {
            SetLowerDivision( lowerDivision->GetContent( ) );
        }
        else
        {
            SetLowerDivision( "1950" );
        }
        wxXmlNode* upperDivision = FirstChildElement( division, "UpperDivision" );
        if ( upperDivision )
        {
            SetUpperDivision( upperDivision->GetContent( ) );
        }
        else
        {
            SetUpperDivision( "2000" );
        }
    }
    wxXmlNode* periods = FirstChildElement( root, "Periods" );
    if ( periods )
    {
        wxXmlNode* firstPeriod = FirstChildElement( periods, "LowerPeriod" );
        if ( firstPeriod )
        {
            SetLowerPeriod( firstPeriod->GetContent( ) );
        }
        else
        {
            SetLowerPeriod( "Antique" );
        }
        wxXmlNode* middlePeriod = FirstChildElement( periods, "MiddlePeriod" );
        if ( middlePeriod )
        {
            SetMiddlePeriod( middlePeriod->GetContent( ) );
        }
        else
        {
            SetMiddlePeriod( "Classical" );
        }
        wxXmlNode* upperPeriod = FirstChildElement( periods, "UpperPeriod" );
        if ( upperPeriod )
        {
            SetUpperPeriod( upperPeriod->GetContent( ) );
        }
        else
        {
            SetUpperPeriod( "Modern" );
        }
    }
    wxXmlNode* lastFile = FirstChildElement( root, "LastFile" );
    if ( lastFile )
    {
        SetLastFile( lastFile->GetContent( ) );
    }
    else
    {
        SetLastFile( "" );
    }
    wxXmlNode* loadLastFile = FirstChildElement( root, "LoadLastFileAtStartUp" );
    if ( loadLastFile )
    {
        bool isTrue = !strcmp(loadLastFile->GetContent( ),"true"); 
        SetLoadLastFileAtStartUp( isTrue );
    }
    else
    {
        SetLoadLastFileAtStartUp( true );
    }
    std::cout << "LastFile: " << GetLastFile( ) << "\n";
    std::cout << "LoadLastFileAtStartUp: " << GetLoadLastFileAtStartUp( ) << "\n";

    wxXmlNode* imageDirectory = FirstChildElement( root, "ImageDirectory" );
    if ( imageDirectory )
    {
        SetImageDirectory( imageDirectory->GetContent( ) );
    }
    else
    {
        SetImageDirectory( "" );
    }      

    wxXmlNode* catalogID = FirstChildElement( root, "CatalogID" );
    if ( catalogID )
    {

        SetCatalogID( catalogID->GetContent( ) );
    }
    else
    {
        SetCatalogID( "SN" );
    }      

    wxXmlNode* countryID = FirstChildElement( root, "CountryID" );
    if ( countryID )
    {

        SetCountryID( countryID->GetContent( ) );
    }
    else
    {
        SetCountryID( "US" );
    }      

    child = FirstChildElement( root, "NbrRecentPreference" );
    if ( child )
    {
        wxString str = child->GetContent( );
        long nbr;
        str.ToLong(&nbr);
        SetNbrRecentPreference( nbr );
    }
 
    wxArrayString* recentArray = GetRecentArray( );
    wxXmlNode* recent = FirstChildElement( root, "RecentFileList" );
    if ( recent )
    {
        wxXmlNode* recentFile = FirstChildElement( recent, "File" );
        while ( recentFile )
        {
            recentArray->Add( recentFile->GetContent( ) );
            recentFile = GetNext( recent, "File" );
        }
    }

   child = FirstChildElement( root, "LastFile" );
    if ( child )
    {
        SetLastFile( child->GetContent( ) );
    }
    else
    {
        // it would be a strange case if there were no last 
        // file but were recent files. However the SetLastFile()
        // calls the frame to setup the recent menu so call it.
        SetLastFile( "" );
    }

    child = FirstChildElement( root, "LoadLastFileAtStartUp" );
    if ( child )
    {
        SetLoadLastFileAtStartUp( String2Bool( child->GetContent( ) ) );
    }

}