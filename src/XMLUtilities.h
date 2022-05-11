/**
 * @file XMLUtilities.h
 * @author Eddie Monroe ()
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 **************************************************/

#ifndef XMLIterator_H
#define XMLIterator_H

#include "wx/xml/xml.h"

//
wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name );

bool IsNodeType( wxXmlNode* ele, NodeType type);
void IDElement( wxXmlNode* ele );


// NodeType FindNodeType(wxXmlNode *element);

void AddStamp( wxXmlNode* child );
void AddStamp( wxXmlNode* parent, wxXmlNode* child, int level = 0 );
wxXmlNode* MoveStamp( wxXmlNode* newParent, wxXmlNode* child );
void SortData( wxXmlNode* newRoot, wxXmlNode* child );

wxXmlNode* NewNode (wxXmlNode* parent, wxString name )
{
    return  new wxXmlNode( parent, wxXML_ELEMENT_NODE, name );

}

wxXmlAttribute* GetAttribute( wxXmlNode* node, wxString attrName )
{
    wxXmlAttribute* attr = node->GetAttributes();
    while (attr)
    {
        if ( !attr->GetName().Cmp( attrName ) )
        {
            return attr;
        }
        attr = attr->GetNext();
    }
}

wxXmlAttribute* SetAttribute( wxXmlNode* node, wxString name, wxString val)
{
    wxXmlAttribute* attr = GetAttribute( node, name);
    if ( attr )
    {
        attr->SetValue(val);
    }
    else
    {
        attr = new wxXmlAttribute( name, val);
        node->AddAttribute(attr);
    }
}

#endif