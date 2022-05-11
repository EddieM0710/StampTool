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
#include "album/LayoutNode.h"
#include "album/Stamp.h"

namespace Utils {

    class StampLink
    {
    public:
        StampLink( Layout::Stamp* albumStamp ) { m_albumStamp = albumStamp; };
        ~StampLink( ) {};

        inline wxTreeItemId GetAlbumtTreeID( ) { return m_albumTreeID; };
        inline void SetAlbumTreeID( wxTreeItemId id ) { m_albumTreeID = id; };

        inline Layout::Stamp* GetAlbumStamp( ) { return m_albumStamp; };
        inline void SetAlbumStamp( Layout::Stamp* stamp ) { m_albumStamp = stamp; };

        inline wxTreeItemId GetCatTreeID( ) { return m_catTreeID; };
        inline void SetCatTreeID( wxTreeItemId id ) { m_catTreeID = id; };

        inline wxXmlNode* GetCatStamp( ) { return m_catStamp; };
        inline void SetCatStamp( wxXmlNode* stamp ) { m_catStamp = stamp; };

        inline wxString GetID( ) { return m_albumStamp->GetAttrStr( Layout::AT_ID ); };
        inline bool IsStamp( wxString id ) { return !id.Cmp( GetID( ) ); };

        void Update(wxTreeItemId catID, wxTreeItemId albumID);


    private:
        StampLink( );
        wxTreeItemId m_albumTreeID;
        Layout::Stamp* m_albumStamp;
        wxTreeItemId m_catTreeID;
        wxXmlNode* m_catStamp;

    };

    typedef std::vector<StampLink*> StampLinkList;

    class StampList
    {
    public:
        int FindStamp( wxString stampID );
        StampLink* AddStamp( Layout::Stamp* stampID );
        void SetCatTreeID( wxString stampID, wxTreeItemId treeID );
        bool GetCatTreeID( wxString stampID, wxTreeItemId& treeID );
        void SetCatStamp( wxString stampID, wxXmlNode* catStamp );
        wxXmlNode* GetCatStamp( wxString stampID );
        StampLink* GetStampLink( wxString stampID );
    private:
        StampLinkList m_list;
    };
}
#endif
