/**
 * @file layout/AlbumBase.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
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

#ifndef AlbumBase_h
#define AlbumBase_h

#include <wx/string.h>
#include <vector>


#include "Defs.h"
#include "design/DesignDefs.h"
#include "design/Attribute.h"
#include <wx/treectrl.h>
#include <wx/xml/xml.h>
#include "utils/XMLUtilities.h"


namespace Design {

class AlbumBase;

//typedef std::vector<AlbumBase*> ChildList;

    /**
     * @brief Base class for all layout objects. The layout objects are
     * initialy loaded from the layout XML.
     *
     **************************************************/
    class AlbumBase
    {
    public:
        /**
         * @brief Unused; Construct a new Album Design Object object
         *
         **************************************************/
        AlbumBase( ) {  };

        ~AlbumBase( );

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         **************************************************/
        AlbumBase( wxXmlNode* ele ) ;

        void SetNodeType( AlbumBaseType type ) { m_nodeType = type; };
        AlbumBaseType GetNodeType( ) { return (AlbumBaseType)m_nodeType; };

        int GetLineNumber(){return m_lineNbr;};
        void SetLineNumber( int nbr){m_lineNbr = nbr; };

        Attribute* FindAttr( wxString name );
        bool LoadAttributes( wxXmlNode* thisObject );

        wxString GetAttrStr( wxString name );
        wxString GetAttrStr( AlbumAttrType type );  

        double GetAttrDbl( AlbumAttrType type );  
        double GetAttrDbl( wxString name );

        void SetAttrStr( wxString name, wxString val );
        void SetAttrStr( AlbumAttrType type, wxString val );
        double SetAttrDbl( AlbumAttrType type, double val) ; 
        
        int GetNbrAttr( ) { return m_attrArray.size( ); };
        Attribute* AttributeItem( int ndx ) { return m_attrArray.at( ndx ); };


        int GetNbrChildren( );

        void SetObjectName( wxString name ) { m_objectName = name; }
        wxString GetObjectName( ) { return m_objectName; }

        void SetObjectText( wxString text ) { m_text = text; }
        wxString GetObjectText( ) { return m_text; }
    
        virtual wxXmlNode* Write( wxXmlNode* parent ) = 0;

        void DeleteChild( AlbumBase* node );

        AlbumBase* GetParent();
       bool HasChildren();

        wxTreeItemId GetTreeItemId(){return m_treeID;};
        void SetTreeItemId(wxTreeItemId id){m_treeID = id;};


        virtual NodeStatus ValidateNode() = 0;
 

        NodeStatus ValidateChildren( AlbumBase* node );
        NodeStatus GetNodeStatus(){ return m_nodeValid;};
        bool IsStatusOK(){ return ( m_nodeValid != AT_FATAL);};
        void SetNodeStatus( NodeStatus status ){  m_nodeValid = status;};
        void SetAttribute( wxXmlNode* xmlNode, AlbumAttrType type )
            { Utils::SetAttrStr( xmlNode, AttrNameStrings[type], GetAttrStr( type ) );};

        virtual void Save( wxXmlNode* xmlNode) = 0;



    private:

        bool LoadChildren( wxXmlNode* parent );

        bool Load( wxXmlNode* thisObject );

        wxString m_objectName;
        int m_nodeType;
        int m_lineNbr;
        wxTreeItemId m_treeID;

        protected:
        LayoutAttributeArray m_attrArray;
        wxString m_text;
        NodeStatus m_nodeValid;
   };
}
#endif
