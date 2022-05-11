/**
 * @file layout/Title.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
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
            SetObjectName( AlbumBaseNames[GetNodeType() ] ); 
            };

        /**
         * @brief Destroy the Title object
         *
         **************************************************/
        ~Title( ) {};

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

        NodeStatus ValidateNode();


    private:


    };
}
#endif