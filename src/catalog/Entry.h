/**
 * @file Stamp.h
 * @author Eddie Monroe ( )
 * @brief This is a wrapper of an wxXmlNode for
 * safe/convenient getting/putting.
 * @version 0.1
 * @date 2021-02-25
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
 **************************************************/

#ifndef Catalog_Entry_h
#define Catalog_Entry_h

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogBase.h"
#include <wx/string.h>



namespace Catalog {

    /**
     * @brief This is a wrapper of an wxXmlNode for
     * safe/convenient getting/putting.
     * @see CatalogBase, Classification, Specimen
     *
     **************************************************/
    class Entry : public CatalogBase
    {
    public:

        /**
         * @brief Construct a new Entry object
         *
         **************************************************/
        Entry( ) : CatalogBase( )
        {
            SetNodeType( NT_Entry );
            IsOK( );
        };

        /**
         * @brief Construct a new Entry object
         *
         * @param entry
         **************************************************/
        Entry( wxXmlNode* entry ) : CatalogBase( entry )
        {
            SetNodeType( NT_Entry );
            IsOK( );
        };

        /**
         * @brief Destroy the Entry object
         *
         **************************************************/
        ~Entry( ) { };

        /**
         * @brief Sanity check instance
         *
         * @return true
         * @return false
         **************************************************/
        bool IsOK( );

        /**
         * @defgroup Get Entry field
         * @brief Retrieves the value of the attribute of the entry
         *
         * @return wxString  wxString representation of the field
         * @{
         **************************************************/
        wxString GetAccuracy( ); ///< Get the entry Accuracy field
        wxString GetCatalogCodes( ); ///< Get the entry Catalog Codes field
        wxString GetColors( ); ///< Get the entry Colors field
        wxString GetCountry( ); ///< Get the entry country field
        wxString GetCurrency( ); ///< Get the entry Currency field
        wxString GetDescription( ); ///< Get the entry Description field
        wxString GetEmission( ); ///< Get the entry emission field
        wxString GetExpiryDate( ); ///< Get the entry Expiry Date field 
        wxString GetFaceValue( ); ///< Get the entry FaceValue field
        wxString GetFormat( ); ///< Get the entry Format field 
        wxString GetGum( ); ///< Get the entry Gum field
        wxString GetHeight( ); ///< Get the entry height field 
        wxString GetID( ); ///< Get the entry ID
        wxString GetIssuedDate( ); ///< Get the entry Issue data field 
        wxString GetLink( ); ///< Get the entry Link field
        wxString GetName( ); ///< Get the entry title field
        wxString GetPaper( ); ///< Get the entry paper field
        wxString GetPerforation( ); ///< Get the entry Perforation field
        wxString GetPrinting( ); ///< Get the entry Printing field
        wxString GetPrintRun( ); ///< Get the entry PrintRun field
        wxString GetScore( ); ///< Get the entry Score field
        wxString GetSeries( ); ///< Get the entry series field
        wxString GetThemes( ); ///< Get the entry Themes field
        wxString GetVariant( ); ///< Get the entry Variant field
        wxString GetWatermark( ); ///< Get the entry Watermark field 
        wxString GetWidth( ); ///< Get the entry Width field
        wxString GetInventoryStatus( );///< Get the Inventory Status field

        /** @}*/

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
        wxString GetVal( DataTypes type ) { return GetAttr( type ); };

        /**
         * @brief Set the Val object
         *
         * @param type
         * @param val
         **************************************************/
        void SetVal( DataTypes type, wxString val ) { SetAttr( type, val ); };

        /**
         * @defgroup
         * @brief Sets the value of the appropriate attribute of the entry
         *
         * @param val  the value to set the attribute to.
         * @{
         **************************************************/
        void SetAccuracy( wxString val ); ///< Get the entry Accuracy field 
        void SetCatalogCodes( wxString val ); ///< Get the entry CatalogCodes field 
        void SetColors( wxString val ); ///< Get the entry Colors field 
        void SetCountry( wxString val ); ///< Get the entry Country field 
        void SetCurrency( wxString val ); ///< Get the entry Currency field 
        void SetDescription( wxString val ); ///< Get the entry Description field 
        void SetEmission( wxString val ); ///< Get the entry Emission field 
        void SetExpiryDate( wxString val ); ///< Get the entry ExpiryDate field 
        void SetFaceValue( wxString val ); ///< Get the entry FaceValue field 
        void SetFormat( wxString val ); ///< Get the entry Format field 
        void SetGum( wxString val ); ///< Get the entry Gum field 
        void SetHeight( wxString val ); ///< Get the entry Height field 
        void SetID( wxString val ); ///< Get the entry ID field 
        void SetIssuedDate( wxString val ); ///< Get the entry IssuedDate field 
        void SetLink( wxString val ); ///< Get the entry Link field 
        void SetName( wxString val ); ///< Get the entry Name field 
        void SetPaper( wxString val ); ///< Get the entry Paper field 
        void SetPerforation( wxString val ); ///< Get the entry Perforation field 
        void SetPrinting( wxString val ); ///< Get the entry Printing field ; 
        void SetPrintRun( wxString val ); ///< Get the entry PrintRun field 
        void SetScore( wxString val ); ///< Get the entry Score field 
        void SetSeries( wxString val ); ///< Get the entry Series field 
        void SetThemes( wxString val ); ///< Get the entry Themes field 
        void SetVariant( wxString val ); ///< Get the entry Variant field 
        void SetWatermark( wxString val ); ///< Get the entry Watermark field 
        void SetWidth( wxString val ); ///< Get the entry Width field 

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
         * @return CheckedStatusType
         **************************************************/
        CheckedStatusType GetCheckedStatusType( );

        ///---
        ///  @brief Get the InventoryStatusType value of the entry
        ///  
        ///  @return InventoryStatusType 
        InventoryStatusType GetInventoryStatusType( );

        /**
         * @brief Get the Status object
         *
         * @return wxString
         **************************************************/
         //wxString GetCheckedStatus( ) { return GetAttr( DT_CheckedStatus ); };
        // wxString GetInventoryStatus( ) { return GetAttr( DT_InventoryStatus ); };

         /**
          * @brief Set the Status object
          *
          * @param val
          **************************************************/
          //void SetCheckedStatus( wxString val ) { SetAttr( DT_CheckedStatus, val ); };
        void SetInventoryStatus( wxString val ) { SetAttr( DT_InventoryStatus, val ); };

        /**
         * @brief Set the Status Type object
         *
         * @param type
        //  **************************************************/
        // void SetCheckedStatusType( CheckedStatusType type )
        // { 
        //     SetAttr( DT_CheckedStatus, ST_CheckedStatusStrings[ type ] );
        // };

        ///---
        ///  @brief Set the Inventory Status Type field to it's string name
        ///  
        ///  @param type 
        void SetInventoryStatusType( InventoryStatusType type )
        {
            SetAttr( DT_InventoryStatus, ST_InventoryStatusStrings[ type ] );
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
         * @brief Is this a stamp type that has stamp cildren, e.g., a setenant or souviner sheet
         *
         * @return true => FT_Se_tenant, FT_Mini_Sheet, FT_Souvenir_Sheet, FT_Booklet, FT_Booklet_Pane )
         * @return false => otherwise
         **************************************************/
        bool IsMultiple( );

        /**
         * @brief Get the Label object
         *
         * @return wxString
         **************************************************/
        wxString GetLabel( )
        {
            wxString label = GetID( );
            label.Append( " - " );
            label.Append( GetName( ) );
            return label;
        };

        /**
         * @brief Get the Classification Name object
         *
         * @param entry
         * @param type
         * @return wxString
         **************************************************/
        wxString GetClassificationName( Entry* entry, CatalogBaseType type );

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
         * @brief does this entry have a child of Specimen type
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
         * @brief Has a child node of type NT_CatalogCode
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
         * @brief Process te striing of catalogcodes into ountry, catalog and id parts
         *
         **************************************************/
        void ProcessCatalogCodes( wxString catCodes );


    private:
        bool m_dataDirty[ DT_NbrTypes ];
        bool m_OK;
    };

}
#endif