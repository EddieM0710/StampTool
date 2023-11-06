/**
 * @file CatalogDefs.h
 * @author Eddie Monroe ( )
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

#ifndef CatalogDefs_H
#define CatalogDefs_H


#include <wx/arrstr.h>
#include <wx/string.h>

class wxXmlNode;


namespace Catalog {

    class CatalogVolume;

    /// @enum CatalogBaseType
    ///  @brief Enum defining Entry node types. One of NT_Catalog = 0, NT_Country, NT_Period,
    ///  NT_Decade, NT_Year, NT_Emission, NT_Status, NT_Condition, NT_Entry,
    ///  NT_Inventory, NT_Item, NT_None
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
        NT_Entry,
        NT_Inventory,
        NT_Item,
        NT_None,
        NT_NbrTypes
    } CatalogBaseType;



    /// ST_Unchecked , ST_Checked,, ST_NbrCheckedStatusTypes
    typedef enum
    {
        ST_Unchecked = 0,
        ST_Checked,
        ST_NbrCheckedStatusTypes
    } CheckedStatusType;



    ///  @enum DataTypes
    ///  @brief Enum defining data types; i.e., fields in a entry. One of  DT_Name,
    ///  DT_Country, DT_Series, DT_Catalog_Codes, DT_Issued_on, DT_Expiry_date, DT_Width,
    ///  DT_Height, DT_Paper, DT_Watermark, DT_Emission, DT_Format, DT_Perforation, DT_Printing, 
    ///  DT_Gum, DT_Currency, DT_FaceValue, DT_Print_run, DT_Variant, DT_Score, DT_Accuracy, 
    ///  DT_Colors, DT_Themes, DT_Description, DT_Link, DT_InventoryStatus, DT_StampMount, DT_BackGround,
    typedef enum
    {
        DT_Name = 0,
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
        DT_InventoryStatus,
        DT_StampMount,
        DT_BackGround,
        DT_CollapseState,
        DT_ImageName,
        DT_NbrTypes
    } DataTypes;

    /// @enum EmissionType
    ///  @brief enum for the stamp emission.  One of: 
    ///  ET_Unknown = 0, ET_Commemorative, ET_Definitive, ET_HuntingPermit, ET_Revenue,
    ///  ET_AirPost, ET_AirPostOfficial, ET_AirPostSemiPostal, ET_ATMlabels, ET_Cinderella,
    ///  ET_Illegal, ET_InsuredLetter,  ET_Military, ET_Newspaper, ET_Official, ET_ParcelPost,
    ///  ET_PersonalDelivery, ET_Personalized, ET_PostageDue, ET_PostalTax, ET_Precancelled,
    ///  ET_Private, ET_Regional, ET_Registration, ET_SemiPostal, ET_WarTax
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
    } EmissionType;

    /// @enum FormatType
    /// @brief Enum defining the format of a entry.
    /// One of: FT_FormatUnknown = 0, FT_Stamp, FT_Se_tenant, FT_Mini_Sheet, FT_Souvenir_Sheet,
    /// FT_Booklet, FT_Booklet_Pane, FT_Gutter_Pair, FT_Stamp_with_Attached_Label, FT_Tete_Beche,
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

    /// @enum ST_NbrInventoryStatusTypes
    ///  @brief  enum for stamp status in collection. One of: ST_None = 0, ST_Missing,
    ///  ST_Ordered, ST_Own, ST_OwnVariant, ST_Exclude
    typedef enum
    {
        ST_None = 0,
        ST_Missing,
        ST_Ordered,
        ST_Own,
        ST_OwnVariant,
        ST_Exclude,
        ST_NbrInventoryStatusTypes
    } InventoryStatusType;

    /// @enum  ItemDataTypes
    /// @brief Enum defining item data types;
    /// 
    /// This represents data kept for actual physical stamps in the collection.
    /// One of IDT_Collection, IDT_InventoryStatus, IDT_Type, IDT_Condition, IDT_Value, IDT_Remarks  
    typedef enum
    {
        IDT_Collection,
        IDT_InventoryStatus,
        IDT_Type,
        IDT_Condition,
        IDT_Value,
        IDT_Remarks,
        IDT_NbrTypes
    } ItemDataTypes;

    /// @enum MergeOverwriteQuery
    /// @brief Enum for specifying file load process.One of: MO_Cancel = 0,
    /// MO_Merge, MO_Overwrite,
    typedef enum
    {
        MO_Cancel = 0,
        MO_Merge,
        MO_Overwrite,
        MO_NbrTypes
    } MergeOverwriteQuery;

    /// @enum MergeProcedure
    /// @brief Enum specifying merge process. Oe of: MP_AddMissing = 0, 
    /// MP_AddMissingEntriesAndFields, MP_AddMissingAndOverwrite,
    /// MP_AddMissingAndQuery, MP_QueryAll,
    typedef enum
    {
        MP_AddMissing = 0,
        MP_AddMissingEntriesAndFields,
        MP_AddMissingAndOverwrite,
        MP_AddMissingAndQuery,
        MP_QueryAll,
        MP_NbrTypes
    } MergeProcedure;

    /// @enum PeriodType
        /// @brief Enum defining periods --
    /// PT_Antique, PT_Classical, PT_Modern, 
    typedef enum
    {
        PT_Antique,
        PT_Classical,
        PT_Modern,
        PT_NbrTypes
    } PeriodType;


    /// @brief Ascii string for each node string.
    /// @note This is the name used for the tree node; not the wxXmlNode node.
    extern  wxString CatalogBaseNames[ NT_NbrTypes ];

    // /// @brief Ascii string for the cataloge code enum
    // extern const wxString CatalogCodeNames[ CC_NbrTypes ];

    /// @brief Strings used for StatusTypes enum
    extern const wxString CheckedStatusStrings[ ST_NbrCheckedStatusTypes ];

    // ///  @brief Strings of ClassificationTypes
    // ///  
    // extern  const wxString ClassificationNames[ CT_NbrTypes ];

    /// @brief Ascii string for each DataType enum
    extern const wxString DataTypeNames[ DT_NbrTypes ];

    ///  @brief string representation of Emission types indexed by Emission Type
    extern const wxString EmissionStrings[ ET_NbrTypes ];

    /// @brief Ascii strings used for FormatTypes enum
    extern const wxString FormatStrings[ FT_NbrTypes ];

    extern const wxString InventoryStatusStrings[ ST_NbrInventoryStatusTypes ];

    /// @brief Ascii string for each ItemDataType enum
    extern const wxString ItemDataNames[ IDT_NbrTypes ];

    /// @brief Ascii string for each XMLDataType enum. These are the same as
    /// DataTypeNames except they have no spaces in the string since they are used for
    /// XML element names.
    extern const wxString XMLDataNames[ DT_NbrTypes ];




    ///  @brief Find the place where the entry should go and adds it.
    ///  
    ///  @param parent 
    ///  @param child 
    ///  @param level 
    void AddEntry( wxXmlNode* parent, wxXmlNode* child, int level );

    /**
     * @brief Look thru all the CatalogBaseNames to find "name"
     * and return the corresponding CatalogBaseType enum
     * @param   name : name of the node to find the Type of
     * @return { CatalogBaseType|    :  enum or -1 if not found.
     */
    CatalogBaseType FindCatalogBaseType( wxString name );

    ///  @brief Get the catalog base type of thid node.
    ///  
    ///  @param element 
    ///  @return CatalogBaseType 
    CatalogBaseType FindCatalogBaseType( wxXmlNode* element );

    ///  @brief loop through the Emission types and find one with the name name.
    ///  
    ///  @param name 
    ///  @return EmissionType 
    EmissionType FindEmissionType( wxString name );

    ///  @brief loop through the format types and find one with the name name.
    ///  
    ///  @param name 
    ///  @return FormatType 
    FormatType FindFormatType( wxString name );

    ///  @brief loop through the inventory status and find one with the name name.
    ///  
    ///  @param name 
    ///  @return InventoryStatusType 
    InventoryStatusType FindStatusType( wxString name );

    ///  @brief Null right now
    ///  
    void InitCatalogDefs( );

    ///  @brief Inserts a node as a sibling
    ///  
    ///  @param sibling 
    ///  @param child 
    ///  @param after 
    ///  @return wxXmlNode* 
    wxXmlNode* InsertEntry( wxXmlNode* sibling, wxXmlNode* child, bool after = true );

    /**
     * @brief is the specified wxXmlNode of specified type
     *
     * @param ele  element of interest
     * @param type  element type
     * @return true  if a match
     */
    bool IsCatalogBaseType( wxXmlNode* ele, CatalogBaseType type );

    ///  @brief Moves a node to a new parent.
    ///  
    ///  @param newParent 
    ///  @param child 
    ///  @return wxXmlNode* 
    wxXmlNode* MoveEntry( wxXmlNode* newParent, wxXmlNode* child );

    ///  @brief Sorts the nodes.
    ///  
    ///  @param newRoot 
    ///  @param parent 
    void SortData( wxXmlNode* newRoot, wxXmlNode* parent );

}

#endif