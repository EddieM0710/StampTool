/**
 * @file Document.h
 * @author Eddie Monroe
 * @brief Encapsulates the actual reading and writing of the XML ODT file.
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
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
         * @brief Copies an image file to the ODT picturesdirectory and makes an entry in the manifest file.
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
        bool AddODTFile( wxZipOutputStream& zip, wxString f );

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
    private:

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


        /**
         * @brief Class member.
         *
         **************************************************/
        wxString m_workingDirectory;
    };
}

#endif
