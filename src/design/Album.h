/**
 * @file layout/Album.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-02
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
 **************************************************/

#ifndef Album_H
#define Album_H

#include "design/AlbumBase.h"
;
#include "design/DesignDefs.h"
;
#include "utils/Project.h"
;
#include "utils/Settings.h"
;
#include <wx/font.h>
;
#include "design/FontInfo.h"
;

namespace Design {

    /**
     * @brief Album layout object; inherits from LayoutBase. This is the top  LayoutBase for holding all the objecs within the album
     *
     **************************************************/
    class Album : public AlbumBase
    {
    public:

        /**
         * @brief Construct a new Album object. The top layout LayoutBase
         * for holding all the objecs within the album
         *
         **************************************************/
        Album(  wxXmlNode* node ) : AlbumBase( node )
        {
            SetNodeType( AT_Album );
            m_defaultTitleFont = -1;
            m_defaultCatNbrFont = -1;
            m_defaultTextFont = -1;
            InitFonts( node );

        };
  
        /**
         * @brief Destroy the Album object
         *
         **************************************************/
        ~Album( ) {};

        /**
         * @brief calculate the layout and update all the odt files based on tht.
         *
         **************************************************/
        void MakeAlbum( );


        /**
         * @brief  Does the layout for each child. Goes to the bottom
         * of each child container object ( row, column, page)
         * and begin filling in position relative to the parent
         *
         * @return true
         * @return false
         **************************************************/
        void UpdatePositions( );

        /**
         * @brief init drills down to the lowest layout object with an actual size
         * and begins calculating the min size of its parents as it progresses
         * back up the heirarchy.
         * @return true
         * @return false
         **************************************************/
        bool UpdateMinimumSize( );

        void UpdateSizes( );
        
        wxXmlNode* Write( wxXmlNode* parent );

        /**
         * @brief Decends into each Album layout child performing its write to the content, styles, or images ODT XML
         *  /**
         * @brief sum of the height of child items; min height for this row
         *
         **************************************************/
        /**
         * @brief Get the Width
         *
         * @return double
         **************************************************/
        double GetWidth( );

        /**
         * @brief Get the Height
         *
         * @return double
         **************************************************/
        double GetHeight( );


        /**
         * @brief Get the Page Width
         *
         * @return double
         **************************************************/
        double GetPageWidth( );
        wxString GetPageWidthStr( );
        void SetPageWidth( wxString str );

        /**
         * @brief Get the Page Height
         *
         * @return double
         **************************************************/
        double GetPageHeight( );
        wxString GetPageHeightStr( );
        void SetPageHeight( wxString str );

        /**
         * @brief Get the Top Margin
         *
         * @return double
         **************************************************/
        double GetTopMargin( );
        wxString GetTopMarginStr();
        void SetTopMargin( wxString str );

        /**
         * @brief Get the Bottom Margin
         *
         * @return double
         **************************************************/
        double GetBottomMargin( );
        wxString GetBottomMarginStr();
        void SetBottomMargin( wxString str );

        /**
         * @brief Get the Right Margin
         *
         * @return double
         **************************************************/
        double GetRightMargin( );
        wxString GetRightMarginStr();
        void SetRightMargin( wxString str );

        /**
         * @brief Get the Left Margin
         *
         * @return double
         **************************************************/
        double GetLeftMargin( );
        wxString GetLeftMarginStr();
        void SetLeftMargin( wxString str );

        /**
         * @brief Get the Border Size
         *
         * @return double
         **************************************************/
        double GetBorderSize( );
        wxString GetBorderSizeStr();
        void SetBorderSize( wxString str );

        /**
         * @brief Get the Border File Name
         *
         * @return wxString
         **************************************************/
        wxString GetBorderFileName( );


        /**
         * @brief Get the Doc Name
         *
         * @return wxString
         **************************************************/
        wxString GetDocName( );
        void SetDocName( wxString str );


        /**
         * @brief Get the Page Parameters
         *
         * @param width
         * @param height
         * @param topMargin
         * @param bottomMargin
         * @param rightMargin
         * @param leftMargin
         **************************************************/
        void GetPageParameters( wxString& width, wxString& height, wxString& topMargin,
            wxString& bottomMargin, wxString& rightMargin, wxString& leftMargin );

        NodeStatus ValidateNode();
        void Save( wxXmlNode* xmlNode );
        void DumpLayout(   );

        FontInfo* FindFontInfo( wxFont* font, wxColor color );
        int GetDefaultTileFontNdx ( )
        {
            return m_defaultTitleFont;
        };
        int GetDefaultCatNbrFontNdx ( )
        {
            return m_defaultCatNbrFont;
        }
        int GetDefaultTextFontNdx ( )
        {
            return m_defaultTextFont;
        }
        bool IsValidFontNdx(int ndx )
        {
            if ( (ndx >= 0) && (ndx < m_fontList.size()))
            {
                return true;
            }
            return false;
        }
        wxFont* GetFont( int ndx )
        {
            if( IsValidFontNdx( ndx ) )
            {
                return GetFontInfo( ndx )->GetFont();
            }
        };

        void InitFonts( wxXmlNode* node );
        int FindFont( wxFont* font, wxColor color );
        int FindFont( FontInfo* info );
  
        FontInfo* GetFontInfo( int ndx );
        FontList& GetFontList()
        {
            return m_fontList;
        }
        int AddNewFont(  wxString nativeDesc, wxString color );

    private:
        // index of title font in FontList
        int m_defaultTitleFont;
        // index of catalog number font in FontList
        int m_defaultCatNbrFont;
        // index of catalog number font in FontList
        int m_defaultTextFont;
                
        FontList m_fontList;
    };
}
#endif