#ifndef Meta_h
#define Meta_h

#include "odt/ODTDefs.h"
#include <wx/xml/xml.h>

namespace ODT {

    class Meta
    {
    public:
        Meta( );
        ~Meta( );
        bool Save( );
        wxXmlDocument* MetaXML( ) { return m_meta; };

    private:
        wxXmlDocument* m_meta;

    };
}
#endif
