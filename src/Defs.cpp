/**
 * @file Defs.cpp
 * @author Eddie Monroe (you@domain.com)
 * @brief Resting place for Global stuff
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 */

 // For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Defs.h"
#include "CatalogDefs.h"
#include "AlbumDefs.h"
#include "CatalogData.h"
#include "Settings.h"
#include "utils/Project.h"
#include "AlbumGenApp.h"
#include "gui/GeneratorData.h"


wxDECLARE_APP( AlbumGenApp );

bool Dirty = false;

void SetDirty( bool state ) { Dirty = state; };
bool IsDirty( ) { return Dirty; };


Utils::Settings* GetSettings( )
{
    Utils::Project* project = GetProject( );
    if ( project )
    {
        return project->GetLSettings( );
    }
    return ( Utils::Settings* )0;
};

inline Utils::Project* GetProject( )
{
    return wxGetApp( ).GetProject( );
}

inline GeneratorData* GetGeneratorData(){ return GetProject()->GetGeneratorData();};

Layout::AlbumData* GetAlbumData() { return GetGeneratorData()->GetAlbumData(); };
Catalog::CatalogData* GetCatalogData() { return GetGeneratorData()->GetCatalogData(); };
CatalogTreeCtrl* GetCatalogTreeCtrl(){ return GetGeneratorData()->GetCatalogTreeCtrl();};
AlbumTreeCtrl* GetAlbumTreeCtrl( ){return GetGeneratorData()->GetAlbumTreeCtrl();};


void InitDefs( )
{
    Catalog::InitCatalogDefs( );
    Layout::InitAlbumDefs( );
}

void ReportError(  wxString funct, wxString msg, bool fatal )
{
    if ( fatal )    
    {
        std::cout << "Fatal Error: " <<funct << " " << msg << " \n";
        exit(1);
    }
    std::cout << "Warning: " <<funct << " " << msg << " \n";
}