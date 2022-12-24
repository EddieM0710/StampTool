/**
 * @file Defs.h
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

#ifndef Defs_H
#define Defs_H

#include <wx/string.h>
//#include "gui/GeneratorData.h"
#include <wx/gdicmn.h>

class GeneratorData;

//#include "utils/Settings.h"
//#include "utils/Project.h"
#define MaxRecentEntries = 8

//extern GeneratorData* m_generatorData;

extern bool Dirty;

void SetDirty( bool state = true);
bool IsDirty();
namespace Utils { class Project; };
namespace Utils { class Settings; };
class GeneratorData;
class DesignTreeCtrl;
class CatalogTreeCtrl;
class AlbumImagePanel;
namespace Design { class DesignData; };
namespace Catalog { class CatalogVolumeData;  };
/**
 * @brief Get the Settings data 
 * 
 * @return CatalogVolumeData* 
 **************************************************/
Utils::Settings* GetSettings( );

Utils::Project* GetProject( );

GeneratorData* GetGeneratorData();
Design::DesignData* GetDesignData() ;
Catalog::CatalogVolumeData* GetCatalogVolumeData() ;
CatalogTreeCtrl* GetCatalogTreeCtrl();
DesignTreeCtrl* GetDesignTreeCtrl();
AlbumImagePanel* GetAlbumImagePanel();

#define RealPoint wxRealPoint  
#define RealSize wxRealPoint 
class RealRect
{
    public:
    RealRect( RealPoint posR, RealPoint sizeR ) { pos = posR; size = sizeR; };
    RealRect( double x, double y, double width, double height ) { SetPosition(x,y), SetSize(width,height);; };
    RealPoint GetPosition( ) { return pos; };
    RealPoint GetSize( ) { return size; };
    void SetPosition( double x, double y) { pos.x = x; pos.y = y;};
    void SetPosition( RealPoint posR ) { pos = posR; };
    void SetSize( double width, double height) { size.x = width; size.y = height;};
    void SetSize( RealPoint sizeR ) { size = sizeR; };
    double GetX( ) { return pos.x; };
    double GetY( ) { return pos.y; };
    double GetHeight( ) { return size.x; };
    double GetWidth( ) { return size.y; };
    void SetX( double x ) { pos.x = x; };
    void SetY( double y ) { pos.y = y; };
    void SetWidth( double width ) { pos.x = width; };
    void SetHeight( double height ) { pos.y = height; };
    RealPoint pos;
    RealPoint size;
};

/**
 * @brief  Returns Ascii "true" or "false" based on bool b
 *
 * @param  b
 * @return const wxString
 **************************************************/
inline const wxString Bool2String( bool b )
{
    return b ? "true" : "false";
};

/**
 * @brief Returns bool true or false given Ascii str "true"
 *
 * @param  str
 * @return true  if str == "true"
 * @return false   if str == "false" ( or anything else)
 **************************************************/
inline const bool String2Bool( wxString str )
{
    return str.CmpNoCase( "true" ) ? false : true;
};

/**
 * @brief Performs the initial instantiantion of all the sTart up data.
 *
 **************************************************/
void InitDefs( );


/**
 * @brief write a message and exit if fatal
 *
 * @param funct  call function
 * @param err  error string
 * @param fatal  exit on fatal
 **************************************************/
void ReportError( wxString funct, wxString err, bool fatal = true );


#endif
