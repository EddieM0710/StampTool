
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
#include "catalog/CatalogSectionData.h"
// #include "catalog/Speciman.h"
#include "catalog/Entry.h"
// #include "catalog/Classification.h"
// #include "CatalogCode.h"

namespace Catalog { 

    /**
     * @brief Global pointer to CatalogSectionData data object
     *
     */



    // CatalogSectionData* GetCatalogSectionData( void )
    // { 
    //     return  GetToolData( )->GetCatalogSectionData( );
    // };
    // void SetCatalogSectionData( CatalogSectionData* catalogSectionData )
    // { 
    //     GetToolData( )->SetCatalogSectionData( catalogSectionData );
    // };

    const wxString ST_CheckedStatusStrings[ ST_NbrCheckedStatusTypes ]
        = { wxT( "Checked" ), wxT( "Unchecked" ) };

    const wxString ST_InventoryStatusStrings[ ST_NbrInventoryStatusTypes ]
        = { wxT( "None" ), wxT( "Missing" ), wxT( "Ordered" ), wxT( "Own" ), wxT( "Own Variant" ), wxT( "Exclude" ) };

    InventoryStatusType FindStatusType( wxString name )
    { 
        wxString baseName;
        for ( int i = 0; i < ST_NbrInventoryStatusTypes; i++ )
        { 
            baseName = ST_InventoryStatusStrings[ i ];
            if ( !name.Cmp( baseName ) )
            { 
                return ( InventoryStatusType )i;
            }
        }
        return ( InventoryStatusType )-1;
    };

    const wxString FT_FormatStrings[ FT_NbrTypes ]
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


    FormatType FindFormatType( wxString name )
    { 
        wxString baseName;
        for ( int i = 0; i < FT_NbrTypes; i++ )
        { 
            baseName = FT_FormatStrings[ i ];
            if ( !name.Cmp( baseName ) )
            { 
                return ( FormatType )i;
            }
        }
        return ( FormatType )-1;
    };

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



    EmissionType FindEmissionType( wxString name )
    { 
        wxString baseName;
        for ( int i = 0; i < ET_NbrTypes; i++ )
        { 
            baseName = ET_EmissionStrings[ i ];
            if ( !name.Cmp( baseName ) )
            { 
                return ( EmissionType )i;
            }
        }
        return ( EmissionType )-1;
    };

    const wxString DT_DataNames[ DT_NbrTypes ] = { 
        wxT( "ID Nbr" ),      wxT( "Name" ),          wxT( "Country" ), 
        wxT( "Series" ),      wxT( "Catalog Codes" ), wxT( "Issued on" ), 
        wxT( "Expiry date" ), wxT( "Width" ),         wxT( "Height" ), 
        wxT( "Paper" ),       wxT( "Watermark" ),     wxT( "Emission" ), 
        wxT( "Format" ),      wxT( "Perforation" ),   wxT( "Printing" ), 
        wxT( "Gum" ),         wxT( "Currency" ),      wxT( "FaceValue" ), 
        wxT( "Print run" ),   wxT( "Variant" ),       wxT( "Score" ), 
        wxT( "Accuracy" ),    wxT( "Colors" ),        wxT( "Themes" ), 
        wxT( "Description" ), wxT( "Link" ),       //   wxT( "Checked" ), 
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
        wxT( "Description" ), wxT( "Link" ),        //  wxT( "CheckedStatus" ), 
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
        "Entry" , 
        "Specimen" , 
        "CatalogCode",    
        "None" };

    const wxString CC_CatalogCodeNames[ CC_NbrTypes ]
        = { wxT( "ID" ), wxT( "Country" ), wxT( "Catalog" ) };

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
    //     case  NT_Entry:
    //     { 
    //         Entry entry( ele );
    //         std::cout << "wxXmlNode " << name << "  ID" << entry.GetID( ) << "  Name " << entry.GetName( ) << "\n";
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

    // void AddEntry( wxXmlNode *child )
    // { 
    //     AddEntry( Root( ), child );
    // }

    void AddEntry( wxXmlNode* parent, wxXmlNode* child, int level )
    { 
        level++;

    
        wxString childName = child->GetName( );
        wxString parentName = parent->GetName( );
        CatalogBaseType parentType = FindCatalogBaseType( parentName );
           std::cout << "AddEntry  ParentName:" << parentName
               << "  ParentType:" << CatalogBaseNames[ parentType ]
               << "  ChildName:" << childName << "  level" << level << "\n";
        if ( level > 6 )
        { 
             std::cout << "Infinite loop\n";
        }
        if ( childName == CatalogBaseNames[ NT_Entry ] )
        { 
            Catalog::Entry entry( child );
            Catalog::CatalogBaseType sortType = 
                ( Catalog::CatalogBaseType )GetSettings( )->GetNextSortClassification( 
                    ( int )parentType );
            if ( ( sortType < NT_Catalog ) || ( sortType >= NT_Entry ) )
            { 
                wxString id = entry.GetID( );
                long a;
                int pos;
                pos = id.find( ' ' );
                id = id.substr( pos );
                id.ToLong( &a );
               //std::cout << "     InsertChild "<< " id:" << id << "  Name:" << entry.GetName( ) << "\n";
                
                // if the sort type is not one of the classification node types
                // then add it here. All entrys and their children get added here.
                parent->AddChild( child );
                return;
            }
            else
            { 
               //std::cout << "     SortType: " << CatalogBaseNames[ sortType ]  << "\n";
                wxString nodeName = CatalogBaseNames[ sortType ];
                wxString name = entry.GetClassificationName( &entry, sortType );
                const char* nodeNameStr = nodeName;
               //std::cout << "     Looking for " << nodeNameStr << " with Name " << name << "\n";

                wxXmlNode* nextNode = Utils::FirstChildElement( parent, nodeNameStr );
                while ( nextNode )
                { 
                    wxString attr = Utils::GetAttrStr( nextNode, "Name" );
                    if ( !attr.IsEmpty( ) )
                    { 
                        if ( !attr.Cmp( name ) )
                        { 
                           //std::cout << "     Found it \n";
                            AddEntry( nextNode, child, level );
                            return;
                        }
                    }
                    nextNode = nextNode->GetNext( );
                }
                // couldn't find it so add it
               //std::cout << "     Adding it: " << nodeNameStr << " with Name "
               //    << name << "\n";

                nextNode = Utils::NewNode( parent, nodeNameStr );
                nextNode->SetParent( parent );
                Utils::SetAttrStr( nextNode, "Name", name );

                AddEntry( nextNode, child, level );
                return;
            }
        }
    }

    wxXmlNode* MoveEntry( wxXmlNode* newParent, wxXmlNode* child )
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

    wxXmlNode* InsertEntry( wxXmlNode* sibling, wxXmlNode* child, bool after )
    { 
        if ( sibling == child )
        { 
            // can't be a child of itself
            return ( wxXmlNode* )0;
        }

        // Make a copy of the old child and insert it
        wxXmlNode* newChildNode = new wxXmlNode( *child );
        wxXmlNode* newChild = newChildNode;
        wxXmlNode* parent = sibling->GetParent( );

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


    void SortData( wxXmlNode* destNode, wxXmlNode* parent )
    { 
         wxString name = parent->GetAttribute( DT_XMLDataNames[ DT_Name ] );
         std::cout << "SortData   Parent Name:" << name << "\n";

        wxXmlNode* child = parent->GetChildren( );
        while ( child )
        { 
             wxString name = child->GetAttribute( DT_XMLDataNames[ DT_Name ] );
             std::cout << "SortData   child Name:" << name << "\n";

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