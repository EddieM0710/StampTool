#include "odt/Document.h"

#include <wx/filename.h>
#include <wx/filefn.h>
#include "album/AlbumData.h"
//#include "DocumentManager.h"

#include <iostream>
#include <fstream>
#include <wx/wfstream.h>

namespace ODT {

    //***********************************
    Document::Document( DocumentManager* parent )
    {
        m_parent = parent;
        m_workingDirectory = wxGetCwd( );
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
        m_parent->GetAlbum( )->GetPageParameters( width, height, topMargin, bottomMargin, rightMargin, leftMargin );
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
        wxString imageLoc = m_parent->GetAlbum( )->GetImagePath( );
        wxFileName inputImage( imageLoc, filename );
        bool status = inputImage.MakeAbsolute( m_workingDirectory );
        wxString i_cwd = inputImage.GetCwd( );

        wxString i_fullPath = inputImage.GetFullPath( );

        wxFileName docImage( "Pictures", filename );
        wxString d_cwd = docImage.GetCwd( );

        wxString d_fullPath = docImage.GetFullPath( );
        std::cout << "d_cwd:" << d_cwd << " d_fullPath:" << d_fullPath << "\n";

        wxCopyFile( inputImage.GetFullPath( ), docImage.GetFullPath( ) );
        ManifestDoc( )->AddManifestFileEntry( docImage.GetFullPath( ), GetMimeType( filename ) );
        return docImage.GetFullPath( );
    }

    //***********************************

    bool Document::AddODTFile( wxZipOutputStream& zip, wxString f )
    {

        zip.PutNextEntry( f );

        char buf[ 4096 ];

        wxFileInputStream l_file( f );
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
                ContentDoc( )->AddPageFrameStyles( );
                //            AddBorder( m_parent->GetAlbum()->GetBorderFileName() );
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

        if ( !wxSetWorkingDirectory( "/tmp" ) )
        {
            // unable to set working director to /tmp
            ReportError( "Document::CreateTempDocumentDirectory", "unable to set working director to /tmp" );

            return false;
        }
        wxString workingDir = wxGetCwd( );
        if ( !wxDirExists( ".StampAlbumGen" ) )
        {
            if ( !wxFileName::Mkdir( ".StampAlbumGen" ) )
            {
                //Unable to create Temp .StampAlbumGen Directory
                ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp .StampAlbumGen Directory" );
                return false;
            }
        }
        if ( !wxSetWorkingDirectory( ".StampAlbumGen" ) )
        {
            // unable to set working directory to /tmp/.StampAlbumGen
            ReportError( "Document::CreateTempDocumentDirectory", "unable to set working directory to /tmp/.StampAlbumGen" );
            return false;
        }
        if ( wxDirExists( "DocFiles" ) )
        {
            //if DocFiles exists then clobber it to get rid of extraneous stuff
            if ( !wxFileName::Rmdir( "DocFiles", wxPATH_RMDIR_RECURSIVE ) )
            {
                // unable to remove /tmp/.StampAlbumGen/DocFiles
                ReportError( "Document::CreateTempDocumentDirectory", "unable to remove /tmp/.StampAlbumGen/DocFiles" );
                return false;
            }
        }
        if ( !wxFileName::Mkdir( "DocFiles" ) )
        {
            //Unable to create TempFile Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create TempFile Directory" );
            return 0;
        }
        if ( !wxSetWorkingDirectory( "DocFiles" ) )
        {
            //Unable to set Working directory to /tmp/.StampAlbumGen/DocFiles
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to set Working directory to /tmp/.StampAlbumGen/DocFiles" );
            return 0;
        }
        if ( !wxFileName::Mkdir( "Thumbnails" ) )
        {
            //Unable to create Temp Thumbnails Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp Thumbnails Directory" );
            return 0;
        }
        if ( !wxFileName::Mkdir( "META-INF" ) )
        {
            //Unable to create Temp META-INF Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp META-INF Directory" );
            return 0;
        }
        if ( !wxFileName::Mkdir( "Configurations2" ) )
        {
            //Unable to create Temp Configurations2 Directory
            ReportError( "Document::CreateTempDocumentDirectory", "Unable to create Temp Configurations2 Directory" );
            return 0;
        }
        if ( !wxFileName::Mkdir( "Pictures" ) )
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
            fileArray.Add( f );
            f = wxFindNextFile( );
        }
        return fileArray.Count( );
    }

    //***********************************


    bool Document::MakeODT( )
    {
        wxString workingDir = wxGetCwd( );
        wxString doc = GetProject( )->GetOutputName( );
        //wxString doc = ODTDoc()->GetAlbum()->GetDocName();
        wxFileName* outputName = new wxFileName( doc );
        wxFileName outputZipName = *outputName;
        outputZipName.SetExt( wxT( "zip" ) );
        wxFFileOutputStream out( outputZipName.GetFullPath( ) );
        wxZipOutputStream zip( out );
        wxTextOutputStream txt( zip );
        wxString sep( wxFileName::GetPathSeparator( ) );

        wxArrayString fileArray;

        // Save files first
        int nbrFiles = GetFileList( fileArray, wxT( "*" ), wxFILE );
        for ( int i = 0; i < nbrFiles; i++ )
        {
            AddODTFile( zip, fileArray.Item( i ) );
        }

        wxArrayString dirArray;
        int nbrDirs = GetFileList( dirArray, wxT( "*" ), wxDIR );
        for ( int i = 0; i < nbrDirs; i++ )
        {
            wxString str = dirArray.Item( i ) + sep + wxT( "*.*" );
            zip.PutNextDirEntry( dirArray.Item( i ) );
            nbrFiles = GetFileList( fileArray, str, wxFILE );
            if ( nbrFiles > 0 )
            {
                for ( int j = 0; j < nbrFiles; j++ )
                {
                    AddODTFile( zip, fileArray.Item( j ) );
                }
            }
        }

        zip.Close( );
        wxRenameFile( outputZipName.GetFullPath( ), outputName->GetFullPath( ) );

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
