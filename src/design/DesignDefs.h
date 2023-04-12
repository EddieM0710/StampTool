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
 **************************************************/

#ifndef DesignDefs_H
#define DesignDefs_H

#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/gdicmn.h>
#include <wx/font.h>

namespace Design {

    class DesignData;
    class LayoutBase;
    class AlbumBase;
    class Album;
    class FontList;

    Album* GetAlbum( void );
    // FontList* GetFontList( void );

    DesignData* GetDesignData( void );

    //DesignData* GetDesignData( DesignData* designData );

    //DesignData* NewDesignData( void );

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

    bool IsAlbumBaseTypeValid( AlbumBaseType type );

    extern wxString AlbumBaseNames[ AT_NbrAlbumTypes ];

    typedef enum
    {
        AT_Name = 0,
        AT_PageWidth,
        AT_PageHeight,
        AT_TopMargin,
        AT_BottomMargin,
        AT_RightMargin,
        AT_LeftMargin,
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
        AT_ShowCatNbr,
        AT_ShowFrame,
        AT_ShowImage,
        AT_GrayScaleImages,
        AT_TopContentPadding,
        AT_BottomContentPadding,
        AT_LeftContentPadding,
        AT_RightContentPadding,
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
        AT_NbrAttrTypes,
        AT_NOTYPE
    } AlbumAttrType;

    extern wxString AttrNameStrings[ AT_NbrAttrTypes ];


    AlbumAttrType FindAlbumAttrType( wxString name );

    typedef enum
    {
        AT_OK = 0,
        AT_WARING,
        AT_FATAL
    } NodeStatus;

    AlbumBaseType FindAlbumBaseType( wxString name );
    typedef enum
    {
        DD_Display,
        DD_PDF
    } ScaleClient;


    /**
     * @brief Performs the initial instantiantion of all the sTart up data.
     *
     **************************************************/
    void InitDesignDefs( ScaleClient client = DD_Display );

    LayoutBase* GetSelectedNodePage( );

    AlbumBase* MakeNode( wxXmlNode* node );

    // Conversion factor to convert from Pixels to MM. 
    // Screen units are in pixels. Album Design elements are in mm.
    extern wxRealPoint  ScaleFactor;


    const static int UnknownFontVal = -1;

    typedef enum {
        AT_UnspecifiedFontType,
        AT_TextFontType,
        AT_TitleFontType,
        AT_NbrFontType,
        AT_NameFontType,
        AT_NbrFontUsageTypes
    } AT_FontUsageType;

    extern int AT_DefaultPointSize[ AT_NbrFontUsageTypes ];
    extern wxString AT_FontUsageTypeStrings[ AT_NbrFontUsageTypes ];

    AT_FontUsageType FindFontUsageType( wxString name );

    typedef enum {
        AT_Default,
        AT_Decorative,
        AT_Roman,
        AT_Script,
        AT_Swiss,
        AT_Modern,
        AT_Teletype,
        AT_NbrFontFamilies
    }AT_FontFamilyType;

    bool IsOK( AT_FontFamilyType type );
    extern wxFontFamily AT_FontFamilyMap[ AT_NbrFontFamilies ];
    extern wxString AT_FontFamilyStrings[ AT_NbrFontFamilies ];
    AT_FontFamilyType GetATFamily( wxFontFamily wxVal );
    AT_FontFamilyType GetFamilyFromStr( wxString family );


    typedef enum {
        AT_Unknown = -1,
        AT_Normal,
        AT_Italic,
        AT_Slant,
        AT_Max,
        AT_NbrFontStyles
    } AT_FontStyleType;

    bool IsOK( AT_FontStyleType type );
    extern wxFontStyle AT_FontStyleMap[ AT_NbrFontStyles ];
    extern wxString AT_FontStyleStrings[ AT_NbrFontStyles ];
    AT_FontStyleType GetATStyle( wxFontStyle wxVal );

    typedef enum {
        AT_InvalidWeight,
        AT_ThinWeight,
        AT_ExtraLightWeight,
        AT_LightWeight,
        AT_NormalWeight,
        AT_MediumWeight,
        AT_SemiBoldWeight,
        AT_BoldWeight,
        AT_ExtraBoldWeight,
        AT_HeavyWeight,
        AT_ExtraHeavyWeight,
        AT_NbrFontWeights
    }AT_FontWeightType;

    bool IsOK( AT_FontWeightType type );
    extern wxFontWeight AT_FontWeightMap[ AT_NbrFontWeights ];
    extern wxString AT_FontWeightStrings[ AT_NbrFontWeights ];
    AT_FontWeightType GetATWeight( wxFontWeight wxVal );

    typedef enum
    {
        AT_TitleLocationTop,
        AT_TitleLocationBottom,
        AT_TitleLocationLeft,
        AT_TitleLocationRight,
        AT_TitleLocationDefault
    } TitleLocation;

    typedef enum
    {
        AT_AlignTop,
        AT_AlignBottom,
        AT_AlignLeft,
        AT_AlignRight,
        AT_Center,
        AT_AlignDefault
    } StampAlignment;

}

#endif
