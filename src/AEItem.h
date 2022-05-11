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

#ifndef AEItem_H
#define AEItem_H


#include "tinyxml2.h"

#include <wx/string.h>


using namespace tinyxml2;

class AEItem
{
public:
    AEItem() {};
    ~AEItem() {};
    void SetComment( wxString comment )
    {
        m_comment.Append( comment );
        std::cout << "m_comment: " << m_comment << "\n";
        m_dirty = true;
    };
    wxString GetComment() { return m_comment;  m_dirty = true; };
    void SetCommand( wxString cmd ) {
        m_command = cmd;
        std::cout << "m_command: " << m_command << "\n";
        m_dirty = true;
    };
    wxString GetCommand() { return m_command;  m_dirty = true; };
    void SetLineNbr( int nbr ) { m_lineNbr = nbr; m_dirty = true; };
    int GetLineNbr() {
        return m_lineNbr;
        std::cout << "m_lineNbr: " << m_lineNbr << "\n";
        m_dirty = true;
    };
    wxArrayString& GetParameterList() { return m_parameters; };
    int AddParameter( char* parm, int len )
    {
        wxString str;
        str.append( parm, len );
        str.Trim();
        str.Trim( false );
        m_dirty = true;
        std::cout << "parm: " << parm << "\n";

        return m_parameters.Add( str );
    }
    int AddParameter( wxString parm )
    {
        parm.Trim();
        parm.Trim( false );
        m_dirty = true;
        return m_parameters.Add( parm );
    }
    void ShowItem() {
        std::cout << m_lineNbr << ": " << m_command;
        if ( m_parameters.Count() > 0 )
        {
            std::cout << " ( ";
            for ( int i = 0; i < m_parameters.Count(); i++ )
            {
                std::cout << m_parameters.Item( i );
            }
            std::cout << " ) ";
        }
        std::cout << m_comment << "\n";
    }
    bool isDirty() { return m_dirty; };
private:
    wxString m_command;
    wxString m_comment;
    wxArrayString m_parameters;
    int m_lineNbr;
    bool m_dirty;
};


#endif