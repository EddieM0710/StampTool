/**
 * @file Document.h
 * @author Eddie Monroe
 * @brief Encapsulates the actual reading and writing of the XML ODT file.
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
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
 **************************************************/
#ifndef Document_h
#define Document_h


#include <wx/xml/xml.h>
#include "design/Album.h"
#include "wx/string.h"
#include <wx/zipstrm.h>
#include "odt/Mimetype.h"
#include "odt/Manifest.h"
#include "odt/Content.h"
#include "odt/Meta.h"
#include "odt/Settings.h"
#include "odt/Styles.h"

namespace ODT {

    class DocumentManager;

    /**
     * @brief Encapsulates the actual reading and writing of the XML ODT file.
     *
     **************************************************/
    class Document
    {
    public:

        /**
         * @brief Construct a new Document object
         *
         **************************************************/
        Document(  );

        /**
         * @brief Destroy the Document object
         *
         **************************************************/
        ~Document( ) {};

        /**
         * @brief Create a Temp Document Directory object. created at /Temp/.StampAlbumGen
         *
         * @return true
         * @return false
         **************************************************/
        bool CreateTempDocumentDirectory( );

        /**
         * @brief Create all the Files in the ODT zip file
         *
         * @return true
         * @return false
         **************************************************/
        bool CreateDocFiles( );

        /**
         * @brief Save the internal ODT parts, zip it up and rename it to ODT.
         *
         **************************************************/
        void MakeDocument( );


        /**
         * @brief Create all the parts for the ODT Document
         *
         * @param albumBase
         * @return true
         * @return false
         **************************************************/
        bool InitODTFiles( );

        /**
         * @brief Adds a border for all the album pages. The border
         * is actually an image of a border pasted as the page background.
         *
         * @param filename - border image to add
         * @return void
         **************************************************/
        void AddBorder( wxString filename );

        /**
         * @brief Copies an image file to the ODT pictures directory and makes an entry in the manifest file.
         *
         * @param filename
         * @return wxString
         **************************************************/
        wxString AddImageFile( wxString filename );

        /**
         * @brief Returns a wxString of the bsolute path to the file.
         *
         * @param file
         * @return wxString
         **************************************************/
        wxString MakeAbsolute( wxString file );

        /**
         * @brief Writes all the XML ODT documents to the tmp directory
         *
         * @return true
         * @return false
         **************************************************/
        bool SaveFiles( );

        /**
         * @brief Saves the mime file
         *
         * @return true
         * @return false
         **************************************************/
        bool SaveMimetype( );

        /**
         * @brief
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* FindOfficeStyles( );

        /**
         * @brief
         *
         * @return true
         * @return false
         **************************************************/
        bool AddPageFrameStyles( );

        // Manifest member functions
        /**
         * @brief Get the Manifest object
         *
         * @return wxXmlDocument*
         **************************************************/
        wxXmlDocument* GetManifest( );

        /**
         * @brief
         *
         * @param fullPath
         * @param mediaType
         **************************************************/
        void AddManifestFileEntry( wxString fullPath, wxString mediaType );

        /**
         * @brief Get the Meta object
         *
         * @return wxXmlDocument*
         **************************************************/
       // wxXmlDocument* GetMeta( );

        /**
         * @brief Get the Settings object
         *
         * @return wxXmlDocument*
         **************************************************/
       // wxXmlDocument* GetSettings( );

        /**
         * @brief
         *
         * @return true
         * @return false
         **************************************************/
        bool MakeODT( );

        /**
         * @brief
         *
         * @param zip
         * @param f
         * @return true
         * @return false
         **************************************************/
        bool AddODTFile( wxZipOutputStream& zip, wxString f, wxString baseDir );

        /**
         * @brief Get the File List object
         *
         * @param fileArray
         * @param searchStr
         * @param flag
         * @return int
         **************************************************/
        int GetFileList( wxArrayString& fileArray, wxString searchStr, int flag = 0 );

        wxXmlDocument* ContentXML( ) { return m_contentDoc->ContentXML( ); };
        wxXmlDocument* SettingsXML( ) { return m_settingsDoc->SettingsXML( ); };
        wxXmlDocument* StylesXML( ) { return m_stylesDoc->StylesXML( ); };
        wxXmlDocument* ManifestXML( ) { return m_manifestDoc->ManifestXML( ); };
        wxXmlDocument* MetaXML( ) { return m_metaDoc->MetaXML( ); };

        Content* ContentDoc( ) { return m_contentDoc; };
        Settings* SettingsDoc( ) { return m_settingsDoc; };
        Styles* StylesDoc( ) { return m_stylesDoc; };
        Manifest* ManifestDoc( ) { return m_manifestDoc; };
        Meta* MetaDoc( ) { return m_metaDoc; };
        wxString GetTmpDir(){ return m_tmpDir.GetFullPath();};
        wxString GetStampGenDir(){ return m_stampAlbumGen.GetFullPath();};
        wxString GetDocFilesDir(){ return m_docFiles.GetFullPath();};
        wxString GetThumbnailsDir(){ return m_thumbnailsDir.GetFullPath();};
        wxString GetMetaInf(){ return m_metaInfDir.GetFullPath();};;
        wxString GetConfigurationsDir(){ return m_configurations2Dir.GetFullPath();};
        wxString GetPicturesDir(){ return m_picturesDir.GetFullPath();};


    private:

        wxFileName m_tmpDir;
        wxFileName m_stampAlbumGen;
        wxFileName m_docFiles;
        wxFileName m_thumbnailsDir;
        wxFileName m_metaInfDir;
        wxFileName m_configurations2Dir;
        wxFileName m_picturesDir;

        //DocumentManager* m_parent;
        MimeType* m_mimeTypeDoc;
        /**
         * @brief Class member. Pointer to the odt content XMLDocumwnt.
         *
         **************************************************/
        Content* m_contentDoc;


        /**
         * @brief Class member. Pointer to the odt content XMLDocumwnt.
         *
         **************************************************/
        Manifest* m_manifestDoc;

        /**
         * @brief Class member. Pointer to the odt meta XMLDocumwnt.
         *
         **************************************************/
        Meta* m_metaDoc;

        /**
         * @brief Class member. Pointer to the odt settings XMLDocumwnt.
         *
         **************************************************/
        Settings* m_settingsDoc;

        /**
         * @brief Class member. Pointer to the odt styles XMLDocumwnt.
         *
         **************************************************/
        Styles* m_stylesDoc;
    };
}

#endif
