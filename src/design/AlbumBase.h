/**
 * @file layout/AlbumBase.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef AlbumBase_h
#define AlbumBase_h

#include <wx/string.h>
#include <vector>


#include "Defs.h"
#include "design/DesignDefs.h"
#include "design/Attribute.h"

#include <wx/xml/xml.h>
#include <wx/treectrl.h>


namespace Design {

class AlbumBase;

typedef std::vector<AlbumBase*> AlbumBaseList;

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
        AlbumBase( AlbumBase* parent, wxXmlNode* ele ) ;


        void SetNodeType( AlbumBaseType type ) { m_nodeType = type; };
        AlbumBaseType GetNodeType( ) { return (AlbumBaseType)m_nodeType; };

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

        AlbumBase* FindFirstChild( wxString name );
        AlbumBase* ChildItem( int ndx ) { return m_layoutChildArray.at( ndx ); };
        AlbumBase* FindChild( wxString name );

        void SetObjectName( wxString name ) { m_objectName = name; }
        wxString GetObjectName( ) { return m_objectName; }

        void SetObjectText( wxString text ) { m_text = text; }
        wxString GetObjectText( ) { return m_text; }
    
        AlbumBaseList::iterator BeginAlbumBaseList(){return  std::begin( m_layoutChildArray );};
        AlbumBaseList::iterator EndAlbumBaseList(){return  std::end( m_layoutChildArray );};

        virtual wxXmlNode* Write( wxXmlNode* parent ) = 0;

        void DeleteChild( AlbumBase* node );
        void AddChild( AlbumBase* node );

        AlbumBase* GetParent(){return m_parent;};
        void SetParent(AlbumBase* parent){m_parent = parent;};

        wxTreeItemId GetTreeItemId(){return m_treeID;};
        void SetTreeItemId(wxTreeItemId id){m_treeID = id;};


        virtual NodeStatus ValidateNode() = 0;
        bool HasChildren(){ return !m_layoutChildArray.empty(); };

        NodeStatus ValidateChildren( AlbumBase* node );
        NodeStatus GetNodeStatus(){ return m_nodeValid;};
        bool IsStatusOK(){ return ( m_nodeValid != AT_FATAL);};
        void SetNodeStatus( NodeStatus status ){  m_nodeValid = status;};
        
    private:

        bool LoadChildren( wxXmlNode* parent );

        bool Load( wxXmlNode* thisObject );
        wxString m_objectName;
        int m_nodeType;
        int m_lineNbr;
        AlbumBase* m_parent;
        wxTreeItemId m_treeID;
        protected:
        AlbumBaseList m_layoutChildArray;
        LayoutAttributeArray m_attrArray;
        wxString m_text;
        NodeStatus m_nodeValid;
   };
}
#endif
