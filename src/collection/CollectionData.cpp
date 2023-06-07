



#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "collection/Collection.h"

#include "collection/CollectionData.h"
#include "collection/CollectionList.h"
#include "utils/Settings.h"


#include "wx/filename.h"
#include "Defs.h"
#include "gui/AppData.h"

namespace Inventory {

    //void CollectionData::LoadData2( ) { LoadData( ); };



    void CollectionData::SetDirty( bool state )
    {
        m_dirty = state;
        if ( m_dirty )
        {
            GetAppData( )->SetDirty( true );
        }
    }

    // int CollectionData::FindStringIndex( wxString str )
    // {
    //     for ( int i = 0; i < m_nameArray.Count( ); i++ )
    //     {
    //         if ( !str.Cmp( m_nameArray.Item( i ) ) )
    //         {
    //             return i;
    //         }
    //     }
    //     return -1;
    // }
}