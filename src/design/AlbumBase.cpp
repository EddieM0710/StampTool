/**
 * @file AlbumBase.cpp
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

#include "design/AlbumBase.h"

#include "design/TitlePage.h"
#include "design/Page.h"
#include "design/Title.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"

namespace Design {

    AlbumBase::AlbumBase( AlbumBase* parent, wxXmlNode* ele )
    {
        m_parent = parent;
        if ( ele )
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

    Attribute* AlbumBase::FindAttr( wxString name )
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

    bool AlbumBase::LoadAttributes( wxXmlNode* thisObject )
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

    wxString AlbumBase::GetAttrStr( wxString name )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            return attr->GetValue( );
        }
        return wxString( "" );
    }


    wxString AlbumBase::GetAttrStr( AlbumAttrType type )
    {
        return GetAttrStr( AttrNameStrings[ type ] );
    }

    double AlbumBase::GetAttrDbl( wxString name )
    {
        double val;
        wxString str = GetAttrStr( name );

        if ( str.ToDouble( &val ) )
        {
            return val;
        }
        return 0.0;
    }

    double AlbumBase::GetAttrDbl( AlbumAttrType type )
    {
        return GetAttrDbl( AttrNameStrings[ type ] );
    }

    double AlbumBase::SetAttrDbl( AlbumAttrType type, double val )
    {
        wxString str = wxString::Format( "%f", val );
        SetAttrStr( AttrNameStrings[ type ], str );
    }

    void AlbumBase::SetAttrStr( wxString name, wxString val )
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

    void AlbumBase::SetAttrStr( AlbumAttrType type, wxString val )
    {
        SetAttrStr( AttrNameStrings[ type ], val );
    }

    AlbumBase* AlbumBase::FindFirstChild( wxString name )
    {

        for ( int i = 0; i < GetNbrChildren( ); i++ )
        {
            wxString childType = ChildItem( i )->GetObjectName( );
            if ( !childType.Cmp( name ) )
            {
                return ChildItem( i );
            }
        }
        return ( AlbumBase* )0;
    }

    //!*********************************************************
    // Procedure::Load
    // *********************************************************

    bool AlbumBase::Load( wxXmlNode* thisObject )
    {
        wxString name = thisObject->GetName( );
        SetObjectName( name );
        m_nodeType = FindAlbumBaseType( name );
        m_lineNbr = thisObject->GetLineNumber( );
        LoadAttributes( thisObject );
        m_text = thisObject->GetNodeContent( );
        LoadChildren( thisObject );
        return true;
    }


    bool AlbumBase::LoadChildren( wxXmlNode* thisObject )
    {
        wxXmlNode* child = thisObject->GetChildren( );
        wxString name;
        while ( child )
        {
            wxString objectType = child->GetName( );
            // if ( objectType == "TitlePage" )
            // {
            //     //                std::cout << "TitlePage" << "\n";
            //     TitlePage* object = new TitlePage( this, child );
            //     m_layoutChildArray.push_back( object );
            //     //                object->Load( child );
            // }
            // else 
            if ( objectType == "Page" )
            {
                //                std::cout << "Page" << "\n";
                Page* object = new Page( this, child );
                m_layoutChildArray.push_back( object );
                //                object->Load( child );
            }
            // else if ( objectType == "Title" )
            // {
            //     //                std::cout << "Title" << "\n";
            //     Title* object = new Title( this, child );
            //     m_layoutChildArray.push_back( object );
            //     //                object->Load( child );
            // }
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


    AlbumBase* AlbumBase::FindChild( wxString name )
    {
        for ( int i = 0; i < GetNbrChildren( ); i++ )
        {
            wxString childType = ChildItem( i )->GetObjectName( );
            if ( !childType.Cmp( name ) )
            {
                return ChildItem( i );
            }
        }
        return ( AlbumBase* )0;
    }

    void AlbumBase::DeleteChild( AlbumBase* node )
    {
        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            AlbumBase* child = ( AlbumBase* )( *it );
            if ( child == node )
            {
                m_layoutChildArray.erase( it );
                node->~AlbumBase( );
            }
        }
    }

    AlbumBase::~AlbumBase( )
    {
        for ( LayoutAttributeArray::iterator it = std::begin( m_attrArray ); it != std::end( m_attrArray ); ++it )
        {
            Attribute* child = ( Attribute* )( *it );
            child->~Attribute( );
        }
        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            AlbumBase* child = ( AlbumBase* )( *it );
            child->~AlbumBase( );
            m_layoutChildArray.erase( it );
        }
    };

    void AlbumBase::AddChild( AlbumBase* node )
    {
        m_layoutChildArray.push_back( node );
    }

    NodeStatus AlbumBase::ValidateChildren( AlbumBase* node )
    {
        if ( !node->IsStatusOK( ) )
        {
            return AT_FATAL;
        }
        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            AlbumBase* child = ( AlbumBase* )( *it );
            if ( ValidateChildren( child ) == AT_FATAL )
            {
                return AT_FATAL;
            }
        }
        return AT_OK;
    }
}