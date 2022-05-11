/**
 * @file Defs.h
 * @author Eddie Monroe ()
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef Defs_H
#define Defs_H

#include <wx/arrstr.h>
#include <wx/string.h>

// wx ID Defs
#define ID_ALBUMGENERATORFRAME 10000
#define ID_ALBUMGENERATORPANEL 10030
#define ID_IDENTIFICATIONPANEL 10040
#define ID_DESCRIPTIONPANEL 10060
#define ID_MISCELLANEOUSDATA 10080
#define ID_GALLERYIMAGEPANEL 10100
#define ID_INVENTORYPANEL 10120
#define ID_CATALOGCODEPANEL 10330
#define ID_GALLERYPANEL 10140
#define ID_FILTER 10160
#define ID_FINDSTAMP 10180
#define ID_IMAGEPANEL 10200
#define ID_LABLEDTEXTBOX 10220
#define ID_MERGEDATAQUERY 10240
#define ID_MERGESTAMPSDIALOG 10260
#define ID_SORTORDERDIALOG 10280
#define CatalogDataTree_Ctrl 10300
#define ID_CHARACTERISTICSPANEL 10320
#define ID_SETTINGSDIALOG 10340
#define MaxRecentEntries = 8

extern bool Dirty;

void SetDirty( bool state = true);
bool IsDirty();

class CatalogData;
class AECmdData;
class Settings;


/**
 * @brief Get the Settings data 
 * 
 * @return CatalogData* 
 **************************************************/
Settings* GetSettings( );

/**
 * @brief Get the Stamp Data object
 * 
 * @return CatalogData* 
 **************************************************/
CatalogData* GetCatalogData( void );
AECmdData* GetAECmdData( void );

/**
 * @brief Set the Stamp Data object
 * 
 * @param  catalogData 
 * @return CatalogData* 
 **************************************************/
CatalogData* SetCatalogData( CatalogData* catalogData );
AECmdData* SetAECmdData( AECmdData* catalogData );

/**
 * @brief Create a new CatalogData file
 *
 * @return CatalogData*
 **************************************************/
CatalogData* NewCatalogData( void );
AECmdData* NewAECmdData( void );
/**
 * @brief  Returns Ascii "true" or "false" based on bool b
 *
 * @param  b
 * @return const wxString
 **************************************************/
inline const wxString Bool2String( bool b )
{
    return b ? "true" : "false";
};

/**
 * @brief Returns bool true or false given Ascii str "true"
 *
 * @param  str
 * @return true  if str == "true"
 * @return false   if str == "false" ( or anything else)
 **************************************************/
inline const bool String2Bool( wxString str )
{
    return str.CmpNoCase( "true" ) ? false : true;
};

/**
 * @enum CatalogNodeType
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
} CatalogNodeType;

typedef enum
{
    AT_Album = 0,
    AT_Page,
    AT_Row,
    AT_Col,
    AT_Title,
    AT_Stamp,
    AT_NbrAlbumTypes
} AlbumNodeType;

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

/**
 * @enum PeriodType
 * @brief Enum defining the status of a given stamp. 
 * 
 **************************************************/
typedef enum
{
    ST_Checked = 0,
    ST_Unchecked,
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
{ ET_Unknown = 0,
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
    ET_NbrTypes} EmissionStrings;

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
extern wxArrayString CatalogNodeNames;


extern  const wxString CT_Names[ CT_NbrTypes ];

/**
 * @brief Look thru all the CatalogNodeNames to find "name"
 * and return the corresponding CatalogNodeType enum
 * @param   name : name of the node to find the Type of
 * @return {CatalogNodeType}      :  enum or -1 if not found.
 **************************************************/
CatalogNodeType FindCatalogNodeType( wxString name );

AlbumNodeType FindAlbumNodeType( wxString name );

/**
 * @brief Performs the initial instantiantion of all the sTart up data.
 *
 **************************************************/
void InitDefs( );



#endif
