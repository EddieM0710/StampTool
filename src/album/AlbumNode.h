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

 //#include <wx/dynarray.h>
 //#include <wx/arrstr.h>
#include <wx/string.h>
#include <vector>

#include "Defs.h"
#include "album/Attribute.h"

#include <wx/xml/xml.h>
//using namespace tinyxml2;

namespace Layout {

    class AlbumNode;
    typedef std::vector<Attribute*> NodeAttributeArray;
    typedef std::vector<AlbumNode*> NodeChildArray;

    //WX_DECLARE_OBJARRAY( Attribute*, NodeAttributeArray );
    //WX_DECLARE_OBJARRAY( AlbumNode*, NodeChildArray );

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
        AlbumNode( ) { m_parent = 0; };

        /**
         * @brief Construct a new Album Layout Object
         *
         * @param name
         **************************************************/
        AlbumNode( AlbumNode* parent ) { m_parent = parent; };

        /**
         * @brief Set the Parent object
         *
         * @param parent
         **************************************************/
        void SetParent( AlbumNode* parent ) { m_parent = parent; };
        AlbumNode* GetParent( ) { return m_parent; };

        /**
         * @brief Find attribute with name.
         *
         * @param name
         * @return Attribute*
         **************************************************/
        Attribute* FindAttr( wxString name );

        /**
         * @brief Get the value of the attribute name
         *
         * @param name
         * @return wxString -  the value of the attribute
         ***************************************************/
        wxString GetAttrVal( wxString name );


        /**
         * @brief Get the numeric value of the attribute.
         *
         * @param name  attribute to convert
         * @return double - value or 0.0 if the conversion fails
         **************************************************/
        double GetAttrValDbl( wxString name );


        /**
         * @brief find the first child with name
         *
         * @param name
         * @return AlbumNode*
         **************************************************/
        AlbumNode* FindFirstChild( wxString name );


        /**
         * @brief Set the Object Name
         *
         * @param name
         **************************************************/
        void SetObjectName( wxString name ) { m_objectName = name; }

        /**
         * @brief Get the Object Name
         *
         * @return wxString
         **************************************************/
        wxString GetObjectName( ) { return m_objectName; }

        /**
         * @brief Set the Object Text
         *
         * @param text
         **************************************************/
        void SetObjectText( wxString text ) { m_text = text; }

        /**
         * @brief Get the Object Text
         *
         * @return wxString
         **************************************************/
        wxString GetObjectText( ) { return m_text; }

        /**
         * @brief Perform XML Load of this object.
         *
         * @param child
         * @return true
         * @return false
         **************************************************/
        bool Load( wxXmlNode* child );

        /**
         * @brief wrapper for child object array count
         *
         * @return int
         **************************************************/
        int ObjectArrayCount( ) {
            int count = m_layoutChildArray.size( );
            return count;
        };

        /**
         * @brief wrapper for attribute array count
         *
         * @return int
         **************************************************/
        int AttributeArrayCount( ) { return m_attrArray.size( ); };

        /**
         * @brief  Wrapper for child object array Item access. i.e., childArray.Item(ndx).
         *
         * @param ndx
         * @return AlbumNode*
         **************************************************/
        AlbumNode* ChildItem( int ndx ) { return m_layoutChildArray.at( ndx ); };

        // 
        /**
         * @brief Wrapper for attribute array Item access. i.e., attrArray.Item(ndx)
         *
         * @param ndx
         * @return Attribute*
         **************************************************/
        Attribute* AttributeItem( int ndx ) { return m_attrArray.at( ndx ); };

        // 
        /**
         * @brief find a child object with name name
         *
         * @param name
         * @return AlbumNode*
         **************************************************/
        AlbumNode* FindChild( wxString name );


        virtual wxXmlNode* Write( wxXmlNode* parent ) = 0;

        /**
         * @brief Get the Line Nbr
         *
         * @return int
         **************************************************/
        int GetLineNbr( ) { return m_lineNbr; };


    private:
        /**
         * @brief Perform XML load of this objects children
         *
         * @param parent
         * @return true
         * @return false
         **************************************************/
        bool LoadChildren( wxXmlNode* parent );

        /**
         * @brief  Perform XML load of this objects attributes
         *
         * @param thisObject
         * @return true
         * @return false
         **************************************************/
        bool LoadAttributes( wxXmlNode* thisObject );

    private:
        /**
         * @brief This objects parent object
         *
         **************************************************/
        AlbumNode* m_parent;
        /**
         * @brief The name of this object.
         *
         **************************************************/
        wxString m_objectName;
        /**
         * @brief The Array of this objects Attributes
         *
         **************************************************/
        NodeAttributeArray m_attrArray;
        /**
         * @brief The array of this objects child objects
         *
         **************************************************/
        NodeChildArray m_layoutChildArray;
        /**
         * @brief The text of this object.
         *
         **************************************************/
        wxString m_text;

        /**
         * @brief
         *
         **************************************************/
        int m_lineNbr;
    };
}
#endif
