/**
 * @file Settings.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef Settings_H
#define Settings_H

#include <wx/arrstr.h>
#include <wx/string.h>
#include "wx/xml/xml.h"


namespace Utils {

    /**
     * @brief Settings for the application
     *
     **************************************************/
    class Settings
    {
    public:
        Settings( );
        ~Settings( ) {};
        wxString GetConfigurationDirectory( ) { return m_configurationDirectory; };
        wxString GetWorkingDirectory( ) { return m_workingDirectory; };
        wxString GetImageDirectory( ) { return m_imageDirectory; };
        wxString GetCatalogID( ) { return m_catalogID; };
        wxString GetCountryID( ) { return m_countryID; };

        bool GetLoadLastFileAtStartUp( ) { return m_loadLastFileAtStartUp; };
        wxString GetLowerDivision( ) { return m_lowerDivision; };
        wxString GetLowerPeriod( ) { return m_lowerPeriod; };
        wxString GetMiddlePeriod( ) { return m_middlePeriod; };
        wxArrayInt* GetSortOrder( ) { return &m_sortOrder; };
        wxString GetUpperDivision( ) { return m_upperDivision; };
        wxString GetUpperPeriod( ) { return m_upperPeriod; };


        void SetConfigurationDirectory( wxString val ) { m_configurationDirectory = val; m_dirty = true; };
        void SetWorkingDirectory( wxString dir ) { m_workingDirectory = dir;  m_dirty = true; };
        void SetImageDirectory( wxString val ) { m_imageDirectory = val; m_dirty = true; };
        void SetCatalogID( wxString val ) { m_catalogID = val;  m_dirty = true; };
        void SetCountryID( wxString val ) { m_countryID = val; m_dirty = true; };
        void SetLoadLastFileAtStartUp( bool state = true ) { m_loadLastFileAtStartUp = state; };
        void SetLowerDivision( wxString val ) { m_lowerDivision = val;  m_dirty = true; };
        void SetLowerPeriod( wxString val ) { m_lowerPeriod = val;  m_dirty = true; };
        void SetMiddlePeriod( wxString val ) { m_middlePeriod = val; m_dirty = true; };
        void SetUpperDivision( wxString val ) { m_upperDivision = val;  m_dirty = true; };
        void SetUpperPeriod( wxString val ) { m_upperPeriod = val; m_dirty = true; };

        int GetNextSortClassification( int current );

        void SetSettingValue( wxString& setting, wxXmlNode* parent, wxString childName, wxString defaultVal );


        /**
         * @brief Set the last used file
         *
         * @param file filename to save as last file
         */
        void SetLastFile( wxString file );

        /**
         * @brief Get the Last File object
         *
         * @return wxString
         */
        inline wxString GetLastFile( ) { return m_lastFile; };

        /**
         * @brief Set the Last Directory object
         *
         * @param  dir path of the last used directory
         */
         /**
          * @brief Load the settings file
          *
          */
        void Load( );

        /**
         * @brief  Save the settings file
         *
         */
        void Save( );


        void AddRecent( wxString filename );
        wxArrayString* GetRecentArray( ) { return &m_recentFiles; };
        void SetNbrRecentPreference( int val ) { m_nbrRecentPreference = val; m_dirty = true; };
        int GetNbrRecentPreference( ) { return m_nbrRecentPreference; };
        void SetDirty( bool state = true ) { m_dirty = state; };
        bool isDirty( ) { return m_dirty; }
    private:
        wxString m_lastFile;
        bool m_loadLastFileAtStartUp;
        wxString m_workingDirectory;
        wxString m_configurationDirectory;
        wxString m_imageDirectory;
        wxString m_countryID;
        wxString m_catalogID;
        wxArrayInt m_sortOrder;
        wxString m_lowerDivision;
        wxString m_upperDivision;
        wxString m_lowerPeriod;
        wxString m_middlePeriod;
        wxString m_upperPeriod;
        wxArrayString m_recentFiles;

        int m_nbrRecentPreference;
        bool m_dirty;
    };
}
#endif