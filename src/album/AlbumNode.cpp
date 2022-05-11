/**
 * @file AlbumNode.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "album/AlbumNode.h"

#include "album/TitlePage.h"
#include "album/Page.h"
#include "album/Title.h"
#include "album/Row.h"
#include "album/Column.h"
#include "album/Stamp.h"

namespace Layout {

    AlbumNode::AlbumNode(AlbumNode* parent, wxXmlNode* ele )
    {
        m_parent = parent;
        if( ele )
        {
            wxString name = ele->GetName( );
            SetObjectName( name );
            m_lineNbr = ele->GetLineNumber( );
            LoadAttributes( ele );
            m_text = ele->GetNodeContent( );
            LoadChildren( ele );
        }
        else
        {
            m_lineNbr = 0;
            m_text = "";
        }
    };

    Attribute* AlbumNode::FindAttr( wxString name )
    {
        int cnt = m_attrArray.size( );
        for ( int i = 0; i < cnt; i++ )
        {
            wxString attrName = m_attrArray.at( i )->GetName( );
            if ( !attrName.Cmp( name ) )
            {
                return m_attrArray.at( i );
            }
        }
        return ( Attribute* )0;
    };

    bool AlbumNode::LoadAttributes( wxXmlNode* thisObject )
    {

        const wxXmlAttribute* attr = thisObject->GetAttributes( );
        while ( attr )
        {
            const char* name = attr->GetName( );
            const char* val = attr->GetValue( );
            Attribute* attribute = new Attribute( name, val );
            m_attrArray.push_back( attribute );
            attr = attr->GetNext( );
        }
    }

    wxString AlbumNode::GetAttrStr( wxString name )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            return attr->GetValue( );
        }
        return wxString( "" );
    }


    wxString AlbumNode::GetAttrStr( AlbumAttrType type )
    {
        return GetAttrStr( AttrNameStrings[ type ] );
    }

    double AlbumNode::GetAttrDbl( wxString name )
    {
        double val;
        wxString str = GetAttrStr( name );

        if ( str.ToDouble( &val ) )
        {
            return val;
        }
        return 0.0;
    }

    double AlbumNode::GetAttrDbl( AlbumAttrType type )
    {
        return GetAttrDbl( AttrNameStrings[ type ] );
    }

    double AlbumNode::SetAttrDbl( AlbumAttrType type, double val )
    {
        wxString str = wxString::Format( "%f", val );
        SetAttrStr( AttrNameStrings[ type ], str );
    }

    void AlbumNode::SetAttrStr( wxString name, wxString val )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            attr->SetValue( val );
        }
        else
        {
            attr = new Attribute( name, val );
            m_attrArray.push_back( attr );
        }
    }

    void AlbumNode::SetAttrStr( AlbumAttrType type, wxString val )
    {
        SetAttrStr( AttrNameStrings[ type ], val );
    }

    AlbumNode* AlbumNode::FindFirstChild( wxString name )
    {

        for ( int i = 0; i < GetNbrChildren( ); i++ )
        {
            wxString childType = ChildItem( i )->GetObjectName( );
            if ( !childType.Cmp( name ) )
            {
                return ChildItem( i );
            }
        }
        return ( AlbumNode* )0;
    }

    //!*********************************************************
    // Procedure::Load
    // *********************************************************

    bool AlbumNode::Load( wxXmlNode* thisObject )
    {
        wxString name = thisObject->GetName( );
        SetObjectName( name );
        m_nodeType = FindAlbumNodeType( name );
        m_lineNbr = thisObject->GetLineNumber( );
        LoadAttributes( thisObject );
        m_text = thisObject->GetNodeContent( );
        LoadChildren( thisObject );
        return true;
    }


    bool AlbumNode::LoadChildren( wxXmlNode* thisObject )
    {
        wxXmlNode* child = thisObject->GetChildren( );
        wxString name;
        while ( child )
        {
            wxString objectType = child->GetName( );
            if ( objectType == "TitlePage" )
            {
//                std::cout << "TitlePage" << "\n";
                TitlePage* object = new TitlePage( this, child );
                m_layoutChildArray.push_back( object );
//                object->Load( child );
            }
            else if ( objectType == "Page" )
            {
//                std::cout << "Page" << "\n";
                Page* object = new Page( this, child );
                m_layoutChildArray.push_back( object );
//                object->Load( child );
            }
            else if ( objectType == "Title" )
            {
//                std::cout << "Title" << "\n";
                Title* object = new Title( this, child );
                m_layoutChildArray.push_back( object );
//                object->Load( child );
            }
            else if ( objectType == "Column" )
            {
//                std::cout << "Column" << "\n";
                Column* object = new Column( this, child );
                m_layoutChildArray.push_back( object );
//                object->Load( child );
            }
            else if ( objectType == "Row" )
            {
//                std::cout << "Row" << "\n";
                Row* object = new Row( this, child );
                m_layoutChildArray.push_back( object );
//                object->Load( child );
            }
            else if ( objectType == "Stamp" )
            {
//                std::cout << "Stamp" << "\n";
                Stamp* object = new Stamp( this, child );
                m_layoutChildArray.push_back( object );
//                object->Load( child );
            }
            child = ( wxXmlNode* )child->GetNext( );
        }
    }


    AlbumNode* AlbumNode::FindChild( wxString name )
    {
        for ( int i = 0; i < GetNbrChildren( ); i++ )
        {
            wxString childType = ChildItem( i )->GetObjectName( );
            if ( !childType.Cmp( name ) )
            {
                return ChildItem( i );
            }
        }
        return ( AlbumNode* )0;
    }

    void AlbumNode::DeleteChild( AlbumNode* node )
    {
        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            AlbumNode* child = ( AlbumNode* )( *it );
            if ( child == node )
            {
                m_layoutChildArray.erase(it);
                node->~AlbumNode();
            }
        }
    }
    
    AlbumNode::~AlbumNode( )
     { 
        for ( LayoutAttributeArray::iterator it = std::begin(m_attrArray ); it != std::end( m_attrArray ); ++it )
        {
            Attribute* child = ( Attribute* )( *it );
            child->~Attribute();
        }
        for ( AlbumNodeList::iterator it = std::begin(m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            AlbumNode* child = ( AlbumNode* )( *it );
            child->~AlbumNode();
            m_layoutChildArray.erase(it);  
        }
    };
 
    void AlbumNode::AddChild( AlbumNode* node )
    {
        m_layoutChildArray.push_back(node);
    }

}