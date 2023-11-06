/**
 * @file Entry.cpp
 * @author Eddie Monroe ( )
 * @brief
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


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

 //#include "catalog/CatalogCode.h"
#include "Defs.h"
#include "Settings.h"
#include "utils/Project.h"
#include "catalog/Entry.h"
#include "catalog/CatalogCode.h"
#include <wx/datetime.h>
#include <wx/strconv.h>
#include <wx/tokenzr.h>
#include <cstdio>
#include "utils/XMLUtilities.h"
#include "collection/CollectionList.h"


namespace Catalog {

    //-------

    wxString Entry::FindImageName( )
    {
        wxString catCodeStr = GetCatalogCodes( );
        Catalog::CatalogCode catCodeArray( catCodeStr );
        return catCodeArray.FindImageName( );
    }

    //-------

    bool Entry::IsCatalogCode( wxString catCode )
    {
        wxString catCodeStr = GetCatalogCodes( );
        Catalog::CatalogCode catCodeArray( catCodeStr );
        return catCodeArray.IsCatalogCode( catCode );
    }

    //-------

        // wxXmlNode* Entry::AddCode( )
        // {
        //     wxXmlNode* ele = GetCatXMLNode( );
        //     if ( ele )
        //     {
        //         return Utils::NewNode( ele, CatalogBaseNames[ NT_CatalogCode ] );
        //     }
        //     return ( wxXmlNode* ) 0;
        // }

    //-------
  //-------

        // find specimen for a collection
    wxXmlNode* Entry::GetItem( wxString collection )
    {
        if ( HasInventoryItem( ) )
        {
            wxXmlNode* ele = GetCatXMLNode( );
            if ( ele )
            {
                wxXmlNode* inventoryNode = Utils::FirstChildElement( ele, CatalogBaseNames[ NT_Inventory ] );
                if ( inventoryNode )
                {
                    wxXmlNode* child = inventoryNode->GetChildren( );
                    while ( child )
                    {
                        if ( !child->GetName( ).Cmp( CatalogBaseNames[ NT_Item ] ) )
                        {
                            wxString str = Utils::GetAttrStr( child, Catalog::ItemDataNames[ IDT_Collection ] );
                            if ( !str.Cmp( collection ) )
                            {
                                return child;
                            }
                        }
                    }
                }
            }
        }
        return ( wxXmlNode* ) 0;
    }

    // wxXmlNode* Entry::GetSpecimen( wxString collectionName )
    // {
    //     wxXmlNode* ele = GetCatXMLNode( );
    //     if ( ele )
    //     {
    //         wxXmlNode* child = ele->GetChildren( );
    //         while ( child )
    //         {
    //             if ( !child->GetName( ).Cmp( "Specimen" ) )
    //             {
    //                 wxString specimenCollection = child->GetAttribute( Catalog::ItemDataNames[ Catalog::IDT_Collection ], "" );
    //                 if ( !collectionName.Cmp( specimenCollection ) )
    //                 {
    //                     return child;
    //                 }
    //             }
    //             child = child->GetNext( );
    //         }
    //     }
    //     return ( wxXmlNode* ) 0;
    // }

    //-------

    wxXmlNode* Entry::AddNewInventoryItem( wxString collection, Catalog::InventoryStatusType type )
    {
        wxXmlNode* inventoryNode = GetInventory( );
        if ( !inventoryNode )
        {
            inventoryNode = Utils::NewNode( GetCatXMLNode( ), "Inventory" );
        }
        if ( inventoryNode )
        {
            wxXmlNode* newNode = Utils::NewNode( inventoryNode, CatalogBaseNames[ NT_Item ] );
            Utils::SetAttrStr( newNode,
                Catalog::ItemDataNames[ Catalog::IDT_Collection ],
                collection );
            Utils::SetAttrStr( newNode,
                Catalog::ItemDataNames[ Catalog::IDT_InventoryStatus ],
                Catalog::InventoryStatusStrings[ type ] );
            return newNode;
        }
        return ( wxXmlNode* ) 0;
    }

    //-------

    void Entry::DeleteSpecimen( wxXmlNode* deleteThisNode )
    {
        wxXmlNode* inventoryNode = GetInventory( );
        if ( inventoryNode )
        {
            inventoryNode->RemoveChild( deleteThisNode );
        }
    }

    //-------

    void Entry::DeleteCode( wxXmlNode* deleteThisNode )
    {
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        {
            ele->RemoveChild( deleteThisNode );
        }
    }

    //-------

    wxString Entry::GetAccuracy( ) {
        return GetAttr( DT_Accuracy );
    };

    //-------

    DataTypes Entry::FindDataType( wxString name )
    {
        for ( int i = DT_Name; i < DT_NbrTypes; i++ )
        {
            if ( !name.Cmp( XMLDataNames[ i ] ) )
            {
                return ( DataTypes ) i;
            }
        }
        return ( DataTypes ) -1;
    }

    //-------

    wxString Entry::GetAttr( DataTypes type )
    {
        if ( IsOK( ) )
        {
            const wxXmlAttribute* attr = Utils::GetAttribute( GetCatXMLNode( ), XMLDataNames[ type ] );
            if ( attr )
            {
                wxString str = attr->GetValue( );
                return str;
            }
        }
        return wxString( "" );
    }

    //-------

    wxString Entry::GetCatalogCodes( ) {
        return GetAttr( DT_Catalog_Codes );
    };

    //-------

    wxString Entry::GetClassificationName( Entry* entry, CatalogBaseType type )
    {
        switch ( type )
        {
            case NT_Period:
            {
                return entry->GetPeriod( );
                break;
            }
            case NT_Decade:
            {
                return entry->GetDecade( );
                break;
            }
            case NT_Year:
            {
                return entry->GetYear( );
                break;
            }
            case NT_Emission:
            {
                return entry->GetEmission( );
                break;
            }
            case NT_Catalog:
            {
                return "Catalog";
                break;
            }
            case NT_Country:
            {
                return entry->GetCountry( );
                break;
            }
            default:
            return wxString( "" );
        }
    }

    //-------

    wxString Entry::GetColors( ) {
        return GetAttr( DT_Colors );
    };

    //-------

    wxString Entry::GetCountry( ) {
        return GetAttr( DT_Country );
    };

    //-------

    wxString Entry::GetCurrency( ) {
        return GetAttr( DT_Currency );
    };

    //-------

    wxString Entry::GetDecade( )
    {
        wxString year = GetYear( );
        if ( !year.Cmp( "Unknown" ) )
        {
            return year;
        }

        double yd;
        year.ToDouble( &yd );
        int yi = yd / 10;
        yi = yi * 10;
        wxString decade = wxString::Format( "%ds", yi );
        return decade;
    }

    //-------

    wxString Entry::GetDescription( ) {
        return GetAttr( DT_Description );
    };

    //-------

    wxString Entry::GetEmission( ) {
        return GetAttr( DT_Emission );
    };

    //-------

    wxString Entry::GetExpiryDate( ) {
        return GetAttr( DT_Expiry_date );
    };

    //-------

    wxString Entry::GetFaceValue( ) {
        return GetAttr( DT_FaceValue );
    };

    //-------

        // wxXmlNode* Entry::GetFirstChildCode( )
        // {
        //     wxXmlNode* ele = GetCatXMLNode( );
        //     if ( ele )
        //     {
        //         return Utils::FirstChildElement( ele, CatalogBaseNames[ NT_CatalogCode ] );
        //     }
        //     return ( wxXmlNode* ) 0;
        // }

    //-------

    wxXmlNode* Entry::GetFirstInventoryItem( )
    {
        wxXmlNode* inventoryNode = GetInventory( );
        if ( inventoryNode )
        {
            return Utils::FirstChildElement( inventoryNode, CatalogBaseNames[ NT_Item ] );
        }
        return ( wxXmlNode* ) 0;
    }

    wxXmlNode* Entry::GetFirstInventoryItem( wxString collectionName )
    {
        wxXmlNode* itemNode = GetFirstInventoryItem( );
        while ( itemNode )
        {
            wxString collection = Utils::GetAttrStr( itemNode, ItemDataNames[ IDT_Collection ] );
            if ( !collection.Cmp( collectionName ) )
            {
                return itemNode;
            }
            itemNode = itemNode->GetNext( );
        }
        return ( wxXmlNode* ) 0;
    }


    //-------

    wxString Entry::GetFormat( ) {
        return GetAttr( DT_Format );
    };

    //-------

    FormatType Entry::GetFormatType( )
    {
        wxString format = GetAttr( DT_Format );
        for ( int i = FT_FormatUnknown; i < FT_NbrTypes; i++ )
        {
            wxString str = FormatStrings[ i ];
            if ( !format.CmpNoCase( FormatStrings[ i ] ) )
            {
                return ( FormatType ) i;
            }
        }
        return ( FormatType ) FT_FormatUnknown;
    }

    //-------

    wxString Entry::GetGum( ) {
        return GetAttr( DT_Gum );
    };

    //-------

    wxString Entry::GetHeight( ) {
        return GetAttr( DT_Height );
    };

    //-------

    wxXmlNode* Entry::GetInventory( )
    {
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        {
            return Utils::FirstChildElement( ele, CatalogBaseNames[ NT_Inventory ] );
        }
        return ( wxXmlNode* ) 0;
    }

    //-------

    wxString Entry::GetMount( ) {
        return GetAttr( DT_StampMount );
    };

    //-------

    wxString Entry::GetID( )
    {
        Catalog::CatalogCode catCodes( GetCatalogCodes( ) );
        return catCodes.GetPreferredCatalogCode( GetProject( )->GetProjectCatalogCode( ) );
    };

    //-------

    wxString Entry::GetInventoryStatus( )
    {
        InventoryStatusType type = GetInventoryStatusType( );
        return InventoryStatusStrings[ type ];
    }

    //-------

    InventoryStatusType Entry::GetInventoryStatusType( )
    {
        wxString currCollection = GetCollectionList( )->GetCurrentName( );
        wxXmlNode* ele = GetCatXMLNode( );
        if ( HasInventoryItem( ) )
        {
            wxXmlNode* inventory = GetInventory( );
            wxXmlNode* child = GetFirstInventoryItem( currCollection );
            if ( child )
            {
                wxString status = child->GetAttribute( Catalog::ItemDataNames[ IDT_InventoryStatus ], "Exclude" );
                return FindStatusType( status );
            }
        }
        return ( InventoryStatusType ) ST_Exclude;
    }


    //-------

    wxString Entry::GetIssuedDate( ) {
        return GetAttr( DT_Issued_on );
    };

    //-------

    wxString Entry::GetLabel( )
    {
        wxString label = GetPreferredCode( );
        wxString height = GetHeight( );
        wxString width = GetWidth( );
        wxString imageName = FindImageName( );
        wxString name = GetName( );
        label.Append( " - " );
        label.Append( name );
        bool nameEmpty = name.IsEmpty( );
        wxString str = GetProject( )->GetImageFullPath( imageName );
        bool imageMissing = !GetProject( )->ImageExists( str );
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

    //-------

    wxString Entry::GetLink( ) {
        return GetAttr( DT_Link );
    };

    //-------

    wxString Entry::GetName( )
    {
        return GetAttr( DT_Name );
    };

    //-------

    wxXmlNode* Entry::GetNextInventoryItem( wxXmlNode* node, wxString collectionName )
    {
        wxXmlNode* itemNode = node->GetNext( );
        while ( itemNode )
        {
            wxString collection = Utils::GetAttrStr( itemNode, ItemDataNames[ IDT_Collection ] );
            if ( !collection.Cmp( collectionName ) )
            {
                return itemNode;
            }
            itemNode = itemNode->GetNext( );
        }
        return ( wxXmlNode* ) 0;
    }
    //-------

    wxString Entry::GetPreferredCode( )
    {
        wxString catCodeStr = GetCatalogCodes( );
        Catalog::CatalogCode catCodeArray( catCodeStr );
        wxString preferredID = catCodeArray.GetPreferredCatalogCode( GetProject( )->GetProjectCatalogCode( ) );
        return preferredID;
    }

    //-------

        // wxXmlNode* Entry::GetNextChildCode( wxXmlNode* ele )
        // {
        //     if ( ele )
        //     {
        //         return Utils::GetNext( ele, CatalogBaseNames[ NT_CatalogCode ] );
        //     }
        //     return ( wxXmlNode* ) 0;
        // }

    //-------

    wxString Entry::GetPaper( ) {
        return GetAttr( DT_Paper );
    };

    //-------

    wxString Entry::GetPerforation( ) {
        return GetAttr( DT_Perforation );
    };

    //-------

    wxString Entry::GetPeriod( )
    {
        wxString year = GetYear( );
        if ( !year.Cmp( "Unknown" ) )
        {
            return year;
        }
        double yd;
        year.ToDouble( &yd );

        long lowerDivision;
        long upperDivision;
        wxString lowerDivisionStr = GetSettings( )->GetLowerDivision( );
        lowerDivisionStr.ToLong( &lowerDivision );
        wxString upperDivisionStr = GetSettings( )->GetUpperDivision( );
        upperDivisionStr.ToLong( &upperDivision );
        if ( yd < lowerDivision )
        {
            return GetSettings( )->GetLowerPeriod( );
        }
        else if ( yd >= upperDivision )
        {
            return GetSettings( )->GetUpperPeriod( );
        }
        else
        {
            return GetSettings( )->GetMiddlePeriod( );
        }
    }

    //-------

    wxString Entry::GetPrinting( ) {
        return GetAttr( DT_Printing );
    };

    //-------

    wxString Entry::GetPrintRun( ) {
        return GetAttr( DT_Print_run );
    };

    //-------

    wxString Entry::GetScore( ) {
        return GetAttr( DT_Score );
    };

    //-------

    wxString Entry::GetSeries( ) {
        return GetAttr( DT_Series );
    };


    //-------

    wxString Entry::GetThemes( ) {
        return GetAttr( DT_Themes );
    };

    //-------

    wxString Entry::GetVariant( ) {
        return GetAttr( DT_Variant );
    };

    //-------

    wxString Entry::GetWatermark( ) {
        return GetAttr( DT_Watermark );
    };

    //-------

    wxString Entry::GetWidth( ) {
        return GetAttr( DT_Width );
    };

    //-------

    wxString Entry::GetYear( )
    {
        wxDateTime dt;
        wxString dateStr = GetIssuedDate( );
        wxString::const_iterator end;
        wxDateTime dateDef = wxDateTime::Today( );
        if ( dt.ParseFormat( dateStr, "%Y-%m-%d", dateDef, &end ) )
        {
            int year = dt.GetYear( );
            char str[ 40 ];
            sprintf( str, "%d", year );
            wxString yearStr = str;
            return yearStr;
        }
        else if ( dt.ParseFormat( dateStr, "%Y", dateDef, &end ) )
        {
            int year = dt.GetYear( );
            char str[ 40 ];
            sprintf( str, "%d", year );
            wxString yearStr = str;
            return yearStr;

        }
        else if ( dt.ParseFormat( dateStr, "%Y-%m", dateDef, &end ) )
        {
            int year = dt.GetYear( );
            char str[ 40 ];
            sprintf( str, "%d", year );
            wxString yearStr = str;
            return yearStr;
        }
        return wxString( "Unknown" );
    }

    //-------

        // bool Entry::HasChildCode( )
        // {
        //     wxXmlNode* ele = GetCatXMLNode( );
        //     if ( ele )
        //     {
        //         if ( Utils::FirstChildElement( ele, CatalogBaseNames[ NT_CatalogCode ] ) )
        //         {
        //             return true;
        //         }
        //     }
        //     return false;
        // }

    //-------

    bool Entry::HasInventoryItem( )
    {
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        {
            wxXmlNode* inventoryNode = Utils::FirstChildElement( ele, CatalogBaseNames[ NT_Inventory ] );
            if ( inventoryNode )
            {
                if ( Utils::FirstChildElement( inventoryNode, CatalogBaseNames[ NT_Item ] ) )
                {
                    return true;
                }
            }
        }
        return false;
    }

    //-------

    bool Entry::IsMultiple( )
    {
        FormatType format = GetFormatType( );
        if ( format == FT_Se_tenant || format == FT_Mini_Sheet
            || format == FT_Souvenir_Sheet || format == FT_Booklet
            || format == FT_Booklet_Pane )
        {
            return true;
        }
        return false;
    }

    //-------

    bool Entry::IsOK( )
    {
        wxXmlNode* ele = GetCatXMLNode( );
        wxString str;
        if ( ele )
        {
            str = ele->GetName( );
            str = CatalogBaseNames[ NT_Entry ];
        }
        if ( GetCatXMLNode( )
            && !CatalogBaseNames[ NT_Entry ].Cmp( GetCatXMLNode( )->GetName( ) ) )
        {
            m_OK = true;
            return m_OK;
        }
        m_OK = false;
        return m_OK;
    };

    //-------

    void Entry::SetAccuracy( wxString val ) {
        SetAttr( DT_Accuracy, val );
    };

    //-------

    void Entry::SetAttr( DataTypes type, wxString val )
    {
        if ( IsOK( ) )
        {
            Utils::SetAttrStr( GetCatXMLNode( ), XMLDataNames[ type ], val );
        };
    }

    //-------

    void Entry::SetCatalogCodes( wxString val )
    {
        SetAttr( DT_Catalog_Codes, val );
    }

    //-------

    void Entry::SetColors( wxString val ) {
        SetAttr( DT_Colors, val );
    };

    //-------

    void Entry::SetCountry( wxString val ) {
        SetAttr( DT_Country, val );
    };

    //-------

    void Entry::SetCurrency( wxString val ) {
        SetAttr( DT_Currency, val );
    };

    //-------

    void Entry::SetDescription( wxString val ) {
        SetAttr( DT_Description, val );
    };

    //-------

    void Entry::SetExpiryDate( wxString val ) {
        SetAttr( DT_Expiry_date, val );
    };

    //-------

    void Entry::SetEmission( wxString val ) {
        SetAttr( DT_Emission, val );
    };

    //-------

    void Entry::SetFaceValue( wxString val ) {
        SetAttr( DT_FaceValue, val );
    };

    //-------

    void Entry::SetFormat( wxString val ) {
        SetAttr( DT_Format, val );
    };

    //-------

    void Entry::SetGum( wxString val ) {
        SetAttr( DT_Gum, val );
    };

    //-------

    void Entry::SetHeight( wxString val ) {
        SetAttr( DT_Height, val );
    };

    //-------

    void Entry::SetIssuedDate( wxString val ) {
        SetAttr( DT_Issued_on, val );
    };

    //-------

    void Entry::SetLink( wxString val ) {
        SetAttr( DT_Link, val );
    };

    //-------

    void Entry::SetName( wxString val ) {
        SetAttr( DT_Name, val );
    };

    //-------

    void Entry::SetPaper( wxString val ) {
        SetAttr( DT_Paper, val );
    };

    //-------

    void Entry::SetPerforation( wxString val ) {
        SetAttr( DT_Perforation, val );
    };

    //-------

    void Entry::SetPrinting( wxString val ) {
        SetAttr( DT_Printing, val );
    };

    //-------

    void Entry::SetPrintRun( wxString val ) {
        SetAttr( DT_Print_run, val );
    };

    //-------

    void Entry::SetScore( wxString val ) {
        SetAttr( DT_Score, val );
    };

    //-------

    void Entry::SetSeries( wxString val ) {
        SetAttr( DT_Series, val );
    };

    //-------

    void Entry::SetThemes( wxString val ) {
        SetAttr( DT_Themes, val );
    };

    //-------

    void Entry::SetVariant( wxString val ) {
        SetAttr( DT_Variant, val );
    };

    //-------

    void Entry::SetWidth( wxString val ) {
        SetAttr( DT_Width, val );
    };

    //-------

    void Entry::SetWatermark( wxString val ) {
        SetAttr( DT_Watermark, val );
    };

    //-------

}
