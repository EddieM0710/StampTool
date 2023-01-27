/**
 * @file layout/FontInfo.h
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

#ifndef FontInfo_H
#define FontInfo_H

#include "design/DesignDefs.h"
#include "design/XMLBase.h"
#include "design/Font.h"
#include <wx/font.h>
#include <wx/colour.h>
#include <vector>


namespace Design { 
    /**
        * @brief Font layout object; In
        *
        **************************************************/
    class FontInfo
    { 
    public:

        // FontInfo frame constructor
        /**
         * @brief Construct a new Font frame object.
         *
         * @param parent
         **************************************************/
        FontInfo(  )
        { 

        };

        /**
         * @brief Destroy the Font object
         *
         **************************************************/
        ~FontInfo( ) { };



        // build the frame container for the font

 //       void Write( wxXmlNode* xmlNode );

        wxFont* GetFont( )
        { 
            return m_font;
        };


        void SetFont( wxFont* font )
        { 
            m_font = font;
        };

        wxColor GetColor( )
        { 
            return m_color;
        };
   
        void SetColor( wxColor color )
        { 
            m_color = color;
        };

        AT_FontFamilyType GetFamily( )
        { 
            return  GetATFamily( m_font->GetFamily( ) );
        };

        wxString GetNativeInfoStr( )
        { 
            return m_font->GetNativeFontInfoDesc( );
        };

        AT_FontWeightType GetWeight( )
        { 
            return  GetATWeight( m_font->GetWeight( ) );
        };

        int GetPointSize( )
        { 
            return m_font->GetPointSize( );
        };

        wxString GetFaceName( )
        { 
            return m_font->GetFaceName( );
        };

        wxString GetFamilyName( )
        { 
            return m_font->GetFamilyString( );
        };

        AT_FontStyleType GetStyle( )
        { 
            return  GetATStyle( m_font->GetStyle( ) );
        };

        bool IsEqual( wxFont* font, wxColor color )
        { 
            if ( IsFontEqual( font ) &&
                IsColorEqual( color ) )
            { 
                return true;
            }
            return false;
        }
        bool IsFontEqual( wxFont* font )
        { 
            if ( *m_font == *font )
            { 
                return true;
            }
            return false;
        }

        bool IsColorEqual( wxColor color )
        { 
            if ( m_color == color )
            { 
                return true;
            }
            return false;
        }
    private:

        wxFont* m_font;
        wxColor m_color;

    };

    typedef std::vector<FontInfo*> FontList;


    int FindFont( FontList& list, wxFont* font, wxColor color );
}

#endif
