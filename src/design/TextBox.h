/**
 * @file TextBox.h
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
 */

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
     * @class TextBox
     *
     * @brief TextBox layout object; Inherits from LayoutBase.
     *
     *
     */
    class TextBox : public LayoutBase
    {


    public:





        /**
         * @brief Construct a new TextBox object
         *
         * @param parent
         */
        TextBox( wxXmlNode* node ) : LayoutBase( node )
        {
            SetNodeType( AT_Text );
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
            SetShowTitle( true );
            SetShowSubTitle( false );
            SetHeight( GetAttrDbl( Design::AT_Height ) );
            SetWidth( GetAttrDbl( Design::AT_Width ) );
            CalcFrame( );
            m_titleFrame = new LabelFrame( Design::AT_TitleFontType );
            m_titleFrame->SetString( GetAttrStr( AT_Name ) );
            m_textFrame = new LabelFrame( Design::AT_TextFontType );
            m_textFrame->SetString( GetText( ) );
        };

        ///  @brief Construct a new Text Box object
        ///  
        TextBox( ) : LayoutBase( ( wxXmlNode* ) 0 )
        {
            SetNodeType( AT_Text );
            SetObjectName( AlbumBaseNames[ AT_Text ] );
            SetShowTitle( true );
            SetShowSubTitle( false );
            SetHeight( 40.0 );
            SetWidth( 40.0 );
            m_text = "Enter some text here.";
            CalcFrame( );
            m_titleFrame = new LabelFrame( Design::AT_TitleFontType );
            m_titleFrame->SetString( GetAttrStr( AT_Name ) );
            m_textFrame = new LabelFrame( Design::AT_TextFontType );
            m_textFrame->SetString( GetText( ) );
        };

        /**
         * @brief Destroy the TextBox object
         *
         */
        ~TextBox( ) { };

        ///  @brief 
        ///  
        void CalcFrame( );

        ///  @brief 
        ///  
        void ClearError( );

        /*
         * @brief Draw object on screen
         *
         * @param dc current device context
         * @param x position in MM from page top
         * @param y position in MM from page left
         */
        void Draw( wxDC& dc, double x, double y );

        ///  @brief 
        ///  
        ///  @param doc 
        ///  @param x 
        ///  @param y 
        void DrawPDF( wxPdfDocument* doc, double x, double y );

        ///  @brief 
        ///  
        ///  @param positionTextCtrl 
        void DumpText( wxTextCtrl* positionTextCtrl );

        ///  @brief 
        ///  
        ///  @param node 
        void LoadFonts( wxXmlNode* node );

        ///  @brief Get the Status object
        ///  
        ///  @return NodeStatus 
        NodeStatus GetStatus( );

        ///  @brief Get the Show Title object
        ///  
        ///  @return true 
        ///  @return false 
        bool GetShowTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowTitle ) );
        };
        bool GetShowSubTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowSubTitle ) );
        };

        void SetShowNbr( bool val ){};
        bool GetShowNbr( ) {
            return false;
        };


        ///  @brief Get the Text Frame object
        ///  
        ///  @return LabelFrame* 
        LabelFrame* GetTextFrame( );

        ///  @brief Get the Text String object
        ///  
        ///  @return wxString 
        wxString GetTextString( );

        ///  @brief Get the Title Frame object
        ///  
        ///  @return LabelFrame* 
        LabelFrame* GetTitleFrame( );

        ///  @brief Get the Title String object
        ///  
        ///  @return wxString 
        wxString GetTitleString( );

        ///  @brief 
        ///  
        void ReportLayout( );

        ///  @brief 
        ///  
        ///  @param xmlNode 
        void Save( wxXmlNode* xmlNode );

        ///  @brief Set the Title String object
        ///  
        ///  @param str 
        void SetTitleString( wxString str );

        ///  @brief Set the Show Title object
        ///  
        ///  @param val 
        void SetShowTitle( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };
        void SetShowSubTitle( bool val ) {
            SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        };

        ///  @brief Set the Text String object
        ///  
        ///  @param str 
        void SetTextString( wxString str );

        ///  @brief 
        ///  
        ///  @param parent 
        void SaveFonts( wxXmlNode* parent );

        /**
         * @brief UpdateMinimumSize
         * Calculates the minimum Height and width of the object. It drills down to
         * the lowest layout object with an actual size and begins calculating the
         * min size of its parents as it progresses back up the heirarchy.
         * @return true
         * @return false
         */
        bool UpdateMinimumSize( );

        ///  @brief 
        ///  
        void UpdatePositions( );

        ///  @brief 
        ///  
        void UpdateSizes( );

        ///  @brief 
        ///  
        ///  @param width 
        void UpdateTextSize( double width );

        ///  @brief 
        ///  
        ///  @return NodeStatus 
        NodeStatus ValidateNode( );


    private:

        //        NodeStatus m_error[ AT_NbrTextErrorTypes ];
        wxString m_title;
        Frame m_textBoxFrame;
        //wxSize m_titleTextExtent;
        bool m_showTitle;
        DebugString m_debugString;
        LabelFrame* m_titleFrame;
        LabelFrame* m_textFrame;

    };
}
#endif