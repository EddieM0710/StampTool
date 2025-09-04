/**
 * @file Settings.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright ( c ) 2021
 *
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <iostream>
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/utils.h> 
#include "wx/xml/xml.h"
#include <wx/utils.h>
#include <wx/stdpaths.h>

#include "Defs.h"
#include "utils/Settings.h"

#include "utils/Project.h"

 //#include "StampToolApp.h"
#include "gui/StampToolFrame.h"
#include "gui/AppData.h"
#include "utils/XMLUtilities.h"
#include "collection/CollectionList.h"
#include "utils/FontList.h"




//wxDECLARE_APP( StampToolApp );


namespace Utils {

    Settings* NewSettingsInstance( )
    {
        Settings* settings = new Settings( );
        settings->InitSettings( );
        return settings;
    }

    Settings::Settings( )
    { };

    void Settings::InitSettings( )
    {
        m_defaultSortOrder.Add( Catalog::NT_Year );
        m_defaultSortOrder.Add( Catalog::NT_Emission );

        SetConfigurationDirectory( );

        Load( );

    };
    void Settings::SetConfigurationDirectory( )
    {
        wxStandardPaths& stdPaths = wxStandardPaths::Get( );
        stdPaths.SetFileLayout( wxStandardPaths::FileLayout_XDG );
        stdPaths.UseAppInfo( wxStandardPaths::AppInfo_AppName );
        wxString settingsDir = stdPaths.GetUserLocalDataDir( );
        wxFileName* fileName = new wxFileName( settingsDir, "" );
        if ( !fileName->DirExists( ) )
        {
            fileName->Mkdir( );
        }
        wxString str = fileName->GetFullPath( );
        m_configurationDirectory = str.Trim( ); m_dirty = true;
    };

    void Settings::SetAppDataDirectory( )
    {

        wxStandardPaths& stdPaths = wxStandardPaths::Get( );

        stdPaths.SetFileLayout( wxStandardPaths::FileLayout_XDG );
        stdPaths.UseAppInfo( wxStandardPaths::AppInfo_AppName );


        // wxString appDataDir = stdPaths.GetAppDocumentsDir( );
        const wxString docsDir = stdPaths.GetDocumentsDir( );
        wxString subdir( docsDir );

        if ( stdPaths.UsesAppInfo( wxStandardPaths::AppInfo_VendorName ) )
        {
            subdir = AppendPathComponent( subdir, wxTheApp->GetVendorName( ) );
        }

        if ( stdPaths.UsesAppInfo( wxStandardPaths::AppInfo_AppName ) )
        {
            subdir = AppendPathComponent( subdir, wxTheApp->GetAppName( ) );
        }


        wxString appDocsDir = subdir;


        wxFileName* fileName = new wxFileName( appDocsDir, "" );
        if ( !fileName->DirExists( ) )
        {
            fileName->Mkdir( );
        }
        wxString str = fileName->GetFullPath( );
        m_appDataDirectory = str.Trim( ); m_dirty = true;
    };

    wxString Settings::AppendPathComponent( const wxString& dir, const wxString& component )
    {
        wxString subdir( dir );

        // empty string indicates that an error has occurred, don't touch it then
        if ( !subdir.empty( ) )
        {
            if ( !component.empty( ) )
            {
                const wxChar ch = *( subdir.end( ) - 1 );
                if ( !wxFileName::IsPathSeparator( ch ) && ch != wxT( '.' ) )
                    subdir += wxFileName::GetPathSeparator( );

                subdir += component;
            }
        }

        return subdir;
    }

    // wxString Settings::AppendAppInfo(const wxString& dir) const
    // {
    //     wxString subdir(dir);

    //     if ( UsesAppInfo(AppInfo_VendorName) )
    //     {
    //         subdir = AppendPathComponent(subdir, wxTheApp->GetVendorName());
    //     }

    //     if ( UsesAppInfo(AppInfo_AppName) )
    //     {
    //         subdir = AppendPathComponent(subdir, wxTheApp->GetAppName());
    //     }

    //     return subdir;
    // }



        // void Settings::NewAppData( )
        // {

        //     wxDirDialog  dirDialog( this, 12355, _( "Select the Filename and Directory for the Application Data" ) );
        //     wxGetCwd( );
        //     fileDialog.SetDefaultDirectory( wxGetCwd( ) );
        //     fileDialog.SetDefaultFilename( _( "unnamed.spt" ) );
        //     fileDialog.SetWildCard( _( "Stamp Tools Project files(*.spt)|*.spt" ) );

        //     if ( fileDialog.ShowModal( ) == wxID_CANCEL )
        //     {
        //         return;
        //     }
        //     wxString dir = fileDialog.GetDir( );
        //     wxSetWorkingDirectory( dir );

        //     GetProject( )->FileNewProject( fileDialog.GetFile( ) );
        // }



            //    
    void Settings::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetAppData( )->SetDirty( true );
        }
    }

    //    
    int Settings::GetNextSortClassification( int current )
    {
        for ( int i = 0; i < m_sortOrder.GetCount( ); i++ )
        {
            int j = m_sortOrder.Item( i );
            //            std::cout << "   " << j << " " << Catalog::CatalogBaseNames[ j ];
        }
        //        std::cout << "\n";
        //        std::cout << "Looking for" << current + 1 << " " << Catalog::CatalogBaseNames[ current + 1 ];

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
                    return Catalog::NT_None;
                }
            }
        }
        // apparently no sorting is going on.
        return Catalog::NT_None;
    }

    wxFont Settings::GetNbrFont( ) {
        return GetFontList( )->GetFont( FontPreference[ Design::AT_NbrFontType ] );
    };
    wxColour Settings::GetNbrColor( ) {
        return GetFontList( )->GetColor( FontPreference[ Design::AT_NbrFontType ] );;
    };

    wxFont Settings::GetNameFont( ) {
        return GetFontList( )->GetFont( FontPreference[ Design::AT_NameFontType ] );
    };
    wxColour Settings::GetNameColor( ) {
        return GetFontList( )->GetColor( FontPreference[ Design::AT_NameFontType ] );;
    };

    wxFont Settings::GetTitleFont( ) {
        return GetFontList( )->GetFont( FontPreference[ Design::AT_TitleFontType ] );
    };
    wxColour Settings::GetTitleColor( ) {
        return GetFontList( )->GetColor( FontPreference[ Design::AT_TitleFontType ] );
    };

    wxFont Settings::GetSubTitleFont( ) {
        return GetFontList( )->GetFont( FontPreference[ Design::AT_SubTitleFontType ] );
    };
    wxColour Settings::GetSubTitleColor( ) {
        return GetFontList( )->GetColor( FontPreference[ Design::AT_TitleFontType ] );
    };

    wxFont Settings::GetTextFont( ) {
        return GetFontList( )->GetFont( FontPreference[ Design::AT_TextFontType ] );
    };
    wxColour Settings::GetTextColor( ) {
        return GetFontList( )->GetColor( FontPreference[ Design::AT_TextFontType ] );
    };


    //    
    void Settings::SetLastFile( wxString file )
    {
        AddRecent( m_lastFile );
        StampToolFrame* frame = GetFrame( );
        if ( frame )
        {
            frame->SetupRecentMenu( );
        }
        m_lastFile = file;
        SetDirty( );
    };

    void Settings::SetLastListFile( wxString file )
    {
        m_lastListFile = file;
        SetDirty( );
    };

    // 
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
        wxBusyCursor wait( wxHOURGLASS_CURSOR );

        wxFileName* filename = new wxFileName( GetConfigurationDirectory( ), "Settings", "xml" );
        wxString fullPath = filename->GetFullPath( );
        wxXmlDocument doc;

        wxXmlNode* settings = NewNode( &doc, "Settings" );

        wxXmlNode* child = NewNode( settings, "AppDataDirectory" );
        if ( child )
        {
            wxString appDataDir = child->GetAttribute( "Name" );
            child->AddAttribute( "Name", m_appDataDirectory );
        }

        child = NewNode( settings, "LastFile" );
        if ( child )
        {
            child->AddAttribute( "LoadLastFileAtStartUp", Bool2String( GetLoadLastFileAtStartUp( ) ) );
            child = NewNode( child, "File" );
            child->AddAttribute( "Name", GetLastFile( ) );
        }

        child = NewNode( settings, "LastCollection" );
        if ( child )
        {
            child->AddAttribute( "Name", m_lastCollection );
        }

        child = NewNode( settings, "CollectionList" );
        if ( child )
        {
            GetCollectionList( )->Save( child );
        }

        wxXmlNode* fonts = NewNode( settings, "Fonts" );
        if ( fonts )
        {
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_NbrFontType ], Design::AT_NbrFontType );
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_NameFontType ], Design::AT_NameFontType );
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_TextFontType ], Design::AT_TextFontType );
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_TitleFontType ], Design::AT_TitleFontType );
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_SubTitleFontType ], Design::AT_SubTitleFontType );
        }

        wxXmlNode* sortOrder = NewNode( settings, "SortOrder" );
        wxArrayInt* sortOrderArray = GetSortOrder( );
        for ( int i = 0; i < sortOrderArray->Count( ); i++ )
        {
            if ( sortOrderArray->Item( i ) >= 0 )
            {
                child = NewNode( sortOrder, "Classification" );
                child->AddAttribute( "Name", Catalog::CatalogBaseNames[ sortOrderArray->Item( i ) ] );
            }
        }

        wxXmlNode* division = NewNode( settings, "PeriodDivision" );
        if ( division )
        {
            division->AddAttribute( "LowerDivision", GetLowerDivision( ) );
            division->AddAttribute( "UpperDivision", GetUpperDivision( ) );
        }

        wxXmlNode* periods = NewNode( settings, "Periods" );
        if ( periods )
        {
            periods->AddAttribute( "LowerPeriod", GetLowerPeriod( ) );
            periods->AddAttribute( "MiddlePeriod", GetMiddlePeriod( ) );
            periods->AddAttribute( "UpperPeriod", GetUpperPeriod( ) );
        }

        wxArrayString* recentArray = GetRecentArray( );
        wxXmlNode* recent = NewNode( settings, "RecentFileList" );
        if ( recent )
        {
            int nbr = GetNbrRecentPreference( );
            char str[ 20 ];
            sprintf( str, "%d", nbr );
            recent->AddAttribute( "NbrRecentPreference", str );

            for ( int i = 0; i < recentArray->Count( ); i++ )
            {
                wxXmlNode* recentFile = NewNode( recent, "File" );
                recentFile->AddAttribute( "Name", recentArray->Item( i ) );
            }
        }

        wxXmlNode* idPref = NewNode( settings, "IDPreference" );
        if ( recent )
        {
            idPref->AddAttribute( "CatalogID", m_catalogID );
            idPref->AddAttribute( "CountryID", m_countryID );
        }
        const char* file = fullPath.c_str( );
        doc.Save( file );
        // Utils::Save(  &doc, file );
        SetDirty( false );
    }

    // 
    void Settings::SetSettingValue( wxString& setting, wxXmlNode* parent, wxString childName, wxString defaultVal )
    {
        wxXmlNode* childNode = FirstChildElement( parent, childName );
        if ( childNode )
        {
            setting = childNode->GetNodeContent( );
            if ( setting.IsEmpty( ) )
            {
                SetDirty( );
                setting = defaultVal;
            }
        }
        else
        {
            SetDirty( );
            setting = defaultVal;
        }
    }

    // 
    void Settings::SetDefaults( )
    {

        if ( m_sortOrder.Count( ) <= 0 )
        {
            SetDirty( );
            m_sortOrder.Add( Catalog::NT_Year );
            m_sortOrder.Add( Catalog::NT_Emission );
        }
        if ( m_lowerDivision.IsEmpty( ) )
        {
            SetDirty( );
            m_lowerDivision = m_defaultLowerDivision;
        }
        if ( m_upperDivision.IsEmpty( ) )
        {
            SetDirty( );
            m_upperDivision = m_defaultUpperDivision;
        }
        if ( m_lowerPeriod.IsEmpty( ) )
        {
            SetDirty( );
            m_lowerPeriod = m_defaultLowerPeriod;
        }
        if ( m_middlePeriod.IsEmpty( ) )
        {
            SetDirty( );
            m_middlePeriod = m_defaultMiddlePeriod;
        }
        if ( m_upperPeriod.IsEmpty( ) )
        {
            SetDirty( );
            m_upperPeriod = m_defaultUpperPeriod;
        }
        if ( m_countryID.IsEmpty( ) )
        {
            SetDirty( );
            m_countryID = m_defaultCountryID;
        }
        if ( m_catalogID.IsEmpty( ) )
        {
            SetDirty( );
            m_catalogID = m_defaultCatalogID;
        }

        if ( m_nbrRecentPreference <= 0 )
        {
            SetDirty( );
            m_nbrRecentPreference = m_defaultNbrRecentPreference;
        }

        wxFont font( *wxNORMAL_FONT );

        SetAppDataDirectory( );
        wxFileName lf( m_appDataDirectory );
        wxSetWorkingDirectory( lf.GetPath( ) );

    }

    void Settings::Load( )
    {
        //Set Defaults
        SetLoadLastFileAtStartUp( true );
        //SetImageDirectory( "" );
        SetCatalogID( "" );
        SetCountryID( "" );

        SetDefaults( );

        SetLastFile( "" );
        SetNbrRecentPreference( 4 );
        SetCatalogVolumeEditable( );
        SetCatalogVolumeEditableDefault( );

        //Now get the Settings
        wxFileName* filename
            = new wxFileName( GetConfigurationDirectory( ), "Settings", "xml" );
        wxString fullPath = filename->GetFullPath( );
        wxXmlDocument doc;
        bool ok = doc.Load( fullPath );

        if ( !ok )
        {
            SetAppDataDirectory( );

            wxString appDir = GetAppDataDirectory( );

            SetDirty( );
            // Loading the settings.xml file failed
            // Save defaults here and return

            Save( );
            return;

        }
        wxString name = doc.GetRoot( )->GetName( );
        wxXmlNode* root = doc.GetRoot( );

        // start processing the XML file
        name = root->GetName( );
        //wxXmlNode* child = root->GetChildren( );;

        //while ( child )
        //{
            //wxString name = child->GetName( );

        wxXmlNode* child = FirstChildElement( root, "SortOrder" );
        if ( child )
        {
            wxArrayInt* sortOrderArray = GetSortOrder( );
            wxXmlNode* sortOrderChild = child->GetChildren( );
            while ( sortOrderChild )
            {
                wxString childName = sortOrderChild->GetName( );
                if ( !childName.Cmp( "Classification" ) )
                {
                    wxString sortOrderChild = child->GetAttribute( "Name" );
                    Catalog::CatalogBaseType type = Catalog::FindCatalogBaseType( name );
                    if ( type > -1 )
                    {
                        sortOrderArray->Add( type );
                    }
                }
                sortOrderChild = sortOrderChild->GetNext( );
            }
        }

        child = FirstChildElement( root, "PeriodDivision" );
        if ( child )
            //else if ( !name.Cmp( "PeriodDivision" ) )
        {
            m_lowerDivision = child->GetAttribute( "LowerDivision" );
            if ( m_lowerDivision.IsEmpty( ) )
            {
                m_lowerDivision = m_defaultLowerDivision;
                SetDirty( );

            }

            m_upperDivision = child->GetAttribute( "UpperDivision" );
            if ( m_upperDivision.IsEmpty( ) )
            {
                m_upperDivision = m_defaultUpperDivision;
                SetDirty( );
            }
        }

        child = FirstChildElement( root, "Periods" );
        if ( child )
            //else if ( !name.Cmp( "Periods" ) )
        {
            m_lowerPeriod = child->GetAttribute( "LowerPeriod" );
            if ( m_lowerPeriod.IsEmpty( ) )
            {
                m_lowerPeriod = m_defaultLowerPeriod;
                SetDirty( );
            }
            m_middlePeriod = child->GetAttribute( "MiddlePeriod" );
            if ( m_middlePeriod.IsEmpty( ) )
            {
                m_middlePeriod = m_defaultMiddlePeriod;
                SetDirty( );
            }
            m_upperPeriod = child->GetAttribute( "UpperPeriod" );
            if ( m_upperPeriod.IsEmpty( ) )
            {
                m_upperPeriod = m_defaultUpperPeriod;
                SetDirty( );
            }
        }

        child = FirstChildElement( root, "AppDataDirectory" );
        if ( child )
        {
            wxString appDataDir = child->GetAttribute( "Name" );
            if ( appDataDir.IsEmpty( ) )
            {
                SetAppDataDirectory( );
                wxFileName lf( m_appDataDirectory, "" );
                wxSetWorkingDirectory( lf.GetPath( ) );
                SetDirty( );
            }
            else
            {
                wxFileName lf( appDataDir );
                if ( lf.DirExists( ) )
                {
                    m_appDataDirectory = appDataDir;
                    wxSetWorkingDirectory( lf.GetPath( ) );
                }
                else
                {
                    SetAppDataDirectory( );
                    wxFileName lf( m_appDataDirectory );
                    wxSetWorkingDirectory( lf.GetPath( ) );
                }
            }
        }


        child = FirstChildElement( root, "LastFile" );
        if ( child )
            //else if ( !name.Cmp( "LastFile" ) )
        {
            wxString loadLastFile = child->GetAttribute( "LoadLastFileAtStartUp" );
            bool isTrue = !loadLastFile.Cmp( "true" );
            SetLoadLastFileAtStartUp( isTrue );

            wxXmlNode* file = child->GetChildren( );
            if ( file )
            {
                wxString childName = file->GetName( );
                if ( !childName.Cmp( "File" ) )
                {
                    m_lastFile = file->GetAttribute( "Name" );
                    if ( m_lastFile.IsEmpty( ) )
                    {
                        wxString dir = GetAppDataDirectory( );
                        wxFileName lf( dir, "" );
                        wxSetWorkingDirectory( lf.GetPath( ) );
                    }
                    else
                    {
                        wxFileName lf( m_lastFile );
                        wxSetWorkingDirectory( lf.GetPath( ) );
                    }
                }
            }
        }

        child = FirstChildElement( root, "StampDataEdit" );
        if ( child )
            //else if ( !name.Cmp( "StampDataEdit" ) )
        {
            wxString defaultVal = child->GetAttribute( "Default" );
            bool isTrue = !defaultVal.Cmp( "true" );
            SetCatalogVolumeEditable( isTrue );
            SetCatalogVolumeEditableDefault( isTrue );
        }

        child = FirstChildElement( root, "IDPreference" );
        if ( child )
            //else if ( !name.Cmp( "IDPreference" ) )
        {
            m_catalogID = child->GetAttribute( "CatalogID" );
            if ( m_catalogID.IsEmpty( ) )
            {
                m_catalogID = m_defaultCatalogID;
            }
            m_countryID = child->GetAttribute( "CountryID" );
            if ( m_countryID.IsEmpty( ) )
            {
                m_countryID = m_defaultCountryID;
            }
        }

        child = FirstChildElement( root, "RecentFileList" );
        if ( child )
            //else if ( !name.Cmp( "RecentFileList" ) )
        {
            wxArrayString* recentArray = GetRecentArray( );
            recentArray->Clear( );
            wxString nbeRecentPref = child->GetAttribute( "NbrRecentPreference" );
            long nbr;
            nbeRecentPref.ToLong( &nbr );
            m_nbrRecentPreference = nbr;

            wxXmlNode* file = child->GetChildren( );
            while ( file )
            {
                wxString childName = file->GetName( );
                if ( !childName.Cmp( "File" ) )
                {
                    name = file->GetAttribute( "Name" );

                    recentArray->Add( name );
                }
                file = file->GetNext( );
            }
        }

        child = FirstChildElement( root, "LastCollection" );
        if ( child )
            //else if ( !name.Cmp( "LastCollection" ) )
        {
            m_lastCollection = child->GetAttribute( "Name" );
        }

        child = FirstChildElement( root, "CollectionList" );
        if ( child )
            //else if ( !name.Cmp( "CollectionList" ) )
        {
            GetCollectionList( )->Load( child );
        }
        else
        {
            GetCollectionList( )->SetDefaultCollection( );
        }

        SetApplicationDefaults( );
        child = FirstChildElement( root, "Defaults" );
        if ( child )
        {
            LoadLayoutPreference( child );
        }

        child = FirstChildElement( root, "Fonts" );
        if ( child )
            //else if ( !name.Cmp( "Fonts" ) )
        {

            FontPreference[ Design::AT_NbrFontType ] = GetFontList( )->LoadFont( child, Design::AT_NbrFontType );
            if ( FontPreference[ Design::AT_NbrFontType ] < 0 )
            {
                FontPreference[ Design::AT_NbrFontType ] = GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_NbrFontType ] );
            }

            FontPreference[ Design::AT_NameFontType ] = GetFontList( )->LoadFont( child, Design::AT_NameFontType );
            if ( FontPreference[ Design::AT_NameFontType ] < 0 )
            {
                FontPreference[ Design::AT_NameFontType ] = GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_NameFontType ] );
            }

            FontPreference[ Design::AT_TextFontType ] = GetFontList( )->LoadFont( child, Design::AT_TextFontType );
            if ( FontPreference[ Design::AT_TextFontType ] < 0 )
            {
                FontPreference[ Design::AT_TextFontType ] = GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_TextFontType ] );
            }

            FontPreference[ Design::AT_TitleFontType ] = GetFontList( )->LoadFont( child, Design::AT_TitleFontType );
            if ( FontPreference[ Design::AT_TitleFontType ] < 0 )
            {
                FontPreference[ Design::AT_TitleFontType ] = GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_TitleFontType ] );
            }

            FontPreference[ Design::AT_SubTitleFontType ] = GetFontList( )->LoadFont( child, Design::AT_SubTitleFontType );
            if ( FontPreference[ Design::AT_SubTitleFontType ] < 0 )
            {
                FontPreference[ Design::AT_SubTitleFontType ] = GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_SubTitleFontType ] );
            }

        }

        for ( int i = 0; i < Design::AT_NbrFontUsageTypes; i++ )
        {
            Utils::Font* font = GetFontList( )->GetMyFont( FontPreference[ i ] );
            wxString fontStr = "";
            if ( font )
            {
                fontStr = font->GetNativeInfoStr( );
            }

        }
    }

    void Settings::SetApplicationDefaults( )
    {

        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_PageWidth ] = Dbl2String( 208.25 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_PageHeight ] = Dbl2String( 269.5 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_TopPageMargin ] = Dbl2String( 12.0 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_BottomPageMargin ] = Dbl2String( 12 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_RightPageMargin ] = Dbl2String( 12 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_LeftPageMargin ] = Dbl2String( 18 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_BorderFileName ] = "big_and_little_line.jpg";
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_BorderSize ] = Dbl2String( 4 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_ShowBorder ] = "true";
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_ShowTitle ] = "true";
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_ShowSubTitle ] = "true";
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_Orientation ] = Design::OrientationStrings[ Design::AT_Portrait ];
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_TopContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_BottomContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_LeftContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_RightContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_OverSizePaper ] = "false";
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_PaperHeight ] = Dbl2String( 269.5 );
        ApplicationLayoutDefault[ Design::LT_Page ][ Design::AT_PaperWidth ] = Dbl2String( 208.25 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_ShowTitle ] = "true";
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_ShowCatNbr ] = "true";
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_ShowImage ] = "true";
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_GrayScaleImages ] = "false";
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_TopContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_BottomContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_LeftContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_RightContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_SelvageHeight ] = Dbl2String( 0 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_SelvageWidth ] = Dbl2String( 0 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_MountAllowanceHeight ] = Dbl2String( 6 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_MountAllowanceWidth ] = Dbl2String( 6 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_StampNamePosition ] = Design::StampNamePositionStrings[ Design::AT_StampNamePositionTop ];
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_StampMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Stamp ][ Design::AT_Catalog ] = "Mi";
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_ShowTitle ] = "false";
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_ShowSubTitle ] = "false";
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_ShowFrame ] = "false";
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_TopContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_BottomContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_LeftContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_RightContentMargin ] = Dbl2String( 2 );
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_CalculateSpacing ] = "true";
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_FixedSpacingSize ] = Dbl2String( 5 );
        ApplicationLayoutDefault[ Design::LT_Frame ][ Design::AT_StampAlignmentMode ] = Design::StampAlignmentModeStrings[ Design::AlignTop ];
        for ( int layout = Design::LT_Page; layout < Design::NbrLayoutTypes; layout++ )
        {
            for ( int attrType = Design::AT_Name; attrType < Design::AT_NbrAttrTypes; attrType++ )
            {
                ApplicationLayoutPreference[ layout ][ attrType ] = ApplicationLayoutDefault[ layout ][ attrType ];
                std::cout << Design::LayoutTypeStrings[ layout ] << " "
                    << Design::AttrNameStrings[ attrType ] << " "
                    << ApplicationLayoutPreference[ layout ][ attrType ] << "\n";
            }
        }

    }

    void Settings::LoadLayoutPreference( wxXmlNode* node )
    {

        wxXmlNode* defaults = Utils::FirstChildElement( node, "Defaults" );
        if ( defaults )
        {
            wxXmlNode* child = defaults->GetChildren( );
            while ( child )
            {
                wxString name = child->GetName( );
                if ( !name.Cmp( "Default" ) )
                {
                    wxString layoutType = child->GetAttribute( "LayoutType" );
                    if ( !layoutType.Cmp( Design::LayoutTypeStrings[ Design::LT_Page ] ) )
                    {
                        wxXmlAttribute* attr = child->GetAttributes( );
                        while ( attr )
                        {
                            wxString attrName = attr->GetName( );
                            wxString attrVal = attr->GetValue( );
                            Design::AlbumAttrType attrType = Design::FindAlbumAttrType( attrName );
                            if ( attrType >= 0 )
                            {
                                ApplicationLayoutPreference[ Design::LT_Page ][ attrType ] = attrVal;
                            }

                            attr = attr->GetNext( );
                        }
                    }
                    else  if ( !layoutType.Cmp( Design::LayoutTypeStrings[ Design::LT_Stamp ] ) )
                    {
                        wxXmlAttribute* attr = child->GetAttributes( );
                        while ( attr )
                        {
                            wxString attrName = attr->GetName( );
                            wxString attrVal = attr->GetValue( );
                            Design::AlbumAttrType attrType = Design::FindAlbumAttrType( attrName );
                            if ( attrType >= 0 )
                            {
                                ApplicationLayoutPreference[ Design::LT_Stamp ][ attrType ] = attrVal;
                            }
                            attr = attr->GetNext( );
                        }
                    }
                    else  if ( !layoutType.Cmp( Design::LayoutTypeStrings[ Design::LT_Frame ] ) )
                    {
                        wxXmlAttribute* attr = child->GetAttributes( );
                        while ( attr )
                        {
                            wxString attrName = attr->GetName( );

                            wxString attrVal = attr->GetValue( );
                            Design::AlbumAttrType attrType = Design::FindAlbumAttrType( attrName );
                            if ( attrType >= 0 )
                            {
                                ApplicationLayoutPreference[ Design::LT_Frame ][ attrType ] = attrVal;
                            }
                            attr = attr->GetNext( );
                        }
                    }
                }
                child = child->GetNext( );
            }
        }
    }

}