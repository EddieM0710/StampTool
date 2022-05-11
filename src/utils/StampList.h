/**
 * @file StampList.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef StampLink_H
#define StampLink_H

#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/treectrl.h>

#include <vector>
#include "design/LayoutBase.h"
#include "design/Stamp.h"

namespace Utils {

    class StampLink
    {
    public:
        StampLink( ) { m_designTreeID = 0; m_catTreeID = 0; };
        ~StampLink( ) { Clear( ); };

        inline wxTreeItemId GetDesignTreeID( ) { return m_designTreeID; };
        inline void SetDesignTreeID( wxTreeItemId id ) { m_designTreeID = id; };

//        inline Design::Stamp* GetAlbumStamp( ) { return m_albumStamp; };
//        inline void SetAlbumStamp( Design::Stamp* stamp ) { m_albumStamp = stamp; };

        inline wxTreeItemId GetCatTreeID( ) { return m_catTreeID; };
        inline void SetCatTreeID( wxTreeItemId id ) { m_catTreeID = id; };

//        inline wxXmlNode* GetCatNode( ) { return m_catNode; };
//        inline void SetCatNode( wxXmlNode* stamp ) { m_catNode = stamp; };

        void Update( wxTreeItemId catID, wxTreeItemId albumID );

        void Clear( );

        inline wxString GetID( );
        inline bool IsStamp( wxString id );

    private:
       // StampLink( );
        wxTreeItemId m_designTreeID;
//        Design::Stamp* m_albumStamp;
        wxTreeItemId m_catTreeID;
//        wxXmlNode* m_catNode;

    };

    typedef std::vector<StampLink*> StampLinkList;

    class StampList
    {
    public:
        StampList( ) {};
        ~StampList( ) { Clear( ); };

        void Clear( );
        int FindStamp( wxString stampID );

        StampLink* AddStamp( wxString stampId );

        void SetCatTreeID( wxString stampID, wxTreeItemId treeID );
        bool GetCatTreeID( wxString stampID, wxTreeItemId& treeID );
        void SetCatNode( wxString stampID, wxXmlNode* catStamp );
//        wxXmlNode* GetCatNode( wxString stampID );
        StampLink* FindStampLink( wxString stampID );
        void ClearCatalogLinks( );

    private:
        StampLinkList m_list;
    };
}
#endif
