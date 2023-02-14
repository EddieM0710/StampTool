/**
 * @file layout/Titlelayout/Page.h
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

#ifndef TitlePage_H
#define TitlePage_H

#include "design/LayoutBase.h" 
#include "design/DesignDefs.h"

namespace Design { 


    //class Border;

    /**
     * @brief TitlePage layout object; inherits from LayoutBase
     * @todo Nearly nothing in class TitlePage has been done.
     *
     **************************************************/
    class TitlePage : public LayoutBase
    { 
    public:
        /**
         * @brief Construct a new Title Page object
         *
         * @param parent
         **************************************************/
        TitlePage(  wxXmlNode* node ) : LayoutBase( node ) 
        { 
            SetNodeType( AT_TitlePage ); 
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
            };

        /**
         * @brief Destroy the Title Page object
         *
         **************************************************/
        ~TitlePage( ) { };

        /**
         * @brief Calculate the layout parameters
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
        //wxXmlNode *Write( wxXmlNode *parent ){ };


        void UpdateSizes( );

        NodeStatus ValidateNode( );

    private:
        // wxXmlNode* Write( wxXmlNode* parent )
        // { 
        //     return ( wxXmlNode* )0;
        // };

    };
}
#endif