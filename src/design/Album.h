/**
 * @file layout/Album.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef Album_H
#define Album_H

#include "design/AlbumBase.h"
#include "design/DesignDefs.h"
#include "utils/Project.h"

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

        /**
         * @brief Get the Page Height
         *
         * @return double
         **************************************************/
        double GetPageHeight( );

        /**
         * @brief Get the Top Margin
         *
         * @return double
         **************************************************/
        double GetTopMargin( );

        /**
         * @brief Get the Bottom Margin
         *
         * @return double
         **************************************************/
        double GetBottomMargin( );

        /**
         * @brief Get the Right Margin
         *
         * @return double
         **************************************************/
        double GetRightMargin( );

        /**
         * @brief Get the Left Margin
         *
         * @return double
         **************************************************/
        double GetLeftMargin( );

        /**
         * @brief Get the Border Size
         *
         * @return double
         **************************************************/
        double GetBorderSize( );

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

    private:

    };
}
#endif