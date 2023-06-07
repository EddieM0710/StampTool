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
 */

#ifndef Catalog_Entry_h
#define Catalog_Entry_h

#include "catalog/CatalogDefs.h"
#include "catalog/CatalogBase.h"
#include "catalog/CatalogData.h"
#include "catalog/CatalogVolume.h"
#include "utils/ImageRepository.h"
#include <wx/string.h>

namespace Catalog {

    /**
     * @brief This is a wrapper of an wxXmlNode for
     * safe/convenient getting/putting.
     * @see CatalogBase, Classification, Specimen
     *
     */
    class Entry : public CatalogBase
    {

    public:

        /**
         * @brief Construct a new Entry object
         *
         */
        Entry( ) : CatalogBase( )
        {
            SetNodeType( NT_Entry );
            IsOK( );
        };

        /**
         * @brief Construct a new Entry object
         *
         * @param entry
         */
        Entry( wxXmlNode* entry ) : CatalogBase( entry )
        {
            SetNodeType( NT_Entry );
            IsOK( );
        };

        /**
         * @brief Destroy the Entry object
         *
         */
        ~Entry( ) { };

        /**
         * @brief Add any empty element of type CatalogCode
         *
         * @return wxXmlNode*
         */
        wxXmlNode* AddCode( );

        /**
         * @brief add an empty element of Specimen type
         *
         * @return wxXmlNode*
         */
        wxXmlNode* AddSpecimen( );

        wxXmlNode* GetSpecimen( wxString collectionName );

        /**
         * @brief Get the Status Type object
         *
         * @return CheckedStatusType
         */
        CheckedStatusType GetCheckedStatusType( );


        /**
         * @brief delete the specified element
         *
         * @param deleteThisNode
         */
        void DeleteCode( wxXmlNode* deleteThisNode );

        /**
         * @brief delete the specified element
         *
         * @param deleteThisNode
         */
        void DeleteSpecimen( wxXmlNode* deleteThisNode );

        /**
         * @brief
         *
         * @param name
         * @return DataTypes
         */
        DataTypes FindDataType( wxString name );

        /**
         * @defgroup Get Entry field
         * @brief Retrieves the value of the attribute of the entry
         *
         * @return wxString  wxString representation of the field
         */
        wxString GetAccuracy( ); ///< Get the entry Accuracy field

        /**
         * @brief Get the Attr object
         *
         * @param type
         * @return wxString
         */
        wxString GetAttr( DataTypes type );

        /**
         * @brief Get the Background object
         *
         * @return wxString
         */
        wxString GetBackground( ) { return GetAttr( DT_BackGround ); };

        wxString GetCatalogCodes( ); ///< Get the entry Catalog Codes field

        /**
         * @brief Get the Classification Name object
         *
         * @param entry
         * @param type
         * @return wxString
         */
        wxString GetClassificationName( Entry* entry, CatalogBaseType type );

        /**
         * @brief Get the CatalogCode for the input catalog code
         * @details ids differ based on the reference catalog. this
         * function will return the id associated with the input catalog
         * or if there is no id for that catalog then the first one found
         * regardless of the catalog.
         *
         * @param catalog
         * @return wxXmlNode*
         */
        wxXmlNode* GetCodeForCatalog( const char* catalog );

        wxString GetColors( ); ///< Get the entry Colors field

        wxString GetCountry( ); ///< Get the entry country field

        wxString GetCurrency( ); ///< Get the entry Currency field

        /**
         * @brief Get the Decade object
         *
         * @return wxString
         */
        wxString GetDecade( );

        wxString GetDescription( ); ///< Get the entry Description field

        wxString GetEmission( ); ///< Get the entry emission field

        wxString GetExpiryDate( ); ///< Get the entry Expiry Date field 

        wxString GetFaceValue( ); ///< Get the entry FaceValue field

        /**
         * @brief Get the first child element with CatalogCode type
         *
         * @return wxXmlNode*
         */
        wxXmlNode* GetFirstChildCode( );

        /**
         * @brief Get the first child element of Specimen type
         *
         * @return wxXmlNode*
         */
        wxXmlNode* GetFirstChildSpecimen( );

        wxString GetFormat( ); ///< Get the entry Format field 

        /**
         * @brief Get the Format Type object
         *
         * @return FormatType
         */
        FormatType GetFormatType( );

        wxString GetGum( ); ///< Get the entry Gum field

        wxString GetHeight( ); ///< Get the entry height field 

        wxString GetMount( );

        wxString GetID( ); ///< Get the entry ID

        wxString GetInventoryStatus( );///< Get the Inventory Status field

        ///  @brief Get the InventoryStatusType value of the entry
        ///  
        ///  @return InventoryStatusType 
        InventoryStatusType GetInventoryStatusType( );

        wxString GetIssuedDate( ); ///< Get the entry Issue data field 

        /**
         * @brief Get the Label object
         *
         * @return wxString
         */
        wxString GetLabel( )
        {
            wxString label = GetID( );
            wxString height = GetHeight( );
            wxString width = GetWidth( );
            wxString imageName = GetCatalogData( )->GetImageFilename( label );
            wxString name = GetName( );
            label.Append( " - " );
            label.Append( name );
            bool nameEmpty = name.IsEmpty( );
            bool imageMissing = !GetCatalogVolume( )->GetImageRepository( )->Exists( imageName );
            wxString sizeMissing = "";
            if ( height.IsEmpty( ) || width.IsEmpty( ) || imageMissing || nameEmpty )
            {
                sizeMissing = " (";
                if ( name.IsEmpty( ) ) sizeMissing += "N";
                if ( imageMissing ) sizeMissing += "I";
                if ( height.IsEmpty( ) ) sizeMissing += "H";
                if ( width.IsEmpty( ) ) sizeMissing += "W";
                sizeMissing += ")";
            }

            label.Append( sizeMissing );

            return label;
        };

        wxString GetLink( ); ///< Get the entry Link field

        wxString GetName( ); ///< Get the entry title field
        /**
            * @brief Get the next child element with CatalogCode type
            *
            * @param ele get the CatalogCode sibling after this one
            * @return wxXmlNode*
            */
        wxXmlNode* GetNextChildCode( wxXmlNode* ele );

        /**
         * @brief Get the next child element of Specimen type
         *
         * @return wxXmlNode*
         */
        wxXmlNode* GetNextChildSpecimen( );

        wxString GetPaper( ); ///< Get the entry paper field

        wxString GetPerforation( ); ///< Get the entry Perforation field

        /**
         * @brief Get the Period object
         *
         * @return wxString
         */
        wxString GetPeriod( );

        wxString GetPrinting( ); ///< Get the entry Printing field

        wxString GetPrintRun( ); ///< Get the entry PrintRun field

        wxString GetScore( ); ///< Get the entry Score field

        wxString GetSeries( ); ///< Get the entry series field

        wxString GetThemes( ); ///< Get the entry Themes field

        /**
         * @brief Get the Val object
         *
         * @param type
         * @return wxString
         */
        wxString GetVal( DataTypes type ) { return GetAttr( type ); };

        wxString GetVariant( ); ///< Get the entry Variant field

        wxString GetWatermark( ); ///< Get the entry Watermark field 

        wxString GetWidth( ); ///< Get the entry Width field

        /**
         * @brief Get the Year object
         *
         * @return wxString
         */
        wxString GetYear( );

        /**
         * @brief Has a child node of type NT_CatalogCode
         *
         * @return true
         * @return false
         */
        bool HasChildCode( );

        /**
         * @brief does this entry have a child of Specimen type
         *
         * @return true
         * @return false
         */
        bool HasChildSpecimen( );

        /**
         * @brief Is this a stamp type that has stamp cildren, e.g., a setenant or souviner sheet
         *
         * @return true => FT_Se_tenant, FT_Mini_Sheet, FT_Souvenir_Sheet, FT_Booklet, FT_Booklet_Pane )
         * @return false => otherwise
         */
        bool IsMultiple( );

        /**
         * @brief Sanity check instance
         *
         * @return true
         * @return false
         */
        bool IsOK( );

        /**
         * @brief Process te striing of catalogcodes into ountry, catalog and id parts
         *
         */
        void ProcessCatalogCodes( wxString catCodes );

        /**
         * @brief Set the Attr object
         *
         * @param type
         * @param val
         */
        void SetAttr( DataTypes type, wxString val );

        /**
         * @defgroup
         * @brief Sets the value of the appropriate attribute of the entry
         *
         * @param val  the value to set the attribute to.
         */
        void SetAccuracy( wxString val ); ///< Get the entry Accuracy field 

        /**
         * @brief Set the Background object
         *
         * @param val
         */
        void SetBackground( wxString val ) { SetAttr( DT_BackGround, val ); };

        void SetCatalogCodes( wxString val ); ///< Get the entry CatalogCodes field 

        void SetColors( wxString val ); ///< Get the entry Colors field 

        void SetCountry( wxString val ); ///< Get the entry Country field 

        void SetCurrency( wxString val ); ///< Get the entry Currency field 

        void SetDescription( wxString val ); ///< Get the entry Description field 

        void SetEmission( wxString val ); ///< Get the entry Emission field 

        void SetExpiryDate( wxString val ); ///< Get the entry ExpiryDate field 

        void SetFaceValue( wxString val ); ///< Get the entry FaceValue field 

        void SetFormat( wxString val ); ///< Get the entry Format field 

        /**
         * @brief Set the Format Type object
         *
         * @param type
         */
        void SetFormatType( FormatType type )
        {
            SetAttr( DT_Format, FormatStrings[ type ] );
        };

        void SetGum( wxString val ); ///< Get the entry Gum field 

        void SetHeight( wxString val ); ///< Get the entry Height field 

        void SetID( wxString val ); ///< Get the entry ID field 

        void SetInventoryStatus( wxString val ) { SetAttr( DT_InventoryStatus, val ); };

        ///  @brief Set the Inventory Status Type field to it's string name
        ///  
        ///  @param type 
        void SetInventoryStatusType( InventoryStatusType type )
        {
            SetAttr( DT_InventoryStatus, InventoryStatusStrings[ type ] );
        };

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

        /**
         * @brief Set the Val object
         *
         * @param type
         * @param val
         */
        void SetVal( DataTypes type, wxString val ) { SetAttr( type, val ); };

        void SetVariant( wxString val ); ///< Get the entry Variant field 

        void SetWatermark( wxString val ); ///< Get the entry Watermark field 

        void SetWidth( wxString val ); ///< Get the entry Width field 

    private:
        bool m_dataDirty[ DT_NbrTypes ];
        bool m_OK;
    };

}
#endif