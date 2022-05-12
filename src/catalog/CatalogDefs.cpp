
/**
 * @file Defs.cpp
 * @author Eddie Monroe (you@domain.com)
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 */

 // For compilers that support precompilation, includes "wx/wx.h".
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
//#include "catalog/CatalogDefs.h"
// #include "catalog/Speciman.h"
#include "catalog/Stamp.h"
// #include "catalog/Classification.h"
// #include "CatalogCode.h"

namespace Catalog {

    /**
     * @brief Global pointer to CatalogData data object
     *
     */



    CatalogData* GetCatalogData( void )
    {
        return GetCatalogData( );
    };
    void SetCatalogData( CatalogData* catalogData )
    {
        GetGeneratorData( )->SetCatalogData( catalogData );
    };

    CatalogData* NewCatalogData( )
    {
        return ( new CatalogData( ) );
    };

    const wxString ST_CheckedStatusStrings[ ST_NbrCheckedStatusTypes ]
        = { wxT( "Checked" ), wxT( "Unchecked" ) };

    const wxString ST_InventoryStatusStrings[ ST_NbrInventoryStatusTypes ]
        = { wxT( "None" ), wxT( "Missing" ), wxT( "Ordered" ), wxT( "Own" ), wxT( "Own Variant" ), wxT( "Exclude" ) };


    const wxString FT_FormatStrings[ FT_NbrTypes ]
        = { wxT( "Unknown" ),
            wxT( "Stamp" ),
            wxT( "Se-tenant" ),
            wxT( "Mini Sheet" ),
            wxT( "Souvenir Sheet" ),
            wxT( "Booklet" ),
            wxT( "Booklet Pane" ),
            wxT( "Gutter Pair" ),
            wxT( "Stamp with Attached Label" ),
            wxT( "Tete-Beche" ) };

    const wxString ET_EmissionStrings[ ET_NbrTypes ]
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

    const wxString DT_DataNames[ DT_NbrTypes ] = {
        wxT( "ID Nbr" ),      wxT( "Name" ),          wxT( "Country" ),
        wxT( "Series" ),      wxT( "Catalog Codes" ), wxT( "Issued on" ),
        wxT( "Expiry date" ), wxT( "Width" ),         wxT( "Height" ),
        wxT( "Paper" ),       wxT( "Watermark" ),     wxT( "Emission" ),
        wxT( "Format" ),      wxT( "Perforation" ),   wxT( "Printing" ),
        wxT( "Gum" ),         wxT( "Currency" ),      wxT( "FaceValue" ),
        wxT( "Print run" ),   wxT( "Variant" ),       wxT( "Score" ),
        wxT( "Accuracy" ),    wxT( "Colors" ),        wxT( "Themes" ),
        wxT( "Description" ), wxT( "Link" ),          wxT( "Checked" ),
        wxT( "Inventory" ), wxT( "Background" )
    };

    const wxString DT_XMLDataNames[ DT_NbrTypes ] = {
        wxT( "ID_Nbr" ),      wxT( "Name" ),         wxT( "Country" ),
        wxT( "Series" ),      wxT( "Catalog_Codes" ), wxT( "Issued_on" ),
        wxT( "Expiry_date" ), wxT( "Width" ),         wxT( "Height" ),
        wxT( "Paper" ),       wxT( "Watermark" ),     wxT( "Emission" ),
        wxT( "Format" ),      wxT( "Perforation" ),   wxT( "Printing" ),
        wxT( "Gum" ),         wxT( "Currency" ),      wxT( "FaceValue" ),
        wxT( "Print_run" ),   wxT( "Variant" ),       wxT( "Score" ),
        wxT( "Accuracy" ),    wxT( "Colors" ),        wxT( "Themes" ),
        wxT( "Description" ), wxT( "Link" ),          wxT( "CheckedStatus" ),
        wxT( "InventoryStatus" ),  wxT( "Background" )
    };

    wxString CatalogBaseNames[ NT_NbrTypes ] = {
        "Catalog" ,
        "Country" ,
        "Period"  ,
        "Decade" ,
        "Year" ,
        "Emission" ,
        "Status" ,
        "Condition" ,
        "Stamp" ,
        "Specimen" ,
        "CatalogCode" };

    const wxString CC_CatalogCodeNames[ CC_NbrTypes ]
        = { wxT( "ID" ), wxT( "Country" ), wxT( "Catalog" ), };

    void InitCatalogDefs( )
    {

    }



    /**
     * @brief String name used for wxXmlNodes.
     *
     */
    const wxString CT_Names[ CT_NbrTypes ] = { wxT( "Name" ),
    wxT( "PreferredCatalog" ), wxT( "ImageDirectory" ) };

    const wxString ItemDataNames[ IDT_NbrTypes ]
        = { wxT( "Type" ), wxT( "Condition" ), wxT( "Value" ), wxT( "Location" ),
            wxT( "Remarks" ) };



    CatalogBaseType FindCatalogBaseType( wxString name )
    {
        wxString baseName;

        for ( int i = 0; i < NT_NbrTypes; i++ )
        {
            baseName = CatalogBaseNames[ i ];
            if ( !name.Cmp( baseName ) )
            {
                return ( CatalogBaseType )i;
            }
        }
        return ( CatalogBaseType )-1;
    };


    // /**
    //  * @brief cout a brief id of the xml node
    //  *
    //  * @param ele
    //  **************************************************/
    // void IDElement( wxXmlNode* ele )
    // {
    //     const char* name = ele->GetName( );
    //     Catalog::CatalogBaseType nodeType = FindCatalogBaseType( name );

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
    //     case  NT_Stamp:
    //     {
    //         Stamp stamp( ele );
    //         std::cout << "wxXmlNode " << name << "  ID" << stamp.GetID( ) << "  Name " << stamp.GetName( ) << "\n";
    //         break;
    //     }
    //     case  NT_Specimen:
    //     {
    //         Specimen item( ele );
    //         std::cout << "wxXmlNode " << name << "  Type " << item.GetType( ) << "  Condition " << item.GetCondition( ) << "\n";
    //         break;
    //     }
    //     case  NT_CatalogCode:
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

    /**
     * @brief is the specified wxXmlNode of specified type
     *
     * @param ele  element of interest
     * @param type  element type
     * @return true  if a match
     **************************************************/
    bool IsCatalogBaseType( wxXmlNode* ele, CatalogBaseType type )
    {
        return !CatalogBaseNames[ type ].Cmp( ele->GetName( ) );
    }


    // CatalogBaseType FindCatalogBaseType( wxXmlNode* element )
    // {
    //     wxString name = element->GetName( );

    //     int cnt = CatalogBaseNames.GetCount( );
    //     for ( int i = 0; i < cnt; i++ )
    //     {
    //         if ( !name.Cmp( CatalogBaseNames.Item( i ) ) )
    //         {
    //             return ( CatalogBaseType )i;
    //         }
    //     }
    //     return ( CatalogBaseType )-1;
    // };

    // void AddStamp(wxXmlNode *child)
    // {
    //     AddStamp(Root(), child);
    // }

    void AddStamp( wxXmlNode* parent, wxXmlNode* child, int level )
    {
        level++;
        wxString childName = child->GetName( );
        wxString parentName = parent->GetName( );
        CatalogBaseType parentType = FindCatalogBaseType( parentName );
        //    std::cout << "AddStamp  ParentName:" << parentName
        //        << "  ParentType:" << CatalogBaseNames[ parentType ]
        //        << "  ChildName:" << childName << "  level" << level << "\n";
        if ( childName == CatalogBaseNames[ NT_Stamp ] )
        {
            Catalog::Stamp stamp( child );
            Catalog::CatalogBaseType sortType =
                ( Catalog::CatalogBaseType )GetSettings( )->GetNextSortClassification(
                    ( int )parentType );
            if ( ( sortType < NT_Catalog ) || ( sortType >= NT_Stamp ) )
            {
                wxString id = stamp.GetID();
                long a;
                int pos;
                pos = id.find(' ');
                id = id.substr(pos);
                id.ToLong(&a);
                //std::cout << "     InsertChild "<< " id:" << id << "  Name:" << stamp.GetName() << "\n";
                
                // if the sort type is not one of the classification node types
                // then add it here. All stamps and their children get added here.
                parent->AddChild( child );
                return;
            }
            else
            {
//                std::cout << "     SortType: " << CatalogBaseNames[ sortType ]  << "\n";
                wxString nodeName = CatalogBaseNames[ sortType ];
                wxString name = stamp.GetClassificationName( &stamp, sortType );
                const char* nodeNameStr = nodeName;
//                std::cout << "     Looking for " << nodeNameStr << " with Name " << name << "\n";

                wxXmlNode* nextNode = Utils::FirstChildElement( parent, nodeNameStr );
                while ( nextNode )
                {
                    wxString attr = Utils::GetAttrStr( nextNode, "Name" );
                    if ( !attr.IsEmpty( ) )
                    {
                        if ( !attr.Cmp( name ) )
                        {
//                            std::cout << "     Found it \n";
                            AddStamp( nextNode, child, level );
                            return;
                        }
                    }
                    nextNode = nextNode->GetNext( );
                }
                // couldn't find it so add it
            //    std::cout << "     Adding it: " << nodeNameStr << " with Name "
            //        << name << "\n";

                nextNode = Utils::NewNode( parent, nodeNameStr );
                Utils::SetAttrStr( nextNode, "Name", name );

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

    wxXmlNode* InsertStamp( wxXmlNode* sibling, wxXmlNode* child, bool after )
    {
        if ( sibling == child )
        {
            // can't be a child of itself
            return ( wxXmlNode* )0;
        }

        // Make a copy of the old child and insert it
        wxXmlNode* newChildNode = new wxXmlNode( *child );
        wxXmlNode* newChild = newChildNode;
        wxXmlNode* parent = sibling->GetParent();

        if ( after )
        {
            if ( !parent->InsertChildAfter( newChild, sibling ) )
            {
                return ( wxXmlNode* )0;;
            }
        }
        else
        {
            if ( !parent->InsertChild( newChild, sibling ) )
            {
                return ( wxXmlNode* )0;;
            }
        }

        wxXmlNode* previousParent = child->GetParent( );
        previousParent->RemoveChild( child );
        return newChild;
    }


    void SortData( wxXmlNode* newRoot, wxXmlNode* parent )
    {
        // wxString name = parent->GetAttribute(DT_XMLDataNames[ DT_Name ]);
        // std::cout << "SortData   Parent Name:" << name << "\n";

        wxXmlNode* child = parent->GetChildren( );
        while ( child )
        {
            // wxString name = child->GetAttribute(DT_XMLDataNames[ DT_Name ]);
            // std::cout << "SortData   child Name:" << name << "\n";

            if ( !CatalogBaseNames[ NT_Stamp ].Cmp( child->GetName( ) ) )
            {
                // Make a copy of the old child in the new doc and insert it
                wxXmlNode* newChildNode = new wxXmlNode( *child );
                AddStamp( newRoot, newChildNode, 0 );
            }
            else
            {
                SortData( newRoot, child);
            }
            child = child->GetNext( );
            ;
        }
    }

    CatalogBaseType FindCatalogBaseType( wxXmlNode* element )
    {
        wxString name = element->GetName( );

        for ( int i = 0; i < NT_NbrTypes; i++ )
        {
            if ( !name.Cmp( CatalogBaseNames[ i ] ) )
            {
                return ( CatalogBaseType )i;
            }
        }
        return ( CatalogBaseType )-1;
    };
}