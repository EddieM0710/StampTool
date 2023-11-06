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

        void AddCollection( Collection* item ) {
            m_list.push_back( item );
        };

        void AddCollection( wxString name, wxString description, wxString location );

        void BuildStrings( );

        void Clear( );

        Inventory::Collection* FindCollection( wxString name );


        Collection* GetCollection( int ndx );

        CollectionArray& GetCollectionList( ) {
            return m_list;
        };

        Collection* GetCurrentCollection( );

        wxString GetCurrentName( );

        wxString GetName( int i ) {
            return m_nameArray[ i ];
        };

        wxArrayString& GetNameArray( ) {
            return m_nameArray;
        };

        wxArrayString& GetNameStrings( );

        void Load( wxXmlNode* parent );

        void Save( wxXmlNode* parent );

        void SetDefaultCollection( );

        bool SetCurrentCollection( wxString str );

    private:
        wxString m_currCollection;
        wxArrayString m_nameArray;
        CollectionArray m_list;
    };
}

#endif 