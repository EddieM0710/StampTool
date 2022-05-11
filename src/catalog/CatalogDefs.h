/**
 * @file CatalogDefs.h
 * @author Eddie Monroe ()
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef CatalogDefs_H
#define CatalogDefs_H


#include <wx/arrstr.h>
#include <wx/string.h>

class wxXmlNode;

namespace Catalog {

class CatalogData;

/**
 * @brief Get the Stamp Data object
 *
 * @return CatalogData* InitCatalogDefs
 * @brief Set the Stamp Data object
 *
 * @param  catalogData
 * @return CatalogData*
 **************************************************/
    void SetCatalogData( CatalogData* catalogData );


    /**
     * @brief Create a new CatalogData file
     *
     * @return CatalogData*
     **************************************************/
    CatalogData* NewCatalogData( void );


    /**
     * @enum CatalogBaseType
     *
     * @brief Enum defining stamp node types.
     *
     **************************************************/
    typedef enum
    {
        NT_Catalog = 0,
        NT_Country,
        NT_Period,
        NT_Decade,
        NT_Year,
        NT_Emission,
        NT_Status,
        NT_Condition,
        NT_Stamp,
        NT_Specimen,
        NT_CatalogCode,
        NT_NbrTypes
    } CatalogBaseType;

    /**
     * @enum PeriodType
     *
     *  @brief Enum defining periods --
     *  PT_Antique, PT_Classical, PT_Modern,
     **************************************************/
    typedef enum
    {
        PT_Antique,
        PT_Classical,
        PT_Modern,
        PT_NbrTypes
    } PeriodType;

    /**
    * @enum DataTypes
     * @brief Enum defining data types; i.e., fields in a stamp.
     *
     **************************************************/
    typedef enum
    {
        DT_ID_Nbr = 0,
        DT_Name,
        DT_Country,
        DT_Series,
        DT_Catalog_Codes,
        DT_Issued_on,
        DT_Expiry_date,
        DT_Width,
        DT_Height,
        DT_Paper,
        DT_Watermark,
        DT_Emission,
        DT_Format,
        DT_Perforation,
        DT_Printing,
        DT_Gum,
        DT_Currency,
        DT_FaceValue,
        DT_Print_run,
        DT_Variant,
        DT_Score,
        DT_Accuracy,
        DT_Colors,
        DT_Themes,
        DT_Description,
        DT_Link,
        DT_Status,
        DT_BackGround,
        DT_NbrTypes
    } DataTypes;



    /**
     * @brief Valid values of Classification Type.
     *
     *
     **************************************************/
    typedef enum
    {
        CT_Title = 0,
        CT_PreferredCatalog,
        CT_ImageDirectory,
        CT_NbrTypes
    } ClassificationTypes;

    /**
     * @brief Enum defining item data types;
     *
     * This represents data
     * kept for actual physical stamps in the collection.
     *
     **************************************************/
    typedef enum
    {
        IDT_Type,
        IDT_Condition,
        IDT_Value,
        IDT_Location,
        IDT_Remarks,
        IDT_NbrTypes
    } ItemDataTypes;
    /**
     * @brief Enum defining catalog code data types;
     *
     * This represents data for catalog code stamp.
     *
     **************************************************/
    typedef enum
    {
        CC_ID,
        CC_Country,
        CC_Catalog,
        CC_NbrTypes
    } CatalogCodeTypes;

    extern const wxString CC_CatalogCodeNames[ CC_NbrTypes ];
    
    /**
     * @enum PeriodType
     * @brief Enum defining the status of a given stamp.
     *
     **************************************************/
    typedef enum
    {
        ST_Unchecked = 0,
        ST_Checked,
        ST_NbrTypes
    } StatusType;

    /**
     * @enum FormatType
     * @brief Enum defining the format of a stamp.
     *
     **************************************************/
    typedef enum
    {
        FT_FormatUnknown = 0,
        FT_Stamp,
        FT_Se_tenant,
        FT_Mini_Sheet,
        FT_Souvenir_Sheet,
        FT_Booklet,
        FT_Booklet_Pane,
        FT_Gutter_Pair,
        FT_Stamp_with_Attached_Label,
        FT_Tete_Beche,
        FT_NbrTypes
    } FormatType;

    typedef enum
    {
        ET_Unknown = 0,
        ET_Commemorative,
        ET_Definitive,
        ET_HuntingPermit,
        ET_Revenue,
        ET_AirPost,
        ET_AirPostOfficial,
        ET_AirPostSemiPostal,
        ET_ATMlabels,
        ET_Cinderella,
        ET_Illegal,
        ET_InsuredLetter,
        ET_Military,
        ET_Newspaper,
        ET_Official,
        ET_ParcelPost,
        ET_PersonalDelivery,
        ET_Personalized,
        ET_PostageDue,
        ET_PostalTax,
        ET_Precancelled,
        ET_Private,
        ET_Regional,
        ET_Registration,
        ET_SemiPostal,
        ET_WarTax,
        ET_NbrTypes
    } EmissionStrings;

    extern const wxString ET_EmissionStrings[ ET_NbrTypes ];

    /**
     * @enum MergeOverwriteQuery
     * @brief Enum for specifying file load process.
     **************************************************/
    typedef enum
    {
        MO_Cancel = 0,
        MO_Merge,
        MO_Overwrite,
        MO_NbrTypes
    } MergeOverwriteQuery;

    /**
     * @enum MergeProcedure
     * @brief Enum specifying merge process
     **************************************************/
    typedef enum
    {
        MP_AddMissing = 0,
        MP_AddMissingEntriesAndFields,
        MP_AddMissingAndOverwrite,
        MP_AddMissingAndQuery,
        MP_QueryAll,
        MP_NbrTypes
    } MergeProcedure;

    /**
     * @brief Strings used for StatusTypes enum
     *
     **************************************************/
    extern const wxString ST_StatusStrings[ ST_NbrTypes ];

    /**
     * @brief Ascii strings used for FormatTypes enum
     *
     **************************************************/
    extern const wxString FT_FormatStrings[ FT_NbrTypes ];

    /**
     * @brief Ascii string for each DataType enum
     *
     **************************************************/
    extern const wxString DT_DataNames[ DT_NbrTypes ];

    /**
     * @brief Ascii string for each XMLDataType enum. These are the same as
     * DT_DataNames except they have no spaces in the string since they are used for
     * XML element names.
     *
     **************************************************/
    extern const wxString DT_XMLDataNames[ DT_NbrTypes ];

    /**
     * @brief Ascii string for each ItemDataType enum
     *
     **************************************************/
    extern const wxString ItemDataNames[ IDT_NbrTypes ];

    /**
     * @brief Ascii string for the cataloge code enum
     *
     **************************************************/
    extern const wxString CC_CatalogCodeNames[ CC_NbrTypes ];

    /**
     * @brief Ascii string for each node string.
     * @note This is the name used for the tree node; not the wxXmlNode node.
     *
     **************************************************/
    extern  wxString CatalogBaseNames[NT_NbrTypes];


    extern  const wxString CT_Names[ CT_NbrTypes ];

    /**
     * @brief Look thru all the CatalogBaseNames to find "name"
     * and return the corresponding CatalogBaseType enum
     * @param   name : name of the node to find the Type of
     * @return {CatalogBaseType}      :  enum or -1 if not found.
     **************************************************/
    CatalogBaseType FindCatalogBaseType( wxString name );

    CatalogData* GetCatalogData( void );


    void InitCatalogDefs( );
   // void IDElement( wxXmlNode* ele );

    /**
     * @brief is the specified wxXmlNode of specified type
     *
     * @param ele  element of interest
     * @param type  element type
     * @return true  if a match
     **************************************************/
    bool IsCatalogBaseType( wxXmlNode* ele, CatalogBaseType type );


    CatalogBaseType FindCatalogBaseType( wxXmlNode* element );

    // void AddStamp(wxXmlNode *child)
    // {
    //     AddStamp(Root(), child);
    // }

    void AddStamp( wxXmlNode* parent, wxXmlNode* child, int level );
    // {
    //     level++;
    //     wxString name = child->GetName( );
    //     wxString parentName = parent->GetName( );
    //     CatalogBaseType parentType = FindCatalogBaseType( parentName );
    //     //    std::cout << "AddStamp  ParentName:" << parentName
    //     //        << "  ParentType:" << CatalogBaseNames[ parentType ]
    //     //        << "  ChildName:" << name << "level" << level << "\n";
    //     if ( name == CatalogBaseNames[ NT_Stamp ] )
    //     {
    //         Stamp stamp( child );
    //         CatalogBaseType sortType = ( CatalogBaseType )GetSettings( )->GetNextSortClassification(
    //             ( int )parentType );
    //         if ( ( sortType < NT_Catalog ) || ( sortType >= NT_Stamp ) )
    //         {
    //             //            std::cout << "     InsertChild\n";
    //                         // if the sort type is not one of the classification node types
    //                         // then add it here. All stamps and their children get added here.
    //             parent->AddChild( child );
    //             return;
    //         }
    //         else
    //         {
    //             //            std::cout << "     SortType: " << CatalogBaseNames[ sortType ]
    //             //                << "\n";
    //             wxString nodeName = CatalogBaseNames[ sortType ];
    //             wxString name = stamp.GetClassificationName( &stamp, sortType );
    //             const char* nameStr = name;
    //             const char* nodeNameStr = nodeName;
    //             //             std::cout << "     Looking for " << nodeNameStr << " with Name "
    //             //                 << nameStr << "\n";

    //             wxXmlNode* nextNode = FirstChildElement( parent, nodeNameStr );
    //             while ( nextNode )
    //             {
    //                 wxXmlAttribute* attr = SetAttrStr( nextNode, "Name", nameStr );
    //                 if ( attr )
    //                 {
    //                     //                    std::cout << "     Found it\n";
    //                     AddStamp( nextNode, child, level );
    //                     return;
    //                 }
    //                 nextNode = nextNode->GetNext( );
    //             }
    //             // couldn't find it so add it
    // //            std::cout << "     Adding it: " << nodeNameStr << " with Name "
    // //                << nameStr << "\n";

    //             nextNode = NewNode( parent, nodeNameStr );
    //             nextNode->SetAttrStr( "Name", nameStr );

    //             AddStamp( nextNode, child, level );
    //             return;
    //         }
    //     }
    // }

    wxXmlNode* MoveStamp( wxXmlNode* newParent, wxXmlNode* child );
    // {
    //     if ( newParent == child )
    //     {
    //         // can't be a child of itself
    //         return ( wxXmlNode* )0;
    //     }

    //     wxXmlNode* parent = newParent->GetParent( );
    //     while ( parent )
    //     {
    //         if ( child == parent )
    //         {
    //             // child can't be an ancestor of itself
    //             return ( wxXmlNode* )0;
    //         }
    //         parent = parent->GetParent( );
    //     }
    //     // Make a copy of the old child and insert it
    //     wxXmlNode* newChildNode = new wxXmlNode( *child );
    //     wxXmlNode* newChild = newChildNode;
    //     newParent->AddChild( newChild );

    //     parent = child->GetParent( );
    //     parent->RemoveChild( child );
    //     return newChild;
    // }

    void SortData( wxXmlNode* newRoot, wxXmlNode* parent );
    // {

    //     wxXmlNode* child = parent->GetChildren( );
    //     while ( child )
    //     {
    //         if ( !CatalogBaseNames[ NT_Stamp ].Cmp( child->GetName( ) ) )
    //         {
    //             // Make a copy of the old child in the new doc and insert it
    //             wxXmlNode* newChildNode = new wxXmlNode( *child );
    //             AddStamp( newRoot, newChildNode );
    //         }
    //         else
    //         {
    //             // if this wasn't a stamp node we will just decend in the hierachy

    //             if ( !child->GetChildren( ) )
    //             {
    //                 SortData( newRoot, child );
    //             }
    //         }
    //         child = child->GetNext( );
    //         ;
    //     }
    // }

}

#endif