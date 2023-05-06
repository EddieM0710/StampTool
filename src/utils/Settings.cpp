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

#include "Defs.h"
#include "utils/Settings.h"

#include "utils/Project.h"

 //#include "StampToolApp.h"
#include "gui/StampToolFrame.h"
#include "gui/AppData.h"
#include "utils/XMLUtilities.h"
#include "utils/FontList.h"
#include <iostream>
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/utils.h> 
#include "wx/xml/xml.h"



//wxDECLARE_APP( StampToolApp );


namespace Utils {

    Settings* NewSettingsInstance( )
    {
        Settings* settings = new Settings( );
        settings->InitSettings( );
        return settings;
    }

    Settings::Settings( )
    {
    };

    void Settings::InitSettings( )
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
            fileName->AppendDir( "StampTool" );
            if ( !fileName->DirExists( ) )
            {
                fileName->Mkdir( );
            }
            wxString str = fileName->GetFullPath( );
            SetConfigurationDirectory( fileName->GetFullPath( ) );
        }

        Load( );

    };
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

    wxFont Settings::GetNbrFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_NbrFontType ].Get( ) ); };
    wxColour Settings::GetNbrColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_NbrFontType ].Get( ) );; };

    wxFont Settings::GetNameFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_NameFontType ].Get( ) ); };
    wxColour Settings::GetNameColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_NameFontType ].Get( ) );; };

    wxFont Settings::GetTitleFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_TitleFontType ].Get( ) ); };
    wxColour Settings::GetTitleColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_TitleFontType ].Get( ) ); };

    wxFont Settings::GetTextFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_TextFontType ].Get( ) ); };
    wxColour Settings::GetTextColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_TextFontType ].Get( ) ); };


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

    // void SaveFont( wxXmlNode* parent, Design::FontUsageType type  )
    // {

    //     void SaveFont( wxXmlNode* parent, Design::FontUsageType type );

    //             SaveFont( fonts, type, m_nbrFont, m_catNbrColor );


        // 
    void Settings::Save( )
    {
        wxFileName* filename = new wxFileName( GetConfigurationDirectory( ), "Settings", "xml" );
        wxString fullPath = filename->GetFullPath( );
        wxXmlDocument doc;

        wxXmlNode* settings = NewNode( &doc, "Settings" );

        // wxXmlNode* child = NewNode( settings, "ImageDirectory" );
        // if ( child )
        // { 
        //     child = NewNode( child, "File" );
        //     child->AddAttribute( "Name", GetImageDirectory( ) );
        // }

        wxXmlNode* child = NewNode( settings, "LastFile" );
        if ( child )
        {
            child->AddAttribute( "LoadLastFileAtStartUp", Bool2String( GetLoadLastFileAtStartUp( ) ) );
            child = NewNode( child, "File" );
            child->AddAttribute( "Name", GetLastFile( ) );
        }

        wxXmlNode* fonts = NewNode( settings, "Fonts" );
        if ( fonts )
        {
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_NbrFontType ], Design::AT_NbrFontType );
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_NameFontType ], Design::AT_NameFontType );
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_TextFontType ], Design::AT_TextFontType );
            GetFontList( )->SaveFont( fonts, FontPreference[ Design::AT_TitleFontType ], Design::AT_TitleFontType );
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
            m_sortOrder.Add( Catalog::NT_Period );
            m_sortOrder.Add( Catalog::NT_Decade );
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

        // if ( !m_nbrFont.IsOk( ) )
        // {
        //     SetDirty( );
        //     font.SetWeight( wxFONTWEIGHT_THIN );
        //     font.SetStyle( wxFONTSTYLE_ITALIC );
        //     font.SetPointSize( 8 );
        //     m_nbrFont = font;
        // }

        // if ( !m_catNbrColor.IsOk( ) )
        // {
        //     SetDirty( );
        //     m_catNbrColor = m_defaultFontColor;
        // }

        // if ( !m_titleFont.IsOk( ) )
        // {
        //     SetDirty( );
        //     font.SetWeight( wxFONTWEIGHT_BOLD );
        //     font.SetStyle( wxFONTSTYLE_NORMAL );
        //     font.SetPointSize( 12 );
        //     m_titleFont = font;
        // }

        // if ( !m_titleColor.IsOk( ) )
        // {
        //     SetDirty( );
        //     m_titleColor = m_defaultFontColor;
        // }

        // if ( !m_textFont.IsOk( ) )
        // {
        //     SetDirty( );
        //     font.SetWeight( wxFONTWEIGHT_NORMAL );
        //     font.SetStyle( wxFONTSTYLE_NORMAL );
        //     font.SetPointSize( 10 );
        //     m_textFont = font;
        // }

        // if ( !m_textColor.IsOk( ) )
        // {
        //     SetDirty( );
        //     m_textColor = m_defaultFontColor;
        // }

        // if ( !m_nameFont.IsOk( ) )
        // {
        //     SetDirty( );
        //     font.SetWeight( wxFONTWEIGHT_NORMAL );
        //     font.SetStyle( wxFONTSTYLE_NORMAL );
        //     font.SetPointSize( 10 );
        //     m_nameFont = font;
        // }

        // if ( !m_textColor.IsOk( ) )
        // {
        //     SetDirty( );
        //     m_textColor = m_defaultFontColor;
        // }
    }

    // 
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
        wxXmlNode* child = root->GetChildren( );;

        while ( child )
        {
            wxString name = child->GetName( );
            if ( !name.Cmp( "SortOrder" ) )
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

            else if ( !name.Cmp( "PeriodDivision" ) )
            {
                m_lowerDivision = child->GetAttribute( "LowerDivision" );
                if ( m_lowerDivision.IsEmpty( ) )
                {
                    m_lowerDivision = m_defaultLowerDivision;
                }

                m_upperDivision = child->GetAttribute( "UpperDivision" );
                if ( m_upperDivision.IsEmpty( ) )
                {
                    m_upperDivision = m_defaultUpperDivision;
                }
            }
            else if ( !name.Cmp( "Periods" ) )
            {
                m_lowerPeriod = child->GetAttribute( "LowerPeriod" );
                if ( m_lowerPeriod.IsEmpty( ) )
                {
                    m_lowerPeriod = m_defaultLowerPeriod;
                }
                m_middlePeriod = child->GetAttribute( "MiddlePeriod" );
                if ( m_middlePeriod.IsEmpty( ) )
                {
                    m_middlePeriod = m_defaultMiddlePeriod;
                }
                m_upperPeriod = child->GetAttribute( "UpperPeriod" );
                if ( m_upperPeriod.IsEmpty( ) )
                {
                    m_upperPeriod = m_defaultUpperPeriod;
                }
            }

            else if ( !name.Cmp( "LastFile" ) )
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
                            m_lastFile = wxGetHomeDir( );
                        }

                        wxFileName lf( m_lastFile );
                        wxSetWorkingDirectory( lf.GetPath( ) );
                    }
                }
            }

            else if ( !name.Cmp( "StampDataEdit" ) )
            {
                wxString defaultVal = child->GetAttribute( "Default" );
                bool isTrue = !defaultVal.Cmp( "true" );
                SetCatalogVolumeEditable( isTrue );
                SetCatalogVolumeEditableDefault( isTrue );
            }

            else if ( !name.Cmp( "IDPreference" ) )
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

            else if ( !name.Cmp( "RecentFileList" ) )
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

            else if ( !name.Cmp( "Fonts" ) )
            {

                FontPreference[ Design::AT_NbrFontType ] = GetFontList( )->LoadFont( child, Design::AT_NbrFontType );
                if ( FontPreference[ Design::AT_NbrFontType ].Get( ) < 0 )
                {
                    FontPreference[ Design::AT_NbrFontType ].Set( GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_NbrFontType ] ) );
                }

                FontPreference[ Design::AT_NameFontType ] = GetFontList( )->LoadFont( child, Design::AT_NameFontType );
                if ( FontPreference[ Design::AT_NameFontType ].Get( ) < 0 )
                {
                    FontPreference[ Design::AT_NameFontType ].Set( GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_NameFontType ] ) );
                }

                FontPreference[ Design::AT_TextFontType ] = GetFontList( )->LoadFont( child, Design::AT_TextFontType );
                if ( FontPreference[ Design::AT_TextFontType ].Get( ) < 0 )
                {
                    FontPreference[ Design::AT_TextFontType ].Set( GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_TextFontType ] ) );
                }

                FontPreference[ Design::AT_TitleFontType ] = GetFontList( )->LoadFont( child, Design::AT_TitleFontType );
                if ( FontPreference[ Design::AT_TitleFontType ].Get( ) < 0 )
                {
                    FontPreference[ Design::AT_TitleFontType ].Set( GetFontList( )->DefaultFont( Design::DefaultPointSize[ Design::AT_TitleFontType ] ) );
                }

                //     wxXmlNode* fontChild = child->GetChildren( ) ;
                //     while ( fontChild )
                //     { 
                //         wxString nativeFontString;
                //         wxFont font;
                //         wxString colorStr;
                //         wxColour color;
                //         Design::FontUsageType type = Utils::LoadFont( fontChild, nativeFontString, colorStr );
                //         if ( type == Design::AT_NbrFontType )
                //         { 
                //             font = wxFont( nativeFontString );
                //             if ( !font.IsOk( ) )
                //             {
                //                 font = *wxNORMAL_FONT;
                //                 font.SetPointSize( 8 );
                //             }

                //             color = wxColour( colorStr );
                //             if ( !color.IsOk( ) )
                //             {
                //                 color = *wxBLACK;
                //             }

                //             SetNbrFont( font );
                //             SetNbrColor( color );
                //             SetAppPrefCatNbrFontNdx( GetFontList()->AddNewFont( font, color ) );
                //         }
                //         else if ( type == Design::AT_TextFontType )
                //         { 
                //             font = wxFont( nativeFontString );
                //             if ( !font.IsOk( ) )
                //             {
                //                 font = *wxNORMAL_FONT;
                //                 font.SetPointSize( 10 );
                //             }

                //             color = wxColour( colorStr );
                //             if ( !color.IsOk( ) )
                //             {
                //                 color = *wxBLACK;
                //             }

                //             SetTextFont( font );
                //             SetTextColor( color );
                //             SetAppPrefTextFontNdx( GetFontList()->AddNewFont( font, color ) );
                //         }
                //        else if ( type == Design::AT_TitleFontType )
                //         { 
                //             font = wxFont( nativeFontString );
                //             if ( !font.IsOk( ) )
                //             {
                //                 font = *wxNORMAL_FONT;
                //                 font.SetPointSize( 12 );
                //             }

                //             color = wxColour( colorStr );
                //             if ( !color.IsOk( ) )
                //             {
                //                 color = *wxBLACK;
                //             }

                //             SetTitleFont( font );
                //             SetTitleColor( color );
                //             SetAppPrefTitleFontNdx( GetFontList()->AddNewFont( font, color ) );
                //         }

                //         fontChild = fontChild->GetNext( );
                //    }
            }
            child = child->GetNext( );

        }


    }
    void Settings::DumpFont( wxString Level )
    {
        // std::cout << Level << "CatNbr font " << GetNbrFont().GetNativeFontInfoUserDesc( )
        //     << "  color " << GetNbrColor().GetAsString( )
        //     << "  Ndx " << m_appPrefNbrFontNdx.Get( ) << "\n";
        // std::cout << Level << "Name font " << GetNbrFont().GetNativeFontInfoUserDesc( )
        //     << "  color " << GetNameColor().GetAsString( )
        //     << "  Ndx " << m_appPrefNbrFontNdx.Get( ) << "\n";
        // std::cout << Level << "Text font " <<GetTextFont().GetNativeFontInfoUserDesc( )
        //     << "  color " << GetTextColor().GetAsString( )
        //     << "  Ndx " << m_appPrefTextFontNdx.Get( ) << "\n";
        // std::cout << Level << "Title font " << GetTitleFont().GetNativeFontInfoUserDesc( )
        //     << "  color " << GetTitleColor().GetAsString( )
        //     << "  Ndx " << m_appPrefTitleFontNdx.Get( ) << "\n";
    };

}