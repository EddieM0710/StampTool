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

    AlbumVolume::AlbumVolume( /* args */ )
    {
        isOKPtr = ( intptr_t ) &isOKPtr;
        m_albumDoc = 0;
        m_album = 0;
    }

    AlbumVolume::~AlbumVolume( )
    {

        if ( m_albumDoc ) m_albumDoc->~wxXmlDocument( );
        if ( m_album ) delete m_album;
        m_albumDoc = 0;
        m_album = 0;
    }

    wxImage AlbumVolume::GetImage( wxString filename )
    {
        wxImage image;
        if ( filename.IsEmpty( ) )
        {
            image = wxNullImage;
        }
        else
        {
            wxString str = GetProject( )->GetImageFullPath( filename );

            if ( !GetProject( )->ImageExists( str ) )
            {
                image = wxNullImage; ;
            }
            else
            {
                image = wxImage( str );

                if ( !image.IsOk( ) )
                {
                    image = wxNullImage; ;
                }
            }
        }
        return image;
    }

    // Utils::ImageRepository* AlbumVolume::GetImageRepository( )
    // {
    //     return m_imageRepository;
    // };

    wxString AlbumVolume::GetPath( )
    {
        wxFileName albumFn( m_albumFilename );
        albumFn.MakeAbsolute( );
        return albumFn.GetPath( );
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
        m_albumDoc = 0;
        m_album = 0;
        return ( AlbumVolume* ) 0;
    }

    bool AlbumVolume::IsOK( )
    {

        if ( isOKPtr == ( intptr_t ) &isOKPtr )
        {
            return true;
        }
        return false;
    }

    void AlbumVolume::LoadDefaultDocument( )
    {
        wxXmlDocument* newDocument = AlbumVolume::NewDesignDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Album" );
        newDocument->SetRoot( root );
        root->AddAttribute( AttrNameStrings[ AT_Name ], "" );
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

    wxString AlbumVolume::GetAlbumPath( )
    {
        wxString filename = GetAlbumFilename( );
        wxFileName FN( filename );
        FN.MakeAbsolute( );
        return FN.GetPath( );
    }

    wxString AlbumVolume::GetAlbumBaseName( )
    {
        wxString filename = GetAlbumFilename( );
        wxFileName FN( filename );
        return FN.GetName( );
    }

    // wxString AlbumVolume::GetZipFileName( )
    // {
    //     wxString path = GetAlbumPath( );
    //     wxString name = GetAlbumBaseName( );
    //     name = name + "Alb.zip";
    //     wxFileName FN( path );
    //     FN.SetName( name );
    //     FN.SetExt( "zip" );
    //     return ( path + "/" + name );
    // }

    bool AlbumVolume::LoadXML( )
    {
        wxString filename = GetAlbumFilename( );
        if ( !wxFileExists( filename ) )
        {
            return false;
        }
        if ( !m_albumDoc )
        {
            m_albumDoc = NewDesignDocument( );
        }
        bool ok = m_albumDoc->Load( filename );

        if ( !ok )
        {
            std::cout << "AlbumVolume::LoadXML: " << filename << " Load Failed.\n";
            return false;
        }

        //        MakeAlbumImageRepository( GetZipFileName( ) );

        SetDirty( false );
        return true;
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


    AlbumVolume* NewAlbumVolumeInstance( )
    {
        AlbumVolume* albumVolume = new AlbumVolume( );
        albumVolume->InitAlbumVolume( );
        return albumVolume;
    }

    wxXmlDocument* AlbumVolume::NewDesignDocument( )
    {
        if ( m_albumDoc )
        {
            delete m_albumDoc;
        }
        m_albumDoc = new wxXmlDocument( );
        return m_albumDoc;
    };

    void AlbumVolume::SaveDesignTree( )
    {
        if ( m_albumDoc )
        {
            wxTreeItemId albumID = GetAlbumTreeCtrl( )->GetRootItem( );
            Design::Album* album = ( Design::Album* ) GetAlbumTreeCtrl( )->GetItemNode( albumID );

            wxXmlNode* root = m_albumDoc->DetachRoot( );
            root->~wxXmlNode( );

            wxXmlNode* xmlNode = Utils::NewNode( m_albumDoc, Design::AlbumBaseNames[ Design::AT_Album ] );
            albumID = GetAlbumTreeCtrl( )->GetRootItem( );
            album->Save( xmlNode );
            GetAlbumTreeCtrl( )->SaveNodeData( xmlNode, albumID );
        }
    }

    void AlbumVolume::SaveXML( )
    {
        wxString filename = GetAlbumFilename( );
        if ( m_albumDoc )
        {
            if ( wxFileExists( filename ) )
            {
                wxFileName bakFile( filename );
                bakFile.SetExt( "bak.alb" );
                wxRenameFile( filename, bakFile.GetFullName( ), true );
            }
            SaveDesignTree( );
            m_albumDoc->Save( filename );
            SetDirty( false );
        }
    }

    // Set the design to dirty  
    void AlbumVolume::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetAppData( )->SetDirty( true );
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
