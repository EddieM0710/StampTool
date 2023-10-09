/**
 * @file Project.cpp
 * @author Eddie Monroe ( you@domain.com )
 * @brief
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright ( c ) 2021
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

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <iostream>
#include <vector>
#include <wx/filename.h>
#include <wx/filefn.h> 
#include <wx/wfstream.h>

#include "utils/Project.h"

#include "Defs.h"
#include "utils/Settings.h"

#include "catalog/CatalogList.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogVolume.h"
#include "design/DesignDefs.h"
#include "design/AlbumVolume.h"
#include "design/AlbumList.h"
#include "design/AlbumBase.h"
#include "design/AlbumData.h"
#include "collection/CollectionData.h"

#include "gui/CatalogTreeCtrl.h"
#include "gui/CatalogTOCTreeCtrl.h"
#include "gui/AlbumTOCTreeCtrl.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/StampToolFrame.h"

 //#include "mount/StampMount.h"

namespace Utils {

    Project::Project( )
    {
        m_ProjectDoc = ( wxXmlDocument* ) 0;
    }
    void Project::InitProject( )
    {
        InitDefs( );
        SetDirty( false );
    }

    // 

    wxString Project::GetImagePath( )
    {
        return m_imagePath;
    };

    wxString Project::GetImageFullPath( wxString imageName )
    {
        wxString projectPath = GetImagePath( );
        projectPath += "/" + imageName;
        wxFileName file( projectPath );
        wxString str = file.GetFullPath( );
        file.MakeAbsolute( );
        str = file.GetFullPath( );
        return str;
    }

    wxImage Project::GetImage( wxString filename )
    {
        wxImage image;
        if ( filename.IsEmpty( ) )
        {
            image = wxNullImage;
        }
        else
        {
            wxString str = GetImageFullPath( filename );

            if ( !ImageExists( str ) )
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

    bool Project::ImageExists( wxString imageName )
    {
        wxImage image;

        if ( wxFileExists( imageName ) )
        {
            if ( image.CanRead( imageName ) )
            {
                return true;
            }
        }
        return false;
    }
    void Project::SetImagePath( wxString imagePath )
    {
        m_imagePath = imagePath;
        m_dirty = true;
    };


    wxString Project::GetDesignFilename( )
    {
        return m_designFilename;
    };

    //

    void Project::SetDesignFilename( wxString albumFilename )
    {
        m_designFilename = albumFilename;
        m_dirty = true;
    };

    // void Project::SetCatalogFilename( wxString catalogFilename )
    // {
    //     if ( m_catalogFilename.Cmp( catalogFilename ) )
    //     {
    //         m_catalogFilename = catalogFilename;
    //         SetDirty( );
    //     }
    // };

    //
    void Project::SetCaption( )
    {
        StampToolFrame* frame = GetFrame( );
        if ( frame )
        {
            GetSettings( )->SetLastFile( m_projectFilename );
            frame->SetCaption( GetSettings( )->GetLastFile( ) );
        }
    }
    void Project::SetProjectFilename( wxString name )
    {
        m_projectFilename = name;
        GetSettings( )->SetLastFile( m_projectFilename );
        SetCaption( );

    };

    //

    wxString Project::MakeFileAbsolute( wxString filename )
    {
        wxFileName newFile( filename );
        if ( !newFile.IsAbsolute( ) )
        {
            newFile.MakeAbsolute( );
        }
        return newFile.GetFullPath( );
    }




    bool Project::LoadProjectXML( )
    {
        wxFileName projFile( m_projectFilename );
        wxString str;

        projFile.DirName( str );

        if ( projFile.FileExists( ) )
        {
            if ( !projFile.IsAbsolute( ) )
            {
                projFile.MakeAbsolute( );
            }
        }
        else
        {
            //setup new files
            return false;
        }

        wxString cwd = projFile.GetPath( );
        wxSetWorkingDirectory( cwd );

        m_ProjectDoc = new wxXmlDocument( );
        wxFileInputStream stream( m_projectFilename );
        if ( !stream.IsOk( ) )
        {
            return false;
        }
        //return Load(stream, encoding, flags);


        if ( !m_ProjectDoc->Load( stream ) )
        {
            ReportError( "Project::Load", "error loading Prokect xml file.", true );
            return false;
        }

        wxXmlNode* projectRoot = m_ProjectDoc->GetRoot( );
        wxString name = projectRoot->GetName( );
        if ( name.Cmp( "Project" ) )
        {
            // std::cout << "Initial node must be <Project>" << "\n";
            // std::cout << "Found \"" << name << "\" instead.\n";
            return false;
        }
        LoadAttributes( projectRoot );

        // // Get Collections
        // wxXmlNode* collectionNode = FirstChildElement( projectRoot, "CollectionList" );
        // if ( collectionNode )
        // {
        //     Inventory::CollectionData* collectionData = GetCollectionList( );
        //     wxString name = collectionNode->GetAttribute( "Filename", "" );
        //     collectionData->SetFilename( name );
        // }

        // Get Albums
        m_albumListNode = FirstChildElement( projectRoot, "AlbumList" );
        GetAlbumData( )->GetAlbumList( ).AddChild( m_albumListNode );

        // Get Mounts
        wxXmlDocument* mountDoc = GetCatalogData( )->LoadMountCSV( );

        // Get Catalogs
        m_catalogListNode = FirstChildElement( projectRoot, "CatalogList" );
        GetCatalogData( )->GetCatalogList( )->AddChild( m_catalogListNode );

        GetSettings( )->SetLastFile( m_projectFilename );

        SetDirty( false );
        return true;
    }


    void Project::LoadAttributes( wxXmlNode* thisObject )
    {
        const wxXmlAttribute* attr = thisObject->GetAttributes( );
        wxFileName filename;
        while ( attr )
        {
            wxString name = attr->GetName( );
            wxString val = attr->GetValue( );

            if ( !name.Cmp( "OutputName" ) )
            {
                //               m_ODTOutputFilename = MakeFileAbsolute( val );
            }
            else if ( !name.Cmp( "Album" ) )
            {
                m_designFilename = MakeFileAbsolute( val );
            }
            else if ( !name.Cmp( "ImagePath" ) )
            {
                m_imagePath = MakeFileAbsolute( val );
                SetImagePath( m_imagePath );
            }
            // else if ( !name.Cmp( "Catalog" ) )
            // {
            //     m_catalogFilename = MakeFileAbsolute( val );
            // }
            else if ( !name.Cmp( "Country" ) )
            {
                m_defaultCountryID = val;
            }
            else if ( !name.Cmp( "CatalogCode" ) )
            {
                m_defaultCatalogCode = val;
            }
            attr = attr->GetNext( );
        }
    }



    void Project::FileNewProject( wxString sptName )
    {
        GetProject( )->SetProjectFilename( sptName );
        wxString lastFile = wxGetCwd( );
        lastFile += "/" + sptName;
        GetSettings( )->SetLastFile( lastFile );

        //clear catalog volume wxList
        GetCatalogData( )->GetCatalogList( )->ClearCatalogArray( );
        //clear dialog volume list
        GetAlbumData( )->GetAlbumList( ).ClearArray( );
        //clear catalog tree
        GetCatalogTreeCtrl( )->ClearCatalogTree( );
        //GetAlbumPageTreeCtrl( )->ClearCatalogTree( );
        //clear dialog tree
        GetAlbumTreeCtrl( )->ClearDesignTree( );

    }

    void Project::Save( )
    {

        if ( wxFileExists( m_projectFilename ) )
        {
            wxFileName bakFile( m_projectFilename );
            bakFile.SetExt( "bak.spt" );
            wxRenameFile( m_projectFilename, bakFile.GetFullName( ), true );
        }
        if ( m_ProjectDoc )
        {
            delete m_ProjectDoc;
            m_ProjectDoc = 0;
        }
        wxXmlDocument* newDoc = new wxXmlDocument( );

        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Project" );
        newDoc->SetRoot( root );
        root->AddAttribute( "Country", GetProjectCountryID( ) );
        root->AddAttribute( "CatalogCode", GetProjectCatalogCode( ) );
        root->AddAttribute( "ImagePath", m_imagePath );

        wxXmlNode* albumListNode = NewNode( root, "AlbumList" );

        wxTreeItemId tocRootID = GetAlbumTOCTreeCtrl( )->GetRootItem( );

        //  TOCTreeItemData* data = ( TOCTreeItemData* ) GetAlbumTOCTreeCtrl( )->GetItemData( tocRootID );
        //  wxXmlNode* tocRootNode = data->GetNodeElement( );

        //  wxXmlNode* clone = NewNode( albumListNode, tocRootNode->GetName( ) );

        //  Utils::CopyNode( tocRootNode, clone );
        GetAlbumTOCTreeCtrl( )->MakeTree( albumListNode );

        wxXmlNode* catalogListNode = NewNode( root, "CatalogList" );

        tocRootID = GetCatalogTOCTreeCtrl( )->GetRootItem( );

        //TOCTreeItemData* data = ( TOCTreeItemData* ) GetCatalogTOCTreeCtrl( )->GetItemData( tocRootID );

       // wxXmlNode* clone = NewNode( catalogListNode, data->GetName( ) );
        GetCatalogTOCTreeCtrl( )->MakeTree( catalogListNode );

        // Utils::CopyNode( tocRootNode, clone );

        if ( m_ProjectDoc )
        {
            delete m_ProjectDoc;
        }
        m_ProjectDoc = newDoc;


        //       m_ProjectDoc->SetRoot( root );
      //  Utils::XMLDump( m_ProjectDoc );
        m_ProjectDoc->Save( m_projectFilename );



        // //Catalog::CatalogVolume* volumeData = 
        // Catalog::CatalogList* catalogList = GetCatalogData( )->GetCatalogList( );
        // Catalog::CatalogVolumeArray* catalogArray = catalogList->GetCatalogArray( );

        // for ( Catalog::CatalogVolumeArray::iterator it = std::begin( *catalogArray );
        //     it != std::end( *catalogArray );
        //     ++it )
        // {
        //     Catalog::CatalogVolume* volume = ( Catalog::CatalogVolume* ) ( it->second );
        //     wxString filename = volume->GetFilename( );
        //     wxString cwd = wxGetCwd( );
        //     wxFileName sectFile( filename );
        //     sectFile.MakeRelativeTo( cwd );
        //     wxXmlNode* newVolume = NewNode( newNode, "Volume" );
        //     wxString sectFileFullPath = sectFile.GetFullPath( );
        //     newVolume->AddAttribute( "FileName", sectFile.GetFullPath( ) );
        // }


        // wxXmlNode* newNode = NewNode( root, "AlbumList" );
        // Design::AlbumList albumList = GetAlbumData( )->GetAlbumList( );
        // Utils::VolumeArray* albumArray = albumList.GetArray( );

        // for ( Utils::VolumeArray::iterator it = std::begin( *albumArray );
        //     it != std::end( *albumArray );
        //     ++it )
        // {
        //     Design::AlbumVolume* volume = ( Design::AlbumVolume* ) ( it->second );
        //     //newNode->AddAttribute( "FileName", m_designFilename );
        //     wxString filename = volume->GetFilename( );
        //     wxString cwd = wxGetCwd( );
        //     wxFileName sectFile( filename );
        //     sectFile.MakeRelativeTo( cwd );
        //     wxXmlNode* newVolume = NewNode( newNode, "Album" );
        //     newVolume->AddAttribute( "FileName", sectFile.GetFullPath( ) );
        // }



        GetCatalogData( )->FileSave( );
        GetAlbumData( )->FileSave( );

        SetDirty( false );
    }





    // Load the Catalog and Design data then populate trees
    void Project::LoadData( )
    {
        GetCatalogTOCTreeCtrl( )->LoadTree( );;
        GetAlbumTOCTreeCtrl( )->LoadTree( );;

        bool state = wxLog::IsEnabled( );
        //GetCollectionData( )->LoadData( );
        GetCatalogData( )->LoadData( );
        GetAlbumData( )->LoadData( );
        //       GetCatalogData( )->SetCollectionListStrings( );
        //       GetCatalogData( )->SetCollectionListSelection( );
    }

    void Project::FileOpenProject( wxString filename )
    {
        SetProjectFilename( filename );
        wxFileName sptFile( filename );
        wxString path = sptFile.GetPath( );
        wxSetWorkingDirectory( sptFile.GetPath( ) );
        GetSettings( )->SetLastFile( filename );
        LoadProjectXML( );
        LoadData( );
    }

    void Project::FileSaveProject( )
    {

        GetSettings( )->Save( );
        Save( );
    }

    void Project::FileSaveAsProject( wxString filename )
    {
        SetProjectFilename( filename );
        GetSettings( )->SetLastFile( filename );
        FileSaveProject( );
    }

}

