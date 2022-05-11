/**
 * @file Defs.h
 * @author Eddie Monroe ()
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef Defs_H
#define Defs_H

#include <wx/string.h>
//#include "utils/Settings.h"
//#include "utils/Project.h"
#define MaxRecentEntries = 8

extern bool Dirty;

void SetDirty( bool state = true);
bool IsDirty();
namespace Utils { class Project; };
namespace Utils { class Settings; };
class GeneratorData;
class DesignTreeCtrl;
class CatalogTreeCtrl;
namespace Design { class DesignData; };
namespace Catalog { class CatalogData;  };
/**
 * @brief Get the Settings data 
 * 
 * @return CatalogData* 
 **************************************************/
Utils::Settings* GetSettings( );

Utils::Project* GetProject( );

GeneratorData* GetGeneratorData();
Design::DesignData* GetDesignData() ;
Catalog::CatalogData* GetCatalogData() ;
CatalogTreeCtrl* GetCatalogTreeCtrl();
DesignTreeCtrl* GetDesignTreeCtrl();

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
