/**
 * @file layout/Title.h
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

#ifndef Title_H
#define Title_H

#include <wx/string.h>

#include "Defs.h"
#include "gui/AlbumImagePanel.h"

namespace Design { 


    /**
     * @brief Design for the page Title text box; Inherits from LayoutBase.
     *
     **************************************************/
    class Title 
    { 

    public:

        /**
         * @brief Construct a new Title object
         *
         * @param parent
         **************************************************/
        Title( ) 
        { 

        };

        /**
         * @brief Destroy the Title object
         *
         **************************************************/
        ~Title( ) { };
        wxString GetTitle( ) { return m_title; };
        void SetTitle( wxString str ) {  m_title = str; };
        void SetWidth( double w ){ m_titleRect.SetWidth( w ); };
        void  SetFont( wxFont *font ){ m_font = font; };
        wxFont* GetFont( ){ return m_font; };
    
    void draw( wxDC& dc  )
    { 
        wxString id;
        wxFont font( *m_font );

        id = m_title;
        id.Trim( );
        id.Trim( false );
        GetAlbumImagePanel( )->MakeMultiLine( id, font, m_titleRect.GetWidth( ) );
        font.SetPointSize( 6 );
        dc.SetFont( font );
        dc.DrawLabel( id, m_titleRect, wxALIGN_CENTER_HORIZONTAL );

    };

    // void UpdateTitle( double width, wxFont font )
    // { 
    //     m_multiLineTitle = m_title;

    //     // first break into lines if necessary
    //     GetAlbumImagePanel( )->MakeMultiLine( m_multiLineTitle, font, width );
    //     // then get the actual multi line text extent
    //     m_titleTextExtent = GetAlbumImagePanel( )->GetLogicalTextExtent( m_multiLineTitle, font );
    //     m_titleRect.SetWidth( m_titleTextExtent.x );
    //     m_titleRect.SetHeight( m_titleTextExtent.y );
    // };

    private:
    
    /* 
     * @brief Font for this title;
     * 
     */
    wxFont* m_font;

    /* 
     * @brief Title string
     * 
     */
    wxString m_title;
    /* 
     * @brief Title string with appropriately imbedded carriage returns
     * 
     */
    wxString m_multiLineTitle;
    /* 
     * @brief Text extent of multiline title
     * 
     */
    wxRealPoint m_titleTextExtent;
    /* 
     * @brief Bounding rect for the title; 
     * i.e., the ODT frame which tht title should be written to
     * 
     */
    wxRect m_titleRect;
    };
}
#endif