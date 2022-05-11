/**
 * @file layout/Column.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef Column_H
#define Column_H

#include "design/LayoutBase.h"
#include "design/DesignDefs.h"

namespace Design {

    /**
     * @brief Column layout object; Inherits from LayoutBase.  The column can contain Row or Stamp objects.
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
        void draw( wxDC& dc, double x, double y );
        bool GetShowTitle( ) { return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ) { SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };
        bool GetShowFrame( ) { return String2Bool( GetAttrStr( AT_ShowFrame ) ); };
        void SetShowFrame( bool val ) { SetAttrStr( AT_ShowFrame, Bool2String( val ) ); };
        void Save( wxXmlNode* xmlNode  );

    private:


    };
}

#endif