
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
#include "catalog/CatalogDefs.h"
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
        Utils::Project* project = GetProject( );
        if ( project )
        {
            return project->GetCatalogData( );
        }
        return ( CatalogData* )0;
    };
    void SetCatalogData( CatalogData* catalogData )
    {
        Utils::Project* project = GetProject( );
        if ( project )
        {
            project->SetCatalogData( catalogData );
        }
    };

    CatalogData* NewCatalogData( )
    {
        return ( new CatalogData( ) );
    };

    const wxString ST_StatusStrings[ ST_NbrTypes ]
        = { wxT( "Checked" ), wxT( "Unchecked" ) };

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
        wxT( "Description" ), wxT( "Link" ),          wxT( "Status" ),
        wxT( "Background" )
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
        wxT( "Description" ), wxT( "Link" ),          wxT( "Status" ),
        wxT( "Background" )
    };

    wxArrayString CatalogNodeNames;


    void InitCatalogDefs( )
    {
        CatalogNodeNames.Add( "Catalog" );
        CatalogNodeNames.Add( "Country" );
        CatalogNodeNames.Add( "Period" );
        CatalogNodeNames.Add( "Decade" );
        CatalogNodeNames.Add( "Year" );
        CatalogNodeNames.Add( "Emission" );
        CatalogNodeNames.Add( "Status" );
        CatalogNodeNames.Add( "Condition" );
        CatalogNodeNames.Add( "Stamp" );
        CatalogNodeNames.Add( "Specimen" );
        CatalogNodeNames.Add( "CatalogCode" );
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


    const wxString CC_CatalogCodeNames[ CC_NbrTypes ]
        = { wxT( "ID" ), wxT( "Country" ), wxT( "Catalog" ), };


    CatalogNodeType FindCatalogNodeType( wxString name )
    {
        wxString baseName;

        int cnt = CatalogNodeNames.GetCount( );
        for ( int i = 0; i < cnt; i++ )
        {
            baseName = CatalogNodeNames.Item( i );
            if ( !name.Cmp( baseName ) )
            {
                return ( CatalogNodeType )i;
            }
        }
        return ( CatalogNodeType )-1;
    };


    // /**
    //  * @brief cout a brief id of the xml node
    //  *
    //  * @param ele
    //  **************************************************/
    // void IDElement( wxXmlNode* ele )
    // {
    //     const char* name = ele->GetName( );
    //     Catalog::CatalogNodeType nodeType = FindCatalogNodeType( name );

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
    bool IsCatalogNodeType( wxXmlNode* ele, CatalogNodeType type )
    {
        return !CatalogNodeNames.Item( type ).Cmp( ele->GetName( ) );
    }


    // CatalogNodeType FindCatalogNodeType( wxXmlNode* element )
    // {
    //     wxString name = element->GetName( );

    //     int cnt = CatalogNodeNames.GetCount( );
    //     for ( int i = 0; i < cnt; i++ )
    //     {
    //         if ( !name.Cmp( CatalogNodeNames.Item( i ) ) )
    //         {
    //             return ( CatalogNodeType )i;
    //         }
    //     }
    //     return ( CatalogNodeType )-1;
    // };

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
            Catalog::Stamp stamp( child );
            Catalog::CatalogNodeType sortType = ( Catalog::CatalogNodeType )GetProject()->GetSettings( )->GetNextSortClassification(
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
                const char* nameStr = name;
                const char* nodeNameStr = nodeName;
                //             std::cout << "     Looking for " << nodeNameStr << " with Name "
                //                 << nameStr << "\n";

                wxXmlNode* nextNode = Utils::FirstChildElement( parent, nodeNameStr );
                while ( nextNode )
                {
                    wxXmlAttribute* attr = Utils::SetAttribute( nextNode, "Name", nameStr );
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

                nextNode = Utils::NewNode( parent, nodeNameStr );
                Utils::SetAttribute( nextNode, "Name", nameStr );

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
                wxXmlNode* newChildNode = new wxXmlNode( *child );
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

    CatalogNodeType FindCatalogNodeType( wxXmlNode* element )
    {
        wxString name = element->GetName( );

        int cnt = CatalogNodeNames.GetCount( );
        for ( int i = 0; i < cnt; i++ )
        {
            if ( !name.Cmp( CatalogNodeNames.Item( i ) ) )
            {
                return ( CatalogNodeType )i;
            }
        }
        return ( CatalogNodeType )-1;
    };
}