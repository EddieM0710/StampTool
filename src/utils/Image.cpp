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

#include <iostream>
#include <vector>
#include <wx/filename.h>
#include <wx/filefn.h> 
#include <wx/wfstream.h>

#include "utils/Project.h"
#include "utils/Image.h"
#include "art/NotFound.xpm"
#include "Defs.h"
#include "utils/Settings.h"
#include "imagefetch/ColnectWxClient.h"

namespace Utils {
 
    wxString GetImageFullPath( wxString imageName )
    {
        wxString projectPath = GetProject( )->GetImageDirectory( );
        projectPath += "/" + imageName;
        wxFileName file( projectPath );
        wxString str = file.GetFullPath( );
        file.MakeAbsolute( );
        str = file.GetFullPath( );
        return str;
    }

    //-------

    bool GetImage( wxString filename, wxImage &image, wxString ColnectItemNbr )
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
            ColnectWxClient* client = new ColnectWxClient( );

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