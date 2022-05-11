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

#include "tinyxml2.h"

using namespace tinyxml2;

XMLIterator::XMLIterator( XMLElement* parent, bool decend )
{
    m_iterator = ( XMLIterator* )0;
    m_parent = parent;
    m_decend = decend;
    m_currElement = 0;
    m_firstDone = false;
}

XMLIterator::~XMLIterator( )
{
}

XMLElement* XMLIterator::First( )
{
    m_firstDone = true;
    // get the first child and save the location
    m_currElement = m_parent->FirstChildElement( );

    // if the currElement is null there is noting to iterate
    if ( !m_currElement )
    {
        return m_currElement;
    }
    if ( m_currElement->NoChildren( ) )
    {
        // if the currElement has no children return it and set its sibling as
        // curr
        XMLElement* retElement = m_currElement;

        m_currElement = retElement->NextSiblingElement( );
        return retElement;
    }
    else
    {
        // if it has children setup a next level iterator and return the
        // currElement
        XMLElement* retElement = m_currElement;
        if ( m_decend )
        {
            m_iterator = new XMLIterator( m_currElement );
        }
        m_currElement = retElement->NextSiblingElement( );
        return retElement;
    }
}
XMLElement* XMLIterator::Next( )
{
    if ( !m_firstDone )
    {
        return First( );
    }
    // if there is an iterator defined then drill down to process
    if ( m_iterator )
    {
        XMLElement* nextElement = m_iterator->Next( );
        if ( nextElement )
        {
            return nextElement;
        }
        // if there is no next element then we are thru processing
        // this elements children; go to the next one.

        if ( m_iterator )
        {
            delete m_iterator;
            m_iterator = 0;
        }
    }

    if ( !m_currElement )
    {
        return m_currElement;
    }

    if ( m_currElement->NoChildren( ) )
    {
        XMLElement* retElement = m_currElement;
        m_currElement = retElement->NextSiblingElement( );
        return retElement;
    }
    else
    {
        XMLElement* retElement = m_currElement;
        if ( m_decend )
        {
            m_iterator = new XMLIterator( m_currElement );
        }
        m_currElement = retElement->NextSiblingElement( );
        return retElement;
    }
}


/**
 * @brief cout a brief id of the xml node
 *
 * @param ele
 **************************************************/
void IDElement( XMLElement* ele )
{
    const char* name = ele->Name( );
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
        std::cout << "XMLElement " << name << " label " << classification.GetLabel( ) << "\n";
        break;
    }
   case  NT_Stamp:
    {
        Stamp stamp( ele );
        std::cout << "XMLElement " << name << "  ID" << stamp.GetID( ) << "  Name " << stamp.GetName( ) << "\n";
        break;
    }
   case  NT_Specimen:
    {
        Specimen item( ele );
        std::cout << "XMLElement " << name << "  Type " << item.GetType( ) << "  Condition " << item.GetCondition( ) << "\n";
        break;
    }
   case  NT_CatalogCode:
    {
        CatalogCode code( ele );
        std::cout << "XMLElement " << name << "  Type " << code.GetCatalog( ) << "  ID " << code.GetID( ) << "\n";
        break;
    }
    default:
    {
        std::cout << "XMLElement " << name << "  Unknown \n";

        break;
    }

    }
}

    /**
     * @brief is the specified XMLElement of specified type
     *
     * @param ele  element of interest
     * @param type  element type
     * @return true  if a match
     **************************************************/
    bool IsNodeType( XMLElement * ele, NodeType type )
    {
        return !NodeNameStrings.Item( type ).Cmp( ele->Value( ) );
    }


// NodeType FindNodeType(XMLElement *element)
// {
//     wxString name = element->Name();

//     int cnt = NodeNameStrings.GetCount();
//     for (int i = 0; i < cnt; i++)
//     {
//         if (!name.Cmp(NodeNameStrings.Item(i)))
//         {
//             return (NodeType)i;
//         }
//     }
//     return (NodeType)-1;
// };

// void AddStamp(XMLElement *child)
// {
//     AddStamp(Root(), child);
// }

void AddStamp( XMLElement* parent, XMLElement* child, int level )
{
    level++;
    wxString name = child->Name( );
    wxString parentName = parent->Name( );
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
            parent->InsertEndChild( child );
            return;
        }
        else
        {
            //            std::cout << "     SortType: " << NodeNameStrings[ sortType ]
            //                << "\n";
            wxString nodeName = NodeNameStrings[ sortType ];
            wxString name = stamp.GetClassificationName( &stamp, sortType );
            const char* nameStr = name.fn_str( );
            const char* nodeNameStr = nodeName.fn_str( );
            //             std::cout << "     Looking for " << nodeNameStr << " with Name "
            //                 << nameStr << "\n";

            XMLElement* nextNode = parent->FirstChildElement( nodeNameStr );
            while ( nextNode )
            {
                const char* attr = nextNode->Attribute( "Name", nameStr );
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

            nextNode = parent->InsertNewChildElement( nodeNameStr );
            nextNode->SetAttribute( "Name", nameStr );

            AddStamp( nextNode, child, level );
            return;
        }
    }
}

XMLElement* MoveStamp( XMLElement* newParent, XMLElement* child )
{
    if ( newParent == child )
    {
        // can't be a child of itself
        return ( XMLElement* )0;
    }

    XMLElement* parent = newParent->Parent( )->ToElement( );
    while ( parent )
    {
        if ( child == parent )
        {
            // child can't be an ancestor of itself
            return ( XMLElement* )0;
        }
        parent = parent->Parent( )->ToElement( );
    }
    // Make a copy of the old child and insert it
    XMLNode* newChildNode = child->DeepClone( ( XMLDocument* )0 );
    XMLElement* newChild = newChildNode->ToElement( );
    newParent->InsertEndChild( newChild );

    parent = child->Parent( )->ToElement( );
    parent->DeleteChild( child );
    return newChild;
}

void SortData( XMLElement* newRoot, XMLElement* child )
{
    while ( child )
    {
        if ( !NodeNameStrings[ NT_Stamp ].Cmp( child->Name( ) ) )
        {
            // Make a copy of the old child in the new doc and insert it
            XMLNode* newChildNode = child->DeepClone( ( XMLDocument* )newRoot->GetDocument( ) );
            XMLElement* newChild = newChildNode->ToElement( );
            AddStamp( newRoot, newChild );
        }
        else
        {
            // if this wasn't a stamp node we will just decend in the hierachy
            if ( !child->NoChildren( ) )
            {
                SortData( newRoot, child->FirstChildElement( ) );
            }
        }
        child = child->NextSiblingElement( );
        ;
    }
}
