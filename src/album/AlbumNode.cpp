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

#include "AlbumNode.h"

#include <wx/arrimpl.cpp>

 //#include "Properties.h"
#include "album/TitlePage.h"
#include "album/Page.h"
#include "album/Title.h"
#include "album/Row.h"
#include "album/Column.h"
#include "album/Stamp.h"

namespace Layout {

    //WX_DEFINE_OBJARRAY( NodeAttributeArray );
    //WX_DEFINE_OBJARRAY( NodeChildArray );

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

    wxString AlbumNode::GetAttrVal( wxString name )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            return attr->GetValue( );
        }
        return wxString( "" );
    }

    double AlbumNode::GetAttrValDbl( wxString name )
    {
        double val;
        wxString str = GetAttrVal( name );

        if ( str.ToDouble( &val ) )
        {
            return val;
        }
        return 0.0;
    }

    AlbumNode* AlbumNode::FindFirstChild( wxString name )
    {

        for ( int i = 0; i < ObjectArrayCount( ); i++ )
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
        SetObjectName( thisObject->GetName( ) );
        m_lineNbr = thisObject->GetLineNumber( );
        LoadAttributes( thisObject );
        m_text = thisObject->GetNodeContent( );
        LoadChildren( thisObject );
        return true;
    }

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

    bool AlbumNode::LoadChildren( wxXmlNode* thisObject )
    {
        wxXmlNode* child = thisObject->GetChildren( );
        wxString name;
        while ( child )
        {
            wxString objectType = child->GetName( );
            if ( objectType == "TitlePage" )
            {
                TitlePage* object = new TitlePage( this );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Page" )
            {
                Page* object = new Page( this );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Title" )
            {
                Title* object = new Title( this );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Column" )
            {
                Column* object = new Column( this );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Row" )
            {
                Row* object = new Row( this );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Stamp" )
            {
                Stamp* object = new Stamp( this );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            child = ( wxXmlNode* )child->GetNext( );
        }
    }
    AlbumNode* AlbumNode::FindChild( wxString name )
    {
        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            wxString childType = ChildItem( i )->GetObjectName( );
            if ( !childType.Cmp( name ) )
            {
                return ChildItem( i );
            }
        }
        return ( AlbumNode* )0;
    }
}