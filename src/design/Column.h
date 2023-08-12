/**
 * @file layout/Column.h
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
 */

#ifndef Column_H
#define Column_H

#include <wx/pdfdocument.h>

#include "design/LayoutBase.h"
#include "utils/DebugString.h"

namespace Design {

    /**
     * @brief Column layout object; Inherits from LayoutBase.
     * The column can contain Row or Stamp objects.
     *
     */
    class Column : public LayoutBase
    {
    public:





        Column( wxXmlNode* node ) : LayoutBase( node ) {
            SetNodeType( AT_Col );
            SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
            SetShowFrame( false );
            SetShowTitle( false );
            SetShowSubTitle( false );
            SetFixedSpacingSize( "4" );
            SetCalculateSpacing( true );
            m_titleFrame = new LabelFrame( Design::AT_TitleFontType );
            m_titleFrame->SetString( GetAttrStr( AT_Name ) );
        };

        ///  @brief Destroy the Column object
        ///  
        ~Column( ) { };

        bool CalculateSpacing( ) { return String2Bool( GetAttrStr( AT_CalculateSpacing ) ); };

        /*
         * @brief Draw object on screen
         *
         * @param dc current device context
         * @param x position in MM
         * @param y position in MM
         */
        void Draw( wxDC& dc, double x, double y );

        ///  @brief 
        ///  
        ///  @param doc 
        ///  @param x 
        ///  @param y 
        void DrawPDF( wxPdfDocument* doc, double x, double y );

        ///  @brief Get the Fixed Spacing object
        ///  
        ///  @return wxString 
        wxString GetFixedSpacing( ) { return GetAttrStr( AT_FixedSpacingSize ); };

        ///  @brief Get the Fixed Spacing Dbl object
        ///  
        ///  @return double 
        double GetFixedSpacingDbl( ) { return GetAttrDbl( AT_FixedSpacingSize ); };

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
        ///  @param node 
        void LoadFonts( wxXmlNode* node );

        ///  @brief 
        ///  
        void ReportLayout( );

        ///  @brief 
        ///  
        ///  @param xmlNode 
        void Save( wxXmlNode* xmlNode );

        ///  @brief 
        ///  
        ///  @param parent 
        void SaveFonts( wxXmlNode* parent );

        ///  @brief Set the Calculate Spacing object
        ///  
        ///  @param val 
        void SetCalculateSpacing( bool val ) { SetAttrStr( AT_CalculateSpacing, Bool2String( val ) ); };

        ///  @brief Set the Fixed Spacing Size object
        ///  
        ///  @param str 
        void SetFixedSpacingSize( wxString str ) { SetAttrStr( AT_FixedSpacingSize, str ); };

        ///  @brief Set the Title String object
        ///  
        ///  @param str 
        void SetTitleString( wxString str );

        /**
         * @brief UpdateMinimumSize
         * Calculates the minimum Height and width of the object. It drills down to
         * the lowest layout object with an actual size and begins calculating the
         * min size of its parents as it progresses back up the heirarchy.
         * @return true
         * @return false
         */
        bool UpdateMinimumSize( );

        /**
         * @brief Calculate the column layout based on child parameters.
         *  Go to the bottom of each child container object ( row, column, page )
         * and begin filling in position relative to the parent
         * *
         *
         * @return true
         * @return false
         */
        void UpdatePositions( );

        ///  @brief 
        ///  
        void UpdateSizes( );

        ///  @brief 
        ///  
        ///  @return NodeStatus 
        NodeStatus ValidateNode( );

        TitleLocation  GetTitleLocation( );
        void SetTitleLocation( TitleLocation loc );

    private:
        // bool m_showTitle;
        DebugString m_debugString;
        LabelFrame* m_titleFrame;

    };
}

#endif