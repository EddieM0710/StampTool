/**
 * @file DesignDefs.h
 * @author Eddie Monroe ()
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
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

#ifndef DesignDefs_H
#define DesignDefs_H

#include <wx/string.h>
#include "wx/xml/xml.h"
#include <wx/gdicmn.h>

namespace Design {

    class DesignData;
    class LayoutBase;
    class AlbumBase;
    class Album;
    
    Album* GetAlbum( void );

    DesignData* GetDesignData( void );

    //DesignData* GetDesignData( DesignData* designData );

    //DesignData* NewDesignData( void );

    typedef enum
    {
        AT_Album = 0,
        AT_Page,
        AT_Row,
        AT_Col,
        AT_Title,
        AT_TitlePage,
        AT_Stamp,
        AT_Font,
        AT_NbrAlbumTypes,
        AT_None = 999
    } AlbumBaseType;
 
    bool IsAlbumBaseTypeValid( AlbumBaseType type ) ;
    
    extern wxString AlbumBaseNames[AT_NbrAlbumTypes];

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
        AT_TopContentPadding,
        AT_BottomContentPadding,
        AT_LeftContentPadding,
        AT_RightContentPadding,
        AT_FontType,
        AT_FontName,
        AT_FontFamily,
        AT_FontSize,
        AT_FontWeight,
        AT_FontColor,
        AT_FontStyle,
        AT_NbrAttrTypes,
        AT_NOTYPE
    } AlbumAttrType;

extern const char* AttrNameStrings[ AT_NbrAttrTypes ] ;


    typedef enum
    {
        AT_OK = 0,
        AT_WARING,
        AT_FATAL 
    } NodeStatus;

    AlbumBaseType FindAlbumBaseType( wxString name );

    /**
     * @brief Performs the initial instantiantion of all the sTart up data.
     *
     **************************************************/
    void InitDesignDefs( );

    LayoutBase* GetSelectedNodePage( );

    AlbumBase* MakeNode( wxXmlNode* node );

    // Conversion factor to convert from Pixels to MM. 
    // Screen units are in pixels. Album Design elements are in mm.
    extern wxRealPoint  PpMM;



}

#endif
