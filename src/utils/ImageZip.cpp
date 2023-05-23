/**
 * @file Font.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright ( c ) 2022
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
#include <wx/datstrm.h>

#include "utils/ImageZip.h"
#include "design/AlbumVolume.h"
#include "gui/GuiUtils.h"

namespace Utils {

    void ImageZip::InitZipOutFile( wxString zipOutFullName )
    {

    }

    void ImageZip::CopyFileToZip( wxString file, bool flat )
    {
        if ( !file.IsEmpty( ) )
        {
            if ( wxFileExists( file ) )
            {
                if ( flat )
                {
                    wxFileName FN( file );
                    wxString entryName = FN.GetName( ) + "." + FN.GetExt( );
                    wxZipEntry entry( entryName );
                    m_zipOut->PutNextEntry( &entry );
                }
                else
                {
                    m_zipOut->PutNextEntry( file );

                }
                // wxFFileInputStream inStream( file );
                // // wxDataInputStream dataIn( inStream );
                // const static int BUF_SIZE = 4096;
                // wxUint8 buf[ BUF_SIZE ];
                // do {
                //     inStream.Read( &buf[ 0 ], BUF_SIZE );      // Read at most n bytes into
                //     m_imageOut->Write8( buf, inStream.LastRead( ) );
                // } while ( inStream.LastRead( ) > 0 );


                //     //zip.PutNextEntry( zippedFileName );

                // char buf[ 4096 ];

                // wxFileInputStream l_file( file );
                // //   zip << l_file;
                // if ( l_file.IsOk( ) )
                // {
                //     bool ok;
                //     ok = l_file.ReadAll( buf, 4096 );
                //     int lastRead = l_file.LastRead( );
                //     while ( lastRead > 0 )
                //     {
                //         if ( m_zipOut->IsOk( ) )
                //         {
                //             m_zipOut->Write( buf, lastRead );
                //             if ( ok )
                //             {
                //                 ok = l_file.ReadAll( buf, 4096 );
                //                 lastRead = l_file.LastRead( );
                //             }
                //             else
                //             {
                //                 lastRead = 0;
                //             }
                //         }
                //         else
                //         {
                //             lastRead = 0;
                //         }
                //     }

                // }


        //zip.PutNextEntry( zippedFileName );

                char buf[ 4096 ];

                wxFileInputStream l_file( file );
                //   zip << l_file;
                if ( l_file.IsOk( ) )
                {
                    bool ok;
                    ok = l_file.ReadAll( buf, 4096 );
                    int lastRead = l_file.LastRead( );
                    while ( lastRead > 0 )
                    {
                        m_zipOut->Write( buf, lastRead );
                        if ( ok )
                        {
                            ok = l_file.ReadAll( buf, 4096 );
                            lastRead = l_file.LastRead( );
                        }
                        else
                        {
                            lastRead = 0;
                        }
                    }

                }
                m_zipOut->CloseEntry( );
                //return true;
            }
        }
    }
}

// bool Document::AddODTFile( wxZipOutputStream& zip, wxString inputFileName, wxString zippedFileName )
// {



//     zip.PutNextEntry( zippedFileName );

//     char buf[ 4096 ];

//     wxFileInputStream l_file( inputFileName );
//     //   zip << l_file;
//     if ( l_file.IsOk( ) )
//     {
//         bool ok;
//         ok = l_file.ReadAll( buf, 4096 );
//         int lastRead = l_file.LastRead( );
//         while ( lastRead > 0 )
//         {
//             zip.Write( buf, lastRead );
//             if ( ok )
//             {
//                 ok = l_file.ReadAll( buf, 4096 );
//                 lastRead = l_file.LastRead( );
//             }
//             else
//             {
//                 lastRead = 0;
//             }
//         }

//     }
//     zip.CloseEntry( );
//     return true;
// }


// bool Document::MakeODT( wxString outputZipName )
// {

//     wxFFileOutputStream out( outputZipName );
//     wxZipOutputStream zip( out );
//     wxTextOutputStream txt( zip );

//     wxArrayString fileArray;

//     // Save files first
//     wxString docFilesDir = GetDocFilesDir( );
//     int nbrFiles = GetFileList( fileArray, docFilesDir, wxFILE );
//     for ( int i = 0; i < nbrFiles; i++ )
//     {
//         wxFileName zipName( fileArray.Item( i ) );
//         zipName.MakeRelativeTo( docFilesDir );
//         AddODTFile( zip, fileArray.Item( i ), zipName.GetFullPath( ) );
//     }


//     zip.Close( );
//     wxRenameFile( outputZipName.GetFullPath( ), outputName->GetFullPath( ) );
//     return true;
// }