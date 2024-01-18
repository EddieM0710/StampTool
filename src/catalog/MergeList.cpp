/*
 * @file catalog/MergeList.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright ( c ) 2022
 *
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "catalog/MergeList.h"
#include "gui/ComparePanel.h"



namespace Catalog
{
    //--------------

    MergeEntry::MergeEntry( ComparePanel* parent ){
        m_status = MS_Undefined;
        m_targetEntry = ( Entry* ) 0;
        m_mergeEntry = ( Entry* ) 0;
        m_comparePanel = parent;
    };

    //--------------

    MergeEntry::MergeEntry( wxXmlNode* targetEntry, wxXmlNode* mergeEntry )
    {
        m_status = MS_Undefined;
        m_targetEntry = new Entry( targetEntry );
        m_mergeEntry = new Entry( mergeEntry );
        if ( m_targetEntry )
        {
            m_name = m_targetEntry->GetAttr( DT_Name );

        }
        else if ( m_mergeEntry )
        {
            m_name = m_mergeEntry->GetAttr( DT_Name );
        }
    };

    //--------------

    MergeEntry::~MergeEntry( )
    {
        if ( m_targetEntry )
            delete m_targetEntry;
        if ( m_mergeEntry )
            delete m_mergeEntry;
        m_targetEntry = 0;
        m_mergeEntry = 0;
    };


    //--------------

    wxString MergeEntry::GetName( )
    {
        wxString name = "";
        if ( m_targetEntry )
        {
            name = m_targetEntry->GetAttr( DT_Name );
        }
        if ( name.IsEmpty( ) && m_mergeEntry )
        {
            name = m_mergeEntry->GetAttr( DT_Name );
        }
        if ( name.IsEmpty( ) )
        {
            name = "None";
        }
        return name;
    }
    //--------------

    int MergeEntry::cmp( DataTypes type ){
        if ( m_targetEntry->GetCatXMLNode( ) && m_mergeEntry->GetCatXMLNode( ) )
        {
            return ( m_comparePanel->CompareEnabled( ( int ) type ) &&
                m_targetEntry->GetAttr( type ).Cmp( m_mergeEntry->GetAttr( type ) ) );
        }
        return false;
    };

    MergeStatus MergeEntry::GetStatus( ){
        return m_status;
    };

    //--------------

    void MergeEntry::SetStatus( ){
        if ( !m_targetEntry || m_targetEntry == ( Entry* ) 0x8000000000000000 )
        {
            m_status = MS_TargetMissing;
            return;
        }
        else if ( !m_mergeEntry || m_mergeEntry == ( Entry* ) 0x8000000000000000 )
        {
            m_status = MS_MergeMissing;
            return;
        }
        for ( int i = 0; i < DT_NbrTypes; i++ )
        {
            if ( cmp( ( DataTypes ) i ) )
            {
                m_status = MS_Different;
                return;
            }
            else
            {
                m_status = MS_Same;
            }
        }
    };

    //--------------

    void MergeEntry::SetTargetEntry( wxXmlNode* targetEntry ){
        m_status = MS_Undefined;
        m_targetEntry = new Entry( targetEntry );
        if ( m_name.IsEmpty( ) && m_targetEntry )
        {
            m_name = m_targetEntry->GetAttr( DT_Name );
        }
    }

    //--------------

    void  MergeEntry::SetMergeEntry( wxXmlNode* mergeEntry ){
        m_status = MS_Undefined;
        m_mergeEntry = new Entry( mergeEntry );
        if ( m_name.IsEmpty( ) && m_mergeEntry )
        {
            m_name = m_mergeEntry->GetAttr( DT_Name );
        }
    }

    //--------------

    wxColour  MergeEntry::GetColour( )
    {
        if ( m_status == MS_Undefined )
        {
            return *wxLIGHT_GREY;
        }

        else if ( m_status == MS_Same )
        {
            return *wxGREEN;
        }

        else if ( m_status == MS_Different )
        {
            return *wxYELLOW;
        }

        else if ( m_status == MS_TargetMissing )
        {
            return *wxRED;
        }

        else if ( m_status == MS_MergeMissing )
        {
            return  *wxCYAN;
        }
        return  *wxWHITE;
    }

    //--------------

    Entry* MergeEntry::GetTargetEntry( ){
        return   m_targetEntry;
    }

    //--------------

    Entry* MergeEntry::GetMergeEntry( ){
        return m_mergeEntry;
    }

    //--------------

    wxString MergeEntry::GetTargetAttribute( DataTypes type ){
        if ( m_targetEntry )
        {
            return  m_targetEntry->GetAttr( type );
        }
        else
        {
            return "";
        }
    }

    //--------------

    wxString MergeEntry::GetMergeAttribute( DataTypes type ){
        if ( m_mergeEntry )
        {
            return  m_mergeEntry->GetAttr( type );
        }
        else
        {
            return "";
        }
    }

    //--------------

    //--------------

    MergeList::MergeList( ComparePanel* parent )
    {
        m_targetRoot = 0;
        m_mergeRoot = 0;
        m_mergeList.clear( );
        m_comparePanel = parent;

    };

    //--------------

    MergeList::~MergeList( ){};


    void MergeList::SetTargetRoot( wxXmlNode* targetRoot ){
        m_targetRoot = targetRoot;
    };

    wxXmlNode* MergeList::GetTargetRoot( )
    {
        return m_targetRoot;
    };

    //--------------

    void MergeList::SetMergeRoot( wxXmlNode* mergeRoot ){
        m_mergeRoot = mergeRoot;
    };

    //--------------

    void MergeList::LoadEntryList( wxXmlNode* node )
    {
        if ( !node->GetName( ).Cmp( CatalogBaseNames[ NT_Entry ] ) )
        {
            MergeEntry* entry = new MergeEntry( m_comparePanel );
            entry->SetTargetEntry( node );
            m_mergeList.push_back( entry );
        }
        wxXmlNode* child = node->GetChildren( );
        while ( child )
        {
            LoadEntryList( child );
            child = child->GetNext( );
        }
    }

    //--------------

    void MergeList::LoadEntryList( )
    {
        if ( m_targetRoot )
        {
            wxXmlNode* child = m_targetRoot->GetChildren( );
            while ( child )
            {
                LoadEntryList( child );
                child = child->GetNext( );
            }
        }
    };

    //--------------

    void MergeList::AddMergeEntryList( wxXmlNode* node )
    {
        if ( !node->GetName( ).Cmp( CatalogBaseNames[ NT_Entry ] ) )
        {
            MergeEntry* entry = new MergeEntry( m_comparePanel );
            entry->SetMergeEntry( node );
            m_mergeList.push_back( entry );
        }
        wxXmlNode* child = node->GetChildren( );
        while ( child )
        {
            LoadEntryList( child );
            child = child->GetNext( );
        }
    }

    //--------------

    MergeEntry* MergeList::FindTargetEntryForNewEntry( Entry* entry, DataTypes type )
    {
        wxString entryVal = entry->GetAttr( type );
        for ( MergeEntryList::iterator it = std::begin( m_mergeList );
            it != std::end( m_mergeList );
            ++it )
        {
            MergeEntry* mergeEntry = ( MergeEntry* ) ( *it );
            if ( !entryVal.Cmp( mergeEntry->GetTargetAttribute( type ) ) )
            {
                return mergeEntry;
            }
        }
        return ( MergeEntry* ) 0;
    }

    //--------------

    void MergeList::AddMergeToEntryList( wxXmlNode* node )
    {
        if ( node )
        {
            Entry entry( node );
            MergeEntry* mergeEntry = FindTargetEntryForNewEntry( &entry, DT_Link );
            if ( mergeEntry )
            {
                mergeEntry->SetMergeEntry( node );
            }
            else
            {
                MergeEntry* entry = new MergeEntry( m_comparePanel );
                entry->SetMergeEntry( node );
                m_mergeList.push_back( entry );
            }

            wxXmlNode* child = node->GetChildren( );
            while ( child )
            {
                AddMergeToEntryList( child );
                child = child->GetNext( );
            }
        }
    };

    //--------------

    void MergeList::AddMergeToEntryList( )
    {
        if ( m_mergeRoot )
        {
            wxXmlNode* child = m_mergeRoot->GetChildren( );
            while ( child )
            {
                AddMergeToEntryList( child );
                child = child->GetNext( );
            }
        }
    };

    //--------------

    MergeEntryList* MergeList::GetMergeList( )
    {
        return &m_mergeList;
    }

    //--------------

    void  MergeList::SetComparePanel( ComparePanel* comparePanel ){
        m_comparePanel = comparePanel;
    }

    void  MergeList::SetStatus( )
    {
        for ( MergeEntryList::iterator it = std::begin( m_mergeList );
            it != std::end( m_mergeList );
            ++it )
        {
            MergeEntry* mergeEntry = ( MergeEntry* ) ( *it );
            mergeEntry->SetStatus( );
        }
    }

    MergeStatus  MergeList::GetStatus( int i )
    {
        return m_mergeList[ i ]->GetStatus( );
    }

    void MergeList::Clear( )
    {
        int len = m_mergeList.size( );
        if ( len > 0 )
        {
            for ( int i = len - 1; i >= 0; i-- )
            {
                MergeEntry* entry = m_mergeList[ i ];
                delete entry;
                m_mergeList.pop_back( );
            }
            len = m_mergeList.size( );
        }
        while ( len > 0 )
        {
            int q = 11;
        }
    }

}