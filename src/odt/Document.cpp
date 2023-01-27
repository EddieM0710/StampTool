/* 
 * @file Document.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
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
#include "odt/Document.h"

#include <wx/filename.h>
#include <wx/filefn.h>
#include "design/DesignData.h"
#include "utils/Project.h"
#include "utils/Settings.h"

#include <iostream>
#include <fstream>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

namespace ODT { 

    //***********************************
    Document::Document(  )
    { 
    };

    //**********************************

    void Document::AddBorder( wxString filename )    
    { 
        wxString docImage = AddImageFile( filename );
        wxString width;
        wxString height;
        wxString topMargin;
        wxString bottomMargin;
        wxString rightMargin;
        wxString leftMargin;
        Design::Album *album = GetDesignData( )->GetAlbum( ) ;
        album->GetPageParameters( width, height, topMargin, bottomMargin, rightMargin, leftMargin );
        width.append( "in" );
        height.append( "in" );
        topMargin.append( "in" );
        bottomMargin.append( "in" );
        rightMargin.append( "in" );
        leftMargin.append( "in" );
        // m_stylesDoc->AddBorderStyle( docImage, width, height, topMargin, bottomMargin, rightMargin, leftMargin  );
    }

    //***********************************
    wxString Document::AddImageFile( wxString filename )
    { 

        wxFileName inputImage(  filename );

        wxFileName destImage( "Pictures", inputImage.GetFullName( ) );
    //    std::cout << " destImage.GetFullPath( ):" << destImage.GetFullPath( ) << "\n";
    //    std::cout << " inputImage.GetFullName( ):" << inputImage.GetFullName( ) << "\n";
    //    std::cout << " ODTDoc( )->GetPicturesDir( ):" << ODTDoc( )->GetPicturesDir( ) << "\n";

        wxString destFullPath = ODTDoc( )->GetPicturesDir( ) + inputImage.GetFullName( );
    //    std::cout << " destFullPath:" << destFullPath << "\n";

        bool state = wxCopyFile( inputImage.GetFullPath( ), destFullPath );
        
      //  wxCopyFile( inputImage.GetFullPath( ), destImage.GetFullPath( ) );
        ManifestDoc( )->AddManifestFileEntry( destImage.GetFullPath( ), GetMimeType( filename ) );

        //StylesDoc( )->AddDrawFillImage( inputImage.GetFullName( ), destImage.GetFullPath( ), "simple", "embed", "onLoad" );

        return destImage.GetFullPath( );
    }

    //***********************************

    bool Document::AddODTFile( wxZipOutputStream& zip, wxString inputFileName, wxString zippedFileName )
    { 



        zip.PutNextEntry( zippedFileName );

        char buf[ 4096 ];

        wxFileInputStream l_file( inputFileName );
        //   zip << l_file;
        if ( l_file.IsOk( ) )
        { 
            bool ok;
            ok = l_file.ReadAll( buf, 4096 );
            int lastRead = l_file.LastRead( );
            while ( lastRead > 0 )
            { 
                zip.Write( buf, lastRead );
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
        zip.CloseEntry( );
        return true;
    }


    void Document::MakeDocument( )
    { 
        SaveFiles( );
        MakeODT( );
    }

    bool Document::InitODTFiles( )
    { 

        if ( CreateTempDocumentDirectory( ) )
        { 
            if ( CreateDocFiles( ) )
            { 
                wxString drawName = StylesDoc( )->AddBackgroundImage( GetDesignData( )->GetAlbum( )->GetBorderFileName( ) );
                ContentDoc( )->AddPageBackgroundFrameStyles( drawName );
                ContentDoc( )->AddPageFrameStyles( );

                //            AddBorder( m_parent->GetAlbum( )->GetBorderFileName( ) );
                return true;
            }
        }
        return false;
    };


    //***********************************


    bool Document::CreateDocFiles( )
    { 

        m_mimeTypeDoc = new MimeType( );

        m_contentDoc = new Content( );

        m_manifestDoc = new Manifest( );

        m_metaDoc = new Meta( );

        m_settingsDoc = new Settings( );

        m_stylesDoc = new Styles( );

        return true;
    }

    //***********************************


    bool Document::CreateTempDocumentDirectory( )
    { 

        wxString workingDir = wxGetCwd( );

        wxFileName m_tmpDir( ".tmp/" );
        m_tmpDir.MakeRelativeTo( workingDir );
        std::cout << "m_tmpDir " << m_tmpDir.GetFullPath( ) << "\n";
        if ( !m_tmpDir.DirExists(  ) )
        { 
            if ( !m_tmpDir.Mkdir(  ) )
            { 
                //Unable to create Temp .StampStampTool Directory
                ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp .StampStampTool Directory" );
                return false;
            }
        }

        m_stampStampTool = m_tmpDir;
        m_stampStampTool.AppendDir( "StampStampTool" );
        std::cout << "m_stampStampTool " << m_stampStampTool.GetFullPath( ) << "\n";
        if (  !m_stampStampTool.DirExists(  )  )
        { 
            if ( !m_stampStampTool.Mkdir(  ) )
            {            
                // unable to set working directory to /tmp/.StampStampTool
                ReportError( "Document::CreateTempDocumentDirectory", "unable to set working directory to /tmp/.StampStampTool" );
                return false;
            }
        }

        m_docFiles = m_stampStampTool;
        m_docFiles.AppendDir( "DocFiles" );
        std::cout << "m_docFiles " << m_docFiles.GetFullPath( ) << "\n";
        if ( m_docFiles.DirExists( ) )
        { 
            //if DocFiles exists then clobber it to get rid of extraneous stuff
            if ( !m_docFiles.Rmdir( wxPATH_RMDIR_RECURSIVE ) )
            { 
                // unable to remove /tmp/.StampStampTool/DocFiles
                ReportError( "Document::CreateTempDocumentDirectory", "unable to remove /tmp/.StampStampTool/DocFiles" );
                return false;
            }
        }
        if ( !m_docFiles.Mkdir(  ) )
        { 
            //Unable to create TempFile Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create TempFile Directory" );
            return 0;
        }

        m_thumbnailsDir = m_docFiles;
        m_thumbnailsDir.AppendDir( "Thumbnails" );
        std::cout << "m_thumbnailsDir " << m_thumbnailsDir.GetFullPath( ) << "\n";
        wxString str = m_thumbnailsDir.GetFullPath( );
        if ( !m_thumbnailsDir.Mkdir(  ) )
        { 
            //Unable to create Temp Thumbnails Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp Thumbnails Directory" );
            return 0;
        }

        m_metaInfDir = m_docFiles;
        m_metaInfDir.AppendDir( "META-INF" );
        std::cout << "m_metaInfDir " << m_metaInfDir.GetFullPath( ) << "\n";
        if ( !m_metaInfDir.Mkdir( ) )
        { 
            //Unable to create Temp META-INF Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp META-INF Directory" );
            return 0;
        }

        m_configurations2Dir = m_docFiles;
        m_configurations2Dir.AppendDir( "Configurations2" );
        if ( !m_configurations2Dir.Mkdir( ) )
        { 
            //Unable to create Temp Configurations2 Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp Configurations2 Directory" );
            return 0;
        }

        m_picturesDir = m_docFiles;
        m_picturesDir.AppendDir( "Pictures" );
        std::cout << "m_picturesDir " << m_picturesDir.GetFullPath( ) << "\n";
        if ( !m_picturesDir.Mkdir(  ) )
        { 
            //Unable to create Temp Pictures Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp Pictures Directory" );
            return 0;
        }
        return true;
    }

    //***********************************


    int Document::GetFileList( wxArrayString& fileArray, wxString searchStr, int flag )
    { 
        fileArray.Clear( );
 
        wxString f = wxFindFirstFile( searchStr, flag );
        while ( f.Length( ) > 0 )
        { 
            wxFileName filename( f );
            fileArray.Add( filename.GetFullPath( ) );
            f = wxFindNextFile( );
        }
        return fileArray.Count( );
    }

    //***********************************


    bool Document::MakeODT( )
    { 
        wxString workingDir = wxGetCwd( );
        wxString doc = GetProject( )->GetODTOutputFilename( );
        //wxString doc = ODTDoc( )->GetAlbum( )->GetDocName( );
        wxFileName* outputName = new wxFileName( doc );
        wxFileName outputZipName = *outputName;
        outputZipName.SetExt( wxT( "zip" ) );
        wxFFileOutputStream out( outputZipName.GetFullPath( ) );
        wxZipOutputStream zip( out );
        wxTextOutputStream txt( zip );
        wxString sep( wxFileName::GetPathSeparator( ) );

        wxArrayString fileArray;

        // Save files first
        wxString docFilesDir = GetDocFilesDir( ) ;
        int nbrFiles = GetFileList( fileArray, docFilesDir, wxFILE );
        for ( int i = 0; i < nbrFiles; i++ )
        { 
                    wxFileName zipName( fileArray.Item( i ) );
                    zipName.MakeRelativeTo( docFilesDir );
                    AddODTFile( zip, fileArray.Item( i ), zipName.GetFullPath( )  );
        }

        //then zip the directories
        wxArrayString dirArray;
        int nbrDirs = GetFileList( dirArray, docFilesDir, wxDIR );

        for ( int i = 0; i < nbrDirs; i++ )
        { 

            wxString str = dirArray.Item( i ) + sep + wxT( "*.*" );
            wxFileName zipName( dirArray.Item( i )  );
            zipName.MakeRelativeTo( docFilesDir );
            zip.PutNextDirEntry( zipName.GetFullPath( ) );
            nbrFiles = GetFileList( fileArray, str, wxFILE );
            if ( nbrFiles > 0 )
            { 
                for ( int j = 0; j < nbrFiles; j++ )
                { 

                    wxFileName zipName( fileArray.Item( j ) );
                    zipName.MakeRelativeTo( docFilesDir );
                    AddODTFile( zip, fileArray.Item( j ), zipName.GetFullPath( ) );
                }
            }
        }

        zip.Close( );
        wxRenameFile( outputZipName.GetFullPath( ), outputName->GetFullPath( ) );
        return true;
    }

    //***********************************


    wxString Document::MakeAbsolute( wxString file )
    { 
        wxFileName inFile;
        wxString str = file;
        inFile.Assign( str );
        inFile.MakeAbsolute( );
        str = inFile.GetFullPath( );
        return str;
    }

    //***********************************


    bool Document::SaveFiles( )
    { 
        m_mimeTypeDoc->Save( );

        m_contentDoc->Save( );

        m_manifestDoc->Save( );

        m_metaDoc->Save( );

        m_settingsDoc->Save( );

        m_stylesDoc->Save( );

        return true;
    }


}
