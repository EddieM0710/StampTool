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

    AlbumData* GetAlbumData( void );

    AlbumData* SetAlbumData( AlbumData* catalogData );

    AlbumData* NewAECmdData( void );

    typedef enum
    {
        AT_Album = 0,
        AT_Page,
        AT_Row,
        AT_Col,
        AT_Title,
        AT_Stamp,
        AT_NbrAlbumTypes
    } AlbumNodeType;

    AlbumNodeType FindAlbumNodeType( wxString name );

    /**
     * @brief Performs the initial instantiantion of all the sTart up data.
     *
     **************************************************/
    void InitAlbumDefs( );
}
#endif
