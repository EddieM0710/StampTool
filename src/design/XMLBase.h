/**
 * @file layout/XMLBase.h
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

#ifndef XMLBase_h
#define XMLBase_h

#include <wx/string.h>
#include <vector>

#include "Defs.h"
#include "design/DesignDefs.h"
#include "design/Attribute.h"
#include <wx/xml/xml.h>
#include "utils/XMLUtilities.h"



namespace Design {

    class XMLBase;

    //typedef std::vector<XMLBase*> ChildList;

        /**
         * @brief Base class for all layout objects. The layout objects are
         * initialy loaded from the layout XML.
         *
         */
    class XMLBase
    {


    public:


        XMLBase( ) {  };

        XMLBase( wxXmlNode* ele );

        ~XMLBase( );

        Attribute* AttributeItem( int ndx ) {
            return m_attrArray.at( ndx );
        };

        void DeleteAttribute( wxString name );

        Attribute* FindAttr( wxString name );

        void DumpAttr( );

        wxString GetAttrStr( wxString name );

        wxString GetAttrStr( AlbumAttrType type );

        double GetAttrDbl( AlbumAttrType type );

        double GetAttrDbl( wxString name );

        int GetLineNumber( ) {
            return m_lineNbr;
        };

        int GetNbrAttr( ) {
            return m_attrArray.size( );
        };

        int GetNbrChildren( );

        AlbumBaseType GetNodeType( ) {
            return ( AlbumBaseType ) m_nodeType;
        };

        NodeStatus GetNodeStatus( ) {
            return m_nodeValid;
        };

        wxString GetObjectName( ) {
            return m_objectName;
        };

        wxString GetObjectText( ) {
            return m_text;
        };

        wxString GetText( ) {
            return m_text;
        }

        bool IsEqual( AlbumAttrType type, wxString val )
        {
            return !val.Cmp( GetAttrStr( type ) );
        }

        bool IsEqualDbl( AlbumAttrType type, double val )
        {
            return ( val == GetAttrDbl( type ) );
        }

        bool IsNodeType( AlbumBaseType type ) {
            return ( type == m_nodeType );
        };

        bool LoadAttributes( wxXmlNode* thisObject );

        virtual void Save( wxXmlNode* xmlNode ) = 0;

        void SetAttribute( wxXmlNode* xmlNode, AlbumAttrType type );

        void SetAttrStr( wxString name, wxString val );

        void SetAttrStr( AlbumAttrType type, wxString val );

        void SetAttrDbl( AlbumAttrType type, double val );

        void SetLineNumber( int nbr ) {
            m_lineNbr = nbr;
        };

        void SetObjectName( wxString name ) {
            m_objectName = name;
        }

        void SetObjectText( wxString text ) {
            m_text = text;
        }

        void SetNodeType( AlbumBaseType type ) {
            m_nodeType = type;
        };

        bool IsStatusOK( ) {
            return ( m_nodeValid != AT_FATAL );
        };

        void SetNodeStatus( NodeStatus status ) {
            m_nodeValid = status;
        };

    private:

        bool LoadChildren( wxXmlNode* parent );

        bool Load( wxXmlNode* thisObject );

        wxString m_objectName;
        int m_nodeType;
        int m_lineNbr;

    protected:
        LayoutAttributeArray m_attrArray;
        wxString m_text;
        NodeStatus m_nodeValid;
    };

}
#endif
