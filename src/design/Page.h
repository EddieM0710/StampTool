/**
 * @file layout/Page.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef Page_H
#define Page_H

#include "design/LayoutBase.h"
namespace Design {

    class Title;

    /**
     * @brief Encapsulates the parameters of the page
     *
     **************************************************/
    class Page : public LayoutBase
    {
    public:
        Page( AlbumBase* parent, wxXmlNode* node ) : LayoutBase(  parent, node ) 
        { 
            SetNodeType( AT_Page );
            SetObjectName( AlbumBaseNames[GetNodeType() ] );
             };
        ~Page( ) {};

        /**
         * @brief Perform the layout for the page.
         * Go to the bottom of each child container object ( row, column, page)
         * and begin filling in position relative to the parent
         * @return true - success
         * @return false - fail
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

        /**
         * @brief Appends the xml for this page
         *
         * @param parent  expected to be the office:text of the office:body
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );

        /**
         * @brief Get the Top Margin object
         *
         * @return double
         **************************************************/
        double GetTopMargin( ) { return m_topMargin; };

        /**
         * @brief Set the Top Margin object
         *
         * @param val
         **************************************************/
        void SetTopMargin( double val ) { m_topMargin = val; };

        /**
         * @brief Get the Bottom Margin object
         *
         * @return double
         **************************************************/
        double GetBottomMargin( ) { return m_bottomMargin; };

        /**
         * @brief Set the Bottom Margin object
         *
         * @param val
         **************************************************/
        void SetBottomMargin( double val ) { m_bottomMargin = val; };

        /**
         * @brief Get the Right Margin object
         *
         * @return double
         **************************************************/
        double GetRightMargin( ) { return m_rightMargin; };

        /**
         * @brief Set the Right Margin object
         *
         * @param val
         **************************************************/
        void SetRightMargin( double val ) { m_rightMargin = val; };

        /**
         * @brief Get the Left Margin object
         *
         * @return double
         **************************************************/
        double GetLeftMargin( ) { return m_leftMargin; };

        /**
         * @brief Set the Left Margin object
         *
         * @param val
         **************************************************/
        void SetLeftMargin( double val ) { m_leftMargin = val; };

        /**
         * @brief Get the Border Size object
         *
         * @return double
         **************************************************/
        double GetBorderSize( ) { return m_borderSize; };

        /**
         * @brief Set the Border Size object
         *
         * @param val
         **************************************************/
        void SetBorderSize( double val ) { m_borderSize = val; };

        NodeStatus ValidateNode();
        
        void draw( wxPaintDC &dc, int x, int y );

    private:


        /**
         * @brief Size of the page top margin
         *
         **************************************************/
        double m_topMargin;

        /**
         * @brief Size of the age bottom margine
         *
         **************************************************/
        double m_bottomMargin;

        /**
         * @brief  size of the page right margin
         *
         **************************************************/
        double m_rightMargin;

        /**
         * @brief Size of the page left margin
         *
         **************************************************/
        double m_leftMargin;


        /**
         * @brief Size of the border
         *
         **************************************************/
        double m_borderSize;

    };
}
#endif