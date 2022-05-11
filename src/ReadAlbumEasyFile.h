/**
 * @file CSV.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef ReadAlbumEasyFile_H
#define ReadAlbumEasyFile_H


#include "tinyxml2.h"
#include <wx/filename.h>
#include <wx/string.h>
#include <cstdio>

#include <wx/txtstrm.h>
#include <wx/wfstream.h>
//#include <wx/arrstr.h>

#include <ArrayWrapper.h>

using namespace tinyxml2;

#define MaxNbrCSVCols 30

typedef enum {
    SEARCH, COMMENT, COMMAND, PARAMSEARCH, PARAMETERS, NbrProcessStates
}ProcessState;
extern char* stateNames[NbrProcessStates];
typedef enum {
    SIMPLESTRING, QUOTEDSTRING, NONE, NbrStringTypes
} StringType;


/**
 * @brief read/write AlbumEasy files.
 *
 **************************************************/
class ReadAlbumEasyFile
{
public:

    /**
     * @brief Construct a new ReadFile object
     *
     **************************************************/
    ReadAlbumEasyFile( wxString& filename, ArrayWrapper* AEItemArray );
private:
    ReadAlbumEasyFile( void ) { };
public:
    /**
     * @brief Destroy the ReadFile object
     *
     **************************************************/
    ~ReadAlbumEasyFile( void ) { };


    /**
     * @brief Try to fix the input line if it has embedded quotes and commas.
     *
     * @details Colnect csv export files seem to be good but opening in Office Calc/Excel then
     * saving it back to a csv file frequently screws things up.
     *
     * @param  line :line to be fixed
     **************************************************/

    bool ProcessFile();
    bool GetComment();
    bool GetCommand();
    bool GetQuotedString( wxString &str );
    wxString GetSimpleString( wxString searchSet );
    bool DoSearch();
    void DoParameterSearch();
    void GetParameters();
    void SkipWhitespace();
    wxString GetSubString();

    bool ReadLine() {
        m_buffer = m_Text->ReadLine();
        m_lineNbr++;
        while ( !m_File->Eof( ) && m_buffer.Length() == 0 )
        {
            m_buffer = m_Text->ReadLine();
            m_lineNbr++;
        }
        m_pos = 0;
        if (  !m_File->Eof( ) )
        {
            m_char = m_buffer[ m_pos ];
            SkipWhitespace();
            m_buffer.Trim(true);
            std::cout << "ReadLine: " << m_buffer << "\n";
            return true;
        }
        else
        {
            m_char = EOF;
            return false;
        }
    };


    void NewItem()
    {
        if ( m_item )
        {
  
            AEItemArray->push_back( m_item );
        }
        m_item = new AEItem();
        m_item->SetLineNbr( m_lineNbr );
    };



private:
    wxString m_filename;
    ArrayWrapper* AEItemArray;

    int m_lineCnt;
    wxFileInputStream* m_File;
    wxTextInputStream* m_Text;
    AEItem* m_item;
    wxString m_buffer;
    int m_lineNbr;
    int m_pos;
    char m_char;
    int m_start;
    int m_end;
    ProcessState m_state;
    ProcessState m_prevState;
    StringType m_strType;
    wxString m_QuotedStr;
};

#endif