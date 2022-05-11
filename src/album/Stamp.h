/**
 * @file Stamp.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef Layout_Stamp_h
#define Layout_Stamp_h

#include "album/LayoutNode.h"

namespace Layout {


    /**
     * @class Stamp
     *
     * @brief Stamp layout object; Inherits from LayoutNode.
     * The Object is built
     * up of 3 ODT objects. The outer object is the frame container
    *  for the stamp frame and the title text. The text is the only thing visible.
     * The next is embedded in it and is tthe visible frame for the stamp.
     * The 3rd one is embedded in the 2nd one and is the image of the object.
     *
     **************************************************/
    class Stamp : public LayoutNode
    {
    public:
        /**
         * @brief Construct a new Stamp object
         *
         * @param parent
         **************************************************/
        Stamp( AlbumNode* parent, wxXmlNode* node ) : LayoutNode( parent, node ) 
        {
             SetNodeType( AT_Stamp );
            SetObjectName( AlbumNodeNames[GetNodeType() ] ); 
            };

        /**
         * @brief Destroy the Stamp object
         *
         **************************************************/
        ~Stamp( ) {};

        /**
         * @brief
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
        void UpdateMinimumSize( );

        void UpdateSizes( );

        /**
         * @brief Builds the frame container for the stamp.  The Object is built
         * up of 3 objects. The outer object is the frame container
         * for the stamp frame and the title text. The text is the only thing visible.
         * The next is embedded in it and is tthe visible frame for the stamp.
         * The 3rd one is embedded in the 2nd one and is the image of the object.
         *
         * @param parent
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* Write( wxXmlNode* parent );

        /**
         * @brief Get the Frame Width
         *
         * @return double
         **************************************************/
        double GetFrameWidth( );

        /**
         * @brief Get the Frame Height
         *
         * @return double
         **************************************************/
        double GetFrameHeight( );

        wxXmlNode* GetCatalogStamp( ) { return m_catalogStamp; };
        void SetCatalogStamp( wxXmlNode* node ) { m_catalogStamp = node; };
        
    private:

        /**
         * @brief creates the ODT XML outside object frame of the object
         *
         * @param parent
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* StampObject( wxXmlNode* parent );

        /**
         * @brief Creates ODT XML frame for the Stamp object
         *
         * @param parent
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* StampFrameObject( wxXmlNode* parent );

        /**
         * @brief Creates the ODT XML image object
         *
         * @param parent
         * @return wxXmlNode*
         **************************************************/
        wxXmlNode* StampImageObject( wxXmlNode* parent );


        /**
         * @brief The name of the stamp to display
         *
         **************************************************/
        wxString m_name;

        /**
         * @brief Stamp image width
         *
         **************************************************/
        double m_widthStampImage;

        /**
         * @brief Stamp image height
         *
         **************************************************/
        double m_heightStampImage;

        /**
         * @brief path to the stap image
         *
         **************************************************/
        wxString m_imageLink;

        wxXmlNode* m_catalogStamp;
    };
}
#endif