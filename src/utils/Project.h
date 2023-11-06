/*
 * @file Project.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-08-01
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
#ifndef Project_h
#define Project_h

#include "wx/string.h"
#include <wx/xml/xml.h>
#include "gui/StampToolFrame.h"
 ////#include "gui/AppData.h"

//#include "mount/StampMount.h"

//namespace Mount { class StampMount; };

namespace Utils {

    // Project* NewProjectInstance( );

    class Project
    {
    public:

        Project( );

        ~Project( ) {
            if ( m_ProjectDoc )
            {
                delete m_ProjectDoc;
            }
        };

        wxXmlNode* AddChild( wxXmlNode* child );

        wxXmlNode* AddNewAlbumVolume( wxString fileName, wxString  volName );

        wxXmlNode* AddNewCatalogVolume( wxString fileName, wxString  volName );

        void CloseProject( );

        bool ContinueIfDirty( wxWindow* parent );

        void FileNewProject( wxString sptName );

        void FileOpenProject( wxString filename );

        void FileSaveAsProject( wxString filename );

        void FileSaveProject( );

        wxXmlNode* GetAlbumListNode( ){
            return m_albumListNode;
        };

        wxXmlNode* GetCatalogListNode( ){
            return m_catalogListNode;
        };

        //     wxString GetDesignFilename( );

   //     void SetDesignFilename( wxString albumFilename );;

        wxImage GetImage( wxString filename );

        wxString GetOutputFilename( );

        wxString GetProjectFilename( ) {
            return m_projectFilename;
        };


        wxString GetImageFullPath( wxString imageName );

        //wxString GetCatalogFilename( );
        //void SetCatalogFilename( wxString catalogFilename );

        wxString GetProjectCatalogCode( ) {
            return m_projectCatalogCode;
        };

        wxString GetProjectCountryID( ) {
            return m_projectCountryID;
        };
        wxString GetImageDirectory( );

        bool ImageExists( wxString imageName );

        void InitProject( );

        // Is project dirty?
        bool IsDirty( ) {
            return m_dirty;
        };

        bool LoadProjectXML( );

        void LoadAttributes( wxXmlNode* thisObject );

        void LoadData( );

        void LoadTOCTree( );

        void  MakeNewProject( wxString fileName );

        // make a default xml project
        wxXmlDocument* MakeDefaultProjectDocument( );

        // make the filename absolute if its not already
        wxString MakeFileAbsolute( wxString filename );

        // save the project to an xml file
        void Save( );

        void SetCaption( );

        void SetProjectFilename( wxString name );

        void SetOutputFilename( wxString outputFilename );

        void SetImageDirectory( wxString imagePath );

        void SetProjectCountryID( wxString str );

        void SetProjectCatalogCode( wxString str );

        void SetDirty( bool state = true ) {
            m_dirty = state;
        };

    private:
        wxXmlDocument* m_ProjectDoc;
        wxXmlNode* m_catalogListNode;
        wxXmlNode* m_albumListNode;
        wxString m_projectFilename;
        wxString m_outputFilename;
        wxString m_designFilename;
        wxString m_imageDirectory;
        //wxString m_catalogFilename;
        wxString m_projectCountryID;
        wxString m_projectCatalogCode;

        //Mount::StampMount* m_stampMount;
        //Mount::StampMount* m_stampMount;

        bool m_dirty;

    };
}
#endif