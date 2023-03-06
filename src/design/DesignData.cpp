/**
 * @file DesignData.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
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
#include "StampToolApp.h"
#include "gui/AlbumImagePanel.h"
#include "gui/DesignTreeCtrl.h"

namespace Design { 

    DesignData* NewDesignDataInstance( )
    { 
        DesignData* designData = new DesignData( );
        designData->InitDesignData( );
        return designData;
    }

    //*****    

    DesignData::DesignData( /* args */ )
    { 
        m_albumDoc = 0;
        m_album = 0;
    }
    DesignData* DesignData::InitDesignData( )
    { 
        m_albumDoc = 0;
        m_album = 0;
        m_fontList.InitFonts();
        return (DesignData* )0;
    }

    //*****  
    DesignData::~DesignData( )
    { 

        if ( m_albumDoc ) m_albumDoc->~wxXmlDocument( );
        if ( m_album ) delete m_album;
        m_albumDoc = 0;
        m_album = 0;
    }

    //*****  
    bool DesignData::IsOK( )
    { 
        if ( m_albumDoc )
        { 
            return true;
        }
        return false;
    }


    // Set the design to dirty
    //*****    
    void DesignData::SetDirty( bool state )
    { 
        m_dirty = state;
        if ( m_dirty )
        { 
            GetToolData( )->SetDirty( true );
        }
    }


    void DesignData::LoadDefaultDocument( )
    { 
        wxXmlDocument* newDocument = DesignData::NewDesignDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Album" );
        newDocument->SetRoot( root );
        root->AddAttribute( AttrNameStrings[ AT_Name ], "" );
        root->AddAttribute( AttrNameStrings[ AT_PageWidth ], "215.9" );
        root->AddAttribute( AttrNameStrings[ AT_PageHeight ], "279.4" );
        root->AddAttribute( AttrNameStrings[ AT_TopMargin ], "7.62" );
        root->AddAttribute( AttrNameStrings[ AT_BottomMargin ], "7.62" );
        root->AddAttribute( AttrNameStrings[ AT_RightMargin ], "7.62" );
        root->AddAttribute( AttrNameStrings[ AT_LeftMargin ], "19.05" );
        root->AddAttribute( AttrNameStrings[ AT_BorderSize ], "4" );

        Album* album = new Album( root );
        SetAlbum( album );
        wxXmlNode* pageNode = new wxXmlNode( wxXML_ELEMENT_NODE, AlbumBaseNames[ AT_Page ] );
        Page* page = ( Page* )new Page( pageNode );
    }


    //*****  
    wxXmlDocument* DesignData::NewDesignDocument( )
    { 
        delete m_albumDoc;
        m_albumDoc = new wxXmlDocument( );
        return m_albumDoc;
    };


    // Save the DesignData to an xml file 
    //*****  
    void DesignData::SaveXML( wxString filename )
    { 
        if ( m_albumDoc )
        { 
            if ( wxFileExists( filename ) )
            { 
                wxFileName bakFile( filename );
                bakFile.SetExt( "bak" );
                wxRenameFile( filename, bakFile.GetFullName( ), true );
            }
            SaveDesignTree( );
            m_albumDoc->Save( filename );
            SetDirty( false );
        }
    }

    // transfers the DesignData tree to an xml file
    //*****  
    void DesignData::SaveDesignTree( )
    { 
        if ( m_albumDoc )
        { 
            wxTreeItemId albumID = GetDesignTreeCtrl( )->GetRootItem( );
            Design::Album* album = ( Design::Album* )GetDesignTreeCtrl( )->GetItemNode( albumID );

            wxXmlNode* root = m_albumDoc->DetachRoot( );
            root->~wxXmlNode( );

            wxXmlNode* xmlNode = Utils::NewNode( m_albumDoc, Design::AlbumBaseNames[ Design::AT_Album ] );
            albumID = GetDesignTreeCtrl( )->GetRootItem( );
            album->Save( xmlNode );
            GetDesignTreeCtrl( )->SaveNodeData( xmlNode, albumID );
        }
    }

    // loads an xml file into memory
    //*****  
    bool DesignData::LoadXML( wxString filename )
    { 
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
            std::cout << filename << " Load Failed.\n";
            return false;
        }


        SetDirty( false );
        return true;
    }

    // Gets the page of the selected design given node
    //*****  
    AlbumBase* DesignData::GetPage( AlbumBase* node )
    { 
        wxTreeItemId id = node->GetTreeItemId( );
        if ( id.IsOk( ) ) id = GetDesignTreeCtrl( )->GetPage( id );
        if ( id.IsOk( ) ) return GetDesignTreeCtrl( )->GetItemNode( id );
        return ( AlbumBase* )0;
    }

    //*****  
    NodeStatus DesignData::ValidatePage( AlbumBase* node )
    { 
        Page* page = ( Page* )GetPage( node );
        if ( page )
        { 
            return page->ValidateChildren( page );
        }
        return AT_FATAL;
    }

    //*****  
    void DesignData::MakePage( Design::LayoutBase* node )
    { 
        Page* page = ( Page* )GetPage( node );
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

    //*****  
    void DesignData::UpdateAlbum( )
    { 
        bool ok = m_album->UpdateMinimumSize( );
        //if ( ok )
        { 
            m_album->UpdateSizes( );
            m_album->UpdatePositions( );
            GetAlbumImagePanel( )->Refresh( );

//            m_album->DumpLayout( );

        }
    }

}
