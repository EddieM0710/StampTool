/**
 * @file AlbumDefs.h
 * @author Eddie Monroe ()
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef AlbumDefs_H
#define AlbumDefs_H

#include <wx/string.h>

namespace Layout {

    class AlbumData;
    class LayoutNode;
    class Album;
    
    Album* GetAlbum( void );

    AlbumData* GetAlbumData( void );

    AlbumData* SetAlbumData( AlbumData* albumData );

    AlbumData* NewAlbumData( void );

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
    } AlbumNodeType;

    extern wxString AlbumNodeNames[AT_NbrAlbumTypes];

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
        AT_NbrAttrTypes
    } AlbumAttrType;

    extern const char* AttrNameStrings[ AT_NbrAttrTypes ];

    typedef enum
    {
        AT_OK = 0,
        AT_WARING,
        AT_FATAL 
    } AlbumNodeStatus;

    AlbumNodeType FindAlbumNodeType( wxString name );

    /**
     * @brief Performs the initial instantiantion of all the sTart up data.
     *
     **************************************************/
    void InitAlbumDefs( );

    LayoutNode* GetSelectedNodePage( );

   // LayoutNode* MakeNode( AlbumNodeType type, wxXmlNode* node );


    // wxString GetAttribute( AlbumNodeType type );
    // double GetAttributeDbl( AlbumNodeType type );
    // void SetAttrStr( AlbumNodeType type, wxString val );
    // void SetAttrDbl( AlbumNodeType type, double val );

  

}

#endif
