/**
 * @file Stamp.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright ( c ) 2022
 * 
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#ifndef Layout_Stamp_h
#define Layout_Stamp_h

#include <wx/pdfdocument.h>

#include "design/LayoutBase.h"
#include "utils/DebugString.h"

namespace Design { 


    typedef enum { 
        AT_InvalidImage = 0, 
        AT_InvalidHeight, 
        AT_InvalidWidth, 
        AT_NbrStampErrorTypes
    }StampErrorType;
    
    extern const char* ErrorStrings[ AT_NbrStampErrorTypes ];

    /**
     * @class Stamp
     *
     * @brief Stamp layout object; Inherits from LayoutBase.
     * The Object is built
     * up of 3 Oobjects. The outer object is the frame container
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
            m_title = GetAttrStr( Design::AT_Name );
            SetShowCatNbr( true );
            SetShowTitle( true );
            wxString height = GetAttrStr( Design::AT_Height );
            SetStampHeight( height ) ;
            wxString width = GetAttrStr( Design::AT_Width );
            SetStampWidth( width ) ;
            CalcFrame( );
        };
        
        Stamp(  ) : LayoutBase(  )
        { 
            SetNodeType( AT_Stamp );
            SetObjectName( AlbumBaseNames[ AT_Stamp ] );
            m_title = "New Stamp";
            SetShowCatNbr( true );
            SetShowTitle( true );
            SetStampHeight( "10.0" ) ;
            SetStampWidth( "10.0" ) ;
            CalcFrame( );
        };

        /**
         * @brief Destroy the Stamp object
         *
         **************************************************/
        ~Stamp( ) { };

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
        void CalcFrame( );

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
//        wxXmlNode* Write( wxXmlNode* parent );

        NodeStatus ValidateNode( );
        void ClearError( );
        void SetError( StampErrorType type, NodeStatus status );
        NodeStatus GetStatus( );
        
        void SetStampHeight( double val ) ;
        void SetStampHeight( wxString str ) ;
        double GetStampHeight( );
        wxString GetStampHeightStr( );
        void SetStampWidth( double val );
        void SetStampWidth( wxString str ) ;
        double GetStampWidth( );
        wxString GetStampWidthStr( ) ;

        /* 
         * @brief Draw object on screen
         * 
         * @param dc current device context
         * @param x position in MM from page top
         * @param y position in MM from page left 
         */        
        void Draw( wxDC &dc, double x, double y );
        void DrawPDF( wxPdfDocument* doc, double x, double y );

        void DrawID( wxDC& dc, double x, double y  );
        void DrawIDPDF( wxPdfDocument* doc, double x, double y );
        //void DrawTitle( wxDC&, wxRect rect  );
        //void MakeMultiLine(  wxDC& dc, wxString text, double width  );
//        void UpdateTitleSize( double width );

        void Save( wxXmlNode* xmlNode );
        wxImage* GetStampImage( );
        wxString GetStampImageFilename( );
        bool GetShowTitle( ){ return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ){ SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };

        bool GetShowCatNbr( ){ return String2Bool( GetAttrStr( AT_ShowCatNbr ) ); };
        void SetShowCatNbr( bool val ){ SetAttrStr( AT_ShowCatNbr, Bool2String( val ) ); };
        
//        wxString GetImageFilename( ){ return m_imageFilename; };
//        void SetImageFilename( wxString str ){  m_imageFilename = str; };

        void ReportLayout(  );

        void DumpStamp( wxTextCtrl* positionTextCtrl );

    private:

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
        // These parameters are all in MM.
        Frame m_stampFrame;
        Frame m_stampImageFrame;
        //Title m_title;

        NodeStatus m_error[ AT_NbrStampErrorTypes ];
        bool m_showCatNbr;
        wxSize m_idTextExtent;
        wxSize m_titleTextExtent;
        bool m_showTitle;
        wxString m_imageFilename;
        DebugString m_debugString;

    };
}
#endif