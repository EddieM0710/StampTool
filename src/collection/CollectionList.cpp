

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "collection/CollectionList.h"
#include "collection/Collection.h"

//#include "collection/CollectionData.h"
#include "utils/Settings.h"


namespace Inventory {

    void CollectionList::Save( wxXmlNode* parent )
    {
        for ( Inventory::CollectionArray::iterator it = std::begin( m_list );
            it != std::end( m_list );
            ++it )
        {
            Inventory::Collection* collection = ( Inventory::Collection* ) ( *it );
            wxXmlNode* child = Utils::NewNode( parent, "Collection" );
            collection->Save( child );
        }
    }

    void CollectionList::Load( wxXmlNode* parent )
    {
        wxXmlNode* child = parent->GetChildren( );;
        while ( child )
        {
            wxString name = child->GetName( );
            if ( !name.Cmp( "Collection" ) )
            {
                Collection* collection = new Collection( );
                collection->Load( child );
                m_list.push_back( collection );
                child = child->GetNext( );
            }
        }
        SetDefaultCollection( );
        BuildStrings( );

    }

    void CollectionList::SetDefaultCollection( )
    {
        wxString lastCollection = GetSettings( )->GetLastCollection( );
        if ( lastCollection.IsEmpty( ) )
        {
            lastCollection = "Mint";
        }
        Collection* collection = FindCollection( lastCollection );
        if ( collection )
        {
            SetCurrentCollection( lastCollection );
        }
        else
        {
            if ( m_list.size( ) > 0 )
            {
                lastCollection = m_list.at( 0 )->GetName( );
                SetCurrentCollection( lastCollection );
            }
            else
            {
                Collection* collection = new Collection( lastCollection, "", "" );
                m_list.push_back( collection );
                SetCurrentCollection( lastCollection );
            }
        }
    }
    Inventory::Collection* CollectionList::FindCollection( wxString name )
    {
        for ( Inventory::CollectionArray::iterator it = std::begin( m_list );
            it != std::end( m_list );
            ++it )
        {
            Inventory::Collection* collection = ( Inventory::Collection* ) ( *it );

            if ( !name.Cmp( collection->GetName( ) ) )
            {
                return collection;
            }
        }
        return  ( Inventory::Collection* ) 0;
    }

    void CollectionList::AddCollection( wxString name, wxString description, wxString location )
    {
        Collection* item = new Collection( name, description, location );
        m_list.push_back( item );
        BuildStrings( );
    };


    void CollectionList::BuildStrings( )
    {
        m_nameArray.Clear( );
        for ( CollectionArray::iterator it = std::begin( m_list );
            it != std::end( m_list );
            ++it )
        {
            Collection* collection = ( Inventory::Collection* ) ( *it );
            m_nameArray.Add( collection->GetName( ) );
        }
    };

    Collection* CollectionList::GetCurrentCollection( ) { return FindCollection( m_currCollection ); };

    wxArrayString& CollectionList::GetNameStrings( )
    {
        return m_nameArray;
    };

    wxString CollectionList::GetCurrentName( ) { return m_currCollection; };

    bool CollectionList::SetCurrentCollection( wxString str )
    {
        Collection* collection = FindCollection( str );
        if ( collection )
        {
            wxString name = collection->GetName( );
            m_currCollection = name;
            GetSettings( )->SetLastCollection( m_currCollection );
            return true;
        }
        return false;
    };

}