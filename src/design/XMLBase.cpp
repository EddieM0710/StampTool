/**
 * @file XMLBase.cpp
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
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "design/XMLBase.h"

#include "gui/DesignTreeCtrl.h"

namespace Design {

    XMLBase::XMLBase( wxXmlNode* ele )
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

    Attribute* XMLBase::FindAttr( wxString name )
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

    bool XMLBase::LoadAttributes( wxXmlNode* thisObject )
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

    wxString XMLBase::GetAttrStr( wxString name )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            return attr->GetValue( );
        }
        return wxString( "" );
    }


    wxString XMLBase::GetAttrStr( AlbumAttrType type )
    {
        return GetAttrStr( AttrNameStrings[ type ] );
    }

    double XMLBase::GetAttrDbl( wxString name )
    {
        double val;
        wxString str = GetAttrStr( name );

        if ( str.ToDouble( &val ) )
        {
            return val;
        }
        return 0.0;
    }

    double XMLBase::GetAttrDbl( AlbumAttrType type )
    {
        return GetAttrDbl( AttrNameStrings[ type ] );
    }

    double XMLBase::SetAttrDbl( AlbumAttrType type, double val )
    {
        wxString str = wxString::Format( "%f", val );
        SetAttrStr( AttrNameStrings[ type ], str );
    }

    void XMLBase::SetAttrStr( wxString name, wxString val )
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

    void XMLBase::SetAttrStr( AlbumAttrType type, wxString val )
    {
        SetAttrStr( AttrNameStrings[ type ], val );
    }

    // XMLBase* XMLBase::FindFirstChild( wxString name )
    // {

    //     for ( int i = 0; i < GetNbrChildren( ); i++ )
    //     {
    //         wxString childType = ChildItem( i )->GetObjectName( );
    //         if ( !childType.Cmp( name ) )
    //         {
    //             return ChildItem( i );
    //         }
    //     }
    //     return ( XMLBase* )0;
    // }

    //!*********************************************************
    // Procedure::Load
    // *********************************************************

    bool XMLBase::Load( wxXmlNode* thisObject )
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


    XMLBase::~XMLBase( )
    {
        for ( LayoutAttributeArray::iterator it = std::begin( m_attrArray ); it != std::end( m_attrArray ); ++it )
        {
            Attribute* child = ( Attribute* )( *it );
            child->~Attribute( );
        }
        wxTreeItemIdValue cookie;
       };

}