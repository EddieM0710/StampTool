/**
 * @file ReadAlbumEasyFile.cpp
 * @author Eddie Monroe ()
 * @brief
 *
 *
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/


 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/arrstr.h>
#include <wx/string.h>
////#include <wx/arrimpl.cpp>

#include "ReadAlbumEasyFile.h"

#include <tinyxml2.h>


char* stateNames[NbrProcessStates] = {
    "SEARCH", "COMMENT", "COMMAND", "PARAMSEARCH","PARAMETERS" };


ReadAlbumEasyFile::ReadAlbumEasyFile( wxString& filename, ArrayWrapper* itemArray )
{
    m_filename = filename;
    AEItemArray = itemArray;
    AEItemArray = new ArrayWrapper();;
};

bool ReadAlbumEasyFile::GetCommand()
{
    wxString searchSet = " (#";
    wxString cmd = GetSimpleString( searchSet );
    std::cout << "cmd: " << cmd << "\n";

    m_item->SetCommand( cmd );

    if ( m_pos >= m_buffer.Length() )
    {

    }
    else if ( m_buffer[m_pos] == '#' )
    {
        m_start = m_pos;
        m_prevState = PARAMSEARCH;
        m_state = COMMENT;
    }
    else if ( m_buffer[m_pos] == '(' )
    {
        m_char = m_buffer[m_pos];
        m_state = PARAMETERS;
    }
    else
    {
        m_char = m_buffer[m_pos];
        m_state = PARAMSEARCH;
    }
}

bool ReadAlbumEasyFile::GetComment()
{
    // a comment goes to the end of the line
    // just grab the rest of the line and save as a comment 
    // and get a new line
    int lineLen = m_buffer.Length();
    m_end = lineLen - 1;

    m_item->SetComment( GetSubString() );
    if ( !ReadLine() )
    {
        return false;
    }
    NewItem();
    m_char = m_buffer[m_pos];
    m_state = SEARCH;

    return true;
}

bool ReadAlbumEasyFile::DoSearch()
{
    //look for the start of a comment or a command
    SkipWhitespace();
    if ( m_char == '#' )
    {
        m_start = m_pos;
        m_state = COMMENT;
    }
    else
    {
        // non-space or non-comment encountered
        // this can only be the start of a command
        m_state = COMMAND;
        m_start = m_pos;
    }
}
void ReadAlbumEasyFile::DoParameterSearch()
{
    //look for the start of a comment or a parameter
    // anything besides space, ( or # is an error
    SkipWhitespace();
    if ( m_char == '(' )
    {
        m_pos++;
        m_start = m_pos;
        m_state = PARAMETERS;
    }
    else if ( m_char == '#' )
    {
        m_start = m_pos;
        m_prevState = PARAMSEARCH;
        m_state = COMMENT;
    }
}

void ReadAlbumEasyFile::SkipWhitespace()
{
    while ( m_char != EOF )
    {
        if ( !isspace( m_char ) )
        {
            return;
        }
        m_pos++;
        m_char = m_buffer[m_pos];
    }
}
wxString ReadAlbumEasyFile::GetSubString()
{
    wxString string = m_buffer.Mid( m_start, m_end - m_start + 1 );
    m_end = -1;
    m_start = -1;
    m_pos++;
    m_char = m_buffer[m_pos];
    return string;
}
wxString ReadAlbumEasyFile::GetSimpleString( wxString searchSet )
{
    wxString simpleString;
    int breakChar = m_buffer.find_first_of( searchSet, m_pos );
    if ( breakChar == wxNOT_FOUND )
    {
        m_end = m_buffer.Length() - 1;
    }
    else
    {
        m_end = breakChar - 1;
    }
    simpleString = GetSubString();
    m_pos = breakChar;
    // if ( breakChar == wxNOT_FOUND  )
    // {
    //     ReadLine();
    // }
    m_char = m_buffer[ m_pos ];
    return simpleString;
}

bool ReadAlbumEasyFile::GetQuotedString( wxString& quotedStr )
{
    while ( m_char != EOF )
    {
        if ( m_pos == m_buffer.Length() - 1 )
        {
            // we have reached the end of a line  inside a quoted string
            // this is an file error condition
            m_char = EOF;
            return false;
        }
        else if ( m_char == '\\' )
        {
            //special char next
            m_pos++;
            m_char = m_buffer[m_pos];
        }
        else if ( m_char == '\"' )
        {
            // this is the end of the string unless the next char is a '\' (backslash)
            if ( m_buffer[m_pos + 1] == '\\' )
            {
                m_end = m_pos - 1;
                quotedStr.Append( GetSubString() );
                NewItem();
                if ( !ReadLine() )
                {
                    return false;
                }
                m_char = m_buffer[m_pos];
                SkipWhitespace();
                if ( m_char != '\"')
                {
                    return false;
                }
                m_pos++;
                m_start = m_pos;
                m_char = m_buffer[m_pos];               
            }
            else
            {
                m_end = m_pos - 1;
                quotedStr.Append( GetSubString() );
                return true;
            }
        }
        else
        {
            m_pos++;
            m_char = m_buffer[m_pos];      
        }
    }
}


void ReadAlbumEasyFile::GetParameters()
{
    if ( m_char == '\"' )
    {
        //must be a quoted string parameter
        m_pos++;
        m_start = m_pos;
        m_char = m_buffer[m_pos];
        wxString quotedString = "";
        bool ok = GetQuotedString( quotedString );
        m_item->AddParameter( quotedString );
        std::cout << "quoteParm: " << quotedString << "\n";
        if ( ok )
        {
            m_state = PARAMETERS;
        }
    }
    else if ( m_char == '#' )
    {
        m_start = m_pos;
        m_prevState = PARAMETERS;
        m_state = COMMENT;

    }
    else if ( isspace( m_char ) )
    {
        //skip initial space
        SkipWhitespace();
    }
    else
    {
        // non-space, non-quote or non-comment encountered
        // this can only be the start of a simple parameter
        // the simple parameter is terminated by whitespace or ')'
        wxString searchSet = " )#";
        m_start = m_pos;
        wxString parm = GetSimpleString( searchSet );
        m_item->AddParameter( parm );
        std::cout << "Parm: " << parm << "\n";
        if ( m_char == ')' )
        {
            if ( m_pos == m_buffer.Length()-1)
            {
                NewItem();
                if ( !ReadLine() )
                {
                    return;
                }
                m_char = m_buffer[m_pos];
            }
            else
            {
                m_pos++;
                m_char = m_buffer[m_pos];
                m_state = SEARCH;
            }
        }
    }
}

bool ReadAlbumEasyFile::ProcessFile()
{
    m_lineNbr = 0;
    m_pos = 0;
    m_char = 0;
    m_start = -1;
    m_end = -1;
    m_state = SEARCH;
    m_strType = NONE;
    m_QuotedStr = "";

    bool status = false;
    if ( m_filename.Length() <= 0 )
    {
        return false;
    }
    m_File = new wxFileInputStream( m_filename );

    if ( !m_File->IsOk() )
    {
        return false;
    }

    m_Text = new wxTextInputStream( *m_File );

    if ( !ReadLine() )
    {
        return false;
    };
    NewItem();
    m_char = m_buffer[ m_pos ];

    while ( m_char != EOF )
    {
        if ( m_lineNbr >= 90 )
        {
            continue;
        }

        switch ( m_state )
        {
        case SEARCH:
            DoSearch();
            break;
        case COMMENT:
            GetComment();
            break;
        case COMMAND:
            GetCommand();
            break;
        case PARAMSEARCH:
            DoParameterSearch();
            break;
        case PARAMETERS:
            GetParameters();
            break;
        default:
            std::cout << "This is uncomfortable! We are i an unknown state!\n";
        }
        std::cout << stateNames[m_state] << " pos: " << m_pos << "  char: " << m_char << "\n";

if(m_pos == -1 )
{
    continue;
}
        if ( m_pos == m_buffer.Length() - 1 )
        {
            // we have reached the end of a line 
            // get more to process
            if ( !ReadLine() )
            {
                if ( m_item )
                {
                    // save last item if dirty
                    if ( m_item->isDirty() )
                    {

                        AEItemArray->push_back( m_item );
                    }
                }
                return false;
            }
        }
        else
        {
            m_char = m_buffer[m_pos];
        }
    }
}
