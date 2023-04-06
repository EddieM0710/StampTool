/**
 * @file Text.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright ( c ) 2022
 *
 * This file is part of Sta@mpTool.
 *
 * Sta@mpTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * Sta@mpTool is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Sta@mpTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#ifndef Layout_Text_h
#define Layout_Text_h

#include <wx/pdfdocument.h>

#include "design/LayoutBase.h"
#include "utils/DebugString.h"

namespace Design {


    // typedef enum {
    //     AT_InvalidHeight = 0,
    //     AT_InvalidWidth,
    //     AT_NbrTextErrorTypes
    // }TextErrorType;

    // extern const char* ErrorStrings[ AT_NbrTextErrorTypes ];

    /**
     * @class Text
     *
     * @brief Text layout object; Inherits from LayoutBase.
     *
     *
     **************************************************/
    class Text: public LayoutBase
    {
    public:

        /**
         * @brief Construct a new Text object
         *
         * @param parent
         **************************************************/
        Text( wxXmlNode* node ): LayoutBase( node )
        {
            SetNodeType( AT_Text );
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
            SetShowTitle( true );
            SetHeight( GetAttrDbl( Design::AT_Height ) );
            SetWidth( GetAttrDbl( Design::AT_Width ) );
            CalcFrame( );
        };

        Text( ): LayoutBase( ( wxXmlNode* ) 0 )
        {
            SetNodeType( AT_Text );
            SetObjectName( AlbumBaseNames[ AT_Text ] );
            SetShowTitle( true );
            SetHeight( 40.0 );
            SetWidth( 40.0 );
            m_text = "Enter some text here.";
            CalcFrame( );
        };

        /**
         * @brief Destroy the Text object
         *
         **************************************************/
        ~Text( ) { };

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

        void UpdateSizes( );

        void UpdatePositions( );

        NodeStatus ValidateNode( );

        void UpdateTextSize( double width );

        void ClearError( );
        NodeStatus GetStatus( );
        void CalcFrame( );


        /*
         * @brief Draw object on screen
         *
         * @param dc current device context
         * @param x position in MM from page top
         * @param y position in MM from page left
         */
        void Draw( wxDC& dc, double x, double y );
        void DrawPDF( wxPdfDocument* doc, double x, double y );


        //void DrawTitle( wxDC&, wxRect rect  );
        //void MakeMultiLine(  wxDC& dc, wxString text, double width  );
//        void UpdateTitleSize( double width );

        void Save( wxXmlNode* xmlNode );

        bool GetShowTitle( ) { return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ) { SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };

        void ReportLayout( );

        void DumpText( wxTextCtrl* positionTextCtrl );
    private:

        //        NodeStatus m_error[ AT_NbrTextErrorTypes ];
        wxString m_title;
        Frame m_textFrame;
        wxSize m_titleTextExtent;
        bool m_showTitle;
        DebugString m_debugString;
    };
}
#endif