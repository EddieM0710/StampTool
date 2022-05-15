/**
 * @file GeneratorData.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "gui/GeneratorData.h" 
#include "catalog/CatalogDefs.h"
#include "gui/DesignTreeCtrl.h"
#include "gui/CatalogTreeCtrl.h"
#include "utils/Settings.h"
#include "utils/Project.h"
#include "odt/ODTDefs.h"
#include "odt/Document.h"
#include "design/DesignData.h"
#include "catalog/CatalogData.h"


//********************(-----------***************
Utils::Settings* GeneratorData::GetSettings( )
{
    return  m_settings;
};

//***************-----------***************
void GeneratorData::SetSettings( Utils::Settings* settings )
{
    m_settings = settings;
};



//********************(-----------***************

Utils::Project* GeneratorData::GetProject( )
{
    return  m_project;
};

//***************-----------***************

void GeneratorData::SetProject( Utils::Project* project )
{
    m_project = project;
};

    void GeneratorData::SetCatalogData( Catalog::CatalogData* catalogData )
    {
        if ( catalogData != m_catalogData )
        {
            m_catalogData->~CatalogData();
            m_catalogData = ( Catalog::CatalogData* )0;
        }
        m_catalogData = catalogData;
    };

void GeneratorData::LoadCatalogData( wxString catalogFilename )
{
    m_catalogData = Catalog::NewCatalogData( );
    m_catalogData->LoadXML( catalogFilename );
}

Design::DesignData* GeneratorData::NewDesignData( void )
{

    if ( m_designData )
    {
        delete m_designData;

        Utils::StampList* stampList = GetStampAlbumCatalogLink( );
        DesignTreeCtrl* designTree = GetDesignTreeCtrl( );
        designTree->DeleteAllItems( );
        stampList->Clear( );
    }
    m_designData = new Design::DesignData( );
    return m_designData;
}



void GeneratorData::LoadDefaultDesignData( )
{
    NewDesignData( );
    m_designData->LoadDefaultDocument( );
}


// Load the Catalog and design data then populate trees
void GeneratorData::LoadData( )
{
    LoadCatalogData( );
    LoadDesignData( );

    LoadDesignTree( );
    LoadCatalogTree( );
    InitODTDocument( );
}

////*****

void GeneratorData::LoadCatalogData( )
{
    wxString catalogFilename = m_project->GetCatalogFilename( );
    LoadCatalogData( catalogFilename );
}



void GeneratorData::LoadCatalogTree( )
{
    GetCatalogTreeCtrl( )->LoadTree( );
}


void GeneratorData::LoadDesignData( )
{
    NewDesignData( );
    wxString albumFilename = m_project->GetDesignFilename( );
    m_designData->LoadXML( albumFilename );
}

void GeneratorData::LoadDesignTree( )
{
    GetDesignTreeCtrl( )->LoadTree( );
}

void GeneratorData::InitODTDocument( )
{
    ODT::Document* odtDoc = new ODT::Document( );
    SetODTDocument( odtDoc );
}

ODT::Document* GeneratorData::GetODTDocument( )
{
    return m_ODTDoc;
};

//*****

void GeneratorData::SetODTDocument( ODT::Document* doc )
{
    m_ODTDoc = doc; SetDirty( );
};

void GeneratorData::InitLoad( )
{
    if ( GetSettings( )->GetLoadLastFileAtStartUp( ) )
    {
        m_project->LoadProjectXML( );
        LoadData( );
    }
}