/**
 * @file Content.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-08
 *
 * @copyright Copyright (c) 2022
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
            const char* drawStyleName,  // fr1
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
            const char* drawStyleName,  // fr1
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
            wxString& drawStyleName,  // fr1
            wxString& textAnchorType, // "page", "paragraph"
            wxString& textStyleName,   // "P1"
            wxString& link );

        wxXmlNode* WriteTextBox( wxXmlNode* parent, double xPos,
            double yPos,
            double width,
            double height,
            wxString& drawStyleName,  // fr1
            wxString& textAnchorType, // "page", "paragraph"
            wxString& textStyleName,
            wxString point,
            wxString text );

        bool AddPageFrameStyles( );

        bool Save( );
        wxXmlDocument* ContentXML( ) { return m_content; };

    private:
        wxXmlDocument* m_content;
    };

}
#endif