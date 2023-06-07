#ifndef StampMount_h
#define StampMount_h


#include "wx/xml/xml.h"
#include <wx/string.h>

namespace Catalog {

    typedef struct
    {
        wxString name;
        int width;
        int height;
        wxString description;
    }Mounts;

    const int NbrStampMounts = 100;

    extern Mounts mounts[ NbrStampMounts ];


    class StampMountData
    {
    public:
        StampMountData( );
        ~StampMountData( ) {};
        // bool LoadCSV( wxString filename );

        wxXmlDocument* NewMountDocument( );
        wxXmlDocument* GetDoc( ) { return m_mountDoc; };
        void FixUpHyphenID( wxXmlDocument* doc );
        void FixUpHyphenID( wxXmlNode* node, wxString level = "" );

        wxString Find( wxString id );

        wxString Find( wxXmlNode* node, wxString id );
        wxXmlDocument* LoadXML( );

        wxXmlDocument* LoadMountCSV( wxString filename );
        wxXmlDocument* m_mountDoc;
    };
}
#endif