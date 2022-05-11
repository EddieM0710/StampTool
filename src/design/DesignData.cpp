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

namespace Design {

    DesignData::DesignData(/* args */ )
    {
        m_albumDoc = 0;
        m_album = 0;
    }

    DesignData::~DesignData( )
    {
  
        if ( m_albumDoc ) m_albumDoc->~wxXmlDocument();
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

        m_albumDoc->Save( filename );
        SetDirty(false);
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

        wxXmlNode* albumBaseRoot = m_albumDoc->GetRoot( );
        wxString name = albumBaseRoot->GetName( );

        if ( name.Length( ) == 0 )
        {
            albumBaseRoot->SetName( filename );
        }
        m_album = new Album( (AlbumBase*)0, albumBaseRoot );
        if ( !m_album )
        {
            return false;
        }

        SetDirty(false);
        return true;
    }

    Row* DesignData::AddRow( LayoutBase* node )
    {
        LayoutBase* parent = node;
        AlbumBaseType prevType = AT_None;
        while ( parent )
        {
            AlbumBaseType type = parent->GetNodeType( );
            if ( type == AT_Page )
            {
                // can't mix rows and cols as siblings
                if (prevType != AT_Col )
                {
                    break;
                }
            }
            else if ( type == AT_Col )
            {
                break;
            }
            parent = ( LayoutBase* )parent->GetParent( );
            prevType = type;
        }
        if ( parent )
        {
            Row* newRow = new Row( parent, ( wxXmlNode* )0 );
            parent->AddChild(newRow);
            SetDirty();
            return newRow;
        }
        else
        {
            return  (Row*)0;
        }


    }

    Column* DesignData::AddCol( LayoutBase* node )
    {
        LayoutBase* parent = node;
        AlbumBaseType prevType = AT_None;
        while ( parent )
        {
            AlbumBaseType type = parent->GetNodeType( );
            if ( type == AT_Page )
            {
                // can't mix rows and cols as siblings
                if (prevType != AT_Row )
                {
                    break;
                }
            }
            else if (type == AT_Row )
            {
                break;
            }
            parent = ( LayoutBase* )parent->GetParent( );
            prevType = type;
        }
        if ( parent )
        {
            SetDirty();
            return new Column( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Column*)0;
        }
    }

    Page* DesignData::AddPage( LayoutBase* node )
    {
        LayoutBase* parent = node;
        while ( parent )
        {
            AlbumBaseType type = parent->GetNodeType( );
            if ( type == AT_Album )
            {
                break;
            }
            parent = ( LayoutBase* )parent->GetParent( );
        }
        if ( parent )
        {
            SetDirty();
            return new Page( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Page*)0;
        }
    }

    Stamp* DesignData::AddStamp( LayoutBase* node )
    {
        LayoutBase* parent = node;
        while ( parent )
        {
            AlbumBaseType type = parent->GetNodeType( );
            if ( type == AT_Col
                || type == AT_Row )
            {
                break;
            }
            parent = ( LayoutBase* )parent->GetParent( );
        }
        if ( parent )
        {
            SetDirty();
            return new Stamp( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Stamp*)0;
        }

    }
    Title* DesignData::AddTitle( LayoutBase* node )
    {
        LayoutBase* parent = node;
        while ( parent )
        {
            AlbumBaseType type = parent->GetNodeType( );
            if ( type == AT_Col
                || type == AT_Row
                || type == AT_Page )
            {
                break;
            }
            parent = ( LayoutBase* )parent->GetParent( );
        }
        if ( parent )
        {
            SetDirty();
            return new Title( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Title*)0;
        }
    }

    AlbumBase* DesignData::GetPage( AlbumBase* node )
    {
        while ( node )
        {
            if ( node->GetNodeType() == AT_Page )
            {
                return node;
            }
            node = node->GetParent();
        }
        return (AlbumBase*)0;
    }


    NodeStatus DesignData::ValidatePage( AlbumBase* node )
    {
        Page* page = (Page*)GetPage(node);
        if ( page )
        {
            return page->ValidateChildren( page );
        }
        return AT_FATAL;
    }
}
