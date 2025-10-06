/*
 * @file ColnectWxClient.h
 * @brief
 * @author Eddie Monroe
 * Modified by:
 * @date 30 Sept 2025
 *
 * @copyright Copyright ( c ) 2024
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
 */

#ifndef _COLNECTWXCLIENT_H_
#define _COLNECTWXCLIENT_H_

#include <utility> // For std::pair

#include <wx/webrequest.h>

typedef struct
{
    wxString name;
    wxString value;
} HeaderPair;
typedef HeaderPair WebRequestHeader;

class ColnectWxClient : public wxEvtHandler
{

public:
    ColnectWxClient( wxWindow *parent = nullptr ) : m_parent( parent )
    {
        m_session = wxWebSession::GetDefault( );
        OnInit( );
    }

    bool OnInit( );

    // Public entrypoint: fetch fields -> fetch item -> download image
    void FetchAndDownload( wxString itemId, 
                          const wxString &outPath );

private:
    // ---- Build Colnect path and auth headers ----
    wxString BuildFieldsPath( ) const;
    wxString BuildItemPath( ) const;

    wxString Create_Hmac( wxString msg );

    wxVector<WebRequestHeader>
    MakeAuthHeaders( wxString &pathNoDomain ) ;

    // ---- Step 1: /fields ( array of names, we find positions ) ----
    void CallFields( );
    void OnFields( wxWebRequestEvent &e );

    // ---- Step 2: /item …/id/<ID> ( array with values ) ----
    void CallItem( );

    void OnItem( wxWebRequestEvent &e );

    // ---- Step 3: GET the image and save it ----
    void CallImage( );

    void OnImage( wxWebRequestEvent &e );

private:
    wxWindow *m_parent{nullptr};
    wxWebSession m_session;

    wxString m_itemId{""};
    wxString m_outPath;
    // wxString m_appSecret;
    bool m_full{true};
    const wxString m_hmac;
    int m_idxItemName{-1};
    int m_idxFrontPic{-1};
    wxString m_imgUrl;
};

#endif