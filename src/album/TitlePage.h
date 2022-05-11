/**
 * @file layout/Titlelayout/Page.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef TitlePage_H
#define TitlePage_H

#include "album/LayoutNode.h" 
#include "album/AlbumDefs.h"

namespace Layout {


    //class Border;

    /**
     * @brief TitlePage layout object; inherits from LayoutNode
     * @todo Nearly nothing in class TitlePage has been done.
     *
     **************************************************/
    class TitlePage : public LayoutNode
    {
    public:
        /**
         * @brief Construct a new Title Page object
         *
         * @param parent
         **************************************************/
        TitlePage( AlbumNode* parent, wxXmlNode* node ) : LayoutNode( parent, node ) 
        { 
            SetNodeType( AT_TitlePage ); 
            SetObjectName( AlbumNodeNames[GetNodeType() ] );
            };

        /**
         * @brief Destroy the Title Page object
         *
         **************************************************/
        ~TitlePage( ) {};

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
        void UpdateMinimumSize( );
        //wxXmlNode *Write(wxXmlNode *parent){};


        void UpdateSizes( );

        bool ValidateNode();

    private:
        wxXmlNode* Write( wxXmlNode* parent )
        {
            return ( wxXmlNode* )0;
        };

    };
}
#endif