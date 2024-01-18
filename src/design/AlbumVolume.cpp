/**
 * @file AlbumVolume.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
 *
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <iostream>
#include <wx/filename.h>
#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/wfstream.h>

#include "utils/CSV.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "utils/XMLUtilities.h"
#include "Defs.h"
#include "design/AlbumVolume.h"
#include "design/AlbumBase.h"
#include "design/Album.h"
#include "design/Stamp.h"
#include "design/Page.h"
#include "design/Row.h"
#include "design/Column.h"
 //#include "StampToolApp.h"
#include "gui/AlbumImagePanel.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/StampToolFrame.h"
#include "gui/AppData.h"
//#include "utils/ImageZip.h"

//#include "utils/ImageRepository.h"

namespace Design {

    AlbumVolume::AlbumVolume( ) : Volume( "Album" )
    {

    }

    AlbumVolume::~AlbumVolume( )
    {

        if ( m_album ) delete m_album;
        m_album = 0;
    }

    AlbumBase* AlbumVolume::GetPage( AlbumBase* node )
    {
        wxTreeItemId id = node->GetTreeItemId( );
        if ( id.IsOk( ) ) id = GetAlbumTreeCtrl( )->GetPage( id );
        if ( id.IsOk( ) )
        {
            return GetAlbumTreeCtrl( )->GetItemNode( id );
        }
        return ( AlbumBase* ) 0;
    }

    AlbumVolume* AlbumVolume::InitAlbumVolume( )
    {
        m_album = 0;
        return ( AlbumVolume* ) this;
    }



    void AlbumVolume::LoadDefaultDocument( wxString volName )
    {
        // NewDocument sets the Volume m_doc
        wxXmlDocument* newDocument = NewDocument( );
        wxXmlNode* root = newDocument->GetRoot( );
        root->AddAttribute( AttrNameStrings[ AT_Name ], volName );
        root->AddAttribute( AttrNameStrings[ AT_OverSizePaper ], "False" );
        root->AddAttribute( AttrNameStrings[ AT_PaperHeight ], "0" );
        root->AddAttribute( AttrNameStrings[ AT_PaperWidth ], "0" );
        root->AddAttribute( AttrNameStrings[ AT_PageWidth ], "215.9" );
        root->AddAttribute( AttrNameStrings[ AT_PageHeight ], "279.4" );
        root->AddAttribute( AttrNameStrings[ AT_TopPageMargin ], "7.62" );
        root->AddAttribute( AttrNameStrings[ AT_BottomPageMargin ], "7.62" );
        root->AddAttribute( AttrNameStrings[ AT_RightPageMargin ], "7.62" );
        root->AddAttribute( AttrNameStrings[ AT_LeftPageMargin ], "19.05" );
        root->AddAttribute( AttrNameStrings[ AT_BorderSize ], "4" );
        root->AddAttribute( AttrNameStrings[ AT_BorderFileName ], "" );

        Album* album = new Album( root );
        SetAlbum( album );
        wxXmlNode* pageNode = new wxXmlNode( wxXML_ELEMENT_NODE, AlbumBaseNames[ AT_Page ] );
        Page* page = ( Page* )new Page( pageNode );
    }



    void AlbumVolume::MakePage( Design::LayoutBase* node )
    {
        Page* page = ( Page* ) GetPage( node );
        if ( page )
        {
            bool ok = page->UpdateMinimumSize( );
            if ( ok )
            {
                page->UpdateSizes( );
                page->UpdatePositions( );
                GetAlbumImagePanel( )->Refresh( );
            }
        }
    }



    void AlbumVolume::Save( )
    {
        SaveXML( );
    }

    void AlbumVolume::SaveXML( )
    {
        wxString filename = GetFilename( );
        if ( GetDoc( ) )
        {
            if ( wxFileExists( filename ) )
            {
                wxFileName bakFile( filename );
                bakFile.SetExt( "bak.alb" );
                wxRenameFile( filename, bakFile.GetFullName( ), true );
            }
            SaveDesignTree( );
            GetDoc( )->Save( filename );
            SetDirty( false );
        }
    }


    void AlbumVolume::SaveDesignTree( )
    {
        if ( GetDoc( ) )
        {
            wxTreeItemId albumID = GetAlbumTreeCtrl( )->GetRootItem( );
            Design::Album* album = ( Design::Album* ) GetAlbumTreeCtrl( )->GetItemNode( albumID );

            // Out with the old
            wxXmlNode* root = GetDoc( )->DetachRoot( );
            root->~wxXmlNode( );

            //in with the new
            wxXmlNode* xmlNode = Utils::NewNode( GetDoc( ), Design::AlbumBaseNames[ Design::AT_Album ] );
            albumID = GetAlbumTreeCtrl( )->GetRootItem( );
            album->Save( xmlNode );
            GetAlbumTreeCtrl( )->SaveNodeData( xmlNode, albumID );
        }
    }



    NodeStatus AlbumVolume::ValidatePage( AlbumBase* node )
    {
        Page* page = ( Page* ) GetPage( node );
        if ( page )
        {
            return page->ValidateChildren( page );
        }
        return AT_FATAL;
    }

    void AlbumVolume::UpdateAlbum( )
    {
        m_album->UpdateMinimumSize( );
        m_album->UpdateSizes( );
        m_album->UpdatePositions( );
        GetAlbumImagePanel( )->Refresh( );

    }

    void AlbumVolume::UpdatePage( AlbumBase* node )
    {
        Design::Page* page = ( Page* ) GetPage( node );
        if ( page )
        {
            page->UpdateMinimumSize( );
            page->UpdateSizes( );
            page->UpdatePositions( );
        }
    }

}
