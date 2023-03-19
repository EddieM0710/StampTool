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
 **************************************************/

 
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "catalog/CatalogCode.h"
#include "Defs.h"
#include "Settings.h"
#include "catalog/Entry.h"
#include <wx/datetime.h>
#include <wx/strconv.h>
#include <wx/tokenzr.h>
#include <cstdio>
#include "utils/XMLUtilities.h"

namespace Catalog { 

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

    void Entry::SetAttr( DataTypes type, wxString val )
    { 
        if ( IsOK( ) )
        { 
            Utils::SetAttrStr( GetCatXMLNode( ), DT_XMLDataNames[ type ], val );
        };
    }

    wxString Entry::GetAttr( DataTypes type )
    { 
        if ( IsOK( ) )
        { 
            const wxXmlAttribute* attr = Utils::GetAttribute( GetCatXMLNode( ), DT_XMLDataNames[ type ] );
            if ( attr )
            { 
                wxString str = attr->GetValue( );
                return str;
            }
        }
        return wxString( "" );
    }

    // CheckedStatusType Entry::GetCheckedStatusType( )
    // { 
    //     wxString status = GetAttr( DT_CheckedStatus );
    //     for ( int i = ST_Checked; i < ST_NbrCheckedStatusTypes; i++ )
    //     { 
    //         wxString str = ST_CheckedStatusStrings[ i ];
    //         if ( !status.CmpNoCase( ST_CheckedStatusStrings[ i ] ) )
    //         { 
    //             return ( CheckedStatusType )i;
    //         }
    //     }
    //     return ( CheckedStatusType )ST_Unchecked;
    // };

    InventoryStatusType Entry::GetInventoryStatusType( )
    { 
        wxString status = GetAttr( DT_InventoryStatus );
        for ( int i = ST_None; i < ST_NbrInventoryStatusTypes; i++ )
        { 
            wxString str = ST_InventoryStatusStrings[ i ];
            if ( !status.CmpNoCase( ST_InventoryStatusStrings[ i ] ) )
            { 
                return ( InventoryStatusType )i;
            }
        }
        return ( InventoryStatusType )ST_None;
    };

    FormatType Entry::GetFormatType( )
    { 
        wxString format = GetAttr( DT_Format );
        for ( int i = FT_FormatUnknown; i < FT_NbrTypes; i++ )
        { 
            wxString str = FT_FormatStrings[ i ];
            if ( !format.CmpNoCase( FT_FormatStrings[ i ] ) )
            { 
                return ( FormatType )i;
            }
        }
        return ( FormatType )FT_FormatUnknown;
    }

    DataTypes Entry::FindDataType( wxString name )
    { 
        for ( int i = DT_ID_Nbr; i < DT_NbrTypes; i++ )
        { 
            if ( !name.Cmp( DT_XMLDataNames[ i ] ) )
            { 
                return ( DataTypes )i;
            }
        }
        return ( DataTypes )-1;
    }

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
        else if (  dt.ParseFormat( dateStr, "%Y", dateDef, &end )  )
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
    wxString Entry::GetID( ) { return GetAttr( DT_ID_Nbr ); };

    wxString Entry::GetName( ) { return GetAttr( DT_Name ); };

    wxString Entry::GetCountry( ) { return GetAttr( DT_Country ); };
    wxString Entry::GetSeries( ) { return GetAttr( DT_Series ); };
    wxString Entry::GetCatalogCodes( ) { return GetAttr( DT_Catalog_Codes ); };
    wxString Entry::GetIssuedDate( ) { return GetAttr( DT_Issued_on ); };
    wxString Entry::GetExpiryDate( ) { return GetAttr( DT_Expiry_date ); };
    wxString Entry::GetWidth( ) { return GetAttr( DT_Width ); };
    wxString Entry::GetHeight( ) { return GetAttr( DT_Height ); };
    wxString Entry::GetPaper( ) { return GetAttr( DT_Paper ); };
    wxString Entry::GetWatermark( ) { return GetAttr( DT_Watermark ); };
    wxString Entry::GetEmission( ) { return GetAttr( DT_Emission ); };
    wxString Entry::GetFormat( ) { return GetAttr( DT_Format ); };
    wxString Entry::GetVariant( ) { return GetAttr( DT_Variant ); };
    wxString Entry::GetThemes( ) { return GetAttr( DT_Themes ); };
    wxString Entry::GetScore( ) { return GetAttr( DT_Score ); };
    wxString Entry::GetPrintRun( ) { return GetAttr( DT_Print_run ); };
    wxString Entry::GetPrinting( ) { return GetAttr( DT_Printing ); };
    wxString Entry::GetPerforation( ) { return GetAttr( DT_Perforation ); };
    wxString Entry::GetLink( ) { return GetAttr( DT_Link ); };
    wxString Entry::GetGum( ) { return GetAttr( DT_Gum ); };
    wxString Entry::GetFaceValue( ) { return GetAttr( DT_FaceValue ); };
    wxString Entry::GetDescription( ) { return GetAttr( DT_Description ); };
    wxString Entry::GetCurrency( ) { return GetAttr( DT_Currency ); };
    wxString Entry::GetColors( ) { return GetAttr( DT_Colors ); };
    wxString Entry::GetAccuracy( ) { return GetAttr( DT_Accuracy ); };
    wxString Entry::GetInventoryStatus( )
    { 
        wxString status = GetAttr( DT_InventoryStatus );
        if ( status.IsEmpty( ) )
        { 
            return ST_InventoryStatusStrings[ ST_None ];
        }
        return status;
    }

    void Entry::SetWidth( wxString val ) { SetAttr( DT_Width, val ); };
    void Entry::SetWatermark( wxString val ) { SetAttr( DT_Watermark, val ); };
    void Entry::SetVariant( wxString val ) { SetAttr( DT_Variant, val ); };
    void Entry::SetThemes( wxString val ) { SetAttr( DT_Themes, val ); };
    void Entry::SetSeries( wxString val ) { SetAttr( DT_Series, val ); };
    void Entry::SetScore( wxString val ) { SetAttr( DT_Score, val ); };
    void Entry::SetPrintRun( wxString val ) { SetAttr( DT_Print_run, val ); };
    void Entry::SetPrinting( wxString val ) { SetAttr( DT_Printing, val ); };
    void Entry::SetPerforation( wxString val ) { SetAttr( DT_Perforation, val ); };
    void Entry::SetPaper( wxString val ) { SetAttr( DT_Paper, val ); };
    void Entry::SetName( wxString val ) { SetAttr( DT_Name, val ); };
    void Entry::SetLink( wxString val ) { SetAttr( DT_Link, val ); };
    void Entry::SetIssuedDate( wxString val ) { SetAttr( DT_Issued_on, val ); };
    void Entry::SetID( wxString val ) { SetAttr( DT_ID_Nbr, val ); };
    void Entry::SetHeight( wxString val ) { SetAttr( DT_Height, val ); };
    void Entry::SetGum( wxString val ) { SetAttr( DT_Gum, val ); };
    void Entry::SetFormat( wxString val ) { SetAttr( DT_Format, val ); };
    void Entry::SetFaceValue( wxString val ) { SetAttr( DT_FaceValue, val ); };
    void Entry::SetExpiryDate( wxString val ) { SetAttr( DT_Expiry_date, val ); };
    void Entry::SetEmission( wxString val ) { SetAttr( DT_Emission, val ); };
    void Entry::SetDescription( wxString val ) { SetAttr( DT_Description, val ); };
    void Entry::SetCurrency( wxString val ) { SetAttr( DT_Currency, val ); };
    void Entry::SetCountry( wxString val ) { SetAttr( DT_Country, val ); };
    void Entry::SetColors( wxString val ) { SetAttr( DT_Colors, val ); };
    void Entry::SetCatalogCodes( wxString val ) { SetAttr( DT_Catalog_Codes, val ); };
    void Entry::SetAccuracy( wxString val ) { SetAttr( DT_Accuracy, val ); };

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

    wxXmlNode* Entry::AddSpecimen( )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            return Utils::NewNode( ele, CatalogBaseNames[ NT_Specimen ] );
        }
        return ( wxXmlNode* )0;
    }

    void Entry::DeleteSpecimen( wxXmlNode* deleteThisNode )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            ele->RemoveChild( deleteThisNode );
        }
    }

    bool Entry::HasChildSpecimen( )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            if ( Utils::FirstChildElement( ele, CatalogBaseNames[ NT_Specimen ] ) )
            { 
                return true;
            }
        }
        return false;
    }
    wxXmlNode* Entry::GetFirstChildSpecimen( )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            return Utils::FirstChildElement( ele, CatalogBaseNames[ NT_Specimen ] );
        }
        return ( wxXmlNode* )0;
    }
    wxXmlNode* Entry::GetNextChildSpecimen( )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            return Utils::GetNext( ele, CatalogBaseNames[ NT_Specimen ] );
        }
        return ( wxXmlNode* )0;
    }


    wxXmlNode* Entry::AddCode( )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            return Utils::NewNode( ele, CatalogBaseNames[ NT_CatalogCode ] );
        }
        return ( wxXmlNode* )0;
    }

    void Entry::DeleteCode( wxXmlNode* deleteThisNode )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            ele->RemoveChild( deleteThisNode );
        }
    }

    bool Entry::HasChildCode( )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            if ( Utils::FirstChildElement( ele, CatalogBaseNames[ NT_CatalogCode ] ) )
            { 
                return true;
            }
        }
        return false;
    }

    wxXmlNode* Entry::GetFirstChildCode( )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            return Utils::FirstChildElement( ele, CatalogBaseNames[ NT_CatalogCode ] );
        }
        return ( wxXmlNode* )0;
    }

    wxXmlNode* Entry::GetNextChildCode( wxXmlNode* ele )
    { 
        if ( ele )
        { 
            return Utils::GetNext( ele, CatalogBaseNames[ NT_CatalogCode ] );
        }
        return ( wxXmlNode* )0;
    }

    wxXmlNode* Entry::GetCodeForCatalog( const char* catalog )
    { 
        wxXmlNode* ele = GetCatXMLNode( );
        if ( ele )
        { 
            wxXmlNode* childCode = Utils::FirstChildElement( ele, CatalogBaseNames[ NT_CatalogCode ] );
            if ( childCode )
            { 
                const wxXmlAttribute* attr = Utils::GetAttribute( childCode, CC_CatalogCodeNames[ CC_Catalog ] );
                if ( attr )
                { 
                    const char* code = attr->GetValue( );
                    if ( !strncmp( catalog, code, strlen( catalog ) ) )
                    { 
                        return childCode;
                    }
                }
            }
        }
        return ( wxXmlNode* )0;
    }


    void Entry::ProcessCatalogCodes( wxString catCodes )
    { 
        if ( !HasChildCode( ) )
        { 
            if ( catCodes.IsEmpty( ) )
            { 
                return;
            }

            wxStringTokenizer tokenizer( catCodes, "," );

            wxString valStr;
            wxString rest;
            while ( tokenizer.HasMoreTokens( ) )
            { 
                valStr = tokenizer.GetNextToken( );
                if ( valStr.StartsWith( wxT( "\"" ), &rest ) )
                    valStr = rest;
                if ( valStr.EndsWith( wxT( "\"" ), &rest ) )
                    valStr = rest;

                // "Mi:US 1, Sn:US 1b, Yt:US 1, Sg:US 1, Un:US 1b"
                valStr = valStr.Trim( );
                valStr = valStr.Trim( false );

                int pos = valStr.Find( ":" );
                wxString catalog = valStr.Mid( 0, pos );
                valStr = valStr.Mid( pos + 1 );
                pos = valStr.Find( " " );
                wxString country = valStr.Mid( 0, pos );
                wxString id = valStr.Mid( pos + 1 );


                wxXmlNode* catCodeElement = Utils::NewNode( GetCatXMLNode( ), CatalogBaseNames[ NT_CatalogCode ] );

                CatalogCode* catCodeNode = new CatalogCode( catCodeElement );
                catCodeNode->SetCatalog( catalog );
                catCodeNode->SetCountry( country );
                catCodeNode->SetID( id );
            }
        }
    }


}