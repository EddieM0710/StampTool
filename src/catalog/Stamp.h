/**
 * @file Stamp.h
 * @author Eddie Monroe ()
 * @brief This is a wrapper of an wxXmlNode for
 * safe/convenient getting/putting.
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef Catalog_Stamp_h
#define Catalog_Stamp_h

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogBase.h"
#include <wx/string.h>



namespace Catalog {

    /**
    * @todo 2 fix so the GetName  refers to the name of an element and GetTitle refers to the attribute of an element.
     **************************************************/



     /**
      * @brief This is a wrapper of an wxXmlNode for
      * safe/convenient getting/putting.
      * @see CatalogBase, Classification, Specimen
      *
      **************************************************/
    class Stamp : public CatalogBase
    {
    public:

        /**
         * @brief Construct a new Stamp object
         *
         **************************************************/
        Stamp( ) : CatalogBase( )
        {
            SetNodeType( NT_Stamp );
            IsOK( );
        };

        /**
         * @brief Construct a new Stamp object
         *
         * @param stamp
         **************************************************/
        Stamp( wxXmlNode* stamp ) : CatalogBase( stamp )
        {
            SetNodeType( NT_Stamp );
            IsOK( );
        };

        /**
         * @brief Destroy the Stamp object
         *
         **************************************************/
        ~Stamp( ) { };

        /**
         * @brief
         *
         * @return true
         * @return false
         **************************************************/
        bool IsOK( );

        /**
         * @defgroup Get Stamp field
         * @brief Retrieves the value of the attribute of the stamp
         *
         * @return wxString  wxString representation of the field
         * @{
         **************************************************/

        wxString GetAccuracy( ); ///< Get the stamp Accuracy field
        wxString GetCatalogCodes( ); ///< Get the stamp Catalog Codes field
        wxString GetColors( ); ///< Get the stamp Colors field
        wxString GetCountry( ); ///< Get the stamp country field
        wxString GetCurrency( ); ///< Get the stamp Currency field
        wxString GetDescription( ); ///< Get the stamp Description field
        wxString GetEmission( ); ///< Get the stamp emission field
        wxString GetExpiryDate( ); ///< Get the stamp Expiry Date field 
        wxString GetFaceValue( ); ///< Get the stamp FaceValue field
        wxString GetFormat( ); ///< Get the stamp Format field 
        wxString GetGum( ); ///< Get the stamp Gum field
        wxString GetHeight( ); ///< Get the stamp height field 
        wxString GetID( ); ///< Get the stamp ID
        wxString GetIssuedDate( ); ///< Get the stamp Issue data field 
        wxString GetLink( ); ///< Get the stamp Link field
        wxString GetName( ); ///< Get the stamp title field
        wxString GetPaper( ); ///< Get the stamp paper field
        wxString GetPerforation( ); ///< Get the stamp Perforation field
        wxString GetPrinting( ); ///< Get the stamp Printing field
        wxString GetPrintRun( ); ///< Get the stamp PrintRun field
        wxString GetScore( ); ///< Get the stamp Score field
        wxString GetSeries( ); ///< Get the stamp series field
        wxString GetThemes( ); ///< Get the stamp Themes field
        wxString GetVariant( ); ///< Get the stamp Variant field
        wxString GetWatermark( ); ///< Get the stamp Watermark field 
        wxString GetWidth( ); ///< Get the stamp Width field

    /**@}*/

    /**
     * @brief Get the Attr object
     *
     * @param type
     * @return wxString
     **************************************************/
        wxString GetAttr( DataTypes type );

        /**
         * @brief Set the Attr object
         *
         * @param type
         * @param val
         **************************************************/
        void SetAttr( DataTypes type, wxString val );

        /**
         * @brief Get the Val object
         *
         * @param type
         * @return wxString
         **************************************************/
        wxString GetVal( DataTypes type ) { GetAttr( type ); };

        /**
         * @brief Set the Val object
         *
         * @param type
         * @param val
         **************************************************/
        void SetVal( DataTypes type, wxString val ) { SetAttr( type, val ); };

        /**
         * @defgroup
         * @brief Sets the value of the appropriate attribute of the stamp
         *
         * @param val  the value to set the attribute to.
         * @{
         **************************************************/
        void SetAccuracy( wxString val ); ///< Get the stamp Accuracy field 
        void SetCatalogCodes( wxString val ); ///< Get the stamp CatalogCodes field 
        void SetColors( wxString val ); ///< Get the stamp Colors field 
        void SetCountry( wxString val ); ///< Get the stamp Country field 
        void SetCurrency( wxString val ); ///< Get the stamp Currency field 
        void SetDescription( wxString val ); ///< Get the stamp Description field 
        void SetEmission( wxString val ); ///< Get the stamp Emission field 
        void SetExpiryDate( wxString val ); ///< Get the stamp ExpiryDate field 
        void SetFaceValue( wxString val ); ///< Get the stamp FaceValue field 
        void SetFormat( wxString val ); ///< Get the stamp Format field 
        void SetGum( wxString val ); ///< Get the stamp Gum field 
        void SetHeight( wxString val ); ///< Get the stamp Height field 
        void SetID( wxString val ); ///< Get the stamp ID field 
        void SetIssuedDate( wxString val ); ///< Get the stamp IssuedDate field 
        void SetLink( wxString val ); ///< Get the stamp Link field 
        void SetName( wxString val ); ///< Get the stamp Name field 
        void SetPaper( wxString val ); ///< Get the stamp Paper field 
        void SetPerforation( wxString val ); ///< Get the stamp Perforation field 
        void SetPrinting( wxString val ); ///< Get the stamp Printing field ; 
        void SetPrintRun( wxString val ); ///< Get the stamp PrintRun field 
        void SetScore( wxString val ); ///< Get the stamp Score field 
        void SetSeries( wxString val ); ///< Get the stamp Series field 
        void SetThemes( wxString val ); ///< Get the stamp Themes field 
        void SetVariant( wxString val ); ///< Get the stamp Variant field 
        void SetWatermark( wxString val ); ///< Get the stamp Watermark field 
        void SetWidth( wxString val ); ///< Get the stamp Width field 

        /*@}*/

        /**
         * @brief Get the Format Type object
         *
         * @return FormatType
         **************************************************/
        FormatType GetFormatType( );

        /**
         * @brief Set the Format Type object
         *
         * @param type
         **************************************************/
        void SetFormatType( FormatType type )
        {
            SetAttr( DT_Format, FT_FormatStrings[ type ] );
        };

        /**
         * @brief Get the Status Type object
         *
         * @return StatusType
         **************************************************/
        StatusType GetStatusType( );

        /**
         * @brief Get the Status object
         *
         * @return wxString
         **************************************************/
        wxString GetStatus( ) { return GetAttr( DT_Status ); };

        /**
         * @brief Set the Status object
         *
         * @param val
         **************************************************/
        void SetStatus( wxString val ) { SetAttr( DT_Status, val ); };

        /**
         * @brief Set the Status Type object
         *
         * @param type
         **************************************************/
        void SetStatusType( StatusType type )
        {
            SetAttr( DT_Status, ST_StatusStrings[ type ] );
        };

        /**
         * @brief Get the Background object
         *
         * @return wxString
         **************************************************/
        wxString GetBackground( ) { return GetAttr( DT_BackGround ); };

        /**
         * @brief Set the Background object
         *
         * @param val
         **************************************************/
        void SetBackground( wxString val ) { SetAttr( DT_BackGround, val ); };

        /**
         * @brief Get the Year object
         *
         * @return wxString
         **************************************************/
        wxString GetYear( );

        /**
         * @brief Get the Period object
         *
         * @return wxString
         **************************************************/
        wxString GetPeriod( );

        /**
         * @brief Get the Decade object
         *
         * @return wxString
         **************************************************/
        wxString GetDecade( );

        /**
         * @brief
         *
         * @param name
         * @return DataTypes
         **************************************************/
        DataTypes FindDataType( wxString name );

        /**
         * @brief
         *
         * @return true
         * @return false
         **************************************************/
        bool IsMultiple( );

        /**
         * @brief Get the Label object
         *
         * @return wxString
         **************************************************/
        wxString GetLabel( )
        {
            wxString name = GetID( );
            name.Append( "-" );
            name.Append( GetName( ) );
            return name;
        };

        /**
         * @brief Get the Classification Name object
         *
         * @param stamp
         * @param type
         * @return wxString
         **************************************************/
        wxString GetClassificationName( Stamp* stamp, CatalogBaseType type );

        /**
         * @brief add an empty element of Specimen type
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* AddSpecimen( );

        /**
         * @brief delete the specified element
         *
         * @param deleteThisNode
         **************************************************/
        void DeleteSpecimen( wxXmlNode* deleteThisNode );

        /**
         * @brief does this stamp have a child of Specimen type
         *
         * @return true
         * @return false
         **************************************************/
        bool HasChildSpecimen( );

        /**
         * @brief Get the first child element of Specimen type
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* GetFirstChildSpecimen( );

        /**
         * @brief Get the next child element of Specimen type
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* GetNextChildSpecimen( );

        /**
         * @brief Add any empty element of type CatalogCode
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* AddCode( );

        /**
         * @brief delete the specified element
         *
         * @param deleteThisNode
         **************************************************/
        void DeleteCode( wxXmlNode* deleteThisNode );

        /**
         * @brief
         *
         * @return true
         * @return false
         **************************************************/
        bool HasChildCode( );

        /**
         * @brief Get the first child element with CatalogCode type
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* GetFirstChildCode( );

        /**
         * @brief Get the next child element with CatalogCode type
         *
         * @param ele get the CatalogCode sibling after this one
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* GetNextChildCode( wxXmlNode* ele );

        /**
         * @brief Get the CatalogCode for the input catalog code
         * @details ids differ based on the reference catalog. this
         * function will return the id associated with the input catalog
         * or if there is no id for that catalog then the first one found
         * regardless of the catalog.
         *
         * @param catalog
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* GetCodeForCatalog( const char* catalog );

        /**
         * @brief
         *
         **************************************************/
        void ProcessCatalogCodes( );

    private:
        bool m_dataDirty[ DT_NbrTypes ];
        bool m_OK;
    };

}
#endif