/**
 * @file layout/LayoutBase.h
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

#ifndef LayoutBase_h
#define LayoutBase_h

#include <wx/string.h>

#include "Defs.h"
#include "design/AlbumBase.h"
#include "design/AlbumVolume.h"
#include "design/Frame.h"
#include "utils/XMLUtilities.h"
#include "gui/AlbumImagePanel.h"
#include "design/LabelFrame.h"

#include <wx/xml/xml.h>
#include <wx/pdfdocument.h>
#include <wx/pdfdocument.h>


class  wxPdfDocument;


namespace Design {

    class LabelFrame;

    /**
     * @brief Base class for all layout objects. The layout objects are
     * initialy loaded from the layout XML.
     *
     */
    class LayoutBase : public AlbumBase
    {


    public:


        /**
         * @brief Unused; Construct a new Album Design Object object
         *
         */
        LayoutBase( );

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         */
        LayoutBase( wxXmlNode* node );

        virtual void DrawPDF( wxPdfDocument* doc, double x, double y ) = 0;

        virtual void Draw( wxDC& dc, double x, double y ) = 0;

        wxString DumpFrame( )
        {
            return m_frame.LayoutString( );
        };

        void DumpLayout( double x, double y );

        void DumpObjectLayout( wxString indent = "" );

        LayoutBase* FindObjectByPos( double x, double y, wxString indent = "" );

        double GetBottomContentMargin( ) { return GetAttrDbl( AT_BottomContentMargin ); };


        /*
         * @brief Get Layout element height
         *
         * @return double - height in MM
         */
        double GetHeight( ) { return m_frame.GetHeight( ); };

        double GetLeftContentMargin( ) { return GetAttrDbl( AT_LeftContentMargin ); };

        /*
         * @brief Get Layout element min height
         *
         * @return double - height in MM
         */
        double GetMinHeight( ) { return m_frame.GetMinHeight( ); };

        /*
         * @brief Get Layout element min width
         *
         * @return double - width in MM
         */
        double GetMinWidth( ) { return m_frame.GetMinWidth( ); };

        double GetRightContentMargin( ) { return GetAttrDbl( AT_RightContentMargin ); };

        bool GetShowFrame( ) { return String2Bool( GetAttrStr( AT_ShowFrame ) ); };

        //        bool GetShowImage( ){ return String2Bool( GetAttrStr( AT_ShowImage ) ); };
        //        void SetShowImage( bool val ){ SetAttrStr( AT_ShowImage, Bool2String( val ) ); };

        bool GetShowNbr( ) { return String2Bool( GetAttrStr( AT_ShowCatNbr ) ); };

        bool GetShowTitle( ) { return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        bool GetShowSubTitle( ) { return String2Bool( GetAttrStr( AT_ShowSubTitle ) ); };

        wxString GetString( Design::FontUsageType fontType )
        {
            if ( fontType == AT_TextFontType )
            {
                return GetText( );
            }
            else if ( fontType == AT_TitleFontType )
            {
                return GetAttrStr( AT_Name );
            }
            else if ( fontType == AT_NameFontType )
            {
                return GetAttrStr( AT_Name );
            }
            else if ( fontType == AT_NbrFontType )
            {
                return GetAttrStr( AT_CatNbr );
            }
            return "";
        };

        // TitleLocation GetTitleLocation( );

        double GetTopContentMargin( ) { return GetAttrDbl( AT_TopContentMargin ); };
        /*
         * @brief Get Layout element position within parent element
         *
         * @return double - position in MM
         */
        double GetXPos( ) { return m_frame.GetXPos( ); };

        /*
         * @brief Get Layout element position
         *
         * @return double - position in MM
         */
        double GetYPos( ) { return m_frame.GetYPos( ); };

        /*
         * @brief Get Layout element width
         *
         * @return double - width in MM
         */
        double GetWidth( ) { return m_frame.GetWidth( ); };



        void ReportLayoutError( wxString funct, wxString err, bool fatal = true );


        bool IsInClient( double x, double y, wxString indent = "" );

        //bool IsTitleLocation( TitleLocation loc );


        virtual void LoadFonts( wxXmlNode* node ) = 0;


        void ReportLayoutFrame( wxString indent = "" );

        void SetClientDimensions( wxDC& dc, double x, double y, double width = 0.0, double height = 0.0, double minWidth = 0.0, double minHeight = 0.0 );
        void SetBottomContentMargin( double val ) { SetAttrDbl( AT_BottomContentMargin, val ); };

        /*
         * @brief  Set Layout element height
         *
         * @param val height - position in MM
         */
        void SetHeight( double val ) { m_frame.SetHeight( val ); };

        void SetLeftContentMargin( double val ) { SetAttrDbl( AT_LeftContentMargin, val ); };
        /*
         * @brief  Set Layout element min height
         *
         * @param val double - min height in MM
         */
        void SetMinHeight( double val ) { m_frame.SetMinHeight( val ); };

        /*
         * @brief  Set Layout element width
         *
         * @param val double - width in MM
         */
        void SetMinWidth( double val ) { m_frame.SetMinWidth( val ); };

        void SetRightContentMargin( double val ) { SetAttrDbl( AT_RightContentMargin, val ); };

        void SetShowFrame( bool val ) { SetAttrStr( AT_ShowFrame, Bool2String( val ) ); };

        void SetShowNbr( bool val ) { SetAttrStr( AT_ShowCatNbr, Bool2String( val ) ); };

        void SetShowTitle( bool val ) { SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };

        void SetShowSubTitle( bool val ) { SetAttrStr( AT_ShowSubTitle, Bool2String( val ) ); };

        void SetTopContentMargin( double val ) { SetAttrDbl( AT_TopContentMargin, val ); };

        //void SetTitleLocation( TitleLocation loc ) { m_titleLocation = loc; };

        /*
         * @brief  Set Layout element position
         *
         * @param val double - position in MM
         */
        void SetYPos( double val ) { m_frame.SetYPos( val ); };

        /*
         * @brief  Set Layout element width
         *
         * @param val double - width in MM
         */
        void SetWidth( double val ) { m_frame.SetWidth( val ); };

        /*
         * @brief  Set Layout element position within parent element
         *
         * @param val double - position in MM
         */
        void SetXPos( double val ) { m_frame.SetXPos( val ); };


        /**
         * @brief Calculate the column layout based on child parameters
         *
         * @return true
         * @return false
         */
        virtual void UpdatePositions( ) = 0;

        /**
         * @brief UpdateMinimumSize
         * Calculates the minimum Height and width of the object. It drills down to
         * the lowest layout object with an actual size and begins calculating the
         * min size of its parents as it progresses back up the heirarchy.
         * @return true
         * @return false
         */
        virtual bool UpdateMinimumSize( ) = 0;

        virtual void UpdateSizes( ) = 0;

        void UpdateString( Design::LabelFrame* frame, double width );

        void ValidateChildType( int& nbrRows, int& nbrCols, int& nbrLeaf );

    protected:
        Frame m_frame;
        Frame m_clientDimensions;
        //defaultDash.Add( .6 );
        //defaultDash.Add( .6 );

    private:

    };
}
#endif
