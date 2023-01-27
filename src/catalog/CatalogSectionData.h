/**
 * @file CatalogSectionData.h
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
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

#ifndef CatalogSectionData_H
#define CatalogSectionData_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <vector>

#include "CatalogDefs.h"
#include "utils/XMLUtilities.h"


namespace Catalog { 


    class CatalogSectionData
    { 
    public:

        CatalogSectionData( );
        ~CatalogSectionData( );
        bool IsOK( );

        // Create a Catalog xml doc
        wxXmlDocument* NewDocument( );

        // Delete the current Catalog xml doc and replace with new doc
        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );

        // Get the Catalog XML doc
        wxXmlDocument* GetDoc( ) { return m_stampDoc; };

        //Create and load a new Catalog xml Doc
        void NewCatalog( );

        void Save( );
        // Load Catalog xml file
        void LoadXML( );

        // Load Catalog csv file
        bool LoadCSV( wxString filename );

        void ReSortTree( );

        Utils::wxXmlNodeArray* MakeParentList( Catalog::FormatType parentType );

        void StructureCatalogSectionData( Catalog::FormatType parentType, 
                        Catalog::FormatType childType, 
                        Catalog::FormatType secondChildType = Catalog::FT_FormatUnknown );

        void ReGroupMultiples( );

       // wxString GetTitle( ) { return m_title; }
       // void SetTitle( wxString val ) { m_title = val; };

        wxXmlNode* FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value );
        wxXmlNode* FindNodeWithPropertyAndValue( wxString property, wxString value );

        void SetDirty( bool state = true );
        bool isDirty( ) { return m_dirty; };

    void SetSectionFilename( wxString name ){ m_sectionFilename = name; };
    wxString GetSectionFilename( ){ return m_sectionFilename; };
    wxString GetSectionName( )
    { 
        wxXmlNode* root = m_stampDoc->GetRoot( );
        if ( root )
        { 
            return Utils::GetAttrStr( root, "Name" );
        }
        return "";
    };
    void SetSectionName( wxString str )
    { 
        wxXmlNode* root = m_stampDoc->GetRoot( );
        if ( root )
        { 
            Utils::SetAttrStr( root, "Name", str );
        }
    };

    wxString GetCatalogSectionImagePath( );
    void SetImagePath( wxString str );    
    void EditDetailsDialog(  wxWindow* parent );
    
    private:
        wxString m_sectionFilename;
        wxXmlDocument* m_stampDoc;
      //  wxString m_title;
        bool m_dirty;
    };
    
    CatalogSectionData* NewCatalogSectionDataInstance( );
    typedef std::vector<CatalogSectionData*> CatalogSectionDataArray;

}
#endif