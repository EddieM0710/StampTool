/**
 * @file Volume.cpp
 * @author Eddie Monroe ( )
 * @brief
 * @version 0.1
 * @date 2021-02-25
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

 //#include <iostream>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/wfstream.h>
#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/msgdlg.h>


#include "utils/Volume.h"

#include "Defs.h"


#include "utils/XMLUtilities.h"
#include "gui/StampToolFrame.h"
#include "gui/AppData.h"


namespace Utils
{



    Volume::Volume( wxString type )
    {
        m_type = type;
        m_doc = 0;
    }

    Volume::~Volume( )
    {
        delete m_doc;
    }


    wxString Volume::GetPath( )
    {
        wxString filename = GetFilename( );
        wxFileName FN( filename );
        FN.MakeAbsolute( );
        return FN.GetPath( );
    }

    wxString Volume::GetBaseName( )
    {
        wxString filename = GetFilename( );
        wxFileName FN( filename );
        return FN.GetName( );
    }

    wxString Volume::GetName( )
    {
        wxXmlNode* root = m_doc->GetRoot( );
        if ( root )
        {
            return Utils::GetAttrStr( root, "Name" );
        }
        return "";
    };
    void Volume::Load( )
    {
        LoadXML( );
        wxString name = GetName( );
        if ( !name.IsEmpty( ) )
        {
            name = GetFilename( );
            wxFileName fn( name );
            SetName( fn.GetName( ) );
        }
    }

    void Volume::LoadXML( )
    {

        bool ok = false;
        if ( m_filename.length( ) > 0 )
        {
            if ( !m_doc )
            {
                m_doc = NewDocument( );
            }
            wxString cwd = wxGetCwd( );
            wxFileInputStream stream( m_filename );
            if ( !stream.IsOk( ) )
            {
                wxString txt = wxString::Format( "%s Stream Create Failed.\n\n", m_filename );
                wxMessageDialog* dlg = new wxMessageDialog(
                    GetFrame( ), txt,
                    wxT( "Warning! Stream Create Failed.\n" ),
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }

            if ( !m_doc->Load( stream ) )
            {
                int err = stream.GetLastError( );
                wxString txt = wxString::Format( "\n%s Stream  Failed. Error: %d\n\n.", m_filename, err );
                wxMessageDialog* dlg = new wxMessageDialog(
                    GetFrame( ), txt,
                    wxT( "Warning! Stream Load Failed.\n" ),
                    wxOK | wxCANCEL | wxCENTER );
                int rsp = dlg->ShowModal( );
                return;
            }
        }
        else
        {
            // this creates an empty document
            if ( !m_doc )
            {
                m_doc = NewDocument( );
            }
            wxXmlNode* Volume = m_doc->GetRoot( );
            if ( Volume )
            {
                wxString name = Volume->GetName( );

                if ( name.Length( ) == 0 )
                {
                    Volume->SetName( m_filename );
                }
            }
        }

        SetDirty( false );
    }


    bool  Volume::operator>( Volume* rhs )
    {
        if ( GetName( ).Cmp( rhs->GetName( ) ) > 0 )
        {
            return true;
        }
        return false;
    }

    bool  Volume::operator<( Volume* rhs )
    {
        if ( GetName( ).Cmp( rhs->GetName( ) ) > 0 )
        {
            return false;
        }
        return true;
    }

    wxXmlDocument* Volume::NewDocument( )
    {
        delete m_doc;
        m_doc = new wxXmlDocument( );
        wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, m_type );
        m_doc->SetRoot( root );
        return m_doc;
    };

    wxXmlDocument* Volume::ReplaceDocument( wxXmlDocument* doc )
    {
        delete m_doc;
        m_doc = doc;
        return m_doc;
    };

    void Volume::Save( )
    {
        wxString filename = m_filename;
        if ( wxFileExists( filename ) )
        {
            wxFileName bakFile( filename );
            bakFile.SetExt( "bak" );
            wxRenameFile( filename, bakFile.GetFullPath( ), true );
        }
        m_doc->Save( filename );
        SetDirty( false );
    }

    void Volume::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetAppData( )->SetDirty( true );
        }
    }


    void Volume::SetName( wxString str )
    {
        wxXmlNode* root = m_doc->GetRoot( );
        if ( root )
        {
            Utils::SetAttrStr( root, "Name", str );
        }
    };
}