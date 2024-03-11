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

    //-------

    Project::Project( )
    {
        m_ProjectDoc = ( wxXmlDocument* ) 0;
        m_projectCountryID = GetSettings( )->GetCountryID( );
        m_projectCatalogCode = GetSettings( )->GetCatalogID( );

        m_projectFilename = "";

        m_catalogListNode = 0;
        m_albumListNode = 0;

        m_imageDirectory = wxGetCwd( );
        m_projectFilename = "Undefined.spt";
    }

    //-------

    wxXmlNode* Project::AddNewAlbumVolume( wxString fileName, wxString  volName )
    {
        wxXmlNode* newNode = Utils::NewNode( m_albumListNode, "Volume" );
        newNode->AddAttribute( "FileName", fileName );
        newNode->AddAttribute( "CollapseState", "False" );
        newNode->AddAttribute( "VolumeName", volName );
        return newNode;
    }

    //-------

    wxXmlNode* Project::AddNewCatalogVolume( wxString fileName, wxString  volName )
    {
        wxXmlNode* newNode = Utils::NewNode( m_catalogListNode, "Volume" );
        newNode->AddAttribute( "FileName", fileName );
        newNode->AddAttribute( "CollapseState", "False" );
        newNode->AddAttribute( "VolumeName", volName );
        return newNode;
    }

    //-------

    void Project::CloseProject( )
    {
        if ( m_ProjectDoc )  m_ProjectDoc->~wxXmlDocument( );
        m_catalogListNode = 0;
        m_albumListNode = 0;
        m_projectFilename = "";
        m_outputFilename = "";;
        m_designFilename = "";;
        m_imageDirectory = "";;
    }

    //-------

    bool Project::ContinueIfDirty( wxWindow* parent ){
        if ( IsDirty( ) )
        {
            // query whether to save first 
            wxMessageDialog* dlg = new wxMessageDialog(
                parent,
                wxT( "The current data has been changed but not saved. \n"\
                    "Select \"OK\" to close the file losing the changes.\n"\
                    "Or select \"Cancel\" to quit file open process.\n" ),
                wxT( "2 ! Unsaved modifications.\n" ),
                wxOK | wxCANCEL | wxCENTER );
            int rsp = dlg->ShowModal( );
            if ( rsp == wxID_CANCEL )
            {
                return false;
            }
        }
        return true;
    }

    //-------

    void Project::FileNewProject( wxString sptName )
    {

        //clear catalog volume wxList
        GetCatalogData( )->GetCatalogList( )->Clear( );
        //clear dialog volume list
        GetAlbumData( )->GetAlbumList( ).Clear( );
        //clear catalog tree
        GetCatalogTreeCtrl( )->Clear( );

        //GetAlbumPageTreeCtrl( )->Clear( );
        //clear dialog tree
        GetAlbumTreeCtrl( )->Clear( );

        wxString lastFile = wxGetCwd( );
        lastFile += "/" + sptName;
        GetSettings( )->SetLastFile( lastFile );

        MakeNewProject( sptName );
        LoadData( );
    }

    //-------

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

    //-------

    void Project::FileSaveProject( )
    {

        GetSettings( )->Save( );
        Save( );
    }

    //-------

    void Project::FileSaveAsProject( wxString filename )
    {
        SetProjectFilename( filename );
        GetSettings( )->SetLastFile( filename );
        FileSaveProject( );
    }

    //-------

    // wxString Project::GetDesignFilename( )
    // {
    //     return m_designFilename;
    // };

    //-------

    wxString Project::GetImageDirectory( )
    {
        return m_imageDirectory;
    };

    //-------

    wxString Project::GetImageFullPath( wxString imageName )
    {
        wxString projectPath = GetImageDirectory( );
        projectPath += "/" + imageName;
        wxFileName file( projectPath );
        wxString str = file.GetFullPath( );
        file.MakeAbsolute( );
        str = file.GetFullPath( );
        return str;
    }

    //-------

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

    //-------

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

    //-------

    void Project::InitProject( )
    {
        InitDefs( );
        SetDirty( false );
    }

    // Load the Catalog and Design data then populate trees
    void Project::LoadData( )
    {
        GetCatalogTOCTreeCtrl( )->LoadTree( );;
        GetAlbumTOCTreeCtrl( )->LoadTree( );;

        bool state = wxLog::IsEnabled( );
        //GetCollectionData( )->LoadData( );
        //GetCatalogTreeCtrl( )->LoadCatalogTree( );
        GetCatalogData( )->UpdateCatalogPanels( );
        GetAlbumData( )->LoadData( );
    }

    //-------

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
        if ( m_albumListNode )
        {
            GetAlbumData( )->GetAlbumList( ).AddChild( m_albumListNode );
        }
        else
        {
            m_albumListNode = NewNode( projectRoot, "AlbumList" );
        }

        // Get Mounts
        wxXmlDocument* mountDoc = GetCatalogData( )->LoadMountCSV( );

        // Get Catalogs
        m_catalogListNode = FirstChildElement( projectRoot, "CatalogList" );
        if ( m_catalogListNode )
        {
            GetCatalogData( )->GetCatalogList( )->AddChild( m_catalogListNode );
        }
        else
        {
            m_catalogListNode = NewNode( projectRoot, "CatalogList" );
        }
        GetSettings( )->SetLastFile( m_projectFilename );

        SetDirty( false );
        return true;
    }

    //-------

    void Project::LoadAttributes( wxXmlNode* thisObject )
    {
        const wxXmlAttribute* attr = thisObject->GetAttributes( );
        wxFileName filename;
        while ( attr )
        {
            wxString name = attr->GetName( );
            wxString val = attr->GetValue( );

            if ( !name.Cmp( "ImagePath" ) )
            {
                m_imageDirectory = MakeFileAbsolute( val );
                SetImageDirectory( m_imageDirectory );
            }
            else if ( !name.Cmp( "Country" ) )
            {
                m_projectCountryID = val;
            }
            else if ( !name.Cmp( "CatalogCode" ) )
            {
                m_projectCatalogCode = val;
            }
            attr = attr->GetNext( );
        }
    }

    //-------
    // Make a new default project
    void  Project::MakeNewProject( wxString fileName )
    {
        m_projectCountryID = GetSettings( )->GetCountryID( );
        m_projectCatalogCode = GetSettings( )->GetCatalogID( );

        m_imageDirectory = wxGetCwd( );
        m_projectFilename = fileName;

        m_ProjectDoc = MakeDefaultProjectDocument( );

        wxXmlNode* root = m_ProjectDoc->GetRoot( );

        m_albumListNode = FirstChildElement( root, "AlbumList" );

        // add the entries of the allbum TOC
        GetAlbumTOCTreeCtrl( )->MakeTree( m_albumListNode );

        m_catalogListNode = FirstChildElement( root, "CatalogList" );

        // add the entries of the catalog TOC
        GetCatalogTOCTreeCtrl( )->MakeTree( m_catalogListNode );

    }
    wxXmlDocument* Project::MakeDefaultProjectDocument( )
    {
        wxXmlDocument* newDoc = new wxXmlDocument( );

        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Project" );
        newDoc->SetRoot( root );
        root->AddAttribute( "Country", GetSettings( )->GetCountryID( ) );
        root->AddAttribute( "CatalogCode", GetSettings( )->GetCatalogID( ) );
        root->AddAttribute( "ImagePath", wxGetCwd( ) );

        wxXmlNode* albumListNode = NewNode( root, "AlbumList" );

        wxXmlNode* catalogListNode = NewNode( root, "CatalogList" );
        return newDoc;
    }

    //-------

    wxString Project::MakeFileAbsolute( wxString filename )
    {
        wxFileName newFile( filename );
        if ( !newFile.IsAbsolute( ) )
        {
            newFile.MakeAbsolute( );
        }
        return newFile.GetFullPath( );
    }

    //-------

    void Project::Save( )
    {

        if ( m_projectFilename.IsEmpty( ) )
        {
            //query for valid filename
            m_projectFilename = "UndefinedName.spt";
        }


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
        wxXmlDocument* newDoc = MakeDefaultProjectDocument( );

        wxXmlNode* root = newDoc->GetRoot( );

        // set curr vals
        SetAttrStr( root, "Country", GetProjectCountryID( ) );
        SetAttrStr( root, "CatalogCode", GetProjectCatalogCode( ) );
        SetAttrStr( root, "ImagePath", m_imageDirectory );

        wxXmlNode* albumListNode = FirstChildElement( root, "AlbumList" );

        // add the entries of the allbum TOC
        GetAlbumTOCTreeCtrl( )->MakeTree( albumListNode );

        wxXmlNode* catalogListNode = FirstChildElement( root, "CatalogList" );

        // add the entries of the catalog TOC
        GetCatalogTOCTreeCtrl( )->MakeTree( catalogListNode );

        if ( m_ProjectDoc )
        {
            delete m_ProjectDoc;
        }
        m_ProjectDoc = newDoc;

        // save the new project file
        m_ProjectDoc->Save( m_projectFilename );

        // then save all the catalogs and albums
        GetCatalogData( )->FileSave( );
        GetAlbumData( )->FileSave( );

        SetDirty( false );
    }

    //-------

    void Project::SetProjectCountryID( wxString str ) {
        if ( str.Cmp( m_projectCountryID ) )
        {
            m_projectCountryID = str;
            m_dirty = true;
        }
    };

    //-------

    void Project::SetProjectCatalogCode( wxString str )
    {
        if ( str.Cmp( m_projectCatalogCode ) )
        {
            m_projectCatalogCode = str;
            m_dirty = true;
        }
    };

    //-------

    void Project::SetCaption( )
    {
        StampToolFrame* frame = GetFrame( );
        if ( frame )
        {
            GetSettings( )->SetLastFile( m_projectFilename );
            frame->SetCaption( GetSettings( )->GetLastFile( ) );
        }
    }

    //-------

    void Project::SetImageDirectory( wxString imagePath )
    {
        if ( imagePath.Cmp( m_imageDirectory ) )
        {
            m_imageDirectory = imagePath;
            m_dirty = true;
        }
    };

    //-------

    // void Project::SetDesignFilename( wxString albumFilename )
    // {
    //     m_designFilename = albumFilename;
    //     m_dirty = true;
    // };

    //-------


    void Project::SetProjectFilename( wxString name )
    {
        m_projectFilename = name;
        GetSettings( )->SetLastFile( m_projectFilename );
        SetCaption( );

    };

    //-------


}

