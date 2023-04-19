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

#include "design/Page.h"
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





    void AlbumBase::SetFontNdx( AT_FontUsageType fontType, int ndx )
    {
        AlbunBaseFonts[ fontType ].Set( ndx );
    };

    int AlbumBase::GetFontNdx( AT_FontUsageType fontType )
    {
        return AlbunBaseFonts[ fontType ].Get( );
    };

    wxFont AlbumBase::GetFont( AT_FontUsageType fontType )
    {
        int ndx = GetFontNdx( fontType );
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            return GetFontList( )->GetFont( ndx );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetFont( GetAlbum( )->GetFontNdxPreference( fontType ) );
        }
        else
        {
            return GetAlbum( )->GetFont( fontType );
        }

    }

    wxColour AlbumBase::GetColor( AT_FontUsageType fontType )
    {
        int ndx = GetFontNdx( fontType );
        if ( GetFontList( )->IsValidFontNdx( ndx ) )
        {
            return GetFontList( )->GetColor( ndx );
        }
        if ( GetNodeType( ) == AT_Album )
        {
            return GetFontList( )->GetColor( GetAlbum( )->GetFontNdxPreference( fontType ) );
        }
        else
        {
            return GetAlbum( )->GetColor( fontType );
        }
    }

    void AlbumBase::SetFont( AT_FontUsageType fontType, wxFont font, wxColour color )
    {
        int ndx = GetFontList( )->AddNewFont( font, color );
        if ( IsDefaultFont( fontType, ndx ) && !IsNodeType( AT_Album ) )
        {
            SetFontNdx( fontType, -1 );
        }
        else
        {
            SetFontNdx( fontType, ndx );
        }
    }

    bool AlbumBase::IsDefaultFont( AT_FontUsageType fontType, int ndx )
    {
        return ( ndx == GetAlbum( )->GetFontNdx( fontType ) );
    }

    void AlbumBase::SaveFonts( wxXmlNode* parent )
    {
        if ( AlbunBaseFonts[ AT_NbrFontType ].IsOk( ) || AlbunBaseFonts[ AT_TextFontType ].IsOk( ) || AlbunBaseFonts[ AT_TitleFontType ].IsOk( ) || AlbunBaseFonts[ AT_NameFontType ].IsOk( ) )
        {
            wxXmlNode* fonts = Utils::NewNode( parent, "Fonts" );
            if ( fonts )
            {
                if ( AlbunBaseFonts[ AT_NbrFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_NbrFontType, GetFontNdx( AT_NbrFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, AlbunBaseFonts[ AT_NbrFontType ], Design::AT_NbrFontType );
                    }
                }
                if ( AlbunBaseFonts[ AT_NameFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_NameFontType, GetFontNdx( AT_NameFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, AlbunBaseFonts[ AT_NameFontType ], Design::AT_NameFontType );
                    }
                }
                if ( AlbunBaseFonts[ AT_TextFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_TextFontType, GetFontNdx( AT_TextFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, AlbunBaseFonts[ AT_TextFontType ], Design::AT_TextFontType );
                    }
                }
                if ( AlbunBaseFonts[ AT_TitleFontType ].IsOk( ) )
                {
                    if ( IsNodeType( AT_Album )  //save all fonts for album                    
                        //or all but default fonts for others
                        || ( !IsNodeType( AT_Album ) && !IsDefaultFont( AT_TitleFontType, GetFontNdx( AT_TitleFontType ) ) ) )
                    {
                        GetFontList( )->SaveFont( fonts, AlbunBaseFonts[ AT_TitleFontType ], Design::AT_TitleFontType );
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

            AlbunBaseFonts[ AT_NbrFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_NbrFontType );
            if ( !AlbunBaseFonts[ AT_NbrFontType ].IsOk( ) )
            {
                if ( nodeType == AT_Album )
                {
                    AlbunBaseFonts[ AT_NbrFontType ].Set( GetSettings( )->GetFontNdxPreference( AT_NbrFontType ) );
                }
            }

            AlbunBaseFonts[ AT_NameFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_NameFontType );
            if ( AlbunBaseFonts[ AT_NameFontType ].IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    AlbunBaseFonts[ AT_NameFontType ].Set( GetSettings( )->GetFontNdxPreference( AT_TextFontType ) );
                }
            }

            AlbunBaseFonts[ AT_TextFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_TextFontType );
            if ( !AlbunBaseFonts[ AT_TextFontType ].IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    AlbunBaseFonts[ AT_TextFontType ].Set( GetSettings( )->GetFontNdxPreference( AT_TextFontType ) );
                }
            }

            AlbunBaseFonts[ AT_TitleFontType ] = GetFontList( )->LoadFont( fonts, Design::AT_TitleFontType );
            if ( !AlbunBaseFonts[ AT_TitleFontType ].IsOk( ) )
            {
                if ( IsNodeType( AT_Album ) )
                {
                    AlbunBaseFonts[ AT_TitleFontType ].Set( GetSettings( )->GetFontNdxPreference( Design::AT_TitleFontType ) );
                }
            }
        }
    }
    void AlbumBase::DumpFont( wxString Level )
    {

        int ndx = AlbunBaseFonts[ AT_NbrFontType ].Get( );
        std::cout << Level << "CatNbr font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = AlbunBaseFonts[ AT_TextFontType ].Get( );
        std::cout << Level << "Text font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;

        ndx = AlbunBaseFonts[ AT_TitleFontType ].Get( );
        std::cout << Level << "Title font " << GetFontList( )->GetFont( ndx ).GetNativeFontInfoUserDesc( )
            << "  color " << GetFontList( )->GetColor( ndx ).GetAsString( )
            << "  Ndx " << ndx << std::endl;
    };
}