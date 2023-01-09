/**
 * @file layout/LayoutBase.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 * This file is part of AlbumGenerator.
 *
 * AlbumGenerator is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#ifndef LayoutBase_h
#define LayoutBase_h

#include <wx/string.h>

#include "Defs.h"
#include "design/AlbumBase.h"
#include "design/Frame.h"
#include "utils/XMLUtilities.h"

#include <wx/xml/xml.h>

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
            SetTopContentPadding( 1.5 );
            SetBottomContentPadding( 1.5 );
            SetLeftContentPadding( 1.5 );
            SetRightContentPadding( 1.5 );

        };

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         **************************************************/
        LayoutBase( wxXmlNode* node ): AlbumBase( node ) {
            SetTopContentPadding( 4 );
            SetBottomContentPadding( 4 );
            SetLeftContentPadding( 4 );
            SetRightContentPadding( 4 );
        };

        /*
         * @brief Write the object data to the ODT file.
         *
         * @param parent object to contain this object
         * @return wxXmlNode*  the node of the object that can contain othr objects
         */
        virtual wxXmlNode* Write( wxXmlNode* parent ) = 0;

        /*
         * @brief Draw object on screen
         *
         * @param dc current device context
         * @param x position in MM
         * @param y position in MM
         */
        virtual void draw( wxDC& dc, double x, double y ) = 0;
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

        wxString GetTitle( ) { return m_title; };

        /*
         * @brief  Set Layout element title
         *
         * @param val wxString
         */
        void SetTitle( wxString title ) { m_title = title; };

        /*
         * @brief Get Layout element title
         *
         * @return double - width in MM
         */
        double GetTitleHeight( ) { return m_titleSize.y; };

        /*
         * @brief  Set Layout element position
         *
         * @param val double - position in MM
         */
        double GetTitleWidth( ) { return m_titleSize.x; };


        bool GetShowTitle( ) { return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ) { SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };

        bool GetShowFrame( ) { return String2Bool( GetAttrStr( AT_ShowFrame ) ); };
        void SetShowFrame( bool val ) { SetAttrStr( AT_ShowFrame, Bool2String( val ) ); };

        //        bool GetShowImage(){ return String2Bool( GetAttrStr( AT_ShowImage ) ); };
        //        void SetShowImage( bool val ){ SetAttrStr( AT_ShowImage, Bool2String( val ) ); };

        bool GetShowCatNbr( ) { return String2Bool( GetAttrStr( AT_ShowCatNbr ) ); };
        void SetShowCatNbr( bool val ) { SetAttrStr( AT_ShowCatNbr, Bool2String( val ) ); };


        double GetTopContentPadding( ) { GetAttrDbl( AT_TopContentPadding ); };
        void SetTopContentPadding( double val ) { SetAttrDbl( AT_TopContentPadding, val ); };

        double GetBottomContentPadding( ) { GetAttrDbl( AT_BottomContentPadding ); };
        void SetBottomContentPadding( double val ) { SetAttrDbl( AT_BottomContentPadding, val ); };

        double GetLeftContentPadding( ) { GetAttrDbl( AT_LeftContentPadding ); };
        void SetLeftContentPadding( double val ) { SetAttrDbl( AT_LeftContentPadding, val ); };

        double GetRightContentPadding( ) { GetAttrDbl( AT_RightContentPadding ); };
        void SetRightContentPadding( double val ) { SetAttrDbl( AT_RightContentPadding, val ); };

        void ValidateChildType( int& nbrRows, int& nbrCols, int& nbrStamps );
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
         * @brief Calculate the size in MM necessary for the title
         *
         * @param width the max width of the title
         * @param font font to be used for writing
         */
        void UpdateTitleSize( double width, wxFont* font );

        //void WriteFrame( wxString loc, wxString name, wxString id, Frame* frame );
        void DumpLayout( double x, double y );

        wxXmlNode* GetTitleFont( wxXmlNode* node, wxString name )
        {
            wxTreeItemId ctrlID = GetTreeItemId( );
            //    GetDesignTreeCtrl()->GetItemData( ctrlID );
        }

        void ReportLayoutFrame( wxString indent = "" );

        //wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name );
  
       void DumpObjectLayout(  wxString indent = "" );
       LayoutBase* FindObjectByPos(  double x, double y, wxString indent = "" );

        //void SetClientDimensions( Frame *frame );

        void SetClientDimensions( wxDC &dc, double x, double y, double width = 0.0, double height= 0.0, double minWidth = 0.0, double minHeight= 0.0 );

        bool IsInClient(  double x, double y, wxString indent = "");

    protected:
        Frame m_frame;
        Frame m_clientDimensions;
        wxString m_title;
        RealSize m_titleSize;

    };
}
#endif
