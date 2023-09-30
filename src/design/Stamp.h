/**
 * @file Stamp.h
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

#ifndef Layout_Stamp_h
#define Layout_Stamp_h

#include <wx/pdfdocument.h>

#include "design/LayoutBase.h"
#include "design/Album.h"
#include "utils/DebugString.h"


namespace Design {


    // typedef enum {
    //     AT_InvalidImage = 0,
    //     AT_InvalidHeight,
    //     AT_InvalidWidth,
    //     AT_NbrStampErrorTypes
    // }StampErrorType;

    // extern const char* ErrorStrings[ AT_NbrStampErrorTypes ];


    /// @brief  Stamp
    ///
    /// Stamp layout object; Inherits from LayoutBase.
    /// the Object is built up of several subframes objects. The outer object is the LayoutBase frame.
    /// Inside the LayoutBase frame is the m_borderFrame, which has the visible frame
    /// for the layout, and the title text.
    /// The m_stampFrame is not visible contains the actual parameters of the physical stamp.
    /// The m_stampImageFrame and the m_nbrFrame is embedded in the m_borderFrame and is the image of the object.
    /// The LayoutBase for this object contains the frame parameters for the stamp Album object.
    ///  These parameters are all in MM.
    class Stamp : public LayoutBase
    {
    public:

        /**
         * @brief Construct a new Stamp object
         *
         * @param parent
         */
        Stamp( wxXmlNode* node );


        ///  @brief Construct a new Stamp object
        ///  
        Stamp( );


        /**
         * @brief Destroy the Stamp object
         *
         */
        ~Stamp( ) { };

        ///  @brief 
        ///  
        void CalculateYPos( double yPos, double height );

        //        void ClearError( );
        //        void SetError( StampErrorType type, NodeStatus status );
        //        NodeStatus GetStatus( );

        /*
         * @brief Draw object on screen
         *
         * @param dc current device context
         * @param x position in MM from page top
         * @param y position in MM from page left
         */
        void Draw( wxDC& dc, double x, double y );
        void DrawRotated( wxDC& dc, double x, double y );

        ///  @brief 
        ///  
        ///  @param doc 
        ///  @param x 
        ///  @param y 
        void DrawPDF( wxPdfDocument* doc, double x, double y );

        wxImage GetImage( );

        ///  @brief 
        ///  
        ///  @param positionTextCtrl 
        void DumpStamp( wxTextCtrl* positionTextCtrl );

        ///  @brief Get the Name Frame object
        ///  
        ///  @return LabelFrame* 
        LabelFrame* GetNameFrame( );

        ///  @brief Get the Name String object
        ///  
        ///  @return wxString 
        wxString GetNameString( );

        ///  @brief Get the Nbr Frame object
        ///  
        ///  @return LabelFrame* 
        LabelFrame* GetNbrFrame( );

        ///  @brief Get the Nbr String object
        ///  
        ///  @return wxString 
        wxString GetNbrString( );

        wxString GetCatalogNbr( );

        wxString GetCatalog( );

        wxString GetCatalogCodes( );

        ///  @brief Get the Show Nbr object
        ///  
        ///  @return true 
        ///  @return false 
        bool GetShowNbr( )
        {
            wxString catStr = GetAttrStr( AT_ShowCatNbr );
            if ( catStr.IsEmpty( ) )
            {
                return GetAlbum( )->GetShowNbr( );
            }
            else
            {
                return String2Bool( catStr );
            }
        };

        void InitParameters( );

        ///  @brief 
        ///  
        ///  @param node 
        void LoadFonts( wxXmlNode* node );

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

        ///  @brief Set the Show Title object
        ///  
        ///  @param val 
        void SetShowTitle( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };

        void SetShowSubTitle( bool val ) {
            SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        };

        ///  @brief Get the Stamp Height object
        ///  
        ///  @return double 
        double GetStampHeight( ) {
            return m_stampFrame.GetHeight( );
        };

        ///  @brief Get the Stamp Height Str object
        ///  
        ///  @return wxString 
        wxString GetStampHeightStr( ) {
            return GetAttrStr( Design::AT_Height );
        };

        // The stamp object Margin is the Margin added to the border frame 
         // for positioning the frame and title within.
        wxString GetStampMarginStr( ) {
            return GetAttrStr( Design::AT_StampMargin );
        };
        double GetStampMargin( ) {
            return GetAttrDbl( Design::AT_StampMargin );
        };

        void SetStampMarginStr( wxString str ) {
            return SetAttrStr( Design::AT_StampMargin, str );
        };

        void SetStampMargin( double val ) {
            return SetAttrDbl( Design::AT_StampMargin, val );
        };


        ///  @brief Get the Stamp Image Filename object
        ///  
        ///  @return wxString 
        wxString GetStampImageFilename( );

        void SetStampImageFilename( wxString filename );

        ///  @brief Get the Stamp Width object
        ///  
        ///  @return double 
        double GetStampWidth( );

        ///  @brief Get the Stamp Width Str object
        ///  
        ///  @return wxString 
        wxString GetStampWidthStr( );

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

        void SetCatalog( wxString cat );

        void SetCatalogCodes( wxString catCodes );

        ///  @brief Set the Nbr String object
        ///  
        ///  @param str 
        void SetNbrString( wxString str );

        ///  @brief Set the Name String object
        ///  
        ///  @param str 
        void SetNameString( wxString str );

        ///  @brief Set the Show Nbr object
        ///  
        ///  @param val 
        void SetShowNbr( bool val ) {
            SetAttrStr( AT_ShowCatNbr, Bool2String( val ) );
        };

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        void SetStampHeight( double val );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param str 
        void SetStampHeight( wxString str );

        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        void SetStampWidth( double val );

        ///  @brief Set the Stamp Width object
        ///  
        ///  @param str 
        void SetStampWidth( wxString str );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        void SetSelvageHeight( double val );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        void SetSelvageHeight( wxString val );

        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        void SetSelvageWidth( double val );


        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        void SetSelvageWidth( wxString val );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        void SetMountAllowanceHeight( double val );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        void SetMountAllowanceHeight( wxString val );

        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        void SetMountAllowanceWidth( double val );


        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        void SetMountAllowanceWidth( wxString val );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        double GetSelvageHeight( );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        wxString GetSelvageHeightStr( );

        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        double GetSelvageWidth( );


        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        wxString GetSelvageWidthStr( );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        double GetMountAllowanceHeight( );

        ///  @brief Set the Stamp Height object
        ///  
        ///  @param val 
        wxString GetMountAllowanceHeightStr( );

        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        double GetMountAllowanceWidth( );


        ///  @brief Set the Stamp Width object
        ///  
        ///  @param val 
        wxString GetMountAllowanceWidthStr( );

        TitleLocation  GetTitleLocation( );

        wxString MakeDisplayNbr( );

        void SetTitleLocation( TitleLocation loc );
        TitleLocation  GetDefaultTitleLocation( );

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
        ///  @return NodeStatus 
        NodeStatus ValidateNode( );

        bool IsDefaultVal( AlbumAttrType type );
        wxImage  RescaleImage( );
        // wxBitmap BlitResize( wxBitmap& bmpIn, double scale, bool antialiasing );

    private:

        /// @brief The m_borderFrame has the parameters of outline for the stamp/mount in the album. 
        /// It is the actual stamp + selvage + mount allowance.
        Frame m_borderFrame;

        /// @brief  The m_stampFrame has the parameters of the actual Stamp.
        /// the m_stampFrame is never actually drawn but all the other parts of this object 
        /// are based on this frame. If these parameters are not set then things go very bad.
        Frame m_stampFrame;

        /// @brief  The m_stampImageFrame has the parameters for the printed album image. 
        // It is 10% smaller than the actual stamp.
        Frame m_stampImageFrame;

        /// @brief 
        LabelFrame* m_nameFrame;
        LabelFrame* m_nbrFrame;

        double m_selvageHeight;
        double m_selvageWidth;
        double m_mountAllowanceHeight;
        double m_mountAllowanceWidth;

        bool m_showCatNbr;

        bool m_showTitle;
        wxString m_imageFilename;
        wxImage m_image;
        DebugString m_debugString;
    };
}
#endif