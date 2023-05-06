/**
 * @file AlbumVolume.h
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

#ifndef AlbumVolume_H
#define AlbumVolume_H

#include "Defs.h"
#include "design/DesignDefs.h"
#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/treebase.h>
#include "utils/XMLUtilities.h"

class AlbumTreeCtrl;


namespace Design {

    class Album;
    class LayoutBase;
    class AlbumBase;

    /// @brief class that contains all the data for the Album design
    class AlbumVolume
    {

    public:

        /// @brief Construct a new Catalog Data object
        AlbumVolume( );

        /// @brief Destroy the Album Volume object
        ///  
        ~AlbumVolume( );

        /// @brief Get the Album object
        ///  
        ///  @return Album* 
        Album* GetAlbum( ) { return m_album; };

        /// @brief Get the Album Filename object
        ///  
        ///  @return wxString 
        wxString GetAlbumFilename( ) { return m_albumFilename; };

        /// @brief Get the Album Name object
        ///  
        ///  @return wxString 
        wxString GetAlbumName( )
        {
            wxXmlNode* root = m_albumDoc->GetRoot( );
            if ( root )
            {
                return Utils::GetAttrStr( root, "Name" );
            }
            return "";
        };

        /// @brief Get the AlbumVolume xml Doc
        wxXmlDocument* GetDoc( ) { return m_albumDoc; };

        /// @brief Gets the page of the selected design given node
        AlbumBase* GetPage( AlbumBase* node );

        /// @brief 
        ///  
        ///  @return AlbumVolume* 
        AlbumVolume* InitAlbumVolume( );

        /// @brief 
        ///  
        ///  @return true 
        ///  @return false 
        bool isDirty( ) { return m_dirty; };

        /// @brief 
        ///  
        ///  @return true 
        ///  @return false 
        bool IsOK( );

        /// @brief create new AlbumVolume xml wxXmlDocument
        wxXmlDocument* NewDesignDocument( );

        /// @brief create a new design document with default data
        void LoadDefaultDocument( );

        /// @brief Save the AlbumVolume to an xml file  
        /// @param filename 
        void SaveXML( );

        /// @brief transfers the AlbumVolume tree to an xml file
        void SaveDesignTree( );

        /// @brief loads an xml file into memory 
        bool LoadXML( );

        /// @brief Set the Album object
        ///  
        ///  @param album 
        void SetAlbum( Album* album ) { m_album = album; };

        /// @brief 
        ///  
        ///  @param node 
        void MakePage( Design::LayoutBase* node );

        /// @brief Set the design to dirty
        /// @param state 
        void SetDirty( bool state = true );

        /// @brief Set the Album Filename object
        ///  
        ///  @param name 
        void SetAlbumFilename( wxString name ) { m_albumFilename = name; };

        /// @brief Set the Album Name object
        ///  
        ///  @param str 
        void SetAlbumName( wxString str )
        {
            wxXmlNode* root = m_albumDoc->GetRoot( );
            if ( root )
            {
                Utils::SetAttrStr( root, "Name", str );
            }
        };

        /// @brief 
        ///  
        void UpdateAlbum( );

        /// @brief 
        ///  
        ///  @param node 
        void UpdatePage( AlbumBase* node );

        /// @brief 
        ///  
        ///  @param node 
        ///  @return NodeStatus 
        NodeStatus ValidatePage( AlbumBase* node );

    private:
        int isOKPtr;
        wxString m_albumFilename;
        wxXmlDocument* m_albumDoc;
        Album* m_album;
        bool m_dirty;
    };


    AlbumVolume* NewAlbumVolumeInstance( );
    typedef std::vector<AlbumVolume*> AlbumVolumeArray;
}
#endif