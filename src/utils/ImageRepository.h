#ifndef ImageRepository_h
#define ImageRepository_h

#include <wx/arrstr.h>
#include <wx/hashmap.h>
#include "wx/zipstrm.h"
#include <wx/mstream.h>

WX_DECLARE_STRING_HASH_MAP( wxZipEntry*, RepositoryCatalog );

namespace Utils {

    ///  @brief Repository for images referenced by catalog or album files
    /// @details The ImageRepository is a zip file. The files are stored by 
    /// filename/ext only; i.e., no directory paths. Only one copy of each file.
    ///  
    class ImageRepository
    {
    public:

        ///  @brief Construct a new Image Repository object
        ///  
        ///  @param archiveFileName 
        ImageRepository( wxString archiveFileName );

        ///  @brief Builds a hash map for quick indexing into the repository.
        ///  
        void BuildRepositoryCatalog( );

        ///  @brief Copy the entire repository from inZip to OutZip.
        ///  
        ///  @param inZip 
        ///  @param outZip 
        ///  @return true 
        ///  @return false 
        bool CopyRepository( wxZipInputStream& inZip, wxZipOutputStream& outZip );

        ///  @brief copies the data dfrom the input stream to the output stream.
        ///  
        ///  @param inputStream 
        ///  @param outputStream 
        ///  @return true 
        ///  @return false 
        bool CopyStreamData( wxInputStream& inputStream, wxOutputStream& outputStream );

        // bool CopyToBuffer( wxInputStream& inputStream, char* buf );

         ///  @brief Copies a file to the output stream.
         ///  
         ///  @param newImage 
         ///  @param outputStream 
         ///  @return true 
         ///  @return false 
        int Extract( wxString newImage, wxMemoryOutputStream& outStream );

        ///  @brief 
        ///  
        ///  @param inputFileName 
        ///  @return true 
        ///  @return false 
        bool Exists( wxString inputFileName );

        wxZipEntry* Find( wxString inputFileName );

        ///  @brief Get the filname/ext of the input path
        ///  
        wxString GetFileName( wxString inputFileName );

        wxImage GetImage( wxString filename );

        ///  @brief inserts a file into the repository
        ///  
        ///  @param inputFileName 
        ///  @return true 
        ///  @return false 
        bool Insert( wxString inputFileName );

        ///  @brief inserts an array of files into the repository.
        ///  
        ///  @param inputArray 
        ///  @return true 
        ///  @return false 
        bool Insert( wxArrayString inputArray );

        ///  @brief if the repository file exists it renames it to a bak file
        ///  
        ///  @param OldZipName 
        ///  @return true 
        ///  @return false 
        bool MakeBakFile( wxString& OldZipName );

        ///  @brief 
        ///  
        ///  @param inputArray 
        ///  @param missingArray 
        void MakeMissingList( wxArrayString inputArray, wxArrayString missingArray );

        ///  @brief removes a file from thr repository.
        ///  
        ///  @param inputFileName 
        ///  @return true 
        ///  @return false 
        bool Remove( wxString inputFileName );

    private:
        RepositoryCatalog m_repositoryCatalog;
        wxString m_archiveFileName;
    };
}
#endif