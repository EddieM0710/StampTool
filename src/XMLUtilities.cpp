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

XMLIterator::XMLIterator( wxXmlNode* parent, bool decend )
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

wxXmlNode* XMLIterator::First( )
{
    m_firstDone = true;
    // get the first child and save the location
    m_currElement = m_parent->GetChildren( );

    // if the currElement is null there is noting to iterate
    if ( !m_currElement )
    {
        return m_currElement;
    }
    if ( m_currElement->GetChildren( ) )
    {
        // if the currElement has no children return it and set its sibling as
        // curr
        wxXmlNode* retElement = m_currElement;

        m_currElement = retElement->GetNext( );
        return retElement;
    }
    else
    {
        // if it has children setup a next level iterator and return the
        // currElement
        wxXmlNode* retElement = m_currElement;
        if ( m_decend )
        {
            m_iterator = new XMLIterator( m_currElement );
        }
        m_currElement = retElement->GetNext( );
        return retElement;
    }
}
wxXmlNode* XMLIterator::Next( )
{
    if ( !m_firstDone )
    {
        return First( );
    }
    // if there is an iterator defined then drill down to process
    if ( m_iterator )
    {
        wxXmlNode* nextElement = m_iterator->Next( );
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

    if ( m_currElement->GetChildren( ) )
    {
        wxXmlNode* retElement = m_currElement;
        m_currElement = retElement->GetNext( );
        return retElement;
    }
    else
    {
        wxXmlNode* retElement = m_currElement;
        if ( m_decend )
        {
            m_iterator = new XMLIterator( m_currElement );
        }
        m_currElement = retElement->GetNext( );
        return retElement;
    }
}


// /**
//  * @brief cout a brief id of the xml node
//  *
//  * @param ele
//  **************************************************/
// void IDElement( wxXmlNode* ele )
// {
//     const char* name = ele->GetName( );
//     NodeType nodeType = FindNodeType( name );

//     switch ( nodeType )
//     {
//     case  NT_Catalog:
//     case  NT_Country:
//     case  NT_Period:
//     case  NT_Decade:
//     case  NT_Year:
//     case  NT_Emission:
//     case  NT_Status:
//     case  NT_Condition:
//     {
//         Classification classification( ele );
//         std::cout << "wxXmlNode " << name << " label " << classification.GetLabel( ) << "\n";
//         break;
//     }
//    case  NT_Stamp:
//     {
//         Stamp stamp( ele );
//         std::cout << "wxXmlNode " << name << "  ID" << stamp.GetID( ) << "  Name " << stamp.GetName( ) << "\n";
//         break;
//     }
//    case  NT_Specimen:
//     {
//         Specimen item( ele );
//         std::cout << "wxXmlNode " << name << "  Type " << item.GetType( ) << "  Condition " << item.GetCondition( ) << "\n";
//         break;
//     }
//    case  NT_CatalogCode:
//     {
//         CatalogCode code( ele );
//         std::cout << "wxXmlNode " << name << "  Type " << code.GetCatalog( ) << "  ID " << code.GetID( ) << "\n";
//         break;
//     }
//     default:
//     {
//         std::cout << "wxXmlNode " << name << "  Unknown \n";

//         break;
//     }

//     }
// }



wxXmlNode* GetNext( wxXmlNode* node, wxString name )
{
    wxXmlNode* child = node->GetNext();
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
    CatalogNodeType nodeType = FindCatalogNodeType( name );

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
    bool IsCatalogNodeType( wxXmlNode * ele, CatalogNodeType type )
    {
        return !CatalogNodeNames.Item( type ).Cmp( ele->GetName( ) );
    }


CatalogNodeType FindCatalogNodeType(wxXmlNode *element)
{
    wxString name = element->GetName();

     int cnt = CatalogNodeNames.GetCount();
    for (int i = 0; i < cnt; i++)
    {
        if (!name.Cmp(CatalogNodeNames.Item(i)))
        {
            return (CatalogNodeType)i;
        }
    }
    return (CatalogNodeType)-1;
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
    CatalogNodeType parentType = FindCatalogNodeType( parentName );
    //    std::cout << "AddStamp  ParentName:" << parentName
    //        << "  ParentType:" << CatalogNodeNames[ parentType ]
    //        << "  ChildName:" << name << "level" << level << "\n";
    if ( name == CatalogNodeNames[ NT_Stamp ] )
    {
        Stamp stamp( child );
        CatalogNodeType sortType = ( CatalogNodeType )GetSettings( )->GetNextSortClassification(
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
            //            std::cout << "     SortType: " << CatalogNodeNames[ sortType ]
            //                << "\n";
            wxString nodeName = CatalogNodeNames[ sortType ];
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
                nextNode = nextNode->GetNext( );
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
        if ( !CatalogNodeNames[ NT_Stamp ].Cmp( child->GetName( ) ) )
        {
            // Make a copy of the old child in the new doc and insert it
            wxXmlNode* newChildNode = new wxXmlNode(  *child );
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


wxXmlNode* NewNode (wxXmlNode* parent, wxString name )
{
    return  new wxXmlNode( parent, wxXML_ELEMENT_NODE, name );

}

wxXmlNode* NewNode (wxXmlDocument* doc, wxString name )
{
    wxXmlNode* root =  new wxXmlNode( NULL, wxXML_ELEMENT_NODE, name );
    doc->SetRoot(root);
    return root;
    

}
wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name )
{
    wxXmlNode* child = node->GetChildren();
    while ( child )
    {
        if ( !child->GetName().Cmp(name))
        {
            return child;
        }
        child = child->GetNext();
    }
    
    return (wxXmlNode*)0;  
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

wxString  GetAttributeValue( wxXmlNode* node, wxString attrName  )
{
    wxXmlAttribute* attr = GetAttribute( node, attrName );
    if ( attr )
    {
        return attr->GetValue( );;
    }
    return ( wxString )"";
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


void XMLDump(wxXmlDocument* doc)
{
   wxXmlNode* node =  doc->GetRoot();
   wxString level = "";
   XMLDumpNode(node, level );
}
void XMLDumpNode( wxXmlNode* node, wxString level )
{
    level += "  ";
    wxXmlNode* child = node->GetChildren( );

    while ( child )
    {
       wxString nodeName = child->GetName( );
       std::cout << level << nodeName << "  " ;
        wxXmlAttribute* attr = child->GetAttributes();
        while (attr )
        {
            wxString name = attr->GetName();
            wxString val = attr->GetValue();
            std::cout << name << ":" << val << " ";
            attr = attr->GetNext();
        }
        std::cout << "\n";
        if ( child->GetChildren())
        {
            XMLDumpNode(child,level);
        }
        child = child->GetNext();
   }
}