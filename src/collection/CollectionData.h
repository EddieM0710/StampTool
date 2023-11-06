
#ifndef CollectionData_H
#define CollectionData_H


//#include "collection/CollectionList.h"

#include "wx/xml/xml.h"
#include <wx/string.h>
#include <wx/arrstr.h>
#include <vector>
//#include <wx/hashmap.h>


//WX_DECLARE_STRING_HASH_MAP( Inventory::Collection*, CollectionArray );

#include "utils/XMLUtilities.h"

namespace Inventory {

    class Collection;
    class CollectionList;
    class CollectionData
    {
    public:

        CollectionData( ) {};
        ~CollectionData( ) {};

        void Save( );
        void SetDirty( bool state = true );


        int FindStringIndex( wxString str );

    private:
        bool m_dirty;


        CollectionList* m_collectionList;
    };

};
#endif