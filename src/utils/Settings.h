/**
 * @file Settings.h
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
 **************************************************/

#ifndef Settings_H
#define Settings_H

#include <wx/arrstr.h>
#include <wx/string.h>
#include "wx/xml/xml.h"
#include "utils/FontList.h"
#include "design/DesignDefs.h"

namespace Utils {

    class Settings;

    Settings* NewSettingsInstance( );

    /**
     * @brief Settings for the application
     *
     **************************************************/
    class Settings
    {
    public:
        Settings( );
        ~Settings( ) { };

        void InitSettings( );

        wxString GetConfigurationDirectory( ) { return m_configurationDirectory; };
        //wxString GetImageDirectory( ) { return m_imageDirectory; };
        wxString GetCatalogID( ) { return m_catalogID; };
        wxString GetCountryID( ) { return m_countryID; };

        bool GetLoadLastFileAtStartUp( ) { return m_loadLastFileAtStartUp; };
        wxString GetLowerDivision( ) { return m_lowerDivision; };
        wxString GetLowerPeriod( ) { return m_lowerPeriod; };
        wxString GetMiddlePeriod( ) { return m_middlePeriod; };
        wxArrayInt* GetSortOrder( ) { return &m_sortOrder; };
        wxString GetUpperDivision( ) { return m_upperDivision; };
        wxString GetUpperPeriod( ) { return m_upperPeriod; };

        wxFont GetNbrFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_NbrFontType ].Get( ) ); };
        wxColour GetNbrColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_NbrFontType ].Get( ) );; };

        wxFont GetNameFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_NameFontType ].Get( ) ); };
        wxColour GetNameColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_NameFontType ].Get( ) );; };

        wxFont GetTitleFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_TitleFontType ].Get( ) ); };
        wxColour GetTitleColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_TitleFontType ].Get( ) ); };

        wxFont GetTextFont( ) { return GetFontList( )->GetFont( FontPreference[ Design::AT_TextFontType ].Get( ) ); };
        wxColour GetTextColor( ) { return GetFontList( )->GetColor( FontPreference[ Design::AT_TextFontType ].Get( ) ); };


        int GetFontNdxPreference( Design::AT_FontUsageType fontType ) { return FontPreference[ fontType ].Get( ); };
        void SetFontNdxPreference( Design::AT_FontUsageType fontType, int ndx ) { FontPreference[ fontType ].Set( ndx ); };

        void SetConfigurationDirectory( wxString val ) { m_configurationDirectory = val.Trim( ); m_dirty = true; };
        //void SetImageDirectory( wxString val ) { m_imageDirectory = val.Trim( );m_dirty = true; };
        void SetCatalogID( wxString val ) { m_catalogID = val.Trim( ); m_dirty = true; };
        void SetCountryID( wxString val ) { m_countryID = val.Trim( ); m_dirty = true; };
        void SetLoadLastFileAtStartUp( bool state = true ) { m_loadLastFileAtStartUp = state; };
        void SetLowerDivision( wxString val ) { m_lowerDivision = val.Trim( ); m_dirty = true; };
        void SetLowerPeriod( wxString val ) { m_lowerPeriod = val.Trim( ); m_dirty = true; };
        void SetMiddlePeriod( wxString val ) { m_middlePeriod = val.Trim( ); m_dirty = true; };
        void SetUpperDivision( wxString val ) { m_upperDivision = val.Trim( ); m_dirty = true; };
        void SetUpperPeriod( wxString val ) { m_upperPeriod = m_configurationDirectory.Trim( ); m_dirty = true; };

        // void SetAppPrefTitleFontNdx( int ndx ) { FontPreference[ Design::AT_TitleFontType ].Set( ndx ); };
        // void SetAppPrefTextFontNdx( int ndx ) { FontPreference[ Design::AT_TitleFontType ].Set( ndx ); };
        // void SetAppPrefCatNbrFontNdx( int ndx ) { FontPreference[ Design::AT_TitleFontType ].Set( ndx ); };


        int GetNextSortClassification( int current );
        void SetSettingValue( wxString& setting, wxXmlNode* parent, wxString childName, wxString defaultVal );
        void SetLastFile( wxString file );
        inline wxString GetLastFile( ) { return m_lastFile; };

        void Load( );
        void Save( );


        void AddRecent( wxString filename );
        wxArrayString* GetRecentArray( ) { return &m_recentFiles; };
        void SetNbrRecentPreference( int val ) { m_nbrRecentPreference = val; m_dirty = true; };
        int GetNbrRecentPreference( ) { return m_nbrRecentPreference; };
        void SetDirty( bool state = true );
        bool isDirty( ) { return m_dirty; };
        void SetDefaults( );
        wxString GetCatCodePrefix( )
        {
            wxString str = "";
            if ( !m_countryID.IsEmpty( ) && !m_catalogID.IsEmpty( ) )
            {
                str = m_catalogID + ":" + m_countryID;
            }
            else
            {
                str = m_defaultCatalogID + ":" + m_defaultCountryID;
            }
            return str;
        };
        bool IsCatalogSectionDataEditable( ) { return m_catalogSectionDataEditable; };
        void SetCatalogSectionDataEditable( bool val = true ) { m_catalogSectionDataEditable = val; };
        bool IsCatalogSectionDataEditableByDefault( ) { return m_catalogSectionDataEditableDefault; };
        void SetCatalogSectionDataEditableDefault( bool val = true ) { m_catalogSectionDataEditableDefault = val; };

        void DumpFont( wxString Level = "" );


    private:
        wxString m_lastFile;
        bool m_loadLastFileAtStartUp;
        wxString m_configurationDirectory;
        //    wxString m_imageDirectory;
        wxString m_countryID;
        wxString m_catalogID;
        wxArrayInt m_sortOrder;
        wxString m_lowerDivision;
        wxString m_upperDivision;
        wxString m_lowerPeriod;
        wxString m_middlePeriod;
        wxString m_upperPeriod;
        // wxFont m_nbrFont;
        // wxColour m_catNbrColor;
        // wxFont m_titleFont;
        // wxColour m_titleColor;
        // wxFont m_textFont;
        // wxColour m_textColor;
        // wxFont m_nameFont;
        // wxColour m_nameColor;
        wxArrayString m_recentFiles;
        int m_nbrRecentPreference;
        bool m_catalogSectionDataEditable;
        bool m_catalogSectionDataEditableDefault;

        const wxString m_defaultLastFile = "";
        const bool m_defaultloadLastFileAtStartUp = true;
        const wxString m_defaultConfigurationDirectory = "";
        const wxString m_defaultImageDirectory = "";
        const wxString m_defaultCountryID = "GB";
        const wxString m_defaultCatalogID = "SG";
        wxArrayInt m_defaultSortOrder;
        const wxString m_defaultLowerDivision = "1950";
        const wxString m_defaultUpperDivision = "2000";
        const wxString m_defaultLowerPeriod = "Antique";
        const wxString m_defaultMiddlePeriod = "Classical";
        const wxString m_defaultUpperPeriod = "Modern";

        // Utils::FontNdx m_appPrefTitleFontNdx;
        // Utils::FontNdx m_appPrefTextFontNdx;
        // Utils::FontNdx m_appPrefNbrFontNdx;
        // Utils::FontNdx m_appPrefNameFontNdx;

        Utils::FontNdx FontPreference[ Design::AT_NbrFontUsageTypes ];
        const wxColour m_defaultFontColor = *wxBLACK;

        //const wxArrayString m_defaultrecentFiles;
        const int m_defaultNbrRecentPreference = 4;
        bool m_dirty;
    };
}
#endif