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
#include "gui/DesignTreeCtrl.h"

namespace Design {

    AlbumBase::AlbumBase( wxXmlNode* ele )
    {
//        m_parent = parent;
        if ( ele )
        {
            wxString name = ele->GetName( );
            SetObjectName( name );
            m_lineNbr = ele->GetLineNumber( );
            LoadAttributes( ele );
            m_text = ele->GetNodeContent( );
//            LoadChildren( ele );
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
            Attribute* attr = m_attrArray.at( i );
            wxString attrName = attr->GetName( );
            if ( !attrName.Cmp( name ) )
            {
                return attr;
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

    // AlbumBase* AlbumBase::FindFirstChild( wxString name )
    // {

    //     for ( int i = 0; i < GetNbrChildren( ); i++ )
    //     {
    //         wxString childType = ChildItem( i )->GetObjectName( );
    //         if ( !childType.Cmp( name ) )
    //         {
    //             return ChildItem( i );
    //         }
    //     }
    //     return ( AlbumBase* )0;
    // }

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
//        LoadChildren( thisObject );
        return true;
    }


    AlbumBase::~AlbumBase( )
    {
        for ( LayoutAttributeArray::iterator it = std::begin( m_attrArray ); it != std::end( m_attrArray ); ++it )
        {
            Attribute* child = ( Attribute* )( *it );
            child->~Attribute( );
        }
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);        while ( childID.IsOk() )
        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            AlbumBase* child = ( AlbumBase* )GetDesignTreeCtrl()->GetItemNode( childID );

            child->~AlbumBase( );
//            m_layoutChildArray.erase( it );
            childID = GetDesignTreeCtrl()->GetNextChild(childID, cookie);
        }
    };

    NodeStatus AlbumBase::ValidateChildren( AlbumBase* node )
    {
        if ( !node->IsStatusOK( ) )
        {
            return AT_FATAL;
        }
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId();
        wxTreeItemId childID = GetDesignTreeCtrl()->GetFirstChild(parentID, cookie);        {
            AlbumBaseType type = ( AlbumBaseType )GetDesignTreeCtrl()->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* )GetDesignTreeCtrl()->GetItemNode( childID );
            if ( ValidateChildren( (AlbumBase*)child ) == AT_FATAL )
            {
                return AT_FATAL;
            }

            childID = GetDesignTreeCtrl()->GetNextChild(childID, cookie);
        }
        return AT_OK;
    }


    int  AlbumBase::GetNbrChildren( ) {            
        if( m_treeID.IsOk() )
        {
            return GetDesignTreeCtrl()->GetChildrenCount(m_treeID, false);;
        }
        return -1;
    };

    AlbumBase* AlbumBase::GetParent()
    {
        if( m_treeID.IsOk() )
        {
            wxTreeItemId parentID = GetDesignTreeCtrl()->GetItemParent(m_treeID);
            if( parentID.IsOk() )
            {
                return GetDesignTreeCtrl()->GetItemNode(parentID);
            }
        }
        return (AlbumBase*)0;
    };       
      
    bool AlbumBase::HasChildren()
    { 
        if( m_treeID.IsOk() )
        {
            return GetDesignTreeCtrl()->HasChildren(m_treeID);
        }
        return false;
    };
}