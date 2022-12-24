/**
 * @file CatalogVolumeData.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
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

#ifndef CatalogVolumeData_H
#define CatalogVolumeData_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <vector>

#include "CatalogDefs.h"
#include "utils/XMLUtilities.h"


namespace Catalog {


    class CatalogVolumeData
    {
    public:

        CatalogVolumeData( );
        ~CatalogVolumeData( );
        bool IsOK( );

        // Create a Catalog xml doc
        wxXmlDocument* NewDocument( );

        // Delete the current Catalog xml doc and replace with new doc
        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );

        // Get the Catalog XML doc
        wxXmlDocument* GetDoc( ) { return m_stampDoc; };

        //Create and load a new Catalog xml Doc
        void NewCatalog();

        void Save( );
        // Load Catalog xml file
        void LoadXML( );

        // Load Catalog csv file
        void LoadCSV( wxString filename );

       // wxString GetTitle( ) { return m_title; }
       // void SetTitle( wxString val ) { m_title = val; };

        wxXmlNode* FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value );
        wxXmlNode* FindNodeWithPropertyAndValue( wxString property, wxString value );

        void SetDirty( bool state = true );
        bool isDirty( ) { return m_dirty; };

    void SetVolumeFilename( wxString name ){ m_volumeFilename = name;};
    wxString GetVolumeFilename( ){ return m_volumeFilename;};
    wxString GetVolumeName()
    {
        wxXmlNode* root = m_stampDoc->GetRoot();
        return Utils::GetAttrStr(root,"Name");
    };
    void SetVolumeName( wxString str )
    {
        wxXmlNode* root = m_stampDoc->GetRoot();
        Utils::SetAttrStr( root, "Name", str );
    };
    private:
        wxString m_volumeFilename;
        wxXmlDocument* m_stampDoc;
      //  wxString m_title;
        bool m_dirty;
    };
    
    CatalogVolumeData* NewCatalogVolumeDataInstance();
    typedef std::vector<CatalogVolumeData*> CatalogVolumeDataArray;

}
#endif