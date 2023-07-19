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

    class Title;

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

        wxString GetBorderFileName( ) { return m_borderFileName; };

        // Get the Bottom Margin 
        double GetBottomMargin( ) { return m_bottomMargin; };

        // Get the Border Size 
        double GetBorderSize( ) { return m_borderSize; };

        // Get the Left Margin 
        double GetLeftMargin( ) { return m_leftMargin; };

        //Get the Right Margin
        double GetRightMargin( ) { return m_rightMargin; };

        LabelFrame* GetTitleFrame( );

        wxString GetTitleString( );

        // Get the Top Margin 
        double GetTopMargin( ) { return m_topMargin; };

        void ReportLayout( );

        void Save( wxXmlNode* parent );

        void SaveFonts( wxXmlNode* parent );

        // Set the Border Size 
        void SetBorderSize( double val ) { m_borderSize = val; };

        void SetBorderFilename( wxString str ) { m_borderFileName = str; };

        // Set the Bottom Margin 
        void SetBottomMargin( double val ) { m_bottomMargin = val; };

        void SetContentFrame( );

        // Set the Left Margin 
        void SetLeftMargin( double val ) { m_leftMargin = val; };

        // Set the Right Margin 
        void SetRightMargin( double val ) { m_rightMargin = val; };

        void SetTitleString( wxString str );

        // Set the Top Margin 
        void SetTopMargin( double val ) { m_topMargin = val; };

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
        wxString GetOrientation( )
        {
            wxString orientation = GetAttrStr( AT_Orientation );
            if ( orientation.IsEmpty( ) )
            {
                return GetAlbum( )->GetDefaultOrientation( );
            }
            return orientation;
        };
        void SetOrientation( wxString orientation )
        {
            SetAttrStr( AT_Orientation, orientation );
            Init( );
        };

        bool IsDefaultOrientation( ) { return GetAlbum( )->IsDefaultOrientation( GetOrientation( ) ); };
    private:

        double m_topMargin;
        double m_bottomMargin;
        double m_rightMargin;
        double m_leftMargin;
        double m_borderSize;
        Frame m_contentFrame;
        wxString m_borderFileName;
        DebugString m_debugString;
        LabelFrame* m_titleFrame;
        //        PageOrientation m_orientation;
    };
}
#endif