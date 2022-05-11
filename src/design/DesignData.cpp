/**
 * @file DesignData.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
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

#include "catalog/Classification.h"
#include "utils/CSV.h"
#include "utils/Settings.h"
#include "utils/XMLUtilities.h"
#include "Defs.h"
#include "design/DesignData.h"
#include "design/AlbumBase.h"
#include "design/Album.h"
#include "design/Stamp.h"
#include "design/Page.h"
#include "design/Title.h"
#include "design/Row.h"
#include "design/Column.h"
#include "AlbumGenApp.h"
#include "gui/AlbumImagePanel.h"
#include "gui/DesignTreeCtrl.h"

namespace Design {

    DesignData::DesignData(/* args */ )
    {
        m_albumDoc = 0;
        m_album = 0;
    }

    DesignData::~DesignData( )
    {

        if ( m_albumDoc ) m_albumDoc->~wxXmlDocument( );
        if ( m_album ) delete m_album;
        m_albumDoc = 0;
        m_album = 0;
    }

    bool DesignData::IsOK( )
    {
        if ( m_albumDoc )
        {
            return true;
        }
        return false;
    }
    wxXmlDocument* DesignData::NewDocument( )
    {
        delete m_albumDoc;
        m_albumDoc = new wxXmlDocument( );
        return m_albumDoc;
    };


    void DesignData::SaveXML( wxString filename )
    {
        if ( wxFileExists( filename ) )
        {
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak" );
            wxRenameFile( filename, bakFile.GetFullName( ), true );
        }
        SaveDesignTree();
        m_albumDoc->Save( filename );
        SetDirty( false );
    }

    void DesignData::SaveDesignTree()
    {
        wxTreeItemId albumID = GetDesignTreeCtrl()->GetRootItem();
        Design::Album* album = (Design::Album*)GetDesignTreeCtrl()->GetItemNode(albumID);
    
        wxXmlNode* root = m_albumDoc->DetachRoot();
        root->~wxXmlNode();
         
        wxXmlNode* xmlNode = Utils::NewNode( m_albumDoc, Design::AlbumBaseNames[Design::AT_Album] );
        albumID = GetDesignTreeCtrl()->GetRootItem();
        album->Save( xmlNode );    
        GetDesignTreeCtrl()->SaveNodeData ( xmlNode, albumID );   
    }

    bool DesignData::LoadXML( wxString filename )
    {
        if ( !m_albumDoc )
        {
            m_albumDoc = NewDocument( );
        }
        bool ok = m_albumDoc->Load( filename );

        if ( !ok )
        {
            std::cout << filename << " Load Failed.\n";
            return false;
        }


        SetDirty( false );
        return true;
    }

    AlbumBase* DesignData::GetPage( AlbumBase* node )
    {
        wxTreeItemId id = node->GetTreeItemId();
        if ( id.IsOk() ) id = GetDesignTreeCtrl()->GetPage(id);
        if ( id.IsOk() ) return GetDesignTreeCtrl()->GetItemNode(id);
        return (AlbumBase*)0;
    }

    NodeStatus DesignData::ValidatePage( AlbumBase* node )
    {
        Page* page = ( Page* )GetPage( node );
        if ( page )
        {
            return page->ValidateChildren( page );
        }
        return AT_FATAL;
    }

    void DesignData::MakePage(LayoutBase* node)
    {
        Page* page = (Page*)GetPage( node );
        if ( page )
        {
            bool ok = page->UpdateMinimumSize( );
            if ( ok )
            {
                page->UpdateSizes( );
                page->UpdatePositions( );
                GetAlbumImagePanel()->DrawBitmap( );
            }
        }
    }

    void DesignData::UpdateAlbum( )
    {
        bool ok = m_album->UpdateMinimumSize( );
       //if ( ok )
        {
            m_album->UpdateSizes( );
            m_album->UpdatePositions( );
            GetAlbumImagePanel()->DrawBitmap( );
            m_album->DumpLayout(   );

        }
    }

}
