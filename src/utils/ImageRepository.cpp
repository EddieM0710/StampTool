
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <iostream>
#include "wx/filename.h"
#include <memory>
#include "wx/wfstream.h"
#include "utils/ImageRepository.h"
#include <wx/filefn.h> 
#include <stdlib.h>

namespace Utils {
    ImageRepository::ImageRepository( wxString archiveFileName )
    {
        m_archiveFileName = archiveFileName;
        if ( wxFileExists( m_archiveFileName ) )
        {
            BuildRepositoryCatalog( );
        }
    }

    void ImageRepository::BuildRepositoryCatalog( )
    {

        if ( !m_repositoryCatalog.empty( ) )
        {
            m_repositoryCatalog.clear( );
        }

        wxFFileInputStream in( m_archiveFileName );
        wxZipInputStream zip( in );
        // load the zip catalog
        if ( !zip.Eof( ) )
        {
            wxZipEntry* entry = zip.GetNextEntry( );

            while ( entry != NULL )
            {
                m_repositoryCatalog[ entry->GetInternalName( ) ] = entry;
                entry = zip.GetNextEntry( );
            }
        }
    }

    // bool ImageRepository::CopyToImage( wxInputStream& inputStream, wxMemoryOutputStream& outStream )
    // {
    //     inputStream.IsOk( );

    //     if ( inputStream.IsOk( ) )
    //     {
    //         bool ok;
    //         int pos = 0;
    //         ok = inputStream.ReadAll( &buf[ pos ], 4096 );
    //         int lastRead = inputStream.LastRead( );
    //         pos += lastRead;
    //         while ( lastRead > 0 )
    //         {
    //             if ( ok )
    //             {
    //                 ok = inputStream.ReadAll( &buf[ pos ], 4096 );
    //                 lastRead = inputStream.LastRead( );
    //                 pos += lastRead;
    //             }
    //             else
    //             {
    //                 lastRead = 0;
    //             }
    //         }
    //     }
    //     return true;
    // }

    bool ImageRepository::CopyStreamData( wxInputStream& inputStream, wxOutputStream& outputStream )
    {
        char buf[ 4096 ];
        if ( inputStream.IsOk( ) )
        {
            bool ok;
            ok = inputStream.CanRead( );
            inputStream.Read( buf, 4096 );
            wxStreamError err = inputStream.GetLastError( );
            int lastRead = inputStream.LastRead( );
            while ( lastRead > 0 )
            {
                outputStream.Write( buf, lastRead );
                if ( ok )
                {
                    ok = inputStream.ReadAll( buf, 4096 );
                    lastRead = inputStream.LastRead( );
                }
                else
                {
                    lastRead = 0;
                }
            }
        }
        return true;
    }


    bool ImageRepository::CopyRepository( wxZipInputStream& inZip, wxZipOutputStream& outZip )
    {
        wxZipEntry* entry;
        outZip.CopyArchiveMetaData( inZip );
        while ( ( entry = inZip.GetNextEntry( ) ) != NULL )
        {
            outZip.CopyEntry( entry, inZip );
        }
        return true;
    }

    int ImageRepository::Extract( wxString newImage, wxMemoryOutputStream& outStream )
    {
        wxString internalName = wxZipEntry::GetInternalName( GetFileName( newImage ) );

        RepositoryCatalog::iterator it = m_repositoryCatalog.find( internalName );
        if ( it != m_repositoryCatalog.end( ) )
        {
            {
                wxFFileInputStream in( m_archiveFileName );
                wxZipInputStream zip( in );

                wxZipEntry* entry = it->second;
                zip.OpenEntry( *entry );
                zip.Read( outStream );
                int entrySize = entry->GetSize( );

                return entrySize;
            }
        }
        return 0;
    }


    bool ImageRepository::Exists( wxString inputFileName )
    {
        if ( Find( inputFileName ) )
        {
            //already in repository
            return true;
        }
        return false;
    }

    wxZipEntry* ImageRepository::Find( wxString file )
    {
        wxString internalName = wxZipEntry::GetInternalName( GetFileName( file ) );

        RepositoryCatalog::iterator it = m_repositoryCatalog.find( internalName );
        if ( it != m_repositoryCatalog.end( ) )
        {
            return it->second;
        }
        return ( wxZipEntry* ) 0;
    }



    wxString ImageRepository::GetFileName( wxString inputFileName )
    {
        wxFileName zipName{ inputFileName };
        return zipName.GetFullName( );
    }

    wxImage ImageRepository::GetImage( wxString filename )
    {
        wxImage image;
        wxMemoryOutputStream outputStream;

        wxString internalName = wxZipEntry::GetInternalName( GetFileName( filename ) );

        RepositoryCatalog::iterator it = m_repositoryCatalog.find( internalName );
        if ( it != m_repositoryCatalog.end( ) )
        {
            {
                wxFFileInputStream in( m_archiveFileName );
                wxZipInputStream zip( in );

                wxZipEntry* entry = it->second;
                zip.OpenEntry( *entry );
                zip.Read( outputStream );

                // now we can access the saved image bytes:
                wxStreamBuffer* theBuffer = outputStream.GetOutputStreamBuffer( );
                int size = theBuffer->GetBufferSize( );
                theBuffer->SetIntPosition( 0 );

                void* internalBuffer = theBuffer->GetBufferStart( );
                wxMemoryInputStream stream( internalBuffer, size );
                bool stat = image.LoadFile( stream );
            }
        }
        return image;
    }

    /// @brief 
    /// @param inputFileName 
    /// @return 
    bool ImageRepository::Insert( wxString inputFileName )
    {
        {
            if ( wxFileExists( inputFileName ) )
            {
                return false;
            }

            if ( Exists( inputFileName ) )
            {
                //already in repository
                return true;
            }

            // take care of existing repository
            wxString OldZipName;
            bool copyFromOldRepository = MakeBakFile( OldZipName );

            wxFFileOutputStream out( m_archiveFileName );
            wxZipOutputStream outZip( out );

            if ( copyFromOldRepository )
            {
                wxFFileInputStream in( OldZipName );
                wxZipInputStream inZip( in );
                CopyRepository( inZip, outZip );
            }

            wxString zipName = GetFileName( inputFileName );
            wxFFileInputStream l_file( inputFileName );

            // then insert the the new file into new repository
            outZip.PutNextEntry( zipName );
            //outZip.Write( l_file );
            CopyStreamData( l_file, outZip );
            outZip.CloseEntry( );
            outZip.Close( );
        }
        // and rebuild the catalog
        BuildRepositoryCatalog( );
        return true;
    }

    bool ImageRepository::Insert( wxArrayString inputArray )
    {
        // CleanupList( inputArray );
         // take care of existing repository
        wxString OldZipName;
        bool copyFromOldRepository = MakeBakFile( OldZipName );
        {
            wxFFileOutputStream out( m_archiveFileName );
            wxZipOutputStream outZip( out );

            if ( copyFromOldRepository )
            {
                wxFFileInputStream in( OldZipName );
                wxZipInputStream inZip( in );
                CopyRepository( inZip, outZip );
            }

            bool outOK = outZip.IsOk( );
            int outErr = outZip.GetLastError( );

            for ( wxArrayString::iterator it = std::begin( inputArray );
                it != std::end( inputArray );
                ++it )
            {
                wxString inputFileName = *it;
                if ( wxFileExists( inputFileName ) )
                {
                    wxString zippedName = GetFileName( inputFileName );
                    if ( !zippedName.IsEmpty( ) && !Find( inputFileName ) )
                    {
                        // if it is not already in the repository
                        // then insert the the new file into new repository
                        outZip.PutNextEntry( zippedName );
                        wxFFileInputStream in_file( inputFileName );
                        //outZip.Write( in_file );
                        CopyStreamData( in_file, outZip );
                    }
                }
            }
            outZip.CloseEntry( );
            outZip.Close( );
        }
        // and rebuild the catalog
        BuildRepositoryCatalog( );
        return true;
    }

    bool ImageRepository::MakeBakFile( wxString& OldZipName )
    {
        if ( wxFileExists( m_archiveFileName ) )
        {
            wxFileName oldZip = m_archiveFileName;
            wxString name = oldZip.GetName( ) + "_bak";
            oldZip.SetName( name );
            OldZipName = oldZip.GetFullPath( );
            if ( wxFileExists( OldZipName ) )
            {
                wxRemoveFile( OldZipName );
            }
            wxRenameFile( m_archiveFileName, OldZipName );
            return true;
        }
        return false;
    }

    void ImageRepository::MakeMissingList( wxArrayString inputArray, wxArrayString missingArray )
    {
        for ( wxArrayString::iterator it = std::begin( inputArray );
            it != std::end( inputArray );
            ++it )
        {
            wxString inputFileName = *it;

            wxFileName zipName( inputFileName );
            wxString zippedName = zipName.GetFullName( );
            if ( !zippedName.IsEmpty( ) && !Find( zippedName ) )
            {
                // if it is missing
                missingArray.Add( zippedName );
            }
        }
    }

    bool ImageRepository::Remove( wxString inputFileName )
    {
        {
            if ( !Exists( inputFileName ) )
            {
                //already in repository
                return true;
            }

            // take care of existing repository
            wxString OldZipName;
            MakeBakFile( OldZipName );

            wxFFileOutputStream out( m_archiveFileName );
            wxZipOutputStream outZip( out );

            wxFFileInputStream in( OldZipName );
            wxZipInputStream inZip( in );

            wxZipEntry* entry;
            wxString zipName = wxZipEntry::GetInternalName( GetFileName( inputFileName ) );

            outZip.CopyArchiveMetaData( inZip );
            entry = inZip.GetNextEntry( );
            while ( entry != NULL )
            {
                if ( zipName.Cmp( entry->GetInternalName( ) ) )
                {
                    outZip.CopyEntry( entry, inZip );
                }
                entry = inZip.GetNextEntry( );
            }
            outZip.CloseEntry( );
            outZip.Close( );
        }
        // and rebuild the catalog
        BuildRepositoryCatalog( );
        return true;
    }
}