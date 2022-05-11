
#ifndef Settings_h
#define Settings_h


#include "odt/ODTDefs.h"
#include <wx/xml/xml.h>

namespace ODT {

    class Settings
    {
    public:

        Settings( );
        ~Settings( ) {};
        bool Save( );

        wxXmlDocument* SettingsXML( ) { return m_settings; };
    private:
        wxXmlDocument* m_settings;
    };
}
#endif
