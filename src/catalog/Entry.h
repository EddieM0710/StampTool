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
 //#include "utils/ImageRepository.h"
#include <wx/string.h>

namespace Catalog {


    /**
     * @brief This is a wrapper of an wxXmlNode for
     * safe/convenient getting/putting.
     * @see CatalogBase, Specimen
     *
     */
    class Entry : public CatalogBase
    {

    public:


        Entry( ) : CatalogBase( )
        {
            SetNodeType( NT_Entry );
            IsOK( );
        };

        Entry( wxXmlNode* entry ) : CatalogBase( entry )
        {
            SetNodeType( NT_Entry );
            IsOK( );
        };


        ~Entry( ) { };


        wxXmlNode* AddNewInventoryItem( wxString collection, Catalog::InventoryStatusType type );

        CheckedStatusType GetCheckedStatusType( );

        void DeleteCode( wxXmlNode* deleteThisNode );

        void DeleteSpecimen( wxXmlNode* deleteThisNode );

        DataTypes FindDataType( wxString name );

        wxString GetAccuracy( ); ///< Get the entry Accuracy field

        wxString GetAttr( DataTypes type );


        wxString GetBackground( ) {
            return GetAttr( DT_BackGround );
        };

        wxString GetCatalogCodes( ); ///< Get the entry Catalog Codes field

        wxString FindImageName( );

        wxString GetClassificationName( Entry* entry, CatalogBaseType type );

        /**
         * @brief Get the CatalogCode for the input catalog code
         * @details ids differ based on the reference catalog. this
         * function will return the id associated with the input catalog
         * or if there is no id for that catalog then the first one found
         * regardless of the catalog.
         */
        wxXmlNode* GetCodeForCatalog( const char* catalog );

        wxString GetColors( ); ///< Get the entry Colors field

        wxString GetCountry( ); ///< Get the entry country field

        wxString GetCurrency( ); ///< Get the entry Currency field

        wxString GetDecade( );

        wxString GetDescription( ); ///< Get the entry Description field

        wxString GetEmission( ); ///< Get the entry emission field

        wxString GetExpiryDate( ); ///< Get the entry Expiry Date field 

        wxString GetFaceValue( ); ///< Get the entry FaceValue field

        wxXmlNode* GetFirstInventoryItem( );

        wxXmlNode* GetFirstInventoryItem( wxString collectionName );

        wxString GetFormat( ); ///< Get the entry Format field 

        FormatType GetFormatType( );

        wxString GetGum( ); ///< Get the entry Gum field

        wxString GetHeight( ); ///< Get the entry height field 

        wxXmlNode* GetInventory( );

        wxString GetMount( );

        wxString GetID( ); ///< Get the entry ID

        wxString GetInventoryStatus( );///< Get the Inventory Status field

        InventoryStatusType GetInventoryStatusType( );

        wxString GetIssuedDate( ); ///< Get the entry Issue data field 

        wxString GetLabel( );

        wxString GetLink( ); ///< Get the entry Link field

        wxString GetName( ); ///< Get the entry title field

        wxString GetPaper( ); ///< Get the entry paper field

        wxString GetPerforation( ); ///< Get the entry Perforation field

        wxString GetPeriod( );

        wxString GetPreferredCode( );

        wxString GetPrinting( ); ///< Get the entry Printing field

        wxString GetPrintRun( ); ///< Get the entry PrintRun field

        wxString GetScore( ); ///< Get the entry Score field

        wxString GetSeries( ); ///< Get the entry series field

        // returns the first specimen in this entry with collection or 0 if not found
        wxXmlNode* GetItem( wxString collection );


        wxString GetThemes( ); ///< Get the entry Themes field


        wxString GetVal( DataTypes type ) {
            return GetAttr( type );
        };

        wxString GetVariant( ); ///< Get the entry Variant field

        wxString GetWatermark( ); ///< Get the entry Watermark field 

        wxString GetWidth( ); ///< Get the entry Width field

        wxString GetYear( );

        bool HasInventoryItem( );

        bool IsCatalogCode( wxString catCode );

        /**
         * @brief Is this a stamp type that has stamp cildren, e.g., a setenant or souviner sheet
         *
         * @return true => FT_Se_tenant, FT_Mini_Sheet, FT_Souvenir_Sheet, FT_Booklet, FT_Booklet_Pane )
         * @return false => otherwise
         */
        bool IsMultiple( );

        bool IsOK( );

        void SetAttr( DataTypes type, wxString val );

        void SetAccuracy( wxString val ); ///< Get the entry Accuracy field 

        void SetBackground( wxString val ) {
            SetAttr( DT_BackGround, val );
        };

        void SetCatalogCodes( wxString val ); ///< Get the entry CatalogCodes field 

        void SetColors( wxString val ); ///< Get the entry Colors field 

        void SetCountry( wxString val ); ///< Get the entry Country field 

        void SetCurrency( wxString val ); ///< Get the entry Currency field 

        void SetDescription( wxString val ); ///< Get the entry Description field 

        void SetEmission( wxString val ); ///< Get the entry Emission field 

        void SetExpiryDate( wxString val ); ///< Get the entry ExpiryDate field 

        void SetFaceValue( wxString val ); ///< Get the entry FaceValue field 

        void SetFormat( wxString val ); ///< Get the entry Format field 

        void SetFormatType( FormatType type )
        {
            SetAttr( DT_Format, FormatStrings[ type ] );
        };

        void SetGum( wxString val ); ///< Get the entry Gum field 

        void SetHeight( wxString val ); ///< Get the entry Height field 

        void SetID( wxString val ); ///< Get the entry ID field 

        void SetIssuedDate( wxString val ); ///< Get the entry IssuedDate field 

        void SetLink( wxString val ); ///< Get the entry Link field 

        wxXmlNode* GetNextInventoryItem( wxXmlNode* node, wxString collectionName );

        void SetName( wxString val ); ///< Get the entry Name field 

        void SetPaper( wxString val ); ///< Get the entry Paper field 

        void SetPerforation( wxString val ); ///< Get the entry Perforation field 

        void SetPrinting( wxString val ); ///< Get the entry Printing field ; 

        void SetPrintRun( wxString val ); ///< Get the entry PrintRun field 

        void SetScore( wxString val ); ///< Get the entry Score field 

        void SetSeries( wxString val ); ///< Get the entry Series field 

        void SetThemes( wxString val ); ///< Get the entry Themes field 

        void SetVal( DataTypes type, wxString val ) {
            SetAttr( type, val );
        };

        void SetVariant( wxString val ); ///< Get the entry Variant field 

        void SetWatermark( wxString val ); ///< Get the entry Watermark field 

        void SetWidth( wxString val ); ///< Get the entry Width field 

    private:
        bool m_dataDirty[ DT_NbrTypes ];
        bool m_OK;
    };

}
#endif