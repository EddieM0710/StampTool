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

#include "design/LayoutBase.h"

namespace Design { 


    /**
     * @brief Design for the page Title text box; Inherits from LayoutBase.
     *
     **************************************************/
    class Title : public LayoutBase
    { 

    public:

        /**
         * @brief Construct a new Title object
         *
         * @param parent
         **************************************************/
        Title(  wxXmlNode* node ) : LayoutBase( node ) 
        { 
            SetNodeType( AT_Title );
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] ); 
        };

        /**
         * @brief Destroy the Title object
         *
         **************************************************/
        ~Title( ) { };

        /**
         * @brief Calculate the layout parameters.
         * @todo Title::Design. This is not done. Neiter position or size are initialized.
         *
         * @return true
         * @return false
         **************************************************/
        void UpdatePositions( );

        /**
         * @brief UpdateMinimumSize drills down to the lowest layout object with an actual size
         * and begins calculating the min size of its parents as it progresses
         * back up the heirarchy.
         * @todo Title::UpdateMinimumSize. This is not done.
         * @return true
         * @return false
         **************************************************/
        bool UpdateMinimumSize( );

        /**
         * @brief Calculate the row layout based on child parameters
         *
         * @return true
         * @return false
         **************************************************/
        void UpdateSizes( );

        /**
         * @brief Write the ODT XML to the contents.
         * @todo Title::Write This is old and needs to be reworked
         *
         * @param parent
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );

        // Getters and Putters

        NodeStatus ValidateNode( );


    private:


    };
}
#endif