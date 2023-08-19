/**
 * @file CatalogVolume.h
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
 */

#ifndef CatalogVolume_H
#define CatalogVolume_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <vector>

#include "CatalogDefs.h"
#include "utils/XMLUtilities.h"

 //namespace Utils { class ImageRepository; };

namespace Catalog {

    class CatalogVolume;

    ///  @brief the array (actually a vector) of Catalog Volumes
    ///  
    typedef std::vector<CatalogVolume*> CatalogVolumeArray;

    /// @brief reate an instance of a Catalog Volume
    /// @return 
    CatalogVolume* NewCatalogVolumeInstance( );

    ///  @brief This is an in memory version og the catalog xml file. 
    ///  
    class CatalogVolume
    {
    public:


        ///  @brief Construct a new Catalog Volume object
        ///  
        CatalogVolume( );

        ///  @brief Destroy the Catalog Volume object
        ///  
        ~CatalogVolume( );

        ///  @brief Get the Volume Filename object
        ///  
        ///  @return wxString 
        wxString GetVolumeFilename( ) { return m_volumeFilename; };

        ///  @brief Set the Volume Name in the rot object
        ///  
        ///  @param str 
        void SetVolumeName( wxString str )
        {
            wxXmlNode* root = m_stampDoc->GetRoot( );
            if ( root )
            {
                Utils::SetAttrStr( root, "Name", str );
            }
        };

        ///  @brief Show the details dialog 
        ///  
        ///  @param parent 
        void EditDetailsDialog( wxWindow* parent );

        /// @brief Starting art element look through all the children for a node with given property/value pair.
        /// @param element 
        /// @param property 
        /// @param value 
        /// @return 
        wxXmlNode* FindNodeWithPropertyAndValue( wxXmlNode* element, wxString property, wxString value );

        /// @brief Starting at the doc root look through all the children for a node with given property/value pair.
        /// @param property 
        /// @param value 
        /// @return 
        wxXmlNode* FindNodeWithPropertyAndValue( wxString property, wxString value );

        bool FixupInventoryStatus( wxXmlNode* parent, InventoryStatusType status );

        bool FixupInventoryStatus( );

        /// Get the Catalog XML doc
        wxXmlDocument* GetDoc( ) { return m_stampDoc; };

        /// @brief Get the Album Filename object
        ///  
        ///  @return wxString 
        wxString GetCatalogFilename( ) { return m_volumeFilename; };

        wxString GetCatalogPath( );

        wxString GetCatalogBaseName( );

        wxString GetZipFileName( );

        ///  @brief Get the Volume Name from the doc root
        ///  
        ///  @return wxString 
        wxString GetVolumeName( )
        {
            wxXmlNode* root = m_stampDoc->GetRoot( );
            if ( root )
            {
                return Utils::GetAttrStr( root, "Name" );
            }
            return "";
        };

        ///  @brief is the dirty flag set?
        ///  
        ///  @return true 
        ///  @return false 
        bool isDirty( ) { return m_dirty; };

        ///  @brief sanity check on instance
        ///  
        ///  @return true 
        ///  @return false 
        bool IsOK( );

        void Load( );

        /// Load Catalog csv file
        bool LoadCSV( wxString filename );

        /// Load Catalog xml file
        void LoadXML( );

        /// this makes a list of the children entry elements that can have childrem
        Utils::wxXmlNodeArray* MakeParentList( Catalog::FormatType parentType );
        void MakeParentList( Catalog::FormatType parentType, Utils::wxXmlNodeArray* parentList, wxXmlNode* node );

        bool MakeCatalogList( wxArrayString& fileArray );
        bool MakeCatalogList( wxXmlNode* parent, wxArrayString& fileArray );

        ///Create and load a new Catalog xml Doc
        void NewCatalog( );

        /// Create a Catalog xml doc
        wxXmlDocument* NewDocument( );

        /// this is an attempt to group the entrys;
        /// i.e., an item of type entry can be a child of an item SeTenent type.
        void ReGroupMultiples( );

        /// Delete the current Catalog xml doc and replace with new doc
        wxXmlDocument* ReplaceDocument( wxXmlDocument* doc );

        /// resort the tree with the new sort order data.
        /// Probably doing this because the sort order was changed.
        void ReSortTree( );

        /// @brief ave to file
        void Save( );

        ///  @brief Set the Dirty flag
        ///  
        ///  @param state 
        void SetDirty( bool state = true );



        ///  @brief Set the Volume Filename object
        ///  
        ///  @param name 
        void SetVolumeFilename( wxString name ) { m_volumeFilename = name; };

        /// this looks through the xml tree and makes related entries of childType a child of the parent type
        void StructureCatalogVolume( Catalog::FormatType parentType,
            Catalog::FormatType childType,
            Catalog::FormatType secondChildType = Catalog::FT_FormatUnknown );

        bool UpdateMount( wxXmlNode* parent );

        bool UpdateMount( );

    private:
        wxString m_volumeFilename;
        wxXmlDocument* m_stampDoc;
        bool m_dirty;
    };

}
#endif