/**
 * @file Font.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright ( c ) 2022
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
#include <wx/pen.h>

#include "design/Font.h"
#include "utils/XMLUtilities.h"
#include "gui/GuiUtils.h"
#include "design/Album.h"

namespace Design { 


    void Font::Save( wxXmlNode* xmlNode )
    { 
        // if ( !m_type.compare( "Default" ) )
        // { 
        // //SetAttribute( xmlNode, AT_FontType1 );
        // //SetAttribute( xmlNode, AT_FontName );
        // }

    }


    void Font::Init( )
    { 
        
        // wxFont* font = 0;
        // //see if we can make a font with the supplied native info string
        // if ( !m_nativeFontInfoDesc.IsEmpty( ) )
        // { 
        //     font = new wxFont( m_nativeFontInfoDesc );
        // }
        // if ( font && !font->IsOk( ) )
        // { 
        //     // didn't work. get the default font.
        //     m_nativeFontInfoDesc.Clear( );
        //     if ( m_type == AT_CatNbrFontType )
        //     { 
        //         int ndx = GetAlbum( )->GetDefaultCatNbrFontNdx( );
        //         if ( ndx >= 0 )
        //         { 
        //             FontInfo* defaultInfo = GetAlbum( )->GetFontInfo( ndx );
        //             font = new wxFont( defaultInfo->GetFont( ) );
        //         }
        //     }
        //     else if ( m_type == AT_TitleFontType )
        //     { 
        //         int ndx = GetAlbum( )->GetDefaultTileFontNdx( );
        //         if ( ndx >= 0 )
        //         { 
        //             FontInfo* defaultInfo = GetAlbum( )->GetFontInfo( ndx );
        //             font = new wxFont( defaultInfo->GetFont( ) );
        //         }
        //     }
        //     if ( font && !font->IsOk( ) )
        //     { 
        //         //This is bring a problem. just create a generic font and go on.
        //         font = new wxFont ( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );
        //     }
        //     if ( font && !font->IsOk( ) )
        //     { 
        //         //crash and burn
        //     }
        //     AT_FontUsageType newType = AT_CatNbrFontType;
        //     //wxString newFace = defaultInfo->GetFaceName( );
            
        //     if ( IsOK( m_family ) )
        //     { 
        //         font->SetFamily( AT_FontFamilyMap[ m_family ] );
        //     }
        //     if ( m_size > 0 && m_size < 200 )
        //     { 
        //         font->SetPointSize( m_size );
        //     }
        //     if ( IsOK( m_weight ) )
        //     { 
        //         font->SetWeight( AT_FontWeightMap[ m_weight ] );
        //     }
        //     if ( IsOK( m_style ) )
        //     { 
        //         font->SetStyle( AT_FontStyleMap[ m_style ] );
        //     |              
        //     if ( m_color )
        //     { 
        //         wxColor newColor = m_color ;
        //     }
        // }
    }
        //    wxString Font::GetFamilyString( )
        // { 
        //     wxString family = GetAttrStr( AT_FontFamily );
        //     if ( !family.IsEmpty( ) && ( GetFamilyFromStr( family ) > 0 ) )
        //     { 
        //         return family;
        //     }
        //     if ( m_fontNdx )
        //     { 
        //         FontInfo* info = GetAlbum( )->GetFontList( ).at( m_fontNdx );
        //         AT_FontFamilyType type = info->GetFamily( );
        //         if ( type != UnknownFontVal )
        //         { 

        //         }
        //     }
        // }

void Font::SetNativeFontString( wxString nativeFontString )
{ 
        wxFont* font = new wxFont( nativeFontString );
        wxFont* currFont = GetAlbum( )->GetFont( m_fontNdx );
        if( nativeFontString.compare( currFont->GetNativeFontInfoDesc( ) ) )
        { 

            SetAttrStr( AT_NativeFontString, nativeFontString );
        }

}

wxFont* Font::GetFont( )
{ 
    if ( ( m_fontNdx >= 0 ) && ( m_fontNdx < GetAlbum( )->GetFontList( ).size( ) ) )
    {       
        FontInfo* info =  GetAlbum( )->GetFontInfo( m_fontNdx );
        if ( info )
        { 
            return info->GetFont( );
        }
    }
    return ( wxFont* )0;
}
wxString Font::GetNativeFontString(  )
{    
        FontInfo* info =  GetAlbum( )->GetFontInfo( m_fontNdx );
        if ( info )
        { 
            wxFont* font = info->GetFont( );
        }

        wxString fontStr = GetAttrStr( AT_NativeFontString );
                return ""; 
       
}


//         void Font::SetFamily( wxString nativeFontString )
//         { 

//             AT_FontFamilyType familyType = GetFamilyFromStr(  family );
//             if ( familyType != UnknownFontVal )
//             {        
//                 SetAttrStr( Design::AT_FontFamily, family );
//             }
//         };
//         void Font::SetFamily( AT_FontFamilyType type )
//         { 
//             if ( IsOK( type ) )
//             {        
//                 SetAttrStr( Design::AT_FontFamily, AT_FontFamilyStrings[ type ] );
//             }
//         };

}
