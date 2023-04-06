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

#include "utils/Project.h"

#include "Defs.h"
#include "utils/Settings.h"

#include "catalog/CatalogData.h"
#include "catalog/CatalogSectionData.h"
#include "design/DesignDefs.h"
#include "design/DesignData.h"
#include "design/AlbumBase.h"

#include "gui/CatalogTreeCtrl.h"
#include "gui/DesignTreeCtrl.h"


namespace Utils {

    Project* NewProjectInstance( )
    {
        Project* project = new Project( );
        project->InitProject( );
        return project;
    }

    Project::Project( )
    {
        m_ProjectDoc = ( wxXmlDocument* ) 0;
    }
    void Project::InitProject( )
    {
        InitDefs( );
        SetDirty( false );
    }

    //***** 

    wxString Project::GetDesignFilename( )
    {
        return m_designFilename;
    };

    //*****

    void Project::SetDesignFilename( wxString albumFilename )
    {
        m_designFilename = albumFilename;
        m_dirty = true;
    };

    //*****

    wxString Project::GetImagePath( )
    {
        return m_imagePath;
    };

    //*****

    void Project::SetImagePath( wxString imagePath )
    {
        m_imagePath = imagePath; SetDirty( );
    };

    //*****

    // wxString Project::GetCatalogFilename( )
    // { 
    //     return m_catalogFilename;
    // };

    //*****

    void Project::SetCatalogFilename( wxString catalogFilename )
    {
        if ( m_catalogFilename.Cmp( catalogFilename ) )
        {
            m_catalogFilename = catalogFilename;
            SetDirty( );
        }
    };

    //*****

    void Project::SetProjectFilename( wxString name )
    {
        m_projectFilename = name;
        GetSettings( )->SetLastFile( m_projectFilename );
    };

    //*****

    wxString Project::MakeFileAbsolute( wxString filename )
    {
        wxFileName newFile( filename );
        if ( !newFile.IsAbsolute( ) )
        {
            newFile.MakeAbsolute( );
        }
        return newFile.GetFullPath( );
    }



    //*****

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
        if ( !m_ProjectDoc->Load( m_projectFilename ) )
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


        wxXmlNode* album = FirstChildElement( projectRoot, "Album" );
        if ( album )
        {
            m_designFilename = album->GetAttribute( "FileName" );
        }
        wxXmlNode* imagePath = FirstChildElement( projectRoot, "ImagePath" );
        if ( imagePath )
        {
            m_imagePath = imagePath->GetAttribute( "Name" );
        }
        wxXmlNode* catalog = FirstChildElement( projectRoot, "Catalog" );
        Catalog::CatalogData* catalogData = GetToolData( )->GetCatalogData( );

        catalogData->ClearCatalogArray( );
        if ( catalog )
        {
            wxXmlNode* section = FirstChildElement( catalog, "Section" );
            if ( !section )
            {
                section = FirstChildElement( catalog, "Volume" );
            }
            while ( section )
            {
                wxString name = section->GetAttribute( "FileName" );

                wxFileName catFile( name );

                if ( catFile.FileExists( ) )
                {

                    if ( catFile.IsAbsolute( ) )
                    {
                        catFile.MakeRelativeTo( cwd );
                    }

                    Catalog::CatalogSectionData* sectionData = GetToolData( )->NewCatalogSectionData( );

                    sectionData->SetSectionFilename( catFile.GetFullPath( ) );
                }
                else
                {

                }

                section = section->GetNext( );
            }
        }

        GetSettings( )->SetLastFile( m_projectFilename );

        SetDirty( false );
        return true;
    }



    //*****

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
                //m_imagePath = MakeFileAbsolute( val );
                //GetSettings( )->SetImageDirectory( m_imagePath );
            }
            else if ( !name.Cmp( "Catalog" ) )
            {
                m_catalogFilename = MakeFileAbsolute( val );
            }
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


    //*****

    void Project::Save( )
    {

        if ( wxFileExists( m_projectFilename ) )
        {
            wxFileName bakFile( m_projectFilename );
            bakFile.SetExt( "bak" );
            wxRenameFile( m_projectFilename, bakFile.GetFullName( ), true );
        }
        if ( m_ProjectDoc )
        {
            delete m_ProjectDoc;
        }
        m_ProjectDoc = new wxXmlDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, "Project" );
        root->AddAttribute( "Country", GetProjectCountryID( ) );
        root->AddAttribute( "CatalogCode", GetProjectCatalogCode( ) );

        wxXmlNode* newNode = NewNode( root, "OutputName" );
        //       newNode->AddAttribute( "FileName", m_outputFilename );

        newNode = NewNode( root, "Album" );
        newNode->AddAttribute( "FileName", m_designFilename );

        newNode = NewNode( root, "ImagePath" );
        newNode->AddAttribute( "Name", m_imagePath );

        newNode = NewNode( root, "Catalog" );
        //Catalog::CatalogSectionData* sectionData = 
        Catalog::CatalogData* catalogData = GetToolData( )->GetCatalogData( );
        Catalog::CatalogSectionDataArray* catalogArray = catalogData->GetCatalogArray( );

        for ( Catalog::CatalogSectionDataArray::iterator it = std::begin( *catalogArray );
            it != std::end( *catalogArray );
            ++it )
        {
            Catalog::CatalogSectionData* section = ( Catalog::CatalogSectionData* ) ( *it );
            wxString filename = section->GetSectionFilename( );
            wxString cwd = wxGetCwd( );
            wxFileName sectFile( filename );
            sectFile.MakeRelativeTo( cwd );
            wxXmlNode* newSection = NewNode( newNode, "Section" );
            newSection->AddAttribute( "FileName", sectFile.GetFullPath( ) );
        }
        m_ProjectDoc->SetRoot( root );

        m_ProjectDoc->Save( m_projectFilename );

        GetToolData( )->FileSaveCatalog( );
        GetToolData( )->FileSaveDesign( );

        SetDirty( false );
    }

}