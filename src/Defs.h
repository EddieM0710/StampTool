/**
 * @file Defs.h
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

#ifndef Defs_H
#define Defs_H

#include <wx/string.h>
#include <wx/gdicmn.h>

class AppData;

#define MaxRecentEntries = 8

class StampToolFrame;
class AlbumTreeCtrl;
class CatalogTreeCtrl;
class CatalogTOCTreeCtrl;
class AlbumTOCTreeCtrl;
class AlbumImagePanel;
namespace Design {
    class AlbumVolume;
};
namespace Design {
    class AlbumData;
};
namespace Utils {
    class FontList;
};
namespace Utils {
    class StampList;
};
namespace Catalog {
    class CatalogVolume;
};
namespace Catalog {
    class CatalogData;
};
namespace Inventory {
    class CollectionList;
};
namespace Catalog {
    class StampMountData;
};

namespace Utils {
    class Settings;
};

namespace Utils {
    class Project;
};





Design::AlbumData* GetAlbumData( );

AlbumImagePanel* GetAlbumImagePanel( );

//CatalogTreeCtrl* GetAlbumPageTreeCtrl( );

AlbumTOCTreeCtrl* GetAlbumTOCTreeCtrl( );

AlbumTreeCtrl* GetAlbumTreeCtrl( );

Design::AlbumVolume* GetAlbumVolume( );

AppData* GetAppData( );

Catalog::CatalogData* GetCatalogData( );

CatalogTOCTreeCtrl* GetCatalogTOCTreeCtrl( );

CatalogTreeCtrl* GetCatalogTreeCtrl( );

Catalog::CatalogVolume* GetCatalogVolume( );

Inventory::CollectionList* GetCollectionList( );

Utils::FontList* GetFontList( );

StampToolFrame* GetFrame( );

Utils::Project* GetProject( );

Utils::Settings* GetSettings( );

Utils::StampList* GetStampAlbumCatalogLink( );

Catalog::StampMountData* GetStampMountData( );


#define RealPoint wxRealPoint  
#define RealSize wxRealPoint
class RealRect
{
public:



    RealRect( RealPoint posR, RealSize sizeR ) {
        pos = posR; size = sizeR;
    };
    RealRect( double x, double y, double width, double height ) {
        SetPosition( x, y ), SetSize( width, height );;
    };
    RealPoint GetPosition( ) {
        return pos;
    };
    RealPoint GetSize( ) {
        return size;
    };
    void SetPosition( double x, double y ) {
        pos.x = x; pos.y = y;
    };
    void SetPosition( RealPoint posR ) {
        pos = posR;
    };
    void SetSize( double width, double height ) {
        size.x = width; size.y = height;
    };
    void SetSize( RealPoint sizeR ) {
        size = sizeR;
    };
    double GetX( ) {
        return pos.x;
    };
    double GetY( ) {
        return pos.y;
    };
    double GetHeight( ) {
        return size.x;
    };
    double GetWidth( ) {
        return size.y;
    };
    void SetX( double x ) {
        pos.x = x;
    };
    void SetY( double y ) {
        pos.y = y;
    };
    void SetWidth( double width ) {
        pos.x = width;
    };
    void SetHeight( double height ) {
        pos.y = height;
    };
    RealPoint pos;
    RealPoint size;





};

/**
 * @brief  Returns Ascii "true" or "false" based on bool b
 *
 * @param  b
 * @return const wxString
 */
inline const wxString Bool2String( bool b )
{
    return b ? "true" : "false";
};

/**
 * @brief Returns bool true or false given Ascii str "true"
 *
 * @param  str
 * @return true  if str == "true"
 * @return false   if str == "false" ( or anything else )
 */
inline const bool String2Bool( wxString str, bool defaultStr = false )
{
    if ( str.CmpNoCase( "true" ) )
    {
        return false;
    }
    else if ( str.CmpNoCase( "false" ) )
    {
        return true;
    }
    else
    {
        return defaultStr;
    }
};

inline const double String2Dbl( wxString str, double defval = 0.0 )
{
    double val;
    if ( str.ToDouble( &val ) )
    {
        return val;
    }
    return defval;
}

inline const wxString Dbl2String( double val )
{
    return wxString::Format( "%.2f", val );
}

/**
 * @brief Performs the initial instantiantion of all the sTart up data.
 *
 */
void InitDefs( );


/**
 * @brief write a message and exit if fatal
 *
 * @param funct  call function
 * @param err  error string
 * @param fatal  exit on fatal
 */
void ReportError( wxString funct, wxString err, bool fatal = true );

#endif
