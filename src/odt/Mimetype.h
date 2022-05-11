#ifndef MimeType_h
#define MimeType_h

#include "odt/ODTDefs.h"
#include <wx/xml/xml.h>

namespace ODT {

    class MimeType
    {
    public:
        MimeType( ) {};
        ~MimeType( ) {};
        bool Save( );
    };
}
#endif