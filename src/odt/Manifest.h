/**
 * @file Manifest.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-08
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/
#ifndef Manifest_h
#define Manifest_h

#include "odt/ODTDefs.h"

#include <wx/xml/xml.h>

namespace ODT {

    class Manifest
    {
    public:

        Manifest( );
        ~Manifest( ) {};


        void AddManifestFileEntry( wxString fullPath, wxString mediaType );
        bool Save( );
        wxXmlDocument* ManifestXML( ) { return m_manifest; };
    private:
        wxXmlDocument* m_manifest;
    };
}
#endif