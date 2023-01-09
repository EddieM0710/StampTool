/**
 * @file layout/Page.h
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

#ifndef Page_H
#define Page_H

#include "design/LayoutBase.h"
#include "design/Album.h"

namespace Design {

    class Title;

    /**
     * @brief Encapsulates the parameters of the page
     *
     **************************************************/
    class Page : public LayoutBase
    {
    public:
        Page( wxXmlNode* node ) : LayoutBase( node )
        {
            SetNodeType( AT_Page );
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );

            Album* album = GetAlbum( );
            if ( album )
            {
                SetXPos( 0.0 );
                SetYPos( 0.0 );
                SetWidth( album->GetWidth( ) );
                SetHeight( album->GetHeight( ) );
                SetTopMargin( album->GetTopMargin( ) );
                SetBottomMargin( album->GetBottomMargin( ) );
                SetRightMargin( album->GetRightMargin( ) );
                SetLeftMargin( album->GetLeftMargin( ) );
                SetBorderSize( album->GetBorderSize( ) );
            }       
        };
        ~Page( ) {};

        /**
         * @brief Perform the layout for the page.
         * Go to the bottom of each child container object ( row, column, page)
         * and begin filling in position relative to the parent
         * @return true - success
         * @return false - fail
         **************************************************/
        void UpdatePositions( );

        /**
         * @brief UpdateMinimumSize
         * Calculates the minimum Height and width of the object. It drills down to
         * the lowest layout object with an actual size and begins calculating the
         * min size of its parents as it progresses back up the heirarchy.
         * @return true
         * @return false
         **************************************************/
        bool UpdateMinimumSize( );

        void UpdateSizes( );

        /**
         * @brief Appends the xml for this page
         *
         * @param parent  expected to be the office:text of the office:body
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );

        /**
         * @brief Get the Top Margin object
         *
         * @return double
         **************************************************/
        double GetTopMargin( ) { return m_topMargin; };

        /**
         * @brief Set the Top Margin object
         *
         * @param val
         **************************************************/
        void SetTopMargin( double val ) { m_topMargin = val; };

        /**
         * @brief Get the Bottom Margin object
         *
         * @return double
         **************************************************/
        double GetBottomMargin( ) { return m_bottomMargin; };

        /**
         * @brief Set the Bottom Margin object
         *
         * @param val
         **************************************************/
        void SetBottomMargin( double val ) { m_bottomMargin = val; };

        /**
         * @brief Get the Right Margin object
         *
         * @return double
         **************************************************/
        double GetRightMargin( ) { return m_rightMargin; };

        /**
         * @brief Set the Right Margin object
         *
         * @param val
         **************************************************/
        void SetRightMargin( double val ) { m_rightMargin = val; };

        /**
         * @brief Get the Left Margin object
         *
         * @return double
         **************************************************/
        double GetLeftMargin( ) { return m_leftMargin; };

        /**
         * @brief Set the Left Margin object
         *
         * @param val
         **************************************************/
        void SetLeftMargin( double val ) { m_leftMargin = val; };

        /**
         * @brief Get the Border Size object
         *
         * @return double
         **************************************************/
        double GetBorderSize( ) { return m_borderSize; };

        /**
         * @brief Set the Border Size object
         *
         * @param val
         **************************************************/
        void SetBorderSize( double val ) { m_borderSize = val; };

        NodeStatus ValidateNode( );

        /* 
         * @brief draw object on screen
         * 
         * @param dc current device context
         * @param x position in MM
         * @param y position in MM
         */
        void draw( wxDC& dc, double x, double y );

        void Save( wxXmlNode* parent );

        void ReportLayout(  );

    private:


        /**
         * @brief Size of the page top margin
         *
         **************************************************/
        double m_topMargin;

        /**
         * @brief Size of the age bottom margine
         *
         **************************************************/
        double m_bottomMargin;

        /**
         * @brief  size of the page right margin
         *
         **************************************************/
        double m_rightMargin;

        /**
         * @brief Size of the page left margin
         *
         **************************************************/
        double m_leftMargin;


        /**
         * @brief Size of the border
         *
         **************************************************/
        double m_borderSize;

    };
}
#endif