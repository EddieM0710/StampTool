/**
 * @file AlbumData.cpp
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
#include "album/AlbumData.h"
#include "album/Album.h"
#include "album/Stamp.h"
#include "album/Page.h"
#include "album/Title.h"
#include "album/Row.h"
#include "album/Column.h"
#include "AlbumGenApp.h"

namespace Layout {

    AlbumData::AlbumData(/* args */ )
    {
        m_albumDoc = 0;
    }

    AlbumData::~AlbumData( )
    {
        delete m_albumDoc;
    }

    bool AlbumData::IsOK( )
    {
        if ( m_albumDoc )
        {
            return true;
        }
        return false;
    }
    wxXmlDocument* AlbumData::NewDocument( )
    {
        delete m_albumDoc;
        m_albumDoc = new wxXmlDocument( );
        return m_albumDoc;
    };
    // wxXmlDocument* AlbumData::ReplaceDocument( wxXmlDocument* doc )
    // {
    //     delete m_albumDoc;
    //     m_albumDoc = doc;
    //     return m_albumDoc;
    // };

    void AlbumData::SaveXML( wxString filename )
    {
        if ( wxFileExists( filename ) )
        {
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak" );
            wxRenameFile( filename, bakFile.GetFullName( ) );
        }

        m_albumDoc->Save( filename );
    }
    void AlbumData::LoadXML( wxString filename )
    {
        if ( !m_albumDoc )
        {
            m_albumDoc = NewDocument( );
        }
        bool ok = m_albumDoc->Load( filename );

        if ( !ok )
        {
            std::cout << filename << " Load Failed.\n";
        }
        else
        {
            wxXmlNode* albumData = m_albumDoc->GetRoot( );
            wxString name = albumData->GetName( );

            if ( name.Length( ) == 0 )
            {
                albumData->SetName( filename );
            }
            m_album = new Album( (AlbumNode*)0, albumData );
        }
    }

    Row* AlbumData::AddRow( LayoutNode* node )
    {
        LayoutNode* parent = node;
        AlbumNodeType prevType = AT_None;
        while ( parent )
        {
            AlbumNodeType type = parent->GetNodeType( );
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
            parent = ( LayoutNode* )parent->GetParent( );
            prevType = type;
        }
        if ( parent )
        {
            Row* newRow = new Row( parent, ( wxXmlNode* )0 );
            parent->AddChild(newRow);
            return newRow;
        }
        else
        {
            return  (Row*)0;
        }
    }

    Column* AlbumData::AddCol( LayoutNode* node )
    {
        LayoutNode* parent = node;
        AlbumNodeType prevType = AT_None;
        while ( parent )
        {
            AlbumNodeType type = parent->GetNodeType( );
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
            parent = ( LayoutNode* )parent->GetParent( );
            prevType = type;
        }
        if ( parent )
        {
            return new Column( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Column*)0;
        }
    }

    Page* AlbumData::AddPage( LayoutNode* node )
    {
        LayoutNode* parent = node;
        while ( parent )
        {
            AlbumNodeType type = parent->GetNodeType( );
            if ( type == AT_Album )
            {
                break;
            }
            parent = ( LayoutNode* )parent->GetParent( );
        }
        if ( parent )
        {
            return new Page( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Page*)0;
        }
    }

    Stamp* AlbumData::AddStamp( LayoutNode* node )
    {
        LayoutNode* parent = node;
        while ( parent )
        {
            AlbumNodeType type = parent->GetNodeType( );
            if ( type == AT_Col
                || type == AT_Row )
            {
                break;
            }
            parent = ( LayoutNode* )parent->GetParent( );
        }
        if ( parent )
        {
            return new Stamp( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Stamp*)0;
        }
    }
    Title* AlbumData::AddTitle( LayoutNode* node )
    {
        LayoutNode* parent = node;
        while ( parent )
        {
            AlbumNodeType type = parent->GetNodeType( );
            if ( type == AT_Col
                || type == AT_Row
                || type == AT_Page )
            {
                break;
            }
            parent = ( LayoutNode* )parent->GetParent( );
        }
        if ( parent )
        {
            return new Title( parent, ( wxXmlNode* )0 );
        }
        else
        {
            return  (Title*)0;
        }
    }
    void AlbumData::Validate()
    {
        ResetValidateStatus( );
        m_album->Validate( );
    }

}