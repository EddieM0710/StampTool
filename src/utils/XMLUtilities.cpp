/**
 * @file XMLIterator.cpp
 * @author Eddie Monroe ()
 * @brief
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
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

#include <iostream>

#include <wx/string.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include "wx/xml/xml.h"

#include "catalog/CatalogCode.h"
#include "catalog/Classification.h"
#include "Defs.h"
#include "catalog/CatalogBase.h"
#include "utils/Settings.h"
#include "catalog/Specimen.h"
#include "catalog/Entry.h"
#include "utils/XMLUtilities.h"


namespace Utils {


int zIndex = 0;
int frameIndex = 0;
int imageIndex = 0;
int StyleNameIndex = 0;



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
        wxXmlNode* child = node->GetNext( );
        while ( child )
        {
            if ( !child->GetName( ).Cmp( name ) )
            {
                return child;
            }
            child = child->GetNext( );
        }
        return ( wxXmlNode* )0;
    }



    wxXmlNode* NewNode( wxXmlNode* parent, wxString name )
    {
        wxXmlNode* newNode =  new wxXmlNode( 0, wxXML_ELEMENT_NODE, name );
        if ( parent )
        {
            parent->AddChild(newNode);
            newNode->SetParent(parent);
        }
        return newNode;

    }

    wxXmlNode* NewNode( wxXmlDocument* doc, wxString name )
    {
        wxXmlNode* root = new wxXmlNode( NULL, wxXML_ELEMENT_NODE, name );
        doc->SetRoot( root );
        return root;


    }
    // wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name )
    // {
    //     wxXmlNode* child = node->GetChildren();
    //     while ( child )
    //     {
    //         if ( !child->GetName().Cmp(name))
    //         {
    //             return child;
    //         }
    //         child = child->GetNext();
    //     }

    //     return (wxXmlNode*)0;  
    // }

    wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name )
    {
        wxXmlNode* childNode = node->GetChildren( );
        while ( childNode )
        {
            wxString childName = childNode->GetName( );
            if ( !childName.compare( name ) )
            {
                return childNode;
            }
            childNode = childNode->GetNext( );
        }
        return ( wxXmlNode* )0;
    }

    wxXmlAttribute* GetAttribute( wxXmlNode* node, wxString attrName )
    {
        wxXmlAttribute* attr = node->GetAttributes( );
        while ( attr )
        {
//            std::cout << attr->GetName( ) << "=" << attr->GetValue() << "\n";
            if ( !attr->GetName( ).Cmp( attrName ) )
            {
                return attr;
            }
            attr = attr->GetNext( );
        }
    }

    wxString  GetAttrStr( wxXmlNode* node, wxString attrName )
    {
        wxXmlAttribute* attr = GetAttribute( node, attrName );
        if ( attr )
        {
            return attr->GetValue( );;
        }
        return ( wxString )"";
    }

    double GetAttrDbl(  wxXmlNode* node, wxString attrName  )
    {
        double val;
        wxString str = GetAttrStr( node, attrName );
        if ( str.ToDouble( &val ) )
        {
            return val;
        }
        return 0.0;
    }

    void SetAttrStr( wxXmlNode* node, wxString name, wxString val )
    {
        wxXmlAttribute* attr = GetAttribute( node, name );
        if ( attr )
        {
            attr->SetValue( val );
        }
        else
        {
            attr = new wxXmlAttribute( name, val );
            node->AddAttribute( attr );
        }
    }
    
    void SetAttrDbl( wxXmlNode* node, wxString name, double val )
    {
        wxString str = wxString::Format( "%f", val );
        SetAttrStr( node, name, str );
    }

// void SetAttrStr( wxXmlNode* node, wxString name, wxString value )
// {
//     if ( node->HasAttribute( name ) )
//     {
//         node->DeleteAttribute( name );
//     }
//     node->SetAttrStr( name, value );
// }


    void XMLDump( wxXmlDocument* doc )
    {
        wxXmlNode* node = doc->GetRoot( );
        wxString level = "";
        XMLDumpNode( node, level );
    }
    void XMLDumpNode( wxXmlNode* node, wxString level )
    {
        level += "  ";
        wxXmlNode* child = node->GetChildren( );

        while ( child )
        {
            wxString nodeName = child->GetName( );

            // dump everything except CatalogCodes
            if ( nodeName.Cmp("CatalogCode") )
            {
                std::cout << level << nodeName << "  ";

                std::cout << GetAttrStr( child, Catalog::DT_XMLDataNames[ Catalog::DT_ID_Nbr ] ) ;
                std::cout << "  " << GetAttrStr( child, Catalog::DT_XMLDataNames[ Catalog::DT_Name ] ) ;

                // wxXmlAttribute* attr = child->GetAttributes( );
                // while ( attr  )
                // {
                //     wxString name = attr->GetName( );
                //     wxString val = attr->GetValue( );
                //     std::cout << name << ":" << val << " ";
                //     attr = attr->GetNext( );
                // }

                std::cout << "\n";
                if ( child->GetChildren( ) )
                {
                    XMLDumpNode( child, level );
                }
            }
            child = child->GetNext( );
        }
    }


    wxXmlNode* AddNewNode( wxXmlNode* parent, wxXmlNodeType type, const wxString& name )
    {
        wxXmlNode* newChild = new wxXmlNode( NULL, type, name );
        parent->AddChild( newChild );
        return newChild;
    }

    wxXmlNode* FindFirstChildWithPropertyofValue( wxXmlNode* element, wxString& property, wxString& value )
    {
        wxString   	attr;
        wxXmlNode* child = element->GetChildren( );
        while ( child )
        {
            if ( child->GetAttribute( property, &attr ) )
            {
                if ( !value.Cmp( attr ) )
                {
                    return child;
                }
            }
            child = ( wxXmlNode* )child->GetNext( );
        }
        return ( wxXmlNode* )0;
    }

    void AddComment( wxXmlNode* node, wxString name, wxString content )
    {
        wxXmlNode* comment = AddNewNode( node, wxXML_COMMENT_NODE, name );
        comment->SetContent( content );
    }


    void Save( wxXmlDocument* doc, wxString filename )
    {
        bool status = false;

        wxFileOutputStream l_file( filename );

        if ( l_file.IsOk( ) )
        {
            wxTextOutputStream text( l_file );
            wxTextOutputStream* textPtr = &text;
            //process Header
            text << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
            wxXmlNode* root = doc->GetRoot( );
            SaveChild( textPtr, root, "" );
        }
    }
    void SaveAttributes( wxTextOutputStream *text, wxXmlNode* node, wxString level )
    {
        wxXmlAttribute* attr = node->GetAttributes( );
        while ( attr )
        {
            *text << " " << attr->GetName( ) << "=\"" << attr->GetValue( ) << "\"";
            attr = attr->GetNext( );
        }
    }


    void SaveChild( wxTextOutputStream* text, wxXmlNode* node, wxString level )
    {
        wxXmlNodeType type = node->GetType( );
        if ( type == wxXML_COMMENT_NODE )
        {
            *text << "<!-- " << node->GetName( ) << "   " << node->GetContent( ) << "-->\n";
        }
        else
        {
            wxString levelStr = level + "  ";
            wxString name = node->GetName( );
            *text << levelStr << "<" << name << " ";

            SaveAttributes( text, node, levelStr );
            wxString content = node->GetContent( );
            if ( !content.IsEmpty( ) || node->GetChildren( ) )
            {
                *text << ">";
                if ( !content.IsEmpty( ) )
                {
                    *text << levelStr << content << "\n";
                }
                wxXmlNode* child = node->GetChildren( );
                while ( child )
                {
                    SaveChild( text, child, levelStr );
                    child = child->GetNext( );
                }
                *text << levelStr << "</" << name << ">\n";
            }
            else
            {
                *text << " />\n";
            }
        }

    }



char* GetZIndex( char* str )
{
    zIndex++;
    sprintf( str, "%d", zIndex );
    return str;
}

char* GetImageName( char* str )
{
    imageIndex++;
    sprintf( str, "graphics%d", imageIndex );
    return str;
}

char* GetDrawName( char* str )
{
    imageIndex++;
    sprintf( str, "Shape%d", imageIndex );
    return str;
}

char* GetFrameName( char* str )
{
    frameIndex++;
    sprintf( str, "Frame%d", frameIndex );
    return str;
}
wxString GetTextStyleName( wxString& str )
{
    StyleNameIndex++;
    str = wxString::Format( "P%d", StyleNameIndex );
    return str;
}
char* DoubleToMMString( char* str, double nbr )
{
    sprintf( str, "%fmm", nbr );
    return str;
}

char* IntToInchString( char* str, int nbr )
{
    sprintf( str, "%din", nbr );
    return str;
}
}