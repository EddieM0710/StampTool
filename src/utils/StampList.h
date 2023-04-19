/**
 * @file StampList.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright ( c ) 2022
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

#ifndef StampLink_H
#define StampLink_H

#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/treectrl.h>

#include <vector>
#include "design/LayoutBase.h"
#include "design/Stamp.h"

namespace Utils {

    ///
    /// This is a link between an item in the catalog Tree and the Design/Album tree.
    ///
    class StampLink
    {
    public:

        /// @brief Construct a new Stamp Link object
        StampLink( ) { m_designTreeID = 0; m_catTreeID = 0; };

        /**
         * @brief Destroy the Stamp Link object
         *
         */
        ~StampLink( ) { Clear( ); };

        /**
         * @brief Get the Design/Album Tree ID
         *
         * @return wxTreeItemId
         */
        inline wxTreeItemId GetDesignTreeID( ) { return m_designTreeID; };

        /**
         * @brief Set the Design/Album Tree id
         *
         * @param id
         */

        inline void SetDesignTreeID( wxTreeItemId id ) { m_designTreeID = id; };

        //        inline Design::Stamp* GetAlbumStamp( ) { return m_albumStamp; };
        //        inline void SetAlbumStamp( Design::Stamp* stamp ) { m_albumStamp = stamp; };

               /**
                 * @brief Get the Catalog Tree ID
                 *
                 * @return wxTreeItemId
                 */
        inline wxTreeItemId GetCatTreeID( ) { return m_catTreeID; };

        /**
         * @brief Set the Catalog Tree id
         *
         * @param id
         */
        inline void SetCatTreeID( wxTreeItemId id ) { m_catTreeID = id; };

        //        inline wxXmlNode* GetCatNode( ) { return m_catNode; };
        //        inline void SetCatNode( wxXmlNode* stamp ) { m_catNode = stamp; };

          /**
           * @brief set cat and album tre ids
           *
           * @param catTreeID
           * @param albumID
           */
        void Update( wxTreeItemId catTreeID, wxTreeItemId albumID );

        /**
         * @brief sets the pointers to the link held by the cat tree and the Album tree to 0.
         Does not delete the link.
         *
         */
        void Clear( );

        /**
         * @brief Gets the Stamp catalog id of the link
         *
         * @return wxString
         */
        inline wxString GetID( );

        /**
         * @brief Is this the link of the catalog id passed in.
         *
         * @param id
         * @return true
         * @return false
         */
        inline bool IsStamp( wxString id );

    private:
        wxTreeItemId m_designTreeID;
        wxTreeItemId m_catTreeID;
    };

    typedef std::vector<StampLink*> StampLinkList;

    /**
     * @brief List of all the StampLinks in the Design tree.
     * @see StampLink
     */
    class StampList
    {
    public:
        /**
         * @brief Construct a new Stamp List object
         *
         */
        StampList( ) { };
        /**
         * @brief Destroy the Stamp List object
         *
         */
        ~StampList( ) { Clear( ); };

        /**
         * @brief Clears all the links then deletes them
         *
         */
        void Clear( );

        /**
         * @brief Get the position of the stamp in the list.
         *
         * @param stampID
         * @return int
         */
        int FindStamp( wxString stampID );

        /**
         * @brief returns the link if it exists or creates a new one and returns it.
         *
         * @param stampId
         * @return StampLink*
         */
        StampLink* AddStamp( wxString stampId );

        /**
         * @brief Calls FindStamp the inserts the Cat tree id
         *
         * @param stampID
         * @param treeID
         */
        void SetCatTreeID( wxString stampID, wxTreeItemId treeID );

        /// Calls FindStamp and returns thr tree id.
        bool GetCatTreeID( wxString stampID, wxTreeItemId& treeID );

        /**
         * @brief Same as FindStamp but returns the link pointer
         *
         * @param stampID
         * @return StampLink*
         */
        StampLink* FindStampLink( wxString stampID );

        /**
         * @brief Sets all catalog ids of all links to 0.
         *
         */
        void ClearCatalogLinks( );

        void DeleteLink( StampLink* link )
        {
            // Erase all even numbers
            for ( std::vector<StampLink*>::iterator it = m_list.begin( ); it != m_list.end( ); )
            {
                if ( *it == link )
                {
                    m_list.erase( it );
                    return;
                }
                it++;
            }
        };

    private:
        StampLinkList m_list;
    };
}
#endif
