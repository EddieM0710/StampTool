/* 
 * @file AutoStylesProp.cpp
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 * 
 */
#include "Defs.h"
#include "odt/Content.h"
#include "odt/AutoStylesProp.h"
#include "utils/XMLUtilities.h"

namespace ODT {


    TextStyle* AutoStylesProp::FindStyleName( wxString name )
    {
        for ( StyleList::iterator it = std::begin( m_styles ); it != std::end( m_styles ); ++it ) {
            if ( !( *it )->GetTextStyleName( ).Cmp( name ) )
            {
                return ( *it );
            }
        }
        return ( TextStyle* )0;
    };

    TextStyle* AutoStylesProp::FindStyle( wxString justify, bool bold, int fontSize )
    {
        for ( StyleList::iterator it = std::begin( m_styles ); it != std::end( m_styles ); ++it ) {
            TextStyle* style = *it;
            if ( !style->GetJustify( ).Cmp( justify )
                && !style->GetBold( ) == bold
                && !style->GetFontSize( ) == fontSize )
            {
                return ( *it );
            }
        }
        return ( TextStyle* )0;
    };

    TextStyle* AutoStylesProp::MakeStyle( wxString justify, bool bold, int fontSize,
        wxString codeName, bool foBreakBeforePage, wxString parentStyleName )
    {
        TextStyle* style = FindStyle( justify, bold, fontSize );
        if ( !style )
        {
            style = new TextStyle( );
            style->SetJustify( justify );
            style->SetBold( bold );
            style->SetFontSize( fontSize );
            style->SetCodeName( codeName );
            wxString str;
            Utils::GetTextStyleName( str );
            style->SetTextStyleName( str );
            style->SetParentStyleName( parentStyleName );
            style->SetFoBreakBeforePage( foBreakBeforePage );
            m_styles.push_back( style );
        }
        return style;
    };

    void AutoStylesProp::DefinePrimaryTextStyles( )
    {
        TextStyle* style = MakeStyle( "", false, 0, "NormalTextStyle", true, "Standard" );
        NormalTextStyle = style->GetTextStyleName( );

        style = MakeStyle( "center", true, 18, "Bold18PtTextStyle" );
        Bold18PtTextStyle = style->GetTextStyleName( );

        style = MakeStyle( "center", false, 8, "Normal8PtTextStyle" );
        Normal8PtTextStyle = style->GetTextStyleName( );

        style = MakeStyle( "center", false, 10, "Normal10PtTextStyle" );
        Normal10PtTextStyle = style->GetTextStyleName( );
    };

    void AutoStylesProp::WriteStyle( TextStyle* style )
    {
        wxXmlNode* automaticStyles = ContentDoc( )->FindOfficAutomaticStyles( );

        //text hold 18pt
        wxXmlNode* P2 = Utils::AddNewNode( automaticStyles, wxXML_ELEMENT_NODE, "style:style" );
        Utils::SetAttrStr( P2, "style:name", style->GetTextStyleName( ) );

        Utils::SetAttrStr( P2, "style:family", "paragraph" );
        Utils::SetAttrStr( P2, "style:parent-style-name", style->GetParentStyleName( ) );
        if ( style->GetFoBreakBeforePage( ) )
        {
            wxXmlNode* paragraphProperties = Utils::AddNewNode( P2, wxXML_ELEMENT_NODE, "style:paragraph-properties" );
            Utils::SetAttrStr( paragraphProperties, "fo:break-before", "page" );
        }
        if ( !style->GetJustify( ).empty( )
            || style->GetFontSize( ) > 0
            || style->GetBold( ) )
        {
            wxXmlNode* paragraphProperties2 = Utils::AddNewNode( P2, wxXML_ELEMENT_NODE, "style:paragraph-properties" );
            if ( !style->GetJustify( ).empty( ) )
            {
                Utils::SetAttrStr( paragraphProperties2, "fo:text-align", "center" );
            }
            Utils::SetAttrStr( paragraphProperties2, "style:justify-single-word", "false" );
            wxXmlNode* styleTextProperties2 = Utils::AddNewNode( P2, wxXML_ELEMENT_NODE, "style:text-properties" );
            if ( style->GetBold( ) )
            {
                Utils::SetAttrStr( styleTextProperties2, "fo:font-weight", "bold" );
                Utils::SetAttrStr( styleTextProperties2, "style:font-weight-complex", "bold" );
                Utils::SetAttrStr( styleTextProperties2, "style:font-weight-asian", "bold" );
            }
            int fontSize = style->GetFontSize( );
            if ( fontSize > 0 )
            {
                wxString size = wxString::Format( "%dpt", fontSize );
                Utils::SetAttrStr( styleTextProperties2, "fo:font-size", size );
                Utils::SetAttrStr( styleTextProperties2, "style:font-size-asian", size );
                Utils::SetAttrStr( styleTextProperties2, "style:font-size-complex", size );
            }
        }
    };

    void AutoStylesProp::WriteAll( )
    {
        for ( StyleList::iterator it = std::begin( m_styles ); it != std::end( m_styles ); ++it ) {
            TextStyle* style = *it;
            WriteStyle( style );
        }
    }
}