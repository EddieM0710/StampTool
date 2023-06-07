#ifndef CollectionList_H
#define CollectionList_H

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/arrstr.h>
#include <vector>

#include "utils/XMLUtilities.h"

namespace Inventory
{
    class Collection;

    typedef std::vector<Collection*> CollectionArray;



    class CollectionList
    {
    public:
        CollectionList( ) {};
        ~CollectionList( ) {};
        void Save( wxXmlNode* parent );
        void Load( wxXmlNode* parent );

        CollectionArray& GetCollectionList( ) { return m_list; };
        void AddCollection( Collection* item ) { m_list.push_back( item ); };
        void AddCollection( wxString name, wxString description, wxString location );
        Inventory::Collection* FindCollection( wxString name );

        wxArrayString& GetNameArray( ) { return m_nameArray; };
        void BuildStrings( );

        wxArrayString& GetNameStrings( );
        void SetDefaultCollection( );

        bool SetCurrentCollection( wxString str );
        Collection* GetCurrentCollection( );
        wxString GetCurrentName( );

    private:
        wxString m_currCollection;
        wxArrayString m_nameArray;
        CollectionArray m_list;
    };
}

#endif 