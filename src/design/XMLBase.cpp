/**
 * @file XMLBase.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright ( c ) 2022
 *
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "design/XMLBase.h"

#include "gui/AlbumTreeCtrl.h"

namespace Design {

    //--------------

    XMLBase::XMLBase( wxXmlNode* ele )
    {
        //        m_parent = parent;
        if ( ele )
        {
            wxString name = ele->GetName( );
            SetObjectName( name );
            m_lineNbr = ele->GetLineNumber( );

            //           std::cout << "XMLBase::XMLBase " << name << " line:" << m_lineNbr << "\n";
            LoadAttributes( ele );
            m_text = ele->GetNodeContent( );
        }
        else
        {
            m_lineNbr = 0;
            m_text = "";
        }
    };

    //--------------

    XMLBase::~XMLBase( )
    {
        for ( LayoutAttributeArray::iterator it = std::begin( m_attrArray ); it != std::end( m_attrArray ); ++it )
        {
            Attribute* child = ( Attribute* ) ( *it );
            child->~Attribute( );
        }
        wxTreeItemIdValue cookie;
    };
    //--------------

    void XMLBase::DeleteAttribute( wxString name )
    {
        for ( LayoutAttributeArray::iterator it = std::begin( m_attrArray );
            it != std::end( m_attrArray );
            ++it )
        {
            Attribute* attr = ( Attribute* ) ( *it );
            wxString attrName = attr->GetName( );
            if ( !attrName.Cmp( name ) )
            {
                m_attrArray.erase( it );
                return;
            }
        }
    }
    //--------------

    void XMLBase::DeleteAttribute( AlbumAttrType type )
    {
        DeleteAttribute( AttrNameStrings[ type ] );
    }
    //--------------


    Attribute* XMLBase::FindAttr( wxString name )
    {
        LayoutAttributeArray::iterator it;
        it = m_attrArray.begin( );
        for ( it = m_attrArray.begin( );
            it != m_attrArray.end( );
            ++it )
        {
            Attribute* attr = ( Attribute* ) ( *it );
            wxString attrName = attr->GetName( );
            if ( !attrName.Cmp( name ) )
            {
                return attr;
            }
        }
        return ( Attribute* ) 0;
    };

    //--------------

    wxString XMLBase::GetAttrStr( wxString name )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            return attr->GetValue( );
        }
        return wxT( "" );
    }

    //--------------

    wxString XMLBase::GetAttrStr( AlbumAttrType type )
    {
        return GetAttrStr( AttrNameStrings[ type ] );
    }

    //--------------

    double XMLBase::GetAttrDbl( wxString name, double defVal )
    {
        return String2Dbl( GetAttrStr( name ), defVal );
    }

    //--------------

    bool XMLBase::GetAttrBool( wxString name, bool defVal )
    {
        return String2Bool( GetAttrStr( name ), defVal );
    }
    //--------------

    bool XMLBase::GetAttrBool( AlbumAttrType type, bool defVal )
    {
        return GetAttrBool( AttrNameStrings[ type ], defVal );
    }

    //--------------

    double XMLBase::GetAttrDbl( AlbumAttrType type, double defVal )
    {
        return GetAttrDbl( AttrNameStrings[ type ], defVal );
    }

    //--------------
    // Procedure::Load
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

    //--------------

    void XMLBase::SetAttrDbl( AlbumAttrType type, double val )
    {
        SetAttrStr( AttrNameStrings[ type ], Dbl2String( val ) );
    }

    //--------------

    bool XMLBase::LoadAttributes( wxXmlNode* thisObject )
    {
        const wxXmlAttribute* attr = thisObject->GetAttributes( );
        //std::cout << "    XMLBase::LoadAttributes  ";
        while ( attr )
        {
            //const char* name = attr->GetName( );
            wxString name( attr->GetName( ) );
            wxString val( attr->GetValue( ) );
            val = val.Trim( ).Trim( false );
            AlbumAttrType type = FindAlbumAttrType( wxString( name ) );
            if ( type == AT_PageWidth
                || type == AT_PageHeight
                || type == AT_TopPageMargin
                || type == AT_BottomPageMargin
                || type == AT_RightPageMargin
                || type == AT_LeftPageMargin
                || type == AT_BorderSize
                || type == AT_Height
                || type == AT_Width
                || type == AT_XPos
                || type == AT_YPos
                || type == AT_MinHeight
                || type == AT_MinWidth
                || type == AT_TopContentMargin
                || type == AT_BottomContentMargin
                || type == AT_LeftContentMargin
                || type == AT_RightContentMargin
                || type == AT_FixedSpacingSize
                || type == AT_PaperHeight
                || type == AT_PaperWidth
                || type == AT_SelvageHeight
                || type == AT_SelvageWidth
                || type == AT_MountAllowanceHeight
                || type == AT_MountAllowanceWidth
                || type == AT_StampMargin )
            {
                val = Dbl2String( String2Dbl( val ) );
                //  val = str.c_str( );
            }


            // std::cout << "       " << name << ":" << val << "\n";
            Attribute* attribute = new Attribute( name, val );
            m_attrArray.push_back( attribute );
            attr = attr->GetNext( );
        }
        std::cout;
        return true;
    }

    //--------------

    void XMLBase::SetAttribute( wxXmlNode* xmlNode, AlbumAttrType type )
    {
        Utils::SetAttrStr( xmlNode, AttrNameStrings[ type ], GetAttrStr( type ) );
    };

    //--------------

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
    //--------------

    void XMLBase::SetAttrBool( wxString name, bool val )
    {
        Attribute* attr = FindAttr( name );
        if ( attr )
        {
            attr->SetValue( Bool2String( val ) );
        }
        else
        {
            attr = new Attribute( name, Bool2String( val ) );
            m_attrArray.push_back( attr );
        }
    }

    void XMLBase::SetAttrBool( AlbumAttrType type, bool val )
    {
        SetAttrBool( AttrNameStrings[ type ], val );
    }
    //--------------

    void XMLBase::SetAttrStr( AlbumAttrType type, wxString val )
    {
        SetAttrStr( AttrNameStrings[ type ], val );
    }



}