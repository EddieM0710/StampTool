/**
 * @file layout/Row.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
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
            SetShowFrame(true);
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
        void draw( wxDC &dc, double x, double y );
        void Save( wxXmlNode* xmlNode );

    private:
        bool m_showID;
        bool m_showTitle;

    };

}
#endif