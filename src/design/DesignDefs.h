/**
 * @file DesignDefs.h
 * @author Eddie Monroe ( )
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright ( c ) 2021
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

#ifndef DesignDefs_H
#define DesignDefs_H

#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/gdicmn.h>
#include <wx/font.h>


namespace Design {

    class AlbumVolume;
    class LayoutBase;
    class AlbumBase;
    class Album;
    class FontList;

    typedef enum
    {
        AT_Name = 0,
        AT_PageWidth,
        AT_PageHeight,
        AT_TopPageMargin,
        AT_BottomPageMargin,
        AT_RightPageMargin,
        AT_LeftPageMargin,
        AT_BorderFileName,
        AT_BorderSize,
        AT_Height,
        AT_Width,
        AT_XPos,
        AT_YPos,
        AT_MinHeight,
        AT_MinWidth,
        AT_CatNbr,
        AT_Link,
        AT_ShowTitle,
        AT_ShowSubTitle,
        AT_ShowCatNbr,
        AT_ShowFrame,
        AT_ShowImage,
        AT_Orientation,
        AT_GrayScaleImages,
        AT_TopContentMargin,
        AT_BottomContentMargin,
        AT_LeftContentMargin,
        AT_RightContentMargin,
        AT_FontType,
        //        AT_FontName, 
        //        AT_FontFamily, 
        AT_NativeFontString,
        //        AT_FontSize, 
        //        AT_FontWeight, 
        AT_FontColor,
        //        AT_FontStyle, 
        AT_ImageName,
        AT_CalculateSpacing,
        AT_FixedSpacingSize,
        AT_OverSizePaper,
        AT_PaperHeight,
        AT_PaperWidth,
        AT_SelvageHeight,
        AT_SelvageWidth,
        AT_SubTitle,
        AT_MountAllowanceHeight,
        AT_MountAllowanceWidth,
        AT_StampNameLocation,
        AT_StampMargin,
        AT_CollapseState,
        AT_Catalog,
        AT_Catalog_Codes,
        AT_NbrAttrTypes,
        AT_NOTYPE
    } AlbumAttrType;
    typedef enum
    {
        AT_Portrait = 0,
        AT_Landscape
    } PageOrientation;

    typedef enum
    {
        AT_Album = 0,
        AT_Page,
        AT_Row,
        AT_Col,
        AT_Text,
        AT_Title,
        AT_TitlePage,
        AT_Stamp,
        AT_Font,
        AT_NbrAlbumTypes,
        AT_None = 999
    } AlbumBaseType;

    typedef enum {
        AT_TitleFontType,
        AT_SubTitleFontType,
        AT_NameFontType,
        AT_TextFontType,
        AT_NbrFontType,
        AT_NbrFontUsageTypes
    } FontUsageType;

    typedef enum
    {
        AT_OK = 0,
        AT_WARNING,
        AT_FATAL
    } NodeStatus;

    typedef enum
    {
        DD_Display,
        DD_PDF
    } ScaleClient;

    typedef enum
    {
        AT_AlignTop,
        AT_AlignBottom,
        AT_AlignLeft,
        AT_AlignRight,
        AT_Center,
        AT_AlignDefault
    } StampAlignment;

    typedef enum
    {
        AT_TitleLocationTop,
        AT_TitleLocationBottom,
        AT_TitleLocationDefault,
        AT_NbrTitleLocations
    } TitleLocation;

    Album* GetAlbum( void );

    AlbumVolume* GetAlbumVolume( void );

    bool IsAlbumBaseTypeValid( AlbumBaseType type );

    TitleLocation FindTitleLocationType( wxString name );

    AlbumAttrType FindAlbumAttrType( wxString name );

    AlbumBaseType FindAlbumBaseType( wxString name );

    FontUsageType FindFontUsageType( wxString name );

    LayoutBase* GetSelectedNodePage( );

    /**
     * @brief Performs the initial instantiantion of all the sTart up data.
     *
     */
    void InitDesignDefs( ScaleClient client = DD_Display );

    AlbumBase* MakeNode( wxXmlNode* node );

    const static int UnknownFontVal = -1;

    // Conversion factor to convert from Pixels to MM. 
    // Screen units are in pixels. Album Design elements are in mm.
    extern wxRealPoint  DeviceUnitsPerMM;

    extern wxString AlbumBaseNames[ AT_NbrAlbumTypes ];

    extern wxString OrientationStrings[ 2 ];

    bool IsPortrait( wxString orientation );

    extern wxString AttrNameStrings[ AT_NbrAttrTypes ];

    extern int DefaultPointSize[ AT_NbrFontUsageTypes ];
    extern wxString FontUsageTypeStrings[ AT_NbrFontUsageTypes ];
    extern wxString StampTitleLocationStrings[ AT_NbrTitleLocations ];

}

#endif
