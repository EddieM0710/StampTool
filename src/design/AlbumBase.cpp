/**
 * @file AlbumBase.cpp
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
 **************************************************/
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <iostream>

#include "design/DesignDefs.h"
#include "design/AlbumBase.h"

#include "design/TitlePage.h"
#include "design/Page.h"
#include "design/Title.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "utils/FontList.h"
#include "gui/DesignTreeCtrl.h"
#include "utils/Settings.h"

namespace Design {

    AlbumBase::~AlbumBase( )
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie );        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetDesignTreeCtrl( )->GetItemType( childID );
            AlbumBase* child = ( AlbumBase* ) GetDesignTreeCtrl( )->GetItemNode( childID );

            child->~AlbumBase( );
            childID = GetDesignTreeCtrl( )->GetNextChild( childID, cookie );
        }
    };

    NodeStatus AlbumBase::ValidateChildren( AlbumBase* node )
    {
        if ( !node->IsStatusOK( ) )
        {
            return AT_FATAL;
        }
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetDesignTreeCtrl( )->GetFirstChild( parentID, cookie ); {
            AlbumBaseType type = ( AlbumBaseType ) GetDesignTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetDesignTreeCtrl( )->GetItemNode( childID );
            if ( ValidateChildren( ( AlbumBase* ) child ) == AT_FATAL )
            {
                return AT_FATAL;
            }

            childID = GetDesignTreeCtrl( )->GetNextChild( childID, cookie );
        }
        return AT_OK;
    }


    int  AlbumBase::GetNbrChildren( ) {
        if ( m_treeID.IsOk( ) )
        {
            return GetDesignTreeCtrl( )->GetChildrenCount( m_treeID, false );;
        }
        return -1;
    };

    AlbumBase* AlbumBase::GetParent( )
    {
        if ( m_treeID.IsOk( ) )
        {
            wxTreeItemId parentID = GetDesignTreeCtrl( )->GetItemParent( m_treeID );
            if ( parentID.IsOk( ) )
            {
                return GetDesignTreeCtrl( )->GetItemNode( parentID );
            }
        }
        return ( AlbumBase* ) 0;
    };

    bool AlbumBase::HasChildren( )
    {
        if ( m_treeID.IsOk( ) )
        {
            return GetDesignTreeCtrl( )->HasChildren( m_treeID );
        }
        return false;
    };

    int AlbumBase::GetTitleFontNdx( ) { return m_titleFont.Get( ); };
    int AlbumBase::GetTextFontNdx( ) { return m_textFont.Get( ); };
    int AlbumBase::GetCatNbrFontNdx( ) { return m_catNbrFont.Get( ); };

    wxFont AlbumBase::GetTitleFont( )
    {
        if ( GetFontList( )->IsValidFontNdx( m_titleFont.Get( ) ) )
        {
            return GetFontList( )->GetFont( m_titleFont.Get( ) );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetFont( GetAlbum( )->GetAppPrefTitleFontNdx( ) );
        }
        else
        {
            return GetAlbum( )->GetTitleFont( );
        }

    }

    wxFont AlbumBase::GetTextFont( )
    {
        if ( GetFontList( )->IsValidFontNdx( m_textFont.Get( ) ) )
        {
            return GetFontList( )->GetFont( m_textFont.Get( ) );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetFont( GetAlbum( )->GetAppPrefTextFontNdx( ) );
        }
        else
        {
            return GetAlbum( )->GetTextFont( );
        }
    }

    wxFont AlbumBase::GetCatNbrFont( )
    {
        if ( GetFontList( )->IsValidFontNdx( m_catNbrFont.Get( ) ) )
        {
            return GetFontList( )->GetFont( m_catNbrFont.Get( ) );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetFont( GetAlbum( )->GetAppPrefCatNbrFontNdx( ) );
        }
        else
        {
            return GetAlbum( )->GetCatNbrFont( );
        }
    }

    wxColour AlbumBase::GetCatNbrColor( )
    {
        if ( GetFontList( )->IsValidFontNdx( m_catNbrFont.Get( ) ) )
        {
            return GetFontList( )->GetColor( m_catNbrFont.Get( ) );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetColor( GetAlbum( )->GetAppPrefCatNbrFontNdx( ) );
        }
        else
        {
            return GetAlbum( )->GetCatNbrColor( );
        }
    }

    wxColour AlbumBase::GetTextColor( )
    {
        if ( GetFontList( )->IsValidFontNdx( m_textFont.Get( ) ) )
        {
            return GetFontList( )->GetColor( m_textFont.Get( ) );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetColor( GetAlbum( )->GetAppPrefTextFontNdx( ) );
        }
        else
        {
            return GetAlbum( )->GetTextColor( );
        }
    }

    wxColour AlbumBase::GetTitleColor( )
    {
        if ( GetFontList( )->IsValidFontNdx( m_titleFont.Get( ) ) )
        {
            return GetFontList( )->GetColor( m_titleFont.Get( ) );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetColor( GetAlbum( )->GetAppPrefTitleFontNdx( ) );
        }
        else
        {
            return GetAlbum( )->GetTitleColor( );
        }
    }

    bool AlbumBase::IsDefaultTitleFont( int ndx ) { return ( ndx == GetAlbum( )->GetTitleFontNdx( ) ); }

    bool AlbumBase::IsDefaultTextFont( int ndx ) { return ( ndx == Design::GetAlbum( )->GetTextFontNdx( ) ); }

    bool AlbumBase::IsDefaultCatNbrFont( int ndx ) { return ( ndx == GetAlbum( )->GetCatNbrFontNdx( ) ); }
    
    void AlbumBase::SetTitleFont( wxFont font, wxColour color )
    {
        m_titleFont.Set( GetFontList( )->AddNewFont( font, color ) );
        int ndx = GetFontList( )->AddNewFont( font, color );
        if ( IsDefaultTitleFont( ndx ) && !IsNodeType( AT_Album ) )
        {
            m_titleFont.Set( -1 );
        }
        else
        {
            m_titleFont.Set( ndx );
        }
    }
    void AlbumBase::SetTextFont( wxFont font, wxColour color )
    {
        int ndx = GetFontList( )->AddNewFont( font, color );
        if ( IsDefaultTextFont( ndx ) && !IsNodeType( AT_Album ) )
        {
            m_textFont.Set( -1 );
        }
        else
        {
            m_textFont.Set( ndx );
        }
    }
    void AlbumBase::SetCatNbrFont( wxFont font, wxColour color )
    {
        int ndx = GetFontList( )->AddNewFont( font, color );
        if ( IsDefaultCatNbrFont( ndx ) && !IsNodeType( AT_Album ) )
        {
            m_catNbrFont.Set( -1 );
        }
        else
        {
            m_catNbrFont.Set( ndx );
        }
    }

    void AlbumBase::SaveFonts( wxXmlNode* parent )
    {
        if ( m_catNbrFont.IsOk( ) || m_textFont.IsOk( ) || m_titleFont.IsOk( ) )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                if ( m_catNbrFont.IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultCatNbrFont( m_catNbrFont.Get( ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, m_catNbrFont, Design::AT_CatNbrFontType );
                    }
                }
                if ( m_textFont.IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultCatNbrFont( m_textFont.Get( ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, m_textFont, Design::AT_TextFontType );
                    }
                }
                if ( m_titleFont.IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultCatNbrFont( m_titleFont.Get( ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, m_titleFont, Design::AT_TitleFontType );
                    }
                }
            }
        }
    }


    void AlbumBase::LoadFonts( wxXmlNode* node )
    {

        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {

            Design::AlbumBaseType nodeType = GetNodeType( );

            m_catNbrFont = GetFontList( )->LoadFont( fonts, Design::AT_CatNbrFontType );
            if ( !m_catNbrFont.IsOk( ) )
            {
                if ( nodeType == AT_Album )
                {
                    m_catNbrFont.Set( GetSettings( )->GetAppPrefCatNbrFontNdx( ) );
                }
            }

            m_textFont = GetFontList( )->LoadFont( fonts, Design::AT_TextFontType );
            if ( !m_textFont.IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    m_textFont.Set( GetSettings( )->GetAppPrefTextFontNdx( ) );
                }
            }

            m_titleFont = GetFontList( )->LoadFont( fonts, Design::AT_TitleFontType );
            if ( !m_titleFont.IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    m_titleFont.Set( GetSettings( )->GetAppPrefTitleFontNdx( ) );
                }
            }
        }
    }
    void AlbumBase::DumpFont( wxString Level )
    {

        int ndx = m_catNbrFont.Get( );
        std::cout << Level << "CatNbr font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = m_textFont.Get( );
        std::cout << Level << "Text font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = m_titleFont.Get( );
        std::cout << Level << "Title font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;
    };
}