/**
 * @file layout/Page.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-02
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

#ifndef Page_H
#define Page_H

#include <wx/pdfdocument.h>


#include "design/LayoutBase.h"
#include "design/Album.h"
#include "utils/DebugString.h"

namespace Design {

    class TitleFrame;

    // Encapsulates the parameters of the page
    class Page : public LayoutBase
    {


    public:

        Page( wxXmlNode* node );
        ~Page( ) { };

        void Init( );

        // Draw object on screen; position in MM
        void Draw( wxDC& dc, double x, double y );

        // Draw object in pdf; position in MM
        void DrawPDF( wxPdfDocument* doc, double x, double y );

        wxString GetBorderFileName( ) {
            return m_borderFileName;
        };

        // Get the Bottom PageMargin 
        double GetBottomPageMargin( ) {
            return m_bottomPageMargin;
        };

        // Get the Border Size 
        double GetBorderSize( ) {
            return m_borderSize;
        };

        // Get the Left PageMargin 
        double GetLeftPageMargin( ) {
            return m_leftPageMargin;
        };

        //Get the Right PageMargin
        double GetRightPageMargin( ) {
            return m_rightPageMargin;
        };

        TitleFrame* GetTitleFrame( );

        wxString GetTitleString( );
        wxString  GetSubTitleString( );


        // Get the Top PageMargin 
        double GetTopPageMargin( ) {
            return m_topPageMargin;
        };

        void ReportLayout( );

        void Save( wxXmlNode* parent );

        void SaveFonts( wxXmlNode* parent );

        // Set the Border Size 
        void SetBorderSize( double val ) {
            m_borderSize = val;
        };

        void SetBorderFilename( wxString str ) {
            m_borderFileName = str;
        };

        // Set the Bottom PageMargin 
        void SetBottomPageMargin( double val ) {
            m_bottomPageMargin = val;
        };

        void SetContentFrame( );

        // Set the Left PageMargin 
        void SetLeftPageMargin( double val ) {
            m_leftPageMargin = val;
        };

        // Set the Right PageMargin 
        void SetRightPageMargin( double val ) {
            m_rightPageMargin = val;
        };

        void SetTitleString( wxString str );
        void  SetSubTitleString( wxString str );
        // Set the Top PageMargin 
        void SetTopPageMargin( double val ) {
            m_topPageMargin = val;
        };

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

        void SetShowTitle( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };

        void SetShowSubTitle( bool val ) {
            SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        };

        void LoadFonts( wxXmlNode* node );


        /**
         * @brief Perform the layout for the page.
         * Go to the bottom of each child container object ( row, column, page )
         * and begin filling in position relative to the parent
         * @return true - success
         * @return false - fail
         */
        void UpdatePositions( );

        /**
         * @brief UpdateMinimumSize
         * Calculates the minimum Height and width of the object. It drills down to
         * the lowest layout object with an actual size and begins calculating the
         * min size of its parents as it progresses back up the heirarchy.
         * @return true
         * @return false
         */
        bool UpdateMinimumSize( );

        void UpdateSizes( );

        void UpdateLayout( );

        NodeStatus ValidateNode( );

        wxString Orientation( )
        {
            wxString orientation = GetAttrStr( AT_Orientation );
            if ( orientation.IsEmpty( ) )
            {
                return AlbumPageDefaults( )->Orientation( );
            }
            return orientation;
        };

        void Orientation( wxString orientation )
        {
            SetAttrStr( AT_Orientation, orientation );
            Init( );
        };

        bool IsOrientation( ) {
            return AlbumPageDefaults( )->IsOrientation( Orientation( ) );
        };
    private:

        double m_topPageMargin;
        double m_bottomPageMargin;
        double m_rightPageMargin;
        double m_leftPageMargin;
        double m_borderSize;
        Design::PageType m_pageType;
        Frame m_contentFrame;
        wxString m_borderFileName;
        DebugString m_debugString;
        TitleFrame* m_titleFrame;
        //        PageOrientation m_orientation;
    };
}
#endif