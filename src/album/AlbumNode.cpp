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


 //#include "Properties.h"
#include "album/TitlePage.h"
#include "album/Page.h"
#include "album/Title.h"
#include "album/Row.h"
#include "album/Column.h"
#include "album/Stamp.h"

namespace Layout {

    // // //WX_DEFINE_OBJARRAY( NodeAttributeArray );
    // // //WX_DEFINE_OBJARRAY( NodeChildArray );

    // // Attribute* AlbumNode::FindAttr( wxString name )
    // // {
    // //     int cnt = m_attrArray.size( );
    // //     for ( int i = 0; i < cnt; i++ )
    // //     {
    // //         wxString attrName = m_attrArray.at( i )->GetName( );
    // //         if ( !attrName.Cmp( name ) )
    // //         {
    // //             return m_attrArray.at( i );
    // //         }
    // //     }
    // //     return ( Attribute* )0;
    // // };


    // wxString AlbumNode::GetAttrStr( AlbumAttrType type )
    // {
    //     return GetAttrStr( AttrNameStrings[ type ] );
    // }

    // double AlbumNode::GetAttrDbl( AlbumAttrType type )
    // {
    //     return Node::GetAttrDbl(  AttrNameStrings[ type ] );
    // }

    // void AlbumNode::SetNodeAttrStr( AlbumAttrType type, wxString val )
    // { 
    //     Node::SetNodeAttrStr( AttrNameStrings[ type ], val );
    // }

    // double AlbumNode::SetAttrDbl( AlbumAttrType type, double val)
    // {
    //     Node::SetAttrDbl( AttrNameStrings[ type ], val );
    // }

    // // double AlbumNode::GetAttrValDbl( wxString name )
    // // {
    // //     double val;
    // //     wxString str = GetAttrVal( name );

    // //     if ( str.ToDouble( &val ) )
    // //     {
    // //         return val;
    // //     }
    // //     return 0.0;
    // // }

    // // AlbumNode* AlbumNode::FindFirstChild( wxString name )
    // // {

    // //     for ( int i = 0; i < ObjectArrayCount( ); i++ )
    // //     {
    // //         wxString childType = ChildItem( i )->GetObjectName( );
    // //         if ( !childType.Cmp( name ) )
    // //         {
    // //             return ChildItem( i );
    // //         }
    // //     }
    // //     return ( AlbumNode* )0;
    // // }

    // //!*********************************************************
    // // Procedure::Load
    // // *********************************************************

    // bool AlbumNode::Load( wxXmlNode* thisObject )
    // {
    //     LoadChildren( thisObject );
    //     return true;
    // }

    // bool AlbumNode::LoadAttributes( wxXmlNode* thisObject )
    // {

    //     const wxXmlAttribute* attr = thisObject->GetAttributes( );
    //     while ( attr )
    //     {
    //         const char* name = attr->GetName( );
    //         const char* val = attr->GetValue( );
    //         Attribute* attribute = new Attribute( name, val );
    //         m_attrArray.push_back( attribute );
    //         attr = attr->GetNext( );
    //     }
    // }

    // bool AlbumNode::LoadChildren( wxXmlNode* thisObject )
    // {
    //     wxXmlNode* child = thisObject->GetChildren( );
    //     wxString name;
    //     while ( child )
    //     {
    //         wxString objectType = child->GetName( );
    //         if ( objectType == "TitlePage" )
    //         {
    //             TitlePage* object = new TitlePage( child );
    //             m_albumChilden.push_back( object );
    //             object->Load( child );
    //         }
    //         else if ( objectType == "Page" )
    //         {
    //             Page* object = new Page( child );
    //             m_albumChilden.push_back( object );
    //             object->Load( child );
    //         }
    //         else if ( objectType == "Title" )
    //         {
    //             Title* object = new Title( child );
    //             m_albumChilden.push_back( object );
    //             object->Load( child );
    //         }
    //         else if ( objectType == "Column" )
    //         {
    //             Column* object = new Column( child );
    //             m_albumChilden.push_back( object );
    //             object->Load( child );
    //         }
    //         else if ( objectType == "Row" )
    //         {
    //             Row* object = new Row( child );
    //             m_albumChilden.push_back( object );
    //             object->Load( child );
    //         }
    //         else if ( objectType == "Stamp" )
    //         {
    //             Stamp* object = new Stamp( child );
    //             m_albumChilden.push_back( object );
    //             object->Load( child );
    //         }
    //         child = ( wxXmlNode* )child->GetNext( );
    //     }
    // }
    // // AlbumNode* AlbumNode::FindChild( wxString name )
    // // {
    // //     for ( int i = 0; i < ObjectArrayCount( ); i++ )
    // //     {
    // //         wxString childType = ChildItem( i )->GetObjectName( );
    // //         if ( !childType.Cmp( name ) )
    // //         {
    // //             return ChildItem( i );
    // //         }
    // //     }
    // //     return ( AlbumNode* )0;
    // // }
        AlbumNode::AlbumNode( wxXmlNode* ele ) 
        {
            wxString name = ele->GetName( );
            SetObjectName( name );
            m_lineNbr = ele->GetLineNumber( );
            LoadAttributes( ele );
            m_text = ele->GetNodeContent( );
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

    wxString AlbumNode::GetAttrStr( wxString name )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            return attr->GetValue( );
        }
        return wxString( "" );
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
                TitlePage* object = new TitlePage( child );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Page" )
            {
                Page* object = new Page( child );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Title" )
            {
                Title* object = new Title( child );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Column" )
            {
                Column* object = new Column( child );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Row" )
            {
                Row* object = new Row( child );
                m_layoutChildArray.push_back( object );
                object->Load( child );
            }
            else if ( objectType == "Stamp" )
            {
                Stamp* object = new Stamp( child );
                m_layoutChildArray.push_back( object );
                object->Load( child );
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

}