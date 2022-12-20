/**
 * @file Project.cpp
 * @author Eddie Monroe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 *
 */

 // For compilers that support precompilation, includes "wx/wx.h".
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
#include <wx/filename.h>


#include "utils/Project.h"

#include "Defs.h"
#include "utils/Settings.h"

#include "catalog/CatalogData.h"
#include "design/DesignDefs.h"
#include "design/DesignData.h"
#include "design/AlbumBase.h"

#include "gui/CatalogTreeCtrl.h"
#include "gui/DesignTreeCtrl.h"


namespace Utils {

    Project* NewProjectInstance()
    {
        Project* project = new Project();
        project->InitProject();
        return project;
    }

    Project::Project( )
    {
        m_ProjectDoc = (wxXmlDocument*)0;
    }
    void Project::InitProject()
    {
        InitDefs( );
        SetDirty( false );
    }

    //*****

    wxString Project::GetODTOutputFilename( )
    {
        return m_ODTOutputFilename;
    }

    //***** 

    void Project::SetODTOutputFilename( wxString outputFilename )
    {
        m_ODTOutputFilename = outputFilename;
        m_dirty = true;
    }


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

    wxString Project::GetCatalogFilename( )
    {
        return m_catalogFilename;
    };

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
            std::cout << "Initial node must be <Project>"
                << "\n";
            std::cout << "Found \"" << name << "\" instead.\n";
            return false;
        }
        LoadAttributes( projectRoot );

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
                m_ODTOutputFilename = MakeFileAbsolute( val );
            }
            else if ( !name.Cmp( "Album" ) )
            {
                m_designFilename = MakeFileAbsolute( val );
            }
            else if ( !name.Cmp( "ImagePath" ) )
            {
                m_imagePath =  MakeFileAbsolute( val ) ;
                GetSettings( )->SetImageDirectory( m_imagePath );
            }
            else if ( !name.Cmp( "Catalog" ) )
            {
                m_catalogFilename = MakeFileAbsolute( val );
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

        root->AddAttribute( "OutputName", m_ODTOutputFilename );
        root->AddAttribute( "Album", m_designFilename );
        root->AddAttribute( "ImagePath", m_imagePath );
        root->AddAttribute( "Catalog", m_catalogFilename );

        m_ProjectDoc->SetRoot( root );

        m_ProjectDoc->Save( m_projectFilename );

        SetDirty( false );
    }

}