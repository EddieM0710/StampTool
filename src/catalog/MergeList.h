/**
* @file MergeList.h
* @author Eddie Monroe( )
* @brief
* @version 0.1
* @date 2021 - 02 - 25
*
*@copyright Copyright( c ) 2021
*
*This file is part of StampTool.
*
*StampTool is free software : you can redistribute it and /or modify it under the
* terms of the GNU General Public License as published by the Free Software Foundation,
* either version 3 of the License, or any later version.
*
*StampTool is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
* PARTICULAR PURPOSE.See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* StampTool.If not, see < https://www.gnu.org/licenses/>.
*
*/

#ifndef MergeList_H
#define MergeList_H

#include "wx/xml/xml.h"
#include <vector>

#include "catalog/CatalogDefs.h"
//#include "catalog/Stamp.h"
#include "catalog/Entry.h"
#include "catalog/CatalogVolume.h"

class ComparePanel;

namespace Catalog
{
    typedef enum {
        MS_None = 0,
        MS_TargetMissing,
        MS_MergeMissing,
        MS_Same,
        MS_Different,
        MS_Undefined
    } MergeStatus;

    class MergeData
    {
    public:

        MergeData( ComparePanel* parent );

        MergeData( wxXmlNode* targetEntry, wxXmlNode* mergeEntry );

        ~MergeData( );

        void SetTargetEntry( wxXmlNode* targetEntry );

        void SetMergeEntry( wxXmlNode* mergeEntry );

        wxColour GetColour( );

        int cmp( DataTypes type );

        MergeStatus GetStatus( );

        MergeStatus SetStatus( );

        Entry* GetTargetEntry( );

        Entry* GetMergeEntry( );

        wxString GetTargetAttribute( DataTypes type );

        wxString GetMergeAttribute( DataTypes type );

        wxString GetName( );;

    private:
        wxString m_name;
        MergeStatus  m_status;
        Entry* m_targetEntry;
        Entry* m_mergeEntry;
        ComparePanel* m_comparePanel;

    };



    typedef std::vector<MergeData*> MergeEntryList;



    class MergeList
    {
    public:

        MergeList( ComparePanel* parent );

        ~MergeList( );

        void SetTargetRoot( wxXmlNode* targetRoot );

        wxXmlNode* GetTargetRoot( );

        void SetMergeRoot( wxXmlNode* mergeRoot );

        void LoadEntryList( wxXmlNode* node );

        void LoadEntryList( );

        void AddMergeEntryList( wxXmlNode* node );

        MergeData* FindTargetEntryForNewEntry( Entry* entry, DataTypes type );

        void AddMergeToEntryList( wxXmlNode* node );

        void AddMergeToEntryList( );

        MergeEntryList* GetMergeList( );

        void  SetComparePanel( ComparePanel* comparePanel );

        void SetStatus( );

        MergeStatus  GetStatus( int i );

        void Clear( );

    private:
        ComparePanel* m_comparePanel;
        MergeEntryList m_mergeList;
        wxXmlNode* m_targetRoot;
        wxXmlNode* m_mergeRoot;
    };
}
#endif