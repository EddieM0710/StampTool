/**
 * @file layout/Row.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
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

#ifndef Row_H
#define Row_H

#include "design/LayoutBase.h"

namespace Design {

    /**
     * @brief Row layout object; Inherits from LayoutBase.  The Row can contain Column or Stamp objects.
     *
     **************************************************/
    class Row : public LayoutBase
    {
    public:
        /**
         * @brief Construct a new Row object
         *
         * @param parent
         **************************************************/
        Row(  wxXmlNode* node ) : LayoutBase( node )
        { 
            SetNodeType( AT_Row ); 
            SetObjectName( AlbumBaseNames[ GetNodeType() ] );
            SetShowFrame(false);
            SetShowTitle(false);
        };

        /**
         * @brief Destroy the Row object
         *
         **************************************************/
        ~Row( ) {};

        /**
         * @brief Calculate the row layout based on child parameters
         *
         * @return true
         * @return false
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

        // build the frame container for the row
        /**
         * @brief  Decends into each child layout object performing its write to the content, styles, or images ODT XML
         *
         * @param parent
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );

        NodeStatus ValidateNode();

        /* 
         * @brief draw object on screen
         * 
         * @param dc current device context
         * @param x position in MM
         * @param y position in MM
         */
        void draw( wxDC &dc, double x, double y );
        void Save( wxXmlNode* xmlNode );

        // returns the index into FontList
        int GetTitleFont()
        {
//            if ( getch)
        }
        void ReportLayout(  );

    private:
        bool m_showCatNbr;
        bool m_showTitle;

    };

}
#endif