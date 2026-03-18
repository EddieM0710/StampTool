/**
 * @file Image.cpp
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

#include <bitset>
#include <sstream>
#include <iostream>
#include <vector>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/filefn.h> 
#include <wx/wfstream.h>

#include "utils/Project.h"
#include "utils/Image.h"
#include "art/NotFound.xpm"
#include "Defs.h"
#include "utils/Settings.h"
#include "CAPI_Interface.h"

namespace Utils {
  wxString GetCountryCode( wxString imageName )
  {
    wxString ch(  "_" );
    wxString str = imageName.AfterFirst( ch[0] );
    return str.BeforeFirst( ch[0] );
  }
 
    wxString GetImageFullPath( wxString imageName )
    {
        wxString projectPath = GetSettings( )->GetImageDirectory( );
        wxString countryCode = GetCountryCode( imageName );
        projectPath += "\\" + countryCode + "\\" + imageName;
        wxFileName file( projectPath );
        wxString str = file.GetFullPath( );
        file.MakeAbsolute( );
        str = file.GetFullPath( );
        return str;
    }
  //-------

    bool GetAppImage( wxImage &image, wxString filename )
    {
        bool fileOK = false;

        wxString projectPath = GetSettings( )->GetImageDirectory( );
        wxString name = projectPath + "\\" + filename;

        if ( filename.IsEmpty( ) || name.IsEmpty( ) )
        {
            //file missing
            image = wxNullImage;
            fileOK = false;
        }
        else
        {
            if ( ImageExists( name ) )
            {
                //file exists
                image = wxImage( name );
                if ( image.IsOk( ) )
                {
                    //file can be read
                    fileOK = true;   
                }
                else 
                {
                    //file cannot be read
                    image = wxNullImage; ;
                    fileOK = false;    
                }           
            }
            else //image does not exist
            {
                 image = wxImage( NotFound );
                fileOK = false;    
            }
        }
        return fileOK;
    }

    //-------

    bool GetImage( wxImage &image, wxString filename, wxString ColnectItemNbr )
    {
        bool fileOK = false;
        bool reload = false;
        wxString fullPath = GetImageFullPath( filename );
        wxFileName fullFileName( fullPath ) ;
        wxString dirPath = fullFileName.GetPath( );
        wxString name = fullFileName.GetName( );

        if ( filename.IsEmpty( ) || name.IsEmpty( ) )
        {
            image = wxNullImage;
            fileOK = false;
        }
        else
        {
            if ( ImageExists( fullPath ) )
            {
                image = wxImage( fullPath );
                if ( image.IsOk( ) )
                {
                    fileOK = true;   
                }
                else 
                {
                    image = wxNullImage; ;
                    fileOK = false;    
                    reload = true;
                }           
            }
            else //image does not exist
            {
                 image = wxImage( NotFound );
                fileOK = false;    
                reload = true;
            }
        }
        if ( reload && !ColnectItemNbr.IsEmpty( ) )
        {
            CAPI_Interface* client = GetProject( )->GetCAPI_Interface( );

            std::cout << "Utils::GetImage download " << fullPath << " " << ColnectItemNbr <<"\n";
            client->FetchAndDownload( ColnectItemNbr, 
                                       fullPath );
            if ( ImageExists( fullPath ) )
            {
            std::cout << "success Utils::GetImage downloaded " << fullPath<<"\n";
            }
        }
        return fileOK;
    }

    //-------

    bool ImageExists( wxString imageName )
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

    
    wxString MakeImageName( wxString catCode )
    {
        catCode.Trim( true );
        catCode.Trim( false );

        catCode.Replace( ":", "_" );
        catCode.Replace( " ", "_" );
        catCode.Append( ".jpg" );
        return catCode;
    }
}