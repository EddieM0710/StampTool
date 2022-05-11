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
#include "CatalogData.h"
//#include "AECmdData.h"
#include "Settings.h"

#include "Defs.h"
#include "CatalogData.h"
#include "Settings.h"

bool Dirty = false;

void SetDirty( bool state){Dirty = state;};
bool IsDirty(){return Dirty;};

/**
 * @brief Global pointer to CatalogData data object
 *
 */
CatalogData* G_CatalogData;


Settings* G_Settings;

Settings* GetSettings( ) { return G_Settings; };

CatalogData* GetCatalogData( void ) { return G_CatalogData; };
// AECmdData* GetAECmdData( void ) { return G_AECmdData; };

// AECmdData* SetAECmdData( AECmdData* aeCmdData )
// {
//     if ( aeCmdData != G_AECmdData )
//     {
//         delete G_AECmdData;
//         G_AECmdData = (AECmdData*)0;
//     }
//     G_AECmdData = aeCmdData;
// };

CatalogData* SetCatalogData( CatalogData* catalogData )
{
    if ( catalogData != G_CatalogData )
    {
        delete G_CatalogData;
        G_CatalogData = (CatalogData*)0;
    }
    G_CatalogData = catalogData;
};

CatalogData* NewCatalogData( )
{
    return ( new CatalogData( ) );
};



const wxString ST_StatusStrings[ ST_NbrTypes ]
= { wxT( "Checked" ), wxT( "Unchecked" )};

const wxString FT_FormatStrings[ FT_NbrTypes ]
= { wxT( "Unknown" ),
    wxT( "Stamp" ),
    wxT( "Se-tenant" ),
    wxT( "Mini Sheet" ),
    wxT( "Souvenir Sheet" ),
    wxT( "Booklet" ),
    wxT( "Booklet Pane" ),
    wxT( "Gutter Pair" ),
    wxT( "Stamp with Attached Label" ),
    wxT( "Tete-Beche" ) };
const wxString ET_EmissionStrings[ ET_NbrTypes ]
= { wxT( "Unknown" ),
    wxT( "Commemorative" ),
    wxT( "Definitive" ),
    wxT( "Hunting Permit" ),
    wxT( "Revenue" ),
    wxT( "Air Post" ),
    wxT( "Air Post Official" ),
    wxT( "Air Post Semi-Postal" ),
    wxT( "ATM labels" ),
    wxT( "Cinderella" ),
    wxT( "Illegal" ),
    wxT( "Insured Letter"  ),
    wxT( "Military" ),
    wxT( "Newspaper" ),
    wxT( "Official" ),
    wxT( "Parcel Post" ),
    wxT( "Personal Delivery" ),
    wxT( "Personalized" ),
    wxT( "Postage Due" ),
    wxT( "Postal Tax" ),
    wxT( "Precancelled" ),
    wxT( "Private" ),
    wxT( "Regional" ),
    wxT( "Registration" ),
    wxT( "Semi-Postal" ),
    wxT( "War Tax" )};

const wxString DT_DataNames[ DT_NbrTypes ] = {
    wxT( "ID Nbr" ),      wxT( "Name" ),          wxT( "Country" ),
    wxT( "Series" ),      wxT( "Catalog Codes" ), wxT( "Issued on" ),
    wxT( "Expiry date" ), wxT( "Width" ),         wxT( "Height" ),
    wxT( "Paper" ),       wxT( "Watermark" ),     wxT( "Emission" ),
    wxT( "Format" ),      wxT( "Perforation" ),   wxT( "Printing" ),
    wxT( "Gum" ),         wxT( "Currency" ),      wxT( "FaceValue" ),
    wxT( "Print run" ),   wxT( "Variant" ),       wxT( "Score" ),
    wxT( "Accuracy" ),    wxT( "Colors" ),        wxT( "Themes" ),
    wxT( "Description" ), wxT( "Link" ),          wxT( "Status" ),
    wxT( "Background" )
};

const wxString DT_XMLDataNames[ DT_NbrTypes ] = {
    wxT( "ID_Nbr" ),      wxT( "Name" ),         wxT( "Country" ),
    wxT( "Series" ),      wxT( "Catalog_Codes" ), wxT( "Issued_on" ),
    wxT( "Expiry_date" ), wxT( "Width" ),         wxT( "Height" ),
    wxT( "Paper" ),       wxT( "Watermark" ),     wxT( "Emission" ),
    wxT( "Format" ),      wxT( "Perforation" ),   wxT( "Printing" ),
    wxT( "Gum" ),         wxT( "Currency" ),      wxT( "FaceValue" ),
    wxT( "Print_run" ),   wxT( "Variant" ),       wxT( "Score" ),
    wxT( "Accuracy" ),    wxT( "Colors" ),        wxT( "Themes" ),
    wxT( "Description" ), wxT( "Link" ),          wxT( "Status" ),
    wxT( "Background" )
};

wxArrayString CatalogNodeNames;
wxArrayString AlbumNodeNames;


void InitDefs( )
{
    CatalogNodeNames.Add( "Catalog" );
    CatalogNodeNames.Add( "Country" );
    CatalogNodeNames.Add( "Period" );
    CatalogNodeNames.Add( "Decade" );
    CatalogNodeNames.Add( "Year" );
    CatalogNodeNames.Add( "Emission" );
    CatalogNodeNames.Add( "Status" );
    CatalogNodeNames.Add( "Condition" );
    CatalogNodeNames.Add( "Stamp" );
    CatalogNodeNames.Add( "Specimen" );
    CatalogNodeNames.Add( "CatalogCode" );

     AlbumNodeNames.Add( "Album" );
     AlbumNodeNames.Add( "Page" );
     AlbumNodeNames.Add( "Row" );
     AlbumNodeNames.Add( "Col" );
     AlbumNodeNames.Add( "Title" );
     AlbumNodeNames.Add( "Stamp" );
     AlbumNodeNames.Add( "NbrAlbumTypes" );

}


/**
 * @brief String name used for wxXmlNodes.
 *
 */
const wxString CT_Names[ CT_NbrTypes ] = { wxT( "Name" ),
wxT( "PreferredCatalog" ), wxT( "ImageDirectory" ) };

const wxString ItemDataNames[ IDT_NbrTypes ]
= { wxT( "Type" ), wxT( "Condition" ), wxT( "Value" ), wxT( "Location" ),
    wxT( "Remarks" ) };


const wxString CC_CatalogCodeNames[ CC_NbrTypes ]
= { wxT( "ID" ), wxT( "Country" ), wxT( "Catalog" ), };


CatalogNodeType FindCatalogNodeType( wxString name )
{
    wxString baseName;

    int cnt = CatalogNodeNames.GetCount( );
    for ( int i = 0; i < cnt; i++ )
    {
        baseName = CatalogNodeNames.Item( i );
        if ( !name.Cmp( baseName ) )
        {
            return ( CatalogNodeType )i;
        }
    }
    return ( CatalogNodeType )-1;
};

AlbumNodeType FindAlbumNodeType( wxString name )
{
    wxString baseName;

    int cnt =AlbumNodeNames.GetCount( );
    for ( int i = 0; i < cnt; i++ )
    {
        baseName = AlbumNodeNames.Item( i );
        if ( !name.Cmp( baseName ) )
        {
            return ( AlbumNodeType )i;
        }
    }
    return ( AlbumNodeType )-1;
};