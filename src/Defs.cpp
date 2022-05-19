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
#include "DesignDefs.h"
#include "CatalogData.h"
#include "Settings.h"
#include "utils/Project.h"
#include "AlbumGenApp.h"


wxDECLARE_APP( AlbumGenApp );

bool Dirty = false;

void SetDirty( bool state ) { Dirty = state; };
bool IsDirty( ) { return Dirty; };

// global declaration of application data 
GeneratorData* m_generatorData;

Utils::Settings* GetSettings( )
{

    return wxGetApp( ).GetGeneratorDate()->GetSettings( );

};

Utils::Project* GetProject( )
{
    return wxGetApp( ).GetGeneratorDate()->GetProject( );
}

inline GeneratorData* GetGeneratorData(){ return wxGetApp( ).GetGeneratorDate();};

Design::DesignData* GetDesignData() { return GetGeneratorData()->GetDesignData(); };
Catalog::CatalogData* GetCatalogData() { return GetGeneratorData()->GetCatalogData(); };
CatalogTreeCtrl* GetCatalogTreeCtrl(){ return GetGeneratorData()->GetCatalogTreeCtrl();};
DesignTreeCtrl* GetDesignTreeCtrl( ){return GetGeneratorData()->GetDesignTreeCtrl();};
AlbumImagePanel* GetAlbumImagePanel(){return GetGeneratorData()->GetAlbumImagePanel();};

void InitDefs( )
{
    Catalog::InitCatalogDefs( );
    Design::InitDesignDefs( );
}

void ReportError(  wxString funct, wxString msg, bool fatal )
{
    // if ( fatal )    
    // {
    //     std::cout << "Fatal Error: " <<funct << " " << msg << " \n";
    //     exit(1);
    // }
    std::cout << "Warning: " <<funct << " " << msg << " \n";
}