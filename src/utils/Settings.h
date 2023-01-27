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
        wxString GetCatNbrFontString( ) { return m_catNbrFontString; };
        wxString GetCatNbrColorString( ) { return  m_catNbrColorString; };
        wxString GetTitleFontString( ) { return m_titleFontString; };
        wxString GetTitleColorString( ) { return m_titleColorString; };
        wxString GetTextFontString( ) { return m_textFontString; };
        wxString GetTextColorString( ) { return m_textColorString; };

        void SetConfigurationDirectory( wxString val ) { m_configurationDirectory = val.Trim( ); m_dirty = true; };
        //void SetImageDirectory( wxString val ) { m_imageDirectory = val.Trim( );m_dirty = true; };
        void SetCatalogID( wxString val ) { m_catalogID = val.Trim( );m_dirty = true; };
        void SetCountryID( wxString val ) { m_countryID = val.Trim( );m_dirty = true; };
        void SetLoadLastFileAtStartUp( bool state = true ) { m_loadLastFileAtStartUp = state; };
        void SetLowerDivision( wxString val ) { m_lowerDivision = val.Trim( );m_dirty = true; };
        void SetLowerPeriod( wxString val ) { m_lowerPeriod = val.Trim( );m_dirty = true; };
        void SetMiddlePeriod( wxString val ) { m_middlePeriod = val.Trim( );m_dirty = true; };
        void SetUpperDivision( wxString val ) { m_upperDivision = val.Trim( );m_dirty = true; };
        void SetUpperPeriod( wxString val ) { m_upperPeriod = m_configurationDirectory.Trim( );m_dirty = true; };
        void SetCatNbrFontString( wxString val ) { m_catNbrFontString = val.Trim( );m_dirty = true; };
        void SetCatNbrColorString( wxString val ) { m_catNbrColorString = val.Trim( );m_dirty = true; };
        void SetTitleFontString( wxString val ) { m_titleFontString = val.Trim( );m_dirty = true; };
        void SetTitleColorString( wxString val ) { m_titleColorString = val.Trim( );m_dirty = true; };
        void SetTextFontString( wxString val ) { m_textFontString = val.Trim( );m_dirty = true; };
        void SetTextColorString( wxString val ) { m_textColorString = val.Trim( );m_dirty = true; };


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
        bool IsCatalogSectionDataEditable( ){ return m_catalogSectionDataEditable; };
        void SetCatalogSectionDataEditable( bool val = true ){ m_catalogSectionDataEditable = val; };
        bool IsCatalogSectionDataEditableByDefault( ){ return m_catalogSectionDataEditableDefault; };
        void SetCatalogSectionDataEditableDefault( bool val = true ){ m_catalogSectionDataEditableDefault = val; };
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
        wxString m_catNbrFontString;
        wxString m_catNbrColorString;
        wxString m_titleFontString;
        wxString m_titleColorString;
        wxString m_textFontString;
        wxString m_textColorString;
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

        //const wxString m_defaultTitleFont = "Serif 12";
        //const wxString m_defaultTextFont = "Serif 10";
        //const wxString m_defaultCatNbrFont = "Serif 8";
        const wxString m_defaultFontColor = "BLACK";

        //const wxArrayString m_defaultrecentFiles;
        const int m_defaultNbrRecentPreference = 4;
        bool m_dirty;
    };
}
#endif