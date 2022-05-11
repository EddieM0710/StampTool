/**
 * @file XMLIterator.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/string.h>
#include <iostream>

#include "CatalogCode.h"
#include "Classification.h"
#include "Defs.h"
#include "Node.h"
#include "Settings.h"
#include "Specimen.h"
#include "Stamp.h"
#include "XMLUtilities.h"

#include "wx/xml/xml.h"

//


wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name )
{
    wxXmlNode* child = node->GetChildren();
    while( child )
    {
        if (!child->GetName().Cmp( name ) )
        {
            return child;
        }
        child = child->GetNext();
    }
    return (wxXmlNode*)0;
}

/**
 * @brief cout a brief id of the xml node
 *
 * @param ele
 **************************************************/
void IDElement( wxXmlNode* ele )
{
    const char* name = ele->GetName( );
    NodeType nodeType = FindNodeType( name );

    switch ( nodeType )
    {
    case  NT_Catalog:
    case  NT_Country:
    case  NT_Period:
    case  NT_Decade:
    case  NT_Year:
    case  NT_Emission:
    case  NT_Status:
    case  NT_Condition:
    {
        Classification classification( ele );
        std::cout << "wxXmlNode " << name << " label " << classification.GetLabel( ) << "\n";
        break;
    }
   case  NT_Stamp:
    {
        Stamp stamp( ele );
        std::cout << "wxXmlNode " << name << "  ID" << stamp.GetID( ) << "  Name " << stamp.GetName( ) << "\n";
        break;
    }
   case  NT_Specimen:
    {
        Specimen item( ele );
        std::cout << "wxXmlNode " << name << "  Type " << item.GetType( ) << "  Condition " << item.GetCondition( ) << "\n";
        break;
    }
   case  NT_CatalogCode:
    {
        CatalogCode code( ele );
        std::cout << "wxXmlNode " << name << "  Type " << code.GetCatalog( ) << "  ID " << code.GetID( ) << "\n";
        break;
    }
    default:
    {
        std::cout << "wxXmlNode " << name << "  Unknown \n";

        break;
    }

    }
}

    /**
     * @brief is the specified wxXmlNode of specified type
     *
     * @param ele  element of interest
     * @param type  element type
     * @return true  if a match
     **************************************************/
    bool IsNodeType( wxXmlNode * ele, NodeType type )
    {
        return !NodeNameStrings.Item( type ).Cmp( ele->GetName( ) );
    }


NodeType FindNodeType(wxXmlNode *element)
{
    wxString name = element->GetName();

     int cnt = NodeNameStrings.GetCount();
    for (int i = 0; i < cnt; i++)
    {
        if (!name.Cmp(NodeNameStrings.Item(i)))
        {
            return (NodeType)i;
        }
    }
    return (NodeType)-1;
};

// void AddStamp(wxXmlNode *child)
// {
//     AddStamp(Root(), child);
// }

void AddStamp( wxXmlNode* parent, wxXmlNode* child, int level )
{
    level++;
    wxString name = child->GetName( );
    wxString parentName = parent->GetName( );
    NodeType parentType = FindNodeType( parentName );
    //    std::cout << "AddStamp  ParentName:" << parentName
    //        << "  ParentType:" << NodeNameStrings[ parentType ]
    //        << "  ChildName:" << name << "level" << level << "\n";
    if ( name == NodeNameStrings[ NT_Stamp ] )
    {
        Stamp stamp( child );
        NodeType sortType = ( NodeType )GetSettings( )->GetNextSortClassification(
            ( int )parentType );
        if ( ( sortType < NT_Catalog ) || ( sortType >= NT_Stamp ) )
        {
            //            std::cout << "     InsertChild\n";
                        // if the sort type is not one of the classification node types
                        // then add it here. All stamps and their children get added here.
            parent->AddChild( child );
            return;
        }
        else
        {
            //            std::cout << "     SortType: " << NodeNameStrings[ sortType ]
            //                << "\n";
            wxString nodeName = NodeNameStrings[ sortType ];
            wxString name = stamp.GetClassificationName( &stamp, sortType );
            const char* nameStr = name ;
            const char* nodeNameStr = nodeName ;
            //             std::cout << "     Looking for " << nodeNameStr << " with Name "
            //                 << nameStr << "\n";

            wxXmlNode* nextNode = FirstChildElement( parent, nodeNameStr );
            while ( nextNode )
            {
                wxXmlAttribute* attr = SetAttribute( nextNode, "Name", nameStr );
                if ( attr )
                {
                    //                    std::cout << "     Found it\n";
                    AddStamp( nextNode, child, level );
                    return;
                }
                nextNode = nextNode->NextSiblingElement( );
            }
            // couldn't find it so add it
//            std::cout << "     Adding it: " << nodeNameStr << " with Name "
//                << nameStr << "\n";

            nextNode = NewNode( parent, nodeNameStr );
            nextNode->AddAttribute( "Name", nameStr );

            AddStamp( nextNode, child, level );
            return;
        }
    }
}

wxXmlNode* MoveStamp( wxXmlNode* newParent, wxXmlNode* child )
{
    if ( newParent == child )
    {
        // can't be a child of itself
        return ( wxXmlNode* )0;
    }

    wxXmlNode* parent = newParent->GetParent( );
    while ( parent )
    {
        if ( child == parent )
        {
            // child can't be an ancestor of itself
            return ( wxXmlNode* )0;
        }
        parent = parent->GetParent( );
    }
    // Make a copy of the old child and insert it
    wxXmlNode* newChildNode = new wxXmlNode( *child );
    wxXmlNode* newChild = newChildNode;
    newParent->AddChild( newChild );

    parent = child->GetParent( );
    parent->RemoveChild( child );
    return newChild;
}

void SortData( wxXmlNode* newRoot, wxXmlNode* parent )
{

     wxXmlNode* child = parent->GetChildren( );
    while ( child )
    {
        if ( !NodeNameStrings[ NT_Stamp ].Cmp( child->GetName( ) ) )
        {
            // Make a copy of the old child in the new doc and insert it
            wxXmlNode* newChildNode = new wxXmlNode( *child );
            newRoot->AddChild( newChildNode );
            AddStamp( newRoot, newChildNode );
        }
        else
        {
            // if this wasn't a stamp node we will just decend in the hierachy
          
            if ( !child->GetChildren( ) )
            {
                SortData( newRoot, child );
            }
        }
        child = child->GetNext( );
        ;
    }
}
