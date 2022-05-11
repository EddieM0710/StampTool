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

#include "design/LayoutBase.h"

namespace Design {


    typedef enum {
        AT_InvalidImage = 0,
        AT_InvalidHeight,
        AT_InvalidWidth,
        AT_NbrStampErrorTypes
    }StampErrorType;
    
    extern const char* ErrorStrings[AT_NbrStampErrorTypes];

    /**
     * @class Stamp
     *
     * @brief Stamp layout object; Inherits from LayoutBase.
     * The Object is built
     * up of 3 ODT objects. The outer object is the frame container
    *  for the stamp frame and the title text. The text is the only thing visible.
     * The next is embedded in it and is tthe visible frame for the stamp.
     * The 3rd one is embedded in the 2nd one and is the image of the object.
     *
     **************************************************/
    class Stamp : public LayoutBase
    {
    public:

        /**
         * @brief Construct a new Stamp object
         *
         * @param parent
         **************************************************/
        Stamp(  wxXmlNode* node ) : LayoutBase( node )
        {
            SetNodeType( AT_Stamp );
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
            wxString height = GetAttrStr( Design::AT_Height );
            SetStampHeight( height ) ;
            wxString width = GetAttrStr( Design::AT_Width );
            SetStampWidth( width ) ;
            CalcFrame();
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
         * @return falseDesign::
        /**
        * @brief UpdateMinimumSize
        * Calculates the minimum Height and width of the object. It drills down to
        * the lowest layout object with an actual size and begins calculating the
        * min size of its parents as it progresses back up the heirarchy.
        * @return true
        * @return false
        **************************************************/
        bool UpdateMinimumSize( );
        void CalcFrame();

        void UpdateSizes( );

        void UpdatePositions( );

        /**
         * 
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

        NodeStatus ValidateNode( );
        void ClearError();
        void SetError( StampErrorType type, NodeStatus status );
        NodeStatus GetStatus();
        
        void SetStampHeight( double val ) ;
        void SetStampHeight( wxString str ) ;
        double GetStampHeight( );
        wxString GetStampHeightStr( );
        void SetStampWidth( double val );
        void SetStampWidth( wxString str ) ;
        double GetStampWidth( );
        wxString GetStampWidthStr( ) ;
        
        void draw( wxDC &dc, double x, double y );
        void Save( wxXmlNode* xmlNode );
        // bool GetShowTitle(){ return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        // void SetShowTitle( bool val ){ SetAttrStr( AT_ShowTitle, Bool2String( val) ); };
        // bool GetShowID(){ return String2Bool( GetAttrStr( AT_ShowId ) ); };
        // void SetShowID( bool val ){ SetAttrStr( AT_ShowId, Bool2String( val ) ); };
        wxImage* GetStampImage();

    private:

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

        bool GetShowTitle(){ return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ){ SetAttrStr( AT_ShowTitle, Bool2String( val) ); };

        bool GetShowID(){ return String2Bool( GetAttrStr( AT_ShowId ) ); };
        void SetShowID( bool val ){ SetAttrStr( AT_ShowId, Bool2String( val ) ); };

        /**
         * @brief The name of the stamp to display
         *
         **************************************************/
//        wxString m_name;

        // The LayoutBase for this objects contains the frame parameters for the stamp Album object. 
        // It is 10% Larger than the actual Stamp.
        // The m_stampFrame has the parameters of the actual Stamp.
        // The m_stampImageFrame has the parameters for the printed album image. 
        // It is 10% smaller than the actual stamp.
        // These parameters are all in inches.
        Frame m_stampFrame;
        Frame m_stampImageFrame;

        NodeStatus m_error[AT_NbrStampErrorTypes];
        bool m_showID;
        bool m_showTitle;


    };
}
#endif