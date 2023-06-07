#ifndef Collection_H
#define Collection_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/arrstr.h>
#include <vector>

#include "utils/XMLUtilities.h"

namespace Inventory
{
    class Collection
    {
    public:

        Collection( )
        {
            SetName( "" );
            SetDescription( "" );
            SetLocation( "" );
        };
        Collection( wxString name, wxString description, wxString location )
        {
            SetName( name );
            SetDescription( description );
            SetLocation( location );
        };
        ~Collection( ) {};

        wxString GetName( ) { return m_name; };
        void SetName( wxString name ) { m_name = name; };
        wxString GetDescription( ) { return m_name; };
        void SetDescription( wxString description ) { m_description = description; };
        wxString GetLocation( ) { return m_location; };
        void SetLocation( wxString location ) { m_location = location; };

        void Load( wxXmlNode* xmlNode );

        void Save( wxXmlNode* xmlNode );

    private:
        wxString m_name;
        wxString m_description;
        wxString m_location;
    };
}
#endif