
/**
 * @file Defs.cpp
 * @author Eddie Monroe ( you@domain.com )
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright ( c ) 2021
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
 *
 */


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "utils/Project.h"
#include "utils/Settings.h"
#include "utils/XMLUtilities.h"
#include "Defs.h"
#include "catalog/CatalogVolume.h"
#include "catalog/Entry.h"

namespace Catalog {

    wxString CatalogBaseNames[ NT_NbrTypes ] = {
        "Catalog" ,
        "Country" ,
        "Period"  ,
        "Decade" ,
        "Year" ,
        "Emission" ,
        "Status" ,
        "Condition" ,
        "Entry" ,
        "Specimen" ,
        "CatalogCode",
        "None" };

    const wxString CatalogCodeNames[ CC_NbrTypes ]
        = { wxT( "ID" ), wxT( "Country" ), wxT( "Catalog" ) };

    const wxString CheckedStatusStrings[ ST_NbrCheckedStatusTypes ]
        = { wxT( "Checked" ), wxT( "Unchecked" ) };

    /**
     * @brief String name used for wxXmlNodes.
     *
     */
    const wxString ClassificationNames[ CT_NbrTypes ] = { wxT( "Name" ),
    wxT( "PreferredCatalog" ), wxT( "ImageDirectory" ) };

    const wxString DataTypeNames[ DT_NbrTypes ] = {
        wxT( "ID Nbr" ),      wxT( "Name" ),          wxT( "Country" ),
        wxT( "Series" ),      wxT( "Catalog Codes" ), wxT( "Issued on" ),
        wxT( "Expiry date" ), wxT( "Width" ),         wxT( "Height" ),
        wxT( "Paper" ),       wxT( "Watermark" ),     wxT( "Emission" ),
        wxT( "Format" ),      wxT( "Perforation" ),   wxT( "Printing" ),
        wxT( "Gum" ),         wxT( "Currency" ),      wxT( "FaceValue" ),
        wxT( "Print run" ),   wxT( "Variant" ),       wxT( "Score" ),
        wxT( "Accuracy" ),    wxT( "Colors" ),        wxT( "Themes" ),
        wxT( "Description" ), wxT( "Link" ),       //   wxT( "Checked" ), 
        wxT( "Inventory" ), wxT( "StampMount" ), wxT( "Background" )
    };

    const wxString EmissionStrings[ ET_NbrTypes ]
        = { wxT( "Unknown" ),
            wxT( "Commemorative" ),
            wxT( "Definitive" ),
            wxT( "Hunting Permit" ),
            wxT( "Revenue" ),
            wxT( "Air Post" ),
            wxT( "Air Post Official" ),
            wxT( "Air Post Semi-Postal" ),
            wxT( "ATM labels" ),
            wxT( "Cinderella" ),
            wxT( "Illegal" ),
            wxT( "Insured Letter" ),
            wxT( "Military" ),
            wxT( "Newspaper" ),
            wxT( "Official" ),
            wxT( "Parcel Post" ),
            wxT( "Personal Delivery" ),
            wxT( "Personalized" ),
            wxT( "Postage Due" ),
            wxT( "Postal Tax" ),
            wxT( "Precancelled" ),
            wxT( "Private" ),
            wxT( "Regional" ),
            wxT( "Registration" ),
            wxT( "Semi-Postal" ),
            wxT( "War Tax" ) };

    const wxString FormatStrings[ FT_NbrTypes ]
        = { wxT( "Unknown" ),
            wxT( "Stamp" ),
            wxT( "Se-tenant" ),
            wxT( "Mini Sheet" ),
            wxT( "Souvenir Sheet" ),
            wxT( "Booklet" ),
            wxT( "Booklet Pane" ),
            wxT( "Gutter Pair" ),
            wxT( "Entry with Attached Label" ),
            wxT( "Tete-Beche" ) };

    const wxString InventoryStatusStrings[ ST_NbrInventoryStatusTypes ]
        = { wxT( "None" ), wxT( "Missing" ), wxT( "Ordered" ), wxT( "Own" ), wxT( "Own Variant" ), wxT( "Exclude" ) };


    const wxString ItemDataNames[ IDT_NbrTypes ]
        = { wxT( "Collection" ), wxT( "Status" ), wxT( "Type" ), wxT( "Condition" ), wxT( "Value" ), wxT( "Location" ),
            wxT( "Remarks" ) };


    const wxString XMLDataNames[ DT_NbrTypes ] = {
        wxT( "ID_Nbr" ),      wxT( "Name" ),         wxT( "Country" ),
        wxT( "Series" ),      wxT( "Catalog_Codes" ), wxT( "Issued_on" ),
        wxT( "Expiry_date" ), wxT( "Width" ),         wxT( "Height" ),
        wxT( "Paper" ),       wxT( "Watermark" ),     wxT( "Emission" ),
        wxT( "Format" ),      wxT( "Perforation" ),   wxT( "Printing" ),
        wxT( "Gum" ),         wxT( "Currency" ),      wxT( "FaceValue" ),
        wxT( "Print_run" ),   wxT( "Variant" ),       wxT( "Score" ),
        wxT( "Accuracy" ),    wxT( "Colors" ),        wxT( "Themes" ),
        wxT( "Description" ), wxT( "Link" ),        //  wxT( "CheckedStatus" ), 
        wxT( "InventoryStatus" ),  wxT( "StampMount" ), wxT( "Background" )
    };


    // find a place in the dest to put thr child
    void AddEntry( wxXmlNode* parent, wxXmlNode* child, int level )
    {
        level++;

        wxString childName = child->GetName( );
        wxString parentName = parent->GetName( );
        CatalogBaseType parentType = FindCatalogBaseType( parentName );
        std::cout << "parent " << parentName << " type " << parentType << "   child " << childName << "\n";
        if ( level > 6 )
        {
            std::cout << "Infinite loop\n";
        }
        // child has to be an entry
        if ( childName == CatalogBaseNames[ NT_Entry ] )
        {
            Catalog::Entry entry( child );
            Catalog::CatalogBaseType sortType =
                ( Catalog::CatalogBaseType ) GetSettings( )->GetNextSortClassification( ( int ) parentType );
            std::cout << "parent next sortType" << CatalogBaseNames[ sortType ] << "\n";
            if ( ( sortType < NT_Catalog ) || ( sortType >= NT_Entry ) )
            {
                wxString id = entry.GetID( );
                long a;
                int pos;
                pos = id.find( ' ' );
                id = id.substr( pos );
                id.ToLong( &a );

                // if the sort type is not one of the classification node types
                // then add it here. All entrys and their children get added here.
                parent->AddChild( child );
                return;
            }
            else
            {
                wxString nodeName = CatalogBaseNames[ sortType ];
                wxString name = entry.GetClassificationName( &entry, sortType );
                const char* nodeNameStr = nodeName;

                wxXmlNode* nextNode = Utils::FirstChildElement( parent, nodeNameStr );
                while ( nextNode )
                {
                    wxString attr = Utils::GetAttrStr( nextNode, "Name" );
                    if ( !attr.IsEmpty( ) )
                    {
                        if ( !attr.Cmp( name ) )
                        {
                            //Found the classification+ it goes in 
                            AddEntry( nextNode, child, level );
                            return;
                        }
                    }
                    nextNode = nextNode->GetNext( );
                }

                // if we got here then we didn't find a ckassificaeion qith that name
                // Insert it here as nextNode in order
                // look for a child it can go after
                wxXmlNode* childNode = parent->GetChildren( );
                bool found = false;
                nextNode = new wxXmlNode( 0, wxXML_ELEMENT_NODE, nodeNameStr );
                Utils::SetAttrStr( nextNode, "Name", name );
                while ( childNode && !found )
                {
                    wxString childNodeName = Utils::GetAttrStr( childNode, "Name" );
                    if ( name.Cmp( childNodeName ) < 0 )
                    {
                        parent->InsertChild( nextNode, childNode );
                        nextNode->SetParent( parent );
                        found = true;
                    }
                    childNode = childNode->GetNext( );;
                }
                if ( !found )
                {
                    //either no children or couldn't figure out where it goes so just add it to end
                    parent->AddChild( nextNode );

                    nextNode->SetParent( parent );
                }
                std::cout << "nextNode " << nextNode->GetName( ) <<
                    Utils::GetAttrStr( nextNode, "Name" ) << "\n";
                AddEntry( nextNode, child, level );
                return;
            }
        }
    }

    CatalogBaseType FindCatalogBaseType( wxXmlNode* element )
    {
        wxString name = element->GetName( );

        for ( int i = 0; i < NT_NbrTypes; i++ )
        {
            if ( !name.Cmp( CatalogBaseNames[ i ] ) )
            {
                return ( CatalogBaseType ) i;
            }
        }
        return ( CatalogBaseType ) -1;
    };

    CatalogBaseType FindCatalogBaseType( wxString name )
    {
        wxString baseName;

        for ( int i = 0; i < NT_NbrTypes; i++ )
        {
            baseName = CatalogBaseNames[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( CatalogBaseType ) i;
            }
        }
        return ( CatalogBaseType ) -1;
    };

    EmissionType FindEmissionType( wxString name )
    {
        wxString baseName;
        for ( int i = 0; i < ET_NbrTypes; i++ )
        {
            baseName = EmissionStrings[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( EmissionType ) i;
            }
        }
        return ( EmissionType ) -1;
    };

    FormatType FindFormatType( wxString name )
    {
        wxString baseName;
        for ( int i = 0; i < FT_NbrTypes; i++ )
        {
            baseName = FormatStrings[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( FormatType ) i;
            }
        }
        return ( FormatType ) -1;
    };


    InventoryStatusType FindStatusType( wxString name )
    {
        wxString baseName;
        for ( int i = 0; i < ST_NbrInventoryStatusTypes; i++ )
        {
            baseName = InventoryStatusStrings[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( InventoryStatusType ) i;
            }
        }
        return ( InventoryStatusType ) ST_None;
    };

    /**
     * @brief is the specified wxXmlNode of specified type
     *
     * @param ele  element of interest
     * @param type  element type
     * @return true  if a match
     */
    bool IsCatalogBaseType( wxXmlNode* ele, CatalogBaseType type )
    {
        return !CatalogBaseNames[ type ].Cmp( ele->GetName( ) );
    }

    void InitCatalogDefs( )
    {

    }



    wxXmlNode* InsertEntry( wxXmlNode* sibling, wxXmlNode* child, bool after )
    {
        if ( sibling == child )
        {
            // can't be a child of itself
            return ( wxXmlNode* ) 0;
        }

        // Make a copy of the old child and insert it
        wxXmlNode* newChildNode = new wxXmlNode( *child );
        wxXmlNode* newChild = newChildNode;
        wxXmlNode* parent = sibling->GetParent( );

        if ( after )
        {
            if ( !parent->InsertChildAfter( newChild, sibling ) )
            {
                return ( wxXmlNode* ) 0;;
            }
        }
        else
        {
            if ( !parent->InsertChild( newChild, sibling ) )
            {
                return ( wxXmlNode* ) 0;;
            }
        }

        wxXmlNode* previousParent = child->GetParent( );
        previousParent->RemoveChild( child );
        return newChild;
    }

    wxXmlNode* MoveEntry( wxXmlNode* newParent, wxXmlNode* child )
    {
        if ( newParent == child )
        {
            // can't be a child of itself
            return ( wxXmlNode* ) 0;
        }

        wxXmlNode* parent = newParent->GetParent( );
        while ( parent )
        {
            if ( child == parent )
            {
                // child can't be an ancestor of itself
                return ( wxXmlNode* ) 0;
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

    // search thru the source nodes to find an entry. When found pur it into dest
    void SortData( wxXmlNode* destNode, wxXmlNode* parent )
    {
        wxString name = parent->GetAttribute( XMLDataNames[ DT_Name ] );

        wxXmlNode* child = parent->GetChildren( );
        while ( child )
        {
            wxString name = child->GetAttribute( XMLDataNames[ DT_Name ] );

            if ( !CatalogBaseNames[ NT_Entry ].Cmp( child->GetName( ) ) )
            {
                // Make a copy of the old child in the new doc and insert it
                wxXmlNode* newChildNode = new wxXmlNode( *child );
                AddEntry( destNode, newChildNode, 0 );
            }
            else
            {
                SortData( destNode, child );
            }
            child = child->GetNext( );
            ;
        }
    }

}