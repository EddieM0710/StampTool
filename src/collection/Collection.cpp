

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "collection/Collection.h"

namespace Inventory {

    void Collection::Save( wxXmlNode* xmlNode )
    {
        Utils::SetAttrStr( xmlNode, "Name", m_name );
        Utils::SetAttrStr( xmlNode, "Description", m_description );
        Utils::SetAttrStr( xmlNode, "Location", m_location );

    }

    void Collection::Load( wxXmlNode* xmlNode )
    {
        m_name = xmlNode->GetAttribute( "Name" );
        m_description = xmlNode->GetAttribute( "Description", m_description );
        m_location = xmlNode->GetAttribute( "Location", m_location );
    }
}