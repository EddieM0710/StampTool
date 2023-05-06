/**
 * @file layout/AlbumBase.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
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
 */

#ifndef AlbumBase_h
#define AlbumBase_h

#include "design/XMLBase.h"
#include "design/AlbumVolume.h"
#include <wx/treectrl.h>


namespace Design {


    /**
     * @brief Base class for all layout objects. The layout objects are
     * initialy loaded from the layout XML.
     *
     */
    class AlbumBase : public XMLBase
    {


    public:

        AlbumBase( ) : XMLBase( ( wxXmlNode* ) 0 ) { };

        AlbumBase( wxXmlNode* ele ) : XMLBase( ele ) { }

        ~AlbumBase( );

        wxArrayString* GetErrorArray( ) { return &m_errorArray; };

        int GetNbrChildren( );

        NodeStatus GetNodeStatus( ) { return m_nodeValid; };

        AlbumBase* GetParent( );

        wxTreeItemId GetTreeItemId( ) { return m_treeID; };

        bool HasChildren( );

        bool IsStatusOK( ) { return ( m_nodeValid != AT_FATAL ); };

        virtual void LoadFonts( wxXmlNode* node ) = 0;

        void SetNodeStatus( NodeStatus status ) { m_nodeValid = status; };

        void SetTreeItemId( wxTreeItemId id ) { m_treeID = id; };

        NodeStatus ValidateChildren( AlbumBase* node );

        virtual NodeStatus ValidateNode( ) = 0;

    private:

        wxTreeItemId m_treeID;
        wxArrayString m_errorArray;

    protected:

    };
}
#endif
