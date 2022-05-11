/**
 * @file DesignDefs.h
 * @author Eddie Monroe ()
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef DesignDefs_H
#define DesignDefs_H

#include <wx/string.h>

namespace Design {

    class DesignData;
    class LayoutBase;
    class Album;
    
    Album* GetAlbum( void );

    DesignData* GetDesignData( void );

    //DesignData* GetDesignData( DesignData* designData );

    DesignData* NewDesignData( void );

    typedef enum
    {
        AT_Album = 0,
        AT_Page,
        AT_Row,
        AT_Col,
        AT_Title,
        AT_TitlePage,
        AT_Stamp,
        AT_NbrAlbumTypes,
        AT_None = 999
    } AlbumBaseType;

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
        AT_ID,
        AT_Link,
        AT_NbrAttrTypes,
        AT_NOTYPE
    } AlbumAttrType;

    extern const char* AttrNameStrings[ AT_NbrAttrTypes ];

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

   // LayoutBase* MakeNode( AlbumBaseType type, wxXmlNode* node );


    // wxString GetAttribute( AlbumBaseType type );
    // double GetAttributeDbl( AlbumBaseType type );
    // void SetAttrStr( AlbumBaseType type, wxString val );
    // void SetAttrDbl( AlbumBaseType type, double val );


}

#endif
