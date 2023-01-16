/**
 * @file Content.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-08
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
#ifndef Content_h
#define Content_h

#include "odt/ODTDefs.h"
#include <wx/xml/xml.h>

namespace ODT {

    class Content
    {
    public:
        Content( );
        ~Content( ) {};

        /**
         * @brief
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* FindOfficeBody( );

        /**
         * @brief
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* FindOfficeContentRoot( );

        wxXmlNode* FindFirstPage( );

        /**
         * @brief
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* FindOfficeText( );

        /**
         * @brief
         *
         * @return true
         * @return false
         **************************************************/
        bool EnableSoftPageBreak( );


        /**
         * @brief
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* AddTitlePage( );

        /**
         * @brief
         *
         * @param parent
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* AddNewPage( );

        /**
         * @brief
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* FindOfficAutomaticStyles( );

        /**
         * @brief Get the Content object
         *
         * @return wxXmlDocument*
         **************************************************/
        wxXmlDocument* GetContent( ) { return m_content; };

        /**
         * @brief
         *
         * @param parent
         * @param xPos
         * @param yPos
         * @param width
         * @param height
         * @param drawStyleName
         * @param textAnchorType
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* WriteFrame( wxXmlNode* parent, double xPos,
            double yPos,
            double width,
            double height,
            const char* drawStyleName,  // fr2
            const char* textAnchorType, // "page", "paragraph"
            const char* textStyleName = Frame20Content );
        /**
         * @brief
         *
         * @param parent
         * @param xPos
         * @param yPos
         * @param width
         * @param height
         * @param drawStyleName
         * @param textAnchorType
         *
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* WriteFrameFixedSize( wxXmlNode* parent, double xPos,
            double yPos,
            double width,
            double height,
            const char* drawStyleName,  // fr2
            const char* textAnchorType, // "page", "paragraph"
            const char* textStyleName = Frame20Content );
        /**
         * @brief
         *>GetContent()
         * @param parent
         * @param xPos
         * @param yPos
         * @param width
         * @param height
         * @param drawStyleName
         * @param textAnchorType
         * @param textStyleName
         * @param link
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* WriteImage( wxXmlNode* parent,
            double xPos,
            double yPos,
            double width,
            double height,
            wxString& drawStyleName,  // fr2
            wxString& textAnchorType, // "page", "paragraph"
            wxString& textStyleName,   // "P1"
            wxString& link );

        wxXmlNode* WriteTextBox( wxXmlNode* parent, double xPos,
            double yPos,
            double width,
            double height,
            wxString& drawStyleName,  // fr2
            wxString& textAnchorType, // "page", "paragraph"
            wxString& textStyleName,
            wxString point,
            wxString text );

        bool AddPageBackgroundFrameStyles( wxString drawName );
        bool AddPageFrameStyles( );

        bool Save( );
        wxXmlDocument* ContentXML( ) { return m_content; };

    private:
        wxXmlDocument* m_content;
    };

}
#endif