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

        // double GetPageAttributeDbl( Design::AlbumAttrType type );

        // wxString GetPageAttributeStr( Design::AlbumAttrType type );

        // bool GetPageAttributeBool( Design::AlbumAttrType type, bool defVal = false );

        // void SetPageAttributeBool( Design::AlbumAttrType type, bool val );

        // void SetPageAttributeDbl( Design::AlbumAttrType type, double val );

        // void SetPageAttributeStr( Design::AlbumAttrType type, wxString val );

        // bool IsDefaultVal( AlbumAttrType type );

        // bool IsDefaultVal( AlbumAttrType type, wxString val );

        // Draw object on screen; position in MM
        void Draw( wxDC& dc, double x, double y );

        // Draw object in pdf; position in MM
        void DrawPDF( wxPdfDocument* doc, double x, double y );

        wxString GetBorderFileName( ) {
            return GetAlbumAttributeStr( Design::AT_BorderFileName );
        };

        // Get the Bottom PageMargin 
        double GetBottomPageMargin( ) {
            return GetAlbumAttributeDbl( Design::AT_BottomPageMargin );
        };

        wxString GetBottomPageMarginStr( ) {
            return GetAlbumAttributeStr( Design::AT_BottomPageMargin );
        };


        // Get the Border Size 
        double GetBorderSize( ) {
            return GetAlbumAttributeDbl( Design::AT_BorderSize );
        };

        wxString GetLeftPageMarginStr( ) {
            return GetAlbumAttributeStr( Design::AT_LeftPageMargin );
        };


        // Get the Left PageMargin 
        double GetLeftPageMargin( ) {
            return  GetAlbumAttributeDbl( Design::AT_LeftPageMargin );
        };

        //Get the Right PageMargin
        double GetRightPageMargin( ) {
            return GetAlbumAttributeDbl( Design::AT_RightPageMargin );
        };

        wxString GetRightPageMarginStr( ) {
            return GetAlbumAttributeStr( Design::AT_RightPageMargin );
        };

        double GetPageWidth( ) {
            return GetAlbumAttributeDbl( Design::AT_PageWidth );
        };

        double GetPageHeight( ) {
            return GetAlbumAttributeDbl( Design::AT_PageHeight );
        };



        TitleFrame* GetTitleFrame( );

        wxString GetTitleString( );
        wxString GetSubTitleString( );


        // Get the Top PageMargin 
        double GetTopPageMargin( ) {
            return GetAlbumAttributeDbl( Design::AT_TopPageMargin );
        };

        wxString GetTopPageMarginStr( ) {
            return GetAlbumAttributeStr( Design::AT_TopPageMargin );
        };

        void ReportLayout( );

        void Save( wxXmlNode* parent );

        void SaveFonts( wxXmlNode* parent );

        // Set the Border Size 
        void SetBorderSize( double val ) {
            SetAlbumAttributeDbl( Design::AT_BorderSize, val );
        };

        void SetBorderSize( wxString val ) {
            SetAlbumAttributeStr( Design::AT_BorderSize, val );
        };

        void SetBorderFilename( wxString str ) {
            SetAlbumAttributeStr( Design::AT_BorderFileName, str );
        };

        // Set the Bottom PageMargin 
        void SetBottomPageMargin( double val ) {
            SetAlbumAttributeDbl( Design::AT_BottomPageMargin, val );
        };

        // content Frame is space within the page border.
        // From the page layout edge takes into account page margin and border
        void SetContentFrame( );

        // Set the Left PageMargin 
        void SetLeftPageMargin( double val ) {
            SetAlbumAttributeDbl( Design::AT_LeftPageMargin, val );
        };

        // Set the Right PageMargin 
        void SetRightPageMargin( double val ) {
            SetAlbumAttributeDbl( Design::AT_RightPageMargin, val );
        };

        void SetTitleString( wxString str );
        void  SetSubTitleString( wxString str );
        // Set the Top PageMargin 
        void SetTopPageMargin( double val ) {
            SetAlbumAttributeDbl( Design::AT_TopPageMargin, val );
        };

        bool GetShowTitle( ) {
            return GetAlbumAttributeBool( Design::AT_ShowTitle );
        };

        bool GetShowBorder( ) {
            return GetAlbumAttributeBool( Design::AT_ShowBorder, true );
        };

        bool GetShowSubTitle( ) {
            return GetAlbumAttributeBool( Design::AT_ShowSubTitle );
        };

        void SetShowNbr( bool val ){};

        bool GetShowNbr( ) {
            return false;
        };

        void SetShowTitle( bool val ) {
            SetAlbumAttributeBool( Design::AT_ShowTitle, val );
        };

        void SetShowBorder( bool val ) {
            if ( IsDefaultVal( Design::AT_ShowBorder, Bool2String( val ) ) )
            {
                DeleteAttribute( Design::AT_ShowBorder );
            }
            else
            {
                SetAlbumAttributeBool( Design::AT_ShowBorder, val );
            }
            if ( val )
            {
                DeleteAttribute( Design::AT_BorderSize );
            }
            else
            {
                SetAlbumAttributeDbl( Design::AT_BorderSize, 0.0 );
            }
        };

        void SetShowSubTitle( bool val ) {
            SetAlbumAttributeBool( AT_ShowSubTitle, val );
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
            return GetAlbumAttributeStr( Design::AT_Orientation );
        };

        void Orientation( wxString orientation )
        {
            SetAlbumAttributeStr( AT_Orientation, orientation );
            Init( );
        };

        bool IsOrientation( ) {
            return ( ( PageDefaults* ) GetDefaults( ) )->IsOrientation( Orientation( ) );
        };
    private:


        Design::PageType m_pageType;

        // Content Frame is space within the page border.
        // From the page layout edge takes into account page margin and border
        Frame m_contentFrame;


        DebugString m_debugString;
        TitleFrame* m_titleFrame;
        //        PageOrientation m_orientation;
    };
}
#endif