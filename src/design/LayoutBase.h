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
 **************************************************/

#ifndef LayoutBase_h
#define LayoutBase_h

#include <wx/string.h>

#include "Defs.h"
#include "design/AlbumBase.h"
#include "design/DesignData.h"
#include "design/Frame.h"
#include "utils/XMLUtilities.h"

#include <wx/xml/xml.h>

class  wxPdfDocument;

namespace Design {


    class Title;

    /**
     * @brief Base class for all layout objects. The layout objects are
     * initialy loaded from the layout XML.
     *
     **************************************************/
    class LayoutBase: public AlbumBase
    {
    public:
        /**
         * @brief Unused; Construct a new Album Design Object object
         *
         **************************************************/
        LayoutBase( ): AlbumBase( ) {
            SetTopContentPadding( 0 );
            SetBottomContentPadding( 0 );
            SetLeftContentPadding( 0 );
            SetRightContentPadding( 0 );
            SetTitleLocation( Design::AT_TitleLocationDefault );
        };

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         **************************************************/
        LayoutBase( wxXmlNode* node ): AlbumBase( node ) {
            SetTopContentPadding( 0 );
            SetBottomContentPadding( 0 );
            SetLeftContentPadding( 0 );
            SetRightContentPadding( 0 );
            SetTitleLocation( Design::AT_TitleLocationDefault );
        };

        virtual void DrawPDF( wxPdfDocument* doc, double x, double y ) = 0;
        virtual void Draw( wxDC& dc, double x, double y ) = 0;
        /*
         * @brief Get Layout element position within parent element
         *
         * @return double - position in MM
         */
        double GetXPos( ) { return m_frame.GetXPos( ); };

        /*
         * @brief  Set Layout element position within parent element
         *
         * @param val double - position in MM
         */
        void SetXPos( double val ) { m_frame.SetXPos( val ); };

        /*
         * @brief Get Layout element position
         *
         * @return double - position in MM
         */
        double GetYPos( ) { return m_frame.GetYPos( ); };

        /*
         * @brief  Set Layout element position
         *
         * @param val double - position in MM
         */
        void SetYPos( double val ) { m_frame.SetYPos( val ); };

        /*
         * @brief Get Layout element width
         *
         * @return double - width in MM
         */
        double GetWidth( ) { return m_frame.GetWidth( ); };

        /*
         * @brief  Set Layout element width
         *
         * @param val double - width in MM
         */
        void SetWidth( double val ) { m_frame.SetWidth( val ); };

        /*
         * @brief Get Layout element height
         *
         * @return double - height in MM
         */
        double GetHeight( ) { return m_frame.GetHeight( ); };

        /*
         * @brief  Set Layout element height
         *
         * @param val height - position in MM
         */
        void SetHeight( double val ) { m_frame.SetHeight( val ); };

        /*
         * @brief Get Layout element min width
         *
         * @return double - width in MM
         */
        double GetMinWidth( ) { return m_frame.GetMinWidth( ); };

        /*
         * @brief  Set Layout element width
         *
         * @param val double - width in MM
         */
        void SetMinWidth( double val ) { m_frame.SetMinWidth( val ); };

        /*
         * @brief Get Layout element min height
         *
         * @return double - height in MM
         */
        double GetMinHeight( ) { return m_frame.GetMinHeight( ); };

        /*
         * @brief  Set Layout element min height
         *
         * @param val double - min height in MM
         */
        void SetMinHeight( double val ) { m_frame.SetMinHeight( val ); };

        wxString GetTitle( ) { return GetAttrStr( Design::AT_Name ); };
        void SetTitle( wxString title ) { SetAttrStr( Design::AT_Name, title ); };

        // Get TitleHeight in MM
        double GetTitleHeight( ) { return m_titleFrame.GetHeight( ); };
        double GetTitleMinHeight( ) { return m_titleFrame.GetMinHeight( ); };

        // TitleWidth in MM   
        double GetTitleWidth( ) { return m_titleFrame.GetWidth( ); };
        double GetTitleMinWidth( ) { return m_titleFrame.GetMinWidth( ); };
        void SetTitleXPos( double val ) { m_titleFrame.SetXPos( val ); };
        void SetTitleYPos( double val ) { m_titleFrame.SetYPos( val ); };
        double GetTitleXPos( ) { return m_titleFrame.GetXPos( ); };
        double GetTitleYPos( ) { return m_titleFrame.GetYPos( ); };


        bool GetShowTitle( ) { return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ) { SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };

        bool GetShowFrame( ) { return String2Bool( GetAttrStr( AT_ShowFrame ) ); };
        void SetShowFrame( bool val ) { SetAttrStr( AT_ShowFrame, Bool2String( val ) ); };

        //        bool GetShowImage( ){ return String2Bool( GetAttrStr( AT_ShowImage ) ); };
        //        void SetShowImage( bool val ){ SetAttrStr( AT_ShowImage, Bool2String( val ) ); };

        bool GetShowNbr( ) { return String2Bool( GetAttrStr( AT_ShowCatNbr ) ); };
        void SetShowNbr( bool val ) { SetAttrStr( AT_ShowCatNbr, Bool2String( val ) ); };


        double GetTopContentPadding( ) { return GetAttrDbl( AT_TopContentPadding ); };
        void SetTopContentPadding( double val ) { SetAttrDbl( AT_TopContentPadding, val ); };

        double GetBottomContentPadding( ) { return GetAttrDbl( AT_BottomContentPadding ); };
        void SetBottomContentPadding( double val ) { SetAttrDbl( AT_BottomContentPadding, val ); };

        double GetLeftContentPadding( ) { return GetAttrDbl( AT_LeftContentPadding ); };
        void SetLeftContentPadding( double val ) { SetAttrDbl( AT_LeftContentPadding, val ); };

        double GetRightContentPadding( ) { return GetAttrDbl( AT_RightContentPadding ); };
        void SetRightContentPadding( double val ) { SetAttrDbl( AT_RightContentPadding, val ); };

        void ValidateChildType( int& nbrRows, int& nbrCols, int& nbrLeaf );
        void ReportLayoutError( wxString funct, wxString err, bool fatal = true );

        /**
         * @brief Calculate the column layout based on child parameters
         *
         * @return true
         * @return false
         **************************************************/
        virtual void UpdatePositions( ) = 0;

        /**
         * @brief UpdateMinimumSize
         * Calculates the minimum Height and width of the object. It drills down to
         * the lowest layout object with an actual size and begins calculating the
         * min size of its parents as it progresses back up the heirarchy.
         * @return true
         * @return false
         **************************************************/
        virtual bool UpdateMinimumSize( ) = 0;

        virtual void UpdateSizes( ) = 0;

        /*
         * @brief  Calc Title size based on allowed width and font size.
         *
         * @param width the max width of the title
         */
         //void UpdateTitleSize( double width );
         //void UpdateTextSize( double width );
        wxRealPoint CalcTextSize( wxString text, double width, wxFont font );
        void UpdateNameSize( double width );
        void UpdateNbrSize( double width );
        void UpdateTextSize( double width );
        void UpdateTitleSize( double width );

        //void WriteFrame( wxString loc, wxString name, wxString id, Frame* frame );
        void DumpLayout( double x, double y );

        // wxXmlNode* GetTitleFont( wxXmlNode* node, wxString name )
        // { 
        //     wxTreeItemId ctrlID = GetTreeItemId( );
        //     //    GetDesignTreeCtrl( )->GetItemData( ctrlID );
        //     return (wxXmlNode*)0; 
        // }

        void ReportLayoutFrame( wxString indent = "" );

        //wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name );

        void DumpObjectLayout( wxString indent = "" );
        LayoutBase* FindObjectByPos( double x, double y, wxString indent = "" );

        //void SetClientDimensions( Frame *frame );

        void SetClientDimensions( wxDC& dc, double x, double y, double width = 0.0, double height = 0.0, double minWidth = 0.0, double minHeight = 0.0 );

        bool IsInClient( double x, double y, wxString indent = "" );
        wxString DumpFrame( )
        {
            return m_frame.LayoutString( );
        };

        bool IsTitleLocation( TitleLocation loc );

        TitleLocation GetTitleLayoutLocation( );
        void SetTitleLocation( TitleLocation loc ) { m_titleLocation = loc; };

    protected:
        Frame m_frame;
        Frame m_clientDimensions;
        //       wxString m_title;
        Frame m_titleFrame;
        Frame m_textFrame;
        Frame m_nbrFrame;
        Frame m_nameFrame;
        TitleLocation m_titleLocation;

    };
}
#endif
