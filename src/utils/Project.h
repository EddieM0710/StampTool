/* 
 * @file Project.h
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * This file is part of AlbumGenerator.
 * 
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 * 
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 * 
 */
#ifndef Project_h
#define Project_h

#include "wx/string.h"
#include <wx/xml/xml.h>
#include "gui/GeneratorData.h"

namespace Utils {

    Project* NewProjectInstance();

    class Project
    {
    public:
        Project( );
        ~Project( ) { if ( m_ProjectDoc ) { delete m_ProjectDoc; } };
        
        void InitProject();

        wxString GetProjectFilename( ) { return m_projectFilename; };
        void SetProjectFilename( wxString name );

        wxString GetODTOutputFilename( );
        void SetODTOutputFilename( wxString outputFilename );

        wxString GetDesignFilename( );
        void SetDesignFilename( wxString albumFilename );;


        wxString GetImagePath( );
        void SetImagePath( wxString imagePath );

        wxString GetCatalogFilename( );
        void SetCatalogFilename( wxString catalogFilename );

        // Load the Project xml file
        bool LoadProjectXML( );

        //Load the project xml attributes
        void LoadAttributes( wxXmlNode* thisObject );

        // save the project to an xml file
        void Save( );

        // make the filename absolute if its not already
        wxString MakeFileAbsolute( wxString filename );

        //inline GeneratorData* GetGeneratorData(){ return &m_generatorData; };

        void SetDirty( bool state = true ) { m_dirty = state; };
        // Is project dirty?
        bool isDirty( ) { return m_dirty; };

    private:
        wxXmlDocument* m_ProjectDoc;
        wxString m_projectFilename;
        wxString m_ODTOutputFilename;
        wxString m_designFilename;
        wxString m_imagePath;
        wxString m_catalogFilename;
        bool m_dirty;

    };
}
#endif