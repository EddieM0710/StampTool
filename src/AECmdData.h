/**
 * @file AECmdData.h
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef AECmdData_H
#define AECmdData_H

#include "Defs.h"
#include "tinyxml2.h"
#include <wx/string.h>

using namespace tinyxml2;

class AECmdData

{
public:

    /**
     * @brief Construct a new AE Command Data object
     *
     */
    AECmdData( );
    ~AECmdData( );
    bool IsOK( );
    XMLDocument* NewDocument( );
    XMLDocument* ReplaceDocument( XMLDocument* doc );
    XMLDocument* GetDoc( ) { return m_AECmdDoc; };
    void SaveXML( wxString filename );
    void LoadXML( wxString filename );
    void LoadAEFile( wxString filename );

    wxString GetTitle( ) { return m_title; }
    void  SetTitle( wxString val ) { m_title = val; };

private:
    /* data */
    XMLDocument* m_AECmdDoc;
    wxString m_title;
};

#endif
