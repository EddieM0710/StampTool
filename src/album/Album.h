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

#include "album/AlbumNode.h"
#include "utils/Project.h"

namespace Layout {

    /**
     * @brief Album layout object; inherits from LayoutNode. This is the top  LayoutNode for holding all the objecs within the album
     *
     **************************************************/
    class Album : public AlbumNode
    {
    public:

        /**
         * @brief Construct a new Album object. The top layout LayoutNode
         * for holding all the objecs within the album
         *
         **************************************************/
        Album( ) : AlbumNode( )
        {
            SetObjectName( "Album" );
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
        bool UpdatePositions( );

        /**
         * @brief init drills down to the lowest layout object with an actual size
         * and begins calculating the min size of its parents as it progresses
         * back up the heirarchy.
         * @return true
         * @return false
         **************************************************/
        void UpdateMinimumSize( );

        bool UpdateSizes( );

        /**
         * @brief Decends into each Album layout child performing its write to the content, styles, or images ODT XML
         *
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );

        /**
         * @brief Get the Width
         *
         * @return double
         **************************************************/
        double GetWidth( )
        {
            return GetAttrValDbl( "PageWidth" );
        };

        /**
         * @brief Get the Height
         *
         * @return double
         **************************************************/
        double GetHeight( )
        {
            GetAttrValDbl( "PageHeight" );
        };


        /**
         * @brief Get the Page Width
         *
         * @return double
         **************************************************/
        double GetPageWidth( )
        {
            return GetAttrValDbl( "PageWidth" );
        };

        /**
         * @brief Get the Page Height
         *
         * @return double
         **************************************************/
        double GetPageHeight( )
        {
            return GetAttrValDbl( "PageHeight" );
        };

        /**
         * @brief Get the Top Margin
         *
         * @return double
         **************************************************/
        double GetTopMargin( )
        {
            return GetAttrValDbl( "TopMargin" );
        };

        /**
         * @brief Get the Bottom Margin
         *
         * @return double
         **************************************************/
        double GetBottomMargin( )
        {
            return GetAttrValDbl( "BottomMargin" );
        };

        /**
         * @brief Get the Right Margin
         *
         * @return double
         **************************************************/
        double GetRightMargin( )
        {
            return GetAttrValDbl( "RightMargin" );
        };

        /**
         * @brief Get the Left Margin
         *
         * @return double
         **************************************************/
        double GetLeftMargin( )
        {
            return GetAttrValDbl( "LeftMargin" );
        };

        /**
         * @brief Get the Border Parameters
         *
         * @param size
         * @param imageLink
         * @return double
         **************************************************/
        double GetBorderParameters( double size, wxString& imageLink );

        /**
         * @brief Get the Border Size
         *
         * @return double
         **************************************************/
        double GetBorderSize( )
        {
            return GetAttrValDbl( "BorderSize" );
        };

        /**
         * @brief Get the Border File Name
         *
         * @return wxString
         **************************************************/
        wxString GetBorderFileName( )
        {
            return GetAttrVal( "BorderFileName" );
        };

        /**
         * @brief Get the Stamp Properties
         *
         * @return wxString
         **************************************************/
        wxString GetStampProperties( )
        {
            return GetAttrVal( "StampProperties" );
        };

        /**
         * @brief Get the Image Path
         *
         * @return wxString
         **************************************************/
        wxString GetImagePath( )
        {
            return GetAttrVal( "ImagePath" );
        };

        /**
         * @brief Get the Doc Name
         *
         * @return wxString
         **************************************************/
        wxString GetDocName( )
        {
            return GetAttrVal( "Name" );
        };


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

    private:

    };
}
#endif