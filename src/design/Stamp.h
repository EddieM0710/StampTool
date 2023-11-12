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

        Stamp( wxXmlNode* node );

        Stamp( );

        ~Stamp( ) { };

        void CalculateYPos( double yPos, double height );

        void Draw( wxDC& dc, double x, double y );

        void DrawRotated( wxDC& dc, double x, double y );

        void DrawPDF( wxPdfDocument* doc, double x, double y );

        void DumpStamp( wxTextCtrl* positionTextCtrl );

        wxString GetCatalogNbr( );

        wxString GetCatalog( );

        wxString GetCatalogCodes( );

        TitleLocation  GetDefaultTitleLocation( );

        wxImage GetImage( );

        double GetMountAllowanceHeight( );

        wxString GetMountAllowanceHeightStr( );

        double GetMountAllowanceWidth( );

        wxString GetMountAllowanceWidthStr( );

        LabelFrame* GetNameFrame( );

        wxString GetNameString( );

        LabelFrame* GetNbrFrame( );

        wxString GetNbrString( );

        double GetSelvageHeight( );

        wxString GetSelvageHeightStr( );

        double GetSelvageWidth( );

        wxString GetSelvageWidthStr( );

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

        bool GetShowTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowTitle ) );
        };

        bool GetShowSubTitle( ) {
            return String2Bool( GetAttrStr( AT_ShowSubTitle ) );
        };

        double GetStampHeight( ) {
            return m_stampFrame.GetHeight( );
        };

        wxString GetStampHeightStr( ) {
            return GetAttrStr( Design::AT_Height );
        };

        wxString GetStampImageFilename( );

        // The stamp object Margin is the Margin added to the border frame 
         // for positioning the frame and title within.
        wxString GetStampMarginStr( ) {
            return GetAttrStr( Design::AT_StampMargin );
        };

        double GetStampMargin( ) {
            return GetAttrDbl( Design::AT_StampMargin );
        };

        double GetStampWidth( );

        wxString GetStampWidthStr( );

        TitleLocation  GetTitleLocation( );

        void InitParameters( );

        bool IsDefaultVal( AlbumAttrType type );

        void LoadFonts( wxXmlNode* node );

        void ReportLayout( );

        wxImage  RescaleImage( );

        void Save( wxXmlNode* xmlNode );

        void SetShowTitle( bool val ) {
            SetAttrStr( AT_ShowTitle, Bool2String( val ) );
        };

        void SetShowSubTitle( bool val ) {
            SetAttrStr( AT_ShowSubTitle, Bool2String( val ) );
        };

        void SetStampMarginStr( wxString str ) {
            return SetAttrStr( Design::AT_StampMargin, str );
        };

        void SetStampMargin( double val ) {
            return SetAttrDbl( Design::AT_StampMargin, val );
        };

        void SetStampImageFilename( wxString filename );

        void SaveFonts( wxXmlNode* parent );

        void SetCatalog( wxString cat );

        void SetCatalogCodes( wxString catCodes );

        void SetMountAllowanceHeight( double val );

        void SetMountAllowanceHeight( wxString val );

        void SetMountAllowanceWidth( double val );

        void SetMountAllowanceWidth( wxString val );

        void SetNbrString( wxString str );

        void SetNameString( wxString str );

        void SetSelvageHeight( double val );

        void SetSelvageHeight( wxString val );

        void SetSelvageWidth( double val );

        void SetSelvageWidth( wxString val );

        void SetShowNbr( bool val ) {
            SetAttrStr( AT_ShowCatNbr, Bool2String( val ) );
        };

        void SetStampHeight( double val );

        void SetStampHeight( wxString str );

        void SetStampWidth( double val );

        void SetStampWidth( wxString str );

        wxString MakeDisplayNbr( );

        void SetTitleLocation( TitleLocation loc );


        /**
         *
        * @brief UpdateMinimumSize
        * Calculates the minimum Height and width of the object. It drills down to
        * the lowest layout object with an actual size and begins calculating the
        * min size of its parents as it progresses back up the heirarchy.
        */
        bool UpdateMinimumSize( );

        void UpdatePositions( );

        void UpdateSizes( );

        NodeStatus ValidateNode( );

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


        LabelFrame* m_nameFrame;
        LabelFrame* m_nbrFrame;

        double m_selvageHeight;
        double m_selvageWidth;
        double m_mountAllowanceHeight;
        double m_mountAllowanceWidth;


        wxString m_imageFilename;
        wxImage m_image;
        // DebugString m_debugString;
    };
}
#endif