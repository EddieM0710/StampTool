/**
 * @file layout/Album.h
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

#ifndef Album_H
#define Album_H
#include <wx/font.h>

#include "design/AlbumBase.h"
#include "design/DesignDefs.h"
 //#include "utils/Project.h"
#include "utils/FontNdx.h"
#include <wx/pdfdc.h>


namespace Design {

    /**
     * @brief Album layout object; inherits from LayoutBase.
     *
     */
    class Album : public AlbumBase
    {

    public:


        ///  @brief Construct a new Album object. The top layout LayoutBase
        /// for holding all the objecs within the album
        Album( wxXmlNode* node ) : AlbumBase( node )
        {
            SetNodeType( AT_Album );
            SetAttrStr( Design::AT_Orientation, OrientationStrings[ Design::AT_Portrait ] );
        };

        ///  @brief Destroy the Album object
        ~Album( ) { };

        ///  @brief 
        ///  
        ///  @return wxString 
        wxString DrawPDF( );

        void DumpFont( wxString Level );

        ///  @brief 
        ///  
        void DumpLayout( );

        ///  @brief Get the Border Size object
        ///  
        ///  @return double 
        double GetBorderSize( );

        ///  @brief Get the Border Size Str object
        ///  
        ///  @return wxString 
        wxString GetBorderSizeStr( );

        ///  @brief Set the Border Size object
        ///  
        ///  @param str 
        void SetBorderSize( wxString str );

        //void SetBorderFilename( wxString str );

        ///  @brief Get the Border File Name object
        ///  
        ///  @return wxString 
        wxString GetBorderFileName( );

        void SetBorderFilename( wxString filename );

        ///  @brief Get the Bottom Margin object
        ///  
        ///  @return double 
        double GetBottomMargin( );

        ///  @brief Get the Bottom Margin Str object
        ///  
        ///  @return wxString 
        wxString GetBottomMarginStr( );

        wxColour GetColor( FontUsageType fontType );

        ///  @brief Get the Doc Name object
        ///  
        ///  @return wxString 
        wxString GetDocName( );

        wxFont GetFont( FontUsageType fontType );

        int GetFontNdx( FontUsageType fontType );

        ///  @brief Get the Font Ndx Preference object
        ///  
        ///  @param fontType 
        ///  @return int 
        int GetFontNdxPreference( FontUsageType fontType );

        ///  @brief Get the Gray Scale Images object
        ///  
        ///  @return true 
        ///  @return false 
        bool GetGrayScaleImages( ) { return String2Bool( GetAttrStr( AT_GrayScaleImages ) ); };

        ///  @brief Get the Height object
        ///  
        ///  @return double 
        double GetHeight( );

        ///  @brief Get the Left Margin object
        ///  
        ///  @return double 
        double GetLeftMargin( );

        ///  @brief Get the Left Margin Str object
        ///  
        ///  @return wxString 
        wxString GetLeftMarginStr( );

        ///  @brief Get the Page Height object
        ///  
        ///  @return double 
        double GetPageHeight( );

        ///  @brief Get the Page Height Str object
        ///  
        ///  @return wxString 
        wxString GetPageHeightStr( );
        wxString GetPaperHeightStr( );

        ///  @brief Get the Page Parameters object
        ///  
        ///  @param width 
        ///  @param height 
        ///  @param topMargin 
        ///  @param bottomMargin 
        ///  @param rightMargin 
        ///  @param leftMargin 
        void GetPageParameters( wxString& width, wxString& height, wxString& topMargin,
            wxString& bottomMargin, wxString& rightMargin, wxString& leftMargin );

        ///  @brief Get the Page Width object
        ///  
        ///  @return double 
        double GetPageWidth( );

        ///  @brief Get the Paper Width for oversize paper
        ///  
        ///  @return double 
        double GetPaperWidth( );

        wxString GetPaperWidthStr( );

        ///  @brief Get the Paper Height for oversize paper
        ///  
        ///  @return double 
        double GetPaperHeight( );

        ///  @brief Get the Page Width Str object
        ///  
        ///  @return wxString 
        wxString GetPageWidthStr( );

        ///  @brief Get the Right Margin object
        ///  
        ///  @return double 
        double GetRightMargin( );

        ///  @brief Get the Right Margin Str object
        ///  
        ///  @return wxString 
        wxString GetRightMarginStr( );

        ///  @brief Get the Show Nbr object
        ///  
        ///  @return true 
        ///  @return false 
        bool GetShowNbr( ) { return String2Bool( GetAttrStr( AT_CatNbr ) ); };

        ///  @brief Get the Top Margin object
        ///  
        ///  @return double 
        double GetTopMargin( );

        ///  @brief Get the Top Margin Str object
        ///  
        ///  @return wxString 
        wxString GetTopMarginStr( );

        ///  @brief Get the Show Title object
        ///  
        ///  @return true 
        ///  @return false 
        bool GetShowTitle( ) { return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        bool GetOverSizePaper( ) { return String2Bool( GetAttrStr( AT_OverSizePaper ) ); };

        ///  @brief Get the Width object
         ///  
         ///  @return double 
        double GetWidth( );

        ///  @brief 
        ///  
        ///  @param fontType 
        ///  @param ndx 
        ///  @return true 
        ///  @return false 
        bool IsDefaultFont( FontUsageType fontType, int ndx );

        ///  @brief 
        ///  
        ///  @param node 
        void LoadFonts( wxXmlNode* node );

        ///  @brief 
        ///  
        void MakeAlbum( );

        /// @brief resets the Font to the default Font
        void MakeDefaultFont( FontUsageType fontType ) { DefaultFonts[ fontType ].MakeDefault( ); };

        ///  @brief 
        ///  
        void MakePDFAlbum( );

        ///  @brief 
        ///  
        ///  @param xmlNode 
        void Save( wxXmlNode* xmlNode );

        void SaveFonts( wxXmlNode* parent );

        ///  @brief Set the Bottom Margin object
        ///  
        ///  @param str 
        void SetBottomMargin( wxString str );

        ///  @brief Set the Doc Name object
        ///  
        ///  @param str 
        void SetDocName( wxString str );

        void SetFont( FontUsageType fontType, wxFont font, wxColour color );

        void SetFontNdx( FontUsageType fontType, int ndx );

        ///  @brief Set the Gray Scale Images object
        ///  
        ///  @param val 
        void SetGrayScaleImages( bool val = true ) { SetAttrStr( AT_GrayScaleImages, Bool2String( val ) ); };

        ///  @brief Set the Left Margin object
        ///  
        ///  @param str 
        void SetLeftMargin( wxString str );

        ///  @brief Set the Page Height object
        ///  
        ///  @param str 
        void SetPageHeight( wxString str );

        ///  @brief Set the Page Width object
        ///  
        ///  @param str 
        void SetPageWidth( wxString str );

        void SetPaperHeight( wxString str );

        void SetPaperWidth( wxString str );

        ///  @brief Set the Right Margin object
        ///  
        ///  @param str 
        void SetRightMargin( wxString str );

        ///  @brief Set the Top Margin object
        ///  
        ///  @param str 
        void SetTopMargin( wxString str );

        ///  @brief Set the Show Title object
        ///  
        ///  @param val 
        void SetShowTitle( bool val ) { SetAttrStr( AT_ShowTitle, Bool2String( val ) ); };

        void SetOverSizePaper( bool val ) { SetAttrStr( AT_OverSizePaper, Bool2String( val ) ); };

        ///  @brief Set the Show Nbr object
        ///  
        ///  @param val 
        void SetShowNbr( bool val ) { SetAttrStr( AT_CatNbr, Bool2String( val ) ); };

        /**
         * @brief init drills down to the lowest layout object with an actual size
         * and begins calculating the min size of its parents as it progresses
         * back up the heirarchy.
         * @return true
         * @return false
         */
        bool UpdateMinimumSize( );

        /**
         * @brief  Does the layout for each child. Goes to the bottom
         * of each child container object ( row, column, page )
         * and begin filling in position relative to the parent
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


        wxString GetDefaultValStr( AlbumAttrType type )
        {
            if ( type == AT_SelvageHeight )
            {
                return  wxString::Format( "%4.1f", m_defaultSelvageHeight );
            }
            else if ( type == AT_SelvageWidth )
            {
                return   wxString::Format( "%4.1f", m_defaultSelvageWidth );
            }
            else if ( type == AT_MountAllowanceHeight )
            {
                return   wxString::Format( "%4.1f", m_defaultMountAllowanceHeight );
            }
            else if ( type == AT_MountAllowanceWidth )
            {
                return   wxString::Format( "%4.1f", m_defaultMountAllowanceWidth );
            }
            else
                return "";
        };

        double GetDefaultVal( AlbumAttrType type )
        {
            if ( type == AT_SelvageHeight )
            {
                return m_defaultSelvageHeight;
            }
            else if ( type == AT_SelvageWidth )
            {
                return m_defaultSelvageWidth;
            }
            else if ( type == AT_MountAllowanceHeight )
            {
                return m_defaultMountAllowanceHeight;
            }
            else if ( type == AT_MountAllowanceWidth )
            {
                return m_defaultMountAllowanceWidth;
            }
            return 0;
        };
        wxString GetDefaultOrientation( ) { return GetAttrStr( Design::AT_Orientation ); };
        void SetDefaultOrientation( wxString orientation )
        {
            SetAttrStr( Design::AT_Orientation, orientation );
        };
        bool IsDefaultOrientation( wxString orientation )
        {
            return ( !orientation.Cmp( GetAttrStr( Design::AT_Orientation ) ) );
        };

    private:

        Utils::FontNdx DefaultFonts[ AT_NbrFontUsageTypes ];

        const double m_defaultSelvageHeight = 0;
        const double m_defaultSelvageWidth = 0;
        const double m_defaultMountAllowanceHeight = 5;
        const double m_defaultMountAllowanceWidth = 4;
        //  PageOrientation m_defaultOrientation;

    };
}
#endif