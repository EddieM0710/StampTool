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

    class Defaults;

    /**
     * @brief Base class for all layout objects. The layout objects are
     * initialy loaded from the layout XML.
     *
     */
    class AlbumBase : public XMLBase
    {


    public:

        AlbumBase( ) : XMLBase( ( wxXmlNode* ) 0 )
        {

            // SetTopContentMargin( 2 );
            // SetBottomContentMargin( 2 );
            // SetLeftContentMargin( 2 );
            // SetRightContentMargin( 2 );
        };

        AlbumBase( wxXmlNode* ele ) : XMLBase( ele )
        {

            // SetTopContentMargin( 2 );
            // SetBottomContentMargin( 2 );
            // SetLeftContentMargin( 2 );
            // SetRightContentMargin( 2 );
        }

        ~AlbumBase( );

        wxArrayString* GetErrorArray( ) {
            return &m_errorArray;
        };

        int GetNbrChildren( );

        NodeStatus GetNodeStatus( ) {
            return m_nodeValid;
        };

        AlbumBase* GetParent( );

        wxTreeItemId GetTreeItemId( ) {
            return m_treeID;
        };

        bool HasChildren( );

        bool IsStatusOK( ) {
            return ( m_nodeValid != AT_FATAL );
        };

        virtual void LoadFonts( wxXmlNode* node ) = 0;

        void SetNodeStatus( NodeStatus status ) {
            m_nodeValid = status;
        };

        void SetTreeItemId( wxTreeItemId id ) {
            m_treeID = id;
        };

        NodeStatus ValidateChildren( AlbumBase* node );

        virtual NodeStatus ValidateNode( ) = 0;

        double GetAlbumAttributeDbl( Design::AlbumAttrType type );

        wxString GetAlbumAttributeStr( Design::AlbumAttrType type );

        bool GetAlbumAttributeBool( Design::AlbumAttrType type, bool defVal = false );

        void SetAlbumAttributeBool( Design::AlbumAttrType type, bool val );

        void SetAlbumAttributeDbl( Design::AlbumAttrType type, double val );

        void SetAlbumAttributeStr( Design::AlbumAttrType type, wxString val );

        bool IsDefaultVal( AlbumAttrType type );

        bool IsDefaultVal( AlbumAttrType type, wxString val );

        Defaults* GetDefaults( )
        {
            return m_albumDefaults;
        }


    protected:

        void SetDefaults( Defaults* defaults ){
            m_albumDefaults = defaults;
        }
    private:

        wxTreeItemId m_treeID;
        wxArrayString m_errorArray;
        Defaults* m_albumDefaults;

    protected:

    };
}
#endif
