/**
 * @file layout/Column.h
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

#ifndef Column_H
#define Column_H

#include "design/LayoutBase.h"
#include "design/DesignDefs.h"

namespace Design {

    /**
     * @brief Column layout object; Inherits from LayoutBase.  
     * The column can contain Row or Stamp objects.
     *
     **************************************************/
    class Column : public LayoutBase
    {
    public:

        // column frame constructor
        /**
         * @brief Construct a new Column frame object.
         *
         * @param parent
         **************************************************/
        Column( wxXmlNode* node ) : LayoutBase( node ) { SetNodeType( AT_Col ); };

        /**
         * @brief Destroy the Column object
         *
         **************************************************/
        ~Column( ) {};


        /**
         * @brief Calculate the column layout based on child parameters
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



        // build the frame container for the column

        /**
         * @brief Decends into each child layout object performing its write to the content, styles, or images ODT XML
         *
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );

        NodeStatus ValidateNode( );
        /*
         * @brief draw object on screen
         *
         * @param dc current device context
         * @param x position in MM
         * @param y position in MM
         */
        void draw( wxDC& dc, double x, double y );

        void Save( wxXmlNode* xmlNode );

    private:


    };
}

#endif