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
    /// The m_actualStampFrame is not visible contains the actual parameters of the physical stamp.
    /// The m_stampImageFrame and the m_nbrFrame is embedded in the m_borderFrame and is the image of the object.
    /// The LayoutBase for this object contains the frame parameters for the stamp Album object.
    ///  These parameters are all in MM.
    class Stamp : public LayoutBase
    {
    public:

        Stamp( wxXmlNode* node );

        Stamp( );

        ~Stamp( ) { };


        // ( AT_GrayScaleImages,
        //     ( AT_TopContentMargin,
        //         ( AT_BottomContentMargin,
        //             ( AT_LeftContentMargin,
        //                 ( AT_RightContentMargin,




        void CalculateYPos( double yPos, double height );

        void Draw( wxDC& dc, double x, double y );

        void DrawRotated( wxDC& dc, double x, double y );

        void DrawPDF( wxPdfDocument* doc, double x, double y );

        Design::Frame* GetBorderFrame( ){

            return &m_borderFrame;
        }

        // wxString GetStampAttributeStr( Design::AlbumAttrType type );

        // double GetStampAttributeDbl( Design::AlbumAttrType type );

        // bool GetStampAttributeBool( Design::AlbumAttrType type );

        wxString GetCatalogNbr( );

        wxString GetCatalog( ) {
            return GetAlbumAttributeStr( Design::AT_Catalog );
        };

        wxString GetCatalogCodes( );

        StampNamePosType  GetDefaultStampNamePosition( );

        wxImage GetImage( );

        double GetMountAllowanceHeight( ){
            return GetAlbumAttributeDbl( Design::AT_MountAllowanceHeight );
        };

        wxString GetMountAllowanceHeightStr( ){
            return GetAlbumAttributeStr( Design::AT_MountAllowanceHeight );
        };

        double GetMountAllowanceWidth( ){
            return GetAlbumAttributeDbl( Design::AT_MountAllowanceWidth );
        };

        wxString GetMountAllowanceWidthStr( ){
            return GetAlbumAttributeStr( Design::AT_MountAllowanceWidth );
        };

        LabelFrame* GetNameFrame( );

        wxString GetNameString( );

        LabelFrame* GetNbrFrame( );

        wxString GetNbrString( );

        double GetSelvageHeight( )
        {
            return GetAlbumAttributeDbl( Design::AT_SelvageWidth );
        };

        wxString GetSelvageHeightStr( )
        {
            return GetAlbumAttributeStr( Design::AT_SelvageWidth );
        };

        double GetSelvageWidth( )
        {
            return  GetAlbumAttributeDbl( Design::AT_SelvageWidth );
        };

        wxString GetSelvageWidthStr( )
        {
            return GetAlbumAttributeStr( Design::AT_SelvageWidth );
        };

        bool GetShowNbr( )
        {
            return GetAlbumAttributeBool( AT_ShowCatNbr, true );

        };

        bool GetShowTitle( ) {
            return GetAlbumAttributeBool( AT_ShowTitle, true );
        };

        bool GetGrayScaleImages( ) {
            return GetAlbumAttributeBool( AT_GrayScaleImages, false );
        };

        // bool GetShowSubTitle( ) {
        //     return String2Bool( GetAttrStr( AT_ShowSubTitle ) );
        // };

        double GetActualStampHeight( ) {
            return m_actualStampFrame.GetHeight( );
        };

        wxString GetActualStampHeightStr( ) {
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

        double GetActualStampWidth( );

        wxString GetActualStampWidthStr( );

        wxString GetStampNamePosition( );

        StampNamePosType  GetStampNamePositionType( );

        void InitParameters( );

        bool IsDefaultVal( AlbumAttrType type );

        bool IsDefaultVal( AlbumAttrType type, wxString val );

        void LoadFonts( wxXmlNode* node );

        void ReportLayout( );

        wxImage  RescaleImage( );

        void Save( wxXmlNode* xmlNode );

        // void SetStampAttributeStr( Design::AlbumAttrType type, wxString val );
        // void SetStampAttributeDbl( Design::AlbumAttrType type, double val );
        // void SetStampAttributeBool( Design::AlbumAttrType type, bool val );

        void SetShowTitle( bool val ) {
            SetAlbumAttributeBool( AT_ShowTitle, val );
        };

        void SetGrayScaleImages( bool val ) {
            SetAlbumAttributeBool( AT_GrayScaleImages, val );
        };

        void SetShowSubTitle( bool val ) { };
        bool GetShowSubTitle( ){
            return false;
        };

        void SetStampMarginStr( wxString str ) {
            return SetAlbumAttributeStr( Design::AT_StampMargin, str );
        };

        void SetStampMargin( double val ) {
            return SetAlbumAttributeDbl( Design::AT_StampMargin, val );
        };

        void SetStampImageFilename( wxString filename );

        void SaveFonts( wxXmlNode* parent );

        void SetCatalog( wxString cat );

        void SetCatalogCodes( wxString catCodes );

        void SetMountAllowanceHeight( double val ){
            SetAlbumAttributeDbl( Design::AT_MountAllowanceHeight, val );
        }

        void SetMountAllowanceHeight( wxString val ){
            SetAlbumAttributeStr( Design::AT_MountAllowanceHeight, val );
        };
        void SetMountAllowanceWidth( double val ){
            SetAlbumAttributeDbl( Design::AT_MountAllowanceWidth, val );
        }
        void SetMountAllowanceWidth( wxString val ){
            SetAlbumAttributeStr( Design::AT_MountAllowanceWidth, val );
        };
        void SetNbrString( wxString str );

        void SetNameString( wxString str );

        void SetSelvageHeight( double val )  {
            SetAlbumAttributeDbl( Design::AT_SelvageHeight, val );
        };

        void SetSelvageHeight( wxString str ){
            SetAlbumAttributeStr( Design::AT_SelvageHeight, str );
        };

        void SetSelvageWidth( double val ) {
            SetAlbumAttributeDbl( Design::AT_SelvageWidth, val );
        };

        void SetSelvageWidth( wxString val )  {
            SetAlbumAttributeStr( Design::AT_SelvageWidth, val );
        };

        void SetShowNbr( bool val ) {
            SetAlbumAttributeBool( AT_ShowCatNbr, val );
        };

        void SetActualStampHeight( double val );

        void SetActualStampHeight( wxString str );

        void SetActualStampWidth( double val );

        void SetActualStampWidth( wxString str );

        wxString MakeDisplayNbr( );

        void SetStampNamePosition( StampNamePosType loc );

        void SetFixedParms( );

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

        /// @brief  The m_actualStampFrame has the parameters of the actual Stamp.
        /// the m_actualStampFrame is never actually drawn but all the other parts of this object 
        /// are based on this frame. If these parameters are not set then things go very bad.
        Frame m_actualStampFrame;

        /// @brief  The m_stampImageFrame has the parameters for the printed album image. 
        // It is 10% smaller than the actual stamp.
        Frame m_stampImageFrame;


        LabelFrame* m_nameFrame;
        LabelFrame* m_nbrFrame;

        wxString m_imageFilename;
        wxImage m_image;
        // DebugString m_debugString;
    };
}
#endif