/**
 * @file layout/AlbumNode.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef AlbumNode_h
#define AlbumNode_h

#include <wx/string.h>
#include <vector>


#include "Defs.h"
//#include "Node.h"
#include "album/AlbumDefs.h"
#include "album/Attribute.h"

#include <wx/xml/xml.h>
#include <wx/treectrl.h>


namespace Layout {

class AlbumNode;

typedef std::vector<AlbumNode*> AlbumNodeList;

    /**
     * @brief Base class for all layout objects. The layout objects are
     * initialy loaded from the layout XML.
     *
     **************************************************/
    class AlbumNode
    {
    public:
        /**
         * @brief Unused; Construct a new Album Layout Object object
         *
         **************************************************/
        AlbumNode( ) {  };

        ~AlbumNode( );

        /**
         * @brief Construct a new Album Layout Object
         *
         * @param name
         **************************************************/
        AlbumNode( AlbumNode* parent, wxXmlNode* ele ) ;


        void SetNodeType( AlbumNodeType type ) { m_nodeType = type; };
        AlbumNodeType GetNodeType( ) { return (AlbumNodeType)m_nodeType; };

        int GetLineNumber(){return m_lineNbr;};
        void SetLineNumber( int nbr){m_lineNbr = nbr;};


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


        int GetNbrChildren( ) {
            int count = m_layoutChildArray.size( );
            return count;
        };

        AlbumNode* FindFirstChild( wxString name );
        AlbumNode* ChildItem( int ndx ) { return m_layoutChildArray.at( ndx ); };
        AlbumNode* FindChild( wxString name );

        void SetObjectName( wxString name ) { m_objectName = name; }
        wxString GetObjectName( ) { return m_objectName; }

        void SetObjectText( wxString text ) { m_text = text; }
        wxString GetObjectText( ) { return m_text; }
    
        AlbumNodeList::iterator BeginAlbumNodeList(){return  std::begin( m_layoutChildArray );};
        AlbumNodeList::iterator EndAlbumNodeList(){return  std::end( m_layoutChildArray );};

        virtual wxXmlNode* Write( wxXmlNode* parent ) = 0;

        void DeleteChild( AlbumNode* node );
        void AddChild( AlbumNode* node );

        AlbumNode* GetParent(){return m_parent;};
        void SetParent(AlbumNode* parent){m_parent = parent;};

        wxTreeItemId GetTreeItemId(){return m_treeID;};
        void SetTreeItemId(wxTreeItemId id){m_treeID = id;};


        virtual AlbumNodeStatus ValidateNode() = 0;
        bool HasChildren(){ return !m_layoutChildArray.empty(); };

    private:

        bool LoadChildren( wxXmlNode* parent );

        bool Load( wxXmlNode* thisObject );
        wxString m_objectName;
        int m_nodeType;
        int m_lineNbr;
        AlbumNode* m_parent;
        wxTreeItemId m_treeID;
        protected:
        AlbumNodeList m_layoutChildArray;
        LayoutAttributeArray m_attrArray;
        wxString m_text;
   };
}
#endif
