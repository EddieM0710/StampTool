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

        /**
         * @brief Unused; Construct a new Album Design Object object
         *
         */
        XMLBase( ) {  };

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         */
        XMLBase( wxXmlNode* ele );

        ///  @brief Destroy the XMLBase object
        ///  
        ~XMLBase( );

        ///  @brief 
        ///  
        ///  @param ndx 
        ///  @return Attribute* 
        Attribute* AttributeItem( int ndx ) { return m_attrArray.at( ndx ); };

        ///  @brief 
        ///  
        ///  @param name 
        ///  @return Attribute* 
        Attribute* FindAttr( wxString name );

        ///  @brief Get the Attr Str object
        ///  
        ///  @param name 
        ///  @return wxString 
        wxString GetAttrStr( wxString name );

        ///  @brief Get the Attr Str object
        ///  
        ///  @param type 
        ///  @return wxString 
        wxString GetAttrStr( AlbumAttrType type );

        ///  @brief Get the Attr Dbl object
        ///  
        ///  @param type 
        ///  @return double 
        double GetAttrDbl( AlbumAttrType type );

        ///  @brief Get the Attr Dbl object
        ///  
        ///  @param name 
        ///  @return double 
        double GetAttrDbl( wxString name );

        ///  @brief Get the Line Number object
        ///  
        ///  @return int 
        int GetLineNumber( ) { return m_lineNbr; };

        ///  @brief Get the Nbr Attr object
        ///  
        ///  @return int 
        int GetNbrAttr( ) { return m_attrArray.size( ); };

        ///  @brief Get the Nbr Children object
        ///  
        ///  @return int 
        int GetNbrChildren( );

        ///  @brief Get the Node Type object
        ///  
        ///  @return AlbumBaseType 
        AlbumBaseType GetNodeType( ) { return ( AlbumBaseType ) m_nodeType; };

        ///  @brief Get the Node Status object
        ///  
        ///  @return NodeStatus 
        NodeStatus GetNodeStatus( ) { return m_nodeValid; };

        ///  @brief Get the Object Name object
        ///  
        ///  @return wxString 
        wxString GetObjectName( ) { return m_objectName; };

        ///  @brief Get the Object Text object
        ///  
        ///  @return wxString 
        wxString GetObjectText( ) { return m_text; };

        ///  @brief Get the Text object
        ///  
        ///  @return wxString 
        wxString GetText( ) { return m_text; }

        ///  @brief 
        ///  
        ///  @param type 
        ///  @return true 
        ///  @return false 
        bool IsNodeType( AlbumBaseType type ) { return ( type == m_nodeType ); };

        ///  @brief 
        ///  
        ///  @param thisObject 
        ///  @return true 
        ///  @return false 
        bool LoadAttributes( wxXmlNode* thisObject );

        ///  @brief 
        ///  
        ///  @param xmlNode 
        virtual void Save( wxXmlNode* xmlNode ) = 0;

        ///  @brief Set the Attribute object
        ///  
        ///  @param xmlNode 
        ///  @param type 
        void SetAttribute( wxXmlNode* xmlNode, AlbumAttrType type );

        ///  @brief Set the Attr Str object
        ///  
        ///  @param name 
        ///  @param val 
        void SetAttrStr( wxString name, wxString val );

        ///  @brief Set the Attr Str object
        ///  
        ///  @param type 
        ///  @param val 
        void SetAttrStr( AlbumAttrType type, wxString val );

        ///  @brief Set the Attr Dbl object
        ///  
        ///  @param type 
        ///  @param val 
        void SetAttrDbl( AlbumAttrType type, double val );

        ///  @brief Set the Line Number object
        ///  
        ///  @param nbr 
        void SetLineNumber( int nbr ) { m_lineNbr = nbr; };

        ///  @brief Set the Object Name object
        ///  
        ///  @param name 
        void SetObjectName( wxString name ) { m_objectName = name; }

        ///  @brief Set the Object Text object
        ///  
        ///  @param text 
        void SetObjectText( wxString text ) { m_text = text; }

        ///  @brief Set the Node Type object
        ///  
        ///  @param type 
        void SetNodeType( AlbumBaseType type ) { m_nodeType = type; };

        ///  @brief 
        ///  
        ///  @return true 
        ///  @return false 
        bool IsStatusOK( ) { return ( m_nodeValid != AT_FATAL ); };

        ///  @brief Set the Node Status object
        ///  
        ///  @param status 
        void SetNodeStatus( NodeStatus status ) { m_nodeValid = status; };

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
